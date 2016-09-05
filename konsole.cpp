#include "konsole.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/statvfs.h> // fuer statfs


#ifdef _WIN32
const char *dir = "dir ";
#elif linux
const char *dir = "ls -l ";
#endif

#ifdef linux
#include <iomanip> // setprecision
// const char *rot="\e[1;31m", *weinrot="\e[31m", *schwarz="\e[0m", *blau="\e[34m", *gelb="\e[33m"; // muss spaeter kompilerunabhaengig 
const char *schwarz="\e[0m", *dgrau="\e[1;30m", *drot="\e[0;31m", *rot="\e[1;31m", *gruen="\e[0;32m", *hgruen="\e[1;32m",
      *braun="\e[0;33m",   *gelb="\e[1;33m",     *dblau="\e[0;34;1;47m",  *blau="\e[1;34m", *violett="\e[0;35m", *hviolett="\e[1;35m",
      *tuerkis="\e[0;36m", *htuerkis="\e[1;36m", *hgrau="\e[0;37m", *weiss="\e[1;37m", *umgek="\e[7m";
const char *_drot=drot, *_rot=rot, *_schwarz=schwarz, *_blau=blau, *_gelb=gelb, *_tuerkis=tuerkis, *_hgrau=hgrau;
// char logdatei[PATH_MAX+1]="/DATA/down/log_termine.txt";
#define _access access
#include <sys/time.h>  // für gettimeofday()
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
#define obfstream


const char *Txkonsolecl::TextC[T_konsoleMAX+1][Smax]=
{
  //TCtp Txkonsolecl::TextC=KLA
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
  // T_nicht_geladen
  {" nicht geladen"," not loaded"},
  // T_am
  {"' am ","' on "},
  // T_als_Dienst_eingerichtet_von
  {", als Dienst eingerichtet von '",", installed as service by '"},
  // T_Versuch
  {", Versuch: ",", try no.: "},
  {"",""}
}; // const char *Txkonsolecl::TextC[T_konsoleMAX+1][Smax]=


Txkonsolecl::Txkonsolecl() 
{
  TCp=(const char* const * const * const *)&TextC;
}

class Txkonsolecl Txk;

uchar nrzf=0; // nicht rueckzufragen, fuer Aufruf aus Cron

argcl::argcl(int i,char** argv) 
{
  argcs=argv[i];
}

const string drots=drot, rots=rot, schwarzs=schwarz, blaus=blau, gelbs=gelb, tuerkiss=tuerkis, violetts=violett, gruens=gruen;

perfcl::perfcl(const string& vvonwo): vonwo(vvonwo)
{
  zp0=clock(); 
  t0=time(NULL);
}

void perfcl::ausgeb(const string& stelle)
{
  zp1=clock();
  t1=time(NULL);
  cout<<gruen;
  if (!vonwo.empty())
   cout<<vonwo<<Txk[T_Versuch]<<++nr<<", ";
  cout<<Txk[T_Dauer]<<setprecision(7)<<setw(9)<<(long)(zp1-zp0)<<" clocks = "
    <<fixed<<(t1-t0)<<schwarz<<setprecision(0)<<" s\r";cout.flush();
} // void perfcl::ausgeb(const string& stelle)


void perfcl::ausgab1000(const string& stelle)
{
  zp1=clock();
  nr++;
  if (zp1-zp0>10000) {
    cout<<gruen<<vonwo<<" "<<stelle<<" "<<nr<<Txk[T_Dauer]<<setprecision(7)<<setw(9)<<(long)(zp1-zp0)<<" = "
      <<fixed<<((zp1-zp0)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s"<<endl;
    exit(0);
  }
} // void perfcl::ausgab1000(const string& stelle)

int perfcl::oberreicht(unsigned long sek)
{
 zp1=clock();
// <<"zp1-zp0: "<<(zp1-zp0)<<", sek: "<<(long)(sek*CLOCKS_PER_SEC)*0.1<<endl;
 return ((zp1-zp0)>(long)sek*CLOCKS_PER_SEC*0.1);
}


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
if (logdatei[0]=='1') exit(0);
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
  string erg="";
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
  }
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
  string erg="";
  if (alt[0]==0 || !strcmp(alt,neu)) {
    erg=quelle;
  } else {
    for(char* p=(char*)quelle;p<quelle+strlen(quelle);p++)  {
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
      }
    }
  }
  return src;
} // sersetze( string src, string const& target, string const& repl)

void getstammext(string *ganz, string *stamm, string *exten) 
{
  size_t posp = ganz->rfind('.');
  if (posp!=std::string::npos) {
    *exten=ganz->substr(posp+1);
    *stamm=ganz->substr(0,posp);
  } else {
    *exten="";
    *stamm=string(*ganz);
  }
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

mdatei::mdatei(const string& name, ios_base::openmode modus,int obverb, int oblog)
{
  for(int iru=0;iru<3;iru++) {
    open(name,modus);
    if (is_open()) {
      oboffen=1;
      break;
    }
    //    int erg __attribute__((unused));
    pruefverz(dir_name(name),0,0,0);
    if (!systemrueck("sudo test -f '"+name+"' || sudo touch '"+name+"'",obverb,oblog)) {
      setfaclggf(name,falsch,modus&ios::out?6:4,falsch,obverb,oblog);
    } // if (!systemrueck("sudo test -f '"+name+"' || sudo touch '"+name+"'",obverb,oblog)) 
  } // for(int iru=0;iru<3;iru++) 
} // mdatei::mdatei (const string& name, ios_base::openmode modus)


#ifdef falsc
#ifdef obfstream
fstream*
#else
FILE*
#endif
oeffne(const string& datei, uchar art, uchar* erfolg,int obverb=0, int oblog=0)
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
      setfaclggf(datei,falsch,art?6:4,falsch,obverb,oblog);
      break;
    } 
    if (!*erfolg) {
      int erg __attribute__((unused));
      erg=systemrueck("sudo touch '"+datei+"'",obverb,oblog);
    }
  } // oeffne
  return sdat;
}
#endif	


