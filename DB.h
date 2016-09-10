#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
//#pragma once
// Visual c++:
// Project->Properties->C++->general->additional include directories
// C:\Programme\MySQL\Connector C 6.0.2\include
// mingw: 
// -I"C:\Programme\MySQL\Connector C 6.0.2\include"
#ifndef DB_H_DRIN
#define DB_H_DRIN
#include <vector>
#include <string>
#include <iostream> // fuer cout ggf.
#include <sstream>
// Project->Properties->C/C++ ->General->Additional Include Directories->"$(ProjectDir)\..\..\..\MySQL Connector C 6.0.2\include"
#include <mysql.h> 
// G.Schade 26.1.14: Den Rest aus der Datei braucht man scheinbar nicht; sonst Konflikt mit bitset unter -std=gnu++11
#ifndef HAVE_UCHAR
typedef unsigned char	uchar;	/* Short for unsigned char */
#endif
// #include "/usr/include/mysql/my_global.h"
// #include <my_global.h> 
using namespace std;
#ifdef linux
#include <string.h>
#endif
// Project->Properties->Linker->general->(mitte)->additional library directories:
// C:\Programme\MySQL\Connector C 6.0.2\lib\opt
// weiterhin: libmysql.dll ins Verzeichnis der Exe stellen
#ifdef _MSC_VER
//#pragma comment(lib, "libmysql.lib")
#endif

enum Txdb_ 
{
  T_DB_wird_initialisiert,
  T_Fehler_db,
  T_beim_Initialisieren_von_MySQL,
  T_Fehler_dp,
  T_bei_Befehl,
  T_Versuche_mysql_zu_starten,
  T_MySQL_erfolgreich_gestartet,
  T_Versuche_Datenbank,
  T_zu_erstellen,
  T_Fehler_beim_Verbinden,
  T_Erfolg_beim_Initialisieren_der_Verbindung_zu_mysql,
  T_Benoetige_MySQL_Passwort_fuer_Benutzer_root_fuer_Befehl,
  T_Das_MySQL_Passwort_fuer_Benutzer_root_ist_leer_Wollen_Sie_eines_festlegen,
  T_j,
  T_Bitte_geben_Sie_ein_MySQL_Passwort_fuer_Benutzer_root_ein,
  T_Bitte_geben_Sie_das_MySQL_Passwort_fuer_Benutzer_root_erneut_ein,
  T_Fuehre_aus_db,
  T_falsche_Fehlernr,
  T_bei_der_Abfrage_der_Spaltenlaenge_bei_Tabelle,
  T_und_Feld,
  T_mit,
  T_bei_Abfrage,
  T_Fehler_beim_Pruefen_auf_Vorhandensein_des_Datensatzes,
  T_Programmfehler,
  T_nicht_anfangen_bei_isql_empty_Aufruf_von_RS_insert_beim_ersten_Mal_ohn_anfangen_bei,
  T_Datenbank_nicht_zu_oeffnen,
  T_Erweitere_Feld,
  T_von,
  T_auf,
  T_Aendere_Feld,
  T_Pruefe_Tabelle,
  T_Lesespalten,
  T_dbMAX,
};

extern class Txdbcl Txd;

class Txdbcl: public TxB
{
  public:
    static const char *TextC[][Smax];
    Txdbcl();
};

svec holdbaussql(string sql);

//
enum DBSTyp {MySQL, Postgres};

class sqlft: public string 
{
  private:
    //	char dbuf[21];
    string *ersetze(const char* alt, const char* neu);
    string *sersetze( string *src, string const& target, string const& repl);
    void druckeein(DBSTyp eDBS, tm *zt);
  public:
    //	string feld;
    sqlft(DBSTyp eDBS, const string& vwert);
    sqlft(DBSTyp eDBS, string* vwert);
    sqlft(DBSTyp eDBS, char* vwert,char* zs);
    sqlft(DBSTyp eDBS, char* vwert,bool obzahl=0);
    sqlft(DBSTyp eDBS, time_t *zt);
    sqlft(DBSTyp eDBS, tm *zt);
    sqlft(DBSTyp eDBS, char c);
    sqlft(DBSTyp eDBS, uchar c);
    sqlft(DBSTyp eDBS, int i);
    sqlft(DBSTyp eDBS, long int i);
    sqlft(DBSTyp eDBS, unsigned int i);
    sqlft(DBSTyp eDBS, unsigned long int i);
    sqlft(DBSTyp eDBS, long long int i);
};

template<typename T, size_t N> T * end(T (&ra)[N]) 
{
  return ra + N;
}

