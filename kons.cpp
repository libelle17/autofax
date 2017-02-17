#include "kons.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/statvfs.h> // fuer statfs
#include <utime.h>
#include <sys/sendfile.h> // fuer sendfile64
#define caus cout // nur zum Debuggen

#ifdef _WIN32
const char *dir = "dir ";
#elif linux
const char *dir = "ls -l ";
#endif
const char *tmmoegl[2]={"%d.%m.%y","%c"}; // Moeglichkeiten fuer strptime

#ifdef linux
#include <iomanip> // setprecision
// const char *rot="\e[1;31m", *weinrot="\e[31m", *schwarz="\e[0m", *blau="\e[34m", *gelb="\e[33m"; // muss spaeter kompilerunabhaengig 
const char *schwarz="\e[0m", *dgrau="\e[1;30m", *drot="\e[0;31m", *rot="\e[1;31m", *gruen="\e[0;32m", *hgruen="\e[1;32m",
      *braun="\e[0;33m",   *gelb="\e[1;33m",     *dblau="\e[0;34;1;47m",  *blau="\e[1;34m", *violett="\e[0;35m", *hviolett="\e[1;35m",
      *tuerkis="\e[0;36m", *htuerkis="\e[1;36m", *hgrau="\e[0;37m", *weiss="\e[1;37m", *umgek="\e[7m";
const char *_drot=drot, *_rot=rot, *_schwarz=schwarz, *_blau=blau, *_gelb=gelb, *_tuerkis=tuerkis, *_hgrau=hgrau;
// char logdatei[PATH_MAX+1]="/DATA/down/log_termine.txt";
#define _access access
#include <sys/time.h>  // f�r gettimeofday()
#elif defined _WIN32
const char *drot="", *rot="", *schwarz="", *blau="", *gelb="", *tuerkis="", *hgrau="";
//offen: bei den Farben muss unterschieden werden zwischen cout (-> _drot) und 
printf(drot, unter windows escape-Sequenzen rausfielselen und durch SetConsoleTextAttribute-Aufrufe ersetzen)
  // char logdatei[PATH_MAX+1]="v:\log_termine.txt";
  template <class _Elem, class _Traits>
  std::basic_ostream<_Elem,_Traits>& operator<<(std::basic_ostream<_Elem,_Traits>& i, color& c){
    HANDLE hStdout=GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(hStdout,c.m_color);
    return i;
  }
//char logdatei[PATH_MAX+1]="v:\\log_termine.txt";
#endif

// z.B. "/root/autofax"
const string& instvz=
#include "instvz" // wird in Makefile erstellt
;
const string& unindt=instvz+"/uninstallinv"; // # Name muss identisch sein mit Variabler UNF in install.sh
const string nix;
class linst_cl linst;

const char *Txkonscl::TextC[T_konsMAX+1][Smax]=
{
  //TCtp Txkonscl::TextC=KLA
  // T_pfad,
  {"pfad","path"},
  // T_kuerze_logdatei,
  {", kuerze logdatei: ",", shorten log file: "},
  // T_Logdatei,
  {"Logdatei ","Log file "},
  // T_gibt_es_noch_nicht_Kuerze_sie_daher_nicht,
  {" gibt es noch nicht. Kuerze sie daher nicht."," does not exist yet. Not shortening it therefore."},
  // T_Kann_Datei
  {"Kann Datei '","Cannot open file '"},
  //T_nicht_als_fstream_zum_Schreiben_oeffnen
  {"' nicht als fstream zum Schreiben oeffnen.","' as fstream for writing."},
  // T_nicht_als_fstream_zum_Lesen_oeffnen
  {"' nicht als fstream zum Lesen oeffnen.","' as fstream for reading."},
  // T_nicht_mit_fopen_zum_Schreiben_oeffnen 
  {"' nicht mit fopen zum Schreiben oeffnen.","' with fopen for writing."},
  // T_nicht_mit_fopen_zum_Lesen_oeffnen 
  {"' nicht mit fopen zum Lesen oeffnen.","' with fopen for reading."},
  // T_Variable_logdatei_leer
  {"Variable 'logdatei' leer!","Variable 'logdatei' empty!"},
  // T_nicht_als_fstream_zum_Anhaengen_oeffnen
  {"' nicht als fstream zum Anhaengen oeffnen.","' as fstream for appending."},
  // T_nicht_mit_fopen_zum_Anhaengen_oeffnen
  {"' nicht mit fopen zum Anhaengen oeffnen: ","' with fopen for appending."},
  // T_Bitte_mit
  {"Bitte mit '","Please exit with '"},
  // T_beenden
  {"' beenden ...","'"},
  // T_stern_zeile
  {"*zeile: ","*line: "},
  // T_Rueckmeldung
  {"Rueckmeldung: ","Feedback: "},
  // T_Suchbefehl
  {"Suchbefehl","Search command"},
  // T_Fuehre_aus
  {"Fuehre aus","Executing"},
  // T_fehlgeschlagen_bei
  {"fehlgeschlagen bei: ","failed at: "},
  // T_Fuehrte_aus
  {"Fuehrte aus","Executed "},
  // T_komma_Ergebnis
  {", Ergebnis: ",", result: "},
  // T_kein_Verzeichnis_nochmal
  {"' kein Verzeichnis, nochmal: ","' not a directory, once again: "},
  // T_nicht_gefunden_soll_ich_es_erstellen
  {"' nicht gefunden, soll ich es erstellen (","' not found, shall I create it ("},
  // T_Fehlender_Parameter_string_zu
  {"Fehlender Parameter <string> zu -","Missing Parameter <string> after -"},
  // T_oder
  {" oder --"," or --"},
  // T_Fehler_Parameter
  {"Fehler: Parameter -","Error: Stated Parameter -"},
  // T_ohne_gueltigen
  {"ohne gueltigen","without valid"},
  // T_mit_Datei_als
  {"mit Datei als","with file as"},
  // T_mit_falschem
  {"mit falschem","with wrong"},
  // T_Pfad_angegeben
  {" Pfad angegeben!"," path!"},
  // T_Nicht_numerischer
  {"Nicht-numerischer","Not-numeric"},
  // T_Fehlender
  {"Fehlender","Missing"},
  // T_Parameter_nr_zu
  {" Parameter <nr> zu -"," Parameter <no> after -"},
  // T_Fehler
  {"Fehler ","Error "},
  // T_Erfolg
  {"Erfolg","Success"},
  // T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden
  {"Weder zypper noch apt-get noch dnf noch yum als Installationspgramm gefunden!",
   "Neither zypper nor apt-get nor dnf nor yum found as installation programme!"},
  // T_Logdateidpp
  {"Logdatei:","Log file:"},
  // T_Lese_Konfiguration_aus
  {"Lese Konfiguration aus '","Reading configuration from '"},
  // T_j_k,
  {"j","y"},
  // T_Fehler_bei_auswert
  {"Fehler bei auwert(): ","Error at evaluate(): "},
  // T_nicht_gefunden
  {" nicht gefunden"," not found"},
  // T_Muss_Datei
  {"Muss Datei '","File '"},
  // T_fuer
  {"' fuer '","' must be made accessible for '"},
  // T_zugreifbar_machen
  {"' zugreifbar machen.","'"},
  // T_spruef_sname
  {"spruef(), sname: ","sprove(), sname: "},
  // T_lief_schon
  {" lief schon."," ran already."},
  // T_nicht_gefunden_versuche_ihn_einzurichten
  {" nicht gefunden, versuche ihn einzurichten"," not found, trying to install it"},
  // T_Aktiviere_Dienst
  {"Aktiviere Dienst: ","Activating service: "},
  // T_Program
  {"Programm '","Program '"},
  // T_laeuft_schon_einmal_Breche_ab
  {"' laeuft schon einmal. Breche ab.","' runs already once. Aborting."},
  // T_Wert
  {" Wert: "," Value: "},
  // T_Dauer
  {" Dauer: "," Duration: "},
  // T_Dienst
  {"Dienst ","Service "},
  // T_geladen
  {" geladen"," loaded"},
	// 	T_ermoeglicht
	{" ermoeglicht"," enabled"},
	// T_nicht_ermoeglicht
	{" nicht ermoeglicht"," not enabled"},
  // T_nicht_geladen
  {" nicht geladen"," not loaded"},
  // T_am
  {"' am ","' on "},
  // T_als_Dienst_eingerichtet_von
  {", als Dienst eingerichtet von '",", installed as service by '"},
  // T_Versuch
  {", Nr: ",", no.: "},
  // T_machfit
  {"machfit()","makefit()"},
  //   T_Loesche_Ausrufezeichen
  {"Loesche: ","Deleting: "},
  // T_Fehler_beim_Loeschen
  {"Fehler beim Loeschen","error deleting"},
  // T_nicht_geloescht_war_eh_nicht_mehr_da
  {" nicht geloescht, war eh nicht mehr da."," not deleted, was no more there."},
  // T_pruefpar
  {"pruefpar()","checkpar()"},
  // T_Konfiguration_fuer
  {"# Konfiguration fuer '","# Configuration for '"},
  // T_erstellt_automatisch_durch_dieses_am
  {"', erstellt automatisch durch dieses am: ","', generated automatically by itself at: "},
  // T_Fehler_bei_lstat
  {"Fehler_bei_lstat ","Error at lstat "},
  // T_Datum_nicht_gesetzt_bei
  {"Datum nicht gesetzt bei '","Date not set for '"},
  // T_Konnte_Datei
  {"Konnte Datei '","Could not open file '"},
  // T_nicht_zum_Lesen_oeffnen
  {"' nicht zum Lesen oeffen!","' for reading!"},
  // T_nicht_zum_Schreiben_oeffnen
  {"' nicht zum Schreiben oeffnen!","' for writing!"},
  // T_Zeilen
  {" Zeilen"," lines"},
	// T_oder_nicht
	{" oder nicht"," or not"},
	// T_nicht_einfuegbar
	{"nicht einfuegbar","not insertable"},
  // T_erneute_Eingabe
  {"erneute Eingabe","once more"},
	// T_obsvfeh
	{"obsvfeh()","ifsverr()"},
	// T_laeuft_jetzt
	{"laeuft jetzt","is running now"},
	// T_Dienst_inexistent
	{"Dienst inexistent","service not existant"},
	// T_Dienstdateiname_nicht_ermittelbar
	{"Dienstdateiname nicht ermittelbar","service file name not given"},
	// T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent
	{"Dienst laeuft noch, aber Dienstdatei inexistent","service still runs, but service file missing"},
	// T_Exec_Dateiname_nicht_ermittelbar
	{"Exec-Dateiname nicht ermittelbar","exec-file name not given"},
	// T_Exec_Datei_fehlt
	{"Exec-Datei fehlt","exec-file missing"},
	// T_activating
	{"'activating'","'activating'"},
	// T_Dienst_kann_gestartet_werden
	{"Dienst kann gestartet werden","service can be started"},
	// T_Sonstiges
	{"Sonstiges","other"},
	// T_Ergebnis_Dienst
	{"Ergebnis Dienst ","result service "},
	// T_Dienst_laeuft
	{"Dienst laeuft","service is running"},
	// T_Dienst_disabled
	{"Dienst 'disabled'","service disabled"},
	// T_stopdis_sname
	{"stopdis(), sname: ","stopdis(), sname: "},
	// T_enableggf
	{"enableggf()","enableifnecessary()"},
	// T_semodpruef
	{"semodpruef()","checksemod()"},
  {"",""}
}; // const char *Txkonscl::TextC[T_konsMAX+1][Smax]=


Txkonscl::Txkonscl() 
{
  TCp=(const char* const * const * const *)&TextC;
}

class Txkonscl Txk;

uchar nrzf=0; // nicht rueckzufragen, fuer Aufruf aus Cron

argcl::argcl(int i,char** argv) 
{
  argcs=argv[i];
}

const string drots=drot, rots=rot, schwarzs=schwarz, blaus=blau, dblaus=dblau, gelbs=gelb, tuerkiss=tuerkis, violetts=violett, gruens=gruen;

perfcl::perfcl(const string& vvonwo): vonwo(vvonwo)
{
  zp0=zp1=clock(); 
  t0=time(NULL);
} // perfcl::perfcl(const string& vvonwo): vonwo(vvonwo)

void perfcl::ausgeb(const string& stelle,uchar obdauer)
{
  zp1alt=zp1;
  zp1=clock();
  t1=time(NULL);
  cout<<gruen;
  if (!vonwo.empty())
   cout<<vonwo<<Txk[T_Versuch]<<setw(4)<<++nr<<", "<<setw(22)<<stelle<<": ";
  cout<<Txk[T_Dauer]<<setprecision(7)<<setw(9)<<(long)(zp1-zp0)<<" clocks = "
    <<fixed<<(t1-t0)<<setprecision(0)<<" s, "
    "delta= "<<setprecision(7)<<setw(9)<<(long)(zp1-zp1alt)<<" clocks"<<fixed<<schwarz<<(obdauer?"\n":"\r");cout.flush();
} // void perfcl::ausgeb(const string& stelle)


void perfcl::ausgab1000(const string& stelle)
{
  zp1=clock();
  nr++;
  if (zp1-zp0>10000) {
    cout<<gruen<<vonwo<<" "<<stelle<<" "<<nr<<Txk[T_Dauer]<<setprecision(7)<<setw(9)<<(long)(zp1-zp0)<<" = "
      <<fixed<<((zp1-zp0)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s"<<endl;
    exit(102);
  }
} // void perfcl::ausgab1000(const string& stelle)

int perfcl::oberreicht(unsigned long sek)
{
 zp1=clock();
// <<"zp1-zp0: "<<(zp1-zp0)<<", sek: "<<(long)(sek*CLOCKS_PER_SEC)*0.1<<endl;
 return ((zp1-zp0)>(long)sek*CLOCKS_PER_SEC*0.1);
} // int perfcl::oberreicht(unsigned long sek)


string ersetzefuerdatei(const string& u) 
{
  static string ziel;
  ziel =u;
  ersetzAlle(&ziel,"*","");
  ersetzAlle(&ziel,":",".");
  return ziel;
} // string ersetzefuerdatei(const string& u) 

char* charersetze(char *u, char alt, char neu) 
{
  for(size_t i=0;i<strlen(u);i++)
    if (u[i]==alt) 
      u[i]=neu;
  return u;
} // charersetze(char *u, const char* alt, const char* neu)

/*
// macht Speicherfehler
wstring ersetze(const wstring& u, const wchar_t* alt, const wchar_t* neu) 
{
wstring erg=L"";
if (alt[0]==0 || !wcscmp(alt,neu)) {
erg=u;
} else {
for(wchar_t* p=(wchar_t*)u.c_str();*p;p++)  {
wchar_t *pi = (wchar_t*)alt;
int i=0,gleich=1;
for(;*(pi+i);i++)
if (*(pi+i)!=*(p+i))
{gleich=0;break;}
if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
}
}
return erg;
} // ersetze(char *u, const char* alt, const char* neu)

string fersetze(const string& u, const char* alt, const char* neu) 
{
string erg="";
if (alt[0]==0 || !strcmp(alt,neu)) {
erg=u;
} else {
for(char* p=(char*)u.c_str();p<(char*)u.c_str()+u.length();p++)  {
if (logdatei[0]=='1') xit(0);
char *pi = (char*)alt;
int i=0,gleich=1;
for(;*(pi+i);i++)
if (*(pi+i)!=*(p+i))
{gleich=0;break;}
if (gleich) {erg+=neu;p+=i-1;} else {
erg+=(*p);
}
}
}
return erg;
} // ersetze(char *u, const char* alt, const char* neu)
 */

string caseersetze(const string& u, const char* alt, const char* neu) 
{
  string erg;
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg=u;
  } else {
    //    for(char* p=(char*)u.c_str();*p;p++)  KLA
    for(char* p=(char*)u.c_str();p<(char*)u.c_str()+u.length();p++)  {
      char *pi = (char*)alt;
      int i=0,gleich=1;
      for(;*(pi+i);i++)
        if (tolower(*(pi+i))!=tolower(*(p+i)))
        {gleich=0;break;}
      if (gleich) {erg+=neu;p+=i-1;} else erg+=(*p);
    }
  } //   if (alt[0]==0 || !strcmp(alt,neu)) else
  return erg;
} // ersetze(char *u, const char* alt, const char* neu)

string *loeschealleaus(string *u, const char* alt) 
{
  size_t len=strlen(alt);
  size_t pos;
  while ((pos=u->find(alt))!=string::npos) {
    u->erase(pos,len);
  }
  return u;
} // loeschealleaus(char *u, const char* alt, const char* neu)

string ersetzAllezu(string& quelle, const string& alt, const string& neu) 
{
  if(!alt.empty()) {
    string zwi;
    zwi.reserve(quelle.length());
    size_t p0 = 0, pakt;
    while((pakt = quelle.find(alt, p0)) != string::npos) {
      zwi += quelle.substr(p0, pakt - p0);
      zwi += neu;
      pakt += alt.length();
      p0 = pakt;
    }
    zwi += quelle.substr(p0);
    return zwi;
  }
  return quelle;
} // string ersetzAllezu(string& quelle, const string& alt, const string& neu) 


