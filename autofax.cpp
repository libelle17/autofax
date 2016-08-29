// Aenderung 4 in linux3
// Namenskonvention: erste Praeferenz wurde darauf gelegt, dass mit der Editor-Suchfunktion moeglichst alle gleichen Bezeichner gefunden werden koennen, zweite Praeferenz darauf, dass deutsche und englische Namenbestandteile moeglichst gut gemischt werden
#ifdef linux
// #include <pgsql/libpq-fe.h> // PGconn
#include <utime.h> // utime(
#include <tiffio.h> // fuer empfarch
#include <iomanip> // setprecision
#elif __MINGW32__ || _MSC_VER
#include <sys/utime.h>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
// // #include "c:\programme\postgresql\9.1\include\libpq-fe.h"
// #include "..\..\..\..\programme\postgresql\9.2\include\libpq-fe.h"
#endif

// #include <iostream>
// #include <fstream> // jetzt in konsole.h
// #include <sstream>
// #include <dirent.h> // DIR, dirent, opendir, readdir, PATH_MAX
// #include <boost/algorithm/string.hpp> // clock // jetzt in konsole.h

// #include "vmime/vmime.hpp"
// #include "vmime/platforms/posix/posixHandler.hpp"
#include "konsole.h"
#include "DB.h"
// #include "iconverter.h"
// #include "datetime_utils.hpp"
// G.Schade 22.4.14 fuer Zusatz-Debugging (SQL): 255, sonst: 0
// fuer die Prozessliste
#define PROC_VERZ "/proc/"
#ifdef linux
#include <sys/utsname.h> // utsname
#endif
#include <set>
const double& version=
#include "version"
;
// Bestandteile der Ueberpruefung auf Funktionsfaehigkeit von hylafax: 
// faxmodem


// const char *logvz; // das reine Verzeichnis
// string logpfad; // zusammengesetzt aus Verzeichnis und name
// const char lgs logdatei_a[PATH_MAX+1] ="/var/log/log_vmparse.txt";
// const char *logdatei = logdatei_a;
const char *logdt="/var/log/autofaxvorgabe.log";// darauf wird in konsole.h verwiesen; muss dann auf lgp zeigen

// const char* logdatname;
uchar ZDB=0; // 255 = mit Debug

class Txautofaxcl: public TxB
{
  public:
    static const char *TextC[][Smax];
    Txautofaxcl() {TCp=(const char* const * const * const *)&TextC;}
} Tx; // class Txautofaxcl

enum T_ 
{/*{{{*/
  T_sprachstr,
  T_j_af,
  T_verarbeitete_Nicht_PDF_Dateien,
  T_verarbeitete_PDF_Dateien,
  T_Soll_die_Capisuite_verwendet_werden,
  T_Soll_Hylafax_verwendet_werden,
  T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden,
  T_Zahl_der_Versuche_in_Capisuite_bis_hylafax_eingeschaltet_wird,
  T_Zahl_der_Versuche_in_hylafax_bis_Capisuite_eingeschaltet_wird,
  T_Linux_Benutzer_fuer_Capisuite,
  T_Hylafax_eigene_Landesvorwahl_ohne_plus_oder_00,
  T_Hylafax_eigene_Ortsvorwahl_ohne_0,
  T_Hylafax_und_Capisuite_eigene_MSN_Faxnummer_ohne_Vorwahl,
  T_Hylafax_Praefix_fuer_ausserorts_zB_0,
  T_Hylafax_Praefix_fuer_das_Ausland_zB_00,
  T_Hylafax_bis_10_Buchstabe_fuer_eigenen_Namen,
  T_Capisuite_bis_20_Buchstaben_fuer_eigenen_Namen,
  T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt,
  T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt,
  T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden,
  T_wartend,
  T_gesandt,
  T_gescheitert,
  T_nicht_in_der_Warteschlange,
  T_woasined,
  T_Der_regulaere_Ausdruck,
  T_konnte_nicht_kompiliert_werden,
  Verbindung_zur_Datenbank_nicht_herstellbar,
  T_Breche_ab,
  T_Konnte_Verzeichnis,
  T_nicht_oeffnen,
  T_zielname_erstes_Ziel,
  T_zielname_Ausweichziel,
  T_Datei,
  T_entspricht,
  T_entsprichtnicht,
  T_entsprichtdoch,
  T_Muster_Doppelpunkt,
  T_Verschiebe,
  T_Fehler_beim_Verschieben,
  T_Kopiere_Doppelpunkt,
  T_Fehler_beim_Kopieren,
  T_Dateiname,
  T_schlechtgeformt,
  T_Fehler_af,
  T_bei,
  T_ja,
  T_nein,
  T_obcapimitDoppelpunkt,
  T_obhylamitDoppelpunkt,
  T_Endung,
  T_Stamm,
  T_trennenach,
  T_ErstelledurchKopieren,
  T_FehlerbeimUmbenennen,
  T_ErstelledurchBenennen,
  T_abgebrochen,
  T_FehlerbeimUmbenennenbei,
  T_aus,
  T_nichtbeschreibbar,
  T_KeinModemmitNamensmuster,
  T_gefundenverwendeHylafaxnicht,
  T_Baudratevon,
  T_mit_af,
  T_zugeringVerwendeHylafaxnicht,
  T_hylafax_faxmodem_nicht_gefunden_Versuche_es_zu_installieren_mit,
  T_StarteHylafax,
  T_hylafaxspringtnichtan,
  T_haengean,
  T_an_mdpp,
  T_KannFcpciNInstVerwCapiNicht,
  T_Kernelversion,
  T_nichtgefFcpciMfdKinstallierwerden,
  T_Konnte,
  T_nichtstarten,
  T_VersucheDatei,
  T_zuinstallieren,
  T_bittestellenSiedieInstallationsdatei,
  T_bereitevtlvonfkn,
  T_StarteCapisuite,
  T_Umwandlungvon,
  T_inPDFmit,
  T_beendetErgebnis,
  T_misserfolg,
  T_Erfolg_af,
  T_lstatfehlgeschlagen,
  T_beiDatei,
  T_konntecapisuiteservice,
  T_malnichtstartenverwN,
  T_SpoolDateierstellt,
  T_SpoolDatei,
  T_SpoolPfad,
  T_DieFaxnrausTabelle,
  T_istleerfaxeesdahernicht,
  T_DieFaxnrvon,
  T_ist,
  T_faxemitCFehler,
  T_Faxdatei,
  T_fehlt,
  T_hat0Bytes,
  T_Faxbefehl,
  T_nichtgefundenloeschesieausDB,
  T_KeinErgebnisbeimFaxen,
  T_HylafaxBefehl,
  T_Anwahlen,
  T_kommaDatei,
  T_Status,
  T_bzw,
  T_Falschals,
  T_eingeordnet,
  T_DateienzahlimVz,
  T_ZahldDSmwegzuschickendenFaxenin,
  T_PDFDatei,
  T_beiSQLAbfrage,
  T_obgescheitert,
  T_Fehler_beim_Verschieben_Ausrufezeichen,
  T_0Bytes,
  T_Loesche_Ausrufezeichen,
  T_nicht_geloescht_war_eh_nicht_mehr_da,
  T_Verwaiste_Datei,
  T_geloescht_Fax_schon_in,
  T_archiviert_Ausrufezeichen,
  T_Weitere_Spool_Eintraege,
  T_Zeit_Doppelpunkt,
  T_Zahl_der_ueberpruefen_Datenbankeintraege,
  T_davon_gescheiterte_Faxe,
  T_davon_erfolgreiche_Faxe,
  T_davon_noch_wartende_Faxe,
  T_davon_nicht_in_Warteschlange,
  T_Fertig_mit,
  T_Fehler_beim_Datumsetzen_von,
  T_eindeutige_Identifikation,
  T_Originalname_der_Datei,
  T_Originalname_der_Datei_vor_Umwandlung_in_PDF,
  T_zu_senden_an,
  T_Prioritaet_aus_Dateinamen,
  T_Zahl_der_bisherigen_Versuche_in_Capisuite,
  T_Zahl_der_bisherigen_Versuche_in_Hylafax,
  T_Spooldatei_in_Capisuite,
  T_Pfad_zur_Spooldatei_in_Capisuite_ohne_abschliessendes_Verzeichnistrennzeichen,
  T_Aenderungszeit_der_CapiSpoolDatei,
  T_Aenderungszeit_der_CapiSpooldatei_im_time_Format,
  T_Aenderungszeit_der_Hylaspooldatei,
  T_Aenderungszeit_der_Hylaspooldatei_im_Time_Format,
  T_jobid_in_letztem_gescheitertem_hylafax,
  T_state_Feld_in_hylafax,
  T_statuscode_in_letztem_gescheitertem_hylafax,
  T_status_in_letztem_gescheitertem_hylafax,
  T_capispooldateien_der_Capisuite,
  T_Fehler_beim_Pruefen_von,
  T_Name_des_Adressaten,
  T_Datum_des_Losschickens,
  T_Ende_der_Uebertragung,
  T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname,
  T_Dateigroesse,
  T_Seitenzahl,
  T_Zahl_der_Anwahlen,
  T_FAxnummer_des_Adressaten,
  T_Titel_des_Adressaten,
  T_PID_falls_aus_Dateinamen_ermittelt,
  T_Kurzbezeichnung_der_eigenen_Faxstelle,
  T_Geraetename,
  T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax,
  T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax,
  T_identisch_zu_submid_nur_MSFax,
  T_Prioritaet_nur_MSFax,
  T_FAxnummer_des_Adressaten_nur_MSFax,
  T_Faxnummer_des_Senders_nur_MSFax,
  T_Beginn_der_Uebertragung_nur_MSFax,
  T_Archiv_fuer_die_erfolgreichen_Faxe,
  T_Archiv_fuer_die_gescheiterten_Faxe,
  T_Welches_Fax_soll_geloescht_werden,
  T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch,
  T_wirklich_geloescht_werden,
  T_Kein_Fax_zum_Loeschen_vorhanden,
  T_Keine_ISDN_Karte_gefunden,
  T_mitCapi,
  T_auf,
  T_verwendet_Kofigurationsdatei_string_anstatt,
  T_faxt_die_Dateien_aus_pfad_anstatt,
  T_Dateien_warten_in_pfad_anstatt,
  T_Empfangsverzeichnis_fuer_Faxempfang,
  T_Capisuite_nicht_verwenden,
  T_hylafax_nicht_verwenden,
  T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken,
  T_versuche_faxe_zuerst_ueber_hylafax_wegzuschicken,
  //  T_sucht_nach_dev_tty_string_als_Modem_mit_string_anstatt,
  T_nach_zahl_Versuchen_Capisuite_wird_Hylafax_versucht,
  T_nach_zahl_Versuchen_Hylafax_wird_Capisuite_verwendet,
  T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt,
  T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt,
  T_verwendet_fuer_Capisuite_den_Linux_Benutzer_string_anstatt,
  T_FAxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,
  T_faxnr_wird_hinter_string_erwartet_statt_hinter,
  T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter,
  T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter,
  T_Adressatenname_wird_hinter_string_erwartet_statt_hinter,
  T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt,
  T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,
  T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,
  T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string_anstatt,
  T_verwendet_die_Datenbank_string_anstatt,
  T_protokolliert_ausfuehrlich_in_Datei,
  T_sonst_knapper,
  T_waehlt_als_Logverzeichnis_pfad_derzeit,
  T_logdatei_string_im_Pfad,
  T_wird_verwendet_anstatt,
  T_logdatei_vorher_loeschen,
  T_Bildschirmausgabe_gespraechiger,
  T_Bildschirmausgabe_mit_SQL_Befehlen,
  T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte,
  T_ein_Fax_nach_Rueckfrage_loeschen,
  T_Eintraege_aus,
  T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist,
  T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus,
  T_loeschen,
  T_Dateien_aus_Warteverzeichnis_gegen,
  T_pruefen_und_verschieben,
  T_listet_Datensaetze_aus,
  T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
  T_Zeigt_diesen_Bildschirm_an,
  T_Fertig_mit_Parsen_der_Befehlszeile,
  T_Gebrauch,
  T_Faxt_Dateien_aus_Verzeichnis_pfad_die,
  T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie,
  T_Tabellen,
  T_aein,
  T_Verzeichnis_mit_zu_faxenden_Dateien,
  T_Verzeichnis_mit_wartenden_Dateien,
  T_Verzeichnis_mit_gescheiterten_Dateien,
  T_Verzeichnis_fuer_empfangene_Faxe,
  T_Buchstabenfolge_vor_erster_Faxnummer,
  T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Capisuite,
  T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Hylafax,
  T_Buchstabenfolge_vor_erstem_Adressaten,
  T_Buchstabenfolge_vor_weiterem_Adressaten_sowie_weiterer_Faxnummer,
  T_Host_fuer_MySQL_MariaDB_Datenbank,
  T_Benutzer_fuer_MySQL_MariaDB,
  T_Passwort_fuer_MySQL_MariaDB,
  T_Datenbankname_fuer_MySQL_MariaDB_auf,
  T_Logverzeichnis,
  T_Logdateiname,
  T_Zahl_der_SQL_Befehle_fuer_Namenszuordnung,
  T_SQL_Befehl_Nr,
  T_Capisuite_ist_offenbar_noch_nicht_richtig_konfiguriert,
  T_ist_Apostroph,
  T_Die_Einstellungen_koennen_spaeter_in,
  T_geaendert_werden,
  T_Faxnr_die_zum_Adressaten_gesandt_wird_bis_20_Zeichen_nur_plus_und_Ziffern,
  T_ausgehende_Multiple_Subscriber_Number_Faxnummer_ohne_Vorwahl,
  T_Amtsholung_ueblicherweise_kk_oder_0,
  T_Faxueberschrift,
  T_Adressat_empfangener_Faxe_die_ueber_Email_verteilt_werden,
  T_Zahl_der_Sendeversuche,
  T_kommagetrennte_Liste_mit_Sekundenabstaenden_zwischen_Sendeversuchen,
  T_Geduld_bis_zum_Verbindungsaufbau_in_s,
  T_komma_wert,
  T_komma_Altwert,
  T_Programm,
  T_Muster,
  T_Ziel,
  T_Logpfad,
  T_oblog,
  T_Ende,
  T_Fax_von,
  T_an,
  T_vom,
  T_fuer_Benutzer,
  T_Alle_wieviel_Minuten_soll,
  T_aufgerufen_werden_0_ist_gar_nicht,
  T_Kann_Capisuite_nicht_installieren_verwende_Capi_nicht,
  T_wird_verwendet,
  T_mit_Baudrate,
  T_Fuer_Hylafax_verwendetes_Modem,
  T_archiviere,
  T_loeschecapi,
  T_loeschehyla,
  T_WVZinDatenbank,
  T_pruefmodem,
  T_setzhylavz,
  T_lieskonfein,
  T_rueckfragen,
  T_autokonfschreib,
  T_konfcapi,
  T_clieskonf,
  T_verzeichnisse,
  T_pruefcron,
  T_korrerfolgszeichen,
  T_bereinigewv,
  T_anhalten,
  T_loeschefax,
  T_loeschewaise,
  T_loescheallewartenden,
  T_tu_lista, 
  T_tu_listi, 
  T_DateienHerricht,
  T_faxealle,
  T_untersuchespool,
  T_zeigweitere,
  T_empfarch,
  T_schlussanzeige,
  T_zielname,
  T_PIDausName,
  T_pruefhyla,
  T_pruefrules,
  T_pruefblack,
  T_pruefmodcron,
  T_pruefcapi,
  T_inDbc,
  T_faxemitC,
  T_inDBh,
  T_faxemitH,
  T_prufespool,
  T_pruefouta,
  T_pruefinca,
  T_pruefprocgettel3,
  T_capiwausgeb,
  T_hylaausgeb,
  T_tuloeschen,
  T_Installation_von_Hylafax_nicht_feststellbar_versuche_es_zu_installieren,
  T_Hylafaxplus_entdeckt_muss_ich_loeschen,
  T_RueckmlgZeile,
  T_Hylafax_laeuft,
  T_Pruefe_ob_Hylafax_gestartet,
  T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen,
  T_in_der_Datenbanktabelle,
  T_wird_das_Erfolgszeichen_korrigiert,
  T_mit_Erfolgskennzeichen_auf,
  T_ohne_Erfolgskennzeichen_auf,
  T__auf,
  T_Zahl_der_empfangenen_Faxe,
  T_von,
  T_nicht_erkannt,
  T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm,
  T_Zahl_der_nicht_geloeschten_Dateien,
  T_hylanr,
  T_Capispooldatei,
  T_Gesamt,
  T_Verwende,
  T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen,
  T_Versuch,
  T_nicht_gefunden_kein_Datenbankeintrag,
  T_setzhylastat,
  T_empfangene_Dateien_loeschen_die_nicht_verarbeitet_werden_koennen,
  T_hylafehlt,
  T_capilaeuft,
  T_gefunden,
  T_Kein_Modem_gefunden,
  T_kein_Faxprogramm_verfuegbar,
  T_Capisuite_gestartet,
  T_schreibe_Konfiguration,
  T_Dateien,
  T_nicht_verarbeitbar_Verschiebe_sie_nach,
  T_Fuehre_aus_Dp,
  T_falls_es_hier_haengt_bitte_erneut_aufrufen,
  T_pruefsamba,
  T_Zufaxen,
  T_Warteauffax,
  T_Nichtgefaxt,
  T_Faxempfang,
  T_Gefaxt,
  T_zu_schreiben,
  T_Zahl_der_Verzeichnisse_fuer_erfolgreich_verschickte_Faxe,
  T_Verzeichnis,
  T_nicht_als_Sambafreigabe_gefunden_wird_ergaenzt,
  T_zufaxenvz,
  T_VorgbSpeziell,
  T_Wolle_Sie_noch_einen_SQL_Befehl_eingeben,
  T_Strich_ist_SQL_Befehl_loeschen_faxnr_wird_ersetzt_mit_der_Faxnr,
  T_faxnr_wird_ersetzt_mit_der_Faxnr,
  T_Datenbank,
  T_nicht_ermittelbar_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
  T_In,
  T_keine_Datenbank_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
  T_koennte_ein_SQL_Fehler_sein_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
  T_keinmal_faxnr_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
  T_beim_letzten_nichts_eingeben,
  T_Muss_Hylafax_installieren,
  T_pruefstdfaxnr,
  T_Letzte,
  T_empfangene_Faxe,
  T_erfolgreich,
  T_erfolglos,
  T_versandten_Faxe,
  T_aus_systemd_fax_service_Datei_ermittelt,
  T_aus_etc_init_d_hylafax_ermittelt,
  T_aus_seiner_ausschliesslichen_Existenz_ermittelt,
  T_aus_seinem_geringen_Alter_ermittelt,
  T_aus_mangelnder_Alternative_ermittelt,
  T_aus_Existenz_von,
  T_ermittelt,
  T_hylafax_Verzeichnis,
  T_Bezeichnung_des_Anrufers,
  T_Password_fuer_samba_fuer_Benutzer,
  T_Zeigt_die_Programmversion_an,
  T_Freie_Software,
  T_Verfasser,
  T_Letzte_Programmaenderung,
  T_Kompiliert,
  T_Quelle,
  T_Hilfe,
  T_Capisuite_verwenden,
  T_hylafax_verwenden,
  T_pruefcvz,
  T_Konfigurationsdatei_editieren,
  T_zufaxen,
  T_warteauffax,
  T_nichtgefaxt,
  T_empfvz,
  T_MeiEinrichtung,
  T_Mei_FaxUeberschrift,
  T_an_Fax,
  T_an_cFax,
  T_an_hFax,
  T_und,
  T_erneute_Eingabe,
  T_liescapiconf,
  T_Fehler_beim_Loeschen,
  T_VorgbAllg,
  T_pruefisdn,
  T_keine_Rueckfragen_zB_aus_Cron,
  T_Samba_muesste_installiert_werden_soll_ich,
  T_Sollen_fehlende_Sambafreigaben_fuer_die_angegebenen_Verzeichnisse_ergaenzt_werden,
  T_Soll_die_SuSEfirewall_bearbeitet_werden,
  T_aktuelle_Einstellungen_aus,
  T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,
  T_Muss_falsches_hylafax_loeschen,
  T_autofax_anhalten,
  T_MAX
};