#ifdef schrott
#endif



int kuerzelogdatei(const char* logdatei,int obverb)
{
#ifdef false
  uchar erfolg=0;
#endif
  // zutun: nicht erst in Vektor einlesen, sondern gleich in die tmp-Datei schreiben 10.6.12

  //	vector<string> Zeilen;   //Der Vektor Zeilen enthält String-Elemente
  char Zeile[256]; //Die maximale Zeilenlänge beträgt 255 Zeichen, weil ein String mit einer Null endet
  if (obverb>1) {
    cout<<"verbose: "<<(int)obverb<<Txk[T_kuerze_logdatei]<<drot<<logdatei<<schwarz<<endl;
  }
  //  Log(string("kuerzelogdatei: ") + drot + logdatei + schwarz,obverb,0);
  // ersetze(logdatei,"\\","\\\\")
  struct stat stat;
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
  string ofil=string(logdatei)+"tmp";
  int abhier=0;
  mdatei outfile(ofil,ios::out);
  if (!outfile.is_open()) {
    perror((string("\nkuerzelogdatei: ")+Txk[T_Kann_Datei]+ofil+Txk[T_nicht_als_fstream_zum_Schreiben_oeffnen]).c_str());
    return 1;
  }
  mdatei logf(logdatei,ios::in);
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
      //		Zeilen.push_back(Zeile); //hängt einfach den Inhalt der Zeile als Vektorelement an das Ende des Vektors
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
          //	for(aktz=Zeilen.size()-1;aktz>=0;aktz--) {
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
                  atm->tm_isdst=-1; // sonst wird zufällig ab und zu eine Stunde abgezogen
                } else if (verwertbar) verwertbar=0;
                break;
              case 1:
                if (strptime(Zeile,"%a %b %d %T %Y", atm)) {
                  if (!verwertbar) {
                    verwertbar=2;
                    j=2;
                  } 
                } else if (verwertbar) verwertbar=0;
            }
          }
          if (verwertbar) {
            gesz=mktime(atm);
            //          	  char tbuf[20];
            //              strftime(tbuf, 18,"%d.%m.%y %X",localtime(&gesz));
            //              <<"Datum: "<<tbuf<<endl;
            //              exit(0);
            time_t jetzt;
            jetzt=time(0);
            sekunden=(long)(jetzt-gesz);
            if (sekunden<1209600) {// jünger als zwei Wochen => behalten
              abhier=1;
            }
            //	  <<jetzt<<"- "<<gesz<<"="<<sekunden<<endl;
          } // if (sscanf(Zeile
          delete[] atm;
        } // (!abhier)
        if (abhier) {
          outfile<<Zeile<<endl;
        }
        }
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
/*	
    Log(string("kuerzelogdatei, nach Einlesen"),obverb,0);	
    tm *atm = new tm; time_t gesz; long sekunden; int aktz;
    for(aktz=Zeilen.size()-1;aktz>=0;aktz--) {
//         Log(string("aktz=") + ltoa_(aktz,buffer,10),obverb,0);
if (sscanf(Zeilen[aktz].c_str(),"%2d.%2d.%2d %2d:%2d:%2d%*s", &atm->tm_mday,&atm->tm_mon,&atm->tm_year,&atm->tm_hour,&atm->tm_min,&atm->tm_sec)==6)
{
atm->tm_mon-=1;
atm->tm_year+=100; // 2000-1900
//	  <<atm->tm_mday<<"."<<atm->tm_mon+1<<"."<<atm->tm_year<<"."<<atm->tm_hour<<"."<<atm->tm_min<<"."<<atm->tm_sec<<endl;
gesz=mktime(atm);
//	  char tbuf[20];
//      strftime(tbuf, 18,"%d.%m.%y %X",localtime(&gesz));
//      <<tbuf<<endl;
time_t jetzt;
jetzt=time(0);
sekunden=(long)(jetzt-gesz);
if (sekunden>1209600) {// älter als zwei Wochen => abschneiden
break;
}
//	  <<jetzt<<"- "<<gesz<<"="<<sekunden<<endl;
}
}
Log(string("kuerzelogdatei, nach Datumspruefung"),obverb,0);	
string ofil=string(logdatei)+"tmp";
#ifdef obfstream
fstream outfile(ofil.c_str(),ios::out);
if (!outfile) {
perror((string("\nkuerzelogdatei: Kann Datei '")+ofil+"' nicht als fstream zum Schreiben oeffnen.").c_str());
return 1;
} else {
for(int j=aktz+1;j<Zeilen.size();j++) {
outfile<<Zeilen[j]<<endl;
}
}
#else
logf = fopen(ofil.c_str(),"w");
if (!logf) {
perror((string("\nkuerzelogdatei: Kann Datei '")+ofil+"' nicht mit logf zum Schreiben oeffnen.").c_str());
return 1;
} else {
for(unsigned j=aktz+1;j<Zeilen.size();j++) {
fputs(Zeilen[j].c_str(),logf);
fputs("\n",logf);
} 
fclose(logf);
}
#endif
 */	
