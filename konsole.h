#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef KONSOLE_H_DRIN
#define KONSOLE_H_DRIN
#ifdef _WIN32
#include <winsock2.h> // entfaellt bei mysql
#include <io.h> // fuer isatty und _isatty
#endif

#include <iostream>
//#define obfstream
#ifdef obfstream
#include <fstream> // fstream
#endif  

#ifdef _MSC_VER
#include <string>
#endif

#ifdef linux
#define vtz '/' // Verzeichnistrennzeichen
#define vtzs "/" // Verzeichnistrennzeichenstring
#elif __MINGW32__ || _MSC_VER
#define vtz '\\' // Verzeichnistrennzeichen
#define vtzs "\\" // Verzeichnistrennzeichen
#endif

#ifndef vector_incl
#include <vector>
#define vector_incl
#endif

using namespace std;
int Log(const string& text,short screen=1,short file=1,bool oberr=0,short klobverb=0);

#ifdef _MSC_VER
#define fileno _fileno // sonst Warnung posix deprecated
#define isatty _isatty // sonst Warnung posix deprecated
#endif

#ifdef __MINGW32__
#undef PATH_MAX
#endif

#ifdef _WIN32
#define PATH_MAX MAX_PATH
// #include <limits.h>
#include <time.h> // fuer mktime und time in kuerzelogdatei
#define lstat stat

#elif linux
#include <string.h> // strcpy, strtok_r, strerror, memcmp, strcmp, strstr, 
#include <errno.h> // errno, ENOENT
#include <pwd.h>   // getuid, getpwuid
#include <sys/param.h>  // MAXHOSTNAMELEN
#include <sys/ioctl.h> // winsize, TIOCGWINST, w, ioctl
#include <stdlib.h>
#include <dirent.h> // DIR, dirHandle, opendir, readdir, PATH_MAX
#include <unistd.h>
#endif

#ifndef _MSC_VER
#include <stdio.h> // fuer fopen, perror, fgets, sscanf, fputs, fclose, stdout, fileno, stderr
#else
#define snprintf _snprintf
#endif

#include <sys/stat.h> // stat, lstat, S_IFMT, S_IFDIR ...
// #include <boost/algorithm/string.hpp> // clock, numeric_limits
#include <time.h>
#include <limits>

typedef unsigned char uchar;
enum binaer:uchar {falsch,wahr};
enum Sprache {deutsch,englisch,Smax};
extern const char *dir;
//extern const string datei;
// extern const char *rot, *weinrot, *schwarz, *blau, *gelb; // muss spaeter kompilerunabhaengig
extern const char *schwarz, *dgrau, *drot, *rot, *gruen, *hgruen, *braun, *gelb, *blau, *dblau, *violett, *hviolett,
       *tuerkis, *htuerkis, *hgrau, *weiss, *umgek;
extern const string drots,rots,schwarzs,blaus,gelbs,tuerkiss,hgraus,violetts,gruens;
#ifdef linux
extern const char *_rot, *_hrot, *_schwarz, *_blau, *_gelb, *_tuerkis, *_hgrau;
#endif
#include <fstream> // kopiere
#include <algorithm>    // std::transform

extern string nix;
// typedef const char *TCtp[][Smax];
typedef const char * const * const TCtp[Smax];
class TxB // Text-Basisklasse
{
 public:
  Sprache lgn; // Sprache numerisch
//  TCtp* TCp;
  const char * const * const * const *TCp;
  inline const char* operator[](long const& nr) const {
    TCtp *hilf = reinterpret_cast<TCtp*>(TCp);
    return (const char*)hilf[nr][lgn];
  }
};

string meinpfad();

