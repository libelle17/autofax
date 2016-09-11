#include "konsole.h"
#include "DB.h"
extern class linstcl linst;

const char *Txdbcl::TextC[T_dbMAX+1][Smax]={
  // T_DB_wird_initialisiert
  {"DB wird initialisiert","DB is being initialized"},
  // T_Fehler_db
  {"Fehler ","Error "},
  // T_beim_Initialisieren_von_MySQL
  {" beim Initialisieren von MySQL: "," initializing MySQL: "},
  // T_Fehler_dp
  {"Fehler: ","Error: "},
  // T_bei_Befehl
  {" bei Befehl: "," at command: "},
  // T_Versuche_mysql_zu_starten
  {": => Versuche mysql zu starten ...",": => trying to start mysql ..."},
  // T_MySQL_erfolgreich_gestartet
  {"MySQL erfolgreich gestartet.","Started MySQL successfully."},
  // ": => Versuche Datenbank `"
  {": => Versuche Datenbank `",": => Trying to install database `"},
  // T_zu_erstellen
  {"` zu erstellen ...","` ..."},
  // T_Fehler_beim_Verbinden
  {"Fehler beim Verbinden: ","Error connecting: "},
  // T_Erfolg_beim_Initialisieren_der_Verbindung_zu_mysql
  {"Erfolg beim Initialisieren der Verbindung zu MySQL!","Success initializing the connection to MySQL!"},
  // T_Benoetige_MySQL_Passwort_fuer_Benutzer_root_fuer_Befehl
  {"MySQL-Passwort fuer Benutzer 'root' (wird benoetigt fuer Befehl: ","MySQL password for user 'root' (is needed for command: "},
  // T_Das_MySQL_Passwort_fuer_Benutzer_root_ist_leer_Wollen_Sie_eines_festlegen
  {"Das MySQL-Passwort fuer Benutzer 'root' ist leer. Wollen Sie eines festlegen?",
   "The MySQL password for the user 'root' is empty. Do You want to give one?"},
  // T_j
  {"j","y"},
  // T_Bitte_geben_Sie_ein_MySQL_Passwort_fuer_Benutzer_root_ein
  {"Bitte geben Sie ein MySQL-Passwort fuer Benutzer 'root' ein: ","Please indicate a mysql password for user 'root': "},
  // T_Bitte_geben_Sie_das_MySQL_Passwort_fuer_Benutzer_root_erneut_ein
  {"Bitte geben Sie das MySQL-Passwort fuer Benutzer 'root' erneut ein: ","Please confirm the mysql password for user 'root': "},
  // T_Fuehre_aus_db
  {"Fuehre aus: ","Executing: "},
  // T_falsche_Fehlernr
  {"falsche Fehlernr ","wrong Errorno "},
  // T_bei_der_Abfrage_der_Spaltenlaenge_bei_Tabelle
  {" bei der Abfrage der Spaltenlaenge bei Tabelle: "," during query of the column width at table: "},
  // T_und_Feld,
  {" und Feld: "," and field: "},
  // T_mit
  {" mit: "," with: "},
  // T_bei_Abfrage
  {" bei Abfrage: "," in query: "},
  // T_Fehler_beim_Pruefen_auf_Vorhandensein_des_Datensatzes
  {"Fehler beim Pruefen auf Vorhandensein des Datensatzes: ","Error while checking the existence of entry: "},
  // T_Programmfehler
  {"Programmfehler: ","Bug: "},
  // T_nicht_anfangen_bei_isql_empty_Aufruf_von_RS_insert_beim_ersten_Mal_ohn_anfangen_bei
  {" !anfangen bei isql.empty() (Aufruf von RS::insert beim ersten Mal ohne anfangen)! bei: ",
    " !anfangen at isql.empty() (call of RS::insert the first timee without anfangen)! at: "},
  // T_Datenbank_nicht_zu_oeffnen
  {"Datenbank nicht zu oeffnen","could not open database"},
  // T_Erweitere_Feld
  {"Erweitere Feld: ","Enlarging field: "},
  // T_von
  {" von: "," from: "},
  // T_auf
  {" auf: "," to: "},
  // T_Aendere_Feld
  {"Aendere Feld: ","Changing field: "},
  // T_Pruefe_Tabelle
  {"Pruefe Tabelle: '","Checking table: '"},
  // T_Lesespalten
  {"lesespalten()","readcolumns()"},
  {"",""}
};

Txdbcl::Txdbcl() {TCp=(const char* const * const * const *)&TextC;}

class Txdbcl Txd;

// Datenbanknamen aus sql-String extrahieren
svec holdbaussql(string sql) 
{
  svec erg;
  string db;
  size_t runde=0;
  while (1) {
    runde++;
    string SQL;
    transform(sql.begin(),sql.end(),std::back_inserter(SQL),::toupper);
    size_t pfrom=SQL.find("FROM ");
    size_t pjoin=SQL.find("JOIN ");
    size_t ab=pfrom<pjoin?pfrom:pjoin;
    if (ab!=string::npos) {
      ab+=5;
      size_t bis=string::npos;
      if (sql[ab]=='`' || sql[ab]=='[' || sql[ab]=='\"') ab++;
      bis=SQL.find_first_of((string(" .,;()'\"`]:{}")+(char)9+(char)10+(char)13).c_str(),ab);
      if (bis!=string::npos) 
        db=sql.substr(ab,bis-ab);
      else
        db=sql.substr(ab);
      if (!db.empty()) {
        uchar alt=0;
        for(size_t j=0;j<erg.size();j++) {
          if (erg[j]==db) {alt=1;break;}
        }
        if (!alt) erg<<db;
      } // if (!db.empty()) 
      if (bis==string::npos) break;
      sql=sql.substr(bis);
    } else break; // if (ab!=string::npos) 
  } // while (1)
  return erg;
} // holdbaussql

Feld::Feld(const string& name, string typ, const string& lenge, const string& prec, 
    const string& comment, bool obind, bool obauto, bool nnull, string vdefa):
  name(name),
  typ(typ),
  lenge(lenge),
  prec(prec),
  comment(comment),
  obind(obind),
  obauto(obauto),
  nnull(nnull),
  defa(vdefa) // Namensdifferenz hier noetig, sonst wird im Konstruktur die falsche Variable bearbeitet
{
  if (!obauto) if (defa.empty()) {
    transform(typ.begin(),typ.end(),typ.begin(),::toupper);
    if (typ.find("INT")!=string::npos || typ=="LONG" || typ=="DOUBLE" ||typ=="FLOAT"  )
      defa="0";
    else if (typ=="DATE" || typ=="DATETIME" || typ=="TIME" ||typ=="TIMESTAMP")
      defa="0000-00-00";
    else if (typ=="YEAR")
      defa="0000";
  }
} // Feld(const string& name, const string& typ, const string& lenge, const string& prec, string comment, bool vind, bool vobauto, bool vnnull, string vdefa):

Index::Index(const string& name, Feld *felder, int feldzahl) :
  name(name),
  feldzahl(feldzahl),
  felder(felder)
{}

  Tabelle::Tabelle(const std::string& name, Feld *vfelder, int vfeldzahl, Index *vindices, int vindexzahl, string comment, const string& engine,
                   const string& charset, const string& collate, const string& rowformat)
:   name(name),
  comment(comment),
  felder(vfelder),
  feldzahl(vfeldzahl),
  indices(vindices),
  indexzahl(vindexzahl),
  engine(engine),
  charset(charset),
  collate(collate),
  rowformat(rowformat)
{}

// statische Variable, 1= mariadb=geprueft
uchar DB::oisok=0;

DB::DB() 
{
}

DB::DB(DBSTyp nDBS, const string& phost, const string& puser, const string& ppasswd, const string& uedb, unsigned int port, 
       const char *const unix_socket, unsigned long client_flag,
    int obverb,int oblog,int versuchzahl, uchar ggferstellen)
{
  init(nDBS,phost.c_str(),puser.c_str(),ppasswd.c_str(),uedb.c_str(),port,unix_socket,client_flag,obverb,oblog,versuchzahl,
  ggferstellen);
}

DB::DB(DBSTyp nDBS, const char* const phost, const char* const puser,const char* const ppasswd, const char* const prootpwd,
       const char* const uedb, unsigned int port, const char *const unix_socket, unsigned long client_flag,int obverb,int oblog,
       int versuchzahl, uchar ggferstellen): rootpwd(prootpwd)
{
  init(nDBS,phost,puser,ppasswd,uedb,port,unix_socket,client_flag,obverb,oblog,versuchzahl,ggferstellen);
}

DB::DB(DBSTyp nDBS, const char* const phost, const char* const puser,const char* const ppasswd, const char* const uedb, 
       unsigned int port, const char *const unix_socket, unsigned long client_flag,int obverb,int oblog,int versuchzahl,uchar ggferstellen)
{
  init(nDBS,phost,puser,ppasswd,uedb,port,unix_socket,client_flag,obverb,oblog,versuchzahl,ggferstellen);
}