void ersetzAlle(string& quelle, const string& alt, const string& neu) 
{
  if(!alt.empty()) {
    string zwi;
    zwi.reserve(quelle.length());
    size_t p0 = 0, pakt;
    while((pakt = quelle.find(alt, p0)) != string::npos) {
      zwi += quelle.substr(p0, pakt - p0);
      zwi += neu;
      pakt += alt.length();
      p0 = pakt;
    }
    zwi += quelle.substr(p0);
    quelle.swap(zwi); 
  }
} // void ersetzAlle(string& quelle, const string& alt, const string& neu) 


string ersetzAllezu(string *quelle, const char* alt, const char* neu) 
{
  if(*alt) {
    string zwi;
    zwi.reserve(quelle->length());
    size_t altlen = strlen(alt);
    size_t p0 = 0, pakt;
    while((pakt = quelle->find(alt, p0)) != string::npos) {
      zwi += quelle->substr(p0, pakt - p0);
      zwi += neu;
      pakt += altlen;
      p0 = pakt;
    }
    zwi += quelle->substr(p0);
    return zwi;
  }
  return *quelle;
} // string ersetzAllezu(string *quelle, const char* alt, const char* neu) 


string ersetzAllezu(const char *quelle, const char* alt, const char* neu) 
{
  string erg;
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg=quelle;
  } else {
    for(char* p=(char*)quelle;p<quelle+strlen(quelle);p++)  {
      char *pi = (char*)alt;
      int i=0,gleich=1;
      for(;*(pi+i);i++)
        if (*(pi+i)!=*(p+i))
        {gleich=0;break;}
      if (gleich) {
			  erg+=neu;p+=i-1;
			} else {
        erg+=(*p);
      } // if (gleich) else
    } //     for(char* p=(char*)quelle;p<quelle+strlen(quelle);p++)
  } //   if (alt[0]==0 || !strcmp(alt,neu)) else
  return erg;
} // string ersetzAllezu(const char *quelle, const char* alt, const char* neu) 


void ersetzAlle(string *quelle, const char* alt, const char* neu) 
{
  if(*alt) {
    string zwi;
    zwi.reserve(quelle->length());
    size_t altlen = strlen(alt);
    size_t p0 = 0, pakt;
    while((pakt = quelle->find(alt, p0)) != string::npos) {
      zwi += quelle->substr(p0, pakt - p0);
      zwi += neu;
      pakt += altlen;
      p0 = pakt;
    }
    zwi += quelle->substr(p0);
    quelle->swap(zwi); 
  }
} // void ersetzAlle(string *quelle, const char* alt, const char* neu) 


void ersetzAlle(string *quelle, const string& alt, const string& neu) 
{
  if(!alt.empty()) {
    string zwi;
    zwi.reserve(quelle->length());
    size_t p0 = 0, pakt;
    while((pakt = quelle->find(alt, p0)) != string::npos) {
      zwi += quelle->substr(p0, pakt - p0);
      zwi += neu;
      pakt += alt.length();
      p0 = pakt;
    }
    zwi += quelle->substr(p0);
    quelle->swap(zwi); 
  }
} // void ersetzAlle(string *quelle, const string& alt, const string& neu) 


// ergibt die Zahl der Vorkommen von *was in *str
size_t zahlin(string *str, const char* was) 
{
  size_t erg=0,pos=0;
  if (*was) {
    while ((pos=str->find(was,pos)+1)) {
      erg++;
    }
  }
  return erg;
} // size_t zahlin(string *str, const char* was) 


void chersetze(string str, string *wsRet, const string& from, const char to) 
{
  //  wsRet->reserve(str.length());
  wsRet->clear();
  size_t start_pos = 0, pos;
  while((pos = str.find_first_of(from, start_pos)) != string::npos) {
    *wsRet += str.substr(start_pos, pos - start_pos);
    *wsRet += to;
    pos ++;
    start_pos = pos;
  }
  *wsRet += str.substr(start_pos);
} // void chersetze(string str, string *wsRet, const string& from, const char to) 


string ersetze(const char *u, const char* alt, const char* neu) 
{
  string erg;
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

string *sersetze(string* src, string const& target, string const& repl) 
{
  if (target.length()) {
    if (src->length()) {
      size_t idx = 0;
      for (;;) {
        idx = src->find( target, idx);
        if (idx == string::npos)  break;
        src->replace( idx, target.length(), repl);
        idx += repl.length();
      } //       for (;;)
    } //     if (src->length())
  } // if (target.length())
  return src;
} // sersetze( string src, string const& target, string const& repl)

void getstammext(const string *const ganz, string *stamm, string *exten) 
{
  size_t posp = ganz->rfind('.');
  if (posp!=std::string::npos) {
    *exten=ganz->substr(posp+1);
    *stamm=ganz->substr(0,posp);
  } else {
    *exten="";
    *stamm=string(*ganz);
  } //   if (posp!=std::string::npos) else
} // void getstammext(string *ganz, string *stamm, string *exten) 

#if defined(__MINGW32__) || defined(_MSC_VER)
int getcols() 
{
  CONSOLE_SCREEN_BUFFER_INFO info; //Schrecklicher Name ;)
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&info);
  return info.dwSize.X;
} // int getcols() 
#elif linux
int getcols() 
{
  winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
} // int getcols() 
#endif

char* curruser() 
{
  static struct passwd *passwd = getpwuid(getuid());
  return passwd->pw_name;
} // curruser()

// Achtung: Wegen der Notwendigkeit der Existenz der Datei zum Aufruf von setfacl kann die Datei erstellt werden!
mdatei::mdatei(const string& name, ios_base::openmode modus/*=ios_base::in|ios_base::out*/,uchar faclbak/*=1*/,int obverb/*=0*/, int oblog/*=0*/)
{
  for(int iru=0;iru<3;iru++) {
    open(name,modus);
    if (is_open()) {
      oboffen=1;
      break;
    }
    //    int erg __attribute__((unused));
    if (name!=unindt)  // sonst vielleicht Endlosschleife
		  pruefverz(dir_name(name),0,0,0,0);
    if (!systemrueck("sudo test -f '"+name+"' || sudo touch '"+name+"'",obverb,oblog)) {
      setfaclggf(name,falsch,modus&ios::out?6:4,falsch,obverb,oblog,faclbak);
    } // if (!systemrueck("sudo test -f '"+name+"' || sudo touch '"+name+"'",obverb,oblog)) 
  } // for(int iru=0;iru<3;iru++) 
} // mdatei::mdatei (const string& name, ios_base::openmode modus)


#ifdef falsch
#ifdef obfstream
fstream*
#else
FILE*
#endif
oeffne(const string& datei, uchar art, uchar* erfolg,int obverb/*=0*/, int oblog/*=0*/,uchar faclbak/*=1*/)
{
#ifdef obfstream	
	ios_base::openmode mode;
	switch (art) {
		case 0: mode=ios_base::in; break;
		case 1: mode=ios_base::out; break;
		case 2: mode=ios_base::out | ios_base::app; break;
		case 3: mode=ios_base::out; break; // text mode, default
	}
	fstream *sdat;
	for(int iru=0;iru<2;iru++) {
		sdat = new fstream(datei,mode);
		if (sdat) if (!sdat->is_open()) sdat=0;
		if (sdat) {
#else
			const char *mode;
			switch (art) {
				case 0: mode="r"; break;
				case 1: mode="w"; break;
				case 2: mode="a"; break;
				case 3: mode="wt"; break; // text mode, default
			}
			FILE *sdat;
			for(int iru=0;iru<2;iru++) {
				if ((sdat= fopen(datei.c_str(),mode))) {
#endif
					*erfolg=1;
					setfaclggf(datei,falsch,art?6:4,falsch,obverb,oblog,faclbak);
					break;
				} 
				if (!*erfolg) {
					int erg __attribute__((unused));
					erg=systemrueck("sudo touch '"+datei+"'",obverb,oblog);
				}
			} // oeffne
			return sdat;
		} // 		if (sdat)
#endif	



int kuerzelogdatei(const char* logdatei,int obverb)
{
#ifdef false
	uchar erfolg=0;
#endif
	// zutun: nicht erst in Vektor einlesen, sondern gleich in die tmp-Datei schreiben 10.6.12

	//	vector<string> Zeilen;   //Der Vektor Zeilen enth�lt String-Elemente
	char Zeile[256]; //Die maximale Zeilenl�nge betr�gt 255 Zeichen, weil ein String mit einer Null endet
	if (obverb>1) {
		cout<<"obverb: "<<(int)obverb<<Txk[T_kuerze_logdatei]<<drot<<logdatei<<schwarz<<endl;
	}
	//  Log(string("kuerzelogdatei: ") + drot + logdatei + schwarz,obverb,0);
	// ersetze(logdatei,"\\","\\\\")
	struct stat stat={0};
	if (lstat(logdatei,&stat)){
		if (obverb>1) {
			cout<<Txk[T_Logdatei]<<drot<<logdatei<<schwarz<<Txk[T_gibt_es_noch_nicht_Kuerze_sie_daher_nicht]<<endl;
		}
		return 1;
	}
	if (obverb>1) {
		cout<<rot<<Txk[T_Logdateidpp]<<endl<<schwarz; 
		int erg __attribute__((unused));
		erg=system((string(dir) + "\"" + logdatei + "\"").c_str());
	}
	const string ofil=string(logdatei)+"tmp";
	int abhier=0;
	mdatei outfile(ofil,ios::out,0);
	if (!outfile.is_open()) {
		perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_als_fstream_zum_Schreiben_oeffnen]).c_str());
		return 1;
	}
	mdatei logf(logdatei,ios::in,0);
	if (!logf.is_open()) {
		perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+logdatei+Txk[T_nicht_als_fstream_zum_Lesen_oeffnen]).c_str());
		return 1;
	}
	while (logf.getline (Zeile, sizeof(Zeile))) {
#ifdef false
#ifdef obfstream	
		fstream *outfile=oeffne(ofil,2,&erfolg);
		if (!erfolg) {
			perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_als_fstream_zum_Schreiben_oeffnen]).c_str());
			return 1;
		}
		fstream *logf=oeffne(logdatei,0,&erfolg); //Die Zeilen dieser Datei sollen in einen Vektor geschrieben werden.
		if (!erfolg) {
			perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+logdatei+Txk[T_nicht_als_fstream_zum_Lesen_oeffnen]).c_str());
			return 1;
		}
		while (logf->getline (Zeile, sizeof(Zeile))) {
			//		Zeilen.push_back(Zeile); //h�ngt einfach den Inhalt der Zeile als Vektorelement an das Ende des Vektors
#else	
			FILE *outfile=oeffne(ofil,2,&erfolg);
			if (!erfolg) {
				perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_mit_fopen_zum_Schreiben_oeffnen]).c_str());
				return 1;
			}
			FILE *logf=oeffne(logdatei,0,&erfolg);
			if (!erfolg) {
				Log(string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+logdatei+Txk[T_nicht_mit_fopen_zum_Lesen_oeffnen],1,0);
				return 1;
			}
			while (fgets(Zeile, sizeof Zeile, logf)) {
				//	 Zeilen.push_back(Zeile);
#endif	
#endif	
				if (!abhier) {
					tm *atm = new tm; time_t gesz; long sekunden; // int aktz;
					//	for(aktz=Zeilen.size()-1;aktz>=0;aktz--) KLA
					//         Log(string("aktz=") + ltoa_(aktz,buffer,10),obverb,0);
					int verwertbar=0, index;
					for(unsigned j=0;j<2;j++) {
						if (verwertbar) {
							index = verwertbar-1;
							j=2;
						} else {
							index = j;
						}
						switch (index) {
							case 0: 
								if (sscanf(Zeile,"%2d.%2d.%2d %2d:%2d:%2d%*s",&atm->tm_mday,&atm->tm_mon,&atm->tm_year,&atm->tm_hour,&atm->tm_min,&atm->tm_sec)==6) {
									if (!verwertbar) {
										verwertbar=1;
										j=2;
									}
									atm->tm_mon--;
									atm->tm_year+=100; // 2000-1900
									//	  <<atm->tm_mday<<"."<<atm->tm_mon+1<<"."<<atm->tm_year<<"."<<atm->tm_hour<<"."<<atm->tm_min<<"."<<atm->tm_sec<<endl;
									atm->tm_isdst=-1; // sonst wird zuf�llig ab und zu eine Stunde abgezogen
								} else if (verwertbar) verwertbar=0;
								break;
							case 1:
								if (strptime(Zeile,"%a %b %d %T %Y", atm)) {
									if (!verwertbar) {
										verwertbar=2;
										j=2;
									} //                   if (!verwertbar)
								} else if (verwertbar) verwertbar=0;
						} //             switch (index)
					} //           for(unsigned j=0;j<2;j++)
					if (verwertbar) {
						gesz=mktime(atm);
						//          	  char tbuf[20];
						//              strftime(tbuf, 18,"%d.%m.%y %X",localtime(&gesz));
						//              <<"Datum: "<<tbuf<<endl;
						time_t jetzt;
						jetzt=time(0);
						sekunden=(long)(jetzt-gesz);
						if (sekunden<1209600) {// j�nger als zwei Wochen => behalten
							abhier=1;
						}
						//	  <<jetzt<<"- "<<gesz<<"="<<sekunden<<endl;
					} // if (sscanf(Zeile
					delete[] atm;
				} // (!abhier)
				if (abhier) {
					outfile<<Zeile<<endl;
				} //         if (abhier)
			} //         if (!abhier)
			outfile.close();
#ifdef false
#ifdef obfstream
			*outfile<<Zeile<<endl;
		}
	}
	logf->close();
	outfile->close();
#else
	fputs(Zeile,outfile);
	//          fputs("\n",outfile);
} // (abhier)
} // while (fgets(Zeile
fclose(logf);
fclose(outfile);
#endif
#endif
if (abhier) {
	remove(logdatei);
	rename(ofil.c_str(),logdatei);
}else{
	remove(ofil.c_str());
}
return 0;
//  << "Alle Zeilen:" << endl;
// unsigned int ii; //unsigned, weil ansonsten Vergleich von signed- und unsigned-Werten. signed=vorzeichenbehaftet
// for(ii=0; ii < Zeilen.size(); ii++ddddddddds) KLA
//  << Zeilen[ii] << endl;
// KLZ
//  << endl;
//************************************
}	 // int kuerzelogdatei(const char* logdatei,int obverb)

string* loeschefarbenaus(string *zwi)
{
  loeschealleaus(zwi,schwarz);
  loeschealleaus(zwi,dgrau); 
  loeschealleaus(zwi,drot); 
  loeschealleaus(zwi,rot); 
  loeschealleaus(zwi,gruen); 
  loeschealleaus(zwi,hgruen); 
  loeschealleaus(zwi,braun); 
  loeschealleaus(zwi,gelb); 
  loeschealleaus(zwi,blau); 
  loeschealleaus(zwi,dblau); 
  loeschealleaus(zwi,violett); 
  loeschealleaus(zwi,hviolett); 
  loeschealleaus(zwi,tuerkis); 
  loeschealleaus(zwi,htuerkis); 
  loeschealleaus(zwi,hgrau); 
  loeschealleaus(zwi,weiss); 
  return zwi;
} // void loeschefarbenaus(string *zwi)