enum Tkonsole_ 
{
  T_pfad,
  T_kuerze_logdatei,
  T_Logdatei,
  T_gibt_es_noch_nicht_Kuerze_sie_daher_nicht,
  T_Kann_Datei,
  T_nicht_als_fstream_zum_Schreiben_oeffnen,
  T_nicht_als_fstream_zum_Lesen_oeffnen,
  T_nicht_mit_fopen_zum_Schreiben_oeffnen,
  T_nicht_mit_fopen_zum_Lesen_oeffnen,
  T_Variable_logdatei_leer,
  T_nicht_als_fstream_zum_Anhaengen_oeffnen,
  T_nicht_mit_fopen_zum_Anhaengen_oeffnen,
  T_Bitte_mit,
  T_beenden,
  T_stern_zeile,
  T_Rueckmeldung,
  T_Suchbefehl,
  T_Fuehre_aus,
  T_fehlgeschlagen_bei,
  T_Fuehrte_aus,
  T_komma_Ergebnis,
  T_kein_Verzeichnis_nochmal,
  T_nicht_gefunden_soll_ich_es_erstellen,
  T_Fehlender_Parameter_string_zu,
  T_oder,
  T_Fehler_Parameter,
  T_ohne_gueltigen,
  T_mit_Datei_als,
  T_mit_falschem,
  T_Pfad_angegeben,
  T_Nicht_numerischer,
  T_Fehlender,
  T_Parameter_nr_zu,
  T_Fehler,
  T_Erfolg,
  T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden,
  T_Logdateidpp,
  T_Lese_Konfiguration_aus,
  T_j_k,
  T_Fehler_bei_auswert,
  T_nicht_gefunden,
  T_Muss_Datei,
  T_fuer,
  T_zugreifbar_machen,
  T_spruef_sname,
  T_lief_schon,
  T_nicht_gefunden_versuche_ihn_einzurichten,
  T_Aktiviere_Dienst,
  T_Program,
  T_laeuft_schon_einmal_Breche_ab,
  T_Wert,
  T_Dauer,
  T_Dienst,
  T_geladen,
  T_nicht_geladen,
  T_am,
  T_als_Dienst_eingerichtet_von,
  T_Versuch,
  T_machfit,
  T_obslaeuft,
  T_konsoleMAX,
};

extern class Txkonsolecl Txk;

class Txkonsolecl : public TxB
{
  public:
    static const char *TextC[T_konsoleMAX+1][Smax];
    Txkonsolecl();
//    inline const char* operator[](Tkonsole_ const& nr) const { return TextC[nr][lgn]; }
};

extern uchar nrzf; // nicht rueckzufragen, fuer Aufruf aus Cron

class errmsgcl
{
public:
 int errnr;
 string msg;
 errmsgcl(int errnr,string& msg):errnr(errnr),msg(msg){}
};

// arg-Class
class argcl
{
 public:
 char* argcs;  // Zeiger auf einen Commandline-Parameter
 uchar agef=0; // gefunden
 argcl(int i,char** argv);
};

class perfcl
{
 public:
 string vonwo;
 clock_t zp0, zp1;
 time_t t0, t1;
 unsigned long nr=0;
 perfcl(const string& vvonwo);
 void ausgeb(const string& stelle="");
 void ausgab1000(const string& stelle="");
 int oberreicht(unsigned long sek);
};

char* curruser();

class mdatei: public fstream
{
  public:
  int oboffen=0;
  mdatei (const string& filename, ios_base::openmode mode = ios_base::in | ios_base::out, int obverb=0, int oblog=0);
};

inline string zustr(int _Val) {
  char _Buf[2 * sizeof(long long)];
  snprintf(_Buf,2*sizeof(long long), "%d", _Val);
  return string(_Buf);
}
inline std::string right(std::string const& source, size_t const length) {
  if (length >= source.size()) { return source; }
  return source.substr(source.size() - length);
} // tail}
inline std::string mitvtz(std::string const& vz) {
  if (right(vz,1)==string(1,vtz)) {
    return vz;
  } else {
    return vz+vtz;
  }
}
inline int istelnr(const std::string& str) {
  if	(str.find_first_not_of("+ 0123456789.,")==string::npos && str.find_first_not_of(" ")!=string::npos) 
    return 1;
  return 0;
}