void DB::init(DBSTyp nDBS, const char* const phost, const char* const puser,const char* const ppasswd, const char* const uedb, 
              unsigned int port, const char *const unix_socket, unsigned long client_flag,int obverb,int oblog,unsigned versuchzahl,
              uchar ggferstellen)
{
  DBS = nDBS;
  fehnr=0;
  string Frage;
  Log(string(Txd[T_DB_wird_initialisiert]),obverb>1,oblog);
  host=phost;
  user=puser;
  passwd=ppasswd;
  uchar installiert=0;
  uchar datadirda=0;
  switch (DBS) {
    case MySQL:
#ifdef linux
      switch (pruefipr()) {
        case zypper: case apt:
          db_systemctl_name="mysql";
          break;
        case dnf: case yum:
          db_systemctl_name="mariadb";
          break;
        default: break;
      }
      if (!oisok) {
        // schauen, ob die Exe-Datei da ist 
        for (int iru=0;iru<2;iru++) {
          installiert=1;
          // wenn nicht gefunden ...
          if (systemrueck("sudo env \"PATH=$PATH\" which mysqld 2>/dev/null",obverb,oblog)) {
            svec frueck;
            // .. und auch hier nicht gefunden ...
            systemrueck("find /usr/sbin /usr/bin /usr/libexec -executable -size +1M -name mysqld",obverb,oblog, &frueck);
            if (!frueck.size()) 
              // .. dann wohl nicht installiert
              installiert=0;
          }
          if (installiert) 
            if (systemrueck("which mysql 2>/dev/null",obverb,oblog)) 
              installiert=0;
          if (installiert) break;
          //        systemrueck("which zypper && zypper -n in mariadb || { which apt-get && apt-get --assume-yes install mariadb-server; }",1,1);
          linst.doinst("mariadb",obverb,oblog);
        }
        // Datenverzeichnis suchen und pruefen
        if (installiert) {
          svec zrueck;
          if (!systemrueck("sed 's/#.*$//g' `mysql --help | sed -n '/Default options/{n;p}'` 2>/dev/null "
                "| grep datadir | cut -d'=' -f2",obverb,oblog,&zrueck)) {
            if (zrueck.size()) {
              datadir=zrueck[zrueck.size()-1];  
            } else {
              svec zzruck, zincldir;
              systemrueck("find /etc /etc/mysql ${MYSQL_HOME} -name my.cnf -printf '%p\\n' -quit", obverb,oblog,&zzruck);
              if (!zzruck.size())
                systemrueck("find ${HOME} -name .my.cnf -printf '%p\\n' -quit",obverb,oblog,&zzruck);
              if (zzruck.size()) {
                systemrueck("sudo cat "+zzruck[0]+" | sed 's/#.*$//g' | grep '!includedir' | sed 's/^[ \t]//g' | cut -d' ' -f2-", 
                    obverb,oblog,&zincldir); 
                for(size_t i=0;i<zincldir.size();i++) {
                  svec zzruck2;
                  systemrueck("sudo find "+zincldir[i]+" -not -type d",obverb,oblog,&zzruck2); // auch links
                  for(size_t i=0;i<zzruck2.size();i++) {
                    zzruck<<zzruck2[i];
                  }
                }
              }
              if(zzruck.size()) {
                for(size_t i=0;i<zzruck.size();i++) {
                  svec zrueck;
                  if (!systemrueck(("sudo sed 's/#.*$//g' '")+zzruck[i]+"' | grep datadir | cut -d'=' -f2",
                        obverb,oblog,&zrueck)) {
                    if (zrueck.size()) {
                      datadir=zrueck[zrueck.size()-1];  
                      break;
                    } // if (zrueck.size()) 
                  } // if (!systemrueck(("cat ")+zzruck[i]+" | sed 's/#.*$//g' | grep datadir | cut -d'=' -f2",obverb-1,oblog,&zrueck)) 
                } // for(size_t i=0;i<zzruck.size();i++) 
              } // if(zzruck.size()) 
            } // if (zrueck.size()) else
          } // if (!systemrueck("sed 's/#.*$//g' `mysql --help | sed -n '/Default options/{n;p}'` 2>/dev/null " ...
          gtrim(&datadir);
          // <<rot<<datadir<<schwarz<<endl;
          if (datadir.empty()) {
            datadir="/var/lib/mysql";
          }
          if (obverb) Log("datadir: "+blaus+datadir+schwarz,obverb,oblog);
          struct stat datadst;
          if (!lstat(datadir.c_str(), &datadst)) {
            if(S_ISDIR(datadst.st_mode)) {
              datadirda=1;
            } else {
              systemrueck("sudo rm -f '"+datadir+"'",1,1);
            }
          }
          if (!datadirda) {
            systemrueck("sudo `find /usr/local /usr/bin /usr/sbin -name mysql_install_db"+string(obverb?"":" 2>/dev/null")+"`",1,1);
            systemrueck("sudo systemctl start "+db_systemctl_name,obverb,oblog);
          }
          oisok=1;
        } // if (installiert)
      } // if (!oisok)

#endif
      conn = mysql_init(NULL);
      if (!conn) {
        this->ConnError=mysql_error(conn);
        //			printf("Fehler %u beim Erstellen einer MySQL-Verbindung: %s\n", mysql_errno(conn), *erg=mysql_error(conn));
        cerr<<Txd[T_Fehler_db]<<mysql_errno(conn)<<Txd[T_beim_Initialisieren_von_MySQL]<<this->ConnError<<endl;
        //			throw "Fehler beim Erstellen einer MySQL-Verbindung";
      } else {
        RS *rs;
        for(unsigned versuch=0;versuch<versuchzahl;versuch++) {
          //          <<"versuch: "<<versuch<<", conn: "<<conn<<", host: "<<host<<", user: "<<user<<", passwd "<<passwd<<", uedb: "<<uedb<<", port: "<<port<<", client_flag: "<<client_flag<<", obverb: "<<(int)obverb<<", oblog: "<<(int)oblog<<endl;
          fehnr=0;
          if (mysql_real_connect(conn, host.c_str(), user.c_str(), passwd.c_str(), uedb, port, unix_socket, client_flag)) {
            break;
          } else {
            switch ((fehnr=mysql_errno(conn))) {
              case 1044: // Access denied for user '<user>'@'<host>' to database '...' (Ubuntu)
              case 1045: // Access denied for user '<user>'@'<host>' (using password: YES)
              case 1698: // dasselbe auf Ubuntu
                for(unsigned aru=0;aru<1;aru++) {
                  for(unsigned iru=0;iru<2;iru++) {
                    cmd=string("sudo mysql -uroot -h'")+host+"' "+(rootpwd.empty()?"":string("-p")+rootpwd)+" -e \"GRANT ALL ON "+uedb+".* TO '"+
                      user+"'@'"+myloghost+"' IDENTIFIED BY '"+ersetze(passwd.c_str(),"\"","\\\"")+"' WITH GRANT OPTION\" 2>&1";
                    if (iru) break;
                    pruefrpw(cmd, versuchzahl);
                  } //                   for(unsigned iru=0;iru<2;iru++) {
                  myr.clear();
                  systemrueck(cmd,1,1,&myr);
                  miterror=1;
                  if (!myr.size()) miterror=0; else if (!strcasestr(myr[0].c_str(),"error")) miterror=0;
                  else {
                    Log(string(Txd[T_Fehler_dp])+rot+myr[0]+schwarz+Txd[T_bei_Befehl]+blau+cmd+schwarz,1,1);
                  }
                  if (!miterror) break;
                } // while (1)
                break;
              case 2002:
                if (!strcasecmp(host.c_str(),"localhost")) {
                  Log(string(Txd[T_Fehler_db])+drot+mysql_error(conn)+schwarz+Txd[T_Versuche_mysql_zu_starten],1,1);
#ifdef linux
                  systemrueck("sudo systemctl enable "+db_systemctl_name,1,1); 
                  svec gstat;
                  systemrueck("getfacl -e -t "+datadir+" 2>/dev/null | grep 'user[ \t]*"+"mysql"+"[ \t]*rwx' || true",obverb,oblog,&gstat);
                  if (!gstat.size()) {
                    systemrueck("sudo setfacl -Rm 'u:mysql:7' '"+datadir+"'",obverb,oblog);
                  }
                  if (!systemrueck("sudo systemctl start "+db_systemctl_name,1,1)) {
                    Log(Txd[T_MySQL_erfolgreich_gestartet],1,1);
                  }
#endif
                } //                 if (!strcasecmp(host.c_str(),"localhost")) {
                break;
              case 1049:
                if (ggferstellen) {
                  Log(string(Txd[T_Fehler_db])+drot+mysql_error(conn)+schwarz+Txd[T_Versuche_Datenbank]+drot+uedb+schwarz+Txd[T_zu_erstellen],1,1);
                  mysql_real_connect(conn, host.c_str(), user.c_str(), passwd.c_str(), 0, port, unix_socket, client_flag);
                  fehnr=mysql_errno(conn);
                  if (!fehnr) {
                    rs=new RS(this,string("CREATE DATABASE IF NOT EXISTS `")+uedb+"`");
                    fehnr=mysql_errno(conn);
                    if (!fehnr) {
                      //                    rs->Abfrage(string("USE `")+uedb+"`");
                      usedb(uedb);
                      fehnr=mysql_errno(conn);
                      if (!fehnr) {
                        delete(rs);
                      }
                    }
                  } else {
                    Log(string(Txd[T_Fehler_beim_Verbinden])+ltoan(fehnr),1,1);
                  } //                   if (!fehnr) {
                  // if (ggferstellen)
                } else {
                  Log(string(Txd[T_Fehler_db])+drot+mysql_error(conn)+schwarz,obverb,oblog);
                } // if (ggferstellen)
                break;
              case 0:
                break;
              default:
                Log(string(Txd[T_Fehler_db])+drot+ltoan(mysql_errno(conn))+schwarz+" "+blau+mysql_error(conn)+schwarz,1,1);
            } //             switch ((fehnr=mysql_errno(conn))) {
            if (!fehnr) break;
          } //           if (mysql_real_connect(conn, host.c_str(), user.c_str(), passwd.c_str(), uedb, port, unix_socket, client_flag))  else 
        } //         for(unsigned versuch=0;versuch<versuchzahl;versuch++) {
        if (!fehnr && conn) {
          Log(string(Txd[T_Erfolg_beim_Initialisieren_der_Verbindung_zu_mysql]),obverb>1,oblog);
          this->ConnError=NULL;
        } else {
          //			printf("Fehler %u beim Verbinden mit MySQL: %s\n", mysql_errno(conn), *erg= mysql_error(conn));
          this->ConnError=mysql_error(conn);
          //          cerr<<"Fehler "<<rot<<mysql_errno(conn)<<schwarz<<" beim Verbinden mit MySQL: "<<rot<<this->ConnError<<schwarz<<endl;
          mysql_close(conn);
          conn=0;
          //			throw "Fehler beim Verbinden mit MySQL";
        } // if (mysql_real_connect(conn, host, user, passwd.c_str(), uedb, port, unix_socket, client_flag))
      } // if (!conn) 
      dnb = '`'; dne = '`'; dvb = '\''; dve = '\'';
      db=uedb;
      break;
    case Postgres:
      break;
  } // switch (DBS) 
} // DB::DB(DBSTyp nDBS, const char* host, const char* user,const char* passwd, const char* db, unsigned int port, const char *unix_socket, unsigned long client_flag,const char** erg)