const string sprachstr=string("language/Sprache/Lingue/Lingua [")+blau+'d'+schwarz+"eutsch,"+blau+'e'+schwarz+"nglisch]"+"";
const char* sprachcstr=&sprachstr.front();

char const *Txautofaxcl::TextC[T_MAX+1][Smax]={
  // T_sprachstr
  {sprachcstr,sprachcstr},
  // T_j_af,
  {"j","y"},
  // T_verarbeitete_Nicht_PDF_Dateien
  {"' verarbeitete Nicht-PDF-Dateien: ","' processed Non-PDF-Files: "},
  // T_verarbeitete_PDF_Dateien
  {"' verarbeitete       PDF-Dateien: ","' processed     PDF-Files: "},
  // T_Soll_die_Capisuite_verwendet_werden
  {"Soll die Capisuite verwendet werden","Shall Capisuite be used"},
  // T_Soll_Hylafax_verwendet_werden
  {"Soll hylafax verwendet werden","Shall hylafax be uses"},
  // T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden
  {"Soll vorrangig die Capisuite statt hylafax gewaehlt werden","Shall capisuite instead of hylafax bei chosen preferentially"},
  // T_Zahl_der_Versuche_in_Capisuite_bis_hylafax_eingeschaltet_wird
  {"Zahl der Versuche in Capisuite, bis hylafax eingeschaltet wird","Number of tries in Capisuite, until hylafax is started"},
  // T_Zahl_der_Versuche_in_hylafax_bis_Capisuite_eingeschaltet_wird
  {"Zahl der Versuche in hylafax, bis Capisuite eingeschaltet wird","Number of tries in hylafax, until Capisuite is started"},
  // T_Linux_Benutzer_fuer_Capisuite
  {"Linux-Benutzer fuer Capisuite","Linux user for Capisuite"},
  // T_Hylafax_eigene_Landesvorwahl_ohne_plus_oder_00
  {"Hylafax: eigene Landesvorwahl ohne '+' oder '00'","hylafax: own international prefix without '+' or '00'"},
  // T_Hylafax_eigene_Ortsvorwahl_ohne_0
  {"Hylafax: eigene Ortsvorwahl ohne '0'","hylafax: own long distance prefix without '0'"},
  // T_Hylafax_und_Capisuite_eigene_MSN_Faxnummer_ohne_Vorwahl
  {"Hylafax und Capisuite: eigene MSN (Faxnummer ohne Vorwahl)","hylafax and capisuite: own MSN (fax number without prefix)"},
  // T_Hylafax_Praefix_fuer_ausserorts_zB_0
  {"Hylafax: Praefix fuer ausserorts (z.B. '0')","hylafax: prefix for long distance (e.g. '0')"},
  // T_Hylafax_Praefix_fuer_das_Ausland_zB_00
  {"Hylafax: Praefix fuer das Ausland (z.B. '00')","hylafax: prefix for abroad (e.g. '00')"},
  // T_Hylafax_bis_10_Buchstabe_fuer_eigenen_Namen
  {"Hylafax: bis 10 Buchstaben fuer eigenen Namen","hylafax: up to 10 letters for own name"},
  // T_Capisuite_bis_20_Buchstaben_fuer_eigenen_Namen
  {"Capisuite: bis 20 Buchstaben fuer eigenen Namen","Capisuite: up to 20 letters for own name"},
  // T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt
  {"Zahl der Klingeltoene, bis Capisuite den Anruf annimmt","Number of ring bells, until capisuite accepts call"},
  // T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt
  {"Zahl der Klingeltoene, bis Hylafax den Anruf annimmt","Number of ring bells, until hylafax accepts call"},
  // T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden
  {"Sollen die Dateien unabhaengig vom Faxerfolg im Zielverzeichnis gespeichert werden",
    "Shall files be stored in target directory irrespective of fax success"},
  // T_wartend
  {"wartend","waiting"},
  // T_gesandt
  {"gesandt","sent"},
  // T_gescheitert
  {"gescheitert","failed"},
  // T_nicht_in_der_Warteschlange
  {"nicht in der Warteschlage","not in queue"},
  // T_woasined
  {"unbekannt","unknown"},
  // T_Der_regulaere_Ausdruck
  {"Der regulaere Ausdruck '","The regular expression '"},
  // T_konnte_nicht_kompiliert_werden
  {"' konnte nicht kompiliert werden.","could not be compiled."},
  // Verbindung_zur_Datenbank_nicht_herstellbar
  {"Verbindung zur Datenbank nicht herstellbar, fehnr: ","Connection to the database could not be established, errnr: "},
  // T_Breche_ab
  {". Breche ab.","Stopping."},
  // T_Konnte_Verzeichnis
  {"Konnte Verzeichnis ","Could not open the directory"},
  // T_nicht_oeffnen
  {" nicht oeffnen",""},
  // T_zielname_erstes_Ziel
  {" zielname:  erstes Ziel: '"," target name:  first target: '"},
  // T_zielname_Ausweichziel
  {" zielname: Ausweichziel: '"," target name:  alternate target: '"},
  // T_Datei
  {"Datei: '","File: '"},
  // T_entspricht
  {"' entspricht "," "},
  // T_entsprichtnicht
  {"nicht ","does not match to "},
  // T_entsprichtdoch
  {"","matches to "},
  // T_Muster_Doppelpunkt
  {"Muster: '","pattern: '"},
  // T_Verschiebe
  {"Verschiebe: '","Moving: '"},
  // T_Fehler_beim_Verschieben
  {"Fehler beim Verschieben","Error while moving"},
  // T_Kopiere_Doppelpunkt
  {"Kopiere: '","Copying: "},
  // T_Fehler_beim_Kopieren
  {"Fehler beim Kopieren: ","Error while copying: "},
  // T_Dateiname,
  {"Dateiname ","File name "},
  // T_schlechtgeformt
  {" schlecht geformt!","malformed!"},
  // T_Fehler_af,
  {"Fehler ","Errror "},
  // T_bei
  {" bei: "," at: "},
  // T_ja
  {"ja","yes"},
  // T_nein
  {"nein","no"},
  // T_obcapimitDoppelpunkt,
  {"mitCapi: ","withCapi: "},
  // T_obhylamitDoppelpunkt
  {"mitHyla: ","with hyla: "},
  // T_Endung
  {"Endung: ","Ending: "},
  // T_Stamm
  {"Stamm:  ","Root: "},
  // T_trennenach
  {"trenne nach: '","separating by: '"},
  // T_ErstelledurchKopieren
  {"Erstelle durch Kopieren: ","Providing by copying: "},
  // T_FehlerbeimUmbenennen
  {"Fehler beim Umbenennen!","Error while renaming!"},
  // T_ErstelledurchBenennen
  {"Erstelle durch Benennen: ","Providing by naming: "},
  // T_abgebrochen
  {"abgebrochen! ","aborted! "},
  // T_FehlerbeimUmbenennenbei
  {" Fehler beim Umbenennen bei:"," Error while renaming:"},
  // T_aus
  {"aus '","in '"},
  // T_nichtbeschreibbar
  {" nicht beschreibbar!","not to open for writing!"},
  // T_KeinModemmitNamensmuster
  {"Kein Modem mit Namensmuster '","No modem found with name pattern '"},
  // T_gefundenverwendeHylafaxnicht
  {"' gefunden, verwende Hylafax nicht.",", not utilizing hylafax."},
  // T_Baudratevon
  {"Baudrate von '","Baud rate of '"},
  // T_mit_af
  {"' mit ","' with "},
  // T_zugeringVerwendeHylafaxnicht
  {" zu gering. Verwende Hylafax nicht."," too small. Not utilizing hylafax."},
  // T_hylafax_faxmodem_nicht_gefunden_Versuche_es_zu_installieren_mit
  {"hylafax (faxmodem) nicht gefunden. Versuche es zu installieren mit","hylafax (fax modem) not found. Trying to install it with"},
  // T_StarteHylafax
  {"Starte Hylafax ...","Starting hylafax ..."},
  // T_hylafaxspringtnichtan
  {"hylafax.service springt nicht an. Verwende Hylafax nicht.","hylafax.service does not start up. Not utilizing hylafax."},
  // T_haengean
  {"haenge an ","appending to "},
  // T_an_mdpp
  {" an: ",": "},
  // T_KannFcpciNInstVerwCapiNicht
  {"Kann Fritz-Modul fcpci nicht installieren, verwende capi nicht.","Cannot install module fcpci for the fritz card, not utilizing capi."},
  // T_Kernelversion
  {"Kernelversion: ","Kernel version: "},
  // T_nichtgefFcpciMfdKinstallierwerden
  {"' nicht gefunden, fcpci muss fuer diesen Kernel installiert werden, versuche es:",
    "' not found, fcpci must be installed for this kernel, trying to:"},
  // T_Konnte
  {"Konnte '","Could not start '"},
  // T_nichtstarten
  {"' nicht starten",""},
  // T_VersucheDatei
  {"Versuche Datei: '","Trying to install file: '"},
  // T_zuinstallieren
  {"' zu installieren",""},
  // T_bittestellenSiedieInstallationsdatei
  {"Bitte stellen Sie die Installationsdatei '","Please provide the installation file '"},
  // T_bereitevtlvonfkn
  {"' bereit, evtl. von www.fkn-systems.de!",", possibly from www.fkn-systems.de!"},
  // T_StarteCapisuite
  {"Starte Capisuite ...","Starting Capisuite ..."},
  // T_Umwandlungvon
  {"Umwandlung von ","Conversion of "},
  // T_inPDFmit
  {" in PDF mit "," to PDF using "},
  // T_beendetErgebnis
  {" beendet, Ergebnis: "," finished, result: "},
  // T_misserfolg
  {"Misserfolg","failure"},
  // T_Erfolg_af
  {"Erfolg","success"},
  // T_lstatfehlgeschlagen
  {"lstat fehlgeschlagen: ","lstat failed: "},
  // T_beiDatei
  {" bei Datei:"," at file: "},
  // T_konntecapisuiteservice
  {"Konnte capisuite.service ","Could not start capisuite.service "},
  // T_malnichtstartenverwN
  {" mal nicht starten, verwende es nicht."," times, not utilizing it."},
  // T_SpoolDateierstellt
  {"Spool-Datei erstellt: '","Generated spool file: '"},
  // T_SpoolDatei
  {" Spool-Datei: '","Spool file: '"},
  // T_SpoolPfad
  {" Spool-Pfad: '"," Spool directory: '"},
  // T_DieFaxnrausTabelle
  {"Die Faxnr aus Tabelle `","The fax number from table `"},
  // T_istleerfaxeesdahernicht
  {" ist leer! Faxe es dahaer nicht."," is empty! Not faxing it therefore."},
  // T_DieFaxnrvon
  {"Die Faxnr von ","The fax number of "},
  // T_ist
  {" ist: "," is: "},
  // T_faxemitCFehler
  {"faxemitC() Fehler: ","faxemitC() Error: "},
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
  // T_KeinErgebnisbeimFaxen
  {"Kein Ergebnis beim Faxen!","Faxing with no result!"},
  // T_HylafaxBefehl
  {"Hylafax-Befehl","Hylafax command"},
  // T_Anwahlen
  {" Anwahlen, "," tries, "},
  // T_kommaDatei
  {", Datei: ",", file: "},
  // T_Status
  {" Status: "," State: "},
  // T_bzw
  {", bzw.: ",", and: "},
  // T_Falschals
  {"Falsch als ","Wrongly archived as "},
  // T_eingeordnet
  {" eingeordnet: ",": "},
  // T_DateienzahlimVz
  {"Dateienzahl im Vz: ","No. of files in directory: "},
  // T_ZahldDSmwegzuschickendenFaxenin
  {"Zahl der Datensaetze mit wegzuschickenden Faxen in `","No. of data records with enqueued faxes in `"},
  // T_PDFDatei
  {" PDF-Datei: "," PDF file: "},
  // T_beiSQLAbfrage
  {" bei SQL-Abfrage: "," at SQL request: "},
  // T_obgescheitert
  {" obgescheitert: "," failed?: "},
  // T_Fehler_beim_Verschieben_Ausrufezeichen
  {"Fehler beim Verschieben!","Error while moving!"},
  // T_0Bytes
  {"0 Bytes: '","0 bytes: '"},
  // T_Loesche_Ausrufezeichen
  {"Loesche: ","Deleting: "},
  // T_nicht_geloescht_war_eh_nicht_mehr_da
  {" nicht geloescht, war eh nicht mehr da."," not deleted, was no more there."},
  // T_Verwaiste_Datei
  {"Verwaiste Datei: ","Orphaned file: "},
  // T_geloescht_Fax_schon_in
  {" geloescht (Fax schon in "," deleted (fax already archived in "},
  // T_archiviert_Ausrufezeichen
  {" archiviert)!","!"},
  // T_Weitere_Spool_Eintraege
  {"Weitere Spool-Eintraege:","Further spool entries:"},
  // T_Zeit_Doppelpunkt
  {"Zeit: ","Time: "},
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
  // T_Fertig_mit
  {"Fertig mit ","Ready with "},
  // T_Fehler_beim_Datumsetzen_von
  {"Fehler beim Datumsetzen von '","Error setting date of '"},
  // T_eindeutige_Identifikation
  {"eindeutige Identifikation","distinct identification"},
  // T_Originalname_der_Datei
  {"Originalname der Datei","original name of the file"},
  // T_Originalname_der_Datei_vor_Umwandlung_in_PDF
  {"Originalname der Datei vor Umwandlung in PDF","original name of the file before converting to pdf"},
  // T_zu_senden_an
  {"zu senden an","to be sent to"},
  // T_Prioritaet_aus_Dateinamen
  {"Prioritaet aus Dateinamen: 0=keine, 1=capi, 2=hyla","Priority from file name: 0=none, 1=capi, 2=hyla"},
  // T_Zahl_der_bisherigen_Versuche_in_Capisuite
  {"Zahl der bisherigen Versuche in Capisuite","No. of previous tries in Capisuite"},
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
  {"state-Feld in hylafax","state field in hylafax"},
  // T_statuscode_in_letztem_gescheitertem_hylafax
  {"statuscode in letztem gescheitertem hylafax","status code of the last failed hylafax"},
  // T_status_in_letztem_gescheitertem_hylafax
  {"status in letztem gescheitertem hylafax","status of the last failed hylafax"},
  // T_capispooldateien_der_Capisuite
  {"capiSpooldateien der Capisuite","capi spool files of capisuite"},
  // T_Fehler_beim_Pruefen_von
  {"Fehler beim Pruefen von: ","Error while examining: "},
  // T_Name_des_Adressaten
  {"Name des Adressaten","Name of the receiver"},
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
  // T_FAxnummer_des_Adressaten
  {"Faxnummer des Adressaten","receiver's fax no"},
  // T_Titel_des_Adressaten
  {"Titel des Adressaten","receiver's fax no"},
  // T_PID_falls_aus_Dateinamen_ermittelt
  {"PID, falls aus Dateinamen ermittelt","PID, if excerpted from file name"},
  // T_Kurzbezeichnung_der_eigenen_Faxstelle
  {"Kurzbezeichnung der eigenen Faxstelle","short name of the own fax location"},
  // T_Geraetename
  {"Geraetename","device name"},
  // T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax
  {"outgoing schedule time oder so aehnlich (nur MS Fax)","outgoing schedule time or similar (only ms fax)"},
  // T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax
  {"Hinweis auf Dateiinhalt oder Adressat (nur MS Fax)","indication of file content or adressat (only ms fax)"},
  // T_identisch_zu_submid_nur_MSFax
  {"identisch zu submid (nur MS Fax)","identical to submid (only ms fax)"},
  // T_Prioritaet_nur_MSFax
  {"Prioritaet (nur MS Fax)","priority (only ms fax)"},
  // T_FAxnummer_des_Adressaten_nur_MSFax
  {"Faxnummer des Adressaten (nur MS Fax)","receiver's fax no. (only ms fax)"},
  // T_Faxnummer_des_Senders_nur_MSFax
  {"Faxnummer des Senders (nur MS Fax)","sender's fax no. (only ms fax)"},
  // T_Beginn_der_Uebertragung_nur_MSFax
  {"Beginn der Uebertragung (nur MS Fax)","transmission begin (only ms fax)"},
  // T_Archiv_fuer_die_erfolgreichen_Faxe
  {"Archiv fuer die erfolgreichen Faxe","archive for successful faxes"},
  // T_Archiv_fuer_die_gescheiterten_Faxe
  {"Archiv fuer die gescheiterte Faxe","archive for failed faxes"},
  // T_Welches_Fax_soll_geloescht_werden
  {"Welches Fax soll geloescht werden (0=Abbruch)","Which fax shall be deleted (0=Cancel)"},
  // T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch
  {"Soll das Fax ","Shall the fax "},
  // T_wirklich_geloescht_werden
  {" wirklich geloescht werden"," really be deleted"},
  // T_Kein_Fax_zum_Loeschen_vorhanden
  {"Kein Fax zum Loeschen vorhanden","No fax there to be deleted"},
  // T_Keine_ISDN_Karte_gefunden
  {"Keine ISDN-Karte gefunden. Setze ","No ISDN-Card found. Setting "},
  // T_mitCapi
  {"mitCapi","withCapi"},
  // T_auf
  {" auf "," to "},
  // T_verwendet_Kofigurationsdatei_string_anstatt
  {"verwendet Konfigurationsdatei <string> anstatt","uses configuration file <string> instead of"},
  // T_faxt_die_Dateien_aus_pfad_anstatt
  {"faxt die Dateien aus <pfad> anstatt","faxes the files from <path> instead of"},
  // T_Dateien_warten_in_pfad_anstatt
  {"Dateien warten in <pfad> anstatt","files are waiting in <path> instead of"},
  // T_Empfangsverzeichnis_fuer_Faxempfang
  {"Empfangsverzeichnis fuer Faxempfang","directory for recieved faxes"},
  // T_Capisuite_nicht_verwenden
  {"capisuite nicht verwenden","do not use capisuite"},
  // T_hylafax_nicht_verwenden
  {"hylafax nicht verwenden","do not use hylafax"},
  // T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken
  {"versuche faxe zuerst ueber Capisuite wegzuschicken","try to send faxes primarily via capisuite"},
  // T_versuche_faxe_zuerst_ueber_hylafax_wegzuschicken
  {"versuche faxe zuerst ueber hylafax wegzuschicken","try to send faxes primarily via hylafax"},
  //      // T_sucht_nach_dev_tty_string_als_Modem_mit_string_anstatt
  //      {"suche nach '/dev/tty<string>*' als Modem, mit <string> anstatt","search for '/dev/tty<string>*' as modem, with <string> instead of"},
  // T_nach_zahl_Versuchen_Capisuite_wird_Hylafax_versucht
  {"nach <zahl> Versuchen Capisuite wird Hylafax versucht, anstatt nach","try Hylafax after <no> tries of Capisuite instead of"}, 
  // T_nach_zahl_Versuchen_Hylafax_wird_Capisuite_verwendet
  {"nach <zahl> Versuchen Hylafax wird Capisuite versucht, anstatt nach","try Capisuite after <no> tries of Hylafax instead of"},
  // T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt
  {"Zahl der Klingeltoene, bis Capisuite den Anruf annimmt, anstatt","No. of bell rings until Capisuite accepts the call, instead of"},
  // T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt
  {"Zahl der Klingeltoene, bis Hylafax den Anruf annimmt, anstatt","No. of bell rings until hylafaxs accepts the call, instead of"},
  // T_verwendet_fuer_Capisuite_den_Linux_Benutzer_string_anstatt
  {"verwendet fuer Capisuite den Linux-Benutzer <string> anstatt","takes the linux user <string> for Capisuite instead of"},
  // T_FAxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert
  {"Faxe werden auch ohne Faxerfolg ins Zielverzeichnis kopiert","copy faxes into target directory irrespective of faxing success"},
  // T_faxnr_wird_hinter_string_erwartet_statt_hinter
  {"faxnr wird hinter <string> erwartet statt hinter","the fax number will be expected after <string> instead of"},
  // T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter
  {"faxnr fuer primaer Capisuite wird hinter <string> erwartet statt hinter",
    "fax no.for fax with preference to capisuite is expected after <string> instead of"},
  // T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter
  {"faxnr fuer primaer hylafax wird hinter <string> erwartet statt hinter",
    "fax no.for fax with preference to hylafax is expected after <string> instead of"},
  // T_Adressatenname_wird_hinter_string_erwartet_statt_hinter
  {"Adressatenname wird hinter <string> erwartet statt hinter","name of addressee is expected after <string> instead of"},
  // T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt
  {"Trennstring <string> fuer mehrere Adressaten/Telefonnummern statt",
    "separating string <string> for multiple addressees/tel'numbers, instead of"},
  // T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf
  {"verwendet die Datenbank auf Host <string> anstatt auf","takes the database on host <string> instead of"},
  // T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt
  {"verwendet fuer MySQL/MariaDB den Benutzer <string> anstatt","takes the user <string> for MySQL/MariaDB instead of"},
  // T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string_anstatt
  {"verwendet fuer MySQL/MariaDB das Passwort <string> anstatt","takes the password <string> for MySQL/MariaDB instead of"},
  // T_verwendet_die_Datenbank_string_anstatt
  {"verwendet die Datenbank <string> anstatt","uses the database <string> instead of"},
  // T_protokolliert_ausfuehrlich_in_Datei
  {"protokolliert ausfuehrlich in Datei '","put detailed logs in file '"},
  // T_sonst_knapper
  {"' (sonst knapper)","' (otherwise shorter)"},
  // T_waehlt_als_Logverzeichnis_pfad_derzeit
  {"waehlt als Logverzeichnis <pfad>, derzeit","choses <path> as log directory, currently"},
  // T_logdatei_string_im_Pfad
  {"logdatei <string> (im Pfad '","log file <string> (in path '"},
  // T_wird_verwendet_anstatt
  {"') wird verwendet anstatt","') will be used instead of"},
  // T_logdatei_vorher_loeschen
  {"logdatei vorher loeschen","delete log file afore"},
  // T_Bildschirmausgabe_gespraechiger
  {"Bildschirmausgabe gespraechiger","screen output more verbose"},
  // T_Bildschirmausgabe_mit_SQL_Befehlen
  {"Bildschirmausgabe mit SQL-Befehlen","screen output with SQL commands"},
  // T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte
  {"alle Parameter werden abgefragt (darunter einige hier nicht gezeigte)","all parameters will be prompted (some of them not shown here)"},
  // T_ein_Fax_nach_Rueckfrage_loeschen
  {"ein Fax nach Rueckfrage loeschen","delete a fax with query"},
  // T_Eintraege_aus
  {"Eintraege aus `","delete entries from `"},
  // T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist
  {"` loeschen, zu denen keine Datei im Wartevz.und kein Capi- oder Hylafax nachweisbar ist",
    "` without detection of file in waiting directory or capisuite fax or hyla-fax"},
  // T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus
  {"alle wartenden Faxe und zugehoerige Eintraege aus `","delete all waiting faxes and associated entries from `"},
  // T_loeschen
  {"` loeschen","`"},
  // T_Dateien_aus_Warteverzeichnis_gegen
  {"Dateien aus Warteverzeichnis gegen `","Examine files in waiting directory against the tables `"},
  // T_pruefen_und_verschieben
  {"` pruefen und ggf. verschieben","` and clean them up"},
  // T_listet_Datensaetze_aus
  {"listet Datensaetze aus `","lists entries from `"},
  // T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt
  {"Zahl der aufzulistenden Datensaetze = <zahl> statt","No. of listed entries = <zahl> instead of"},
  // T_Zeigt_diesen_Bildschirm_an
  {"Zeigt diesen Bildschirm an","shows this screen"},
  // T_Fertig_mit_Parsen_der_Befehlszeile
  {"Fertig mit Parsen der Befehlszeile","Parsing the command line finished"},
  // T_Gebrauch
  {"Gebrauch: ","Usage: "},
  // T_Faxt_Dateien_aus_Verzeichnis_pfad_die
  {"Faxt Dateien aus Verzeichns <pfad>, die '","Faxes files from directory <path>, which contain '"},
  // T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie
  {" <faxnr>' enthalten und durch soffice in pdf konvertierbar sind \nund traegt sie in MariaDB-Datenbank '",
    " <faxno>' and are convertible into pdf, \nand logs this in the the mariadb database '"}, 
  // T_Tabellen,
  {"' (Tabellen: `","' (tables: `"},
  // T_aein
  {"`) ein.","`)."},
  // T_Verzeichnis_mit_zu_faxenden_Dateien
  {"Verzeichnis mit zu faxenden Dateien","Directory with files to fax"},
  // T_Verzeichnis_mit_wartenden_Dateien
  {"Verzeichnis mit wartenden Dateien","Directory with waiting files"},
  // T_Verzeichnis_mit_gescheiterten_Dateien
  {"Verzeichnis mit gescheiterten Dateien","Directory with failed files"},
  // T_Verzeichnis_fuer_empfangene_Faxe
  {"Verzeichnis fuer empfangene Faxe","Directory for received faxes"},
  // T_Buchstabenfolge_vor_erster_Faxnummer
  {"Buchstabenfolge vor erster Fax-Nummer","Letter-sequence before the first fax number"},
  // T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Capisuite
  {"Buchstabenfolge vor erster Fax-Nummer primaer fuer Capisuite","Letter-sequence before the first fax number primarily for Capisuite"},
  // T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Hylafax
  {"Buchstabenfolge vor erster Fax-Nummer fuer Hylafax","Letter-sequence before the first fax number primarily for hylafax"},
  // T_Buchstabenfolge_vor_erstem_Adressaten
  {"Buchstabenfolge vor erstem Adressaten","Letter-sequence before the first addressee"},
  // T_Buchstabenfolge_vor_weiterem_Adressaten_sowie_weiterer_Faxnummer,
  {"Buchstabenfolge vor weiterem Adressaten sowie weiterer Faxnummer","Letter-sequence before further addressee or fax number"},
  // T_Host_fuer_MySQL_MariaDB_Datenbank
  {"Host fuer MySQL/MariaDB-Datenbank","host for mysql/mariadb-database"},
  // T_Benutzer_fuer_MySQL_MariaDB,
  {"Benutzer fuer MySQL/MariaDB:","user for mysql/mariadb:"},
  // T_Passwort_fuer_MySQL_MariaDB,
  {"Passwort fuer MySQL/MariaDB","password for mysql/mariadb"},
  // "Datenbankname fuer MySQL/MariaDB auf '"
  {"Datenbankname fuer MySQL/MariaDB auf '","database name for mysql/mariabd on '"},
  // T_Logverzeichnis
  {"Logverzeichnis","log directory"},
  // T_Logdateiname
  {"Logdateiname","log file name"},
  // T_Zahl_der_SQL_Befehle_fuer_Namenszuordnung
  {"Zahl der SQL-Befehle fuer Namenszuordnung:","No.of SQL-commands for assignment of fax names"},
  // T_SQL_Befehl_Nr,
  {"SQL-Befehl Nr. ","SQL command no. "},
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
  // T_Programm,
  {"Programm: ","Program: "},
  // T_Muster,
  {"Muster ","Pattern "},
  // T_Ziel,
  {"Ziel ","Target "},
  // T_Logpfad,
  {"Logpfad: '","Log path: '"},
  // T_oblog,
  {"' (oblog: ","' (with logging: "},
  // T_Ende,
  {"-Ende-","-End-"},
  // T_Fax_von
  {"Fax von ","Fax from "},
  // T_an,
  {" an "," to "},
  // T_vom
  {" vom "," at "},
  // T_fuer_Benutzer
  {" fuer Benutzer '"," for user '"},
  // T_Alle_wieviel_Minuten_soll
  {"alle wieviel Minuten soll ","every how many minutes shall "},
  // T_aufgerufen_werden_0_ist_gar_nicht]
  {" ueber crontab aufgerufen werden (0=gar nicht)", " be called in crontab (0=not at all)"},
  // T_Kann_Capisuite_nicht_installieren_verwende_Capi_nicht
  {"Kann Capisuite nicht installieren, verwende Capi nicht","Can't install capisuite, not using capi"},
  // T_wird_verwendet
  {" wird verwendet."," being used."},
  // T_mit_Baudrate,
  {"' mit Baudrate ","' with baud rate "},
  // T_Fuer_Hylafax_verwendetes_Modem
  {"Fuer Hylafax verwendetes Modem","Modem used for hylafax"},
  // T_archiviere
  {"archiviere()","archiving()"},
  // T_loeschecapi
  {"loeschecapi()","deletecapi()"},
  // T_loeschehyla
  {"loeschehyla()","deletehyla()"},
  // T_WVZinDatenbank
  {"WVZinDatenbank()","WDirinDatabase()"},
  // T_pruefmodem
  {"pruefmodem()","checkmodem()"},
  // T_setzhylavz
  {"setzhylavz()","sethyladir()"},
  // T_lieskonfein
  {"lieskonfein()","readconf()"},
  // T_rueckfragen
  {"rueckfragen()","callbacks()"},
  // T_autokonfschreib
  {"autokonfschreib()","autoconfwrite()"},
  // T_konfcapi
  {"konfcapi()","confcapi()"},
  // T_clieskonf
  {"clieskonf()","creadconf()"},
  // T_verzeichnisse
  {"verzeichnisse()","directories()"},
  // T_pruefcron
  {"pruefcron()","checkcron()"},
  // T_korrerfolgszeichen
  {"korrerfolgszeichen()","correctwrongsuccessflag()"},
  // T_bereinigewv
  {"bereinigewv()","purgewaitingdirectory()"},
  // T_anhalten
  {"anhalten()","stop()"},
  // T_loeschefax
  {"loeschefax()","deletefax()"},
  // T_loeschewaise,
  {"loeschewaise()","deleteorphans()"},
  // T_loescheallewartenden,
  {"loescheallewartenden()","deleteallwaiting()"},
  // T_tu_lista
  {"tu_lista()","do_listo()"},
  // T_tu_listi
  {"tu_listi()","do_listi()"},
  // T_DateienHerricht
  {"DateienHerricht()","PrepareFiles()"},
  // T_faxealle
  {"faxealle()","faxingall()"},
  // T_untersuchespool,
  {"untersuchespool()","examinespool()"},
  // T_zeigweitere
  {"zeigweitere()","showothers()"},
  // T_empfarch
  {"empfarch()","archiveReceived()"},
  // T_schlussanzeige
  {"schlussanzeige()","finaldisplay()"},
  // T_zielname
  {"zielname()","targetname()"},
  // T_PIDausName
  {"PIDAausName()","PIDfromName()"},
  // T_pruefhyla
  {"pruefhyla()","checkhyla()"},
  // T_pruefrules
  {"pruefrules()","checkrules()"},
  // T_pruefblack
  {"pruefblack()","checkblack()"},
  // T_pruefmodcron
  {"pruefmodcron()","checkmodcron()"},
  // T_pruefcapi,
  {"pruefcapi()","checkcapi()"},
  // T_inDbc
  {"inDbc()","intoDatabaseCapi()"},
  // T_faxemitC
  {"faxemitC()","faxingwithCapi()"},
  // T_inDBh
  {"inDBh()","intoDatabaseHyla()"},
  // T_faxemitH
  {"faxemitH()","faxingwithHyla()"},
  // T_prufespool
  {"pruefespool()","checkspool()"},
  // T_pruefouta
  {"pruefeouta()","checkouta()"},
  // T_pruefinca
  {"pruefinca()","checkinca()"},
  // T_pruefprocgettel3
  {"pruefprocgettel3()","checkprocgettel3()"},
  // T_capiwausgeb
  {"capiwausgeb()","displaycapitries()"},
  // T_hylaausgeb
  {"hylaausgeb()","displayhylatries()"},
  // T_tuloeschen
  {"tuloeschen()","dodelete()"},
  // T_Installation_von_Hylafax_nicht_feststellbar_versuche_es_zu_installieren
  {"Installation von Hylafax nicht feststellbar, versuche es zu installieren ...",
    "Installation of hylafax not statable, trying to install it ..."},
  // T_Hylafaxplus_entdeckt_muss_ich_loeschen
  {"Hylafax+ entdeckt, muss ich loeschen ...","Hylafax+ found, having to delete it ..."},
  // T_RueckmlgZeile
  {"Rueckmldg.Zeile: ","Response line: "},
  // T_Hylafax_laeuft
  {"Hylafax laeuft!","Hylafax is running!"},
  // T_Pruefe_ob_Hylafax_gestartet
  {"Pruefe, ob Hylafax gestartet ...","Checking if hylafax is running ..."},
  // T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen
  {"1=erfolgreiche Uebertragung, 0=fehlgeschlagen","1=successful transmission, 0=failure"},
  // T_in_der_Datenbanktabelle
  {"in der Datenbanktabelle `","in the database table `"},
  // T_wird_das_Erfolgszeichen_korrigiert
  {"` wird das Erfolgszeichen korrigiert","` the success flag is being corrected"},
  // T_mit_Erfolgskennzeichen_auf
  {"` mit Erfolgskennzeichen auf","` with success flag"},
  // T_ohne_Erfolgskennzeichen_auf
  {"` ohne Erfolgskennzeichen auf","` without success flag"},
  // T__auf
  {"` auf","`"},
  // T_Zahl_der_empfangenen_Faxe
  {"       Zahl der empfangenen Faxe: ","       Number of received faxes: "},
  // T_von
  {" von "," from "},
  // T_nicht_erkannt
  {" nicht erkannt!"," not identified!"},
  // T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm
  {"Fehlermeldung beim Loeschversuch eines Hyla-Faxes mit `faxrm ","Error while trying to delete a hyla-fax with `faxrm "},
  // T_Zahl_der_nicht_geloeschten_Dateien
  {"Zahl der nicht geloeschten Dateien: ","No. of not deleted files: "},
  // T_hylanr
  {", hylanr: ",", hylano.: "},
  // T_Capispooldatei
  {", Capispooldatei: ",", capispoolfile: "},
  // T_Gesamt
  {"Gesamt: ","Total: "},
  // T_Verwende
  {"Verwende: ","Using: "},
  // T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen
  {"Hylafax ohne + entdeckt, muss ich loeschen ...","hylafax without plus found, must delete it ..."},
  // T_Versuch
  {" Versuch: "," try no.: "},
  // T_nicht_gefunden_kein_Datenbankeintrag
  {"' nicht gefunden, kein Datenbankeintrag!"," not found, no database entry!"},
  // T_setzhylastat
  {"setzhylastat()","sethylastat()"},
  // T_empfangene_Dateien_loeschen_die_nicht_verarbeitet_werden_koennen
  {"empfangene Dateien loeschen, die nicht verarbeitet werden koennen","delete received files that could not be processed"},
  // T_hylafehlt
  {"hylafehlt: ","hylamissing: "},
  // T_capilaeuft
  {"capilaeuft: ","capirunning: "},
  // T_gefunden
  {" gefunden."," found."},
  // T_Kein_Modem_gefunden
  {"Kein Modem gefunden.","No modem found."},
  // T_kein_Faxprogramm_verfuegbar
  {"(kein Faxprogramm verfuegbar)","(no fax program available)"},
  // T_Capisuite_gestartet
  {"Capisuite gestartet.","capisuite started."},
  // T_schreibe_Konfiguration
  {"schreibe Konfiguration!","writing configuration!"},
  // T_Dateien
  {"Dateien ","Files "},
  // T_nicht_verarbeitbar_Verschiebe_sie_nach
  {" nicht verarbeitbar. Verschiebe sie nach "," not processable. Moving them to "},
  // T_Fuehre_aus_Dp
  {"Fuehre aus: ","Executing: "},
  // T_falls_es_hier_haengt_bitte_erneut_aufrufen
  {" (falls es hier haengt, bitte erneut aufrufen)"," (if it hangs, please invoke again)"},
  // T_pruefsamba
  {"pruefsamba()","checksamba()"},
  // T_Zufaxen
  {"Zufaxen","TobeFaxed"},
  // T_Warteauffax
  {"Warteauffax","WaitingFaxes"},
  // T_Nichtgefaxt
  {"Nichtgefaxt","NotFaxed"},
  // T_Faxempfang
  {"Faxempfang","FaxArrival"},
  // T_Gefaxt
  {"Gefaxt","Faxed"},
  // T_zu_schreiben
  {"zu schreiben: ","must write: "},
  // T_Zahl_der_Verzeichnisse_fuer_erfolgreich_verschickte_Faxe
  {"Zahl der Verzeichnisse fuer erfolgreich verschickte Faxe","No of directories for successfully sent faxes"},
  // T_Verzeichnis
  {"Verzeichnis '","Directory '"},
  // T_nicht_als_Sambafreigabe_gefunden_wird_ergaenzt
  {"' nicht als Sambafreigabe gefunden, wird ergaenzt.","' not found as or under a samba share, amending it."},
  // T_zufaxenvz
  {"zufaxenvz: '","outgoing dir: '"},
  // T_VorgbSpeziell
  {"VorgbSpeziell()","specificprefs()"},
  // "Wollen Sie noch einen SQL-Befehl eingeben?"
  {"Wollen Sie noch einen SQL-Befehl eingeben?","Do You want to enter another sql command?"},
  // T_Strich_ist_SQL_Befehl_loeschen_faxnr_wird_ersetzt_mit_der_Faxnr
  {" ('-'=SQL-Befehl loeschen,'&&faxnr&&' wird ersetzt mit der Faxnr)",
   " ('-'=delete this sql command,'&&faxnr&&' will be replaces with the fax-no.)"},
  // T_faxnr_wird_ersetzt_mit_der_Faxnr
  {" ('&&faxnr&&' wird ersetzt mit der Faxnr)",
   " ('&&faxnr&&' will be replaces with the fax-no.)"},
  // T_Datenbank
  {"Datenbank '","Database '"},
  // T_nicht_ermittelbar_Wollen_Sie_den_SQL_Befehl_neu_eingeben
  {"' nicht ermittelbar. Wollen Sie den SQL-Befehl neu eingeben?","' not found. Do You want to reenter the sql command?"},
  // T_In
  {"In '","In '"},
  // T_keine_Datenbank_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben
  {"' keine Datenbank gefunden. Wollen Sie den SQL-Befehl neu eingeben?",
   "' no database found. Do You want to reenter the sql command?"},
  // T_koennte_ein_SQL_Fehler_sein_Wollen_Sie_den_SQL_Befehl_neu_eingeben
  {"' koennte ein SQL-Fehler sein. Wollen Sie den SQL-Befehl neu eingeben?",
   "' could be an sql error. Do You want to reenter the sql command?"},
  // T_keinmal_faxnr_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben
  {"' keinmal '&&faxnr&&' gefunden. Wollen Sie den SQL-Befehl neu eingeben?",
   "' no occurance of '&&faxnr&&' found. Do You want to reenter the sql command?"},
  // T_beim_letzten_nichts_eingeben
  {" (beim letzten '-' eingeben)"," (for the last one enter '-')"},
  // T_Muss_Hylafax_installieren
  {"Muss Hylafax installieren","Have to install hylafax"},
  // T_pruefstdfaxnr
  {"pruefstdfaxnr()","checkstdfaxnr()"},
  // T_Letzte
  {"Letzte ","Last "},
  // T_empfangene_Faxe
  {" empfangene Faxe:"," received faxes:"},
  // T_erfolgreich
  {" erfolgreich"," successfully"},
  // T_erfolglos
  {" erfolglos"," unsuccessfully"},
  // T_versandten_Faxe
  {" versandten Faxe:"," sent faxes:"},
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
  // T_Bezeichnung_des_Anrufers
  {"Bezeichnung des Anrufers","Labelling of the caller"},
  // T_Password_fuer_samba_fuer_Benutzer
  {"Password fuer samba fuer Benutzer ","Password for samba for user "},
  // T_Zeigt_die_Programmversion_an
  {"Zeigt die Programmversion an","shows the program version"},
  // T_Freie_Software,
  {"Freie Software","Free Software"},
  // T_Verfasser
  {", Verfasser: ",", author: "},
  // T_Letzte_Programmaenderung
  {"Letzte Programmaenderung: ","Last modification: "},
  // T_Kompiliert
  {"Kompiliert: ","Compiled: "},
  // T_Quelle
  {"Quelle: ","Source: "},
  // T_Hilfe
  {"Hilfe: ","Help: "},
  // T_Capisuite_verwenden 
  {"Capisuite verwenden","use capisuite"},
  // T_hylafax_verwenden
  {"Hylafax verwenden","use hylafax"},
  // T_pruefcvz
  {"pruefcvz()","checkcdirs()"},
  // T_Konfigurationsdatei_editieren
  {"Konfigurationsdatei editieren","edit configuration file"},
  // T_zufaxen
  {"zufaxen","tofax"},
  // T_warteauffax,
  {"warteauffax","waitingfax"},
  // T_nichtgefaxt,
  {"nichtgefaxt","notfaxed"},
  // T_empfvz
  {"empfvz","recvdir"},
  // T_MeiEinrichtung
  {"MeiEinrichtung","MyInstitution"},
  // T_Mei_FaxUeberschrift
  {"Mei FaxUeberschrift","My fax headline"},
  // T_an_Fax
  {"an Fax","to fax"},
  // T_an_cFax,
  {"an cFax","to cfax"},
  // T_an_hFax
  {"an hFax","to hfax"},
  // T_und
  {"und","and"},
  // T_erneute_Eingabe
  {"erneute Eingabe","once more"},
  // T_liescapiconf
  {"liescapiconf()","readcapiconf()"},
  // T_Fehler_beim_Loeschen
  {"Fehler beim Loeschen","error deleting"},
  // T_VorgbAllg
  {"VorgbAllg()","generalprefs()"},
  // T_pruefisdn
  {"T_pruefisdn()","checkisdn()"},
  // T_keine_Rueckfragen_zB_aus_Cron
  {"keine Rueckfragen, z.B. aus cron","no questions, e.g. for cron"},
  // T_Samba_muesste_installiert_werden_soll_ich
  {"Samba muesste installiert werden, soll ich?","samba needs to be installed, shall I?"},
  // T_Sollen_fehlende_Sambafreigaben_fuer_die_angegebenen_Verzeichnisse_ergaenzt_werden
  {"Sollen fehlende Sambafreigaben fuer die angegebenen Verzeichnisse ergaenzt werden?",
    "Shall missing samba shares for the specified directories be added?"},
  // T_Soll_die_SuSEfirewall_bearbeitet_werden
  {"Soll die SuSEfirewall2 bearbeitet werden?","Shall the SuSEfirewall2 be edited?"},
  // T_aktuelle_Einstellungen_aus
  {"Aktuelle Einstellungen aus '","Current settings from '"},
  // T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in
  {"Gescheiterte Faxe werden hier gesammelt anstatt in","Failed Faxes are collected here and not in"}, 
  // T_Muss_falsches_hylafax_loeschen
  {"Muss falsches hylafax loeschen!!!","Have to delete the wrong hylafax!!!"},
  // T_autofax_anhalten
  {"autofax anhalten","stop autofax"},
  {"",""}
};