if (abhier) {
  remove(logdatei);
  rename(ofil.c_str(),logdatei);
}else{
  remove(ofil.c_str());
}
return 0;
//  << "Alle Zeilen:" << endl;
// unsigned int ii; //unsigned, weil ansonsten Vergleich von signed- und unsigned-Werten. signed=vorzeichenbehaftet
// for(ii=0; ii < Zeilen.size(); ii++ddddddddds) {
//  << Zeilen[ii] << endl;
// }
//  << endl;
//************************************
}	 // int kuerzelogdatei(const char* logdatei,int obverb)



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
        string zwi=text; 
        loeschealleaus(&zwi,schwarz);
        loeschealleaus(&zwi,dgrau); 
        loeschealleaus(&zwi,drot); 
        loeschealleaus(&zwi,rot); 
        loeschealleaus(&zwi,gruen); 
        loeschealleaus(&zwi,hgruen); 
        loeschealleaus(&zwi,braun); 
        loeschealleaus(&zwi,gelb); 
        loeschealleaus(&zwi,blau); 
        loeschealleaus(&zwi,dblau); 
        loeschealleaus(&zwi,violett); 
        loeschealleaus(&zwi,hviolett); 
        loeschealleaus(&zwi,tuerkis); 
        loeschealleaus(&zwi,htuerkis); 
        loeschealleaus(&zwi,hgrau); 
        loeschealleaus(&zwi,weiss); 
        static bool erstaufruf=1;

        char tbuf[20];
        time_t jetzt=time(0);
        strftime(tbuf,19,"%d.%m.%y %X ",localtime(&jetzt));

        if (erstaufruf) {
          kuerzelogdatei(logdt,klobverb); // screen
          //          Log("nach kuerzelogdatei",screen,0);
          erstaufruf=0;
        }	  
        mdatei logf(logdt,ios::out|ios::app);
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
        // wenn cerr woanders hingeht als cout oder die Meldung gar nicht an screen gerichtet ist, hier ohne Berücks.v.screen==-1
        if (isatty(fileno(stdout))!=isatty(fileno(stderr)) || !screen) {
          cerr<<text<<endl; // <<": "<<hstrerror<<endl;
        }
        errno=0;
      }
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
  // Löscht etwaige Fehlerzustände die das Einlesen verhindern könnten
  cin.clear();
  // Ignoriert soviele Zeichen im Puffer wie im Puffer vorhanden sind
  // (= ignoriert alle Zeichen die derzeit im Puffer sind)
  cin.ignore(cin.rdbuf()->in_avail());
  // Füge alle eingelesenen Zeichen in den Puffer bis ein Enter gedrückt wird
  // cin.get() liefert dann das erste Zeichen aus dem Puffer zurück, welches wir aber ignorieren (interessiert uns ja nicht)
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
   * Written by Lukás Chmela
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
} // ltoa_(long value, char* result, int base)

