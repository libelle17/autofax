enum FaxTyp:uchar {capi=1,hyla};
enum FxStat:uchar {init/*0*/,gestrichen,schwebend,wartend/*3*/,blockiert/*4*/,bereit/*5*/,verarb/*6*/,gesandt/*7*/,gescheitert/*8*/,fehlend,woasined};
enum hyinst {keineh,hysrc,hypak,hyppk}; // hyla source, hyla Paket, hylaplus Paket

class zielmustercl; // fuer die Verteilung der erfolgreich gefaxten Dateien auf verschiedene Dateien
class fxfcl; // Faxfile
class fsfcl; // Faxsendfile
class paramcl; // Programmparameter
void useruucp(const string& huser, int obverb,int oblog);
string zielname(const string& qdatei, const string& zielvz,uchar wieweiterzaehl=0, string* zieldatei=0, int obverb=0, int oblog=0);
string zielname(const string& qdatei, zielmustercl *zmp,uchar wieweiterzaehl=0, string* zieldatei=0, int obverb=0, int oblog=0);
void dorename(const string& quelle, const string& ziel, const string& cuser=nix, uint *vfehler=0, int obverb=0, int oblog=0);
string verschiebe(const string& qdatei, const string& zielvz, const string& cuser=nix,uint *vfehler=0, uchar wieweiterzaehl=0, int obverb=0,int oblog=0);
void verschiebe(const string& qdatei, zielmustercl *zmp, const string& cuser=nix, uint *vfehler=0, uchar wieweiterzaehl=0, int obverb=0, int oblog=0);
string kopiere(const string& qdatei, const string& zieldp, uint *kfehler, uchar wieweiterzaehl, int obverb=0,int oblog=0);
string kopiere(const string& qdatei, zielmustercl *zmp, uint *kfehler, uchar wieweiterzaehl, int obverb=0, int oblog=0);
void prueffuncgettel3(DB *Myp, const string& usr, const string& host, int obverb, int oblog);
void pruefstdfaxnr(DB *Myp, const string& usr, const string& host, int obverb, int oblog);
void faxemitC(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, paramcl *pmp, int obverb, int oblog);
void faxemitH(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, paramcl *pmp, int obverb, int oblog);
int pruefcapi(paramcl *pmp, int obverb, int oblog);
void kuerzevtz(string *vzp);
pid_t PIDausName(const char* PName, uchar klgr, uchar exakt, int obverb, int oblog);
void getSender(paramcl *pmp,const string& faxnr, string *getnamep, string *bsnamep,int obverb=0,int oblog=0);
void hfaxsetup(paramcl *pmp,int obverb=0, int oblog=0);
void hconfig(paramcl *pmp,int obverb=0, int oblog=0);
const string& pruefspool(DB *My,const string& spooltab, const string& altspool, int obverb, int oblog, uchar direkt=0);
void pruefouttab(DB *My, const string& touta, int obverb, int oblog, uchar direkt=0);
void pruefudoc(DB *My, const string& tudoc, int obverb, int oblog, uchar direkt=0);
void pruefinctab(DB *My, const string& tinca, int obverb, int oblog, uchar direkt=0);
void kuerzevtz(string *vzp);
void pruefrules(int obverb, int oblog);
void pruefblack(int obverb, int oblog);
void pruefmodcron(int obverb, int oblog);

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
    int kompilier(uchar obext=1);
    int setzemuster(const string& vmuster,uchar obext=1);
    const string& holmuster();
    int obmusterleer();
}; // class zielmustercl

class urfxcl // urspruengliche Dateidaten vor Aufteilung an verschiedene Faxadressaten
{
 public:
    string teil;
    string ur;
    unsigned prio; // Prioritaet der Fax-Programme: 0 = capi und 0 = hyla per Konfigurationsdatei, 1= capi und 2= hyla per Faxdateiname
    urfxcl(const string& teil, string& ur,unsigned prio): teil(teil), ur(ur), prio(prio) {}
};