inline int isnumeric(const std::string& str)
{
  if	(str.find_first_not_of(" 0123456789.,")==string::npos && str.find_first_not_of(" ")!=string::npos) 
    return 1;
  return 0;
}

inline int isneun(const std::string& str)
{
  if	(str.find_first_not_of(" 9")==string::npos && str.find_first_not_of(" ")!=string::npos) 
    return 1;
  return 0;
}

inline int isnumeric(char* str)
{
  while (*str) {
    if(!strchr(" 0123456789.,",*str)) return 0;
    str++;
  }
  return 1;
}

string* anfzweg(string& quel);

inline std::string *gtrim(std::string *str) {
  str->erase(0, str->find_first_not_of("\t "));       //prefixing spaces
  str->erase(str->find_last_not_of("\t ")+1);         //surfixing spaces
  return str;
}

inline std::string *ltrim(std::string *str) {
  str->erase(0, str->find_first_not_of("\t "));       //prefixing spaces
  return str;
}

inline void rtrim(char* str,size_t size) {
  for (int nd=0,i=size-1;i;i--) {
    if (!str[i]) nd=1; 
    else if (nd && str[i]!=32 && str[i]!=9) break;
    str[i]=0;
  }
}

string fersetze(const string& u, const char* alt, const char* neu);
string caseersetze(const string& u, const char* alt, const char* neu); 
string *loeschealleaus(string *u, const char* alt);

string ersetze(const char *const u, const char* const alt, const char* neu);
string *sersetze(string *src, string const& target, string const& repl);
// wstring ersetze(const wstring& u, const wchar_t* alt, const wchar_t* neu); 

string ersetzAllezu(string& quelle, const string& alt, const string& neu);
void ersetzAlle(string& quelle, const string& alt, const string& neu);
string ersetzAllezu(string *quelle, const char* alt, const char* neu);
string ersetzAllezu(const char *quelle, const char* alt, const char* neu);
void ersetzAlle(string *quelle, const char* alt, const char* neu);
void ersetzAlle(string *quelle, const string& alt, const string& neu);

char* charersetze(char *u, char alt, char neu);
void chersetze(const string& u, string *z, const string& alt, const char neu);
string ersetzefuerdatei(const string& u);
size_t zahlin(string *str, const char* was);
long cmpmem( char* feld, const char* search, int len_feld); // , int len_search
// fuer lies (Konfigurationsdatei lesen)
char* ltoan(long value, int base=10, uchar obtz=0, uchar minstel=0); 
char* ltoa_(long value, char* result, int base); 

class Schluessel {
  public:
    char key[90];
    char val[100];
    template <typename T> void hole(T *var) { *var=atol(val); }
    template <typename T> void setze(T *var) { strncpy(val,ltoan(*var),sizeof val-1);val[sizeof val-1]=0; }
};
template <> inline void Schluessel::hole < char* > (char** var) { *var = val; }
template <> inline void Schluessel::hole < const char* > (const char** var) { *var = val; }
template <> inline void Schluessel::hole < string > (string *var) { *var = val; }
template <> inline void Schluessel::hole < binaer > (binaer *var) { *var = (binaer)atoi(val); }
template <> inline void Schluessel::setze < char* > (char** var) { strncpy(val,*var,sizeof val-1);val[sizeof val-1]=0; }
template <> inline void Schluessel::setze < const char* > (const char** var) { strncpy(val,*var,sizeof val-1);val[sizeof val-1]=0; }
template <> inline void Schluessel::setze < string > (string *var) { strncpy(val,var->c_str(),sizeof val-1);val[sizeof val-1]=0;}