const string& pk = "8A490qdmjsaop4a89d0qÃ9m0943Ã09Ãax";
// const string& ccapiconfdat="/etc/capisuite/capisuite.conf";
// const string& cfaxconfdat="/etc/capisuite/fax.conf";


extern class lsyscl lsys;
extern class linstcl linst;

using namespace std;
const DBSTyp myDBS=MySQL;
string tmpc; // fuer crontab

#define autofaxcpp
#include "autofax.h"
constexpr const char *paramcl::moeglhvz[2];
// wird nur in VorgbSpeziell gebraucht:
zielmustercl::zielmustercl(const char * const vmuster,const char * const vziel):muster(vmuster),ziel(vziel)
{
 kompilier();
};  // zielmustercl

zielmustercl::zielmustercl(const char * const vmuster,const string& vziel):muster(vmuster),ziel(vziel)
{
 kompilier();
};  // zielmustercl


zielmustercl::zielmustercl() {
}

int zielmustercl::kompilier() {
  int reti=regcomp(&regex, muster.c_str(),REG_EXTENDED); 
  if (reti) {
    Log(string(Tx[T_Der_regulaere_Ausdruck])+drot+muster+schwarz+Tx[T_konnte_nicht_kompiliert_werden],1,0);
    return 1;
  }
  return 0;
} // zielmustercl::zielmustercl