int DB::usedb(const string& db)
{
  int fehler=0; 
  switch (DBS) {
    case MySQL:
      fehler = mysql_select_db(conn,db.c_str());    
      break;
    case Postgres:
      break;
  }
  return fehler;
} // usedb

void DB::pruefrpw(const string& wofuer, unsigned versuchzahl)
{
  myloghost=!strcasecmp(host.c_str(),"localhost")||!strcmp(host.c_str(),"127.0.0.1")||!strcmp(host.c_str(),"::1")?"localhost":"%";
  for(unsigned versuch=0;versuch<versuchzahl;versuch++) {
    cmd=string("sudo mysql -uroot -h'")+host+"' "+(rootpwd.empty()?"":string("-p")+rootpwd)+" -e \"show variables like 'gibts wirklich nicht'\" 2>&1";
    myr.clear();
    systemrueck(cmd,-1,0,&myr);
    miterror=1;
    if (!myr.size()) miterror=0; else if (!strcasestr(myr[0].c_str(),"error")) miterror=0;
    else {
      //      Log(string(Txd[T_Fehler_dp])+rot+myr[0]+schwarz+Txd[T_bei_Befehl]+blau+cmd+schwarz,1,1);
    }
    if (miterror) {
      if (!nrzf) {
        rootpwd=Tippstring(string(Txd[T_Benoetige_MySQL_Passwort_fuer_Benutzer_root_fuer_Befehl])+"\n"+tuerkis+wofuer+schwarz+")",0);
        //                    if (rootpwd.empty()) return; // while (1)
        if (user=="root") passwd=rootpwd;
      }
    } else {
      break; // naechster Versuch
    } // if (miterror) KLA KLZ else KLA
  }
  if (rootpwd.empty()) setzrpw();
} // pruefrpw

void DB::setzrpw()
{
  string rootpw2, cmd;
  if (!nrzf) {
    while (1) {
      if (Tippob(Txd[T_Das_MySQL_Passwort_fuer_Benutzer_root_ist_leer_Wollen_Sie_eines_festlegen])) {
        rootpwd=Tippstring(Txd[T_Bitte_geben_Sie_ein_MySQL_Passwort_fuer_Benutzer_root_ein],&rootpwd);
        rootpw2=Tippstring(Txd[T_Bitte_geben_Sie_das_MySQL_Passwort_fuer_Benutzer_root_erneut_ein],&rootpw2);
        if (rootpw2==rootpwd && !rootpwd.empty()) {
          cmd=string("sudo mysql -uroot -h'")+host+"' -e \"GRANT ALL ON *.* TO 'root'@'"+myloghost+
            "' IDENTIFIED BY '"+ersetzAllezu(rootpwd,"\"","\\\"")+"' WITH GRANT OPTION\"";
          Log(string(Txd[T_Fuehre_aus_db])+blau+cmd+schwarz,1,1);
          int erg __attribute__((unused));
          erg=system(cmd.c_str());
          break;
        } // if (rootpw2==rootpwd ...
      } else {
        break;
      } // if (Tippob(Txd[T_Das_MySQL_Passwort_fuer_Benutzer_root_ist_leer_Wollen_Sie_eines_festlegen])) 
    } // while (1)
  } // if (!nrzf)
} // setzrpw

DB::~DB(void)
{
  switch (DBS) {
    case MySQL:
      if (!this->ConnError)
        mysql_close(conn);
      conn=0;
      break;
    case Postgres:
      break;
  }
} // DB::~DB(void)
/*
   int DB::Abfrage(string sql,const char** erg,uchar obstumm) 
   return Abfrage(sql.c_str(),erg,obstumm);
   }
   int DB::Abfrage(const char* sql,const char** erg,uchar obstumm) 
   switch (DBS) 
   case MySQL:
   if (mysql_query(conn,sql)) 
 *erg=mysql_error(conn);
 if (!obstumm)
 printf("Fehler %u: %s\n", mysql_errno(conn), *erg);
 return 1;

 result = mysql_store_result(conn);
//			row = mysql_fetch_row(result);

return 0;
// int DB::Abfrage(const char* sql,const char** erg) 

int DB::AbfragemE(string sql,const char** erg,uchar obstumm) 
return AbfragemE(sql.c_str(),erg,obstumm);

int DB::AbfragemE(const char* sql,const char** erg,uchar obstumm) 
int ergi = Abfrage(sql,erg,obstumm);
AbfrageEnde();
return ergi;
} // int DB::AbfragemE(const char* sql,const char** erg) 
 */

// wird aufgerufen in: prueftab
void DB::lesespalten(Tabelle *ltab,int obverb)
{
  Log(violetts+Txd[T_Lesespalten]+blau+ltab->name+"'"+schwarz,obverb);
  char ***cerg;
  //          RS spalt(this,string("SHOW COLUMNS FROM `")+tab->name+"`");
  delete spalt;
  //  spalt=new RS(this,string("SELECT column_name,character_maximum_length FROM information_schema.columns WHERE table_name = '")+ltab->name
  //      +"' and table_schema = '"+db+"' order by ordinal_position"); // geht nicht fuer Zahlen
  spalt=new RS(this,string("SELECT column_name p0,"
        "MID(column_type,INSTR(column_type,'(')+1,INSTR(column_type,')')-INSTR(column_type,'(')-1) p1, column_type p2 "
        "FROM information_schema.columns WHERE table_name = '")+ltab->name+"' AND table_schema = '"+db+"' ORDER BY ordinal_position");
  if (!spalt->obfehl) {
    delete[] spnamen;
    spnamen= new char*[spalt->num_rows];
    delete[] splenge;
    splenge= new char*[spalt->num_rows];
    delete[] sptyp;
    sptyp= new char*[spalt->num_rows];
    int spnr=0;
    //    <<violett<<"Schema: "<<schwarz<<db<<endl;
    //    <<violett<<"Tabelle: "<<schwarz<<ltab->name<<endl;
    while (cerg=spalt->HolZeile(),cerg?*cerg:0) {
      spnamen[spnr]=*(*cerg);
      splenge[spnr]=*(*cerg+1);
      sptyp[spnr]=*(*cerg+2);
      /*
         MYSQL_RES *dbres;
         dbres = mysql_list_fields(conn,ltab->name.c_str(),ltab->felder[spnr].name.c_str());
         <<violett<<"spnamen["<<spnr<<"]: "<<schwarz<<spnamen[spnr]<<endl;
         <<violett<<" splenge["<<spnr<<"]: "<<schwarz<<(splenge[spnr]?splenge[spnr]:"NULL")<<endl;
         if (dbres) if (dbres->fields->name) 
           <<" dbres->fields->name: "<<dbres->fields->name<<endl;
         if (dbres) if (dbres->fields->length) 
           <<" dbres->fields->length: "<<dbres->fields->length<<endl;
       */
      spnr++;
    }
    if (obverb) {
      for(size_t j=0;j<spalt->num_rows;j++) {
       Log(blaus+"spanmen["+ltoan(j)+"]: "+schwarz+spnamen[j]);
       Log(blaus+"splenge["+ltoan(j)+"]:  "+schwarz+splenge[j]);
       Log(blaus+"sptyp["+ltoan(j)+"]:    "+schwarz+sptyp[j]);
      }
    }
  }
} // lesespalten

