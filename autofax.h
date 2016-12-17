#include <regex.h> // regex_t, regex, regcomp, regexec

enum FaxTyp:uchar {capi=1,hyla};
enum FxStat:uchar {init/*0*/,gestrichen,schwebend,wartend/*3*/,blockiert,bereit,verarb/*6*/,gesandt/*7*/,gescheitert/*8*/,fehlend,woasined};
enum hyinst {keineh,hysrc,hypak,hyppk}; // hyla source, hyla Paket, hylaplus Paket

class zielmustercl; // fuer die Verteilung der erfolgreich gefaxten Dateien auf verschiedene Dateien
class fxfcl; // Faxfile
class fsfcl; // Faxsendfile
class paramcl; // Programmparameter
string zielname(const string& qdatei, const string& zielverz,uchar wieweiterzaehl, string* zieldatei, int obverb, int oblog);
string zielname(const string& qdatei, zielmustercl *zmp,uchar wieweiterzaehl, string* zieldatei, int obverb, int oblog);
void dorename(const string& quelle, const string& ziel, const string& cuser="", uint *vfehler=0, int obverb=0, int oblog=0);
string verschiebe(const string& qdatei, const string& zielvz, const string& cuser="",uint *vfehler=0, uchar wieweiterzaehl=0, int obverb=0,int oblog=0);
void verschiebe(const string& qdatei, zielmustercl *zmp, const string& cuser="", uint *vfehler=0, uchar wieweiterzaehl=0, int obverb=0, int oblog=0);
string kopiere(const string& qdatei, const string& zieldp, uint *kfehler, uchar wieweiterzaehl, int obverb=0,int oblog=0);
string kopiere(const string& qdatei, zielmustercl *zmp, uint *kfehler, uchar wieweiterzaehl, int obverb=0, int oblog=0);
void pruefstdfaxnr(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog);
void pruefprocgettel3(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog);
void faxemitC(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, paramcl *pmp, int obverb, int oblog);
void faxemitH(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, paramcl *pmp, int obverb, int oblog);
int pruefcapi(paramcl *pmp, int obverb, int oblog);
void kuerzevtz(string *vzp);
pid_t PIDausName(const char* PName, uchar klgr, uchar exakt, int obverb, int oblog);
void getSender(paramcl *pmp,const string& faxnr, string *getnamep, string *bsnamep,int obverb=0,int oblog=0);

// Steuerung der Abspeicherung gesendeter Faxe je nach Muster
class zielmustercl 
{
  // beim letzten Element muss ziel leer sein!
  private:
    string muster;
  public:
    string ziel;
    regex_t regex;
    // wird nur in Vorgaben gebraucht:
    zielmustercl(const char * const muster,const char * const ziel);
    zielmustercl(const char * const muster,const string& ziel);
    zielmustercl();
    int kompilier();
    int setzemuster(const string& vmuster);
    const string& holmuster();
    int obmusterleer();
}; // class zielmustercl

class urfxcl // urspruengliche Dateidaten vor Aufteilung an verschiedene Faxadressaten
{
 public:
    string teil;
    string ur;
    unsigned prio; // Prioritaet der Fax-Programme: 0 = capi und 0 = hyla per Konfigurationsdatei, 1= capi und 2= hyla per Faxdateiname
    urfxcl(string& teil, string& ur,unsigned prio): teil(teil), ur(ur), prio(prio) {}
};

class fxfcl // Faxfile
{
  public:
    string npdf; // nicht-PDF
    string spdf; // schon-PDF
    string ur;   // urspruenglicher Dateinamen
    unsigned prio; // Prioritaet der Fax-Programme: 0 = capi und 0 = hyla per Konfigurationsdatei, 1= capi und 2= hyla per Faxdateiname
		ulong pseiten; // PDF-Seitenzahl
    fxfcl(string& npdf,string& spdf,string& ur,unsigned prio): npdf(npdf),spdf(spdf),ur(ur),prio(prio),pseiten(0) {}
    // nur fuer Initialisierung in fsfcl, Konstruktur /*1*/, nur fuer faxealle
    fxfcl(unsigned prio, string& npdf,string& spdf,ulong pseiten): npdf(npdf),spdf(spdf),prio(prio),pseiten(pseiten) {}
    fxfcl(string& spdf,string& ur,unsigned prio): npdf(""),spdf(spdf),prio(prio),pseiten(0) {}
    fxfcl() {}
};