int zielmustercl::setzemuster(const string& vmuster)
{
 muster=vmuster;
 return kompilier();
}
int zielmustercl::obmusterleer() {
 return muster.empty();
}

const string& zielmustercl::holmuster() {
 return muster;
}

// wird aufgerufen in: loeschefax, untersuchespool, capiwausgeb, setzhylastat, hylaausgeb
inline const char* FxStatS(FxStat *i) 
{
  enum FxStat:uchar {init,wartend,gesandt,gescheitert,fehlend,woasined};
  if (i) {
    switch (*i){
      case init: return "init";
      case wartend: return Tx[T_wartend];
      case gesandt: return Tx[T_gesandt];
      case gescheitert: return Tx[T_gescheitert];
      case fehlend: return Tx[T_nicht_in_der_Warteschlange];
      default:;
    }
  }
  return Tx[T_woasined];
} // FxStatS

//archiviert den Datensatz
// wird aufgerufen in: untersuchespool
void fsfcl::archiviere(DB *My, paramcl *pmp, struct stat *entryp, uchar obgescheitert, FaxTyp ftyp, uchar *geloeschtp, int obverb, int oblog)
{
  Log(violetts+Tx[T_archiviere]+schwarz+Tx[T_obgescheitert]+blau+ltoan((int)obgescheitert)+schwarz,obverb,oblog);
  // Voraussetzung: telnr, original, id; veraendert: geloescht
  static time_t jetzt = time(0);
  RS rins(My); 
  RS zs(My);
  string getname,bsname;
  getSender(pmp,telnr,&getname,&bsname);
  for(int runde=0;runde<2;runde++) {
    vector<instyp> einf;
    if (runde==0) zs.Abfrage("SET NAMES 'utf8'");
    else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
    einf.push_back(instyp(My->DBS,"titel",&bsname));
    einf.push_back(instyp(My->DBS,"rcname",&getname));
    if (capi) {if (cdd.empty()) cdd="0000-00-00";} else {if (hdd.empty()) hdd="0000-00-00";}
    einf.push_back(instyp(My->DBS,"submt",ftyp==capi?&cdd:&hdd));
    einf.push_back(instyp(My->DBS,"submid",ftyp==capi?&capisd:&hylanr));
    string pid;
    if (!original.empty()) {
      const char* ocstr=original.c_str(); // da c_str() fluechtig sein koennte
      char* pidp = (char*)strcasestr(ocstr,"pid ");
      if (pidp) {
        if (pidp==ocstr || (pidp>ocstr && (strchr(" .,;",*(pidp-1))))){
          for(pidp+=4;*pidp && *pidp!=' ';pidp++) {
            if (strchr("0123456789",*pidp)) pid+=*pidp;
          } 
        }
      }
    }
    if (pid.empty()) pid="0";
    einf.push_back(instyp(My->DBS,"pid",&pid));
    einf.push_back(instyp(My->DBS,"Erfolg",(int)!obgescheitert));
    einf.push_back(instyp(My->DBS,"docname",&original));
    Log(string("original (docname): ")+blau+original+schwarz,obverb,oblog);
    einf.push_back(instyp(My->DBS,"transe",&jetzt));
    if (!telnr.empty()) {
      string stdfax=pmp->stdfaxnr(telnr);
      einf.push_back(instyp(My->DBS,"rcfax",&stdfax));
    }
    if (!adressat.empty()) einf.push_back(instyp(My->DBS,"adressat",&adressat));

    einf.push_back(instyp(My->DBS,"fsize",entryp->st_size>4294967295?0:entryp->st_size)); // int(10)
    rins.insert(pmp->touta,einf, 1,0,ZDB?ZDB:!runde); 
    if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
    if (!rins.fnr) break;
    if (runde==1) {
      Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
      exit(0);
    }
  } // for(int runde=0;runde<2;runde++) 
  if (!rins.fnr) { 
    RS rsloe(My,string("DELETE FROM `")+pmp->spooltab+"` WHERE id = \""+id+"\"");
    *geloeschtp=1;
  } // if (!rins.fnr) 
} // archiviere