int DB::prueftab(Tabelle *ptab,int obverb) 
{
  Log(violetts+Txd[T_Pruefe_Tabelle]+blau+ptab->name+"'"+schwarz,obverb);
  int gesfehlr=0;
  RS rs(this);
  std::stringstream sql;
  // eine Indexfeldlaenge groesser als die Feldlaenge fuehrt zu Fehler (zumindex bei MariaDB)
  for(int i=0;i<ptab->indexzahl;i++){
    for(int j=0;j<ptab->indices[i].feldzahl;j++){
      for(int k=0;k<ptab->feldzahl;k++){
        if (!ptab->felder[k].lenge.empty()) if (!ptab->indices[i].felder[j].lenge.empty())
          if (!strcasecmp(ptab->felder[k].name.c_str(),ptab->indices[i].felder[j].name.c_str())) 
            if (atol(ptab->felder[k].lenge.c_str())<atol(ptab->indices[i].felder[j].lenge.c_str())){
              ptab->felder[k].lenge=ptab->indices[i].felder[j].lenge;
            }
      }
    }
  }
  vector<string> fstr;
  vector<string> istr;
  const char* def_engine="InnoDB";
  const char* def_charset="latin1";
  const char* def_collate="latin1_german2_ci";
  const char* def_rowformat="DYNAMIC";
  switch (DBS){
    case MySQL:
      {
        if (conn==0) conn = mysql_init(NULL);
        lesespalten(ptab,obverb>1);

        for(int i=0;i<ptab->feldzahl;i++) {
          if (!spalt->obfehl)
            for(unsigned j=0;j<spalt->num_rows;j++) {
              if (!strcasecmp(ptab->felder[i].name.c_str(),spnamen[j])) {
                if (splenge[j]) 
                  if (atol(splenge[j]) > atol(ptab->felder[i].lenge.c_str())) 
                    ptab->felder[i].lenge=splenge[j];
                break;
              }
            }
          fstr.resize(fstr.size()+1);
          istr.resize(istr.size()+1);
          ersetzAlle(ptab->felder[i].comment,"'","\\'");
          //<<"ptab->felder[i].comment: "<<ptab->felder[i].comment<<endl;
          fstr[i]= "`" + ptab->felder[i].name + "` "+
            ptab->felder[i].typ+
            ((ptab->felder[i].lenge==""||ptab->felder[i].lenge=="0")?"":
             (string("(")+ptab->felder[i].lenge+
              ((ptab->felder[i].prec=="")?"":
               (string(",")+ptab->felder[i].prec))
              +")"))
            +(ptab->felder[i].nnull  ?  " NOT NULL ":"")
            +(ptab->felder[i].defa.empty()&&!ptab->felder[i].nnull?"":string(" DEFAULT '")+ptab->felder[i].defa+"'")
            +(ptab->felder[i].obauto?" AUTO_INCREMENT":" ")
            +(ptab->felder[i].obind && ptab->felder[i].obauto?" PRIMARY KEY":" ")
            +((ptab->felder[i].comment.empty())?"":
                (string(" COMMENT '")+ptab->felder[i].comment+"'"));
          if (ptab->felder[i].obind && !ptab->felder[i].obauto) {
            istr[i]=string(", ADD INDEX `")+ptab->felder[i].name+"`(`"+ptab->felder[i].name+"`)";
          }
        } // for(int i=0;i<ptab->feldzahl;i++)
        MYSQL_RES *dbres = mysql_list_tables(conn,ptab->name.c_str());
        if (!dbres->row_count) {
          /*ptab->comment=**/sersetze(&ptab->comment,string("'"),string("\\'"));
          sql<<"CREATE TABLE `"<<ptab->name.c_str();
          sql<<"` ("<<fstr[0]<<istr[0]<<") COMMENT='";
          sql<<ptab->comment
            <<"' ENGINE="<<(ptab->engine==""?def_engine:ptab->engine);
          sql<<" DEFAULT CHARSET="
            <<(ptab->charset==""?def_charset:ptab->charset);
          sql<<((ptab->charset!=""&&ptab->collate=="")?"":" COLLATE=")
            <<(ptab->collate==""?(ptab->charset!=""?"":def_collate):ptab->collate);
          sql<<" ROW_FORMAT="
            <<(ptab->rowformat==""?def_rowformat:ptab->rowformat);
          rs.Abfrage(sql.str(),obverb?255:1); // falls obverb, dann sql-String ausgeben
          gesfehlr+=rs.obfehl;
          if (gesfehlr) Log(string("gesfehlr 1: ")+ltoan(gesfehlr),1,1);
          lesespalten(ptab,obverb>1);
        } // if (!dbres->row_count) 
        mysql_free_result(dbres);


        // Pruefung, ob Spalten hinzugefuegt werden muessen
        for(int gspn=0;gspn<ptab->feldzahl;gspn++) { // geplante Spalten
          binaer gefunden=falsch;
          for(unsigned j=0;j<spalt->num_rows;j++) { // reale Spalten
            if (!strcasecmp(ptab->felder[gspn].name.c_str(),spnamen[j])) {
              gefunden=wahr;
              break;
            }
          }
          if (!gefunden) {
            sql.str(std::string()); sql.clear();
            sql<<"ALTER TABLE `"<<ptab->name<<"` ADD "<<fstr[gspn];
            if (gspn) sql<<" AFTER `"<<ptab->felder[gspn-1].name<<"`";
            else sql<<" FIRST";
            sql<<istr[gspn];
            /*int erg=*/rs.Abfrage(sql.str(),obverb?255:1);
            gesfehlr+=rs.obfehl;
            if (gesfehlr) Log(string("gesfehlr 2: ")+ltoan(gesfehlr),1,1);
          }
        }

        // Pruefung, ob Spalten geaendert oder verschoben werden muessen
        for(int gspn=0;gspn<ptab->feldzahl;gspn++) { // geplante Spalten
          binaer verschieb=falsch, aendere=falsch;
          for(unsigned spnr=0;spnr<spalt->num_rows;spnr++) { // reale Spalten
            if (!strcasecmp(ptab->felder[gspn].name.c_str(),spnamen[spnr])) { // Feldnamen identisch
              if (strcasecmp(sptyp[spnr],"mediumtext") && strcasecmp(sptyp[spnr],"blob") && strcasecmp(sptyp[spnr],"longblob") && 
                  strcasecmp(sptyp[spnr],"longtext") && strcasecmp(sptyp[spnr],"text")) {
                if ((ptab->felder[gspn].lenge!="0" && !ptab->felder[gspn].lenge.empty()) &&
                    atol(ptab->felder[gspn].lenge.c_str()) > (long)atol(splenge[spnr])) {
                  aendere=wahr;
                }
              }
              // <<"ptab->felder[gspn].lenge: "<<rot<<ptab->felder[gspn].lenge<<schwarz<<endl;
              // <<"splenge[spnr]: "<<rot<<splenge[spnr]<<schwarz<<endl;
              if (gspn) { // Verschiebung erst ab der zweiten geplanten Spalte reicht auch und vermeidet Speicherunterlaeufe
                verschieb=wahr; 
                if (spnr) if (!strcasecmp(ptab->felder[gspn-1].name.c_str(),spnamen[spnr-1])) verschieb=falsch;
                if (verschieb) spnr--;
              }
              if (verschieb || aendere) break;
            }
          }
          if (verschieb || aendere) {
            // <<"verschieb: "<<rot<<verschieb<<schwarz<<endl;
            // <<"aendere: "<<rot<<aendere<<schwarz<<endl;
            sql.str(std::string()); sql.clear();
            sql<<"ALTER TABLE `"<<ptab->name<<"` MODIFY "<<fstr[gspn];
            if (gspn) sql<<" AFTER `"<<ptab->felder[gspn-1].name<<"`";
            else sql<<" FIRST";
            /*int erg=*/rs.Abfrage(sql.str(),obverb?255:1);
            gesfehlr+=rs.obfehl;
            if (gesfehlr) Log(string("gesfehlr 3: ")+ltoan(gesfehlr),1,1);
            if (verschieb) 
              lesespalten(ptab,obverb>1);
            if (aendere) {
              if (!istr[gspn].empty()) {
                RS rloesch(this,string("DROP INDEX `")+ptab->felder[gspn].name +"` ON `"+ptab->name+"`");
                sql.str(std::string()); sql.clear();
                sql<<"ALTER TABLE `"<<ptab->name<<"`"<<istr[gspn].substr(1);
                rs.Abfrage(sql.str(),obverb?255:1);
              }
            }
          }
        }

        for(int i=0;i<ptab->indexzahl;i++) {
          // steht aus: Namen nicht beruecksichtigen, nur Feldreihenfolge und ggf. -laenge
          RS rind(this,string("SHOW INDEX FROM `") + ptab->name+"` WHERE KEY_NAME = '"+ ptab->indices[i].name +"'");
          if (!rind.obfehl) {
            uchar obneu=0;
            if (!rind.result->row_count){
              obneu=1;
            } else {
              for(int j=0;j<ptab->indices[i].feldzahl;j++) {
                char*** erg= rind.HolZeile();
                if (!*erg) {
                  obneu=1;break;
                } else if (strcasecmp(ptab->indices[i].felder[j].name.c_str(),*(*erg+4))) { 
                  // 0 = Tabelle, 1 = non_unique (0,1), 2 = Key_name, 3 = seq_in_index, 4 = column_name, 5 = Collation ('A','D'), 6=Cardinality(0,1), 
                  // 7= sub_part(NULL,<ziffer>), 8=packed(null), 9=NULL("Yes"),10=index_type("BTREE"),11=comment(""),12=index_comment("")
                  obneu=1;break;
                } else if (ptab->indices[i].felder[j].lenge!="" && *(*erg+7)) {
                  if (ptab->indices[i].felder[j].lenge!=*(*erg+7)) { 
                    obneu=1;break;
                  }
                }
              }
              if (!obneu) {    // Wenn zu viele Zeilen da sind, auch loeschen
                char*** erg= rind.HolZeile();
                if (*erg) {
                  obneu=1;
                }
              }
              if (obneu) {
                RS rloesch(this,string("DROP INDEX `")+ptab->indices[i].name +"` ON `"+ptab->name+"`");
              }
            }

            if (obneu) {
              RS rindins(this);
              sql.str(std::string()); sql.clear();
              sql<<"CREATE INDEX `"<<ptab->indices[i].name<<"` ON `"<<ptab->name<<"`(";
              for(int j=0;j<ptab->indices[i].feldzahl;j++) {
                sql<<"`"<<ptab->indices[i].felder[j].name<<"`";
                for(unsigned spnr=0;spnr<spalt->num_rows;spnr++) { // reale Spalten
                  if (!strcasecmp(ptab->indices[i].felder[j].name.c_str(),spnamen[spnr])) { // Feldnamen identisch
                    long numsplen=atol(splenge[spnr]);
                    long numinlen=ptab->indices[i].felder[j].lenge.empty()?0:atol(ptab->indices[i].felder[j].lenge.c_str());
                    if (!numinlen || !numsplen) { // numsplen ist 0 z.B. bei varbinary
                      // das sollte reichen
                      if (numsplen>50 || !numsplen) ptab->indices[i].felder[j].lenge="50"; 
                    } else if (numinlen>numsplen) {
                      // laenger darf ein MariadB-Index z.Zt. nicht sein
                      if (numsplen>767) ptab->indices[i].felder[j].lenge="767";
                      else ptab->indices[i].felder[j].lenge=splenge[spnr];
                    }
                  }
                }
                // <<gruen<<"ptab->indices["<<i<<"].name["<<j<<"].name: "<<schwarz<<ptab->indices[i].felder[j].name<<endl;
                // <<gruen<<"ptab->indices["<<i<<"].felder["<<j<<"].lenge: "<<schwarz<<ptab->indices[i].felder[j].lenge<<endl;
                if (ptab->indices[i].felder[j].lenge!="0" && ptab->indices[i].felder[j].lenge!="") {
                  sql<<"("<<ptab->indices[i].felder[j].lenge<<")";
                }
                if (j<ptab->indices[i].feldzahl-1) {
                  sql<<",";
                }
              } // for(int j=0;j<ptab->indices[i].feldzahl;j++) 
              sql<<")";
              rindins.Abfrage(sql.str(),obverb?255:1);
            } // if (obneu) 
          } // if (!rind.obfehl) 
        }
      }
      break;
    case Postgres:
      break;
  }
  return gesfehlr;
} // int DB::prueftab(Tabelle *ptab,bool obverb) 