class fsfcl : public fxfcl // Faxsendfile
{
  public:
    string id;
    string telnr;    // Telnr. des Adressaten
    string capisd; // capispooldatei
    int capids;  //capidials
    string hylanr; // hylanr
    int hdialsn; // hyladials
    uchar fobcapi; // ob es jetzt mit Capi weggefaxt werden muss
    uchar fobhyla; // ob es jetzt mit Hyla weggefaxt werden muss
    string adressat; // Name des Adressaten aus Faxdatei
    string original; // base_name(spdf)
    string origvu;   // base_name(npdf)
    string idudoc;   // id des urspruenglichen Dateinamens in tabelle udoc
    string cspf;     // capispoolpfad
    string cdd;      // cdateidatum
    string cdials;   // capidials
    string ctries; // parameter aus capiprot
    string starttime; // parameter aus capiprot
    string dialstring; // parameter aus capiprot
		int protpos=-1; // Ergebnis von holcapiprot 
    string hstate="0"; // Statuszahl ("state" in man sendq)
    string hstatus; // Textbeschreibung des letztes Fehlschlags
    string hstatuscode; // in xferfaxlog nicht gefunden
		string tts;
		string number;
    string hdials;   // hyladials
		string maxdials; // maxdials (hylafax)
    string hdd;      // hdateidatum
    string sendqgespfad; // kann fuer capi oder hyla verwendet werden
    string hgerg;  // hyla_gescheitert_erg
    int hversuzahl;
    FxStat capistat=init;// 1=wartend, 2=gesandt, 3=gescheitert, 4=fehlend (in spool keine Capi-Datei eingetragen oder die eingetragene gibts nicht)
    FxStat hylastat=init;// 1=wartend, 2=gesandt, 3=gescheitert, 4=fehlend (in spool keine hyla-Datei eingetragen oder die eingetragene gibts nicht)
  private:
  public:
      void archiviere(DB *My, paramcl *pmp, struct stat *entryp,uchar obgescheitert, FaxTyp ftyp, uchar *gel, int obverb, int oblog);
    int loeschecapi(int obverb, int oblog);
    int loeschehyla(paramcl *pmp,int obverb, int oblog);
    /*1*/fsfcl(string id, string npdf, string spdf, string telnr, unsigned prio, string capisd, int capids, string hylanr, int hdialsn, 
         uchar obcapi, uchar obhyla, string adressat,ulong pseiten):
         fxfcl(prio,npdf,spdf,pseiten), id(id), telnr(telnr), capisd(capisd), capids(capids), 
         hylanr(hylanr), hdialsn(hdialsn), fobcapi(obcapi), fobhyla(obhyla), adressat(adressat) {}
    /*2*/fsfcl(string id,string original): id(id), original(original) {}
    /*3*/fsfcl(string id, string capisd, string hylanr, string cspf): id(id), capisd(capisd), hylanr(hylanr), cspf(cspf) {}
    /*4*/fsfcl(string& hylanr): hylanr(hylanr) {}
    /*5*/fsfcl(string sendqgespfad, FxStat capistat): sendqgespfad(sendqgespfad), capistat(capistat) {}
    void setzcapistat(paramcl *pmp, struct stat *entrysendp);
    void capiwausgeb(stringstream *ausgp, string& maxctrials, uchar fuerlog=0, int obverb=0, int oblog=0,unsigned long faxord=0);
    void hylaausgeb(stringstream *ausgp, paramcl *pmp, int obsfehlt, uchar fuerlog=0, int obverb=0, uchar obzaehl=0, int oblog=0);
    int holcapiprot(int obverb);
}; // class fsfcl

extern const string s_true; // ="true";
extern const string s_dampand; // =" && ";
extern const string s_gz; // ="gz";