int Log(const string& text, short screen, short file, bool oberr, short klobverb)
{
  static unsigned int cols=0;
  static bool letztesmaloZ;
  const bool naechstezeile=0;
#ifdef false
  uchar erfolg=0;
#endif  
  // screen=0 = schreibt nicht auf den Bildschirm, 1 = schreibt, -1 = schreibt ohne Zeilenwechsel, -2 = schreibt bleibend ohne Zeilenwechsel
  // <<"Log: "<<text<<", screen: "<<screen<<", file: "<<file<<endl;
  if (file || screen) {
    if (screen) {
      if (!cols) cols=getcols();
      cout<<text;
      if (letztesmaloZ && (cols>=text.length())) {
        cout<<string(cols-text.length(),' ');
      }	
      if (screen==-2); else if (screen==-1 && !naechstezeile) {cout<<"\r";cout.flush();} else cout<<endl; 
      letztesmaloZ = (screen==-1);
    } // if (screen) 
    if (file) {
      if (!logdt || !*logdt) {
        cerr<<rot<<Txk[T_Variable_logdatei_leer]<<schwarz<<endl;
      } else {
        static bool erstaufruf=1;
        char tbuf[20];
        time_t jetzt=time(0);
        strftime(tbuf,sizeof tbuf,"%d.%m.%y %X: ",localtime(&jetzt));
        string zwi=tbuf+text; 
        loeschefarbenaus(&zwi);

        if (erstaufruf) {
          kuerzelogdatei(logdt,klobverb); // screen
          //          Log("nach kuerzelogdatei",screen,0);
          erstaufruf=0;
        }	  
        mdatei logf(logdt,ios::out|ios::app,0);
        if (!logf.is_open()) {
          perror((string("\nLog: ")+Txk[T_Kann_Datei]+logdt+Txk[T_nicht_als_fstream_zum_Anhaengen_oeffnen]).c_str());
          return 1;
        } else {
          logf<<zwi<<endl; 
          logf.close();
        }
#ifdef false        
#ifdef obfstream
        fstream *logf=oeffne(logdt,2,&erfolg);
        if (!erfolg) {
          perror((string("\nLog: ")+Txk[T_Kann_Datei]+logdt+Txk[T_nicht_als_fstream_zum_Anhaengen_oeffnen]).c_str());
          return 1;
        } else {
          *logf<<zwi<<endl; 
          logf->close();
        }
#else	
        FILE *logf=oeffne(logdt,2,&erfolg);
        if (!erfolg) {
          //perror((string("\nLog: Kann Datei '")+logdt+"' nicht mit fopen zum Anhaengen oeffnen.").c_str()); // ergebnisgleich wie:
          cerr<<"\nLog: "<<Txk[T_Kann_Datei]<<logdt<<Txk[T_nicht_mit_fopen_zum_Anhaengen_oeffnen]<<strerror(errno)<<endl;
          return 1;
        } else {
          fputs(string(string(tbuf)+zwi).c_str(),logf);
          fputs("\n",logf);
          fclose(logf);
        } // if (!erolg) else
#endif
#endif

      } // if (!logdt || !*logdt) _gKLA_ _gKLZ_ else _gKLA_
      if (oberr) {
        //      string hstrerror=strerror(errno); // da errno trotz richtiger Fallunterscheidung bei isatty(fileno(stdout)) gesetzt wird
        // wenn cerr woanders hingeht als cout oder die Meldung gar nicht an screen gerichtet ist, hier ohne Ber�cks.v.screen==-1
        if (isatty(fileno(stdout))!=isatty(fileno(stderr)) || !screen) {
          cerr<<text<<endl; // <<": "<<hstrerror<<endl;
        }
        errno=0;
      } //       if (oberr)
    } // (file)
  } // if (file || screen) 
  // <<"Screen: "<<screen<<"letztesmaloZ: "<<letztesmaloZ;
  // <<"und dann: "<<letztesmaloZ<<endl;
  return 0;
} // Log(string text)


#ifdef _MSC_VER
inline void wait () 
{
  cout<<Txk[T_Bitte_mit]<<_drot<<"return"<<_schwarz<<Txk[T_beenden];
  // L�scht etwaige Fehlerzust�nde die das Einlesen verhindern k�nnten
  cin.clear();
  // Ignoriert soviele Zeichen im Puffer wie im Puffer vorhanden sind
  // (= ignoriert alle Zeichen die derzeit im Puffer sind)
  cin.ignore(cin.rdbuf()->in_avail());
  // F�ge alle eingelesenen Zeichen in den Puffer bis ein Enter gedr�ckt wird
  // cin.get() liefert dann das erste Zeichen aus dem Puffer zur�ck, welches wir aber ignorieren (interessiert uns ja nicht)
  cin.get();
}  // inline void wait () 
#endif

// braucht nur 1/300 von FindStringInBuffer
long cmpmem( char* feld, const char* search, int len_feld) // , int len_search
{
  /*#ifdef _DEBUG
    gettimeofday(&perfStart, 0); 
#endif
   */
  long i=0;
  int j=-1;
  int len_search=strlen(search);
  for(; i<len_feld-len_search; feld++,i++){
    j=memcmp(feld, search, len_search);
    if (!j) 
      break;
  }
  /*
#ifdef _DEBUG
gettimeofday(&perfEnd, 0); 
#endif
#ifdef _DEBUG
#ifdef _WIN32
perf2= (((double)(perfEnd-perfStart))/((double)freq)); 
#else
perf2= static_cast<double> (perfEnd.tv_sec * 1000000 + perfEnd.tv_usec- perfStart.tv_sec * 1000000 - perfStart.tv_usec) / 1000000;
#endif
#endif
   */
  return !j?i:-1;
  //    return (i == len_feld-len_search)?0:feld;  

}    // long cmpmem( char* feld, const char* search, int len_feld) // , int len_search


char* ltoan(long value, int base, uchar obtz, uchar minstel) 
{
  /**
   * C++ version 0.4 char* style "itoa":
   * Written by Luk�s Chmela
   * Released under GPLv3.
   */
  const uchar resultlenge=30;
  static char result[resultlenge];
  // check that the base is valid
  if (base < 2 || base > 36) { *result = '\0'; return result; }

  char* ptr = result, *ptr1 = result, tmp_char;
  long tmp_value;

  uchar stelle=0,stellen=0;
  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    stellen++;
    if (obtz) if (value) if (++stelle==3) {*ptr++ ='.';stelle=0;stellen++;}
  } while ( value );
  while (stellen++<minstel && stellen<resultlenge) *ptr++ = ' ';

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
} // ltoan(long value, char* result, int base)

char* ltoa_(long value, char* result, int base=10) 
{
  /**
   * C++ version 0.4 char* style "itoa":
   * Written by Luk�s Chmela
   * Released under GPLv3.
   */
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0'; return result; }

  char* ptr = result, *ptr1 = result, tmp_char;
  long tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
} // ltoa_(long value, char* result, int base)

double verszuzahl(string vers)
{
 string vneu;
 uchar obkomma=0;
 for(size_t i=0;i<vers.size();i++) {
  if (strchr("0123456789",vers[i])) {
	 vneu+=vers[i];
	} else if (vers[i]=='.'||vers[i]==',') {
	 if (!obkomma) {
	  vneu+='.';
		obkomma=1;
	 } // 	 if (!obkomma)
	} //   if (strchr("0123456789",vers[i]))  else if ..
 } //  for(size_t i=0;i<vers.size();i++)
 if (vneu.empty()) return 0; else return atof(vneu.c_str());
} // double verstozahl(string vers)

// Programmversion, falls diese beim Programm mit " --version" abrufbar ist
double progvers(const string& prog,int obverb, int oblog)
{
	double vers=0;
	string pfad;
	if (obprogda(prog,obverb,oblog,&pfad)) {
		svec urueck;
		systemrueck(pfad+" --version",obverb,oblog,&urueck);
		if (urueck.size()) vers=verszuzahl(urueck[0].c_str());
	} // 	if (obprogda(prog,obverb,oblog,&pfad))
	return vers;
} // double progvers(string prog,int obverb, int oblog)

#ifdef notwendig
void kopierm(string *quelle, string *ziel)
{
  mdatei fileIn(quelle->c_str(),ios::in|ios::binary,0);
  mdatei fileOut(ziel->c_str(),ios::out | ios::trunc | ios::binary,0);
  fileOut<<fileIn.rdbuf();
} // void kopierm(string *quelle, string *ziel)
#endif

// von http://chris-sharpe.blogspot.de/2013/05/better-than-systemtouch.html
void touch(const std::string& pathname,int obverb/*=0*/,int oblog/*=*/)
{
  int fehler=0;
	int fd = open(pathname.c_str(), O_WRONLY|O_CREAT|O_NOCTTY|O_NONBLOCK, 0666);
	if (fd<0) { // Couldn't open that path.
		if (obverb) std::cerr << __PRETTY_FUNCTION__ << ": Couldn't open() path \"" << pathname << "\"\n";
		fehler=1;
	} else {
		int rc = utimensat(AT_FDCWD, pathname.c_str(), nullptr, 0);
		if (rc) {
			if (obverb) std::cerr << __PRETTY_FUNCTION__ << ": Couldn't utimensat() path \"" << pathname << "\"\n";
			fehler=1;
		}
		if (obverb||oblog) std::clog << __PRETTY_FUNCTION__ << ": Completed touch() on path \"" << pathname << "\"\n";
	}
	if (fehler)
		systemrueck("sudo touch '"+pathname+"'",obverb,oblog);
}

void aufSplit(vector<string> *tokens, const char *text, char sep, bool nichtmehrfach)
{
  const string texts=text;
  aufSplit(tokens,&texts,sep,nichtmehrfach);
} // void aufSplit(vector<string> *tokens, const char *text, char sep, bool nichtmehrfach)


void aufSplit(vector<string> *tokens, const string *text, char sep,bool nichtmehrfach) 
{
  int start = 0, end = 0;
  tokens->clear();
  while ((end = text->find(sep, start)) != (int)string::npos) {
    if (nichtmehrfach || end!=start) tokens->push_back(text->substr(start, end - start));
    start = end + 1;
  }
  tokens->push_back(text->substr(start));
} // void aufSplit(vector<string> *tokens, const string *text, char sep,bool nichtmehrfach) 


void aufiSplit(vector<string> *tokens, const string *text, const char* sep,bool nichtmehrfach) 
{
  int start = 0, end = 0;
  size_t len = strlen(sep);
  char* usep = new char[len];
  strcpy(usep,sep);
  for (char *p=usep ; *p; ++p) *p = toupper(*p);
  string utext;
  transform(text->begin(),text->end(),std::back_inserter(utext),::toupper);
  tokens->clear();
  while ((end = utext.find(usep, start)) != (int)string::npos) {
    if (nichtmehrfach || end!=start) {
      tokens->push_back(text->substr(start, end - start));
    }
    start = end + len;
  }
  tokens->push_back(text->substr(start));
  delete usep;
} // void aufiSplit(vector<string> *tokens, const string *text, const char* sep,bool nichtmehrfach) 


void aufSplit(vector<string> *tokens, const string *text, char* sep,bool nichtmehrfach) 
{
  int start = 0, end = 0;
  int len = strlen(sep);
  tokens->clear();
  while ((end = text->find(sep, start)) != (int)string::npos) {
    if (nichtmehrfach || end!=start) tokens->push_back(text->substr(start, end - start));
    start = end + len;
  }
  tokens->push_back(text->substr(start));
} // void aufSplit(vector<string> *tokens, const string *text, char* sep,bool nichtmehrfach) 

// Anfuehrungszeichen weg
string* anfzweg(string& quel) {
  if (quel.length()>1) {if (quel[0]==quel[quel.length()-1] && strchr("\"'",quel[0])) {
    quel.erase(quel.length()-1,1);
    quel.erase(0,1);
  }}
  return &quel;
} // string* anfzweg(


lsysen lsyscl::getsys(int obverb/*=0*/,int oblog/*=0*/)
{
      if (sys==usys) {
        if (!systemrueck("cat /proc/version | grep SUSE",obverb-2,oblog)) return sus;
        if (!systemrueck("cat /proc/version | grep 'Ubuntu\\|ebian'",obverb-2,oblog)) return deb;
        if (!systemrueck("cat /proc/version | grep edora",obverb-2,oblog)) return fed;
      } //       if (sys==usys)
      return usys;
} // lsysen lsyscl::getsys(int obverb/*=0*/,int oblog/*=0*/)

string& lsyscl::getlib64(int obverb/*=0*/,int oblog/*=0*/)
{
	if (usr_lib64_vz.empty()){
		if (getsys()==deb) {
			usr_lib64_vz="/usr/lib/x86_64-linux-gnu";
		} else {
			usr_lib64_vz="/usr/lib64";
		} // 		if (getsys()==deb) else
	} // 	if (usr_lib64_vz.empty())
	return usr_lib64_vz;
} // string& lsyscl::getlib64(int obverb/*=0*/,int oblog/*=0*/)

class lsyscl lsys;

/*
betrsys pruefos()
{
 static betrsys aktbs=keins;
 if (aktbs==keins) {
  svec rueck;
  systemrueck("which lsb_release >/dev/null 2>&1 && lsb_release -i || { test -f /etc/fedora-release && cat /etc/fedora-release;}",0,0,&rueck);
  if (rueck.size()) {
   if (rueck[0].find("SUSE LINUX")!=string::npos) aktbs=suse;
   else if (rueck[0].find("Ubuntu")!=string::npos) aktbs=ubuntu;
   else if (rueck[0].find("Fedora")!=string::npos) aktbs=fedora;
  }
 }
 return aktbs;
} // betrsys pruefos()
*/

// erg=1: gibt es fuer den aktuellen Benutzer; erg=2: gibt es fuer root; erg=0: nicht gefunden
int obprogda(const string& prog,int obverb, int oblog, string *pfad/*=0*/)
{
  if (prog.empty())
	  return 0;
	const int maxz=8;
  for(int iru=0;iru<maxz;iru++) {
    struct stat fstat={0};
    string verz;
		if (prog[0]=='/') iru=maxz; // z.B. /root/autofax/ocrv/bin/ocrmypdf
    switch (iru) {
      case 0: verz="/usr/local/bin/"; break;
      case 1: verz="/usr/bin/"; break;
      case 2: verz="/usr/local/sbin/"; break;
      case 3: verz="/usr/sbin/"; break;
      case 4: verz="/sbin/"; break;
      case 5: verz="/bin/"; break;
			case 6: verz="/usr/libexec/"; break;
			case 7: verz="/run/"; break;
      default: break;
    } //     switch (iru)
    verz+=prog;
    if (!lstat(verz.c_str(),&fstat)) {
      if (pfad) *pfad=verz;
      return 1;
    }
  } // for(int iru=0;iru<3;iru++) 
  svec rueck;
  if (!systemrueck("which "+prog+" 2>/dev/null",obverb,oblog,&rueck)) {
    if (pfad) *pfad=rueck[0];
    return 2;
  } // if (!systemrueck("which "+prog+" 2>/dev/null",obverb,oblog,&rueck))
  if (strcmp(curruser(),"root")) {
    if (!systemrueck("sudo which \""+prog+"\" 2>/dev/null || sudo env \"PATH=$PATH\" which \""+prog+"\" 2>/dev/null",obverb,oblog,&rueck)) {
      if (pfad) *pfad=rueck[0];
      return 3;
    }
  } // if (strcmp(curruser(),"root")) 
  if (pfad) pfad->clear();
  return 0; 
} // string obprogda(string prog,int obverb, int oblog)

instprog linst_cl::pruefipr(int obverb,int oblog)
{
	if (ipr==keinp) {
		if (obprogda("rpm",obverb-1,oblog)) {
			schau="rpm -q";
			dev="devel";
			if (obprogda("zypper",obverb-1,oblog)) { // opensuse
				// heruntergeladene Dateien behalten
				ipr=zypper;
				instp="sudo zypper -n --gpg-auto-import-keys in ";
				instyp=instp+"-y ";
				upr="sudo zypper -n rm -u ";
				uypr=upr+"-y ";
				repos="sudo zypper lr | grep 'g++\\|devel_gcc'>/dev/null 2>&1 || "
				      "sudo zypper ar http://download.opensuse.org/repositories/devel:/gcc/`cat /etc/*-release |"
							"grep ^NAME= | cut -d'\"' -f2 | sed 's/ /_/'`_`cat /etc/*-release | grep ^VERSION_ID= | cut -d'\"' -f2`/devel:gcc.repo;";
				compil="gcc gcc-c++ gcc6-c++";
			} else { // dann fedora
				if (obprogda("dnf",obverb-1,oblog)) {
					ipr=dnf;
					instp="sudo dnf install ";
					instyp="sudo dnf -y install ";
					upr="sudo dnf remove ";
					uypr="sudo dnf -y remove ";
				} else if (obprogda("yum",obverb-1,oblog)) {
					ipr=yum;
					instp="sudo yum install ";
					instyp="sudo yum -y install ";
					upr="sudo yum remove ";
					uypr="sudo yum -y remove ";
				} // 				if (obprogda("dnf",obverb-1,oblog))
				compil="make automake gcc-c++ kernel-devel";
			} // 			if (obprogda("zypper",obverb-1,oblog)) KLZ // opensuse
		} else if (obprogda("apt-get",obverb-1,oblog)) {
			// Repositories: Frage nach cdrom ausschalten
			systemrueck("sudo sh -c \"grep -q -m 1 '^[^#]*cdrom' /etc/apt/sources.list && test 0$(grep -n -m 1 '^[^#]*ftp.*debian' /etc/apt/sources.list |"
					"cut -d: -f1) \\> 0$(grep -n -m 1 '^[^#]*cdrom' /etc/apt/sources.list | cut -d: -f1) && "
					"ping -qc 1 www.debian.org >/dev/null 2>&1 && sed -i.bak '/^[^#]*cdrom/d' /etc/apt/sources.list\"",obverb,oblog);
			// hier werden die Dateien vorgabemaessig behalten
			ipr=apt;
			schau="dpkg -s";
			instp="sudo apt-get install "; 
			instyp="sudo apt-get -y --force-yes --reinstall install "; 
			upr="sudo apt-get --auto-remove purge ";
			uypr="sudo apt-get -y --auto-remove purge ";
			compil="install build-essential linux-headers-`uname -r`";
			dev="dev";
		} else {
			cerr<<Txk[T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden]<<endl;
		} // 		if (obprogda("rpm",obverb-1,oblog))
	} //   if (ipr==keinp)
	return ipr;
} // instprog linst_cl::pruefipr(int obverb,int oblog)