uchar DB::tuerweitern(const string& tabs, const string& feld,long wlength,uchar obstumm)
{
  stringstream korr;
  string lenge;
  korr<<"SELECT character_maximum_length, data_type,is_nullable,column_default,column_comment FROM information_schema.columns WHERE table_schema='"<<
    db<<"' AND table_name='"<<tabs<<"' AND column_name='"<<feld<<"'";
  RS spaltlen(this,korr.str(),obstumm);
  if (!spaltlen.obfehl) {
    char*** cerg;
    while(cerg= spaltlen.HolZeile(),cerg?*cerg:0) {
      if (*(*cerg+0)) {
        lenge=*(*cerg+0);
        if (atol(lenge.c_str())<wlength) {
          Log(string(Txd[T_Erweitere_Feld])+tabs+"."+feld+Txd[T_von]+lenge.c_str()+Txd[T_auf]+ltoan(wlength),1,1);
          korr.str(std::string()); korr.clear();
          if (*(*cerg+1) && *(*cerg+2)) {
            korr<<"ALTER TABLE `"<<tabs<<"` MODIFY COLUMN `"<<feld<<"` "<<*(*cerg+1)/*data_type*/<<"("<<wlength<<") "<<
              (!strcasecmp(*(*cerg+2),"yes")?"NULL":"NOT NULL")<<" "<<(*(*cerg+3)?string("DEFAULT '")+*(*cerg+3)+"'":"")<<
              " COMMENT '"<<ersetzAllezu(*(*cerg+4),"'","\\'")<<"'";
            RS spaltaend(this,korr.str(),255/*obstumm*/);
            if (spaltaend.fnr==1074) {
              korr.str(std::string()); korr.clear();
              string neufeld;
              if (!strcasecmp(*(*cerg+1),"binary")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"varbinary")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"tinyblob")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"blob")) neufeld="mediumblob";
              else if (!strcasecmp(*(*cerg+1),"char")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"varchar")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"text")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"tinytext")) neufeld="mediumtext";
              else if (!strcasecmp(*(*cerg+1),"mediumtext")) neufeld="longtext";
              else if (!strcasecmp(*(*cerg+1),"mediumblob")) neufeld="longblob";
              if (!neufeld.empty()) {
                Log(string(Txd[T_Aendere_Feld])+tabs+"."+feld+" von: "+*(*cerg+1)+" auf: "+neufeld,1,1);
                korr<<"ALTER TABLE `"<<tabs<<"` MODIFY COLUMN `"<<feld<<"` "<<neufeld/*data_type*/<<" "<<
                  (!strcasecmp(*(*cerg+2),"yes")?"NULL":"NOT NULL")<<" "<<(*(*cerg+3)?string("DEFAULT '")+*(*cerg+3)+"'":"")<<
                  " COMMENT '"<<ersetzAllezu(*(*cerg+4),"'","\\'")<<"'";
                RS spaltaend2(this,korr.str(),255/*obstumm*/);
              }
            } // if (fnr==1074) 
          }
          return -1; // Aenderung durchgefuehrt
        } // if (atol(lenge.c_str())<wlength) 
        return 0; // kein Fehler, keine Aenderung noetig
      } else {
        //        hier z.B. numerische Felder G.Schade 1.1.16
        //        cerr<<"Fehler bei der Abfrage der Tabellenlaenge bei Tabelle: "<<tabs<<" und Feld: "<<feld<<endl<<" mit: "<<korr.str()<<endl;
        //        return 2; // Fehler bei der Abfrage der Spaltenlaenge
      } // if (**cerg) else
    } // while(cerg= HolZeile(),cerg?*cerg:0) 
  } else {
    cerr<<Txd[T_falsche_Fehlernr]<<spaltlen.fnr<<Txd[T_bei_der_Abfrage_der_Spaltenlaenge_bei_Tabelle]<<tabs<<
      Txd[T_und_Feld]<<feld<<endl<<Txd[T_mit]<<korr.str()<<endl;
    return 1;
  } // if (!obfehl) else 
  return 5;  // wird nie erreicht, verhindert aber Compilerfehlermeldung
} // tuerweitern

void DB::erweitern(const string& tabs, vector<instyp> einf,uchar obstumm,uchar obsammeln, const unsigned long *maxl)
{
  for(uint i=0;i<einf.size();i++){
    long wlength;
    if (obsammeln) {
      wlength = maxl[i];
    } else {
      wlength = einf[i].wert.length();
    }
    tuerweitern(tabs,einf[i].feld,wlength,obstumm);
  }
} // RS::erweitern