class paramcl // Programmparameter 
{
  private:
    double tstart, tende;
    svec modems;       // gefundene Modems
    size_t optslsz=0; // last opts.size()
    uchar modemgeaendert=0; // hmodem neu gesetzt
  public:
    string mpfad;  // meinpfad()
    string meinname; // base_name(meinpfad()) // argv[0] // 'autofax'
    string vaufr; // (vollaufruf) z.B. '/usr/bin/autofax -norf'
    string saufr; // (stummaufruf) 'autofax -norf'
    string instverz=""; // $HOME/autofax
//    cppSchluess *hconfp=0;
    schlArr hylconf;
    uchar hgelesen=0; // Protokolldatei war auslesbar
    static constexpr const char *moeglhvz[2]={"/var/spool/fax","var/spool/hylafax"};
    uchar obfcard=1;    // ob Fritzcard eingesteckt
    uchar obfcgeprueft=0; // ob schon geprueft, ob Fritzcard eingesteckt
    uchar obmodem=1;    // ob Modem angeschlossen
    uchar obmdgeprueft=0; // ob schon geprueft, ob Modem verfuegbar
    uchar obocrgeprueft=0; // ob ocrmypdf installiert ist
    const string spooltab="spool";
    const string altspool="altspool";
    const string udoctab="udoc";
    int obverb=0; // verbose
    int oblog=0;  // mehr Protokollieren
    uchar obvi=0;   // ob Konfigurationsdatei editiert werden soll
    uchar loef=0;   // loesche eine Fax-Datei
    uchar loew=0;  // loeschewaise in der Datenbank, aber nicht mehr real nachweisbare Dateien in der Datenbank loeschen
    uchar loea=0; // loesche alle wartenden Faxe und zugehoerige Dateieintraege
    uchar loee=0; // empfangene Dateien loeschen, die nicht verarbeitet werden koennen
    uchar kez=0;    // korrigiere Erfolgskennzeichen
    uchar bwv=0;    // bereinige Warteverzeichnis
    uchar anhl=0;    // autofax anhalten
    uchar lista=0;   // liste Archiv auf
    uchar listf=0;   // liste gescheiterte auf
    uchar listi=0;   // liste Eingegangene auf
    uchar listw=0;   // liste wartende auf
    string suchstr;  // Wortteil, nach dem in alten Faxen gesucht werden soll
    string dszahl="30"; // Datensatzzahl fuer Tabellenausgaben
    uchar logdateineu=0; // logdt vorher loeschen
    uchar hilfe=0;      // Hilfe anzeigen
    uchar zeigvers=0;  // Version anzeigen
		size_t faxord; // Ordinalzahl des Faxes unter allen anstehenden Faxen
		unsigned long geszahl=0;
    unsigned long ankzahl=0; // Zahl der angekommenen Faxe
    unsigned long dbzahl=0; // Zahl der ueberprueften Datenbankeintraege
    unsigned long wzahl=0;
    unsigned long ezahl=0;
    unsigned long gzahl=0;
    unsigned long fzahl=0;
    unsigned long weizahl=0; // Zahl der weiteren wartenden Faxe, die nicht in der Spooltabelle dieses Programms eingetragen sind
    uchar gleichziel; // faxe auch ohne Fax-Erfolg auf Zielverzeichnis abspeichern
    uchar obocri; // empfangene Faxe OCR unterziehen
    uchar obocra; // gesandte Bilder OCR unterziehen
    uchar obcapi=1; // ob ueberhaupt die Capisuite verwendet werden soll
    uchar obhyla=1; // ob ueberhaupt hylafax verwendet werden soll
    uchar konfobcapi; // ob obcapi in der Konfigurationsdatei eingestellt ist
    uchar konfobhyla; // ob obhyla in der Konfigurationsdatei eingestellt ist
    //    string hmodemstr; // Erkennung des Faxgeraetes nach /dev/tty, Standard ACM
    string hmodem;    // erkanntes und laufendes Modem ttyACM0
    //    string hmodname;  // ttyACM0
    uchar hylazuerst;  // ob ein Fax zuerst ueber Hylafax versucht werden soll zu faxen
    uchar rzf=0; // rueckzufragen
    string dbq; // Datenbank
    string cuser; // Linux-Benutzer fuer Capisuite, Samba
    string muser; // Benutzer fuer Mysql/MariaDB
    string mpwd;  // Passwort fuer Mysql/MariaDB
    DB* My=0;
    const string touta="outa"; // MariaDB-Tabelle fuer gesandte oder gescheiterte Faxe
    const string tudoc="udoc"; // MariaDB-Tabelle fuer gesandte oder gescheiterte Faxe
    const string tinca="inca"; // MariaDB-Tabelle fuer empfangene Faxe
    string cfaxconfdat; // /etc/capisuite/fax.conf oder /usr/local/etc/capisuite/fax.conf laut Handbuch
    string ccapiconfdat; // /etc/capisuite/capisuite.conf oder /usr/local/etc/capisuite/capisuite.conf laut Handbuch
    // Parameter aus /etc/capisuite/fax.conf:
    string spoolcapivz; // Verzeichnis der Capi-Spool-Dateien /var/spool/capisuite/
    string cfaxuservz;    // /var/spool/capisuite/users/
    string cfaxusersqvz;    // /var/spool/capisuite/users/<user>/sendq
    string nextdatei;  // /var/spool/capisuite/users/<user>/sendq/fax-nextnr
    string cfaxuserrcvz;    // /var/spool/capisuite/users/<user>/received
    string cdonevz; // Capisuite-Archiv: /var/spool/capisuite/done
    string cfailedvz; // Capisuite-Archiv der gescheiterten /var/spool/capisuite/failed
    string countrycode; // Landesvorwahl
    string citycode;    // Ortsvorwahl
    string msn;         // MSN fuer Fax
    string LongDistancePrefix; // Vorsatz fuer ausserorts
    string InternationalPrefix; // Vorsatz fuer ausserlandes
    string LocalIdentifier; // eigener Namen fuer Hylafax bis 10 Buchstaben
    string cFaxUeberschrift; // eigener Namen fuer Capisuite bis 20 Buchstaben
    string cklingelzahl; // Zahl der Klingeltoene, bis Capisuite einen Anruf annnimmt
    string hklingelzahl; // Zahl der Klingeltoene, bis Hylafax einen Anruf annnimmt
    string maxhdials;     // Zahl der Wahlversuche in Hylafax
		string maxcdials;    // Zahl der Wahlversuche in Capisuite
    uchar capizukonf=0; // capi zu konfigurieren
    uchar hylazukonf=0; // hyla zu konfigurieren
    uchar oblgschreib=0; // Konfigurationsdatei seitens der Sprache voraussichtlich schreiben
    uchar obkschreib=0; // Konfigurationsdatei schreiben
    uchar logdneu=0;    // Logdatei geaendert
    uchar logvneu=0;    // Logverzeichnis geaendert
    string varsphylavz; // Verzeichnis der Hyla-Spool-Dateien /var/spool/fax
    string xferfaxlog; // varsphylavz + "/etc/xferfaxlog"; 
    string faxgtpfad;   // /usr/lib/fax/faxgetty
    string hsendqvz; // /var/spool/fax/sendq
#ifdef _WIN32
    char cpt[255];
    DWORD dcpt;
#elif linux
    char cpt[MAXHOSTNAMELEN]; 
    size_t cptlen;
#endif
    string host="localhost";  // fuer MySQL/MariaDB
    string logdname; // Logdatei-Name ohne Pfad
    string logvz; // nur das Verzeichnis
    string loggespfad; // Gesamtpfad, auf den dann die in konsole.h verwiesene und oben definierte Variable logdt zeigt
                       // bei jeder Aenderung muss auch logdt neu gesetzt werden!
    string zufaxenvz;
    string wvz; // Warteverzeichnis
    string nvz; // Gescheitertenverzeichnis
    string empfvz; // Empfangsverzeichnis
    string cronminut; // Minuten fuer crontab; 0 = kein Crontab-Eintrag
    string maxcapiv; // maximale Versuchnr in Capi, bis Hyla versucht wird
    string maxhylav; // maixmale Versuchsnr in Hylafax, bis Capi versucht wird
    string langu; // Sprache (Anfangsbuchstabe)

//    cppSchluess *cgconfp; // Gesamtkonfiguration
    schlArr cgconf; // Gesamtkonfiguration
    //    size_t gcs; // dessen Groesse
    string sqlvz;  // Zahl der SQL-Befehle aus Vorgaben
    size_t sqlvzn=0; // Zahl der SQL-Befehle aus Vorgaben numerisch
//    cppSchluess *sqlconfvp=0; // SQL-Pointer aus Vorgaben
    schlArr sqlconfv;
    string sqlz;  // Zahl der SQL-Befehle
    size_t sqlzn=0; // Zahl der SQL-Befehle numerisch
//    cppSchluess *sqlconfp; // SQL-Pointer
    schlArr sqlconf; // SQL-Array