const string& absch::suche(const char* const sname)
{
  static const string nix;
  for (size_t i=0;i<av.size();i++) {
    if (av[i].name==sname) {
      return av[i].wert;
    }
  } //   for (size_t i=0;i<av.size();i++)
  return nix;
} // const string& absch::suche(const char* const sname)

const string& absch::suche(const string& sname)
{
  return suche(sname.c_str());
} // const string& absch::suche(const string& sname)

// Achtung: Wegen der Notwendigkeit zur Existenz der Datei zum Aufruf von setfacl kann die Datei erstellt werden!
int confdat::lies(const string& fname, int obverb)
{
  string zeile;
  if (fname.empty()) 
    return 2;
  mdatei f(fname,ios::in);
  if (f.is_open()) {
    if (obverb>0) cout<<"confdat::lies(fname...), fname: "<<blau<<fname<<schwarz<<endl;
    while (getline(f,zeile)) {
      zn<<zeile;
    }
    obgelesen=1;
    return 0;
  }
  return 1;
} // lies(const string& fname, int obverb)

void absch::clear()
{
 aname.clear();
 av.clear();
} // void absch::clear()


void confdat::Abschn_auswert(int obverb, char tz)
{
  absch abp;
  for(size_t i=0;i<zn.size();i++) {
    string *zeile=&zn[i];
    size_t pos=zeile->find('#');
    if (pos!=string::npos) zeile->erase(pos);
    gtrim(zeile);
    if (zeile->length()) {
      if (zeile->at(0)=='[' && zeile->at(zeile->length()-1)==']') {
        zeile->erase(zeile->length()-1);
        zeile->erase(0,1);
        if (/*!abp.aname.empty() && */abp.av.size()) {
           abschv.push_back(abp);
           abp.clear();
        }
        abp.aname=*zeile;
      } else {
        pos=zeile->find(tz);
        if (pos!=string::npos && pos>0) { 
          string name,wert;
          name=zeile->substr(0,pos);
          gtrim(&name);
          wert=zeile->substr(pos+1);
          gtrim(&wert);
          anfzweg(wert);
          abp.av.push_back(abSchl(name,wert));
        } //         if (pos!=string::npos && pos>0) 
      } //       if (zeile->at(0)=='[' && zeile->at(zeile->length()-1)==']') 
    } //     if (zeile->length()) 
  } //   for(size_t i=0;i<zn.size();i++) 
  if (!abp.aname.empty() && abp.av.size()) {
    abschv.push_back(abp);
  }
//  for(size_t i=0;i<abschv.size();i++) KLA
//   <<violett<<"aname: '"<<abschv[i].aname<<"'"<<endl;
//   for(size_t j=0;j<abschv[i].av.size();j++) 
//    <<j<<": "<<abschv[i].av[j].name<<": "<<abschv[i].av[j].wert<<endl;
//  KLZ
} // void confdat::Abschn_auswert(int obverb, char tz)

// aufgerufen in: confdat::confdat(const string& fname, schlArr *sA, int obverb, char tz):name(fname)
void confdat::auswert(schlArr *sA, int obverb, char tz)
{
  richtige=0;
  sA->reset();
  if (obgelesen) {
    string ibemerk;
    for(size_t i=0;i<zn.size();i++) {
      string *zeile=&zn[i];
      size_t pos=zeile->find('#');
      if (pos!=string::npos) {
        // wir nehmen an, die Kommentarzeile gehoert zum naechsten Parameter, wenn sie vorne beginnt
        if (!pos) {
        // Ueberschrift am Anfang  weglassen
          if (!richtige && zeile->find("onfigura")!=string::npos && zeile->find("automati")!=string::npos) {
          } else {
            if (!ibemerk.empty()) ibemerk+='\n';
            ibemerk+=zeile->substr(pos);
          } // if (!richtige ... else
        } // if (!pos)
        zeile->erase(pos);
      } // if (pos!=string::npos)
      ltrim(zeile);
      if (!zeile->empty()) {
        if (obverb>1) Log(string(Txk[T_stern_zeile])+*zeile,obverb);
        pos=zeile->find(tz);
        if (pos!=string::npos && pos>0) { 
          size_t ii=sA->zahl,gef;
          while( ii-- ) {
            gef=zeile->find((*sA)[ii].name);
            if (!gef) { // conf[ii].name muss am Zeilenanfang anfangen, sonst Fehler z.B.: number, faxnumber
              (*sA)[ii].gelesen=1;
              if (strchr((string(" ")+(char)9+tz).c_str(),zeile->at(gef+(*sA)[ii].name.length()))) {
                ++richtige;
                (*sA)[ii].wert=zeile->substr(pos+1);
                gtrim(&(*sA)[ii].wert); // Leerzeichen entfernen
                // Anfuehrungszeichen entfernen
                anfzweg((*sA)[ii].wert);
//      if (name.find("autofax")!=string::npos)
// <<" name: "<<schwarz<<(*sA)[ii].name<<violett<<" wert: '"<<schwarz<<(*sA)[ii].wert<<"'"<<violett<<" bemerk: '"<<ibemerk<<"'"<<schwarz<<endl;
                (*sA)[ii].bemerk=ibemerk;
                ibemerk.clear();
              } // if (strchr((string(" ")+(char)9+tz).c_str(),gef+(*sA)[ii].name.length())) 
              break;
            } // if( !strcmp(sA[i].name.c_str(),zeile->c_str()) ) 
            if (!gef)
              Log(rots+Txk[T_Fehler_bei_auswert]+schwarz+(*sA)[ii].name+rot+Txk[T_nicht_gefunden],obverb+1);
          } // while( ii-- ) 
        } // if (pos!=string::npos && 1==sscanf(zeile->c_str(),scs.c_str(),zeile->c_str())) 
      } // if (!zeile->empty()) 
    } // for(size_t i=0;i<zn.size();i++) 
  } // if (obgelesen) 
//  if (name.find("config.tty")!=string::npos) KLA
//    for(size_t ii=0;ii<sA->zahl;ii++) KLA
// <<" name: "<<schwarz<<(*sA)[ii].name<<violett<<" wert: '"<<schwarz<<(*sA)[ii].wert<<"'"<<violett<<" bemerk: '"<<(*sA)[ii].bemerk<<"'"<<schwarz<<endl;
//    KLZ
//  KLZ
} // void sAdat::auswert(cppSchluess *sA, size_t csize, int obverb, char tz)

/*
void confdat::auswert(cppSchluess *conf, size_t csize, int obverb, char tz)
{
  richtige=0;
  for(size_t i=0;i<csize;i++) {
    conf[i].wert.clear();
    conf[i].gelesen=0;
  }
  if (obgelesen) {
    for(size_t i=0;i<zn.size();i++) {
      string *zeile=&zn[i];
      size_t pos=zeile->find('#');
      if (pos!=string::npos) zeile->erase(pos);
      ltrim(zeile);
      if (!zeile->empty()) {
        if (obverb>1) Log(string(Txk[T_stern_zeile])+*zeile,obverb);
        pos=zeile->find(tz);
        if (pos!=string::npos && pos>0) { 
          size_t ii=csize,gef;
          while( ii-- ) {
            gef=zeile->find(conf[ii].name);
            if (!gef) { // conf[ii].name muss am Zeilenanfang anfangen, sonst Fehler z.B.: number, faxnumber
              conf[ii].gelesen=1;
              if (strchr((string(" ")+(char)9+tz).c_str(),zeile->at(gef+conf[ii].name.length()))) {
                ++richtige;
                conf[ii].wert=zeile->substr(pos+1);
                gtrim(&conf[ii].wert); // Leerzeichen entfernen
                // Anfuerhungszeichen entfernen
                anfzweg(conf[ii].wert);
              } // if (strchr((string(" ")+(char)9+tz).c_str(),gef+conf[ii].name.length())) 
              break;
            } // if( !strcmp(conf[i].name.c_str(),zeile->c_str()) ) 
            if (!gef)
              Log(rots+Txk[T_Fehler_bei_auswert]+schwarz+conf[ii].name+rot+Txk[T_nicht_gefunden],obverb+1);
          } // while( ii-- ) 
        } // if (pos!=string::npos && 1==sscanf(zeile->c_str(),scs.c_str(),zeile->c_str())) 
      } // if (!zeile->empty()) 
    } // for(size_t i=0;i<zn.size();i++) 
  } // if (obgelesen) 
} // void confdat::auswert(cppSchluess *conf, size_t csize, int obverb, char tz)
*/

confdat::confdat(const string& fname,int obverb):name(fname)
{
  if (!fname.empty())
  lies(fname,obverb);
} // confdat::confdat(const string& fname,int obverb):name(fname)


confdat::confdat(const string& fname, schlArr *sA, int obverb, char tz):name(fname)
{
  if (obverb>0) 
    cout<<violett<<Txk[T_Lese_Konfiguration_aus]<<blau<<fname<<violett<<"':"<<schwarz<<endl;
  if (!fname.empty()) {
    lies(fname,obverb);
    auswert(sA,obverb,tz);
  } //   if (!fname.empty())
} // confdat::confdat(const string& fname, schlArr *sA, int obverb, char tz):name(fname)


/*
confdat::confdat(const string& fname, cppSchluess *conf, size_t csize, int obverb, char tz)
{
  if (obverb>0) cout<<violett<<Txk[T_Lese_Konfiguration_aus]<<blau<<fname<<schwarz<<endl;
  lies(fname,obverb);
  auswert(conf,csize,obverb,tz);
}
*/
void schlArr::ausgeb()
{
  for(size_t i=0;i<zahl;i++) {
   cout<<"i: "<<gruen<<i<<schwarz<<" Name: "<<blau<<schl[i].name<<schwarz<<Txk[T_Wert]<<blau<<schl[i].wert<<schwarz<<endl;
  }
} // void schlArr::ausgeb()


void schlArr::reset()
{
  for(size_t i=0;i<zahl;i++) {
    schl[i].wert.clear();
    schl[i].gelesen=0;
  }
} // void schlArr::reset()


schlArr::schlArr()
{
 schl=0;
 zahl=0;
} // schlArr::schlArr()


void schlArr::neu(size_t vzahl)
{
 if (schl) delete[] schl;
 zahl=vzahl;
 schl=new cppSchluess[zahl];
} // void schlArr::neu(size_t vzahl)

/*// wird vielleicht nicht gebraucht
schlArr::schlArr(size_t zahl): zahl(zahl)
{
 schl = new cppSchluess[zahl];
}
*/

void schlArr::init(vector<cppSchluess*> *sqlvp)
{
  if (schl) delete[] schl;
  zahl=sqlvp->size();
  schl = new cppSchluess[zahl];
  for(size_t sqli=0;sqli<zahl;sqli++) {
    schl[sqli].name=sqlvp->at(sqli)->name;
    schl[sqli].wert=sqlvp->at(sqli)->wert;
  }
} // void schlArr::init(vector<cppSchluess*> *sqlvp)


void schlArr::init(size_t vzahl, ...)
{
 va_list list;
 va_start(list,vzahl);
 zahl=vzahl;
 if (schl) delete[] schl;
 schl = new cppSchluess[zahl];
 for(size_t i=0;i<zahl;i++) {
  schl[i].name=va_arg(list,const char*);
// <<rot<<"schl["<<i<<"].name: "<<schwarz<<schl[i].name<<endl;
 }
 va_end(list);
} // void schlArr::init(size_t vzahl, ...)

// das Setzen auch der Bemerkung wird bisher nicht benoetigt
int schlArr::setze(const string& name, const string& wert/*, const string& bem*/)
{
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
      schl[ind].wert=wert;
//      if (!bem.empty()) schl[ind].bemerk=bem;
      return 0;
    }
  } //   for(size_t ind=0;ind<zahl;ind++)
  return 1;
} // int schlArr::setze(const string& name, const string& wert)
 
const string& schlArr::hole(const string& name)
{
  static const string nix;
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
      return schl[ind].wert;
    }
  } //   for(size_t ind=0;ind<zahl;ind++)
  return nix;
} // const string* schlArr::hole(const string& name)

void cppSchluess::hole (struct tm *tmp) {
	if (!wert.empty()) {
		for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++) {
			if (strptime(wert.c_str(), tmmoegl[im], tmp)) break;
		}
		//		strptime(wert.c_str(), "%d.%m.%y %T", tmp);
	} // 	if (!wert.empty())
} // void cppSchluess::hole (struct tm *tmp)

// wenn die bisherige Bemerkung in einer Sprache mit der zu setzenden identisch, also nicht zwischenzeitlich manuell geaendert, 
// dann in aktueller Sprache uebernehmen
// fertige wird nur aufgerufen aus optioncl::setzebem(
void schlArr::setzbemv(const string& name,TxB *TxBp,size_t Tind,uchar obfarbe,svec *fertige)
{
  string bemst; 
  svec bemv, *vp;
  if (fertige) {
    vp=fertige;
	} else {
	  Sprache altSpr=TxBp->lgn;
		for(int akts=0;akts<Smax;akts++) {
			TxBp->lgn=(Sprache)akts;
			bemst=(*TxBp)[Tind];
			if (obfarbe) loeschefarbenaus(&bemst);
			bemv<<bemst;
		} //         for(int akts=0;akts<Smax;akts++)
		TxBp->lgn=altSpr;
		vp=&bemv;
	} // if fertige else
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
     uchar gefunden=0;
     if (schl[ind].bemerk.empty())
       gefunden=1;
     else {
       const string bv=schl[ind].bemerk.substr(2);
       for(int aktsp=0;aktsp<Smax;aktsp++) {
         if (bv==(*vp)[aktsp]) {
           gefunden=(aktsp!=TxBp->lgn); // wenn aktuelle Sprache, nichts tun
           break;
         } // if (bv==bemv[aktsp]) 
       } // for(int aktsp=0;aktsp<Smax;aktsp++) 
     } // (schl[ind].bemerk.empty) else
     if (gefunden) {
      schl[ind].bemerk="# "+(*vp)[TxBp->lgn];
     }
    } //     if (schl[ind].name==name)
  } //   for(size_t ind=0;ind<zahl;ind++)
} // void schlArr::setzbemv(const string& name,const string& bem)


void schlArr::aschreib(mdatei *f)
{
  for (size_t i = 0;i<zahl;i++) {
    if (!schl[i].bemerk.empty()) *f<<(schl[i].bemerk[0]=='#'?"":"# ")<<*loeschefarbenaus(&schl[i].bemerk)<<endl;
    *f<<schl[i].name<<" = \""<<schl[i].wert<<"\""<<endl;
  } //   for (size_t i = 0;i<zahl;i++)
} // void schlArr::aschreib(mdatei *f)

int schlArr::fschreib(const string& fname)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    aschreib(&f);
    return 0;
  } //   if (f.is_open())
  return 1;
} // int schlArr::fschreib(const string& fname)

schlArr::~schlArr()
{
  if (schl) delete[] schl;
}

int multischlschreib(const string& fname, schlArr **confs, size_t cszahl,string mpfad)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    if (!mpfad.empty()) {
      char buf[30];
      time_t jetzt=time(0);
      tm *ltm = localtime(&jetzt);
      strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", ltm);
      const string ueberschr=Txk[T_Konfiguration_fuer]+mpfad+Txk[T_erstellt_automatisch_durch_dieses_am]+buf;
      if (!ueberschr.empty()) f<<ueberschr<<endl;
    } //     if (!mpfad.empty())
    for (size_t j=0;j<cszahl;j++) {
     confs[j]->aschreib(&f);
    }
    return 0;
  } //   if (f.is_open())
  return 1;
} // int multischlschreib(const string& fname, schlArr **confs, size_t cszahl)


string XOR(const string& value, const string& key)
{
  string retval(value);
  short unsigned int klen=key.length(), vlen=value.length(), k=0, v;
  for(v=0;v<vlen;v++) {
    retval[v]=value[v]^key[k];
    k=(++k<klen?k:0);
  } //   for(v=0;v<vlen;v++)
  return retval;
} // string XOR(const string& value, const string& key)


int cppschreib(const string& fname, cppSchluess *conf, size_t csize)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    for (size_t i = 0;i<csize;i++) {
      f<<conf[i].name<<" = \""<<conf[i].wert<<"\""<<endl;
    }
    return 0;
  }
  return 1;
} // int cppschreib(const string& fname, cppSchluess *conf, size_t csize)

/*
int multicppschreib(const string& fname, cppSchluess **conf, size_t *csizes, size_t cszahl)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    for (size_t j=0;j<cszahl;j++) {
      for (size_t i = 0;i<csizes[j];i++) {
        f<<conf[j][i].name<<" = \""<<conf[j][i].wert<<"\""<<endl;
      }
    }
    return 0;
  }
  return 1;
} // int multicppschreib(const string& fname, cppSchluess **conf, size_t *csizes, size_t cszahl)
*/