class cppSchluess {
  public:
    string name;
    uchar gelesen;
    string wert;
//    inline cppSchluess& operator=(cppSchluess zuzuw){name=zuzuw.name;wert=zuzuw.wert; return *this;} // wird nicht benoetigt
    template <typename T> void hole(T *var) { *var=atol(wert.c_str()); }
    template <typename T> void setze(T *var) { wert=ltoan(*var); }
};
template <> inline void cppSchluess::hole < char* > (char** var) {*var = (char*)wert.c_str(); }
template <> inline void cppSchluess::hole < const char* > (const char** var) {*var = wert.c_str(); }
template <> inline void cppSchluess::hole < string > (string *var) {*var = wert; }
template <> inline void cppSchluess::hole < binaer > (binaer *var) { *var = (binaer)atoi(wert.c_str()); }
template <> inline void cppSchluess::setze < char* > (char** var) {wert=*var; }
template <> inline void cppSchluess::setze < const char* > (const char** var) {wert=*var;}
template <> inline void cppSchluess::setze < string > (string *var) {wert=*var;}
template <> inline void cppSchluess::setze < const string > (const string *var) {wert=*var;}

class schlArr {
 public:
 cppSchluess *schl=0; 
 size_t zahl;
 schlArr();
 void neu(size_t vzahl=0);
 void init(size_t vzahl, ...);
 void init(vector<cppSchluess*> *sqlvp);
 inline /*const*/ cppSchluess& operator[](size_t const& nr) const { return schl[nr]; }
 int setze(const string& name, const string& wert);
 const string& hole(const string& name);
 void schreib(mdatei *f);
 int schreib(const string& fname);
 void ausgeb();
 void reset();
 ~schlArr();
};

class abSchl {
 public:
   string name;
   string wert;
   abSchl(string& vname, string& vwert):name(vname),wert(vwert) {}
};

// Linux-System-Enum
enum lsysen:uchar {usys,sus,deb,fed};
class lsyscl
{
  public:
    lsysen sys; 
    lsysen getsys(int obverb=0,int oblog=0);
};

// enum betrsys {keins,suse,ubuntu,fedora};
// betrsys pruefos();
string obprogda(string prog,int obverb, int oblog);
enum instprog {keinp,zypper,apt,dnf,yum};
instprog pruefipr(int obverb=0, int oblog=0);
string gethome();

#ifdef _MSC_VER
extern inline void wait();
#else
// #define wait();
#endif

#ifdef _WIN32
extern const char *drot, *rot, *schwarz, *blau, *gelb, *tuerkis, *hgrau;
extern const string drots, rots, schwarzs, blaus, gelbs, tuerkis, hgrau;
inline std::ostream& _drot(std::ostream &s){
  //    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
  return s;
}
inline std::ostream& _blau(std::ostream &s){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);
  return s;
}
inline std::ostream& _rot(std::ostream &s){
  //    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
  return s;
}
inline std::ostream& _schwarz(std::ostream &s){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
  return s;
}
inline std::ostream& _gelb(std::ostream &s){
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN);
  return s;
}
struct color {
  color(WORD attribute):m_color(attribute){};
  WORD m_color;
};

#endif
class svec: public vector<std::string> {
  public:
    inline svec& operator<<(const std::string& str) {
      this->push_back(str);
      return *this;
    }
};
//svec& operator<<(svec& v, const std::string& str);
template<class T>
class tsvec: public vector<T> {
  public:
    inline tsvec<T>& operator<<(const T& str) {
      this->push_back(str);
      ((T&)str).init();
      return *this;
    }
};

// Abschnitt einer Konfigurationsdatei
class absch {
 public:
 string aname;
 vector<abSchl> av;
 const string& suche(const char* const sname);
 const string& suche(const string& sname);
 void clear();
};