int DB::machbinaer(const string& tabs, const string& fmeld,uchar obstumm)
{
  Log(violetts+"machbinaer()"+schwarz+" tabs. "+blau+tabs+schwarz+" fmeld: "+blau+fmeld+schwarz+" obstumm: "+ltoan(obstumm),!obstumm);
  size_t p1,p2,p3,p4;
  p1=fmeld.find("'")+1;
  if (p1==string::npos) return 1;
  p2=fmeld.find("'",p1)+1;
  if (p2==string::npos) return 2;
  //                string inc=fmeld.substr(p1,p2-p1-1);
  p3=fmeld.find("'",p2)+1;
  if (p3==string::npos) return 3;
  p4=fmeld.find("'",p3)+1;
  if (p4==string::npos) return 4;
  string feld=fmeld.substr(p3,p4-p3-1);
  stringstream korr;
  string lenge;
  string neufeld;
  korr<<"SELECT character_maximum_length p0, data_type p1,is_nullable p2,column_default p3,column_comment p4"
    " FROM information_schema.columns WHERE table_schema='"<<
    db<<"' AND table_name='"<<tabs<<"' AND column_name='"<<feld<<"'";
  RS spaltlen(this,korr.str(),obstumm);
  if (!spaltlen.obfehl) {
    char*** cerg;
    while(cerg= spaltlen.HolZeile(),cerg?*cerg:0) {
      if (*(*cerg+0)) {
        lenge=*(*cerg+0);
        if (!strcasecmp(*(*cerg+1),"CHAR")) neufeld="BINARY";
        else if (!strcasecmp(*(*cerg+1),"VARCHAR")) neufeld="VARBINARY";
        else continue;
        while(1) { 
          korr.str(std::string()); korr.clear();
          korr<<"ALTER TABLE `"<<tabs<<"` MODIFY COLUMN `"<<feld<<"` "<<neufeld/*data_type*/<<"("<<lenge<<") "<<
            (!strcasecmp(*(*cerg+2),"yes")?"NULL":"NOT NULL")<<" "<<(*(*cerg+3)?string("DEFAULT '")+*(*cerg+3)+"'":"")<<
            " COMMENT '"<<ersetzAllezu(*(*cerg+4),"'","\\'")<<"'";
          RS spaltaend(this,korr.str(),255/*obstumm*/);
          if (mysql_errno(this->conn)!=1406) break;
          lenge=ltoan(atol(lenge.c_str())+10); 
        }
        return -1; // Aenderung durchgefuehrt
      } 
      return 0; // kein Fehler, keine Aenderung noetig
    } 
    return 6;
  } 
  return 7;
} // RS::machbinaer

inline string instyp::ersetze(const char *u, const char* alt, const char* neu) 
{
  string erg="";
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg.append(u);
  } else {
    for(char* p=(char*)u;*p;p++)  {
      char *pi = (char*)alt;
      int i=0,gleich=1;
      for(;*(pi+i);i++)
        if (*(pi+i)!=*(p+i))
        {gleich=0;break;}
      if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
    }
  }
  return erg;
} // ersetze(char *u, const char* alt, const char* neu)

inline string *instyp::sersetze( string *src, string const& target, string const& repl) 
{
  if (target.length()) {
    if (src->length()) {
      size_t idx = 0;
      for (;;) {
        idx = src->find( target, idx);
        if (idx == string::npos)  break;
        src->replace( idx, target.length(), repl);
        idx += repl.length();
      }
    }
  }
  return src;
} // sersetze( string src, string const& target, string const& repl)


/*
   instyp::instyp(DBSTyp eDBS, char* vfeld,char* vwert) KLA
   feld=vfeld;
//	wert=ersetze(ersetze(vwert,"\\","\\\\").c_str(),"\'","\\\'");
wert=sqlft(eDBS,vwert);
KLZ // instyp::instyp(char* vfeld,char* vwert) 

instyp::instyp(DBSTyp eDBS, char* vfeld,time_t zt) KLA
feld=vfeld;
//	sprintf(dbuf,"%d-%d-%d %d:%d:%d",zt.tm_year+1900,zt.tm_mon+1,zt.tm_mday,zt.tm_hour,zt.tm_min,zt.tm_sec);
//	wert=dbuf;
wert=sqlft(eDBS,&zt);
KLZ // instyp::instyp(char* vfeld,struct tm zt) KLA
 */

sqlft::sqlft(DBSTyp eDBS, const string& vwert):
  string(vwert) 
{
  ersetze("\\","\\\\");
  ersetze("\'","\\\'");
  insert(0,1,dvb(eDBS));
  append(1,dve(eDBS));
}

sqlft::sqlft(DBSTyp eDBS, string *vwert):
  string(*vwert) 
{
  ersetze("\\","\\\\");
  ersetze("\'","\\\'");
  insert(0,1,dvb(eDBS));
  append(1,dve(eDBS));
}

sqlft::sqlft(DBSTyp eDBS, char* vwert,bool obzahl):
  string(vwert) 
{
  if (!obzahl) {
    ersetze("\\","\\\\");
    ersetze("\'","\\\'");
    insert(0,1,dvb(eDBS));
    append(1,dve(eDBS));
  }
}

sqlft::sqlft(DBSTyp eDBS, char* vwert,char* zs):
  string(vwert) 
{
  ersetze("\\","\\\\");
  ersetze("\'","\\\'");
  insert(0,1,dvb(eDBS));
  insert(0,zs);
  append(1,dve(eDBS));
}

string *sqlft::ersetze(const char* alt, const char* neu) 
{
  if (size()){
    string erg;
    //	 erg.assign(1,c_str()[0]); // delimiter
    if (alt[0]==0 || !strcmp(alt,neu)) {
      erg=c_str();
    } else {
      erg="";
      for(char* p=(char*)c_str();*p;p++)  {
        char *pi = (char*)alt;
        int i=0,gleich=1;
        for(;*(pi+i);i++)
          if (*(pi+i)!=*(p+i))
          {gleich=0;break;}
        if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
      }
    }
    this->assign(erg);
  }
  return this;
} // ersetze(char *u, const char* alt, const char* neu)

string *sqlft::sersetze( string *src, string const& target, string const& repl) 
{
  if (target.length()) {
    if (src->length()) {
      size_t idx = 0;
      for (;;) {
        idx = src->find( target, idx);
        if (idx == string::npos)  break;
        src->replace( idx, target.length(), repl);
        idx += repl.length();
      }
    }
  }
  this->assign(*src);
  return this;
} // sersetze( string src, string const& target, string const& repl)

/*
   sqlft::sqlft(DBSTyp eDBS, time_t *tm):
   string(21,0) {
   struct tm zt;
   memcpy(&zt,localtime(tm),sizeof zt);
   sprintf((char*)c_str(),"%c%.4d-%.2d-%.2d %.2d:%.2d:%.2d%c",dvb(eDBS),zt.tm_year+1900,zt.tm_mon+1,zt.tm_mday,zt.tm_hour,zt.tm_min,zt.tm_sec,dve(eDBS));
   }
 */

sqlft::sqlft(DBSTyp eDBS, time_t *tm): string(21,0)
{
  struct tm zt;
  memcpy(&zt,localtime(tm),sizeof zt);
  druckeein(eDBS,&zt);
}

void sqlft::druckeein(DBSTyp eDBS, tm *zt) 
{
  sprintf((char*)c_str(),"%c%.4d-%.2d-%.2d %.2d:%.2d:%.2d%c",dvb(eDBS),zt->tm_year+1900,zt->tm_mon+1,zt->tm_mday,zt->tm_hour,zt->tm_min,zt->tm_sec,dve(eDBS));
}

sqlft::sqlft(DBSTyp eDBS, tm *zt):
  string(21,0) 
{
  druckeein(eDBS,zt);
}

sqlft::sqlft(DBSTyp eDBS, uchar c):
  string(1,0) 
{
  sprintf((char*)c_str(),"%d",c);
}

sqlft::sqlft(DBSTyp eDBS, char c):
  string(1,0) 
{
  sprintf((char*)c_str(),"%d",c);
}

sqlft::sqlft(DBSTyp eDBS, int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%i",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, long int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%li",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, unsigned int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%u",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, unsigned long int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%lu",i);
  resize(strlen(c_str()));
}

sqlft::sqlft(DBSTyp eDBS, long long int i):
  string(21,0) 
{
  sprintf((char*)c_str(),"%llu",i);
  resize(strlen(c_str()));
}

void DB::LetzteID(string *erg) 
{
  if (erg) {
    switch (DBS) {
      case MySQL:
        {
          RS rs(this,"select LAST_INSERT_ID()");
          *erg= *rs.HolZeile()[0];
        }
        break;
      case Postgres:
        break;
    }
  }
}