class fxfcl // Faxfile
{
  public:
    string npdf; // nicht-PDF
    string spdf; // schon-PDF
    string ur;   // urspruenglicher Dateinamen
    unsigned prio; // Prioritaet der Fax-Programme: 0 = capi und 0 = hyla per Konfigurationsdatei, 1= capi und 2= hyla per Faxdateiname
		ulong pseiten; // PDF-Seitenzahl
    fxfcl(const string& npdf,const string& spdf,const string& ur,unsigned prio): npdf(npdf),spdf(spdf),ur(ur),prio(prio),pseiten(0) {}
    // nur fuer Initialisierung in fsfcl, Konstruktur /*1*/, nur fuer faxealle
    fxfcl(unsigned prio, const string& npdf,const string& spdf,ulong pseiten): npdf(npdf),spdf(spdf),prio(prio),pseiten(pseiten) {}
    fxfcl(const string& spdf,const string& ur,unsigned prio): npdf(""),spdf(spdf),prio(prio),pseiten(0) {}
    fxfcl() {}
};

class fsfcl : public fxfcl // Faxsendfile
{
  public:
    string id;   // id in spooltab
    string telnr;    // Telnr. des Adressaten
    string capisd; // capispooldatei
    int capids;  //capidials
    string hylanr; // hylanr
		string protdakt; // z.B. /var/spool/hylafax/doneq/q9902
    int hdialsn; // hyladials
    uchar fobcapi; // ob es jetzt mit Capi weggefaxt werden muss
    uchar fobhyla; // ob es jetzt mit Hyla weggefaxt werden muss
    string adressat; // Name des Adressaten aus Faxdatei
		string idalt; // id in altspool
    string original; // base_name(spdf)
    string origvu;   // base_name(npdf)
    string idudoc;   // id des urspruenglichen Dateinamens in tabelle udoc
    string cspf;     // capispoolpfad
    string cdd;      // cdateidatum
    string cdials;   // capidials
    string ctries; // parameter aus capiprot
    string starttime; // parameter aus capiprot
    string dialstring; // parameter aus capiprot
    string hstate="0"; // Statuszahl ("state" in man sendq)
    string hstatus; // Textbeschreibung des letztes Fehlschlags
    string hstatuscode; // in xferfaxlog nicht gefunden
		time_t tts=0;
		time_t killtime=0;
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
    /*1*/fsfcl(const string id, const string npdf, const string spdf, const string telnr, unsigned prio, const string capisd, int capids, 
		           const string hylanr, int hdialsn, uchar obcapi, uchar obhyla, const string adressat, ulong pseiten, string idalt):
         fxfcl(prio,npdf,spdf,pseiten), id(id), telnr(telnr), capisd(capisd), capids(capids), 
         hylanr(hylanr), hdialsn(hdialsn), fobcapi(obcapi), fobhyla(obhyla), adressat(adressat),idalt(idalt) {}
    /*2*/fsfcl(const string id,const string original): id(id), original(original) {}
    /*3*/fsfcl(const string id, const string capisd, const string hylanr, string const cspf): id(id), capisd(capisd), hylanr(hylanr), cspf(cspf) {}
    /*4*/fsfcl(const string& hylanr): hylanr(hylanr) {}
    /*5*/fsfcl(const string sendqgespfad, FxStat capistat): sendqgespfad(sendqgespfad), capistat(capistat) {}
    void setzcapistat(paramcl *pmp, struct stat *entrysendp);
    void capiausgeb(stringstream *ausgp, string& maxctrials, uchar fuerlog=0, int obverb=0, int oblog=0,unsigned long faxord=0);
    void hylaausgeb(stringstream *ausgp, paramcl *pmp, int obsfehlt, uchar fuerlog=0, int obverb=0, uchar obzaehl=0, int oblog=0);
    int holcapiprot(int obverb);
}; // class fsfcl

extern const string s_true; // ="true";
extern const string s_dampand; // =" && ";
extern const string s_gz; // ="gz";
extern const string defvors; // ="https://github.com/libelle17/"
extern const string defnachs; // ="/archive/master.tar.gz"