#ifdef notcpp
int Schschreib(const char *fname, Schluessel *conf, size_t csize)
{
#ifdef false
  uchar erfolg=0;
#endif
  mdatei f(fname,ios::out);
  if (!f.is_open()) { return 1; }
  for(size_t i=0;i<csize;i++) {
    f<<conf[i].key<<" = \""<<conf[i].val<<"\""<<endl;
  }
#ifdef false
#ifdef obfstream 
  fstream *f=oeffne(fname,3,&erfolg);
  if (!erfolg) return 1;
  for(size_t i=0;i<csize;i++) {
    *f<<conf[i].key<<" = \""<<conf[i].val<<"\""<<endl;
  }
#else
  FILE *f=oeffne(fname,3,&erfolg);
  if (!erfolg) return 1;
  for (size_t i = 0;i<csize;i++) {
    fprintf(f,"%s = \"%s\"\n",conf[i].key,conf[i].val);
  }
  fclose(f);
#endif
#endif	
  return 0;
} // int Schschreib(const char *fname, Schluessel *conf, size_t csize)
#endif

// Dateiname ohne Pfad
std::string base_name(const std::string& path)
{
  return path.substr(path.find_last_of("/\\") + 1);
} // std::string base_name(std::string const & path)

// Pfadname einer Datei
std::string dir_name(const std::string& path)
{
  return path.substr(0,path.find_last_of("/\\"));
} // std::string dir_name(std::string const & path)

// soll fuer den Fall eines uebergebenen 'rueck'-Zeigers den Rueckgabewert der aufgerufenen Funktion zuruckliefern,
// ausser bei 'find', da die Zahl der Funde
// bei rueck==0 liefert es das Ergebnis der system(..)-Funktion zurueck
// obverb: 1 = Befehl anzeigen, 2 = auch Rueckgabezeilen anzeigen
// obergebnisanzeig: 1=falls Fehler und obverb>1, >1=falls Fehler
int systemrueck(const string& cmd, char obverb/*=0*/, int oblog/*=0*/, vector<string> *rueck/*=0*/, 
    int verbergen/*=0*/, int obergebnisanzeig/*wahr*/, const string& ueberschr/*=""*/,vector<errmsgcl> *errm/*=0*/,uchar obincron/*=0*/)
{
// verbergen: 0 = nichts, 1= '2>/dev/null' anhaengen + true zurueckliefern, 2='>/dev/null 2>&1' anhaengen + Ergebnis zurueckliefern
  binaer ob0heissterfolg=wahr;
  uchar neurueck=0;
  uchar weiter=0;
  int erg=-111;
  string hcmd=cmd;
  uchar obfind=(cmd.substr(0,4)=="find" || cmd.substr(0,9)=="sudo find");
  if (verbergen==1 || (obfind && (obverb<1 || strcmp(curruser(),"root")))) {
    if (obverb<=1) 
      hcmd+=" 2>/dev/null; true";
  } else if (verbergen==2) {
    if (obverb<=1)
      hcmd+=" >/dev/null 2>&1";
  } //   if (verbergen==1 || (obfind && (obverb<1 || strcmp(curruser(),"root")))) else iff
  string *czg=&hcmd;
	if (obincron) {
    vector<string> tok;
    aufSplit(&tok,czg,' ');
		if (tok.size()>0) {
		 if (obprogda(tok[0],obverb,oblog,czg)) {
			for(unsigned j=1;j<tok.size();j++) {
			 *czg+=' ';
			 *czg+=tok[j];
			} // 			for(unsigned j=1;j<tok.size();j++)
		 } // 		 if (obprogda(tok[0],obverb,oblog,czg))
		} // 		if (tok.size()>0)
	} // 	if (obincron)
  // "obfind: "<<(int)obfind<<", obverb: "<<(int)obverb<<", curruser(): "<<curruser()<<", '"<<violett<<*czg<<schwarz<<"'"<<endl;
  string meld(Txk[T_Rueckmeldung]);
  string aktues;
  if (ueberschr.empty()) { 
    if (obfind) {
      aktues=Txk[T_Suchbefehl];
    } else {
      aktues=Txk[T_Fuehre_aus];
      weiter=1;
    } //     if (obfind)
  } else {
    aktues=ueberschr;
  } //   if (ueberschr.empty())
  Log(aktues+": "+blau+czg->substr(0,getcols()-7-aktues.length())+schwarz+" ...",obverb>0?-1:0,oblog);
  if (!rueck) if (obergebnisanzeig) {neurueck=1;rueck=new vector<string>;}
  // #define systemrueckprofiler
#ifdef systemrueckprofiler
  perfcl prf("systemrueck");
#endif
  if (rueck) {
    if (FILE* pipe = popen(czg->c_str(), "r")) {
#ifdef systemrueckprofiler
      prf.ausgeb();
#endif
      //    setvbuf ( pipe, NULL, _IOFBF, 2048);
      /*
         int fd = fileno(pipe);

         int flags;
         flags = fcntl(fd, F_GETFL, 0);
         flags |= O_NONBLOCK;
         fcntl(fd, F_SETFL, flags);
       */
      //      unsigned int zeile=0;
      while(1) {
#ifdef systemrueckprofiler
        prf.ausgab1000("in while");
#endif
        if (feof(pipe)) break;
        //        zeile++;
        char buffer[1280];
        // in der folgenden Zeile werden auch ggf. sterr-Meldungen ausgegeben/weitergeleitet
        if (fgets(buffer, sizeof buffer, pipe)) {
          size_t posi;
          if (buffer[posi=strlen(buffer)-1]==10) buffer[posi]=0;
          rueck->push_back(string(buffer));
        } // if(fgets(buffer, sizeof buffer, pipe) != NULL)
        if (feof(pipe)) break;
      } // while(!feof(pipe)) 
#ifdef systemrueckprofiler
      prf.ausgab1000("nach while");
#endif
      if (obverb>1 || oblog || obergebnisanzeig) if (rueck->size()) {
        for(unsigned i=0;i<rueck->size();i++) {
#ifdef systemrueckprofiler
#endif
          meld=meld+"\n"+tuerkis+rueck->at(i)+schwarz;
        }
      }
#ifdef systemrueckprofiler
      Log(rots+"Rueck.size: "+ltoan(rueck->size())+", obergebnisanzeig: "+(obergebnisanzeig?"ja":"nein"),1,oblog);
      Log(*czg,1,oblog)
        prf.ausgab1000("vor pclose");
#endif
      if (obfind) {
        erg=rueck->size();
      } else
        erg = pclose(pipe)/256;
#ifdef systemrueckprofiler
      prf.ausgab1000("nach pclose");
#endif
    } else {
      perror((string("popen() ")+Txk[T_fehlgeschlagen_bei]+*czg).c_str());
      erg=1;
    } //     if (FILE* pipe = popen(czg->c_str(), "r"))  else 
  } else {
    erg= system(czg->c_str());
  } // if (rueck) else
#ifdef systemrueckprofiler
  prf.ausgab1000("vor weiter");
#endif
	if (weiter) aktues=Txk[T_Fuehrte_aus];
	if (obverb>0 || oblog) {
		string ergebnis;
		if (errm) {
			for(size_t i=0;i<errm->size();i++) {
				if (erg==errm->at(i).errnr) {
					ergebnis=(erg?rots:gruens)+ltoan(erg)+": "+gruen+errm->at(i).msg;
					break;
				} // 				if (erg==errm->at(i).errnr)
			} // for(size_t i=0;i<errm->size();i++) 
		}  // if (errm)
		if (ergebnis.empty()) {
			if (obfind) {
				ergebnis=gruens+ltoan(erg)+blau+string(Txk[T_Zeilen]);
			} else {
				if (ob0heissterfolg) {
					if (erg) {
						if (cmd.substr(0,6)=="rpm -q" || cmd.substr(0,7)=="dpkg -s" || 
						    cmd.substr(0,5)=="which" || cmd.substr(0,10)=="sudo which" || cmd.substr(0,16)=="sudo iptables -L") {
							ergebnis=gruens+Txk[T_nicht_gefunden];
						} else if (cmd.substr(0,14)=="sudo modprobe ") {
						  ergebnis=gruens+Txk[T_nicht_einfuegbar];
						} else {
							ergebnis=rots+Txk[T_Fehler]+ltoan(erg);
						}
						if (obverb>=0) obergebnisanzeig=wahr;
						obverb++;
					} else {
						ergebnis=Txk[T_Erfolg];
					} // ob0heissterfolg else
				} else {
					ergebnis=ltoan(erg);
				} // 				if (ob0heissterfolg) else
			} // 			if (obfind) else
		} //     if (ergebnis.empty()
#ifdef systemrueckprofiler
    prf.ausgab1000("vor log");
#endif
    Log(aktues+": "+blau+*czg+schwarz+Txk[T_komma_Ergebnis]+blau+ergebnis+schwarz,obverb>0?obverb:0,oblog);
  } // if (obverb>0 || oblog)
  if (obergebnisanzeig) if (rueck->size()) 
    Log(meld,obverb>1||(ob0heissterfolg && erg && obergebnisanzeig>1),oblog);
  if (neurueck) delete rueck;
  return erg; 
} // int systemrueck(const string& cmd, char obverb, int oblog, vector<string> *rueck, binaer ...

void pruefplatte()
{
  struct statvfs fp={0};
  const string platte="/";
  statvfs(platte.c_str(),&fp);   
  if (fp.f_bsize * fp.f_bfree < 100000) { // wenn weniger als 100 MB frei sind ...
    systemrueck("sudo pkill postdrop");
  }
} // pruefplatte

// ob das aktuelle Programm mehrfach laeuft
void pruefmehrfach(const string& wen)
{
  svec rueck;
	const string iwen=wen.empty()?base_name(meinpfad()):wen;
  systemrueck("ps -eo comm|grep '^"+iwen+"'",0,0,&rueck);
  if (rueck.size()>1) {
    cout<<Txk[T_Program]<<blau<<iwen<<schwarz<<Txk[T_laeuft_schon_einmal_Breche_ab]<<endl;
    exit(98);
  } //   if (rueck.size()>1) {
  /*
  for(size_t j=0;j<rueck.size();j++) {
   // <<violett<<"rueck["<<j<<"]: "<<rot<<rueck[j]<<schwarz<<endl;
  }
  */
} // void pruefmehrfach(char* ich)

// <datei> kann auch Verzeichnis sein
// obunter = mit allen Unterverzeichnissen
// obimmer = immer setzen, sonst nur, falls mit getfacl fuer datei Berechtigung fehlt (wichtig fuer Unterverzeichnisse)
int setfaclggf(const string& datei,const binaer obunter,const int mod/*=4*/,uchar obimmer/*=0*/,int obverb/*=0*/,int oblog/*=0*/,uchar faclbak/*=1*/)
{
  static const string cuser=curruser(); 
  if (cuser!="root") {
      static int obsetfacl=obprogda("setfacl",obverb-1,0);
      if (obsetfacl) {
       const char* modbuch;
       switch (mod) {
        case 4: modbuch="r"; break;
        case 6: modbuch="rw"; break;
        default: modbuch="rwx";  // 7
       } //        switch (mod)
       if (!obimmer) {
        svec gstat;
        systemrueck("getfacl -e -t '"+datei+"' 2>/dev/null | grep 'user[ \t]*"+cuser+"[ \t]*"+modbuch+"' || true",obverb,oblog,&gstat);
        if (!gstat.size()) obimmer=wahr; // wenn keine Berechtigung gefunden => erstellen
       }
       if (obimmer) {
          if (obverb) systemrueck("sudo sh -c 'ls -l \""+datei+"\"'",2,0);
					if (faclbak) {
						string sich=base_name(datei)+"."+base_name(meinpfad())+".perm";
						systemrueck("sudo sh -c 'cd \""+dir_name(datei)+"\";test -f \""+sich+"\"||getfacl -R \""+base_name(datei)+"\">\""+sich+"\"'",obverb,oblog);
						anfgggf(unindt,"sudo sh -c 'cd \""+dir_name(datei)+"\";setfacl --restore=\""+sich+"\"'");
					}
					systemrueck(string("sudo setfacl -")+(obunter?"R":"")+"m 'u:"+cuser+":"+ltoan(mod)+"' '"+datei+"'",obverb,oblog);
          if (obverb) systemrueck("sudo sh -c 'ls -l \""+datei+"\"'",2,0);
       } //        if (obimmer)
      } //       if (obsetfacl)
  } //   if (cuser!="root")
  return 0;
} // int setfaclggf(const string& datei, const binaer obunter, const int mod, binaer obimmer,int obverb, int oblog)


// obmitfacl: 1= setzen, falls noetig, >1= immer setzen
int pruefverz(const string& verz,int obverb/*=0*/,int oblog/*=0*/, uchar obmitfacl/*=1*/,uchar obmitcon/*=1*/)
{
  struct stat sverz={0};
  int fehler=1;
  if (!verz.empty()) {
    if (!lstat(verz.c_str(), &sverz)) {
      if(S_ISDIR(sverz.st_mode)) {
        fehler=0;
      }
    } //     if (!lstat(verz.c_str(), &sverz))
    if (fehler) {
		  fehler=systemrueck("mkdir -p '"+verz+"' 2>/dev/null||sudo mkdir -p '"+verz+"'",obverb,oblog);
			anfgggf(unindt,"sudo rmdir '"+verz+"'");
		}
//    if (fehler) fehler=systemrueck("sudo mkdir -p '"+verz+"'",obverb,oblog);
    if (obmitfacl) setfaclggf(verz, wahr, 7, (obmitfacl>1),obverb,oblog);
		 // <<violett<<verz<<schwarz<<endl;
		if (obmitcon) systemrueck("which sestatus 2>/dev/null && sudo chcon -R -t samba_share_t '"+verz+"'",obverb,oblog);
  } // if (!verz.empty())
  return fehler;
} // void pruefverz(const string& verz,int obverb,int oblog)


string aktprogverz()
{
  char pBuf[300];
#if defined(__MINGW32__) || defined(_MSC_VER)
  int bytes = GetModuleFileName(NULL, pBuf, sizeof pBuf);
  if(bytes == 0) pBuf[0]=0;
#elif linux
  char szTmp[32];
  sprintf(szTmp, "/proc/%d/exe", getpid());
  int bytes = MIN(readlink(szTmp, pBuf, sizeof pBuf), sizeof pBuf - 1);
  if(bytes >= 0) pBuf[bytes] = 0;
#endif
  return string(pBuf);
} // string aktprogverz()

char Tippbuchst(const string& frage, const string& moegl,const char *berkl[], const char* erlaubt, const char *vorgabe) 
{
  string input;
  if (!erlaubt) erlaubt=moegl.c_str();
  while(1) {
    cout<<blau<<frage<<schwarz<<" (";
    for(unsigned i=0;i<moegl.length();i++) {
      cout<<"'"<<drot<<moegl[i]<<schwarz<<"'";
      if (berkl) cout<<" = "<<blau<<berkl[i]<<schwarz;
      if (i<moegl.length()-1) cout<<", ";
    }
    cout<<")"<<(!vorgabe?"":string("['")+tuerkis+vorgabe+schwarz+"']")<<"?: ";
    input="";
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input=="" && vorgabe) {input=vorgabe;break;}
    if (input[0]) if (strchr(erlaubt,(int)input[0])) break;
  } //   while(1)
  return input[0];
  //  return Tippbuchst(frage.c_str(), moegl.c_str(), berkl, erlaubt, vorgabe);
} // char Tippbuchst(const string& frage, const string& moegl,const char *berkl[], const char* erlaubt, const char *vorgabe) 


// vorgabe fur vorgabe = T_j_k; alternativ='n'
uchar Tippob(const string& frage,const char *vorgabe) 
{
  char erg=Tippbuchst(frage, string(Txk[T_j_k])+"n",0,"jJyYoOsSnN",vorgabe);
  return (!!strchr("jyJYoOsS",(int)erg));
} // uchar Tippob(const string& frage,const char *vorgabe) 

// bisher nicht verwendet, 15.12.15
string Tippstrings(const char *frage, char* moegl[], char *vorgabe)
  // das letzte Element von moegl muss 0 sein
{
  string input;
  while(1) {
    char passt=0;
    cout<<blau<<frage<<schwarz<<" (";
    for(unsigned i=0;moegl[i];i++) {
      if (i) cout<<", ";
      cout<<"'"<<drot<<moegl[i]<<schwarz<<"'";
    }
    cout<<")"<<(vorgabe?"":string("['")+tuerkis+vorgabe+schwarz+"']")<<"?: ";
    input="";
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    // <<rot<<"input: '"<<input<<"', vorgabe: '"<<vorgabe<<"'"<<endl<<schwarz;
    if (input=="" && vorgabe) {input=vorgabe;break;}
    if (input[0]) {
      for(unsigned i=0;moegl[i];i++) {
        if (!strcmp(moegl[i],input.c_str())) {passt=1;break;}
      }
    } //     if (input[0])
    if (passt) break; 
  } //   while(1)
  return input;
} // Tippstrings