class instyp 
{
 public:
    const string feld;
    string wert;
    unsigned char obkeinwert; // bei update wird <wert> nicht als Wert, sondern als Feld o.ae. verwendet (z.B. update xy set altdatum = datum)
  private:
    //	char dbuf[21];
    inline string ersetze(const char *u, const char* alt, const char* neu);
    inline string *sersetze( string *src, string const& target, string const& repl);
  public:
    template <typename tC> explicit instyp (DBSTyp eDBS, char* const feld, tC vwert): feld(feld) {
//      feld=feld;
      wert=sqlft(eDBS,vwert);
      obkeinwert=0;
    }
    template <typename tC> explicit instyp (DBSTyp eDBS, const char* feld, tC vwert):feld(feld) {
//      feld=feld;
      wert=sqlft(eDBS,vwert);
      obkeinwert=0;
    }
//    void init(){feld="";wert="";obkeinwert=0;}
    instyp (DBSTyp eDBS, char* feld, char *vwert):feld(feld) {
//      feld=feld;
      wert=sqlft(eDBS,vwert,false);
      obkeinwert=0;
    }
    instyp (DBSTyp eDBS, char* feld, char *vwert,char* zs):feld(feld) {
//      feld=feld;
      wert=sqlft(eDBS,vwert,zs);
      obkeinwert=0;
    }
    instyp (DBSTyp eDBS, char* feld, char *vwert,bool obzahl):feld(feld) {
//      feld=feld;
      wert=sqlft(eDBS,vwert,obzahl);
      obkeinwert=0;
    }
    instyp (DBSTyp eDBS, const char* feld, const char *vwert,unsigned char vobkeinwert):feld(feld) {
//      feld=feld;
      wert=vwert;
      obkeinwert=vobkeinwert;
    }
};
// delimiter value begin
inline char dvb(DBSTyp DBS) 
{
  switch(DBS) {
    case MySQL: return '\'';
    case Postgres: return '\"';
    default: return '"';
  }
}
// delimiter value end
inline char dve(DBSTyp DBS) 
{
  switch(DBS) {
    case MySQL: return '\'';
    case Postgres: return '\"';
    default: return '"';
  }
}

// delimiter name begin
inline char dnb(DBSTyp DBS) 
{
  switch(DBS) {
    case MySQL: return '`';
    case Postgres: return '\"';
    default: return '"';
  }
}
// delimiter name end
inline char dne(DBSTyp DBS) 
{
  switch(DBS) {
    case MySQL: return '`';
    case Postgres: return '\"';
    default: return '"';
  }
}

class Feld 
{
  public:
    const string name;
    const string typ;
    string lenge;
    const string prec;
    string comment;
    bool obind;
    bool obauto;
    bool nnull;
    string defa;
    Feld(const string& name, string typ="", const string& lenge="", const string& prec="", 
         const string& comment="", bool obind=0, bool obauto=0, bool nnull=0, string defa="");
};

class Index 
{
  public:
    const string name;
    int feldzahl;
    Feld *felder;
    Index(const string& vname, Feld *vfelder, int vfeldzahl);
};

class Tabelle 
{
  public:
    const string name;
    string comment;
    Feld *felder;
    int feldzahl;
    Index *indices;
    int indexzahl;
    const string engine;
    const string charset;
    const string collate;
    const string rowformat;
    Tabelle(const string& name, Feld *felder, int feldzahl, Index *indices, int vindexzahl, string comment="",
        const string& engine="InnoDB", const string& charset="latin1", const string& collate="latin1_german2_ci", const string& rowformat="DYNAMIC");
};

class RS;