// wird aufgerufen in: loeschefax, untersuchespool
int fsfcl::loeschecapi(int obverb, int oblog)
{
  Log(violetts+Tx[T_loeschecapi]+schwarz,obverb,oblog);
  string stamm,exten;
  getstammext(&capisd,&stamm,&exten);
  int zdng=0; // Zahl der nicht Geloeschten
  if (!stamm.empty()) {
    for(uchar ru=0;ru<2;ru++) {
      string zuloe=cspf+vtz+stamm+(ru?".txt":".sff");
      zdng+=tuloeschen(zuloe,"",obverb,oblog);
    }
  } else {
    zdng=1;
  }
  return zdng;
} // void fsfcl::loeschecapi(int obverb, int oblog)

// Rueckgabe: Zahl der nicht geloeschten Eintraege
// wird aufgerufen in: loeschefax, untersuchespool
int fsfcl::loeschehyla(paramcl *pmp,int obverb, int oblog)
{
  Log(violetts+Tx[T_loeschehyla]+schwarz,obverb,oblog);
  if (hylanr!="0" && !hylanr.empty()) {
    svec rmerg;
    uchar vmax=5;
    svec findrueck;
    // wenn Datei nicht mehr in sendq, sondern in doneq, sei es gelungen oder gescheitert, dann ist loeschen sinnlos
    systemrueck(("sudo find '")+pmp->hsendqvz+"' -name q"+hylanr,obverb,oblog,&findrueck);
    if (!findrueck.size()) {
      return 0;
    }
    for(uchar iru=0;iru<vmax;iru++) {
      if (iru) {
        systemrueck(string("sudo systemctl restart '")+pmp->sfaxgetty->sname+"' '"+pmp->shfaxd->sname+"' '"+pmp->sfaxq->sname+"'",obverb-1,oblog);
      }
      systemrueck(string("sudo faxrm ")+hylanr+" 2>&1",obverb,oblog,&rmerg);
      if (rmerg.size()) {
        if (rmerg[0].find(" removed")!=string::npos || rmerg[0].find("job does not exist")!=string::npos) {
          return 0;
        }
        Log(rots+Tx[T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm]+hylanr+"`:\n    "+schwarz+rmerg[0],1,1);
      } // if (rmerg.size()) 
    } // for(uchar iru=0;iru<vmax;iru++) 
  } // if (hylanr!="0" && !hylanr.empty()) 
  return 1;
} // int fsfcl::loeschehyla(int obverb, int oblog)

paramcl::paramcl(int argc, char** argv)
{
  for(int i=1;i<argc;i++)
    if (argv[i][0])
      argcmv.push_back(argcl(i,argv)); 
  ich=argv[0];
  tstart=clock();
  cklingelzahl="1";
  hklingelzahl="2"; // muss mindestens 2 sein, um die Nr. des anrufenden zu uebertragen
  konfdatname.clear();
  scapisuite=new servc("","capisuite");
} // paramcl::paramcl()

paramcl::~paramcl()
{
  if (My) delete My;
  if (sfaxq) delete sfaxq;
  if (shfaxd) delete shfaxd;
  if (sfaxgetty) delete sfaxgetty;
  if (scapisuite) delete scapisuite;
} // paramcl::~paramcl()