string Tippstrings(const char *frage, vector<string> *moegl, string *vorgabe)
{
  string input;
  while(1) {
    char passt=0;
    cout<<blau<<frage<<schwarz<<" (";
    for(unsigned i=0;i<moegl->size();i++) {
      if (i) cout<<",";
      //      cout<<"'"<<drot<<moegl->at(i)<<schwarz<<"'";
      cout<<drot<<moegl->at(i)<<schwarz;
    } //     for(unsigned i=0;i<moegl->size();i++)
    cout<<")"<<(vorgabe->empty()?"":string("['")+tuerkis+*vorgabe+schwarz+"']")<<"?: ";
    input="";
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    // <<rot<<"input: '"<<input<<"', vorgabe: '"<<*vorgabe<<"'"<<endl<<schwarz;
    if (input.empty() && !vorgabe->empty()) {input=*vorgabe;break;}
    if (input[0]) {
      for(unsigned i=0;i<moegl->size();i++) {
        if (moegl->at(i)==input) {passt=1;break;}
      }
    } //     if (input[0])
    if (passt) break; 
  } //   while(1)
  return input;
} // Tippstrings


string Tippzahl(const char *frage, const char *vorgabe) 
{
  string input;
  while(1) {
    cout<<blau<<frage<<schwarz<<(!vorgabe?"":string(" [")+tuerkis+vorgabe+schwarz+"]")<<"? ";
    input="";
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input=="" && vorgabe) {input=vorgabe;break;}
    if (isnumeric(input)) break;
  }
  return input;
} // Tippzahl

string Tippzahl(const char *frage, string *vorgabe) 
{
  return Tippzahl(frage,(vorgabe?vorgabe->c_str():0)); 
}
string Tippzahl(const string& frage, string *vorgabe)
{
 return Tippzahl(frage.c_str(),(vorgabe?vorgabe->c_str():0));
}

char* Tippcstring(const char *frage, char* buf, unsigned long buflen, const char* vorgabe) 
{
  const string vstr=string(vorgabe);
  strncpy(buf,Tippstring(string(frage),&vstr).c_str(),buflen-1);
  buf[buflen-1]=0;
  return buf;
} // Tippcstring

string Tippstring(const char *frage, const string *vorgabe) 
{
  return Tippstring(string(frage), vorgabe);
} // Tippstring

string Tippstring(const string& frage, const string *vorgabe) 
{
  string input;
  while(1) {
    cout<<blau<<frage<<schwarz<<(!vorgabe || vorgabe->empty()?"":string(" [\"")+tuerkis+*vorgabe+schwarz+"\"]")<<"? ";
    input.clear();
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input.empty() && vorgabe) {
     input=*vorgabe;
     break;
    } //     if (input=="" && vorgabe)
    break;
  } //   while(1)
  return input;
} // Tippstring

string Tippverz(const char *frage,string *vorgabe) 
{
  string input, vg2="n"; uchar fertig=0;
  while(1) {
    cout<<blau<<frage<<schwarz<<(!vorgabe || vorgabe->empty()?"":string(" [\"")+tuerkis+*vorgabe+schwarz+"\"]")<<"? ";
    input="";
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input=="" && vorgabe) {input=*vorgabe;}
    struct stat st={0};
    //    <<"input: '"<<rot<<input<<schwarz<<"'"<<endl;
    while (1) {
      if (!lstat(input.c_str(), &st)) {
        if(S_ISDIR(st.st_mode)) {
          fertig=1;
          break;
        } else {
          cout<<"'"<<rot<<input<<schwarz<<Txk[T_kein_Verzeichnis_nochmal];
          break;
        }
      } else {
        string inpi;
        cout<<" '"<<rot<<input<<schwarz<<Txk[T_nicht_gefunden_soll_ich_es_erstellen]<<drot<<Txk[T_j_k]<<schwarz;
        cout<<"/"<<drot<<"n"<<schwarz<<")(\""<<tuerkis<<vg2<<schwarz<<"\")?";
        getline(cin,inpi);
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
        if (inpi=="") {inpi=vg2;break;}
        if (strchr("jyJY",inpi[0])) {
          pruefverz(input);
          /*
          int erg __attribute__((unused));
          erg=system((string("sudo mkdir -p ")+input).c_str());
          */
        } else {
          break;
        } //         if (strchr("jyJY",inpi[0])) else
      } //       if (!lstat(input.c_str(), &st)) else
    } //     while (1)
    if (fertig) break;
  } //   while(1)
  return input;
} // Tippverz

uchar VerzeichnisGibts(const char* vname)
{
  DIR *verz;
  if ((verz=opendir(vname))){
    closedir(verz);
    return 1;
  }
  return 0;
} // VerzeichnisGibts

int optioncl::pruefpar(vector<argcl> *argcvm , size_t *akt, uchar *hilfe, Sprache lg) // 1 = das war der Parameter, 0 = nicht
// argcvm = Vektor der Kommandozeilenparameter
// *akt = Index auf aktuell zu untersuchenden
// *hilfe = Aussage, ob Hilfe aufgerufen werden muss
// vorangestellte "1" => opschreibp auf 0 setzen
// vorangestelltes "un" => bei binaeren Operatoren nicht
{
//  Log(violetts+Txk[T_pruefpar]+schwarz+" "+ltoan(*akt),1,0);
  uchar nichtspeichern=0;
  uchar gegenteil=0;
// wenn der Index noch im Bereich und der zugehoerige Kommandozeilenparameter noch nicht unter den Programmparametern gefunden wurde ...
  if (*akt<argcvm->size()) if (!argcvm->at(*akt).agef) {
    char *acstr=argcvm->at(*akt).argcs;
//    <<rot<<"acstr: "<<schwarz<<acstr<<endl;
    int aclen=strlen(acstr);
    if (aclen>1) {
      if (aclen>2 && acstr[0]=='-'&&acstr[1]=='-') {
        acstr+=2;
        aclen-=2;
        if (aclen>1 && *acstr=='1') {
         nichtspeichern=1; 
         acstr++;
         aclen--;
        }
        if (aclen>2 && acstr[0]=='n'&&acstr[1]=='o') {
         gegenteil=1;
         acstr+=2;
         aclen-=2;
        }
        if (!strcmp(acstr,lang.c_str())) {
          argcvm->at(*akt).agef=1;
        }
      } else if (strchr("-/",acstr[0])) {
        acstr+=1;
        aclen-=1;
        if (aclen>1 && *acstr=='1') {
         nichtspeichern=1; 
         acstr++;
         aclen--;
        }
        if (aclen>2 && acstr[0]=='n'&&acstr[1]=='o') {
         gegenteil=1;
         acstr+=2;
         aclen-=2;
        }
        if (!strcmp(acstr,kurz.c_str())) {
          argcvm->at(*akt).agef=1;
        }
      } //       if (strchr("-/",acstr[0])
    } // if (strlen(acstr)>1) 
    // wenn Kommandozeilenparameter gefunden ...
    if (argcvm->at(*akt).agef) {
      // ... und zu setzender binaerer Parameter hinterlegt ...
      if (pptr) {
        // ggf. auf Gegenteil korrigieren
        if (gegenteil) wert=!wert;
        // ... und dieser noch nicht richtig gesetzt ist ...
        if (*pptr!=wert) {
          // ... dann setzen ...
          *pptr=wert;
          // ... merken, dass die Konfigurationsdatei geschrieben werden muss ...
          if (!nichtspeichern) {
            if (obschreibp) *obschreibp=1;
            // ... und wenn ein Konfigurationsarray uebergeben wurde und ein Elementname dazu ...
            if (cp && pname) {
              // ... dann diesen auch auf den Wert setzen
              cp->setze(pname,ltoan(wert));
            } //             if (cp && pname)
          } // if (!nichtspeichern)
        } // if (*pptr!=wert) 
        // wenn also kein binaerer Parameter hinterlegt (=> Textparameter)
      } else {
        char *pstr=0;
        uchar wiefalsch=0;
        // und hinter dem aktuellen Parameter noch einer kommt ...
        if (*akt<argcvm->size()-1) {
          char *nacstr=argcvm->at(*akt+1).argcs;
          struct stat entryarg={0};
          switch (art) {
              // und das ein "sonstiger Parameter" ist, ...
            case psons:
            // er also nicht mit '-' oder '/' anfaengt ...
              if (!strchr("-/",nacstr[0])) {
                // ... dann zuweisen
                pstr=nacstr;
              }
              break;
              // wenn es ein Verzeichnis oder eine Datei sein soll ...
            case pverz:
            case pfile:
              // ... die also nicht mit '-' anfaengt
              if (nacstr[0]!='-') {
                // ... und sie bestimmte existentielle Bedingungen erfuellt ...
                if (stat(nacstr,&entryarg)) wiefalsch=1;  // wenn inexistent
                else if ((art==pverz)^(S_ISDIR(entryarg.st_mode))) wiefalsch=2; // Datei fuer Verzeichnis o.u.
                // ... dann zuweisen
                else pstr=nacstr;
              }
              break;
              // oder wenn es eine Zahl sein soll ...
            case pzahl:
            // und sie nicht mit '-' oder '/' anfaengt ...
              if (!strchr("-/",nacstr[0])) {
                // und tatsaechlich numerisch ist ...
                if (!isnumeric(nacstr)) wiefalsch=1;
                // dann zuweisen
                else pstr=nacstr;
              } // if (!strchr("-/",nacstr[0])) 
              break;
          } // switch (art) 
        } // if (*akt<argcvm->size()-1)
        /// wenn nacstr als Zusatzparameter bestaetigt
        if (pstr) {
          // ... und dessen Inhalt sich von zptr unterscheidet ...
          if (*zptr!=pstr) {
            // ... dann zuweisen ...
            *zptr=pstr; 
            // ... und ggf. Konfigurationsdatei speichern, 
            if (!nichtspeichern) {
              if (obschreibp) *obschreibp=1;
              // wenn Konfigurationsarray und ein Indexname dort uebergeben ... 
              if (cp && pname) {
                // dann Inhalt dort zuweisen
                cp->setze(pname,pstr);
              } // if (cp && pname)
            } // if (!nichtspeichern)
          } // if (*zptr!=pstr) 
          argcvm->at(++(*akt)).agef=1;
        } else {
          // wenn kein Zusatzparameter erkennbar, dann melden
          switch (art) {
            case psons:
              Log(drots+Txk[T_Fehlender_Parameter_string_zu]+kurz+Txk[T_oder]+lang+"!"+schwarz,1,1);
              break;
            case pverz:
            case pfile:
              Log(drots+Txk[T_Fehler_Parameter]+kurz+Txk[T_oder]+lang+" "+(wiefalsch==1?Txk[T_ohne_gueltigen]:wiefalsch==2?
                    Txk[T_mit_Datei_als]:Txk[T_mit_falschem])+Txk[T_Pfad_angegeben]+schwarz,1,1);
              break;
            case pzahl:
              Log(drots+(wiefalsch==1?Txk[T_Nicht_numerischer]:Txk[T_Fehlender])+Txk[T_Parameter_nr_zu]+kurz+Txk[T_oder]+lang+"!"+schwarz,1,1);
              break;
          } // switch (art)
          *hilfe=1;
        } // if (pstr) else
      } // if (pptr) else
      return 1;
    } // if (argcvm->at(*akt).agef)
  } // if (*akt<argcvm->size()) if (!argcvm->at(*akt).agef) 
  return 0;
} // pruefpar

string& optioncl::machbemerkung(Sprache lg,binaer obfarbe)
{
 static const string nix; // =""
 bemerkung.clear();
  if (TxBp) {
    if (Txi!=-1) {
      if (TxBp->TCp[Txi][lg]) {
        TCtp *hilf = reinterpret_cast<TCtp*>(TxBp->TCp);
        bemerkung= (const char*)hilf[Txi][lg];
        if (rottxt) bemerkung+=(obfarbe?blaus:nix)+*rottxt+(obfarbe?schwarz:nix);
        if (Txi2!=-1) bemerkung+=(const char*)hilf[Txi2][lg]; 
        if (zptr) bemerkung+=" '"+(obfarbe?blaus:nix)+*zptr+(obfarbe?schwarz:nix)+"'";
        if (obno) bemerkung+=(obfarbe?violetts:nix)+Txk[T_oder_nicht]+(obfarbe?schwarz:nix);
      } // if (TxBp->TCp[Txi][lg])
    } // if (Txi!=-1)
  } // if (TxBp)
  return bemerkung;
} // string& optioncl::machbemerkung(Sprache lg,binaer obfarbe)

void optioncl::hilfezeile(Sprache lg)
{
  if (TxBp) {
    if (Txi!=-1) {
      if (TxBp->TCp[Txi][lg]) {
        cout<<drot<<" -"<<kurz<<", --"<<lang;
        if (zptr) {if (art==psons || art==pfile) cout<<" <string>"; else if (art==pverz) cout<<" <"<<Txk[T_pfad]<<">"; else cout<<" <zahl>";}
        cout<<schwarz<<": "<< machbemerkung(lg)<<endl;
      } // if (TxBp->TCp[Txi][lg])
    } // if (Txi!=-1)
  } // if (TxBp)
} // hilfezeile

/*
linsten linstcl::checkinst(int obverb, int oblog) 
{
  if (inst==uinst) {
    if (!systemrueck("which zypper 2>/dev/null",obverb,oblog)) {
      // heruntergeladene Dateien behalten
      inst=zyp;
    } else if (!systemrueck("which apt-get 2>/dev/null",obverb,oblog)) {
      // hier werden die Dateien vorgabemaessig behalten
      inst=apt;
    } else {
      inst=unent;
      cerr<<Txk[T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden]<<endl;
    }
  }
  return inst;
} // linsten linstcl::checkinst(int obverb, int oblog) 
*/


string linst_cl::ersetzeprog(const string& prog) 
{
  switch(linst.pruefipr()) {
    case apt:
      if (prog=="mariadb") return "mariadb-server";
      if (prog=="hylafax") return "hylafax-server";
      if (prog=="hylafax+") return "hylafax+-server";
      if (prog=="hylafax hylafax-client") return "hylafax-server hylafax-client";
      if (prog=="hylafax+ hylafax+-client") return "hylafax+-server hylafax+-client";
      if (prog=="kernel-source") return "linux-source";
      if (prog=="tiff") return "libtiff-tools";
      if (prog=="libxslt-tools") return "xsltproc";
      if (prog=="imagemagick") return "imagemagick imagemagick-doc";
      if (prog=="libreoffice-base") return "libreoffice-common libreoffice-base";
      if (prog=="libcapi20-2") return "libcapi20-dev";
      if (prog=="python-devel") return "python-dev";
      if (prog=="python3-devel") return "python3-dev";
      if (prog=="tesseract-ocr-traineddata-english") return "tesseract-ocr-eng";
      if (prog=="tesseract-ocr-traineddata-german") return "tesseract-ocr-deu";
      if (prog=="tesseract-ocr-traineddata-orientation_and_script_detection") return "tesseract-ocr-osd";
      if (prog=="libavformat-devel") return "libavformat-dev";
      if (prog=="poppler-tools") return "poppler-utils";
			if (prog=="libffi-devel") return "libffi-dev";
			if (prog=="boost-devel") return "libboost-dev";
      break;
    case dnf: case yum:
      if (prog=="mariadb") return "mariadb-server";
      if (prog=="kernel-source") return "kernel-devel-$(uname -r)";
      if (prog=="tiff") return "libtiff-tools";
      if (prog=="libcapi20-2") return "isdn4k-utils";
      if (prog=="libcapi20-3") return "";
//      if (prog=="python-devel") return "python3-devel"; // bei capisuite_copy falsch; dann bei ocrmypdf fuer apt noch zu pruefen
      if (prog=="capiutils") return "";
      if (prog=="imagemagick") return "ImageMagick ImageMagick-doc";
      if (prog=="libxslt-tools") return "libxslt";
      if (prog=="libreoffice-base") return "libreoffice-filters libreoffice-langpack-de";
      if (prog=="tesseract-ocr") return "tesseract";
      if (prog=="tesseract-ocr-traineddata-english") return "";
      if (prog=="tesseract-ocr-traineddata-german") return "tesseract-langpack-deu tesseract-langpack-deu_frak";
      if (prog=="tesseract-ocr-traineddata-orientation_and_script_detection") return "tesseract-osd";
      if (prog=="poppler-tools") return "poppler-utils";
      break;
	  case zypper:
		  if (prog=="redhat-rpm-config") return "";
			if (prog=="libffi-devel") return "libffi$(gcc --version|head -n1|sed \"s/.*) \\(.\\).\\(.\\).*/\\1\\2/\")-devel";
    default: break;
  } //   switch(linst.pruefipr())
  return prog;
} // string linst_cl::ersetzeprog(const string& prog) 