class paramcl // Programmparameter 
{
  private:
    double tstart, tende;
    svec modems;       // gefundene Modems
    size_t optslsz=0; // last opts.size()
    uchar modemgeaendert=0; // hmodem neu gesetzt
  public:
	  string cl; // comanndline
    string mpfad;  // meinpfad()
    string meinname; // base_name(meinpfad()) // argv[0] // 'autofax'
    string vaufr; // (vollaufruf) z.B. '/usr/bin/autofax -norf'
    string saufr; // (stummaufruf) 'autofax -norf'
		string zsaufr; // zitiert saufr (in sed)
//    string instvz; // $HOME/autofax
//    cppSchluess *hconfp=0;
    schlArr hylconf;
    uchar hgelesen=0; // Protokolldatei war auslesbar
    static constexpr const char *moeglhvz[2]={"/var/spool/fax","var/spool/hylafax"};
		string huser="uucp"; // "uucp" oder "fax"
    uchar obfcard=1;    // ob Fritzcard eingesteckt
    uchar obfcgeprueft=0; // ob schon geprueft, ob Fritzcard eingesteckt
    uchar obmodem=1;    // ob Modem angeschlossen
    uchar obmdgeprueft=0; // ob schon geprueft, ob Modem verfuegbar
    uchar obocrgeprueft=0; // ob ocrmypdf installiert ist
    const string spooltab="spool";
    const string altspool="altspool"; // Historie der Spooltabelle
    const string udoctab="udoc";
    int obverb=0; // verbose
    int oblog=0;  // mehr Protokollieren
    uchar obvi=0;   // ob Konfigurationsdatei editiert werden soll
    uchar loef=0;   // loesche eine Fax-Datei
    uchar loew=0;  // loeschewaise in der Datenbank, aber nicht mehr real nachweisbare Dateien in der Datenbank loeschen
    uchar loea=0; // loesche alle wartenden Faxe und zugehoerige Dateieintraege
    uchar loee=0; // empfangene Dateien loeschen, die nicht verarbeitet werden koennen
		uchar erneut=0;  // empfangenes Fax erneut bereitstellen
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
    uchar obcapi=1; // ob ueberhaupt die Capisuite verwendet werden soll, gesetzt in: pruefisdn(), lieskonfein(), rueckfragen(), getcommandline(), main()
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
		string cempfavz; //  /var/spool/capisuite/autofaxarch/
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
    string varsphylavz; // Verzeichnis der Hyla-Spool-Dateien /var/spool/hylafax oder /var/spool/fax
		string hempfavz;    // var/spool/(hyla)fax/autofaxarch
		string xferfaxlog; // varsphylavz + "/etc/xferfaxlog"; 
		string faxqpfad,hfaxdpfad; // /usr/local/sbin/faxq, /usr/local/sbin/hfaxq
		string faxgtpfad;   // /usr/lib/fax/faxgetty oder /usr/local/sbin/faxgetty
    string hsendqvz; // /var/spool/hylafax/sendq
		unsigned long aufrufe=0; // Zahl der bisherigen Programmaufrufe
		struct tm laufrtag={0}; // Tag des letztes Aufrufs
		unsigned long tagesaufr=0; // Zahl der bisherigen Programmaufrufe heute
		unsigned long monatsaufr=0; // Zahl der bisherigen Programmaufrufe heute
#ifdef _WIN32
    char cpt[255];
    DWORD dcpt;
#elif linux
    char cpt[MAXHOSTNAMELEN]; 
    size_t cptlen;
#endif
    string host="localhost";  // fuer MySQL/MariaDB
    string logdname; // Logdatei-Name ohne Pfad autofax.log
    string logvz; // nur das Verzeichnis /var/log
    string loggespfad; // Gesamtpfad, auf den dann die in kons.h verwiesene und oben definierte Variable logdt zeigt
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
		uchar keineverarbeitung=0;
		uchar cmeingegeben=0;
		vector<argcl> argcmv; // class member vector
    servc *sfaxq=0, *shfaxd=0, *shylafaxd=0, *sfaxgetty=0, *scapis=0;
    string modconfdat; // hylafax-Konfigurationsdatei, z.B. /var/spool/hylafax/etc/config.ttyACM0
    confdat *cfaxcp=0; // Zeiger auf ausgelesene /etc/capisuite/fax.conf
		string virtvz; //	instvz+"/ocrv";
	  string ocrmp; //	virtvz+"/bin/ocrmypdf";
		string vorcm; // Vor-Cron-Minuten