    zielmustercl *zmp; // Zielmusterzeiger
//    cppSchluess *zmconfp; // dessen Serialisierung
    schlArr zmconf; // dessen Serialisierung
    string zmz; // Zielmusterzahl
    size_t zmzn; // Zielmusterzahl numerisch
    zielmustercl *zmvp; // Zielmusterzeiger aus Vorgaben
    string zmvz; // Zielmusterzahl aus Vorgaben
    size_t zmvzn=0; // Zielmusterzahl numerisch aus Vorgaben

//    cppSchluess *capiconfp; // Capi-Konfiguration (fax.conf)
    schlArr cconf;  // capisuite.conf
    schlArr capiconf; // Capi-Konfiguration (fax.conf)
//    size_t ccs; // capiconf-confsize
    string konfdatname; // name der Konfigurationsdatei
    string anfaxstr, ancfaxstr, anhfaxstr; // 'an Fax', "an cFax", "an hFax"
    string anstr; // ' an '
    string undstr;  //  'und'
    string cmd; // string fuer command fuer Betriebssystembefehle
    vector<optioncl> opts;
    vector<argcl> argcmv; // class member vector
    servc *sfaxq=0, *shfaxd=0, *shylafaxd=0, *sfaxgetty=0, *scapisuite=0;
    string modconfdat; // hylafax-Konfigurationsdatei
    confdat *cfaxcp=0; // Zeiger auf ausgelesene /etc/capisuite/fax.conf