class DB 
{
  public:
    // muss außerhalb der Klasse und einer Funktion noch mal definiert werden
    static uchar oisok; // 1=Installation von MariaDB wurde ueberprueft
    string db_systemctl_name; // mysql, mariadb je nach System
    MYSQL *conn;
    //	MYSQL_RES *result;
    //	MYSQL_ROW row;
    DBSTyp DBS;
    char dnb; // delimiter name begin
    char dne; // delimiter name end
    char dvb; // delimiter value begin
    char dve; // delimiter value end
    //	char* ConStr;
    //  const char* db;
    string db;
    //  const char* host;
    string host;
    //  const char* user;
    string user;
    string passwd;
    string myloghost; // einheitliche Benennung von 'localhost' bzw. '%'
    string rootpwd; // root-Passwort
    unsigned int fehnr;
    const char* ConnError;
    string sql;
    uchar miterror;
    vector<string> myr;
    string cmd;
    string datadir;
    RS *spalt=nullptr;
    char **spnamen=nullptr,**splenge=nullptr,**sptyp=nullptr;
    int usedb(const string& db);
    void pruefrpw(const string& wofuer, unsigned versuchzahl);
    void setzrpw();
    my_ulonglong arows;
    vector< vector<instyp> > ins;
    void erweitern(const string& tab, vector<instyp> einf,uchar obstumm,uchar obsammeln=0, const unsigned long *maxl=0);
    uchar tuerweitern(const string& tab, const string& feld,long wlength,uchar obstumm);
    int machbinaer(const string& tabs, const string& fmeld,uchar obstumm);
    //	DB(DBSTyp DBS, const char* host, const char* user,const char* passwd, const char* db, unsigned int port, const char *unix_socket, unsigned long client_flag);
    DB();
    DB(DBSTyp nDBS, const char* const phost, const char* const user,const char* const ppasswd, const char* const uedb="", unsigned int port=0, 
       const char *const unix_socket=NULL, unsigned long client_flag=0,int obverb=0,int oblog=0,int versuchzahl=3,uchar ggferstellen=1);
    DB(DBSTyp nDBS, const char* const phost, const char* const user, const char* const ppasswd, const char* const prootpwd, const char* const uedb="", 
       unsigned int port=0, const char *const unix_socket=NULL, unsigned long client_flag=0,int obverb=0,int oblog=0,int versuchzahl=3,
       uchar ggferstellen=1);
    DB(DBSTyp nDBS, const string& phost, const string& puser, const string& ppasswd, const string& uedb, unsigned int port, const char* 
       const unix_socket, unsigned long client_flag,
       int obverb,int oblog,int versuchzahl=3,uchar ggferstellen=1);
    void init(DBSTyp nDBS, const char* const phost, const char* const user,const char* const ppasswd, const char* const uedb="", unsigned int port=0, 
              const char *const unix_socket=NULL, unsigned long client_flag=0,int obverb=0,int oblog=0,unsigned versuchzahl=3,
              uchar ggferstellen=1);
    ~DB(void);
    /*
       int Abfrage(const char* sql,const char** erg=(const char**)&"", uchar obstumm=0);
       int Abfrage(string sql,const char** erg=(const char**)&"", uchar obstumm=0);
       int AbfragemE(const char* sql,const char** erg=(const char**)&"", uchar obstumm=0); // mit Ende
       int AbfragemE(string sql,const char** erg=(const char**)&"", uchar obstumm=0);      // mit Ende
     */
    //	int insert(const char* tab, vector<instyp> einf, const char** erg=(const char**)&"",uchar anfangen=1,uchar sammeln=0);
    //	void AbfrageEnde();
    void LetzteID(string* erg);
    char* tmtosql(tm *tmh,char* buf);
    char* tmtosqlmZ(tm *tmh,char* buf);
    //	char** HolZeile();
    my_ulonglong affrows(); // unsigned __int64
    void lesespalten(Tabelle *tab,int obverb=0);
    int prueftab(Tabelle *tab,int obverb=0);
};


class RS 
{
  public:
    DB* db;
    string sql;
    string isql; // insert-sql
    uchar obfehl;
    string fehler;
    unsigned int fnr;
    MYSQL_RES *result;
    unsigned long *lengths;
    MYSQL_ROW row;
    unsigned int num_fields;
    unsigned long long  num_rows;
    string table;
    vector<string> feld;
    vector<string> typ;
    vector<long> lenge;
    vector<long> prec;
    vector<string> kommentar;
    RS(DB* pdb);
    char*** HolZeile();
    void weisezu(DB* pdb);
    void clear();
    template<typename sT> 
      int Abfrage(sT psql,uchar obstumm=0){
        int erg=0;
        this->sql=psql;
        if (!sql.empty()) {
          erg = doAbfrage(obstumm);
        }
        return erg;
      }

    RS(DB* pdb,const char* const psql, uchar obstumm=0);
    RS(DB* pdb,const string& psql, uchar obstumm=0);
    RS(DB* pdb,stringstream psqls, uchar obstumm=0);
    ~RS();
    void update(const string& tab, vector<instyp> einf,uchar obstumm, const string& bedingung);
    void insert(const string& tab, vector<instyp> einf, uchar anfangen=1,uchar sammeln=0,uchar obstumm=0,string *id=0,uchar eindeutig=0);
  private:
    int doAbfrage(uchar obstumm);
};

//string ersetze(const char *u, const char* alt, const char* neu);
#endif // DB_H_DRIN