// Problem: bei obyes erscheint die Rueckfrage dem Benutzer nicht, statt dessen wartet das Programm
int linst_cl::doinst(const string& prog,int obverb/*=0*/,int oblog/*=0*/,const string& fallsnichtda/*=nix*/) // ,uchar obyes/*=1*/)
{
  // <<rot<<"doinst 1: "<<violett<<prog<<schwarz<<" obverb: "<<(int)obverb<<endl;
  int ret=2;
  // eprog kann auch von aussen vor Programmaufruf gesetzt werden
  if (eprog.empty()) eprog=ersetzeprog(prog);
  if (!fallsnichtda.empty()) {
    //    if (!systemrueck((alsroot?string("root "):string(""))+"which '"+fallsnichtda+"' >/dev/null 2>&1",obverb,oblog)) 
    if (obprogda(fallsnichtda,obverb,oblog)) {
      eprog.clear();
      return 0;
    } //     if (obprogda(fallsnichtda,obverb,oblog))
  } // if (!fallsnichtda.empty()) 
//	int iru;
  if (!eprog.empty()) {
    switch (linst.pruefipr()) {
      case zypper:
        if (obnmr) {
          obnmr=0;
          systemrueck("sudo zypper mr -k -all",obverb,oblog);
        } //         if (obnmr)
      default: break;
    } // switch (linst.pruefipr()) 
		const uchar obyes=1;
		if (!(ret=systemrueck((obyes?instyp:instp)+eprog,obverb+1,oblog))) {
		  anfgggf(unindt,upr+eprog);
		} // 		if (!(ret=systemrueck((obyes?instyp:instp)+eprog,obverb+1,oblog)))
		//				for(iru=0;iru<2;iru++) KLA
		//					if ((ret=systemrueck("sudo apt-get -y install "+eprog,obverb+1,oblog))!=100) break;
		//					systemrueck("sudo dpkg --configure -a",obverb+1,oblog);
		//				KLZ
		eprog.clear();
	} // if (!eprog.empty()) 
	return ret;
} // uchar linst_cl::doinst(const string& prog,int obverb,int oblog) 

// fuege an, wenn noch nicht enthalten
void anfgggf(string datei, string inhalt)
{
	uchar obda=0;
	mdatei uni0(datei,ios::in,0);
	if (uni0.is_open()) {
		string zeile;
		while (getline(uni0,zeile)) {
			if (zeile.find(inhalt)!=string::npos) {
				obda=1;
				break;
			} // 						if (zeile.find(upr+eprog)!=string::npos)
		} // 					while (getline(uni0,zeile))
	} // 				if (uni0.is_open())
	if (!obda) {
		mdatei uniff(datei,ios::app,0);
		if (uniff.is_open()) {
			uniff<<inhalt<<endl; 
		} else {
			perror((string("\nLog: ")+Txk[T_Kann_Datei]+logdt+Txk[T_nicht_als_fstream_zum_Anhaengen_oeffnen]).c_str());
		} // 			if (uniff.is_open())
	} // 			if (!obda)
} // void anfgggf(string datei, string inhalt)

int linst_cl::doggfinst(const string& prog,int obverb,int oblog)
{
  if (!(eprog=ersetzeprog(prog)).empty()) {
    if (obfehlt(eprog,obverb,oblog)) {
      return doinst(prog,obverb,oblog);
    }
    eprog.clear();
  } // if (!(eprog=ersetzeprog(prog)).empty()) 
  return 0;
} // uchar linst_cl::doggfinst(const string& prog,int obverb,int oblog)

int linst_cl::douninst(const string& prog,int obverb/*=0*/,int oblog/*=0*/,uchar obyes/*=1*/) 
{
	int ret=2;
	if (eprog.empty()) eprog=ersetzeprog(prog);
	if (!eprog.empty()) {
		ret=systemrueck((obyes?uypr:upr)+prog,obverb,oblog);
		eprog.clear();
	}
	return ret;
} // uchar linst_cl::douninst(const string& prog,int obverb,int oblog) 


int linst_cl::obfehlt(const string& prog,int obverb,int oblog)
{
 // <<violett<<"linst::obfehlt: "<<schwarz<<prog<<endl;
  switch (linst.pruefipr()) {
    case zypper: case dnf: case yum: 
      return systemrueck("rpm -q "+prog+" 2>/dev/null",obverb,oblog);
    case apt:
      return systemrueck("dpkg -s "+ersetzeprog(prog)+" 2>/dev/null",obverb,oblog);
    default: break;
  }
  return 2;
} // uchar linst_cl::obfehlt(const string& prog,int obverb,int oblog)


string meinpfad() {
  char buff[PATH_MAX];
  buff[0]=0;
  ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
  }
  return string(buff);
} // meinpfad

string gethome()
{
 static string erg;
 if (erg.empty()) {
   erg=getenv("HOME");
   /*
   svec srueck;
   systemrueck("echo $HOME",0,0,&srueck);
   if (srueck.size()) {
     erg=srueck[0];
   }
   */
 } //  if (erg.empty())
 return erg;
} // string gethome()

servc::servc(const string& vsname,const string& vename,int obverb, int oblog): sname((vsname.empty()?vename:vsname)),ename(vename) 
{
  machfit(obverb,oblog);
} // servc::servc(const string& vsname,const string& vename,int obverb, int oblog): sname((vsname.empty()?vename:vsname)),ename(vename)

void servc::semodpruef(int obverb/*=0*/,int oblog/*=0*/)
{
  static uchar obse=2;
	Log(violetts+Txk[T_semodpruef]+schwarz+sname,obverb,oblog);
	string sepfad;
	if (obprogda("sestatus",obverb,oblog,&sepfad)) {
		if (obse==2) {
			obse=0;
			svec sr2;
			systemrueck("sestatus",obverb,oblog,&sr2);
			for(size_t j=0;j<sr2.size();j++) {
				if (!sr2[j].find("Current mode:"))
					if (sr2[j].find("enforcing")!=string::npos) {
						obse=1; 
						break;
					} // 				if (sr2[j].find("enforcing")!=string::npos)
			} //       for(size_t j=0;j<sr2.size();j++)
		}
		if (obse) {
			linst.doinst("policycoreutils-python-utils",obverb+1,oblog,"audit2allow");
			systemrueck("sudo setenforce 0",obverb,oblog);
			restart(obverb,oblog);
			const string selocal=sname+"_selocal";
			systemrueck("sudo grep \""+ename+"\" /var/log/audit/audit.log | audit2allow -M "+selocal,obverb,oblog);
			systemrueck("sudo setenforce 1",obverb,oblog);
			struct stat sstat={0};
			const string mod=instvz+vtz+selocal+".pp";
			if (!lstat(mod.c_str(),&sstat)) {
				linst.doinst("policycoreutils",obverb+1,oblog,"semodule");
				systemrueck("sudo semodule -i \""+mod+"\"",obverb,oblog);
				anfgggf(unindt,"sudo semodule -r \""+mod+"\"");
			} // 					if (!lstat((instvz+vtz+selocal+".pp").c_str(),&sstat)
		}  // if (obse)
	} // 			if (obprogda("sestatus",obverb,oblog,&sepfad))
} // int servc::sepruef(int obverb,int oblog)


void servc::semanpruef(int obverb/*=0*/,int oblog/*=0*/,const string& mod/*="getty_t*/)
{
	string sepfad;
	if (ename.find("faxgetty")!=string::npos) {
		if (obprogda("sestatus",obverb,oblog,&sepfad)) {
			systemrueck("sudo semodule -l|grep permissive_"+mod+" >/dev/null||sudo semanage permissive -a "+mod,obverb,oblog);
			anfgggf(unindt,"sudo semanage permissive -d "+mod);
		} // 	if (obprogda("sestatus",obverb,oblog,&sepfad))
	} // 		if (ename.find("faxgetty")!=string::npos)
} // int servc::semanpruef(const string& mod/*="getty_t*/, int obverb/*=0*/,int oblog/*=0*/)

int servc::machfit(int obverb/*=0*/,int oblog/*=0*/, binaer nureinmal/*=falsch*/)
{
	Log(violetts+Txk[T_machfit]+schwarz+" sname: "+violett+sname+schwarz+" svfeh: "+blau+ltoan(svfeh)+schwarz, obverb,oblog);
	// ueberpruefen, ob in systemctl status service Datei nach ExecStart existiert
	for(int iru=0;iru<2;iru++) {
	  caus<<violett<<"machfit "<<blau<<sname<<violett<<", iru: "<<gruen<<iru<<schwarz<<endl;
		if (!obsvfeh(obverb,oblog)) {
			break;
		} else {
			restart(obverb,oblog);
			if (!svfeh) break;
		}
		if (!iru && svfeh>5) {
		  caus<<"machfit, svfeh: "<<gruen<<svfeh<<schwarz<<endl;
//			exit(108);
			//      svec sr1;
			//      systemrueck("journalctl -xen 1 \"$(systemctl show '"+sname+"' | awk -F'={ path=| ;' '/ExecStart=/{print $2}')\" | tail -n 1",2,0,&sr1);
			//      if (sr1.size()) KLA
			//       if (sr1[0].find("permission")!=string::npos) KLA
//			semodpruef(obverb,oblog);
		} // 		if (!iru && svfeh>5)
	} // for(int iru=0;iru<2;iru++) 
	//  if (servicelaeuft)
	if (!svfeh&&!obenabled)
		enableggf(obverb,oblog);
	return !svfeh;
} // int servc::machfit(int obverb,int oblog)

// wird aufgerufen in: hservice_faxq_hfaxd, hservice_faxgetty
uchar servc::spruef(const string& sbez, uchar obfork, const string& parent, const string& sexec, const string& CondPath, const string& After, 
                    int obverb/*=0*/,int oblog/*=0*/, uchar mitstarten/*=1*/)
{
	Log(violetts+Txk[T_spruef_sname]+schwarz+sname,obverb,oblog);
	if (!obsvfeh(obverb-1,oblog)) {
		Log(("Service ")+blaus+sname+schwarz+Txk[T_lief_schon],obverb,oblog);
	} else {
		/*
			 char pBuf[300];
			 int bytes = MIN(readlink("/bin/systemd", pBuf, sizeof pBuf), sizeof pBuf - 1);
			 if(bytes >= 1) pBuf[bytes-1] = 0; // ../system statt /systemd
			 systemd=string(pBuf)+"/"+sname+".service";
		 */
		systemd="/etc/systemd/system/"+sname+".service";
		for(uchar iru=0;iru<2;iru++) {
			if (mitstarten && svfeh>5)
				restart(obverb,oblog); // svfeh wird hier auch gesetzt
			if (!svfeh) {
				Log(("Service ")+blaus+sname+schwarz+Txk[T_laeuft_jetzt],obverb,oblog);
				break;
			} // 			if (!svfeh)
			//          <<dblau<<"svfeh else: "<<schwarz<<sname<<endl;
			//  if (systemrueck("systemctl list-units faxq.service --no-legend | grep 'active running'",obverb-1,oblog)) KLA
			// string systemd="/usr/lib/systemd/system/"+sname+".service"; // au�erhalb Opensuse: /lib/systemd/system/ ...
			Log(blaus+systemd+Txk[T_nicht_gefunden_versuche_ihn_einzurichten]+schwarz,1,0);
			mdatei syst(systemd,ios::out);
			if (syst.is_open()) {
				syst<<"[Unit]"<<endl;
				char buf[80];
				time_t jetzt = time(0);
				struct tm *tmp = localtime(&jetzt);
				strftime(buf, sizeof(buf), "%d.%m.%y %H:%M:%S", tmp);
				syst<<"Description="<<sbez<<Txk[T_als_Dienst_eingerichtet_von]<<parent<<Txk[T_am]<<buf<<endl;
				if (!CondPath.empty()) 
					syst<<"ConditionPathExists="<<CondPath<<endl;
				if (!After.empty())
					syst<<"After="<<After<<endl;
				syst<<endl;
				syst<<"[Service]"<<endl;
				if (obfork) 
					syst<<"Type=forking"<<endl;
				syst<<"User=root"<<endl;
				syst<<"Group=root"<<endl;
				syst<<"Restart=always"<<endl;
				syst<<"RestartSec=30"<<endl;
				// if (!spre.empty()) syst<<"ExecStartPre=source "<<spre<<endl;
				syst<<"ExecStart="<<sexec<<endl;
				syst<<endl;
				syst<<"[Install]"<<endl;
				syst<<"WantedBy=multi-user.target "<<endl;
				syst.close();
				systemrueck("sudo systemctl daemon-reload",obverb-1,oblog);
				anfgggf(unindt,"N="+sname+";C=\"sudo systemctl\";$C stop $N;$C disable $N;rm -r '"+systemd+"';$C daemon-relaod;$C reset-failed;");
				syst.close();
				restart(obverb-1,oblog);
				obsvfeh(obverb-1,oblog);
				semodpruef(obverb,oblog);
				semanpruef(obverb,oblog);
			} // if (syst.is_open()) 
		} // if (!svgibts || !obslaeuft(obverb,oblog)) 
	} // if (servicelaeuft) else
	if (!svfeh&&!obenabled) { 
		enableggf(obverb,oblog);
	} // 	if (!svfeh&&!obenabled)
	return !svfeh;
} // void servc::spruef() 