  private:
    void lgnzuw(); // in vorgaben, lieskonfein, getcommandl0, getcommandline, rueckfragen
    string neuerdateiname(const string& qpfad); // in DateienHerricht
    void WVZinDatenbank(vector<fxfcl> *fxvp); // in DateienHerricht
    string getzielvz(const string& datei); // in bereinigewv
    int setzegcp(const string& name, string *wert);
    void pruefcvz();
    void pruefsfftobmp();
    void setzhylastat(fsfcl *fsf, uchar *hyla_uverz_nrp, uchar startvznr,int *obsfehltp=0, 
				struct stat *est=0);
		void konfcapi();
    int xferlog(fsfcl *fsfp, string *totpages=0, string *ntries=0, string *totdials=0, string *tottries=0, string *maxtries=0);
    void richtcapiher();
    void setzmodconfd();
    void setzzielmuster(confdat& afconf);
    void setzsql(confdat& afconf);
    int pruefinstv();
    int kompilbase(const string& was,const string& endg);
    int kompiliere(const string& was,const string& endg,const string& vorcfg=nix,const string& cfgbismake=s_dampand);
		int kompilfort(const string& was,const string& vorcfg=nix,const string& cfgbismake=s_dampand,uchar ohneconf=0);
    void bereinigecapi();
	  int zupdf(const string* quell, const string& ziel, ulong *pseitenp=0, int obocr=1, int loeschen=1); // 0=Erfolg
		int holtif(const string& datei,ulong *seitenp=0,struct tm *tmp=0,struct stat *elogp=0,
		           string *absdrp=0,string *tsidp=0,string *calleridp=0,string *devnamep=0);
		void setztmpcron();
		void pruefmodcron();
		void pruefunpaper();
    int pruefocr();
		void unpaperfuercron();
		void empfhyla(const string& ganz,uchar indb=1,uchar mitversch=1);
		void empfcapi(const string& stamm,uchar indb=1,uchar mitversch=1);
	public:
		int Log(const string& text,const bool oberr=0,const short klobverb=0);
    paramcl(int argc,char** argv);
    ~paramcl();
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

    void bereinigewv();
    void anhalten();
    void tu_lista(const string& oberfolg,const string& submids=nix);
    void tu_listi();
    void suchestr();
    int pruefsoffice(uchar mitloe=0);
    int pruefconvert();
    void DateienHerricht();
    void clieskonf();
    void capisv();
    int pruefcapi();
		int holvomnetz(const string& datei,const string& vors=defvors,const string& nachs=defnachs);
    void hliesconf();
    void hconfigtty();
    int cservice();
    int hservice_faxq_hfaxd();
    void hylasv1();
    void hylasv2(hyinst hyinstart);
//    int hservice_faxgetty();
    int pruefhyla();
    int  loeschefax();
		int  empferneut();
    int  loeschewaise();
    int  loescheallewartende();
    void faxealle();
    void untersuchespool(uchar mitupd=1);
    void zeigweitere();
    void zeigkonf();
		void zeigdienste();
    void sammlecapi(vector<fsfcl> *fsfvp);
    void sammlehyla(vector<fsfcl> *fsfvp);
    void korrigierecapi(unsigned tage=90);
    void korrigierehyla(unsigned tage=90);
    void empfarch();
		void zeigueberschrift();
		void schlussanzeige();
    void autofkonfschreib();
}; // class paramcl