// wird aufgerufen in: bereinigewv
string paramcl::getzielvz(const string& qdatei)
{
  for(zielmustercl *zmakt=zmp;1;zmakt++){
    if (!regexec(&(zmakt->regex),qdatei.c_str(),0,NULL,0))
      return zmakt->ziel;
    if (zmakt->obmusterleer()) break;
  }
  return "";
} // getzielvz

// passt einen Dateinamen gemaess der vorhandenen Dateien in allen moegenlichen Zielverzeichnissen so an
// dass er beim Umwandeln in PDF und Verschieben als erfolgreiches oder nicht erfolgreiches Fax sich nicht ueberschneidet
// wird aufgerufen in: DateienHerricht
string paramcl::neuerdateiname(const string& qpfad)
{
  string dateiname=qpfad, altdname, stamm, exten, extu;
  loeschealleaus(&dateiname,"'");
  loeschealleaus(&dateiname,"\"");
  for(unsigned runde=0;runde<2;runde++) {
    for(unsigned aru=0;1;aru++) {
      dateiname=base_name(dateiname);
      if (dateiname==altdname) break;
      altdname = dateiname;
      dateiname=zielname(dateiname,wvz,1,(string*)0,obverb,oblog);
      dateiname=zielname(dateiname,nvz,1,(string*)0,obverb,oblog);
      dateiname=zielname(dateiname,zmp,1,(string*)0,obverb,oblog);
    }
    getstammext(&dateiname,&stamm,&exten);
    if (!runde) extu=exten; 
    else break;
    string pdf=stamm+".pdf";
    if (pdf==dateiname) break;
    else dateiname=pdf;
  }
  return base_name(stamm+"."+extu);
} // neuerdateiname

// wird aufgerufen von DateienHerricht
// die frisch ins Warteverzeichnis verschobenen Dateien werden in spooltab eingetragen
void paramcl::WVZinDatenbank(vector<fxfcl> *fxvp)
{
  Log(violetts+Tx[T_WVZinDatenbank]+schwarz,obverb,oblog);
  RS rins(My); 
  RS zs(My);
  string spoolid="";
  for (unsigned nachrnr=0; nachrnr<fxvp->size(); ++nachrnr) {
    for(int runde=0;runde<2;runde++) {
      if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
      } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
      rins.clear();
      vector<instyp> einf; // fuer alle Datenbankeinfuegungen
      string odatei = base_name(fxvp->at(nachrnr).spdf);
      einf.push_back(instyp(My->DBS,"original",&odatei));
      // den Adressaten ermitteln
      size_t pn, pt, ptc, pth;
      pn=odatei.find(anstr);
      pt=odatei.find(anfaxstr);
      ptc=odatei.find(ancfaxstr);
      pth=odatei.find(anhfaxstr);
      if (ptc<pt) pt=ptc;
      if (pth<pt) pt=pth;
      if (pt!=string::npos && pn<pt-anstr.length()-1) { // mind. 1 Buchstaben sollte der Absender haben
       string subst=odatei.substr(pn+anstr.length(),pt-pn-anstr.length());
       einf.push_back(instyp(My->DBS,"adressat",&subst));
      }
      if (nachrnr<fxvp->size()) {
        string oudatei = base_name(fxvp->at(nachrnr).npdf);
        einf.push_back(instyp(My->DBS,"origvu",&oudatei));
      }
      einf.push_back(instyp(My->DBS,"prio",fxvp->at(nachrnr).prio));
      rins.insert(spooltab,einf, 1,0,ZDB?ZDB:!runde,&spoolid);
      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      if (spoolid!="null") break;
      if (runde==1) {
        Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
        exit(0);
      }
    }   // for(int runde=0;runde<2;runde++)
    Log(drots+string("  Spool-ID: ")+schwarz+spoolid,obverb,oblog);
  } // for (unsigned nachrnr=0; nachrnr<spdfp->size(); ++nachrnr) 
  for (uchar tr=0;tr<2;tr++) {
    char ***cerg;
    RS tellen(My,string("select max(length(gettel3(")+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"')))"
        " from `" +spooltab+"`");
    while (cerg=tellen.HolZeile(),cerg?*cerg:0) {
      if (*(*cerg+0))
        My->tuerweitern(spooltab,"telnr",atol(*(*cerg+0)),!obverb);
      break;
    }
    // hier wird die Telefonnummer aus dem Namen extrahiert
    RS tel(My,string("update `")+spooltab+"` "
        "set telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"') "
        "where isnull(telnr) or telnr=''",ZDB);
  }
} // WVZinDatenbank

// in lieskonfein, getcommandl0, getcommandline, rueckfragen
void paramcl::lgnzuw()
{
  if (langu=="d" || langu=="D" || langu=="deutsch" || langu=="Deutsch") {
    Txd.lgn=Txk.lgn=Tx.lgn=deutsch;
  } else if (langu=="e" || langu=="E" || langu=="english" || langu=="english" || langu=="English" || langu=="Englisch") {
    Txd.lgn=Txk.lgn=Tx.lgn=englisch;
  } else {
    Txd.lgn=Txk.lgn=Tx.lgn=deutsch;
  }
} // void paramcl::lgnzuw()


// wird aufgerufen in: main
void paramcl::logvorgaben(const string& vprog)
{
#ifdef _WIN32
  logvz = "C:\\Dokumente und Einstellungen\\All Users\\Anwendungsdaten";
#elif linux
  logvz = "/var/log";
#endif
  prog=base_name(vprog); // autofax
  instverz=string(getenv("HOME"))+'/'+prog;
  logdname = prog+".log";
  loggespfad=logvz+vtz+logdname;
  logdt=&loggespfad.front();
} // void paramcl::logvorgaben


// wird aufgerufen in: main
void paramcl::getcommandl0()
{
  Log(violetts+"getcommandl0()"+schwarz,obverb,oblog);
  // Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
  cgconf.init(36, "language","host","muser","mpwd","datenbank","sqlz","musterzahl",
    "obcapi","obhyla","hylazuerst","maxcapiv","maxhylav","cuser",
    "countrycode","citycode","msn","LongDistancePrefix","InternationalPrefix","LocalIdentifier",
    "cFaxUeberschrift","cklingelzahl","hmodem","hklingelzahl",
    "gleichziel","zufaxenvz","wartevz","nichtgefaxtvz","empfvz","anfaxstr","ancfaxstr","anhfaxstr",
    "anstr","undstr","cronminut","logvz","logdname");
  uchar plusverb=0;
  //  for(int i=argc-1;i>0;i--) KLA if (argv[i][0]==0) argc--; KLZ // damit fuer das Compilermakro auch im bash-script argc stimmt
  for(unsigned iru=0;iru<3;iru++) {
    switch (iru) {
      case 0:
        opts.push_back(optioncl("lg","language", &Tx,T_sprachstr,&langu,psons));
        opts.push_back(optioncl("langu","sprache", &Tx,-1,&langu,psons));
        opts.push_back(optioncl("lang","lingue", &Tx,-1,&langu,psons));
        break;
      case 1:
        opts.push_back(optioncl("v","verbose", &Tx, T_Bildschirmausgabe_gespraechiger,&plusverb,1));
        loggespfad=logvz+vtz+logdname;
        opts.push_back(optioncl("lvz","logvz", &Tx, T_waehlt_als_Logverzeichnis_pfad_derzeit,&logvz, pverz,&cgconf,"logvz",&logvneu));
        opts.push_back(optioncl("ld","logdname", &Tx, T_logdatei_string_im_Pfad, &logvz, T_wird_verwendet_anstatt, &logdname, psons,
           &cgconf,"logdname",&logdneu));
        opts.push_back(optioncl("l","log",&Tx, T_protokolliert_ausfuehrlich_in_Datei, &loggespfad, T_sonst_knapper, &oblog,1));
        opts.push_back(optioncl("ldn","logdateineu", &Tx, T_logdatei_vorher_loeschen, &logdateineu, 1));
        break;
      case 2:
        opts.push_back(optioncl("kd","konfdat", &Tx, T_verwendet_Kofigurationsdatei_string_anstatt,&konfdatname,pfile));
        break;
    }
    // hier wird die Befehlszeile ueberprueft:
    for(;optslsz<opts.size();optslsz++) {
      for(size_t i=0;i<argcmv.size();i++) {
        if (opts[optslsz].pruefp(&argcmv,&i,&hilfe)) {
          if (iru==1) {
            if (plusverb) {obverb++;plusverb=0;}
            if (!obcapi) hylazuerst=1; else if (!obhyla) hylazuerst=0;
          }
          if (opts[optslsz].kurz!="v") break;
        }
      }
    }
    optslsz=opts.size();
    if (!iru) lgnzuw();
  } // for(unsigned iru=0;iru<3;iru++)
  if (logvneu ||logdneu) {
    if (!logdname.empty()) {
      loggespfad=logvz+vtz+logdname;
      logdt=&loggespfad.front();
      // <<rot<<"logdt: "<<logdt<<endl;
      // <<rot<<"loggespfad: "<<loggespfad<<endl;
      //<<violett<<"logdname: "<<*cgconf.hole("logdname")<<schwarz<<endl;
    }
    obkschreib=1;
  } // if (logvneu ||logdneu) 
} // void paramcl::getcommandl0(int argc, char** argv)

// wird aufgerufen in: main
void paramcl::pruefmodem()
{
  Log(violetts+Tx[T_pruefmodem]+schwarz,obverb,oblog);
  svec rueck;
  // <<"pruefmodem 1 nach obcapi: "<<(int)obcapi<<endl;
  obmodem=0;
  cmd="find /sys/class/tty";
  systemrueck(cmd, obverb,oblog,&rueck);
  for(size_t i=0;i<rueck.size();i++) {
    struct stat entrydriv;
    if (!lstat(((rueck[i])+"/device/driver").c_str(),&entrydriv)) {
      string tty=base_name(rueck[i]);
      // ttyS0 erscheint auf Opensuse und Ubuntu konfiguriert, auch wenn kein Modem da ist
      if (tty!="ttyS0") {
        svec rue2;
        vector<errmsgcl> errv;
        string f0=schwarzs+"Modem "+blau+tty+schwarz+" gibts";
        string f1=f0+" nicht";
        errv.push_back(errmsgcl(0,f0));
        errv.push_back(errmsgcl(1,f1));
        if (!systemrueck("sudo stty -F /dev/"+tty+" >/dev/null 2>&1",obverb,oblog,&rue2,wahr,wahr,"",&errv)) {
          obmodem=1;
          modems<<tty;
          Log(string("Modem: ")+blau+Tx[T_gefunden],obverb,oblog);
        } // if (!systemrueck("sudo stty -F /dev/"+tty+" >/dev/null 2>&1",obverb,oblog,&rue2)) 
      } // if (tty!="ttyS0") 
    } // if (!lstat(((rueck[i])+"/device/driver").c_str(),&entrydriv)) 
  } // for(size_t i=0;i<rueck.size();i++) 
  obmdgeprueft=1;
  if (!obmodem) {
    obhyla=0;
    Log(rots+Tx[T_Kein_Modem_gefunden]+schwarz,obverb,oblog);
  }
  // wvdialconf oder schneller: setserial -a /dev/tty*, mit baud_base: <!=0>  als Kriterium
} // void paramcl::pruefmodem()

void paramcl::pruefisdn()
{
  Log(violetts+Tx[T_pruefisdn]+schwarz,obverb,oblog);
  svec rueck;
  cmd="lspci 2>/dev/null || sudo lspci 2>/dev/null | grep -i 'isdn'";
  logdt=&loggespfad.front();
  systemrueck(cmd, obverb,oblog,&rueck);
  // <<"pruefmodem 1 vor  obcapi: "<<(int)obcapi<<endl;
  if (rueck.size()) {
    obfcard=1;
  } else {
    Log(rots+Tx[T_Keine_ISDN_Karte_gefunden]+schwarz+Tx[T_mitCapi]+rot+Tx[T_auf]+schwarz+"0.",1,oblog);
    obcapi=obfcard=0;
  }
  obfcgeprueft=1;
} // void paramcl::pruefisdn()