char* ltoa_(long value, char* result, int base=10) 
{
  /**
   * C++ version 0.4 char* style "itoa":
   * Written by Lukás Chmela
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

void kopiere(string *quelle, string *ziel)
{
  mdatei fileIn(quelle->c_str(),ios::in|ios::binary);
  mdatei fileOut(ziel->c_str(),ios::out | ios::trunc | ios::binary);
  fileOut<<fileIn.rdbuf();
} // void kopiere(string *quelle, string *ziel)


void aufSplit(vector<string> *tokens, const char *text, char sep, bool nichtmehrfach)
{
  string texts=text;
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

string* anfzweg(string& quel) {
  if (quel.length()>1) {if (quel[0]==quel[quel.length()-1] && strchr("\"'",quel[0])) {
    quel.erase(quel.length()-1,1);
    quel.erase(0,1);
  }}
  return &quel;
} // string* anfzweg(


lsysen lsyscl::getsys(int obverb,int oblog)
{
      if (sys==usys) {
        if (!systemrueck("cat /proc/version | grep SUSE",obverb-2,oblog)) return sus;
        if (!systemrueck("cat /proc/version | grep 'Ubuntu\\|ebian'",obverb-2,oblog)) return deb;
        if (!systemrueck("cat /proc/version | grep edora",obverb-2,oblog)) return fed;
      }
      return usys;
}

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

string obprogda(string prog,int obverb, int oblog)
{
  svec rueck;
  if (!systemrueck("which "+prog+" 2>/dev/null",obverb,oblog,&rueck))
    return rueck[0];
  for(int iru=0;iru<3;iru++) {
    struct stat fstat;
    string verz;
    switch (iru) {
      case 0: verz="/sbin/"; break;
      case 1: verz="/usr/sbin/"; break;
      case 2: verz="/usr/local/sbin/"; break;
      default: break;
    }
    verz+=prog;
    if (!lstat(verz.c_str(),&fstat))
      return verz;
  }
  return ""; 
} // string obprogda(string prog,int obverb, int oblog)

instprog pruefipr(int obverb,int oblog)
{
  static instprog aktipr=keinp;
  if (aktipr==keinp) {
    if (!systemrueck("which zypper 2>/dev/null",obverb-1,oblog))
      // heruntergeladene Dateien behalten
      aktipr=zypper;
    else if (!systemrueck("which apt-get 2>/dev/null",obverb-1,oblog))
      // hier werden die Dateien vorgabemaessig behalten
      aktipr=apt;
    else if (!systemrueck("which dnf 2>/dev/null",obverb-1,oblog))
      aktipr=dnf;
    else if (!systemrueck("which yum 2>/dev/null",obverb-1,oblog))
      aktipr=yum;
   else
     cerr<<Txk[T_Weder_zypper_noch_apt_get_noch_dnf_noch_yum_als_Installationspgrogramm_gefunden]<<endl;
 }
 return aktipr;
} // instprog pruefipr(int obverb,int oblog)

const string& absch::suche(const char* const sname)
{
  static string nix="";
  for (size_t i=0;i<av.size();i++) {
    if (av[i].name==sname) {
      return av[i].wert;
    }
  }
  return nix;
} // const string& absch::suche(const char* const sname)

const string& absch::suche(const string& sname)
{
  return suche(sname.c_str());
} // const string& absch::suche(const string& sname)


int confdat::lies(const string& fname, int obverb)
{
  string zeile;
  if (fname.empty()) 
    return 2;
  mdatei f(fname,ios::in);
  if (f.is_open()) {
    if (obverb>0) cout<<"confdat::lies(fname...), fname: "<<fname<<endl;
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
        }
      }
    }
  }
  if (!abp.aname.empty() && abp.av.size()) {
    abschv.push_back(abp);
  }
//  for(size_t i=0;i<abschv.size();i++) KLA
//   <<violett<<"aname: '"<<abschv[i].aname<<"'"<<endl;
//   for(size_t j=0;j<abschv[i].av.size();j++) 
//    <<j<<": "<<abschv[i].av[j].name<<": "<<abschv[i].av[j].wert<<endl;
//  KLZ
} // void confdat::Abschn_auswert(int obverb, char tz)



void confdat::auswert(schlArr *sA, int obverb, char tz)
{
  richtige=0;
  sA->reset();
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
          size_t ii=sA->zahl,gef;
          while( ii-- ) {
            gef=zeile->find((*sA)[ii].name);
            if (!gef) { // conf[ii].name muss am Zeilenanfang anfangen, sonst Fehler z.B.: number, faxnumber
              (*sA)[ii].gelesen=1;
              if (strchr((string(" ")+(char)9+tz).c_str(),zeile->at(gef+(*sA)[ii].name.length()))) {
                ++richtige;
                (*sA)[ii].wert=zeile->substr(pos+1);
                gtrim(&(*sA)[ii].wert); // Leerzeichen entfernen
                // Anfuerhungszeichen entfernen
                anfzweg((*sA)[ii].wert);
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
  }
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
 }
 va_end(list);
} // void schlArr::init(size_t vzahl, ...)

int schlArr::setze(const string& name, const string& wert)
{
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
      schl[ind].wert=wert;
      return 0;
    }
  }
  return 1;
} // int schlArr::setze(const string& name, const string& wert)
 
const string& schlArr::hole(const string& name)
{
  static const string nix="";
  for(size_t ind=0;ind<zahl;ind++) {
    if (schl[ind].name==name) {
      return schl[ind].wert;
    }
  }
  return nix;
} // const string* schlArr::hole(const string& name)

void schlArr::schreib(mdatei *f)
{
  for (size_t i = 0;i<zahl;i++) {
    *f<<schl[i].name<<" = \""<<schl[i].wert<<"\""<<endl;
  }
} // void schlArr::schreib(mdatei *f)

int schlArr::schreib(const string& fname)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    schreib(&f);
    return 0;
  }
  return 1;
} // int schlArr::schreib(const string& fname)

schlArr::~schlArr()
{
  if (schl) delete[] schl;
}

int multischlschreib(const string& fname, schlArr **confs, size_t cszahl)
{
  mdatei f(fname,ios::out);
  if (f.is_open()) {
    for (size_t j=0;j<cszahl;j++) {
     confs[j]->schreib(&f);
    }
    return 0;
  }
  return 1;
} // int multischlschreib(const string& fname, schlArr **confs, size_t cszahl)


string XOR(const string& value, const string& key)
{
  string retval(value);
  short unsigned int klen=key.length(), vlen=value.length(), k=0, v;
  for(v=0;v<vlen;v++) {
    retval[v]=value[v]^key[k];
    k=(++k<klen?k:0);
  }
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

int schreib(const char *fname, Schluessel *conf, size_t csize)
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
} // int schreib(const char *fname, Schluessel *conf, size_t csize)


std::string base_name(const std::string& path)
{
  return path.substr(path.find_last_of("/\\") + 1);
} // std::string base_name(std::string const & path)

std::string dir_name(const std::string& path)
{
  return path.substr(0,path.find_last_of("/\\"));
} // std::string dir_name(std::string const & path)

// soll fuer den Fall eines uebergebenen 'rueck'-Zeigers den Rueckgabewert der aufgerufenen Funktion zuruckliefern,
// ausser bei 'find', da die Zahl der Funde
// bei rueck==0 liefert es das Ergebnis der system(..)-Funktion zurueck
int systemrueck(const string& cmd, char obverb, int oblog, vector<string> *rueck, 
    binaer ob0heissterfolg, binaer obergebnisanzeig, const string& ueberschr,vector<errmsgcl> *errm)
{
  uchar neurueck=0;
  uchar weiter=0;
  int erg;
  string const * czg=&cmd;
  string hcmd;
  uchar obfind=(cmd.substr(0,4)=="find" || cmd.substr(0,9)=="sudo find");
  if (obfind && (obverb<1 || strcmp(curruser(),"root"))) {
   hcmd=cmd+" 2>/dev/null";
   czg=&hcmd;
  }
  // "obfind: "<<(int)obfind<<", obverb: "<<(int)obverb<<", curruser(): "<<curruser()<<", '"<<violett<<*czg<<schwarz<<"'"<<endl;
  string meld(Txk[T_Rueckmeldung]);
  string aktues;
  if (ueberschr.empty()) { 
    if (obfind) {
      aktues=Txk[T_Suchbefehl];
    } else {
      aktues=Txk[T_Fuehre_aus];
      weiter=1;
    }
  } else {
    aktues=ueberschr;
  }
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
      if (obfind)
        erg=rueck->size();
      else
        erg = pclose(pipe)/256;
#ifdef systemrueckprofiler
      prf.ausgab1000("nach pclose");
#endif
    } else {
      perror((string("popen() ")+Txk[T_fehlgeschlagen_bei]+*czg).c_str());
      erg=1;
    }
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
          ergebnis=(erg?rots:schwarzs)+ltoan(erg)+": "+errm->at(i).msg;
          break;
        }
      }
    }  // if (errm)
    if (ergebnis.empty()) {
      if (ob0heissterfolg) {
        if (erg) {
          ergebnis=rots+string(Txk[T_Fehler])+ltoan(erg)+schwarz;
          if (obverb>=0) obergebnisanzeig=wahr;
          obverb++;
        } else {
          ergebnis=Txk[T_Erfolg];
        } // ob0heissterfolg else
      } else {
        ergebnis=ltoan(erg);
      }
    } //     if (ergebnis.empty() {
#ifdef systemrueckprofiler
    prf.ausgab1000("vor log");
#endif
    Log(aktues+": "+blau+*czg+schwarz+Txk[T_komma_Ergebnis]+blau+ergebnis+schwarz,obverb>0?obverb:0,oblog);
  } // if (obverb>0 || oblog)
  if (obergebnisanzeig) if (rueck->size()) 
    Log(meld,obverb>1,oblog);
  if (neurueck) delete rueck;
  return erg; 
} // int systemrueck(const string& cmd, char obverb, int oblog, vector<string> *rueck, binaer ...

void pruefplatte()
{
  struct statvfs fp;
  string platte="/";
  statvfs(platte.c_str(),&fp);   
  if (fp.f_bsize * fp.f_bfree < 100000) { // wenn weniger als 100 MB frei sind ...
    systemrueck("sudo pkill postdrop");
  }
} // pruefplatte

void pruefmehrfach(string& wen)
{
  svec rueck;
  if (wen.empty()) wen=base_name(meinpfad());
  systemrueck("ps -eo comm|grep '^"+wen+"'",0,0,&rueck);
  if (rueck.size()>1) {
    cout<<Txk[T_Program]<<blau<<wen<<schwarz<<Txk[T_laeuft_schon_einmal_Breche_ab]<<endl;
    exit(0);
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
int setfaclggf(const string& datei, const binaer obunter, const int mod, binaer obimmer,int obverb, int oblog)
{
  static string cuser=curruser(); 
  if (cuser!="root") {
      static int obsetfacl=!systemrueck("which setfacl",obverb-1,0); 
      if (obsetfacl) {
       const char* modbuch;
       switch (mod) {
        case 4: modbuch="r"; break;
        case 6: modbuch="rw"; break;
        default: modbuch="rwx";  // 7
       }
       if (!obimmer) {
        svec gstat;
        systemrueck("getfacl -e -t "+datei+" 2>/dev/null | grep 'user[ \t]*"+cuser+"[ \t]*"+modbuch+"' || true",obverb,oblog,&gstat);
        if (!gstat.size()) obimmer=wahr; // wenn keine Berechtigung gefunden => erstellen
       }
       if (obimmer) {
          if (obverb) systemrueck("sudo sh -c 'ls -l "+datei+"'",2,0);
          systemrueck(string("sudo setfacl -")+(obunter?"R":"")+"m 'u:"+cuser+":"+ltoan(mod)+"' '"+datei+"'",obverb,oblog);
          if (obverb) systemrueck("sudo sh -c 'ls -l "+datei+"'",2,0);
       }
      }
  }
  return 0;
} // int setfaclggf(const string& datei, const binaer obunter, const int mod, binaer obimmer,int obverb, int oblog)


// obmitfacl: 1= setzen, falls noetig, 2= immer setzen
int pruefverz(const string& verz,int obverb,int oblog, uchar obmitfacl)
{
  struct stat sverz;
  int fehler=1;
  if (!verz.empty()) {
    if (!lstat(verz.c_str(), &sverz)) {
      if(S_ISDIR(sverz.st_mode)) {
        fehler=0;
      }
    }
    if (fehler) fehler=systemrueck("mkdir -p '"+verz+"' 2>/dev/null",obverb,oblog);
    if (fehler) fehler=systemrueck("sudo mkdir -p '"+verz+"'",obverb,oblog);
    if (obmitfacl)
     setfaclggf(verz, wahr, 7, falsch,obverb,oblog);
  }
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
  }
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
    }
    if (passt) break; 
  }
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
    }
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
    }
    if (passt) break; 
  }
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
  string vstr=string(vorgabe);
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
    input="";
    getline(cin,input);
    if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
    if (input=="" && vorgabe) {
     input=*vorgabe;
     break;
    }
    break;
  }
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
    struct stat st;
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
        }
      }
    }
    if (fertig) break;
  }
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

int optioncl::pruefp(vector<argcl> *argcvm , size_t *akt, uchar *hilfe) // 1 = das war der Parameter, 0 = nicht
{
  if (*akt<argcvm->size()) if (!argcvm->at(*akt).agef) {
    char *acstr=argcvm->at(*akt).argcs;
    if (strlen(acstr)>1) {
      if (acstr[0]=='-'||acstr[0]=='/') {
        if (!strcmp(&(acstr[1]),kurz.c_str())) {
          argcvm->at(*akt).agef=1;
        }
      }
      if (!argcvm->at(*akt).agef) if (strlen(acstr)>2) if (acstr[0]=='-'&&acstr[1]=='-') 
        if (!strcmp(&(acstr[2]),lang.c_str())) {
          argcvm->at(*akt).agef=1;
        }
    }
    if (argcvm->at(*akt).agef) {
      if (pptr) {
        if (*pptr!=wert) {
          *pptr=wert;
          if (obschreibp) *obschreibp=1;
          if (cp && pname) {
            cp->setze(pname,ltoan(wert));
          }
        }
      } else {
        char *pstr=0;
        uchar falsch=0;
        if (*akt<argcvm->size()-1)  {
          char *nacstr=argcvm->at(*akt+1).argcs;
          struct stat entryarg;
          switch (art) {
            case psons:
              if (!strchr("-/",nacstr[0])) {
                pstr=nacstr;
              }
              break;
            case pverz:
            case pfile:
              if (nacstr[0]!='-') {
                if (stat(nacstr,&entryarg)) falsch=1;  // wenn inexistent
                else if ((art==pverz)^(S_ISDIR(entryarg.st_mode))) falsch=2; // Datei fuer Verzeichnis o.u.
                else pstr=nacstr;
              }
              break;
            case pzahl:
              if (!strchr("-/",nacstr[0])) {
                if (!isnumeric(nacstr)) falsch=1;
                else pstr=nacstr;
              }
              break;
          }
        }
        if (pstr) {
          if (*zptr!=pstr) {
            *zptr=pstr; 
            if (obschreibp) *obschreibp=1;
            if (cp && pname) {
             cp->setze(pname,pstr);
            }
          }
          argcvm->at(++(*akt)).agef=1;
        } else {
          switch (art) {
            case psons:
              Log(drots+Txk[T_Fehlender_Parameter_string_zu]+kurz+Txk[T_oder]+lang+"!"+schwarz,1,1);
              break;
            case pverz:
            case pfile:
              Log(drots+Txk[T_Fehler_Parameter]+kurz+Txk[T_oder]+lang+" "+(falsch==1?Txk[T_ohne_gueltigen]:falsch==2?
                    Txk[T_mit_Datei_als]:Txk[T_mit_falschem])+Txk[T_Pfad_angegeben]+schwarz,1,1);
              break;
            case pzahl:
              Log(drots+(falsch==1?Txk[T_Nicht_numerischer]:Txk[T_Fehlender])+Txk[T_Parameter_nr_zu]+kurz+Txk[T_oder]+lang+"!"+schwarz,1,1);
              break;
          }
          *hilfe=1;
        } // if (pstr) else
      } // if (pptr) else
      return 1;
    } // if (argcvm->at(*akt).agef)
  } // if (*akt<argcvm->size()) if (!argcvm->at(*akt).agef) 
  return 0;
} // pruefp

void optioncl::hilfezeile(Sprache lg)
{
  if (TxBp) {
    if (Txi!=-1) {
      if (TxBp->TCp[Txi][lg]) {
        cout<<drot<<" -"<<kurz<<", --"<<lang;
        if (zptr) {if (art==psons || art==pfile) cout<<" <string>"; else if (art==pverz) cout<<" <"<<Txk[T_pfad]<<">"; else cout<<" <zahl>";}
        TCtp *hilf = reinterpret_cast<TCtp*>(TxBp->TCp);
        cout<<schwarz<<": "<< (const char*)hilf[Txi][lg];
        if (rottxt) cout<<blau<<*rottxt<<schwarz;
        if (Txi2!=-1) cout<<(const char*)hilf[Txi2][lg]; 
        if (zptr) cout<<" '"<<blau<<*zptr<<schwarz<<"'";
        cout<<endl;
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


string linstcl::ersetzeprog(const string& prog) 
{
  switch(pruefipr()) {
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
      break;
    case dnf: case yum:
      if (prog=="mariadb") return "mariadb-server";
      if (prog=="kernel-source") return "kernel-devel-$(uname -r)";
      if (prog=="libcapi20-2") return "isdn4k-utils";
      if (prog=="libcapi20-3") return "";
      if (prog=="capiutils") return "";
      if (prog=="imagemagick") return "ImageMagick ImageMagick-doc";
      break;
    default: break;
  }
  return prog;
} // string linstcl::ersetzeprog(const string& prog) 


uchar linstcl::doinst(const string& prog,int obverb,int oblog,const string& fallsnichtda, binaer alsroot) 
{
  // <<rot<<"doinst 1: "<<violett<<prog<<schwarz<<" obverb: "<<(int)obverb<<endl;
  uchar ret=2;
  if (eprog.empty()) eprog=ersetzeprog(prog);
  if (!fallsnichtda.empty()) if (!systemrueck((alsroot?string("root "):string(""))+"which '"+fallsnichtda+"' >/dev/null 2>&1",obverb,oblog)) return 0;
  if (!eprog.empty()) {
    switch (pruefipr()) {
      case zypper:
        if (obnmr) {
          obnmr=0;
          systemrueck("sudo zypper mr -k -all",obverb,oblog);
        }
        ret=systemrueck("sudo zypper -n --gpg-auto-import-keys in -f "+eprog,obverb+1,oblog);
        break;
      case apt:
        ret=systemrueck("sudo apt-get -y install "+eprog,obverb+1,oblog);
        break; 
      case dnf:
        ret=systemrueck("sudo dnf -y install "+eprog,obverb+1,oblog);
        break;
      case yum:
        ret=systemrueck("sudo yum -y install "+eprog,obverb+1,oblog);
        break;
      default: break;
    }
    eprog.clear();
  }
  return ret;
} // uchar linstcl::doinst(const string& prog,int obverb,int oblog) 

uchar linstcl::doggfinst(const string& prog,int obverb,int oblog)
{
  if (!(eprog=ersetzeprog(prog)).empty()) {
    if (obfehlt(eprog,obverb,oblog)) {
      return doinst(prog,obverb,oblog);
    }
  }
  return 0;
} // uchar linstcl::doggfinst(const string& prog,int obverb,int oblog)

uchar linstcl::doinst(const char* prog,int obverb,int oblog,const string& fallsnichtda,binaer alsroot)
{
  const string& progs=prog;
  // <<rot<<"doinst 2: "<<violett<<prog<<schwarz<<" obverb: "<<(int)obverb<<endl;
  return doinst(progs,obverb,oblog,fallsnichtda,alsroot);
} // uchar linstcl::doinst(const char* prog,int obverb,int oblog,const string& fallsnichtda)

uchar linstcl::douninst(const string& prog,int obverb,int oblog) 
{
  switch (pruefipr()) {
    case zypper:
      return systemrueck("sudo zypper -n rm "+prog,obverb,oblog);
      break;
    case apt:
      return systemrueck("sudo apt-get -y remove "+ersetzeprog(prog),obverb,oblog);
      break; 
    case dnf:
      return systemrueck("sudo dnf -y remove "+ersetzeprog(prog),obverb,oblog);
      break; 
    case yum:
      return systemrueck("sudo yum -y remove "+ersetzeprog(prog),obverb,oblog);
      break; 
    default: break;
  }
  return 2;
} // uchar linstcl::douninst(const string& prog,int obverb,int oblog) 


uchar linstcl::obfehlt(const string& prog,int obverb,int oblog)
{
 // <<violett<<"linst::obfehlt: "<<schwarz<<prog<<endl;
  switch (pruefipr()) {
    case zypper: case dnf: case yum: 
      return systemrueck("rpm -q "+prog+" 2>/dev/null",obverb,oblog);
    case apt:
      return systemrueck("dpkg -s "+ersetzeprog(prog)+" 2>/dev/null",obverb,oblog);
    default: break;
  }
  return 2;
} // uchar linstcl::obfehlt(const string& prog,int obverb,int oblog)


string meinpfad() {
  char buff[PATH_MAX];
  buff[0]=0;
  ssize_t len = readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
  }
  return string(buff);
} // meinpfad

servc::servc(string vsname,string vename,int obverb, int oblog): sname((vsname.empty()?vename:vsname)),ename(vename) 
{
  machfit(obverb,oblog);
}

int servc::machfit(int obverb,int oblog, binaer nureinmal)
{
    if (!obslaeuft(obverb,oblog,nureinmal)) {
      restart(obverb,oblog);
    }
    //  if (servicelaeuft)
    enableggf(obverb,oblog);
    return servicelaeuft;
} // int servc::machfit(int obverb,int oblog)

// wird aufgerufen in: hservice_faxq_hfaxd, hservice_faxgetty
uchar servc::spruef(const string& sbez,uchar obfork, const string& parent, const string& sexec, const string& CondPath, const string& After, 
                    const string& wennnicht0, int obverb,int oblog)
{
  Log(violetts+Txk[T_spruef_sname]+schwarz+sname,obverb,oblog);
  string systemd;
  int svgibts=0; // 1 = Datei systemd existiert
  if (!wennnicht0.empty()) {
    servicelaeuft=!systemrueck(wennnicht0,obverb-1,oblog);
  }
  if (servicelaeuft && svgibts) {
    Log(("Service ")+blaus+sname+schwarz+Txk[T_lief_schon],obverb,oblog);
  } else {
    for(uchar iru=0;iru<2;iru++) {
    /*
      char pBuf[300];
      int bytes = MIN(readlink("/bin/systemd", pBuf, sizeof pBuf), sizeof pBuf - 1);
      if(bytes >= 1) pBuf[bytes-1] = 0; // ../system statt /systemd
      systemd=string(pBuf)+"/"+sname+".service";
    */
      systemd="/etc/systemd/system/"+sname+".service";
      struct stat svstat;
      svgibts=!lstat(systemd.c_str(),&svstat);
      if (!svgibts || !obslaeuft(obverb,oblog)) {
        if (svgibts && serviceda) {
          restart(obverb,oblog); // hier wird auch serviceslaeuft gesetzt
          /*
             servicelaeuft=!systemrueck(("sudo pkill ")+ename+" >/dev/null 2>&1; sudo systemctl restart "+sname,obverb-1,oblog); 
           */
          // bei restart return value da 
          //          <<dblau<<"serviceda: "<<schwarz<<sname<<", servicelaeuft: "<<(int)servicelaeuft<<endl;
        } else {
          //          <<dblau<<"serviceda else: "<<schwarz<<sname<<endl;
          //  if (systemrueck("systemctl list-units faxq.service --no-legend | grep 'active running'",obverb-1,oblog)) KLA
          // string systemd="/usr/lib/systemd/system/"+sname+".service"; // außerhalb Opensuse: /lib/systemd/system/ ...
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
          } // if (syst.is_open()) 
        } // if (svgibts && serviceda) else
      } // if (!svgibts || !obslaeuft(obverb,oblog)) 
      if (servicelaeuft) { 
        if (systemrueck("systemctl is-enabled "+sname,obverb-1,oblog)) {
          systemrueck("sudo systemctl enable "+sname,obverb,oblog);
        }
        break;
      }
    } //  for(uchar iru=0;iru<2;iru++) 
  } // if (servicelaeuft) else
  return servicelaeuft;
} // void servc::spruef() 