class confdat {
  public:
    uchar obgelesen=0;
    svec zn;
    string name;
    vector<absch> abschv;
    size_t richtige;
    confdat(const string& fname, int obverb);
    confdat(const string& fname, schlArr *sA, int obverb=0, char tz='=');
//    confdat(const string& fname,cppSchluess *conf, size_t csize, int obverb=0, char tz='=');
    int lies(const string& fname,int obverb);
    void auswert(schlArr *sA, int obverb=0, char tz='=');
//    void auswert(cppSchluess *conf, size_t csize, int obverb=0, char tz='=');
    void Abschn_auswert(int obverb=0, char tz='=');
};

// fuer Commandline-Optionen
enum par_t:uchar {psons,pverz,pfile,pzahl}; // Parameterart: Sonstiges, Verzeichnis, Zahl


class optioncl
{
  public:
    string kurz;
    string lang;
    TxB *TxBp=0;
    long Txi;
    string *rottxt=0; // ggf rot zu markierender Text zwischen Txi und Txi2
    long Txi2=-1;
//    string oerkl;
    uchar *pptr=0; // Zeiger auf Parameter, der hier eingestellt werden kann
    int wert; // Wert, der pptr zugewiesen wird, falls dieser Parameter gewaehlt wird
    string *zptr=0; // zusatzzeiger auf Parameter, der hier eingegeben werden kann
    par_t art; // Parameterart
    schlArr *cp=0; // Konfigurationsarray, das ggf. geschrieben werden muss
    const char *pname; // Name des Konfigurationsparameters
    uchar *obschreibp=0; // ob Konfiguration geschrieben werden muss
//    uchar ogefunden=0; // braucht man nicht, ist in argcl
    optioncl(string kurz, string lang, TxB *TxBp, long Txi) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, string *zptr, par_t art,schlArr *cp=0, const char *pname=0,uchar* obschreibp=0) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), zptr(zptr), art(art),cp(cp),pname(pname),obschreibp(obschreibp) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, string *rottxt, long Txi2, string *zptr, par_t art,schlArr *cp=0, 
             const char *pname=0,uchar* obschreibp=0) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), rottxt(rottxt), Txi2(Txi2), zptr(zptr), art(art),
               cp(cp),pname(pname),obschreibp(obschreibp)  {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, uchar *pptr, int wert,schlArr *cp=0, const char *pname=0,uchar* obschreibp=0) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), pptr(pptr), wert(wert),cp(cp),pname(pname),obschreibp(obschreibp) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, string *rottxt, long Txi2, uchar *pptr, int wert) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), rottxt(rottxt), Txi2(Txi2), pptr(pptr), wert(wert) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, const string *rottxt, long Txi2, uchar *pptr, int wert) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), rottxt((string*)rottxt), Txi2(Txi2), pptr(pptr), wert(wert) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, binaer *pptr, int wert) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), pptr((uchar*)pptr), wert(wert) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, int *pptr, int wert) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), pptr((uchar*)pptr), wert(wert) {}
    optioncl(string kurz, string lang, TxB *TxBp, long Txi, string *rottxt, long Txi2, int *pptr, int wert) : 
               kurz(kurz), lang(lang), TxBp(TxBp), Txi(Txi), rottxt(rottxt), Txi2(Txi2), pptr((uchar*)pptr), wert(wert) {}
    int pruefp(vector<argcl> *argcvm , size_t *akt, uchar *hilfe); // 1 = das war der Parameter, 0 = nicht
    void hilfezeile(Sprache lg);
};

#endif // KONSOLE_H_DRIN

extern const char *logdt;