char* DB::tmtosql(tm *tmh,char* buf) 
{
  switch (DBS) {
    case MySQL:
      sprintf(buf,"%.4d%.2d%.2d",tmh->tm_year+1900,tmh->tm_mon+1,tmh->tm_mday);
      break;
    case Postgres:
      break;
  }
  return buf;
}
//
char* DB::tmtosqlmZ(tm *tmh,char* buf) 
{
  switch (DBS) {
    case MySQL:
      sprintf(buf,"%.4d%.2d%.2d%.2d%.2d%.2d",tmh->tm_year+1900,tmh->tm_mon+1,tmh->tm_mday,tmh->tm_hour,tmh->tm_min,tmh->tm_sec);
      break;
    case Postgres:
      break;
  }
  return buf;
}

my_ulonglong DB::affrows() 
{ // affected rows
  switch (DBS) {
    case MySQL:
      arows = mysql_affected_rows(conn);
      //      if (arows==(my_ulonglong)-1) if (errno==1065) arows=0;
      return arows;
      break;
    case Postgres:
      break;
  }
  return arows=0;
} // my_ulonglong DB::affrows() { // affected rows
/*
   char** DB::HolZeile() {
   switch (DBS) {
   case MySQL:
   row = mysql_fetch_row(result);
   return row;
   }
   return (char**)0;
   } // char** DB::HolZeile() {
 */

char*** RS::HolZeile() 
{
  switch (db->DBS) {
    case MySQL:
      if (!obfehl)// Anfrage erfolgreich, Rückgabedaten werden verarbeitet
        if (result) {  // Es liegen Zeilen vor
          row = mysql_fetch_row(result);
          //          lengths = mysql_fetch_lengths(result);
          return &row;
        }
      break;
    case Postgres:
      break;
  }
  return (char***)0;
} // char** DB::HolZeile() {


RS::RS(DB* pdb) 
{
  weisezu(pdb);
}

void RS::weisezu(DB* pdb) 
{
  db=pdb;
  this->result = 0;
  // um bei wiederholten Abfragen vorher mysql_free_result aufrufen zu koennen
  obfehl=-1;
}

// fuer obstumm gibt es die Stufen: 255 (zeige SQL an), 0, 1, 2 (zeige auch bei Fehler nichts an)
int RS::doAbfrage(uchar obstumm) 
{
  fnr=0;
  // fuer wiederholten Abfragen
  // <<"in doAbfrage: "<<blau<<sql<<schwarz<<endl;
  switch (db->DBS) {
    case MySQL:
      if (!obfehl)  {
        mysql_free_result(result);
        obfehl=-1;
      }
      num_rows=0;
      num_fields=0;
      //      if (sql=="select column_name from information_schema.columns where table_schema='emails' and table_name = 'lmailbody' and extra = 'auto_increment'") {mysql_commit(db->conn);} // sql="select 'ID'";
      // <<"sql.c_str(): "<<sql.c_str()<<endl;
      if (obstumm==255)
        Log(string("SQL: ")+drot+sql+schwarz,1,1);
      if (!db->conn) {
       fnr=9999;
       fehler=Txd[T_Datenbank_nicht_zu_oeffnen];
      } else {
        if (mysql_query(db->conn,sql.c_str())) {
          fnr=mysql_errno(db->conn);
          fehler=mysql_error(db->conn);
          if (fnr==1138) { // Invalid use of NULL value; bei Spaltenverschiebungen kann oft NOT NULL nicht mehr geaendert werden
            string lsql;
            transform(sql.begin(),sql.end(),std::back_inserter(lsql),::toupper);
            if ((!lsql.find("ALTER TABLE") || !lsql.find("CREATE TABLE")) && lsql.find("NOT NULL")!=string::npos) {
              lsql=caseersetze(sql,"NOT NULL","");
              if (!mysql_query(db->conn,lsql.c_str())) goto erfolg;
              else {
                fnr=mysql_errno(db->conn);
                fehler=mysql_error(db->conn);
              }
            } // if ((!lsql.find("ALTER TABLE") || !lsql.find("CREATE TABLE")) && lsql.find("NOT NULL")!=string::npos) 
          } // if (fnr==1138)
          obfehl=1;
          Log(string(Txd[T_Fehler_db])+drot+ltoan(fnr)+schwarz+" (\""+fehler+"\") in doAbfrage, sql: "+
              tuerkis+sql+schwarz,(fnr!=1406 && obstumm!=2) || (fnr==1406 && obstumm==255),1);
          if (!fehler.find("Disk full"))
          exit(115);
        } else {
erfolg:
          obfehl=0;
          result = mysql_store_result(db->conn);
          if (result) {
            num_fields = mysql_num_fields(result);
            num_rows = mysql_num_rows(result);
          } else {
          }
          //			row = mysql_fetch_row(result);
        } // if (mysql_query(db->conn,sql.c_str())) else  
      } // if (!db->conn) else
      break;
    case Postgres:
      break;
  }
  if (obfehl) if ((fnr!=1406 && !obstumm) || (fnr==1406 && obstumm==255)) {
    //		printf("Fehler %u: %s\n", fnr, fehler);
    cerr<<Txd[T_Fehler_db]<<drot<<fnr<<schwarz<<Txd[T_bei_Abfrage]<<blau<<sql<<schwarz<<": "<<endl<<drot<<fehler<<schwarz<<endl;
  }
  return (int)obfehl;
} // RS::doAbfrage

/*
   int RS::Abfrage(string psql,uchar obstumm) KLA
   this->sql=psql;
   return doAbfrage(obstumm);
   KLZ
 */

RS::RS(DB* pdb,const char* const psql,uchar obstumm) 
{
  weisezu(pdb);
  Abfrage(psql,obstumm);
}

RS::RS(DB* pdb,stringstream psqls,uchar obstumm) 
{
  string ueber= psqls.str();
  weisezu(pdb);
  Abfrage(ueber, obstumm);
}

RS::RS(DB* pdb,const string& psql,uchar obstumm) 
{
  weisezu(pdb);
  Abfrage(psql,obstumm);
}

RS::~RS() 
{
  if (db)
    switch (db->DBS) {
      case MySQL:
        if (!obfehl) {
          mysql_free_result(result);
          obfehl=-1;
        }
        break;
      case Postgres:
        break;
    }
}

void RS::update(const string& utab, vector< instyp > einf,uchar obstumm, const string& bedingung) 
{
  ulong locks=0;

  switch (db->DBS) {
    case MySQL:
      isql=string("UPDATE ")+db->dnb+utab+db->dne+" SET ";
      for(uint i = 0;i<einf.size();i++) {
        isql+=db->dnb+einf[i].feld+db->dne;
        isql+=" = ";
        if (einf[i].obkeinwert)
          if (einf[i].wert.find(' ')==string::npos)
            isql+=(einf[i].wert); // z.B. `althyla` = null
          else
            isql+=db->dnb+(einf[i].wert)+db->dne; // z.B. `althyla`=`hyla`
        else
          isql+=(einf[i].wert);
        if (i<einf.size()-1)
          isql+=", ";
      }
      isql+=" WHERE ";
      isql+=bedingung;
      // <<blau<<isql<<schwarz<<endl;
      break;
    case Postgres:
      break;
  } // switch (db->DBS) 


  switch (db->DBS) {
    case MySQL:
      {
        char ***cerg;
        string altsqlm;
        RS sqlm(db,"SHOW VARIABLES LIKE 'sql_mode'");
        if (!sqlm.obfehl) while (cerg=sqlm.HolZeile(),cerg?*cerg:0) {
          if (*(*cerg+1)) if (!strcmp(*(*cerg+1),"STRICT_ALL_VARIABLES")) 
            altsqlm=*(*cerg+1);
          Abfrage("SET sql_mode = 'STRICT_ALL_TABLES'",obstumm);
        }
        for (int iru=0;iru<2;iru++) { // interne Runde
          Abfrage(isql,obstumm);
          if (!obfehl) {
            break;
          }  else {
            Log(string(tuerkis)+string("SQL: ")+schwarz+isql,(fnr!=1406 && obstumm!=2) || (fnr==1406 && obstumm==255),1);
            string fmeld=mysql_error(db->conn);
            Log(mysql_error(db->conn),(fnr!=1406 && obstumm!=2) || (fnr==1406 && obstumm==255),1);
            if (fnr==1406){
              db->erweitern(utab,einf,obstumm,0);
              //              if (obfehl) break; 16.1.15, sonst wirkt die aktuelle Abfrage nicht meh
            }  else if (fnr==1213){ // Deadlock found
              locks++;
              //              "locks: "<<drot<<locks<<endl;
              mysql_commit(db->conn);
              continue;
            } else if (fnr==1366) { // Incorrect string value
              db->machbinaer(utab,fmeld,0);
            } else {
              cout<<rot<<"Fehler "<<schwarz<<fnr<<" bei sql-Befehl: "<<isql<<endl;
              break; 
            }
          }
        } //  for (int iru=0;iru<2;iru++) 
        if (!altsqlm.empty()) 
          Abfrage(string("SET sql_mode = '")+altsqlm+"'",obstumm);
        // nach Gebrauch loeschen
        isql.clear();
      }
      break;
    case Postgres:
      break;
  }
} // update, aus int DB::insert(vector< instyp > einf,const char** erg,int anfangen=1,int sammeln=0) 