// wird aufgerufen in: main, pruefhyla
// koennte auch im Fall eines entfernten Modems oder hylafax-Programms benoetigt werden
// sucht das Hylaverzeichnis und setzt varsphylavz darauf, return 0, wenn nicht gefunden dann varsphylavz="", return 1
// wird aufgerufen in: pruefhyla, main
// varsphylavz und hsendqvz festlegen
int paramcl::setzhylavz()
{
  Log(violetts+Tx[T_setzhylavz]+schwarz,obverb,oblog);
  // wird fruehestens in korrerfolgszeichen benoetigt
  // varsphylavz wird benoetigt in: korrerfolgszeichen, untersuchespool, hfaxsetup(pruefhyla), pruefhyla, hylaausgeb(untersuchespool,zeigweitere)
  // hsendqvz wird benoetigt in: loescheallewartende, loeschewaise, zeigweitere, inDBh(faxemitH)
  const char* testcmd="/bin/faxrcvd";
  int fundart=0;
  uchar weiterpruefen=0; 
  // 28.3.16: Die Datei /etc/init.d/hylafax+ taugt nicht fuer die Fallunterscheidung, da sie selbst eine Fallunterscheidung enthaelt

  svec hrueck;
  // 1) hylafax-Dienst im systemd suchen, dort steht z.B. ConditionPathExists=/var/spool/hylafax/etc/setup.cache ...
  systemrueck("grep /var $(dirname $(dirname $(which systemctl)))/lib/systemd/system/*fax*.service 2>/dev/null | "
      "head -n 1 | cut -d'=' -f2 | awk -F'/etc' '{print $1}'", obverb,oblog,&hrueck);
  if (hrueck.size()) {
    varsphylavz=hrueck[0];
    fundart=1;
  } else {
    // 2) ... ansonsten steht vielleicht in /etc/init.d/hylafax das Verzeichnis:
    // in der OpenSuse-Datei bekam das Verzeichnis den Namen "SPOOL",
    // in Ubuntu "HYLAFAX_HOME"; dort bekam die Variable "SPOOL" einen anderen Inhalt

//    cppSchluess hylaconf[]={{"SPOOL"},{"HYLAFAX_HOME"}};
//    size_t cs=sizeof hylaconf/sizeof*hylaconf;
    schlArr hyconf; hyconf.init(2,"SPOOL","HYLAFAX_HOME");
    string hylacdat="/etc/init.d/hylafax";
    confdat hylac(hylacdat,&hyconf,obverb);
    if (!hyconf[1].wert.empty()) {
      //  if (cpplies(hylacdat,hylaconf,cs)) KLA
      varsphylavz=hyconf[1].wert;
      fundart=2;
    } else if (!hyconf[0].wert.empty()) {
      varsphylavz=hyconf[0].wert;
      fundart=2;
    } else {
      // 3) ... ansonsten schauen, welches Verzeichnis es gibt ...
      struct stat hstat,fstat;
      int hgibts, fgibts;
      const char *hfax="/var/spool/hylafax", *ffax="/var/spool/fax";
      hgibts=!lstat(hfax,&hstat);
      fgibts=!lstat(ffax,&hstat);
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
      }
    }
    weiterpruefen=1;
  } // if (hrueck.size()) else 

  // falls nicht im systemd-Dienst gefunden, dann zuerst im praeferierten, dann in anderen Verzeichnissen pruefen, wo es ./bin/faxrecvd gibt 
  if (weiterpruefen) {
    //  if (lsys.getsys(obverb,oblog)==sus) varsphylavz="/var/spool/fax";
    //  else if (lsys.getsys(obverb,oblog)==deb) varsphylavz="/var/spool/hylafax";
    string testvz=varsphylavz;
    for(unsigned iru=0;iru<(sizeof moeglhvz/sizeof *moeglhvz)+1;iru++) {
      struct stat entryhyla;
      if (!lstat((testvz+testcmd).c_str(),&entryhyla)) {
        varsphylavz=testvz; 
        if (iru) fundart=6;
        break;
      } else if (iru==sizeof moeglhvz/sizeof *moeglhvz) {
        // obhyla=0 hier noch nicht, da setzhylavz auch einmal vor der Installation schon aufgerufen wird
        break; // kein Verzeichnis gefunden
      }
      testvz=moeglhvz[iru];
    }
  }
  if (obverb) {
    string grund;
    switch (fundart) {
      case 1: grund=Tx[T_aus_systemd_fax_service_Datei_ermittelt];break;
      case 2: grund=Tx[T_aus_etc_init_d_hylafax_ermittelt];break;
      case 3: grund=Tx[T_aus_seiner_ausschliesslichen_Existenz_ermittelt];break;
      case 4: grund=Tx[T_aus_seinem_geringen_Alter_ermittelt];break;
      case 5: grund=Tx[T_aus_mangelnder_Alternative_ermittelt];break;
      case 6: grund=Tx[T_aus_Existenz_von]+blaus+testcmd+schwarz+Tx[T_ermittelt];break;
    }
    Log(string(Tx[T_hylafax_Verzeichnis])+blau+varsphylavz+schwarz+grund,obverb,oblog);
  }
  kuerzevtz(&varsphylavz);
  hsendqvz=varsphylavz+"/sendq";
  xferfaxlog=varsphylavz+"/etc/xferfaxlog"; 
  kuerzevtz(&hsendqvz);
  pruefverz(hsendqvz,obverb,oblog);
  return 0;
} // int paramcl::setzhylavz()

// Musterfunktion, die von einer Funktion in gesonderter,fakultativer Datei 'vorgaben.cpp' ueberschrieben werden kann
void paramcl::VorgbSpeziell() 
{
  Log(violetts+Tx[T_VorgbSpeziell]+schwarz,obverb,oblog);
  dbq="autofax";
  muser="user";
  citycode="8131";
  msn="999999";
  LocalIdentifier=Tx[T_MeiEinrichtung];
  cFaxUeberschrift=Tx[T_Mei_FaxUeberschrift];
  sqlz=sqlvz="0";
//  host="localhost"; // 'localhost' schon Vorgabe bei Definition
  zufaxenvz="/var/"+prog+vtz+Tx[T_zufaxen];
  wvz="/var/"+prog+vtz+Tx[T_warteauffax];
  nvz="/var/"+prog+vtz+Tx[T_nichtgefaxt];
  empfvz="/var/"+prog+vtz+Tx[T_empfvz];
  static zielmustercl zmi[]={zielmustercl("[Ss]pamfax","/var/autofax/spam"),zielmustercl("","/var/autofax/gesandt")}; // nur als Beispiel
  zmvp=zmi;
  zmvzn=sizeof zmi/sizeof *zmi;
} // void paramcl::VorgbSpeziell() 

// in VorgbAllg, pruefcapi
void paramcl::liescapiconf()
{
  Log(violetts+Tx[T_liescapiconf]+schwarz,obverb,oblog);
  svec rueck;
  systemrueck("find /etc/capisuite /usr/local/etc/capisuite -type f -name fax.conf",obverb-2,oblog,&rueck);
  if (rueck.size()) cfaxconfdat=rueck[0];

  capiconf.init(10,"spool_dir","fax_user_dir","send_tries","send_delays","outgoing_MSN",
      "dial_prefix","fax_stationID","fax_headline","fax_email_from","outgoing_timeout");
  if (!cfaxconfdat.empty()) {
    static string capiconfvz=dir_name(cfaxconfdat);
    pruefverz(capiconfvz,obverb,oblog,0);
    //  confdat cfaxconf(cfaxconfdat,capiconf,ccs,obverb);
    static confdat cfaxconf(cfaxconfdat,&capiconf,obverb);
    cfaxcp=&cfaxconf;
    cfaxcp->Abschn_auswert(obverb);
    // wenn sich cuser in cfaxconf findet, dann so lassen
    // wenn nicht, dann:
    //   wenn cuser leer, dann den ersten besten user nehmen
    //   sonst cuser setzen
//    cuser="";
    string ncuser;
    for(size_t i=cfaxconf.zn.size();i>0;) {
      int erg;
      char buf[250];
      if ((erg=sscanf(cfaxconf.zn[--i].c_str(),"[%[^]]]",buf))>0) 
        if (strcasecmp(buf,"global")) {
          if (!cuser.empty()) {
           if (cuser==buf) {
            ncuser.clear();
            break;
           }
          }
          if (ncuser.empty()) ncuser=buf; // nehme den letzten besten user
        }
    }
    if (cuser.empty()) 
      cuser=ncuser;
    if (cuser.empty()) {
      string benutzer=curruser();
      if (benutzer!="root")
       cuser=benutzer;
      hylazuerst=1;
    }
  }
  if (capiconf[0].wert.empty()) {
    spoolcapivz="/var/spool/capisuite";
  }  else {           
    //  if (cpplies(cfaxconfdat,capiconf,ccs,&rest)) KLA
    spoolcapivz=capiconf[0].wert;
    cfaxuservz=capiconf[1].wert;
  }
  if (cfaxuservz.empty()) 
    cfaxuservz=spoolcapivz+"/users";
  // <<rot<<"cfaxuservz in Vorgallg: "<<cfaxuservz<<schwarz<<endl;

  rueck.clear();
  systemrueck("find /etc/capisuite /usr/local/etc/capisuite -type f -name capisuite.conf",obverb-2,oblog,&rueck);
  if (rueck.size()) {
    ccapiconfdat=rueck[0];
  }
  if (!ccapiconfdat.empty()) {
    uchar obneuer=0;
    struct stat cstat;
    static time_t lgelzeit=0; // Aenderungszeitpunkt der evtl. zuletzt eingelesenen ccapiconfdat
    time_t aktgelzeit;
    if (!lstat(ccapiconfdat.c_str(),&cstat)) { // <<rot<<ccapiconfdat<<" existiert!"<<schwarz<<endl;
      aktgelzeit=cstat.st_mtime;
      if (aktgelzeit>lgelzeit) {
        lgelzeit=aktgelzeit;
        obneuer=1;
      }
    }
    if (obneuer || !cconf.zahl) {
      if (!cconf.zahl) {
        cconf.init(3,"incoming_script","log_file","log_error");
      } else {
        cconf.reset();
      }
      confdat ccapic(ccapiconfdat,&cconf,obverb);
      if (!cuser.empty()) {
        for(size_t j=1;j<3;j++) {
          if (!cconf[j].wert.empty()) {
            struct stat statdat;
            if (!lstat(cconf[j].wert.c_str(),&statdat)) {
              setfaclggf(cconf[j].wert, falsch, 6, falsch,obverb,oblog);
            }
          }
        } // for(size_t j=1;j<3;j++) 
      } // if (!cuser.empty()) 
    } // if (obneuer || !cconf.zahl) 
  } // if (!ccapiconfdat.empty())

  if (!spoolcapivz.empty()) {
    cdonevz = mitvtz(spoolcapivz)+"done";
    cfailedvz = mitvtz(spoolcapivz)+"failed";
  }
} // void paramcl::liescapiconf()

// wird aufgerufen in: main
// allgemeine Vorgaben, fuer Deutschland
void paramcl::VorgbAllg()
{
  Log(violetts+Tx[T_VorgbAllg]+schwarz,obverb,oblog);
  liescapiconf();
  hylazuerst=0;
  // hmodemstr="ACM";
  maxcapiv="3";
  maxhylav="3";
  gleichziel=1;
  anfaxstr=Tx[T_an_Fax];
  ancfaxstr=Tx[T_an_cFax];
  anhfaxstr=Tx[T_an_hFax];
  anstr=Tx[T_an];
  undstr=Tx[T_und];
  countrycode="49";
  LongDistancePrefix="0";
  InternationalPrefix="00";
   // um z.B. spezielle Vorgaben (s. VorgbSpeziell) vom Server abhaengig machen zu koennen
#ifdef _WIN32
  // char lpszUsername[255]; DWORD dUsername = sizeof(lpszUsername); GetUserName(lpszUsername, &dUsername);
  dcpt = sizeof(cpt);
  GetComputerName(cpt,&dcpt);
#elif linux
  // uid_t userId = getuid(); passwd* pw = getpwuid(userId); pw->pw_name<<endl;
  cptlen = MAXHOSTNAMELEN;
  gethostname(cpt, cptlen);
#endif
  cronminut="2";
//  pruefcvz(); // 1.7.16 zu frueh
} // void paramcl::VorgbAllg

// wird aufgerufen in: konfcapi, VorgbAllg
void paramcl::pruefcvz()
{
  // <<rot<<"cfaxuservz in pruefcvz: "<<cfaxuservz<<schwarz<<endl;
  Log(violetts+Tx[T_pruefcvz]+schwarz+"ccfaxuservz: "+violett+cfaxuservz+schwarz,obverb,oblog);
  kuerzevtz(&cfaxuservz);
  pruefverz(cfaxuservz,obverb,oblog,1);
  cfaxusersqvz=cfaxuservz+vtz+cuser+"/sendq"; //  "/var/spool/capisuite/users/<user>/sendq";
  pruefverz(cfaxusersqvz,obverb,oblog,1);
  cfaxuserrcvz=cfaxuservz+vtz+cuser+"/received";
  // <<violett<<"cfaxuserrcvz: "<<cfaxuserrcvz<<schwarz<<endl;
  pruefverz(cfaxuserrcvz,obverb,oblog,1);
  pruefverz(cfaxuservz+vtz+"/autofaxarch",obverb,oblog,1);
  pruefverz(cfaxuservz+vtz+"/failed",obverb,oblog,1);
  pruefverz(cfaxuservz+vtz+"/sendq",obverb,oblog,1);

} // paramcl::pruefcvz

// wird aufgerufen in lieskonfein
void paramcl::setzzielmuster(confdat& afconf)
{
    if (!zmvzn || !zmvp) {
      zmvp= new zielmustercl{"","/var/"+prog+"/ziel"};
      zmvzn=1;
    }
    zmvz=ltoan(zmvzn); // aus VorgbSpeziell

    uchar zmda=0; // 1= Zielmuster in der Konfigurationsdatei schon festgelegt
    for(int iru=0;;iru++) {
      zmzn=atol(zmz.c_str());
      if (!iru) if (zmzn>0) zmda=1;
      if (zmzn) break;
      // Vorgaben uebernehmen
      zmz=zmvz;
      obkschreib=1;
    }
    
//    zmconfp = new cppSchluess[zmzn+zmzn];
    zmconf.neu(zmzn+zmzn);
    zmp=new zielmustercl[zmzn];
    // Vorgaben uebernehmen
    for(size_t i=0;i<(zmzn<zmvzn?zmzn:zmvzn);i++) {
     zmp[i].setzemuster(zmvp[i].holmuster());
     zmp[i].ziel=zmvp[i].ziel;
    }
    for (size_t i=0;i<zmzn;i++) {
     zmconf[2*i].name=string("ZMMuster_")+ltoan(i+1);
     zmconf[2*i].setze(&zmp[i].holmuster());
     zmconf[2*i+1].name=string("ZMZiel_")+ltoan(i+1);
     zmconf[2*i+1].setze(&zmp[i].ziel);
    }
    if (zmda) {
    // jetzt stehen die Variablen fuer die Zielverzeichnisse zur Verfuegung
      afconf.auswert(&zmconf,obverb);
      for(size_t i=0;i<zmzn;i++) {
        if (i==zmzn-1) zmconf[2*i].wert=""; // das letzte Muster muss "" sein, damit jedes Fax beruecksichtigt wird
        zmp[i].setzemuster(zmconf[2*i].wert);
        zmp[i].ziel=zmconf[2*i+1].wert;
      }
    }
} // void paramcl::setzzielmuster()

// wird aufgerufen in lieskonfein
void paramcl::setzsql(confdat& afconf)
{
  sqlzn=atol(sqlz.c_str());
  // Vorgaben uebernehmen
  if (sqlzn) {
    //      sqlconfp= new cppSchluess[sqlzn];
    sqlconf.neu(sqlzn);
    for(size_t i=0;i<sqlzn;i++) {
      sqlconf[i].name=string("SQL_")+ltoan(i+1);
      if (i<sqlvzn && i<sqlconfv.zahl) {
        sqlconf[i].wert=sqlconfv[i].wert;
        // <<"i: "<<hviolett<<i<<schwarz<<", sqlconf["<<i<<"]: "<<blau<<sqlconf[i].name<<schwarz<<endl;
        // <<"i: "<<blau<<i<<schwarz<<", sqlconf["<<i<<"]: "<<rot<<sqlconf[i].wert<<schwarz<<endl;
      } // if (i<sqlvzn) 
    } // for(size_t i=0;i<sqlzn;i++) 
  } // if (sqlzn) 
  // jetzt erst stehen die Variablen fuer alle SQL-Befehle zur Verfuegung
  afconf.auswert(&sqlconf,obverb);
  //       for(size_t akt=0;akt<sqlzn;akt++) KLA
  //        <<"akt: "<<hviolett<<akt<<schwarz<<", sqlconf["<<akt<<"]: "<<blau<<sqlconf[akt].name<<schwarz<<endl;
  //       <<"akt: "<<violett<<akt<<schwarz<<", sqlconf["<<akt<<"]: "<<dblau<<sqlconf[akt].wert<<schwarz<<endl;
  //      KLZ
}


