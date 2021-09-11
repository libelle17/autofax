// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
// sed -n '/\/\/α/,/\/\/ω/p;/\/\/ω/a\\' test
// sed -n '/\/\/α/,/\/\/ω/p' test
// aktuelle Programmversion
const double& versnr= //α
#include "versdt"
;
#include "kons.h"
#include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "autofax.h"
#include <fcntl.h> // fuer fd_reopen, O_RDONLY usw.
#include <termios.h> // fuer tcgetattr, termios
#include <qpdf/QPDF.hh> // fuer die Seitenzahl von PDF-Dateien
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]=
{
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	// T_virtpruefweiteres
	{"virtpruefweiteres()","virtcheckmore()"},
	// T_virtmacherkl_Tx_lgn
	{"pvirtmacherkl, Tx.lgn: ","pvirtmakeexpl, Tx.lgn: "},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_st_k
	{"st","st"},
	// T_stop_l
	{"stop","stop"},
	// T_DPROG_anhalten
	{DPROG " anhalten","stop " DPROG},
	// T_anhalten
	{"anhalten()","stop()"},
	// T_Cron_Aufruf_von
	{"Cron-Aufruf von '","cron call of '"},
	// T_gestoppt
	{"' gestoppt.","' stopped."},
	// T_n_k
	{"n","n"},
	// T_dszahl_l
	{"dszahl","reccount"},
	// T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
	{"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <no> instead of"},
	// T_Datenbank_nicht_initialisierbar_breche_ab
	{"Datenbank nicht initialisierbar, breche ab","database init failed, stopping"},
	// T_pvirtnachrueckfragen,
	{"pvirtnachrueckfragen()","pvirtbeforecheckmultiple()"},
	// T_pvirtfuehraus,
	{"pvirtfuehraus()","pvirtexecute()"},
	// T_in_pvirtfuehraus_pidw,
	{"in pvirtfuehraus(), pidw","in pvirtexecute(), pidw"},
	// T_virttesterg,
	{"virttesterg()","virtcheckresult()"},
	// T_virtzeigversion,
	{"virtzeigversion()","virtshowversion()"},
	// T_virtzeigueberschrift, 
	{"virtzeigueberschrift()","virtshowheadline()"},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_SQL_Befehl_Nr
	{"SQL-Befehl Nr. ","SQL-command no. "},
	// T_faxnr_wird_ersetzt_mit_der_Faxnr
	{" (bitte ggf. SQL-Befehl mit 2 Ergebnisfeldern, '&&faxnr&&' wird ersetzt mit der Faxnr)",
		" (if wanted type sql-command with 2 result fields, '&&faxnr&&' will be replaces with the fax-no.)"},
	// T_Strich_ist_SQL_Befehl_loeschen_faxnr_wird_ersetzt_mit_der_Faxnr
	{" ('-'=SQL-Befehl loeschen, 2 Ergebnisfelder, '&&faxnr&&' wird ersetzt mit der Faxnr, s.man -Lde " DPROG ")",
		" ('-'=delete this sql command, 2 result fields, '&&faxnr&&' will be replaces with the fax-no., see man " DPROG ")"},
	// T_In
	{"In '","In '"},
	// T_keine_Datenbank_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben
	{"' keine Datenbank gefunden. Wollen Sie den SQL-Befehl neu eingeben?",
		"' no database found. Do You want to reenter the sql command?"},
	// T_Datenbank
	{"Datenbank '","Database '"},
	// T_nicht_ermittelbar_Wollen_Sie_den_SQL_Befehl_neu_eingeben
	{"' nicht ermittelbar. Wollen Sie den SQL-Befehl neu eingeben?","' not found. Do You want to reenter the sql command?"},
	// T_keinmal_faxnr_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben
	{"' keinmal '&&faxnr&&' gefunden. Wollen Sie den SQL-Befehl neu eingeben?",
		"' no occurance of '&&faxnr&&' found. Do You want to reenter the sql command?"},
	// T_koennte_ein_SQL_Fehler_sein_Wollen_Sie_den_SQL_Befehl_neu_eingeben
	{"' koennte ein SQL-Fehler sein. Wollen Sie den SQL-Befehl neu eingeben?",
		"' could be an sql error. Do You want to reenter the sql command?"},
	// T_Wolle_Sie_noch_einen_SQL_Befehl_eingeben,
	{"Wollen Sie noch einen SQL-Befehl eingeben?","Do You want to enter another sql command?"},
	// T_zum_Streichen_Strich_eingeben
	{" (zum Streichen '-' eingeben)"," (to delete enter '-')"},
// T_beim_letzten_fuer_alle_Uebrigen_nichts_eingeben
	{" (beim letzten fuer alle Uebrigen nichts eingeben)"," (for the last for all the rest enter nothing)"},
	// T_Zielverzeichnis_Nr
	{"Zielverzeichnis Nr. ","Target directory no. "},
	// T_SQL_Befehl
	{"SQL-Befehl: ","SQL-Command: "},
	// T_Zielmuster_Nr
	{"Zielmuster Nr. ","Target pattern no. "},
	// T_Ziel_Nr
	{"Ziel Nr. ","Target no. "},
	// T_Zielmuster
	{"Zielmuster","Target pattern"},
	// T_Ziel,
	{"Ziel ","Target "},
	// T_an_Fax
	{"an Fax","to fax"},
	// T_an_cFax,
	{"an cFax","to cfax"},
	// T_an_hFax
	{"an hFax","to hfax"},
	// T_an_fFax
	{"an fFax","to ffax"},
	// T_an,
	{" an "," to "},
	// T_und
	{"und","and"},
	// T_an_Mail
	{"an Mail","to mail"},
	// T_klar_an
	{"klar an","plain to"},
	// T_liescapiconf
	{"liescapiconf()","readcapiconf()"},
	// T_MeiEinrichtung
	{"MeiEinrichtung","MyInstitution"},
	// T_Mei_FaxUeberschrift
	{"Mei FaxUeberschrift","My fax headline"},
	// T_Der_regulaere_Ausdruck
	{"Der regulaere Ausdruck '","The regular expression '"},
	// T_konnte_nicht_kompiliert_werden_Fehler
	{"' konnte nicht kompiliert werden, Fehler: ","could not be compiled, error: "},
	// T_Zufaxen
	{"Zufaxen","TobeFaxed"},
	// T_zufaxen
	{"zufaxen","tobefaxed"},
	// T_Warteauffax
	{"Warteauffax","WaitingFaxes"},
	// T_warteauffax,
	{"warteauffax","waitingfaxes"},
	// T_Nichtgefaxt
	{"Nichtgefaxt","NotFaxed"},
	// T_nichtgefaxt,
	{"nichtgefaxt","notfaxed"},
	// T_empfvz
	{"empfvz","recvdir"},
	// T_zvz_k
	{"zvz","tdr"},
	// T_zufaxenvz_l
	{"zufaxenvz","tofaxdir"},
	// T_faxt_die_Dateien_aus_pfad_anstatt_aus
	{"faxt die Dateien aus <pfad> anstatt aus","faxes the files from <path> instead of"},
	// T_wvz_k
	{"wvz","wdr"},
	// T_wartevz_l
	{"wartevz","waitdir"},
	// T_Dateien_warten_in_pfad_anstatt
	{"Dateien warten in <pfad> anstatt","files are waiting in <path> instead of"},
	// T_ngvz_k
	{"ngvz","ndr"},
	// T_nichtgefaxtvz_l
	{"nichtgefaxtvz","notfaxeddir"},
	// T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in
	{"Gescheiterte Faxe werden hier gesammelt anstatt in","Failed Faxes are collected here and not in"}, 
	// T_evz_k
	{"evz","rdr"},
	// T_empfvz_l
	{"empfvz","receiveddir"},
	// T_Empfangsverzeichnis_fuer_Faxempfang
	{"Empfangsverzeichnis fuer Faxempfang","directory for recieved faxes"},
	// T_fbox_k
	{"fbox","fbox"},
	// T_fboxs_k
	{"fboxs","fboxs"},
	// T_fboxe_k
	{"fboxe","fboxr"},
	// T_obfbox_l
	{"obfbox","takefbox"},
	// T_obfboxs_l
	{"obfboxs","takefboxs"},
	// T_obfboxe_l
	{"obfboxe","takefboxr"},
	// T_Fritzbox_verwenden
	{"Fritzbox verwenden","use fritzbox"},
	// T_Fritzbox_zum_Senden_verwenden
	{"Fritzbox zum Senden verwenden","use fritzbox for receiving"},
	// T_Fritzbox_zum_Empfang_verwenden
	{"Fritzbox zum Empfang verwenden","use fritzbox for sending"},
	// T_fbankvz_k
	{"fbvz","fbdr"},
	// T_fbankvz_l
	{"fritzboxvz","fritzboxdir"},
	// T_Ankunftsverzeichnis_der_Fritzbox_ueber_CIFS
	{"Ankunftsverzeichnis der Fritzbox (ueber CIFS)","receiving directory of the fritzbox (via CIFS)"},
	// T_farchvz_k
	{"favz","favz"},
	// T_farchvz_l
	{"farchvz","farchvz"},
	// T_Archivverzeichnis_der_Fritzbox
	{"Archivverzeichnis der Fritzbox","archive directory of the fritzbox"},
	// T_capi_k
	{"capi","capi"},
	// T_capis_k
	{"capis","capis"},
	// T_capie_k
	{"capie","capir"},
	// T_obcapi_l
	{"obcapi","takecapi"},
	// T_obcapis_l
	{"obcapis","takecapis"},
	// T_obcapie_l
	{"obcapie","takecapir"},
	// T_Capisuite_verwenden 
	{"Capisuite verwenden","use capisuite"},
	// T_Capisuite_zum_Senden_verwenden 
	{"Capisuite zum Senden verwenden","use capisuite for sending"},
	// T_Capisuite_zum_Empfang_verwenden 
	{"Capisuite zum Empfang verwenden","use capisuite for receiving"},
	// T_hyla_k
	{"hyla","hyla"},
	// T_hylas_k
	{"hylas","hylas"},
	// T_hylae_k
	{"hylae","hylar"},
	// T_obhyla_l
	{"obhyla","takehyla"},
	// T_obhylas_l
	{"obhylas","takehylas"},
	// T_obhylae_l
	{"obhylae","takehylar"},
	// T_hylafax_verwenden
	{"Hylafax verwenden","use hylafax"},
	// T_hylafax_zum_Senden_verwenden 
	{"Hylafax zum Senden verwenden","use hylafax for sending "},
	// T_hylafax_zum_Empfang_verwenden 
	{"Hylafax zum Empfang verwenden","use hylafax for receiving"},
	// T_hz_k,
	{"hz","hf"},
	// T_hylazuerst_l,
	{"hylazuerst","hylafirst"},
	// T_versuche_faxe_zuerst_ueber_Hylafax_wegzuschicken,
	{"versuche faxe zuerst ueber Hylafax wegzuschicken","trying to send faxes first via hylafax"},
	// T_mod_k
	{"mod","mod"},
	// T_hmodem_l
	{"hmodem","hmodem"},
	// T_Fuer_Hylafax_verwendetes_Modem
	{"Fuer Hylafax verwendetes Modem, anstatt ","Modem used for hylafax, instead of "},
	// T_cz_k
	{"cz","fc"},
	// T_capizuerst_l
	{"capizuerst","firstcapi"},
	// T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken
	{"versuche faxe zuerst ueber Capisuite wegzuschicken","try to send faxes primarily via capisuite"},
	// T_mc_k
	{"mc","mc"},
	// T_maxcapiv_l
	{"maxcapiv","maxcapitries"},
	// T_nach_zahl_Versuchen_Capisuite_wird_andere_Methode_versucht
	{"nach <zahl> Versuchen Capisuite wird andere Methode versucht, anstatt nach","try Hylafax after <no> tries of other method instead of"}, 
	// T_mh_k
	{"mh","mh"},
	// T_maxhylav_l
	{"maxhylav","maxhylatries"},
	// T_nach_zahl_Versuchen_Hylafax_wird_andere_Methode_verwendet
	{"nach <zahl> Versuchen Hylafax wird andere Methode versucht, anstatt nach","try other method after <no> tries of fbfax"},
	//	T_nach_zahl_Versuchen_fbfax_wird_andere_Methode_verwendet
	{"nach <zahl> Versuchen fbfax wird andere Methode versucht, anstatt nach","try other method after <no> tries of fbfax"},
	// T_mf_k,
	{"mf","mf"},
	// T_maxfbfxv_l,
	{"maxfbfxv","maxfbfaxtries"},
	// T_cuser_k
	{"cuser","cuser"},
	// T_cuser_l
	{"cuser","cuser"},
	// T_verwendet_fuer_Capisuite_Samba_den_Linux_Benutzer_string_anstatt
	{"verwendet fuer Capisuite und/oder Samba den Linux-Benutzer <string> anstatt", "takes the linux user <string> for capisuite and/or samba instead of"},
	// T_ckzl_k
	{"ckzl","crct"},
	// T_cklingelzahl_l
	{"cklingelzahl","cringcount"},
	// T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt
	{"Zahl der Klingeltoene, bis Capisuite den Anruf annimmt, anstatt","No. of bell rings until Capisuite accepts the call, instead of"},
	// T_hkzl_k
	{"hkzl","hrct"},
	// T_hklingelzahl_l
	{"hklingelzahl","hringcount"},
	// T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt
	{"Zahl der Klingeltoene, bis Hylafax den Anruf annimmt, anstatt","No. of bell rings until hylafaxs accepts the call, instead of"},
	// T_hintv_k
	{"hintv","hintv"},
	// T_hintervall_l
	{"hintervall","hinterval"},
	// T_Abstand_in_Sekunden_nach_Besetzt_bis_Hylafax_erneut_waehlt
	{"Abstand in Sekunden nach besetzt, bis hylafax erneut waehlt","interval in seconds after busy, until hylafax dials again"},
	// T_Abstand_in_Sekunden_nach_Besetzt_bis_Hylafax_erneut_waehlt_anstatt
	{"Abstand in Sekunden nach besetzt, bis hylafax erneut waehlt anstatt","interval in seconds after busy, until hylafax dials again instead of"},
	// T_md_k
	{"hmw","hmd"},
	// T_maxdials_l
	{"hmaxwahlvers","hmaxdials"},
	// T_Zahl_der_Wahlversuche_in_Hylafax
	{"Zahl der Wahlversuche in Hylafax, anstatt ","No of dialing retries in hylafax, instead of  "},
	// T_gz_k
	{"gz","it"},
	// T_gleichziel_l
	{"gleichziel","immediatelytarget"},
	// T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert
	{"Faxe werden auch ohne Faxerfolg ins Zielverzeichnis kopiert","copy faxes into target directory irrespective of faxing success"},
	// T_ocri_k
	{"ocre","ocri"},
	// T_ocri_l
	{"ocre","ocri"},
	// T_Text_aus_empfangenen_Faxen_wird_ermittelt
	{"Text aus empfangenen Faxen wird ermittelt","Text from received faxes will be filtered"},
	// T_ocra_k
	{"ocra","ocro"},
	// T_ocra_l
	{"ocra","ocro"},
	// T_Text_aus_gesandten_Bildern_wird_ermittelt
	{"Text aus gesandten Bildern wird ermittelt","Text from sent pictures will be filtered"},
	// T_afs_k
	{"afs","tfs"},
	// T_ams_k
	{"ams","tms"},
	// T_kams_k
	{"kams","ptms"},
	// T_anfaxstr_l
	{"anfaxstr","tofaxstr"},
	// T_anmailstr_l
	{"anmailstr","tomailstr"},
	// T_klaranmailstr_l
	{"klaranmailstr","plaintomailstr"},
	// T_mv_k,
	{"mv","mf"},
	// T_mailvon_l,
	{"mailvon","mailfrom"},
	// T_smtpadr_k,
	{"sma","sma"},
	// T_smtpadr_l,
	{"smtpadr","smtpaddr"},
	// T_portnr_k,
	{"pnr","pno"},
	// T_portnr_l,
	{"portnr","portno"},
	// T_smtpusr_k,
	{"smb","smu"},
	// T_smtpusr_l,
	{"smtpben","smtpusr"},
	// T_smtppwd_k,
	{"smp","smp"},
	// T_smtppwd_l,
	{"smtppwt","smtppwd"},
	// T_Absender_mailadresse,
	{"Absender-Mailadresse","mail address of the sender"},
	// T_als_Absender_zu_verwendende_Mailadresse,
	{"als Absender zu verwendende Mailadresse","mail address used as sender"},
	// T_smtp_Adresse,
	{"smtp-Adresse","smtp address"},
	// T_smtp_Adresse_ohne_port,
	{"smtp-Adresse ohne Port","smtp address without port"},
	// T_port_Nummer,
	{"Port-Nummer","port number"},
	// T_Port_Nummer,
	{"Port-Nummer","port number"},
	// T_smtp_usr,
	{"SMTP-Benutzer","smtp user"},
	// T_Smtp_usr,
	{"SMTP-Benutzer","smtp user"},
	// T_smtp_pwd,
	{"SMTP-Passwort","smtp password"},
	// T_Smtp_Pwd,
	{"SMTP-Passwort","smtp password"},
	// T_mt_k,
	{"mt","mt"},
	// T_mailtit_l,
	{"mailtitel","mailtitle"},
	// T_mailtitle,
	{"Mailtitel","mail title"},
	// T_Mailtitle,
	{"Mailtitel","mail title"},
	// T_mb_k,
	{"mb","mb"},
	// T_mailbod_l,
	{"mailbody","mailbody"},
	// T_mailbody,
	{"Mailtext","mail body"},
	// T_Mailbody,
	{"Mailtext","mail body"},
	// T_faxnr_wird_hinter_string_erwartet_statt_hinter
	{"faxnr wird hinter <string> erwartet statt hinter","the fax number will be expected after <string> instead of"},
	// T_mailadresse_wird_hinter_string_erwartet_statt_hinter
	{"mailadresse wird hinter <string> erwartet statt hinter","the mail address will be expected after <string> instead of"},
	// T_mailadresse_fuer_unverschluesselte_Mail_wird_hinter_string_erwartet_statt_hinter
	{"mailadresse fuer unverschluesselte Mail wird hinter <string> erwartet statt hinter",
    "mail address for unencoded mail will be expected after <string> instead of"},
	// T_affs_k,
	{"affs","tffs"},
	// T_anffaxstr_l,
	{"anffaxstr","toffaxstr"},
	// T_faxnr_fuer_primaer_Fritzbox_wird_hinter_string_erwartet_statt_hinter,
	{"faxnr fuer primaer Fritzbox wird hinter <string> erwartet statt hinter",
		"fax no.for fax with preference to fritzbox is expected after <string> instead of"},
	// T_acfs_k
	{"acfs","tcfs"},
	// T_ancfaxstr_l
	{"ancfaxstr","tocfaxstr"},
	// T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter
	{"faxnr fuer primaer Capisuite wird hinter <string> erwartet statt hinter", 
		"fax no.for fax with preference to capisuite is expected after <string> instead of"},
	// T_ahfs_k
	{"ahfs","thfs"},
	// T_anhfaxstr_l
	{"anhfaxstr","tohfaxstr"},
	// T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter
	{"faxnr fuer primaer hylafax wird hinter <string> erwartet statt hinter", 
		"fax no.for fax with preference to hylafax is expected after <string> instead of"},
	// T_as_k
	{"as","ts"},
	// T_anstr_l
	{"anstr","tostr"},
	// T_Adressatenname_wird_hinter_string_erwartet_statt_hinter
	{"Adressatenname wird hinter <string> erwartet statt hinter","name of addressee is expected after <string> instead of"},
	// T_us_k
	{"us","ands"},
	// T_undstr_l,
	{"undstr","andstr"},
	// T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt
	{"Trennstring <string> fuer mehrere Adressaten/Telefonnummern statt", "separating string <string> for multiple addressees/tel'numbers, instead of"},
	// 	T_find_k,
	{"fd","fd"},
	// T_find_l,
	{"finde","find"},
	// T_Version_1_2_oder_3_Dateisuche_anstatt
	{"Version 1,2 oder 3 -Dateisuche (variable Performanceunterschiede) anstatt", 
		"version 1,2 or 3 of filefind (variable performance differences instead of"},
	// T_loef
	{"loef","delf"},
	// T_loeschefax_l
	{"loeschefax","deletefax"},
	// T_ein_Fax_nach_Rueckfrage_loeschen
	{"ein Fax nach Rueckfrage loeschen","delete a fax with query"},
	// T_loew
	{"loew","delo"},
	// T_loeschewaise_l
	{"loeschewaise","deleteorphans"},
	// T_Eintraege_aus
	{"Eintraege aus `","delete entries from `"},
	// T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist
	{"` loeschen, zu denen keine Datei im Wartevz.und kein Capi- oder Hylafax nachweisbar ist", "` without detection of file in waiting directory or capisuite fax or hylafax"},
	// T_loea_k
	{"loea","dela"},
	// T_loescheallew_l
	{"loescheallew","deleteallwaiting"},
	// T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus
	{"alle wartenden Faxe und zugehoerige Eintraege aus `","delete all waiting faxes and associated entries from `"},
	// T_loeschen
	{"` loeschen","`"},
	// T_erneut_k
	{"erneut","again"},
	// T_erneutempf_l
	{"erneutempf","receiveagain"},
	// T_empfangenes_Fax_erneut_bereitstellen
	{"empfangenes Fax erneut bereitstellen","present a received fax again"},
	// T_uml_k
	{"uml","red"},
	// T_umleiten_l
	{"umleiten","redirect"},
	// T_ausgehendes_Fax_vorzeitig_ueber_andere_Wege_schicken
	{"ausgehendes Fax vorzeitig auf zweitem Weg schicken","redirect outgoing fax ahead by the other channel"},
	// T_auml_k,
	{"auml","reda"},
	// T_alleumleiten_l,
	{"alleumleiten","redirectall"},
	// T_alle_ausgehenden_Faxe_vorzeitig_ueber_andere_Wege_schicken,
	{"alle ausgehenden Faxe vorzeitig ueber andere Wege schicken","redirect all outgoing faxes ahead by other channels"},
	// T_kez_k
	{"kez","csf"},
	// T_korrerfolgszeichen_l
	{"korrerfolgszeichen","correctsuccessflag"},
	// T_in_der_Datenbanktabelle
	{"in der Datenbanktabelle `","in the database table `"},
	// T_wird_das_Erfolgszeichen_korrigiert
	{"` wird das Erfolgszeichen korrigiert","` the success flag is being corrected"},
	// T_bvz_k
	{"bvz","rod"},
	// T_bereinigevz_l
	{"bereinigevz","reorderdir"},
	// T_Dateien_aus_Warteverzeichnis_Gescheitertenvz_und_Gefaxtvz_gegen
	{"Dateien aus Wartevz.,Gescheitertenvz.u.Gefaxtvz.gegen `","Examine files in waiting,failed a.faxed directory against the tables `"},
	// T_pruefen_und_aufraeumen
	{"` pruefen und ggf. aufraeumen","` and put them to order"},
	// T_lista_k
	{"lista","listo"},
	// T_listausg_l
	{"listausg","listoutg"},
	// T_listet_Datensaetze_aus
	{"listet Datensaetze aus `","lists entries from `"},
	// T_mit_Erfolgskennzeichen_auf
	{"` mit Erfolgskennzeichen auf","` with success flag"},
	// T_listf_k
	{"listf","listf"},
	// T_listfailed_l
	{"listfehlgeschl","listfailed"},
	// T_ohne_Erfolgskennzeichen_auf
	{"` ohne Erfolgskennzeichen auf","` without success flag"},
	// T_listi_k
	{"liste","listi"},
	// T_listinca_l
	{"listeing","listinca"},
	// T__auf
	{"` auf","`"},
	// T_listw_k,
	{"listw","listw"},
	// T_listwart_l
	{"listwartende","listwaiting"},
	// T_listet_wartende_Faxe_auf
	{"listet wartende Faxe auf","lists waiting faxes"},
	// T_s_k
	{"s","s"},
	// T_suche_l
	{"suche","search"},
	// T_suche_in_verarbeiteten_Faxen_nach
	{"Suche in verarbeiteten Faxen nach <string>: ","Look in processed faxes for <string>: "},
	// T_vf_k
	{"vf","vf"},
	// T_vf_l
	{"vf","vf"},
	// T_FBFax_Konfigurationdateien_bearbeiten
	{"FBFax-Konfigurationsdateien bearbeiten (beenden mit ':qa')","edit fbfax configuration files (finish with ':qa')"},
	// T_vc_k
	{"vc","vc"},
	// T_vc_l
	{"vc","vc"},
	// T_Capisuite_Konfigurationdateien_bearbeiten
	{"Capisuite-Konfigurationsdateien bearbeiten (beenden mit ':qa')","edit capisuite configuration files (finish with ':qa')"},
	// T_vh_k
	{"vh","vh"},
	// T_vh_l
	{"vh","vh"},
	// T_Hylafax_Modem_Konfigurationsdatei_bearbeiten
	{"Hylafax-Modem-Konfigurationsdatei bearbeiten (beenden mit ':qa')","edit hylafax modem configuration file (finish with ':qa')"},
	// T_konfcapi
	{"konfcapi()","confcapi()"},
	// T_Capisuite_ist_offenbar_noch_nicht_richtig_konfiguriert
	{"Capisuite ist offenbar noch nicht konfiguriert (","Capisuite seems not to be configured correcty ("},
	// T_ist_Apostroph,
	{" ist '"," is '"},
	// T_Die_Einstellungen_koennen_spaeter_in,
	{" Die Einstellungen koennen spaeter in '"," The settings can later be modified in '"},
	// T_geaendert_werden,
	{"' geaendert werden.","'"},
	// T_Faxnr_die_zum_Adressaten_gesandt_wird_bis_20_Zeichen_nur_plus_und_Ziffern,
	{"Faxnr., die zum Adressaten gesandt wird (bis 20 Zeichen, nur '+' und Ziffern)",
		"Fax number which is sent to the addressee (up to 20 characters, only '+' and numerals)"},
	// T_ausgehende_Multiple_Subscriber_Number_Faxnummer_ohne_Vorwahl,
	{"hinausgehende 'Multiple Subscriber Number' (Faxnummer ohne Vorwahl)","outgoing 'multiple subscriber number' (fax number without prefix)"},
	// T_Amtsholung_ueblicherweise_kk_oder_0,
	{"Amtsholung, ueblicherweise '' oder '0'","outside line access, typically '' or '0'"},
	// T_Faxueberschrift,
	{"Faxueberschrift","fax headline"},
	// T_Adressat_empfangener_Faxe_die_ueber_Email_verteilt_werden,
	{"Adressat empfangener Faxe, die ueber Email verteilt werden","addressee of received faxes which are distributed via email"},
	// T_Zahl_der_Sendeversuche,
	{"Zahl der Sendeversuche","Number of transmission tries"},
	// T_kommagetrennte_Liste_mit_Sekundenabstaenden_zwischen_Sendeversuchen,
	{"kommagetrennte Liste mit Sekundenabstaenden zwischen Sendeversuchen","comma separated list with distances between transmission tries"},
	// T_Geduld_bis_zum_Verbindungsaufbau_in_s,
	{"Geduld bis zum Verbindungsaufbau in s","timeout for connection establishment"},
	// T_komma_wert,
	{", wert: ",", value: "},
	// T_komma_Altwert,
	{", Altwert: ",", old value: "},
	// T_Verschiebe
	{"Verschiebe: '","Moving: '"},
	// T_Fehler_beim_Verschieben
	{"Fehler beim Verschieben ","Error while moving "},
	// T_FehlerbeimUmbenennenbei
	{" Fehler beim Umbenennen bei:"," Error while renaming:"},
	// T_Kopiere_Doppelpunkt
	{"Kopiere: '","Copying: "},
	// T_Fehler_beim_Kopieren
	{"Fehler beim Kopieren: ","Error while copying: "},
	// T_Dateiname,
	{"Dateiname ","File name "},
	// T_schlechtgeformt
	{" schlecht geformt!","malformed!"},
	// T_zielname_erstes_Ziel
	{" zielname:  erstes Ziel: '"," target name:  first target: '"},
	// T_zielname_Ausweichziel
	{" zielname: Ausweichziel: '"," target name:  alternate target: '"},
	// T_Quelle_und_Ziel_gleich
	{", Quelle und Ziel gleich",", source and target identical"},
	// T_entspricht
	{"' entspricht "," "},
	// T_entsprichtnicht
	{"nicht ","does not match to "},
	// T_entsprichtdoch
	{"","matches to "},
	// T_Muster_Doppelpunkt
	{"Muster: '","pattern: '"},
	// T_pruefcvz
	{"pruefcvz()","checkcdirs()"},
	// T_prueffbox,
	{"prueffbox()","checkfbox()"},
	// T_pruefcapi,
	{"pruefcapi()","checkcapi()"},
	// T_capilaeuft
	{"capilaeuft: ","capirunning: "},
	// T_Module_geladen
	{"Module geladen:","Modules loaded:"},
	// T_Lade_Capi_Module
	{", lade Capi-Module ...",", loading capi-modules ..."},
	// T_Kernelversion
	{"Kernelversion: ","Kernel version: "},
	// T_KannFcpciNInstVerwCapiNicht
	{"Kann Fritz-Modul fcpci nicht installieren, verwende capi nicht.\nZ.B.koennte mit ",
		"Cannot install module fcpci for the fritz card, not utilizing capi. For example, with "},
	// T_eine_neuere_Version_als_die_des_aktuellen_Kernels_installiert_worden_sein_dann_bitte_erneutes_Systemupdate
	{" eine neuere Version als die des aktuellen Kernels installiert worden sein, dann bitte erneutes Systemupdate",
		", a newer version than the current kernel could have been installed, in this case please do another system update"},
	// T_nichtgefFcpciMfdKinstallierwerden
	{"' nicht gefunden, fcpci muss fuer diesen Kernel installiert werden, versuche es:",
		"' not found, fcpci must be installed for this kernel, trying to:"},
	// T_Zur_Inbetriebnahme_der_Capisuite_muss_das_Modul_capi_geladen_werten,
	{"Zur Inbetriebnahme der Capisuite muss das Modul capi geladen werden. Zu dessen Erstellung musste der Befehl "
		"'sudo dnf -y install kernel-modules-extra' aufgerufen werden, der den Linux-Kernel aktualisiert hat (",
		"In order to use the capisuite, the module capi has to be loaded. In order to generate this, the command "
			"'sudo dnf -y install kernel-modules-extra' hat to be called, which updated the linux kernel ("},
	// T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten
	{"Bitte zu dessen Verwendung den Rechner neu starten und dann nochmal ",
		"Please reboot and afterwords call "},
	// T_aufrufen,
	{" aufrufen!"," again!"},
	// T_Moment_muss_Kernel_herunterladen
	{"Moment, muss Kernel-rpm herunterladen ...","One moment, must download kernel-rpm ..."},
	// T_Der_Kernel_hat_sich_offenbar_seit_dem_Einloggen_von
	{"Der Kernel hat sich offenbar seit dem Einloggen von '","The kernel seems to have been updated sind logging in from '"},
	// T_nach_
	{"' nach '","' to '"},
	// T_verjuengt_Bitte_den_Rechner_neu_starten_und_dann_mich_nochmal_aufrufen
	{"' verjuengt. \nBitte den Rechner neu starten und dann mich nochmal aufrufen!","'. \nPlease restart the pc and then call me again!"},
	// T_Konnte
	{"Konnte '","Could not start '"},
	// T_nichtstarten
	{"' nicht starten",""},
	// T_StarteCapisuite
	{"Starte Capisuite ...","Starting Capisuite ..."},
	// T_Capisuite_gestartet
	{"Capisuite gestartet.","capisuite started."},
	// T_konntecapisuiteservice
	{"Konnte capisuite.service ","Could not start capisuite.service "},
	// T_malnichtstartenverwN
	{" mal nicht starten, verwende es nicht."," times, not utilizing it."},
	// T_pruefrules
	{"pruefrules()","checkrules()"},
	// T_pruefblack
	{"pruefblack()","checkblack()"},
	// T_haengean
	{"haenge an ","appending to "},
	// T_an_mdpp
	{" an: ",": "},
	// T_pruefsfftobmp
	{"pruefsfftobmp()","checksfftobmp()"},
	// T_clieskonf
	{"clieskonf()","creadconf()"},
	// T_pruefmodcron
	{"pruefmodcron()","checkmodcron()"},
	// T_Zahl_der_SQL_Befehle_fuer_die_Absenderermittlung,
	{"Zahl der SQL-Befehle fuer die Absenderermittlung","No.of the sql-commands for finding out senders"},
	// T_Zahl_der_Muster_Verzeichnis_Paare_zum_Speichern_ankommender_Faxe
	{"Zahl der Muster/Verzeichnis-Paare zum Speichern ankommender Faxe","No of pairs of patterns/directories for saving received faxes"},
	// T_Verzeichnis_mit_zu_faxenden_Dateien
	{"Verzeichnis mit zu faxenden Dateien","Directory with files to fax"},
	// T_Verzeichnis_mit_wartenden_Dateien
	{"Verzeichnis mit wartenden Dateien","Directory with waiting files"},
	// T_Verzeichnis_mit_gescheiterten_Dateien
	{"Verzeichnis mit gescheiterten Dateien","Directory with failed files"},
	// T_Verzeichnis_fuer_empfangene_Faxe
	{"Verzeichnis fuer empfangene Faxe","Directory for received faxes"},
	// T_Soll_die_FritzBox_verwendet_werden
	{"Soll die Fritzbox verwendet werden","Shall the fritzbox be used"},
	// T_Soll_die_FritzBox_zum_Senden_verwendet_werden
	{"Soll die Fritzbox zum Senden verwendet werden","Shall the fritzbox be used for sending"},
	// T_Soll_die_FritzBox_zum_Empfang_verwendet_werden
	{"Soll die Fritzbox zum Empfang verwendet werden","Shall the fritzbox be used for receiving"},
	// T_Mit_CIFS_gemountetes_Verzeichnis_mit_ankommenden_Faxen_der_Fritzbox
	{"Mit CIFS gemountetes Verzeichnis mit ankommenden Faxen der Fritzbox", "Via CIFS mounted directory with received faxes at the fritzbox"},
	// T_Archiv_Verzeichnis_fuer_ankommende_Faxe_der_Fritzbox
	{"Archiv-Verzeichnis fuer ankommende Faxe der Fritzbox","archive directory for incoming faxes at the fritzbox"},
	// T_Soll_die_Capisuite_verwendet_werden
	{"Soll die Capisuite verwendet werden","Shall Capisuite be used"},
	// T_Soll_die_Capisuite_zum_Senden_verwendet_werden
	{"Soll die Capisuite zum Senden verwendet werden","Shall Capisuite be used for sending"},
	// T_Soll_die_Capisuite_zum_Empfang_verwendet_werden
	{"Soll die Capisuite zum Empfang verwendet werden","Shall Capisuite be used for receiving"},
	// 	T_pruefisdn
	{"T_pruefisdn()","checkisdn()"},
	// T_ISDN_Karte_gefunden
	{"ISDN-Karte gefunden: ","ISDN-Card found: "},
	// T_Keine_ISDN_Karte_gefunden
	{"Keine ISDN-Karte gefunden. Setze ","No ISDN-Card found. Setting "},
	// T_mitCapi
	{"mitCapi","withCapi"},
	// T_aauf
	{" auf "," to "},
	// T_Setze
	{". Setze ",". Setting "},
	// T_ob_eine_Fritzcard_drinstak
	{"ob eine Fritzcard drinstak, als die Konfigurationsdatei geschrieben wurde","if a fritzcard was present when the configuration file was written"},
	// T_Faxt_Dateien_aus_Verzeichnis_pfad_die
	{"Faxt Dateien aus Verzeichns <pfad>, die '","Faxes files from directory <path>, which contain '"},
	// T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie
	{" <faxnr>/<mailadr>' enthalten und durch soffice in pdf konvertierbar sind \nund traegt sie in MariaDB-Datenbank '",
		" <faxno>/<mailaddr>' and are convertible into pdf, \nand logs this in the the mariadb database '"}, 
	// T_Tabellen,
	{"' (Tabellen: `","' (tables: `"},
	// T_aein
	{"`) ein.","`)."},
	// T_Zustand_der_Dienste
	{"Zustand der Dienste: ","State of the services: "},
	// T_pruefmodem
	{"pruefmodem()","checkmodem()"},
	// T_gibts
	{" gibts"," exists"},
	// T_nicht
	{" nicht"," not"},
	// T_Kein_Modem_gefunden
	{"Kein Modem gefunden.","No modem found."},
	// T_Soll_Hylafax_verwendet_werden
	{"Soll hylafax verwendet werden","Shall hylafax be used"},
	// T_Soll_Hylafax_zum_Senden_verwendet_werden
	{"Soll hylafax zum Senden verwendet werden","Shall hylafax be used for sending"},
	// T_Soll_Hylafax_zum_Empfang_verwendet_werden
	{"Soll hylafax zum Empfang verwendet werden","Shall hylafax be used for receiving"},
	// T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden
	{"Soll vorrangig die Capisuite statt hylafax gewaehlt werden","Shall capisuite instead of hylafax bei chosen preferentially"},
	// T_Zahl_der_Versuche_in_Capisuite_bis_andere_Methode_versucht_wird
	{"Zahl der Versuche in Capisuite, bis andere Methode versucht wird","Number of tries in Capisuite, until other method is started"},
	// T_Zahl_der_Versuche_in_hylafax_bis_andere_Methode_versucht_wird
	{"Zahl der Versuche in hylafax, bis andere Methode versucht wird","Number of tries in hylafax, until other method is started"},
	// T_Zahl_der_Versuche_in_fbfax_bis_andere_Methode_versucht_wird
	{"Zahl der Versuche in fbfax, bis andere Methode versucht wird","Number of tries in fbfax, until other method is started"},
	// T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt
	{"Zahl der Klingeltoene, bis Hylafax den Anruf annimmt","Number of ring bells, until hylafax accepts call"},
	// T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden
	{"Sollen die Dateien unabhaengig vom Faxerfolg im Zielverzeichnis gespeichert werden",
		"Shall files be stored in target directory irrespective of fax success"},
	// T_soll_Text_in_empfangenen_Faxen_mit_OCR_gesucht_werden
	{"Soll Text in empfangenen Faxen (mit \"OCR\") gesucht werden?",
		"Shall text from received faxes be searched (with \"ocr\")?"},
	// T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden
	{"Soll Text in gesandten Bildern (mit \"OCR\") gesucht werden?",
		"Shall text from sent pictures be searched (with \"ocr\")?"},
	// T_Buchstabenfolge_vor_erster_Faxnummer
	{"Buchstabenfolge vor erster Fax-Nummer","Letter sequence before the first fax number"},
	// T_Buchstabenfolge_vor_erster_Mailadresse
	{"Buchstabenfolge vor erster Mailadresse","Letter sequence before the first mail address"},
	// T_Buchstabenfolge_vor_erster_Mailadresse_fuer_unverschluesselte_Mail
	{"Buchstabenfolge vor erster Mailadresse fuer unverschluesselte Mail",
		"letter sequence before the first mail address for an unencoded mail"},
	// T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Fritzbox
	{"Buchstabenfolge vor erster Fax-Nummer primaer fuer Fritzbox","Letter-sequence before the first fax number primarily for fritzbox"},
	// T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Capisuite
	{"Buchstabenfolge vor erster Fax-Nummer primaer fuer Capisuite","Letter-sequence before the first fax number primarily for capisuite"},
	// T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Hylafax
	{"Buchstabenfolge vor erster Fax-Nummer fuer Hylafax","Letter-sequence before the first fax number primarily for hylafax"},
	// T_Buchstabenfolge_vor_erstem_Adressaten
	{"Buchstabenfolge vor erstem Adressaten","Letter-sequence before the first addressee"},
	// T_Buchstabenfolge_vor_weiterem_Adressaten_sowie_weiterer_Faxnummer,
	{"Buchstabenfolge vor weiterem Adressaten sowie weiterer Faxnummer","Letter-sequence before further addressee or fax number"},
	// T_setzhylavz
	{"setzhylavz()","sethyladir()"},
	// T_aus_systemd_fax_service_Datei_ermittelt
	{" aus systemd-fax-service-Datei ermittelt"," determined from systemd fax service file"},
	// T_aus_etc_init_d_hylafax_ermittelt,
	{" aus /etc/init.d/hylafax ermittelt"," determined from /etc/init.d/hylafax"},
	// T_aus_seiner_ausschliesslichen_Existenz_ermittelt
	{" aus seiner ausschliesslichen Existenz ermittelt"," determined from its exclusive existence"},
	// T_aus_seinem_geringen_Alter_ermittelt
	{" aus seinem geringeren Alter ermittelt"," determined from its lower age"},
	// T_aus_mangelnder_Alternative_ermittelt
	{" aus mangelnder Alternative ermittelt"," determined from missing alternative"},
	// T_aus_Existenz_von,
	{" aus Existenz von "," determined from the existence of "},
	// T_ermittelt
	{" ermittelt.","."},
	// T_hylafax_Verzeichnis
	{"hylafax-Verzeichnis: ","hylafax-directory: "},
	// T_pruefhyla
	{"pruefhyla()","checkhyla()"},
	// T_Konfiguration_von_hylafax_durch
	{"# Konfiguration von hylafax durch ","# Configuration of hylafax by "},
	// T_muss_mindestens_2_sein_zur_Uebergabe_der_Nr_des_Anrufenden
	{" #muss mindestens 2 sein zur Uebergabe der Nummer des Anrufenden"," #must be at least 2 to transfer the no of the caller"},
	// T_vom
	{" vom "," at "},
	// T_nichtbeschreibbar
	{" nicht beschreibbar!","not to open for writing!"},
	// T_Baudratevon
	{"Baudrate von '","Baud rate of '"},
	// T_mit_af
	{"' mit ","' with "},
	// T_zugeringVerwendeHylafaxnicht
	{" zu gering. Verwende Hylafax nicht."," too small. Not utilizing hylafax."},
	// T_mit_Baudrate,
	{"' mit Baudrate ","' with baud rate "},
	// T_wird_verwendet
	{" wird verwendet."," being used."},
	// T_Pruefe_ob_Hylafax_gestartet
	{"Pruefe, ob Hylafax gestartet ...","Checking if hylafax is running ..."},
	// T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen
	{"Hylafax ohne + entdeckt, muss ich loeschen ...","hylafax without plus found, must delete it ..."},
	// T_Hylafaxplus_entdeckt_muss_ich_loeschen
	{"Hylafax+ entdeckt, muss ich loeschen ...","Hylafax+ found, having to delete it ..."},
	// T_Hylafax_laeuft
	{"Hylafax laeuft!","Hylafax is running!"},
	// T_Fehler_in_pruefhyla
	{"Fehler in pruefhyla()!","Error in checkhyla()!"},
	// T_Muss_Hylafax_installieren
	{"Muss Hylafax installieren ...","Have to install hylafax ..."},
	// T_ueber_den_Quellcode
	{"... ueber den Quellcode","... with the source code"},
	// T_Ergebnis_nach
	{"Ergebnis nach sed","result after sed"},
	// T_ueber_das_Installationspaket
	{"... ueber das Installationspaket","... with the installation package"},
	// T_hylafehlt
	{"hylafehlt: ","hylamissing: "},
	// T_Muss_falsches_hylafax_loeschen
	{"Muss falsches hylafax loeschen!!!","Have to delete the wrong hylafax!!!"},
	// T_Fuehre_aus_Dp
	{"Fuehre aus: ","Executing: "},
	// T_falls_es_hier_haengt_bitte_erneut_aufrufen
	{" (falls es hier haengt, insbes. laenger als 3 Wochen, dann bitte erneut aufrufen)",
		" (if it hangs, especially more than 3 weeks, please invoke again)"},
	// T_hylafaxspringtnichtan
	{"hylafax.service springt nicht an. Verwende Hylafax nicht.","hylafax.service does not start up. Not utilizing hylafax."},
	// T_verzeichnisse
	{"verzeichnisse()","directories()"},
	// T_Muster,
	{"Muster ","Pattern "},
	// T_rufpruefsamba
	{"rufpruefsamba()","callchecksamba()"},
	// T_Faxempfang
	{"Faxempfang","FaxArrival"},
	// T_Gefaxt
	{"Gefaxt","Faxed"},
	// T_zufaxenvz
	{"zufaxenvz: '","outgoing dir: '"},
	// T_pruefspool
	{"pruefspool()","checkspool()"},
	// T_pruefouta
	{"pruefouta()","checkouta()"},
	// T_eindeutige_Identifikation
	{"eindeutige Identifikation","distinct identification"},
	// T_Originalname_der_Datei
	{"Originalname der Datei","original name of the file"},
	// T_Originalname_der_Datei_vor_Umwandlung_in_PDF
	{"Originalname der Datei vor Umwandlung in PDF","original name of the file before converting to pdf"},
	// T_zu_senden_an
	{"zu senden an","to be sent to"},
	// T_wie_mailen
	{"wie zu mailen (1=verschluesselt,2=klar)","how to mail (1=encrypted, 2=plain)"},
	// T_Adressat
	{"Adressat","addressee"},
	// T_Prioritaet_aus_Dateinamen
	{"Prioritaet der Fax-Programme: 0=unbestimmt, 1=fbfax, 2=capi, 3=hyla, 11=fbfax, 12=capi, 13=hyla per Faxdateiname",
		"Priority of the fax programs: 0=indetermined, 1=fbfax, 2=capi, 3=hyla, 11=fbfax, 12=capi, 13=hypla per fax file name"},
	// T_Zahl_der_bisherigen_Versuche_in_Capisuite
	{"Zahl der bisherigen Versuche in Capisuite","No. of previous tries in Capisuite"},
	// T_Zahl_der_bisherigen_Versuche_in_fbfax,
	{"Zahl der bisherigen Versuche in fbfax","No. of previous tries in fbfax"},
	// T_Pfad_zur_Spooldatei_in_fbfax,
	{"Pfad zur Spooldatei in fbfax","path to the spool file in fbfax"},
	// T_Zahl_der_bisherigen_Versuche_in_Hylafax
	{"Zahl der bisherigen Versuche in Hylafax","No. of previous tries in Hylafax"},
	// T_Spooldatei_in_Capisuite
	{"Spooldatei in Capisuite","Spool file in Capisuite"},
	// T_Pfad_zur_Spooldatei_in_Capisuite_ohne_abschliessendes_Verzeichnistrennzeichen
	{"Pfad zur Spooldatei in Capisuite, ohne abschliessendes Verzeichnistrennzeichen",
		"Path to the spool file in Capisuite, without closing directory separator"},
	// T_Aenderungszeit_der_CapiSpoolDatei
	{"Aenderungszeit der CapiSpooldatei","Modification time of the capi spool file"},
	// T_Aenderungszeit_der_CapiSpooldatei_im_time_Format
	{"Aenderungszeit der CapiSpooldatei, im time()-Format","Modification time of the capi spool file, in time() format"},
	// T_Aenderungszeit_der_Hylaspooldatei
	{"Aenderungszeit der Hyla-Spooldatei","Modification time of the hyla spool file"},
	// T_Aenderungszeit_der_Hylaspooldatei_im_Time_Format
	{"Aenderungszeit der Hyla-Spooldatei, im time()-Format","Modification time of the hyla spool file, in time() format"},
	// T_jobid_in_letztem_gescheitertem_hylafax
	{"jobid in letztem gescheitertem hylafax","job id of the last failed hylafax"},
	// T_state_Feld_in_hylafax
	{"state-Feld in hylafax: 0=init,1=gestrichen,2=schwebend,3=wartend,4=blockiert,5=bereit,6=verarb,7=gesandt,8=gescheitert,9=fehlend,10=woasined",
		"state-field in hylafax: 0=init,1=suspended,2=pending,3=sleeping,4=blocked,5=ready,6=active,7=done,8=failed,9=missing,10=unknown"},
	// T_Index_auf_urspruenglichen_Dateinamen
	{"Index auf urspruenglichen Dateinamen in Tabelle 'udoc'","Index on original filename in table 'udoc'"},
	// T_capistat
	{"capistat: 0=init,1=gestrichen,2=schwebend,3=wartend,4=blockiert,5=bereit,6=verarb,7=gesandt,8=gescheitert,9=fehlend,10=woasined",
		"capistat: 0=init,1=suspended,2=pending,3=sleeping,4=blocked,5=ready,6=active,7=done,8=failed,9=missing,10=unknown"},
	// T_statuscode_in_letztem_gescheitertem_hylafax
	{"statuscode in letztem gescheitertem hylafax","status code of the last failed hylafax"},
	// T_status_in_letztem_gescheitertem_hylafax
	{"status in letztem gescheitertem hylafax","status of the last failed hylafax"},
	// T_capispooldateien_der_Capisuite
	{"capiSpooldateien der Capisuite","capi spool files of capisuite"},
	// T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen
	{"1=erfolgreiche Uebertragung, 0=fehlgeschlagen","1=successful transmission, 0=failure"},
	// T_Name_des_Adressaten_aus_Faxnummer_ermittelt
	{"Name des Adressaten, aus Faxnummer ermittelt","Name of the receiver according to his fax number"},
	// T_Datum_des_Losschickens
	{"Datum des Losschickens","submit time"},
	// T_Ende_der_Uebertragung
	{"Ende der Uebertragung","end of submission"},
	// T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname
	{"Kennung im Faxsystem (hylafax: Nr., Capisuite: Datei, MS Fax: Fax-Dateiname",
		"identifier in fax system (hylafax: no, capisuite: file, ms fax: fax file name"},
	// T_Dateigroesse
	{"Dateigroesse","file size"},
	// T_Seitenzahl
	{"Seitenzahl","no. of pages"},
	// T_Zahl_der_Anwahlen
	{"Zahl der Anwahlen","No. of tries"},
	// T_Faxnummer_des_Adressaten
	{"Faxnummer des Adressaten","receiver's fax no"},
	// T_Titel_des_Adressaten
	{"Titel des Adressaten","receiver's fax no"},
	// T_PID_falls_aus_Dateinamen_ermittelt
	{"PID, falls aus Dateinamen ermittelt","PID, if excerpted from file name"},
	// T_Kurzbezeichnung_der_eigenen_Faxstelle
	{"Kurzbezeichnung der eigenen Faxstelle","short name of the own fax location"},
	// T_Geraetename
	{"Geraetename","device name"},
	// T_Name_des_Adressaten_aus_Dateiname
	{"Name des Adressaten aus Dateiname","Name of the receiver from file name"},
	// T_Archiv_fuer_die_erfolgreichen_Faxe
	{"Archiv fuer die erfolgreichen Faxe","archive for successful faxes"},
	// T_pruefudoc
	{"pruefudoc()","checkudoc()"},
	// T_Archiv_fuer_die_Dateinamen_vor_Aufteilung
	{"Archiv fuer die Dateinamen vor Aufteilung","archive for filenames before splitting"},
	// T_pruefinca
	{"pruefinca()","checkinca()"},
	// T_identisch_zu_submid_in_outa
	{"identisch zu submid in outa","identical to submid in outa"},
	// T_Verwende
	{"Verwende: ","Using: "},
	// T_kein_Faxprogramm_verfuegbar
	{"(kein Faxprogramm verfuegbar)","(no fax program available)"},
	// T_aktiv
	{"aktiv","active"},
	// T_aktiviert
	{"aktiviert","activated"},
	// T_inaktiv
	{"inaktiv","inactive"},
	// T_korrigiere,
	{"korrigiere()","correct()"},
	// T_korrigierefbox,
	{"korrigierefbox()","correctfbox()"},
	// T_korrigierecapi
	{"korrigierecapi()","correctcapi()"},
	// T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird
	{"Folgende Faxe waren mit falschem Erfolgskennzeichen eingetragen, was korrigiert wird:",
		"The following faxes were documented with wrong success flag, which will be corrected:"},
	// T_Faxnr
	{"Faxnr.","fax no."},
	// T_zp
	{"Zeitpunkt","timestamp"},
	// T_tries
	{"Versuche","tries"},
	// T_size
	{"Größe","size"},
	// T_docname
	{"Dateiname","docname"},
	// T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird
	{"Folgende Faxe waren nicht eingetragen, was korrigiert wird:",
		"The following faxes from the hylafax logfile have not been documented, which will be corrected:"},
	// T_telnr
	{"Tel'nr.","tel.no."},
	// T_Gabelung_zu_korrigiere_misslungen,
	{"Gabelung zu korrigiere() misslungen","Fork to correct() failed"},
	// T_Gabelung_zu_faxemitH_misslungen
	{"Gabelung zu faxemitH() misslungen","Fork to faxingwithHyla() failed"},
	// T_Gabelung_zu_faxemitF_misslungen
	{"Gabelung zu faxemitF() misslungen","Fork to faxingwithFritz() failed"},
	// T_Gabelung_zu_faxemitC_misslungen
	{"Gabelung zu faxemitC() misslungen","Fork to faxingwithCapi() failed"},
	// T_Gabelung_zu_untersuchespool_misslungen
	{"Gabelung zu untersuchespool() misslungen","Fork to checkspool() failed"},
	// T_Gabelung_zu_zeigweitere_misslungen
	{"Gabelung zu zeigweitere() misslungen","Fork to showothers() failed"},
	// T_Gabelung_zu_empfarch_misslungen
	{"Gabelung zu empfarch() misslungen","Fork to archiveReceived() failed"},
	// T_Gabelung_zu_wegfaxen_misslungen
	{"Gabelung zu wegfaxen() misslungen","Fork to faxingall() failed"},
	// T_Gabelung_zu_bereinigevz_misslungen
	{"Gabelung zu bereinigevz() misslungen","Fork to reorderdir() failed"},
	// T_Gabelung_zu_vschlmail_misslungen
	{"Gabelung zu vschlmail() misslungen","Fork to encrymail() failed"},
	// T_Gabelung_zu_klarmail_misslungen
	{"Gabelung zu klarmail() misslungen","Fork to plainmail() failed"},
	// T_empfarch
	{"empfarch()","archiveReceived()"},
	// T_empfcapi
	{"empfcapi(): ","recvcapi(): "},
	// T_empfhyla
	{"empfhyla(): ","recvhyla(): "},
	// T_empffbox
	{"empffbox(): ","recvfbox(): "},
	// T_was
	{", was: ",", what: "},
	// T_Bilddatei
	{"Bilddatei","Picture file"},
	// T_avon
	{" von "," from "},
	// T_zupdf
	{"zupdf()","topdf()"},
	// T_pruefocr
	{"pruefocr()","checkocr()"},
	// T_Umwandlungvon
	{"Umwandlung von ","Conversion of "},
	// T_inPDFmit
	{" in PDF mit "," to PDF using "},
	// T_misserfolg
	{"Misserfolg","failure"},
	// T_Erfolg_af
	{"Erfolg","success"},
	// T_Seiten
	{", Seitenzahl: ",", no. of pages: "},
	// T_Installiere_ocrmypdf
	{"Installiere ocrmypdf ...","Installing ocrmypdf ..."},
	// T_Ihre_Python3_Version_koennte_mit
	{"Ihre Python3-Version koennte mit ","Your python3 version is "},
	// T_veraltet_sein_Wenn_Sie_Ihre_Faxe_OCR_unterziehen_wollen_dann_fuehren_Sie_bitte_ein_Systemupdate_durch_mit
	{" veraltet sein. Wenn Sie Ihre Faxe OCR unterziehen wollen, dann fuehren Sie bitte einen Systemupdate durch mit ",
		" and could be obsolete. If You want to treat Your faxes with OCR, please update Your system with "},
	// T_pruefsoffice
	{"pruefsoffice()","checksoffice()"},
	// T_pruefconvert
	{"pruefconvert()","checkconvert()"},
	// T_pruefunpaper
	{"pruefunpaper()","checkunpaper()"},
	// T_beendetErgebnis
	{" beendet, Ergebnis: "," finished, result: "},
	// T_holtif
	{"holtif()","gettif()"},
	// T_nicht_angekommen
	{"nicht angekommen ","not arrived "},
	// T_Dateien
	{"Dateien ","Files "},
	// T_nicht_verarbeitbar_Verschiebe_sie_nach
	{" nicht verarbeitbar. Verschiebe sie nach "," not processable. Moving them to "},
	// T_Zahl_der_empfangenen_Faxe
	{"       Zahl der empfangenen Faxe: ","       Number of received faxes: "},
	// T_bereinigevz
	{"bereinigevz()","reorderdirectories()"},
	// T_Bereinige_Verzeichnis
	{"Bereinige Verzeichnis ","Cleaning directory '"},
	// T_DateienzahlimVz
	{", Dateienzahl im Verzeichnis: ",", no. of files in directory: "},
	// T_Fehler_beim_Verschieben_Ausrufezeichen
	{"Fehler beim Verschieben!","Error while moving!"},
	// T_gefunden_in_Tabelle
	{"gefunden in Tabelle: ","found in table: "},
	// T_kommaFaxerfolg
	{", Faxerfolg: ",", fax success: "},
	// T_Fehlt
	{"Fehlt","Lacking"},
	// T_Nicht_gefaxt
	{"Ø gefaxt","Ø faxed"},
	// T_Aus2
	{"Aus ","From "},
	// T_wurden_in_Unterverzeichnisse_verschoben
	{" wurden in Unterverzeichnisse verschoben: "," have been moved to subdirectories: "},
	// T_tu_lista
	{"tu_lista()","do_listo()"},
	// T_tu_listi
	{"tu_listi()","do_listi()"},
	// T_Letzte
	{"Letzte ","Last "},
	// T_erfolgreich
	{" erfolgreich"," successfully"},
	// T_erfolglos
	{" erfolglos"," unsuccessfully"},
	// T_versandte_Faxe
	{" versandte Faxe:"," sent faxes:"},
	// T_empfangene_Faxe
	{" empfangene Faxe:"," received faxes:"},
	// T_untersuchespool,
	{"untersuchespool()","examinespool()"},
	// T_zeigweitere
	{"zeigweitere()","showothers()"},
	// T_Weitere_Spool_Eintraege
	{"Weitere Spool-Eintraege:","Further spool entries:"},
	// T_sammlecapi
	{"sammlecapi()","collectcapi()"},
	// T_sammlefbox
	{"sammlefbox()","collectfbox()"},
	// T_bereinigefbox
	{"bereinigefbox()","cleanfbox()"},
	// T_bereinigecapi
	{"bereinigecapi()","cleancapi()"},
	// T_Zahl_der_ueberpruefen_Datenbankeintraege
	{" Ueberpruefte Datenbankeintraege: ","No.of reviewed database entries: "},
	// T_davon_gescheiterte_Faxe
	{"... davon      gescheiterte Faxe: ","... thereof        failed faxes: "},
	// T_davon_erfolgreiche_Faxe
	{"... davon      erfolgreiche Faxe: ","... thereof    successful faxes: "},
	// T_davon_noch_wartende_Faxe
	{"... davon     noch wartende Faxe: ","... thereof still waiting faxes: "},
	// T_davon_nicht_in_Warteschlange
	{"... davon nicht in Warteschlange: ","... thereof    not queued faxes: "},
	// T_Verwaiste_Datei
	{"Verwaiste Datei: ","Orphaned file: "},
	// T_geloescht_Fax_schon_in
	{" geloescht (Fax schon in "," deleted (fax already archived in "},
	// T_archiviert_Ausrufezeichen
	{" archiviert)!","!"},
	// T_sammlehyla
	{"sammlehyla()","collecthyla()"},
	// T_gestrichen
	{"gestri.","suspen."},
	// T_schwebend
	{"schweb.","pending"},
	// T_wartend
	{"wartend","waiting"},
	// T_blockiert,
	{"blocki.","blocked"},
	// T_bereit
	{"bereit","ready"},
	// T_verarb
	{"in Arb.","proces."},
	// T_gesandt
	{"gesandt","sent"},
	// T_gescheitert
	{"gescheitert","failed"},
	// T_nicht_in_der_Warteschlange
	{"nicht in der Warteschlange","not in queue"},
	// T_woasined
	{"unbekannt","unknown"},
	// T_setzhylastat
	{"setzhylastat()","sethylastat()"},
	// T_archiviere
	{"archiviere()","archiving()"},
	// T_obgescheitert
	{" obgescheitert: "," failed?: "},
	// T_loeschefbox
	{"loeschefbox()","deletefbox()"},
	// T_loeschecapi
	{"loeschecapi()","deletecapi()"},
	// T_loeschehyla
	{"loeschehyla()","deletehyla()"},
	// T_Loesche_Fax_hylanr
	{"Loesche das Fax mit der hylanr: ","Deleting the fax with the hylano: "},
	// T_erfolgreich_geloescht_fax_mit
	{"Erfolgreich geloescht: Fax mit der hylanr: ","Successfully deleted: Fax with the hylano: "},
	// T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm
	{"Fehlermeldung beim Loeschversuch eines Hyla-Faxes mit `faxrm ","Error while trying to delete a hyla-fax with `faxrm "},
	// T_capiausgeb
	{"capiausgeb()","displaycapitries()"},
	// T_fboxausgeb,
	{"fboxausgeb()","displayfboxtries()"},
	// T_Anwahlen
	{" Anwahlen,"," tries,"},
	// T_kommaDatei
	{",Datei:",",file:"},
	// T_bzw
	{",bzw.:",",and:"},
	// T_hylaausgeb
	{"hylaausgeb()","displayhylatries()"},
	// T_suchestr
	{"suchestr()","searchstr()"},
	// T_mitstr
	{" mit '"," with '"},
	// T_wartende_Faxe
	{" wartende Faxe "," waiting faxes"},
	// T_pruefstdfaxnr
	{"pruefstdfaxnr()","checkstdfaxnr()"},
	// T_prueffuncgettel3
	{"prueffuncgettel3()","checkfuncgettel3()"},
	// T_aendere_fax
	{"aenderefax()","changefax()"},
	// T_Welches_Fax_soll_geloescht_werden
	{"Welches Fax soll geloescht werden (0=Abbruch)","Which fax shall be deleted (0=Cancel)"},
	// T_Welches_Fax_soll_umgeleitet_werden
	{"Welches Fax soll umgeleitet werden (0=Abbruch)","Which fax shall be redirected (0=Cancel)"},
	// T_Soll_das_Fax
	{"Soll das Fax ","Shall the fax "},
	// T_wirklich_geloescht_werden
	{" wirklich geloescht werden"," really be deleted"},
	// T_umgeleitet_werden
	{" umgeleitet werden"," be redirected"},
	// T_Zahl_der_nicht_geloeschten_Dateien
	{"Zahl der nicht geloeschten Dateien: ","No. of not deleted files: "},
	// T_hylanr
	{", hylanr: ",", hylano.: "},
	// T_FBoxspooldatei,
	{", FBoxspooldatei: ",", fbox-spool-file: "},
	// T_Capispooldatei
	{", Capispooldatei: ",", capi-spool-file: "},
	// T_Gesamt
	{"Gesamt: ","Total: "},
	// T_Kein_Fax_zum_Loeschen_vorhanden
	{"Kein Fax zum Loeschen vorhanden","No fax there to be deleted"},
	// T_Kein_Fax_zum_Umleiten_vorhanden
	{"Kein Fax zum Umleiten vorhanden","No fax there to be redirected"},
	// T_empferneut
	{"empferneut()","recvagain()"},
	// T_loeschewaise,
	{"loeschewaise()","deleteorphans()"},
	// T_loescheallewartenden,
	{"loescheallewartenden()","deleteallwaiting()"},
	// T_Welches_Fax_soll_erneut_empfangen_werden_bitte_Nr_in_der_1_Spalte_eingeben_a_alle_Angezeigten
	{"Welches Fax soll erneut empfangen werden (bitte Nr. in der 1.Spalte eingeben, a=alle Angezeigten)",
		"Which Fax shall be received again (please enter the no. in the first column, a=all displayed)"},
	// T_Bearbeite
	{"Bearbeite: ","Processing: "},
	// T_Aus
	{"Aus ","To delete from "},
	// T_zu_loeschen
	{" zu loeschen: ",": "},
	// T_Sollen_wirklich_alle
	{"Sollen wirklich alle ","Shall all "},
	// T_wartenden_Faxe_geloescht_werden
	{" wartenden Faxe geloescht werden?"," waiting faxes really be deleted?"},
	// T_waisen_Faxe_geloescht_werden
	{" waisen Faxe geloescht werden?"," orphan faxes really be deleted?"},
	// T_Keine_waisen_Faxe_zum_Loeschen_da
	{"Keine waisen Faxe zum Loeschen da.","No orphan faxes to be deleted."},
	// T_Keine_wartenden_Faxe_zum_Loeschen_da
	{"Keine wartenden Faxe zum Loeschen da.","No waiting faxes to be deleted."},
// T_inspoolschreiben,
	{"inspoolschreiben()","writetospool()"},
	// T_wegfaxen
	{"wegfaxen()","faxingall()"},
	// T_obfboxmitDoppelpunkt
	{"mitFbox: ","withFbox"},
	// T_obcapimitDoppelpunkt,
	{"mitCapi: ","withCapi: "},
	// T_obhylamitDoppelpunkt
	{"mitHyla: ","withHyla: "},
	// T_obkmailmitDoppelpunkt
	{"mitklarmail: ","withclearmail: "},
	// T_obvmailmitDoppelpunkt
	{"mitvschlmail: ","withencrmail: "},
	// T_Unterverzeichnis
	{"Unterverzeichnis '","Subdirectory '"},
	// T_passt_zu_Muster
	{"' passt zu Muster '","' fits to pattern '"},
	// T_passt_zu_keinem_Muster
	{"' passt zu keinem Muster","' fits to no pattern"},
	// T_war_schon
	{"', war schon: ","', passed: "},
	// T_kommt_noch
	{"', kommt noch: ","', will come: "},
	// T_Endung
	{"Endung: ","Ending: "},
	// T_Stamm
	{"Stamm:  ","Root: "},
	// T_Anfangsteil
	{"Anfangsteil: ","Beginning: "},
	// T_Faxnummer_zu
	{"Faxnummer zu ","Fax number of "},
	// T_gefunden_dp
	{" gefunden: "," found: "},
	// T_Name_zu
	{"Name zu ","Name of "},
	// T_FehlerbeimUmbenennen
	{"Fehler beim Umbenennen!","Error while renaming!"},
	// T_ErstelledurchBenennen
	{"Erstelle durch Benennen: ","Providing by naming: "},
	// T_ErstelledurchKopieren
	{"Erstelle durch Kopieren: ","Providing by copying: "},
	// T_nichtfaxbar
	{"nicht faxbar wg. Benennung","not faxable due to naming"},
	// T_abgebrochen
	{"abgebrochen! ","aborted! "},
	// T_Gesammelt_wurden
	{"Gesammelt wurden: ","Collected were: "},
	// T_aus
	{"aus '","in '"},
	// T_verarbeitete_Nicht_PDF_Dateien
	{"' verarbeitete Nicht-PDF-Dateien: ","' processed Non-PDF-Files: "},
	// T_lstatfehlgeschlagen
	{"lstat fehlgeschlagen: ","lstat failed: "},
	// T_beiDatei
	{" bei Datei:"," at file: "},
	// T_verarbeitete_PDF_Dateien
	{"' verarbeitete       PDF-Dateien: ","' processed     PDF-Files: "},
	// T_beiSQLAbfrage
	{" bei SQL-Abfrage: "," at SQL request: "},
	// T_ZahldDSmwegzuschickendenFaxenin
	{"Zahl der Datensaetze mit wegzuschickenden Faxen in `","No. of data records with enqueued faxes in `"},
	// T_PDFDatei
	{" PDF-Datei: "," PDF file: "},
	// T_Fehler_zu_faxende_Datei
	{"Fehler: zu faxende Datei '","Error: scheduled fax file '"},
	// T_nicht_gefunden_Eintrag_ggf_loeschen_mit_
	{"' nicht gefunden.\n Eintrag ggf. loeschen mit '","' not found.\n Optionally delete entry with '"},
	// T_in_wegfaxen
	{"in wegfaxen, pidw","in faxingall, pidw"},
	// T_in_korrerfolgszeichen
	{"in korrerfolgszeichen, pidw","in correctsuccessflag, pidw"},
	// T_fxinDatenbank
	{"fxinDatenbank()","fxinDatabase()"},
	// T_WVZinDatenbank
	{"WVZinDatenbank()","WDirinDatabase()"},
	// T_inDbc
	{"inDbc()","intoDatabaseCapi()"},
	// T_faxemitH
	{"faxemitH()","faxingwithHyla()"},
	// T_faxemitF
	{"faxemitF()","faxingwithFBox()"},
	// T_inDBh
	{"inDBh()","intoDatabaseHyla()"},
	// T_inDBf
	{"inDBf()","intoDatabaseFBox()"},
	// T_inDBk
	{"inDBk()","intoDatabasemail()"},
	// T_SpoolDateierstellt
	{"Spool-Datei erstellt: '","Generated spool file: '"},
	// T_SpoolDatei
	{" Spool-Datei: '","Spool file: '"},
	// T_SpoolPfad
	{" Spool-Pfad: '"," Spool directory: '"},
	// T_faxemitC
	{"faxemitC()","faxingwithCapi()"},
	// T_DieFaxnrausTabelle
	{"Die Faxnr aus Tabelle `","The fax number from table `"},
	// T_istleerfaxeesdahernicht
	{" ist leer! Faxe es daher nicht."," is empty! Not faxing it therefore."},
	// T_DieFaxnrvon
	{"Die Faxnr von ","The fax number of "},
	// T_ist
	{" ist: "," is: "},
	// T_faxemitCFehler
	{"faxemitC() Fehler: ","faxingwithCapi() Error: "},
	// T_Faxdatei
	{"Faxdatei ","Fax file "},
	// T_fehlt
	{" fehlt."," is missing."},
	// T_hat0Bytes
	{" hat 0 Bytes."," has 0 bytes."},
	// T_Faxbefehl
	{"Faxbefehl","Fax command"},
	// T_nichtgefundenloeschesieausDB
	{") nicht gefunden, loesche sie aus der Datenbank",") not found, deleting it from database"},
	// T_nicht_gefunden_kein_Datenbankeintrag
	{"' nicht gefunden, kein Datenbankeintrag!"," not found, no database entry!"},
	// T_HylafaxBefehl
	{"Hylafax-Befehl","Hylafax command"},
	// T_FbfaxBefehl
	{"fbfax-Befehl","fbfax command"},
	// T_RueckmlgZeile
	{"Rueckmldg.Zeile: ","Response line: "},
	// T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Erfolg_gesetzt_werden,
	{"Bei folgenden Faxen mußte das Erfolgskennzeichen gemaess Hylafax-Protkolldatei auf Erfolg gesetzt werden:",
		"For the following faxes, the success-flag had to be set to success following the hylafax logfile:"},
	// T_Dateidatum
	{"Dateidatum","file date"},
	// T_pages
	{"Seiten","pages"},
	// T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Misserfolg_gesetzt_werden
	{"Bei folgenden Faxen musste das Erfolgskennzeichen gemaess Hylafax-Protkolldatei auf Misserfolg gesetzt werden:",
		"For the following faxes, the success-flag had to be set to failure following the hylfax logfile:"},
	// T_Insgesamt,
	{"Insgesamt ","In total "},
	// T_Fundstellen_von,
	{" Fundstellen von "," references of "},
	// T_Keine_Fundstellen_von
	{"Keine Fundstellen von ","No references of "},
	// T_nurempf_k,
	{"nurempf","reconly"},
	// T_nurempf_l,
	{"nurempfangen","receiveonly"},
	// T_empfaengt_nur,
	{"empfaengt nur","receives only"},
	// T_nursend_k,
	{"nursend","sndonly"},
	// T_nursend_l,
	{"nursenden","sendonly"},
	// T_sendet_nur,
	{"sendet nur","sends only"},
	// T_instsfftobmp,
	{"instsfftobmp()","instsfftobmp()"},
  // T_kompilier,
	{"kompilier()","compile()"},
	// T_nextnum,
	{"nextnum()","nextnum()"},
	// T_scheitere,
	{"scheitere()","fail()"},
	// T_korrigierehyla,
	{"korrigierehyla()","correcthyla()"},
	// T_oder_
	{" oder "," or "},
	// T_bzw_
	{"' bzw. '","' resp. '"},
	// T_std_mailtit,
	{"Mail von " DPROG,"mail from " DPROG},
	// T_std_mailbod,
	{"bitte Anhang beachten","please look at the attachment"},
	// T_fax_auf_allen_Wegen_schicken_uml
	{"1=Fax_auf_allen Wegen schicken (-uml)","1=send fax on all channels (--redirect)"},
	// T_mail_gesandt_0_nein_1_ja,
	{"mail gesandt (0=nein, 1=ja)","mail sent (0=no, 1=yes)"},
	// T_Prioritaet_von_capisuite_1_3,
	{"Prioritaet von capisuite (1-3)","Priority of capisuite (1-3)"},
	// T_Prioritaet_von_hylafax_1_3,
	{"Prioritaet von hylafax (1-3)","Priority of hylafax (1-3)"},
	// T_Prioritaet_von_fritzbox_1_3,
	{"Prioritaet von fritzbox (1-3)","Priority of fritzbox (1-3)"},
	// T_cp_k,
	{"cp","cp"},
	// T_cprio_l,
	{"cprio","cprio"},
	// T_hp_k,
	{"hp","hp"},
	// T_hprio_l,
	{"hprio","hprio"},
	// T_fp_k,
	{"fp","fp"},
	// T_fprio_l,
	{"fprio","fprio"},
	// T_Mit_welcher_Prioritaet_soll_capisuite_verwendet_werden_1_3,
	{"Mit welcher Prioritaet soll capisuite verwendet werden (1-3)","With which priority shall capisuite be used (1-3)"},
	// T_Mit_welcher_Prioritaet_soll_hylafax_verwendet_werden_1_3,
	{"Mit welcher Prioritaet soll hylafax verwendet werden (1-3)","With which priority shall hylafax be used (1-3)"},
	// T_Mit_welcher_Prioritaet_soll_fritzbox_verwendet_werden_1_3,
	{"Mit welcher Prioritaet soll fritzbox verwendet werden (1-3)","With which priority shall fritzbox be used (1-3)"},
  // T_sortprio,
	{"sortprio()","sortprio()"},
	// T_standardprio,
	{"standardprio()","standardprio()"},
	// T_fstab_Eintrag_wieder_entfernen,
	{"fstab-Eintrag wieder entfernen","delete fstab-entry"},
	// T_Sollen_alle_Faxe_umgeleitet_werden
	{"Sollen alle Faxe umgeleitet werden","Shall all faxes be redirected"},
	// T_cpneu_k,
	{"cpneu","cpnew"},
  // T_cpneu_l,
	{"cpneu","cpnew"},
	// T_Capisuite_neu_einrichten,
	{"Capisuite neu einrichten", "install capisuite again"},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

struct TxB Tx((const char* const* const* const*)DPROG_T);
const char sep = 9; // geht auch: "[[:blank:]]"
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;
pidvec pidw; // wird zweimal verwendet, um auf Kindprozesse zu warten: in wegfaxen (auf die Faxarten) und in pvirtfueraus (auf korrigierefbox, -capi und -hyla
const unsigned ktage=1; // kurzes Intervall fuer Faxtabellenkorrektur, 1 Tag
const unsigned mtage=30; // mittleres Intervall fuer Faxtabellenkorrektur, 1 Monat
const unsigned ltage=73000; // langes Intervall fuer Faxtabellenkorrektur, 200 Jahre

using namespace std; //ω

const string cSQL_{"SQL_"}, cZMMuster_{"ZMMuster_"}, cZMZiel_{"ZMZiel_"};

// fürs Debugging
inline int dfork() {
	return fork();
}

// aufgerufen in: verschiebe (Version 1), verschiebe (Version 2), inspoolschreiben
// ziel kann Verzeichnis oder Datei sein; im ersten Fall wird eine Datei des Namens von quelle dort als *zielp verwendet
// wenn quelle und zielp identisch sind, tut dorename() nichts, ansonsten:
// verschiebt oder benennt um; prueft nicht auf etwa schon vorhandenes Ziel,
// aber wenn mit 'schonda' Vorhandensein und Gültigkeit des Ziels signalisiert wird, so wird statt dessen die Quelle gelöscht,
void dorename(const string& quelle, const string& ziel, const string& cuser/*=nix*/, uint *vfehlerp/*=0*/, uchar schonda/*=0*/,
		int obverb/*=0*/, int oblog/*=0*/, stringstream *ausgp/*=0*/)
{
	//  hLog(violetts+Tx[T_dorename]+schwarz);
	const string meld{Tx[T_Verschiebe]+tuerkiss+quelle+schwarz+"'\n         -> '"+gruen+ziel+schwarz+"'"};
	unsigned fehler{0};
	if (ausgp&&obverb) *ausgp<<meld<<endl; else fLog(meld,obverb,oblog);
	string *zielp{(string*)&ziel},ersatzziel;
	struct stat zstat{0};
	// wenn das Ziel ein Verzeichnis ist, Dateinamen anhaengen
	if (!lstat(ziel.c_str(),&zstat)&&S_ISDIR(zstat.st_mode)) {
		ersatzziel=ziel;
		kuerzevtz(&ersatzziel);	
		ersatzziel+=vtz;
		ersatzziel+=base_name(quelle);
		zielp=&ersatzziel;
	} // 	if (!lstat(ziel.c_str(),&zstat)&&S_ISDIR(zstat.st_mode))
	uchar obident{0};
	if (char* act1=realpath(quelle.c_str(),NULL)) {
		if (char* act2=realpath(zielp->c_str(),NULL)) {
			if (!strcmp(act1,act2))
				obident=1;
			free(act2);
		} // 		if (char* act2=realpath(ziel.c_str(),NULL))
		free(act1);
	} // 	if (char* act1=realpath(quelle.c_str(),NULL))
	if (!obident) {
		if (schonda) {
			if (const int erg{tuloeschen(quelle.c_str(),cuser,obverb,oblog,ausgp)}) {
				fehler+=erg;
			}
		} else {
			for(uchar iru=1;iru<3;iru++) {
				if (rename(quelle.c_str(),zielp->c_str())) {
					if(cuser.empty()) iru++;
					if(iru==1) {
						setfaclggf(dir_name(quelle),obverb>0?obverb-1:0,oblog,/*obunter=*/wahr,/*mod=*/7,/*obimmer=*/1,
								/*faclbak=*/1,/*user=*/nix,/*fake=*/0,ausgp);
					} else if (!schonda) {
						perror((Tx[T_Fehler_beim_Verschieben]+quelle+" -> "+ziel).c_str());
						const string cmd{sudc+"mv \""+quelle+"\" \""+*zielp+"\""};
						const int erg{systemrueck(cmd,obverb,1)};
						fehler+=erg;
					} // if(iru) else
				} // if (rename(quelle.c_str(),zielp->c_str())) 
				else break;
			} // for(uchar iru=1;iru>-1;iru--)
		} // 	if (schonda)
	} // 	if (!obident)
	if (fehler) {
		cerr<<rot<<fehler<<schwarz<<" = "<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<blau<<quelle<<schwarz<<" ->\n"<<blau<<ziel<<schwarz<<endl;
	} // if (fehler)
	if (vfehlerp) *vfehlerp=fehler;
} // dorename

// aufgerufen in inspoolschreiben, main, kopiere (2), wandle, empfhyla, empfcapi
string kopiere(const string& qdatei, const string& zield, uint *kfehler, const uchar wieweiterzaehl, int obverb, int oblog)
{
	//  hLog(violetts+Tx[T_kopiere]+schwarz);
	// wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
	int fehler{0},
			efeh{0};
	auto const altobverb{obverb};
	obverb=2;
	////	if (is_same<decltype(zield),const std::string&>::value) KLA
	// nur zur Sicherheit, eigentlich sollte mit Verzeichnis kopier(... direkt aufgerufen werden
	struct stat zstat{0};
	string zieldt{zield};
	if (!lstat(zieldt.c_str(),&zstat)) {
		if (S_ISDIR(zstat.st_mode)) {
			if (zieldt[zieldt.length()-1]!='/') zieldt+='/';
			zieldt+=base_name(qdatei);
		}
	}
	const string dir{dir_name(zieldt)},
				base{base_name(zieldt)};
	string ziel;
	uchar obgleich{0};
	if (!base.empty() && !dir.empty()) {
		ziel=zielname(base,dir,wieweiterzaehl,/*zieldatei=*/0,&obgleich,obverb,oblog);
		fLog(Tx[T_Kopiere_Doppelpunkt]+rots+qdatei+schwarz+"'\n         -> '"+rot+ziel+schwarz+"'",obverb,oblog);
		if ((efeh=kopier(qdatei,ziel,obverb,oblog))) {
			fehler+=efeh;
			fLog(rots+Tx[T_Fehler_beim_Kopieren]+Tx[T_Dateiname]+blau+zieldt+schwarz,1,1);
		} // if (efeh=kopier(qdatei,ziel,obverb,oblog))
	} else {
		fLog(rots+Tx[T_Fehler_beim_Kopieren]+Tx[T_Dateiname]+blau+zieldt+schwarz+Tx[T_schlechtgeformt],1,1);
	} // if (!base.empty() && !dir.empty())  else 
	if (kfehler) *kfehler=fehler;
	obverb=altobverb;
	return ziel;
	////	KLZ
	////	return nix;
} // string kopiere

// aufgerufen in inspoolschreiben
string kopiere(const string& qdatei, const vector<shared_ptr<zielmustercl>>& zmsp, uint *kfehler, const uchar wieweiterzaehl, int obverb, int oblog) 
{
	//  hLog(violetts+Tx[T_kopiere]+schwarz);
	// wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
	uchar obgleich{0};
	const string ziel{zielname(qdatei,zmsp,wieweiterzaehl,/*zieldatei=*/0,&obgleich,obverb,oblog)};
	return kopiere(qdatei, ziel, kfehler, wieweiterzaehl,obverb,oblog);
} // string kopiere


// passt einen Dateinamen gemaess der vorhandenen Dateien in allen moeglichen Zielverzeichnissen so an
// dass er beim Umwandeln in PDF und Verschieben als erfolgreiches oder nicht erfolgreiches Fax sich nicht ueberschneidet
// aufgerufen in: inspoolschreiben (2x)
string hhcl::neuerdateiname(const string& qpfad)
{
	string dateiname{qpfad}, altdname, stamm, exten, extu;
	loeschealleaus(&dateiname,"'");
	loeschealleaus(&dateiname,"\"");
	for(unsigned runde=0;runde<2;runde++) {
		for(unsigned aru=0;1;aru++) {
			dateiname=base_name(dateiname);
			if (dateiname==altdname) break;
			altdname = dateiname;
			uchar obgleich{0};
			dateiname=zielname(dateiname,wvz,/*wieweiterzaehl=*/1,/*zieldatei=*/0,&obgleich,obverb,oblog);
			dateiname=zielname(dateiname,ngvz,/*wieweiterzaehl=*/1,/*zieldatei=*/0,&obgleich,obverb,oblog);
			dateiname=zielname(dateiname,zmsp,/*wieweiterzaehl=*/1,/*zieldatei=*/0,&obgleich,obverb,oblog);
		} //     for(unsigned aru=0;1;aru++)
		getstammext(&dateiname,&stamm,&exten);
		if (!runde) extu=exten; 
		else break;
		const string pdf{stamm+".pdf"};
		if (pdf==dateiname) break;
		else dateiname=pdf;
	} //   for(unsigned runde=0;runde<2;runde++)
	return base_name(stamm+"."+extu);
} // neuerdateiname


// ermittelt fuer eine in ein Zielverzeichnis zu kopierende Datei den dortigen Namen
// falls obgleichp, wird darin gespeichert, ob die Datei dort schon vorhanden und identisch ist (in diesem Fall wird kein anderer Name ermittelt)
// sonst wird, wenn wieweiterzaehl<2 ist, im Fall des Vorhandenseins im Zielverzeichnis ein neuer Name gefunden
// aufgerufen in verschiebe (Version 1) und kopiere (Version 1), neuerdateiname, zielname (Version 2)
string zielname(const string& qdatei, const string& rzielvz, uchar wieweiterzaehl/*=0*/, string* zieldatei/*=0*/, uchar *obgleichp/*=0*/,
		int obverb/*=0*/, int oblog/*=0*/, stringstream *ausgp/*=0*/)
{
	//  hLog(violetts+Tx[T_zielname]+schwarz);
	// wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
	string dateiname{base_name(qdatei)};
	struct stat st{0};
	string ziel,zielvz=rzielvz;
	if (lstat(zielvz.c_str(),&st)||!S_ISDIR(st.st_mode)) {
		ziel=zielvz;
		zielvz=dir_name(zielvz);
	} else {
		ziel=zielvz+(zielvz[zielvz.length()-1]==vtz?"":vtzs)+dateiname;
	}
	// auf Gleichheit testen
	if (obgleichp) *obgleichp=!dateivgl(qdatei,ziel);
	string meld{Tx[T_zielname_erstes_Ziel]+rots+ziel+schwarz+"'"+(obgleichp&&*obgleichp?Tx[T_Quelle_und_Ziel_gleich]:"")};
	if (ausgp&&obverb) *ausgp<<meld<<endl; else fLog(meld,obverb,oblog);
	if (!(obgleichp&&*obgleichp)) {
		if (wieweiterzaehl<2) {
			ulong ausweich{0};
			uchar ausgewichen{0};
			string stamm,exten;
			for(;1;) {
				struct stat entryziel{0};
				if (lstat(ziel.c_str(), &entryziel)) break;
				// in der Schleife nur beim ersten Mal aufrufen
				if (!ausgewichen) {
					getstammext(&dateiname,&stamm,&exten); // kommt hier außer bei obgleich immer vorbei
					// wenn von einer vorhandenen Ausweichnummerierung aus weitergezaehlt werden soll (anstatt dateiname_1_1 ...)
					if (wieweiterzaehl) {
						size_t pos = stamm.rfind('_');
						if (pos!=string::npos) {
							const string auswstr{stamm.substr(pos+1)};
							if (isnumeric(auswstr)) { 
								ausweich=atol(auswstr.c_str());
								if (ausweich) if (stamm.length()>pos) stamm.erase(pos);
							}
						} // if (pos!=string::npos) 
					} // if (wieweiterzaehl) 
				}
				ausweich++;
				ausgewichen=1;
				dateiname=stamm+"_"+ltoan(ausweich)+"."+exten;
				ziel=zielvz + (zielvz[zielvz.length()-1]==vtz?"":vtzs) + dateiname;
			} // for(;1;) 
			if (ausgewichen) {
				meld=Tx[T_zielname_Ausweichziel]+rots+ziel+schwarz+"'";
				if (ausgp&&obverb) *ausgp<<meld<<endl; else fLog(meld,obverb,oblog);
			}
		} // if (wieweiterzaehl<2) 
	} // 	if (obgleichp&&*obgleichp)
	if (zieldatei) *zieldatei=dateiname;
	return ziel;
} // zielname 

// aufgerufen in: verschiebe (Version 2), kopiere (Version 2), neuerdateiname, 
string zielname(const string& qdatei, const vector<shared_ptr<zielmustercl>>& zmup, uchar wieweiterzaehl/*=0*/, string* zieldatei/*=0*/, uchar *obgleichp/*=0*/, 
		int obverb/*=0*/, int oblog/*=0*/, stringstream *ausgp/*=0*/)
{
	//  hLog(violetts+Tx[T_zielname]+schwarz);
//	for(const zielmustercl *zmakt=&zmup;1;zmakt++){
	for(auto zmakt:zmup) {
		const int reti{regexec(&(zmakt->regex),qdatei.c_str(),0,NULL,0)};
		const string meld{Txk[T_datei]+rots+qdatei+schwarz+Tx[T_entspricht]+(reti?Tx[T_entsprichtnicht]:Tx[T_entsprichtdoch])+
			Tx[T_Muster_Doppelpunkt]+rot+zmakt->muster+schwarz+"'"};
		if (ausgp&&obverb) *ausgp<<meld<<endl; else fLog(meld,obverb,oblog);
		if (!reti){
			return zielname(qdatei,zmakt->ziel,wieweiterzaehl,zieldatei,obgleichp,obverb,oblog,ausgp);
		} //     if (!reti)
//		if (zmakt->obmusterleer()) break;
	} //   for(zielmustercl *zmakt=zmup;1;zmakt++)
	return {};
} // zielname

// von fkn-systems
const char * const rulesdt="/etc/udev/rules.d/46-FKN_isdn_capi.rules";
// aufgerufen in: hhcl::pruefcapi
void pruefrules(int obverb, int oblog) 
{
	fLog(violetts+Tx[T_pruefrules]+schwarz,obverb>0?obverb-1:0,oblog);
	struct stat entrybuf{0};
	if (lstat(rulesdt, &entrybuf)) { 
		mdatei rules(rulesdt,ios::out);
		if (rules.is_open()) {
			rules<<"# Symlink (capi20 -> capi) zu"<<endl;
			rules<<"# Kompatibilitaetszwecken erstellen"<<endl;
			rules<<"KERNEL==\"capi\", SYMLINK=\"capi20\""<<endl;
		} //     if (rules.is_open())
	} //   if (lstat(rulesdt, &entrybuf))
} // void pruefrules() {

const string blackdt{"/etc/modprobe.d/50-blacklist.conf"};
// aufgerufen in: pruefcapi
void pruefblack(int obverb, int oblog) 
{
	fLog(violetts+Tx[T_pruefblack]+schwarz,obverb>0?obverb-1:0,oblog);
	const char* vgl[]{"blacklist avmfritz", "blacklist mISDNipac"};
	uchar obda[]{0}, 
				obeinsfehlt{0};
	mdatei blacki(blackdt,ios::in);
	if (blacki.is_open()) {
		string zeile;
		while(getline(blacki,zeile)) {
			for(unsigned i=0;i<elemzahl(vgl);i++) {
				if (zeile.find(vgl[i])!=string::npos) obda[i]=1;
			}
		} //     while(getline(blacki,zeile))
		blacki.close();
		for(unsigned i=0;i<elemzahl(vgl);i++) {
			if (!obda[i]) {obeinsfehlt=1;break;}
		} //     for(unsigned i=0;i<elemzahl(vgl);i++)
		if (obeinsfehlt) {
			mdatei blacka(blackdt,ios::out|ios::app);
			if (blacka.is_open()) {
				for(unsigned i=0;i<elemzahl(vgl);i++) {
					if (!obda[i]) {
						fLog(Tx[T_haengean]+blaus+blackdt+schwarz+Tx[T_an_mdpp]+gruen+vgl[i]+schwarz,obverb,oblog);
						blacka<<vgl[i]<<endl;
					}
				} // for(unsigned i=0;i<elemzahl(vgl);i++) 
			} // if (blacka.is_open()) 
		} // obeinsfehlt
	} else {
	} // if (blacki.is_open())  else
} // void pruefblack(int obverb, int oblog) 

constexpr const char *hhcl::moeglhvz[2];
// aufgerufen in pruefsfftobmp und empfcapi
void hhcl::instsfftobmp()
{
	hLog(violetts+Tx[T_instsfftobmp]+schwarz);
	const uchar obboostda{!linstp->doggfinst("boost-devel",obverb,oblog)};
	if (obboostda) {
		const string sff{"sfftobmp_copy"};
		holvomnetz(sff);
		const string vorcfg{"sed -i.bak -e \"s/^[[:blank:]]*\\(char \\*shortopts.*\\)/const \\1/;"
			"s/m_vFiles.push_back( fs::path(m_argv\\[n\\].*/m_vFiles.push_back( fs::path(string(m_argv[n])\\/*, fs::native*\\/) );"
			"/\" src/cmdline.cpp"
			"&& sed -i.bak -e \"s/lboost_filesystem-mt/lboost_filesystem/g\" src/Makefile.in "
			////                      " && sed -i.bak -e 's/-${am__api_version}//g' aclocal.m4 "
			////                      " && sed -i.bak -e 's/-${am__api_version}//g' configure "
			"&& sed -i.bak -e \"s/\\(-lboost_filesystem\\)/-lboost_system \\1/g\" src/Makefile.in "};
		kompiliere(sff,s_gz,vorcfg);
	} // 	if (obboostda)
} // void instsfftobmp


zielmustercl::zielmustercl(const char * const vmuster,const char * const vziel):muster(vmuster),ziel(vziel)
{
	kompilier();
};  // zielmustercl

zielmustercl::zielmustercl(const char * const vmuster,const string& vziel):muster(vmuster),ziel(vziel)
{
	kompilier();
};  // zielmustercl

zielmustercl::zielmustercl(const string& vmuster,const string& vziel):muster(vmuster),ziel(vziel)
{
	kompilier();
};  // zielmustercl

zielmustercl::zielmustercl() 
{
}

int zielmustercl::kompilier(const uchar obext/*=1*/) 
{
//	fLog(violetts+Tx[T_kompilier]+schwarz,obverb,oblog);
	const int reti{regcomp(&regex, muster.c_str(),obext?REG_EXTENDED|REG_ICASE:RE_SYNTAX_ED|REG_ICASE)}; 
	if (reti) {
		const int MAX_ERROR_MSG{0x1000};
		char error_message[MAX_ERROR_MSG];
		regerror (reti, &regex, error_message, MAX_ERROR_MSG);
		fLog(Tx[T_Der_regulaere_Ausdruck]+drots+muster+schwarz+Tx[T_konnte_nicht_kompiliert_werden_Fehler]+error_message,1,0);
		return 1;
	} //   if (reti)
	return 0;
} // zielmustercl::zielmustercl

int zielmustercl::setzemuster(const string& vmuster,const uchar obext/*=1*/)
{
	muster=vmuster;
	return kompilier(obext);
} // int zielmustercl::setzemuster(const string& vmuster)

int zielmustercl::obmusterleer() const
{
	return muster.empty();
} // int zielmustercl::obmusterleer() 

const string& zielmustercl::holmuster() const
{
	return muster;
} // const string& zielmustercl::holmuster()

const string& zielmustercl::holziel() const
{
	return ziel;
} // const string& zielmustercl::holziel()


hhcl::hhcl(const int argc, const char *const *const argv):dhcl(argc,argv,DPROG,/*mitcron*/1) //α
{
	hLog(violetts+"hhcl::hhcl()"+schwarz);
	// mitpids=1;
 // mitcron=0; //ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω

// in virtVorgbAllg, pruefcapi
void hhcl::liescapiconf()
{
	hLog(violetts+Tx[T_liescapiconf]+schwarz);
	svec qrueck;
	const string wo{"/etc/capisuite /usr/local/etc/capisuite"},
				moegl{"find "+wo+" -type f -name "};
	if (findv==1) {
		systemrueck(moegl+"fax.conf",obverb-2,oblog,&qrueck,/*obsudc=*/0);
	} else findfile(&qrueck,findv,obverb,oblog,0,wo,/*muster=*/"/fax\\.conf$");
	if (qrueck.size()) cfaxconfdt=qrueck[0];
	if (!cfaxconfdt.empty()) {
		pruefverz(dir_name(cfaxconfdt),obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0);
		if (!cfcnfCp) {
			vector<aScl> vecta{
					{"spool_dir",&spoolcapivz},
					{"fax_user_dir",&cfaxuservz},
					{"send_tries",&maxcdials},
					{"send_delays",&send_delays},
					{"outgoing_MSN",&outgoing_MSN},
					{"dial_prefix",&dial_prefix},
					{"fax_stationID",&fax_stationID},
					{"fax_headline",&fax_headline},
					{"fax_email_from",&fax_email_from},
					{"outgoing_timeout",&outgoing_timeout},
				};
			cfcnfCp=new schAcl<WPcl>("cfcnfC", &vecta);
		}
		if (cfaxcp) delete cfaxcp;
		cfaxcp = new confdcl(cfaxconfdt,obverb);
		cfaxcp->kauswert(cfcnfCp);
		//		cfaxcp->Abschn_auswert(obverb);
#ifdef false
		cfcnfA.init(10,"spool_dir","fax_user_dir","send_tries","send_delays","outgoing_MSN",
				"dial_prefix","fax_stationID","fax_headline","fax_email_from","outgoing_timeout");
		if (!cfaxconfdt.empty()) {
			pruefverz(dir_name(cfaxconfdt),obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0);
			static confdat cfaxcd(cfaxconfdt,&cfcnfA,obverb);
			cfaxcdtp=&cfaxcd;
			cfaxcdtp->Abschn_auswert(obverb);
		}
#endif
		// wenn sich cuser in cfaxcd findet, dann so lassen
			// wenn nicht, dann:
			//   wenn cuser leer, dann den ersten besten user nehmen
			//   sonst cuser setzen
			////    cuser="";
		string ncuser;
		for(size_t i=cfaxcp->zn.size();i>0;) {
			char buf[250]{0};
////			if (!cfaxcp->zn[i-1].find("[MailFax")) break; // 18.6.18: MailFaxReceived, MailFaxFailed, MailFaxSent
			if ((sscanf(cfaxcp->zn[--i].c_str(),"[%[^]]]",buf))>0) { 
				if (getpwnam(buf)&&strcasecmp(buf,"global")) {
					if (!cuser.empty()) {
						if (cuser==buf) {
							ncuser.clear();
							break;
						} //            if (cuser==buf)
					} //           if (!cuser.empty())
					if (ncuser.empty()) ncuser=buf; // nehme den letzten besten user
				} //         if (strcasecmp(buf,"global"))
			} // 			if ((sscanf(cfaxcp->zn[--i].c_str(),"[%[^]]]",buf))>0)
		} //     for(size_t i=cfaxcp->zn.size();i>0;)
		if (cuser.empty()) 
			cuser=ncuser;
		if (cuser.empty()) {
			if (cus.cuid)
				cuser=cus.cusstr;
			// hylazuerst=1;
			obfa[1]=0; // 19.6.19
			obher[1]=0; // 16.9.20
			obweg[1]=0; // 16.9.20
		} //     if (cuser.empty())
	} //   if (!cfaxconfdt.empty())
	if (spoolcapivz.empty()) {
		spoolcapivz="/var/spool/capisuite";
	} else {
		kuerzevtz(&spoolcapivz);
	}
	cempfavz=spoolcapivz+"/" DPROG "arch";
	if (cfaxuservz.empty()) {
		cfaxuservz=spoolcapivz+"/users";
	} else {
		kuerzevtz(&cfaxuservz);
	}
	//// <<rot<<"cfaxuservz in Vorgallg: "<<cfaxuservz<<schwarz<<endl;
	qrueck.clear();
	int vorlfindv{3}; // findv wird erst spaeter festgelegt
	if (vorlfindv==1) {
		systemrueck(moegl+"capisuite.conf",obverb-2,oblog,&qrueck,/*obsudc=*/0);
	} else findfile(&qrueck,vorlfindv,obverb,oblog,0,wo,/*muster=*/"/capisuite\\.conf$");
	if (qrueck.size()) {
		ccapiconfdt=qrueck[0];
	} //   if (qrueck.size())
	if (!ccapiconfdt.empty()) {
		static uchar cczulesen{1};
		struct stat cstat{0};
		static time_t lgelzeit{0}; // Aenderungszeitpunkt der evtl. zuletzt eingelesenen ccapiconfdt
		if (!lstat(ccapiconfdt.c_str(),&cstat)) { //// <<rot<<ccapiconfdt<<" existiert!"<<schwarz<<endl;
			const time_t aktgelzeit{cstat.st_mtime};
			if (aktgelzeit>lgelzeit) {
				lgelzeit=aktgelzeit;
				cczulesen=1;
			} //       if (aktgelzeit>lgelzeit)
		} // if (!lstat(ccapiconfdt.c_str(),&cstat)) 
		if (cczulesen) {
			pruefverz(dir_name(ccapiconfdt),obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0);
			if (!cccnfCp) {
				vector<aScl> vecta {
					{"incoming_script",&cdn[0]},
						{"log_file",&cdn[1]},
						{"log_error",&cdn[2]},
						{"idle_script",&cdn[3]}
				};
				cccnfCp=new schAcl<WPcl>("cccnfC", &vecta);
			}
			confdcl ccapc(ccapiconfdt,obverb);
			////<<"azaehlerdt: "<<blau<<azaehlerdt<<schwarz<<endl;
			ccapc.kauswert(cccnfCp);
			cczulesen=0;
			if (!cuser.empty()) {
				for(size_t j=0;j<elemzahl(cdn);j++) {
					if (!cdn[j].empty()) {
						//// <<"cdn["<<j<<"]: "<<cdn[j]<<endl;
						struct stat statdat{0};
						if (!lstat(cdn[j].c_str(),&statdat)) {
							setfaclggf(cdn[j],obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/6);
						} //             if (!lstat(cccnfA[j].wert.c_str(),&statdat))
					} // if (!cccnfA[j].wert.empty()) 
				} // for(size_t j=1;j<3;j++) 
			} // if (!cuser.empty()) 
#ifdef false
			if (!cccnfA.zahl) {
				cccnfA.init(4,"incoming_script","log_file","log_error","idle_script");
			} else {
				cccnfA.reset();
			} //       if (!cccnfA.zahl) else
			confdat ccapicd(ccapiconfdt,&cccnfA,obverb);
			if (!cuser.empty()) {
				for(size_t j=0;j<cccnfA.zahl;j++) {
					if (!cccnfA[j].wert.empty()) {
						struct stat statdat{0};
						if (!lstat(cccnfA[j].wert.c_str(),&statdat)) {
							setfaclggf(cccnfA[j].wert,obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/6);
						} //             if (!lstat(cccnfA[j].wert.c_str(),&statdat))
					} // if (!cccnfA[j].wert.empty()) 
				} // for(size_t j=1;j<3;j++) 
			} // if (!cuser.empty()) 
#endif
		} // if (cczulesen)
	} // if (!ccapiconfdt.empty())

	if (!spoolcapivz.empty()) {
		cdonevz = mitvtz(spoolcapivz)+"done";
		cfailedvz = mitvtz(spoolcapivz)+"failed";
	} //   if (!spoolcapivz.empty())
} // void hhcl::liescapiconf

// wird  aufgerufen in: pruefcapi
void hhcl::konfcapi()
{
	hLog(violetts+Tx[T_konfcapi]+schwarz+", ccapiconfdt: "+violett+ccapiconfdt+schwarz);
	// Zahl der Klingeltoene in capisuite einstellen
	/*//
		cppSchluess cccnfA[]={{"incoming_script"}};
		size_t cs=elemzahl(cccnfA);
	 */
	//// <<"cccnfA[0].wert: "<<cccnfA[0].wert<<endl;
	if (!cdn[0].empty()) {
		systemrueck("sed -i$(test -f "+cdn[0]+".orig||echo '.orig') "
				"'s/\\(^.*connect_faxG3.*headline\\).*\\().*$\\)/\\1,"+cklingelzahl+"\\2/' "+cdn[0],obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
	}
	////    if (cpplies(ccapiconfdt,cccnfA,cs)) KLA
	/*//
		mdatei f(cccnfA[0].wert,ios::in); // /usr/lib64/capisuite/incoming.py
		if (f.is_open()) KLA
		string zeile;
		const char* searchstr="connect_faxG3(";
	// <<rot<<"Lese: "<<cccnfA[0].wert<<schwarz<<endl;
	while(getline(f,zeile)) KLA
	size_t nk=zeile.find(searchstr);
	if (nk!=string::npos) KLA
	nk+=strlen(searchstr);
	const char* headline="headline";
	size_t nkh=zeile.find(headline,nk);
	if (nkh!=string::npos) KLA
	nkh+=strlen(headline);
	size_t klap=zeile.find(')',nkh-1);
	if (klap!=string::npos) KLA
	string nkz=zeile.substr(nkh+1,klap-nkh); // das , nach headline
	if (nkz!=cklingelzahl) KLA
	string neuzeile=zeile.substr(0,nkh)+","+cklingelzahl+zeile.substr(klap);
	string neudatei=string(cccnfA[0].wert)+"_neu";
	f.close();
	mdatei fneu(neudatei,ios::out);
	mdatei falt(cccnfA[0].wert,ios::in);
	if (falt.is_open()) if (fneu.is_open()) KLA
	while(getline(falt,zeile)) KLA
	nk=zeile.find(searchstr);
	if (nk!=string::npos) KLA
	fneu<<neuzeile<<endl;
	KLZ else KLA
	fneu<<zeile<<endl;
	KLZ 

	KLZ // while(getline(falt,zeile)) 
	struct stat entryorig{0};
	string origdatei=string(cccnfA[0].wert)+"_orig";
	if (lstat(origdatei.c_str(),&entryorig)) KLA
	dorename(cccnfA[0].wert,origdatei,cuser,0,obverb,oblog);
	KLZ else KLA
	tuloeschen(cccnfA[0].wert,cuser,obverb,oblog);
	KLZ            
	dorename(neudatei,cccnfA[0].wert,cuser,0,obverb,oblog); 
	KLZ  // if (falt.is_open()) if (fneu.is_open()) 
	break;
	KLZ // if (nkz!=cklingelzahl) 
	KLZ // if (klap!=string::npos) 
	KLZ //           if (nkh!=string::npos) KLA
	KLZ // if ((nkz=strstr(zeile,searchstr))) 
	KLZ // while(getline(f,zeile)) 
	KLZ // if (f.is_open()) 
	KLZ // if (cpplies(ccapiconfdt,cccnfA,cs)) 
	 */
	////  static cppSchluess cfcnfA[]=KLA KLA"spool_dir"KLZ,KLA"fax_user_dir"KLZ,KLA"send_tries"KLZ,KLA"send_delays"KLZ,
	////         KLA"outgoing_MSN"KLZ,KLA"dial_prefix"KLZ,KLA"fax_stationID"KLZ,KLA"fax_headline"KLZ,KLA"fax_email_from"KLZ KLZ;
	//// fax_stationID
	uchar capicffehlt{0};
	// //<<rot<<"fax_stationID: '"<<fax_stationID<<"'"<<schwarz<<endl;
	if (fax_stationID.find("000 0000")!=string::npos || fax_stationID.empty()) {
		////    if (cfax_stationID.find("000 0000")!=string::npos) 
		////    fLog(string("Capisuite ist offenbar noch nicht konfiguriert(")+blau+"fax_stationID"+schwarz+" enthaelt '000 0000').\n"
		////        "Die Einstellung koennen spaeter in "+blau+cfaxconfdt+schwarz+" geaendert werden.",1,0);
		::fLog(Tx[T_Capisuite_ist_offenbar_noch_nicht_richtig_konfiguriert]+blaus+"'fax_stationID'"+schwarz+Tx[T_ist_Apostroph]+blau+
				fax_stationID+schwarz+"')."+ Tx[T_Die_Einstellungen_koennen_spaeter_in]+blau+cfaxconfdt+schwarz+Tx[T_geaendert_werden],1,1);
		// fax_stationID
		capicffehlt=1;
	} // if (fax_stationID.find("000 0000")!=string::npos || fax_stationID.empty()) 
	if (rzf || (capicffehlt && !nrzf)) {
		while (fax_stationID.find("000 0000")!=string::npos || !istelnr(fax_stationID)) {
			fax_stationID="+"+countrycode+" "+citycode+" "+msn;
			fax_stationID=Tippstr(string("fax_stationID: ")+Tx[T_Faxnr_die_zum_Adressaten_gesandt_wird_bis_20_Zeichen_nur_plus_und_Ziffern],
					&fax_stationID);
		}
		vector<string> tok;
		aufSplit(&tok,fax_stationID,' ');
		// outgoing_MSN
		outgoing_MSN=msn;
		if (outgoing_MSN.empty() || isneun(outgoing_MSN)) outgoing_MSN=tok[tok.size()-1].c_str();
		do {
			outgoing_MSN=Tippstr(string("outgoing_MSN: ")+
					Tx[T_ausgehende_Multiple_Subscriber_Number_Faxnummer_ohne_Vorwahl],&outgoing_MSN);
		} while (!isnumeric(outgoing_MSN) || isneun(outgoing_MSN));
		// dial_prefix
		dial_prefix=Tippstr(string("dial_prefix: ")+Tx[T_Amtsholung_ueblicherweise_kk_oder_0],&dial_prefix,/*obnichtleer=*/0);
		// fax_headline
		fax_headline=cFaxUeberschrift;
		fax_headline=Tippstr(string("fax_headline: ")+Tx[T_Faxueberschrift],&fax_headline);
		// fax_email_from
		fax_email_from=Tippstr(string("fax_email_from: ")+
				Tx[T_Adressat_empfangener_Faxe_die_ueber_Email_verteilt_werden],&fax_email_from);
		// send_tries
		if (!isnumeric(maxcdials)) maxcdials="15";
		do {
			maxcdials=Tippstr(string("send_tries: ")+Tx[T_Zahl_der_Sendeversuche],&maxcdials);
		} while (!isnumeric(maxcdials));
		// send_delays
		send_delays="60,60,60,300,300,300,300,300,3600,3600,3600,3600,18000,36000";
		do {
			send_delays=Tippstr(string("send_delays: ")+Tx[T_kommagetrennte_Liste_mit_Sekundenabstaenden_zwischen_Sendeversuchen],
					&send_delays);
		} while (!isnumeric(send_delays));
		// outgoing_timeout
		outgoing_timeout="60";
		outgoing_timeout=Tippstr(string("outgoing_timeout: ")+Tx[T_Geduld_bis_zum_Verbindungsaufbau_in_s],&outgoing_timeout);
		if (obverb>0) {
			for(unsigned snr=0;snr<cfcnfCp->size();snr++) {
				hLog("snr: "+blaus+ltoan(snr)+schwarz+" "+(*cfcnfCp)[snr]->pname+", "+(*cfcnfCp)[snr]->virtholstr());
			}
		} // if (obverb>0)
	} // if (rzf || (capicffehlt && !nrzf))
	const string suchcuser{"["+cuser+"]"};
	// es gibt zwei moegliche Gruende zum Neuschreiben der Datei: 1) Parameter diffierieren, 2) noch kein User angelegt
	uchar cuserda{0}, paramdiff{0}, neuschreiben{0};
	setfaclggf(cfaxconfdt,obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/6);
	string zeile;
	// iru=0 => pruefen, ob Datei geaendert werden muss; iru=1 => aendern
	uchar tuumben{0};
	for(uchar iru=0;iru<2;iru++) {
		mdatei *fneu{0};
		mdatei f(cfaxconfdt,ios::in); // /etc/capisuite/fax.conf
		if (f.is_open()) {
			if (iru) {
				cfaxconfeigdt=instvz+vtz+"cfaxconfdt_neu";
				fneu=new mdatei(cfaxconfeigdt,ios::out,0);
				if (!fneu->is_open()) break;
			} // if (iru)
			if (f.is_open()) {
				while(getline(f,zeile)) {
					size_t kommpos=zeile.find('#');
					uchar geschrieben{0};
					////          if (kommpos!=string::npos) zeile.erase(kommpos);
					////          if (!zeile.length()) continue;
					if (!cuserda) 
						if (zeile.find(suchcuser)!=string::npos) 
							cuserda=1;
					//// <<rot<<"iru: "<<(int)iru<<", paramdiff: "<<(int)paramdiff<<schwarz<<endl;
					if (iru || !paramdiff) {
						size_t nkz=zeile.find('=');
						string lzeile,rzeile;
						if (nkz<kommpos) {
							lzeile=zeile.substr(0,nkz); 
							rzeile=zeile.substr(nkz+1);
							for(unsigned snr=0;snr<cfcnfCp->size();snr++) {
								if (lzeile.find((*cfcnfCp)[snr]->pname)!=string::npos) {
									//// _out<<"snr: "<<snr<<", lzeile: "<<tuerkis<<lzeile<<schwarz<<", rzeile: "<<blau<<rzeile<<schwarz<<endl;
									string altwert{rzeile};
									gtrim(&altwert);
									anfzweg(&altwert); // Anfuehrungszeichen entfernen
									if (snr==0 || snr==1) (*cfcnfCp)[snr]->setzstr(altwert); // spool_dir und fax_user_dir hier nicht konfigurierbar
									fLog(string("cfcnfC[")+ltoan(snr)+"].name: "+tuerkis+(*cfcnfCp)[snr]->pname+schwarz+Tx[T_komma_wert]+
											((*cfcnfCp)[snr]->virtholstr()==altwert?blau:rot)+(*cfcnfCp)[snr]->virtholstr()+schwarz+Tx[T_komma_Altwert]+
											blau+altwert+schwarz,obverb+iru,oblog+iru);
									if ((*cfcnfCp)[snr]->virtholstr()!=altwert) {
										if (!iru) {
											neuschreiben=1;
											paramdiff=1;
										} else {
											string zschr{(*cfcnfCp)[snr]->pname+" = \""+(*cfcnfCp)[snr]->virtholstr()+"\""};
											*fneu<<zschr<<endl;
											geschrieben=1;
										} //                   if (!iru) else
									} //                 if (cfcnfA[snr].wert!=altwert)
									break; // wenn richtige Zeile gefunden, nicht mehr weitersuchen, unabhaengig vom Ergebnis
								} // if ((nkz=strstr(zeile,cfcnfA[snr].name))) 
							} // if ((nkz=zeile.find(cfcnfA[snr].wert))!=string::npos) 
						} // 						if (nkz<kommpos)
					} // if (!paramdiff) 
					if (iru)
						if (!geschrieben) 
							*fneu<<zeile<<endl;
				} // while( fgets(p=zeile,sizeof zeile,f) ) 
			} // if (f.is_open)
			if (!iru) {
				if (!cuserda) neuschreiben=1;
				if (!neuschreiben) break; // dann fertig
			} else { // if (iru)
				if (!cuserda)  {
					// schreibe Konfiguration fuer Benutzer in fax.conf
					*fneu<<suchcuser<<endl;
					*fneu<<"fax_numbers=\""<<outgoing_MSN<<"\""<<endl;
					*fneu<<"fax_stationID=\""<<fax_stationID<<"\""<<endl;
					*fneu<<"fax_headline=\""<<fax_headline<<"\""<<endl;
					*fneu<<"fax_email_from=\""<<fax_email_from<<"\""<<endl;
					*fneu<<"fax_action=\"MailAndSave\""<<endl;
				} // if (!cuserda)
				if (fneu) {
					fneu->close();
					delete fneu;
					fneu=0;
				} // 				if (fneu)
				tuumben=1;
			} // if (iru)
			if (!cfaxuservz.empty()) cfaxuservz=cfaxuservz;
			//// <<rot<<"cfaxuservz konfcapi: "<<cfaxuservz<<schwarz<<endl;
		} // if (f.is_open())
	} // for(uchar iru=0;iru<2;iru++) 
	if (tuumben) {
		const string origdatei{cfaxconfdt+"_orig"};
		struct stat entryorig{0};
		if (lstat(origdatei.c_str(),&entryorig)) {
			dorename(cfaxconfdt,origdatei,cuser,/*vfehlerp=*/0,/*schonda=*/0,obverb,oblog);
		} else {
			tuloeschen(cfaxconfdt,cuser,obverb,oblog);
		} // 				if (lstat(origdatei.c_str(),&entryorig)) else
		uint vfehler=0;
		kopiere(cfaxconfeigdt,cfaxconfdt,&vfehler,/*wieweiterzaehl=*/2);
	} // 	if (tuumben)
	pruefcvz();
	nextnum();
	hLog(violetts+Txk[T_Ende]+Tx[T_konfcapi]+schwarz+"ccapiconfdt: "+violett+ccapiconfdt+schwarz);
} // void hhcl::konfcapi

// aufgerufen in: konfcapi, verzeichnisse
void hhcl::pruefcvz()
{
	hLog(violetts+"pruefcvz()"+schwarz);
	//// <<rot<<"cfaxuservz in pruefcvz: "<<cfaxuservz<<schwarz<<endl;
	hLog(violetts+Tx[T_pruefcvz]+schwarz+" ccfaxuservz: "+violett+cfaxuservz+schwarz);
	kuerzevtz(&cfaxuservz);
	pruefverz(cfaxuservz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/"",/*benutzer=*/cuser,/*obmachen=*/1);
	cfaxusersqvz=cfaxuservz+vtz+cuser+"/sendq"; //  "/var/spool/capisuite/users/<user>/sendq";
	pruefverz(cfaxusersqvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/"",/*benutzer=*/cuser,/*obmachen=*/1);
	cfaxuserrcvz=cfaxuservz+vtz+cuser+"/received";
	pruefverz(cfaxuserrcvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/"",/*benutzer=*/cuser,/*obmachen=*/1);
	cfaxuserrcfalschevz=cfaxuserrcvz+"/falsche";
	pruefverz(cfaxuserrcfalschevz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/"",/*benutzer=*/cuser,/*obmachen=*/1);
} // hhcl::pruefcvz

// in empfcapi und pruefcapi, virtrueckfragen
void hhcl::pruefsfftobmp()
{
	hLog(violetts+Tx[T_pruefsfftobmp]+schwarz);
	// 23.1.19: auch zypper in libboost_filesystem1_66_0-devel noetig, evtl. auch zypper in libboost_system1_66_0-devel
	const lsysen system{lsys.getsys(obverb,oblog)};
	if (system==fed) {
		//// P=hylafax_copy; T=$P.tar.gz; wget https://github.com/libelle17/$P/archive/master.tar.gz -O $T && tar xpvf $T && rm -f $T && mv ${P}-master/* . && rmdir ${P}-master
		const uchar obboostda{!linstp->doggfinst("boost-devel",obverb,oblog)};
		if (!obprogda("sfftobmp",obverb,oblog) || systemrueck("sfftobmp --version 2>/dev/null")) {
			uchar obfrei{obprogda("jpegtran",obverb,oblog) && obprogda("cjpeg",obverb,oblog) && obprogda("djpeg",obverb,oblog)};
			if (!obfrei) {
				const string jpeg{"jpegsrc_copy"};
				holvomnetz(jpeg);
				obfrei=!kompiliere(jpeg,s_gz);
			}
			if (obfrei) {
				/*//
					svec brueck;
				// rpm -q boost-devel / dpkg -s libboost-dev -> evtl. besser
				systemrueck(sudc+"find "+lsys.getlib64()+" /usr/lib /usr/local/lib /usr/local/lib64 /lib -name libboost_python.so -print -quit",
				obverb,oblog,&brueck);
				uchar obboostda=brueck.size();
				if (!obboostda) KLA
				obboostda = !linstp->doggfinst("boost",obverb,oblog) && !linstp->doggfinst("boost-devel",obverb,oblog);
				KLZ
				 */
				if (obboostda) {
					int serg{0};
					if (systemrueck("grep '/usr/local/lib' /etc/ld.so.conf",obverb,oblog,/*rueck=*/0,/*obsudc=*/1)) {
            systemrueck("echo '/usr/local/lib' >> /etc/ld.so.conf",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
						serg=systemrueck("ldconfig",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
					}
					if (!serg) {
						instsfftobmp();
					} // if (!systemrueck(sudc+"grep
				} // if (!linstp->doggfinst("boost",obverb,oblog) && !linstp->doggfinst("boost-devel",obverb,oblog)) 
			} // if (!systemrueck(befehl,obverb,oblog)) 
		} // if (!obprogda("sfftobmp",obverb,oblog)) 
	} else {
		linstp->doggfinst("sfftobmp",obverb,oblog);
	} // if (system==fed) else
	hLog(violetts+Txk[T_Ende]+Tx[T_pruefsfftobmp]+schwarz);
} // pruefsfftobmp


// in konfcapi und faxemitC (da konfacpi aus pruefcapi nicht unbedingt aufgerufen wird)
// Datei /fax-nextnr ggf. richtigstellen
void hhcl::nextnum()
{
	hLog(violetts+Tx[T_nextnum]+schwarz);
	//// dieser Abschnitt war zuvor richtcapiher
	ulong nextnr{0};
	struct stat entrynextnr{0};
	//// <<"cfaxusersqvz: "<<cfaxusersqvz<<endl;
	nextdatei=cfaxusersqvz+"/fax-nextnr";
	//// <<ndatei<<endl;
	if (!lstat(cfaxusersqvz.c_str(),&entrynextnr)) {
		mdatei nextstr(nextdatei,ios::in);
		if (nextstr.is_open()) {
			string zeile;
			if (getline(nextstr,zeile)) {
				nextnr=atol(zeile.c_str());
			}
		} // if (nextstr.is_open()) 
	} // if (!lstat(cfaxusersqvz.c_str(),&entrynextnr))
	if (!nextnr) {
		pruefverz(cfaxuservz,obverb,oblog,/*obmitfacl=*/2,/*obmitcon=*/0,/*besitzer=*/"",/*benutzer=*/cuser);
		setfaclggf(spoolcapivz,obverb>0?obverb-1:0,oblog,/*obunter=*/wahr,/*mod=*/7,/*obimmer=*/wahr);
		if (findv==1) {
			cmd=sudc+"echo $(( `find "+spoolcapivz+ " -type f -name '*-fax-*.sff' 2>/dev/null "
				"| cut -d '-' -f3 | cut -d '.' -f1 | sort -rn | head -n1` + 1 )) > '"+nextdatei+"'";
			systemrueck(cmd,obverb,oblog,/*rueck=*/0,/*obsudc=*/0);
		} else {
			svec qrueck;
			findfile(&qrueck,findv,obverb,oblog,0,spoolcapivz,/*muster=*/"-fax-.*\\.sff$");
			size_t maxzahl=0;
			for(size_t i=0;i<qrueck.size();i++) {
				string q{qrueck[i]};
				string zahls;
				for(size_t j=0;j<qrueck[i].length();j++){char buch=qrueck[i][j];if (buch>='0'&&buch<='9') zahls+=buch;}
				size_t zahl=atol(zahls.c_str());
				if (zahl>maxzahl) maxzahl=zahl;
			} // 			for(size_t i=0;i<qrueck.size();i++)
			maxzahl++;
			mdatei nextstr(nextdatei,ios::out);
			if (nextstr.is_open()) {
				nextstr<<maxzahl<<endl;
			} // 			if (nextstr.is_open())
		} // 		if (findv==1) else
	} // 	if (!nextnr)
	setfaclggf(nextdatei,obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/6);
} // void hhcl::nextnum()

// aufgerufen in: pruefcapi(), anhalten()
void hhcl::capisv()
{
	if (!scapis) scapis=new servc("","capisuite");
} // void hhcl::capisv(obverb,oblog)

// aufgerufen in: pruefcapi
// lieftert 0, wenn die Dienstdatei da (erg)
// setzt csfehler, wenn Dienst nicht laeuft
int hhcl::cservice()
{
	hLog(violetts+"cservice()"+schwarz);
	int csfehler{0}, 
			erg{-1};
	string cspfad;
	if (obprogda("capisuite",obverb,oblog,&cspfad)) {
		erg=0;
		scapis->stopggf(obverb,oblog,1); 
		const string vz{"/etc/init.d"},datei{"/capisuite"},ziel{"/etc/ausrangiert"};
		if (findv==1) {
			erg=systemrueck(/*//sudc+"sh -c 'systemctl stop capisuite; pkill capisuite >/dev/null 2>&1; pkill -9 capisuite >/dev/null 2>&1; "*/
					"cd "+vz+
					" && [ $(find . -maxdepth 1 -name \"capisuite\" 2>/dev/null | wc -l) -ne 0 ]"
					" &&{ "+sudc+"mkdir -p "+ziel+"&&"+sudc+"mv -f "+vz+datei+" "+ziel+"; }||:"/*//'*/,obverb,oblog,/*rueck=*/0,/*obsudc=*/0);
		} else {
			svec qrueck;
			findfile(&qrueck,findv,obverb,oblog,0,vz,/*muster=*/datei+"$",1,1,Fol_Dat);
			if (qrueck.size()) {
				pruefverz(ziel,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/"",/*benutzer=*/cuser);
				systemrueck("mv -f "+vz+datei+" "+ziel,obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
			} // 			if (qrueck.size())
		} // 		if (findv==1)
		// entweder Type=forking oder Parameter -d weglassen; was besser ist, weiss ich nicht
		csfehler+=!scapis->spruef("Capisuite",0,meinname,cspfad/*+" -d"*/,"","",obverb,oblog);
		if (obverb) hLog("csfehler: "+gruens+ltoan(csfehler)+schwarz);
		////    return csfehler;
	} // if (obprogda("capisuite",obverb,oblog,&cspfad)) 
	return erg;
} // int hhcl::cservice

// in pruefcapi
void hhcl::clieskonf()
{
	hLog(violetts+Tx[T_clieskonf]+schwarz+", cfaxcp->name: "+violett+(cfaxcp?cfaxcp->fname:"0")+schwarz);
	if (fax_stationID!="+"+countrycode+" "+citycode+" "+msn  
			|| outgoing_MSN!=msn  
			|| fax_headline!=cFaxUeberschrift  
		 ) {
		capizukonf=1;
	}
	int richtige{0};
	if (cfaxcp) {
//		cfaxcp->Abschn_auswert(obverb);
		for(size_t i=0;i<cfaxcp->abschv.size();i++) {
			if (cfaxcp->abschv[i].aname==cuser) {
				richtige=0;
				//// <<"abschv["<<i<<"].av.size() "<<cfaxcp->abschv[i].av.size()<<endl;
				for(size_t j=0;j<cfaxcp->abschv[i].av.size();j++) {
					if (cfaxcp->abschv[i].av[j].name=="fax_numbers") {if (*cfaxcp->abschv[i].av[j].wertp==outgoing_MSN) richtige++;}
					else if (cfaxcp->abschv[i].av[j].name=="fax_stationID") {if (*cfaxcp->abschv[i].av[j].wertp==fax_stationID) richtige++;}
					else if (cfaxcp->abschv[i].av[j].name=="fax_headline") {if (*cfaxcp->abschv[i].av[j].wertp==fax_headline) richtige++;}
					else if (cfaxcp->abschv[i].av[j].name=="fax_email_from") {if (*cfaxcp->abschv[i].av[j].wertp==fax_email_from) richtige++;}
				} //         for(size_t j=0;j<cfaxcp->abschv[i].av.size();j++)
				break;
			} //       if (cfaxcp->abschv[i].aname==cuser)
		} //     for(size_t i=0;i<cfaxcp->abschv.size();i++)
		if (richtige!=4) {
			capizukonf=1;
		} //     if (richtige!=4)
	} //   if (cfaxcp)
	svec ckzlrueck;
	if (!ccapiconfdt.empty()) {
		const string befehl{"grep connect_faxG3 `grep incoming_script= "+ccapiconfdt+" 2>/dev/null|cut -d'\"' -f2 2>/dev/null`"
			"|sed 's/.*headline//;s/^,//;s/).*//'"};
		systemrueck(befehl,obverb,oblog,&ckzlrueck,/*obsudc=*/0,/*verbergen=*/1);
	}
	if (ckzlrueck.size()) {
		if (cklingelzahl!=ckzlrueck[0]) {
			//// <<", ckzlrueck[0]: '"<<ckzlrueck[0]<<"', cklingelzahl: '"<<cklingelzahl<<"'"<<endl;
			capizukonf=1;
		}
	} else {
		capizukonf=1;
	} // 	if (ckzlrueck.size()) else
} // void hhcl::clieskonf

// aufgerufen in: pruefcapi
void hhcl::pruefmodcron()
{
	//  fLog(violetts+Tx[T_pruefmodcron]+schwarz,obverb>0?obverb-1:0,oblog);
	hLog(violetts+Tx[T_pruefmodcron]+schwarz);
	const string mp{"@reboot /sbin/modprobe "};
	const string mps[]{mp+"capi",mp+"fcpci"};
	setztmpcron();
	for(uchar ru=0;ru<elemzahl(mps);ru++) {
		if (systemrueck("bash -c 'grep \""+mps[ru]+"\" -q <("+sudc+"crontab -l 2>/dev/null)'",obverb,oblog,/*rueck=*/0,/*obsudc=*/0)) {
			svec rueck;
			const string bef{"crontab -l 2>/dev/null >"+tmpcron+";echo \""+mps[ru]+"\">>"+tmpcron+";crontab "+tmpcron};
			if (!systemrueck(bef,obverb,oblog,&rueck,/*obsudc=*/1)) {
				////    for(size_t znr=0;znr<rueck.size();znr++) { fLog(rueck[znr],1+obverb,oblog); } //     for(size_t znr=0;znr<rueck.size();znr++)
				const string befehl{sudc+"bash -c 'grep \""+mps[ru]+"\" -q <(crontab -l 2>/dev/null)&&"
					"{ crontab -l 2>/dev/null|sed \"/"+ersetzAllezu(mps[ru],"/","\\/")+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'"};
				anfgg(unindt,befehl,bef,obverb,oblog);
			} //if (!systemrueck("("+sudc+"crontab -l 2>/dev/null >"+tmpcron+";echo \""+mps[ru]+"\">>"+tmpcron+";"+sudc+"crontab "+tmpcron+")",obverb,oblog,&rueck))
		} // 		if (systemrueck("bash -c 'grep \""+mps[ru]+"\" -q <("+sudc+"crontab -l 2>/dev/null)'",obverb,oblog))
	} //   for(uchar ru=0;ru<elemzahl(mps);ru++)
} // void pruefmodcron(int obverb, int oblog)

// aufgerufen in: untersuchespool, pvirtfuehraus
// rueckgabe: wie obfa[0] (obfbox) eingestellt sein sollte
int hhcl::prueffbox()
{
	hLog(violetts+Tx[T_prueffbox]+schwarz+" obfbox: "+(obfa[0]?"1":"0")+(obweg[0]?"1":"0"));
	if (obfa[0] || obweg[0]==1) {
		const string fbfax("fbfax");
		if (!obprogda(fbfax)) {
			caus<<rot<<"prueffbox 2"<<schwarz<<endl;
			const auto altobverb{obverb};
			obverb=1;
			holvomnetz(fbfax);
			kompiliere(fbfax,s_gz);
			obverb=altobverb;
		} // 		if (!obprogda(fbfax))
	} // 	if (obfa[0] || obweg[0]==1)
	return 1;
} // int hhcl::prueffbox

// aufgerufen in: untersuchespool, dovc, pvirtfuehraus
// rueckgabe: wie obfa[1] (obcapi) eingestellt sein sollte
int hhcl::pruefcapi()
{
	hLog(violetts+Tx[T_pruefcapi]+schwarz+" obcapi: "+(obfa[1]?"1":"0")+", obweg: "+(obweg[1]==1?"1":"0")+", obher: "+(obher[1]==1?"1":"0"));
	static uchar capiloggekuerzt{0}, 
							 capischonerfolgreichinstalliert{0};
	int capilaeuft{0}, 
			erg{1};
	unsigned versuch{0};
	auto altobverb{obverb};
	obverb=1;
	uchar schonkonfiguriert{0};
	capisv();
	if (obfa[1] || obweg[1]==1 || obher[1]==1) {
		for(;versuch<2;versuch++) {
			// capi4linux muss zum Laufen der Capisuite installiert sein
			// fuer fcpci muss in driver.c eingefuegt werden:
			//// #if !defined(IRQF_DISABLED)
			//// #  define IRQF_DISABLED 0x00
			//// #endif
			////    capilaeuft=(PIDausName("capisuite")>=0);
			capilaeuft=this->scapis->machfit(obverb>0?obverb-1:0,oblog,wahr)&&!ccapiconfdt.empty()&&!cfaxconfdt.empty();
			hLog(violetts+Tx[T_capilaeuft]+schwarz+ltoan(capilaeuft)+schwarz);
			if (capilaeuft && !cpneu) {
				capischonerfolgreichinstalliert=1;
			} else {
	caus<<"obfa[1]: "<<(int)obfa[1]<<"obweg[1]: "<<(int)obweg[1]<<"obher[1]: "<<(int)obher[1]<<endl;
				////      pid_t pid = GetPIDbyName("capisuite") ; // If -1 = not found, if -2 = proc fs access error
				uchar fcpcida{0}, capida{0}, capidrvda{0};
				vector<string> rueck;
				systemrueck("lsmod",obverb,oblog,&rueck,/*obsudc=*/0);
				for(size_t i=0;i<rueck.size();i++){
					if (!fcpcida) {if (!rueck[i].find("fcpci ")) {fcpcida=1;continue;}}
					if (!capidrvda) {if (!rueck[i].find("capidrv ")) {capidrvda=1;continue;}}
					if (!capida) {if (!rueck[i].find("capi ")) {capida=1;continue;}}
					if (fcpcida && capida && capidrvda) break;
				} // for(size_t i=0;i<rueck.size();i++)
				lsysen system=lsys.getsys(obverb,oblog);
				if (!fcpcida || !capida || !capidrvda) {
					::fLog(blaus+Tx[T_Module_geladen]+schwarz+" fcpci: "+blau+(fcpcida?"1":"0")+schwarz+", capi: "+blau+(capida?"1":"0")+schwarz+
							", capidrv: "+blau+(capidrvda?"1":"0")+schwarz+Tx[T_Lade_Capi_Module],obverb,0);
					systemrueck("modprobe -rf avmfritz mISDNipac hisax_fcpcipnp hisax_isac hisax",obverb,oblog,/*rueck=*/0,/*obsudc=*/1,1);
					utsname unbuf;
					if (!fcpcida) {
						uname(&unbuf);
						hLog(Tx[T_Kernelversion]+blaus+unbuf.release+schwarz);
					}
					for(uchar ivers=0;ivers<3;ivers++) {
						if (!fcpcida)
							if (systemrueck("modprobe -v fcpci 2>/dev/null",obverb>0?obverb-1:0+ivers,oblog,/*rueck=*/0,/*obsudc=*/1)) {
								const string fcpciko{string("/lib/modules/")+unbuf.release+"/kernel/extras/fcpci.ko"};
								switch (ivers) {
									case 1:
										tuloeschen(fcpciko,cuser,obverb,oblog);
										break;
									case 2:
										fLog(rots+Tx[T_KannFcpciNInstVerwCapiNicht]+blau+linstp->ersetzeprog("kernel-source")+rots+
												Tx[T_eine_neuere_Version_als_die_des_aktuellen_Kernels_installiert_worden_sein_dann_bitte_erneutes_Systemupdate]+schwarz,1,1);
										erg=0;
										goto schluss;
								} // 								switch (ivers)
								struct stat entryfc{0};
								if (lstat(fcpciko.c_str(), &entryfc)) {
									fLog(Txk[T_datei]+blaus+fcpciko+schwarz+Tx[T_nichtgefFcpciMfdKinstallierwerden],obverb,1);
									const int altobverb{obverb};
									obverb=obverb<2?2:obverb;
									linstp->doinst("kernel-source",1+obverb,oblog);
									/*// 
										const string qvz="/usr/src";
										const string versi="fcpci-3.10.0";
										const string srcf=string("fritz-")+versi+".tar.bz2";
										pruefverz(qvz,obverb,oblog,0);
										struct stat entrysrc KLA 0 KLZ;
										if (lstat((qvz+vtz+srcf).c_str(),&entrysrc)) KLA
										systemrueck(string("cd ")+qvz+";"+sudc+"wget https://belug.de/~lutz/pub/fcpci/"+srcf+
										" --no-check-certificate",1+obverb,oblog);
										KLZ
										string srcvz=qvz+vtz+versi+"/src";
										if (lstat(srcvz.c_str(),&entrysrc)) KLA
										systemrueck(string("cd ")+qvz+";"+sudc+"tar xjf "+srcf,obverb,oblog);
									//sed -e '/#include <linux\/isdn\/capilli.h>/ a\#include <linux\/utsname.h>' -e '/NOTE("(%s built on %s at %s)\\n", TARGET, __DATE__, __TIME__);/ c    NOTE("(%s built on release %s, version %s)\\n", TARGET, utsname()->release, utsname()->version);' main.c >main_neu.c
									// fuer Kernel 4.3.3-3-default und gcc muss jetzt noch 1) , __DATE__ und __TIME__ aus main.c Zeile 365 entfernt werden,
									// 2) in driver.c Zeile 373 IRQF_DISABLED durch 0x00 ersetzt werden, dann kompilier- und installierbar
									KLZ
									systemrueck("cd "+srcvz+";"+sudc+"test -f driver.c.bak || sed -i.bak '/request_irq/i#if !defined(IRQF_DISABLED)\\n"
									"# define IRQF_DISABLED 0x00\\n#endif' driver.c;"
									sudc+"sed -e '/#include <linux\\/isdn\\/capilli.h>/a #include <linux\\/utsname.h>' "
									"-e '/NOTE(\"(%s built on %s at %s)\\\\n\", TARGET, __DATE__, __TIME__);/"
									"c NOTE(\"(%s built on release %s, version %s)\\\\n\", TARGET, utsname()->release, utsname()->version);' "
									"main.c >main_neu.c;mv -n main.c main.c.bak;mv -n main_neu.c main.c;"
									sudc+"make clean",1+obverb,oblog);
									svec rueck;
									systemrueck(sudc+"rm -f /root/bin/xargs",1+obverb,oblog);
									systemrueck("cd "+srcvz+";"+sudc+"make all ",1+obverb,oblog); 
									// || KLA "+sudc+"dnf clean all;"+sudc+"dnf update;"+sudc+"make all; KLZ
									systemrueck("cd "+srcvz+";"+sudc+"make install",1+obverb,oblog);
									 */
									// in Mint musste man gcc downgraden, um fcpci installieren zu koennen
									uchar obdown{0};
									string gccpfad,gpppfad;
									struct utsname unameD{0};
									uname(&unameD);
									const string rel{unameD.release};
									const size_t p1{rel.find('.')};
									if (p1!=string::npos) {
										const size_t p2{rel.find('.',p1+1)};
										if (p2!=string::npos) {
											float vers=atof(rel.substr(0,p2).c_str());
											if (vers>0 && vers<3.14) {
												if (obprogda("gcc",obverb,oblog,&gccpfad) && obprogda("g++",obverb,oblog,&gpppfad)) {
													obdown=1;
													//// systemrueck(sudc+"cp \""+gccpfad+"\" \""+gccpfad+".bak\" && " sudc+"cp \""+gpppfad+"\" \""+gpppfad+".bak\"",obverb,oblog);
													if (!kopier(gccpfad,gccpfad+".bak",obverb,oblog)) kopier(gpppfad,gpppfad+".bak",obverb,oblog);
													linstp->doinst("gcc-4.8",1+obverb,oblog);
													linstp->doinst("g++-4.8",1+obverb,oblog);
													systemrueck("ln -sf \""+gccpfad+"-4.8\" \""+gccpfad+"\" && "+
															"ln -sf \""+gpppfad+"-4.8\" \""+gpppfad+"\"",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
												} // if (!obprogda("gcc",obverb,oblog,&gccpfad) && !obprogda("g++",obverb,oblog,&gpppfad)) 
											} // if (vers>0 && vers<3.14) 
										} // if (p2!=string::npos) 
									} // if (p1!=string::npos) 
									if (systemrueck("ls /lib/modules/$(uname -r)/build",obverb,oblog,/*rueck=*/0,/*obsudc=*/0)) {
										if (system==deb) {
											systemrueck("apt -y install linux-headers-$(uname -r)",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
										}
									} // 									if (systemrueck("ls /lib/modules/$(uname -r)/build",obverb,oblog))
									systemrueck("ls -l /lib/modules/$(uname -r)/build 2>/dev/null || "
											"{ NEU=$(find /lib/modules -type l -name build -print0|"+linstp->xargspf+" -0 -r ls -l --time-style=full-iso|"
											"sort -nk6,7|head -n1|cut -d' ' -f9); test -h $NEU &&"+sudc+"cp -a $NEU /lib/modules/$(uname -r)/build; }",
											obverb,oblog,/*rueck=*/0,/*obsudc=*/0);
									const string proj{"fcpci_copy"};
									const string srcvz{instvz+vtz+proj+".tar.gz"};
									holvomnetz(proj);
									// https://patchwork.kernel.org/patch/10349769/
									const string vorcfg{sudc+"test -f driver.c.bak || sed -i.bak \"/request_irq/i#if \\!defined(IRQF_DISABLED)\\n"
										"# define IRQF_DISABLED 0x00\\n#endif\" driver.c; HV=$(uname -r|cut -d. -f1);NV=$(uname -r|cut -d. -f2);[ $HV -gt 4 -o \\( $HV = 4 -a $NV -ge 18 \\) ]&& grep -q ctrl-\\>proc_fops driver.c && sed -i.bak2 \"/ctrl->proc_fops/c   ctrl->proc_show = ctr_info; \\/\\/ G.Schade 19.1.19\" driver.c;"+
											sudc+"sed -e '/#include <linux\\/isdn\\/capilli.h>/a #include <linux\\/utsname.h>' "
											"-e '/NOTE(\"(%s built on %s at %s)\\\\n\", TARGET, __DATE__, __TIME__);/"
											"c NOTE(\"(%s built on release %s, version %s)\\\\n\", TARGET, utsname()->release, utsname()->version);' "
											"main.c >main_neu.c;mv -n main.c main.c.bak;mv -n main_neu.c main.c;"+
											sudc+"sed -i.bak \"/install: / i .PHONY: uninstall\\nuninstall:\\n\\t\\t"+
											sudc+"modprobe -r \\$\\(CARD\\).ko\\n\\t\\tsudo rm \\$\\(TARGETDIR\\)/\\$\\(CARD\\)\\n\" Makefile;"+
											sudc+"make clean"};
									const string cfgbismake{" 2>/dev/null;"+sudc};
									kompiliere(proj,s_gz,vorcfg,cfgbismake);
									systemrueck("depmod",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
									if (obdown) {
										systemrueck("mv -f \""+gccpfad+".bak\" \""+gccpfad+"\" &&"+
												"mv -f \""+gpppfad+".bak\" \""+gpppfad+"\"",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
									} // 									if (obdown)
									////									exit(99);
									obverb=altobverb;
								} // if (lstat(fcpciko.c_str(), &entryfc)) 
							} // if (systemrueck
					} // for(uchar ivers=0;ivers<2;ivers++) 

					// Fedora:
					// dnf install ncurses-devel
					// cd /usr/src/kernels/4.7.3-200.fc24.x86_64
					// make olddefconfig
					// dnf install elfutils-libelf-devel
					if (systemrueck("modprobe capi 2>/dev/null",obverb,oblog,/*rueck=*/0,/*obsudc=*/1)) {
						if (system==fed) {
							svec vrueck1,vrueck2;
							string v1,v2;
							const string getvmvers{sudc+"ls /boot/vmlinuz-* -r|head -n 1|cut -d- -f2,3,4,5"};
							systemrueck(getvmvers,obverb,oblog,&vrueck1,/*obsudc=*/1);
							if (vrueck1.size()) v1=vrueck1[0];
							systemrueck("dnf -y install kernel-modules-extra-$(uname -r) && "
									"{ lsmod | grep capidrv ||modprobe capidrv 2>/dev/null; "
									"lsmod | grep kernelcapi ||modprobe kernelcapi 2>/dev/null;}",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
							systemrueck(getvmvers,obverb,oblog,&vrueck2,/*obsudc=*/1);
							if (vrueck2.size()) v2=vrueck2[0];
							////            <<"vi: "<<v1<<"\n"<<"v2: "<<v2<<endl;
							// sollte nach Korrektur von kernel-modules-extra zu kernel-modules-extra-$(uname -r) kaum mehr vorkommen
							if (v1!=v2) {
								virtautokonfschreib();
								exit(schluss(9,blaus+Tx[T_Zur_Inbetriebnahme_der_Capisuite_muss_das_Modul_capi_geladen_werten]+schwarz+v1+blau+" -> "
											+schwarz+v2+blau+").\n"+blau+Tx[T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten]+schwarz+mpfad+blau+Tx[T_aufrufen]
											+schwarz,1));
							} // if (v1!=v2) 
#ifdef brauchtsaano // am 19.3.17 braucht's es ned
							//// nach kdpeter.blogspot.de/2013/10/fedora-compile-single-module-directory.html
							////         systemrueck(sudc+"dnf -y install @\"Development Tools\" rpmdevtools yum-utils ncurses-devel",obverb,oblog);
							linstp->doggfinst("fedpkg",obverb+1,oblog);
							linstp->doinst("fedora-packager",obverb+1,oblog,"fedora-cert");
							linstp->doinst("rpmdevtools",obverb+1,oblog,"rpmdev-setuptree");
							struct stat nstat{0};
							if (lstat("/usr/include/numa.h",&nstat))
								linstp->doinst("numactl-devel",obverb+1,oblog);
							if (lstat("/usr/include/curses.h",&nstat))
								linstp->doinst("ncurses-devel",obverb+1,oblog);
							linstp->doggfinst("pesign",obverb+1,oblog);
							systemrueck("rpmdev-setuptree",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
							svec krue;
							systemrueck("find "+instvz+" -name kernel-$(uname -r|rev|cut -d. -f2-|rev).src.rpm",obverb,oblog,&krue,/*obsudc=*/1);
							if (!krue.size()) {
								::fLog(Tx[T_Moment_muss_Kernel_herunterladen],-1,oblog);
								systemrueck("cd "+instvz+" && dnf download --source kernel-$(uname -r)",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
							} // 							if (!krue.size())
							svec rueck;
							systemrueck("cd "+instvz+" && ls -t kernel*.rpm|head -n 1",obverb,oblog,&rueck,/*obsudc=*/0);
							if (rueck.size()) {
								const string kstring{rueck[0]}; // "kernel-4.8.4-200.fc24.src.rpm"
								string kernel=kstring.substr(kstring.find('-')+1);
								kernel.erase(kernel.rfind('.'));
								kernel.erase(kernel.rfind('.'));
								utsname unbuf;
								uname(&unbuf);
								const string release{unbuf.release};
								const string relev{release.substr(0,release.find(unbuf.machine)-1)};
								if (kernel.find(relev)) {
									exit(schluss(10,Tx[T_Der_Kernel_hat_sich_offenbar_seit_dem_Einloggen_von]+blaus+relev+schwarz+Tx[T_nach_]+blau+kernel+schwarz+
												Tx[T_verjuengt_Bitte_den_Rechner_neu_starten_und_dann_mich_nochmal_aufrufen],1));
								} // 							if (kernel.find(relev))
								systemrueck("cd "+instvz+" && dnf -y builddep "+kstring,obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
								systemrueck("cd "+instvz+" && rpm -ivh "+kstring,obverb,oblog,/*rueck=*/0,/*obsudc=*/0);// mit sudo wird kernel.spec nicht erstellt
								// warning: group/user mockbuild does not exist - using root
								const string grund{gethome()+"/rpmbuild",specs=grund+"/SPECS",build=grund+"/BUILD"};
								pruefverz(specs,obverb,oblog);
								pruefverz(build,obverb,oblog);
								for(unsigned iru=0;iru<2;iru++) {
									if (!systemrueck("cd '"+gethome()+"/rpmbuild/SPECS' && rpmbuild -bp --target=$(uname -m) kernel.spec",
												obverb,oblog,/*rueck=*/0,/*obsudc=*/1)) {
										systemrueck("dnf -y install kernel-devel-$(uname -r)",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
										systemrueck("KSTRING="+kstring+" && cd "+gethome()+"/rpmbuild/BUILD/$(echo $KSTRING|cut -d. -f1,2,4)/linux-`uname -r` && "
												"make -C /lib/modules/`uname -r`/build M=`pwd`/drivers/isdn/capi modules",obverb,oblog,/*rueck=*/0,/*obsudc=*/0);
										break;
									} // 									if (!systemrueck
									if (iru) break;
									systemrueck("dnf -y install $(cd '"+gethome()+"/rpmbuild/SPECS' && "
											sudc+"rpmbuild -bp --target=$(uname -m) kernel.spec 2>&1 >/dev/null"
											"| sed '/is needed by/!d;s/^[[:blank:]]*\\(.*\\) is needed by.*/\\1/')",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
									// dnf install audit-libs-devel binutils-devel bison elfutils-devel flex hmaccalc newt-devel numactl-devel 
									//     pciutils-devel "perl(ExtUtils::Embed)" perl-devel xz-devel
									// dann nochmal
								} // for(unsigned iru=0;iru<2;iru++) 
								// dann nach Anleitung: dnf -y install kernel-devel
								// cd ~/rpmbuild/BUILD/kernel<version>/linux<version>
								// make -C /lib/modules/`uname -r`/build M=`pwd`/drivers/isdn/capi modules
							} // if (rueck.size()) 
#endif					
						} // if (system==fed) 
					} // if (systemrueck(sudc+"modprobe capi",obverb,oblog))
					systemrueck("modprobe capidrv 2>/dev/null",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
				} // if (!fcpcida || !capida || !capidrvda) 
				pruefrules(obverb,oblog);
				pruefblack(obverb,oblog);
				capischonerfolgreichinstalliert=!(cservice()||linstp->obfehlt("capi4linux i4l-isdnlog"));
				//// <<violett<<"capischonerfolgreichinstalliert: "<<schwarz<<(int)capischonerfolgreichinstalliert<<endl;
				if (capischonerfolgreichinstalliert) {
					struct stat d1{0}, d2{0};
					if (lstat("/etc/capisuite",&d1) && lstat("/usr/local/etc/capisuite",&d2))
						capischonerfolgreichinstalliert=0;
				}
				//// rot<<"capischonerfolgreichinstalliert 0: "<<(int)capischonerfolgreichinstalliert<<schwarz<<endl;
				if (!capischonerfolgreichinstalliert ||cpneu) {
					fLog(Tx[T_Konnte]+blaus+"capisuite"+schwarz+Tx[T_nichtstarten],1,oblog);
					linstp->doinst("ghostscript",obverb+1,oblog,"gs");
					//// if (systemrueck("which zypper",-1,-1)) KLA
					////        if (linstp->checkinst(-1,-1)!=zyp) KLA
					/*//
						if (linstp->ipr!=zypper) KLA
						::fLog(rots+Tx[T_Kann_Capisuite_nicht_installieren_verwende_Capi_nicht],1,1);
						this->obcapi=0;
						erg=0;
						goto schluss;
						KLZ
					 */
					if (system!=sus)
						linstp->doggfinst("capiutils",obverb+1,oblog);
					pruefsfftobmp();
					linstp->doggfinst("libcapi20-2",obverb+1,oblog);
					linstp->doggfinst("libcapi20-3",obverb+1,oblog);
					linstp->doggfinst("python-devel",obverb+1,oblog);
					linstp->doinst("libxslt-tools",obverb+1,oblog,"xsltproc");
					uchar mitcservice{0};
					// 25.11.16 nicht mehr auf Repo
					/*
						 if (system==sus) KLA
						 linstp->doggfinst("capi4linux i4l-isdnlog",obverb+1,oblog);
						 systemrueck("zypper lr | grep 'kkeil factory development project' || "
						 sudc+"zypper ar -f http://download.opensuse.org/repositories/home:/kkeil:/Factory/openSUSE_Factory/home:kkeil:Factory.repo",
						 1,1);
					// i4l-isdnlog scheint nicht wirklich noetig zu sein
					//   capischonerfolgreichinstalliert=!systemrueck("zypper -n --gpg-auto-import-keys in capisuite capi4linux i4l-isdnlog", 1+obverb,oblog); 
					// i4l-base geloescht
					capischonerfolgreichinstalliert=!linstp->doinst("-f capisuite capi4linux i4l-isdnlog",obverb+1,oblog);
					KLZ // if (lsys.getsys(obverb,oblog)==sus) 
					 */
					if (!capischonerfolgreichinstalliert ||cpneu) {
						holvomnetz("capisuite_copy");
						svec csrueck;
						systemrueck("find /usr/lib*/python* -type f -name Makefile -printf '%h\\n' "+string(obverb?"":"2>/dev/null")+"| sort -r",
								obverb,oblog,&csrueck,/*obsudc=*/0);
						if (csrueck.size()) {
							struct stat c20stat{0},c20hstat{0};
							if (lstat((lsys.getlib64()+"/libcapi20.so").c_str(),&c20stat)||
									lstat("/usr/include/capi20.h",&c20hstat) || cpneu) {
								holvomnetz("capi20_copy");
								const string vorcfg{"sed -i.bak \""
									"/^\\/\\* standard CAPI2.0 functions \\*\\//a "
									"#include \\<capiutils.h\\>\\n"
									"unsigned char *put_byte\\( unsigned char **ppnPtr, _cbyte nVal \\);\\n"
									"unsigned char *put_word\\( unsigned char **ppnPtr, _cword nVal \\);\\n"
									"unsigned char *put_netword\\( unsigned char **ppnPtr, _cword nVal \\);\\n"
									"void CapiDebug\\(int nLevel, const char *pnFormat, ...\\);\\n"
									"unsigned short get_netword\\( unsigned char **ppnPtr \\);\\n"
									"unsigned char *put_dword\\( unsigned char **ppnPtr, _cdword nVal \\);\\n"
									"unsigned short get_word\\( unsigned char **ppnPtr \\);\\n"
									"\" capi20.h"};
								kompiliere(/*was*/"capi20_copy",/*endg*/s_gz,vorcfg);
//								kompiliere(/*was*/"capi20_copy",/*endg*/s_gz,/*vorcfg*/"make clean");
								// ln sollte er in crontab finden
								systemrueck("cd "+instvz+" && L="+lsys.getlib64()+"/libcapi20.so && L3=${L}.3 && test -f $L3 && ! test -f $L && "+
										sudc+"ln -s $L3 $L; test -f $L;",obverb,oblog,/*rueck=*/0,/*obsudc=*/0);
							} // 							if (lstat((lsys.getlib64()+"/libcapi20.so").c_str(),&c20stat)||
							/*//
							//            systemrueck("sh -c 'P=capi20_copy;T=$P.tar.bz2;M=$P-master;cd "+instvz+" && tar xpvf $T && rm -rf $P; mv $M $P && cd $P "
							//                        " && ./configure && make &&"+sudc+"make install '",obverb,oblog);
							//            svec rueck;
							//            systemrueck("find /usr -name capi20.h 2>/dev/null",obverb,oblog,&rueck); 
							 */
							systemrueck("cd "+instvz+" &&{ cd capisuite 2>/dev/null &&{ test -f Makefile && make clean;};}",obverb>0?obverb-1:0,oblog,
									/*rueck=*/0,/*obsudc=*/0);
							obverb++;
							svec rueck;
							string pyvz;
							systemrueck("python -c \"import os; print os.path.dirname(os.__file__)\"",obverb,oblog,&rueck,/*obsudc=*/0);
							if (rueck.size()) {
								pyvz=*sersetze(&rueck[0],"/","\\/");
							} else {
								pyvz=ersetzAllezu(lsys.getlib64(),"/","\\/")+"\\/python2.7";
							} // 							if (rueck.size()) else
							if (!kompiliere("capisuite_copy",s_gz,
										"find src \\( -name \"*.h\" -o -name \"*.c\" -o -name \"*.cpp\" \\) -exec sed -i.bak \"s/\\( throw (.*)\\)/\\/\\*\\1\\*\\//g\" \"{}\" \\;;"
										"find src \\( -name \"capi.h\" -o -name \"capi.cpp\" \\) -exec sed -i.bak \"s/\\(\\~Capi \\?()\\)\\(;\\?$\\)/\\1 noexcept(false)\\2/g\" \"{}\" \\;;"
										"sed -i.bak \""
										// 20.11.16 diese Zeile scheint jetzt wieder in Fedora 24 unnoetig
										//													 "s/python_configdir=.*/python_configdir="+*sersetze(&csrueck[0],"/","\\/")+"/;"
										// 20.11.16 pyexecdir und pythondir mussten in Fedora 24 so gesetzt werden
										// 23.11.16: für openSUSE müsste man wohl --datarootdir=/usr/local/lib64 versuchen, 
										//           so wie es in capisuite.conf hier auch schon steht
										"s/\\( pyexecdir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										"s/\\( pythondir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										////													 "s/\\( *pyexecdir=\\).*/\\1"+pyvz+"\\/site-packages\\/capisuite/;"
										////													 "s/\\( *pythondir=\\).*/\\1"+pyvz+"\\/site-packages\\/capisuite/;"
										"s/\\( *python_configdir=\\).*/\\1\\`\\${PYTHON} -c \\\"import distutils.sysconfig;"
										"print distutils.sysconfig.get_config_var('\\''LIBPL'\\'')\\\"\\`/;"
										"s/\\( *python_moduledir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										"s/\\( *python_moduleexecdir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										"\" configure"
										////                           " && KLA test -f /usr/lib64/libcapi20.so.3 && ! test -f /usr/lib64/libcapi20.so && "
										////                           "ln -s /usr/lib64/libcapi20.so.3 /usr/lib64/libcapi20.so; true; KLZ"
										,"HAVE_NEW_CAPI4LINUX=0 --libdir=/usr/local/lib64 --datarootdir=/usr/local/lib64 --sysconfdir=/etc --localstatedir=/var && "
										"sed -i \"s/PyErr_NewException(\\\"/PyErr_NewException((char*)\\\"/g\" src/application/capisuitemodule.cpp && ")) {
											mitcservice=1;
											// die durch konfcapi erstellte Datei cfaxconfdt wird durch Obiges überschrieben
											struct stat st{0};
											if (!lstat(cfaxconfeigdt.c_str(),&st)) {
												kopier(/*quel=*/cfaxconfeigdt,/*ziel=*/cfaxconfdt,obverb,oblog);
											}
										}
							/*//
							//            string befehl="sh -c 'P=capisuite; T=$P.tar.gz; M=$P-master; cd "+instvz+""
							//                  " && tar xpvf $T && rm -rf $P ; mv $M $P && cd $P"
							//                  " && sed -i.bak \"s_python_configdir=.*_python_configdir="+*sersetze(&csrueck[0],"/","\\/")+"_\" configure"
							//                  " && KLA test -f /usr/lib64/libcapi20.so.3 && ! test -f /usr/lib64/libcapi20.so && "
							//                        "ln -s /usr/lib64/libcapi20.so.3 /usr/lib64/libcapi20.so; true; KLZ "
							//                  " && ./configure HAVE_NEW_CAPI4LINUX=0 --datarootdir=/usr/local/lib --sysconfdir=/etc --localstatedir=/var"
							//                  " && sed -i \"s/PyErr_NewException(\\\"/PyErr_NewException((char*)\\\"/g\" src/application/capisuitemodule.cpp"
							////                  " && sed -i.bak 's/<capi20.h>/\\\""+*sersetze(&rueck[0],"/","\\\"\\/")+"/' src/backend/capi.h"
							////                  " && sed -i.bak 's/<capi20.h>/\\\""+*sersetze(&rueck[0],"/","\\\"\\/")+"/' src/backend/connection.h"
							//                  " && make"
							//                  " && "+sudc+"make install"
							//                  " && "+sudc+"systemctl daemon-reload; "
							//                  "'";
							//            if (!systemrueck(befehl,obverb,oblog)) KLA
							//              //        pruefverz("/etc/capisuite",obverb,oblog,1,0);
							//              //        systemrueck("ls /etc/capisuite/capisuite.conf "
							//              //                    "|| cp -a "+instvz+"/capisuite/src/capisuite.conf /etc/capisuite");
							//              //        systemrueck("ls /etc/capisuite/fax.conf || cp -a "+instvz+"/capisuite/scripts/fax.conf /etc/capisuite");
							////              pruefverz("/usr/local/var/log",obverb,oblog,1,0);
							//              //         pruefverz("/usr/local/var/log",obverb,oblog,1,0);
							//              mitcservice=1;
							//            KLZ // if (!systemrueck(sh -c ...
							 */
							obverb--;
						} // if (csrueck.size()) 
						// aktuelles Verzeichnis
					} // if (!capischonerfolgreichinstalliert) 
					liescapiconf();
					if (mitcservice) {
						capischonerfolgreichinstalliert=!cservice() && !ccapiconfdt.empty() && !cfaxconfdt.empty();
					}
					/*//
					// capisuite unter Kernel 4: 
					// zypper in sfftobmp libcapi20-2
					//        // scp linux2:/usr/include/capiutils.h /usr/include
					//        // scp linux2:/usr/include/capicmd.h /usr/include
					// zypper in libcapi20-3 python-devel capi4linux capi4linux-devel
					// in ubuntu: sfftobmp, (libcapi20-3)?, libcapi20-dev, python-dev, xsltproc

					// git clone https://github.com/larsimmisch/capisuite.git
					// wget https://github.com/larsimmisch/capisuite/archive/master.tar.gz -O capisuite.tar.gz
					// tar xpvf capisuite.tar.gz
					// mv capisuite-master capisuite
					// cd capisuite
					// bei mehreren Installationen wird hier unsortiert die erste Zeile genommen:
					// sed -i.bak 's_python_configdir=.*_python_configdir=`find \/usr\/lib*\/python* -type f -name Makefile -printf "%h\\\\n"`_' configure
					// bei mehreren Installationen koennte hier die richtigen genommen werden:
					// sed -i.bak 's_python_configdir=.*_python_configdir=`cat $(which python-config) | head -n 1| sed "s\/#\\!\\(.*\\)\/\\1\\\/config\/"`_' configure
					// auf Fedora funzt aber nur die Original-configure
					// in ubuntu: ./configure HAVE_NEW_CAPI4LINUX 0
					//            make
					//            "+sudc+"make install
					// "+sudc+"cp -ai "+instvz+"/capisuite/src/capisuite.conf /etc/capisuite/
					// "+sudc+"cp -ai "+instvz+"/capisuite/scripts/fax.conf /etc/capisuite/
					// "+sudc+"chmod 777 /usr/local/var/log
					// ln -s /usr/lib64/libcapi20.so.3.0.6 libcapi20.so
					// in ./src/application/pythonscript.cpp Zeile 104: (Py_ssize_t*)&length statt &length
					// in /usr/include/capiutils.h eine dritte Zeile einfuegen: #define CAPI_LIBRARY_V2
					// in src/backend/connection.cpp eine Zeile 26 einfuegen: #include <cstring>
					 */
				} // if (!capischonerfolgreichinstalliert)
				servc::daemon_reload();
			} // if (capilaeuft) else
			//// <<rot<<"capischonerfolgreichinstalliert: "<<schwarz<<(int)capischonerfolgreichinstalliert<<endl;
			//// <<rot<<"capizukonf: "<<schwarz<<(int)capizukonf<<endl;
			//// <<rot<<"versuch: "<<schwarz<<versuch<<endl;
			if (capischonerfolgreichinstalliert) {
				if (!capizukonf) {
					clieskonf();
				}
				if (/*//obcapi && */!schonkonfiguriert && (versuch>0 || this->capizukonf || rzf)) {
					this->konfcapi();
					scapis->restart(obverb>0?obverb-1:0,oblog);
					capizukonf=0;
					schonkonfiguriert=1;
				} //     if (versuch>0) KLA
				// das Folgende verhindert zwar den Programmabbruch bei active (exit), das nuetzt aber nichts. In dem Fall fcpci aktualisieren! 23.5.14
				//    capilaeuft = !systemrueck("systemctl status capisuite | grep ' active (running)' >/dev/null 2>&1",0,obverb,oblog);
				//     capilaeuft  = !systemrueck("systemctl is-active capisuite",0,obverb,oblog);
				capilaeuft=!scapis->obsvfeh(obverb>0?obverb-1:0,oblog);
				if (capilaeuft) {
					break;
				} else {
					servc::daemon_reload();
					systemrueck("systemctl stop isdn",obverb>0?obverb:-1,oblog,0,/*obsudc=*/1,1);
					////      systemrueck(sudc+"systemctl start isdn",obverb,oblog);
					fLog(Tx[T_StarteCapisuite],-1,oblog);
					scapis->stop(-1,oblog);
					capilaeuft=scapis->startundenable(-1,oblog);
					if (capilaeuft) {
						fLog(Tx[T_Capisuite_gestartet],1,oblog);
						break;
					} else {
						////       ::fLog("Capisuite konnte nicht gestartet werden.",1,1);
					} // 					if (capilaeuft)
				} //       if (capilaeuft) else
			} // if (capischonerfolgreichinstalliert) 
		} //  for(unsigned versuch=0;1;versuch++) (3.)
		if (capilaeuft) {
			if (!capiloggekuerzt) {
				kuerzelogdatei("/var/log/capisuite.log",obverb); // screen
				capiloggekuerzt=1;
			} // 			if (!capiloggekuerzt) 
			if (!kez&& !bvz && !anhl && !tulista && !tulistf && !tulisti && !tulistw && suchstr.empty())
				/*//if (this->obcapi) */pruefmodcron();
		} else {
			::fLog(rots+Tx[T_konntecapisuiteservice]+gruen+ltoan(versuch)+rot+Tx[T_malnichtstartenverwN]+schwarz,1,1);
			erg=0;
		} //   if (capilaeuft)
	//// if (obfa[1] ...
	} else {
		rzf=1;
#if false
		if (scapis) scapis->stopdis(obverb,oblog);
		if (obmodem) {
			obfa[2]=Tippob(Tx[T_Soll_Hylafax_verwendet_werden],obfa[2]?Txk[T_j_af]:"n");
		} else {
			obfa[2]=0;
		}
		if (obmodem) {
			obfa[2]=Tippob(Tx[T_Soll_Hylafax_verwendet_werden],obfa[2]?Txk[T_j_af]:"n");
		} else {
			obfa[2]=0;
		}
#endif
		erg=0;
	} // 	if (obfa[1] ... ) else
schluss: // sonst eine sonst sinnlose for-Schleife mehr oder return mitten aus der Funktion ...
	obverb=altobverb;
	hLog(violetts+Txk[T_Ende]+Tx[T_pruefcapi]+schwarz+" obcapi: "+(obfa[1]?"1":"0")+(obweg[1]?"1":"0")+(obher[1]?"1":"0"));
	return erg;
} // pruefcapi

// aufgerufen in: pvirtvorrueckfragen
// soll aufgerufen werden, wenn entweder obfa[1]!=0 oder rzf!=0
void hhcl::pruefisdn()
{
	hLog(violetts+Tx[T_pruefisdn]+schwarz);
	if (obfa[1] || obweg[1]==1 || obher[1]==1) {
		static uchar obfcgeprueft{0}; // ob schon geprueft, ob Fritzcard eingesteckt
		if (!obfcgeprueft) {
			svec rueck;
			////	cmd="{ lspci 2>/dev/null || "+sudc+"lspci 2>/dev/null;}|grep -i 'isdn'"; systemrueck(cmd, obverb,oblog,&rueck);
			for(int iru=0;iru<2;iru++) {
				if (systemrueck("lspci 2>/dev/null|grep -i 'isdn'",obverb,oblog,&rueck,/*obsudc=*/iru)) break;
			}
			if (rueck.size()) {
				hLog(blaus+Tx[T_ISDN_Karte_gefunden]+schwarz+rueck[0]+blau+Tx[T_Setze]+Tx[T_mitCapi]+schwarz+Tx[T_aauf]+blau+"1.");
				// wenn zum Konfigurationszeitpunkt keine Fritzcard drinstak, aber jetzt, dann rueckfragen
				if (!obfcard) {
					fLog(Txk[T_rueckzufragen_wegen]+rots+"!obfcard"+schwarz,1,0);
					rzf=1;
					obfcard=1;
				} // 		if (!obfcard)
			} else {
				hLog(rots+Tx[T_Keine_ISDN_Karte_gefunden]+schwarz+Tx[T_mitCapi]+rot+Tx[T_aauf]+schwarz+"0.");
				obfa[1]=obweg[1]=obher[1]=obfcard=0;
			} // 	if (rueck.size())
			if (obverb) hLog("obfcard: "+blaus+ltoan(obfcard)+schwarz);
			obfcgeprueft=1;
		} // 	if (!obfcgeprueft)
	} // 	if (obfa[1] ...
} // void hhcl::pruefisdn

void hhcl::dovf()
{
	hLog(violetts+"dovf()"+schwarz);
	prueffbox();
	string zeig;
	cmd=edit;
	viadd(&cmd,&zeig,gethome()+"/.config/fbfax.conf");
	string erg;
	viadd(&erg,&zeig,smbdt,1,1,1); // log_file
	viadd(&erg,&zeig,passwddt,1,1,1); // log_file
	viadd(&erg,&zeig,groupdt,1,1,1); // log_file
	viadd(&erg,&zeig,sudoersdt,1,1,1); // log_file
	vischluss(erg,zeig);
} // void hhcl::dovc()


void hhcl::dovc()
{
	hLog(violetts+"dovc()"+schwarz);
	pruefcapi();
	string zeig;
	cmd=edit;
	viadd(&cmd,&zeig,cfaxconfdt);
	viadd(&cmd,&zeig,ccapiconfdt);
	viadd(&cmd,&zeig,rulesdt);
	viadd(&cmd,&zeig,blackdt);
	if (scapis) viadd(&cmd,&zeig,scapis->systemd);
	if (!cdn[0].empty()) viadd(&cmd,&zeig,cdn[0]); // incoming_script
	if (!cdn[3].empty()) viadd(&cmd,&zeig,cdn[3]); // idle_script
	string erg;
	if (!cdn[1].empty()) viadd(&erg,&zeig,cdn[1],1,1,1); // log_file
	if (!cdn[2].empty()) viadd(&erg,&zeig,cdn[2],1,1,1); // log_error
	vischluss(erg,zeig);
} // void hhcl::dovc()


//α
// aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	liescapiconf();
	// hylazuerst=0;
	//// hmodemstr="ACM";
	maxcapiv="3";
	maxhylav="3";
	maxfbfxv="3";
	maxhdials="11";
	gleichziel=1;
	obocri=1;
	obocra=0;
	findv=1;
	farchvz="/var/spool/fbfax/arch";
	anfaxstr=Tx[T_an_Fax];
	ancfaxstr=Tx[T_an_cFax];
	anhfaxstr=Tx[T_an_hFax];
	anffaxstr=Tx[T_an_fFax];
	anmailstr=Tx[T_an_Mail];
	klaranmailstr=Tx[T_klar_an];
	mailtit=Tx[T_std_mailtit];
	mailbod=Tx[T_std_mailbod];
	anstr=Tx[T_an];
	undstr=Tx[T_und];
	countrycode="49";
	LongDistancePrefix="0";
	InternationalPrefix="00";
	cklingelzahl="1";
	hklingelzahl="2"; // muss mindestens 2 sein, um die Nr. des anrufenden zu uebertragen
	hintervall="120"; // Intervall nach Besetzt
	// um z.B. spezielle Vorgaben (s. VorgbSpeziell) vom Server abhaengig machen zu koennen
#ifdef _WIN32
	//// char lpszUsername[255]; DWORD dUsername = sizeof(lpszUsername); GetUserName(lpszUsername, &dUsername);
	dcpt = sizeof(cpt);
	GetComputerName(cpt,&dcpt);
#elif linux // WIN32
	//// uid_t userId = getuid(); passwd* pw = getpwuid(userId); pw->pw_name<<endl;
	cptlen = MAXHOSTNAMELEN;
	gethostname(cpt, cptlen);
#endif // WIN32 else
	dhcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz);
	virtMusterVorgb(); //ω
	dhcl::pvirtVorgbSpeziell(); //α
} // void hhcl::pvirtVorgbSpeziell

// ueberlaedt die Funktion aus kons.cpp
int hhcl::fui0()
{ //ω
	return auswfb();
	return 0; //α
};
int hhcl::fui1() 
{ //ω
	return auswca();
	return 0; //α
};
int hhcl::fui2() 
{ //ω
	return auswhy();
	return 0; //α
};
// FBox
int hhcl::fui3() {
	return obfa[0] || obher[0]==1;
}
int hhcl::fui4() {
	return obfa[0] || obweg[0]==1 || obher[0]==1;
}
int hhcl::fui5() {
	return obfa[1] || obweg[1]==1 || obher[1]==1;
}
int hhcl::fui6() {
	return obfa[2] || obweg[2]==1 || obher[2]==1;
}
int hhcl::fui7() {
	return obfa[0] || obweg[0]==1 ;
}
int hhcl::fui8() {
	return obfa[1] || obweg[1]==1;
}
int hhcl::fui9() {
	return obfa[2] || obweg[2]==1;
}
// Capi
int hhcl::fui10() {
	return obfa[1] || obher[1]==1;
}
// Hyla
int hhcl::fui11() {
	return obfa[2] || obher[2]==1;
}
void hhcl::fuv0() 
{ //ω
	if (hintervall!=hintervalt) hconfigtty();
}  //α //ω
int hhcl::auswfb(){return obfa[0]&&(obfa[1]||obfa[2]);}
int hhcl::auswca(){return obfa[1]&&(obfa[0]||obfa[2]);}
int hhcl::auswhy(){return obfa[2]&&(obfa[0]||obfa[1]);}

// aufgerufen in lauf //α
void hhcl::virtinitopt()
{
	hLog(violetts+"virtinitopt()"+schwarz); //ω
// optcl::optcl(const string& pname,const void* pptr,const par_t part, const int kurzi, const int langi, TxB* TxBp, const long Txi, const uchar wi, const long Txi2, const string rottxt, const int iwert,const uchar woher, const string& Txtrf/*={}*/,const uchar obno/*=obno==(uchar)-1?part==puchar?1:0:obno*/,const string* refstr/*=0*/,const uchar* obfragz/*=0*/,fnhcliztyp fnobfragz/*=0*/,fnhclztyp fnnachhz/*=0*/,fnhclztyp fnvorhz/*=0*/,const uchar sonderrf/*=0*/):
	// Kopiervorlage:
	// opn<<new optcl(/*pname*/"pname",/*pptr*/pptr,/*art*/pstri,/*kurzi*/T_kurz_k,/*langi*/T_lang_l,/*TxBp*/&Tx,/*Txi*/T_Option_erklaert,/*wi*/1,/*Txi2*/T_Option_Nachtext,/*rottxt*/nix,/*wert*/1,/*woher*/!pname.empty(),/*Txtrf*/{},/*obno*/1,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/0,/*fnnachhz*/&hcl::fu1,/*fnvorhz*/0,/*sonderrf*/0,/*fngueltigz*/0)
	opn<<new optcl(/*pname*/"zufaxenvz",/*pptr*/&zufaxenvz,/*art*/pverz,T_zvz_k,T_zufaxenvz_l,/*TxBp*/&Tx,/*Txi*/T_faxt_die_Dateien_aus_pfad_anstatt_aus,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!zufaxenvz.empty(),Tx[T_Verzeichnis_mit_zu_faxenden_Dateien]);
	opn<<new optcl(/*pname*/"wartevz",/*pptr*/&wvz,/*art*/pverz,T_wvz_k,T_wartevz_l,/*TxBp*/&Tx,/*Txi*/T_Dateien_warten_in_pfad_anstatt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!wvz.empty(),Tx[T_Verzeichnis_mit_wartenden_Dateien]);
	opn<<new optcl(/*pname*/"nichtgefaxtvz",/*pptr*/&ngvz,/*art*/pverz,T_ngvz_k,T_nichtgefaxtvz_l,/*TxBp*/&Tx,/*Txi*/T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!ngvz.empty(),Tx[T_Verzeichnis_mit_gescheiterten_Dateien]);
	opn<<new optcl(/*pname*/"empfvz",/*pptr*/&empfvz,/*art*/pverz,T_evz_k,T_empfvz_l,/*TxBp*/&Tx,/*Txi*/T_Empfangsverzeichnis_fuer_Faxempfang,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!empfvz.empty(),Tx[T_Verzeichnis_fuer_empfangene_Faxe]);
	opn<<new optcl(/*pname*/"obfbox",/*pptr*/&obfa[0],/*art*/puchar,T_fbox_k,T_obfbox_l,/*TxBp*/&Tx,/*Txi*/T_Fritzbox_verwenden,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obfa[0]!=(uchar)-1,Tx[T_Soll_die_FritzBox_verwendet_werden],/*obno*/1,/*refstr*/0,/*obfragz*/&obfrbox);
	opn<<new optcl(/*pname*/"obfboxs",/*pptr*/&obweg[0],/*art*/puchar,T_fboxs_k,T_obfboxs_l,/*TxBp*/&Tx,/*Txi*/T_Fritzbox_zum_Senden_verwenden,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obweg[0]!=-1,Tx[T_Soll_die_FritzBox_zum_Senden_verwendet_werden],/*obno*/1,/*refstr*/0,/*obfragz*/&obfrbox);
	opn<<new optcl(/*pname*/"obfboxe",/*pptr*/&obher[0],/*art*/puchar,T_fboxe_k,T_obfboxe_l,/*TxBp*/&Tx,/*Txi*/T_Fritzbox_zum_Empfang_verwenden,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obher[0]!=-1,Tx[T_Soll_die_FritzBox_zum_Empfang_verwendet_werden],/*obno*/1,/*refstr*/0,/*obfragz*/&obfrbox);
	opn<<new optcl(/*pname*/"fbankvz",/*pptr*/&fbankvz,/*art*/pverz,T_fbankvz_k,T_fbankvz_l,/*TxBp*/&Tx,/*Txi*/T_Ankunftsverzeichnis_der_Fritzbox_ueber_CIFS,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!fbankvz.empty(),Tx[T_Mit_CIFS_gemountetes_Verzeichnis_mit_ankommenden_Faxen_der_Fritzbox],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragez*/&hcl::fui3);
	opn<<new optcl(/*pname*/"farchvz",/*pptr*/&farchvz,/*art*/pverz,T_farchvz_k,T_farchvz_l,/*TxBp*/&Tx,/*Txi*/T_Archivverzeichnis_der_Fritzbox,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!farchvz.empty(),Tx[T_Archiv_Verzeichnis_fuer_ankommende_Faxe_der_Fritzbox],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui3);
	opn<<new optcl(/*pname*/"obcapi",/*pptr*/&obfa[1],/*art*/puchar,T_capi_k,T_obcapi_l,/*TxBp*/&Tx,/*Txi*/T_Capisuite_verwenden ,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obfa[1]!=(uchar)-1,Tx[T_Soll_die_Capisuite_verwendet_werden]);
	opn<<new optcl(/*pname*/"obcapis",/*pptr*/&obweg[1],/*art*/puchar,T_capis_k,T_obcapis_l,/*TxBp*/&Tx,/*Txi*/T_Capisuite_zum_Senden_verwenden ,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obweg[1]!=(uchar)-1,Tx[T_Soll_die_Capisuite_zum_Senden_verwendet_werden]);
	opn<<new optcl(/*pname*/"obcapie",/*pptr*/&obher[1],/*art*/puchar,T_capie_k,T_obcapie_l,/*TxBp*/&Tx,/*Txi*/T_Capisuite_zum_Empfang_verwenden ,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obher[1]!=(uchar)-1,Tx[T_Soll_die_Capisuite_zum_Empfang_verwendet_werden]);
	opn<<new optcl(/*pname*/"obhyla",/*pptr*/&obfa[2],/*art*/puchar,T_hyla_k,T_obhyla_l,/*TxBp*/&Tx,/*Txi*/T_hylafax_verwenden ,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obfa[2]!=(uchar)-1,Tx[T_Soll_Hylafax_verwendet_werden]);
	opn<<new optcl(/*pname*/"obhylas",/*pptr*/&obweg[2],/*art*/puchar,T_hylas_k,T_obhylas_l,/*TxBp*/&Tx,/*Txi*/T_hylafax_zum_Senden_verwenden ,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obweg[2]!=(uchar)-1,Tx[T_Soll_Hylafax_zum_Senden_verwendet_werden]);
	opn<<new optcl(/*pname*/"obhylae",/*pptr*/&obher[2],/*art*/puchar,T_hylae_k,T_obhylae_l,/*TxBp*/&Tx,/*Txi*/T_hylafax_zum_Empfang_verwenden ,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obher[2]!=(uchar)-1,Tx[T_Soll_Hylafax_zum_Empfang_verwendet_werden]);
	opn<<new optcl(/*pname*/"fprio",/*pptr*/&prios[0],/*art*/pint,T_fp_k,T_fprio_l,/*TxBp*/&Tx,/*Txi*/T_Prioritaet_von_fritzbox_1_3,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!!prios[0],Tx[T_Mit_welcher_Prioritaet_soll_fritzbox_verwendet_werden_1_3],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui0);
	opn<<new optcl(/*pname*/"cprio",/*pptr*/&prios[1],/*art*/pint,T_cp_k,T_cprio_l,/*TxBp*/&Tx,/*Txi*/T_Prioritaet_von_capisuite_1_3,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!!prios[1],Tx[T_Mit_welcher_Prioritaet_soll_capisuite_verwendet_werden_1_3],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui1);
	opn<<new optcl(/*pname*/"hprio",/*pptr*/&prios[2],/*art*/pint,T_hp_k,T_hprio_l,/*TxBp*/&Tx,/*Txi*/T_Prioritaet_von_hylafax_1_3,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!!prios[2],Tx[T_Mit_welcher_Prioritaet_soll_hylafax_verwendet_werden_1_3],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui2);

//	opn<<new optcl(/*pname*/"hylazuerst",/*pptr*/&hylazuerst,/*art*/pint,T_hz_k,T_hylazuerst_l,/*TxBp*/&Tx,/*Txi*/T_versuche_faxe_zuerst_ueber_Hylafax_wegzuschicken,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/hylazuerst!=-1,T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden);
//	opn<<new optcl(/*pname*/"hylazuerst",/*pptr*/&hylazuerst,/*art*/pint,T_cz_k,T_capizuerst_l,/*TxBp*/&Tx,/*Txi*/T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/0,/*woher*/hylazuerst!=-1,-1);
	opn<<new optcl(/*pname*/"hmodem",/*pptr*/&hmodem,/*art*/pstri,T_mod_k,T_hmodem_l,/*TxBp*/&Tx,/*Txi*/T_Fuer_Hylafax_verwendetes_Modem,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!hmodem.empty(),/*Txtrf*/string(),/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui6);
	opn<<new optcl(/*pname*/"maxfbfxv",/*pptr*/&maxfbfxv,/*art*/pdez,T_mf_k,T_maxfbfxv_l,/*TxBp*/&Tx,/*Txi*/T_nach_zahl_Versuchen_fbfax_wird_andere_Methode_verwendet,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,!maxfbfxv.empty(),Tx[T_Zahl_der_Versuche_in_fbfax_bis_andere_Methode_versucht_wird],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui7);
	opn<<new optcl(/*pname*/"maxcapiv",/*pptr*/&maxcapiv,/*art*/pdez,T_mc_k,T_maxcapiv_l,/*TxBp*/&Tx,/*Txi*/T_nach_zahl_Versuchen_Capisuite_wird_andere_Methode_versucht,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!maxcapiv.empty(),Tx[T_Zahl_der_Versuche_in_Capisuite_bis_andere_Methode_versucht_wird],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui8);
	opn<<new optcl(/*pname*/"maxhylav",/*pptr*/&maxhylav,/*art*/pdez,T_mh_k,T_maxhylav_l,/*TxBp*/&Tx,/*Txi*/T_nach_zahl_Versuchen_Hylafax_wird_andere_Methode_verwendet,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,!maxhylav.empty(),Tx[T_Zahl_der_Versuche_in_hylafax_bis_andere_Methode_versucht_wird],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui9);
	opn<<new optcl(/*pname*/"cuser",/*pptr*/&cuser,/*art*/pstri,T_cuser_k,T_cuser_l,/*TxBp*/&Tx,/*Txi*/T_verwendet_fuer_Capisuite_Samba_den_Linux_Benutzer_string_anstatt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!cuser.empty(),/*Txtrf*/{},/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui5);
	opn<<new optcl(/*pname*/"cklingelzahl",/*pptr*/&cklingelzahl,/*art*/pdez,T_ckzl_k,T_cklingelzahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!cklingelzahl.empty(),Tx[T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui10);
	opn<<new optcl(/*pname*/"hklingelzahl",/*pptr*/&hklingelzahl,/*art*/pdez,T_hkzl_k,T_hklingelzahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!hklingelzahl.empty(),Tx[T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui11);
	opn<<new optcl(/*pname*/"hintervall",/*pptr*/&hintervall,/*art*/pdez,T_hintv_k,T_hintervall_l,/*TxBp*/&Tx,/*Txi*/T_Abstand_in_Sekunden_nach_Besetzt_bis_Hylafax_erneut_waehlt_anstatt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!hintervall.empty(),Tx[T_Abstand_in_Sekunden_nach_Besetzt_bis_Hylafax_erneut_waehlt],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui9,/*fnnachhz*/&hcl::fuv0);
	opn<<new optcl(/*pname*/"maxdials",/*pptr*/&maxhdials,/*art*/pdez,T_md_k,T_maxdials_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_Wahlversuche_in_Hylafax,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!maxhdials.empty(),/*Txtrf*/{},/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui9);
	opn<<new optcl(/*pname*/"gleichziel",/*pptr*/&gleichziel,/*art*/pint,T_gz_k,T_gleichziel_l,/*TxBp*/&Tx,/*Txi*/T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/gleichziel!=-1,Tx[T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden]);
	opn<<new optcl(/*pname*/"ocri",/*pptr*/&obocri,/*art*/pint,T_ocri_k,T_ocri_l,/*TxBp*/&Tx,/*Txi*/T_Text_aus_empfangenen_Faxen_wird_ermittelt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obocri!=-1,Tx[T_soll_Text_in_empfangenen_Faxen_mit_OCR_gesucht_werden]);
	opn<<new optcl(/*pname*/"ocra",/*pptr*/&obocra,/*art*/pint,T_ocra_k,T_ocra_l,/*TxBp*/&Tx,/*Txi*/T_Text_aus_gesandten_Bildern_wird_ermittelt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/obocra!=-1,Tx[T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden]);
	opn<<new optcl(/*pname*/"anfaxstr",/*pptr*/&anfaxstr,/*art*/pstri,T_afs_k,T_anfaxstr_l,/*TxBp*/&Tx,/*Txi*/T_faxnr_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!anfaxstr.empty(),Tx[T_Buchstabenfolge_vor_erster_Faxnummer]);
	opn<<new optcl(/*pname*/"anffaxstr",/*pptr*/&anffaxstr,/*art*/pstri,T_affs_k,T_anffaxstr_l,/*TxBp*/&Tx,/*Txi*/T_faxnr_fuer_primaer_Fritzbox_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!anffaxstr.empty(),Tx[T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Fritzbox],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui0);
	opn<<new optcl(/*pname*/"ancfaxstr",/*pptr*/&ancfaxstr,/*art*/pstri,T_acfs_k,T_ancfaxstr_l,/*TxBp*/&Tx,/*Txi*/T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!ancfaxstr.empty(),Tx[T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Capisuite],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui1);
	opn<<new optcl(/*pname*/"anhfaxstr",/*pptr*/&anhfaxstr,/*art*/pstri,T_ahfs_k,T_anhfaxstr_l,/*TxBp*/&Tx,/*Txi*/T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!anhfaxstr.empty(),Tx[T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Hylafax],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/&hcl::fui2);
	opn<<new optcl(/*pname*/"anstr",/*pptr*/&anstr,/*art*/pstri,T_as_k,T_anstr_l,/*TxBp*/&Tx,/*Txi*/T_Adressatenname_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!anstr.empty(),Tx[T_Buchstabenfolge_vor_erstem_Adressaten]);
	opn<<new optcl(/*pname*/"undstr",/*pptr*/&undstr,/*art*/pstri,T_us_k,T_undstr_l,/*TxBp*/&Tx,/*Txi*/T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!undstr.empty(),Tx[T_Buchstabenfolge_vor_weiterem_Adressaten_sowie_weiterer_Faxnummer]);
	opn<<new optcl(/*pname*/"anmailstr",/*pptr*/&anmailstr,/*art*/pstri,T_ams_k,T_anmailstr_l,/*TxBp*/&Tx,/*Txi*/T_mailadresse_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!anmailstr.empty(),Tx[T_Buchstabenfolge_vor_erster_Mailadresse]);
	opn<<new optcl(/*pname*/"klaranmailstr",/*pptr*/&klaranmailstr,/*art*/pstri,T_kams_k,T_klaranmailstr_l,/*TxBp*/&Tx,/*Txi*/T_mailadresse_fuer_unverschluesselte_Mail_wird_hinter_string_erwartet_statt_hinter,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!klaranmailstr.empty(),Tx[T_Buchstabenfolge_vor_erster_Mailadresse_fuer_unverschluesselte_Mail]);
	opn<<new optcl(/*pname*/"mailvon",/*pptr*/&mailvon,/*art*/pstri,T_mv_k,T_mailvon_l,/*TxBp*/&Tx,/*Txi*/T_Absender_mailadresse,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!mailvon.empty(),Tx[T_als_Absender_zu_verwendende_Mailadresse]);
	opn<<new optcl(/*pname*/"smtpadr",/*pptr*/&smtpadr,/*art*/pstri,T_smtpadr_k,T_smtpadr_l,/*TxBp*/&Tx,/*Txi*/T_smtp_Adresse,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!smtpadr.empty(),Tx[T_smtp_Adresse_ohne_port]);
	opn<<new optcl(/*pname*/"portnr",/*pptr*/&portnr,/*art*/pstri,T_portnr_k,T_portnr_l,/*TxBp*/&Tx,/*Txi*/T_port_Nummer,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!portnr.empty(),{});
	opn<<new optcl(/*pname*/"smtpusr",/*pptr*/&smtpusr,/*art*/pstri,T_smtpusr_k,T_smtpusr_l,/*TxBp*/&Tx,/*Txi*/T_smtp_usr,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!smtpusr.empty(),{});
	opn<<new optcl(/*pname*/"smtppwd",/*pptr*/&smtppwd,/*art*/ppwd,T_smtppwd_k,T_smtppwd_l,/*TxBp*/&Tx,/*Txi*/T_smtp_pwd,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!smtppwd.empty(),Tx[T_Smtp_pwd],/*obno*/0,/*refstr*/&smtpusr);
	opn<<new optcl(/*pname*/"mailtit",/*pptr*/&mailtit,/*art*/pstri,T_mt_k,T_mailtit_l,/*TxBp*/&Tx,/*Txi*/T_mailtitle,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!mailtit.empty(),Tx[T_Mailtitle]);
	opn<<new optcl(/*pname*/"mailbod",/*pptr*/&mailbod,/*art*/pstri,T_mb_k,T_mailbod_l,/*TxBp*/&Tx,/*Txi*/T_mailbody,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/!mailbod.empty(),Tx[T_Mailbody]);
// echo "This is the message body and contains the message" | mailx -v -r "gschade@dachau-mail.de" -s "This is the subject"  -S smtp="mail.mnet-online.de:587" -S smtp-use-starttls -S smtp-auth=login -S smtp-auth-user="gschade@dachau-mail.de" -S smtp-auth-password="..." -S ssl-verify=ignore -a untersch gerald.schade@gmx.de
	opn<<new optcl(/*pname*/"findv",/*pptr*/&findv,/*art*/pint,T_find_k,T_find_l,/*TxBp*/&Tx,/*Txi*/T_Version_1_2_oder_3_Dateisuche_anstatt,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/findv!=-1,string());
	opn<<new optcl(/*pptr*/&loef,/*art*/puchar,T_loef,T_loeschefax_l,/*TxBp*/&Tx,/*Txi*/T_ein_Fax_nach_Rueckfrage_loeschen,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&loew,/*art*/puchar,T_loew,T_loeschewaise_l,/*TxBp*/&Tx,/*Txi*/T_Eintraege_aus,/*wi*/1,/*Txi2*/T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist,/*rottxt*/spooltab,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&loea,/*art*/puchar,T_loea_k,T_loescheallew_l,/*TxBp*/&Tx,/*Txi*/T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus,/*wi*/1,/*Txi2*/T_loeschen,/*rottxt*/spooltab,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&erneut,/*art*/puchar,T_erneut_k,T_erneutempf_l,/*TxBp*/&Tx,/*Txi*/T_empfangenes_Fax_erneut_bereitstellen,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&uml,/*art*/puchar,T_uml_k,T_umleiten_l,/*TxBp*/&Tx,/*Txi*/T_ausgehendes_Fax_vorzeitig_ueber_andere_Wege_schicken,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&auml,/*art*/puchar,T_auml_k,T_alleumleiten_l,/*TxBp*/&Tx,/*Txi*/T_alle_ausgehenden_Faxe_vorzeitig_ueber_andere_Wege_schicken,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&kez,/*art*/puchar,T_kez_k,T_korrerfolgszeichen_l,/*TxBp*/&Tx,/*Txi*/T_in_der_Datenbanktabelle,/*wi*/0,/*Txi2*/T_wird_das_Erfolgszeichen_korrigiert,/*rottxt*/touta,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&bvz,/*art*/puchar,T_bvz_k,T_bereinigevz_l,/*TxBp*/&Tx,/*Txi*/T_Dateien_aus_Warteverzeichnis_Gescheitertenvz_und_Gefaxtvz_gegen,/*wi*/0,/*Txi2*/T_pruefen_und_aufraeumen,/*rottxt*/touta,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&anhl,/*art*/puchar,T_st_k,T_stop_l,/*TxBp*/&Tx,/*Txi*/T_DPROG_anhalten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1); //α //ω
	opn<<new optcl(/*pptr*/&tulista,/*art*/puchar,T_lista_k,T_listausg_l,/*TxBp*/&Tx,/*Txi*/T_listet_Datensaetze_aus,/*wi*/1,/*Txi2*/T_mit_Erfolgskennzeichen_auf,/*rottxt*/touta,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&tulistf,/*art*/puchar,T_listf_k,T_listfailed_l,/*TxBp*/&Tx,/*Txi*/T_listet_Datensaetze_aus,/*wi*/1,/*Txi2*/T_ohne_Erfolgskennzeichen_auf,/*rottxt*/touta,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&tulisti,/*art*/puchar,T_listi_k,T_listinca_l,/*TxBp*/&Tx,/*Txi*/T_listet_Datensaetze_aus,/*wi*/1,/*Txi2*/T__auf,/*rottxt*/tinca,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&tulistw,/*art*/puchar,T_listw_k,T_listwart_l,/*TxBp*/&Tx,/*Txi*/T_listet_wartende_Faxe_auf,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&nurempf,/*art*/puchar,T_nurempf_k,T_nurempf_l,/*TxBp*/&Tx,/*Txi*/T_empfaengt_nur,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&nursend,/*art*/puchar,T_nursend_k,T_nursend_l,/*TxBp*/&Tx,/*Txi*/T_sendet_nur,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&suchstr,/*art*/pstri,T_s_k,T_suche_l,/*TxBp*/&Tx,/*Txi*/T_suche_in_verarbeiteten_Faxen_nach,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1);
	opn<<new optcl(/*pptr*/&dszahl,/*art*/pdez,T_n_k,T_dszahl_l,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/1); //α //ω
	opn<<new optcl(/*pptr*/&obvf,/*art*/puchar,T_vf_k,T_vf_l,/*TxBp*/&Tx,/*Txi*/T_FBFax_Konfigurationdateien_bearbeiten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&obvc,/*art*/puchar,T_vc_k,T_vc_l,/*TxBp*/&Tx,/*Txi*/T_Capisuite_Konfigurationdateien_bearbeiten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pptr*/&obvh,/*art*/puchar,T_vh_k,T_vh_l,/*TxBp*/&Tx,/*Txi*/T_Hylafax_Modem_Konfigurationsdatei_bearbeiten,/*wi*/1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
//	opn<<new optcl(/*pname*/"sqlz",/*pptr*/&sqlzn,/*art*/plong,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_SQL_Befehle_fuer_die_Absenderermittlung,/*wi*/-1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/sqlzn>0);
//	opn<<new optcl(/*pname*/"musterzahl",/*pptr*/&zmzn,/*art*/plong,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Zahl_der_Muster_Verzeichnis_Paare_zum_Speichern_ankommender_Faxe,/*wi*/-1,/*Txi2*/-1,/*rottxt*/nix,/*wert*/-1,/*woher*/(zmzn>0));
	opn<<new optcl(/*pptr*/&cpneu,/*art*/puchar,T_cpneu_k,T_cpneu_l,/*TxBp*/&Tx,/*Txi*/T_Capisuite_neu_einrichten,/*wi*/0,/*Txi2*/-1,/*rottxt*/nix,/*wert*/1,/*woher*/1);
	dhcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	hLog(violetts+Tx[T_virtmacherkl_Tx_lgn]+schwarz+ltoan(Tx.lgn));
//	erkl<<violett<<DPROG<<blau<<Txk[T_tut_dieses_und_jenes]<<schwarz; //ω 
	erkl<<blau<<Tx[T_Faxt_Dateien_aus_Verzeichnis_pfad_die]<<anfaxstr<<Tx[T_oder_]<<anmailstr<<Tx[T_oder_]<<klaranmailstr<<
		Tx[T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie]
		<<drot<<dbq<<blau<<Tx[T_Tabellen]<<drot<<touta<<blau<<"`,`"<<drot<<spooltab<<blau<<Tx[T_aein]<<schwarz;
} // void hhcl::pvirtmacherkl //α
//ω

void hhcl::machopvzm()
{
	for(size_t i=0;i<zmVp.size();) {
		++i;
		stringstream zmmname,zmzname;
		zmmname<<"ZMMuster_"<<i;
		zmzname<<"ZMZiel_"<<i;
		const string istr{ltoan(i)};
		opvzm<<new optcl(/*pname*/zmmname.str(),/*pptr*/&zmVp[i-1].muster,/*part*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Zielmuster_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/1,Tx[T_Zielmuster]);
		opvzm<<new optcl(/*pname*/zmzname.str(),/*pptr*/&zmVp[i-1].ziel,/*part*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Ziel_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/1,Tx[T_Ziel]);
	}
}
//α

// aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	dbq=DPROG;
	findv=1;
	muser="user";
	citycode="8131";
	msn="999999";
	LocalIdentifier=Tx[T_MeiEinrichtung];
	cFaxUeberschrift=Tx[T_Mei_FaxUeberschrift];
	////  host="localhost"; // 'localhost' schon Vorgabe bei Definition
	zufaxenvz="/var/"+meinname+vtz+Tx[T_zufaxen];
	wvz="/var/"+meinname+vtz+Tx[T_warteauffax];
	ngvz="/var/"+meinname+vtz+Tx[T_nichtgefaxt];
	empfvz="/var/"+meinname+vtz+Tx[T_empfvz];
//	static zielmustercl zmi[]={zielmustercl("[Ss]pamfax","/var/"+meinname+"/spam"),zielmustercl("","/var/"+meinname+vtz+Tx[T_gesandt])};//= nur Beispiel
	// wird nur vor dem ersten fork bearbeitet
//	zmvp=zmi;
	zmVp.clear();
	zmVp.push_back(zielmustercl("[Ss]pamfax","/var/"+meinname+"/spam"));
	zmVp.push_back(zielmustercl("","/var/"+meinname+vtz+Tx[T_gesandt]));
	machopvzm();
	dhcl::virtMusterVorgb(); //α
} // void hhcl::MusterVorgb

// aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
	if (obvf) dovf();
	if (obvc) dovc();
} // void hhcl::virtvorzaehler //α
//ω

void hhcl::zeigdienste()
{
	hLog(violetts+Tx[T_Zustand_der_Dienste]+schwarz,1,0);
	servc *svp[4]{scapis,sfaxq,shfaxd,sfaxgetty};
	for(int i=0;i<4;i++) {
		if (svp[i]) {
			svp[i]->obsvfeh();
			cout<<" "<<setw(25)<<svp[i]->sname<<": "<<blau<<Txk[sfeh[svp[i]->svfeh]]<<schwarz<<endl;
		} // 		if (svp[i])
	} // 	for(int i=0;i<4;i++)
} // void hhcl::zeigdienste

// augerufen in: pruefhyla, zeigkonf, loeschehyla, anhalten
void hhcl::hylasv1()
{
	if (!this->sfaxgetty) this->sfaxgetty=new servc("hylafax-faxgetty-"+this->hmodem,"faxgetty");
} // void hhcl::hylasv1

// augerufen in: pruefhyla, zeigkonf, loeschehyla, anhalten
void hhcl::hylasv2(hyinst hyinstart)
{
	if (hyinstart==hysrc || hyinstart==hyppk) {
		if (!sfaxq) sfaxq=new servc("hylafax-faxq","faxq");
		if (!shfaxd) shfaxd=new servc("hylafax-hfaxd","hfaxd");
		// => hyinstart==hypak
	} else {
		if (!sfaxq) sfaxq=new servc("","faxq");
		if (!shfaxd) shfaxd=new servc("","hfaxd");
	} // if (hyinstart==hysrc || hyinstart==hyppk) else
	if (!shylafaxd) shylafaxd=new servc("hylafax","faxq hfaxd");
} // void hhcl::hylasv2

// aufgerufen in lauf //α
void hhcl::virtzeigversion(const string& ltiffv/*=string()*/)
{
	hLog(violetts+Tx[T_virtzeigversion]+schwarz);
	dhcl::virtzeigversion(ltiffv);  //ω
	zeigkonf();
	capisv();
	hylasv1();
	hylasv2(hysrc);
	zeigdienste();
} // void hhcl::virtzeigversion //α
//ω

// aus: coreutils
int fd_reopen(int desired_fd, char const *file, int flags, mode_t mode)
{
	const int fd{open(file, flags, mode)};
	if (fd==desired_fd||fd<0) {
		return fd;
	} else {
		const int fd2{dup2(fd, desired_fd)};
		int saved_errno = errno;
		close(fd);
		errno=saved_errno;
		return fd2;
	} // 	if (fd == desired_fd || fd < 0) else
} // fd_reopen

// mit strace usw. aus coreutils; in pruefmodem
int ttytest(const string& tty)
{
	int erg{0},fdflags{0};
	int defin;
	if ((defin=dup(STDIN_FILENO))>=0) {
		static struct termios mode{0};
		int fd;
		if ((fd=fd_reopen(STDIN_FILENO, ("/dev/"+tty).c_str(), O_RDONLY | O_NONBLOCK, 0))>=0) {
			if ((fdflags = fcntl (STDIN_FILENO, F_GETFL)) != -1 && fcntl (STDIN_FILENO, F_SETFL, fdflags & ~O_NONBLOCK) >= 0) {
				if (!tcgetattr (STDIN_FILENO, &mode)) {
					erg=1;
				} // 				if (!tcgetattr (STDIN_FILENO, &mode))
			} // 			if ((fdflags = fcntl (STDIN_FILENO, F_GETFL)) != -1 && fcntl (STDIN_FILENO, F_SETFL, fdflags & ~O_NONBLOCK) >= 0)
			close(fd);
		} // 		if ((fd=fd_reopen (STDIN_FILENO, ("/dev/"+tty).c_str(), O_RDONLY | O_NONBLOCK, 0))>=0)
		dup2(defin,STDIN_FILENO);
		close(defin);
	} // 	if ((defin=dup(STDIN_FILENO))>=0)
	return erg;
} // int ttytest

// aufgerufen in: main, virtrueckfragen
// soll aufgerufen werden, wenn entweder obfa[2]!=0 oder rzf!=0
void hhcl::pruefmodem()
{
	hLog(violetts+Tx[T_pruefmodem]+schwarz);
	if (obfa[2] || obweg[2]==1 || obher[2]==1) {
		static uchar obmdgeprueft{0}; // ob schon geprueft, ob Modem verfuegbar
		if (!obmdgeprueft) {
			obmodem=0;
			//	const string althmodem(hmodem);
			const string svz{"/sys/class/tty/"};
			svec qrueck;
			//// <<"pruefmodem 1 nach obcapi: "<<(int)obcapi<<endl;
			// 19.2.17: evtl. besser mit: dmesg|grep '[^t]*tty[^] 0\t:.$]'|sed 's/[^t]*\(tty[^] \t:.$]*\).*/\1/'
			// 25.2.17: geht leider nicht nach "<DPROG> -nohyla"
			// #define mitdmesg
#ifdef mitdmesg
			systemrueck("dmesg|grep tty",obverb,oblog,&qrueck,/*obsudc=*/0);
#else // mitdmesg
			if (findv==1) {
				systemrueck("cd "+svz+";find */device/driver", obverb,oblog,&qrueck,/*obsudc=*/0);
			} else {
				findfile(&qrueck,findv,obverb,oblog,0,svz,/*muster=*/"",1,127,0);
				for(size_t i=qrueck.size();i;) {
					i--;
					struct stat st{0};
					if (lstat((qrueck[i]+"/device/driver").c_str(),&st)) {
						qrueck.erase(qrueck.begin()+i);
					} // 				if (lstat((qrueck[i]+"/device/driver").c_str(),&st))
				} // 			for(size_t i=qrueck.size();i;)
			} // 		if (findv==1)
#endif // mitdmesg else
			for(size_t i=0;i<qrueck.size();i++) {
#ifdef mitdmesg
				size_t pos=qrueck[i].find("tty");
				if (pos==string::npos) continue;
				size_t p2=qrueck[i].find_first_of("] \t:.,;-",pos);
				if (p2==string::npos) continue;
				const string tty{qrueck[i].substr(pos,p2-pos)};
				if (tty=="tty"||tty=="tty0") continue;
				////	modem=svz+modem;
				//// <<rot<<svz+modem<<schwarz<<endl;
#else // mitdmesg
				const string tty{findv==1?qrueck[i].substr(0,qrueck[i].find('/')):base_name(qrueck[i])};
				////			struct stat entrydriv=KLA 0 KLZ;
				////			if (!lstat((modem+"/device/driver").c_str(),&entrydriv)) KLA
				////				const string tty=base_name(modem);
#endif // mitdmesg else
				// ttyS0 erscheint auf Opensuse und Ubuntu konfiguriert, auch wenn kein Modem da ist
				if (tty!="ttyS0") {
					int terg;
					if (cus.cuid) {
						vector<errmsgcl> errv;
						const string f0{schwarzs+"Modem "+blau+tty+schwarz+Tx[T_gibts]};
						const string f1{f0+Tx[T_nicht]};
						errv.push_back(errmsgcl(0,f0));
						errv.push_back(errmsgcl(1,f1));
						//// aus coreutils; ' time 10 ' geht nicht, '{ { sudo stty -F /dev/ttyS1 1>&3;kill 0;}|{ sleep 10;kill 0;} } 3>&1' auch nicht
						// stty auch aus crontab aufrufbar (Pfad: /usr/bin:/bin)
						if (!sudc.empty()) systemrueck(sudc+"date"); // dummy-Befehl, da der naechste stehenbleibt, wenn root-Passwort noetig
						terg=!systemrueck("timeout 10 "+sudc+"stty -F /dev/"+tty/*//+" time 10" wirkt nicht*/,
								obverb,oblog,/*rueck*/0,/*obsudc=*/0,/*verbergen=*/2,/*obergebnisanzeig=*/wahr,/*ueberschr=*/"",/*errm=*/&errv);
					} else {
						terg=ttytest(tty);
					} // 				if (cus.cuid) else
					if (terg) {
						obmodem=1;
						modems<<tty;
						hLog("Modem: "+blaus+tty+schwarz+Txk[T_gefunden]);
						break; // 30.7.20 wegen Reserveserver
					} // if (terg)
				} // if (tty!="ttyS0") 
				// KLA // if (!lstat(((qrueck[i])+"/device/driver").c_str(),&entrydriv)) 
			} // for(size_t i=0;i<qrueck.size();i++) 
			////  uchar modemsumgesteckt=0;
			uchar schonda{0};
			if (!hmodem.empty()) {
				for(size_t j=0;j<modems.size();j++) {
					if (modems[j]==hmodem) {
						schonda=1;
						break;
					}
				} // for(size_t j=0;j<modems.size();j++) 
				if (!schonda) hmodem.clear();
			} // if (!hmodem.empty()) 
			if (hmodem.empty()) {
				if (modems.size()) if (!modems[0].empty()) {
					if (obverb>1) {
						hLog("modems[0]: "+blaus+modems[0]+schwarz);
					} // 				if (obverb)
					hmodem=modems[0];/*//modemsumgesteckt=1;*/ 
					modemgeaendert=1;
				} //   if (modems.size()) if (!modems[0].empty()) if (modems[0]!=hmodem) 
			} // if (hmodem.empty()) 
			obmdgeprueft=1;
			if (!obmodem) {
				fLog(rots+Tx[T_Kein_Modem_gefunden]+schwarz,obfa[2]||obweg[2]==1||obher[2]==1?1:obverb,oblog);
				obfa[2]=obweg[2]=obher[2]=0;
			}
			// wenn zum Konfigurationszeitpunkt kein Modem drinstak, aber jetzt, dann rueckfragen
			if (!schonda && (obfa[2]||obweg[2]==1||obher[2]==1) /*//obmodem && agcnfA.hole("obmodem")=="0"*/) {
				fLog(Txk[T_rueckzufragen_wegen]+rots+"!schonda"+schwarz+" (Modem)",1,0);
				rzf=1;
			}
			// wenn nur obzuschreib, dann noch nicht auf neu eingestecktes Modem reagieren
		} // 		if (!obmdgeprueft)
	} // 	if (obfa[2] ...
	hLog(violetts+Txk[T_Ende]+Tx[T_pruefmodem]+schwarz);
	// wvdialconf oder schneller: setserial -a /dev/tty*, mit baud_base: <!=0>  als Kriterium
} // void hhcl::pruefmodem

//α
// aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz); //ω
	if (rzf) obfa[0]=obfa[1]=obfa[2]=1; // vor rueckfragen alle Moeglichkeiten pruefen
	if (obfa[1]||obweg[1]==1||obher[1]==1) pruefisdn(); // setzt ggf. obfa[1] wieder zurueck
	if (obfa[2]||obweg[2]==1||obher[2]==1) pruefmodem();
	if (!obfrbox) obfa[0]=obweg[0]=obher[0]=0;
	hintervalt=hintervall;
} // void hhcl::pvirtvorrueckfragen //α

void hhcl::neurf()
{
	for(auto omit=opn.schl.end();omit!=opn.schl.begin();) {
		omit--;
		if (!(*omit)->Txtrf.empty()) {
			const char* const text=(*omit)->Txtrf.c_str();
			cout<<text<<endl;
		}
	}
} // void hhcl::neurf
 //ω

// aufgerufen in virtlieskonfein, pvirtnachvi, virtrueckfragen
void hhcl::standardprio(const int obmitsetz)
{
	hLog(violetts+Tx[T_standardprio]+schwarz+", obmitsetz: "+ltoan(obmitsetz),1,0);
	if (obmitsetz) 
		for(int j=0;j<3;j++) {
			clprios[j]=prios[j];
		}
	memset(prios,0,3*sizeof *prios);
	// und jetzt prios mit standardisierten Prioritaeten aus clprios erstellt (also z.B. 3 statt 4)
	for(int p=1;p<=3;p++) {
		unsigned minp{(unsigned)-1}; // die kleinste uebrige Prioritaet, Vorgabe = die groesste unsigned-Zahl
		int minj{3+1}; 
		for(int j=0;j<3;j++) if ((obfa[j]||obweg[j]) && !prios[j]){ // Prioritaeten nur fuer aktive Programme
			if((unsigned)clprios[j]<minp){
				minp=clprios[j];
				minj=j;
			}
		} // 		for(int j=0;j<3;j++) ...
		if (minj<3+1) {
			if (p!=clprios[minj]) {
				caus<<"Setze obzuschreib in standardprio, minj: "<<minj<<", p: "<<p<<", clprios[minj]: "<<clprios[minj]<<endl;
				hccd.obzuschreib=1;
			}
			prios[minj]=p;
		} // 		if (minj<3+1)
	} // 	for(int p=1;p<=3;p++)
} // void hhcl::standardprio

// liefert 1, wenn fbfax als rnr.tes aufgerufen werden soll, 2 wenn capi, 3, wenn hyla
int hhcl::priorang(const int rnr)
{
 for(int p=0;p<3;p++) {
	if (prios[p]==rnr)
		return p+1;
 }
 return 0;
} // int hhcl::priorang

void hhcl::fuellfbip()
{
	////		const bool fbfehlt{(const bool)systemrueck("ping fritz.box -4c1",obverb,oblog,&fbip)}; // fritz.box
	fbip.clear();
	obfrbox=!systemrueck("A=169.254.1.1;ping -4c1 $A >/dev/null&&echo $A||ping -6c1 fritz.box|sed '1!d;s/^[^(]*([^(]*(\\([^)]*\\).*$/\\1/'",
			// z.B. 192.168.1.1 oder z.B. fd00::a96:d7ff:fe49:19ca
			obverb,oblog,&fbip); // liefert die IP-Adresse der Fritzbox
	// PING fritz.box (192.168.178.1) 56(84) bytes of data.
} // void hhcl::fuellfbip

// Leider laesst sich wohl zur Zeit ueber Tr-064 nicht die Fax-Funktion einstellen muss als ueber die Benutzeroberflaeche manuell geschehen
void hhcl::holfbpar()
{
	string mntdrv;
	// wenn eine Fritzbox eine IP-Adresse hat, wird in fuellfbip gesetzt
	if (fbip.size()) {
		svec frna;
		const string *const ipp{&fbip[0]};
		//				caus<<"*ipp: "<<*ipp<<endl;
		// wenn ein freundlicher Name gefunden wurde
		int gefunden{0};
		for (int iru=0;iru<2;iru++) {
			string ip;
			if (iru) ip='['+*ipp+']'; else ip=*ipp;
			if (!systemrueck("curl "+ip+":49000/tr64desc.xml 2>/dev/null|sed -n '/friendlyName/{s/^[^>]*>\\([^<]*\\).*/\\1/;p;q}'",obverb,oblog,&frna)&&frna.size()) {
				gefunden=1;
				break;
			}
		}
		if (gefunden) {
			// z.B. GSHeim
			//					caus<<"frna[0]: "<<frna[0]<<endl;
			fbdev="FritzBox "+frna[0];
			svec mounts;
			const string zufinden{"^//\\(192.168.178.1\\|169.254.1.1\\|fritz.box\\|"+*ipp+"\\)/"+frna[0]+" "};
			for(int aru=0;aru<2;aru++) {
				if (!systemrueck("mount|grep '"+zufinden+"'|cut -d' ' -f3",obverb,oblog,&mounts)&&mounts.size()) {
					// z.B. /mnt/gsheim
					//						caus<<"mounts[0]: "<<mounts[0]<<endl;
					// //192.168.178.1/DiabFB on /mnt/diabfb type cifs (rw,relatime,vers=1.0,cache=strict,username=ftpuser,domain=DIABFB,uid=0,noforceuid,gid=0,noforcegid,addr=192.168.178.1,unix,posixpaths,mapposix,acl,rsize=61440,wsize=65536,actimeo=1)
					mntdrv=mounts[0];
					svec datei;
					// die jüngste pdf-Datei auf dem CIFS-Verzeichnis suchen
					systemrueck("find '"+mntdrv+"' -type f -iname '*pdf' -print0|/usr/bin/xargs -0 -r ls -l --time-style=full-iso|sort -nrk 6,7|head -n1", obverb,oblog,&datei);
					if (datei.size()) {
						// -rwxrwxrwx 1 root root   10061 2017-11-01 10:03:52.000000000 +0100 /mnt/diabfb/Generic-FlashDisk-01/FRITZ/faxbox/01.11.17_10.03_Telefax.081316150166.pdf
						if (const size_t p1{datei[0].find(" "+mntdrv)+1}) {
							fbankvz=dir_name(datei[0].substr(p1));
						} // 									if (const size_t p1=datei[0].find(" "+tok[2])+1)
					} // 								if (datei.size())
					break; 
				} // 						if (!systemrueck("mount|grep '"+zufinden+"'|cut -d' ' -f3",obverb,oblog,&mounts)&&mounts.size())
				for(int iru=0;iru<2;iru++) {
					svec fstabs;
					systemrueck("grep '"+zufinden+"' /etc/fstab|cut -d' ' -f2",obverb,oblog,&fstabs,/*obsudc*/1);
					if (fstabs.size()) {
						mntdrv=fstabs[0];
					} else {
						string fbnameklein; // /mnt/gsheim
						transform(frna[0].begin(),frna[0].end(),std::back_inserter(fbnameklein),::tolower);
						fbnameklein="/mnt/"+fbnameklein;
						pruefverz(fbnameklein);
						systemrueck("echo //169.254.1.1/"+frna[0]+" "+fbnameklein+" cifs nofail,vers=1.0,credentials=/root/.fbcredentials 0 2 >>/etc/fstab",obverb,oblog,/*rueck*/0,/*obsudc*/1);
						anfgg(unindt,sudc+"sed -i '/^\\/\\/169.254.1.1\\/"+frna[0]+" /d' /etc/fstab",Tx[T_fstab_Eintrag_wieder_entfernen],obverb,oblog);
						mntdrv=fbnameklein;
					}
					if (!mntpunkt(mntdrv.c_str())) {
						anfgg(unindt,sudc+"umount "+mntdrv,"vor Loeschen absteigen",obverb,oblog);
						if (systemrueck("mount "+mntdrv,obverb,oblog,/*rueck*/0,/*obsudc*/1)) {
							systemrueck("sed -i '/ "+ersetzAllezu(mntdrv,"/","\\/")+" /d' /etc/fstab",obverb,oblog,/*rueck*/0,/*obsudc*/1);
						}
					}
				}
			} // 					for(int aru=0;aru<2;aru++)
		} // 				if (!systemrueck("curl ["+*ipp+"]:49000/tr64desc.xml 2>/dev/null|sed -n '/friendlyName/{s/^[^>]*>\\([^<]*\\).*/\\1/;p;q}'",obverb,oblog,&frna)&&frna.size())
	} // 				if (fbip.size())
	obverb=0;
} // void hhcl::holfbpar

const string hhcl::initdhyladt{"/etc/init.d/hylafax"};

// aufgerufen in: pruefhyla, main
int hhcl::setzhylavz()
{
	// koennte auch im Fall eines entfernten Modems oder hylafax-Programms benoetigt werden
	// sucht das Hylaverzeichnis und setzt varsphylavz darauf, return 0, wenn nicht gefunden dann varsphylavz="", return 1
	// varsphylavz und hsendqvz festlegen
	fLog(violetts+Tx[T_setzhylavz]+schwarz,obverb,oblog);
	// wird fruehestens in korrigierecapi benoetigt
	// varsphylavz wird benoetigt in: korrigierecapi, untersuchespool, hfaxsetup(pruefhyla), pruefhyla, hylaausgeb(untersuchespool,zeigweitere)
	// hsendqvz wird benoetigt in: loescheallewartenden, loeschewaise, zeigweitere, inDBh(faxemitH)
	const char* testcmd="/bin/faxrcvd";
	int fundart{0};
	uchar weiterpruefen{0}; 
	// 28.3.16: Die Datei /etc/init.d/hylafax+ taugt nicht fuer die Fallunterscheidung, da sie selbst eine Fallunterscheidung enthaelt

	svec hrueck;
	// 1) hylafax-Dienst im systemd suchen, dort steht z.B. ConditionPathExists=/var/spool/hylafax/etc/setup.cache ...
	systemrueck("grep /var $(dirname $(dirname $(which systemctl)))/lib/systemd/system/*fax*.service 2>/dev/null|"
			"head -n 1|cut -d= -f2|sed 's/^[[:space:]]*//'|awk -F'/etc' '{print $1}'", obverb,oblog,&hrueck,/*obsudc=*/0);
	if (hrueck.size()) {
		varsphylavz=hrueck[0];
		fundart=1;
	} else {
		// 2) ... ansonsten steht vielleicht in /etc/init.d/hylafax das Verzeichnis:
		// in der OpenSuse-Datei bekam das Verzeichnis den Namen "SPOOL",
		// in Ubuntu "HYLAFAX_HOME"; dort bekam die Variable "SPOOL" einen anderen Inhalt

		////    cppSchluess hylaconf[]={{"SPOOL"},{"HYLAFAX_HOME"}};
		////    size_t cs=elemzahl(hylaconf);
		struct stat hstat{0};
		if (!lstat(initdhyladt.c_str(),&hstat)) {
			initdhyladt_gibts=1;
			if (!hfcnfCp) {
				hfcnfCp=new schAcl<WPcl>("hfcnfC", new vector<aScl>{
						{"SPOOL",&spoolvz},
						{"HYLAFAX_HOME",&hylafax_homevz}
						});
			}
			// confdcl *hfaxcp{0}; // Zeiger auf ausgelesene /etc/init.d/hylafax.conf
			// if (hfaxcp) delete hfaxcp;
			confdcl hfaxc(initdhyladt,obverb);
			hfaxc.kauswert(hfcnfCp);
		} //     if (!lstat(initdhyladt.c_str(),&hstat))
		if (!hylafax_homevz.empty()) {
			//  if (cpplies(initdhyladt,hylaconf,cs)) KLA
			varsphylavz=hylafax_homevz;
			fundart=2;
		} else if (!spoolvz.empty()) {
			varsphylavz=spoolvz;
			fundart=2;
		} else {
			// 3) ... ansonsten schauen, welches Verzeichnis es gibt ...
			struct stat hstat{0},fstat{0};
			const char *const hfax{"/var/spool/hylafax"}, *const ffax{"/var/spool/fax"};
			const int hgibts{!lstat(hfax,&hstat)}, fgibts{!lstat(ffax,&hstat)};
			if (hgibts && !fgibts) {
				varsphylavz=hfax; 
				fundart=3;
			} else if (!hgibts && fgibts) {
				varsphylavz=ffax;
				fundart=3;
			}  else if (hgibts && fgibts) {
				// 4) ... falls beide, dann das juengere nehmen
				if (hstat.st_mtime>fstat.st_mtime) {
					varsphylavz=hfax;
				} else {
					varsphylavz=ffax;
				}
				fundart=4;
			} else {
				// 5) ... falls beide nicht, dann /var/spool/hylafax
				varsphylavz=hfax;
				fundart=5;
			} //       if (hgibts && !fgibts) else else
		} //     if (!hycnfA[1].wert.empty())  else else 
		weiterpruefen=1;
	} // if (hrueck.size()) else 

	// falls nicht im systemd-Dienst gefunden, dann zuerst im praeferierten, dann in anderen Verzeichnissen pruefen, wo es ./bin/faxrecvd gibt 
	if (weiterpruefen) {
		////  if (lsys.getsys(obverb,oblog)==sus) varsphylavz="/var/spool/fax";
		////  else if (lsys.getsys(obverb,oblog)==deb) varsphylavz="/var/spool/hylafax";
		string testvz{varsphylavz};
		for(unsigned iru=0;iru<(elemzahl(moeglhvz))+1;iru++) {
			struct stat entryhyla{0};
			if (!lstat((testvz+testcmd).c_str(),&entryhyla)) {
				varsphylavz=testvz; 
				if (iru) fundart=6;
				break;
			} else if (iru==elemzahl(moeglhvz)) {
				// obhyla=0 hier noch nicht, da setzhylavz auch einmal vor der Installation schon aufgerufen wird
				break; // kein Verzeichnis gefunden
			} //   else if (iru==elemzahl(moeglhvz))
			testvz=moeglhvz[iru];
		} //     for(unsigned iru=0;iru<(elemzahl(moeglhvz))+1;iru++)
	} //   if (weiterpruefen)
	if (obverb) {
		string grund;
		switch (fundart) {
			case 1: grund=Tx[T_aus_systemd_fax_service_Datei_ermittelt];break;
			case 2: grund=Tx[T_aus_etc_init_d_hylafax_ermittelt];break;
			case 3: grund=Tx[T_aus_seiner_ausschliesslichen_Existenz_ermittelt];break;
			case 4: grund=Tx[T_aus_seinem_geringen_Alter_ermittelt];break;
			case 5: grund=Tx[T_aus_mangelnder_Alternative_ermittelt];break;
			case 6: grund=Tx[T_aus_Existenz_von]+blaus+testcmd+schwarz+Tx[T_ermittelt];break;
		} //     switch (fundart)
		hLog(Tx[T_hylafax_Verzeichnis]+blaus+varsphylavz+schwarz+grund);
	} // if (obverb)
	kuerzevtz(&varsphylavz);
	hsendqvz=varsphylavz+"/sendq";
	pruefverz(hsendqvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/huser,/*benutzer=*/cuser,/*obmachen=*/0);
	hdoneqvz=varsphylavz+"/doneq";
	pruefverz(hdoneqvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/huser,/*benutzer=*/cuser,/*obmachen=*/0);
	harchivevz=varsphylavz+"/archive";
	pruefverz(harchivevz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0,/*besitzer=*/huser,/*benutzer=*/cuser,/*obmachen=*/0);
	xferfaxlog=varsphylavz+"/etc/xferfaxlog"; 
	hempfavz=varsphylavz+"/" DPROG "arch";
	return 0;
} // int hhcl::setzhylavz

// in hliesconf() und hconfigtty()
void hhcl::setzmodconfd()
{
	modconfdt=this->varsphylavz+"/etc/config"+"."+this->hmodem; 
} // void hhcl::setzmodconfd


// aufgerufen in: pruefhyla (2x)
// Modem konfigurieren
int hhcl::hconfigtty()
{
	hLog(violetts+"hconfigtty()"+schwarz);
	int ret{0};
	setzmodconfd();
	struct stat bakstat{0};
	if (lstat((modconfdt+".bak").c_str(),&bakstat)) {
		kopier(modconfdt,modconfdt+".bak",obverb,oblog);
	}
	////systemrueck("test -f '"+modconfdt+"' && test -f '"+modconfdt+".bak' ||"+sudc+"cp -a '"+modconfdt+"' '"+modconfdt+".bak'",obverb,oblog);
	//// <<rot<<modconfdt<<schwarz<<endl;
	// z.B. /var/spool/hylafax/etc/config.ttyACM0
	mdatei hci(modconfdt,ios::out);
	if (hci.is_open()) {
		//// <<rot<<" ist offen"<<schwarz<<endl;
		time_t jetzt=time(0);
		hci<<Tx[T_Konfiguration_von_hylafax_durch]+meinname+Tx[T_vom]<<ztacl(jetzt,"%d.%m.%y %T")<<endl;
		//// pthread_mutex_lock(&timemutex);
		//// struct tm *tm=localtime(&&jetzt);
		//// char buf[80];
		//// strftime(buf, sizeof(buf), "%d.%m.%y %T", tm);
		//// pthread_mutex_unlock(&timemutex);
		hci<<"CountryCode:    "<<this->countrycode<<endl;
		hci<<"AreaCode:   "<<this->citycode<<endl;
		hci<<"FAXNumber:    \""<<this->countrycode<<"."<<this->citycode<<"."<<this->msn<<"\""<<endl;
		hci<<"LongDistancePrefix: "<<this->LongDistancePrefix<<endl;
		hci<<"InternationalPrefix:  "<<this->InternationalPrefix<<endl;
		hci<<"DialStringRules:  \"etc/dialrules\""<<endl;
		hci<<"ServerTracing:    0xFFFFF"<<endl;
		hci<<"SessionTracing:   0xFFFFF"<<endl;
		hci<<"RecvFileMode:   0600"<<endl;
		hci<<"LogFileMode:    0600"<<endl;
		hci<<"DeviceMode:   0600"<<endl;
		hci<<"RingsBeforeAnswer:  "<<this->hklingelzahl<<Tx[T_muss_mindestens_2_sein_zur_Uebergabe_der_Nr_des_Anrufenden]<<endl;
		hci<<"MaxDials: "<<this->maxhdials<<endl;
		hci<<"MaxTries: "<<this->maxhdials<<endl;
		hci<<"CIDNumber: NMBR="<<endl;
		hci<<"CIDName:   NAME="<<endl;
		hci<<"SpeakerVolume:    off"<<endl;
		hci<<"GettyArgs:    \"-h %l dx_%s\""<<endl;
		hci<<"LocalIdentifier:  "<<this->LocalIdentifier<<endl;
		hci<<"LogFacility:    daemon"<<endl;
		//// #ifdef obhp
		struct stat Lstat{0};
		if (!lstat((this->varsphylavz+"/etc/LiberationSans-25.pcf").c_str(),&Lstat)) {
			hci<<"TagLineFont:    etc/LiberationSans-25.pcf"<<endl;
		} else {
			//// #else
			hci<<"TagLineFont:    etc/lutRS18.pcf"<<endl;
			//// #endif
		}
		hci<<"TagLineFormat:    \"Von %%l|%c|Seite %%P of %%T\""<<endl;
		hci<<"AdaptiveAnswer:   yes"<<endl;
		hci<<"AnswerRotary:   \"voice fax data\""<<endl;
		hci<<"MaxRecvPages:   500"<<endl;
		hci<<"JobReqBusy:   "<<this->hintervall<<endl; // 120
		hci<<"# Modem-related stuff: should reflect modem command interface"<<endl;
		hci<<"# and hardware connection/cabling (e.g. flow control)."<<endl;
		hci<<"ModemType:    Class1    # use class 1 interface"<<endl;
		hci<<"ModemRate:    38400   # rate for DCE-DTE communication"<<endl;
		hci<<"ModemFlowControl:  rtscts # hardware flow control # xonxoff   # software flow control"<<endl;
		hci<<"ModemSetupDTRCmd: ATS13=1&D3 # ATS13=1&D2 # setup so DTR drop resets modem"<<endl;
		hci<<"ModemSetupDCDCmd: AT&C1   # setup so DCD reflects carrier (or not)"<<endl;
		hci<<"ModemNoFlowCmd:   AT&H0 # AT&H0&I0&R1 # setup modem for no flow control"<<endl;
		hci<<"ModemHardFlowCmd: AT&H1 # AT&H1&I0&R2 # setup modem for hardware flow control"<<endl;
		hci<<"ModemSoftFlowCmd: AT&H2 # AT&H2&I2&R1 # setup modem for software flow control"<<endl;

		hci<<"ModemResultCodesCmd:  ATQ0X4 #CID=1    # enable result codes"<<endl;
		hci<<"ModemMfrQueryCmd: !USR5637 # !USR"<<endl;
		hci<<"ModemModelQueryCmd: ATI3"<<endl;
		hci<<"ModemRevQueryCmd: ATI7    # XXX returns a multi-line result"<<endl;
		hci<<"# When AT+FCLASS=1 is issued the modem automatically switches"<<endl;
		hci<<"# to software flow control; these parameters let the fax software"<<endl;
		hci<<"# reset flow control as needed after entering Class 1."<<endl;
		hci<<"Class1NFLOCmd:    AT+FLO=0 # AT&H0&I0&R1  # setup modem for no flow control"<<endl;
		hci<<"Class1HFLOCmd:    AT+FLO=2 # AT&H1&I0&R2  # setup modem for hardware flow control"<<endl;
		hci<<"Class1SFLOCmd:    AT+FLO=1 # ""   # modem does this automatically"<<endl;
		hci<<"# This should resolve \"DIS/DTC received 3 times\" errors:"<<endl;
		hci<<"Class1ResponseWaitCmd:  AT+FRS=1  # wait after sending TCF for response"<<endl;
		hci<<"# The remainder of this configuration is included so that the"<<endl;
		hci<<"# modem \"idles\" in Class 0 while not sending or receiving facsimile."<<endl;
		hci<<"ModemSetupAACmd:  AT+FCLASS=0 # leave modem idling in class 0"<<endl;
		hci<<"ModemAnswerCmd:   AT+FCLASS=1A  # answer in Class 1"<<endl;
		hci<<"# die folgenden sind aus dem Internet"<<endl;
		hci<<"ModemResetCmds:   ATS19=255"<<endl;
		hci<<"ModemAnswerFaxCmd:  ATS27=8S56=0+FCLASS=1;A"<<endl;
		hci<<"ModemAnswerDataCmd: ATS27=1S56=16+FCLASS=0;A"<<endl;
		hci<<"Class1RecvIdentTimer: 10000"<<endl;
		hci<<""<<endl;
		hci<<"# When using AT+FRS=n we see USR modems reset themselves in the middle of sessions"<<endl;
		hci<<"# this is not good.  So, we seem to work-around that problem by not using the"<<endl;
		hci<<"# command.  Unfortunately, this isn't an ideal thing."<<endl;
		hci<<"Class1SwitchingCmd: \"<delay\0727>\""<<endl;
		hci<<"# FaxRcvdCmd: ./schreibe.sh"<<endl;
	} else {
		cerr<<Txk[T_datei]<<modconfdt<<Tx[T_nichtbeschreibbar]<<endl;
		// <<rot<<" nicht offen"<<schwarz<<endl;
		ret=1;
	} // 	if (hci.is_open())
	hLog(violetts+Txk[T_Ende]+"hconfigtty()"+schwarz);
	return ret;
} // void hhcl::hconfigtty

// aufgerufen in faxemitH, pruefhyla
void useruucp(const string& huser, const int obverb, const int oblog)
{
	fLog(violetts+"useruucp()"+schwarz,obverb,oblog);
	if (systemrueck("getent passwd "+huser,obverb,oblog,/*rueck=*/0,/*obsudc=*/1)) {
		const string bef{"useradd -b /etc -c \"Unix-to-Unix CoPy\" -U -r "+huser};
		systemrueck(bef,obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
		anfgg(unindt,sudc+"userdel "+huser,bef,obverb,oblog);
	} // 	if (systemrueck
} // void useruucp

// aufgerufen in: hservice_faxq_hfaxd und hfaxsetup
void hhcl::setzfaxgtpfad()
{
	struct stat entryfaxgt{0};
	if (lstat(faxgtpfad.c_str(),&entryfaxgt)) {
		faxgtpfad.clear();
		//  faxgtpfad="/usr/lib/fax/faxgetty";
		//    faxgtpfad="/usr/sbin/faxgetty";
		obprogda("faxgetty",obverb,oblog,&faxgtpfad);
		if (faxgtpfad.empty() || lstat(faxgtpfad.c_str(),&entryfaxgt)) {
			faxgtpfad.clear();
			svec qrueck;
			const string wo{"/usr/lib/fax /usr/sbin /usr/bin /root/bin /sbin /usr/local/sbin /usr/local/bin"};
			if (findv==1) {
				systemrueck(sudc+"find "+wo+" -perm /111 -name faxgetty", obverb>0?obverb-1:0,oblog,&qrueck);
			} else findfile(&qrueck,findv,obverb,oblog,0,wo,/*muster=*/"faxgetty$",-1,1,Fol_Dat,0,0,0,1);
			if (qrueck.size()) 
				faxgtpfad=qrueck[0];
		} // 		if (faxgtpfad.empty() || lstat(faxgtpfad.c_str(),&entryfaxgt))
	} // 	if (lstat(faxgtpfad.c_str(),&entryfaxgt))
	// violett<<"faxgtpfad 4: "<<faxgtpfad<<schwarz<<endl;
} // void hhcl::setzfaxgtpfad

// aufgerufen in: pruefhyla
// Dienste erstellen
int hhcl::hservice_faxq_hfaxd()
{
	hLog(violetts+"hservice_faxq_hfaxd()"+schwarz);
	int hylafehler{0};
	struct stat hstat{0}, 
							fstat{0};
	if (hfaxdpfad.empty()||lstat(hfaxdpfad.c_str(),&hstat)) { obprogda("hfaxd",obverb,oblog,&hfaxdpfad); }
	hylafehler+=!shfaxd->spruef("HFaxd",0/*1*/,meinname,hfaxdpfad+" -d -i hylafax"/* -s 444*/, varsphylavz+"/etc/setup.cache", "",obverb,oblog);
	this->shfaxd->machfit(obverb,oblog);
	if (faxqpfad.empty()||lstat(faxqpfad.c_str(),&fstat)) { obprogda("faxq",obverb,oblog,&faxqpfad); }
	hylafehler+=!sfaxq->spruef("Faxq",0/*1*/,meinname,faxqpfad+" -D", varsphylavz+"/etc/setup.cache", shfaxd->sname+".service",obverb,oblog);
	setzfaxgtpfad();
	hylafehler+=!this->sfaxgetty->spruef("HylaFAX faxgetty for "+this->hmodem,0,meinname,faxgtpfad+" "+this->hmodem,"","",obverb,oblog,0);
	return hylafehler;
} // void hservice_faxq_hfaxd

// aufgerufen in: pruefhyla
int hhcl::hconfig() const
{
	hLog(violetts+"hconfig()"+schwarz);
	int erg{0};
	const string confd{this->varsphylavz+"/etc/config"};
	mdatei conf(confd,ios::out);
	if (conf.is_open()) {
		conf<<"LogFacility:    daemon"<<endl;
		conf<<"CountryCode:    "<<this->countrycode<<endl;
		conf<<"AreaCode:   "<<this->citycode<<endl;
		conf<<"LongDistancePrefix: "<<this->LongDistancePrefix<<endl;
		conf<<"InternationalPrefix:  "<<this->InternationalPrefix<<endl;
		conf<<"DialStringRules:  \"etc/dialrules\""<<endl;
		conf<<"ServerTracing:    1"<<endl;
		conf<<"SessionTracing:   0xffffffff"<<endl;
		struct stat entryfaxsd{0};
		svec qrueck;
		string faxsdpfad{this->varsphylavz+"/bin/faxsend"};
		if (lstat(faxsdpfad.c_str(),&entryfaxsd)) {
			faxsdpfad="/usr/sbin/faxsend";
			if (lstat(faxsdpfad.c_str(),&entryfaxsd)) {
				faxsdpfad.clear();
				const string wo{"/usr /root/bin /sbin"};
				if (findv==1) {
					systemrueck(sudc+"find "+wo+" -perm /111 -name faxsend",obverb>0?obverb-1:0,oblog,&qrueck);
				} else findfile(&qrueck,findv,obverb,oblog,0,wo,/*muster=*/"faxsend$",-1,1,Fol_Dat,0,0,0,1);
				if (qrueck.size()) 
					faxsdpfad=qrueck[0];
			} // 			if (lstat(faxsdpfad.c_str(),&entryfaxsd))
		} // 		if (lstat(faxsdpfad.c_str(),&entryfaxsd))
		if (!faxsdpfad.empty())
			conf<<"SendFaxCmd:   "<<faxsdpfad<<endl;
		conf<<"Use2D:      \"no\""<<endl;
	} else {
		cerr<<"hconfig(): "<<Txk[T_datei]<<confd<<Tx[T_nichtbeschreibbar]<<endl;
		erg=1;
	} //   if (conf.is_open())
	hLog(violetts+Txk[T_Ende]+"hconfig()"+schwarz);
	return erg;
} // void hconfig

// aufgerufen in pruefhyla
// hylafax konfigurieren 
void hhcl::hfaxsetup()
{
	hLog(violetts+"hfaxsetup()"+schwarz);
	string faxsu;
	////  const char *faxsu="/usr/sbin/faxsetup";
	if (obprogda("faxsetup",obverb,oblog,&faxsu)) {
#ifdef DPROGsetup
		// das Skript faxsetup soll leicht veraendert als '" <DPROG> "setup' abgespeichert und dann aufgerufen werden
		const char *afaxsu="/usr/local/sbin/" DPROG "setup";
		mdatei alt(faxsu,ios::in);
		if (alt.is_open()) {
			mdatei neu(afaxsu,ios::out);
			if (neu.is_open()) {
				string zeile, ergzeile;
				size_t znr=0,promptz=0;
				string vorgabe;
				while(getline(alt,zeile)) {
					size_t p0,p1,kla,klz,einr=0;
					uchar zukomm{0};
					if (zeile.find("INTERACTIVE=yes")!=string::npos) {
						zeile="INTERACTIVE=no" # Aenderung G.Schade 25.5.16;
					} else if (zeile.find("ok=prompt")!=string::npos) {
						// Interaktivitaet streichen
						zeile="     ok=skip    # prompt for parameters # Aenderung G.Schade 1.1.16";
					} else if (!zeile.find("PATH_EGETTY=")) {
						// suche das aktuelle Fax-Empfangsprogramm; 'which faxgetty' geht nicht immer, da z.B. /usr/lib/fax/ nicht im Standard-Befehlssuchpfad,
						// aber unter Opensuse 42.1 der Vorgabeort fuer faxgetty
						zeile="PATH_EGETTY=$("+sudc+"find /usr/lib/fax /usr/sbin /usr/bin /root/bin /sbin -perm /111 -name faxgetty 2>/dev/null) "
							"# /bin/egetty # pathname for external getty program # Aenderung G.Schade 29.2./ 23.3.16";
					} else if (zeile.find("$MV $DIR_LIBDATA/hyla.conf.tmp $DIR_LIBDATA/hyla.conf")!=string::npos) {
						// wenn zuvor keine der Veraenderungen von hyla.conf erfolgt, dann gibt es auch hyla.conf.tmp nicht;
						// dies soll ohne Fehlermeldung gehen
						zeile=" test -f \"$DIR_LIBDATA/hyla.conf.tmp\" && "+zeile;
					} else {
						if (zeile[0]!='#' && (p0=zeile.find("prompt "))!=string::npos) {
							einr=p0+2;
							if ((kla=zeile.find('[',p0))!=string::npos) if ((klz=zeile.find(']',kla))!=string::npos) {
								// faxaddmodem soll hier nicht aufgerufen werden
								promptz=znr; 
								if (zeile.find("run faxaddmodem")==string::npos) 
									vorgabe=zeile.substr(kla+1,klz-kla-1);
								else
									vorgabe="no";
							}
							zukomm=1;
						} //             if (zeile[0]!='#' && (p0=zeile.find("prompt "))!=string::npos)
						// wenn in der oder der naechsten Zeile read steht
						// (z.B. in den Funktionen promptFor...parameter()), dann soll ohne Rueckfrage die Vorgabe verwendet werden
						if ((znr==promptz || znr==promptz+1) && zeile[0]!='#' && (p1=zeile.find("read "))!=string::npos) {
							ergzeile=string(einr,' ')+zeile.substr(p1+5);
							if ((p1=ergzeile.find(' ',einr))!=string::npos) ergzeile=ergzeile.substr(0,p1);
							ergzeile=ergzeile+"=\""+vorgabe+"\" # G.Schade 1.1.16";
							zukomm=1;
						}
						if (zukomm) zeile="# "+zeile+" # Kommentar G.Schade 1.1.16";
					} // if (zeile.find("INTERACTIVE=yes")!=string::npos) else else else else
					neu<<zeile<<endl;
					if (!ergzeile.empty()) {
						neu<<ergzeile<<endl;
						ergzeile.clear();
					}
					znr++;
				} // while(getline(alt,zeile)) 
				neu.close();
				if (chmod(afaxsu.c_str(),S_IRWXU|S_IRWXG))
					systemrueck(sudc+"chmod 770 '"+afaxsu+"'",0,1);
				this->sfaxgetty->stop(obverb,oblog);
				this->shfaxd->stop(obverb,oblog);
				this->sfaxq->stop(obverb,oblog);
				/*//
					systemrueck(sudc+"systemctl stop "+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog);
					systemrueck(sudc+"pkill "+this->sfaxgetty->ename+" "+this->shfaxd->ename+" "+this->sfaxq->ename,obverb,oblog);
				 */
				fLog(blaus+Tx[T_Fuehre_aus_Dp]+schwarz+afaxsu+blau+Tx[T_falls_es_hier_haengt_bitte_erneut_aufrufen]+schwarz,1,oblog);
				obverb=0; // dann haengt's immer
				system((sudc+"pkill hfaxd;"+shpf+" "+afaxsu+(obverb?" -verbose":"")+" >/dev/null 2>&1").c_str());  
				this->sfaxgetty->restart(obverb,oblog);
				this->shfaxd->restart(obverb,oblog);
				this->sfaxq->restart(obverb,oblog);
				//// systemrueck(". "+afaxsu+(obverb?" -verbose":""),obverb,oblog,0,falsch); // haengt am Schluss, geht nicht mit unbuffer, unbuffer /usr/local/sbin/" DPROG "setup -verbose, loeschen von exit 0 am schluss, exec, stty -echo -onlcr usw., nohup,
				fLog(blaus+Txk[T_Fertig_mit]+schwarz+afaxsu,1,oblog);
				servc::daemon_reload();
				////        systemrueck("rm "+afaxsu,1,1);
			} // if (neu.is_open()) 
		} // if (alt.is_open()) 
#else
		this->sfaxgetty->stop(obverb,oblog,1);
		this->shfaxd->stop(obverb,oblog,1);
		this->sfaxq->stop(obverb,oblog,1);
		/*//
			systemrueck(sudc+"systemctl stop "+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog);
			systemrueck(sudc+"pkill "+this->sfaxgetty->ename+" "+this->shfaxd->ename+" "+this->sfaxq->ename,obverb,oblog);
		 */
		fLog(blaus+Tx[T_Fuehre_aus_Dp]+schwarz+sudc+faxsu+" -nointeractive"+blau+Tx[T_falls_es_hier_haengt_bitte_erneut_aufrufen]+schwarz,1,oblog);
		pruefplatte();
		// Stehenbleiben konnte ich nur durch pkill verhindern, Prozess des Bash-Gabelprogramms nicht gefunden
		if (!systemrueck("( (sleep 20; pkill " DPROG ") & exec "+faxsu+" -nointeractive"+(obverb?" -verbose":"")+" )",obverb,oblog,0,1)) {
			this->shfaxd->stop(obverb,oblog,1);
			this->sfaxq->stop(obverb,oblog,1);
			servc::daemon_reload();
		} // if (!systemrueck(sudc+faxsu+" -nointeractive"+(obverb?" -verbose":""),obverb,oblog,0,2)) 
		/*//
			int erg __attribute__((unused));
			erg=system((sudc+"$(which sh) $("+sudc+"env \"PATH=$PATH\" which faxsetup) -nointeractive"+string(obverb?" -verbose":"")+
			"&&"+sudc+"pkill hfaxd faxq >/dev/null 2>&1"
			"&&"+sudc+"systemctl daemon-reload").c_str()); 
		 */
		this->sfaxgetty->start(obverb,oblog);
		this->shfaxd->start(obverb,oblog);
		this->sfaxq->start(obverb,oblog);
		pruefplatte();
		// systemrueck(". "+faxsu+(obverb?" -verbose":""),obverb,oblog,0,falsch); // haengt am Schluss, geht nicht 
		// mit unbuffer, unbuffer /usr/local/sbin/" DPROG "setup -verbose, loeschen von exit 0 am schluss, exec, stty -echo -onlcr usw., nohup,
		fLog(blaus+Txk[T_Fertig_mit]+schwarz+faxsu,1,oblog);
		////    systemrueck(sudc+"systemctl daemon-reload",0,1);
#endif
	} //   if (!lstat(faxsu, &entrybuf)) KLA
	this->setzfaxgtpfad();
} // hfaxsetup

// in pruefhyla
void hhcl::hliesconf()
{
	hLog(violetts+"hliesconf()"+schwarz);
#ifdef false
	const char* const sarr[]{"CountryCode","AreaCode","FAXNumber","LongDistancePrefix","InternationalPrefix","RingsBeforeAnswer","LocalIdentifier","MaxDials"};
	schlArr hyaltcnfA(sarr,elemzahl(sarr));
#endif
	setzmodconfd();
	struct stat mstat{0};
	if (lstat(modconfdt.c_str(),&mstat)) {
		hylazukonf=1;
	} else {
#ifdef false
		confdat haltcd(modconfdt,&hyaltcnfA,obverb,':');
		if (countrycode_dt!=countrycode || citycode_dt!=citycode || faxnumber_dt=countrycode+"."+citycode+"."+msn 
				|| longdistanceprefix_dt!=LongDistancePrefix || internationalprefix_dt!=InternationalPrefix 
				|| ringsbeforeanswer_dt!=hklingelzahl || localidentifier_dt!=LocalIdentifier|| maxdials_dt!=maxhdials /*|| hyaltcnfA.schl[7].wert!=maxdials */
			 ) {
			hylazukonf=1;
		} // if (hyaltcnfA.shl[0].wert ...
#else
		if (!hyaltcnfCp) {
			hyaltcnfCp=new schAcl<WPcl>("hyaltcnfC", new vector<aScl>{
					{"CountryCode",&countrycode_dt},
					{"AreaCode",&areacode_dt},
					{"FAXNumber",&faxnumber_dt},
					{"LongDistancePrefix",&longdistanceprefix_dt},
					{"InternationalPrefix",&internationalprefix_dt},
					{"RingsBeforeAnswer",&ringsbeforeanswer_dt},
					{"JobReqBusy",&jobreqbusy_dt},
					{"LocalIdentifier",&localidentifier_dt},
					{"MaxDials",&maxdials_dt}
					});
		}
		confdcl hyaltc(modconfdt,obverb,':');
		hyaltc.kauswert(hyaltcnfCp);
		if (countrycode_dt!=countrycode ||
				areacode_dt!=citycode ||
				faxnumber_dt!=countrycode+"."+citycode+"."+msn ||
				longdistanceprefix_dt!=LongDistancePrefix ||
				internationalprefix_dt!=InternationalPrefix||
				ringsbeforeanswer_dt!=hklingelzahl ||
				jobreqbusy_dt!=hintervall ||
				localidentifier_dt!=LocalIdentifier ||
				maxdials_dt!=maxhdials ||
				0 ) {
			hconfigtty();
			caus<<rot<<"schreibe Hylafax-conf"<<schwarz<<endl;
			shylafaxd->restart(obverb>0?obverb-1:0,oblog);
		}
#endif
	} //   if (lstat(modconfdt.c_str(),&mstat)) else
	// hyaltcnfA.ausgeb();
} // void hhcl::hliesconf


// aufgerufen in dovh, pvirtfuehraus
// Rueckgabe: wie obfa[2] eingestellt sein sollte
int hhcl::pruefhyla()
{
	//// const int altobverb{obverb};
	hLog(violetts+Tx[T_pruefhyla]+schwarz);
	int ret{1};
	hylasv1();
	do { // fuer break
		caus<<"hmodem: "<<hmodem<<endl;
		if (hmodem.empty()) {
			fLog(blaus+Tx[T_Kein_Modem_gefunden]+schwarz,(obfa[2]||obweg[2]==1||obher[2]==1)?1:obverb,oblog);
			this->obfa[2]=obweg[2]=obher[2]=0;
		} else {
			lsysen system=lsys.getsys(obverb,oblog);
			hyinst hyinstart; // hyla source, hyla Paket, hylaplus Paket
			if (system==deb /*// || system==fed*/) {
				hyinstart=hysrc;
			} else {
				hyinstart=hyppk;
			} 
			hylasv2(hyinstart);
			if (obfa[2]||obweg[2]==1||obher[2]==1) {
				long br{0}; // baud rate
				string brs; // Baud-Rate-String
				int hylalaeuftnicht{0};
				static uchar hylafehlt{1};
				uchar falscheshyla{0};
				uchar modemlaeuftnicht{1};
				uchar frischkonfiguriert{0};
				if (modemgeaendert) {
					if (hconfigtty()) {
						ret=0;
						break;
					}
					caus<<"Setze obzuschreib in pruefhyla"<<endl;
					hccd.obzuschreib=1;
				} //   if (modemgeaendert)

				// Baud rate ermitteln ...
				svec ruecki;
				systemrueck(("stty -F /dev/")+this->hmodem+"| head -n 1 | cut -f2 -d' '",obverb,oblog,&ruecki,/*obsudc=*/1);
				if (ruecki.size()) {
					brs=ruecki[0];
					br=atol(brs.c_str());
				} // 				if (ruecki.size())
				// .. und anzeigen
				if (br<=0) {
					fLog(Tx[T_Baudratevon]+blaus+"/dev/"+this->hmodem+schwarz+Tx[T_mit_af]+rot+brs+schwarz+Tx[T_zugeringVerwendeHylafaxnicht],1,1);
					////    return 1;
				} else {
					hLog("Modem '"+blaus+"/dev/"+this->hmodem+schwarz+Tx[T_mit_Baudrate]+gruen+brs+schwarz+Tx[T_wird_verwendet]);
				} //   if (br<=0) else
				// ein Fehler in der Version 4.0.7 von libtiff verhindert die Zusammenarbeit mit hylafax
				/*//
					const string befehl="sh -c \"NACHWEIS="+lsys.getlib64()+"/sclibtiff;! test -f /usr/include/tiff.h ||! test -f \\$NACHWEIS"
					"&&{ "+linstp->psuch+" cmake||"+linstp->instyp+" cmake;true"
					"&& P=tiff_copy; T=\\$P.tar.gz; Z=tiff-4.0.7"
					"; wget https://github.com/libelle17/\\$P/archive/master.tar.gz -O \\$T"
					"&& tar xpvf \\$T && mv \\${P}-master \\$Z && cd \\$Z"
					"&& rm -f CMakeCache.txt"
					"&& sed -i.bak s'/uint16 Param;/uint32 Param;/' libtiff/tif_fax3.h"
					"&& cmake -DCMAKE_INSTALL_PREFIX=/usr -DLIBTIFF_ALPHA_VERSION=1 . "
					"&& make"
					"&& "+sudc+"make install"
					"&&{ grep -q \\\"cd \\\"\\$(pwd)\\\" \\\""+unindt+"\\\""
					"|| printf \\\"cd \\\"\\$(pwd)\\\" && make uninstall; cd \\\""+instvz+"\\\"\\n\\\" >> \\\""+unindt+"\\\";} "
					"&& "+sudc+"touch \\$NACHWEIS;};:\"";
				 */
				/*//
					systemrueck("sh -c 'cd \""+instvz+"\";T="+datei+".tar.gz; wget https://github.com/libelle17/"+datei+"/archive/master.tar.gz -O $T'", 
					return systemrueck("sh -c 'P="+was+";T=$P.tar."+endg+";M=$P-master;cd \""+instvz+"\" && tar xpvf $T"
					"&& rm -rf $P 2>/dev/null||"+sudc+"rm -rf $P&& mv $M $P'",obverb,oblog);
					return systemrueck("sh -c 'cd \""+instvz+vtz+was+"\"&&"+vorcfg+"&&./configure "+cfgbismake+" make &&"+sudc+"make install "
					"&&{ grep -q \"cd \"$(pwd)\" \""+unindt+"\""
					"|| printf \"cd \"$(pwd)\" && make uninstall; cd \""+instvz+"\"\\n\" >> \""+unindt+"\";} "
					"'"
				 */
				prueftif(TIFFGetVersion());

				for(unsigned versuch=0;versuch<3;versuch++) {
					// 1) Dienst(e) hylafax, (hylafax-)hfaxd, (hylafax-)faxq identifizieren
					// pruefen, ob hylafax.service laeuft
					hLog(Tx[T_Pruefe_ob_Hylafax_gestartet]);
					const char* const c_hfs="hylafax";
					const char* const c_hfc="hylafax-client";
					const char* const c_hfps="hylafax+";
					const char* const c_hfpc="hylafax+-client";
					char *hfr, *hfcr, *hff, *hfcf; // hylafax richtig, hylafax client richtig, hylafax falsch, hylafax client falsch
					string hfftext;
					hylalaeuftnicht=1;
					hylafehlt=1;
					if (hyinstart==hysrc || hyinstart==hyppk) {
						hfr=(char*)c_hfps; hfcr=(char*)c_hfpc; hff=(char*)c_hfs; hfcf=(char*)c_hfc;
						hfftext=Tx[T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen];
						// => hyinstart==hypak
					} else {
						hfr=(char*)c_hfs; hfcr=(char*)c_hfc; hff=(char*)c_hfps; hfcf=(char*)c_hfpc;
						hfftext=Tx[T_Hylafaxplus_entdeckt_muss_ich_loeschen];
						huser="fax";
					} // if (hyinstart==hysrc || hyinstart==hyppk) else
					// 2) deren Existenz, Betrieb und ggf. Startbarkeit pruefen
					// wenn die richtigen Dienste laufen, dann nichts weiter ueberpruefen ..
					//// <<violett<<"pruefhyla 1"<<schwarz<<endl;
					if ((!sfaxq->obsvfeh(obverb>0?obverb-1:0,oblog) && !shfaxd->obsvfeh(obverb>0?obverb-1:0,oblog)) /*|| this->shylafaxd->obslaeuft(... */) {
						hLog(Tx[T_Hylafax_laeuft]);
						hylalaeuftnicht=0;
						hylafehlt=0;
					} else if (versuch>1) {
						fLog(rots+Tx[T_Fehler_in_pruefhyla]+schwarz,1,oblog);
						ret=0;
						break;
					} //     if ((this->sfaxq->obslaeuft(obverb-1,oblog) && this->shfaxd->obslaeuft(obverb-1,oblog))  else
					if (hylafehlt) {
						// falls nein, dann schauen, ob startbar
						if (sfaxq->machfit(obverb?obverb-1:0,oblog) && shfaxd->machfit(obverb?obverb-1:0,oblog) && sfaxgetty->machfit(obverb?obverb-1:0,oblog)) {
							hylafehlt=0;
							hylalaeuftnicht=0;
						}
						//// <<"hylafehlt: "<<(int)hylafehlt<<endl;
					} else {
						//// <<"hylafehlt nicht!"<<endl;
					} //     if (hylafehlt) else
					int nochmal;
					for(int aru=0;aru<2;aru++) {
						nochmal=0;
						//// <<violett <<"Versuch: "<<(int)versuch<<" hylafehlt: "<<(int)hylafehlt<<" hylalaeuftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
						if (hylafehlt) {
							// 3) ggf. neu installieren
							fLog(violetts+Tx[T_Muss_Hylafax_installieren]+schwarz,1,1);
							// a) von der source
							linstp->doinst("ghostscript",obverb+1,oblog,nochmal?nix:"gs");
              if (!obsotiff) {
							 linstp->doinst("tiff",obverb+1,oblog,"tiff2ps");
							 linstp->doinst("tiff",obverb+1,oblog,"fax2ps");
							} //               if (!obsotiff)
							prueftif(TIFFGetVersion());
							linstp->doinst("postfix",obverb+1,oblog,"postfix");
							if (obverb) fLog(violetts+"hyinstart: "+schwarz+ltoan(hyinstart),1,1);
							hyinstart=hysrc; // spaeter zu loeschen
							if (hyinstart==hysrc) {
								fLog(violetts+Tx[T_ueber_den_Quellcode]+schwarz,1,1);
								string was;
								for(int iru=0;iru<2;iru++) {
									if (!holvomnetz("hylafax","https://sourceforge.net/projects/","/files/latest")) {
										svec hrueck;
										if (systemrueck("cd \""+instvz+"\"&& tar xvf hylafax.tar.gz",obverb,oblog,&hrueck,/*obsudc=*/1)) {
											tuloeschen("hylafax.tar.gz",cuser,obverb,oblog);
											continue;
										} else {
											if (hrueck.size()) {
												was=hrueck[0].substr(0,hrueck[0].length()-1);
											} // 							if (hrueck.size())
											break;
										} //			if (!systemrueck("sh -c 'cd \""+instvz+"\"&&"+sudc+"tar xvf hylafax.tar.gz'",obverb,oblog,&hrueck))
									} // 		if (!holvomnetz("hylafax","https://sourceforge.net/projects/","/files/latest"))
								} // 								for(int iru=0;iru<2;iru++)
								if (!was.empty()) {
									useruucp(huser,obverb,oblog);
									// Fehlermeldung faxgetty nicht gefunden verbergen
									const string vorcfg{"sed -i.bak 's_\\(ls -lL \\$1$\\)_\\1 2>/dev/null_g' configure"};
									const string cfgbismake{nix+" --nointeractive && echo $? = Ergebnis nach configure && "
										"sed -i.bak \"s/uint16_t/unsigned short/g\" hfaxd/FileSystem.c++ && "
										"sed -i.bak \"s.PAGESIZE='North American Letter'.PAGESIZE='ISO A4'.g;"
										"s.PATH_GETTY='\\.*'.PATH_GETTY='"
										"$(grep LIBEXEC defs|cut -d= -f2|sed 's/^[[:space:]]*//;s/[[:space:]]*$//')/faxgetty'.g\" config.cache"
										"&& echo $? = "+Tx[T_Ergebnis_nach]+" sed"
										"&&"+sudc};
									if (!kompilfort(was,vorcfg,cfgbismake)) {
										const string nachcfg{
											"systemctl daemon-reload && systemctl stop hylafax 2>/dev/null"
											"&& test -f /etc/init.d/hylafax &&{  mkdir -p /etc/ausrangiert"
											"&& mv -f /etc/init.d/hylafax /etc/ausrangiert;}"
											"&& pkill hfaxd faxq >/dev/null 2>&1 && faxsetup -nointeractive >/dev/null 2>&1 "
											"&& echo $? = Ergebnis nach faxsetup -nointeractive"
											"&& pkill hfaxd faxq >/dev/null 2>&1"//wird von faxset -nointeractive gestartet + kollidiert mit dem service
											"&& systemctl daemon-reload &&echo $? = Ergebnis nach systemctl daemon-reload;:;"};
										systemrueck(nachcfg,obverb<1?obverb:1,oblog,/*rueck=*/0,/*obsudc=*/1);
										mdatei confc(instvz+vtz+was+vtz+"config.cache");
										if (confc.is_open()) {
											string zeile;
											while(getline(confc,zeile)) {
												if (zeile.find("DIR_LIBEXEC")!=string::npos) {
													string rechts{zeile.substr(zeile.find("=")+1)};
													anfzweg(&rechts);
													faxgtpfad=rechts+vtz+"faxgetty";
													faxqpfad=rechts+vtz+"faxq";
													hfaxdpfad=rechts+vtz+"hfaxd";
													break;
												} // 									if (zeile.find("DIR_LIBEXEC")!=string::npos)
											} // 								while(getline(confc,zeile))
											confc.close();
										} // 							if (confc.is_open())
									} // 						if (!kompilfort(was,"",cfgbismake))
								} // !was.empty()
								// 2>/dev/null wegen tar:Schreibfehler (=> Schreibversuch durch von head geschlossene pipe)
								////					systemrueck("sh -c 'cd $("+sudc+"tar --list -f hylafax+ 2>/dev/null | head -n 1) && "
								//// hservice_faxgetty();
								//// hservice_faxq_hfaxd();
							} else {
								fLog(violetts+Tx[T_ueber_das_Installationspaket]+schwarz,1,1);
								// b) mit dem Installationspaket
								if (!linstp->obfehlt(hff) || !linstp->obfehlt(hfcf)) {
									fLog(hfftext,-1,1);
									linstp->douninst(string(hff)+" "+hfcf,obverb,oblog);
									falscheshyla=1;
								}
								//// <<"hfr: "<<violett<<hfr<<schwarz<<" hfcr: "<<violett<<hfcr<<schwarz<<" obverb: "<<(int)obverb<<endl;
								hylafehlt=linstp->obfehlt(hfr,obverb,oblog) || linstp->obfehlt(hfcr,obverb,oblog) || 
									!obprogda("faxq",obverb,oblog) || !obprogda("hfaxd",obverb,oblog) || !obprogda("faxgetty",obverb,oblog);
								yLog(obverb,oblog,0,0,"%s%s%s%d%s%s%s%d",gruen,Tx[T_hylafehlt],schwarz,hylafehlt,gruen,Txk[T_Versuch],schwarz,versuch);
								// b1) falsches Hylafax loeschen
								if (hylafehlt) {
									if (falscheshyla) {
										fLog(rots+Tx[T_Muss_falsches_hylafax_loeschen]+schwarz,1,1);
										if (0) {
											systemrueck("cd /etc/init.d"
													" && [ $(find . -maxdepth 1 -name \"*faxq*\" -or -name \"*hfaxd*\" -or -name \"hylafax*\" 2>/dev/null | wc -l) -ne 0 ]"
													" && { mkdir -p /etc/ausrangiert && mv -f *faxq* *hfaxd* hylafax* /etc/ausrangiert;}||:",-2,oblog,/*rueck=*/0,/*obsudc=*/1);
											systemrueck("cd $(dirname $(dirname $(which systemctl)))/lib/systemd/system && "
													"rm -f faxq.service hfaxd.service faxgetty*.service hylafax*.service;",-2,oblog,/*rueck=*/0,/*obsudc=*/1);
											systemrueck("cd /etc/systemd/system && rm -f faxq.service hfaxd.service faxgetty*.service;",-2,oblog,/*rueck=*/0,/*obsudc=*/1);
											for(int iru=0;iru<2;iru++) {
												const string local{iru?"local/":nix};
												systemrueck("cd /usr/"+local+"bin 2>/dev/null && "
														"rm -f faxalter faxcover faxmail faxrm faxstat sendfax sendpage;",-2,oblog,/*rueck=*/0,/*obsudc=*/1);
												systemrueck("cd /usr/"+local+"sbin 2>/dev/null && "
														"rm -f choptest cqtest dialtest edit-faxcover faxabort faxaddmodem "
														"faxadduser faxanswer faxconfig faxcron faxdeluser faxinfo faxlock faxmodem faxmsg faxq faxqclean faxquit faxsetup "
														"faxsetup.linux faxstate faxwatch probemodem rchylafax* recvstats tagtest tiffcheck tsitest typetest xferfaxstats "
														"faxsetup.bsdi faxsetup.iri faxgetty faxsend hfaxd hylafax lockname ondelay pagesend textfmt;",
														-2,oblog,/*rueck=*/0,/*obsudc=*/1);
												systemrueck("rm -rf /usr/"+local+"/lib/fax",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
												systemrueck("rm -rf /usr/"+local+"/share/hylafax",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
												systemrueck("rm -rf /usr/"+local+"/lib/fax",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
												systemrueck("rm -rf /usr/"+local+"/lib/hylafax",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
												systemrueck("rm -rf /usr/"+local+"/lib/libfax*",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
												systemrueck("rm -rf /usr/"+local+"/lib/libhylafax*",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
											} //                 for(int iru=0;iru<2;iru++)
											systemrueck("rm -rf /etc/hylafax",-2,oblog,/*rueck=*/0,/*obsudc=*/1,1);
											// es bleiben noch /var/log/hylafax und /var/spool/fax oder /var/spool/hylafax
										} // if (0)
									} // if falscheshyla
									// b2) richtiges Hylafax installieren
									hylafehlt=linstp->doinst(string(hfr)+" "+string(hfcr),obverb,oblog);
								} // if (hylafehlt)
							} // if (hyinstart==hysrc)  else

							// wenn sich faxsend findet ...
							if (obprogda("faxsend",obverb,oblog)) {
								// und ein hylafax-Verzeichnis da ist ...
								if (this->setzhylavz()) {
									this->obfa[2]=obweg[2]=obher[2]=0;
									ret=0;
									break;
								} else {
									// falls oben hylafax neu installiert wurde und zuvor eine hylafax-Installation nach Gebrauch geloescht worden war,
									// dann die alten Eintraege (xferfaxlog.rpmsave) wieder aktivieren
									struct stat entryxfer{0}, entryxfer0{0};
									const string d0{xferfaxlog+".rpmsave"};
									if (!lstat(xferfaxlog.c_str(),&entryxfer)) {
										if (entryxfer.st_size<10) { // wenn neu
											if (!lstat(d0.c_str(),&entryxfer0) && entryxfer0.st_size>10) {
												kopier(d0,xferfaxlog,obverb,oblog);
												////                systemrueck(sudc+"cp -a "+d0+" "+xferfaxlog,obverb,oblog);
											} else {
												if (falscheshyla)  {
													char* fspoolvz=0;
													for(unsigned iru=0;iru<elemzahl(moeglhvz);iru++) {
														if (this->moeglhvz[iru]!=this->varsphylavz) {
															fspoolvz=(char*)this->moeglhvz[iru];
															break;
														} // if (this->moeglhvz[iru]
													} // for(unsigned iru=0
													if (fspoolvz) {
														/*
															 wenn /var/spool/hylafax/etc/xferfaxlog 1 Byte hat und /var/spool/fax/etc/xferfaxlog mehr dann kopieren:
															 etc/xferfaxlog sendq recvq log doneq docq archive
														 */
														/*// // muss noch getestet werden
															systemrueck(("cp ")+fspoolvz+"/etc/xferfaxlog "+this->varsphylavz+"/etc/",obverb,oblog);
															systemrueck(("cp ")+fspoolvz+"/sendq "+this->varsphylavz+"/",obverb,oblog);
															systemrueck(("cp ")+fspoolvz+"/recvq "+this->varsphylavz+"/",obverb,oblog);
															systemrueck(("cp ")+fspoolvz+"/log "+this->varsphylavz+"/",obverb,oblog);
															systemrueck(("cp ")+fspoolvz+"/doneq "+this->varsphylavz+"/",obverb,oblog);
															systemrueck(("cp ")+fspoolvz+"/docq "+this->varsphylavz+"/",obverb,oblog);
															systemrueck(("cp ")+fspoolvz+"/archive "+this->varsphylavz+"/",obverb,oblog);
														 */
													}
												} // if (falscheshyla)
											} // !lstat(d0.c_str()
										} // if (entryfer.st_size<10

									} // if (!lstat(xferfaxlog.c_str(),&entryxfer)) 
									// bei hysrc ist das Folgende wohl eigentlich nicht noetig
									// Berechtigungen korrigieren
									useruucp(huser,obverb,oblog);
									systemrueck("chown "+huser+":uucp -R "+this->varsphylavz,obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
								} // 							if (this->setzhylavz())
							} // if (obprogda("faxsend",obverb,oblog))
							/*//
								fLog(string(Tx[T_StarteHylafax]),1,oblog);
							//      if (hyinstart==hypak) hylalaeuftnicht=hservice_faxq_hfaxd();
							<<"hylafehlt: "<<(int)hylafehlt<<endl;
							if (0) {
							if (hylafehlt || versuch) {
							//        fLog(string(Tx[(T_)T_Installation_von_Hylafax_nicht_feststellbar_versuche_es_zu_installieren]),-2,1);

							//        string cmd("which zypper 2>/dev/null && zypper -n in hylafax hylafax-client || "
							//        "KLA which apt-get 2>/dev/null && apt-get -y install hylafax-server hylafax-client; KLZ; systemctl daemon-reload; ");
							//        hylafehlt=systemrueck(cmd,1+obverb,oblog,0,wahr,wahr,Tx[T_hylafax_faxmodem_nicht_gefunden_Versuche_es_zu_installieren_mit]); 

							}
							// falls ja, dann starten (falls erst installiert werden muss, dann bei versuch==1
							} // if (0)
							 */
						} // if (hylafehlt)
						int fglaeuftnicht{0};
						for (uchar iru=0;iru<3;iru++) {
							//// <<violett<<"pruefhyla 2"<<schwarz<<endl;
							if ((fglaeuftnicht=sfaxgetty->obsvfeh(obverb>0?obverb-1:0,oblog))) {
								// falls nein, dann schauen, ob startbar
								if (sfaxgetty->machfit(obverb,oblog)) fglaeuftnicht=0;
							}
							//// <<rot<<" fglaueftnicht: "<<fglaeuftnicht<<", hmodem: "<<hmodem<<schwarz<<endl;
							string pfad;
							if (obprogda("faxstat",obverb,oblog,&pfad)) {
								modemlaeuftnicht=1+fglaeuftnicht;
								svec rueck;
								systemrueck(pfad+" 2>&1",obverb,oblog,&rueck,/*obsudc=*/1);
								for(size_t ruei=0;ruei<rueck.size();ruei++) {
									if (!aru) {
										if (!ruei && rueck[0].find("no version information")!=string::npos) {
											nochmal=1;
											//// <<violett<<rueck[0]<<schwarz<<endl;
											reduzierlibtiff();
											hylafehlt=1;
											break;
										}
									} // 									if (!aru)
									//// <<"rueck["<<ruei<<"]: "<<rueck[ruei]<<endl;
									//// <<" hmodem: "<<hmodem<<endl;
									if (rueck[ruei].find(this->hmodem)!=string::npos) {
										modemlaeuftnicht--;
										break;
									}
////								modemlaeuftnicht=systemrueck(pfad+"|grep "+this->hmodem+" 2>&1",obverb,oblog,/*rueck=*/0,/*obsudc=*/1)+fglaeuftnicht;
								} // 								for(size_t ruei=0;ruei<rueck.size();ruei++)
								if (nochmal) break;
							} // 							if (obprogda("faxstat",obverb,oblog,&pfad))
							////        if (!modemlaeuftnicht) break;
							////  <<rot<<" hyinstart: "<<(int)hyinstart<<", modemlaeuftnicht: "<<(int)modemlaeuftnicht<<schwarz<<endl;
							////  <<rot<<" hylalaueftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
							if (hyinstart==hypak || hyinstart==hysrc || hyinstart==hyppk) {
								//// if (0)
								hylalaeuftnicht=hservice_faxq_hfaxd()+fglaeuftnicht;
							}
							if (hylalaeuftnicht) cout<<rot<<" hylalaueftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
							if (modemlaeuftnicht) cout<<rot<<" modemlaueftnicht: "<<(int)modemlaeuftnicht<<schwarz<<endl;
							if (!hylalaeuftnicht && !modemlaeuftnicht) break;
							if (iru>1) {
								systemrueck("chmod 660 "+this->varsphylavz+"/FIFO*",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
								if (hconfig()) continue;
								hconfigtty();
								frischkonfiguriert=1;
							}
							if (!iru) {
								caus<<rot<<"hier faxsetup!"<<endl;
								hfaxsetup();
								//// if (0)
								//// hservice_faxgetty();
							}
						} // for (uchar iru=0;iru<3;iru++)
						if (nochmal) continue;
						break;
					}
					if (!ret) break;
					// wenn !hylazukonf, dann auslesen, mit den Werten vergleichen und ggf. zu 1 setzen
					if (!hylazukonf) {
						hliesconf();
					}
					//// <<rot<<"fglaeuftincht: "<<(int)fglaeuftnicht<<", modemlaeuftnicht: "<<(int)modemlaeuftnicht<<", hylalaeuftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
					//// if (!hylalaeuftnicht && !modemlaeuftnicht) break;
					////          cmd=string("zypper -n in uucp"); // fuer cu
					////          systemrueck(cmd,1,1,0,wahr,wahr,"installiere cu"); 
					////          cmd=string("usermod -a -G dialout root");
					////          systemrueck(cmd,1,1,0,wahr,wahr,"berechtige mich"); 
					////          cmd=string("chmod 666 ")+this->hmodem;
					////          systemrueck(cmd,1,1,0,wahr,wahr,"berechtige mich"); 
					if (this->hylazukonf && !frischkonfiguriert) {
						////    hconfig(this,obverb,oblog); // countrycode, citycode/areacode, longdistancepraefix, internationalprefix
						if (!frischkonfiguriert) {
							// dieser Aufruf geschieht z.B. nach Parameter -hkzl 7
							hconfigtty();
						}
						if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog,1);
						if (shfaxd) shfaxd->stop(obverb,oblog,1);
						if (sfaxq) sfaxq->stop(obverb,oblog,1);
						if (shylafaxd) shylafaxd->stopdis(obverb>1?obverb:0,oblog,1);
						/*//
							if (!systemrueck(sudc+"systemctl stop '"+this->sfaxgetty->sname+"' '"+this->shfaxd->sname+"' '"+this->sfaxq->sname+"' 2>/dev/null",
							obverb,oblog)) KLA
							systemrueck(sudc+"systemctl stop hylafax 2>/dev/null",obverb-2,oblog);
							systemrueck(sudc+"systemctl disable hylafax 2>/dev/null",obverb-2,oblog);
							systemrueck(string(sudc+"pkill ")+sfaxgetty->ename+" "+shfaxd->ename+" "+sfaxq->ename+" >/dev/null 2>&1",obverb-2,oblog);
							KLZ 
						// if (!systemrueck(string(sudc+"systemctl stop ")+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog)) 
						 */
						if (sfaxgetty->startundenable(obverb,oblog) &&  shfaxd->startundenable(obverb,oblog) && sfaxq->startundenable(obverb,oblog)) {
							this->hylazukonf=0;
						} // if (!systemrueck(string(sudc+"systemctl start ")+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog)) 
					} // if (this->hylazukonf && !frischkonfiguriert) 
					//// systemrueck("grep -rl 'faxcron\\|faxqclean' /etc/cron* | /usr/bin/xargs ls -l;",obverb,oblog); 
					// // in hylafax: /etc/cron.daily/suse.de-faxcron, 
					////     break; // zu Testzwecken
					if (hylalaeuftnicht || modemlaeuftnicht) {
						// hier Fehler: nach einem Versuch darf 
						if (versuch) {
							/* if (this->konfobhyla) */ this->hylazukonf=1;
						}
						if (versuch>1) {
							fLog(Tx[T_hylafaxspringtnichtan],1,1);
							this->obfa[2]=obweg[2]=obher[2]=0;
							ret=0;
							break;
						} //         if (versuch>1) 
					} else {
						break;
					} // if (hylalaeuftnicht || modemlaeuftnicht) 
				} // for(unsigned versuch=0;versuch<2;versuch++)
				if (!ret) break;
				// Empfangsberechtigungen sicherstellen
				////		char *uvz[2]={(char*)"/log/",(char*)"/recvq/"};
				const string uvz[2]{"/log/","/recvq/"};
				for (unsigned i=0;i<2;i++) {
					const string dt{varsphylavz+uvz[i]+"seqf"};
					struct stat dstat{0};
					if (lstat(dt.c_str(),&dstat)) {
						useruucp(huser,obverb,oblog);
						systemrueck("touch "+dt+" && chown "+huser+":uucp "+dt,obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
					} // 		 if (lstat(dt.c_str(),&dstat))
				} // 		for (unsigned i=0;i<2;i++)
////				systemrueck("V="+varsphylavz+";L=\\$V/log;R=\\$V/recvq;chmod 774 \\$L \\$R;chmod 660 \\$L/seqf \\$R/seqf", obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
				systemrueck("V="+varsphylavz+";L=$V/log;R=$V/recvq;chmod 774 $L $R;chmod 660 $L/seqf $R/seqf", obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
				// Archivierung ggf. aktivieren
				if (!hylalaeuftnicht) {
					const string hour{"/etc/cron.hourly"}, fc{"faxqclean"};
					//// das Folgende fuehrt zu einer Bildschirmmeldung mit *, wenn Verzeichnis leer 
					////struct stat hfstat{0};
					////if (!lstat(hour.c_str(),&hfstat)) {
					////systemrueck(sudc+"sh -c \"for D in "+hour+"/*;do grep -q '"+fc+" *$' \\$D&&sed -i 's/"+fc+" *$/"+fc+" -a -A/g' \\$D||true;done\"",obverb,oblog);
					////} // 			if (!lstat(hour.c_str(),&hfstat))
					svec qrueck;
					if (findv==1) {
						systemrueck("find "+hour+" -type f -exec grep -l \""+fc+" *$\" {} \\; 2>/dev/null", obverb,oblog,&qrueck,/*obsudc=*/1);
					} else {
						findfile(&qrueck,findv,obverb,oblog,0,hour,/*muster=*/"",-1,33,7);
						regex_t regx;
						uchar noreg{0};
						if (regcomp(&regx, (fc+" *$").c_str(), REG_EXTENDED | REG_NOSUB)) noreg=1;
						for(size_t i=qrueck.size();i;) {
							i--;
							uchar gef{0};
							mdatei qr(qrueck[i],ios::in);
							if (qr.is_open()) {
								string zeile;
								while(getline(qr,zeile)) {
									if (noreg) {
										if (zeile.find(fc+"\\n")!=string::npos){gef=1;break;}
									} else {
										if (!regexec(&regx, zeile.c_str(), 0, 0, 0)) {gef=1;break;}
									}
								} // 								while(getline(qr,zeile))
								qr.close();
								if (!gef) qrueck.erase(qrueck.begin()+i);
							} // 							if (qr.is_open())
						} // 						for(size_t i=qrueck.size();i;)
					} // 					if (findv==1) else
					for(size_t i=0;i<qrueck.size();i++) {
						systemrueck("sed -i 's/"+fc+" *$/"+fc+" -a -A/g' "+qrueck[i]+"||:;",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
					}
					/*//
						if (!lstat("/etc/cron.hourly/hylafax",&hfstat)) KLA
						systemrueck("!"+sudc+"grep -q 'faxqclean *$' /etc/cron.hourly/hylafax || "sudc+"sed -i 's/faxqclean *$/faxqclean -a -A/g' /etc/cron.hourly/hylafax", obverb,oblog); // keine Sicherungskopie, sonst ausgefuehrt
						KLZ // 			if (!lstat("/etc/cron.hourly/hylafax",&hfstat))
					 */
				} //     if (!hylalaeuftnicht)
			} else {
				if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog);
				if (shfaxd) shfaxd->stopdis(obverb,oblog);
				if (sfaxq) sfaxq->stopdis(obverb,oblog);
				if (shylafaxd) shylafaxd->stopdis(obverb>1?obverb:0,oblog);
				ret=0;
			} // (obhyla) else
			hLog(violetts+Txk[T_Ende]+Tx[T_pruefhyla]+schwarz);
		} // 	if (hmodem.empty()) else
	} while (0); // fuer break
	//// obverb=altobverb;
	return ret;
} // int hhcl::pruefhyla


// augerufen in: virtpruefweiteres
void hhcl::dovh()
{
	hLog(violetts+"dovh()"+schwarz);
	// muss nach setzhylavz kommen
	pruefhyla();
	string zeig;
	cmd=edit;
	viadd(&cmd,&zeig,modconfdt);
	viadd(&cmd,&zeig,varsphylavz+"/etc/config");
	if (sfaxgetty) viadd(&cmd,&zeig,sfaxgetty->systemd);
	if (shfaxd) viadd(&cmd,&zeig,shfaxd->systemd);
	if (sfaxq) viadd(&cmd,&zeig,sfaxq->systemd);
	if (shylafaxd) viadd(&cmd,&zeig,shylafaxd->systemd);
	if (initdhyladt_gibts) viadd(&cmd,&zeig,initdhyladt);
	string erg;
	viadd(&erg,&zeig,xferfaxlog,1,0,1);
	vischluss(erg,zeig);
} // void hhcl::dovh

// aufgerufen in: main
void hhcl::rufpruefsamba()
{
	hLog(violetts+Tx[T_rufpruefsamba]);
	vector<const string*> vzn;
	svec abschni,suchs;
	const int ISambaName[]{T_Zufaxen,T_Warteauffax,T_Nichtgefaxt,T_Faxempfang}; 
	////={&zufaxenvz,&wvz,&nvz,&empfvz};
	if (!zufaxenvz.empty()) vzn.push_back(&zufaxenvz);
	if (!wvz.empty()) vzn.push_back(&wvz);
	if (!ngvz.empty()) vzn.push_back(&ngvz);
	if (!empfvz.empty()) vzn.push_back(&empfvz);
	for(auto zmakt: zmsp) {
		if (!zmakt->ziel.empty()) vzn.push_back(&zmakt->ziel);
	} //     for(zielmustercl *zmakt=zmp;1;zmakt++)
	for(unsigned k=0;k<vzn.size();k++) {
		string schstr;
		if (k<4) {
			abschni<<Tx[ISambaName[k]];
			Sprache altSpr{Tx.lgn};
			for(int aktsp=0;aktsp<SprachZahl;aktsp++) {
				Tx.lgn=(Sprache)aktsp;
				schstr=string("\\[")+Tx[ISambaName[k]]+"\\]\\|";
			} //         for(int aktsp=0;aktsp<SprachZahl;aktsp++)
			Tx.lgn=altSpr;
		} else {
			abschni<<string(Tx[T_Gefaxt])+"_"+ltoan(k-4);
			if (k==4) {
				Sprache altSpr{Tx.lgn};
				for(int aktsp=0;aktsp<SprachZahl;aktsp++) {
					Tx.lgn=(Sprache)aktsp;
					schstr=string("\\[")+Tx[T_Gefaxt]+"_\\|";
				} //         for(int aktsp=0;aktsp<SprachZahl;aktsp++)
				Tx.lgn=altSpr;
			} // 						if (k==4)
		} // 					if (k<4) else
		suchs<<schstr;
	} // 	for(unsigned k=0;k<vzn.size();k++)
	pruefsamba(vzn,abschni,suchs,DPROG,cuser);
	hLog(violetts+Txk[T_Ende]+Tx[T_rufpruefsamba]);
} // pruefsamba


// aufgerufen in: virtpruefweiteres
void hhcl::verzeichnisse()
{
	hLog(violetts+Tx[T_verzeichnisse]+schwarz);
	pruefcvz(); 
	//// caus<<"zufaxenvz: "<<zufaxenvz<<", cuser: "<<cuser<<endl;
	pruefverz(zufaxenvz,obverb,oblog,/*obmitfacl=*/2,/*obmitcon=*/1,/*besitzer=*/cuser); // dahin soll man schreiben koennen
//	pruefverz(zufaxenvz+"/2200",obverb,oblog,/*obmitfacl=*/2,/*obmitcon=*/1,/*besitzer=*/cuser); // dahin soll man schreiben koennen
	pruefverz(wvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/cuser);
	pruefverz(ngvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/cuser);
	pruefverz(empfvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/cuser);
	for(auto zmakt: zmsp) {
		pruefverz(zmakt->ziel,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/cuser);
	}
	for(uint imu=0;imu<this->zmzn;imu++) {
		const string imus{ltoan(imu)};
		fLog(Tx[T_Muster]+imus+": '"+blau+this->zmsp[imu]->muster+schwarz+"'",this->obverb>1,this->oblog);
		fLog(Tx[T_Ziel]+imus+":   '"+blau+this->zmsp[imu]->ziel+schwarz+"'",this->obverb>1,this->oblog);
	} //   for(uint imu=0;imu<this->zmzn;imu++)
} // hhcl:: verzeichnisse

// aufgerufen in: main
const string& pruefspool(DB *My,const string& spooltab, const string& altspool, const int obverb, const int oblog, uchar direkt/*=0*/)
{
	fLog(violetts+Tx[T_pruefspool]+schwarz+", direkt: "+(direkt?"1":"0"),obverb,oblog);
	const size_t aktc{0};
	if (!direkt) {
		Feld felder[] {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1),
			Feld("original","varchar","1","",Tx[T_Originalname_der_Datei],/*obind=*/1,/*obauto=*/0,/*nnull=*/1),
			Feld("origvu","varchar","1","",Tx[T_Originalname_der_Datei_vor_Umwandlung_in_PDF],0,0,1),
			Feld("idudoc","int","10","",Tx[T_Index_auf_urspruenglichen_Dateinamen],0,0,1),
			Feld("telnr","varchar","1","",Tx[T_zu_senden_an],0,0,1),
			Feld("wiemail","int","1","",Tx[T_wie_mailen],0,0,1,/*vdefa=*/"0"), // 1 = verschluesselte Mail, 2 = klare Mail
			Feld("adressat","varchar","1","",Tx[T_Adressat],0,0,1),
			Feld("pprio","int","2","",Tx[T_Prioritaet_aus_Dateinamen],0,0,1),
			Feld("fbdials","int","10","",Tx[T_Zahl_der_bisherigen_Versuche_in_fbfax],0,0,1),
			Feld("fboxstat","int","2","",Tx[T_capistat],0,0,1),
			Feld("fbspooldt","varchar","1","",Tx[T_Pfad_zur_Spooldatei_in_fbfax],0,0,1),
			Feld("capidials","int","10","",Tx[T_Zahl_der_bisherigen_Versuche_in_Capisuite],0,0,1),
			Feld("capistat","int","2","",Tx[T_capistat],0,0,1),
			Feld("hyladials","int","10","",Tx[T_Zahl_der_bisherigen_Versuche_in_Hylafax],0,0,1),
			Feld("capispooldt","varchar","1","",Tx[T_Spooldatei_in_Capisuite],0,0,1),
			Feld("capispoolpfad","varchar","1","",Tx[T_Pfad_zur_Spooldatei_in_Capisuite_ohne_abschliessendes_Verzeichnistrennzeichen],0,0,1),
			Feld("cdateidatum","datetime","0","0",Tx[T_Aenderungszeit_der_CapiSpoolDatei],0,0,1),
			Feld("cdateizeit","double","0","0",Tx[T_Aenderungszeit_der_CapiSpooldatei_im_time_Format],0,0,1),
			Feld("hylanr","int","10","","jobid in hylafax",0,0,1),
			Feld("hdateidatum","datetime","0","0",Tx[T_Aenderungszeit_der_Hylaspooldatei],0,0,1),
			Feld("hdateizeit","double","0","0",Tx[T_Aenderungszeit_der_Hylaspooldatei_im_Time_Format],0,0,1),
			Feld("althylanr","int","10","",Tx[T_jobid_in_letztem_gescheitertem_hylafax],0,0,1),
			Feld("hylastate","int","2","",Tx[T_state_Feld_in_hylafax],0,0,1),
			Feld("hylastatuscode","int","10","",Tx[T_statuscode_in_letztem_gescheitertem_hylafax],0,0,1),
			Feld("hylastatus","varchar","80","",Tx[T_status_in_letztem_gescheitertem_hylafax],0,0,1),
			Feld("allewege","int","1","",Tx[T_fax_auf_allen_Wegen_schicken_uml],0,0,1,/*vdefa=*/"0"),
			Feld("mailgesandt","int","2","",Tx[T_mail_gesandt_0_nein_1_ja],0,0,1,/*vdefa=*/"0"),
			Feld("pages","int","10","",Tx[T_Seitenzahl],0,0,1),
		}; //     Feld felder[] = 
		Feld ifelder0[]{Feld("capispooldt")}; Index i0("capispooldt",ifelder0,elemzahl(ifelder0));
		Feld ifelder1[]{Feld("cdateidatum")};    Index i1("cdateidatum",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[]{Feld("hdateidatum")};    Index i2("hdateidatum",ifelder2,elemzahl(ifelder2));
		////    Feld ifelder3[] = {Feld("original")};       Index i3("original",ifelder3,elemzahl(ifelder3));
		Index indices[]{i0,i1,i2/*,i3*/};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taa(My,altspool,felder,elemzahl(felder),indices,elemzahl(indices),0,0,Tx[T_capispooldateien_der_Capisuite]
				/*//, "InnoDB","utf8","utf8_unicode_ci","DYNAMIC"*/);
		if (taa.prueftab(aktc,obverb)) {
			exit(schluss(11,rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+altspool,1));
		} // 		if (taa->prueftab(&taa, aktc,obverb))
		Tabelle tab(My,spooltab,felder,elemzahl(felder),indices,elemzahl(indices),0,0,Tx[T_capispooldateien_der_Capisuite]
				/*// , "InnoDB","utf8","utf8_unicode_ci","DYNAMIC"*/);
		if (tab.prueftab(aktc,obverb)) {
			exit(schluss(11,rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+spooltab,1));
		} // 		if (tab->prueftab(&tab, aktc,obverb))
	} // if (!direkt) 
	return spooltab;
} // const char* pruefspool

// aufgerufen in: main
void pruefouttab(DB *My, const string& touta, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	fLog(violetts+Tx[T_pruefouta]+schwarz,obverb,oblog);
	const size_t aktc{0};
	if (!direkt) {
		Feld felder[] {
			Feld("eind","int","10","",Tx[T_eindeutige_Identifikation],1,1),
			Feld("Erfolg","int","1","",Tx[T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen],0,0,1),
			Feld("rcname","varchar","1","",Tx[T_Name_des_Adressaten_aus_Faxnummer_ermittelt],0,0,1),
			Feld("submt","datetime","0","0",Tx[T_Datum_des_Losschickens],0,0,1),
			Feld("transe","datetime","0","0",Tx[T_Ende_der_Uebertragung],0,0,1),
			Feld("submid","varchar","1","",Tx[T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname],0,0,1),
			Feld("docname","varchar","1","",Tx[T_Dateiname],0,0,1),
			Feld("idudoc","int","10","",Tx[T_Index_auf_urspruenglichen_Dateinamen],0,0,1),
			Feld("fsize","int","10","",Tx[T_Dateigroesse],0,0,1,"",1),
			Feld("pages","int","10","",Tx[T_Seitenzahl],0,0,1),
			Feld("retries","int","10","",Tx[T_Zahl_der_Anwahlen],0,0,1),
			Feld("rcfax","varchar","1","",Tx[T_Faxnummer_des_Adressaten],0,0,1),
			Feld("adressat","varchar","1","",Tx[T_Name_des_Adressaten_aus_Dateiname],0,0,1),
			Feld("titel","varchar","1","",Tx[T_Titel_des_Adressaten],0,0,1),
			Feld("pid","int","10","",Tx[T_PID_falls_aus_Dateinamen_ermittelt],0,0,1),
			Feld("tsid","varchar","1","",Tx[T_Kurzbezeichnung_der_eigenen_Faxstelle],0,0,1),
			Feld("devname","varchar","1","",Tx[T_Geraetename],0,0,1),
			//			Feld("oscht","datetime","0","0",Tx[T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax],0,0,1),
			//			Feld("subject","varchar","1","",Tx[T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax],0,0,1),
			//			Feld("id","varchar","1","",Tx[T_identisch_zu_submid_nur_MSFax],0,0,1),
			//			Feld("prio","int","1","",Tx[T_Prioritaet_nur_MSFax],0,0,1),
			//			Feld("csid","varchar","1","",Tx[T_Faxnummer_des_Adressaten_nur_MSFax],0,0,1),
			//			Feld("sender","varchar","1","",Tx[T_Faxnummer_des_Senders_nur_MSFax],0,0,1),
			//			Feld("transs","datetime","0","0",Tx[T_Beginn_der_Uebertragung_nur_MSFax],0,0,1),
		};
		Feld ifelder0[] = {Feld("submt"),Feld("Erfolg")};   Index i0("submt",ifelder0,elemzahl(ifelder0));
		Feld ifelder1[] = {Feld("Erfolg"),Feld("submt")};   Index i1("Erfolg",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[] = {Feld("docname"),Feld("Erfolg")}; Index i2("docname",ifelder2,elemzahl(ifelder2));
		Feld ifelder3[] = {Feld("pid"),Feld("Erfolg")};     Index i3("pid",ifelder3,elemzahl(ifelder3));
		Feld ifelder4[] = {Feld("rcfax"),Feld("Erfolg")};   Index i4("rcfax",ifelder4,elemzahl(ifelder4));
		Feld ifelder5[] = {Feld("submid")}; Index i5("submid",ifelder5,elemzahl(ifelder5));
		Index indices[]={i0,i1,i2,i3,i4,i5};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,touta,felder,elemzahl(felder),indices,elemzahl(indices),0,0,
				Tx[T_Archiv_fuer_die_erfolgreichen_Faxe]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			exit(schluss(11,rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+touta,1));
		}
	} // if (!direkt)
} // int pruefouttab

// aufgerufen in: main
void pruefudoc(DB *My, const string& tudoc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	fLog(violetts+Tx[T_pruefudoc]+schwarz,obverb,oblog);
	const size_t aktc{0};
	if (!direkt) {
		Feld felder[] {
			Feld("id","int","10","",Tx[T_eindeutige_Identifikation],1,1),
			Feld("udocname","varchar","1","",Tx[T_Dateiname],0,0,1),
		};
		Feld ifelder0[] = {Feld("udocname")};   Index i0("udocname",ifelder0,elemzahl(ifelder0));
		Index indices[]={i0};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tudoc,felder,elemzahl(felder),indices,elemzahl(indices),0,0,
				Tx[T_Archiv_fuer_die_Dateinamen_vor_Aufteilung]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			exit(schluss(11,rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tudoc,1));
		}
	} // if (!direkt)
} // int pruefudoc

// aufgerufen in: virtpruefweiteres
void pruefinctab(DB *My, const string& tinca, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	fLog(violetts+Tx[T_pruefinca]+schwarz,obverb,oblog);
	const size_t aktc{0};
	if (!direkt){
		Feld felder[] {
			Feld("eind","int","10","",Tx[T_eindeutige_Identifikation],1,1),
			Feld("Erfolg","int","1","",Tx[T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen],0,0,1),
			////      Feld("rcname","varchar","1","",Tx[T_Name_des_Adressaten],0,0,1),
			////      Feld("submt","datetime","0","0",Tx[T_Datum_des_Losschickens],0,0,1),
			Feld("transe","datetime","0","0",Tx[T_Ende_der_Uebertragung],0,0,1),
			////      Feld("submid","varchar","1","",Tx[T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname],0,0,1),
			////      Feld("docname","varchar","1","",Tx[T_Dateiname],0,0,1),
			Feld("fsize","int","10","",Tx[T_Dateigroesse],0,0,1),
			Feld("pages","int","10","",Tx[T_Seitenzahl],0,0,1),
			Feld("retries","int","10","",Tx[T_Zahl_der_Anwahlen],0,0,1),
			////      Feld("rcfax","varchar","1","",Tx[T_Faxnummer_des_Adressaten],0,0,1),
			Feld("titel","varchar","1","",Tx[T_Titel_des_Adressaten],0,0,1),
			////      Feld("pid","int","10","",Tx[T_PID_falls_aus_Dateinamen_ermittelt],0,0,1),
			Feld("tsid","varchar","1","",Tx[T_Kurzbezeichnung_der_eigenen_Faxstelle],0,0,1),
			Feld("devname","varchar","1","",Tx[T_Geraetename],0,0,1),
			//			Feld("callerid","varchar","1","",Tx[T_Bezeichnung_des_Anrufers],0,0,1),
			////      Feld("oscht","datetime","0","0",Tx[T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax],0,0,1),
			////      Feld("subject","varchar","1","",Tx[T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax],0,0,1),
			Feld("id","varchar","1","",Tx[T_identisch_zu_submid_in_outa],0,0,1),
			////      Feld("prio","int","10","",Tx[T_Prioritaet_nur_MSFax],0,0,1),
			Feld("csid","varchar","1","",Tx[T_Faxnummer_des_Adressaten],0,0,1),
			////      Feld("sender","varchar","1","",Tx[T_Faxnummer_des_Senders_nur_MSFax],0,0,1),
			//			Feld("transs","datetime","0","0",Tx[T_Beginn_der_Uebertragung_nur_MSFax],0,0,1),
		};
		Feld ifelder0[]{Feld("transe"),Feld("Erfolg")};   Index i0("transe",ifelder0,elemzahl(ifelder0));
		Feld ifelder1[]{Feld("Erfolg"),Feld("transe")};   Index i1("Erfolg",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[]{Feld("titel"),Feld("Erfolg")}; Index i2("titel",ifelder2,elemzahl(ifelder2));
		Feld ifelder3[]{Feld("tsid"),Feld("Erfolg")}; Index i3("tsid",ifelder3,elemzahl(ifelder3));
		Feld ifelder4[]{Feld("id"),Feld("Erfolg")}; Index i4("id",ifelder4,elemzahl(ifelder4));
		Index indices[]{i0,i1,i2,i3,i4};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,tinca,felder,elemzahl(felder),indices,elemzahl(indices),0,0,
				Tx[T_Archiv_fuer_die_erfolgreichen_Faxe]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			exit(schluss(11,rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+tinca,1));
		}
	} // 	if (!direkt)
} // void pruefinctab


//α
// aufgerufen in lauf
void hhcl::virtpruefweiteres()
{
	hLog(violetts+Tx[T_virtpruefweiteres]+schwarz); //ω
	setzhylavz();
	if (obvh) dovh();
	verzeichnisse();
	if (!kez&& !bvz && !anhl && !tulista && !tulistf && !tulisti && !tulistw && suchstr.empty())
		rufpruefsamba();
	if (logdateineu) tuloeschen(logdt,string(),obverb,oblog);
	hLog(Tx[T_zufaxenvz]+drots+zufaxenvz+schwarz+"'");
	hLog(Txk[T_Logpfad]+drots+loggespfad+schwarz+Txk[T_oblog]+drot+ltoan((int)oblog)+schwarz+")");
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab])); //α //ω
	if (initDB()) {
		exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));
	}
	// pruefe Tabelle <spooltab> und erstelle sie ggf.
	pruefspool(My,spooltab, altspool, obverb,oblog);
	pruefouttab(My,touta, obverb,oblog);
	pruefudoc(My,tudoc, obverb,oblog);
	pruefinctab(My,tinca, obverb,oblog);

	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ 
	hLog(violetts+Tx[T_virtzeigueberschrift]+schwarz); //ω
	char buf[20]; 
	snprintf(buf,sizeof buf,"%.5f",versnr);
	uebers<<Tx[T_Verwende]
			+blaus+(obfa[0]?"Fritzbox":(obweg[0]==1?"Fritzbox senden"+(obher[0]==1?string(", empfangen"):string()):(obher[0]==1?"Fritzbox empfangen":"")))+schwarz
			+((obfa[0]||obweg[0]==1||obher[0]==1)&&(obfa[2]||obweg[2]==1||obher[2]==1||obfa[1]||obweg[1]==1||obher[1]==1)?", ":"")
			+blau+(obfa[1]?"Capisuite":(obweg[1]==1?"Capisuite senden"+(obher[1]==1?string(", empfangen"):string()):(obher[1]==1?"Capisuite empfangen":"")))+schwarz
			+((obfa[1]||obweg[1]==1||obher[1]==1)&&(obfa[2]||obweg[2]==1||obher[2]==1)?", ":"")
			+blau+(obfa[2]?"Hylafax":(obweg[2]==1?"Hylafax senden"+(obher[2]==1?string(", empfangen"):string()):(obher[2]==1?"Hylafax empfangen":"")))+schwarz
			+(!obfa[0]&&obweg[0]!=1&&obher[0]!=1&&!obfa[1]&&obweg[1]!=1&&obher[1]!=1&&!obfa[2]&&obweg[2]!=1&&obher[2]!=1?(blaus+Tx[T_kein_Faxprogramm_verfuegbar]+schwarz):"")
			+(scapis||(shfaxd&&sfaxq&&sfaxgetty)?"; ":"")
			+(scapis?dblaus+"Capisuite "+(scapis->laeuft()?(scapis->lief()?Tx[T_aktiv]:Tx[T_aktiviert]):Tx[T_inaktiv])+schwarz:"")
			+(scapis&&(shfaxd&&sfaxq&&sfaxgetty)?", ":"")
			+(shfaxd&&sfaxq&&sfaxgetty?dblaus+"Hylafax "
				+(shfaxd->laeuft()&&sfaxq->laeuft()&&sfaxgetty->laeuft()?
					(shfaxd->lief()&&sfaxq->lief()&&sfaxgetty->lief()?Tx[T_aktiv]:Tx[T_aktiviert]):Tx[T_inaktiv])+schwarz:"");
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift
//ω
// aufgerufen in: getsender, archiviere, empfhyla, empfcapi
string hhcl::stdfaxnr(const string& faxnr)
{
	hLog(violetts+"stdfaxnr()"+schwarz);
	const string land{this->InternationalPrefix+this->countrycode},
				vorwahl{this->LongDistancePrefix+this->citycode};
	string trimfaxnr;
	size_t p1,p2{string::npos};
	p1=faxnr.find('.');
	if (p1!=string::npos) p2=faxnr.find('.',p1+1);
	// Fuer Faxnr wie '49.8131.12345'
	if (p2!=string::npos) trimfaxnr=this->InternationalPrefix; else if (p1!=string::npos) trimfaxnr=this->LongDistancePrefix;

	for (string::const_iterator it=faxnr.begin(); it!=faxnr.end(); ++it) {
		// nur dieses Zeichen beruecksichtigen
		if (strchr("+0123456789",*it)) { 
			// wenn nicht die Faxnummer mit '+' oder '00' oder '0' anfaengt ..
			if (trimfaxnr.empty() && *it!='+' && faxnr.find(this->InternationalPrefix,distance(faxnr.begin(),it))
					&& faxnr.find(this->LongDistancePrefix,distance(faxnr.begin(),it))) {

				// .. dann die Vorwahl voranstellen
				trimfaxnr=vorwahl;
			}
			// '+' in '00' umwandeln
			if (*it=='+')
				trimfaxnr+=this->InternationalPrefix;
			// ansonsten alles abschreiben
			else
				trimfaxnr+=*it;
		} //       if (strchr("+0123456789",*it))
	} //     for (string::const_iterator it=faxnr.begin(); it!=faxnr.end(); ++it)
	// wenn am Schluss das eigene Land am Anfang steht, dann streichen
	if (!trimfaxnr.find(land)) trimfaxnr=this->LongDistancePrefix+trimfaxnr.substr(land.length());
	return trimfaxnr;
} // string hhcl::stdfaxnr

// aufgerufen in: archiviere, korrigierecapi, empfhyla, empfcapi
void hhcl::getSender(const string& faxnr, string *getnamep, string *bsnamep,const size_t aktc) 
{
	hLog(violetts+"getSender("+"..,"+faxnr+")"+schwarz);
	if (!faxnr.empty()) {
		this->My->usedb(this->My->dbname,aktc);
		const string trimfaxnr{this->stdfaxnr(faxnr)};
		// vor den angegebenen SQL-Befehlen nachschauen, wie die gesandten Faxe benannt wurden
		const string **const locsqlp{new const string*[this->sqlzn+1]};
		const string sql0{"SELECT * from (SELECT adressat, titel, submt, LENGTH(titel)-LENGTH(REPLACE(titel,',','')) kzahl "
			"FROM `"+this->touta+"` WHERE rcfax"
			////stdfaxnr(rcfax,"+this->InternationalPrefix+","+this->LongDistancePrefix+","+this->countrycode+","+this->citycode+")"
			"='&&faxnr&&') i WHERE kzahl<>0 AND titel<>'' AND titel RLIKE '^[^0123456789]' ORDER BY kzahl,submt DESC"};
		locsqlp[0]=&sql0;
		for(size_t snr=0;snr<this->sqlzn;snr++) {
			locsqlp[snr+1]=&sqlp[snr]; // &(this->sqlcnfA)[snr].wert;
		}
		for(size_t snr=0;snr<this->sqlzn;snr++) {
			hLog(rots+"snr: "+schwarz+ltoan(snr));
			hLog(rots+"sql: "+schwarz+*locsqlp[snr]);
			RS rhae(this->My,ersetzAllezu(*locsqlp[snr],"&&faxnr&&",trimfaxnr.c_str()),aktc,ZDB); // (const char*)trimfaxnr));
			if (!rhae.obqueryfehler) {
				hLog(string("obqueryfehler: ")+ltoan((int)rhae.obqueryfehler));
				char ***cerg;
				while (cerg=rhae.HolZeile(),cerg?*cerg:0) {
					hLog(string("cerg: ")+ltoan((bool)*cerg));
					if (*(*cerg+0)) {
						hLog("P0: "+blaus+*(*cerg+0)+schwarz);
						if (getnamep->empty()) if (*(*cerg+0)) *getnamep = *(*cerg+0);
					}
					if (*(*cerg+1)) {
						hLog("P1: "+blaus+*(*cerg+1)+schwarz);
						if (bsnamep->empty()) if (*(*cerg+1)) *bsnamep = *(*cerg+1);
					}
					break;
				} // while (cerg=rhae.HolZeile(),cerg?*cerg:0) 
			} // if (!rhae.obqueryfehler) 
			if (!obverb) if (getnamep->empty()) break;
			////    if (!obverb) if (*getnamep!="" && bsname !="") break;
		} // for(size_t snr=0;snr<this->sqlzn;snr++) 
		if (getnamep->empty()) {
			*getnamep=trimfaxnr;
		}
	} // if (!faxnr->empty()) 
	ersetzAlle(*bsnamep,"/",";");
	ersetzAlle(*bsnamep,":",";");
} // void getSender

// liest eine Protokolldatei von fbfax aus
// aufgerufen in: korrigierefbox, setzfboxstat
void liesvw(const string& vwdt,time_t* fbzpp,string* minabstp, string* telnrp, string* originalp,string* fbdialsp, string* fbmaxdialsp, FxStat* fboxstatp,time_t* fbnzpp/* naechster Zeitpunkt*/)
{
	struct stat vwstat{0};
	if (!lstat(vwdt.c_str(),&vwstat)) {
		mdatei f(vwdt.c_str(),ios::in|ios::binary); 
		if (f.is_open()) {
			string zeile;
			if (getline(f,zeile)) if (fbzpp) *fbzpp=atol(zeile.c_str());  // fb-Zeitpunkt
			if (getline(f,zeile)) {
				if (minabstp) *minabstp=zeile; // restliche Minutenabstaende
				if (!zeile.empty()) {
					const size_t posk{zeile.find(',')};
					long nmin;
					if (posk!=string::npos) {
					  nmin=atol(zeile.substr(0,posk).c_str()); // z.B. "720,1440"
					} else {
            nmin=atol(zeile.c_str());  // z.B. "1440"
					}
					if (fbnzpp) if (fbzpp) *fbnzpp=*fbzpp+60*nmin;
				}
			}
			if (getline(f,zeile)) if (telnrp) *telnrp=zeile; // telnr
			if (getline(f,zeile)) if (originalp) {size_t pos{zeile.rfind('/')+1};*originalp=(pos?zeile.substr(pos):zeile);} // Dateiname
			if (getline(f,zeile)) if (fbdialsp) if (size_t pos{zeile.find('/')}) {*fbdialsp=zeile.substr(0,pos); if (fbmaxdialsp) *fbmaxdialsp=zeile.substr(pos+1);}
			f.close();
			if (fboxstatp) if (*fboxstatp!=gesandt && *fboxstatp!=gescheitert) *fboxstatp=wartend;
			// fehlt: verarb
		} else {
			*fboxstatp=fehlend;
		}  //       if (!lstat(sendqgespfad.c_str(),entrysendp)) else
	} else {
		*fboxstatp=fehlend;
	}
} // void liesvw

// aufgerufen 2 x in pvirtfuehraus
void hhcl::korrigierefbox(const unsigned tage/*=90*/,const size_t aktc)
{
	////	obverb=2; ZDB=1;
	hLog(violetts+Tx[T_korrigierefbox]+schwarz);
	// mit dem thread abzweigen, falls Programm mit Abzweigungen ausgeführt
	set<string>::iterator fit; // Iterator dafuer
	svec rueck[2];
	size_t ruecki;
	string inse;
	string teln,zp,tries;
	size_t size;
	for(int cru=0;cru<2;cru++) {
		if (findv==1) {
			cmd="find '"+(cru?fbgvz:fbnvz)+"' -maxdepth 1 "+(tage?string("-mtime -")+ltoan(tage):"")+" -iname 'dt*.tif'";////-printf '%f\\n'";
			systemrueck(cmd,obverb,oblog,&rueck[cru],/*obsudc=*/1);
		} else {
			time_t ab=0;
			if (tage) ab=time(0)-(tage*24*60*60);
			findfile(&rueck[cru],findv,obverb,oblog,0,(cru?fbgvz:fbnvz),/*muster=*/"dt.*\\.tif$",1,1,0,ab,0,1);
		} // 						if (findv==1)
	} // 					for(int cru=0;cru<2;cru++)
	if (rueck[0].size()||rueck[1].size()) {
		RS vgl1(My,"DROP TABLE IF EXISTS tmpfbox",aktc,ZDB);
		RS vgl2(My,"CREATE TABLE tmpfbox(submid VARCHAR(40) KEY, titel VARCHAR(600), rcname VARCHAR(900),"
				"teln VARCHAR(40),zp DATETIME, tries INT, size INT(15), docname VARCHAR(900), erfolg INT) collate utf8_general_ci",aktc,ZDB);
		for(int cru=0;cru<2;cru++) {
			for(ruecki=0;ruecki<rueck[cru].size();ruecki++) {
				teln.clear();zp.clear();tries.clear();size=0;
				struct stat tifstat{0};
				if (!lstat(rueck[cru][ruecki].c_str(),&tifstat)) {
					size=tifstat.st_size;
					//// pthread_mutex_lock(&timemutex);
					//// struct tm *tmp=localtime(&tifstat.st_mtime);
					//// char buf[100];
					//// strftime(buf, sizeof(buf), "%F %T", tmp);
					//// pthread_mutex_unlock(&timemutex);
					stringstream zpstr;
					zpstr<<ztacl(tifstat.st_mtime,"%F %T");
					//// zp=buf;
					zp=zpstr.str();
				}
				string stamm,exten;
				getstammext(&rueck[cru][ruecki],&stamm,&exten);
				const string eind{stamm.substr(stamm.rfind('/')+1)};
				const string vwdt{stamm+".vw"};
				string docname;
				liesvw(vwdt,0,0,&teln,&docname,&tries);
				if (tries.empty()) tries="0";
				string getname,bsname;
				getSender(teln,&getname,&bsname,aktc);
				//// <<"ursp: "<<ursp<<endl;
				inse+="('"+eind+"','"+bsname+"','"+getname+"','"+teln+"','"+zp+"',"+tries+","+ltoan(size)+",'"+docname+"',"+(cru?"1":"0")+"),";
				if (!(ruecki % 100)||ruecki==rueck[cru].size()-1) {
					inse[inse.size()-1]=';';
					////		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_ON);
					RS vgl3(My,"INSERT INTO tmpfbox VALUES "+inse,aktc,ZDB);
					inse.clear();
				} // 							if (ruecki==100||rueck==rueck[cru].size()-1)
			} //           for(ruecki=0;ruecki<rueck[cru].size();ruecki++)
		} // 					for(uchar cru=0;cru<2;cru++)
		//						auswe[auswe.size()-1]=')';
		// die laut tmpfbox uebermittelten Faxe, die in outa als Mißerfolg eintragen sind
		char ***cerg;
		RS kor1(My,"SELECT t.submid p0, t.teln p1, t.zp p2, a.submt p3, t.tries p4, t.erfolg p5, t.size p6, a.docname p7 "
				"FROM `"+touta+"` a RIGHT JOIN tmpfbox t ON t.submid=a.submid WHERE a.erfolg<>t.erfolg",aktc,ZDB);
		if (!kor1.obqueryfehler) {
			size_t zru=0;
			while (cerg=kor1.HolZeile(),cerg?*cerg:0) {
				if (!zru++) {
					cout<<violett<<Tx[T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
					cout<<schwarz<<setw(19)<<"submid"<<"|"<<setw(15)<<Tx[T_Faxnr]<<"|"<<setw(19)<<Tx[T_zp]<<"|"
						<<setw(19)<<"submt"<<"|"<<setw(5)<<Tx[T_tries]<<"|"<<setw(6)<<Txk[T_Erfolg]<<"|"<<setw(10)<<Tx[T_size]<<"|"<<Tx[T_docname]<<schwarz<<endl;
				} // 								if (!zru++)
				cout<<setw(3)<<zru<<") "<<blau<<setw(14)<<cjj(cerg,0)<<"|"<<violett<<setw(15)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(19)<<cjj(cerg,2)<<"|"
					<<schwarz<<setw(17)<<cjj(cerg,3)<<"|"<<blau<<setw(5)<<cjj(cerg,4)<<"|"<<violett<<setw(6)<<cjj(cerg,5)<<"|"
					<<blau<<setw(10)<<cjj(cerg,6)<<"|"<<violett<<string(cjj(cerg,7)).substr(0,55)<<endl;
			} // while (cerg=kor1.HolZeile(),cerg?*cerg:0) 
			RS kor2(My,"UPDATE `"+touta+"` a RIGHT JOIN tmpfbox t ON t.submid=a.submid SET a.erfolg=t.erfolg where a.erfolg<>t.erfolg",aktc,ZDB);
		} // 						if (!kor1.obqueryfehler) 
		RS kor3(My,"SELECT t.submid p0,t.teln p1,t.zp p2,t.tries p3,t.erfolg p4,t.size p5,"
				"IF(ISNULL(asp.original),'',asp.original) p6,"
				"IF(ISNULL(asp.idudoc),0,asp.idudoc) p7,IF(ISNULL(asp.pages),0,asp.pages) p8,"
				"IF(ISNULL(asp.adressat) OR asp.adressat=t.teln,'',asp.adressat) p9 "
				"FROM tmpfbox t "
				"LEFT JOIN `"+touta+"` a ON a.submid=t.submid "
				"LEFT JOIN `"+altspool+"` asp ON asp.fbspooldt=t.submid "
				"LEFT JOIN `"+touta+"` av ON av.erfolg<>0 AND av.idudoc=asp.idudoc AND av.idudoc<>0 "
				"WHERE ISNULL(a.submid) AND (t.erfolg<>0 OR ISNULL(av.idudoc)) "
				"GROUP BY t.submid",aktc,ZDB);
		if (!kor3.obqueryfehler) {
			size_t zru=0;
			while (cerg=kor3.HolZeile(),cerg?*cerg:0) {
				if (!zru++) {
					cout<<violett<<Tx[T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
					cout<<schwarz<<setw(20)<<"submid"<<"|"<<setw(25)<<Tx[T_telnr]<<"|"<<setw(19)<<Tx[T_zp]<<"|"
						<<setw(5)<<Tx[T_tries]<<"|"<<setw(6)<<Txk[T_Erfolg]<<"|"<<setw(10)<<Tx[T_size]<<schwarz<<"|"<<blau<<Tx[T_docname]<<schwarz<<endl;
				} // 							if (!zru++)
				cout<<setw(4)<<zru<<") "<<blau<<setw(14)<<cjj(cerg,0)<<"|"<<violett<<setw(25)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(19)<<cjj(cerg,2)<<"|"
					<<violett<<setw(5)<<cjj(cerg,3)<<"|"<<blau<<setw(6)<<cjj(cerg,4)<<"|"<<violett<<setw(10)<<cjj(cerg,5)<<"|"
					<<blau<<string(cjj(cerg,6)).substr(0,55)<<schwarz<<endl;
			} // while (cerg=kor3.HolZeile(),cerg?*cerg:0) 
			RS kor4(My,"INSERT INTO `"+touta+"` (erfolg,submt,transe,submid,titel,rcname,fsize,retries,rcfax,docname,idudoc,pages,adressat) "
					"SELECT t.erfolg,t.zp,t.zp,t.submid,t.titel,t.rcname,t.size,t.tries,t.teln,IF(ISNULL(asp.original),t.docname,asp.original),"
					"IF(ISNULL(asp.idudoc),0,asp.idudoc),IF(ISNULL(asp.pages),0,asp.pages),"
					"IF(ISNULL(asp.adressat) OR asp.adressat=t.teln,'',asp.adressat) "
					"FROM tmpfbox t "
					"LEFT JOIN `"+touta+"` a ON a.submid=t.submid "
					"LEFT JOIN `"+altspool+"` asp ON asp.fbspooldt=t.submid "
					"LEFT JOIN `"+touta+"` av ON av.erfolg<>0 AND av.idudoc=asp.idudoc AND av.idudoc<>0 "
					"WHERE ISNULL(a.submid) AND (t.erfolg<>0 OR ISNULL(av.idudoc)) "
					"GROUP BY t.submid",aktc,ZDB);
		} // 						if (!kor3.obqueryfehler)

		// die laut tmpcapi uebermittelten Faxe, die nicht in outa als uebermittelt eingetragen sind, 
		// und zu denen nicht bereits eine erfolgreiche hylafax-Uebertragung eingetragen ist
		/*//
			RS ntr(My,"SELECT t.submid p0,t.teln p1,a.original p2,unix_timestamp(t.zp) p3,a.hdateidatum p4, a.idudoc p5,t.pages p6 FROM tmpcapi t "
			"LEFT JOIN outa o ON t.submid = o.submid LEFT JOIN altspool a ON t.submid=a.hylanr "
			"LEFT JOIN outa o2 ON o2.submid=a.fbspooldt AND o2.erfolg<>0 WHERE o.erfolg=0 AND t.erfolg<>0 AND ISNULL(o2.submid)",ZDB);
		 */
	} // 							if (rueck[0].size()||rueck[1].size()) 
	hLog(violetts+Txk[T_Ende]+Tx[T_korrigierefbox]+schwarz);
	////		obverb=0; ZDB=0;
} // void hhcl::korrigierefbox

// Parameter -kez
// aufgerufen in: main, zeigweitere
void hhcl::korrigierecapi(const unsigned tage/*=90*/,const size_t aktc)
{
	hLog(violetts+Tx[T_korrigierecapi]+schwarz);
		// geht wegen Loeschens der Protokolldateien nur (noch) fuer Gefundene, s.u.
		set<string>::iterator fit; // Iterator dafuer
		svec rueck[2];
		size_t ruecki;
		string inse;
		string teln,zp,tries,user;
		size_t size;
		/*//
		////			set<string> fdn; // Fax-Dateien
		if (0) {
		cmd=sudc+"find '"+cdonevz+"' -maxdepth 1 -type f -iname '*-fax-*.sff'"; //  -printf '%f\\n'"; // cfailedvz weniger wichtig
		systemrueck(cmd,obverb,oblog,&rueck);
		// sortieren
		for(ruecki=0;ruecki<rueck.size();ruecki++) {
		fdn.insert(rueck[ruecki]);
		} 
		} // if (0)
		 */
		for(int cru=0;cru<2;cru++) {
			if (findv==1) {
				cmd="find '"+(cru?cdonevz:cfailedvz)+"' -maxdepth 1 "+(tage?string("-mtime -")+ltoan(tage):"")+" -iname '*-fax-*.sff'";////-printf '%f\\n'";
				systemrueck(cmd,obverb,oblog,&rueck[cru],/*obsudc=*/1);
			} else {
				time_t ab=0;
				if (tage) ab=time(0)-(tage*24*60*60);
				findfile(&rueck[cru],findv,obverb,oblog,0,(cru?cdonevz:cfailedvz),/*muster=*/"-fax-.*\\.sff$",1,1,0,ab,0,1);
			} // 						if (findv==1)
		} // 					for(int cru=0;cru<2;cru++)
		if (rueck[0].size()||rueck[1].size()) {
			RS vgl1(My,"DROP TABLE IF EXISTS tmpcapi",aktc,ZDB);
			RS vgl2(My,"CREATE TABLE tmpcapi(submid VARCHAR(40) KEY, titel VARCHAR(600), rcname VARCHAR(900),"
					"teln VARCHAR(40),zp DATETIME, tries INT, size INT(15), erfolg INT)",aktc,ZDB);
			for(int cru=0;cru<2;cru++) {
				for(ruecki=0;ruecki<rueck[cru].size();ruecki++) {
					teln.clear();zp.clear();tries.clear();user.clear();size=0;
					struct stat sffstat{0};
					if (!lstat(rueck[cru][ruecki].c_str(),&sffstat)) {
						size=sffstat.st_size;
						//// pthread_mutex_lock(&timemutex);
						//// struct tm *tmp=localtime(&sffstat.st_mtime);
						//// char buf[100];
						//// strftime(buf, sizeof(buf), "%F %T", tmp);
						//// pthread_mutex_unlock(&timemutex);
						stringstream zpstr;
						zpstr<<ztacl(sffstat.st_mtime,"%F %T");
						//// zp=buf;
						zp=zpstr.str();
					}
					string stamm,exten;
					getstammext(&rueck[cru][ruecki],&stamm,&exten);
					const string txtdt{stamm+".txt"};
					struct stat txtstat{0};
					if (!lstat(txtdt.c_str(),&txtstat)) {
//						const string feld[]{/*"dialstring","starttime",*/"tries","user"/*,"addressee","subject"*/};
            tries.clear();
						user.clear();
						schAcl<WPcl> sffC("sffC", new vector<aScl>{
								{"tries",&tries},
								{"user",&user},
								{"dialstring",&teln},
								});
						confdcl sff(txtdt,obverb);
						sff.kauswert(&sffC);
					} // 						if (!lstat(txtdt.c_str(),&txtstat))
					string ursp{base_name(rueck[cru][ruecki])};
					vector<string> tok; 
					aufSplit(&tok,ursp,'-');
					ursp.clear(); for(size_t j=1;j<tok.size();j++){ursp+=tok[j];if (j<tok.size()-1) ursp+="-";}
					string getname,bsname;
					getSender(teln,&getname,&bsname,aktc);
					//// <<"ursp: "<<ursp<<endl;
					inse+="('"+ursp+"','"+bsname+"','"+getname+"','"+teln+"','"+zp+"',"+tries+","+ltoan(size)+","+(cru?"1":"0")+"),";
					if (!(ruecki % 100)||ruecki==rueck[cru].size()-1) {
						inse[inse.size()-1]=';';
						////		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_ON);
						RS vgl3(My,"INSERT INTO tmpcapi VALUES "+inse,aktc,ZDB);
						inse.clear();
					} // 							if (ruecki==100||rueck==rueck[cru].size()-1)
				} //           for(ruecki=0;ruecki<rueck[cru].size();ruecki++)
			} // 					for(uchar cru=0;cru<2;cru++)
			//						auswe[auswe.size()-1]=')';
			// die laut tmpcapi uebermittelten Faxe, die in outa als Mißerfolg eintragen sind
			char ***cerg;
			RS kor1(My,"SELECT t.submid p0, t.teln p1, t.zp p2, a.submt p3, t.tries p4, t.erfolg p5, t.size p6, a.docname p7 "
					"FROM `"+touta+"` a RIGHT JOIN tmpcapi t ON t.submid=a.submid WHERE a.erfolg<>t.erfolg",aktc,ZDB);
			if (!kor1.obqueryfehler) {
				size_t zru=0;
				while (cerg=kor1.HolZeile(),cerg?*cerg:0) {
					if (!zru++) {
						cout<<violett<<Tx[T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
						cout<<schwarz<<setw(19)<<"submid"<<"|"<<setw(15)<<Tx[T_Faxnr]<<"|"<<setw(19)<<Tx[T_zp]<<"|"
							<<setw(19)<<"submt"<<"|"<<setw(5)<<Tx[T_tries]<<"|"<<setw(6)<<Txk[T_Erfolg]<<"|"<<setw(10)<<Tx[T_size]<<"|"<<Tx[T_docname]<<schwarz<<endl;
					} // 								if (!zru++)
					cout<<setw(3)<<zru<<") "<<blau<<setw(14)<<cjj(cerg,0)<<"|"<<violett<<setw(15)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(19)<<cjj(cerg,2)<<"|"
						<<schwarz<<setw(17)<<cjj(cerg,3)<<"|"<<blau<<setw(5)<<cjj(cerg,4)<<"|"<<violett<<setw(6)<<cjj(cerg,5)<<"|"
						<<blau<<setw(10)<<cjj(cerg,6)<<"|"<<violett<<string(cjj(cerg,7)).substr(0,55)<<endl;
				} // while (cerg=kor1.HolZeile(),cerg?*cerg:0) 
				RS kor2(My,"UPDATE `"+touta+"` a RIGHT JOIN tmpcapi t ON t.submid=a.submid SET a.erfolg=t.erfolg where a.erfolg<>t.erfolg",aktc,ZDB);
			} // 						if (!kor1.obqueryfehler) 
			RS kor3(My,"SELECT t.submid p0,t.teln p1,t.zp p2,t.tries p3,t.erfolg p4,t.size p5,"
					"IF(ISNULL(asp.original),'',asp.original) p6,"
					"IF(ISNULL(asp.idudoc),0,asp.idudoc) p7,IF(ISNULL(asp.pages),0,asp.pages) p8,"
					"IF(ISNULL(asp.adressat) OR asp.adressat=t.teln,'',asp.adressat) p9 "
					"FROM tmpcapi t "
					"LEFT JOIN `"+touta+"` a ON a.submid=t.submid "
					"LEFT JOIN `"+altspool+"` asp ON asp.capispooldt=t.submid "
					"LEFT JOIN `"+touta+"` av ON av.erfolg<>0 AND av.idudoc=asp.idudoc AND av.idudoc<>0 "
					"WHERE ISNULL(a.submid) AND (t.erfolg<>0 OR ISNULL(av.idudoc)) "
					"GROUP BY t.submid",aktc,ZDB);
			if (!kor3.obqueryfehler) {
				size_t zru=0;
				while (cerg=kor3.HolZeile(),cerg?*cerg:0) {
					if (!zru++) {
						cout<<violett<<Tx[T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
						cout<<schwarz<<setw(20)<<"submid"<<"|"<<setw(25)<<Tx[T_telnr]<<"|"<<setw(19)<<Tx[T_zp]<<"|"
							<<setw(5)<<Tx[T_tries]<<"|"<<setw(6)<<Txk[T_Erfolg]<<"|"<<setw(10)<<Tx[T_size]<<schwarz<<"|"<<blau<<Tx[T_docname]<<schwarz<<endl;
					} // 							if (!zru++)
					cout<<setw(4)<<zru<<") "<<blau<<setw(14)<<cjj(cerg,0)<<"|"<<violett<<setw(25)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(19)<<cjj(cerg,2)<<"|"
						<<violett<<setw(5)<<cjj(cerg,3)<<"|"<<blau<<setw(6)<<cjj(cerg,4)<<"|"<<violett<<setw(10)<<cjj(cerg,5)<<"|"
						<<blau<<string(cjj(cerg,6)).substr(0,55)<<schwarz<<endl;
				} // while (cerg=kor3.HolZeile(),cerg?*cerg:0) 
				RS kor4(My,"INSERT INTO `"+touta+"` (erfolg,submt,transe,submid,titel,rcname,fsize,retries,rcfax,docname,idudoc,pages,adressat) "
						"SELECT t.erfolg,t.zp,t.zp,t.submid,t.titel,t.rcname,t.size,t.tries,t.teln,IF(ISNULL(asp.original),'',asp.original),"
						"IF(ISNULL(asp.idudoc),0,asp.idudoc),IF(ISNULL(asp.pages),0,asp.pages),"
						"IF(ISNULL(asp.adressat) OR asp.adressat=t.teln,'',asp.adressat) "
						"FROM tmpcapi t "
						"LEFT JOIN `"+touta+"` a ON a.submid=t.submid "
						"LEFT JOIN `"+altspool+"` asp ON asp.capispooldt=t.submid "
						"LEFT JOIN `"+touta+"` av ON av.erfolg<>0 AND av.idudoc=asp.idudoc AND av.idudoc<>0 "
						"WHERE ISNULL(a.submid) AND (t.erfolg<>0 OR ISNULL(av.idudoc)) "
						"GROUP BY t.submid",aktc,ZDB);
			} // 						if (!kor3.obqueryfehler)

			// die laut tmpcapi uebermittelten Faxe, die nicht in outa als uebermittelt eingetragen sind, 
			// und zu denen nicht bereits eine erfolgreiche hylafax-Uebertragung eingetragen ist
			/*//
				RS ntr(My,"SELECT t.submid p0,t.teln p1,a.original p2,unix_timestamp(t.zp) p3,a.hdateidatum p4, a.idudoc p5,t.pages p6 FROM tmpcapi t "
				"LEFT JOIN outa o ON t.submid = o.submid LEFT JOIN altspool a ON t.submid=a.hylanr "
				"LEFT JOIN outa o2 ON o2.submid=a.capispooldt AND o2.erfolg<>0 WHERE o.erfolg=0 AND t.erfolg<>0 AND ISNULL(o2.submid)",ZDB);
			 */
		} // 							if (rueck[0].size()||rueck[1].size()) 
		hLog(violetts+Txk[T_Ende]+Tx[T_korrigierecapi]+schwarz);
} // korrigierecapi

// aufgerufen in inspoolschreiben und untersuchespool; Vorsicht, wenn qdateip ein Verzeichnisname ist!
template<typename T> string verschiebe(const string& qdatei, const T/*string,zielmustercl*/& zielvz, const string& cuser/*=nix*/, 
		uint *vfehlerp/*=0*/, const uchar wieweiterzaehl/*=1*/, int obverb/*=0*/,int oblog/*=0*/, stringstream *ausgp/*=0*/,const uchar auchgleiche/*=0*/)
{
	// wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
	uchar obgleich{0};
	uint fehler{0};
	const string ziel{zielname(qdatei,zielvz,wieweiterzaehl,/*zieldatei=*/0,(auchgleiche?0:&obgleich),obverb>0?obverb-1:0,oblog,ausgp)};
	// wenn wieweiterzaehl==2 und Zieldatei schon vorhanden und nicht 0 Bytes, dann nicht ueberschreiben und Fehler melden
	while (!ziel.empty()) { // while nur fuer break
		if (!obgleich && wieweiterzaehl==2) {
			struct stat st{0};
			if (!lstat(ziel.c_str(),&st)&&st.st_size) {
				fehler=1;
				break;
			} // 			if (!lstat(ziel.c_str(),&st)&&st.st_msize)
		} // 		if (!obgleich && wieweiterzaehl==2)
		dorename(qdatei,ziel,cuser,&fehler,/*schonda=*/obgleich,obverb,oblog,ausgp);
		break;
	} // 	while (!ziel.empty()) 
	if (vfehlerp) *vfehlerp=fehler;
	return ziel;
} // string verschiebe

// aufgerufen in zupdf, rueckfragen
int hhcl::pruefsoffice(const string soffname/*soffice*/,uchar mitloe/*=0*/)
{
	hLog(violetts+Tx[T_pruefsoffice]+schwarz);
	static uchar sofficegeprueft{0};
	static int sofficeda{0};
	if (mitloe || !sofficegeprueft) {
		////              systemrueck("which zypper 2>/dev/null && zypper -n in soffice || "
		////                          "{ which apt-get 2>/dev/null && apt-get -y install soffice; }",obverb,oblog);
		if (mitloe) linstp->douninst("libreoffice-base",obverb,oblog);
		sofficeda=!linstp->doinst("libreoffice-base",obverb,oblog,soffname);
		sofficegeprueft=1;
	} //   if (!sofficegeprueft)
	return sofficeda;
} // int hhcl::pruefsoffice

// aufgerufen in zupfd, rueckfragen
int hhcl::pruefconvert()
{
	hLog(violetts+Tx[T_pruefconvert]+schwarz);
	static uchar convertgeprueft{0};
	static int convertda{0};
	if (!convertgeprueft) {
		////              systemrueck("which zypper 2>/dev/null && zypper -n in convert || "
		////                          "{ which apt-get 2>/dev/null && apt-get -y install convert; }",obverb,oblog);
		convertda=!linstp->doinst("imagemagick",obverb,oblog,"convert");
		convertgeprueft=1;
	} //   if (!convertgeprueft)
	return convertda;
} // int hhcl::pruefconvert

// aufgerufen in: empfarch, zupdf
int hhcl::holtif(const string& datei,ulong *seitenp,struct tm *tmp,struct stat *elogp, 
		string *absdrp,string *tsidp,string *calleridp,string *devnamep)
{
	hLog(violetts+Tx[T_holtif]+schwarz);
	int erg{1};
	vector<string> tok; // fuer imagedescription
	if (tmp) {
		////			memset(tmp, 0, sizeof(*tmp)); // schon bei Initialisierung
		if (elogp) {
			////				memset(elogp,0,sizeof *elogp); // schon bei Initialisierung
			if (!lstat(datei.c_str(),elogp))  {
				////					if (chmod(datei.c_str(),S_IRWXU|S_IRWXG|S_IRWXO)) systemrueck(sudc+"chmod +r \""+datei+"\"",obverb,oblog);
				pthread_mutex_lock(&timemutex);
				memcpy(tmp, localtime(&elogp->st_mtime),sizeof(*tmp));
				pthread_mutex_unlock(&timemutex);
				//// char buf[100];
				//// strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", tmp);
				//// <<"Buf: "<<buf<<endl;
			} //     if (!lstat(datei.c_str(),elogp)) 
		} // if (elogp)
	} // if (tmp)
	setfaclggf(dir_name(datei),obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/7);
	setfaclggf(datei,obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/4,/*obimmer=*/0,/*faclbak=*/0);
	if (TIFF* tif = TIFFOpen(datei.c_str(), "r")) {
		erg=0;
		char *rdesc{0};
		if (tmp) {
			if (TIFFGetField(tif, TIFFTAG_DATETIME, &rdesc)) {
				//// <<"Datetime: \n"<<rdesc<<endl;
				strptime(rdesc,"%Y:%m:%d %T",tmp);
				//// char buf[100];
				//// strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", tmp);
				//// <<"Buf (2): "<<buf<<endl;
			} // if (TIFFGetField(tif, TIFFTAG_DATETIME, &rdesc))
		} // if (tmp)
		if (seitenp) *seitenp=TIFFNumberOfDirectories(tif);
		rdesc=0;
		if (TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &rdesc)) {
			////          printf("Beschreibung: %s\n",beschreib);
			////  out<<"Beschreibung: \n"<<rdesc<<endl;
			tok.clear();
			aufSplit(&tok,rdesc,'\n');
			if (tok.size()) {
				if (tok.size()>1) {
					//// <<gruen<<"tok[0]: "<<schwarz<<tok[0]<<endl;
					if (calleridp) *calleridp=tok[0];
					//// <<gruen<<"tok[1]: "<<schwarz<<tok[1]<<endl;
					*tsidp=tok[1];
					if (tok.size()>2) if (absdrp) *absdrp=tok[2];
				} else {
					if (istelnr(tok[0])) {
						//// <<gruen<<"tok[0] b: "<<schwarz<<tok[0]<<endl;
						if (calleridp) *calleridp=tok[0]; 
					} else { 
						//// <<gruen<<"tok[0] c: "<<schwarz<<tok[0]<<endl;
						if (absdrp) *absdrp=tok[0];
					} // 					if (istelnr(tok[0]))
				} //           if (tok.size()>1)  else
			} // if (tok.size()) 
		} // if (TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &rdesc)) 
		//// rdesc=0;
		//// if (TIFFGetField(tif, TIFFTAG_MODEL, &rdesc))
		rdesc=0;
		uchar obdev{0};
		if (calleridp) {if (calleridp->empty()) obdev=1;} else obdev=1;
		if (obdev) if (!devnamep) obdev=0;
		if (obdev) {
			if (TIFFGetField(tif, TIFFTAG_MAKE, &rdesc)) {
				////          printf("Beschreibung: %s\n",beschreib);
				//// <<gruen<<"rdesc: "<<schwarz<<rdesc<<endl;
				if (rdesc) {
					*devnamep+=", ";
					*devnamep+=rdesc;
				} // 				if (rdesc)
			} // if (TIFFGetField(tif, TIFFTAG_MAKE, &rdesc)) 
		} // if (calleridp->empty()) 
		TIFFClose(tif);
	} // if (TIFF* tif = TIFFOpen(datei.c_str(), "r")) 
	hLog(violetts+Txk[T_Ende]+Tx[T_holtif]+schwarz);
	return erg;
} // int hhcl::holtif

unsigned hhcl::pdfseitenzahl(const string& datei)
{
#ifdef false
	svec rueck;
	// pdf: pdfinfo (ubuntu und fedora: poppler-utils, opensuse: poppler-tools)
	linstp->doinst("poppler-tools",obverb,oblog,"pdfinfo");
	// falls libtiff geaendert, die zugehoerige Warnung ausblenden
	systemrueck("pdfinfo \""+datei+"\" 2>/dev/null|grep -a Pages|sed 's/[^ ]*[ ]*\\(.*\\)/\\1/'",obverb,oblog,&rueck);
	if (rueck.size()) {
		hLog("PDF: "+blaus+datei+schwarz+Tx[T_Seiten]+gruen+rueck[0]+schwarz);
		return atol(rueck[0].c_str());
	} // 			if (rueck.size())
	return 0;
#else
	QPDF pdf;
	pdf.processFile(datei.c_str());
	QPDFObjectHandle root = pdf.getRoot();
	QPDFObjectHandle pages = root.getKey("/Pages");
	QPDFObjectHandle count = pages.getKey("/Count");
////	<<rot<<count.getIntValue()<<endl;
	return count.getIntValue();
#endif
}

// in inspoolschreiben und empfhyla, empfcapi und empffbox
int hhcl::zupdf(const string* quellp, const string& ziel, ulong *pseitenp/*=0*/, const int obocr/*=1*/, const int loeschen/*=1*/) // 0=Erfolg
{
	hLog(violetts+Tx[T_zupdf]+schwarz+" '"+blau+*quellp+schwarz+"' '"+blau+ziel+schwarz+"', obocr: "+(obocr?"1":"0")+", loeschen: "+(loeschen?"1":"0"));
	int erg{1};
	string stamm,exten; // , *quellp=&quell;
	getstammext(quellp,&stamm,&exten);
	const int keinbild{(exten=="doc"||exten=="xls"||exten=="txt"||exten=="odf"||exten=="ppt"||exten=="docx"||exten=="htm"||exten=="html")};
	const string* lqp{quellp}; // laufender quell-pointer
	struct stat st{0};
	if (!lstat(ziel.c_str(),&st)) {
		uint vfehler=0;
		verschiebe<string>(ziel,dir_name(ziel),cuser,&vfehler,/*wieweiterzaehlt=*/1,obverb,oblog,/*ausgp=*/0,/*auchgleiche=*/1);
	} // 	if (!lstat(ziel.c_str(),&st))
	for(int aru=0;aru<2;aru++) {
		if (/*aru||*/!keinbild) {
			if (obocr) {
				if (!pruefocr()) {
					svec rueck;
					setfaclggf(ziel,obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/7,/*obimmer=*/0,/*faclbak=*/0);
					const string cmd{ocrmp+" -rcsl "+(langu=="d"?"deu":"eng")+" \""+*lqp+"\" \""+ziel+"\" 2>&1"};
					int zerg{systemrueck(cmd,obverb,oblog,&rueck,/*obsudc=*/0,0,wahr,"",0,1)};
					if (zerg==5) zerg=systemrueck(cmd,obverb,oblog,&rueck,/*obsudc=*/1,0,wahr,"",0,1); // kein Schreibrecht im Verzeichnis
					if (zerg) {
						cout<<"Fehler "<<blau<<zerg<<schwarz<<" bei: "<<blau<<cmd<<schwarz<<endl;
						for (size_t zei=0;zei<rueck.size();zei++) cout<<rot<<rueck[zei]<<schwarz<<endl;
					} else { // if (zerg)
						erg=0; // nicht umgekehrt
						for(unsigned uru=0;uru<rueck.size();uru++) {
							if (rueck[uru].find("ERROR")!=string::npos) {
								erg=1;
								break;
							} // 						 if (rueck[uru].find("ERROR")!=string::npos)
						} // 						for(unsigned uru=0;uru<rueck.size();uru++)
//					} else { // Datei kann auch trotz Fehler erstellt werden, deshalb Kommentar
//						erg=zerg;
					} // 					if (!systemrueck(string("ocrmypdf -rcsl ")+...
					if (!erg) {
						struct stat lziel{0};
						erg=lstat(ziel.c_str(),&lziel);
					} // 					if (!erg)
					if (!erg) {
						////						if (chmod(ziel.c_str(),S_IRWXU|S_IRWXG|S_IRWXO)) systemrueck(sudc+"chmod +r \""+ziel+"\"",obverb,oblog);
						break;
					} // 					if (!erg)
				} // pruefocr()
			} // if (obocr)
		} // 		if (!keinbild)
		if (aru) break; // 1,5 Runden maximal benoetigt
		if (erg) {
			string cmd1, cmd2;
			if (strcasecmp(exten.c_str(),"pdf")) { // wenn noch keine pdf-Datei
				for(unsigned runde=1;runde<=2;runde++) {
					cmd2.clear();
					string pname;
					switch ((runde+keinbild)%2) {
						case 0: 
							// 5.12.16 opensuse: bearbeitet jetzt nur (noch?) die erste Seite!
							pname="soffice";
							if (pruefsoffice(pname)) {
								cmd1="cd "+gethome()+"; ";
								cmd2=pname+" --headless --convert-to pdf --outdir \""+dir_name(ziel)+"\" \""+*quellp+"\" 2>&1";
							} // 						if (pruefsoffice
							break; // Ergebnis immer 0
						case 1: 
							pname="convert";
							if (pruefconvert()) {
								cmd1.clear();
								cmd2=sudc+pname+" \""+*quellp+"\" \""+ziel+"\""; 
							} // 						if (pruefconvert
							break;
					} // switch (runde) 
					if (!cmd2.empty()) {
						vector<string> umwd;
						if ((erg=systemrueck(cmd1+cmd2, obverb,oblog,&umwd))) {
							for(unsigned uru=0;uru<umwd.size();uru++) {
								if (umwd[uru].find("failed to read path from javaldx")!=string::npos) {
									erg=systemrueck(cmd1+sudc+cmd2, obverb,oblog);
									/*// int altobverb=obverb; obverb=1; pruefsoffice(1); obverb=altobverb; */
								} // 					  if (umwd[uru].find("javaldx failed")!=string::npos)
							} // 					 for(unsigned uru=0;uru<umwd.size();uru++)
						} // 					if ((erg=systemrueck(cmd2, obverb,oblog,&umwd)))
						struct stat entryziel{0};
						erg=lstat(ziel.c_str(),&entryziel); 
						fLog(Tx[T_Umwandlungvon]+blaus+*quellp+Tx[T_inPDFmit]+tuerkis+pname+schwarz+
								Tx[T_beendetErgebnis]+(erg?rots+Tx[T_misserfolg]:blaus+Tx[T_Erfolg_af])+schwarz, 1||erg,(erg?1:oblog));
						if (!erg) break;
					} // if (cmd2.empty()) erg=1; else 
				} // for(unsigned runde=1;runde<=2;runde++) 
			} else { // schon pdf-Datei
				erg=kopier(*quellp,ziel);
			} // 	if (strcasecmp else
			if (erg) {
				if (keinbild) break; // ocrmypdf kann nur Bilder umwandeln
			} else {
				if (!obocr||keinbild) break;  // ocrmypdf hier nicht erwuenscht oder sinnvoll
				lqp=&ziel; // ocrmypdf mit der Ergebnisdatei
			} // (erg) else
			//  string *oquel=(erg?&quell:&ziel);
		} // (erg)
	} // 	for(int aru=0;aru<2;aru++)
	if (!erg) {
		attrangleich(ziel,*quellp,0,obverb,oblog);
		// falls !erg und Seitenzahl gleich, dann tif loeschen
		if (pseitenp) {
			*pseitenp=pdfseitenzahl(ziel);
		} // 		if (pseitenp)
		if (loeschen && exten=="tif") {
			ulong seiten{0};
			holtif(*quellp, &seiten,0,0,0,0,0,0);
			hLog("TIF: "+blaus+*quellp+schwarz+Tx[T_Seiten]+gruen+ltoan(seiten)+schwarz);
////			if (rueck.size()) {
				if (pseitenp) {
					if (*pseitenp==seiten && seiten>0) {
						tuloeschen(*quellp,cuser,obverb,oblog);
					} else if (*pseitenp<seiten || !*pseitenp) {
						tuloeschen(ziel,cuser,obverb,oblog);
					} // 		 if (*pseitenp==seiten && seiten>0) else
				} // 		 if (pseitenp)
////			} // if (rueck.size())
			// pdfinfo /DATA/shome/gerald/t.pdf |grep Pages|sed 's/[^ ]*[ ]*\(.*\)/\1/'
		} // 		if (loeschen && exten=="tif")
	} // 	if (!erg)
	return erg; 
} // int hhcl::zupdf

// ocrmypdf laueft z.T. nicht aus einem Programm, das aus cron aufgerufen wird, wenn sich nicht im selben Verzeichnis unpaper findet
void hhcl::unpaperfuercron(const string& ocrprog)
{
	hLog(violetts+"unpaperfuercron()"+schwarz);
	const string unp{"unpaper"};
	const string uppfad{dir_name(ocrprog)+"/"+unp};
	struct stat lst{0};
	if (lstat(uppfad.c_str(),&lst)) {
		string prog;
		if (obprogda(unp,obverb,oblog,&prog)) {
			systemrueck(sudc+"ln -s '"+prog+"' '"+uppfad+"'",obverb,oblog);
		} // 	 if (obprogda(unp,obverb,oblog,&prog))
	} // 	if (lstat(uppfad.c_str(),&lst))
} // void hhcl::unpaperfuercron()

// aufgerufen in pruefocr()
void hhcl::pruefunpaper()
{
	hLog(violetts+Tx[T_pruefunpaper]+schwarz);
	double vers{progvers("unpaper")};
	if (vers<6.1) {
		linstp->doinst("libxslt-tools",obverb,oblog,"xsltproc");
		if (linstp->ipr==dnf||linstp->ipr==yum) {
			////sudc+"rpm -Uvh http://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-stable.noarch.rpm 
			////             http://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-stable.noarch.rpm
			////systemrueck("rpm -Uvh https://github.com/libelle17/rpmfusion_copy/blob/master/rpmfusion-free-release-stable.noarch.rpm "
			////" https://github.com/libelle17/rpmfusion_copy/blob/master/rpmfusion-nonfree-release-stable.noarch.rpm",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
			const string rpf{"rpmfusion_copy"};
			holvomnetz(rpf);
			kompilbase(rpf,s_gz);
			if (!pruefinstv()) {
				systemrueck("cd \""+instvz+vtz+rpf+"\"&&"+sudc+"rpm -Uvh ./rpmfusion*rpm",obverb+1,oblog,/*rueck=*/0,/*obsudc=*/0);
			} //   if (!pruefinstv())
			linstp->doinst("ffmpeg",obverb,oblog);
			linstp->doinst("ffmpeg-devel",obverb,oblog);
			linstp->doinst("ffmpeg-compat",obverb,oblog);
		} else {
			svec qrueck;
			const string dname{"libswresample.so"};
			if (findv==1) {
				systemrueck("find "+linstp->libs+"-xtype f -name "+dname,obverb,oblog,&qrueck,/*obsudc=*/0);
			} else findfile(&qrueck,findv,obverb,oblog,0,linstp->libs,/*muster=*/dname+"$",33,1,7);
			if (!qrueck.size()) {
				linstp->doinst("ffmpeg-"+linstp->dev,obverb+1,oblog);
			}
			linstp->doggfinst("libavformat-"+linstp->dev,obverb+1,oblog);
			if (linstp->ipr==apt) {
				linstp->doggfinst("pkg-config",obverb+1,oblog);
			}
		} // 		if (linstp->ipr==dnf||linstp->ipr==yum)
		/*//if (linstp->ipr==apt||linstp->ipr==dnf||linstp->ipr==yum)*/ 
		const string upc{"unpaper_copy"};
		holvomnetz(upc);
		if (vers) systemrueck("which unpaper &&"+sudc+"rm $(which unpaper) && hash -r",obverb,oblog,/*rueck=*/0,/*obsudc=*/0);
		const int altobverb{obverb};
		if (obverb>0) obverb--;
		kompiliere(upc,s_gz);
		obverb=altobverb;
		systemrueck("ldconfig "+lsys.getlib64(),obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
		// unpaper: error while loading shared libraries: libavformat.so.56: cannot open shared object file: No such file or directory
		if (systemrueck("unpaper --version 2>/dev/null",obverb,oblog,/*rueck=*/0,/*obsudc=*/0)==127) {
			// /usr/bin/make in Ubuntu und Opensuse, /bin/make in Fedora, somit aus crontab aufrufbar
			const string ivu=instvz+vtz+upc;
			if (!(systemrueck("cd \""+ivu+"\"&&{ M=Makefile;[ -f $M ]&&{ grep -q 'distclean:' $M&&make distclean||{ grep -q 'clean:' $M&&make clean;};};};"
							"[ -f configure ]&&./configure;make",obverb,oblog,/*rueck=*/0,/*obsudc=*/0))) {
				systemrueck("cd \""+ivu+"\"&& make install",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
				systemrueck("ldconfig "+lsys.getlib64(),obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
			}
		} // 		if (systemrueck
	} // 						if (!urueck.size()||vers<6.1)
} // void hhcl::pruefunpaper()


// aufgerufen in zupdf, inspoolschreiben
int hhcl::pruefocr()
{
	hLog(violetts+Tx[T_pruefocr]+schwarz);
	// 23.1.19: auch pip install virtualenv noetig
	if (!obocrgeprueft) {
		uchar tda{0}, deuda{0}, engda{0}, osdda{0};
		systemrueck("ldconfig "+lsys.getlib64(),obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
		string tpfad;
		svec rueck;
		for(int aru=0;aru<2;aru++) {
			if (obprogda("tesseract",obverb,oblog,&tpfad)) {
				systemrueck(tpfad+" --list-langs 2>&1",obverb,oblog,&rueck,/*obsudc=*/0); // gibt das normale Ergebnis als Fehlermeldung aus!
				for(size_t iru=0;iru<rueck.size();iru++) {
					if (rueck[iru].find("List of available")!=string::npos) {
						tda=1;
						break;
					} // 					if (rueck[iru].find("List of available")!=string::npos)
				} // 				for(size_t iru=0;iru<rueck.size();iru++)
				if (tda) break;
			} else {
				reduzierlibtiff();
				switch (linstp->ipr) {
					case zypper:
						systemrueck("zypper ar -f --gpgcheck-allow-unsigned-repo https://download.opensuse.org/repositories/home:Alexander_Pozdnyakov/openSUSE_Leap_$(lsb-release -r|cut -f2)/home:Alexander_Pozdnyakov.repo",obverb,oblog);break; // 29.8.20, s. https://github.com/tesseract-ocr/tesseract/wiki usw.
					default: break;
				}
				linstp->doinst("tesseract-ocr",obverb,oblog);
				systemrueck("ldconfig "+lsys.getlib64(),obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
			} // 			if (obprogda("tesseract",obverb,oblog,&tpfad))
		} // 		for(int aru=0;aru<2;aru++)
		if (tda) {	
			for(size_t i=1;i<rueck.size();i++) {
				if (rueck[i]=="deu") deuda=1;
				else if (rueck[i]=="eng") engda=1;
				else if (rueck[i]=="osd") osdda=1;
			} //       for(size_t i=1;i<rueck.size();i++)
			if (!deuda) linstp->doinst("tesseract-ocr-traineddata-german",obverb,oblog);
			if (!engda) linstp->doinst("tesseract-ocr-traineddata-english",obverb,oblog);
			if (!osdda) {
				double tessvers{progvers("tesseract")};
				if (tessvers<5) {
					linstp->doinst("tesseract-ocr-traineddata-orientation_and_script_detection",obverb,oblog);
				}
			}
			pruefunpaper();
			linstp->doggfinst("qpdf");
			// uchar alt=0;
			uchar ocrzuinst{1};
			// zu tun: pruefen statt dessen instvz + "/ocrv/bin/ocrmypdf
			struct stat ostat{0};
			virtvz=instvz+"/ocrv";
			ocrmp=virtvz+"/bin/ocrmypdf";
			if (!lstat(ocrmp.c_str(),&ostat))
				//		if (obprogda("ocrmypdf",obverb,oblog)) 
			if (progvers(ocrmp)>4.40) 
				ocrzuinst=0;
		if (ocrzuinst) {
			fLog(Tx[T_Installiere_ocrmypdf],-1,oblog);
			if (linstp->ipr==dnf||linstp->ipr==yum||linstp->ipr==zypper||linstp->ipr==apt) {
				/*// // das Folgende hilft nix; im Internet hatte einer das gleiche Problem 8/15, Loesung aber nicht gefunden, nur update s.u.
					if (double pyv=progvers("python3")<=3.41) {
					linstp->doinst("python3",obverb+1,oblog);
					linstp->doinst("python3"+linstp->dev,obverb+1,oblog);
					} // 				if (double pyv=progvers("python3")<=3.41)
				 */
				// in fedora pip statt pip3
				linstp->doinst("python3-pip",obverb+1,oblog,"pip3");
				obprogda("python3-config",obverb,oblog,&linstp->p3cpf); // "/usr/bin/python3-config"
				linstp->doinst("python3-devel",obverb+1,oblog,linstp->p3cpf);
				linstp->doggfinst("gcc");
				if (!systemrueck("find /usr/lib /usr/lib64 \\( -type f -o -type l \\) -name libffi.so")) {
					if (linstp->obfehlt("libffi48-devel",obverb+1,oblog))
						linstp->doggfinst("libffi-devel",obverb+1,oblog);
				} // 				if (lstat("/usr/lib64/libffi.so",&lffi))
				if (linstp->ipr==dnf||linstp->ipr==yum) 
					linstp->doggfinst("redhat-rpm-config",obverb+1,oblog);
				linstp->doinst("ghostscript",obverb+1,oblog,"gs");
				string ocrvers; // ocrmypdf-Version, falls die letzte mit Python nicht geht
				for(int aru=0;aru<2;aru++) {
					string pyvers;
					const double pyv{progvers("python3",&pyvers)};
					if (pyv<3.46) {
						fLog(rots+Tx[T_Ihre_Python3_Version_koennte_mit]+blau+pyvers+rot+
								Tx[T_veraltet_sein_Wenn_Sie_Ihre_Faxe_OCR_unterziehen_wollen_dann_fuehren_Sie_bitte_ein_Systemupdate_durch_mit]+
								blau+linstp->upd+schwarz,1,1);
					} else if (pyv==3.46) {
						ocrvers="==4.5.6"; // neuere ocrmypdf erfordern python3 >= 3.5
					} else {
						systemrueck("python3 -m pip install --upgrade setuptools pip",obverb+1,oblog,/*rueck=*/0,/*obsudc=*/2);
					} //          if (double pyv=progvers("python3")<=3.41)
					//				systemrueck((cus.cuid?sudo:"")+"python3 -m pip install --upgrade ocrmypdf");  // http://www.uhlme.ch/pdf_ocr
					string vprog;
					for(int iru=0;iru<2;iru++) {
						const string virtualenv{"virtualenv"};
						if (obprogda(virtualenv,obverb,oblog,&vprog)) break;
						systemrueck("pip3 install "+virtualenv,obverb,oblog,/*rueck=*/0,/*obsudc=*/2);
					} // 				for(int iru=0;iru<2;iru++)

					string bef;
					if (!vprog.empty()) {
						bef=vprog+" \""+virtvz+"\";"
							". \""+virtvz+"/bin/activate\";"
							"pip3 install requests;"
							"pip3 install --upgrade ocrmypdf"+ocrvers+";"
							"deactivate;";
					} else {
						bef="python3 -m venv \""+virtvz+"\";"
							"python3 -m venv --upgrade \""+virtvz+"\";"
							". \""+virtvz+"/bin/activate\";"
							"pip3 install --upgrade pip;"
							"pip3 install ocrmypdf"+ocrvers+";"
							"deactivate;";
							////		"grep \""+sudc+"rm -rf \\\""+virtvz+"\\\"\" \""+unindt+"\"||printf \""+sudc+"rm -rf \\\""+virtvz+"\\\"\\n\">>\""+unindt+"\";"
							////		"grep ocrmypdf \""+unindt+"\"||printf \""+sudc+"pip3 uninstall --yes ocrmypdf\\n\">>\""+unindt+"\";"
							////		"||sed -i \"/ python3/isudc pip3 uninstall --yes ocrmypdf\" \""+unindt+"\""
					} // if (!vprog.empty()) else
					systemrueck(bef,obverb,oblog,/*rueck=*/0,/*obsudc=*/2);
					// der ocrmypdf-Aufruf wuerde mit 'match' scheitern, wenn 'tesseract --version' als erste Zeile einen Warnhinweis auf eine geaenderte
					// libtiff-Bibliothek liefert, nicht hingegen mit 'search'
					systemrueck("find "+virtvz+" -name tesseract.py -exec sed -i.bak 's/re.match/re.search/g' {} \\;",obverb,oblog,0,/*obsudc=*/1);
					if (!lstat(ocrmp.c_str(),&ostat)) {
						anfgg(unindt,sudc+"rm -rf \""+virtvz+"\"","",obverb,oblog);
						anfgg(unindt,
								sudc+". \""+virtvz+"/bin/activate\";"+
								"pip3 uninstall --yes ocrmypdf;"
								"deactivate;",bef,obverb,oblog);
						break;
					} // 					if (!lstat(ocrmp.c_str(),&ostat))
					if (aru) break;
					ocrvers="==4.5.6"; // neuere ocrmypdf erfordern python3 >= 3.5
				} // 				for(int aru=0;aru<2;aru++)

				//// sudc+"pip3 uninstall --yes ocrmypdf"
				//// sudc+"dnf install ./ghostscript-9.16-4.fc24.i686.rpm"
				//// sudc+"dnf -y install ghostscript // ghostscript 9.20 geht nicht mit pdf/a und overwrite"
#ifdef sonstige
			} else {
				if (!linstp->doggfinst("python3-devel",obverb+1,oblog)) {
					if (!linstp->doinst("python3-pip",obverb+1,oblog,"pip3")) {
						lsysen system=lsys.getsys(obverb,oblog);
						if (system==deb) {
							linstp->doggfinst("pkg-config",obverb+1,oblog);
							linstp->doggfinst("python3-setuptools",obverb+1,oblog);
							linstp->doggfinst("libffi-dev",obverb+1,oblog,1);
							linstp->doggfinst("libssl-dev",obverb+1,oblog);
						}
						const string proj{"ocrmypdf_copy"};
						const string srcvz{instvz+vtz+proj+".tar.gz"};
						holvomnetz(proj);
						if (!kompilbase(proj,s_gz)) {
							/*//
							// sudo pip3 install image PyPDF2 ruffus reportlab cryptography cffi
							// sudo PKG_CONFIG_PATH=/usr/lib64/ffmpeg-compat/pkgconfig pkg-config --cflags libavcodec
							// moegliche weitere Befehle:
							// sudo dnf -y --reinstall install python3-pip
							// sudo dnf clean all
							// sudo dnf -y update
							// sudo pip install -U setuptools
							// dnf install mupdf mupdf-devel
							// pyvenv venv
							// . venv/bin/activate
							// .. pip3 install image PyPDF2 ruffus reportlab M2Crypto cryptography cffi ocrmypdf
							//  pip install --upgrade pip
							// pip3 install --upgrade git+https://github.com/jbarlow83/OCRmyPDF.git
							// instvz+"/venv/bin/pip3 install --upgrade git+https://github.com/jbarlow83/OCRmyPDF.git
							// sudo python3 -m pip install ocrmypdf
							// dnf install python3-devel (fuer Python.h)
							// sudo dnf -y install libffi libffi-devel (fuer ffi.h)
							// CFLAGS=-I/usr/include/libffi/include ./"+instvz+"/venv/bin/pip3 install pyOpenSSL
							// sudo python3 -m pip install ocrmypdf
							// sudo dnf -y install qpdf
							 */
							pruefunpaper();
							systemrueck("cd \""+instvz+vtz+proj+"\" &&python3 -m pip install image PyPDF2 ruffus reportlab M2Crypto cryptography cffi ocrmypdf", 
									      obverb,oblog,/*rueck=*/0,/*obsudc=*/2);
							//// <<rot<<"vor doinst(unpaper)"<<schwarz<<endl;
							linstp->doinst("unpaper",obverb>0?obverb-1:obverb,oblog);
							//// <<rot<<"nach doinst(unpaper)"<<schwarz<<endl;
						} //    if (!kompilbase(was,endg))
					} //       if (!linstp->doinst("python3-pip",obverb+1,oblog,"pip3"))
				} //     if (!linstp->doggfinst("python-devel",obverb+1,oblog))
#endif // sonstige
			} // if (linstp->ipr==dnf)
		} //     		if (ocrzuinst)
		string prog;
		if (obprogda(ocrmp,obverb,oblog,&prog)) {
			unpaperfuercron(prog);
		} //  if (obprogda(ocr,obverb,oblog,&prog))
		obocrgeprueft=1;
		} //     if (!tda)
	} // if (!obocrgeprueft) 
	return 0;
} // int hhcl::pruefocr

// aufgerufen in: empfarch
void hhcl::empffbox(const string& ganz,const size_t aktc,const string& nr/*=nix*/)
{
	const auto altobverb{obverb};
//	obverb=2;
	hLog(violetts+Tx[T_empffbox]+schwarz+ganz+", aktc: "+ltoan(aktc)+", nr: "+nr);
	struct stat stganz{0};
	const uchar ganzfehlt{(uchar)lstat(ganz.c_str(),&stganz)}; // muesste immer 0 sein, wenn es die Datei gibt
	if (!ganzfehlt) {
		string stamm,exten;
		getstammext(&ganz,&stamm,&exten);
		const string base{base_name(stamm)}; // Dateiname ohne Pfad
		struct tm tm{0};
		if (!strptime(base.c_str(),"%d.%m.%y_%H.%M",&tm)) {
			memcpy(&tm,localtime(&stganz.st_mtime),sizeof tm); // gmtime
		}
		const string tf{"Telefax."}; 
		size_t p2{base.rfind(tf)};
		const string callerid{p2==string::npos?string():base.substr(p2+tf.length())};
		const string tsid{stdfaxnr(callerid)};
		string absdr, bsname;
		getSender(tsid,&absdr,&bsname,aktc);
		//// <<gruen<<"absdr("<<tsid<<"): "<<schwarz<<absdr<<" bsname: "<<bsname<<endl;
		if (!bsname.empty()) {
			absdr+=", ";
			absdr+=bsname;
		} // 			if (!bsname.empty())
		if (absdr.empty() || istelnr(absdr)) { // wenn Nr. nicht gefunden, kommt sie in absdr wieder zurueck
			absdr=tsid;
		} // 		if (absdr.empty() || istelnr(absdr))
		fuersamba(absdr);  
		if (absdr.length()>187) absdr.erase(187);
		if (absdr.length()>70) absdr.erase(70);
		ulong fnr{0};
		struct stat statfarchvz{0};
		const string nrdt{farchvz+"/nnr"}; // /var/spool/fbfax/arch + naechste Nummer
		static uchar farchvzgeprueft{0};
		if (!farchvzgeprueft) {
			farchvzgeprueft=pruefverz(farchvz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/cuser,/*benutzer=*/cuser);
		}
		uchar obfarchda{0};
		if (!lstat(farchvz.c_str(),&statfarchvz)) {
			obfarchda=1;
			struct stat statfnr{0};
			if (!lstat(nrdt.c_str(),&statfnr)) {
				mdatei mnrdt(nrdt,ios::in);
				if (mnrdt.is_open()) {
					string zeile;
					getline(mnrdt,zeile);
					fnr=atol(zeile.c_str());
				} // 						if (mnnr.is_open())
			} // 					if (!lstat(nnr.c_str(),&statnnr))
			fnr++;
		} // 				if (!lstat(fempfavz.c_str(),&statfempfavz))
		//				dorename(ganz,fempfavz,cuser,/*vfehlerp=*/0,/*schonda=*/0,obverb,oblog);
		stringstream frstr;
		frstr<<"Fax f"<<fnr<<","<<Tx[T_avon]<<absdr<<", T."<<tsid<<", "<<Tx[T_vom]<<put_time(&tm,"%d.%m.%Y %H.%M.%S");
		const string frumpf{frstr.str()},
					fdatei{frumpf+".pdf"},
					fpfad{empfvz+vtz+fdatei};
		fLog((nr.empty()?"":nr+")")+blaus+base+schwarz+" => "+gruen+fdatei+schwarz,1,1);
		// ..., die empfangene Datei in fpfad kopieren ...
		uint kfehler{0};
		kopiere(ganz,fpfad,&kfehler,/*wieweiterzaehl=*/1,obverb,oblog);
		if (!kfehler) {
			attrangleich(fpfad,empfvz,&ganz,obverb,oblog);
			ankzahl++;
			struct stat entrynd{0};
			const uchar obfpfadda{!lstat(fpfad.c_str(),&entrynd)};
			if (obfpfadda && obfarchda) {
				mdatei mnrdt(nrdt,ios::out);
				if (mnrdt.is_open()) {
					mnrdt<<fnr;
				}
			}
			////		if (obfpfadda) if (chmod(fpfad.c_str(),S_IRWXU|S_IRGRP|S_IROTH)) systemrueck(sudc+"chmod +r \""+fpfad+"\"",obverb,oblog);
			RS rins(My,tinca); 
			vector<instyp> einf; // fuer alle Datenbankeinfuegungen
			einf.push_back(/*2*/instyp(My->DBS,"fsize",stganz.st_size));
			const unsigned sz{pdfseitenzahl(fpfad)};//24.8.20:bei ganz: terminate called after throwing an instance of 'QPDFSystemError' ... stale file handle
			einf.push_back(/*2*/instyp(My->DBS,"pages",sz));
			einf.push_back(/*2*/instyp(My->DBS,"titel",&absdr));
			einf.push_back(/*2*/instyp(My->DBS,"tsid",&tsid));
			////        einf.push_back(instyp(My->DBS,"callerid",&callerid));
			einf.push_back(/*2*/instyp(My->DBS,"devname",&fbdev));
			einf.push_back(/*2*/instyp(My->DBS,"id",&base));
			einf.push_back(/*2*/instyp(My->DBS,"transe",&tm));
			svec eindfeld; eindfeld<<"id";
			rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/0,/*eindeutig=*/0,eindfeld); 
			if (rins.fnr) {
				fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
			} else {
				if (ganz.find(farchvz)) { // bei empferneut nicht
					int fehler{0};
					if (!(fehler=kopier(fpfad/*ganz*/,farchvz+vtz+base+"."+exten,2/*obverb*/,oblog))) { // 29.8.20: Kopieren geht nicht von /mnt/fbdiab => /
						dorename(ganz,stamm+"_alt.pdf",cuser,/*vfehlerp=*/0,/*schonda=*/0,2/*obverb*/,oblog);
					} else {
						caus<<rot<<"Fehler: "<<blau<<fehler<<schwarz<<endl;
					}
				}
			} //         if (runde==1)
			if (!zupdf(&fpfad, fpfad+"ocr", 0, 1, 0)) { // 0=Erfolg
        dorename(fpfad+"ocr",fpfad,cuser,0,0,obverb,oblog);
			}
		} else {
			const string warndt{empfvz+vtz+Tx[T_nicht_angekommen]+frumpf+".nix"};
			touch(warndt,obverb,oblog);
			attrangleich(warndt,empfvz,&ganz,obverb,oblog);
		}
	}
	obverb=altobverb;
} // void hhcl::empffbox(const string& ganz,const size_t aktc,const string& nr/*=nix*/)

// aufgerufen in: empferneut, empfarch
void hhcl::empfhyla(const string& ganz,const size_t aktc, const uchar was,const string& nr/*=nix*/)
{
	// uchar indb/*=1*/,uchar mitversch/*=1*/)
	// was&4: Bilddateien erstellen, was&2 q-Datei archivieren, was&1: in Datenbank eintragen, 
	// Dateien kommen als tif-Dateien an, z.B. /var/spool/hylafax/../fax000000572.tif
	hLog(violetts+Tx[T_empfhyla]+schwarz+ganz+Tx[T_was]+(was&4?Tx[T_Bilddatei]:"")+(was&2?", q ":"")+(was&1?", Tab.":""));
	struct stat stganz{0};
	const uchar ganzfehlt{(uchar)lstat(ganz.c_str(),&stganz)}; // muesste immer 0 sein, wenn es die Datei gibt
	if (!ganzfehlt) {
		string stamm,exten;
		getstammext(&ganz,&stamm,&exten);
		const string base{base_name(stamm)};
		string fnr{base.substr(3)};
		fnr=fnr.substr(fnr.find_first_not_of("0"));
		struct tm tm{0};
		struct stat elog{0};
		ulong seiten{0};
		string absdr,tsid,callerid,devname{hmodem};
		if (!holtif(ganz,&seiten,&tm,&elog,&absdr,&tsid,&callerid,&devname)) // Tif-Informationen holen
			ankzahl++;
		string tabsdr; // transferierter Absender
		if (callerid.empty()) {
			svec trueck;
			struct stat trst{0};
			if (!lstat(xferfaxlog.c_str(),&trst)) {
				systemrueck("tac \""+xferfaxlog+"\" 2>/dev/null |grep -am 1 \""+base_name(ganz)+"\" |cut -f8,9",obverb,oblog,&trueck); 
				if (trueck.size()) {
					vector<string> tok; 
					aufSplit(&tok,trueck[0],'\t');
					if (tok.size()) {
						//// <<gruen<<"tok[0] d: "<<schwarz<<tok[0]<<endl; // Tel'nr z.B. 49.8131.1234567
						callerid=tok[0];
						if (tok.size()>1) {
							//// <<gruen<<"tok[1] d: "<<schwarz<<tok[1]<<endl; // Namen z.B. G.Schade
							tabsdr=tok[1];
							anfzweg(&tabsdr); // Anfuehrungszeichen entfernen
						} //           if (tok.size()>1)
					} // if (tok.size()) 
				} // if (trueck.size()) 
			} // 	if (!lstat(xferfaxlog.c_str(),&trst))
		} // if (callerid.empty()) 
		//// <<gruen<<"tsid: "<<schwarz<<tsid<<endl;
		tsid=stdfaxnr(tsid.empty()?callerid:tsid);
		if (absdr.empty()) {
			string bsname;
			getSender(tsid,&absdr,&bsname,aktc);
			//// <<gruen<<"absdr("<<tsid<<"): "<<schwarz<<absdr<<" bsname: "<<bsname<<endl;
			if (!bsname.empty()) {
				absdr+=", ";
				absdr+=bsname;
			} // 			if (!bsname.empty())
			if (absdr.empty() || istelnr(absdr)) { // wenn Nr. nicht gefunden, kommt sie in absdr wieder zurueck
				absdr=tabsdr;
			} // 		if (absdr.empty() || istelnr(absdr))
		} //     if (absdr.empty())
		fuersamba(absdr);  
		int obhpfadda{1}, obpdfda{1}; // wenn !(was&4), dann nicht behindern
		if (was&4) {
			//// char tbuf[100];
			//// strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H.%M.%S", &tm);
			if (absdr.length()>187) absdr.erase(187);
			if (absdr.length()>70) absdr.erase(70);
			//// const string hrumpf="Fax h"+fnr+","+Tx[T_avon]+absdr+", T."+tsid+", "+Tx[T_vom]+tbuf;
			stringstream hrstr;
			hrstr<<"Fax h"<<fnr<<","<<Tx[T_avon]<<absdr<<", T."<<tsid<<", "<<Tx[T_vom]<<put_time(&tm,"%d.%m.%Y %H.%M.%S");
			const string hrumpf{hrstr.str()},
						hdatei{hrumpf+".tif"},
						hpfad{empfvz+vtz+hdatei},
						ziel{empfvz+vtz+hrumpf+".pdf"};
			fLog((nr.empty()?"":nr+")")+blaus+base+schwarz+" => "+gruen+hdatei+schwarz,1,1);
			// ..., die empfangene Datei in hpfad kopieren ...
			uint kfehler{0};
			string vorsoffice{kopiere(ganz,hpfad,&kfehler,/*wieweiterzaehl=*/1,obverb,oblog)};
			if (!kfehler) {
				attrangleich(hpfad,empfvz,&ganz,obverb,oblog);
			} else {
				vorsoffice=ganz;
			} //     if (!kfehler) else
			struct stat entrynd{0};
			obhpfadda=!lstat(hpfad.c_str(),&entrynd);
			////		if (obhpfadda) if (chmod(hpfad.c_str(),S_IRWXU|S_IRGRP|S_IROTH)) systemrueck(sudc+"chmod +r \""+hpfad+"\"",obverb,oblog);
			ulong pseiten{0};
			if (!lstat(ziel.c_str(),&entrynd)) 
				tuloeschen(ziel,cuser,obverb,oblog);
			obpdfda=!zupdf(&vorsoffice, ziel, &pseiten, obocri, 1); // 0=Erfolg
			if (obpdfda && !lstat(ziel.c_str(),&entrynd)) {
				attrangleich(ziel,empfvz,&ganz,obverb,oblog);
				elog.st_size=entrynd.st_size;
				if (!kfehler) 
					tuloeschen(hpfad,cuser,obverb,oblog);
			} // 			if (obpdfda) if (!lstat(ziel.c_str(),&entrynd))
			if (obhpfadda||obpdfda) {
				if (was&2) {
					//// cmd=string(sudc+"mv \"")+ganz+"\" \""+hempfavz+"\""; systemrueck(cmd,obverb,oblog);
					static uchar hempfgeprueft{0};
					if (!hempfgeprueft) {
						pruefverz(hempfavz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/huser,/*benutzer=*/cuser);
						hempfgeprueft=1;
					} // 			if (!hempfgeprueft)
					dorename(ganz,hempfavz,cuser,/*vfehlerp=*/0,/*schonda=*/0,obverb,oblog);
				} // 	if (was&2)
			} else {
				const string warndt{empfvz+vtz+Tx[T_nicht_angekommen]+hrumpf+".nix"};
				touch(warndt,obverb,oblog);
				attrangleich(warndt,empfvz,&ganz,obverb,oblog);
			} // 		if (obhpfadda||obpdfda) else
		} // 	if (was&4) 
		// wenn was&4, dann obhpdfadda oder obpdfda zur Voraussetzung machen
		if (was&1 &&(obhpfadda||obpdfda)) {
			// ... und falls erfolgreich in der Datenbanktabelle inca eintragen
			RS rins(My,tinca); 
			vector<instyp> einf; // fuer alle Datenbankeinfuegungen
			einf.push_back(/*2*/instyp(My->DBS,"fsize",elog.st_size));
			einf.push_back(/*2*/instyp(My->DBS,"pages",seiten));
			einf.push_back(/*2*/instyp(My->DBS,"titel",&absdr));
			einf.push_back(/*2*/instyp(My->DBS,"tsid",&tsid));
			////        einf.push_back(instyp(My->DBS,"callerid",&callerid));
			einf.push_back(/*2*/instyp(My->DBS,"devname",&devname));
			einf.push_back(/*2*/instyp(My->DBS,"id",&base));
			einf.push_back(/*2*/instyp(My->DBS,"transe",&tm));
			svec eindfeld; eindfeld<<"id";
			rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/0,/*eindeutig=*/0,eindfeld); 
			if (rins.fnr) {
				fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
			} //         if (runde==1)
		} // 	if (was&1 &&(obhpfadda||obpdfda))
	} // 	if (!ganzfehlt)
} // void hhcl::empfhyla(const string& stamm,uchar indb/*=1*/,uchar mitversch/*=1*/)


// aufgerufen in: main
void hhcl::empferneut()
{
	const size_t aktc{0};
	hLog(violetts+Tx[T_empferneut]+schwarz);
	tu_listi(/*zurauswahl=*/1);
	const string onrs{Tippstr(Tx[T_Welches_Fax_soll_erneut_empfangen_werden_bitte_Nr_in_der_1_Spalte_eingeben_a_alle_Angezeigten], 0)};
	size_t beg{1},end{0};
	if (onrs=="a") {
		beg=0;
		end=vinca.size();
	} else {
		const size_t onr{(size_t)atol(onrs.c_str())-1};
		if (onr<vinca.size()) {
			beg=onr;
			end=onr+1;
		} // 		if (onr<vinca.size())
	} // 	if (onrs=="a") else 
	for(size_t j=beg;j<end;) {
		const string fnr{vinca[j++]};
		fLog(Tx[T_Bearbeite]+blaus+ltoan(j)+") ..."+schwarz,obverb,0);
		struct stat cstat{0};
		if (fnr.find('-')!=string::npos) {
      const string rumpf{(fnr.find("fax-")?"":cuser+'-')+fnr};
			string txtd{cempfavz+vtz+rumpf};
			//// <<txtd<<endl;
			if (!lstat((txtd+".txt").c_str(),&cstat)&&!lstat((txtd+".sff").c_str(),&cstat)) {
				empfcapi(txtd,aktc,4,ltoan(j));
			} else {
				txtd=cfaxuserrcfalschevz+vtz+fnr;
				//// <<txtd<<endl;
				if (!lstat((txtd+".txt").c_str(),&cstat)&&!lstat((txtd+".sff").c_str(),&cstat)) {
					empfcapi(txtd,aktc,4,ltoan(j));
				} else {
					svec sffe;
					cmd="find '"+spoolcapivz+"/' -maxdepth 2 -type f -iname '"+rumpf+".sff"+"'";
					systemrueck(cmd,obverb,oblog,&sffe,/*obsudc=*/0);
					for (auto fund:sffe) {
						fund.resize(fund.length()-4);
						fund+=".txt";
						if (!lstat(fund.c_str(),&cstat)) {
							fund.resize(fund.length()-4);
							empfcapi(fund,aktc,4,ltoan(j));
							break;
						}
					}
				}
			}
		} else {
			const string txtd{hempfavz+vtz+fnr+".tif"};
			if (!lstat(txtd.c_str(),&cstat)) {
				empfhyla(txtd,aktc,4,ltoan(j));
			} else {
				empffbox(farchvz+vtz+fnr+".pdf",aktc,ltoan(j));
			} // 		if (!lstat(txtd.c_str(),&cstat))
		} // 	if (fnr.find('-')!=string::npos)
	} // 	for(j=beg;j<end;j++)
	fLog(violetts+Txk[T_Ende]+Tx[T_empferneut]+schwarz,1,0);
} // int hhcl::empferneut

// aufgerufen in: main
// loesche die Eintraege in spooltab, deren Dateien nicht im Warteverzeichnis nicht im Capi- und nicht im Hylasystem stehen
size_t hhcl::loeschewaise()
{
	auto const altZDB{ZDB};
	auto const altobverb{obverb};
	ZDB=1;
	obverb=1;
	hLog(blaus+Tx[T_loeschewaise]+schwarz);
	const size_t aktc{0};
	vector<string> allec;
	vector<string> ids;
	char*** cerg;
	RS su(My,"SELECT original p0, capispooldt p1, hylanr p2, fbspooldt p3, id p4 FROM `"+spooltab+"`",aktc,ZDB);
	while (cerg=su.HolZeile(),cerg?*cerg:0) {
		if (*(*cerg+0)) {
			struct stat entryo{0};
			caus <<"Überprüfe: "<<gruen<<wvz+vtz+cjj(cerg,0)<<schwarz<<endl;
			if (!lstat((wvz+vtz+cjj(cerg,0)).c_str(),&entryo)) continue; // Wenn es die Datei im Warteverzeichnis gibt
			caus <<"capispooldt: "<<gruen<<cfaxusersqvz+vtz+cjj(cerg,1)<<schwarz<<endl;
			if (*(*cerg+1)) if (*cjj(cerg,1)) {
				if (!lstat((cfaxusersqvz+vtz+cjj(cerg,1)).c_str(),&entryo)) continue; // wenn eine capispooldt drinsteht und es sie gibt
			}
			caus <<"hsendqvz: "<<gruen<<hsendqvz+"/q"+cjj(cerg,2)<<schwarz<<endl;
			if (*(*cerg+2)) if (*cjj(cerg,2)) if (memcmp("0",cjj(cerg,2),2)) { // hylanr hat in der Datenbank Vorgabewert 0
				if (!lstat((hsendqvz+"/q"+cjj(cerg,2)).c_str(),&entryo)) continue; // wenn eine Hylaspooldatei drinsteht und es sie gibt
			}
			if (*(*cerg+3)) if (*cjj(cerg,3)) {
				if (!lstat((fbwvz+vtz+cjj(cerg,3)+".vw").c_str(),&entryo) && !lstat((fbwvz+vtz+cjj(cerg,3)+".tif").c_str(),&entryo)) continue; // wenn fbfax-Dateien da sind
		cmd=sudc+"find '"+fbwvz+"' -maxdepth 1 -type f -iname 'dt*.vw'"; ////  -printf '%f\\n'";
			}
			if (*(*cerg+4)) {
				fLog(rots+Tx[T_Aus]+"'"+blau+spooltab+rot+"'"+Tx[T_zu_loeschen]+schwarz+"'"+blau+cjj(cerg,0)+schwarz+"', id: "+blau+cjj(cerg,4)+schwarz,1,1);
				ids.push_back(cjj(cerg,4));
			}
		} // if (*(*cerg+0)) 
	} // while (cerg=su.HolZeile(),cerg?*cerg:0) 
	if (ids.size()) {
		if (Tippob(Tx[T_Sollen_wirklich_alle]+gruens+ltoan(ids.size())+schwarz+Tx[T_waisen_Faxe_geloescht_werden],"n")) {
			string liste;
			for(size_t i=0;i<ids.size();i++) {
				liste+=ids[i];
				if (i<ids.size()-1) liste+=',';
			} // 			for(size_t i=0;i<ids.size();i++) 
			RS loe(My,"DELETE FROM `"+spooltab+"` WHERE id IN ("+liste+")",aktc,ZDB);
		} // 		if (Tippob(Tx[T_Sollen_wirklich_alle]+gruens+ltoan(ids.size())+schwarz+Tx[T_waisen_Faxe_geloescht_werden],"n"))
	} else {
		fLog(Tx[T_Keine_waisen_Faxe_zum_Loeschen_da],1,oblog);
	} // 	if (ids.size()) else
	obverb=altobverb;
	ZDB=altZDB;
	return ids.size();
} // int hhcl::loeschewaise()

// aufgerufen in: main
size_t hhcl::loescheallewartenden()
{
	hLog(blaus+Tx[T_loescheallewartenden]+schwarz);
	const size_t aktc{0};
	size_t erg{0};
	svec allec, alled, allew;
	struct stat entryvz{0};
	if (!lstat(cfaxusersqvz.c_str(),&entryvz)) {
		if (findv==1) {
			cmd="find '"+cfaxusersqvz+"/' -maxdepth 1 -type f -iname 'fax-*.*'";
			systemrueck(cmd,obverb,oblog,&allec,/*obsudc=*/1);
		} else findfile(&allec,findv,obverb,oblog,0,cfaxusersqvz,/*muster=*/"fax-[^.]*\\..*",1,1,Fol_Dat,0,0,1);
		erg+=(allec.size()>>1); // *.txt und *.sff
	} // if (!lstat(cfaxusersqvz.c_str(),&entryvz)) 
	//  cmd=string("rm ")+cfaxuservz+vtz+cuser+vtz+"sendq"+vtz+"fax-*.*"; //  "/var/spool/capisuite/users/<user>/sendq";
	if (!lstat(hsendqvz.c_str(),&entryvz)) {
		if (findv==1) {
			cmd="find '"+hsendqvz+"' -maxdepth 1 -type f -regex '.*/q[0-9]+' -printf '%f\\n'";
			systemrueck(cmd,obverb,oblog, &alled,/*obsudc=*/1);
		} else findfile(&alled,findv,obverb,oblog,1,hsendqvz,/*muster=*/"/q[^/]*",1,1,Fol_Dat,0,0,1);
		erg+=alled.size();
	} // if (!lstat(hsendqvz.c_str(),&entryvz)) 
	vector<fsfcl> fsfav;
	size_t j=0;
	for(size_t i=0;i<allec.size();i++) {
		if (allec[i].find(".sff")!=string::npos) {
			char ***cerg;
			RS zl(My,"SELECT original,origvu FROM `"+spooltab+"` WHERE capispooldt='"+base_name(allec[i])+"'",aktc,ZDB);
			if(cerg=zl.HolZeile(),cerg?*cerg:0) {
				fLog(blaus+ltoan(++j)+schwarz+": '"+allec[i]+"' -> '"+blau+cjj(cerg,0)+schwarz+"'",1,oblog);
				fsfav.push_back(/*6*/fsfcl(/*origial=*/cjj(cerg,0),/*origvu=*/cjj(cerg,1),/*cnr=*/6));
			} else {
				fLog(blaus+ltoan(++j)+schwarz+": "+allec[i]+blau+schwarz,1,oblog);
			} // 			if(cerg=zl.HolZeile(),cerg?*cerg:0) else
		} // 				if (allec[i].find(".sff")!=string::npos)
	} // 			for(size_t i=0;i<allec.size();i++)
	for(size_t i=0;i<alled.size();i++) {
		char ***cerg;
		string transalle{alled[i]};
		ersetzAlle(&transalle,"q","");  
		RS zl(My,"SELECT original,origvu FROM `"+spooltab+"` WHERE hylanr="+transalle,aktc,ZDB);
		if(cerg=zl.HolZeile(),cerg?*cerg:0) {
			fLog(blaus+ltoan(++j)+schwarz+": '"+hsendqvz+vtz+alled[i]+"' -> '"+blau+cjj(cerg,0)+schwarz+"'",1,oblog);
			fsfav.push_back(/*6*/fsfcl(/*origial=*/cjj(cerg,0),/*origvu=*/cjj(cerg,1),/*cnr=*/6));
		} else {
			fLog(blaus+ltoan(++j)+schwarz+": "+alled[i]+blau+schwarz,1,oblog);
		} // 		if(cerg=zl.HolZeile(),cerg?*cerg:0)
	} // 			for(size_t i=0;i<alled.size();i++)

	char ***cerg;
	RS zl(My,"SELECT original,origvu FROM `"+spooltab+"`"/* WHERE telnr=''*/,aktc,ZDB);
	while (cerg=zl.HolZeile(),cerg?*cerg:0) {
		fLog(blaus+ltoan(++j)+schwarz+": '"+blau+cjj(cerg,0)+schwarz+"'",1,oblog);
		++erg;
		fsfav.push_back(/*6*/fsfcl(/*origial=*/cjj(cerg,0),/*origvu=*/cjj(cerg,1),/*cnr=*/6));
	}

	if (erg) {
		if (Tippob(blaus+Tx[T_Sollen_wirklich_alle]+gruens+ltoan(erg)+blau+Tx[T_wartenden_Faxe_geloescht_werden],"n")) {
			for(size_t i=0;i<allec.size();i++) {
				tuloeschen(allec[i],cuser,1,oblog);
				if (allec[i].find(".sff")!=string::npos) {
					const string fname{base_name(allec[i])};
					RS loe(My,"DELETE FROM `"+spooltab+"` WHERE capispooldt='"+fname+"'",aktc,ZDB);
				} // 				if (allec[i].find(".sff")!=string::npos)
			} // for(size_t i=0;i<allec.size();i++) 
			for(size_t i=0;i<alled.size();i++) {
				string transalle{alled[i]};
				ersetzAlle(&transalle,"q","");  
				/*4*/fsfcl zuloe(transalle);
				if (!zuloe.loeschehyla(this,obverb,oblog)) {
					////      cmd=string("faxrm ")+transalle;
					////      if (systemrueck(cmd,obverb,oblog)) KLA
					RS loe(My,"DELETE FROM `"+spooltab+"` WHERE hylanr="+transalle,aktc,ZDB);
				} // 				if (!zuloe.loeschehyla(this,obverb,oblog))
			} // for(size_t i=0;i<alled.size();i++) 
			for(size_t nr=0;nr<fsfav.size();nr++) {
				fsfav[nr].scheitere(wvz,ngvz,cuser,0,obverb,oblog);
			} // 			for(size_t i=0;i<fsfav.size();i++)
			RS loe(My,"DELETE FROM `"+spooltab+"`"/* WHERE telnr=''*/,aktc,ZDB);
		} // 		if (Tippob(Tx[T_Sollen_wirklich_alle]+gruens+ltoan(erg)+schwarz+Tx[T_wartenden_Faxe_geloescht_werden],"n"))
	} else {
		fLog(Tx[T_Keine_wartenden_Faxe_zum_Loeschen_da],1,oblog);
	} // if (erg)
	return erg;
} // int hhcl::loescheallewartenden()

// aufgerufen in inspoolschreiben
// ermittelt in Dateinamen steckendes Datum und gibt zurueck, ob dieses schon vorbei ist
int hhcl::obvorbei(const string& vzname,uchar *auchtag)
{
	hLog(blaus+"obvorbei()"+schwarz);
	tm ht({0});
	time_t jetzt{time(0)},// / (24*60*60) *24*60*60 ;
				 heute{jetzt-jetzt%86400},
				 par{jetzt};
	//// <<"jetzt: "<<jetzt<<endl;
	//// <<"heute: "<<heute<<endl;
	//// <<"jetzt: "<<put_time(gmtime(&jetzt),"%c")<<endl;
	uchar geht{0};
	const char *mus[]
	{"%d.%m.%y %H.%M","%d.%m.%Y %H.%M","%d.%m.%y","%d.%m.%Y","%H.%M"
		,"%y-%m-%d %H.%M","%Y-%m-%d %H.%M","%y-%m-%d","%Y-%m-%d"
			,"%y%m%d%H%M","%Y%m%d%H%M","%H%M"
			,"%y%m%d","%Y%m%d"
	};
	unsigned iru=0;
	for(;iru<elemzahl(mus);iru++) {
		memcpy(&ht,gmtime(&heute),sizeof ht);
		if (obverb>1) {
			fLog(" iru: "+blaus+ltoan(iru)+schwarz+":"+blau+mus[iru]+schwarz,obverb,oblog);
		}
		if (strptime(vzname.c_str(),mus[iru],&ht)) {
			if (obverb>1) {
				stringstream sts;
				sts<<" iru: "<<blau<<iru<<schwarz<<": "<<blau<<put_time(&ht,"%c")<<schwarz;
				fLog(sts.str(),obverb,oblog);
			}
			geht=1;
			if (strchr(mus[iru],'d'))
				if (auchtag) *auchtag=1;
			break;
		} // 		if (strptime(vzname.c_str(),mus[iru],&ht))
	} // 	for(unsigned iru=0;iru<elemzahl(mus);iru++)
	if (geht) {
		if (obverb>1) {
				stringstream sts;
				sts<<"Parameter: "<<put_time(&ht,"%Y-%m-%d %H:%M:%S");
				fLog(sts.str(),obverb,oblog);
		}
		if ((par=mktime(&ht))==-1) {
			return -1;
		} // 		if ((par=mktime(&ht))==-1)
	} // 	if (geht)
	if (obverb||oblog) {
		stringstream sts;
    sts<<put_time(&ht,"%Y-%m-%d %H:%M:%S");
		hLog(Tx[T_Unterverzeichnis]+blaus+vzname+schwarz+(geht?Tx[T_passt_zu_Muster]+blaus+mus[iru]+schwarz+
					(par<jetzt?Tx[T_war_schon]:Tx[T_kommt_noch])+blau+sts.str()+schwarz:Tx[T_passt_zu_keinem_Muster]));
	} // 	if (obverb||oblog)
	return par<jetzt;
} // int obvorbei

void hhcl::fxinDatenbank(fxfcl& fx,const size_t aktc)
{
	hLog(violetts+Tx[T_fxinDatenbank]+schwarz);
	string spoolid,udocid;
		vector<instyp> einf; // fuer alle Datenbankeinfuegungen
		int wiemail{0};// 1 = verschluesselte Mail, 2 = klare Mail
		////<<rot<<"1: "<<gruen<<fx.spdf<<schwarz<<endl;
		////<<rot<<"2: "<<gruen<<fx.ur<<schwarz<<endl;
		////<<rot<<"3: "<<gruen<<fx.npdf<<schwarz<<endl;
		////<<rot<<"4: "<<gruen<<fx.ur<<schwarz<<endl;
		if (fx.spdf!=fx.ur||fx.npdf!=fx.ur) {
			RS rins(My,udoctab); 
			einf.push_back(/*2*/instyp(My->DBS,"udocname",fx.ur));
			////<<"udocid: "<<udocid<<endl;
			rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/&udocid);
			if (rins.fnr) {
				fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
			} //       if (runde==1)
			////<<"udocid: "<<udocid<<endl;
			//// rins.dsclear();
			einf.clear();
		} // 			if (fx.spdf!=fx.ur||fx.npdf!=fx.ur)
		if (!udocid.empty()) 
			einf.push_back(/*2*/instyp(My->DBS,"idudoc",udocid));
		const string odatei{base_name(fx.spdf)};
		einf.push_back(/*2*/instyp(My->DBS,"original",&odatei));
		// den Adressaten ermitteln
		size_t pn, posaf, posafc, posafh, pm, pkm;
		pn=odatei.find(anstr);
		posaf=odatei.find(anfaxstr);
		posafc=odatei.find(ancfaxstr);
		posafh=odatei.find(anhfaxstr);
		pm=odatei.find(anmailstr);
		pkm=odatei.find(klaranmailstr);
		if (posafc<posaf) posaf=posafc;
		if (posafh<posaf) posaf=posafh;
		if (pm<posaf) {posaf=pm; wiemail=1;}
		if (pkm<posaf) {posaf=pkm; wiemail=2;}
		if (posaf!=string::npos && pn<posaf-anstr.length()-1) { // mind. 1 Buchstaben sollte der Absender haben
			const string subst{odatei.substr(pn+anstr.length(),posaf-pn-anstr.length())};
			einf.push_back(/*2*/instyp(My->DBS,"adressat",&subst));
		}
////		if (nachrnr<fxvp->size()) KLA
			const string oudatei{base_name(fx.npdf)};
			einf.push_back(/*2*/instyp(My->DBS,"origvu",&oudatei));
////		KLZ
		einf.push_back(/*2*/instyp(My->DBS,"wiemail",wiemail));
		// in fxvp:
		// in Datenbank: 
		// Prioritaet der Fax-Programme: 1=fbfax, 2=capi, 3=hyla per Konfigurationsdatei, 11=fbfax, 12=capi, 13=hyla, 14=vschlmail, 15=klarmail per Faxdateiname
//		if (fx.pprio>0 || (prios[2]>prios[1]&&obfa[2])/*hylazuerst*/) fx.pprio++;
////		caus<<rot<<"fx.pprio: "<<fx.pprio<<endl;
		if (!fx.pprio) {
			fx.pprio=priorang(1);
		}
////		caus<<rot<<"fx.pprio: "<<fx.pprio<<endl;
		einf.push_back(/*2*/instyp(My->DBS,"pprio",fx.pprio));
		einf.push_back(/*2*/instyp(My->DBS,"pages",fx.pseiten));
		einf.push_back(/*2*/instyp(My->DBS,"telnr",nix));
		RS rinsa(My,altspool); 
		rinsa.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB); // ,&spoolid);
		RS rinss(My,spooltab); 
		caus<<rot<<My->dbname<<schwarz<<endl;
		rinss.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/&spoolid);
		if (rinss.fnr) {
			fLog(Tx[T_Fehler_af]+drots+ltoan(rinss.fnr)+schwarz+Txk[T_bei]+tuerkis+rinss.sql+schwarz+": "+blau+rinss.fehler+schwarz,1,1);
		} //       if (runde==1)
		hLog(drots+"  Spool-ID: "+schwarz+spoolid);
} // void hhcl::fxinDatenbank

// aufgerufen in inspoolschreiben
// die frisch ins Warteverzeichnis verschobenen Dateien werden in spooltab eingetragen
void hhcl::telinDatenbank(const size_t aktc)
{
	hLog(violetts+Tx[T_WVZinDatenbank]+schwarz);
	for (uchar tr=0;tr<2;tr++) {
		char ***cerg;
		RS tellen(My,string("SELECT MAX(LENGTH(gettel3(")+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"','"+anffaxstr+"','"+anmailstr+"','"+klaranmailstr+"')))"
				" FROM `" +spooltab+"`",aktc,ZDB);
		while (cerg=tellen.HolZeile(),cerg?*cerg:0) {
			if (*(*cerg+0) && *(*(*cerg+0))) {
				My->tuerweitern(altspool,"telnr",atol(cjj(cerg,0)),aktc,ZDB);
				My->tuerweitern(spooltab,"telnr",atol(cjj(cerg,0)),aktc,ZDB);
			} //       if (*(*cerg+0))
			break;
		} //     while (cerg=tellen.HolZeile(),cerg?*cerg:0)
		// hier wird die Telefonnummer aus dem Namen extrahiert
		RS tea(My,"UPDATE `"+altspool+"` "
				"SET telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"','"+anffaxstr+"','"+anmailstr+"','"+klaranmailstr+"') "
				"WHERE telnr=''",aktc,ZDB);
		RS tel(My,"UPDATE `"+spooltab+"` "
				"SET telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"','"+anffaxstr+"','"+anmailstr+"','"+klaranmailstr+"') "
				"WHERE telnr=''",aktc,ZDB);
	} //   for (uchar tr=0;tr<2;tr++)
	hLog(violetts+Txk[T_Ende]+Tx[T_WVZinDatenbank]+schwarz);
} // telinDatenbank

// aufgerufen in: faxemitC
void hhcl::inDbc(DB *My, const string& spooltab, const string& altspool, const string& spoolg, const fsfcl *const fsfp, 
		const string& telnr, const size_t aktc)
{
	hLog(violetts+Tx[T_inDbc]+schwarz);
	string spooldir, spoolfil;
	spooldir=dir_name(spoolg);
	spoolfil=base_name(spoolg);
	uint affr{0};
	fLog(Tx[T_SpoolDateierstellt]+rots+spoolg+schwarz+"'",obverb,oblog);
	fLog(Tx[T_SpoolDatei]+rots+spoolfil+schwarz+"'",obverb,oblog);
	fLog(Tx[T_SpoolPfad]+rots+spooldir+schwarz+"'",obverb,oblog);
	struct stat entryspool{0};
	if (!lstat((spoolg.c_str()), &entryspool)) {
		vector<instyp> einf; // fuer alle Datenbankeinfuegungen
		einf.push_back(/*2*/instyp(My->DBS,"capispoolpfad",&spooldir));
		einf.push_back(/*2*/instyp(My->DBS,"capispooldt",&spoolfil));
		einf.push_back(/*2*/instyp(My->DBS,"cdateidatum",&entryspool.st_mtime));
		einf.push_back(/*2*/instyp(My->DBS,"cdateizeit",entryspool.st_mtime));
		einf.push_back(/*2*/instyp(My->DBS,"telnr",&telnr));
		if (!fsfp->idalt.empty()) {
			const string bedc{"id="+fsfp->idalt};
			RS rupd(My,altspool); 
			rupd.tbupd(einf,ZDB,bedc,aktc);
		} // 			if (!fsfp->idalt.empty())
		const string bedingung{"id="+fsfp->id};
		RS rupd(My,spooltab);
		rupd.tbupd(einf,ZDB,bedingung,aktc);
		affr=My->affrows(aktc);
		////			if (affr>0) break;
		if (rupd.fnr) {
			yLog(obverb,oblog,0,0,"%s%s%d%s%s%s%s%s%s%s%s%s",Tx[T_Fehler_af],drot,rupd.fnr,schwarz,Txk[T_bei],tuerkis,rupd.sql.c_str(),schwarz,": ",
					blau,rupd.fehler.c_str(),schwarz);
		} //       if (runde==1)
		yLog(obverb,oblog,1,1,"%s  affected_rows(%s%d%s): %s%d",drot,blau,aktc,drot,schwarz,affr);
	}   // if (!lstat((*spoolgp->c_str()), &entryspool)) 
} // inDbc

// aufgerufen in: wegfaxen
void hhcl::faxemitC(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& zfxdt)
{
	// 3. wartende Dateien bestimmen
	// 4. falls welche gefunden, capisuite pruefen
	// 5. faxen
	//      und wenn erfolgreich im spool, dann jeweils in Datenbank eintragen
	hLog(violetts+Tx[T_faxemitC]+schwarz);
	const size_t aktc{6};
	// 5. faxen und wenn erfolgreich im spool, dann in Datenbank eintragen
	if (fsfp->telnr.empty()) {
		fLog(Tx[T_DieFaxnrausTabelle]+tuerkiss+spooltab+schwarz+"`, id `"+tuerkis+fsfp->id+schwarz+"` "+
				drot+fsfp->spdf+schwarz+Tx[T_istleerfaxeesdahernicht],1,1);
	} else {
		hLog(Tx[T_DieFaxnrvon]+drots+fsfp->spdf+schwarz+Tx[T_ist]+blau+fsfp->telnr+schwarz);
		struct stat entryff{0};
		if (lstat(zfxdt.c_str(), &entryff)) {
			fLog(rots+Tx[T_faxemitCFehler]+schwarz+Tx[T_Faxdatei]+blau+zfxdt+rot+ Tx[T_fehlt]+schwarz,1,1);
			//// archiviere
		} else if (!entryff.st_size) {
			fLog(rots+Tx[T_faxemitCFehler]+schwarz+Tx[T_Faxdatei]+blau+zfxdt+rot+ Tx[T_hat0Bytes]+schwarz,1,1);
		} else {
			// capisuitefax mit Userangabe nur fuer root erlaubt
			this->nextnum();
			string csfpfad;
			const string cmd{"capisuitefax -n "+(cus.cuid?"":"-u"+this->cuser)+" -d "+fsfp->telnr+" \""+zfxdt+"\" 2>&1"};
			svec faxerg;
			systemrueck(cmd,1,1,&faxerg,/*obsudc=*/0,0,wahr,Tx[T_Faxbefehl],0,1);
			if (faxerg.size()) {
				const string tzs1{"uccessful enqueued as job "}, // muss sprachlich so falsch bleiben wie im python-Script
							tzs2{" for "};
				for(size_t fnr=0;fnr<faxerg.size();fnr++) {
					size_t p1,p2;
					if ((p1=faxerg[fnr].find(tzs1))!=string::npos) {
						p1+=tzs1.length();
						if ((p2=faxerg[fnr].find(tzs2,p1))!=string::npos) {
							stringstream sg;
							sg<<this->cfaxusersqvz<<vtz<<"fax-"<<setw(3)<<setfill('0')<<faxerg[fnr].substr(p1,p2-p1)<<".sff"<<setfill(' ');
							inDbc(My, spooltab, altspool, sg.str(), fsfp, faxerg[fnr].substr(p2+tzs2.length()), aktc);
						}
						break;
					} else if (!(p1=faxerg[fnr].find("can't open"))) {
						// Fax nicht in capisuite-spool gestellt, da Datei nicht zu oeffnen, also auch wieder aus Tabelle loeschen
						fLog(rots+Txk[T_datei]+blau+zfxdt+rot+"' (id: "+blau+fsfp->id+rot+
								Tx[T_nichtgefundenloeschesieausDB]+schwarz,1,1);
						RS rsloe(My,"DELETE FROM `"+spooltab+"` WHERE id = "+fsfp->id,aktc,ZDB);
						break;
					}
				}
			} else {
				cerr<<rot<<"capisuitefax "<<Txk[T_nicht_gefunden]<<schwarz<<endl;
			} // 	if (obprogda(prog,obverb,oblog,&csfpfad)) else
		} //     if (lstat(zfxdt.c_str(), &entryff))  else else
	} //   if (fsfp->telnr.empty())
} // faxemitC

void hhcl::inDBk(DB *My, const string& spooltab, const string& altspool, const fsfcl *const fsfp, const size_t aktc)
{
	uint affr{0};
	hLog(violetts+Tx[T_inDBk]+schwarz);
	vector<instyp> einf; // fuer alle Datenbankeinfuegungen
	einf.push_back(/*2*/instyp(My->DBS,"mailgesandt",1));
	const string bedingung{"id="+fsfp->id};
	RS rupd(My,spooltab); 
	rupd.tbupd(einf,ZDB,bedingung,aktc);
	affr=My->affrows(aktc);
	//			if (affr>0) break;
	if (rupd.fnr) {
		fLog(Tx[T_Fehler_af]+drots+ltoan(rupd.fnr)+schwarz+Txk[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,this->oblog);
	} //       if (runde==1)
	yLog(this->obverb,this->oblog,1,1,"%s%s%s%d%s%s%s%d",drot,"  affected_rows(",blau,aktc,drot,"): ",schwarz,affr);
}

// aufgerufen in faxemitF
void hhcl::inDBf(DB *My, const string& spooltab, const string& altspool, const string& fbvwdt,const fsfcl *const fsfp,const size_t aktc)
{
	hLog(violetts+Tx[T_inDBf]+schwarz);
////	int altobverb{obverb}; obverb=2;
	const size_t p1=fbvwdt.rfind('/'), p2=fbvwdt.rfind('.');
	uint affr{0};
	if (p1!=string::npos && p2!=string::npos) {
		const string fbid=fbvwdt.substr(p1+1,p2-p1-1);
		hLog(Tx[T_SpoolPfad]+rots+fbvwdt+schwarz+"'");
		struct stat vwst{0};
		if (!lstat(fbvwdt.c_str(), &vwst)) {
			vector<instyp> einf; // fuer alle Datenbankeinfuegungen
			einf.push_back(/*2*/instyp(My->DBS,"fbspooldt",fbid));
			einf.push_back(/*2*/instyp(My->DBS,"telnr",fsfp->telnr));
			if (!fsfp->idalt.empty()) {
				const string bedf{"id="+fsfp->idalt};
				RS rupd(My,altspool); 
				rupd.tbupd(einf,ZDB,bedf,aktc);
			}
			const string bedingung{"id="+fsfp->id};
			RS rupd(My,spooltab); 
			rupd.tbupd(einf,ZDB,bedingung,aktc);
			affr=My->affrows(aktc);
			//			if (affr>0) break;
			if (rupd.fnr) {
				fLog(Tx[T_Fehler_af]+drots+ltoan(rupd.fnr)+schwarz+Txk[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,this->oblog);
			} //       if (runde==1)
			yLog(this->obverb,this->oblog,1,1,"%s%s%s%d%s%s%s%d",drot,"  affected_rows(",blau,aktc,drot,"): ",schwarz,affr);
		} else {
			fLog(drots+Tx[T_SpoolDatei]+fbvwdt+Tx[T_nicht_gefunden_kein_Datenbankeintrag],1,1);
		}   // if (!lstat((*spoolgp->c_str()), &entryspool)) 
	}
////	obverb=altobverb;
}

// aufgerufen in faxemitH
void hhcl::inDBh(DB *My, const string& spooltab, const string& altspool, const string& hylaid, 
		const fsfcl *const fsfp,const string *const tel, const size_t aktc)
{
	hLog(violetts+Tx[T_inDBh]+schwarz);
	const string spoolfil{"q"+hylaid},
				spoolg{this->hsendqvz+vtz+spoolfil};
	uint affr{0};
	hLog(Tx[T_SpoolDateierstellt]+rots+spoolg+schwarz+"'");
	hLog(Tx[T_SpoolDatei]+rots+spoolfil+schwarz+"'");
	hLog(Tx[T_SpoolPfad]+rots+this->hsendqvz+schwarz+"'");
	struct stat entryspool{0};
//	string spoolid;
	if (!lstat(spoolg.c_str(), &entryspool)) {
		vector<instyp> einf; // fuer alle Datenbankeinfuegungen
		einf.push_back(/*2*/instyp(My->DBS,"hylanr",hylaid));
		einf.push_back(/*2*/instyp(My->DBS,"hdateidatum",&entryspool.st_mtime));
		einf.push_back(/*2*/instyp(My->DBS,"hdateizeit",entryspool.st_mtime));
		einf.push_back(/*2*/instyp(My->DBS,"telnr",tel));
		if (!fsfp->idalt.empty()) {
			const string bedh{"id="+fsfp->idalt};
			RS rupd(My,altspool); 
			rupd.tbupd(einf,ZDB,bedh,aktc);
		}
		const string bedingung{"id="+fsfp->id};
		RS rupd(My,spooltab); 
		rupd.tbupd(einf,ZDB,bedingung,aktc);
		affr=My->affrows(aktc);
		//			if (affr>0) break;
		if (rupd.fnr) {
			fLog(Tx[T_Fehler_af]+drots+ltoan(rupd.fnr)+schwarz+Txk[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,this->oblog);
		} //       if (runde==1)
		yLog(this->obverb,this->oblog,1,1,"%s%s%s%d%s%s%s%d",drot,"  affected_rows(",blau,aktc,drot,"): ",schwarz,affr);
	} else {
		fLog(drots+Tx[T_SpoolDatei]+spoolg+Tx[T_nicht_gefunden_kein_Datenbankeintrag],1,1);
	}   // if (!lstat((*spoolgp->c_str()), &entryspool)) 
} // inDBh


void hhcl::vschlmail(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& zfxdt)
{
} // void hhcl::vschlmail

void hhcl::klarmail(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& zfxdt)
{
	const size_t aktc{9};
	string postfix;
	if (!obprogda("postfix",obverb,oblog,&postfix)) {
		linstp->doinst("postfix",1+obverb,oblog);
	}
	if (obprogda("postfix",obverb,oblog,&postfix)) {
		caus<<rot<<"postfix: "<<blau<<postfix<<schwarz<<endl;
	}
// echo "This is the message body and contains the message" | mailx -v -r "gschade@dachau-mail.de" -s "This is the subject"  -S smtp="mail.mnet-online.de:587" -S smtp-use-starttls -S smtp-auth=login -S smtp-auth-user="gschade@dachau-mail.de" -S smtp-auth-password="..." -S ssl-verify=ignore -a untersch gerald.schade@gmx.de
	cmd="echo \""+mailbod+"\"|mailx -r \""+mailvon+"\" -s \""+mailtit+"\" -S smtp=\""+smtpadr+":"+portnr+"\" -S smtp-use-starttls -S smtp-auth=login -S smtp-auth-user=\""+smtpusr+"\" -S smtp-auth-password=\""+smtppwd+"\" "
			" -S ssl-verify=ignore -a \""+zfxdt+"\" \""+fsfp->telnr+"\"";
	svec rueck;
	if (systemrueck(cmd,1,1,&rueck)) {
		caus<<"klarmail ging nicht!"<<endl;
	} else {
		caus<<"klarmail ging!"<<endl;
		inDBk(My, spooltab, altspool, fsfp, aktc);
		// archiviere;
	}
} // void hhcl::klarmail

// aufgerufen in: wegfaxen
void hhcl::faxemitF(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& zfxdt)
{
////	int altobverb{obverb}; obverb=2;
	hLog(violetts+Tx[T_faxemitF]+schwarz);
	const size_t aktc{8};
	if (fsfp->telnr.empty()) {
		fLog(Tx[T_DieFaxnrausTabelle]+tuerkiss+spooltab+schwarz+"`, id `"+tuerkis+fsfp->id+schwarz+"` "+
				drot+fsfp->spdf+schwarz+Tx[T_istleerfaxeesdahernicht],1,1);
	} else {
		hLog(Tx[T_DieFaxnrvon]+drots+fsfp->spdf+schwarz+Tx[T_ist]+blau+fsfp->telnr+schwarz);
		string fbfax;
		////    systemrueck(sudc+"sh -c 'which sendfax'",obverb,1,&rueck);
		if (obprogda("fbfax",obverb,oblog,&fbfax)) {
			const string cmd{fbfax+" -stu -nr -dt \""+zfxdt+"\" -an \""+fsfp->telnr+"\" 2>&1"};
			svec faxerg;
			//// <<rot<<"Achtung: faxemith: "<<endl<<schwarz<<cmd<<endl;
			if (!systemrueck(cmd,1,1,&faxerg,/*obsudc=*/0,0,wahr,Tx[T_FbfaxBefehl])) {
			if (faxerg.size()) {
//				fsfp.fbsdt=*faxerg;
				string fbsdt{faxerg[0]};
				gtrim(&fbsdt);
				inDBf(My, spooltab, altspool,fbsdt,fsfp,aktc);
			}
////					const string cmd{"grep -l \""+zfxdt+"\" $(sed -n '/wartevz/{s/.*\\=[[:space:]]*\\(.*\\)/\\1/;s/\"\\(.*\\)\"/\\1/p}' \""+verg[0]+"\")/*.vw"};
#ifdef umstaendlich
					const string cmd{"grep -l \""+zfxdt+"\" \""+wvz+"/*.vw\""};
					svec fxr;
					if (!systemrueck(cmd,obverb,oblog,&fxr,0,0,wahr)) {
						for(size_t i=0;i<fxr.size();i++) {
							fLog(string(Tx[T_RueckmlgZeile])+ltoan(i)+": "+fxr.at(i),obverb>0?obverb-1:0,oblog);
							inDBf(My, spooltab, altspool,fxr[i],fsfp,aktc);
							break;
						} // for(size_t i=0;i<fxr.size();i++)
					} // 				if (!systemrueck(cmd,obverb,oblog,&faxerg,0,0,wahr))
#endif
			} // if (!systemrueck(cmd,1,1,&faxerg,wahr,wahr,Tx[T_FbfaxBefehl]))
		} // if (rueck.size()) 
	} // tel.empty() else
////	obverb=altobverb;
} // void hhcl::faxemitF

// aufgerufen in: wegfaxen
void hhcl::faxemitH(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& zfxdt)
{
	// wenn in capi maxversuch ueberschritten, dann mit hylafax faxen und wenn erfolgreich im spool, dann in Datenbank aktualisieren
	// 3. wartende Dateien bestimmen
	hLog(violetts+Tx[T_faxemitH]+schwarz);
	const size_t aktc{7};
	// 5. faxen und wenn erfolgreich im spool, dann in Datenbank eintragen
	/*
	string tel;
	char* posa{strcasestr((char*)fsfp->spdf.c_str(),(char*)this->anfaxstr.c_str())};
	if (!posa) if (!this->ancfaxstr.empty()) posa=strcasestr((char*)fsfp->spdf.c_str(),(char*)this->ancfaxstr.c_str());
	if (!posa) if (!this->anhfaxstr.empty()) posa=strcasestr((char*)fsfp->spdf.c_str(),(char*)this->anhfaxstr.c_str());
	if (posa) posa+=5;
	for(;posa;posa++){
		if (!*posa || *posa=='_') break; // '_' ist wegen Ausweichzielen mit Unterstrichen
		if (strchr("0123456789",*posa)) tel+=*posa;
		else if (*posa=='+') tel+=this->InternationalPrefix;
	} // 	for(;posa;posa++)
	*/
	if (fsfp->telnr.empty()) {
		fLog(Tx[T_DieFaxnrausTabelle]+tuerkiss+spooltab+schwarz+"`, id `"+tuerkis+fsfp->id+schwarz+"` "+
				drot+fsfp->spdf+schwarz+Tx[T_istleerfaxeesdahernicht],1,1);
	} else {
		hLog(Tx[T_DieFaxnrvon]+drots+fsfp->spdf+schwarz+Tx[T_ist]+blau+fsfp->telnr+schwarz);
		//// 27.3.16: Uebernacht wurden die Berechtigungen so eingeschraenkt, dass Faxsenden nicht mehr ging, evtl. durch faxqclean
		useruucp(this->huser,obverb,oblog);
		if (findv==1) {
			systemrueck("find "+this->varsphylavz+" -name seqf -exec chmod 660 {} \\;"" -exec chown "+this->huser+":uucp {} \\;",
					        obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
		} else {
			svec qrueck;
			findfile(&qrueck,findv,obverb,oblog,0,this->varsphylavz,/*muster=*/"/seqf$",-1,1,Fol_Dat);
			for(size_t i=0;i<qrueck.size();i++) {
				systemrueck("chmod 660 '"+qrueck[i]+"'",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
				systemrueck("chown "+this->huser+":uucp '"+qrueck[i]+"'",obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
			} // 			for(size_t i=0;i<qrueck.size();i++)
		} // 		if (findv==1)
		const char *const tz1{"request id is "}, 
					     *const tz2{" ("};
		string sendfax;
		////    systemrueck(sudc+"sh -c 'which sendfax'",obverb,1,&rueck);
		if (obprogda("sendfax",obverb,oblog,&sendfax)) {
			const string cmd{sendfax+" -n -A "+(isnumeric(this->maxhdials)?"-T "+this->maxhdials:"")+" -d "+fsfp->telnr+" \""+zfxdt+"\" 2>&1"};
			svec faxerg;
			//// <<rot<<"Achtung: faxemith: "<<endl<<schwarz<<cmd<<endl;
			if (!systemrueck(cmd,1,1,&faxerg,/*obsudc=*/0,0,wahr,Tx[T_HylafaxBefehl])) {
				for(size_t i=0;i<faxerg.size();i++) {
					fLog(string(Tx[T_RueckmlgZeile])+ltoan(i)+": "+faxerg.at(i),obverb>0?obverb-1:0,oblog);
					if (char *z1=strstr((char*)faxerg.at(i).c_str(),tz1)) {
						if (char *z2=strstr(z1,tz2)) {
							const string hylaid{z1+strlen(tz1),z2-z1-strlen(tz1)};
							if (isnumeric(hylaid)) {
								////            inDatenbankh(My, this->hsendqvz, &hylaid, idsp, npdfp, spdfp, nachrnr, &tel, obverb, oblog);
								inDBh(My, spooltab, altspool, hylaid, fsfp,&fsfp->telnr, aktc);
							} // if (isnumeric(hylaid)) 
						}   // if (char *z2=strstr(z1,tz2)) 
						break;
					} // if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1))
				} // string cmd=sendfax+" -n -A -d "+tel+" \""+zfxdt+"\" 2>&1";
			} // if (!systemrueck(cmd,1,1,&faxerg,wahr,wahr,Tx[T_HylafaxBefehl]))
		} // if (rueck.size()) 
	} // tel.empty() else
} // faxemitH

// uebersetzt den index auf anfaxstr in pprio
inline const int ppri(const int iprio)
{
	switch (iprio) {
		case 0: return 0;   // Prioritaet durch Programm festlegen
		case 1: return 11;  // fbfax
		case 2: return 12;  // capi
		case 3: return 13;  // hyla
		case 4: return 14;  // vschlmail
		case 5: return 15;  // klarmail
	}
	return -1;
}

// aufgerufen in: pvirtfuehraus
void hhcl::inspoolschreiben(const size_t aktc)
{
	// zufaxenvz = zufaxen-Verzeichnis
	// 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
	// 1b. die Nicht-PDF-Dateien in dem Verzeichnis zum PDF-Druck ermitteln, in Warteverzeichnis verschieben und in die PDF-Liste spdf eintragen ...
	// 2a. ... und in im Warteverzeichnis in PDF umwandeln, falls erfolgreich und gleichziel => auch in ziel kopieren
	// 2b. Die originalen PDF-Dateien ins Warteverzeichnis verschieben, falls erfolgreich, nicht schon registriert und gleichziel => auch in ziel kopieren
	// 3. in die Spool-Tabelle eintragen

	//// const int altobverb{obverb};
	hLog(violetts+Tx[T_inspoolschreiben]+schwarz+", "+blau+Tx[T_obfboxmitDoppelpunkt]+schwarz+(obfa[0]||obweg[0]==1?Txk[T_ja]:Txk[T_nein])+", "
			                                    +blau+Tx[T_obcapimitDoppelpunkt]+schwarz+(obfa[1]||obweg[1]==1?Txk[T_ja]:Txk[T_nein])+", "
			                                    +blau+Tx[T_obhylamitDoppelpunkt]+schwarz+(obfa[2]||obweg[2]==1?Txk[T_ja]:Txk[T_nein]));
	const string filter[]{"[[:space:][:punct:]]\\+[0-9][0-9[:space:][:punct:]]*[_]\\?.*\\.",// statt ?.* zuvor ?[0-9]*, aber vielleicht unnoetig
		"[[:blank:]]\\+[a-zA-Z0-9.!#$%&'\\''*+/=?^_`{|}~-]\\+@[a-zA-Z0-9]\\([a-zA-Z0-9-]\\{0,61\\}[a-zA-Z0-9]\\)\\?\\(\\.[a-zA-Z0-9]\\([a-zA-Z0-9-]\\{0,61\\}[a-zA-Z0-9]\\)\\?\\)*[_]\\?.*\\."
	};
	struct stat entrynpdf{0};
	////vector<string> npdf, spdf, *npdfp=&npdf, *spdfp=&spdf;  vector<uchar> prios;
	vector<fxfcl> fxv; // Faxvektor
	vector<string> anfxstrvec; // Trennstrings fuer Faxnummer/Mailadresse
	vector<int> filtnr; // zugehoerige Filternummer
	anfxstrvec.push_back(anfaxstr); filtnr.push_back(0);
	if (!anffaxstr.empty()) {anfxstrvec.push_back(anffaxstr);filtnr.push_back(0);}
	if (!ancfaxstr.empty()) {anfxstrvec.push_back(ancfaxstr);filtnr.push_back(0);}
	if (!anhfaxstr.empty()) {anfxstrvec.push_back(anhfaxstr);filtnr.push_back(0);}
	if (!anmailstr.empty()) {anfxstrvec.push_back(anmailstr);filtnr.push_back(1);}
	if (!klaranmailstr.empty()) {anfxstrvec.push_back(klaranmailstr);filtnr.push_back(1);}
	svec zfda,zfvz; // Zufaxen-Datei, Warteverzeichnis-Verzeichnis
	if (findv==1) {
		systemrueck(sudc+"find \""+zufaxenvz+"\" -maxdepth 1 -type f -not -name \"*\\`*.nix\"",obverb,oblog,&zfda,/*obsudc*/0,/*verbergen*/0,/*obergebnisanzeig*/wahr,/*ueberschr*/string(),/*errm*/0,/*obincron*/0,/*ausp*/0,/*obdirekt*/0,/*ohnewisch*/1);
	} else findfile(&zfda,findv,obverb,oblog,/*anteil=*/0,zufaxenvz,/*muster=*/"^[^`]*$",/*tiefe=*/1,/*typbit=*/B_Datei,/*folge=*/Fol_Dat);
	// Unterverzeichnisse für Faxe mit Zeitsteuerung suchen
	if (findv==1) {
		systemrueck(sudc+"find \""+zufaxenvz+"\" -maxdepth 1 -type d",obverb,oblog,&zfvz,/*obsudc*/0,/*verbergen*/0,/*obergebnisanzeig*/wahr,/*ueberschr*/string(),/*errm*/0,/*obincron*/0,/*ausp*/0,/*obdirekt*/0,/*ohnewisch*/1);
	} else findfile(&zfvz,findv,obverb,oblog,/*anteil=*/0,zufaxenvz,/*muster=*/"",/*tiefe=*/1,/*typbit=*/B_Verzn,/*folge=*/Fol_Dat);
	for(size_t iakt=0;iakt<zfvz.size();iakt++) {
		if (zfvz[iakt]!=zufaxenvz) {
			const string uvz{base_name(zfvz[iakt])};
			uchar auchtag{0};
			if (obvorbei(uvz,&auchtag)) {
				svec zfuda; // Zufaxen-Datei im Unterverzeichnis
				// Dateien im Unterverzeichnis suchen
				if (findv==1) {
					systemrueck(sudc+"find \""+zfvz[iakt]+"\" -maxdepth 1 -type f -not -name \"*\\`*.nix\"",obverb,oblog,&zfuda);
				} else findfile(&zfuda,findv,obverb,oblog,/*anteil=*/0,zfvz[iakt],/*muster=*/"^[^`]*$",/*tiefe=*/1,/*typbit=*/B_Datei,/*folge=*/Fol_Dat,0,0,0,0,0,1);
				// wenn Datum oder Uhrzeit schon vorbei ist, dann beinhaltete Fax-Datein verarbeiten
				for(size_t iiru=0;iiru<zfuda.size();iiru++) {
					zfda<<zfuda[iiru];
				} // 				for(size_t iiru=0;iiru<zfuda.size();iiru++)
				// wenn Verzeichnis Datum enthielt, schon vorbei ist und leer ist, dann loeschen
				if (auchtag && !zfuda.size()) {
					// wenn wirklich gar nichts drin ist
					if (!systemrueck(sudc+"find \""+zfvz[iakt]+"\" -mindepth 1 -ls -quit",obverb,oblog)) {
						tuloeschen(zfvz[iakt],"",1,oblog);
					}
				} // 				if (!auchtag && !zfuda.size())
			} // 			if (obvorbei(uvz,&auchtag))
		} // 		if (zfvz[iakt]!=zufaxenvz)
	} // 	for(size_t iakt=0;iakt<zfvz.size();iakt++)
	
/*//	
#ifdef alt
	zielmustercl mu[anfxstrvec.size()];
#endif
*/
	// 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
	for(uchar iprio=anfxstrvec.size()-1;; iprio--) {
		if (!anfxstrvec[iprio].empty()) {
			/*//			
#ifdef alt
			// der regex-flavor posix_basic (ed) erlaubt keinen Abzug aus 
			const string mstr=anfxstrvec.at(iprio)+filter+".*"; // z.B. "an Fax +49"
			if (mu[iprio].setzemuster(mstr,0)) {
			fLog(Tx[T_Fehler_beim_Analysieren_des_Musters]+mstr,1,1);
			continue;
			} // 		if (mu[iprio].setzemuster(mstr,0))
#endif
			 */
			// der Reihe nach nach Dateien suchen, die das jeweilige Trennzeichen enthalten
			for(size_t iakt=0;iakt<zfda.size();iakt++) {
				if (!zfda.at(iakt).empty()) {
					string stamm,exten,vor;
					const string urname{zfda[iakt]};
					getstammext(&(zfda.at(iakt)),&stamm,&exten);
					fLog(string(Tx[T_Endung])+tuerkis+exten+schwarz,obverb>1,oblog);
					fLog(string(Tx[T_Stamm])+tuerkis+stamm+schwarz,obverb>1,oblog);
					svec toktxt/*Spaltung an anstr*/, tokname/*Spaltung an undstr*/, toknr/*Spaltung an undstr*/;
					// 5) Zahl der Faxe = max(3,4)
					// 6) Suche fehlender Faxnummern

					// Datei ist faxbar, wenn mindestens eine Faxnr gefunden. 
					// 1) Aufteilung in 1a) alles vor dem ersten anFaxString und 1b) alles nach dem letzten anFaxString
					aufiSplit(&toktxt,stamm,anfxstrvec[iprio],/*nichtmehrfach=*/0,obverb,oblog,1);
					if (toktxt.size()>1||(!iprio&&toktxt.size())) {
						size_t p1;
						// 2) Aufteilung von 1a) in 2a) alles vor dem und 2b) alles nach dem letzten anString
						if ((p1=irfind(toktxt[0],anstr))!=string::npos) {
							vor=toktxt[0].substr(0,p1);
							const string nach{toktxt[0].substr(p1+undstr.length())};
							// 3) Aufteilung von 2b) an jedem undString
							aufiSplit(&tokname,nach,undstr,/*nichtmehrfach=*/1,obverb,oblog);
						} else {
							vor=toktxt[0];
						}
						gtrim(&vor);
						hLog(Tx[T_Anfangsteil]+blaus+vor+schwarz);
						if (toktxt.size()>1) { 
							// 4) Aufteilung von 1b) an jedem undString
							aufiSplit(&toknr,toktxt[toktxt.size()-1],undstr,/*nichtmehrfach=*/1,obverb,oblog);
						} // 						if (toktxt.size()>1)
						for(size_t i=0;i<toknr.size();i++) {
							string neunr;
							if (strchr(toknr[i].c_str(),'@')) { // Mail
								for(size_t p=toknr[i].length()-1;p;--p) {
									if (toknr[i][p]=='@') break;
									if (toknr[i][p]=='_') {
										toknr[i].erase(p); // wenn '_', dann ab da streichen
										break; // dann Schleife beenden
									}
								}
								while(toknr[i].length()&&(toknr[i][0]==' '||toknr[i][0]==9)) {
                 toknr[i].erase(0,1); 
								}
							} else { //Fax
								for(size_t p=0;p<toknr[i].length();p++) {
									if (toknr[i][p]=='+') neunr+="00";
									else if (strchr("0123456789",toknr[i][p])) neunr+=toknr[i][p];
									else if (toknr[i][p]=='_') break;
								}
								toknr[i]=neunr;
							}
						} // 						for(size_t i=0;i<toknr.size();i++)
						for(size_t i=0;i<tokname.size();i++) gtrim(&tokname[i]);
						for(size_t i=toknr.size();i<tokname.size();i++) toknr<<""; // Fehlende auffuellen
						for(size_t i=tokname.size();i<toknr.size();i++) tokname<<""; // ... oder umgekehrt
						for(size_t j=0;j<toknr.size();j++) {
							if (toknr[j].empty() && !tokname[j].empty()) {
								string tn; // Leerzeichen, auch in der Mitte, entfernen
								for(string::iterator k=tokname[j].begin();k<tokname[j].end();k++) if (*k!=' ') tn+=*k;
								char ***cerg;
								RS rs(My,"SELECT COUNT(DISTINCT o.rcfax),COUNT(o.rcfax), o.rcfax FROM outa o "
										"INNER JOIN "
										"(SELECT eind FROM outa WHERE REPLACE(adressat,' ','') = '"+tn+"' AND erfolg=1 ORDER BY eind DESC LIMIT 7) o2 "
										"ON o.eind=o2.eind "
										"WHERE REPLACE(adressat,' ','') = '"+tn+"'",aktc,ZDB);
								if (!rs.obqueryfehler) {
									while (cerg=rs.HolZeile(),cerg?*cerg:0) {
										if (*(*cerg+0)) if (!strcmp(*(*cerg+0),"1")) if (*(*cerg+2)) { 
											toknr[j]=*(*cerg+2);
											fLog(Tx[T_Faxnummer_zu]+blaus+tokname[j]+schwarz+Tx[T_gefunden_dp]+gruen+*(*cerg+2)+schwarz,1,oblog);
										} // 							if (*(*cerg+0)) if (!strcmp(*(*cerg+0),"1")) if (*(*cerg+2))
									} // 						while (cerg=rs.HolZeile(),cerg?*cerg:0)
								} // 					if (!rs.obqueryfehler)
							} else if (!toknr[j].empty() && tokname[j].empty()) {
								char ***cerg;
								RS rs(My,"SELECT COUNT(DISTINCT o.adressat),COUNT(o.adressat), o.adressat FROM outa o "
										"INNER JOIN "
										"(SELECT eind FROM outa WHERE REPLACE(REPLACE(rcfax,' ',''),'+','00')='"+stdfaxnr(toknr[j])+"' "
										"   AND erfolg=1 AND ADRESSAT<>'' ORDER BY eind DESC LIMIT 7) o2 "
										"ON o.eind=o2.eind "
										"WHERE REPLACE(REPLACE(rcfax,' ',''),'+','00') = '"+stdfaxnr(toknr[j])+"'",aktc,ZDB);
								if (!rs.obqueryfehler) {
									while (cerg=rs.HolZeile(),cerg?*cerg:0) {
										if (*(*cerg+0)) if (!strcmp(*(*cerg+0),"1")) if (*(*cerg+2)) { 
											tokname[j]=*(*cerg+2);
											fLog(Tx[T_Name_zu]+blaus+toknr[j]+schwarz+Tx[T_gefunden_dp]+gruen+*(*cerg+2)+schwarz,1,oblog);
										} // 							if (*(*cerg+0)) if (!strcmp(*(*cerg+0),"1")) if (*(*cerg+2))
									} // 						while (cerg=rs.HolZeile(),cerg?*cerg:0)
								} // 					if (!rs.obqueryfehler)
							} // 							if (toknr[j].empty() && !tokname[j].empty()) elseif umgekehrt
						} // 						for(size_t j=0;j<toknr.size();j++)
						fLog(Tx[T_Bearbeite]+rots+zfda[iakt]+schwarz,1,oblog);
						hLog(rots+"toktxt:"); 
						for(uint j=0;j<toktxt.size();j++) 
							yLog(obverb,oblog,0,0," %s%u%s) %s%s%s",blau,j,schwarz,blau,toktxt[j].c_str(),schwarz);
						hLog(rots+"toknr:"); 
						for(uint j=0;j<toknr.size();j++) 
							yLog(obverb,oblog,0,0," %s%u%s) %s%s%s",blau,j,schwarz,blau,toknr[j].c_str(),schwarz);
						hLog(rots+"tokname:"); 
						for(uint j=0;j<tokname.size();j++) 
							yLog(obverb,oblog,0,0, "%s%u%s) %s%s%s",blau,j,schwarz,blau,tokname[j].c_str(),schwarz);
						if (toknr.size()) {
							string benstr;
							for(unsigned j=0;j<toknr.size();j++) { 
								if (!toknr[j].empty()) {
									string kopier,*zielp;
									if (benstr.empty()) zielp=&benstr; else zielp=&kopier;
									*zielp=vor+(tokname[j].empty()?" ":anstr+tokname[j]+" ")+anfxstrvec[iprio]+" "+toknr[j]+'.'+exten;
									fLog("toknr["+blaus+ltoan(j)+"]:"+tuerkis+toknr[j]+schwarz,(obverb>0?obverb-1:obverb),oblog);
									uint kfehler{0};
									// die erste Zieldatei
									if (zielp==&benstr) {
										if (zfda[iakt]!=benstr) {
											uint vfehler{0};
											dorename((zfda[iakt]),benstr,cuser,&vfehler,/*schonda*/!dateivgl(zfda[iakt],benstr),obverb,oblog);
											if (vfehler) {
												fLog(rots+Tx[T_FehlerbeimUmbenennen]+": "+ltoan(vfehler)+schwarz+"("+zfda[iakt]+" -> "+benstr+")",1,1);
												continue;
											}
											fLog(Tx[T_ErstelledurchBenennen]+rots+benstr+schwarz,1,oblog);
										} // if (zfda[iakt]!=tmp) 

										// alle weiteren
									} else {
										const string kopiert{kopiere(benstr,kopier,&kfehler,/*wieweiterzaehl=*/1)};
										if (kfehler) {
											fLog(rots+Tx[T_Fehler_beim_Kopieren]+ltoan(kfehler)+schwarz+"("+benstr+" -> "+kopier+")",1,1);
											continue;
										}
										fLog(Tx[T_ErstelledurchKopieren]+rots+kopier+schwarz,1,oblog);
									} // 									if (zielp==&benstr)
									zfda[iakt].clear(); // Datei bei Gebrauch aus dem Vektor zfda loeschen, um dann die Restlichen zu sehen
									urfxcl urfx(*zielp,urname,ppri(iprio));
									// 1b. die Nicht-PDF-Dateien in dem Verzeichnis zum PDF-Druck ermitteln, 
									//    in Warteverzeichnis verschieben und in die PDF-Liste spdfp eintragen ...
									while (1) { // nur 1x
										uint vfehler{0};
										// wenn die Datei im zufaxenvz in einen Namenskonflikt geriete ...
										const string ndname{zufaxenvz+vtz+neuerdateiname(urfx.teil)};
										if (ndname!=urfx.teil) {
											dorename(urfx.teil,ndname,cuser,&vfehler,/*schonda=*/!dateivgl(urfx.teil,ndname),obverb,oblog);
											if (vfehler) {
												cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
													blau<<urfx.teil<<schwarz<<" ->\n"<<
													blau<<ndname<<schwarz<<endl;
												break; // while (1)
											} // if (vfehler) 
											fLog(Tx[T_ErstelledurchBenennen]+rots+ndname+schwarz,1,oblog);
											urfx.teil=ndname;
										} // if (ndname!=urfx.teil) 
										string wartedatei{verschiebe<string>(urfx.teil,wvz,cuser,&vfehler,/*wieweiterzaehl=*/1,obverb,oblog)};
										if (vfehler) {
											cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
												blau<<urfx.teil<<schwarz<<" ->\n"<<
												blau<<wvz<<schwarz<<endl;
												break; // while (1)
										} //     if (vfehler)
										// hier gaebe es also weder beim Kopieren ins zufaxenverzeichnis noch beim Verschieben ins Warteververzeichnis ein Problem
										string stamm,exten;
										////          npdfp->push_back(wartedatei);
										getstammext(&wartedatei,&stamm,&exten);
										const string wartepdf{stamm+".pdf"};
										if (!strcasecmp(exten.c_str(),"pdf")) wartedatei.clear();
////										fxv.push_back(fxfcl(wartedatei,wartepdf,urfx.ur,urfx.pprio));
	// 2a. ... und im Warteverzeichnis in PDF umwandeln, falls erfolgreich und gleichziel => auch in ziel kopieren
										fxfcl fx(wartedatei,wartepdf,urfx.ur,urfx.pprio);
										while (1) { // nur 1x
											int nfehlt{1},zupdffehler{0};
											if (!fx.npdf.empty()) {
												if ((nfehlt=lstat((fx.npdf.c_str()), &entrynpdf))) {
													fLog(Tx[T_lstatfehlgeschlagen]+rots+strerror(errno)+schwarz+Tx[T_beiDatei]+ fx.npdf,1,1,1);
													break;
												} else {
													zupdffehler=zupdf(&fx.npdf, fx.spdf, &fx.pseiten, obocra, 0); // 0=erfolg
												}
											} // 	  if (!fx.npdf.empty())
											if (zupdffehler||(!fx.npdf.empty()&&lstat((fx.npdf.c_str()),&entrynpdf))) {
												// Misserfolg, zurueckverschieben und aus der Datenbank loeschen
												uint wfehler{0};
												//// <<violett<<"fxv["<<(int)nachrnr<<"].npdf: "<<fx.npdf<<schwarz<<endl;
												//// <<violett<<"fxv["<<(int)nachrnr<<"].spdf: "<<fx.spdf<<schwarz<<endl;
												struct stat npdfstat{0};
												if (!lstat(fx.npdf.c_str(), &npdfstat)) {
													string fxneu{verschiebe<string>(fx.npdf,zufaxenvz,cuser,&wfehler,/*wieweiterzaehl=*/1,obverb,oblog)};
												}
												struct stat spdfstat{0};
												if (!lstat(fx.spdf.c_str(), &spdfstat)) {
													string fxneu2{verschiebe<string>(fx.spdf,zufaxenvz,cuser,&wfehler,/*wieweiterzaehl=*/1,obverb,oblog)};
												}
////												fxv.erase(fxv.begin()+nachrnr);
											} else {
												// Erfolg
												if (gleichziel) {
													uint kfehler{0};
													benstr=kopiere(fx.spdf, zmsp, &kfehler, /*wieweiterzaehl=*/1, obverb, oblog);
													if (!nfehlt) benstr=kopiere(fx.npdf, zmsp, &kfehler, /*wieweiterzaehl=*/1, obverb, oblog);
												} // if (gleichziel)
												fxv.push_back(fx);
												// 3) in spooltab eintragen
												fxinDatenbank(fx,aktc);
											} // 	  if (lstat((fx.npdf.c_str()), &entrynpdf)) else
											break;
										}
										break; // while (1)
									} // while (1)
								} // 	 if (!toknr[j].empty())
							} // for(unsigned j=0;j<toknr.size();j++) 
						} // 						if (toknr.size())
					} // 					if (toktxt.size()>1||(!iprio&&toktxt.size()))
				} // 			if (!zfda.at(iakt) 
			} // for(size_t iakt=0;iakt<zfda.size();iakt++)
		} // 	  if (!:anfxstrvec[iprio]vec[iprio].empty())
		if (!iprio) break;
	} // 	for(uchar iprio=anfxstrvec[iprio]vec.size()-1;; iprio--)

	// nicht faxbare
	for(size_t i=0;i<zfda.size();i++) {
		if (!zfda[i].empty()) {
			touch(zmsp[0]->ziel+vtz+Tx[T_nichtfaxbar]+" `"+base_name(zfda[i])+"`.nix",obverb,oblog);
		}
	} // 	for(size_t i=0;i<iprid.size();i++) 

	hLog(blaus+Tx[T_Gesammelt_wurden]+schwarz);
	for(unsigned i=0;i<fxv.size();i++) {
		hLog("npdf["+rots+ltoan(i)+schwarz+"]: "+rot+fxv[i].npdf+schwarz);
		hLog("spdf["+rots+ltoan(i)+schwarz+"]: "+rot+fxv[i].spdf+schwarz);
		yLog(obverb,oblog,0,0,"prio[%s%u%s]: %s%d%s",rot,i,schwarz,rot,fxv[i].pprio,schwarz);
	} // for(unsigned i=0;i<fxv.size();i++)
	// zufaxenvz = zufaxen-Verzeichnis
	fLog(Tx[T_aus]+drots+zufaxenvz+schwarz+vtz+Tx[T_verarbeitete_Nicht_PDF_Dateien]+drot+ltoan(fxv.size())+schwarz,1,1);
	////  geszahl+=npdfp->size(); // 1b


	// 2b. Die originalen PDF-Dateien ins Warteverzeichnis verschieben, falls erfolgreich, nicht schon registriert und gleichziel 
	//      => auch in ziel kopieren
	for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) {
		if (!anfxstrvec.at(iprio).empty()) {
			svec zfda;
			const string reg{".*"+anfxstrvec.at(iprio)+filter[filtnr[iprio]]+"pdf"};
			if (findv==1) {
				cmd=sudc+"find \""+zufaxenvz+"\" -maxdepth 1 -type f -regextype ed -iregex '"+reg+"'";
				//			    " [- ,/;:\\\\\\.\\+]*[0-9][- ,/;:\\\\\\.\\+0-9]*[_]*[0-9]*[\\.]{0,1}pdf*$\" -iname \"*.pdf\"";
				systemrueck(cmd,obverb, oblog, &zfda);
			} else findfile(&zfda,findv,obverb,oblog,0,zufaxenvz,/*muster=*/reg,1,1,Fol_Dat,0,0,1,0,1);
			for(size_t i=0;i<zfda.size();i++) {
				if (obocra) {
					struct stat spdfstat{0};
					if (!lstat(zfda.at(i).c_str(),&spdfstat)) {
						struct utimbuf ubuf{0};
						ubuf.actime=ubuf.modtime=spdfstat.st_mtime;
						if (!pruefocr()) {
							setfaclggf(zfda.at(i),obverb>0?obverb-1:0,oblog,/*obunter=*/falsch,/*mod=*/7,/*obimmer=*/falsch,/*faclbak=*/0);
							const string cmd{string(ocrmp+" -rcsl ")+(langu=="d"?"deu":"eng")+" \""+zfda.at(i)+"\" \""+zfda.at(i)+"\""
								" && chmod +r \""+zfda.at(i)+"\" 2>/dev/null"};
							int zerg{systemrueck(cmd,obverb,oblog)};
							svec rueck;
							if (zerg==5) zerg=systemrueck(sudc+cmd,obverb,oblog,&rueck); // kein Schreibrecht im Verzeichnis
							if (zerg) {
								cout<<"Fehler "<<blau<<zerg<<schwarz<<" bei: "<<blau<<cmd<<schwarz<<endl;
								for (size_t zei=0;zei<rueck.size();zei++) cout<<rot<<rueck[zei]<<schwarz<<endl;
							} // if (zerg)
						} //						if (!pruefocr())
						utime(zfda.at(i).c_str(),&ubuf);
					} // if (!lstat(zfda.at(i).c_str(),&spdfstat)) 
				} // if (obocra) 
				const string ndname{zufaxenvz+vtz+neuerdateiname(zfda.at(i))};
				uint vfehler{0};
				if (ndname!=zfda.at(i)) {
					dorename(zfda.at(i),ndname,cuser,&vfehler,/*schonda=*/!dateivgl(zfda.at(i),ndname),obverb,oblog);
					if (vfehler) {
						continue;
					} // if (vfehler) 
					////            zfda.at(i)=ndname;
				} // if (ndname!=zfda.at(i))
				const string wartedatei{verschiebe<string>(ndname,wvz,cuser,&vfehler,/*wieweiterzaehl=*/1,obverb,oblog)};
				if (vfehler) {
					continue; 
				}
				uchar vorhanden{0}; // 1= Datei schon zuvor als nicht-PDF-Datei eingetragen
				for(size_t ii=0;ii<fxv.size()&&ii<zfda.size();ii++) {
					if (fxv[ii].spdf==ndname) {vorhanden=1;break;} 
				}
				if (!vorhanden) {
					fxfcl fx(wartedatei,zfda.at(i),ppri(iprio));
					// 3) in spooltab eintragen
					fxinDatenbank(fx,aktc);
					fxv.push_back(fx);
					if (gleichziel) {
						uint kfehler{0};
						/*string zield=*/kopiere(wartedatei, zmsp, &kfehler, /*wieweiterzaehl=*/1, obverb, oblog);
					} //  if (gleichziel)
				} //if (!vorhanden)
			} // for(size_t i=0
		} // if (!anfxstrvec.at(iprio).empty()) 
	} // for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) 
	for(unsigned i=0;i<fxv.size();i++) {
		hLog("npdf["+rots+ltoan(i)+schwarz+"]: "+rot+fxv[i].npdf+schwarz);
		hLog("spdf["+rots+ltoan(i)+schwarz+"]: "+rot+fxv[i].spdf+schwarz);
		hLog("prio:       "+rots+ltoan(fxv[i].pprio)+schwarz);
		hLog("pseiten:    "+rots+ltoan(fxv[i].pseiten)+schwarz);
	} //   for(unsigned i=0;i<fxv.size();i++)

	geszahl=fxv.size();
	fLog(Tx[T_aus]+drots+zufaxenvz+schwarz+vtz+Tx[T_verarbeitete_PDF_Dateien]+drot+ltoan(geszahl)+schwarz,1,1);

	telinDatenbank(aktc);
} // void hhcl::inspoolschreiben

// aufgerufen in: pvirtfuehraus
void hhcl::wegfaxen(const size_t aktc)
{
////	const int altobverb{obverb};
	hLog(violetts+Tx[T_wegfaxen]+schwarz+", "
			+blau+Tx[T_obfboxmitDoppelpunkt]+schwarz+(obfa[0]||obweg[0]==1?Txk[T_ja]:Txk[T_nein])+"; "
			+blau+Tx[T_obcapimitDoppelpunkt]+schwarz+(obfa[1]||obweg[1]==1?Txk[T_ja]:Txk[T_nein])+": "
			+blau+Tx[T_obhylamitDoppelpunkt]+schwarz+(obfa[2]||obweg[2]==1?Txk[T_ja]:Txk[T_nein]));
	// 4. Dateien aus der Spool-Tabelle aufrufen zum Abarbeiten mit der Wegschick-Funktion
	vector<fsfcl> fsfv;
	char ***cerg;
	ulong dbszahl{0}; // Zahl der Datenbanksaetze
	//  const string hzstr=ltoan(hylazuerst);
	if (!isnumeric(maxhylav)) maxhylav="3";
	if (!isnumeric(maxcapiv)) maxcapiv="3";
	if (!isnumeric(maxfbfxv)) maxfbfxv="3";
	// 4. Dateien aus der Spool-Tabelle aufrufen zum Abarbeiten mit der Wegschick-Funktion
	const string prio1{ltoan(priorang(1))},
	             prio2{ltoan(priorang(2))},
	             prio3{ltoan(priorang(3))},
							 obfa0{ltoan(obfa[0]||obweg[0]==1)},
							 obfa1{ltoan(obfa[1]||obweg[1]==1)},
							 obfa2{ltoan(obfa[2]||obweg[2]==1)};

	// Ermittle die in spool eingetragenen, noch an Faxsysteme zu verschickenden Faxe
	RS r0(My,"SELECT * FROM (SELECT s.id p0, s.origvu p1, s.original p2, s.telnr p3, s.pprio p4, s.capispooldt p5, s.capidials p6, "
			"s.hylanr p7, s.hyladials p8, \n"

			"("+obfa0+"=1 AND s.fbspooldt='' AND "
			"((("+prio1+"=1 AND s.capispooldt='' AND s.hylanr=0 AND (s.pprio <=3 OR (s.pprio=12 AND "+obfa1+"=0) OR (s.pprio=13 AND "+obfa2+"=0))) OR"+
			"  (                s.capispooldt='' AND s.hylanr=0 AND s.pprio=11) OR"+
			"  ("+prio2+"=1 AND ((s.capispooldt<>'' AND (s.capidials>="+maxcapiv+" OR s.capidials=-1)) OR (s.hylanr<>'' AND (s.hyladials>="+maxhylav+" OR s.hylastate=8)))) OR "
			"  ("+prio3+"=1 AND ((s.capispooldt<>'' AND (s.capidials>="+maxcapiv+" OR s.capidials=-1)) AND s.hylanr<>'' AND (s.hyladials>="+maxhylav+" OR s.hylastate=8))))"
			" OR s.allewege=1)"
			") p9, \n"

			"("+obfa1+"=1 AND s.capispooldt='' AND "
			"((("+prio1+"=2 AND s.fbspooldt='' AND s.hylanr=0 AND (s.pprio <=3 OR (s.pprio=11 AND "+obfa0+"=0) OR (s.pprio=13 AND "+obfa2+"=0))) OR"+
			"  (                s.fbspooldt='' AND s.hylanr=0 AND s.pprio=12) OR"+
			"  ("+prio2+"=2 AND ((s.fbspooldt<>'' AND (s.fbdials>="+maxfbfxv+" OR s.fbdials=-1)) OR (s.hylanr<>'' AND (s.hyladials>="+maxhylav+" OR s.hylastate=8)))) OR "
			"  ("+prio3+"=2 AND ((s.fbspooldt<>'' AND (s.fbdials>="+maxfbfxv+" OR s.fbdials=-1)) AND s.hylanr<>'' AND (s.hyladials>="+maxhylav+" OR s.hylastate=8))))"
			" OR s.allewege=1)"
			") p10, \n"

			"("+obfa2+"=1 AND s.hylanr=0 AND "
			"((("+prio1+"=3 AND s.fbspooldt='' AND s.capispooldt='' AND (s.pprio <=3 OR (s.pprio=11 AND "+obfa0+"=0) OR (s.pprio=12 AND "+obfa1+"=0))) OR"+
			"  (                s.fbspooldt='' AND s.capispooldt='' AND s.pprio=13) OR"+
			"  ("+prio2+"=3 AND ((s.fbspooldt<>'' AND (s.fbdials>="+maxfbfxv+" OR s.fbdials=-1)) OR (s.capispooldt<>'' AND (s.capidials>="+maxcapiv+" OR s.capidials=-1)))) OR "
			"  ("+prio3+"=3 AND ((s.fbspooldt<>'' AND (s.fbdials>="+maxfbfxv+" OR s.fbdials=-1)) AND s.capispooldt<>'' AND (s.capidials>="+maxcapiv+" OR s.capidials=-1))))"
			" OR s.allewege=1)"
			") p11, \n"
			"s.adressat p12, s.pages p13 "
			",alts.id p14, s.wiemail p15 "
			"FROM `"+spooltab+"` s "
			"LEFT JOIN `"+altspool+"` alts ON s.idudoc=alts.idudoc "
			"WHERE s.original>'' GROUP BY s.id) i WHERE p9 OR p10 OR p11 OR p15 in (1,2)",aktc,ZDB);
	if (r0.obqueryfehler) {
		cerr<<rots<<"aktc: "<<schwarz<<aktc<<", "<<rot<<Tx[T_Fehler_af]<<schwarz<<(int)r0.obqueryfehler<<rot<<Tx[T_beiSQLAbfrage]<<schwarz<<r0.sql<<endl;
	} else {
		while (cerg=r0.HolZeile(),cerg?*cerg:0) {
			(dbszahl)++;
			caus<<*(*cerg+0)<<" "<<*(*cerg+5)<<endl;
			if (*(*cerg+0) && *(*cerg+1) && *(*cerg+2) && *(*cerg+3) && *(*cerg+4) && *(*cerg+5) && 
					*(*cerg+6) && *(*cerg+7) && *(*cerg+8)) {
				//// obcapi = cjj(cerg,9), obhyla=cjj(cerg,10)
				//// <<cjj(cerg,1)<<endl; caus<<cjj(cerg,2)<<endl; caus<<cjj(cerg,3)<<endl;
				fsfv.push_back(/*1*/fsfcl(cjj(cerg,0)/*id*/, cjj(cerg,1)/*npdf*/, cjj(cerg,2)/*spdf*/, cjj(cerg,3)/*telnr*/, 
							atoi(cjj(cerg,4))/*prio*/, cjj(cerg,5)/*capisd*/, atoi(cjj(cerg,6))/*capids*/, cjj(cerg,7)/*hylanr*/, atoi(cjj(cerg,8))/*hdialsn*/,
							(binaer)atoi(cjj(cerg,9))/*fobfbox*/, (binaer)atoi(cjj(cerg,10))/*fobcapi*/, (binaer)atoi(cjj(cerg,11))/*fobhyla*/, 
							cjj(cerg,12)/*adressat*/, atoi(cjj(cerg,13)/*pages*/), cjj(cerg,14)/*alts.id*/, atoi(cjj(cerg,15))/*s.wiemail*/));
				//// fsfv[fsfv.size()-1].ausgeb(/*obverb*/1);
			} // 			if (*(*cerg+0) && *(*cerg+1) && *(*cerg+2) && *(*cerg+3) && *(*cerg+4) && *(*cerg+5) &&  ...
		} // while (cerg=r0.HolZeile(),cerg?*cerg:0) 
		hLog(Tx[T_ZahldDSmwegzuschickendenFaxenin]+spooltab+"`: "+blau+ltoan(fsfv.size())+schwarz);
		uchar wasichbin{0}; //1=capi,2=hyla,3=fritzbox,4=anMail,5=klaran
		pid_t pid{1}; // fuer FBox, Capi und Hyla abzweigen
		if (fsfv.size()) {
			if (obfa[1]||obweg[1]==1) {
				pid=nursend?1:dfork();
				if (pid<0) {
					fLog(rots+Tx[T_Gabelung_zu_faxemitC_misslungen]+schwarz,1,oblog);
					exitt(17);
				} else if (!pid) {
					wasichbin=1; // Kindprozess
				} else {
					pidcl phier(pid,"faxemitC"); // Elternprozess
					pidv<<phier;
					pidw<<phier;
				}  // 			if (!pid) else else
			} // 		if (obcapi)
			// alle Abzweigungen muessen vom Hauptzweig ausgehen, sonst gehen dort Eintraege in pidv verloren
			if (pid>0) {
				if (obfa[2]||obweg[2]==1) {
					pid=nursend?1:dfork();
					if (pid<0) {
						fLog(rots+Tx[T_Gabelung_zu_faxemitH_misslungen]+schwarz,1,oblog);
						exitt(17);
					} else if (!pid) {
						wasichbin=2; // Kindprozess
					} else {
						pidcl phier(pid,"faxemitH"); // Elternprozess
						pidv<<phier;
						pidw<<phier;
					} // 				if (pid<0) else else
				} // 			if (obhyla)
			} // 		if (pid>0)
			if (pid>0) {
				if (obfa[0]||obweg[0]==1) {
					pid=nursend?1:dfork();
					if (pid<0) {
						fLog(rots+Tx[T_Gabelung_zu_faxemitF_misslungen]+schwarz,1,oblog);
						exitt(17);
					} else if (!pid) {
						wasichbin=3; // Kindprozess
					} else {
						pidcl phier(pid,"faxemitF"); // Elternprozess
						pidv<<phier;
						pidw<<phier;
					} // 				if (pid<0) else else
				} // 			if (obhyla)
			} // 		if (pid>0)
			if (pid>0) {
				pid=nursend?1:dfork();
				if (pid<0) {
					fLog(rots+Tx[T_Gabelung_zu_vschlmail_misslungen]+schwarz,1,oblog);
					exitt(17);
				} else if (!pid) {
					wasichbin=4; // Kindprozess
				} else {
					pidcl phier(pid,"vschlmail");
					pidv<<phier;
					pidw<<phier; // Elternprozess
				} // 				if (pid<0) else else
			}
			if (pid>0) {
				pid=nursend?1:dfork();
				if (pid<0) {
					fLog(rots+Tx[T_Gabelung_zu_klarmail_misslungen]+schwarz,1,oblog);
					exitt(17);
				} else if (!pid) {
					wasichbin=5; // Kindprozess
				} else {
					pidcl phier(pid,"klarmail");
					pidv<<phier;
					pidw<<phier; // Elternprozess
				} // 				if (pid<0) else else
			}
			//// const auto altobverb{obverb}; obverb=1;
			if (wasichbin||nursend) {
				// hier Fork zu Capi, Hyla, und Fritz nicht der Hauptzweig
				// Hylafax sollte nicht mehrere Faxe auf einmal versuchen wegzuschicken
				uchar hfaxinarbeit{0};
				if (obfa[2]||obweg[2]==1) {
					for(unsigned i=0;i<fsfv.size();i++) {
            if (fsfv[i].fobhyla && fsfv[i].hylastat==verarb) {
							hfaxinarbeit=1;
							break;
						}
					}
				}
				for(unsigned i=0;i<fsfv.size();i++) {
					hLog(" i: "+blaus+ltoan(i)+schwarz+Tx[T_PDFDatei]+blau+fsfv[i].spdf+schwarz+
							", "+Tx[T_obfboxmitDoppelpunkt]+blau+(fsfv[i].fobfbox?Txk[T_ja]:Txk[T_nein])+schwarz+
							", "+Tx[T_obcapimitDoppelpunkt]+blau+(fsfv[i].fobcapi?Txk[T_ja]:Txk[T_nein])+schwarz+
							", "+Tx[T_obhylamitDoppelpunkt]+blau+(fsfv[i].fobhyla?Txk[T_ja]:Txk[T_nein])+schwarz+
							", "+Tx[T_obvmailmitDoppelpunkt]+blau+(fsfv[i].fobvmail?Txk[T_ja]:Txk[T_nein])+schwarz+
							", "+Tx[T_obkmailmitDoppelpunkt]+blau+(fsfv[i].fobkmail?Txk[T_ja]:Txk[T_nein])+schwarz
							);
					const string zfxdt{wvz+vtz+fsfv[i].spdf};
					struct stat st{0};
					if (/*wasichbin==1 einmal reicht hier schon &&*/ lstat(zfxdt.c_str(),&st)) {
						fLog(rots+(wasichbin==1?"Capi: ":wasichbin==2?"Hyla: ":wasichbin==3?"FBox: ":wasichbin==4?"VMail: ":wasichbin==5?"KMail: ":"")+
								schwarz+Tx[T_Fehler_zu_faxende_Datei]+rots+zfxdt+schwarz+
								Tx[T_nicht_gefunden_Eintrag_ggf_loeschen_mit_]+blau+base_name(aktprogverz())+" -"+Tx[T_loew]+schwarz+
								Tx[T_bzw_]+blau+base_name(aktprogverz())+" -"+Tx[T_loef]+schwarz+"'",1,oblog);
					} else {
						//// caus<<"Stelle 4, i: "<<i<<", wasichbin: "<<(int)wasichbin<<", fsfv[i].fobfbox: "<<(int)fsfv[i].fobfbox<<", obfa[0]: "<<obfa[0]<<endl;
						if (wasichbin==1||nursend) if (fsfv[i].fobcapi) if (obfa[1]||obweg[1]==1) faxemitC(My, spooltab, altspool, &fsfv[i],zfxdt);  
						if (wasichbin==2||nursend) if (!hfaxinarbeit && fsfv[i].fobhyla) if (obfa[2]||obweg[2]==1) faxemitH(My, spooltab, altspool, &fsfv[i],zfxdt);  
						if (wasichbin==3||nursend) if (fsfv[i].fobfbox) if (obfa[0]||obweg[0]==1) faxemitF(My, spooltab, altspool, &fsfv[i],zfxdt);  
						if (wasichbin==4||nursend) if (fsfv[i].wiemail==1) vschlmail(My, spooltab, altspool, &fsfv[i],zfxdt);  
						if (wasichbin==5||nursend) if (fsfv[i].wiemail==2) klarmail(My, spooltab, altspool, &fsfv[i],zfxdt);  
					} // if (pid>0 && lstat(zfxdt.c_str(),&st))
					////      _out<<fsfv[i].id<<" "<<rot<<fsfv[i].npdf<<" "<<schwarz<<(int)fsfv[i].fobcapi<<" "<<(int)fsfv[i].obhyla<<endl;
				} // for(unsigned i=0;i<fsfv.size();i++) 
				hLog(violetts+"Pid "+blau+ltoan(pid)+violett+" "+Txk[T_Ende]+Tx[T_wegfaxen]+schwarz+", "+blau+Tx[T_obcapimitDoppelpunkt]+schwarz+
						(obfa[1]||obweg[1]==1?Txk[T_ja]:Txk[T_nein])+", "+blau+Tx[T_obhylamitDoppelpunkt]+schwarz+(obfa[2]||obweg[2]==1?Txk[T_ja]:Txk[T_nein]));
				if (!nursend) exitt(0);
			} // 		if (wasichbin||nursend)
			//// obverb=altobverb;
			// 1. warte auf faxemitC, faxemitH, faxemitF
		} // 		if (fsfv.size())
		if (!nursend) wartaufpids(&pidw,0,obverb,oblog,Tx[T_in_wegfaxen]); // wird also nur vom Hauptthread aus aufgerufen
		// nur wegfaxen mit abgeschlossenen Unterprogrammen
#ifdef immerwart
		ulong kaufrufe{0};
		do {
			string altobsendC;
			lieszaehlerein(&kaufrufe,0,0,0,/*obempfp=*/0,&altobsendC,/*obstumm=*/1);
			//// <<rot<<"kaufrufe: "<<kaufrufe<<" aufrufe: "<<aufrufe<<endl;
			//// <<"altobsendC: '"<<altobsendC<<"', aufrufe: "<<aufrufe<<", kaufrufe: "<<kaufrufe<<endl;
			if (aufrufe!=kaufrufe && altobsendC!="1") {
				//// <<"zcnfA[5] vorher: "<<violett<<zcnfA[5].wert<<schwarz<<endl;
				schreibzaehler(0,&eins);
				//// <<"zcnfA[5] nachher: "<<violett<<zcnfA[5].wert<<schwarz<<endl;
			} // 			if (aufrufe!=kaufrufe && altobsendC!="1")
		} while (kaufrufe==aufrufe);
#endif // immerwart
	} // 	if (r0.obqueryfehler) else
	hLog(violetts+Txk[T_Ende]+Tx[T_wegfaxen]+schwarz+", "
			+blau+Tx[T_obfboxmitDoppelpunkt]+schwarz+(obfa[0]||obweg[0]==1?Txk[T_ja]:Txk[T_nein])+"; "
			+blau+Tx[T_obcapimitDoppelpunkt]+schwarz+(obfa[1]||obweg[1]==1?Txk[T_ja]:Txk[T_nein])+": "
			+blau+Tx[T_obhylamitDoppelpunkt]+schwarz+(obfa[2]||obweg[2]==1?Txk[T_ja]:Txk[T_nein]));
////	obverb=altobverb;
} // void hhcl::wegfaxen


// aufgerufen in: empferneut (3x), empfarch
void hhcl::empfcapi(const string& stamm,const size_t aktc,const uchar was/*=7*/,const string& nr/*=nix*/)
// uchar indb/*=1*/,uchar mitversch/*=1*/)
// was&4: Bilddateien erstellen, was&2 capi-Datei verschieben, was&1: in Datenbank eintragen, 
{
	hLog(violetts+Tx[T_empfcapi]+schwarz+stamm+Tx[T_was]+(was&4?Tx[T_Bilddatei]:"")+(was&2?", sff ":"")+(was&1?", Tab.":""));

	const	string ctxdt{stamm+".txt"};
	struct stat txtstat{0};
	string filename, call_from,call_to,time,cause,
				 zeits;
	if (!lstat(ctxdt.c_str(),&txtstat)) {
		schAcl<WPcl> txtC("txtC", new vector<aScl>{
				{"filename",&filename},
				{"call_from",&call_from},
				{"call_to",&call_to},
				{"time",&time},
				{"cause",&cause},
				});
		confdcl txtc(ctxdt,obverb);
		txtc.kauswert(&txtC);
		struct tm tm{0};
		for(unsigned im=0;im<tmmoelen;im++) {
			if (strptime(time.c_str(), tmmoegl[im], &tm)) break;
		} // 			for(unsigned im=0;im<elemzahl(tmmoegl);im++)
		//// strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H.%M.%S", &tm);
		stringstream sptrstr;
		sptrstr<<put_time(&tm,"%d.%m.%Y %H.%M.%S");
		// tm enthaelt also z.B. die in /var/spool/capisuite/users/<user>/received/fax-999999.txt unter "time" stehende Zeit
		//// s=tbuf;
		//// sptr=&s;
		zeits=sptrstr.str();
		time=zeits;
		for(unsigned i{0};i<txtC.size();i++) {
			hLog(schwarzs+"   "+txtC[i]->pname+": "+tuerkis+*(string*)txtC[i]->pptr);
		}
		tm.tm_isdst=-1; // sonst wird zufaellig ab und zu eine Stunde abgezogen
		const time_t modz=mktime(&tm);
		string getname,bsname;
		getSender(call_from,&getname,&bsname,aktc);
		getname+=", ";
		getname+=bsname;
		////      if (getname.length()>187) getname.erase(187);
		if (getname.length()>70) getname.erase(70);
		uint vfehler{0};
		uchar verschieb{0};
		struct stat sffstat{0};
		ulong pseiten{0};
		const string base{base_name(stamm)};
		const size_t hpos{base.find_last_of('-')+1}; // u.a.: string::npos+1=0
		const string fnr{base.substr(hpos)};
		if (was&4) { // Bilddatei erstellen
			// um das Datum dann anzugleichen
			const string sffdatei{stamm+".sff"};
			const int sfffehlt{lstat(sffdatei.c_str(),&sffstat)};
			const string tifrumpf{"Fax c"+fnr+","+Tx[T_avon]+getname+", T."+stdfaxnr(call_from)+","+Tx[T_vom]+zeits};
			if (sfffehlt) {
				// .txt nach falsche verschieben
				verschieb=1;
			} else {
				int erg{-1};
				if (sffstat.st_size) {
					// -f == force, steht nicht in --help
					static uchar sffgeprueft{0};
					if (!sffgeprueft) {
						pruefsfftobmp();
						sffgeprueft=1;
					} // 			if (!sffgeprueft)
					// ..., die empfangene Datei in tifpfad kopieren ...
					const string tifdatei{tifrumpf+".tif"};
					const string tifpfad{empfvz+vtz+tifdatei}; //// Tx[T_Fax_von]+call_from+Tx[T_an]+call_to+Tx[T_vom]+tbuf+".tif";
					fLog((nr.empty()?"":nr+")")+blaus+stamm+schwarz+" => "+gruen+tifdatei+schwarz,1,1);
					cmd="sfftobmp -f -d -t "+sffdatei+" -o \""+tifpfad+"\" 2>&1";
					for(int iru=0;iru<2;iru++) {
						struct stat st{0};
						// nach evtl. Vorversuchen aufraeumen
						if (!lstat(tifpfad.c_str(),&st)) 
							tuloeschen(tifpfad,cuser,obverb,oblog);
						svec srueck;
						erg=systemrueck(cmd,obverb,oblog,&srueck,/*obsudc=*/0,0,wahr,"",0,1);
						if (srueck.size()) {
							// wenn Fehlermeldung "no version information available, dann sfftobmp unter aktuellem libtiff5 nochmal installieren
							if (srueck[0].find("libtiff")!=string::npos && srueck[0].find("no version information")!=string::npos) {
								instsfftobmp();
							}
						} else {
							break;
						} // 					if (srueck.size()) else
					} // 			for(int iru=0;iru<2;iru++)
					if (!erg) {
						attrangleich(tifpfad,empfvz,&sffdatei,obverb,oblog);
						ankzahl++;
						// bereits hier, da weder convert noch soffice noch ocrmypdf eine *.sff-Datei lesen kann, convert auch keine tiff-Datei
						const string ziel{empfvz+vtz+tifrumpf+".pdf"}; 
						const int obpdfda{!zupdf(&tifpfad, ziel, &pseiten, obocri, 1)}; // 0=Erfolg
						struct stat stziel{0};
						if (obpdfda && !lstat(ziel.c_str(),&stziel)) {
							tuloeschen(tifpfad,cuser,obverb,oblog);
						} // 					if (obpdfda && !lstat(ziel.c_str(),&stziel))
					} else {
						uint kfehler{1};
						const string sffneu{empfvz+vtz+tifrumpf+".sff"};
						kopiere(sffdatei,sffneu,&kfehler,/*wieweiterzaehl=*/2,obverb,oblog);
						if (kfehler) {
							verschieb=2;
						} else {
							attrangleich(sffneu,empfvz,&sffdatei,obverb,oblog);
						} // if (!kfehler) else
					} // if (!erg) else
				} else {
					// empfangenes Fax mit 0 Bytes, vermutlich abgefangen von anderem System, samt Textdatei nach 'falsche' verschieben
					verschieb=2;
				} // if (entrysff.st_size)
				// wenn sfftobmp funktioniert hat // oder die Datei verschoben wurde
			} // if (lstat(sffdatei.c_str(),&entrysff)) else  
			if (verschieb) {
				const string warndt{empfvz+vtz+Tx[T_nicht_angekommen]+tifrumpf+".nix"};
				touch(warndt,obverb,oblog);
				attrangleich(warndt,empfvz,&sffdatei,obverb,oblog);
			} // 		if (verschieb)
			if (was&2) { // sff-Datei verschieben
				if (verschieb) {
					////        if (loee) KLA
					static uchar falschegeprueft{0};
					if (!falschegeprueft) {
						pruefverz(cfaxuserrcfalschevz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/"",/*benutzer=*/cuser);
						falschegeprueft=1;
					} // 			if (!falschegeprueft)
					verschiebe<string>(ctxdt,cfaxuserrcfalschevz,cuser,&vfehler,/*wieweiterzaehl=*/1,obverb,oblog);
					if (verschieb==2) {
						fLog(Tx[T_Dateien]+rots+stamm+".* "+schwarz+Tx[T_nicht_verarbeitbar_Verschiebe_sie_nach]+rot+"./falsche"+schwarz+".",1,1);
						verschiebe<string>(sffdatei,cfaxuserrcfalschevz,cuser,&vfehler,/*wieweiterzaehl=*/1,obverb,oblog);
						// so, dass es jeder merkt
					} // if (verschieb==2) 
					//      KLZ // if (loee) 
				} else {
					static uchar cempfavzgeprueft{0};
					if (!cempfavzgeprueft) {
						pruefverz(cempfavz,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/"",/*benutzer=*/cuser);
						cempfavzgeprueft=1;
					} // 			if (!cempfavzgeprueft)
					string zdt{cempfavz+vtz+cuser+"-"+base+".sff"};
					dorename(sffdatei,zdt,cuser,&vfehler,/*schonda=*/!dateivgl(sffdatei,zdt),obverb,oblog);
					zdt=cempfavz+vtz+cuser+"-"+base_name(ctxdt);
					dorename(ctxdt,zdt,cuser,&vfehler,/*schonda=*/!dateivgl(ctxdt,zdt),obverb,oblog);
				} // if (utime(tifpfad.c_str(),&ubuf))  else
			} // 	if (mitversch)
		} // was&4, Bilddatei verschieben
		if (was&1)	{ // in Datenbank eintragen
			//			RS zs(My);
			RS rins(My,tinca); 
			vector<instyp> einf; // fuer alle Datenbankeinfuegungen
			einf.push_back(/*2*/instyp(My->DBS,"titel",getname+", "+bsname));
			einf.push_back(/*2*/instyp(My->DBS,"tsid",&call_from));
			einf.push_back(/*2*/instyp(My->DBS,"transe",&modz));
			einf.push_back(/*2*/instyp(My->DBS,"id",&base));
			einf.push_back(/*2*/instyp(My->DBS,"fsize",sffstat.st_size));
			einf.push_back(/*2*/instyp(My->DBS,"csid",&call_to));
			einf.push_back(/*2*/instyp(My->DBS,"pages",pseiten));
			svec eindfeld; eindfeld<<"id";
			rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/ZDB,/*idp=*/0,/*eindeutig=*/0,eindfeld); 
			if (rins.fnr) {
				fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
			} //         if (runde==1)
		} // 	if (was&1)
	} // 	if (!lstat(ctxdt.c_str(),&txtstat))
}// void hhcl::empfcapi

// aufgerufen in: main
void hhcl::empfarch(uchar obalte/*=0*/)
{
	hLog(violetts+Tx[T_empfarch]+schwarz);
	const size_t aktc{5};

	// 1) fbox
	struct stat fst{0};
	if (!fbankvz.empty()&&!lstat(fbankvz.c_str(),&fst)) {
		svec qrueck;
		string suchs;
		//		if (tagesaufr==4 ||1) {
		suchs="find '"+fbankvz+"' -iname '*pdf' -not -iname '*_alt\\.pdf'";	
		//		} else {
		//		  suchs="find '"+fbankvz+"' -mtime -1 -iname '*pdf'";	
		//		}
		systemrueck(suchs,obverb,oblog,&qrueck);
		for(size_t i=0;i<qrueck.size();i++) {
			empffbox(qrueck[i],aktc,ltoan(i));
		}
		suchs="find '"+fbankvz+"' -mtime +31 -iname '*_alt\\.pdf' -delete";	
		systemrueck(suchs,obverb,oblog,&qrueck);
	} // 	if (!fbankvz.empty()&&!lstat(fbankvz.c_str(),&fst))

	// 2) capi
	/*//
		cppSchluess umst[]={{"filename"},{"call_from"},{"call_to"},{"time"},{"cause"}};
		size_t cs=elemzahl(umst);
	 */
	const string * const csuchvzp{obalte?&cempfavz:&cfaxuserrcvz};
	struct stat entryvz{0};
	////  cfaxuserrcvz="/var/spool/capisuite/users/schade/received";
	if (!lstat(csuchvzp->c_str(),&entryvz)) /* /var/spool/capisuite/users/~/received */ {
		svec qrueck;
		if (findv==1) {
			// Faxe in der Empfangswarteschlange auflisten, ...
			cmd=sudc+"find \""+*csuchvzp+"\" -maxdepth 1 -type f -iname \"*.txt\"";
			systemrueck(cmd,obverb,oblog, &qrueck);
		} else findfile(&qrueck,findv,obverb,oblog,0,*csuchvzp,/*muster=*/"\\.txt$",1,1,Fol_Dat,0,0,1);
		for(size_t i=0;i<qrueck.size();i++) {
			// ..., Informationen darueber einsammeln, ...
			string stamm,exten;
			getstammext(&(qrueck[i]),&stamm,&exten);
			empfcapi(stamm,aktc,/*was=*/obalte?1:7);
		} // for(size_t i=0;i<rueck.size();i++) 
	} 	// if (!lstat(csuchvzp->c_str(),&entryvz)) /* /var/spool/capisuite/users/~/received */

	// 3) hyla
	svec qrueck;
	const string hsuchvz{varsphylavz+(obalte?"":"/recvq")};
	if (findv==1) {
		// Faxe in der Empfangswarteschlange auflisten, ...
		cmd=sudc+"find \""+hsuchvz+"\" -name \"fax*.tif\"";
		systemrueck(cmd,obverb,oblog, &qrueck,/*obsudc*/0,/*verbergen*/0,/*obergebnisanzeig*/wahr,/*ueberschr*/string(),/*errm*/0,/*obincron*/0,/*ausp*/0,/*obdirekt*/0,/*ohnewisch*/1);
	} else findfile(&qrueck,findv,obverb,oblog,0,hsuchvz,/*muster=*/"/fax.*\\.tif$",-1,1,0);
	for(size_t i=0;i<qrueck.size();i++) {
		// ..., Informationen darueber einsammeln, ...
		empfhyla(qrueck[i],aktc,/*was=*/obalte?1:7);
	} // for(size_t i=0;i<rueck.size();i++) 

#ifdef immerwart
	ulong jaufrufe{0};
	do {
		string altobempf;
		lieszaehlerein(&jaufrufe,0,0,0,&altobempf,/*obgesap=*/0,/*obstumm=*/1);
		//// <<"jaufrufe: "<<jaufrufe<<" aufrufe: "<<aufrufe<<endl;
		if (aufrufe!=jaufrufe && altobempf!="1") {
			schreibzaehler(&eins);
		}
	} while (jaufrufe==aufrufe);
#endif // immerwart
	fLog(Tx[T_Zahl_der_empfangenen_Faxe]+drots+ltoan(ankzahl)+schwarz,1,1);
	hLog(violetts+Txk[T_Ende]+Tx[T_empfarch]+schwarz);
} // void hhcl::empfarch

// aufgerufen in: bereinigevz
string hhcl::getzielvz(const string& qdatei)
{
	for(auto zmakt: zmsp) {
		if (!regexec(&(zmakt->regex),qdatei.c_str(),0,NULL,0))
			return zmakt->ziel;
		//// if (zmakt->obmusterleer()) break;
	}
	return {};
} // getzielvz

const char *const chfarbe(const uchar stand)
{
	switch (stand) {
		case 0: return rot;
		case 1: return violett;
	}
	return blau;
} // const char const* chfarbe(uchar stand)

const char* chstandtxt(const uchar stand)
{
	switch (stand) {
		case 0: return Tx[T_Fehlt];
		case 1: return Tx[T_Nicht_gefaxt];
						//	case 2: return Tx[T_gefaxt];
	}
	return Tx[T_Gefaxt];
} // const char* chstandtxt(uchar stand)


// aufgerufen in bereinigevz 
// verschiebt Dateien je nach Eintrag in outa, altspool und den Faxsystemen
// in das Gescheitertenverzeichnis und im ersten Fall auch das Zielverzeichnis
// wann&1 = erfolgreiche Faxe verschieben, wann&2 = erfolglose Faxe verschieben
void hhcl::dober(const string& quvz, set<string>& fdn,uchar wann,stringstream *ausgp,const size_t aktc,
		set<string> *cmisslp,set<string> *cgelup,set<string> *hmisslp,set<string> *hgelup)
{
	hLog(violetts+"dober()"+schwarz);
	string meld;
	set<string>::iterator fit; // Iterator dafuer
	////  for(fit=fdn.begin();fit!=fdn.end();++fit) _out<<blau<<*fit<<schwarz<<endl;
	// die Dateien, die in outa stehen, je nach Erfolgskennzeichen in das Zielverzeichnis oder das Gescheitertenverzeichnis verschieben
	for(unsigned runde=0;runde<2;runde++) {
		string sql;
		switch (runde) {
			case 0: sql="SELECT id p0, original p1, origvu p2 FROM `"+spooltab+"`"; break;
			case 1: sql="SELECT eind p0, docname p1, Erfolg p2 FROM `"+touta+"`"; break;
		} //     switch (runde)
		RS rsp(My,sql,aktc,ZDB);
		char ***cerg;
		while (cerg=rsp.HolZeile(),cerg?*cerg:0) {
			// nur die erste Tabelle hat zwei Spalten mit Dateinamen
			for(unsigned cnr=1;cnr<(runde?2:3);cnr++) {
				if (*(*cerg+cnr)) {
					string dbdocname{*(*cerg+cnr)};
					for (unsigned aru=0;aru<(runde?7:1);aru++) {
						////<<"aru: "<<aru<<" cnr: "<<cnr<<" runde: "<<runde<<" dbdocname: "<<dbdocname<<endl;
						string stamm,exten;
						getstammext(&dbdocname,&stamm,&exten);
						if (!aru || !exten.empty()) {
							if (aru) {
								switch (aru) {
									case 1: dbdocname=stamm+".doc"; break;
									case 2: dbdocname=stamm+".xls"; break;
									case 3: dbdocname=stamm+".jpg"; break;
									case 4: dbdocname=stamm+".tif"; break;
									case 5: dbdocname=stamm+".png"; break;
									case 6: dbdocname=stamm+".txt"; break;
								} //                   switch (aru)
							} //                 if (aru)
							////							if (dbdocname.find("Zwingel Dieter Labor an Fax 081368208")!=string::npos) //// <<rot<<"dbdocname: "<<dbdocname<<schwarz<<endl;
							if ((fit=fdn.find(dbdocname))!=fdn.end()) { // wenn Datenbankeintrag in der sortierten Menge der Dateinamen enthalten
								const string fdat{*fit};
								////							if (dbdocname.find("Zwingel Dieter Labor an Fax 081368208")!=string::npos) //// <<violett<<"*fit: "<<fdat<<schwarz<<endl;
								struct stat qst{0};
								const string qdt{quvz+vtz+fdat};
								lstat(qdt.c_str(),&qst);
								uchar obgescheitert{0};
								if (runde) { // wenn in outa, nicht in der Spool-Tabelle
									string zlvz;
									////                        if (runde==1) zlvz=getzielvz(qdt); else if (runde==2) zlvz=ngvz;
									if (runde==1) {
										if (*cjj(cerg,2)=='1') 
											zlvz=getzielvz(qdt); 
										else if (*cjj(cerg,2)=='0') {
											obgescheitert=1;
											zlvz=ngvz; // Erfolgskennzeichen, Ziel, gescheitert
										}
									} // 												if (runde==1)
									if ((obgescheitert&&(wann&2)) || (!obgescheitert&&(wann&1))) {
										unsigned vfehler=0;
										if (!zlvz.empty()) {
											const string zdt{zlvz+vtz+*fit};
											verschiebe<string>(qdt, zdt, cuser,&vfehler, /*wieweiterzaehl=*/2,/*obverb=*/ausgp?0:1,/*oblog=*/1,ausgp);
											if (vfehler) {
												meld=rots+Tx[T_Fehler_beim_Verschieben_Ausrufezeichen]+": "+ltoan(vfehler)+schwarz+qdt+" -> "+zdt;
												if (ausgp) *ausgp<<meld<<endl; else fLog(meld,1,1);
												////fLog(rots+Tx[T_Fehler_beim_Verschieben_Ausrufezeichen]+": "+ltoan(vfehler)+schwarz+qdt+" -> "+zdt,1,1);
											} // if (vfehler)
										} // if (!zlvz.empty()) 
									} // 											if (obgescheitert || wann)
									fdn.erase(fit);
								} else { // if (runde) 
									fdn.erase(fit); // die in der Spool-Tabelle genannten Dateien nicht bearbeiten
								} //    if (runde) else
								meld=Tx[T_gefunden_in_Tabelle]+blaus+(runde?touta.c_str():spooltab.c_str())+schwarz+", "+(runde?"eind":"id")+": "
									+blau+cjj(cerg,0)+schwarz+" = Name: "+(runde?((*cerg+2)&&(*cjj(cerg,2)=='1')?blau:gruen):rot)+fdat.c_str()+schwarz
									+", Bytes: "+blau+ltoan(qst.st_size)+schwarz+Tx[T_kommaFaxerfolg]+blau+(obgescheitert?Txk[T_nein]:Txk[T_ja])+schwarz;
								if (ausgp) *ausgp<<meld<<endl; else fLog(meld,1,1);
								////		fLog(1,1,0,0,"%s%s%s%s, %s: %s%s%s = Name: %s%s%s, Bytes: %s%zu%s",Tx[T_gefunden_in_Tabelle],
								////		    blau,runde?touta.c_str():spooltab.c_str(),schwarz,runde?"eind":"id", blau,cjj(cerg,0),schwarz,
								////				(runde?((*cerg+2)&&(*cjj(cerg,2)=='1')?blau:gruen):rot), fdat.c_str(),schwarz, blau,qst.st_size,schwarz);
								//								if (runde) break;
							} // if ((fit=fdn.find(dbdocname))!=fdn.end()) 
							//	if (!runde) break;
						} // if (!aru || !exten.empty()) 
					} // 					for (unsigned aru=0;aru<(runde?7:1);aru++)
				} // if (*(*cerg+cnr)) 
			} // for(unsigned cnr=1;cnr<3;cnr++) 
		} // while (cerg=rsp.HolZeile(),cerg?*cerg:0) 
	} // for(unsigned runde=0;runde<3;runde++) 
	uchar ueanz{0}; // Ueberschrift schon angezeigt
	// jetzt die Verknuepfung aus altspool holen
	const string sqlr{"SELECT capispooldt p0,hylanr p1 FROM `"+altspool+"` WHERE "};
	size_t fitnr{0};
	if (fdn.size()) {
		for(fit=fdn.end();;) {
			--fit;
			fitnr++;
			const string qdt{quvz+vtz+*fit};
			string sql;   
			////			transform(fit->begin(),fit->end(),std::back_inserter(gross),::toupper);
			const string gross{boost::locale::to_upper(*fit, loc)};
			if (gross.find(".PDF")==gross.length()-4) {
				sql=sqlr+"original = '"+*fit+"'";
			} else {
				sql=sqlr+"origvu = '"+*fit+"'";
			}
			RS rsp(My,sql,aktc,ZDB);
			char ***cerg;
			uchar cstand{0}, hstand{0}; // 0= nicht gefunden, 1=nicht gefaxt, 2=gefaxt
			if (cerg=rsp.HolZeile(),cerg?*cerg:0) {
				// <<blau<<cjj(cerg,0)<<" "<<cjj(cerg,1)<<schwarz<<" gefunden: "<<blau<<*fit<<schwarz<<endl;
				if (*cjj(cerg,0)) {
					if (cmisslp->find(cjj(cerg,0))!=cmisslp->end()) { // wenn Datenbankeintrag in der sortierten Menge der Dateinamen enthalten
						cstand=1;
					} else if (cgelup->find(cjj(cerg,0))!=cgelup->end()) { // wenn Datenbankeintrag in der sortierten Menge der Dateinamen enthalten
						cstand=2;
					}
				} // 				if (*cjj(cerg,0))
				if (*cjj(cerg,1)) {
					if (hmisslp->find(cjj(cerg,1))!=hmisslp->end()) { // wenn Datenbankeintrag in der sortierten Menge der Dateinamen enthalten
						hstand=1;
					} else if (hgelup->find(cjj(cerg,0))!=hgelup->end()) { // wenn Datenbankeintrag in der sortierten Menge der Dateinamen enthalten
						hstand=2;
					}
				} // 				if (*cjj(cerg,1))
			} else {
				////		 <<"nicht gefunden: "<<blau<<*fit<<schwarz<<endl;
			} // 			if (cerg=rsp.HolZeile(),cerg?*cerg:0)
			if (/*obverb*/1) {
				if (!ueanz) {
					meld=Tx[T_Bereinige_Verzeichnis]+blaus+quvz+schwarz+"' (2):";
					if (ausgp) *ausgp<<meld<<endl; else fLog(meld,1,1);
					////					fLog(Tx[T_Bereinige_Verzeichnis]+blaus+quvz+schwarz+"' (2):",1,1);
					ueanz=1;
				}
				char const* farbe=weiss;
				if (cstand==2) farbe=blau;
				else if (hstand==2) farbe=dblau;
				else if (cstand==1||hstand==1) farbe=violett;
				else farbe=rot;
				meld=string(ltoan(fitnr))+") Capi: "+chfarbe(cstand)+chstandtxt(cstand)+blau+"("+(cerg&&*cerg?cjj(cerg,0):"")+")"+schwarz
					+", Hyla: "+chfarbe(hstand)+chstandtxt(hstand)+blau+"("+(cerg&&*cerg?cjj(cerg,1):"")+schwarz+"): "+farbe+*fit+schwarz;
				if (ausgp) *ausgp<<meld<<endl; else fLog(meld,1,1);
				////				fLog(1,1,0,0,"%zu) Capi: %s%s%s(%s)%s, Hyla: %s%s%s(%s)%s: %s%s%s",fitnr,chfarbe(cstand),chstandtxt(cstand),blau,
				////						(cerg&&*cerg?cjj(cerg,0):""),schwarz, chfarbe(hstand),chstandtxt(hstand),blau,
				////						(cerg&&*cerg?cjj(cerg,1):""),schwarz,farbe,fit->c_str(),schwarz);
			} // 		if (obverb)
			// <<fitnr<<") "<<farbe<<*fit<<schwarz<<endl;
			uint vfehler{0};
			string zdt;
			if (cstand==2 || hstand==2) {
				if (wann&1) {
					zdt=verschiebe<vector<shared_ptr<zielmustercl>>>(qdt, zmsp, cuser,&vfehler, /*wieweiterzaehl=*/2,/*obverb=*/ausgp?0:1,/*oblog=*/1,ausgp);
				} // 				if (wann)
				// wenn nicht im System nachweisbar, dann auch nicht umbenennen
			} else {
				zdt=ngvz+vtz+*fit;
				/*//
					if (!cstand&&!hstand) KLA
					if (!ngvz.empty()) KLA
					dorename(qdt,zdt,cuser,&vfehler,1,1);
					KLZ
					KLA else KLZ
				 */
				if ((wann&2)&& !ngvz.empty()) {
					verschiebe<string>(qdt, ngvz, cuser,&vfehler,/*wieweiterzaehl=*/2,/*obverb=*/ausgp?0:1,/*oblog=*/1,ausgp);
				} // 				if (!ngvz.empty())
			} // 			if (cstand==2 || hstand==2) else
			if (vfehler) {
				meld=rots+Tx[T_Fehler_beim_Verschieben_Ausrufezeichen]+": "+ltoan(vfehler)+schwarz+qdt+" -> "+zdt;
				if (ausgp) *ausgp<<meld<<endl; else fLog(meld,1,1);
				////				fLog(rots+Tx[T_Fehler_beim_Verschieben_Ausrufezeichen]+": "+ltoan(vfehler)+schwarz+qdt+" -> "+zdt,1,1);
			} // 			if (vfehler)
			// fdn.erase(fit);
			if (fit==fdn.begin()) break;
		} //  		for(fit=fdn.end();;)
	} // 	if (fdn.size())
} // void hhcl::dober(const string& quvz, set<string>& fdn,uchar wann,stringstream *ausgp)



// Parameter -bvz
// aufgerufen in: main
void hhcl::bereinigevz(const size_t aktc/*=0*/)
{
	hLog(violetts+"bereinigevz()"+schwarz);
	// laeuft das Programm uanufgefordert parallel, dann ist aktc>0; dann sollen die Programmmeldungen gesammelt ausgegeben werden (ueber ausg)
	stringstream ausg;
	string meld;
	if (obverb||oblog) {
		meld=violetts+Tx[T_bereinigevz]+schwarz;
		if (aktc) ausg<<meld<<endl; else fLog(meld,obverb,oblog);
	}
	for(int vru=0;vru<3;vru++) {
		set<string> vzs,fdn;
//		zielmustercl *zmakt;
		switch (vru) {
			// Warteverzeichnis
			case 0: 
				vzs.insert(wvz); 
				break;
				// das letzte Zielverzeichnis
			case 1: 
				/*
				for(unsigned i{0};i<zmsp.size();i++){
					// nur das letzte Verzeichnis aufgraeumen
					if (zmsp[i]->obmusterleer()) {
						vzs.insert(zmsp[i]->ziel);
						break;
					} // 		if (zmakt->obmusterleer())
				} // 	for(zielmustercl *zmakt=zmp;1;zmakt++)
				*/
				for(auto zmakt:zmsp) {
					// nur das letzte Verzeichnis aufgraeumen
					if (zmakt->obmusterleer()) {
						vzs.insert(zmakt->ziel);
					  break;
					}
				}
				break;
				// das Gescheitertenverzeichnis
			default:
				vzs.insert(ngvz); 
		} // 	 switch (vru)
		set<string>::iterator fit; // Iterator dafuer
		// zur Zeit jeweils nur ein Element
		for(fit=vzs.begin();fit!=vzs.end();fit++) {
			unsigned long fzahl=0; // Fehlerzahl
			const string dsvz{*fit}; // Dateiensuchverzeichnis
			svec rueck;
			if (findv==1) {
				cmd="find "+dsvz+" -maxdepth 1 -type f -not -name \"*\\`*.nix\" -printf '%f\\n'";
				systemrueck(cmd,aktc?0:obverb,oblog,&rueck,/*obsudc=*/1,/*verbergen=*/0,/*obergebnisanzeig=*/wahr,/*ueberschr=*/nix,/*errm=*/0,
						        /*obincron=*/0,aktc?&ausg:0);
			} else findfile(&rueck,findv,aktc?0:obverb,oblog,/*anteil=*/1,dsvz,/*muster=*/"^[^`]*$",/*tiefe=*/1,/*_typbit=*/1,/*folge=*/Fol_Dat);
			for(size_t dnr=0;dnr<rueck.size();dnr++) {
				fdn.insert(rueck[dnr]);
			}
			meld=Tx[T_Bereinige_Verzeichnis]+blaus+dsvz+schwarz+Tx[T_DateienzahlimVz]+blau+ltoan(fdn.size())+schwarz+": ";
			if (aktc) ausg<<meld<<endl; else fLog(meld,1,1);

			// Vergleich Dokumentationen der Faxsysteme vorbereiten, dazu dortige Dateien einlesen
			// 1) Archivsysteme der Faxsysteme
			//  a) Capisuite
			set<string> cmissl,cgelu,hmissl,hgelu; // Fax-Dateien
			rueck.clear();
			systemrueck("find "+cfailedvz+" -type f -name '*.sff'",aktc?0:obverb,oblog,&rueck,/*obsudc=*/0,/*verbergen=*/0,
					/*obergebnisanzeig=*/wahr,/*ueberschr=*/nix,/*errm=*/0,/*obincron=*/0,&ausg);
			for(size_t i=0;i<rueck.size();i++) {
				size_t pos=rueck[i].rfind("fax-");
				if (pos!=string::npos) cmissl.insert(rueck[i].substr(pos));
			}
			rueck.clear();
			systemrueck("find "+cdonevz+" -type f -name '*.sff'",aktc?0:obverb,oblog,&rueck,/*obsudc=*/0,/*verbergen=*/0,wahr,nix,0,0,&ausg);
			for(size_t i=0;i<rueck.size();i++) {
				size_t pos=rueck[i].rfind("fax-");
				if (pos!=string::npos) cgelu.insert(rueck[i].substr(pos));
			}
			// b) Hylafaxdateien
			rueck.clear();
			systemrueck("find "+varsphylavz+" -type f -regex '.*/q[0-9]+' -print0 "+(obverb?"":"2>/dev/null")+"|"+linstp->xargspf+" -0 grep -l ^state:8 ",
					aktc?0:obverb,oblog,&rueck,/*obsudc=*/0,/*verbergen=*/0,wahr,nix,0,0,&ausg); // gescheitert
			for(size_t i=0;i<rueck.size();i++) {
				size_t pos=rueck[i].rfind("q");
				if (pos!=string::npos) hmissl.insert(rueck[i].substr(pos+1));
			}
			rueck.clear();
			systemrueck("find "+varsphylavz+" -type f -regex '.*/q[0-9]+' -print0 "+(obverb?"":"2>/dev/null")+"|"+linstp->xargspf+" -0 grep -l ^state:7 ",
					aktc?0:obverb,oblog,&rueck,/*obsudc=*/0,/*verbergen=*/0,wahr,nix,0,0,&ausg); // gelungen
			for(size_t i=0;i<rueck.size();i++) {
				size_t pos=rueck[i].rfind("q");
				if (pos!=string::npos) hgelu.insert(rueck[i].substr(pos+1));
			}
			// c) Hylafax-Protokolldatei
			if (!xferfaxlog.empty()) {
				struct stat entryvz{0};
				if (!lstat(xferfaxlog.c_str(),&entryvz)) {
					rueck.clear();
					// dort von jeder hylanr den jüngsten Eintrag nehmen mit "SEND" oder "UNSENT"; wenn Spalte 14 leer = gefaxt, sonst = nicht gefaxt
					systemrueck("tac "+xferfaxlog+"|awk 'BEGIN{FS=\"\\t\";OFS=FS;arr[\"SEND\"];arr[\"UNSENT\"];};"
							"$2 in arr&&!s[$5]++ {print $2,$5,$14}'",aktc?0:obverb,oblog,&rueck,/*obsudc=*/0,/*verbergen=*/0,wahr,nix,0,0,&ausg);
					for(size_t i=0;i<rueck.size();i++) {
						svec toc;
						aufSplit(&toc,rueck[i],sep);
//						string farbe;
						anfzweg(&toc[1]);
						if (toc[0]=="SEND" && toc[2]=="\"\"") {
							hgelu.insert(toc[1]);
						} else {
							hmissl.insert(toc[1]);
						} // 						if (toc[0]=="SEND" && toc[2]=="\"\"") else
					} // 			for(size_t i=0;i<rueck.size();i++)
				} // 		if (!lstat(xferfaxlog.c_str(),&entryvz))
			} // 	if (!xferfaxlog.empty())

			dober(dsvz,fdn,/*wann=*/(!vru?3:(vru==1?2:1)),aktc?&ausg:0,aktc,&cmissl,&cgelu,&hmissl,&hgelu);
			// Zielverzeichnisse durch Verschieben alter Dateien in Jahres-Unterverzeichnisse gliedern
			if (vru) {
				rueck.clear();
				cmd="find "+dsvz+" -maxdepth 1 -mtime +365 -type f -printf '%TY\\t%T+\\t%p\\n'|sort -k2";
				systemrueck(cmd,aktc?0:obverb,oblog,&rueck,/*obsudc=*/1,/*verbergen=*/0,/*obergebnisanzeig=*/wahr,
						        /*ueberschr=*/nix,/*errm=*/0,/*obincron=*/0,aktc?&ausg:0);
				for(size_t dnr=0;dnr<rueck.size();dnr++) {
					vector<string> tok; 
					aufSplit(&tok,rueck[dnr],'\t');
					pruefverz(dsvz+vtz+tok[0],aktc?0:obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/cuser,/*benutzer=*/"");
					unsigned vfehler{0};
					const string zield{dsvz+vtz+tok[0]};
					verschiebe<string>(tok[2],zield,cuser,&vfehler,/*wieweiterzaehl=*/1,/*obverb=*/aktc?0:1,oblog,aktc?&ausg:0);
					fzahl+=!vfehler;
				} // 		for(size_t dnr=0;dnr<rueck.size();dnr++)
				meld=Tx[T_Aus2]+blaus+dsvz+schwarz+Tx[T_wurden_in_Unterverzeichnisse_verschoben]+gruen+ltoan(fzahl)+schwarz+" "+Tx[T_Dateien];
				if (aktc) ausg<<meld<<endl; else fLog(meld,1,1);
			} // 		if (vru)
		} // 	 for(fit=vzs.begin();fit!=vzs.end();fit++)
	} // 	for(int vru=0;vru<3;vru++)
	if (obverb||oblog) {
		meld=violetts+Txk[T_Ende]+Tx[T_bereinigevz]+schwarz;
		if (aktc) ausg<<meld<<endl; else fLog(meld,obverb,oblog);
	}
	if (aktc)
		hLog(ausg.str());
} // bereinigevz
//α
// Parameter -st / --stop
// aufgerufen in: main
void hhcl::anhalten()
{
	hLog(violetts+Tx[T_anhalten]+schwarz);
	// crontab
	/*
	setztmpcron();
	for(int iru=0;iru<1;iru++) {
		const string befehl=
			"bash -c 'grep \""+saufr[iru]+"\" -q <(crontab -l)&&{ crontab -l|sed \"/"+zsaufr[iru]+"/d\">"+tmpcron+";crontab "+tmpcron+";};:'";
		systemrueck(befehl,obverb,oblog,*//*rueck=*//*0,*//*obsudc=*//*1);
	} // 	for(int iru=0;iru<2;iru++)
  */
	pruefcron("0"); // soll vor Log(Tx[T_Verwende ... stehen
	fLog(blaus+Tx[T_Cron_Aufruf_von]+schwarz+mpfad+blau+Tx[T_gestoppt]+schwarz,1,oblog); //ω
	// services
	//// befehl="systemctl stop capisuite hylafax-faxq hylafax-hfaxd hylafax-faxgetty-"+hmodem+" hylafax >/dev/null 2>&1;:";
	//// systemrueck(befehl,obverb,oblog,/*rueck=*/0,/*obsudc=*/1);
	hylasv1();
	hylasv2(hysrc);
	capisv();
	if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog);
	if (shfaxd) shfaxd->stopdis(obverb,oblog);
	if (sfaxq) sfaxq->stopdis(obverb,oblog);
	if (shylafaxd) shylafaxd->stopdis(obverb>1?obverb:0,oblog);
	if (scapis) scapis->stopdis(obverb,oblog);
	zeigdienste();
} // void hhcl::anhalten() //α
//ω

// aufgerufen in: main (2x)
void hhcl::tu_lista(const string& oberfolg, const string& submids)
{
	// "... submid id ()" wuerde zu Mysql-Fehler fuehren
	hLog(violetts+Tx[T_tu_lista]+schwarz);
	const size_t aktc{0};
	char ***cerg;
	RS rlista(My,"SELECT Ueberm p0, Submid p1, Faxname p2, Empfaenger p3, Fax p4, Erfolg p5 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') Ueberm, Submid, RIGHT(CONCAT(space(75),LEFT(Docname,75)),75) Faxname, "
			"RIGHT(CONCAT(SPACE(30),LEFT(rcname,30)),30) Empfaenger, rcfax Fax, Erfolg, transe "
			"FROM `"+touta+"` WHERE "+(submids.length()<=2?"Erfolg = "+oberfolg+" ":"submid in "+submids+" ")+
			" ORDER BY transe DESC"+(submids.length()<=2?" LIMIT "+dszahl:"")+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",aktc,ZDB);

	if (submids.length()<=2)
		cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<(oberfolg=="1"?Tx[T_erfolgreich]:Tx[T_erfolglos])<<Tx[T_versandte_Faxe]<<schwarz<<endl;
	while (cerg=rlista.HolZeile(),cerg?*cerg:0) {
		cout<<blau<<setw(17)<<cjj(cerg,0)<<"|"<<violett<<setw(14)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(65)<<cjj(cerg,2)<<"|"
			<<schwarz<<setw(30)<<cjj(cerg,3)<<"|"<<blau<<cjj(cerg,4)<<schwarz<<endl;
	} // while (cerg=rlista.HolZeile(),cerg?*cerg:0) 
} // tu_lista

// aufgerufen in: main
void hhcl::tu_listi(const uchar zurauswahl/*=0*/)
{
	hLog(violetts+Tx[T_tu_listi]+schwarz);
	const size_t aktc{0};
	if (zurauswahl) vinca.clear(); // zur Sicherheit 
	char ***cerg;
	RS listi(My,"select p0, p1, p2, p3, p4 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') p0,RIGHT(CONCAT(SPACE(85),LEFT(titel,85)),85) p1,"
			"fsize p2,tsid p3,id p4, transe FROM `"+tinca+"` i "
			" ORDER BY transe DESC LIMIT "+dszahl+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",aktc,ZDB);
	cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<Tx[T_empfangene_Faxe]<<schwarz<<endl;
	size_t j{0};
	while (cerg=listi.HolZeile(),cerg?*cerg:0) {
		cout<<setw(3)<<++j<<") "<<blau<<setw(17)<<cjj(cerg,0)<<"|"<<violett<<setw(84)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(13)<<cjj(cerg,2)<<"|"
			<<schwarz<<setw(17)<<cjj(cerg,3)<<"|"<<blau<<cjj(cerg,4)<<schwarz<<endl;
		if (zurauswahl) vinca<<cjj(cerg,4);
	} // while (cerg=listi.HolZeile(),cerg?*cerg:0) 
} // tu_listi


// Aufrufstatistik, um in zeigweitere die Dateien korrigieren zu koennen:
// bei jedem 3. Aufruf einen Tag, bei jedem 3. Aufruf des Tages 3 Monate und des Monats unbefristet
void hhcl::bestimmtage()
{
	// bei jedem 3. Aufruf einen Tag, bei jedem 3. Aufruf des Tages 30 Tage und des Monats 200 Jahre
	if (monatsaufr==3) {
		tage=ltage; // 73000
	}	else if (tagesaufr==3) {
		tage=mtage; // 30
	}	else if (!(tagesaufr % 3)) {
		tage=ktage; // 1
	} // 		if (monatsaufr==3) else if else if
} // void hhcl::bestimmtage()

void hhcl::bereinigefbox(const size_t aktc)
{
	hLog(violetts+Tx[T_bereinigefbox]+schwarz);
	struct stat entryvz{0};
	svec qrueck;
	if (findv==1) {
		// 20.1.16: wenn dort eine .txt-steht ohne zugehoerige .sff-Datei, dann haelt sie den ganzen Betrieb auf
		cmd=sudc+"find '"+fbwvz+"' -maxdepth 1 -type f -iname 'dt*.vw'"; ////  -printf '%f\\n'";
		systemrueck(cmd,obverb,oblog,&qrueck,/*obsudc*/0,/*verbergen*/0,/*obergebnisanzeig*/wahr,/*ueberschr*/string(),/*errm*/0,/*obincron*/0,/*ausp*/0,/*obdirekt*/0,/*ohnewisch*/1);
	} else findfile(&qrueck,findv,obverb,oblog,0,cfaxusersqvz,/*muster=*/"/dt*\\.vw$",/*tiefe*/1,1,0);
	for(size_t i=0;i<qrueck.size();i++) {
		string stamm,exten;
		getstammext(&qrueck[i],&stamm,&exten);
		const string zugeh{stamm+".tif"};
		if (lstat(zugeh.c_str(),&entryvz)) {
			const string base{base_name(zugeh)};
			RS inouta(My,"SELECT submid FROM `"+touta+"` WHERE submid = '"+base+"'",aktc,ZDB);
			if (inouta.num_rows) {
				fLog(blaus+Tx[T_Verwaiste_Datei]+gruen+qrueck[i]+schwarz+Tx[T_geloescht_Fax_schon_in]+gruen+touta+schwarz+
						Tx[T_archiviert_Ausrufezeichen],1,1);
				tuloeschen(qrueck[i],cuser,obverb,oblog);
				break;
			} else {
				// 31.1.16: ... und wenn diese sich nicht in outa findet ...
				const string waisen{fbgvz+"/waisen"};
				pruefverz(waisen,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/"",/*benutzer=*/cuser);
				uint vfehler{0};
				verschiebe<string>(qrueck[i],waisen,cuser,&vfehler,/*wieweiterzaehl=*/1,obverb,oblog);
			} // if (inouta.num_rows) else 
		} // if (lstat(zugeh.c_str(),&entryvz)) 
	} // for(size_t i=0;i<qrueck.size();i++) 
	hLog(violetts+Txk[T_Ende]+Tx[T_bereinigefbox]+schwarz);
} // void hhcl::bereinigefbox

// in sammlecapi
void hhcl::bereinigecapi(const size_t aktc)
{
	hLog(violetts+Tx[T_bereinigecapi]+schwarz);
	struct stat entryvz{0};
	svec qrueck;
	if (findv==1) {
		// 7.2.16: alte *.lock-Dateien loeschen
		cmd=sudc+"find '"+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.lock'"; ////  -printf '%f\\n'";
		systemrueck(cmd,obverb,oblog,&qrueck);
	} else findfile(&qrueck,findv,obverb,oblog,0,cfaxusersqvz,/*muster=*/"/fax.*\\.lock$",1,1,0);
	for(size_t i=0;i<qrueck.size();i++) {
		string stamm,exten;
		getstammext(&qrueck[i],&stamm,&exten);
		const string zugeh{stamm+".sff"};
		if (lstat(zugeh.c_str(),&entryvz)) {
			tuloeschen(qrueck[i],cuser,obverb,oblog);
		}
	} //       for(size_t i=0;i<qrueck.size();i++)
	qrueck.clear();
	if (findv==1) {
		// 20.1.16: wenn dort eine .txt-steht ohne zugehoerige .sff-Datei, dann haelt sie den ganzen Betrieb auf
		cmd=sudc+"find '"+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.txt'"; ////  -printf '%f\\n'";
		systemrueck(cmd,obverb,oblog,&qrueck);
	} else findfile(&qrueck,findv,obverb,oblog,0,cfaxusersqvz,/*muster=*/"/fax.*\\.txt$",1,1,0);
	for(size_t i=0;i<qrueck.size();i++) {
		string stamm,exten;
		getstammext(&qrueck[i],&stamm,&exten);
		const string zugeh{stamm+".sff"};
		if (lstat(zugeh.c_str(),&entryvz)) {
			const string base{base_name(zugeh)};
			RS inouta(My,"SELECT submid FROM `"+touta+"` WHERE submid = '"+base+"'",aktc,ZDB);
			if (inouta.num_rows) {
				fLog(blaus+Tx[T_Verwaiste_Datei]+gruen+qrueck[i]+schwarz+Tx[T_geloescht_Fax_schon_in]+gruen+touta+schwarz+
						Tx[T_archiviert_Ausrufezeichen],1,1);
				tuloeschen(qrueck[i],cuser,obverb,oblog);
				break;
			} else {
				// 31.1.16: ... und wenn diese sich nicht in outa findet ...
				const string waisen{cfaxusersqvz+"/waisen"};
				pruefverz(waisen,obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/1,/*besitzer=*/"",/*benutzer=*/cuser);
				uint vfehler{0};
				verschiebe<string>(qrueck[i],waisen,cuser,&vfehler,/*wieweiterzaehl=*/1,obverb,oblog);
			} // if (inouta.num_rows) else 
		} // if (lstat(zugeh.c_str(),&entryvz)) 
	} // for(size_t i=0;i<qrueck.size();i++) 
	hLog(violetts+Txk[T_Ende]+Tx[T_bereinigecapi]+schwarz);
} // void hhcl::bereinigecapi

// aufgerufen in aenderefax, zeigweitere
void hhcl::sammlefbox(vector<fsfcl> *fsfvp,const size_t aktc)
{
	// auto const altZDB{ZDB}; auto const altobverb{obverb};
	// ZDB=1; obverb=1;
	hLog(violetts+Tx[T_sammlefbox]+schwarz);
	struct stat entryvz{0};
	if (!lstat(fbwvz.c_str(),&entryvz)) {
		if (!kez&& !bvz && !anhl && !tulista && !tulistf && !tulisti && !tulistw && suchstr.empty())
			bereinigefbox(aktc);
		// ...
		svec qrueck;
		if (findv==1) {
			cmd=sudc+"find '"+fbwvz+"' -maxdepth 1 -type f -name 'dt[0123456789]*.tif'"; ////  -printf '%f\\n'";
			systemrueck(cmd,obverb,oblog,&qrueck,/*obsudc*/0,/*verbergen*/0,/*obergebnisanzeig*/wahr,/*ueberschr*/string(),/*errm*/0,/*obincron*/0,/*ausp*/0,/*obdirekt*/0,/*ohnewisch*/1);
		} else findfile(&qrueck,findv,obverb,oblog,0,fbwvz,/*muster=*/"/dt[0123456789]*\\.tif$",/*tiefe*/1,1,0,0,0,1);
		for(size_t i=0;i<qrueck.size();i++) {
			uchar indb{0};
			char ***cerg;
			RS rs(My,"SELECT id FROM `"+spooltab+"` WHERE CONCAT('"+fbwvz+"/',fbspooldt,'.tif')='"+qrueck[i]+"'",aktc,ZDB);
			if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
			if (!indb) {
				//// <<"i: "<<i<<" "<<violett<<qrueck[i]<<schwarz<<endl;
				//// systemrueck("rm "+qrueck[i].substr(0,qrueck[i].length()-4)+".*",1,0);
				/*7*/fsfcl fsf;
				const size_t p1{qrueck[i].rfind('/')}, p2{qrueck[i].rfind('.')};
				fsf.fbsdt=qrueck[i].substr(p1+1,p2-p1-1);
				fsf.hylanr="-1";
				fsf.pprio=11;
				struct stat entrysend{0};
				fsf.setzfboxstat(this,&entrysend,/*erweitert=*/1);
				fsfvp->push_back(fsf);
			} // if (!indb) 
		} // for(size_t i=0
	} // if (!lstat(cfaxusersqvz.c_str(),&entryvz)) 
	// obverb=altobverb; ZDB=altZDB;
} // void hhcl::sammlefbox

// aufgerufen in aenderefax, zeigweitere
void hhcl::sammlecapi(vector<fsfcl> *fsfvp,const size_t aktc)
{
	hLog(violetts+Tx[T_sammlecapi]+schwarz);
	struct stat entryvz{0};
	if (!lstat(cfaxusersqvz.c_str(),&entryvz)) {
		if (!kez&& !bvz && !anhl && !tulista && !tulistf && !tulisti && !tulistw && suchstr.empty())
			bereinigecapi(aktc);
		svec qrueck;
		if (findv==1) {
			cmd=sudc+"find '"+cfaxuservz+"' -path \"*/sendq/fax*\" -type f -iname 'fax*.sff'"; ////  -printf '%f\\n'";
			systemrueck(cmd,obverb,oblog,&qrueck);
		} else findfile(&qrueck,findv,obverb,oblog,0,cfaxuservz,/*muster=*/"/sendq/fax.*\\.sff$",-1,1,0,0,0,1);
		for(size_t i=0;i<qrueck.size();i++) {
			uchar indb{0};
			char ***cerg;
			RS rs(My,"SELECT id FROM `"+spooltab+"` WHERE CONCAT(capispoolpfad,'/',capispooldt)='"+qrueck[i]+"'",aktc,ZDB);
			if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
			if (!indb) {
				/*5*/fsfcl fsf(qrueck[i],wartend);
				fsf.capisd=base_name(qrueck[i]);
				fsf.hylanr="-1";
				fsf.cspf=dir_name(qrueck[i]);
				struct stat entrysend{0};
				fsf.setzcapistat(this,&entrysend);
				fsfvp->push_back(fsf);
			} // if (!indb) 
		} // for(size_t i=0
	} // if (!lstat(cfaxusersqvz.c_str(),&entryvz)) 
} // void hhcl::sammlecapi

// aufgerufen in: setzhylastat
int hhcl::xferlog(fsfcl *fsfp/*,string *totpages,string *ntries,string *totdials,string *tottries,string *maxtries*/)
{
	// mit grep braucht er fuer eine 400 kb Datei ca. 170 clock()-Einheiten (vorne und hinten)
	// rueckwaerts braucht er fuer eine 400 kb Datei bis zum letzten Satz 93 clock()-Einheiten, bis zum ersten 220000.
	// vorwaerts braucht er fuer diese Datei ca. 9000 clock()-Einheiten
	// #define profiler
	hLog(violetts+"xferlog()"+schwarz);
#ifdef profiler
	perfcl prf("xferlog");
#endif
	int gefunden{0};
#define mitgrep
#ifdef mitgrep
	svec grueck;
#define direkt
#ifdef direkt
	// ggf. broken pipe error; schadet aber experimentell dem Ergebnis nicht, deshalb Fehler unsichtbar
	////  systemrueck(string("tac \"")+xferfaxlog+"\" 2>/dev/null | grep -m 1 \""+this->hmodem+sep+jobid+sep+"\" | cut -f 14",obverb,oblog,&grueck); 
	int aktion{0}; // 0=andere, 1='SEND', 2='UNSENT'
	//// systemrueck("tac \""+xferfaxlog+"\" 2>/dev/null | grep -m 1 \"tty[^"+sep+"]*"+sep+fsfp->hylanr+sep+"\" | cut -f1,2,14,20",obverb,oblog,&grueck); 
	struct stat trst{0};
	if (!lstat(xferfaxlog.c_str(),&trst)) {
		// 2.3.17 in Eintraegen UNSENT und SUBMIT kann tty... auch fehlen
		systemrueck("tac \""+xferfaxlog+"\" 2>/dev/null | grep -am 1 \"^[^"+sep+"]*"+sep+"[^"+sep+"]*"+sep+"[^"+sep+"]*"+sep+"[^"+sep+"]*"+
				sep+fsfp->hylanr+sep+"\" | cut -f1,2,8,14,20",obverb,oblog,&grueck,/*obsudc=*/0); 
		fsfp->sendqgespfad.clear();
		if (grueck.size()) {
			gefunden=1;
			vector<string> tok;
			aufSplit(&tok,grueck[0],sep);
			if (tok.size()<=2) fsfp->hgerg=grueck[0];
			if (tok.size()) {
				// a) fuehrt (zumindest hier) zu grottenfalschen Daten
				//			if (strptime(tok[0].c_str(),"%m/%d/%y %H:%M",&tm))
				// b) get_time ist (zumindest hier) noch nicht in <iomanip>
				//       istringstream iss(tok[0]);
				//			 iss>>get_time(&tm,"%m/%d/%y %H:%M");
				//			 if (!iss.fail()) 
				// c) das geht:
				int y{0},M{0},d{0},h{0},m{0};
				if (sscanf(tok[0].c_str(), "%d/%d/%d %d:%d", &M, &d, &y, &h, &m)==5) {
					struct tm tm={0};
					tm.tm_year=y+(y<100?100:-1900);
					tm.tm_mon=M-1;
					tm.tm_mday=d;
					tm.tm_hour=h;
					tm.tm_min=m;
					tm.tm_sec=0;
					tm.tm_isdst=-1;
					fsfp->xtts=mktime(&tm);
				} // 			if (sscanf(tok[0].c_str(), "%d/%d/%d %d:%d", &M, &d, &y, &h, &m)==5)
				if (tok.size()>1) {
					fsfp->hstatus=tok[1];
					if (tok[1]=="SEND") aktion=1;
					else if (tok[1]=="UNSENT") aktion=2;
					if (tok.size()>2) {
						fsfp->number=tok[2];
						anfzweg(&fsfp->number);// Telefonnummer; Anfuehrungszeichen entfernen
						if (tok.size()>3) {
							fsfp->hgerg=tok[3];
							anfzweg(&fsfp->hgerg); // Anfuehrungszeichen entfernen
							switch (aktion) {
								case 2: 
									fsfp->hylastat=gescheitert;
									fsfp->hstate="8"; 
									break;
								case 1: 
									if (fsfp->hgerg.empty()) {
										fsfp->hylastat=gesandt;
										fsfp->hstate="7"; 
									} else {
										fsfp->hylastat=verarb;
										fsfp->hstate="6";
									} // 									if (fsfp->hgerg.empty()) else
									break;
							} //         switch (aktion)
							if (tok.size()>4) {
								vector<string> toi;
								aufSplit(&toi,tok[4],'/');
								if (toi.size()) {
									fsfp->hpages=toi[0];
									if (toi.size()>1) {
										//										if (ntries) *ntries=toi[1];
										if (toi.size()>2) {
											if (toi.size()>3) {
												fsfp->hdials=toi[3];
												//											if (totdials) *totdials=toi[3];
												if (toi.size()>4) {
													fsfp->maxdials=toi[4];
													if (toi.size()>5) {
														//														if (tottries) *tottries=toi[5];
														/*
															 if (toi.size()>6) KLA
															 if (maxtries) *maxtries=toi[6];
															 KLZ //                       if (toi.size()>6)
														 */
													} //                       if (toi.size()>5)
												} //                     if (toi.size()>4)
											} //                   if (toi.size()>3)
										} //                 if (toi.size()>2)
									} //               if (toi.size()>1) 
								} //             if (toi.size()) 
							} // 							if (tok.size()>4)
						} //           if (tok.size()>3) 
					} //         if (tok.size()>2) 
				} //       if (tok.size()>1)
			} //     if (tok.size())
#else
			    // ggf. broken pipe error
			systemrueck("tac \""+xferfaxlog+"\" 2>/dev/null|grep -am 1 \""+this->hmodem+sep+fsfp->hylanr+sep+"\"",obverb,oblog,&grueck,/*obsudc=*/0); 
			if (grueck.size()) KLA
				vector<string> tok;
			aufSplit(&tok,&grueck[grueck.size()-1],sep);
#endif // direkt else
#else // mitgrep else
			mdatei f(xferfaxlog.c_str(),ios::in|ios::binary); 
			string zeile;
#define rueckwaerts
#ifdef rueckwaerts
			char ch;
			string rzeile;
			if (f.is_open()) KLA
				f.seekg(-1,ios::end); 
			for(;f.get(ch);f.seekg(-2,ios::cur)) KLA
				if (ch==10) KLA
					zeile.clear();
			for(size_t index=rzeile.length()-1;index!=string::npos;index--) KLA
				zeile+=rzeile[index];
			KLZ
#else // rueckwaerts
				while(getline(f,zeile)) KLA
#endif // rueckwaerts
					vector<string> tok;
			aufSplit(&tok,&zeile,sep);
#endif // mitgrep else
#ifndef direkt
			if (tok.size()>15) KLA
				if (tok[4]==fsfp->hylanr) KLA
					gefunden=1;
			fsfp->herg=tok[13];
			if ((fsfp->herg)=="\"\"") fsfp->herg.clear();
			////            if (erg->length()>1) if ((*erg)[0]=='"' && (*erg)[erg->length()-1]=='"') *erg=erg->substr(1,erg->length()-2);
			if (obverb) KLA
				hLog(blaus+"tok[13]: "+schwarz+fsfp->herg);
			KLZ
#ifndef mitgrep
#ifdef rueckwaerts
				break;
			KLZ // if (tok[4]==fsfp->hylanr) KLA
				KLZ // if (tok.size()>15)
				rzeile.clear();
			KLZ else KLA
				rzeile+=ch;
#endif // rueckwaerts
#endif // not mitgrep
			KLZ // 
				KLZ // if (ch==10)
#endif  // not direkt
		} else {
			fsfp->hylastat=fehlend;
		} // if f.is_open() oder (grueck.size()
	} // 	if (!lstat(xferfaxlog.c_str(),&trst))
#ifdef profiler
	prf.ausgeb();
#endif
	return gefunden;
} // void xferlog(string varsphylavz, string jobid, string *erg)


// aufgerufen in hhcl::aenderefax, hhcl::untersuchespool, hhcl::zeigweitere
void hhcl::setzhylastat(fsfcl *fsf, uchar *hyla_uverz_nrp, uchar startvznr, int *obsfehltp/*=0*/, struct stat *est/*=0*/) 
{
	hLog(violetts+Tx[T_setzhylastat]+schwarz);
	uchar obsfehlt{1};
	yLog(obverb,oblog,0,0,"%shylanr: %s%s%s %s%s hyla_uverz_nrp: %s%lu%s startverzn: %s%lu%s",violett,schwarz,fsf->hylanr.c_str(),violett,
			Tx[T_setzhylastat],schwarz,blau,*hyla_uverz_nrp,schwarz,blau,startvznr,schwarz);
	// wenn in *hyla_uverz_nrp '1' uebergeben wird, nur in sendq suchen
	// Rueckgabe: 0 = in doneq oder archive gefunden
	struct stat entryprot{0};
	fsf->sendqgespfad.clear();
	if (fsf->hylanr!="0") {
		svec qrueck;
		const string wo{hsendqvz+" "+(*hyla_uverz_nrp?"":hdoneqvz+" "+harchivevz)};
		if (findv==1) {
			const string cmd{"find "+wo+" -name 'q"+fsf->hylanr+"'"};
			systemrueck(cmd,obverb,oblog,&qrueck,/*obsudc=*/1);
		} else findfile(&qrueck,findv,obverb,oblog,0,wo,/*muster=*/"/q"+fsf->hylanr+"$",-1,1,0,0,0,1);
		if (qrueck.size()) {
			fsf->hqdt=qrueck[0];
			obsfehlt=lstat(fsf->hqdt.c_str(), &entryprot);
			*hyla_uverz_nrp=(qrueck.at(0).find("/doneq")==string::npos && qrueck.at(0).find("/archive")==string::npos);
		} //   if (qrueck.size())
		if (obverb) {
			hLog(schwarzs+"obsfehlt: "+blau+(obsfehlt?"1":"0")+schwarz+", hyla_uverz_nr: "+blau+(*hyla_uverz_nrp?"1":"0")+schwarz);
		} // 		if (obverb)
		if (obsfehltp) *obsfehltp=obsfehlt;

		if (!obsfehlt) {
			string pdf1,pdf2,ttss,killtimes;
			pruefverz(dir_name(fsf->hqdt),obverb,oblog,/*obmitfacl=*/1,/*obmitcon=*/0);
			schAcl<WPcl> hylcnfC("cfcnfC", new vector<aScl>{
						{"state",&fsf->hstate},
						{"totdials",&fsf->hdials},
						{"status",&fsf->hstatus},
						{"statuscode",&fsf->hstatuscode},
						{"!pdf",&pdf1},
						{"tts",&ttss},
						{"number",&fsf->number},
						{"maxdials",&fsf->maxdials},
						{"pdf",&pdf2},
						{"killtime",&killtimes}
						});
			confdcl hqc(fsf->hqdt,obverb,':');
			hqc.kauswert(&hylcnfC,obverb,1);
			fsf->xtts=atol(ttss.c_str());
			fsf->killtime=atol(killtimes.c_str());
			string *pdf{pdf1.empty()?&pdf2:&pdf1};
			svec tok;
			aufiSplit(&tok,*pdf,":",1,obverb>0?obverb-1:0,oblog);
			fsf->sendqgespfad=this->varsphylavz+vtz+tok[tok.size()-1];
			if (est) lstat(fsf->sendqgespfad.c_str(),est); 
			fsf->hylastat=static_cast<FxStat>(atol(fsf->hstate.c_str()));
			hgelesen=hqc.obgelesen;
		} // 		if (!obsfehlt)
		if (obsfehlt||!hgelesen) {
			// wenn also die Datenbankdatei weder im Spool noch bei den Erledigten nachweisbar ist
			if (est) memset(est,0,sizeof *est);
			this->xferlog(fsf);
		}
	} // 	if (fsf->hylanr!="0") 
	if (fsf->hylastat==init) fsf->hylastat=fehlend; // 28.7.19
	hLog(violetts+Txk[T_Ende]+Tx[T_setzhylastat]+", hylastat: "+blau+FxStatS(&fsf->hylastat)+schwarz);
} // setzhylastat


// aufgerufen in: zeigweitere, aenderefax
void hhcl::sammlehyla(vector<fsfcl> *fsfvp,const size_t aktc)
{
	hLog(violetts+Tx[T_sammlehyla]+schwarz);
	struct stat entryvz{0};
	if (!lstat(hsendqvz.c_str(),&entryvz)) {
		svec qrueck;
		if (findv==1) {
			cmd=sudc+"find '"+hsendqvz+"' -maxdepth 1 -type f -regex '.*/q[0-9]+' -printf '%f\\n'";
			systemrueck(cmd,obverb,oblog,&qrueck);
		} else findfile(&qrueck,findv,obverb,oblog,1,hsendqvz,/*muster=*/"/q[0123456789]+$",1,1,0,0,0,1);
		for(size_t i=0;i<qrueck.size();i++) {
			uchar indb{0};
			const string hylanr{qrueck[i].substr(1)};
			char ***cerg;
			RS rs(My,"SELECT id FROM `"+spooltab+"` WHERE hylanr="+hylanr,aktc,ZDB); //// "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
			if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
			if (!indb) {
				/*4*/fsfcl fsf(hylanr); //// fsf(rueck[i]);
				uchar hyla_uverz_nr{1};
				/*//fsf.*/
				setzhylastat(&fsf, &hyla_uverz_nr, 2, 0, 0);
				fsfvp->push_back(fsf);
			} // if (!indb)
		} // for(size_t i=0;i<rueck.size();i++) 
	} // if (!lstat(hsendqvz.c_str(),&entryvz))
	hLog(violetts+Txk[T_Ende]+Tx[T_sammlehyla]+schwarz);
} // void hhcl::sammlehyla(vector<fsfcl> *fsfvp)


// Zeige Dateien im Spool an, die nicht in der Spool-Tabelle stehen
// aufgerufen in: pvirtnachrueckfragen
void hhcl::zeigweitere()
{
	hLog(violetts+Tx[T_zeigweitere]+schwarz);
	const size_t aktc{4};
	static int obtitel{0};
	stringstream ausg; //      ausg.str(std::string()); ausg.clear();
	//// <<"Korrektur wird durchgefuehrt ueber Tage: "<<tage<<endl;
	if (obfa[0]||obweg[0]==1) {
		vector<fsfcl> fsfcv;
		sammlefbox(&fsfcv,aktc);
		for(size_t i=0;i<fsfcv.size();i++) {
			if (!obtitel) {
				ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
				obtitel=1;
			} // 			if (!obtitel) 
			fsfcv[i].fboxausgeb(this, &ausg, 0, obverb, oblog, ++faxord);
		} //     for(size_t i=0;i<fsfcv.size();i++)
	} // if (obcapi)
	if (obfa[1]||obweg[1]==1) {
		vector<fsfcl> fsfcv;
		sammlecapi(&fsfcv,aktc);
		for(size_t i=0;i<fsfcv.size();i++) {
			if (!obtitel) {
				ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
				obtitel=1;
			} // 			if (!obtitel) 
			fsfcv[i].capiausgeb(this, &ausg, maxcdials, 0, obverb, oblog, ++faxord);
		} //     for(size_t i=0;i<fsfcv.size();i++)
	} // if (obcapi)
	if (obfa[2]||obweg[2]==1) {
		vector<fsfcl> fsfhv;
		sammlehyla(&fsfhv,aktc);
		for(size_t i=0;i<fsfhv.size();i++) {
			if (!obtitel) {
				ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
				obtitel=1;
			} // 		for(size_t i=0;i<fsfhv.size();i++)
			fsfhv[i].hylaausgeb(&ausg, this/*, 0*/, 0, obverb, 1, oblog);
		} //     for(size_t i=0;i<fsfhv.size();i++) 
	} // if (obhyla) 
	if (obtitel) fLog(ausg.str(),1,oblog);
	hLog(violetts+Txk[T_Ende]+Tx[T_zeigweitere]+schwarz);
} // void hhcl::zeigweitere


// aufgerufen in: aenderefax, untersuchespool, capiausgeb, setzhylastat, hylaausgeb
const char* FxStatS(const FxStat *const i) 
{
	//  enum FxStat:uchar {init,wartend,gesandt,gescheitert,fehlend,woasined};
	if (i) {
		switch (*i){
			case init: return "init";
			case gestrichen: return Tx[T_gestrichen];
			case schwebend: return Tx[T_schwebend];
			case wartend: return Tx[T_wartend];
			case blockiert: return Tx[T_blockiert]; 
			case bereit: return Tx[T_bereit];
			case verarb: return Tx[T_verarb];
			case gesandt: return Tx[T_gesandt];
			case gescheitert: return Tx[T_gescheitert];
			case fehlend: return Tx[T_nicht_in_der_Warteschlange];
			default:;
		} // switch (*i)
	} // if (i)
	return Tx[T_woasined];
} // FxStatS

//archiviert den Datensatz
// aufgerufen in: untersuchespool, korrigierehyla
void fsfcl::archiviere(DB *const My, hhcl *const hhip, const struct stat *const entryp, const uchar obgescheitert, const FaxTyp ftyp, 
		uchar *geloeschtp, const size_t aktc, const int obverb, const int oblog)
{
////	int altobverb{obverb}; int wahr{1}; memcpy((void*)&obverb,&wahr, sizeof wahr); hhip->ZDB=1;
	//  string nob=ltoan((int)!obgescheitert);
	fLog(violetts+Tx[T_archiviere]+schwarz+Tx[T_obgescheitert]+blau+ltoan((int)obgescheitert)+schwarz/*+" !obgescheitert: "+nob+*/,obverb,oblog);
	// Voraussetzung: telnr, original, id; veraendert: geloescht
	RS rins(My,hhip->touta); 
	string getname,bsname;
	hhip->getSender(telnr,&getname,&bsname,aktc);
	vector<instyp> einf;
	einf.push_back(/*2*/instyp(My->DBS,"titel",&bsname));
	einf.push_back(/*2*/instyp(My->DBS,"rcname",&getname));
	if (ftyp==capi) {if (cdd.empty()) cdd="0000-00-00";} else if (ftyp==hyla) {if (hdd.empty()) hdd="0000-00-00";}
	string fdd;
  if (ftyp==fritz) {
		stringstream zpstr;
		zpstr<<ztacl(fbzp,"%F %T");
		fdd=zpstr.str();
	}
	einf.push_back(/*2*/instyp(My->DBS,"submt",ftyp==capi?&cdd:ftyp==fritz?&fdd:&hdd));
	einf.push_back(/*2*/instyp(My->DBS,"submid",ftyp==capi?&capisd:ftyp==fritz?&fbsdt:&hylanr));
	string patid;
	if (!original.empty()) {
		const char* ocstr=original.c_str(); // da c_str() fluechtig sein koennte
		char* patidp = (char*)strcasestr(ocstr,"pid ");
		if (patidp) {
			if (patidp==ocstr || (patidp>ocstr && (strchr(" .,;",*(patidp-1))))){
				for(patidp+=4;*patidp && *patidp!=' ';patidp++) {
					if (strchr("0123456789",*patidp)) patid+=*patidp;
				}  //           for(patidp+=4;*patidp && *patidp!=' ';patidp++)
			} //         if (patidp==ocstr || (patidp>ocstr && (strchr(" .,;",*(patidp-1)))))
		} //       if (patidp)
	} //     if (!original.empty())
	if (patid.empty()) patid="0";
	einf.push_back(/*2*/instyp(My->DBS,"pid",&patid));
	einf.push_back(/*2*/instyp(My->DBS,"Erfolg",(int)!obgescheitert));
	einf.push_back(/*2*/instyp(My->DBS,"docname",&original));
	fLog("original (docname): "+blaus+original+schwarz,obverb,oblog);
	einf.push_back(/*2*/instyp(My->DBS,"idudoc",&idudoc));
	if (!xtts) xtts=time(0);
	////<<gruen<<"xtts: "<<rot<<xtts<<schwarz<<endl;
	//// char buf[100];
	//// strftime(buf, sizeof(buf), "%d.%m.%y %T", localtime(&xtts));
	//// <<"buf: "<<buf<<endl;
	einf.push_back(/*2*/instyp(My->DBS,"transe",&xtts));
	if (!telnr.empty()) {
		const string stdfax{hhip->stdfaxnr(telnr)};
		einf.push_back(/*2*/instyp(My->DBS,"rcfax",&stdfax));
	} //     if (!telnr.empty())
	if (!adressat.empty()) einf.push_back(/*2*/instyp(My->DBS,"adressat",&adressat));
	einf.push_back(/*2*/instyp(My->DBS,"fsize",entryp->st_size>4294967295?0:entryp->st_size)); // int(10)
	einf.push_back(/*2*/instyp(My->DBS,"pages",pseiten));
	svec eindfeld; eindfeld<<"submt";eindfeld<<"submid";
	caus<<"vor tbins"<<endl;
	rins.tbins(&einf,aktc,/*sammeln=*/0,/*obverb=*/hhip->ZDB,/*idp=*/0,/*eindeutig=*/0,eindfeld);  // einfuegen
	caus<<"nach tbins"<<endl;
	if (rins.fnr) {
		fLog(Tx[T_Fehler_af]+drots+ltoan(rins.fnr)+schwarz+Txk[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,1);
	} //     if (runde==ruz-1)
	if (!rins.fnr && geloeschtp) { 
		RS rsloe(My,"DELETE FROM `"+hhip->spooltab+"` WHERE id = \""+id+"\"",aktc,hhip->ZDB);
		*geloeschtp=1;
	} // if (!rins.fnr) 
////	memcpy((void*)&obverb,&altobverb, sizeof altobverb);
} // archiviere

// aufgerufen in: aenderefax, untersuchespool
int fsfcl::loeschefbox(hhcl *const hhip, const int obverb, const int oblog)
{
	int *obvp=(int*)&obverb; *obvp=1;
	fLog(violetts+Tx[T_loeschefbox]+schwarz,obverb,oblog);
	int zdng{0}; // Zahl der nicht Geloeschten
	if (!fbsdt.empty()) {
		for(uchar ru=0;ru<2;ru++) {
			const string zuloe{hhip->fbwvz+vtz+fbsdt+(ru?".vw":".tif")};
			zdng+=tuloeschen(zuloe,"",1,oblog);
		} //     for(uchar ru=0;ru<2;ru++) 
	} else { 
		zdng=1;
	} // if (!fbsdt.empty())
	*obvp=0;
	return zdng;
} // void fsfcl::loeschefbox


// aufgerufen in: aenderefax, untersuchespool
int fsfcl::loeschecapi(const int obverb, const int oblog)
{
	fLog(violetts+Tx[T_loeschecapi]+schwarz,obverb,oblog);
	string stamm,exten;
	getstammext(&capisd,&stamm,&exten);
	int zdng{0}; // Zahl der nicht Geloeschten
	if (!stamm.empty()) {
		for(uchar ru=0;ru<2;ru++) {
			const string zuloe{cspf+vtz+stamm+(ru?".txt":".sff")};
			zdng+=tuloeschen(zuloe,"",1,oblog);
		} //     for(uchar ru=0;ru<2;ru++) 
	} else { 
		zdng=1;
	} // if (!stamm.empty())
	return zdng;
} // void fsfcl::loeschecapi

// Rueckgabe: Zahl der nicht geloeschten Eintraege
// aufgerufen in: aenderefax, loescheallewartenden, untersuchespool,
int fsfcl::loeschehyla(hhcl *const hhip, const int obverb, const int oblog)
{
	fLog(violetts+Tx[T_loeschehyla]+schwarz,obverb,oblog);
	if (hylanr!="0" && !hylanr.empty()) {
		svec qrueck;
		if (findv==1) {
			// wenn Datei nicht mehr in sendq, sondern in doneq, sei es gelungen oder gescheitert, dann ist Loeschen sinnlos
			systemrueck("find '"+hhip->hsendqvz+"' -name q"+hylanr,obverb,oblog,&qrueck,/*obsudc=*/1);
		} else findfile(&qrueck,findv,obverb,oblog,0,hhip->hsendqvz,/*muster=*/"/q"+hylanr+"$");
		if (!qrueck.size()) {
			return 0;
		}
		hhip->hylasv1();
		hhip->hylasv2(hysrc);
		const uchar vmax{5};
		for(uchar iru=0;iru<vmax;iru++) {
			if (iru) {
				if (hhip->sfaxgetty) hhip->sfaxgetty->restart(obverb+1,oblog);
				if (hhip->shfaxd) hhip->shfaxd->restart(obverb+1,oblog);
				if (hhip->sfaxq) hhip->sfaxq->restart(obverb+1,oblog);
				//// systemrueck("systemctl restart '"+hhip->sfaxgetty->sname+"' '"+hhip->shfaxd->sname+"' '"+hhip->sfaxq->sname+"'",
				////  obverb-1,oblog,/*rueck=*/0,/*obsudc=*/1);
			} // if (iru) 
			svec rueck, rmerg;
			string fuser;
			struct stat trst{0};
			if (!lstat(hhip->xferfaxlog.c_str(),&trst)) {
				systemrueck("tac \""+hhip->xferfaxlog+"\" 2>/dev/null|grep -am 1 \"SUBMIT"+sep+sep+sep+hylanr+"\"|cut -f18|sed -e 's/^\"//;      s/\"$//'",
						obverb, oblog,&rueck,/*obsudc=*/0);
				fLog(Tx[T_Loesche_Fax_hylanr]+hylanr+" ...",-1,0);
				if (rueck.size() && rueck[0]!="root") {
					fuser=rueck[0]; 
					//// <<violett<<"fuser: "<<fuser<<schwarz<<endl;
					systemrueck("su -c \"faxrm "+hylanr+"\" "+fuser+" 2>&1",oblog,obverb,&rmerg,/*obsudc=*/1);
				} else {
					systemrueck("faxrm "+hylanr+" 2>&1",oblog,obverb,&rmerg,/*obsudc=*/1);
				}
				// folgender Befehl kann einen tac: write error: Broken pipe -Fehler erzeugen
				// systemrueck("su -c \"faxrm "+hylanr+"\" $(tac \""+hhip->xferfaxlog+"\"|grep -am 1 \"SUBMIT"+sep+sep+sep+hylanr+"\"|cut -f18|sed -e 's/^\"//;s/\"$//') 2>&1",2,oblog,&rmerg,/*obsudc=*/1);
				if (rmerg.size()) {
					if (rmerg[0].find(" removed")!=string::npos || rmerg[0].find("job does not exist")!=string::npos) {
						fLog(blaus+Tx[T_erfolgreich_geloescht_fax_mit]+schwarz+hylanr,1,1);
						return 0;
					}
					fLog(rots+Tx[T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm]+hylanr+"`:\n    "+schwarz+rmerg[0],1,1);
				} // if (rmerg.size()) 
			} else {
				break;
			} // 	if (!lstat(hhip->xferfaxlog.c_str(),&trst))
		} // for(uchar iru=0;iru<vmax;iru++) 
	} // if (hylanr!="0" && !hylanr.empty()) 
	return 1;
} // int fsfcl::loeschehyla

// aufgerufen in: untersuchespool, aenderefax, zeigweitere
void fsfcl::fboxausgeb(hhcl *const hhip, stringstream *ausgp, uchar fuerlog, int obverb, int oblog, ulong faxord)
{
	fLog(violetts+Tx[T_fboxausgeb]+schwarz+"  fboxstat: "+blau+FxStatS(&fboxstat)+schwarz,obverb,oblog);
	if (!fuerlog) *ausgp<<blau<<endl;
	if (faxord) *ausgp<<faxord<<")";
	else *ausgp<<"  ";
	*ausgp<<"Fbox: "<<schwarz;
	const char* const farbe1{(fboxstat<wartend||fboxstat>gesandt?hgrau:blau)}, // static_cast<FxStat>(...) nicht noetig
				* const farbe2{(fboxstat<wartend||fboxstat>gesandt?hgrau:schwarz)};
	*ausgp<<farbe1<<setw(11)<<FxStatS(&fboxstat)<<schwarz;
	if (fboxstat!=fehlend) {
		*ausgp<<","<<farbe1<<setw(3)<<fbdials<<"/"<<fbmaxdials<<farbe2<<(fboxstat==verarb?umgek:"")<<Tx[T_Anwahlen]<<schwarz;
		*ausgp<<farbe1<<ztacl(fbnzp,"%d.%m.%y %T")<<farbe2;
		*ausgp<<",T.:"<<farbe1<<setw(12)<<telnr<<farbe2; 
		*ausgp<<Tx[T_kommaDatei]<<rot<<hhip->fbwvz+vtz+fbsdt+".tif"/*sendqgespfad*/<<farbe2;
		*ausgp<<Tx[T_bzw]<<farbe1<<"*.vw"<<schwarz;
		if (fbdials.empty()) fbdials="0";
	} // if (fboxstat!=fehlend) 
} // void fsfcl::fboxausgeb

// ermittelt die letzten Sendedaten zu sendqgespfad mit fsf.capistat, schreibt die Zahl der Versuche in ctries zurueck und ergaenzt den 
// Anzeigezeiger ausgp
// aufgerufen in: aenderefax, untersuchespool, zeigweitere
void fsfcl::capiausgeb(hhcl *const hhip, stringstream *ausgp, const string& maxcdials, uchar fuerlog, int obverb, int oblog,ulong faxord)
{
	fLog(violetts+Tx[T_capiausgeb]+schwarz+"  capistat: "+blau+FxStatS(&capistat)+schwarz+ " maxcdials: "+blau+maxcdials+schwarz,obverb,oblog);
	if (!fuerlog) *ausgp<<blau<<endl;
	if (faxord) *ausgp<<faxord<<")";
	else *ausgp<<"  ";
	*ausgp<<"Capi: "<<schwarz;
	const char* const farbe1{(capistat<wartend||capistat>gesandt?hgrau:blau)}, // static_cast<FxStat>(...) nicht noetig
				* const farbe2{(capistat<wartend||capistat>gesandt?hgrau:schwarz)};
	*ausgp<<farbe1<<setw(11)<<FxStatS(&capistat)<<schwarz;
	/*//
		if (capistat==wartend) {
	 *ausgp<<schwarz<<" "<<Tx[T_wartend]<<schwarz;
	 } else if (capistat==gesandt) {
	 *ausgp<<blau<<" "<<Tx[T_gesandt]<<schwarz;
	 } else if (capistat==gescheitert) {
	 *ausgp<<drot<<" "<<Tx[T_gescheitert]<<schwarz;
	 } else if (capistat==fehlend) {
	//    *ausgp<<hgrau<<" "<<FxStatS(&capistat)<<schwarz; // bringt zur Zeit keinen Vorteil
	 *ausgp<<hgrau<<" "<<Tx[T_nicht_in_der_Warteschlange]<<schwarz;
	 }
	 */
	if (capistat!=fehlend) {
		////    if (cpplies(suchtxt,cccnfA,cs)) KLA
		//// RS rmod(My,string("update spool set capidials=")+cccnfA[0].val+" where id = "+cjj(cerg,0),ZDB);
		if (ctries.empty()) ctries="0";
		*ausgp<<","<<farbe1<<setw(3)<<ctries<<"/"<<maxcdials<<farbe2<<(capistat==verarb?umgek:"")<<Tx[T_Anwahlen]<<schwarz;
		////                      if (versuzahl>12) ausg<<"zu spaet, ";
		struct tm tm{0};
		for(unsigned im=0;im<hhip->tmmoelen;im++) {
			if (strptime(starttime.c_str(), tmmoegl[im], &tm)) break;
		}
		// naechster Aufrufzeitpunkt (ab 7/19)
		if (1) {
			tm.tm_isdst=-1; // sonst wurde eine Stunde hinzugezaehlt
			time_t letzt{mktime(&tm)};
			if (letzt!=-1) {
				static svec minv;
				if (!minv.size()) {
					aufSplit(&minv,hhip->send_delays,",");
				}
				const long ctriesn{atol(ctries.c_str())};
				if ((long)minv.size()>=ctriesn) {
					letzt+=atol(minv[ctriesn].c_str());
				}
			}
			pthread_mutex_lock(&timemutex);
			memcpy(&tm,localtime(&letzt),sizeof tm); // gmtime
			pthread_mutex_unlock(&timemutex);
		} // if (1)

		//// char buf[100];
		//// strftime(buf, sizeof(buf), "%d.%m.%y %T", &tm);
		//// *ausgp<<blau<<buf<<schwarz; 
		*ausgp<<farbe1<<put_time(&tm,"%d.%m.%y %T")<<farbe2;
		*ausgp<<",T.:"<<farbe1<<setw(12)<<dialstring<<farbe2; 
		*ausgp<<Tx[T_kommaDatei]<<rot<<sendqgespfad<<farbe2;
		*ausgp<<Tx[T_bzw]<<farbe1<<"*.txt"<<farbe2;
	} // if (capistat!=fehlend) 
} // void fsfcl::capiausgeb

// aufgerufen in: untersuchespool, aenderefax, sammlefbox
void fsfcl::setzfboxstat(hhcl *hhip, struct stat *entrysendp,uchar erweitert/*0*/)
	// benoetigt aus this: fbsdt
{
	int dateifehlt{0};
	if(fbsdt.empty()) {
		fboxstat=fehlend;
	} else {
		sendqgespfad=hhip->fbwvz+vtz+fbsdt+".vw";
		if ((dateifehlt=lstat(sendqgespfad.c_str(),entrysendp))) {
				// gesandte und gescheiterte Faxe wurden von capisuite entsprechend umbenannt
				for(fboxstat=gesandt;fboxstat<=gescheitert;fboxstat=static_cast<FxStat>(fboxstat+1)) { 
					// entspr. gefaxte/gescheiterte Datei in capisuite
					sendqgespfad=(fboxstat==gescheitert?hhip->fbnvz:hhip->fbgvz)+vtz+fbsdt+".vw";
					fLog(string("fboxstat: ")+ltoan((int)fboxstat)+" "+blau+sendqgespfad+schwarz,1,hhip->oblog);
					if (!(dateifehlt=lstat((sendqgespfad.c_str()), entrysendp))) break; 
				}  //         for(fboxstat=gesandt;fboxstat<=gescheitert;fboxstat=static_cast<FxStat>(fboxstat+1))
				// hier koennte fboxstat auch fehlend sein
		}
		liesvw(sendqgespfad,&fbzp,/*minststp*/0,erweitert?&telnr:0,erweitert?&original:0,&fbdials,&fbmaxdials,&fboxstat,&fbnzp);
	} // 	if(fbsdt.empty()) else
} // void fsfcl::setzfboxstat

// aufgerufen in: untersuchespool, aenderefax
void fsfcl::setzcapistat(hhcl *hhip, struct stat *entrysendp)
{
	int dateifehlt{0},
			protpos{0};
	if (capisd.empty()) {
		capistat=fehlend;
	} else {
		string aktuser;
		sendqgespfad=cspf+vtz+capisd;
		size_t p1,p2;
		if ((p1=cspf.rfind(vtz))) if ((p2=cspf.rfind(vtz,p1-1))) {
			aktuser=cspf.substr(p2+1,p1-p2-1);
			if ((dateifehlt=lstat(sendqgespfad.c_str(),entrysendp))) {
				// gesandte und gescheiterte Faxe wurden von capisuite entsprechend umbenannt
				for(capistat=gesandt;capistat<=gescheitert;capistat=static_cast<FxStat>(capistat+1)) { 
					// entspr. gefaxte/gescheiterte Datei in capisuite
					sendqgespfad=(capistat==gescheitert?hhip->cfailedvz:hhip->cdonevz)+vtz+aktuser+"-"+capisd; 
					fLog(string("capistat: ")+ltoan((int)capistat)+" "+blau+sendqgespfad+schwarz,hhip->obverb,hhip->oblog);
					if (!(dateifehlt=lstat((sendqgespfad.c_str()), entrysendp))) break; 
				}  //         for(capistat=gesandt;capistat<=gescheitert;capistat=static_cast<FxStat>(capistat+1))
				// hier koennte capistat auch fehlend sein
			}
			if (!dateifehlt) {	
				if ((protpos=holcapiprot(hhip->obverb))<0) {
					capistat=fehlend;
				} else if (capistat!=gesandt && capistat!=gescheitert) {
					struct stat statlock{0};
					if (lstat((sendqgespfad.substr(0,protpos)+".lock").c_str(),&statlock))
						capistat=wartend;
					else
						capistat=verarb;
				} // 				if ((p3=holcapiprot(obverb))<0)
			}  //       if (!lstat(sendqgespfad.c_str(),entrysendp)) else
		} // if ((p1=cspf.rfind(vtz))) if ((p2=cspf.rfind(vtz,p1-1))) 
	} //   if (capisd.empty()) else
} // fsfcl::setzcapistat

// aufgerufen in setzcapistat
// Ergebnis: p1 (>=0): Datei war da und enthielt Punkt, -2: Datei war nicht da oder enthielt keinen Punkt
int fsfcl::holcapiprot(int obverb)
{
	size_t p1{sendqgespfad.rfind('.')};
	if (p1!=string::npos) {
		const string sdgstxtdt{sendqgespfad.substr(0,p1)+".txt"};
		struct stat sdgstxtstat{0};
		if (!lstat(sdgstxtdt.c_str(),&sdgstxtstat)) {
			//						const string feld[]{/*"dialstring","starttime",*/"tries","user"/*,"addressee","subject"*/};
			schAcl<WPcl> sdgsC("sdgsC", new vector<aScl>{
					{"tries",&ctries},
					{"starttime",&starttime},
					{"dialstring",&dialstring},
					});
			confdcl sdgsd(sdgstxtdt,obverb);
			sdgsd.kauswert(&sdgsC);
		}
		/*
			 KLA
			 const char* const sarr[]=KLA"tries","starttime","dialstring"KLZ;
			 schlArr sdcnfA(sarr,elemzahl(sarr));
			 struct stat cstatKLA0KLZ;
			 if (lstat(sdgstxtdt.c_str(),&cstat)) KLA
			 return -2; // .txt-Datei fehlt
			 KLZ else KLA
			 confdat cpcd(sdgstxtdt,&sdcnfA,obverb);
			 ctries=sdcnfA[0].wert;
			 starttime=sdcnfA[1].wert;
			 dialstring=sdcnfA[2].wert;
			 KLZ //   if (lstat(sdgstxtdt.c_str(),&cstat)) else
		 */
		return (int)p1;
	} //   if (p1)
	return -1; // sendqgespfad enthaelt keinen ., .txt-Datei nicht zu benennen
} // int fsfcl::holcapiprot


// aufgerufen in untersuchespool und zeigweitere
void fsfcl::hylaausgeb(stringstream *ausgp, hhcl *hhip/*, int obsfehlt*/, uchar fuerlog, int obverb, uchar obzaehl, int oblog)
{
	fLog(violetts+Tx[T_hylaausgeb]+schwarz+"  hylastat: "+blau+FxStatS(&hylastat)+schwarz,obverb,oblog);
	if (!fuerlog) *ausgp<<blau<<endl;
	if (obzaehl) *ausgp<<++hhip->faxord<<")";
	else *ausgp<<"  ";
	*ausgp<<"Hyla: "<<schwarz;
	const char* const farbe1{(hylastat<wartend||hylastat>gesandt?hgrau:blau)}, // static_cast<FxStat>(...) nicht noetig
				* const farbe2{(hylastat<wartend||hylastat>gesandt?hgrau:schwarz)};
	*ausgp<<farbe1<<setw(11)<<FxStatS(&hylastat)<<(hgerg.empty()?"":" ("+hgerg+")")<<schwarz;
	/*//
		if (obsfehlt) KLA
	// wenn also die Datenbankdatei weder im Spool noch bei den Erledigten nachweisbar ist
	if (hylastat==gesandt) KLA
	 *ausgp<<blau<<" "<<Tx[T_gesandt]<<schwarz;
	 KLZ else if (hylastat==gescheitert) KLA
	 *ausgp<<blau<<" "<<Tx[T_gescheitert]<<" ("<<hgerg<<")"<<schwarz;
	 KLZ else if (hylastat==fehlend) KLA
	 *ausgp<<hgrau<<" "<<Tx[T_nicht_in_der_Warteschlange]<<schwarz;
	 KLZ
	 KLZ else KLA
	 KLZ // if (obsfehlt) else
	 */
	//// wenn eine Protokolldatei auslesbar war
	//// modemlaeuftnicht=systemrueck(("faxstat | grep ")+this->hmodem+" 2>&1",obverb,oblog,/*rueck=*/0,/*obsudc=*/1) + fglaeuftnicht;
	if ((hhip->hgelesen && hylastat!=fehlend && hylastat!=init)) {
		*ausgp<<",";
		//// char buf[100]; int hversuzahl=atol(hdials.c_str()); snprintf(buf,4,"%3d",hversuzahl);
		*ausgp<<farbe1<<setw(3)<<hdials<<"/"<<maxdials<<farbe2<<(hstate=="6"?umgek:"")<<Tx[T_Anwahlen]<<schwarz; // totdials
		// hier muss noch JobReqBusy, JobReqNoAnswer, JobReqNoCarrier, JobReqNoFCon, JobReqOther, JobReqProto dazu gerechnet werden
		//// time_t spoolbeg=(time_t)atol(tts.c_str());
		//// pthread_mutex_lock(&timemutex);
		//// char buf[100];
		//// strftime(buf, sizeof(buf), "%d.%m.%y %T", localtime(&tts));
		//// *ausgp<<blau<<buf<<schwarz; 
		//// pthread_mutex_unlock(&timemutex);

//		xtts+=atol(hhip->hintervall.c_str()); // naechster Aufrufzeitpunkt ist schon eingerechnet
		*ausgp<<farbe1<<ztacl(xtts,"%d.%m.%y %T")<<farbe2;
		////              if (hversuzahl>12) ausg<<", zu spaet";
		*ausgp<<",T.:"<<farbe1<<setw(12)<<number<<farbe2;
		*ausgp<<Tx[T_kommaDatei]<<rot<<sendqgespfad<<farbe2;
	} //   if (hhip->hgelesen && hylastat!=fehlend)
	if (hqdt.empty()) {
		if (hylanr!="0") *ausgp<<dgrau<<", hylanr: "<<farbe2<<hylanr;
	} else {
		*ausgp<<Tx[T_bzw]<<farbe1<<hqdt<<schwarz;
	} // 	if (hqdt.empty())
	fLog(violetts+Txk[T_Ende]+Tx[T_hylaausgeb]+schwarz+"  hylastat: "+blau+FxStatS(&hylastat)+schwarz,obverb,oblog);
} // void fsfcl::hylaausgeb

// aufgerufen in: aenderefax(/*aktion=*/0 ...), untersuchespool, loescheallewartenden;  in bereinigevz leicht modifizierte Verschiebung
void fsfcl::scheitere(const string& wvz, const string& ngvz, const string& cuser, const string* const ziel/*=0*/,
		const int obverb/*=0*/, const int oblog/*=0*/)
{
	fLog(violetts+Tx[T_scheitere]+schwarz,obverb,oblog);
	for(unsigned iru=0;iru<2;iru++) {
		const string *const datei{iru?&origvu:&original};
		if (!datei->empty()) {
			const string zuloe{wvz+vtz+*datei};
			struct stat zstat{0};
			uint vfehler;
			if (!lstat(zuloe.c_str(),&zstat)) {
				verschiebe<string>(zuloe, ngvz, cuser, &vfehler, /*wieweiterzaehl=*/1, /*obverb=*/1, oblog);
				if (ziel)
					touch(*ziel+vtz+Tx[T_nichtgefaxt]+" `"+base_name(zuloe)+"`.nix",obverb,oblog);
			}
		} // if (!datei->empty()) 
	} // for(unsigned iru=0;iru<2;iru++) 
} // fsfcl::scheitere(const string& wvz, const string ngvz, const int obverb, const int oblog)


// Dateien in Spool-Tabelle nach inzwischen verarbeiteten durchsuchen, Datenbank- und Dateieintraege korrigieren 
// aufgerufen in: pvirtfuehraus, pvirtnachrueckfragen (mit tulistw)
void hhcl::untersuchespool(uchar mitupd/*=1*/,const size_t aktc/*=3*/) // faxart 0=capi, 1=hyla 
{
	// Schaue nach, welche der gespoolten schon weggeschickt sind, Anpassung der Primaerdateien und des Datenbankeintrags
	hLog(violetts+Tx[T_untersuchespool]+schwarz);
	char ***cerg;
	RS rs(My,"SELECT s.id p0,s.capispooldt p1,s.capispoolpfad p2,s.original p3,s.cdateidatum p4,"
			" s.telnr p5,s.origvu p6,s.hylanr p7,s.capidials p8,s.hyladials p9,s.hdateidatum p10,s.adressat p11,s.idudoc p12,s.pprio p13,s.pages p14 "
			",alts.id p15,s.mailgesandt p16,s.fbdials p17,s.fbspooldt p18 "
			"FROM `"+spooltab+"` s "
			"LEFT JOIN `"+altspool+"` alts ON s.idudoc=alts.idudoc "
			"WHERE (s.hylanr RLIKE '^[0-9]+$' AND s.hylanr<>0) OR s.capispooldt RLIKE '^fax-[0-9]+\\.sff$' OR s.fbspooldt<>'' OR s.mailgesandt<>0 "
			"GROUP BY s.id",aktc,ZDB);
	if (!rs.obqueryfehler) {
		faxord=0;
		while (cerg=rs.HolZeile(),cerg?*cerg:0) {
			faxord++;
			if (*(*cerg+0)) if (*(*cerg+3)) {
				(dbzahl)++;
				stringstream ausg; //      ausg.str(std::string()); ausg.clear();
				/*2*/fsfcl fsf(*(*cerg+0),*(*cerg+3)); // id, original
				if (*(*cerg+1)) fsf.capisd =*(*cerg+1); // capispooldt
				if (*(*cerg+2)) fsf.cspf   =*(*cerg+2); // capispoolpfad
				if (*(*cerg+4)) fsf.cdd    =*(*cerg+4); // cdateidatum
				if (*(*cerg+5)) fsf.telnr  =*(*cerg+5); // telnr
				if (*(*cerg+6)) fsf.origvu =*(*cerg+6); // origvu
				if (*(*cerg+7)) fsf.hylanr =*(*cerg+7); // hylanr
				if (*(*cerg+8)) fsf.cdials =*(*cerg+8); // capidials
				if (*(*cerg+9)) fsf.hdials =*(*cerg+9); // hyladials
				if (*(*cerg+10)) fsf.hdd   =*(*cerg+10); // hdateidatum
				if (*(*cerg+11)) fsf.adressat =*(*cerg+11); // adressat
				if (*(*cerg+12)) fsf.idudoc = *(*cerg+12);  // id des ursp.Dateinamens in udoc
				if (*(*cerg+13)) fsf.pprio = atol(*(*cerg+13));  // Prioritaet wie in Datenbank
				if (*(*cerg+14)) fsf.pseiten = atol(*(*cerg+14));  // pages wie in Datenbank
				if (*(*cerg+15)) fsf.idalt = *(*cerg+15);  // id hyla
				if (*(*cerg+16)) fsf.mailges = *(*cerg+16);  // ob mail gesandt
				if (*(*cerg+17)) fsf.fbdials = *(*cerg+17);  // fbdials
				if (*(*cerg+18)) fsf.fbsdt = *(*cerg+18);  // fbspooldt
				//// <<"fsf.id: "<<violett<<fsf.id<<schwarz<<endl;
				//// <<"fsf.idalt: "<<violett<<fsf.idalt<<schwarz<<endl;
				fLog("id: "+fsf.id+": ",obverb?-2:0,oblog); // -2: schreibt ohne Zeilenwechsel
				ausg<<blau<<setw(2)<<faxord<<") "<<rot<<wvz<<vtz<<fsf.original<<schwarz<<": "; //ab hier Neue-Zeile-Zeichen immer am Anfang d.nae Zeile
				// -a) ueber klarmail
				if (fsf.mailges!="0") {
					if (mitupd) {
						// ...
					}
				}
				struct stat entrysend{0};
				// a) ueber fbfax
				if ((obfa[0]||obweg[0]==1) && fsf.mailges=="0") {
					if (faxord==1) this->prueffbox(); // in der ersten Runde, in der FBox verwendet werden soll, FBox pruefen
//					fsf.ausgeb();
					fsf.setzfboxstat(this, &entrysend);
					fsf.fboxausgeb(this,&ausg, 0, obverb, oblog);
					if (mitupd) {
						vector<instyp> einf; // fuer alle Datenbankeinfuegungen
						const string bedingung{"id="+fsf.id};
						const string bedc{"id="+fsf.idalt};
						if (fsf.fboxstat==wartend || fsf.fboxstat==gescheitert) {
							einf.push_back(/*2*/instyp(My->DBS,"fbdials",&fsf.fbdials));
							einf.push_back(/*2*/instyp(My->DBS,"fboxstat",fsf.fboxstat));
							if (!fsf.idalt.empty()) {
								RS rupd(My,altspool); 
								rupd.tbupd(einf,ZDB,bedc,aktc,/*asy=*/0);
							}
							RS rupd(My,spooltab); 
							rupd.tbupd(einf,ZDB,bedingung,aktc,/*asy=*/0);
						} else if (fsf.fboxstat==gesandt) {
							// ... und ggf. in hylafax loeschen
							fsf.loeschehyla(this,obverb, oblog);
							fsf.loeschecapi(obverb,oblog);
						} else if (fsf.fboxstat==fehlend) {
						} //             if (fsf.capistat==wartend)  else else else 
					} // 					if (mitupd) 
				} // 				if (obfa[0] && fsf.mailges=="0")

				// b) ueber capisuite
				// den Status in Capi der aus spool geholten Zeile untersuchen, dort aktualisieren
				//   und ggf. in hylafax stoppen
				if ((obfa[1]||obweg[1]==1) && fsf.mailges=="0") {
					if (faxord==1) this->pruefcapi(); // in der ersten Runde, in der Capi verwendet werden soll, Capi pruefen
					fsf.setzcapistat(this, &entrysend);
					fsf.xtts=0; // fuer archiviere
					fsf.capiausgeb(this,&ausg,maxcdials, 0, obverb, oblog);
					if (mitupd) {
						vector<instyp> einf; // fuer alle Datenbankeinfuegungen
						const string bedingung{"id="+fsf.id};
						const string bedc{"id="+fsf.idalt};
						if (fsf.capistat==wartend || fsf.capistat==gescheitert) {
							einf.push_back(/*2*/instyp(My->DBS,"capidials",&fsf.ctries));
							einf.push_back(/*2*/instyp(My->DBS,"capistat",fsf.capistat));
							if (!fsf.idalt.empty()) {
								RS rupd(My,altspool); 
								rupd.tbupd(einf,ZDB,bedc,aktc,/*asy=*/0);
							}
							RS rupd(My,spooltab); 
							rupd.tbupd(einf,ZDB,bedingung,aktc,/*asy=*/0);
						} else if (fsf.capistat==gesandt) {
							// ... und ggf. in hylafax loeschen
							fsf.loeschefbox(this,obverb, oblog);
							fsf.loeschehyla(this,obverb, oblog);
						} else if (fsf.capistat==fehlend) {
						} //             if (fsf.capistat==wartend)  else else else 
					} // if (mitupd) 
				} // if (obcapi) 

				// c) ueber hylafax
				if ((obfa[2]||obweg[2]==1) && fsf.mailges=="0") {
					uchar hyla_uverz_nr{0}; // suche ueberall, liefere 1 zuruck, wenn weder in /doneq noch in /archive gefunden
					int obsfehlt{-1};
					/*fsf.*/
					setzhylastat(&fsf, &hyla_uverz_nr, 0, &obsfehlt, &entrysend);
					//// <<gruen<<"fsf.hylastat: "<<schwarz<<(int)fsf.hylastat<<endl;
					//// <<gruen<<"fsf.hqdt: "<<schwarz<<fsf.hqdt<<endl;
					//// <<"vor hylaausgeb 2, fsf.hstate: '"<<fsf.hstate<<"'"<<endl;
					fsf.hylaausgeb(&ausg, this/*, obsfehlt*/, 0, obverb, 0, oblog);
					//          if (!obsfehlt) KLA // Protokolldatei vorhanden 12.10.16 sollte jetzt auch mit xferfax gehen
					if (mitupd) {
						vector<instyp> einf; // fuer alle Datenbankeinfuegungen
						einf.push_back(/*2*/instyp(My->DBS,"hylastate",&fsf.hstate));
						if (!fsf.hstatus.empty()) einf.push_back(/*2*/instyp(My->DBS,"hylastatus",&fsf.hstatus));
						if (!fsf.hstatuscode.empty()) einf.push_back(/*2*/instyp(My->DBS,"hylastatuscode",&fsf.hstatuscode));
						////				if (!hyla_uverz_nr) KLA // wenn fertig
						////					if (fsf.hylastat==gescheitert) KLA // (hylastate=="8") // 8, status gescheitert, evtl. unzureichend dokumentiert, aber wahr
						////                einf.push_back(/*6*/instyp(My->DBS,"hylanr","0",(uchar)1));
						////                einf.push_back(instyp(My->DBS,"hyladials","-1",(uchar)1));
						////                fsf.hdials="-1";
						////					KLZ else 
						if (fsf.hylastat==gesandt) { // (hylastate=="7") // 7, status erfolgreich
							// ... und ggf. in capisuite loeschen
							fsf.loeschefbox(this,obverb, oblog);
							fsf.loeschecapi(obverb,oblog);
						} // if (fsf.hylastat==gescheitert) else
						////						KLZ // if (!hyla_uverz_nr) 
						einf.push_back(/*2*/instyp(My->DBS,"hyladials",&fsf.hdials));
						const string bedingung{"id="+fsf.id};
						const string bedh{"id="+fsf.idalt};
						if (!fsf.idalt.empty()) {
							RS rupd(My,altspool); 
							rupd.tbupd(einf,ZDB,bedh,aktc,/*asy=*/0);
						}
						RS rupd(My,spooltab); 
						rupd.tbupd(einf,ZDB,bedingung,aktc,/*asy=*/0);
					} // if (mitupd) 
//			caus<<"Stelle 56 "<<endl; systemrueck("mysql -upraxis -p.... -e'select * from faxeinp.spool'",2,0);
				} // if (obhyla)
				////        KLZ // if (!obsfehlt) ... else
				if (1) {
					if (obfa[0]||obweg[0]==1 || obfa[1]||obweg[1]==1 || obfa[2]||obweg[2]==1 || fsf.mailges=="1") {
						// im Erfolgsfall zugrundeliegende Dateien verschieben
						if (fsf.fboxstat==gesandt || fsf.capistat==gesandt || fsf.hylastat==gesandt || fsf.mailges!="0") {
							(ezahl)++;

							if (mitupd) {
								// Fax gelungen, Dateien in warteauffax nach zielmuster verschieben bzw. loeschen ...
								for(unsigned iru=0;iru<2;iru++) {
									const string * const datei{iru?&fsf.origvu:&fsf.original};
									if (!datei->empty()) {
										const string zuloe{wvz+vtz+*datei};
										if (gleichziel) { 
											tuloeschen(zuloe,cuser,obverb,oblog);
										} else {
											uint vfehler{0};
											verschiebe<vector<shared_ptr<zielmustercl>>>(zuloe, zmsp, cuser,&vfehler, /*wieweiterzaehl=*/1, obverb, oblog);
										} // if (gleichziel) else 
									} // if (!datei->empty()) 
								} // for(unsigned iru=0;iru<2;iru++) 
							} // if (mitupd)
						} else if (
							  ((!obfa[0]&&obweg[0]!=1)||fsf.fboxstat==gescheitert)&&
							  ((!obfa[1]&&obweg[1]!=1)||fsf.capistat==gescheitert)&&
							  ((!obfa[2]&&obweg[2]!=1)||fsf.hylastat==gescheitert)) {
							(gzahl)++; 
						} else if (
							  ((!obfa[0]&&obweg[0]!=1)||fsf.fboxstat==fehlend)&&
							  ((!obfa[1]&&obweg[1]!=1)||fsf.capistat==fehlend)&&
							  ((!obfa[2]&&obweg[2]!=1)||fsf.hylastat==fehlend)) {
							(fzahl)++;
						} else if (fsf.fboxstat==wartend || fsf.capistat==wartend || (fsf.hylastat>static_cast<FxStat>(gestrichen)&&fsf.hylastat<=static_cast<FxStat>(verarb))) {
							(wzahl)++;
						} //           if (fsf.capistat==gesandt || fsf.hylastat==gesandt) else if ...
						// Aktionen, wenn in beiden gescheitert oder fehlend
						if (obverb>0 && fsf.mailges=="0") {
							hLog(violetts+"Fboxstat: "+schwarz+FxStatS(&fsf.fboxstat)+
  							  violett+", Capistat: "+schwarz+FxStatS(&fsf.capistat)+
								  violett+", Hylastat: "+schwarz+FxStatS(&fsf.hylastat));
						} //           if (obverb>0)
						// die Flags aller aktivierten Faxwege stehen auf gescheitert
						const uchar allegesch{(obfa[0]||obweg[0]==1||obfa[1]||obweg[1]==1||obfa[2]||obweg[2]==1) && 
							     ((!obfa[0]&&obweg[0]!=1)||fsf.fboxstat==gescheitert)&&
									 ((!obfa[1]&&obweg[1]!=1)||fsf.capistat==gescheitert)&&
									 ((!obfa[2]&&obweg[2]!=1)||fsf.hylastat==gescheitert)  && fsf.mailges=="0"};
						////          if (obcapi && obhyla && fsf.capistat==gescheitert && maxcapiv>=maxcdials) allegesch=1;
						////          else if (obcapi && obhyla && fsf.hylastat==gescheitert && maxhylav>=maxhdials) allegesch=1;
						// die Flags aller aktivierten Faxwege stehen auf gescheitert oder fehlend
						const uchar nimmer{fsf.mailges=="0"&&
							     (((!obfa[0]&&obweg[0]!=1) || fsf.fboxstat==fehlend || fsf.fboxstat==gescheitert) && 
							      ((!obfa[1]&&obweg[1]!=1) || fsf.capistat==fehlend || fsf.capistat==gescheitert) && 
								    ((!obfa[2]&&obweg[2]!=1) || fsf.hylastat==fehlend || fsf.hylastat==gescheitert))};
						//// <<rot<<"\nfsf.capistat: "<<violett<<fsf.capistat<<rot<<" fsf.hylastat: "<<violett<<fsf.hylastat<<rot<<" allegesch: "<<violett<<(int)allegesch<<rot<<" nimmer: "<<violett<<(int)nimmer<<schwarz<<endl;
						uchar ogibts[2]{0};
						if (nimmer) {
							for(unsigned iru=0;iru<2;iru++) {
								struct stat ostat{0};
								ogibts[iru]=!lstat((wvz+vtz+(iru?fsf.origvu:fsf.original)).c_str(),&ostat);
								hLog(blaus+"odatei["+(iru?"1":"0")+"]: "+(iru?fsf.origvu:fsf.original));
								hLog(blaus+"ogibts["+(iru?"1":"0")+"]: "+(ogibts[iru]?"1":"0"));
							} // for(unsigned iru=0
						} // if (nimmer)
						if (mitupd) {
							if (fsf.fboxstat==gesandt || fsf.capistat==gesandt || fsf.hylastat==gesandt || allegesch || (nimmer /* && !ogibts[0] */) ||fsf.mailges=="1") {
								uchar geloescht{0};
								/*//
								// <<"\n"<<gruen<<"gesandt: "<<schwarz<<(int)gesandt<<endl;
								// <<gruen<<"gescheitert: "<<schwarz<<(int)gescheitert<<endl;
								// <<gruen<<"fehlend: "<<schwarz<<(int)fehlend<<endl;
								// <<gruen<<"allegesch: "<<schwarz<<(int)allegesch<<endl;
								// <<gruen<<"nimmer: "<<schwarz<<(int)nimmer<<endl;
								// <<gruen<<"fsf.capistat: "<<schwarz<<(int)fsf.capistat<<endl;
								// <<gruen<<"fsf.hylastat: "<<schwarz<<(int)fsf.hylastat<<endl;
								// <<"obfa[1]: "<<(int)obfa[1]<<endl;
								// <<"obfa[2]: "<<(int)obfa[2]<<endl;
								// <<"fsf.capisd: '"<<fsf.capisd<<"'"<<endl;
								// <<gruen<<"fsf.capisd.empty(): "<<schwarz<<(int)fsf.capisd.empty()<<endl;
								 */
								fsf.archiviere(My,this,&entrysend,allegesch||nimmer,
										fsf.mailges!="0"?kmail:
										fsf.fboxstat==gesandt?fritz:fsf.capistat==gesandt?capi:fsf.hylastat==gesandt?hyla:
										!fsf.capisd.empty()?capi:!fsf.hylanr.empty()?hyla:!fsf.fbsdt.empty()?fritz:keintyp,
										&geloescht, 8, obverb, oblog);
							} //           if (fsf.capistat==gesandt || fsf.hylastat==gesandt || allegesch || (nimmer /* && !ogibts[0] */) )
							// wenn alle aktivierten Faxwege auf gescheitert oder fehlend stehen oder die Quelldatei fehlt ...
							if (allegesch || (nimmer && !ogibts[0])) {
								// Fax gescheitert, Dateien von warteauffax nach nichtgefaxt verschieben
								fsf.scheitere(wvz,ngvz,cuser,&zmsp[0]->ziel,obverb,oblog);
							} // if (allegesch || (nimmer && !ogibts[0]))
						} // 						if (mitupd)
					} // if (obfa[1] || obfa[2] || fsf.mailges=="1")
				} // if (0)
				fLog(ausg.str(),1,oblog);
			} // if (*(*cerg+0)) if (*(*cerg+3))
		} // while (cerg=rs.HolZeile(),cerg?*cerg:0) 
	} // if (!rs.obqueryfehler) 
	fLog(Tx[T_Zahl_der_ueberpruefen_Datenbankeintraege]+drots+ltoan(dbzahl)+schwarz,1,oblog);
	fLog(Tx[T_davon_gescheiterte_Faxe]+drots+ltoan(gzahl)+schwarz,1,oblog);
	fLog(Tx[T_davon_erfolgreiche_Faxe]+drots+ltoan(ezahl)+schwarz,1,oblog);
	fLog(Tx[T_davon_noch_wartende_Faxe]+drots+ltoan(wzahl)+schwarz,1,oblog);
	fLog(Tx[T_davon_nicht_in_Warteschlange]+drots+ltoan(fzahl)+schwarz,1,oblog);
	hLog(violetts+Txk[T_Ende]+Tx[T_untersuchespool]+schwarz);
} // untersuchespool

// aufgerufen in: main
void hhcl::suchestr()
{
	hLog(violetts+Tx[T_suchestr]+schwarz);
	const size_t aktc{0};
	const string scnv{" CONVERT(\"%"+suchstr+"%\" USING utf8) COLLATE utf8_unicode_ci "};
	size_t geszahl{0};
	for(int erf=1;erf>=0;erf--) {
		const string oberfolg{ltoan(erf)};
		char ***cerg;
		RS rlista(My,"SELECT Ueberm p0, Submid p1, Faxname p2, Empfaenger p3, Fax p4, Erfolg p5 FROM ("
				"SELECT * FROM ("
				"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') Ueberm, Submid, RIGHT(CONCAT(space(75),LEFT(Docname,75)),75) Faxname, "
				"RIGHT(CONCAT(SPACE(30),LEFT(rcname,30)),30) Empfaenger, rcfax Fax, Erfolg, transe "
				"FROM `"+touta+"` WHERE Erfolg = "+oberfolg+" AND (Docname LIKE"+scnv+"OR rcname LIKE"+scnv+"OR rcfax LIKE"+scnv+""
				"OR submid LIKE"+scnv+" OR transe LIKE CONVERT(\"%"+suchstr+"%\" USING utf8) COLLATE utf8_unicode_ci) "
				" ORDER BY transe DESC LIMIT "+dszahl+") i "
				" ORDER BY transe LIMIT 18446744073709551615) i",aktc,ZDB);
		ulong zeile{0};
		while (cerg=rlista.HolZeile(),cerg?*cerg:0) {
			if (!zeile)
				cout<<gruen<<Tx[T_Letzte]<<blau<<dszahl<<gruen<<(oberfolg=="1"?Tx[T_erfolgreich]:Tx[T_erfolglos])<<Tx[T_versandte_Faxe]<<
					Tx[T_mitstr]<<blau<<suchstr<<"':"<<schwarz<<endl;
			zeile++;
			geszahl++;
			cout<<blau<<setw(17)<<cjj(cerg,0)<<"|"<<violett<<setw(14)<<cjj(cerg,1)<<schwarz<<"|"<<(erf?blau:violett)<<setw(65)<<cjj(cerg,2)<<"|"
				<<schwarz<<setw(30)<<cjj(cerg,3)<<"|"<<blau<<cjj(cerg,4)<<schwarz<<endl;
		} // while (cerg=rlista.HolZeile(),cerg?*cerg:0) 
	} //   for(int erf=1;erf>=0;erf--) 

	char ***cerg;
	RS rlisti(My,"select p0, p1, p2, p3, p4 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') p0,RIGHT(CONCAT(SPACE(85),LEFT(titel,85)),85) p1,"
			"fsize p2,tsid p3,id p4, transe FROM `"+tinca+"` i WHERE (titel LIKE"+scnv+""
			"OR tsid LIKE"+scnv+"OR transe LIKE"+scnv+"OR id LIKE CONVERT(\"%"+suchstr+"%\" USING utf8) COLLATE utf8_unicode_ci)"
			" ORDER BY transe DESC LIMIT "+dszahl+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",aktc,ZDB);
	ulong zeile{0};
	while (cerg=rlisti.HolZeile(),cerg?*cerg:0) {
		if (!zeile)
			cout<<gruen<<Tx[T_Letzte]<<blau<<dszahl<<gruen<<Tx[T_empfangene_Faxe]<<Tx[T_mitstr]<<blau<<suchstr<<"':"<<schwarz<<endl;
		zeile++;
		geszahl++;
		cout<<blau<<setw(17)<<cjj(cerg,0)<<"|"<<violett<<setw(85)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(17)<<cjj(cerg,2)<<"|"
			<<schwarz<<setw(17)<<cjj(cerg,3)<<"|"<<blau<<cjj(cerg,4)<<schwarz<<endl;
	} // while (cerg=rlisti.HolZeile(),cerg?*cerg:0) 

	RS spool(My,"SELECT p0, p1, p2, p3, p4 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(if(hdateidatum=0,cdateidatum,hdateidatum),'%d.%m.%y %H:%i:%s') p0,"
			"RIGHT(CONCAT(SPACE(85),LEFT(origvu,85)),85) p1,"
			"IF(capidials=0,hyladials,capidials) p2,IF(hylanr=0,capispooldt,hylanr) p3,id p4, if(hdateidatum=0,cdateidatum,hdateidatum) so "
			"FROM `"+spooltab+"` i WHERE (origvu LIKE"+scnv+"OR original LIKE"+scnv+"OR telnr LIKE"+scnv+"OR capispooldt LIKE"+scnv+
			"OR cdateidatum LIKE CONVERT(\"%"+suchstr+"%\" USING utf8) COLLATE utf8_unicode_ci)"
			" ORDER BY so DESC LIMIT "+dszahl+") i "
			" ORDER BY so LIMIT 18446744073709551615) i",aktc,ZDB);
	zeile=0;
	while (cerg=spool.HolZeile(),cerg?*cerg:0) {
		if (!zeile)
			cout<<gruen<<Tx[T_Letzte]<<blau<<dszahl<<gruen<<Tx[T_wartende_Faxe]<<Tx[T_mitstr]<<blau<<suchstr<<"':"<<schwarz<<endl;
		zeile++;
		geszahl++;
		cout<<blau<<setw(17)<<cjj(cerg,0)<<"|"<<violett<<setw(85)<<cjj(cerg,1)<<schwarz<<"|"<<blau<<setw(17)<<cjj(cerg,2)<<"|"
			<<schwarz<<setw(17)<<cjj(cerg,3)<<"|"<<blau<<cjj(cerg,4)<<schwarz<<endl;
	} // while (cerg=rlisti.HolZeile(),cerg?*cerg:0) 
	if (geszahl)
		cout<<gruen<<Tx[T_Insgesamt]<<blau<<geszahl<<gruen<<Tx[T_Fundstellen_von]<<blau<<suchstr<<schwarz<<endl;
  else
		cout<<gruen<<Tx[T_Keine_Fundstellen_von]<<blau<<suchstr<<schwarz<<endl;
} // suchestr

// aufgerufen in: main
void pruefstdfaxnr(DB *Myp, const string& usr, const string& host, const int obverb, const int oblog)
{
	fLog(violetts+Tx[T_pruefstdfaxnr]+schwarz,obverb,oblog);
	const size_t aktc{0};
	const string body{
		"begin \n"
		" declare anfg varchar(100) default concat(IPf,'+');\n"
		" declare pos int default 0;\n"
		" declare it char default '';\n"
		" declare land varchar(100) default concat(IPf,CoCd);\n"
		" declare trimfaxnr varchar(100) default '';\n"
		" glp: loop\n"
		"   set it = substring(faxnr,pos,1);\n"
		"   if instr('+0123456789',it) then\n"
		"    if trimfaxnr='' and not instr(anfg,it) then\n"
		"     set trimfaxnr=concat(LDPf,CiCd);\n"
		"    end if;\n"
		"   end if;\n"
		"   if (it='+') then\n"
		"    set trimfaxnr=concat(trimfaxnr,IPf);\n"
		"   else\n"
		"    set trimfaxnr=concat(trimfaxnr,it);\n"
		"   end if;\n"
		"   set pos=pos+1;\n"
		"   if pos>length(faxnr) then leave glp; end if;\n"
		" end loop;\n"
		" if instr(trimfaxnr,land)=1 then\n"
		"  set trimfaxnr=concat(LDPf,substr(trimfaxnr,length(land)+1));\n"
		" end if;\n"
		" return trimfaxnr;\n"
		"end"};
	const string para{"(faxnr VARCHAR(200), IPf VARCHAR(10), LDPf VARCHAR(20), CoCd VARCHAR(20), CiCd VARCHAR(20)) \n"
		"RETURNS VARCHAR(200) CHARSET utf8 COLLATE utf8_unicode_ci DETERMINISTIC\n"};
	Myp->prueffunc("stdfaxnr", body, para, aktc,obverb,oblog);
}  // void pruefstdfaxnr(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)

// aufgerufen in: main
void prueffuncgettel3(DB *const Myp, const string& usr, const string& host, const int obverb, const int oblog)
{
	fLog(violetts+Tx[T_prueffuncgettel3]+schwarz,obverb,oblog);
	const size_t aktc{0};
	const string body{
		"begin \n"
		" declare pos int;\n"
		" declare obMail int default 0;\n"
		" declare nachAffe int default 0;\n"
		" declare nachPunkt int default 0;\n"
		" declare ch char default '0';\n"
		" declare tel varchar(100) default '';\n"
		" set pos = instr(dname,anfaxstr);\n"
		" if pos>0 then\n"
		"  set pos=pos+length(anfaxstr);\n"
		" else\n"
		"  if ancfaxstr > '' then\n"
		"   set pos=instr(dname,ancfaxstr);\n"
		"   if pos>0 then\n"
		"    set pos=pos+length(ancfaxstr);\n"
		"   else\n"
		"    if anhfaxstr > '' then\n"
		"     set pos=instr(dname,anhfaxstr);\n"
		"     if pos>0 then\n"
		"      set pos=pos+length(anhfaxstr);\n"
		"     else\n"
		"      if anffaxstr > '' then\n"
		"       set pos=instr(dname,anffaxstr);\n"
		"       if pos>0 then\n"
		"        set pos=pos+length(anffaxstr);\n"
		"       else\n"
		"        set pos=instr(dname,anmailstr);\n"
	  "        if pos>0 then\n"
		"         set obMail=1;\n"
    "         set pos=pos+length(anmailstr);\n"
		"        else\n"
		"         set pos=instr(dname,klaranmailstr);\n"
	  "         if pos>0 then\n"
		"          set obMail=1;\n"
    "          set pos=pos+length(klaranmailstr);\n"
		"         end if;\n"
		"        end if;\n"
		"       end if;\n"
		"      end if;\n"
		"     end if;\n"
		"    end if;\n"
		"   end if;\n"
		"  end if;\n"
		" end if;\n"
		" if pos>0 then\n"
		"  wlab: loop\n"
		"   set ch=substring(dname,pos,1);\n"
		"   if obMail=1 then\n"
		"    if ch='@' then\n"
		"     set nachAffe=1;\n"
		"    else\n"
		"     if ch='.' then\n"
		"      if nachPunkt=1 then\n"
		"       leave wlab;\n"
		"      else\n"
		"       if nachAffe=1 then\n"
		"        set nachPunkt=1;\n"
		"       end if;\n"
		"      end if;\n"
		"     end if;\n"
		"    end if;\n"
		"   end if;\n"
		"   if (obMail=0 or nachPunkt=1) and ch='_' then leave wlab; end if;\n"
		"   if obMail=0 then\n"
		"    if instr('0123456789',ch) then set tel=concat(tel,ch);\n"
		"    else if ch='+' then set tel=concat(tel,'00'); end if; end if;\n"
		"   else\n"
		"    set tel=concat(tel,ch);\n"
		"   end if;\n"
		"   set pos=pos+1;\n"
		"   if pos>length(dname) then leave wlab; end if;\n"
		"  end loop;\n"
		" end if;\n"
		" return tel;\n"
		"end"};
	const string para{"(dname VARCHAR(1000),anfaxstr VARCHAR(100),ancfaxstr VARCHAR(100),anhfaxstr VARCHAR(100),anffaxstr VARCHAR(100),"
		"anmailstr VARCHAR(150),klaranmailstr VARCHAR(150)) \n"
		"RETURNS VARCHAR(1000) CHARSET utf8 COLLATE utf8_unicode_ci DETERMINISTIC\n"};
	Myp->prueffunc("gettel3", body, para, aktc,obverb,oblog);
} // void prueffuncgettel3

// aufgerufen in: main
// aktion: 0=loeschen, 1=umleiten (von capi auf hyla+fbfax usw.), 2=alleumleiten
int hhcl::aenderefax(const int aktion/*=0*/,const size_t aktc/*=0*/)
{
	hLog(violetts+Tx[T_aendere_fax]+"("+(aktion?"1":"0")+")"+schwarz);
	vector<fsfcl> fsfav;
	faxord=0;
	string ergnr,erg;
	char*** cerg;
	/*//
		RS zul(My,string("SELECT CONCAT_WS(' ',LEFT(CONCAT(IF(ISNULL(original),'NULL',original),SPACE(50)),50),"
		"RIGHT(CONCAT(SPACE(15),IF(ISNULL(capispooldt),'NULL',capispooldt)),15),")+
		"CONCAT('Capidials:',RIGHT(CONCAT(SPACE(4),IF(ISNULL(capidials),'NULL',capidials)),4)),"
		"CONCAT('Hyla:',RIGHT(CONCAT(SPACE(5),IF(ISNULL(hylanr),'NULL',hylanr)),5)), "
		"CONCAT('Hyladials:',RIGHT(CONCAT(SPACE(4),IF(ISNULL(hyladials),'NULL',hyladials)),4))) p0,"
		"id p1,"
		"IF(ISNULL(capispooldt),'NULL',capispooldt) p2,"
		"IF(ISNULL(capispoolpfad),'"+cfaxusersqvz+"',capispoolpfad) p3,"
		"hylanr p4 FROM `"+spooltab+"` ORDER BY id",ZDB);
	 */
	RS zul(My,"SELECT CONCAT_WS(' ',LEFT(CONCAT(original,SPACE(50)),50),"
			"CONCAT('Capisdt:',RIGHT(CONCAT(SPACE(15),capispooldt),15),"
			"       ', Capidials:',RIGHT(CONCAT(SPACE(2),capidials),2),"
			"       ', Hylanr:',RIGHT(CONCAT(SPACE(5),hylanr),5),"
			"       ', Hdials:',RIGHT(CONCAT(SPACE(2),hyladials),2),"
			"       ', Fbsdt:',RIGHT(CONCAT(SPACE(6),fbspooldt),6),"
			"       ', FBdials:',RIGHT(CONCAT(SPACE(2),fbdials),2)"
			")) p0,"
			"id p1,"
			"capispooldt p2,"
			"IF(capispoolpfad='','"+cfaxusersqvz+"',capispoolpfad) p3,"
			"hylanr p4,"
			"original p5, origvu p6, fbspooldt p7 "
			"FROM `"+spooltab+"` ORDER BY id",aktc,ZDB);
	while (cerg=zul.HolZeile(),cerg?*cerg:0) {
		if (*(*cerg+0) && *(*cerg+1)) {
			fLog("Fax "+blaus+ltoan(++faxord)+schwarz+": "+cjj(cerg,0),1,1);
			/*3*/fsfcl fsf(cjj(cerg,1),cjj(cerg,2),cjj(cerg,4),cjj(cerg,3));
			if (*(*cerg+5)) fsf.original=cjj(cerg,5);
			if (*(*cerg+6)) fsf.origvu=cjj(cerg,6);
			if (*(*cerg+7)) fsf.fbsdt=cjj(cerg,7);
			fsfav.push_back(fsf);
		} // if (*(*cerg+0) && *(*cerg+1)) 
	} // while (cerg=zul.HolZeile(),cerg?*cerg:0) 
	size_t ivorher=fsfav.size();
	sammlefbox(&fsfav,aktc);
	for(size_t i=ivorher;i<fsfav.size();i++) {
		////      if (i==ivorher)  fLog("Capi:",1,0);
		stringstream aus;
		fsfav[i].fboxausgeb(this,&aus,1,obverb,oblog,++faxord);
		const string auss{aus.str()};
		fLog(auss,1,oblog);
	} // 	for(size_t i=ivorher;i<fsfav.size();i++)
	ivorher=fsfav.size();
	sammlecapi(&fsfav,aktc);
	for(size_t i=ivorher;i<fsfav.size();i++) {
		////      if (i==ivorher)  fLog("Capi:",1,0);
		stringstream aus;
		fsfav[i].capiausgeb(this,&aus,maxcdials,1,obverb,oblog,++faxord);
		const string auss{aus.str()};
		fLog(auss,1,oblog);
	} // 	for(size_t i=ivorher;i<fsfav.size();i++)
	ivorher=fsfav.size();
	sammlehyla(&fsfav,aktc);
	for(size_t i=ivorher;i<fsfav.size();i++) {
		////      if (i==ivorher) fLog("Hyla:",1,0);
		stringstream aus;
		fsfav[i].hylaausgeb(&aus,this/*,0*/,1,obverb,1,oblog);
		const string auss{aus.str()};
		fLog(auss,1,oblog);
	} //   for(size_t i=ivorher;i<fsfav.size();i++) 
	if (!nrzf) {
		if (fsfav.size()) {
			if (aktion==2) {
				if (Tippob(Tx[T_Sollen_alle_Faxe_umgeleitet_werden],"n")) {
					RS umpri(My,"UPDATE `"+spooltab+"` SET allewege=1",aktc,ZDB);
				}
			} else {
				ergnr=Tippzahl(Tx[(aktion?T_Welches_Fax_soll_umgeleitet_werden:T_Welches_Fax_soll_geloescht_werden)]);
				if (ergnr=="0") return 0;
				size_t nr{(size_t)atol(ergnr.c_str())-1};
				if (nr>=0 && nr<fsfav.size()) {
					if (Tippob(Tx[T_Soll_das_Fax]+gruens+ergnr+schwarz+Tx[(aktion?T_umgeleitet_werden:T_wirklich_geloescht_werden)],"n")) {
						if (aktion) {
							RS umpri(My,"UPDATE `"+spooltab+"` SET allewege=1 WHERE id="+fsfav[nr].id,aktc,ZDB);
						} else { // !aktion
							int zdng{0}; // Zahl der nicht geloeschten
							if (fsfav[nr].fbsdt!="NULL" && !fsfav[nr].fbsdt.empty()) {
								zdng+=fsfav[nr].loeschefbox(this,obverb,oblog);
								hLog(blaus+"fbox: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_FBoxspooldatei]+
										schwarz+fsfav[nr].fbsdt);
							}
							if (fsfav[nr].capisd!="NULL" && !fsfav[nr].capisd.empty()) {
								zdng+=fsfav[nr].loeschecapi(obverb,oblog);
								hLog(blaus+"capi: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_Capispooldatei]+
										schwarz+fsfav[nr].capisd);
							}
							if (fsfav[nr].hylanr!="NULL" && !fsfav[nr].hylanr.empty()) {
								zdng+=fsfav[nr].loeschehyla(this,obverb,oblog);
								hLog(blaus+"hyla: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_hylanr]+schwarz+fsfav[nr].hylanr);
							}
							hLog(blaus+Tx[T_Gesamt]+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng));
							// hier werden noch die Dateien von wvz auf ngvz verschoben 
							fsfav[nr].scheitere(wvz,ngvz,cuser,0,obverb,oblog);
							struct stat entrysend{0};
							fsfav[nr].setzfboxstat(this,&entrysend);
							fsfav[nr].setzcapistat(this,&entrysend);
							uchar hyla_uverz_nr{1};
							/*fsfav[nr].*/setzhylastat(&fsfav[nr], &hyla_uverz_nr, 0, 0, 0); // hyla_uverz_nr, obsfehlt
							hLog(violetts+"fboxstat: "+schwarz+FxStatS(&fsfav[nr].fboxstat)+
									violett+", capistat: "+schwarz+FxStatS(&fsfav[nr].capistat)+
									violett+", hylastat: "+schwarz+FxStatS(&fsfav[nr].hylastat));
							////<<"zdng: "<<zdng<<endl;
							////<<"fsfav[nr].capistat: "<<(int)fsfav[nr].capistat<<", fehlend: "<<(int)fehlend<<endl;
							////<<"fsfav[nr].hylastat: "<<(int)fsfav[nr].hylastat<<", fehlend: "<<(int)fehlend<<endl;
							////<<"fsfav[nr].id.empty(): "<<fsfav[nr].id.empty()<<endl;
							if ((!zdng|| (
											(fsfav[nr].fboxstat==fehlend||fsfav[nr].fboxstat==init)&&
											(fsfav[nr].capistat==fehlend||fsfav[nr].capistat==init)&&
											(fsfav[nr].hylastat==fehlend||fsfav[nr].hylastat==init))) && 
									!fsfav[nr].id.empty()) {
								////<<rot<<"loesche!!!!!!!"<<endl;
								RS loe(My,"DELETE FROM `"+spooltab+"` WHERE id="+fsfav[nr].id,aktc,-obverb);
							}
						} // if (aktion) else
					} // if (Tippob(Tx[T_Soll_das_Fax]+gruens+ergnr+schwarz+Tx[T_wirklich_geloescht_werden],"n")) 
				} // if (nr>=0 && nr<fsfav.size()) 
			} // 			if (aktion==2) else
		} else {
			fLog(Tx[aktion?T_Kein_Fax_zum_Umleiten_vorhanden:T_Kein_Fax_zum_Loeschen_vorhanden],1,oblog);
		} // if (fsfav.size()) 
	} // !nrzf
	return 1;
} // int hhcl::aenderefax

// aufgerufen in: pvirtfueraus, zeigweitere
void hhcl::korrigierehyla(const unsigned tage/*=90*/,const size_t aktc)
{
	hLog(violetts+Tx[T_korrigierehyla]+schwarz);
		////	uchar gehtmitxfer=0;
		if (!xferfaxlog.empty()) {
			struct stat entryvz{0};
			if (!lstat(xferfaxlog.c_str(),&entryvz)) {
				////			gehtmitxfer=1;
				//// cmd=string(sudc+"find '")+varsphylavz+"' -type f -regex '.*/q[0-9]+'";
				//// string hylanr=qrueck[i].substr(qrueck[i].rfind('q')+1);
				//// ausw+=hylanr;
				//// ausw+=",";
				//// ausw[ausw.size()-1]=')';
				//// tac /var/spool/hylafax/etc/xferfaxlog | awk -vDate=`date -d'now-1 month' +%m/%d/%y` 'function isdate(var) KLA if (var ~ /[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9]/) return 1; return 0; KLZ isdate($1) && $1 > Date KLAprint Date " " $0KLZ'
				////		  cmd="tac \""+xferfaxlog+"\" 2>/dev/null|grep '"+sep+"UNSENT"+sep+"\\|"+sep+"SEND"+sep+"'|cut -f 2,5,14,20|awk '!s[$2]++'";
				//// awk-Befehl: Suche bis vor 3 Monaten von zu jeder hylanr ($5) die letzte Zeile (s[$5]==0) mit dem Befehl ($2) SEND oder UNSENT; gib mit \t aus
				cmd="tac \""+xferfaxlog+"\" 2>/dev/null|awk -vDate=`date -d'now-"+ltoan(tage)+" day' +%Y%m%d` "
					"'BEGIN{FS=\"\\t\";OFS=FS;arr[\"SEND\"];arr[\"UNSENT\"];}; "
					"{merk=20(substr($1,7,2))substr($1,1,2)substr($1,4,2)}; "
					"merk~/^[0-9]+$/ && merk!=\"20\" && merk<Date {exit 0}; "
					"merk~/^[0-9]+$/ && merk!=\"20\" && $2 in arr && !s[$5]++ {print $1,$2,$5,$8,$11,$14,$20}'"; //...$14,$20;gz++KLZ END KLA print gz KLZ'
				//$1=Date,$2=action,$5=qfile(hylid,sumid),$8=Tel'nr,$11=Seitenzahl,$14=reason,$20=jobinfo(totpages/ntries/ndials/totdials/maxdials/tot/maxtries)
				svec qrueck;
				// wenn unter SEND im Feld reason ($14) nichts steht, erfolgreich, sonst erfolglos
				systemrueck(cmd,obverb,oblog,&qrueck);
				//Erfolgskennzeichenkorrektur: auswe=Erfolg, auswm=Misserfolg; inse = fehlende Eintraege
				string auswe{"("}, auswm{"("}, inse;
				for(size_t i=0;i<qrueck.size();i++) {
					vector<string> tok; 
					aufSplit(&tok,qrueck[i],'\t');
					if (tok.size()>5) {
						//// <<tok[0]<<'|'<<tok[1]<<'|'<<tok[2]<<'|'<<tok[3]<<'|'<<tok[4]<<'|'<<tok[5]<<'|'<<tok[6]<<endl;
						uchar erfolg{0};
						if (tok[1]=="SEND") {
							if (tok[5]=="\"\"") erfolg=1;
						} // 				if (tok[1]=="SEND")
						if (erfolg) {
							auswe+="'";
							auswe+=tok[2];
							auswe+=+"',"; 
						} else {
							auswm+="'";
							auswm+=tok[2];
							auswm+=+"',"; 
						} // if /erfolg) else
#ifndef mitmisserfolg
						if (erfolg)
#endif
							inse+="("+tok[2]+","+"\"20"+tok[0].substr(6,2)+"-"+tok[0].substr(0,2)+"-"+tok[0].substr(3,2)+" "+tok[0].substr(9,2)+":"+
								tok[0].substr(12,2)+"\","+tok[3]+","+tok[4]+",\""+tok[6]+"\","+(erfolg?"1":"0")+"),";
					} // 				if (tok.size()>0)
				} // for(size_t i=0;i<rueck.size();i++) 
				auswe[auswe.size()-1]=')';
				auswm[auswm.size()-1]=')';
				if (inse.size()>2) {
					inse[inse.size()-1]=';';
					////		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_ON);
					RS vgl1(My,"DROP TABLE IF EXISTS tmph",aktc,ZDB);
					RS vgl2(My,"CREATE TABLE tmph(submid VARCHAR(11) collate utf8_general_ci KEY,Datum DATETIME,tel VARCHAR(30),pages INT,attr VARCHAR(20),erfolg INT);",aktc,ZDB);
					RS vgl3(My,"INSERT INTO tmph VALUES "+inse,aktc,ZDB);
					// die laut xferfaxlog uebermittelten Faxe, die nicht in outa als uebermittelt eingetragen sind, 
					// und zu denen nicht bereits eine erfolgreiche capisuite-Uebertragung eingetragen ist
					RS ntr(My,"SELECT t.submid p0,t.tel p1,a.original p2,unix_timestamp(t.Datum) p3,IF(ISNULL(a.hdateidatum),t.Datum,a.hdateidatum) p4, "
							"a.idudoc p5,t.pages p6 FROM tmph t "
							"LEFT JOIN `"+touta+"` o ON t.submid = o.submid "
							"LEFT JOIN `"+altspool+"` a ON t.submid=a.hylanr "
							"LEFT JOIN `"+touta+"` o2 ON o2.submid=a.capispooldt AND NOT ISNULL(a.capispooldt) AND a.capispooldt<>'' AND o2.erfolg<>0 "
							"WHERE ISNULL(o.erfolg) AND t.erfolg<>0 AND (ISNULL(o2.submid) OR o2.submid='') "
							"GROUP BY t.submid",aktc,ZDB);
					char ***cerg;
					//// size_t znr=0;
					size_t zru=0;
					while (cerg=ntr.HolZeile(),cerg?*cerg:0) {
						////<<"znr: "<<rot<<++znr<<schwarz<<endl;
						const string hylanr{cjj(cerg,0)};
						/*4*/fsfcl fsf(hylanr); // hylanr
						svec qrueck;
						const string wo{varsphylavz+"/archive/"+hylanr};
						if (findv==1) {
							cmd="find "+wo+" -iname \"doc*\\.pdf\\."+hylanr+"\"";
							systemrueck(cmd,obverb>0?obverb-1:0,oblog,&qrueck);
						} else findfile(&qrueck,findv,obverb,oblog,0,wo,/*muster=*/"doc.*\\.pdf\\."+hylanr+"$",1,1,Fol_Dat,0,0,1);
						struct stat entrys{0};
						if (qrueck.size()) {
							lstat(qrueck[0].c_str(),&entrys);
						}
						if (*(*cerg+1)) fsf.telnr=*(*cerg+1);    // tel
						if (*(*cerg+2)) fsf.original=*(*cerg+2); // original
						if (*(*cerg+3)) fsf.xtts=atol(*(*cerg+3)); // Datum (aus xferfaxlog, tts
						if (*(*cerg+4)) fsf.hdd=*(*cerg+4); // hdateidatum
						if (*(*cerg+5)) fsf.idudoc=*(*cerg+5);
						if (fsf.idudoc.empty()) fsf.idudoc="0";
						if (*(*cerg+6)) fsf.pseiten=atol(*(*cerg+6));
						if (!zru++) {
							cout<<violett<<Tx[T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
							cout<<schwarz<<setw(20)<<"submid"<<"|"<<setw(25)<<Tx[T_telnr]<<"|"<<setw(12)<<Tx[T_zp]<<"|"
								<<setw(19)<<Tx[T_Dateidatum]<<"|"<<setw(7)<<Tx[T_pages]<<schwarz<<"|"<<blau<<Tx[T_docname]<<schwarz<<endl;
						} // 							if (!zru++)
						cout<<
							setw(4)<<zru<<") "<<
							blau<<setw(14)<<cjj(cerg,0)<<schwarz<<"|"<<
							violett<<setw(25)<<cjj(cerg,1)<<schwarz<<"|"<<
							blau<<setw(12)<<cjj(cerg,3)<<"|"<<
							violett<<setw(19)<<cjj(cerg,4)<<"|"<<
							violett<<setw(7)<<cjj(cerg,6)<<"|"<<
							blau<<string(cjj(cerg,2)).substr(0,55)<<schwarz<<endl;
						//// <<"vor archiviere, telnr: "<<fsf.telnr<<" xtts: "<<fsf.xtts<<" hdd: "<<fsf.hdd<<" original: "<<fsf.original<<
						////                           " hdd: "<<fsf.hdd<<" idudoc: "<<fsf.idudoc<<endl;
						fsf.archiviere(My,this,&entrys,0,hyla,0,3,obverb,oblog);
					} // 				while (cerg=ntr.HolZeile(),cerg?*cerg:0)
					//		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_OFF);
				} // 			if (inse.size()>1)
				//// "select tmph.i,submid,erfolg,outa.* from tmph left join outa on tmph.i=outa.submid
				//// select t.*,a.capispooldt,o2.erfolg, o2.submid from tmph t left join outa o on t.submid = o.submid 
				//// left join altspool a on a.hylanr = t.submid left join outa o2 on a.capispooldt=o2.submid where isnull(o.submid);
				char ***cerg;
				size_t cergz=0;
				if (auswe.size()>2) {
					RS rs1(My,"SELECT submid FROM `"+touta+"` WHERE erfolg=0 AND submid IN "+auswe,aktc,ZDB);
					////"` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
					string auswmf{"("};  // fuer die Ausgabe
					while (cerg=rs1.HolZeile(),cerg?*cerg:0) {
						if (!cergz++)
							fLog(Tx[T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Erfolg_gesetzt_werden],1,1);
						auswmf+="'";
						auswmf+=cjj(cerg,0); 
						auswmf+="',";
						//// <<violett<<cjj(cerg,0)<<schwarz<<endl; 
					} //// 				while (cerg=rs1.HolZeile(),cerg?*cerg:0)
					if (cergz) {
						auswmf[auswmf.size()-1]=')';
						tu_lista("",auswmf);
						RS k1(My,"UPDATE `"+touta+"` SET erfolg=1 WHERE erfolg=0 AND submid IN "+auswe,aktc,ZDB);
					} // 				if (cergz) 
				} // 		if (auswe.size()>1)
				if (auswm.size()>2) {
					RS rs2(My,"SELECT submid FROM `"+touta+"` WHERE erfolg=1 AND submid IN "+auswm,aktc,ZDB);
					// "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
					cergz=0;
					string auswef{"("}; // zur Ausgabe
					while (cerg=rs2.HolZeile(),cerg?*cerg:0) {
						if (!cergz++)
							fLog(Tx[T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Misserfolg_gesetzt_werden],1,1);
						auswef+="'";
						auswef+=cjj(cerg,0); 
						auswef+="',";
						//// <<rot<<cjj(cerg,0)<<schwarz<<endl; 
					} // 			while (cerg=rs2.HolZeile(),cerg?*cerg:0)
					if (cergz) {
						auswef[auswef.size()-1]=')';
						tu_lista("",auswef);
						RS k1(My,"UPDATE `"+touta+"` SET erfolg=0 WHERE erfolg=1 AND submid IN "+auswm,aktc,ZDB);
					} // 				if (cergz) 
				} // 		if (auswm.size()>1)
				//// <<blau<<auswe<<schwarz<<endl;
				//// <<rot<<auswm<<schwarz<<endl;
				////	return;
				//// string ausw="(";
				//// uchar indb;
				//// string hylanr;
				////        RS rs(My,string("SELECT id FROM `")+touta+"` WHERE submid="+hylanr,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",aktc,ZDB);
				////        if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
				//// if (!indb) KLA
				////		<<hylanr<<" fehlt"<<endl;
				////		/*4*/fsfcl fsf(hylanr); // fsf(rueck[i]);
				//// KLZ // if (!indb)
				//// RS rs(My,string("SELECT id FROM `")+touta+"` WHERE submid in "+ausw,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",aktc,ZDB);
				//// while (cerg=rs.HolZeile(),cerg?*cerg:0) KLA
				//// KLZ
			} // if (!lstat(hsendqvz.c_str(),&entryvz))
		} // 	if (!xferfaxlog.empty())
		/*//
			if (!gehtmitxfer) {
			set<string> fdn; // Fax-Dateien
			svec qrueck;
			if (findv==1) {
			cmd=sudc+"find "+varsphylavz+" -regex '.*q[0-9]+' -print0 "+(obverb?"":"2>/dev/null")+"| /usr/bin/xargs -0 grep -l ^state:7 "; // gesandt
			qrueck.clear();
			systemrueck(cmd,obverb,oblog,&qrueck);
			} else {
			findfile(&qrueck,findv,obverb,oblog,0,varsphylavz,"/q[0123456789]+$",-1,1,0,0,0,1);
			for (size_t i=qrueck.size();i;) {
			i--;
			uchar gef=0;
			mdatei qr(qrueck[i],ios::in);
			if (qr.is_open()) {
			string zeile;
			while(getline(qr,zeile)) {
			if (!zeile.find("state:7")){gef=1;break;}
			}
			qr.close();
			}
			if (!gef) qrueck.erase(qrueck.begin()+i);
			}
			}
			for(size_t qruecki=0;qruecki<qrueck.size();qruecki++) {
			size_t pos;
			if ((pos=qrueck[qruecki].rfind("/q"))!=string::npos) fdn.insert(qrueck[qruecki].substr(pos+2));
			} //           for(qruecki=0;qruecki<qrueck.size();qruecki++)
			if (0) {
			string sql="SELECT titel p0, tsid p1, submt p2, submid p3, oscht p4, subject p5, docname p6, id p7, fsize p8, pages p9, "
			"devname p10, retries p11, prio p12, rcfax p13, rcname p14, csid p15, sender p16, transs p17, transe p18, Pid p19, eind p20, Erfolg p21 "
			"FROM `"+touta+"` WHERE submid "+(runde?"RLIKE '^[0-9]+$' AND submid<>0":"LIKE '%fax-%.sff'")+" ORDER BY submt";
			RS routa(My,sql,aktc,obverb);
			if (!routa.obqueryfehler) {
			char ***cerg;
			while (cerg=routa.HolZeile(),cerg?*cerg:0) {
			if (*(*cerg+3)) if (*(*cerg+20)) if (*(*cerg+21)) {
			string farbe=rot;
			if (runde)
			fit=fdn.find(*(*cerg+3));
			else
			fit=fdn.find(cdonevz+vtz+cuser+"-"+*(*cerg+3));
			if ((fit!=fdn.end()) != (**(*cerg+21)=='0')) farbe=blau;
			else {
			stringstream ausg;
			if (fit!=fdn.end()) {
			ausg<<Tx[T_gefunden]<<": "<<(int)(fit!=fdn.end())<<" "<<
			Tx[T_Falschals]<<(**(*cerg+21)=='0'?Tx[T_gescheitert]:Tx[T_gesandt])<<Tx[T_eingeordnet]<<farbe<<setw(14)<<
		 cjj(cerg,3)<<schwarz<<" "<<cjj(cerg,2)<<" "<<blau<<cjj(cerg,6)<<schwarz;
		 fLog(ausg.str(),1,1);
		//                RS vs(My,"UPDATE `"+touta+"` SET Erfolg= !Erfolg WHERE submid = '"+cjj(cerg,3)+"'",aktc,ZDB);
		} //               if (fit!=fdn.end())
		} // ((fit!=fdn.end()) != (*cjj(cerg,21)=='0')) else
		} // if (*(*cerg+3)) if (*(*cerg+20)) if (*(*cerg+21)) 
		} // while (cerg=routa.HolZeile(),cerg?*cerg:0) 
		} // if (!routa.obqueryfehler) 
		} // if (0)
		} // 	if (!gehtmitxfer)
		 */
		hLog(violetts+Txk[T_Ende]+Tx[T_korrigierehyla]+schwarz);
} // void hhcl::korrigierehyla

//α
void hhcl::pvirtnachvi()
{ //ω
	standardprio(/*obmitsetz*/1);
} //α

// aufgerufen in lauf
void hhcl::pvirtnachrueckfragen()
{
	hLog(violetts+Tx[T_pvirtnachrueckfragen]+schwarz);
	if (rzf) { //ω
		const size_t aktc{0};
		sqlrp.clear();
		unsigned neunr{1}; // Nr. des SQL-Befehles nach neuer Zaehlung
		schAcl<optcl> oprsql=schAcl<optcl>("oprsql"); // Optionen
		for(size_t akt=0;/*akt<sqlzn*/1;) {
			//// <<"akt: "<<akt<<" "<<sqlp[akt]<<endl;
			const string *const vorgabe{(akt<sqlzn?(string*)opn[akt+sqlz0]->pptr/*sqlp[akt]*/:&nix)};
			//// <<"vorgabe: "<<*vorgabe<<", sqlvp["<<akt<<"]: "<<sqlvp[akt]<<endl;
			akt++;
			string zwi;
			while (1) {
				zwi=Tippstr(string(Tx[T_SQL_Befehl_Nr])+ltoan(akt)+(vorgabe->empty()?
							Tx[T_faxnr_wird_ersetzt_mit_der_Faxnr]:
							Tx[T_Strich_ist_SQL_Befehl_loeschen_faxnr_wird_ersetzt_mit_der_Faxnr]),
						vorgabe,/*obnichtleer=*/0);
				if (zwi=="-") zwi.clear();
				if (zwi.empty()) {
					break;
				} else {
					svec dben=holdbaussql(zwi);
					DB *testDB[dben.size()];
					//// <<"dben.size(): "<<(int)dben.size()<<endl;
					uchar dbda{1};
					if (!dben.size()) {
						if (Tippob(Tx[T_In]+rots+zwi+blau+Tx[T_keine_Datenbank_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) continue;
						dbda=0;
					} else { // if (!dben.size()) 
						uchar nochmal{0};
						for(size_t i=0;i<dben.size();i++) {
							//// <<"i: "<<blau<<i<<rot<<": "<<dben[i]<<schwarz<<endl;
							if (pruefDB(&testDB[i], dben[i])) {
								dbda=0;
								if (Tippob(Tx[T_Datenbank]+rots+dben[i]+blau+Tx[T_nicht_ermittelbar_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) {
									nochmal=1;
									break;
								} // if (strchr("jyJYoOsS",(int)erg)) 
							} // if (pruefDB(dben[i])) 
						} // for(size_t i=0;i<dben.size();i++) 
						if (nochmal) continue;     
					} // if (!dben.size()) 
					if (dbda) {
						if (zwi.find("&&faxnr&&")==string::npos) {
							if (Tippob(Tx[T_In]+rots+zwi+blau+Tx[T_keinmal_faxnr_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) continue;
						} else {
							RS rtest(testDB[0],ersetzAllezu(zwi,"&&faxnr&&","9999"),aktc,ZDB); //// (const char*)trimfaxnr));
							if (rtest.obqueryfehler) {
								if (Tippob(Tx[T_In]+rots+zwi+blau+Tx[T_koennte_ein_SQL_Fehler_sein_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) continue;
							} // if (rtest.obqueryfehler)
						} // if (zwi.find("&&faxnr&&")==string::npos) 
					} // if (dbda)
					for(size_t i=0;i<dben.size();i++) {
						if (testDB[i]) {delete testDB[i];testDB[i]=0;}
					}
				} // if (zwi.empty()) else
				break;
			} // while (1)
			if (zwi.empty()) {
			} else {
				// hier Sql-Dateien pruefen
				/*
					 cppSchluess* neuS=new cppSchluess;
					 neuS->name=string(cSQL_)+ltoan(++aktsp);
					 neuS->wert=zwi;
					 sqlv.push_back(neuS);
					 nsqlzn++;
				 */
				sqlrp.push_back(shared_ptr<string>(new string(zwi)));
				const string istr{ltoan(neunr)};
				stringstream soptname;
				soptname<<cSQL_<<(neunr++);
				//// <<"akt: "<<(akt)<<" "<<*(string*)opn.omap[soptname.str()]->pptr<<endl;
				//			opn.omap[soptname.str()]->virtoausgeb();
				optcl *opp{new optcl(/*pname*/soptname.str(),/*pptr*/sqlrp[sqlrp.size()-1].get(),/*art*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_SQL_Befehl_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/1,Tx[T_SQL_Befehl])};
				oprsql<<opp;
			} // if (zwi.empty()) else
			// sqlzn-1 waere sehr viel
			if (akt+1>sqlzn) {
				if (!Tippob(Tx[T_Wolle_Sie_noch_einen_SQL_Befehl_eingeben],Txk[T_j_af])) { 
					break;
				}
			}
			//			map<const char* const,optcl const*>::iterator omit;
			//			shared_ptr<optcl> omit;
		} // 		for(size_t akt=0;1;)
		sqlzn=neunr-1;
		// vorherige SQL-Abfragen loeschen
		for(auto omit=opn.schl.end();omit!=opn.schl.begin();) {
			omit--;
			if (!(*omit)->pname.find(cSQL_)) {
				(*omit)->virtloeschomaps(&opn);
				opn.schl.erase(omit);
			}
		}
		// aktuelle SQL-Abfragen eintragen
		for(auto omit=oprsql.schl.begin();omit!=oprsql.schl.end();omit++) {
			opn<<(*omit);
		}
		schAcl<optcl> oprzm=schAcl<optcl>("oprzm"); // Optionen
		zmmrp.clear();
		zmzrp.clear();
		neunr=1; // Nr. des Zielmusterpaares nach neuer Zaehlung
		zmmrp.clear();
		zmzrp.clear();
		////opn.oausgeb(blau);
		for(size_t akt=0;/*akt<zmzn*/1;) {
			const string *const vgbm{(akt<zmzn?&zmsp[akt]->muster:&nix)},
						*const vgbz{(akt<zmzn?&zmsp[akt]->ziel:&nix)};
			akt++;
			string zwim,zwiz;
			while (1) {
				zwim=Tippstr(string(Tx[T_Zielmuster_Nr])+ltoan(akt)+Tx[(akt<zmzn?T_zum_Streichen_Strich_eingeben:T_beim_letzten_fuer_alle_Uebrigen_nichts_eingeben)],vgbm,/*obnichtleer=*/0);
				if (zwim=="-") break;
				zwiz=Tippverz(string(Tx[T_Zielverzeichnis_Nr])+ltoan(akt),vgbz);
				if (!zwiz.empty()) break;
			} // while (1)
			if (zwim=="-") {
			} else {
				zmmrp.push_back(shared_ptr<string>(new string(zwim)));
				zmzrp.push_back(shared_ptr<string>(new string(zwiz)));
				const string istr{ltoan(neunr)};
				stringstream zmmname,zmzname;
				zmmname<<cZMMuster_<<neunr;
				zmzname<<cZMZiel_<<neunr;
				//// <<"akt: "<<(akt)<<" "<<*(string*)opn.omap[soptname.str()]->pptr<<endl;
				//			opn.omap[soptname.str()]->virtoausgeb();
				optcl *opmp{new optcl(/*pname*/zmmname.str(),/*pptr*/zmmrp[neunr-1].get(),/*art*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Zielmuster_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/2,Tx[T_Zielmuster])};
				oprzm<<opmp;
				optcl *opzp{new optcl(/*pname*/zmzname.str(),/*pptr*/zmzrp[neunr-1].get(),/*art*/pstri,/*kurzi*/-1,/*langi*/-1,/*TxBp*/&Tx,/*Txi*/T_Ziel_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/2,/*Txtrf*/Tx[T_Ziel])};
				oprzm<<opzp;
				neunr++;
			} // 			if (zwim=="-")
			if (zwim.empty())
				break;
		} // 		for(size_t akt=0;/*akt<zmzn*/1;akt++)
		zmzn=neunr-1;
		// vorherige Zielmusterpaare loeschen
		for(auto omit=opn.schl.end();omit!=opn.schl.begin();) {
			omit--;
			if (!(*omit)->pname.find(cZMMuster_)||!(*omit)->pname.find(cZMZiel_)) {
				(*omit)->virtloeschomaps(&opn);
				opn.schl.erase(omit);
			}
		}
		// aktuelle Zielmusterpaare eintragen
		for(auto omit=oprzm.schl.begin();omit!=oprzm.schl.end();omit++) {
			opn<<(*omit);
		}
		standardprio(/*obmitsetz*/1);
	} // 	if (rzf) //α
	// if (initDB()) exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));  //ω
	if (obfa[0]||obweg[0]==1) {
		svec vzv;
		if (!systemrueck("fbfax -zgvz",obverb,oblog,&vzv)) {
			if (vzv.size()>2) {fbnvz=vzv[2]; gtrim(&fbnvz);}
			if (vzv.size()>1) {fbgvz=vzv[1]; gtrim(&fbgvz);}
			if (vzv.size()>0) {fbwvz=vzv[0]; gtrim(&fbwvz);}
			else obfa[0]=obweg[0]=0;
		}
	}
	if (tulista||tulistf||tulisti||tulistw||!suchstr.empty()) {
		// wird fuer kez und normalen Ablauf spaeter in virtpruefweiteres abgerufen
		if (initDB()) {
			exit(schluss(10,Tx[T_Datenbank_nicht_initialisierbar_breche_ab]));
		}
		obsetz=0; // Aufruf nicht mitzaehlen
		keineverarbeitung=1; // nicht pruefggfmehrfach aufrufen
		if (tulista) {
			tu_lista("1");
		} else if (tulistf) {
			tu_lista("0");
		} else if (tulisti) {
			tu_listi();
		} else if (tulistw) {
			untersuchespool(/*mitupd=*/0,/*aktc=*/3);
			zeigweitere();
			hLog(blaus+Txk[T_Ende]+schwarz);
		} else if (!suchstr.empty()) {
			suchestr();
		} // if (tulista) else else else else
	} // 	if (tulista||listf||listi||listw||!suchstr.empty())
} // void hhcl::pvirtnachrueckfragen //α
//ω

// die *.nix-Dateien wieder loeschen, wenn der zugrundeliegende Fehler nicht mehr nachweisbar ist
// aufgerufen in pvirtfuehraus
void hhcl::loeschenix()
{
	// eine Liste der ziele ohne Doppelte erstellen
	set<string> vzn;
	for(auto zmakt: zmsp) {
		vzn.insert(zmakt->ziel);
	}
	// daraus einen Suchpfad erstellen
	string pfade;
	for(auto vz: vzn) {
   pfade+=" "+vz;
	}
	// eine Runde fuer 'nichtgefaxt', eine fuer 'nicht faxbar'
	for(int iru=0;iru<2;iru++) {
		string namstr;
		size_t tref{iru?T_nichtfaxbar:T_nichtgefaxt};
		// fuer alle Sprachen
		Sprache altSpr{Tx.lgn};
		for(int aktsp=0;aktsp<SprachZahl;aktsp++) {
			Tx.lgn=(Sprache)aktsp;
			if (aktsp) namstr+=" -o ";
			namstr+="-name '";
			namstr+=Tx[tref];
			namstr+="*`*`.nix'";
		} // 		for(int aktsp=0;aktsp<SprachZahl;aktsp++)
		Tx.lgn=altSpr;
		svec frueck;
		systemrueck("find"+pfade+" -maxdepth 1 -size 0 \\( "+namstr+" \\)",obverb,oblog,&frueck,/*obsudc=*/1);
		for(size_t j=0;j<frueck.size();j++) {
			size_t p1{frueck[j].find('`')}, 
						 p2{frueck[j].rfind('`')};
			string udat{(iru?zufaxenvz:ngvz)+vtz+frueck[j].substr(p1+1,p2-p1-1)};
			struct stat statudat{0};
			// wenn es die zugrundeliegende Datei nicht mehr gibt, dann auch die nix-Datei loeschen
			if (lstat(udat.c_str(),&statudat)) {
				tuloeschen(frueck[j],cuser,obverb,oblog);
			}
		} // 		for(size_t j=0;j<frueck.size();j++)
	} // 	for(int iru=0;iru<2;iru++)
} // void hhcl::loeschenix

void hhcl::pvirtfuehraus() //α
{ 
	hLog(violetts+Tx[T_pvirtfuehraus]+schwarz); //ω
	if (kez||bvz||anhl||tulista||tulistf||tulisti||tulistw||!suchstr.empty()) {
		// also bei den in pvirtnachrueckfragen Abgehandelten hier nichts mehr tun
		if (kez) {
			// hier ggf. erstes fork
			const pid_t pid{nurempf||nursend?0:dfork()};
			if (pid>0) {
				pidcl phier(pid,Tx[T_korrigiere]);
				pidw<<phier;
				pidv<<phier;
			} else if (!pid) {
				hLog(violetts+Tx[T_korrigiere]+schwarz);
				if (obfa[0]||obweg[0]==1) korrigierefbox(ltage);
				if (obfa[1]||obweg[1]==1) korrigierecapi(ltage);
				if (obfa[2]||obweg[2]==1) korrigierehyla(ltage);
				exitt(0);
			} else if (pid<0) {
				hLog(rots+Tx[T_Gabelung_zu_korrigiere_misslungen]+schwarz);
				exitt(17);
			} // 	if (!pid)
			empfarch(/*obalte=*/1);
			wartaufpids(&pidw,0,obverb,oblog,Tx[T_in_korrerfolgszeichen]); // wird also nur vom Hauptthread aus aufgerufen
		} else if (bvz) {
			bereinigevz(/*aktc=*/0);
		} else if (anhl) {
			anhalten();
		} // 		if (kez)
	} else {
		pruefcron(nix); // soll vor hLog(Tx[T_Verwende ... stehen
		if (!keineverarbeitung) {
			pruefstdfaxnr(My,muser,host,obverb,oblog);
			prueffuncgettel3(My,muser,host,obverb,oblog);
			loeschenix();
			////  int qerg = mysql_query(My.conn,proc.c_str());
			// 1) nicht-pdf-Dateien in pdf umwandeln, 2) pdf-Dateien faxen, 3) alle in warte-Verzeichnis kopieren, 4) in Spool-Tabelle eintragen
			////  vector<string> npdf, spdf;
			if (obfrbox) if (obfa[0]||obweg[0]==1) if (!prueffbox()) obfa[0]=obweg[0]=0;
			if (obfcard) if (obfa[1]||obweg[1]==1) if (!pruefcapi()) obfa[1]=obweg[1]=0;
			if (obmodem) if (obfa[2]||obweg[2]==1) if (!pruefhyla()) obfa[2]=obweg[2]=0;
			if (loef||loew||loea) {
				if (loef) aenderefax(/*aktion=*/0,/*aktc=*/0);
				if (loew) loeschewaise();
				if (loea) loescheallewartenden();
			} else if (erneut) {
				empferneut();
			} else if (uml||auml) {
				aenderefax(uml?/*aktion=*/1:2,/*aktc=*/0);
			} else {
				// bei jedem 1000. Aufruf
				if (!(aufrufe % 1000 )) {
					// hier ggf. erstes fork
					const pid_t pidb{nurempf||nursend?1:dfork()};
					if (!pidb) {
						bereinigevz(11);
						exitt(0);
					} else if (pidb<0) {
						hLog(rots+Tx[T_Gabelung_zu_bereinigevz_misslungen]+schwarz);
						exitt(17);
					} // 					if (!pidb)
					pidv<<pidcl(pidb,"bereinigevz");
				} // 				if (aufrufe % 1000 )
				// hier stehen obfa[1] und obfa[2] fest
				ulong rzahl{0}, szahl{0}, zzahl{0};
				uchar rlaeuft{0}, slaeuft{0}, zlaeuft{0};
				uchar zaehlergeschrieben{0};
				pid_t pide{-1}, pids{-1}, pidz{-1};
				while (1) {
					static  int wzahl{0};
					wzahl++;
					if (wzahl<20)
					if (!rlaeuft) {
						// hier ggf. erstes fork
						pide=nurempf?0:nursend?1:dfork();
						if (!pide) {
							empfarch();
							exitt(0);
						} else if (pide<0) {
							hLog(rots+Tx[T_Gabelung_zu_empfarch_misslungen]+schwarz);
							exitt(17);
						} // 					if (!pide)
						while(1) {
							if (kill(pide,0)!=-1 || errno!=ESRCH) {
								rzahl++;	
								rlaeuft=1;
								break;
							} // 							if (kill(pide,0)!=-1 || errno!=ESRCH)
						} // 						while(1)
						pidv<<pidcl(pide,"empfarch");
					} //					if (!rlaeuft)

					if (!slaeuft) {
						// hier ggf. erstes fork
						pids=nurempf?1:nursend?0:dfork();
						if (!pids) {
							inspoolschreiben(/*aktc=*/3);
							wegfaxen(/*aktc=*/3);
							// Dateien in Spool-Tabelle nach inzwischen Verarbeiteten durchsuchen, Datenbank- und Dateieintraege korrigieren 
							untersuchespool(/*mitupd=*/1,/*aktc=*/3);
							if (obfa[0]||obweg[0]==1||obfa[1]||obweg[1]==1||obfa[2]||obweg[2]==1) {
								bestimmtage();
								tage=1;
								// hier ggf. erstes fork
								const pid_t pid{nurempf||nursend?0:dfork()};
								if (pid>0) {
									pidcl phier(pid,Tx[T_korrigiere]);
									pidw<<phier;
									pidv<<phier;
								} else if (!pid) {
////									obverb=1; ZDB=1;
									hLog(violetts+Tx[T_korrigiere]+schwarz);
									if (obfa[0]||obweg[0]==1) { if (tage) korrigierefbox(tage,9); } // 					if (obfa[0])
									if (obfa[1]||obweg[1]==1) { if (tage) korrigierecapi(tage,9); } // 					if (obfa[1])
									if (obfa[2]||obweg[2]==1) { if (tage) korrigierehyla(tage,10);} // braucht bei mir mit 2500 Eintraegen in altspool ca. 30000 clocks
////									obverb=0; ZDB=0;
									exitt(0);
								} else if (pid<0) {
									hLog(rots+Tx[T_Gabelung_zu_korrigiere_misslungen]+schwarz);
									exitt(17);
								} // 	if (!pid)
							}
							// 2. warte auf korrigierefbox, korrigierecapi und korrigierehyla
							if (!nursend) {
								wartaufpids(&pidw,0,obverb,oblog,Tx[T_in_pvirtfuehraus_pidw]);
								exitt(0);
							}
						} else if (pids<0) {
							hLog(rots+Tx[T_Gabelung_zu_wegfaxen_misslungen]+schwarz);
							exitt(17);
						} // 					if (!pids)
						while(1) {
							if (kill(pids,0)!=-1 || errno!=ESRCH) {
								szahl++;	
								slaeuft=1;
								break;
							}
						} // 						while(1)
						pidv<<pidcl(pids,"wegfaxen");
					} // 					if (!slaeuft)

					if (!zlaeuft) {
//						if (obfa[0] || obfa[1] || obfa[2]) {
							// hier ggf. erstes fork
							pidz=nurempf||nursend?0:dfork();
							if (!pidz) {
								zeigweitere();
								exitt(0);
							} else if (pidz<0) {
								hLog(rots+Tx[T_Gabelung_zu_zeigweitere_misslungen]+schwarz);
								exitt(17);
							} // 					if (!pidz)
							while(1) {
								// wenn Programm noch laeuft
								if (kill(pidz,0)!=-1 || errno!=ESRCH) {
									zzahl++;	
									zlaeuft=1;
									break;
								} // 								if (kill(pidz,0)!=-1 || errno!=ESRCH)
							} // 							while(1)
							pidv<<pidcl(pidz,"zeigweitere");
//						} // 				if (obcapi || obhyla)
					} // 					if (!zlaeuft) 

					if (!zaehlergeschrieben) {
						setzzaehler();
						schreibzaehler();
						zaehlergeschrieben=1;
					} // 					if (!zaehlergeschrieben)
					const ssize_t wz1{100}, wz2{250};
					const int sz{240}; // so oft ueberpruefen undd wz2 ms auf den letzten thread warten, ehe die anderen nochmal gestartet werden
					uchar efertig{0},sfertig{0},zfertig{0};
////					int altobverb=obverb; obverb=2;
					if (obverb>1) fLog("Pid: "+blaus+ltoan(getpid())+schwarz);
					for(int ru=0;ru<sz;ru++) {
						// warten, bis ein thread nicht mehr laeuft
						for (unsigned long long int iru=0;;iru++) {
							for(size_t i=pidv.size();i;) {
								i--;
								const int res{kill(pidv.at(i).pid,0)};
								uchar zuloeschen{0};
								if (res==-1 && errno==ESRCH) zuloeschen=1;
								else {
									int status; pid_t erg=waitpid(pidv.at(i).pid,&status,WNOHANG); if (erg>0) zuloeschen=1;
								}
								yLog(obverb>1,oblog,0,0," i: %s%zu%s, pid: %s%ld%s, name: %s%s%s, beendet: %s%d%s",
										blau,i,schwarz,blau,(long)pidv.at(i).pid,schwarz,blau,pidv.at(i).name.c_str(),schwarz,blau,zuloeschen,schwarz);
								if (zuloeschen) {
									//// <<"pidv.at(i).pid: "<<pidv.at(i).pid<<" pide: "<<pide<<" pids: "<<pids<<" pidz: "<<pidz<<endl;
									if (pidv.at(i).pid==pide) rlaeuft=0;
									else if (pidv.at(i).pid==pids) slaeuft=0;
									else if (pidv.at(i).pid==pidz) zlaeuft=0;
									////<<violett<<"loesche: "<<rot<<(pidv.begin()+i)->name<<endl;
									pidv.erase(pidv.begin()+i);
								}
							} // 		for(size_t i=0;i<pidv.size();i++)
							//// <<"pidv.size(): "<<pidv.size()<<endl;
							const int altoblog{oblog};
							if (!(iru%100)) oblog=1;
							yLog(obverb>1,oblog>1,0,0,"elaueft: %s%d%s, rzahl: %s%d%s",blau,rlaeuft,schwarz,blau,rzahl,schwarz);
							yLog(obverb>1,oblog>1,0,0,"slaueft: %s%d%s, szahl: %s%d%s",blau,slaeuft,schwarz,blau,szahl,schwarz);
							yLog(obverb>1,oblog>1,0,0,"zlaueft: %s%d%s, zzahl: %s%d%s",blau,zlaeuft,schwarz,blau,zzahl,schwarz);
							if (!(iru%100)) oblog=altoblog;
							if (!rlaeuft || !slaeuft || !zlaeuft) break;
							this_thread::sleep_for(chrono::milliseconds(wz1));
							yLog(obverb>1,0,0,0,"in %s(): %s%s: %s%d%s ms",__FUNCTION__,rot,Txk[T_warte],blau,wz1,schwarz);
						} // 	while (1)
						// wenn nicht der thread, der noch haengt, zum ersten Mal aufgerufen wurde, dann abbrechen 
						efertig=(rzahl>1||(rzahl==1&&!rlaeuft));
						sfertig=(szahl>1||(szahl==1&&!slaeuft));
						zfertig=(zzahl>1||(zzahl==1&&!zlaeuft)||(!obfa[0]&&obweg[0]!=1&&obher[0]!=1&&!obfa[1]&&obweg[1]!=1&&obher[1]!=1&&!obfa[2]&&obweg[2]!=1&&obher[2]!=1));
						if (efertig&&sfertig&&zfertig) break;
						if (!rzahl||!szahl||!zzahl) break; // wenn eins noch nicht angefangen hat, dann nicht wz2*sz ms lang warten
						this_thread::sleep_for(chrono::milliseconds(wz2));
						yLog(obverb>1,0,0,0,"in %s(): %s%s: %s%d%s ms",__FUNCTION__,rot,Txk[T_warte],blau,wz2,schwarz);
					} // 					for(int i=0;i<sz;i++)
////					obverb=altobverb;
					if (efertig&&sfertig&&zfertig) break;
				} // 				while (1)
			} // if (loef || loew || loea) else if else if
		} // 		if (!keineverarbeitung)
	} // if (kez) else else else
} // void hhcl::pvirtfuehraus  //α

// aufgerufen in lauf
void hhcl::virtschlussanzeige()
{  
	hLog(violetts+Txk[T_virtschlussanzeige]+schwarz); //ω
	dhcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige
 
// aufgerufen in: main und pruefcapi
void hhcl::virtautokonfschreib()
{
//// const auto altobverb{obverb}; obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein])); //ω
	/*//
		capizukonf und hylazukonf hier immer 0
		char buf[200];
		sprintf(buf,"rzf: %d, capizukonf: %d, hylazukonf: %d, obzuschreib: %d",(int)rzf, (int)capizukonf, (int)hylazukonf, (int)obzuschreib);
		hLog(blaus+buf+schwarz);
	 */
	struct stat kstat{0}; //α
	if (lstat(akonfdt.c_str(),&kstat)) {
		caus<<"Setze obzuschreib, da "<<akonfdt<<" nicht da"<<endl;
		hccd.obzuschreib=1;
	}
	if (rzf||hccd.obzuschreib||kschreib) {
		hLog(gruens+Txk[T_schreibe_Konfiguration]+schwarz);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||hccd.obzuschreib) //α
//// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
	if (cfaxcp) { 
		delete cfaxcp; 
		cfaxcp=0; 
	}
} // hhcl::~hhcl //α

// wird nur im Fall obhilfe==3 nicht aufgerufen
void hhcl::virtlieskonfein()
{
////	const int altobverb{obverb}; obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz); //ω
	for(int j=0;j<3;j++) clprios[j]=prios[j];
	for(int j=0;j<3;j++) prios[j]=0;
	hcl::virtlieskonfein(); //α //ω
	// jetzt wird clprios nach der Reihenfolge in prios vervollstaendigt:
	for(int p=1;p<=3;p++) { // fuer jede Prioritaet
		int cont{0};
    for(int j=0;j<3;j++) if (clprios[j]==p) {cont=1;break;} // wenn sie schon vorkommt, ...
		if (cont) continue; // dann nichts tun
		unsigned minp{(unsigned)-1};
		int minj{3+1}; 
		for(int j=0;j<3;j++) if ((obfa[j]||obweg[j]==1) && !clprios[j]) { // wenn nicht, dann
			if ((unsigned)prios[j]<minp) { // ist die kleinste uebrige Prioritaet Kandidat
				minp=prios[j];
				minj=j;
			}
		}
		if (minj<3+1) clprios[minj]=p;
	}
	standardprio(/*obmitsetz*/0);
	// Fritzbox
	// wenn nicht "obfbox=0" in der Konfigurationsdatei steht
	if (obfa[0]||obweg[0]==1||obher[0]==1) {
		fuellfbip();
		if (obfrbox) {
			holfbpar();
	  }
	}
	// sqlzn und zmzn aus den Konfigurationsdateien ermitteln (um sie nicht dort speichern zu muessen)
	sqlzn=0;
	zmzn=0;
	for(size_t nr=0;nr<hccd.paare.size();nr++) {
		if  (!hccd.paare[nr].name.find(cSQL_)) {
			const long neusqlzn{atol(hccd.paare[nr].name.substr(cSQL_.length()).c_str())};
			if (neusqlzn>(long)sqlzn) sqlzn=neusqlzn;
		} else if  (!hccd.paare[nr].name.find(cZMMuster_)) {
			const long neuzmzn{atol(hccd.paare[nr].name.substr(cZMMuster_.length()).c_str())};
			if (neuzmzn>(long)zmzn) zmzn=neuzmzn;
		} else if  (!hccd.paare[nr].name.find(cZMZiel_)) {
			const long neuzmzn{atol(hccd.paare[nr].name.substr(cZMZiel_.length()).c_str())};
			if (neuzmzn>(long)zmzn) zmzn=neuzmzn;
		}
////		<<"Nr."<<nr<<", Name: "<<blau<<hccd.paare[nr].name<<schwarz<<", Wert: "<<violett<<hccd.paare[nr].wert<<schwarz<<endl;
	}
	sqlz0=opn.size();
	if (sqlzn) {
		// wenn SQL-Befehle aus Konfigurkationsdatei geholt
		delete[] sqlp;
		sqlp=new string[sqlzn]{string()};
		schAcl<optcl> opsql=schAcl<optcl>("opsql");
		for(size_t i=0;i<sqlzn;) {
			++i;
			stringstream soptname;
			soptname<<cSQL_<<i;
			opsql<<new optcl(/*pname*/soptname.str(),/*pptr*/&sqlp[i-1],/*art*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_SQL_Befehl_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/ltoan(i),/*wert*/-1,/*woher*/2,Tx[T_SQL_Befehl],/*obno*/0,/*refstr*/0,/*obfragz*/0,/*fnobfragz*/0,/*fnnachhz*/0,/*fnvorhz*/0,/*sonderrf*/1);
			//// folgendes wuerde zum Absturz fuehren (der shared_ptr muss derselbe sein, damit er und sein Inhalt nur einmal versucht wird zu destruieren):
			////		shared_ptr<optcl> kop2{opsql[opsql.size()-1]};
			////		opn<<kop2;
		} // 	for(long i=0;i<sqlzn;)
		// ggf. die Zahlenreichenfolgen neu festlegen, z.B. durch direkte Bearbeitung der Konfigurationsdatei entstandene Luecken schliessen
		hccd.kauswert(&opsql,obverb,/*mitclear*/0);
		sqlzn=0;
		for(auto aktopsql:opsql.schl) {
			if (!((string*)aktopsql->pptr)->empty()) {
				stringstream soptname;
				soptname<<cSQL_<<++sqlzn;
				aktopsql->pname=soptname.str();
				aktopsql->sonderrf=1;
				opn<<aktopsql;
			}
		} // 		for(auto aktopsql:opsql.schl)
		//// opn.oausgeb(rot);
	} // if (sqlzn)
	// wenn in der Konfigurationsdatei keine sql-Befehle stehen, dann die aus den Vorgaben nehmen
	if (!sqlzn) {
		sqlzn=sqlVp.size();
		delete[] sqlp;
		sqlp=new string[sqlzn];
//		opn.omap["sqlz"]->woher=1;
		for(size_t i=0;i<sqlVp.size();i++) {
			sqlp[i]=*(string*)opvsql[i]->pptr;
			//// <<"opvsql["<<i<<"]: "<<*(string*)opvsql[i]->pptr<<endl;
			opvsql[i]->sonderrf=1;
			opn<<opvsql[i];
		}
	} // 	if (!sqlzn)

	zmsp.clear();
	if (zmzn) {
////		<<blau<<"opzm.size(): "<<violett<<opzm.size()<<schwarz<<endl;
//		opn.omap["musterzahl"]->woher=2;
		schAcl<optcl> opzm=schAcl<optcl>("opzm");
		delete[] zmmp;
		zmmp=new string[zmzn];
		delete[] zmzp;
		zmzp=new string[zmzn];
		for(size_t i=0;i<zmzn;) {
			++i;
			stringstream zmmname,zmzname;
			zmmname<<cZMMuster_<<i;
			zmzname<<cZMZiel_<<i;
			////	  const string *const istrp=new string(ltoan(i));	
			const string istr{ltoan(i)};
			opzm<<new optcl(/*pname*/zmmname.str(),/*pptr*/&zmmp[i-1],/*art*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Zielmuster_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/2,Tx[T_Zielmuster]);
			opzm<<new optcl(/*pname*/zmzname.str(),/*pptr*/&zmzp[i-1],/*art*/pstri,-1,-1,/*TxBp*/&Tx,/*Txi*/T_Ziel_Nr,/*wi*/0,/*Txi2*/-1,/*rottxt*/istr,/*wert*/-1,/*woher*/2,Tx[T_Ziel]);
			//// <<"opn.schl.size(): "<<opn.schl.size()<<", omap.size(): "<<opn.omap.size()<<endl;
		} // 	for(long i=0;i<zmzn;)
		////		<<blau<<"opzm.size(): "<<violett<<opzm.size()<<schwarz<<endl;
		////		<<blau<<"opn.size(): "<<violett<<opn.size()<<schwarz<<endl;
		hccd.kauswert(&opzm,obverb,/*mitclear*/0);
////		opzm.oausgeb(rot);
		zmz0=opn.size();
		zmzn=0;
		shared_ptr<optcl> laktopzm=0;
		for(auto aktopzm:opzm.schl) {
			if (laktopzm) {
				// jeden 2. Durchgang auswerten: aktopzm=Ziel, laktopzm=Muster
				if (!((string*)aktopzm->pptr)->empty()) {
					stringstream zmmname,zmzname;
					zmmname<<cZMMuster_<<++zmzn;
					laktopzm->pname=zmmname.str();
					laktopzm->sonderrf=1;
					opn<<laktopzm;
					zmzname<<cZMZiel_<<zmzn;
					aktopzm->pname=zmzname.str();
					aktopzm->sonderrf=1;
					opn<<aktopzm;
					zmsp.push_back(shared_ptr<zielmustercl>(new zielmustercl(*(string*)laktopzm->pptr,*(string*)aktopzm->pptr)));
				}
				laktopzm=0;
			} else {
				laktopzm=aktopzm;
			}
		} // 		for(auto aktopzm:opzm.schl)
		//		opn.gibaus(1);
		//		opzm.~schAcl();
		////		<<"zmznneu: "<<zmznneu<<endl;

	} // 	if (zmzn)
	if (!zmzn) {
		// wenn in der Konfigurationsdatei keine Zielmuster stehen
		zmzn=zmVp.size();
		//		opn.omap["musterzahl"]->woher=1;
		for(size_t i=0;i<zmzn+zmzn;i++) {
			opn<<opvzm[i];
      if (i%2==1) {
				zmsp.push_back(shared_ptr<zielmustercl>(new zielmustercl(*(string*)opvzm[i-1]->pptr,*(string*)opvzm[i]->pptr)));
			}
		} // 		for(long i=0;i<zmzn;i++) 
	} // 	if (!zmzn)
	//// for(size_t i=0;i<zmsp.size();i++) caus<<"i: "<<i<<", zmsp[i].muster: "<<zmsp[i]->muster<<", zmsp[i].ziel: "<<zmsp[i]->ziel<<endl;
	////	opn.oausgeb(rot);
	////	opn.gibomapaus();
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
////	obverb=altobverb;
} // void hhcl::virtlieskonfein() //ω

int main(int argc,char** argv) //α
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,virtinitopt,parsecl,virtMusterVorgb,virtlieskonfein,verarbeitkonf,virtzeigueberschrift,pvirtmacherkl,virttesterg,zeighilfe,pvirtvorzaehler,lieszaehlerein,dovi,virtzeigversion,pvirtvorrueckfragen,rueckfragen,pvirtnachrueckfragen,pruefggfmehrfach,tuloeschen(logdt...,virtpruefweiteres,pruefcron,pvirtfuehraus,virtautokonfschreib,gitpull,wartaufpids,setzzaehler,schreibzaehler,virtschlussanzeige
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
	hLog(violetts+Tx[T_virttesterg]+schwarz);
} //ω


void fsfcl::ausgeb(int obverb) {
	if (obverb) {
		cout<<"id : "<<blau<<id<<schwarz<<", telnr: "<<blau<<telnr<<schwarz<<", spdf: "<<blau<<spdf<<schwarz<<", npdf: "<<blau<<npdf<<schwarz<<", mailges: "<<blau<<mailges<<schwarz<<", original: "<<blau<<original
			<<schwarz<<", origvu: "<<blau<<origvu<<schwarz<<", fobfbox: "<<blau<<(int)fobfbox<<schwarz<<", fobcapi: "<<blau<<(int)fobcapi<<schwarz<<", fobhyla: "<<
			blau<<(int)fobhyla<<schwarz<<", fobkmail: "<<blau<<(int)fobkmail<<schwarz<<", fobvmail: "<<blau<<(int)fobvmail<<schwarz<<", idalt: "<<blau<<idalt<<
			schwarz<<", fbdials: "<<blau<<fbdials<<schwarz<<", fbsdt: '"<<blau<<fbsdt<<schwarz<<"'"<<endl;
	}
}


/* fax löschen:
	 systemctl stop [servicename]
systemctl disable [servicename]
rm /etc/systemd/system/[servicename]
rm /etc/systemd/system/[servicename] # and symlinks that might be related
rm /usr/lib/systemd/system/[servicename]
rm /usr/lib/systemd/system/[servicename] # and symlinks that might be related
systemctl daemon-reload
systemctl reset-failed

1) If hylafax is running, stop running faxgetty on the modem to be removed by finding out the PID and killing the process
2) delete the corresponding config (e.g config.ttySx for serial line modems or config.ttyACMx for usb modems) file in /var/spool/hylafax/etc
3) delete the  corresponding file (e.g config.ttySx for serial line modems or config.ttyACMx for usb modems) from /var/spool/hylafax/status

Delete the associated FIFO.<devid> from /var/spool/hylafax, the
associated config file from /var/spool/hylafax/etc, and the associated
status file from /var/spool/hylafax/status.
*/