int servc::obsvfeh(int obverb/*=0*/,int oblog/*=0*/) // ob service einrichtungs fehler
	// svfeh=1: Dienst inexistent, 2: Dienst 'disabled' 3: Dienstdatei nicht ermittelbar, 4: Dienst laeuft noch, aber Dienstdatei inexistent
	// svfeh=5: Exe-Datei nicht ermittelbar, 6: Exe-Datei fehlt, 7: activating 8: Dienst kann gestartet werden, 9: Sonstiges
{
	Log(violetts+Txk[T_obsfveh]+schwarz+" sname: "+violett+sname+schwarz,obverb,oblog);
	string sdatei;
	fehler=0;
	svfeh=-1;
	obenabled=1;
	for(int iru=0;iru<2;iru++) {
		svec statrueck;
		systemrueck("systemctl -n 0 status '"+sname+"'",obverb,oblog,&statrueck,1);
		for(size_t j=0;j<statrueck.size();j++) {
			const string *sp=&statrueck[j];
			if (sp->find("Loaded:")!=string::npos) {
				size_t p2=string::npos,p1=sp->find("("); if (p1!=string::npos) p2=sp->find(";",p1);
				if (p2!=string::npos) {
					sdatei=sp->substr(p1+1,p2-p1-1);
					if (systemd.empty()) systemd=sdatei;
				}
				if (sp->find("disabled")!=string::npos) {
					// svfeh=2; // stoert bei if (!svfeh) enableggf(
					obenabled=0;
				} else if (sp->find("not-found")!=string::npos) {
					svfeh=1;
				}
			} else if (sp->find("active (running)")!=string::npos) {
				svfeh=0;
				break;
			} else if (sp->find("activating")!=string::npos) {
			  svfeh=7;
			 // z.B.: Process: 10126 ExecStartPre=/usr/share/samba/update-apparmor-samba-profile (code=exited, status=0/SUCCESS)
			} else if (svfeh && sp->find("code=exited")!=string::npos) {
				// z.B. Exe-Datei bricht ab
				// z.B.: 'Main PID: 17031 (code=exited, status=255)'
				// oder:
				//   Loaded: loaded (/etc/systemd/system/aout.service; disabled; vendor preset: disabled)
			  //   Active: activating (auto-restart) (Result: exit-code) since Thu 2017-02-16 15:08:33 CET; 1s ago
				//  Process: 24594 ExecStart=/root/a.aout (code=exited, status=203/EXEC)
			  // Main PID: 24594 (code=exited, status=203/EXEC)
				// 11.9.16: dann muss evtl. selinux angepasst werden
				size_t gpos=sp->rfind('=');
				if (gpos<sp->length()-1)
					fehler=atol(sp->substr(gpos+1).c_str());
				else 
					fehler=1;
			} // if (sp->find("exited")!=string::npos) 
		} //  									for(size_t j=0;j<statrueck.size();j++)
		if (svfeh==7&&!fehler) { // 16.2.17: nur noch bei activating ohne exited
			// Dienst existent, Dienstdatei bekannt und existent, Exe-Datei bekannt und existent, Dienst laeuft aber nicht
			perfcl prf(Txk[T_Aktiviere_Dienst]+sname);
			while (!prf.oberreicht(3)) {}
			if (obverb) prf.ausgeb();
		} else {
			break;
		} // 									if (!fehler)
	} // 	for(int iru=0;iru<2;iru++)
	if (svfeh) {
		if (sdatei.empty()) {
			svfeh=3; // Dienstdatei nicht ermittelbar
		} else {
			// Dienst existent, Dienstdatei bekannt
			struct stat svst={0};
			if ((svfeh=lstat(systemd.c_str(),&svst))) { 
				svfeh=4; // // Dienst laeuft evtl. noch, aber Dienstdatei inexistent
			} else {
				// Dienst existent, Dienstdatei bekannt und existent
				svec srueExe;
				systemrueck("sudo cat '"+systemd+"'|grep ExecStart=|cut -d= -f2|cut -d' ' -f1",obverb,oblog,&srueExe);
				if (!srueExe.size()) {
					svfeh=5; // Exec-Datei nicht ermittelbar
				} else {
					if (ename.empty()) ename=base_name(srueExe[0]); // stimmt z.B. nicht bei /usr/lib/mysql/mysql-systemd-helper
					// Dienst existent, Dienstdatei bekannt und existent, Exe-Datei bekannt
					struct stat lst={0};
					if (lstat(srueExe[0].c_str(),&lst)) {
						svfeh=6; // Exec-Datei fehlt, hier auch: activating
					} else {// 				if (lstat(srueExe.c_str(),&lst))
					  svfeh=8; // Sonstiges
					} // 						if (lstat(srueExe[0].c_str(),&lst)) else
				} // 			if (!srueExe.size()) else
			} // 			if ((svfeh=lstat(systemd.c_str(),&svst))) 
		} // if (sdatei.empty()) else
	} // if (svfeh)
	/*
		 svec srueck;
		 systemrueck("systemctl list-unit-files|grep "+sname+".service",obverb,oblog,&srueck);  // 
		 if (!srueck.size()) KLA
		 svfeh=1; // Dienst inexistent
		 KLZ else KLA
		 if (!(obenabled=(srueck[0].find("enabled")!=string::npos))) KLA
		 svfeh=2; // Dienst 'disabled'
		 KLZ
		 if (systemd.empty()) KLA
		 svec srue3;
		 systemrueck("systemctl -n 0 status '"+sname+"' 2>/dev/null|grep Loaded:|cut -d'(' -f2|cut -d';' -f1",obverb,oblog,&srue3);
		 if (srue3.size()) systemd=srue3[0]; // z.B. /etc/systemd/system/abc.service
		 KLZ // 					if (systemd.empty())
		 if (systemd.empty()) KLA
		 svfeh=3; // Dienstdatei systemd nicht ermittelbar
		 KLZ else KLA
	// Dienst existent, Dienstdatei bekannt
	struct stat svst=KLA0KLZ;
	if ((svfeh=lstat(systemd.c_str(),&svst))) KLA 
	svfeh=4; // // Dienst laeuft noch, aber Dienstdatei inexistent
	KLZ else KLA
	// Dienst existent, Dienstdatei bekannt und existent
	svec srueExe;
	systemrueck("systemctl -n 0 status '"+sname+"'|grep ExecStart=|cut -d= -f2|cut -d' ' -f1",obverb,oblog,&srueExe);
	if (!srueExe.size())
	systemrueck("sudo cat '"+systemd+"'|grep ExecStart=|cut -d= -f2|cut -d' ' -f1",obverb,oblog,&srueExe);
	if (!srueExe.size()) KLA
	svfeh=5; // Exec-Datei nicht ermittelbar
	KLZ else KLA
	if (ename.empty()) ename=base_name(srueExe[0]); // stimmt z.B. nicht bei /usr/lib/mysql/mysql-systemd-helper
	// Dienst existent, Dienstdatei bekannt und existent, Exe-Datei bekannt
	struct stat lst=KLA0KLZ;
	if (lstat(srueExe[0].c_str(),&lst)) KLA
	svfeh=6; // Exec-Datei fehlt, hier auch: activating
	KLZ else KLA// 				if (lstat(srueExe.c_str(),&lst))
	KLZ // 						if (lstat(srueExe[0].c_str(),&lst)) else
	KLZ // 			if (!srueExe.size()) else
	KLZ // if ((svfeh=lstat(systemd.c_str(),&svst)))  else
	KLZ // 			if (systemd.empty()) else
	 */

	/* Folgendes wird vielleicht nicht benoetigt, da es bei disabled eh nicht angezeigt wird
		 srueck.clear;
		 systemrueck("systemctl -a --no-legend list-units '"+sname+".service'",obverb,oblog,&srueck);  // bei list-units return value immer 0
		 if (!srueck.empty()) KLA // svfeh=1 => Dienst inexistent
	// Dienst existent
	if (srueck[0].find(sname+".service loaded active running")==string::npos) KLA // sonst: svfeh=0
	// Dienst existent, Dienst laeuft aber nicht
	if (srueck[0].find(sname+".service loaded inactive")==string::npos) KLA
	if (srueck[0].find(sname+".service loaded activating")==string::npos) KLA
	svfeh=8; // loaded failed = Dienst kann evtl. gestartet werden
	KLZ else KLA
	KLZ // 								if (srueck[0].find(sname+".service loaded activating")==string::npos) else
	KLZ // 							if (srueck[0].find(sname+".service loaded inactive")==string::npos)
	KLZ // 	if (!(svfeh=srueck.empty())) 
	KLZ // 		if (!(obenabled=(srueck[0].find("enabled")!=string::npos))) else
	 */
	const int sfeh[]={ T_Dienst_laeuft,T_Dienst_inexistent, T_Dienst_disabled, T_Dienstdateiname_nicht_ermittelbar, T_Dienst_laeuft_noch_aber_Dienstdatei_inexistent, T_Exec_Dateiname_nicht_ermittelbar, T_Exec_Datei_fehlt, T_activating, T_Dienst_kann_gestartet_werden, T_Sonstiges};
	if (sname!="hylafax") { 
		Log(Txk[T_Ergebnis_Dienst]+blaus+sname+schwarz+": "+gruen+Txk[sfeh[svfeh]]+schwarz,svfeh,oblog);
	} // 	if (sname!="hylafax")
	Log(violetts+"Ende "+Txk[T_obsfveh]+schwarz+" sname: "+violett+sname+schwarz,obverb,oblog);
	return svfeh;
} // int servc::obsvfeh(int obverb,int oblog)

/*
// wird aufgerufen in: pruefhyla, pruefcapi, spruef
int servc::obslaeuft(int obverb,int oblog, binaer nureinmal)
{
//  Log(violetts+Txk[T_obslaeuft]+schwarz+" sname: "+violett+sname+schwarz,obverb,oblog);
perfcl prf(Txk[T_Aktiviere_Dienst]+sname);
size_t runde=0;
while (1) {
runde++;
obsvfeh(obverb,oblog);
if (svfeh=!1) {
Log(blau+srueck[0]+schwarz,obverb>1?obverb-1:0,oblog);
if (!svfeh) {
break;
} else if (srueck[0].find("activating")!=string::npos) {
svfeh=6;
}
if (fehler) break;
if (nureinmal || prf.oberreicht(3)) {
break;
}
prf.ausgeb();
} else if (srueck[0].find("loaded")!=string::npos) {
break;
} else {
break;
} //       if (srueck[0].find("active running")!=string::npos) else else else else
} else { // if (!srueck.empty()) 
break;
} //     if (!srueck.empty())  else 
} // while (1)
if (svfeh) {
vector<errmsgcl> errv;
const string froh=schwarzs+Txk[T_Dienst]+blau+sname+schwarz;
const string f0=froh+Txk[T_geladen];
const string f1=froh+Txk[T_nicht_geladen];
errv.push_back(errmsgcl(0,f0));
errv.push_back(errmsgcl(1,f1));
svfeh=systemrueck("systemctl -n 0 status '"+sname+"'| grep ' loaded '",obverb,oblog,0,falsch,wahr,"",&errv);
} //   if (svfeh)
return !svfeh;
} // int servc::obslaeuft(int obverb,int oblog)
 */

void servc::pkill(int obverb/*=0*/,int oblog/*=0*/)
{
    systemrueck(("sudo pkill '")+ename+"'",obverb-1,oblog,0,1);
}

int servc::restart(int obverb/*=0*/,int oblog/*=0*/)
{
  for(int i=0;i<2;i++) {
    systemrueck(string("sudo systemctl daemon-reload; sudo systemctl restart '")+sname+"'",obverb,oblog,0,2);
	  caus<<violett<<"restart, i: "<<gruen<<i<<schwarz<<" sname: "<<sname<<endl;
    if (!obsvfeh(obverb,oblog)) break;
    if (i) break;
    pkill(obverb,oblog);
  } //   for(int i=0;i<2;i++)
  return !svfeh;
} // int servc::restart(int obverb,int oblog)

void servc::start(int obverb/*=0*/,int oblog/*=0*/)
{
  systemrueck(string("sudo systemctl start '")+sname+"'",obverb,oblog,0,2);
} // int servc::start(int obverb,int oblog)

int servc::startundenable(int obverb/*=0*/,int oblog/*=0*/)
{
  start(obverb,oblog);
  enableggf(obverb,oblog);
	  caus<<violett<<"startundeable, sname: "<<schwarz<<sname<<endl;
  return !obsvfeh(obverb,oblog);
} // int servc::start(int obverb,int oblog)

void servc::stop(int obverb/*=0*/,int oblog/*=0*/,uchar mitpkill/*=0*/)
{
  systemrueck("sudo systemctl stop '"+sname+"'",obverb,oblog,0,2);
  if (mitpkill) {
    pkill(obverb,oblog);
  }
} // int servc::stop(int obverb,int oblog)

void servc::stopdis(int obverb/*=0*/,int oblog/*=0*/,uchar mitpkill)
{
    Log(violetts+string(Txk[T_stopdis_sname])+schwarz+sname,obverb,oblog);
	if (!obsvfeh(obverb,oblog)) {
		stop(obverb,oblog);
	} // 	if (!obsvfeh(obverb,oblog))
	if (svfeh!=1&&obenabled)
		systemrueck(string("sudo systemctl disable '")+sname+"'",obverb,oblog,0,2);
} // int servc::stop(int obverb,int oblog)

int servc::enableggf(int obverb/*=0*/,int oblog/*=0*/)
{
    Log(violetts+string(Txk[T_enableggf])+schwarz+sname,obverb,oblog);
    vector<errmsgcl> errv;
    const string froh=schwarzs+Txk[T_Dienst]+blau+sname+schwarz;
    const string f0=froh+Txk[T_ermoeglicht];
    const string f1=froh+Txk[T_nicht_ermoeglicht];
    errv.push_back(errmsgcl(0,f0));
    errv.push_back(errmsgcl(1,f1));
    errv.push_back(errmsgcl(6,f1));
 return systemrueck(string("systemctl is-enabled '")+sname+"' >/dev/null 2>&1 || sudo systemctl enable '"+sname+"'",obverb,oblog,0,2,wahr,"",&errv);
} // int servc::enableggf(int obverb,int oblog)


void servc::daemon_reload(int obverb/*=0*/, int oblog/*=0*/)
{
 systemrueck("sudo systemctl daemon-reload",obverb,oblog);
}

// Rueckgabe: Zahl der nicht Geloeschten
// wird aufgerufen in: loeschecapi, untersuchespool
int tuloeschen(const string& zuloe,const string& cuser, int obverb, int oblog)
{
//  Log(violetts+Tx[T_tuloeschen]+schwarz,obverb,oblog);
  struct stat entryzuloe={0};
  if (!lstat(zuloe.c_str(),&entryzuloe)) {
    Log(string(Txk[T_Loesche_Ausrufezeichen])+gruen+zuloe+schwarz,obverb,oblog);
    int erg=-1;
    for(uchar iru=1;iru<3;iru++) {
      if ((erg=remove(zuloe.c_str()))) {
        if(cuser.empty()) iru++;
        if(iru==1) {
          setfaclggf(zuloe, falsch, 6, falsch,obverb,oblog,0);
        } else {
          if (errno) if (errno!=13) perror((string(Txk[T_Fehler_beim_Loeschen])+" "+ltoan(errno)).c_str()); // Permission denied
          const string cmd=string("sudo rm -rf \"")+zuloe+"\"";
          erg=systemrueck(cmd,obverb+1,1);
        } // if(iru) else
      } else {
        erg=0;
        break;
      } //       if ((erg=remove(zuloe.c_str())))
    } // for(uchar iru=1;iru>-1;iru--)
    return erg;
  } // if (!lstat(zuloe.c_str(),&entryzuloe)) 
  Log(rot+zuloe+schwarz+Txk[T_nicht_geloescht_war_eh_nicht_mehr_da],obverb,oblog);
  return 0;
} // int tuloeschen(string zuloe,int obverb, int oblog)

// in optioncl::optioncl
void optioncl::setzebem(schlArr *cp,const char *pname)
{
  if (cp && pname) {
    svec bems;
    for(int akts=0;akts<Smax;akts++) bems<<machbemerkung((Sprache)akts,falsch);
    cp->setzbemv(pname,&Txk,0,0,&bems);
  }
} // void optioncl::setzebem(TxB *TxBp,schlArr *cp,const char *pname)

/*2*/optioncl::optioncl(string kurz, string lang, TxB *TxBp, long Txi, string *zptr, par_t art,schlArr *cp, const char *pname,uchar* obschreibp) : 
  kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), zptr(zptr), art(art),cp(cp),pname(pname),obschreibp(obschreibp) 
{
  setzebem(cp,pname);
}

/*3*/optioncl::optioncl(string kurz, string lang, TxB *TxBp, long Txi, const string *rottxt, long Txi2, string *zptr, par_t art,schlArr *cp, 
    const char *pname,uchar* obschreibp) : 
  kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), rottxt(rottxt), Txi2(Txi2), zptr(zptr), art(art),
  cp(cp),pname(pname),obschreibp(obschreibp) 
{
  setzebem(cp,pname);
}

/*4*/optioncl::optioncl(string kurz, string lang, TxB *TxBp, long Txi, uchar *pptr, int wert,schlArr *cp, const char *pname,uchar* obschreibp) :
  kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), pptr(pptr), wert(wert),cp(cp),pname(pname),obschreibp(obschreibp),obno(obschreibp?1:0)
{
  setzebem(cp,pname);
}

// gleicht das Datum von <zu> an <gemaess> an, aehnlich touch
int attrangleich(const string& zu, const string& gemaess,int obverb, int oblog)
{
  struct stat statgm={0};
  if (lstat(gemaess.c_str(),&statgm)) {
    Log(string(rots+Txk[T_Fehler_bei_lstat])+schwarz+gemaess,obverb,oblog);
    return 1;
  }
  struct stat statzu={0};
  if (lstat(zu.c_str(),&statzu)) {
    Log(string(rots+Txk[T_Fehler_bei_lstat])+schwarz+zu,obverb,oblog);
    return 1;
  }
  if (chmod(zu.c_str(),statgm.st_mode)) {
   systemrueck("sudo chmod --reference=\""+gemaess+"\" \""+zu+"\"",obverb,oblog);
  }
  if (chown(zu.c_str(),statgm.st_uid,statgm.st_gid)) {
   systemrueck("sudo chown --reference=\""+gemaess+"\" \""+zu+"\"",obverb,oblog);
  }
  struct utimbuf ubuf={0};
  ubuf.actime=ubuf.modtime=statgm.st_mtime;
  if (utime(zu.c_str(),&ubuf)) {
   systemrueck("sudo touch -r \""+gemaess+"\" \""+zu+"\"",obverb,oblog);
  }
  lstat(zu.c_str(),&statzu);
  if (memcmp(&statgm.st_mtime, &statzu.st_mtime,sizeof statzu.st_mtime)) {
    Log(rots+Txk[T_Datum_nicht_gesetzt_bei]+schwarz+zu+rot+"'"+schwarz,1,1);
    //          exit(0);
  }
  return 0;
} // int attrangleich(string& zu, string& gemaess,int obverb, int oblog)

// liefert 0, wenn Erfolg
int kopier(const string& quel, const string& ziel, int obverb, int oblog)
{
  int erg=-1;
  int fehler=1;
  int source=open(quel.c_str(),O_RDONLY,0);
  if (source==-1) {
//    Log(Txk[T_Konnte_Datei]+rots+quel+schwarz+Txk[T_nicht_zum_Lesen_oeffnen],obverb,oblog);
  } else {
    struct stat statq={0};
    if (!fstat(source,&statq)) {
      int dest=open(ziel.c_str(),O_WRONLY|O_CREAT,statq.st_mode);
      if (dest==-1) {
        fehler=2;
//        Log(Txk[T_Konnte_Datei]+rots+ziel+schwarz+Txk[T_nicht_zum_Schreiben_oeffnen],obverb,oblog);
      } else {
        erg=sendfile64(dest,source,0,statq.st_size);
        close(dest);
        if (erg==-1) {
          fehler=3;
        } else {
          fehler=0;
          chmod(ziel.c_str(),statq.st_mode);
          chown(ziel.c_str(),statq.st_uid,statq.st_gid);
          struct utimbuf ubuf={0};
          ubuf.actime=ubuf.modtime=statq.st_mtime;
          utime(ziel.c_str(),&ubuf);
        } // if (erg==-1)
      } // if (dest==-1) else 
      close(source);
    } // if (!fstat(source,&statq)) 
  } // if (source==-1) else 
  if (fehler)
    return systemrueck("sudo test -f \""+quel+"\" && sudo sh -c 'cp -a \""+quel+"\" \""+ziel+"\"'",obverb,oblog);
  return 0;
} // int kopier(string& quel, string& ziel, int obverb, int oblog)