// wird aufgerufen in: main
void paramcl::lieskonfein()
{
  Log(violetts+Tx[T_lieskonfein]+schwarz,obverb,oblog);
  if (konfdatname.empty()) konfdatname = aktprogverz()+".conf";
  /*
  static cppSchluess gconf[]={{"langu"},{"obcapi"},{"obhyla"},{"hylazuerst"},{"maxcapiv"},{"maxhylav"},{"cuser"},
    {"countrycode"},{"citycode"},{"msn"},{"LongDistancePrefix"},{"InternationalPrefix"},{"LocalIdentifier"},
    {"cFaxUeberschrift"},{"cklingelzahl"},{"hmodem"},{"hklingelzahl"},
    {"gleichziel"},{"zufaxenvz"},{"wartevz"},{"nichtgefaxtvz"},{"empfvz"},{"cronminut"},{"anfaxstr"},{"ancfaxstr"},{"anhfaxstr"},
    {"anstr"},{"undstr"},{"host"},{"muser"},{"mpwd"},{"datenbank"},{"logvz"},{"logdname"},{"sqlz"},{"musterzahl"}};
  cgconfp=gconf;
  gcs=sizeof gconf/sizeof*gconf;
  */
    // cgconf.init muss spaetetens am Anfang von getcommandl0 kommen
  confdat afconf(konfdatname,&cgconf,obverb); // hier werden die Daten aus der Datei eingelesen
  if (1) {
    //  if (cpplies(konfdatname,gconf,gcs)) KLA
    // sodann werden die Daten aus gconf den einzelenen Klassenmitgliedsvariablen zugewiesen 
    // die Reihenfolge muss der in cgconf.init (in getcommandl0) sowie der in rueckfragen entsprechen
    rzf=0;
    unsigned lfd=0;
    if (langu.empty()) {
      if (cgconf[lfd].gelesen) cgconf[lfd].hole(&langu); else rzf=1; // Sprache aus der Commandline geht vor Konfiguration
      lgnzuw();
    } 
    lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&host); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&muser); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) mpwd=XOR(string(cgconf[lfd].wert),pk); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&dbq); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&sqlz); else rzf=1; lfd++;
    setzsql(afconf);
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&zmz); else rzf=1; lfd++;
    setzzielmuster(afconf);
  // <<"lieskonfein vor  obcapi: "<<(int)obcapi<<endl;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&obcapi); else rzf=1; lfd++;
  // <<"lieskonfein nach obcapi: "<<(int)obcapi<<endl;
    konfobcapi=obcapi;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&obhyla); else rzf=1; lfd++;
    konfobhyla=obhyla;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&hylazuerst); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&maxcapiv); else rzf=1;} lfd++;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&maxhylav); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cuser); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&countrycode); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&citycode); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&msn); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&LongDistancePrefix); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&InternationalPrefix); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&LocalIdentifier); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cFaxUeberschrift); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cklingelzahl); else rzf=1;} lfd++;
    if (obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&hmodem); else rzf=1;} lfd++;
    if (obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&hklingelzahl); else rzf=1;} lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&gleichziel); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&zufaxenvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&wvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&nvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&empfvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&anfaxstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&ancfaxstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&anhfaxstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&anstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&undstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cronminut); else rzf=1; lfd++;
    if (logvneu) cgconf[lfd].setze(&logvz);
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&logvz); else rzf=1; lfd++;
    if (logdneu) cgconf[lfd].setze(&logdname);
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&logdname); else rzf=1; lfd++;
    loggespfad=logvz+vtz+logdname;
    logdt=&loggespfad.front();
  } else {
    rzf=1;
  } // (1) else
  if (nrzf) rzf=0;
} // void paramcl::lieskonfein()

// wird aufgerufen in: main
int paramcl::getcommandline()
{
  Log(violetts+"getcommandline()"+schwarz,obverb,oblog);
  //  uchar plusverb=0;
  opts.push_back(optioncl("zvz","zufaxenvz", &Tx, T_faxt_die_Dateien_aus_pfad_anstatt,&zufaxenvz,pverz,&cgconf,"zufaxenvz",&obkschreib));
  opts.push_back(optioncl("wvz","wartevz", &Tx, T_Dateien_warten_in_pfad_anstatt,&wvz,pverz,&cgconf,"wartevz",&obkschreib));
  opts.push_back(optioncl("nvz","nichtgefaxtvz", &Tx, T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,&nvz,pverz,
          &cgconf,"nichtgefaxtvz",&obkschreib));
  opts.push_back(optioncl("evz","empfvz", &Tx, T_Empfangsverzeichnis_fuer_Faxempfang,&empfvz,pverz,&cgconf,"empfvz",&obkschreib));
  opts.push_back(optioncl("cm","cronminut", &Tx,T_Alle_wieviel_Minuten_soll,&prog,T_aufgerufen_werden_0_ist_gar_nicht, &cronminut, pzahl, 
                          &cgconf,"cronminut",&obkschreib));
  opts.push_back(optioncl("capi","obcapi", &Tx, T_Capisuite_verwenden ,&obcapi,1,&cgconf,"obcapi",&obkschreib));
  opts.push_back(optioncl("nocapi","keincapi", &Tx, T_Capisuite_nicht_verwenden,&obcapi,0,&cgconf,"obcapi",&obkschreib));
  opts.push_back(optioncl("hyla","obhyla", &Tx, T_hylafax_verwenden,&obhyla,1,&cgconf,"obhyla",&obkschreib));
  opts.push_back(optioncl("nohyla","keinhyla", &Tx, T_hylafax_nicht_verwenden,&obhyla,0,&cgconf,"obhyla",&obkschreib));
  opts.push_back(optioncl("cz","capizuerst", &Tx, T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken,&hylazuerst,0,&cgconf,"hylazuerst",&obkschreib));
  opts.push_back(optioncl("hz","hylazuerst", &Tx, T_versuche_faxe_zuerst_ueber_hylafax_wegzuschicken,&hylazuerst,1,&cgconf,"hylazuerst",&obkschreib));
  //  opts.push_back(optioncl("hms","hylamodemstring",&Tx, T_sucht_nach_dev_tty_string_als_Modem_mit_string_anstatt,&hmodemstr,psons));
  opts.push_back(optioncl("mod","hmodem",&Tx, T_Fuer_Hylafax_verwendetes_Modem,&hmodem,psons,&cgconf,"hmodem",&hylazukonf));
  opts.push_back(optioncl("mc","maxcapiv",&Tx, T_nach_zahl_Versuchen_Capisuite_wird_Hylafax_versucht,&maxcapiv,pzahl,&cgconf,"maxcapiv",&obkschreib));
  opts.push_back(optioncl("mh","maxhylav",&Tx, T_nach_zahl_Versuchen_Hylafax_wird_Capisuite_verwendet,&maxhylav,pzahl,&cgconf,"maxhylav",&obkschreib));
  opts.push_back(optioncl("cuser","cuser",&Tx, T_verwendet_fuer_Capisuite_den_Linux_Benutzer_string_anstatt,&cuser,psons,&cgconf,"cuser",&capizukonf));
  opts.push_back(optioncl("ckzl","cklingelzahl",&Tx, T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt,&cklingelzahl,pzahl,
                                                        &cgconf,"cklingelzahl",&capizukonf));
  opts.push_back(optioncl("hkzl","hklingelzahl",&Tx, T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt,&hklingelzahl,pzahl,
                                                        &cgconf,"hklingelzahl",&hylazukonf));
  opts.push_back(optioncl("gz","gleichziel", &Tx, T_FAxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,&gleichziel,1,
                                                  &cgconf,"gleichziel",&obkschreib));
  opts.push_back(optioncl("afs","anfaxstr",&Tx, T_faxnr_wird_hinter_string_erwartet_statt_hinter,&anfaxstr,psons,&cgconf,"anfaxstr",&obkschreib));
  opts.push_back(optioncl("acfs","ancfaxstr",&Tx, T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter,&ancfaxstr,psons,
                                                      &cgconf,"ancfaxstr",&obkschreib));
  opts.push_back(optioncl("ahfs","anhfaxstr",&Tx, T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter,&anhfaxstr,psons,
                                                     &cgconf,"anhfaxstr",&obkschreib));
  opts.push_back(optioncl("as","anstr",&Tx, T_Adressatenname_wird_hinter_string_erwartet_statt_hinter,&anstr,psons,&cgconf,"anstr",&obkschreib));
  opts.push_back(optioncl("us","undstr",&Tx, T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt,&undstr,psons,
                                                &cgconf,"undstr",&obkschreib));
  opts.push_back(optioncl("host","host",&Tx, T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,&host,psons,&cgconf,"host",&obkschreib));
  opts.push_back(optioncl("muser","muser",&Tx, T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,&muser,psons,&cgconf,"muser",&obkschreib));
  opts.push_back(optioncl("mpwd","mpwd",&Tx, T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string_anstatt,&mpwd,psons,&cgconf,"mpwd",&obkschreib));
  opts.push_back(optioncl("db","datenbank",&Tx, T_verwendet_die_Datenbank_string_anstatt,&dbq,psons,&cgconf,"datenbank",&obkschreib));
  //  opts.push_back(optioncl("l","log", &Tx, T_protokolliert_ausfuehrlich_in_Datei+drot+loggespfad+schwarz+Tx[T_sonst_knapper],&oblog,1));
  //  opts.push_back(optioncl("lvz","logvz",&Tx, T_waehlt_als_Logverzeichnis_pfad_anstatt,&logvz,pverz));
  //  opts.push_back(optioncl("ld","logdname",&Tx, T_logdatei_string_im_Pfad+drot+logvz+schwarz+Tx[T_wird_verwendet_anstatt],&logdname,psons));
  //  opts.push_back(optioncl("ldn","logdateineu", &Tx, T_logdatei_vorher_loeschen,&logdateineu,1));
  //  opts.push_back(optioncl("v","verbose", &Tx, T_Bildschirmausgabe_gespraechiger,&plusverb,1));
  opts.push_back(optioncl("sqlv","sql-verbose", &Tx, T_Bildschirmausgabe_mit_SQL_Befehlen,&ZDB,255));
  opts.push_back(optioncl("rf","rueckfragen", &Tx, T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte,&rzf,1));
  opts.push_back(optioncl("norf","keinerueckfragen", &Tx, T_keine_Rueckfragen_zB_aus_Cron,&nrzf,1));
  opts.push_back(optioncl("loef","loeschefax", &Tx, T_ein_Fax_nach_Rueckfrage_loeschen,&loef,1));
  opts.push_back(optioncl("loew","loeschewaise", &Tx, T_Eintraege_aus, &spooltab, 
        T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist, &loew,1));
  opts.push_back(optioncl("loea","loescheallew", &Tx, T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus, &spooltab, T_loeschen, &loea,1));
  opts.push_back(optioncl("loee","loescheempf", &Tx, T_empfangene_Dateien_loeschen_die_nicht_verarbeitet_werden_koennen,&loee,1));
  opts.push_back(optioncl("kez","korrerfolgszeichen", &Tx, T_in_der_Datenbanktabelle, &touta, T_wird_das_Erfolgszeichen_korrigiert, &kez,1));
  opts.push_back(optioncl("bwv","bereinigewv", &Tx, T_Dateien_aus_Warteverzeichnis_gegen, &touta, T_pruefen_und_verschieben, &bwv,1));
  opts.push_back(optioncl("st","stop", &Tx, T_autofax_anhalten,&anhl,1));
  opts.push_back(optioncl("lista","listarchiv", &Tx, T_listet_Datensaetze_aus, &touta, T_mit_Erfolgskennzeichen_auf, &lista,1));
  opts.push_back(optioncl("listf","listfailed", &Tx, T_listet_Datensaetze_aus, &touta, T_ohne_Erfolgskennzeichen_auf, &listf,1));
  opts.push_back(optioncl("listi","listinca", &Tx, T_listet_Datensaetze_aus, &tinca, T__auf, &listi,1));
  opts.push_back(optioncl("n","dszahl", &Tx, T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt, &dszahl,pzahl));
  opts.push_back(optioncl("info","version", &Tx, T_Zeigt_die_Programmversion_an, &zeigversion,1));
  opts.push_back(optioncl("vi","vi", &Tx, T_Konfigurationsdatei_editieren, &obvi,1));
  opts.push_back(optioncl("h","hilfe", &Tx, T_Zeigt_diesen_Bildschirm_an, &hilfe,1));
  opts.push_back(optioncl("?","help", &Tx, -1, &hilfe,1));

//   string altlogdname(logdname);
//  string altckzl(cklingelzahl);
//  string althkzl(hklingelzahl);

  // hier wird die Befehlszeile ueberprueft:
  for(;optslsz<opts.size();optslsz++) {
    for(size_t i=0;i<argcmv.size();i++) {
      if (opts[optslsz].pruefp(&argcmv,&i,&hilfe)) {
        break;
      }
    }
  }
  if (nrzf) rzf=0;
  for(size_t i=0;i<argcmv.size();i++) {
    if (!argcmv[i].agef) {
      Log(rots+"Parameter: "+gruen+argcmv[i].argcs+rot+Tx[T_nicht_erkannt]+schwarz,1,1);
      hilfe=1;
    }
  }
  if (!obcapi) hylazuerst=1; else if (!obhyla) hylazuerst=0;
  /*
  if (altlogdname!=logdname || altlogvz!=logvz) {
    if (!logdname.empty()) {
      loggespfad=logvz+vtz+logdname;
      logdt=&loggespfad.front();
      cgconf.setze("logdname",logdname);
      cgconf.setze("logvz",logvz);
      obkschreib=1;
    }
  }
  */
  /*
  if (altckzl!=cklingelzahl || rzf) {
    cgconf.setze("cklingelzahl",cklingelzahl); // zum Schreiben in die /usr/local/sbin/autofax.conf in autokonfschreib
    capizukonf=1;
    obkschreib=1;
  }
  if (althkzl!=hklingelzahl || rzf) {
    cgconf.setze("hklingelzahl",hklingelzahl);
    hylazukonf=1;
    obkschreib=1;
  }
  */
  