int kuerzelogdatei(const char* logdatei,int obverb);
void kopiere(string *quelle, string *ziel);
void aufSplit(vector<string> *tokens, const string *text, char sep, bool nichtmehrfach=1);
void aufSplit(vector<string> *tokens, const char *text, char sep, bool nichtmehrfach=1);
void aufiSplit(vector<string> *tokens, const string *text, const char* sep,bool nichtmehrfach=1);
void aufSplit(vector<string> *tokens, const string *text, char* sep,bool nichtmehrfach=1);
void getstammext(string *ganz, string *stamm, string *exten);
// int cpplies(string fname,cppSchluess *conf,size_t csize,vector<string> *rest=0,char tz='=',short obverb=0);
string XOR(const string& value, const string& key);
int schreib(const char *fname, Schluessel *conf, size_t csize);
int cppschreib(const string& fname, cppSchluess *conf, size_t csize);
// int multicppschreib(const string& fname, cppSchluess **conf, size_t *csizes, size_t cszahl);
int multischlschreib(const string& fname, schlArr **confs, size_t cszahl);
std::string base_name(const std::string& path);
std::string dir_name(const std::string& path);
int systemrueck(const string& cmd, char obverb=0, int oblog=0, vector<string> *rueck=0, 
                binaer ob0heissterfolg=wahr, binaer obergebnisanzeig=wahr, const string& ueberschr="",vector<errmsgcl> *errm=0);
void pruefplatte();
void pruefmehrfach(string& wen=nix);
int setfaclggf(const string& datei, const binaer obunter=falsch, const int mod=4, binaer obimmer=falsch,int obverb=0,int oblog=0);
int pruefverz(const string& verz,int obverb=0,int oblog=0, uchar obmitfacl=1);
string aktprogverz();
char Tippbuchst(const string& frage, const string& moegl,const char *berkl[], const char* erlaubt=0, const char *vorgabe=0);
// vorgabe fur vorgabe = T_j_k; alternativ='n'
uchar Tippob(const string& frage,const char *vorgabe=Txk[T_j_k]);
string Tippstrings(const char *frage, char* moegl[], char *vorgabe=0); // das letzte Element von moegl muss 0 sein
string Tippstrings(const char *frage, vector<string> *moegl, string *vorgabe=0); 
string Tippzahl(const char *frage, const char *vorgabe=0);
string Tippzahl(const char *frage, string *vorgabe);
string Tippzahl(const string& frage, string *vorgabe);
string Tippstring(const char *frage, const string *vorgabe=0);
char* Tippcstring(const char *frage, char* buf, unsigned long buflen, const char* vorgabe="");
string Tippstring(const string& frage, const string *vorgabe=0);
string Tippverz(const char *frage,string *vorgabe=0);
uchar VerzeichnisGibts(const char* vname);

class linstcl
{
  public:
//    linsten inst;
    uchar obnmr=1;
    string eprog; // ersetztes Programm
    string ersetzeprog(const string& prog);
    uchar doinst(const string& prog,int obverb=0,int oblog=0,const string& fallsnichtda="", binaer alsroot=falsch);
    uchar doinst(const char* prog,int obverb=0,int oblog=0,const string& fallsnichtda="", binaer alsroot=falsch);
    uchar doggfinst(const string& prog,int obverb=0,int oblog=0);
    uchar douninst(const string& prog,int obverb=0,int oblog=0);
    uchar obfehlt(const string& prog,int obverb=0,int oblog=0);
};

// Service aus SystemD
class servc {
  public:
    int servicelaeuft=0, serviceda=0;
    int fehler=0;
    string sname,ename; // ausgefuehrte Datei
    servc(string vsname,string vename): sname((vsname.empty()?vename:vsname)),ename(vename) {}
    servc(string vsname,string vename,int obverb, int oblog);
    uchar spruef(const string& sbez,uchar obfork,const string& parent, const string& sexec, const string& CondPath, const string& After, 
                 const string& wennnicht0, int obverb=0,int oblog=0);
    int obslaeuft(int obverb, int oblog, binaer nureinmal=falsch);
    int restart(int obverb, int oblog);
    void start(int obverb, int oblog);
    int startundenable(int obverb, int oblog);
    void stop(int obverb, int oblog);
    void stopdis(int obverb, int oblog);
    int enableggf(int obverb,int oblog);
    int machfit(int obverb, int oblog, binaer nureinmal=falsch);
    static void daemon_reload(int obverb=0, int oblog=0);
};