// wird aufgerufen in: pruefhyla, pruefcapi, spruef
int servc::obslaeuft(int obverb,int oblog, binaer nureinmal)
{
  perfcl prf(Txk[T_Aktiviere_Dienst]+sname);
  while (1) {
    svec sysrueck;
    servicelaeuft=0;
    serviceda=0;
    systemrueck(("systemctl list-units '")+sname+".service' --all --no-legend",obverb,oblog,&sysrueck);  // bei list-units return value immer 0
    if (!sysrueck.empty()) {
      Log(blau+sysrueck[0]+schwarz,obverb>1?obverb-1:0,oblog);
      if (sysrueck[0].find("active running")!=string::npos) {
        servicelaeuft=1; 
        serviceda=1;
        break;
      } else if (sysrueck[0].find("activating")!=string::npos) {
        if (nureinmal || prf.oberreicht(120)) break;
        prf.ausgeb();
      } else if (sysrueck[0].find("loaded")!=string::npos) {
        serviceda=1;
        break;
      } else {
        break;
      }
    } else { // if (!sysrueck.empty()) 
     break;
    }
  } // while (1)
  if (!serviceda) {
    vector<errmsgcl> errv;
    string froh=schwarzs+Txk[T_Dienst]+blau+sname+schwarz;
    string f0=froh+Txk[T_geladen];
    string f1=froh+Txk[T_nicht_geladen];
    errv.push_back(errmsgcl(0,f0));
    errv.push_back(errmsgcl(1,f1));
    serviceda=!systemrueck("systemctl status '"+sname+"'| grep ' loaded '",obverb,oblog,0,wahr,wahr,"",&errv);
  }
  return servicelaeuft;
} // int servc::obslaeuft(int obverb,int oblog)