void RS::insert(const string& itab, vector< instyp > einf,uchar anfangen,uchar sammeln,uchar obstumm,string *id,uchar eindeutig) 
{
  /*
     anf=1,sammeln=0 ohne Puffer
     anf=1,sammeln=1 mit Puffer anfangen
     anf=0,sammeln=0 Puffer entleeren
     anf=0,sammeln=1 in Puffer schreiben
   */
  ulong locks=0;
  uchar obhauptfehl=0;
  static uchar dochanfangen=0; // => bei Erreichen von maxzaehler in der naechsten Runde neu anfangen
  static unsigned long zaehler=0; // Zahl der tatsaechlich einzufuegenden Datensaetze 
  //1. falls 0, dann auch Kopfzeile nicht behandeln, 2. falls Maxzaehler erreicht, dann Zwischeneinfuegen
  const int maxzaehler=100; // wg. Performanc: Maximalzahl fuer Sammelinsert
  static unsigned long *maxl=0; // fuer Feldlaengenkorrekturen 
  // <<"insert in "<<drot<<itab<<schwarz<<" anfangen: "<<(int)anfangen<<" sammeln: "<<(int)sammeln<<endl;
  uchar obeinfuegen=1; // Datensatz einfuegen, da noch nicht vorhanden
  /*
     if (einf.empty()) if (sammeln || anfangen)
     exit(7); // notwendiger Parameter fehlt
  // <<"nach exit(7)"<<endl;
   */
  if (id) *id="";
  if (dochanfangen) {
    anfangen=1;
    dochanfangen=0;
  }
  if (anfangen)
    zaehler=0;
  //  if (sammeln || (!sammeln && !anfangen)) 
  //<<"in insert, anfangen: "<<(int)(anfangen||dochanfangen)<<", sammeln: "<<(int)sammeln<<"\n";
  if (anfangen) {
    if (maxl) {
      delete[] maxl; maxl=0;
    }
  }
  if (!maxl) {
    maxl= new unsigned long[einf.size()];
    for (unsigned long k=0;k<einf.size();k++){
      maxl[k]=0;
    }
  }
  for (unsigned long k=0;k<einf.size();k++){
    if (einf[k].wert.length()>maxl[k]) {
      maxl[k]=einf[k].wert.length();
    }
  }
  if (eindeutig){
    string autoz;
    stringstream aut; // , autid;
    //    RS autrs(db);
    switch (db->DBS) {
      case MySQL:
        aut/*id*/<<"SELECT column_name FROM information_schema.columns WHERE table_schema='"<<db->db<<
          "' AND table_name = '"<<itab<<"' AND extra = 'auto_increment'";
        Abfrage(aut.str().c_str(),obstumm);
        obhauptfehl=obfehl;
        if (!obfehl) {
          autoz=*HolZeile()[0];
          // Datensatz schon vorhanden?
          aut.str(std::string()); aut.clear();
          aut<<"SELECT `"<<autoz<<"` FROM `"<<itab<<"` WHERE ";
          for(uint i=0;i<einf.size();i++){
            if (i) aut<<" AND ";
            aut<<db->dnb<<einf[i].feld<<db->dne<<"="<<einf[i].wert;
          }
          Abfrage(aut.str(),obstumm);
          if (!obfehl) {
            char*** erg= HolZeile();
            if (*erg) {
              if (id) *id=*erg[0];
              obeinfuegen=0;
            }
            break;
            // Feld zu kurz
          } else {
            Log(string(Txd[T_Fehler_beim_Pruefen_auf_Vorhandensein_des_Datensatzes])+mysql_error(db->conn),1,1);
          } // (!obfehl)
        } // (!obfehl)
        break;
      case Postgres:
        break;
    } // switch (db->DBS)
  } // eindeutig
  if (obeinfuegen) {
    zaehler+=1;
    if (!anfangen && zaehler==maxzaehler) {
      sammeln=0;
      zaehler=0;
      dochanfangen = 1;
    }
  }

  if (anfangen) {
    switch (db->DBS) {
      case MySQL:
        isql=string("INSERT INTO ")+db->dnb+itab+db->dne+'(';
        for(uint i = 0;i<einf.size();i++) {
          if (i) isql+=',';
          isql+=db->dnb+einf[i].feld+db->dne;
        }
        isql+=") VALUES(";
        break;
      case Postgres:
        break;
    } // switch (db->DBS) 
  } // if (obeinfuegen)

  if (obeinfuegen) {
    switch (db->DBS) {
      case MySQL:
        //				isql.reserve(isql.length()+2);
        if (!anfangen) if (isql.empty()) {
          Log(string(drot)+Txd[T_Programmfehler]+schwarz+Txd[T_nicht_anfangen_bei_isql_empty_Aufruf_von_RS_insert_beim_ersten_Mal_ohn_anfangen_bei]
              +drot+db->dnb+itab+db->dne+schwarz+", einf.size(): "+ltoan(einf.size()),1,1);
          for(uint i=0;i<einf.size();i++){
            Log(string("einf[")+ltoan(i)+"].feld: "+blau+einf[i].feld+schwarz,1,1);
            Log(string("einf[")+ltoan(i)+"].wert: "+tuerkis+einf[i].wert+schwarz,1,1);
          }
          exit(114);
        }
        if (zaehler>1) isql+=",(";
        for(uint i = 0;i<einf.size();i++) {
          if (i) {
            //						isql.reserve(isql.length()+1);
            isql+=',';
          }
          //					isql.reserve(isql.length()+2+strlen(einf[i].wert.c_str()));
//          if (einf[i].feld=="EML") { isql+="_utf8"; }
          isql+=(einf[i].wert);
        }
        //				isql.reserve(isql.length()+2);
        isql+=")";
        break;
      case Postgres:
        break;
    } // switch (db->DBS) 
  } // if (obeinfuegen)

  if (!sammeln)if (zaehler) {
    switch (db->DBS) {
      case MySQL:
        {
          char ***cerg;
          string altsqlm;
          RS sqlm(db,"SHOW VARIABLES LIKE 'sql_mode'");
          if (!sqlm.obfehl) while (cerg=sqlm.HolZeile(),cerg?*cerg:0) {
            if (*(*cerg+1)) if (!strcmp(*(*cerg+1),"STRICT_ALL_VARIABLES")) 
              altsqlm=*(*cerg+1);
            Abfrage("SET sql_mode = 'STRICT_ALL_TABLES'",obstumm);
          }
           // interne Runde
          for (int iru=0;iru<2;iru++) {
            Abfrage(isql,obstumm);
            if (id) {
              if (obfehl) *id="null";
              else *id=ltoan(mysql_insert_id(db->conn));
            }
            if (!obfehl) {
              break;
            }  else {
              Log(string(tuerkis)+string("SQL: ")+schwarz+isql,(fnr!=1406 && obstumm!=2) || (fnr==1406 && obstumm==255),1);
              string fmeld=mysql_error(db->conn);
              Log(fmeld,(fnr!=1406 && obstumm!=2) || (fnr==1406 && obstumm==255),1);
              if (fnr==1406){
                db->erweitern(itab,einf,obstumm, sammeln || (!sammeln && !anfangen),maxl);
                //                if (obfehl) break; // 16.1.16, sonst wirkt die aktuelle Abfrage nicht mehr
              }  else if (fnr==1213){ // Deadlock found
                locks++;
                //              "locks: "<<drot<<locks<<endl;
                mysql_commit(db->conn);
                continue;
              } else if (fnr==1366) { // Incorrect string value
                db->machbinaer(itab,fmeld,0);
              } else {
                cout<<rot<<"Fehler "<<schwarz<<fnr<<" bei sql-Befehl: "<<isql<<endl;
                exit(113);
                break; 
              }
            }
          } //  for (int iru=0;iru<2;iru++) 
          if (!altsqlm.empty()) 
            Abfrage(string("SET sql_mode = '")+altsqlm+"'",obstumm);
          // nach Gebrauch loeschen
          isql.clear();
        }
        break;
      case Postgres:
        break;
    }
  } // switch (db->DBS) 
  if (!sammeln) if (!obhauptfehl){
    if (maxl) {
      delete[] maxl; maxl=0;
    }
  }
} // int DB::insert(vector< instyp > einf,const char** erg,int anfangen=1,int sammeln=0) 

void RS::clear()
{
  sql.clear();
  obfehl=-1;
  fehler="";
  fnr=0;
  result=NULL;
  row=NULL;
  num_fields=0;
  // table.clear();
  feld.clear();
  typ.clear(); 
  lenge.clear();
  prec.clear();
  kommentar.clear();
} // clear