  private:
    void lgnzuw(); // in vorgaben, lieskonfein, getcommandl0, getcommandline, rueckfragen
    string neuerdateiname(const string& qpfad); // in DateienHerricht
    void WVZinDatenbank(vector<fxfcl> *fxvp); // in DateienHerricht
    string getzielvz(const string& datei); // in bereinigewv
    int setzegcp(const string& name, string *wert);
    void pruefcvz();
    void pruefsfftobmp();
    void setzhylastat(fsfcl *fsf, string *protdaktp, uchar *hyla_uverz_nrp, uchar startvznr,int *obsfehltp=0, int obverb=0, int oblog=0);
    void konfcapi();
    int xferlog(fsfcl *fsfp, int obverb=0, int oblog=0,
        string *totpages=0, string *ntries=0, string *totdials=0, string *tottries=0, string *maxtries=0);
    void richtcapiher();
    void setzmodconfd();
    void setzzielmuster(confdat& afconf);
    void setzsql(confdat& afconf);
    int pruefinstv();
    int kompilbase(const string& was,const string& endg);
    int kompiliere(const string& was,const string& endg, const string& vorcfg=s_true,const string& cfgbismake=s_dampand);
    void bereinigecapi();
	  int zupdf(string& quell, string& ziel, ulong *pseitenp=0, int obocr=1, int loeschen=1, int obverb=0, int oblog=0); // 0=Erfolg
		int holtif(string& datei,ulong *seitenp=0,struct tm *tmp=0,struct stat *elogp=0,
		           string *absdrp=0,string *tsidp=0,string *calleridp=0,string *devnamep=0,int obverb=0,int oblog=0);
	public:
    paramcl(int argc,char** argv);
    ~paramcl();
		void pruefunpaper();
    void pruefggfmehrfach();
    void nextnum();
    string stdfaxnr(const string& faxnr);
    void logvorgaben();
    void getcommandl0();
    void pruefmodem();
		void setzfaxgtpfad();
		void pruefisdn();
    void liescapiconf();
    void VorgbAllg(); // allgemeine Vorgaben
    #ifdef autofaxcpp
    void VorgbSpeziell() __attribute__((weak)); // implementationsspezifische Vorgaben (aber nur Quellcodeaenderung aenderbar, Modul vorgaben.cpp)
    #else
    void VorgbSpeziell(); // implementationsspezifische Vorgaben (aber nur Quellcodeaenderung aenderbar, Modul vorgaben.cpp)
    #endif
    void lieskonfein();
    int  getcommandline();
    void rueckfragen();
    int setzhylavz(); // sucht das Hylaverzeichnis und setzt varsphylavz darauf, return 0, wenn nicht gefunden dann varsphylavz="", return 1
    void verzeichnisse();
    void pruefcron();
    void pruefsamba();
    int  initDB();
    int  pruefDB(const string& db);

    void korrerfolgszeichen();
    void bereinigewv();
    void anhalten();
    void tu_lista(const string& oberfolg);
    void tu_listi();
    void suchestr();
    int pruefsoffice(uchar mitloe=0);
    int pruefconvert();
    int pruefocr();
    void DateienHerricht();
    void clieskonf();
    void capisv(int obverb,int oblog);
    int pruefcapi();
    void holvongithub(string datei);
    void hliesconf();
    void hconfigtty();
    int cservice();
    int hservice_faxq_hfaxd();
    void hylasv1(int obverb,int oblog);
    void hylasv2(hyinst hyinstart, int obverb,int oblog);
//    int hservice_faxgetty();
    int pruefhyla();
    int  loeschefax(int obverb, int oblog);
    int  loeschewaise(int obverb, int oblog);
    int  loescheallewartende(int obverb, int oblog);
    void faxealle();
    void untersuchespool(uchar mitupd=1);
    void zeigweitere();
    void sammlecapi(vector<fsfcl> *fsfvp);
    void sammlehyla(vector<fsfcl> *fsfvp);
    void empfarch();
    void schlussanzeige();
    void autofkonfschreib();
    void zeigkonf();
}; // class paramcl