int servc::restart(int obverb,int oblog)
{
  for(int i=0;i<2;i++) {
    systemrueck(string("sudo systemctl restart '")+sname+"' >/dev/null 2>&1",obverb,oblog);
    if (obslaeuft(obverb,oblog)) break;
    if (i) break;
    systemrueck(("sudo pkill '")+ename+"' >/dev/null 2>&1",obverb-1,oblog);
  }
  return servicelaeuft;
} // int servc::restart(int obverb,int oblog)

void servc::start(int obverb,int oblog)
{
  systemrueck(string("sudo systemctl start '")+sname+"' >/dev/null 2>&1",obverb,oblog);
} // int servc::start(int obverb,int oblog)

int servc::startundenable(int obverb,int oblog)
{
  start(obverb,oblog);
  enableggf(obverb,oblog);
  return obslaeuft(obverb,oblog);
} // int servc::start(int obverb,int oblog)

void servc::stop(int obverb,int oblog)
{
  systemrueck(string("sudo systemctl stop '")+sname+"' >/dev/null 2>&1",obverb,oblog);
} // int servc::stop(int obverb,int oblog)

void servc::stopdis(int obverb,int oblog)
{
  stop(obverb,oblog);
  systemrueck(string("sudo systemctl disable '")+sname+"' >/dev/null 2>&1",obverb,oblog);
} // int servc::stop(int obverb,int oblog)

int servc::enableggf(int obverb,int oblog)
{
 return systemrueck(string("systemctl is-enabled '")+sname+"' >/dev/null 2>&1 || sudo systemctl enable '"+sname+"' >/dev/null 2>&1",obverb,oblog);
}

void servc::daemon_reload(int obverb, int oblog)
{
 systemrueck("sudo systemctl daemon-reload",obverb,oblog);
}

