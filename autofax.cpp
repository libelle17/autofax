// Aenderung in linux3
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
// #include <fstream> // jetzt in kons.h
// #include <sstream>
// #include <dirent.h> // DIR, dirent, opendir, readdir, PATH_MAX
// #include <boost/algorithm/string.hpp> // clock // jetzt in kons.h

// #include "vmime/vmime.hpp"
// #include "vmime/platforms/posix/posixHandler.hpp"
#include "kons.h"
#include "DB.h"
// #include "iconverter.h"
// #include "datetime_utils.hpp"
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

// const char* logdatname;
uchar ZDB=0; // G.Schade 22.4.14 fuer Zusatz-Debugging (SQL): ZDB 255, sonst: 0
const char sep = 9; // geht auch: "[[:blank:]]"

const string s_true="true";
const string s_dampand="&&";
const string s_gz="gz";
// const char *tmmoegl[2]={"%d.%m.%y","%c"}; // Moeglichkeiten fuer strptime

const char *logdt="/var/log/autofaxvorgabe.log";// darauf wird in kons.h verwiesen; muss dann auf lgp zeigen
const unsigned ktage=1; // kurzes Intervall fuer Faxtabellenkorrektur, 1 Tag
const unsigned mtage=30; // mittleres Intervall fuer Faxtabellenkorrektur, 1 Monat
const unsigned ltage=73000; // langes Intervall fuer Faxtabellenkorrektur, 200 Jahre

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
  T_Linux_Benutzer_fuer_Capisuite_Samba,
  T_Linux_Benutzer_fuer_Samba,
  T_Eigene_Landesvorwahl_ohne_plus_oder_00,
  T_Eigene_Ortsvorwahl_ohne_0,
  T_Eigene_MSN_Faxnummer_ohne_Vorwahl,
  T_Praefix_fuer_ausserorts_zB_0,
  T_Praefix_fuer_das_Ausland_zB_00,
  T_Hylafax_bis_10_Buchstabe_fuer_eigenen_Namen,
  T_Capisuite_bis_20_Buchstaben_fuer_eigenen_Namen,
  T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt,
  T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt,
  T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden,
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
  T_capistat,
  T_statuscode_in_letztem_gescheitertem_hylafax,
  T_status_in_letztem_gescheitertem_hylafax,
  T_capispooldateien_der_Capisuite,
  T_Fehler_beim_Pruefen_von,
  T_Name_des_Adressaten_aus_Dateiname,
  T_Datum_des_Losschickens,
  T_Ende_der_Uebertragung,
  T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname,
  T_Dateigroesse,
  T_Seitenzahl,
  T_Zahl_der_Anwahlen,
  T_Faxnummer_des_Adressaten,
  T_Titel_des_Adressaten,
  T_PID_falls_aus_Dateinamen_ermittelt,
  T_Kurzbezeichnung_der_eigenen_Faxstelle,
  T_Geraetename,
  T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax,
  T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax,
  T_identisch_zu_submid_nur_MSFax,
  T_Prioritaet_nur_MSFax,
  T_Faxnummer_des_Adressaten_nur_MSFax,
  T_Faxnummer_des_Senders_nur_MSFax,
  T_Beginn_der_Uebertragung_nur_MSFax,
  T_Archiv_fuer_die_erfolgreichen_Faxe,
  T_Archiv_fuer_die_Dateinamen_vor_Aufteilung,
  T_Archiv_fuer_die_gescheiterten_Faxe,
  T_Welches_Fax_soll_geloescht_werden,
  T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch,
  T_wirklich_geloescht_werden,
  T_Kein_Fax_zum_Loeschen_vorhanden,
  T_Keine_ISDN_Karte_gefunden,
  T_ISDN_Karte_gefunden,
  T_Setze,
  T_mitCapi,
  T_aauf,
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
  T_verwendet_fuer_Capisuite_Samba_den_Linux_Benutzer_string_anstatt,
  T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,
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
//  T_Zahl_der_SQL_Befehle_fuer_Namenszuordnung,
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
  T_korrigierecapi,
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
  T_pruefspool,
  T_pruefouta,
  T_pruefudoc,
  T_pruefinca,
  T_prueffuncgettel3,
  T_capiausgeb,
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
  T_avon,
  T_nicht_erkannt,
  T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm,
  T_Zahl_der_nicht_geloeschten_Dateien,
  T_hylanr,
  T_Capispooldatei,
  T_Gesamt,
  T_Verwende,
  T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen,
  T_nicht_gefunden_kein_Datenbankeintrag,
  T_setzhylastat,
//  T_empfangene_Dateien_loeschen_die_nicht_verarbeitet_werden_koennen,
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
  T_versandte_Faxe,
  T_aus_systemd_fax_service_Datei_ermittelt,
  T_aus_etc_init_d_hylafax_ermittelt,
  T_aus_seiner_ausschliesslichen_Existenz_ermittelt,
  T_aus_seinem_geringen_Alter_ermittelt,
  T_aus_mangelnder_Alternative_ermittelt,
  T_aus_Existenz_von,
  T_ermittelt,
  T_hylafax_Verzeichnis,
  T_Bezeichnung_des_Anrufers,
  T_Passwort_fuer_samba,
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
  T_liescapiconf,
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
  T_Zielmuster_Nr,
  T_Zielverzeichnis_Nr,
  T_ueber_den_Quellcode,
  T_ueber_das_Installationspaket,
  T_gibts,
  T_nicht,
  T_Loesche_Fax_hylanr,
  T_erfolgreich_geloescht_fax_mit,
  T_Moment_muss_Kernel_herunterladen,
  T_Zur_Inbetriebnahme_der_Capisuite_muss_das_Modul_capi_geladen_werten,
  T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten,
  T_aufrufen,
  T_Text_aus_empfangenen_Faxen_wird_ermittelt,
  T_Text_aus_empfangenen_Faxen_wird_nicht_ermittelt,
  T_Text_aus_gesandten_Bildern_wird_ermittelt,
  T_Text_aus_gesandten_Bildern_wird_nicht_ermittelt,
  T_Text_aus_empfangenen_Faxen_wird_bei_diesem_Aufruf_ermittelt,
  T_Text_aus_empfangenen_Faxen_wird_bei_diesem_Aufruf_nicht_ermittelt,
  T_Text_aus_gesandten_Bildern_wird_bei_diesem_Aufruf_ermittelt,
  T_Text_aus_gesandten_Bildern_wird_bei_diesem_Aufruf_nicht_ermittelt,
  T_soll_Text_in_empfangenen_Faxen_mit_OCR_gesucht_werden,
  T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden,
  T_nicht_angekommen,
  T_Optionen_die_nicht_gespeichert_werden,
  T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden,
  T_ob_ein_Modem_drinstak,
  T_or,
  T_ob_eine_Fritzcard_drinstak,
  T_Zahl_der_angegebenen_sql_Befehle_zur_Suche_nach_Absendern,
  T_Zahl_der_Muster_Verzeichnis_Paare_zum_Speichern_ankommender_Faxe,
  T_pruefsfftobmp,
  T_listet_wartende_Faxe_auf,
  T_cronzuplanen,
  T_Zahl_der_Wahlversuche_in_Hylafax,
  T_suche_in_verarbeiteten_Faxen_nach,
  T_mitstr,
  T_wartende_Faxe,
  T_Index_auf_urspruenglichen_Dateinamen,
  T_Gesammelt_wurden,
	T_gestrichen,
	T_schwebend,
	T_wartend,
	T_blockiert,
	T_bereit,
  T_verarb,
  T_gesandt,
  T_gescheitert,
  T_nicht_in_der_Warteschlange,
  T_woasined,
	T_nichtfaxbar,
	T_Der_Kernel_hat_sich_offenbar_seit_dem_Einloggen_von,
	T_nach,
	T_verjuengt_Bitte_den_Rechner_neu_starten_und_dann_mich_nochmal_aufrufen,
	T_pruefDB,
	T_wird,
	T_gar_nicht,
	T_alle,
	T_Minuten,
	T_statt,
	T_aufgerufen,
	T_unveraendert,
	T_Kein_cron_gesetzt_nicht_zu_setzen,
	T_Seiten,
	T_suchestr,
	T_pruefsoffice,
	T_pruefconvert,
	T_pruefunpaper,
	T_pruefocr,
	T_zupdf,
	T_Lade_Capi_Module,
	T_sammlecapi,
	T_bereinigecapi,
	T_sammlehyla,
	T_sammlefertigehyla,
	T_holtif,
	T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Misserfolg_gesetzt_werden,
	T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Erfolg_gesetzt_werden,
	T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird,
	T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird,
	T_Faxnr,
	T_Name_des_Adressaten_aus_Faxnummer_ermittelt,
	T_Aufrufintervall,
	T_kein_Aufruf,
	T_Minute,
	T_Firewallport,
	T_offen,
	T_zu,
	T_Installationsverzeichnis,
	T_Ergebnis_nach_make,
	T_Ergebnis_nach_make_install,
	T_MAX
};


const string sprachstr=string("Language/Sprache/Lingue/Lingua [")+blau+'d'+schwarz+"eutsch,"+blau+'e'+schwarz+"nglisch]"+"";
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
  {"Soll hylafax verwendet werden","Shall hylafax be used"},
  // T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden
  {"Soll vorrangig die Capisuite statt hylafax gewaehlt werden","Shall capisuite instead of hylafax bei chosen preferentially"},
  // T_Zahl_der_Versuche_in_Capisuite_bis_hylafax_eingeschaltet_wird
  {"Zahl der Versuche in Capisuite, bis hylafax eingeschaltet wird","Number of tries in Capisuite, until hylafax is started"},
  // T_Zahl_der_Versuche_in_hylafax_bis_Capisuite_eingeschaltet_wird
  {"Zahl der Versuche in hylafax, bis Capisuite eingeschaltet wird","Number of tries in hylafax, until Capisuite is started"},
  // T_Linux_Benutzer_fuer_Capisuite_Samba
  {"Linux-Benutzer fuer Capisuite und Samba","Linux user for capisuite and samba"},
  // T_Linux_Benutzer_fuer_Samba
  {"Linux-Benutzer fuer Samba","Linux user for samba"},
  // T_Eigene_Landesvorwahl_ohne_plus_oder_00
  {"Eigene Landesvorwahl ohne '+' oder '00'","Own international prefix without '+' or '00'"},
  // T_Eigene_Ortsvorwahl_ohne_0
  {"Eigene Ortsvorwahl ohne '0'","Own long distance prefix without '0'"},
  // T_Eigene_MSN_Faxnummer_ohne_Vorwahl
  {"Eigene MSN (Faxnummer ohne Vorwahl)","Own MSN (fax number without prefix)"},
  // T_Praefix_fuer_ausserorts_zB_0
  {"Praefix fuer ausserorts (z.B. '0')","prefix for long distance (e.g. '0')"},
  // T_Praefix_fuer_das_Ausland_zB_00
  {"Praefix fuer das Ausland (z.B. '00')","prefix for abroad (e.g. '00')"},
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
  {"Versuche Datei: '","Trying to install the file: '"},
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
  {"Prioritaet der Fax-Programme: 0=capi und 1=hyla per Konfigurationsdatei, 2=capi und 3=hyla per Faxdateiname",
	 "Priority of the fax programs: 0=capi and 1=hyla via configuration file, 2=capi and 3=hyla via fax file name"},
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
	{"state-Feld in hylafax: 0=init,1=gestrichen,2=schwebend,3=wartend,4=blockiert,5=bereit,6=verarb,7=gesandt,8=gescheitert,9=fehlend,10=woasined",
	 "state-field in hylafax: 0=init,1=suspended,2=pending,3=sleeping,4=blocked,5=ready,6=active,7=done,8=failed,9=missing,10=unknown"},
	// T_capistat
	{"capistat: 0=init,1=gestrichen,2=schwebend,3=wartend,4=blockiert,5=bereit,6=verarb,7=gesandt,8=gescheitert,9=fehlend,10=woasined",
	 "capistat: 0=init,1=suspended,2=pending,3=sleeping,4=blocked,5=ready,6=active,7=done,8=failed,9=missing,10=unknown"},
  // T_statuscode_in_letztem_gescheitertem_hylafax
  {"statuscode in letztem gescheitertem hylafax","status code of the last failed hylafax"},
  // T_status_in_letztem_gescheitertem_hylafax
  {"status in letztem gescheitertem hylafax","status of the last failed hylafax"},
  // T_capispooldateien_der_Capisuite
  {"capiSpooldateien der Capisuite","capi spool files of capisuite"},
  // T_Fehler_beim_Pruefen_von
  {"Fehler beim Pruefen von: ","Error while examining: "},
  // T_Name_des_Adressaten_aus_Dateiname
  {"Name des Adressaten aus Dateiname","Name of the receiver from file name"},
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
  // T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax
  {"outgoing schedule time oder so aehnlich (nur MS Fax)","outgoing schedule time or similar (only ms fax)"},
  // T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax
  {"Hinweis auf Dateiinhalt oder Adressat (nur MS Fax)","indication of file content or adressat (only ms fax)"},
  // T_identisch_zu_submid_nur_MSFax
  {"identisch zu submid (nur MS Fax)","identical to submid (only ms fax)"},
  // T_Prioritaet_nur_MSFax
  {"Prioritaet (nur MS Fax)","priority (only ms fax)"},
  // T_Faxnummer_des_Adressaten_nur_MSFax
  {"Faxnummer des Adressaten (nur MS Fax)","receiver's fax no. (only ms fax)"},
  // T_Faxnummer_des_Senders_nur_MSFax
  {"Faxnummer des Senders (nur MS Fax)","sender's fax no. (only ms fax)"},
  // T_Beginn_der_Uebertragung_nur_MSFax
  {"Beginn der Uebertragung (nur MS Fax)","transmission begin (only ms fax)"},
  // T_Archiv_fuer_die_erfolgreichen_Faxe
  {"Archiv fuer die erfolgreichen Faxe","archive for successful faxes"},
  // T_Archiv_fuer_die_Dateinamen_vor_Aufteilung
  {"Archiv fuer die Dateinamen vor Aufteilung","archive for filenames before splitting"},
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
  // T_ISDN_Karte_gefunden
  {"ISDN-Karte gefunden: ","ISDN-Card found: "},
  // T_Setze
  {". Setze ",". Setting "},
  // T_mitCapi
  {"mitCapi","withCapi"},
  // T_aauf
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
  //  // T_sucht_nach_dev_tty_string_als_Modem_mit_string_anstatt
  //  KLA "suche nach '/dev/tty<string>*' als Modem, mit <string> anstatt","search for '/dev/tty<string>*' as modem, with <string> instead of" KLZ,
  // T_nach_zahl_Versuchen_Capisuite_wird_Hylafax_versucht
  {"nach <zahl> Versuchen Capisuite wird Hylafax versucht, anstatt nach","try Hylafax after <no> tries of Capisuite instead of"}, 
  // T_nach_zahl_Versuchen_Hylafax_wird_Capisuite_verwendet
  {"nach <zahl> Versuchen Hylafax wird Capisuite versucht, anstatt nach","try Capisuite after <no> tries of Hylafax instead of"},
  // T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt
  {"Zahl der Klingeltoene, bis Capisuite den Anruf annimmt, anstatt","No. of bell rings until Capisuite accepts the call, instead of"},
  // T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt
  {"Zahl der Klingeltoene, bis Hylafax den Anruf annimmt, anstatt","No. of bell rings until hylafaxs accepts the call, instead of"},
  // T_verwendet_fuer_Capisuite_Samba_den_Linux_Benutzer_string_anstatt
  {"verwendet fuer Capisuite und/oder Samba den Linux-Benutzer <string> anstatt","takes the linux user <string> for capisuite and/or samba instead of"},
  // T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert
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
    "` without detection of file in waiting directory or capisuite fax or hylafax"},
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
  {"Fertig mit Parsen der Befehlszeile, Konfiguration zu schreiben: ","Parsing the command line finished, about to write configuration: "},
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
  {"Passwort fuer MySQL/MariaDB (Achtung: nur schwach verschluesselt!)","password for mysql/mariadb (caution: only weakly encrypted!)"},
  // "Datenbankname fuer MySQL/MariaDB auf '"
  {"Datenbankname fuer MySQL/MariaDB auf '","database name for mysql/mariabd on '"},
  // T_Logverzeichnis
  {"Logverzeichnis","log directory"},
  // T_Logdateiname
  {"Logdateiname","log file name"},
//  // T_Zahl_der_SQL_Befehle_fuer_Namenszuordnung
//  KLA "Zahl der SQL-Befehle fuer Namenszuordnung:","No.of SQL-commands for assignment of fax names" KLZ,
  // T_SQL_Befehl_Nr,
  {"Ggf. SQL-Befehl Nr. ","If desired, SQL command no. "},
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
  // T_Alle_wieviel_Minuten_soll
  {"alle wieviel Minuten soll ","every how many minutes shall "},
  // T_aufgerufen_werden_0_ist_gar_nicht]
  {" ueber crontab aufgerufen werden (0=gar nicht), anstatt ", " be called in crontab (0=not at all), instead of "},
  // T_Kann_Capisuite_nicht_installieren_verwende_Capi_nicht
  {"Kann Capisuite nicht installieren, verwende Capi nicht","Can't install capisuite, not using capi"},
  // T_wird_verwendet
  {" wird verwendet."," being used."},
  // T_mit_Baudrate,
  {"' mit Baudrate ","' with baud rate "},
  // T_Fuer_Hylafax_verwendetes_Modem
  {"Fuer Hylafax verwendetes Modem, anstatt ","Modem used for hylafax, instead of "},
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
  // T_korrigierecapi
  {"korrigierecapi()","correctcapi()"},
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
  // T_pruefspool
  {"pruefspool()","checkspool()"},
  // T_pruefouta
  {"pruefouta()","checkouta()"},
  // T_pruefudoc
  {"pruefudoc()","checkudoc()"},
  // T_pruefinca
  {"pruefinca()","checkinca()"},
  // T_prueffuncgettel3
  {"prueffuncgettel3()","checkfuncgettel3()"},
  // T_capiausgeb
  {"capiausgeb()","displaycapitries()"},
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
  // T_avon
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
  // T_nicht_gefunden_kein_Datenbankeintrag
  {"' nicht gefunden, kein Datenbankeintrag!"," not found, no database entry!"},
  // T_setzhylastat
  {"setzhylastat()","sethylastat()"},
//  // T_empfangene_Dateien_loeschen_die_nicht_verarbeitet_werden_koennen
//  KLA "empfangene Dateien loeschen, die nicht verarbeitet werden koennen","delete received files that could not be processed" KLZ,
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
  {" (falls es hier haengt, insbes. laenger als 3 Wochen, dann bitte erneut aufrufen)",
   " (if it hangs, especially more than 3 weeks, please invoke again)"},
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
  {" ('-'=SQL-Befehl loeschen, 2 Ergebnisfelder, '&&faxnr&&' wird ersetzt mit der Faxnr, s.man -Lde autofax)",
   " ('-'=delete this sql command, 2 result fields, '&&faxnr&&' will be replaces with the fax-no., see man autofax)"},
  // T_faxnr_wird_ersetzt_mit_der_Faxnr
  {" (2 Ergebnisfelder, '&&faxnr&&' wird ersetzt mit der Faxnr)",
   " (2 result fields, '&&faxnr&&' will be replaces with the fax-no.)"},
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
  {"Muss Hylafax installieren ...","Have to install hylafax ..."},
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
  // T_versandte_Faxe
  {" versandte Faxe:"," sent faxes:"},
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
  // T_Passwort_fuer_samba
  {"Passwort fuer samba ","Password for samba "},
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
  // T_liescapiconf
  {"liescapiconf()","readcapiconf()"},
  // T_VorgbAllg
  {"VorgbAllg()","generalprefs()"},
  // T_pruefisdn
  {"T_pruefisdn()","checkisdn()"},
  // T_keine_Rueckfragen_zB_aus_Cron
  {"keine Rueckfragen, z.B. aus cron","no questions, e.g. for a call of autofax within cron"},
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
  // T_Zielmuster_Nr
  {"Zielmuster Nr. ","Target pattern no. "},
  // T_Zielverzeichnis_Nr
  {"Zielverzeichnis Nr. ","Target directory no. "},
  // T_ueber_den_Quellcode
  {"... ueber den Quellcode","... with the source code"},
  // T_ueber_das_Installationspaket
  {"... ueber das Installationspaket","... with the installation package"},
  // T_gibts
  {" gibts"," exists"},
  // T_nicht
  {" nicht"," not"},
  // T_Loesche_Fax_hylanr
  {"Loesche das Fax mit der hylanr: ","Deleting the fax with the hylano: "},
  // T_erfolgreich_geloescht_fax_mit
  {"Erfolgreich geloescht: Fax mit der hylanr: ","Successfully deleted: Fax with the hylano: "},
  // T_Moment_muss_Kernel_herunterladen
  {"Moment, muss Kernel-rpm herunterladen ...","One moment, must download kernel-rpm ..."},
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
  // T_Text_aus_empfangenen_Faxen_wird_ermittelt
  {"Text aus empfangenen Faxen wird ermittelt","Text from received faxes will be filtered"},
  // T_Text_aus_empfangenen_Faxen_wird_nicht_ermittelt
  {"Text aus empfangenen Faxen wird nicht ermittelt","Text from received faxes will not be filtered"},
  // T_Text_aus_gesandten_Bildern_wird_ermittelt
  {"Text aus gesandten Bildern wird ermittelt","Text from sent pictures will be filtered"},
  // T_Text_aus_gesandten_Bildern_wird_nicht_ermittelt
  {"Text aus gesandten Bildern wird nicht ermittelt","Text from sent pictures will not be filtered"},
  // T_Text_aus_empfangenen_Faxen_wird_bei_diesem_Aufruf_ermittelt
  {"Text aus empfangenen Faxen wird bei diesem Aufruf ermittelt","Text from received faxes will be filtered at this call"},
  // T_Text_aus_empfangenen_Faxen_wird_bei_diesem_Aufruf_nicht_ermittelt
  {"Text aus empfangenen Faxen wird bei diesem Aufruf nicht ermittelt","Text from received faxes will not be filtered at this call"},
  // T_Text_aus_gesandten_Bildern_wird_bei_diesem_Aufruf_ermittelt
  {"Text aus gesandten Bildern wird bei diesem Aufruf ermittelt","Text from sent pictures will be filtered at this call"},
  // T_Text_aus_gesandten_Bildern_wird_bei_diesem_Aufruf_nicht_ermittelt
  {"Text aus gesandten Bildern wird bei diesem Aufruf nicht ermittelt","Text from sent pictures will not be filtered at this call"},
  // T_soll_Text_in_empfangenen_Faxen_mit_OCR_gesucht_werden
  {"Soll Text in empfangenen Faxen (mit \"OCR\") gesucht werden?",
   "Shall text from received faxes be searched (with \"ocr\")?"},
  // T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden
  {"Soll Text in gesandten Bildern (mit \"OCR\") gesucht werden?",
   "Shall text from sent pictures be searched (with \"ocr\")?"},
  // T_nicht_angekommen
  {"nicht angekommen ","not arrived "},
  // T_Optionen_die_nicht_gespeichert_werden
  {"Optionen, die nicht gespeichert werden: ","Options which are not saved: "},
  // T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden,
  {"Optionen, die in der Konfigurationsdatei gespeichert werden koennen (vorausgehendes '1'=doch nicht speichern, 'no'=Gegenteil, z.B. '-noocra','-1noocri'):",
   "Options which can be saved in the configuration file: (preceding '1'=don't save, 'no'=contrary, e.g. '-noocra','-1noocri'):"},
  // T_ob_ein_Modem_drinstak
  {"ob ein Modem drinstak, als diese Konfigurationsdatei geschrieben wurde","if a modem was present, when this configuration file was written"},
  // T_or
  {"' oder '","' or '"},
  // T_ob_eine_Fritzcard_drinstak
  {"ob eine Fritzcard drinstak, als die Konfigurationsdatei geschrieben wurde","if a fritzcard was present when the configuration file was written"},
  // T_Zahl_der_angegebenen_sql_Befehle_zur_Suche_nach_Absendern
  {"Zahl der angegebenen SQL-Befehle zur Suche nach Absendern","No. of specified sql commands for the search for senders"},
  // T_Zahl_der_Muster_Verzeichnis_Paare_zum_Speichern_ankommender_Faxe
  {"Zahl der Muster/Verzeichnis-Paare zum Speichern ankomender Faxe","No. of pattern/directory-pairs for saving received faxes"},
  // T_pruefsfftobmp
  {"pruefsfftobmp()","checksfftobmp()"},
  // T_listet_wartende_Faxe_auf
  {"listet wartende Faxe auf","lists waiting faxes"},
  // T_cronzuplanen
  {", cronzuplanen: ",", crontoscedule: "},
  // T_Zahl_der_Wahlversuche_in_Hylafax
  {"Zahl der Wahlversuche in Hylafax, anstatt ","No of dialing retries in hylafax, instead of  "},
  // T_suche_in_verarbeiteten_Faxen_nach
  {"Suche in verarbeiteten Faxen nach <string>: ","Look in processed faxes for <string>: "},
  // T_mitstr
  {" mit '"," with '"},
  // T_wartende_Faxe
  {" wartende Faxe "," waiting faxes"},
  // T_Index_auf_urspruenglichen_Dateinamen
  {"Index auf urspruenglichen Dateinamen in Tabelle udoc","Index on original filename in table udoc"},
  // T_Gesammelt_wurden
  {"Gesammelt wurden: ","Collected were: "},
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
	// T_nichtfaxbar
	{"nicht faxbar wg. Benennung","not faxable due to naming"},
	// T_Der_Kernel_hat_sich_offenbar_seit_dem_Einloggen_von
	{"Der Kernel hat sich offenbar seit dem Einloggen von '","The kernel seems to have been updated sind logging in from '"},
	// T_nach
	{"' nach '","' to '"},
	// T_verjuengt_Bitte_den_Rechner_neu_starten_und_dann_mich_nochmal_aufrufen
	{"' verjuengt. \nBitte den Rechner neu starten und dann mich nochmal aufrufen!","'. \nPlease restart the pc and then call me again!"},
	// T_pruefDB
	{"pruefDB(","checkDB("},
	// T_wird
	{" wird "," will be called "},
	// T_gar_nicht
	{"gar nicht","not at all"},
	// T_alle
	{"alle ","every "},
	// T_Minuten
	{" Minuten"," minutes"},
	// T_statt
	{" statt "," instead of "},
	// T_aufgerufen
	{" aufgerufen.","."},
	// T_unveraendert
	{"unveraendert ","as it was "},
  // T_Kein_cron_gesetzt_nicht_zu_setzen
	{"Kein cron gesetzt, nicht zu setzen","No cron set, not to set"},
	// T_Seiten
	{" Seite(n)"," page(s)"},
	// T_suchestr
	{"suchestr()","searchstr()"},
	// T_pruefsoffice
	{"pruefsoffice()","checksoffice()"},
	// T_pruefconvert
	{"pruefconvert()","checkconvert()"},
	// T_pruefunpaper
	{"pruefunpaper()","checkunpaper()"},
	// T_pruefocr
	{"pruefocr()","checkocr()"},
	// T_zupdf
	{"zupdf()","topdf()"},
	// T_Lade_Capi_Module
	{"Lade Capi-Module ...","Loading capi-modules ..."},
	// T_sammlecapi
	{"sammlecapi()","collectcapi()"},
	// T_bereinigecapi
	{"bereinigecapi()","revisecapi()"},
	// T_sammlehyla
	{"sammlehyla()","collecthyla()"},
	// T_sammlefertigehyla
	{"korrigierehyla()","correcthyla()"},
	// T_holtif
	{"holtif()","gettif()"},
	// T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Misserfolg_gesetzt_werden
	{"Bei folgenden Faxen musste das Erfolgskennzeichen gemaess Hylafax-Protkolldatei auf Misserfolg gesetzt werden:",
	 "For the following faxes, the success-flag had to be set to failure following the hylfax logfile:"},
	// T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Erfolg_gesetzt_werden,
	{"Bei folgenden Faxen mußte das Erfolgskennzeichen gemaess Hylafax-Protkolldatei auf Erfolg gesetzt werden:",
	 "For the following faxes, the success-flag had to be set to success following the hylafax logfile:"},
	// T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird
	{"Folgende Faxe waren mit falschem Erfolgskennzeichen eingetragen, was korrigiert wird:",
	 "The following faxes were documented with wrong success flag, which will be corrected:"},
	// T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird
	{"Folgende Faxe waren nicht eingetragen, was korrigiert wird:",
	 "The following faxes from the hylafax logfile have not been documented, which will be corrected:"},
	// T_Faxnr
	{"Faxnr.","fax no."},
	// T_Name_des_Adressaten_aus_Faxnummer_ermittelt
  {"Name des Adressaten, aus Faxnummer ermittelt","Name of the receiver according to his fax number"},
	// T_Aufrufintervall
	{", Aufrufintervall: ",", (cron) call interval: "},
	// T_kein_Aufruf
	{"kein cron-Aufruf","no cron call"},
	// T_Minute
	{" Minute"," minute"},
	// T_Firewallport
	{"Firewallport ","Firewall port "},
	// T_offen
	{" offen"," open"},
	// T_zu
	{" zu"," shut"},
	// T_Installationsverzeichnis
	{"Installationsverzeichnis: ","Installation directory: "},
	// T_Ergebnis_nach_make
	{"Ergebnis nach make","Result of make"},
	// T_Ergebnis_nach_make_install
	{"Ergebnis nach make install","result after make install"},
  {"",""}
}; // char const *Txautofaxcl::TextC[T_MAX+1][Smax]=


const string& pk = "8A490qdmjsaop4a89d0qÃ9m0943Ã09Ãax";
// const string& ccapiconfdat="/etc/capisuite/capisuite.conf";
// const string& cfaxconfdat="/etc/capisuite/fax.conf";


extern class lsyscl lsys;
extern class linst_cl linst;

using namespace std;
#ifdef mitpostgres 
const DBSTyp myDBS=Postgres; // MySQL;
#else
const DBSTyp myDBS=MySQL; // Postgres; // MySQL;
#endif
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
  int reti=regcomp(&regex, muster.c_str(),REG_EXTENDED|REG_ICASE); 
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
} // int zielmustercl::setzemuster(const string& vmuster)

int zielmustercl::obmusterleer() {
 return muster.empty();
} // int zielmustercl::obmusterleer() 

const string& zielmustercl::holmuster() {
 return muster;
} // const string& zielmustercl::holmuster()

// wird aufgerufen in: loeschefax, untersuchespool, capiausgeb, setzhylastat, hylaausgeb
inline const char* FxStatS(FxStat *i) 
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
// wird aufgerufen in: untersuchespool, korrigierehyla
void fsfcl::archiviere(DB *My, paramcl *pmp, struct stat *entryp, uchar obgescheitert, FaxTyp ftyp, uchar *geloeschtp, int obverb, int oblog)
{
//  string nob=ltoan((int)!obgescheitert);
  Log(violetts+Tx[T_archiviere]+schwarz+Tx[T_obgescheitert]+blau+ltoan((int)obgescheitert)+schwarz/*+" !obgescheitert: "+nob+*/,obverb,oblog);
  // Voraussetzung: telnr, original, id; veraendert: geloescht
  RS rins(My); 
  RS zs(My);
  string getname,bsname;
  getSender(pmp,telnr,&getname,&bsname);
  for(int runde=0;runde<2;runde++) {
    vector<instyp> einf;
    if (runde==0) zs.Abfrage("SET NAMES 'utf8'");
    else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
    einf.push_back(/*2*/instyp(My->DBS,"titel",&bsname));
    einf.push_back(/*2*/instyp(My->DBS,"rcname",&getname));
    if (capi) {if (cdd.empty()) cdd="0000-00-00";} else {if (hdd.empty()) hdd="0000-00-00";}
    einf.push_back(/*2*/instyp(My->DBS,"submt",ftyp==capi?&cdd:&hdd));
    einf.push_back(/*2*/instyp(My->DBS,"submid",ftyp==capi?&capisd:&hylanr));
    string pid;
    if (!original.empty()) {
      const char* ocstr=original.c_str(); // da c_str() fluechtig sein koennte
      char* pidp = (char*)strcasestr(ocstr,"pid ");
      if (pidp) {
        if (pidp==ocstr || (pidp>ocstr && (strchr(" .,;",*(pidp-1))))){
          for(pidp+=4;*pidp && *pidp!=' ';pidp++) {
            if (strchr("0123456789",*pidp)) pid+=*pidp;
          }  //           for(pidp+=4;*pidp && *pidp!=' ';pidp++)
        } //         if (pidp==ocstr || (pidp>ocstr && (strchr(" .,;",*(pidp-1)))))
      } //       if (pidp)
    } //     if (!original.empty())
    if (pid.empty()) pid="0";
    einf.push_back(/*2*/instyp(My->DBS,"pid",&pid));
    einf.push_back(/*2*/instyp(My->DBS,"Erfolg",(int)!obgescheitert));
    einf.push_back(/*2*/instyp(My->DBS,"docname",&original));
    Log(string("original (docname): ")+blau+original+schwarz,obverb,oblog);
    einf.push_back(/*2*/instyp(My->DBS,"idudoc",&idudoc));
		if (!tts) tts=time(0);
		//<<gruen<<"tts: "<<rot<<tts<<schwarz<<endl;
		// char buf[100];
    // strftime(buf, sizeof(buf), "%d.%m.%y %T", localtime(&tts));
		// <<"buf: "<<buf<<endl;
    einf.push_back(/*2*/instyp(My->DBS,"transe",&tts));
    if (!telnr.empty()) {
      string stdfax=pmp->stdfaxnr(telnr);
      einf.push_back(/*2*/instyp(My->DBS,"rcfax",&stdfax));
    } //     if (!telnr.empty())
    if (!adressat.empty()) einf.push_back(/*2*/instyp(My->DBS,"adressat",&adressat));
		einf.push_back(/*2*/instyp(My->DBS,"fsize",entryp->st_size>4294967295?0:entryp->st_size)); // int(10)
		einf.push_back(/*2*/instyp(My->DBS,"pages",pseiten));
    rins.insert(pmp->touta,einf, 1,0,ZDB?ZDB:!runde);  // einfuegen
    if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
    if (!rins.fnr) break;
    if (runde==1) {
      Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,obverb+1,oblog);
      exit(10);
    } //     if (runde==1)
  } // for(int runde=0;runde<2;runde++) 
  if (!rins.fnr && geloeschtp) { 
    RS rsloe(My,"DELETE FROM `"+pmp->spooltab+"` WHERE id = \""+id+"\"");
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
      zdng+=tuloeschen(zuloe,"",1,oblog);
    } //     for(uchar ru=0;ru<2;ru++) 
  } else { 
    zdng=1;
  } // if (!stamm.empty())
  return zdng;
} // void fsfcl::loeschecapi(int obverb, int oblog)

// Rueckgabe: Zahl der nicht geloeschten Eintraege
// wird aufgerufen in: loeschefax, loescheallewartende, untersuchespool,
int fsfcl::loeschehyla(paramcl *pmp,int obverb, int oblog)
{
  Log(violetts+Tx[T_loeschehyla]+schwarz,obverb,oblog);
  if (hylanr!="0" && !hylanr.empty()) {
    const uchar vmax=5;
    svec findrueck;
    // wenn Datei nicht mehr in sendq, sondern in doneq, sei es gelungen oder gescheitert, dann ist loeschen sinnlos
    systemrueck(("sudo find '")+pmp->hsendqvz+"' -name q"+hylanr,obverb,oblog,&findrueck);
    if (!findrueck.size()) {
      return 0;
    }
    pmp->hylasv1();
    pmp->hylasv2(hysrc);
    for(uchar iru=0;iru<vmax;iru++) {
      if (iru) {
        if (pmp->sfaxgetty) pmp->sfaxgetty->restart(obverb+1,oblog);
        if (pmp->shfaxd) pmp->shfaxd->restart(obverb+1,oblog);
        if (pmp->sfaxq) pmp->sfaxq->restart(obverb+1,oblog);
        // systemrueck(string("sudo systemctl restart '")+pmp->sfaxgetty->sname+"' '"+pmp->shfaxd->sname+"' '"+pmp->sfaxq->sname+"'",obverb-1,oblog);
      } // if (iru) 

      svec rueck, rmerg;
      string fuser;
      systemrueck("tac \""+pmp->xferfaxlog+"\" 2>/dev/null|grep -m 1 \"SUBMIT"+sep+sep+sep+hylanr+"\"|cut -f18|sed -e 's/^\"//;      s/\"$//'",
          obverb, oblog,&rueck);
      Log(Tx[T_Loesche_Fax_hylanr]+hylanr+" ...",-1,0);
      if (rueck.size() && rueck[0]!="root") {
        fuser=rueck[0]; 
        systemrueck("sudo su -c \"faxrm "+hylanr+"\" "+fuser+" 2>&1",oblog,obverb,&rmerg);
      } else {
        systemrueck("sudo faxrm "+hylanr+" 2>&1",oblog,obverb,&rmerg);
      }
      // folgender Befehl kann einen tac: write error: Broken pipe -Fehler erzeugen
      // systemrueck("sudo su -c \"faxrm "+hylanr+"\" $(tac \""+pmp->xferfaxlog+"\"|grep -m 1 \"SUBMIT"+sep+sep+sep+hylanr+"\"|cut -f18|sed -e 's/^\"//;s/\"$//') 2>&1",2,oblog,&rmerg);
      if (rmerg.size()) {
        if (rmerg[0].find(" removed")!=string::npos || rmerg[0].find("job does not exist")!=string::npos) {
          Log(blaus+Tx[T_erfolgreich_geloescht_fax_mit]+schwarz+hylanr,1,1);
          return 0;
        }
        Log(rots+Tx[T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm]+hylanr+"`:\n    "+schwarz+rmerg[0],1,1);
      } // if (rmerg.size()) 
    } // for(uchar iru=0;iru<vmax;iru++) 
  } // if (hylanr!="0" && !hylanr.empty()) 
  return 1;
} // int fsfcl::loeschehyla()

int paramcl::Log(const string& text,bool oberr/*=0*/,short klobverb/*=0*/)
{
	return ::Log(text,obverb,oblog,oberr,klobverb);
}

paramcl::paramcl(int argc, char** argv)
{
  cl=argv[0];
  for(int i=1;i<argc;i++)
    if (argv[i][0]) {
      argcmv.push_back(argcl(i,argv)); 
			cl+=" ";
			cl+=argv[i];
		}
  mpfad=meinpfad();
  meinname=base_name(mpfad); // argv[0];
	pruefinstv();
  vaufr=mpfad+" -norf"; // /usr/bin/autofax -norf
  saufr=base_name(vaufr); // autofax -norf
  tstart=clock();
	//  konfdatname.clear();
} // paramcl::paramcl()

void paramcl::pruefggfmehrfach()
{
  if (!hilfe && !obvi && !zeigvers && !lista && !listf && !listi && !listw && suchstr.empty() && !loef && !loew && !loea && !anhl) {
    pruefmehrfach(meinname);
  }
} // void paramcl::pruefggfmehrfach()

paramcl::~paramcl()
{
  if (My) {delete My; My=0;}
  if (sfaxq) {delete sfaxq; sfaxq=0;}
  if (shfaxd) {delete shfaxd; shfaxd=0;}
  if (sfaxgetty) {delete sfaxgetty; sfaxgetty=0;}
  if (scapisuite) {delete scapisuite; scapisuite=0;}
  if (shylafaxd) {delete shylafaxd; shylafaxd=0;}
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

// passt einen Dateinamen gemaess der vorhandenen Dateien in allen moeglichen Zielverzeichnissen so an
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
  Log(violetts+Tx[T_WVZinDatenbank]+schwarz);
  RS rins(My); 
  RS zs(My);
  string spoolid,udocid;
  for (unsigned nachrnr=0; nachrnr<fxvp->size(); ++nachrnr) {
    for(int runde=0;runde<2;runde++) {
      if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
      } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
      rins.clear();
      vector<instyp> einf; // fuer alle Datenbankeinfuegungen
      if (fxvp->at(nachrnr).spdf!=fxvp->at(nachrnr).ur||fxvp->at(nachrnr).npdf!=fxvp->at(nachrnr).ur) {
       einf.push_back(/*2*/instyp(My->DBS,"udocname",fxvp->at(nachrnr).ur));
       rins.insert(udoctab,einf,1,0,ZDB?ZDB:!runde,&udocid);
       rins.clear();
       einf.clear();
      }
      if (!udocid.empty()) 
        einf.push_back(/*2*/instyp(My->DBS,"idudoc",udocid));
      string odatei = base_name(fxvp->at(nachrnr).spdf);
      einf.push_back(/*2*/instyp(My->DBS,"original",&odatei));
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
       einf.push_back(/*2*/instyp(My->DBS,"adressat",&subst));
      }
      if (nachrnr<fxvp->size()) {
        string oudatei = base_name(fxvp->at(nachrnr).npdf);
        einf.push_back(/*2*/instyp(My->DBS,"origvu",&oudatei));
      }
			// in fxvp:
			// Prioritaet der Fax-Programme: 0 = capi und 0 = hyla per Konfigurationsdatei, 1= capi und 2= hyla per Faxdateiname
			// in Datenbank: 
			// Prioritaet der Fax-Programme: 0 = capi und 1 = hyla per Konfigurationsdatei, 2= capi und 3= hyla per Faxdateiname
      if (fxvp->at(nachrnr).prio>0 || hylazuerst) fxvp->at(nachrnr).prio++;
      einf.push_back(/*2*/instyp(My->DBS,"prio",fxvp->at(nachrnr).prio));
      einf.push_back(/*2*/instyp(My->DBS,"pages",fxvp->at(nachrnr).pseiten));
      rins.insert(altspool,einf, 1,0,ZDB?ZDB:!runde); // ,&spoolid);
      rins.insert(spooltab,einf, 1,0,ZDB?ZDB:!runde,&spoolid);
      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      if (spoolid!="null") break;
      if (runde==1) {
        ::Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
        exit(12);
      } //       if (runde==1)
    }   // for(int runde=0;runde<2;runde++)
    Log(drots+string("  Spool-ID: ")+schwarz+spoolid);
  } // for (unsigned nachrnr=0; nachrnr<spdfp->size(); ++nachrnr) 
  for (uchar tr=0;tr<2;tr++) {
    char ***cerg;
    RS tellen(My,string("SELECT MAX(LENGTH(gettel3(")+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"')))"
        " FROM `" +spooltab+"`");
    while (cerg=tellen.HolZeile(),cerg?*cerg:0) {
      if (*(*cerg+0)) {
        My->tuerweitern(altspool,"telnr",atol(*(*cerg+0)),!obverb);
        My->tuerweitern(spooltab,"telnr",atol(*(*cerg+0)),!obverb);
      }
      break;
    }
    // hier wird die Telefonnummer aus dem Namen extrahiert
    RS tea(My,"UPDATE `"+altspool+"` "
        "SET telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"') "
        "WHERE telnr=''",ZDB);
    RS tel(My,"UPDATE `"+spooltab+"` "
        "SET telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"') "
        "WHERE telnr=''",ZDB);
  } //   for (uchar tr=0;tr<2;tr++)
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
void paramcl::logvorgaben()
{
#ifdef _WIN32
  logvz = "C:\\Dokumente und Einstellungen\\All Users\\Anwendungsdaten";
#elif linux
  logvz = "/var/log";
#endif
  logdname = meinname+".log";
  loggespfad=logvz+vtz+logdname;
  logdt=&loggespfad.front();
} // void paramcl::logvorgaben

// wird aufgerufen in: main
void paramcl::getcommandl0()
{
  Log(violetts+"getcommandl0()"+schwarz);
  // Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
  cgconf.init(41, "language","host","muser","mpwd","datenbank","obcapi","obhyla","hylazuerst","maxcapiv","maxhylav","cuser",
    "countrycode","citycode","msn","LongDistancePrefix","InternationalPrefix","LocalIdentifier",
    "cFaxUeberschrift","cklingelzahl","hmodem","hklingelzahl","maxdials",
    "gleichziel","ocri","ocra","zufaxenvz","wartevz","nichtgefaxtvz","empfvz","anfaxstr","ancfaxstr","anhfaxstr",
    "anstr","undstr","cronminut","logvz","logdname","obmodem","obfcard","sqlz","musterzahl");
  uchar plusverb=0;

  //  for(int i=argc-1;i>0;i--) KLA if (argv[i][0]==0) argc--; KLZ // damit fuer das Compilermakro auch im bash-script argc stimmt
  for(unsigned iru=0;iru<3;iru++) {
    switch (iru) {
      case 0:
        opts.push_back(/*2*/optioncl("lg","language", &Tx,T_sprachstr,&langu,psons,&cgconf,"language",&oblgschreib));
        cgconf.setzbemv("language",&Tx,T_sprachstr,1);
        opts.push_back(/*2*/optioncl("langu","sprache", &Tx,-1,&langu,psons));
        opts.push_back(/*2*/optioncl("lang","lingue", &Tx,-1,&langu,psons));
        break;
      case 1:
        opts.push_back(/*4*/optioncl("v","verbose", &Tx, T_Bildschirmausgabe_gespraechiger,&plusverb,1));
        loggespfad=logvz+vtz+logdname;
        logdt=&loggespfad.front();
        opts.push_back(/*2*/optioncl("lvz","logvz", &Tx, T_waehlt_als_Logverzeichnis_pfad_derzeit,&logvz, pverz,&cgconf,"logvz",&logvneu));
        opts.push_back(/*3*/optioncl("ld","logdname", &Tx, T_logdatei_string_im_Pfad, &logvz, T_wird_verwendet_anstatt, &logdname, psons,
           &cgconf,"logdname",&logdneu));
        opts.push_back(/*9*/optioncl("l","log",&Tx, T_protokolliert_ausfuehrlich_in_Datei, &loggespfad, T_sonst_knapper, &oblog,1));
        logdt=&loggespfad.front();
        opts.push_back(/*4*/optioncl("ldn","logdateineu", &Tx, T_logdatei_vorher_loeschen, &logdateineu, 1));
        break;
      case 2:
        opts.push_back(/*2*/optioncl("kd","konfdat", &Tx, T_verwendet_Kofigurationsdatei_string_anstatt,&konfdatname,pfile));
        break;
    } //     switch (iru)
    // hier wird die Befehlszeile ueberprueft:
    for(;optslsz<opts.size();optslsz++) {
      for(size_t i=0;i<argcmv.size();i++) {
        if (opts[optslsz].pruefpar(&argcmv,&i,&hilfe,Tx.lgn)) {
          if (iru==1) {
            if (plusverb) {obverb++;plusverb=0;}
            if (!obcapi) hylazuerst=1; else if (!obhyla) hylazuerst=0;
          } //           if (iru==1)
          if (opts[optslsz].kurz!="v") break;
        } // if (opts[optslsz].pruefpar(&argcmv,&i,&hilfe))
      } // for(size_t i=0;i<argcmv.size();i++) 
    } //     for(;optslsz<opts.size();optslsz++)
    optslsz=opts.size();
    if (!iru) {
      lgnzuw();
    }
  } // for(unsigned iru=0;iru<3;iru++)
  if (logvneu ||logdneu) {
    if (!logdname.empty()) {
      loggespfad=logvz+vtz+logdname;
      logdt=&loggespfad.front();
      // <<rot<<"logdt: "<<logdt<<endl;
      // <<rot<<"loggespfad: "<<loggespfad<<endl;
      //<<violett<<"logdname: "<<*cgconf.hole("logdname")<<schwarz<<endl;
    } //     if (!logdname.empty())
    obkschreib=1;
  } // if (logvneu ||logdneu) 
} // void paramcl::getcommandl0(int argc, char** argv)

// wird aufgerufen in: main
void paramcl::pruefmodem()
{
  Log(violetts+Tx[T_pruefmodem]+schwarz);
  svec rueck;
  // <<"pruefmodem 1 nach obcapi: "<<(int)obcapi<<endl;
  obmodem=0;
  cmd="find /sys/class/tty";
  systemrueck(cmd, obverb,oblog,&rueck);
  for(size_t i=0;i<rueck.size();i++) {
    struct stat entrydriv={0};
    if (!lstat(((rueck[i])+"/device/driver").c_str(),&entrydriv)) {
      string tty=base_name(rueck[i]);
      // ttyS0 erscheint auf Opensuse und Ubuntu konfiguriert, auch wenn kein Modem da ist
      if (tty!="ttyS0") {
        svec rue2;
        vector<errmsgcl> errv;
        string f0=schwarzs+"Modem "+blau+tty+schwarz+Tx[T_gibts];
        string f1=f0+Tx[T_nicht];
        errv.push_back(errmsgcl(0,f0));
        errv.push_back(errmsgcl(1,f1));
        if (!systemrueck("sudo stty -F /dev/"+tty+" time 10",obverb,oblog,&rue2,2,wahr,"",&errv)) {
          obmodem=1;
          modems<<tty;
          Log(string("Modem: ")+blau+tty+schwarz+Tx[T_gefunden]);
        } // if (!systemrueck("sudo stty -F /dev/"+tty+" >/dev/null 2>&1",obverb,oblog,&rue2)) 
      } // if (tty!="ttyS0") 
    } // if (!lstat(((rueck[i])+"/device/driver").c_str(),&entrydriv)) 
  } // for(size_t i=0;i<rueck.size();i++) 
  //  uchar modemumgesteckt=0;
  uchar schonda=0;
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
      if (obverb) {
        Log(string("modems[0]: ")+rot+modems[0]+schwarz);
        Log(string("hmodem:    ")+rot+hmodem+schwarz);
      }
      hmodem=modems[0];/*modemsumgesteckt=1;*/ 
      modemgeaendert=1;
    } //   if (modems.size()) if (!modems[0].empty()) if (modems[0]!=hmodem) 
  } // if (hmodem.empty()) 
  obmdgeprueft=1;
  if (!obmodem) {
    obhyla=0;
    Log(rots+Tx[T_Kein_Modem_gefunden]+schwarz);
  }
  // wenn zum Konfigurationszeitpunkt kein Modem drinsteckte, aber jetzt, dann rueckfragen
  if (obmodem && cgconf.hole("obmodem")=="0") {
   rzf=1;
  }
  // wenn nur obkschreib, dann noch nicht auf neu eingestecktes Modem reagieren
  if (rzf) {
    cgconf.setze("obmodem",obmodem?"1":"0");
  }
  cgconf.setzbemv("obmodem",&Tx,T_ob_ein_Modem_drinstak);
  Log(violetts+Tx[T_pruefmodem]+" Ende"+schwarz);
  // wvdialconf oder schneller: setserial -a /dev/tty*, mit baud_base: <!=0>  als Kriterium
} // void paramcl::pruefmodem()

void paramcl::pruefisdn()
{
  Log(violetts+Tx[T_pruefisdn]+schwarz);
  svec rueck;
  cmd="{ lspci 2>/dev/null || sudo lspci 2>/dev/null;}|grep -i 'isdn'";
  systemrueck(cmd, obverb,oblog,&rueck);
  // <<"pruefmodem 1 vor  obcapi: "<<(int)obcapi<<endl;
  if (rueck.size()) {
    Log(blaus+Tx[T_ISDN_Karte_gefunden]+schwarz+rueck[0]+blau+Tx[T_Setze]+Tx[T_mitCapi]+schwarz+Tx[T_aauf]+blau+"1.");
    obfcard=1;
  } else {
    Log(rots+Tx[T_Keine_ISDN_Karte_gefunden]+schwarz+Tx[T_mitCapi]+rot+Tx[T_aauf]+schwarz+"0.");
    obcapi=obfcard=0;
  }
  if (obverb) Log("obfcard: "+blaus+ltoan(obfcard));
  obfcgeprueft=1;
  // wenn zum Konfigurationszeitpunkt keine Fritzcard drinsteckte, aber jetzt, dann rueckfragen
  if (obfcard && cgconf.hole("obfcard")=="0") {
   rzf=1;
  }
  // wenn nur obkschreib, dann noch nicht auf neu eingesteckte Fritzcard reagieren
  if (rzf) {
    cgconf.setze("obfcard",obfcard?"1":"0");
  }
	/*
  string bemst; 
  svec bemv;
	Sprache altSpr=Tx.lgn;
	for(int akts=0;akts<Smax;akts++) KLA
		Tx.lgn=(Sprache)akts;
		bemst=Tx[T_ob_ein_Modem_drinstak];
    bemv<<bemst;
  KLZ //         for(int akts=0;akts<Smax;akts++)
	Tx.lgn=altSpr;
	*/
	cgconf.setzbemv("obfcard",&Tx,T_ob_eine_Fritzcard_drinstak);
} // void paramcl::pruefisdn()

// wird aufgerufen in: main, pruefhyla
// koennte auch im Fall eines entfernten Modems oder hylafax-Programms benoetigt werden
// sucht das Hylaverzeichnis und setzt varsphylavz darauf, return 0, wenn nicht gefunden dann varsphylavz="", return 1
// wird aufgerufen in: pruefhyla, main
// varsphylavz und hsendqvz festlegen
int paramcl::setzhylavz()
{
  Log(violetts+Tx[T_setzhylavz]+schwarz);
  // wird fruehestens in korrigierecapi benoetigt
  // varsphylavz wird benoetigt in: korrigierecapi, untersuchespool, hfaxsetup(pruefhyla), pruefhyla, hylaausgeb(untersuchespool,zeigweitere)
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
    const string hylacdat="/etc/init.d/hylafax";
    struct stat hstat={0};
    if (!lstat(hylacdat.c_str(),&hstat)) {
      confdat hylac(hylacdat,&hyconf,obverb);
    }
    if (!hyconf[1].wert.empty()) {
      //  if (cpplies(hylacdat,hylaconf,cs)) KLA
      varsphylavz=hyconf[1].wert;
      fundart=2;
    } else if (!hyconf[0].wert.empty()) {
      varsphylavz=hyconf[0].wert;
      fundart=2;
    } else {
      // 3) ... ansonsten schauen, welches Verzeichnis es gibt ...
      struct stat hstat={0},fstat={0};
      const char *hfax="/var/spool/hylafax", *ffax="/var/spool/fax";
      int hgibts=!lstat(hfax,&hstat), fgibts=!lstat(ffax,&hstat);
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
    } //     if (!hyconf[1].wert.empty())  else else 
    weiterpruefen=1;
  } // if (hrueck.size()) else 

  // falls nicht im systemd-Dienst gefunden, dann zuerst im praeferierten, dann in anderen Verzeichnissen pruefen, wo es ./bin/faxrecvd gibt 
  if (weiterpruefen) {
    //  if (lsys.getsys(obverb,oblog)==sus) varsphylavz="/var/spool/fax";
    //  else if (lsys.getsys(obverb,oblog)==deb) varsphylavz="/var/spool/hylafax";
    string testvz=varsphylavz;
    for(unsigned iru=0;iru<(sizeof moeglhvz/sizeof *moeglhvz)+1;iru++) {
      struct stat entryhyla={0};
      if (!lstat((testvz+testcmd).c_str(),&entryhyla)) {
        varsphylavz=testvz; 
        if (iru) fundart=6;
        break;
      } else if (iru==sizeof moeglhvz/sizeof *moeglhvz) {
        // obhyla=0 hier noch nicht, da setzhylavz auch einmal vor der Installation schon aufgerufen wird
        break; // kein Verzeichnis gefunden
      } //   else if (iru==sizeof moeglhvz/sizeof *moeglhvz)
      testvz=moeglhvz[iru];
    } //     for(unsigned iru=0;iru<(sizeof moeglhvz/sizeof *moeglhvz)+1;iru++)
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
    Log(string(Tx[T_hylafax_Verzeichnis])+blau+varsphylavz+schwarz+grund);
  } // if (obverb)
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
  Log(violetts+Tx[T_VorgbSpeziell]+schwarz);
  dbq="autofax";
  muser="user";
  citycode="8131";
  msn="999999";
  LocalIdentifier=Tx[T_MeiEinrichtung];
  cFaxUeberschrift=Tx[T_Mei_FaxUeberschrift];
  sqlz=sqlvz="0";
//  host="localhost"; // 'localhost' schon Vorgabe bei Definition
  zufaxenvz="/var/"+meinname+vtz+Tx[T_zufaxen];
  wvz="/var/"+meinname+vtz+Tx[T_warteauffax];
  nvz="/var/"+meinname+vtz+Tx[T_nichtgefaxt];
  empfvz="/var/"+meinname+vtz+Tx[T_empfvz];
  static zielmustercl zmi[]={zielmustercl("[Ss]pamfax","/var/autofax/spam"),zielmustercl("","/var/autofax/gesandt")}; // nur als Beispiel
  zmvp=zmi;
  zmvzn=sizeof zmi/sizeof *zmi;
} // void paramcl::VorgbSpeziell() 

// in VorgbAllg, pruefcapi
void paramcl::liescapiconf()
{
  Log(violetts+Tx[T_liescapiconf]+schwarz);
  svec rueck;
	const string moegl="find /etc/capisuite /usr/local/etc/capisuite -type f -name ";
  systemrueck(moegl+"fax.conf",obverb-2,oblog,&rueck);
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
      char buf[250]={0};
      if ((sscanf(cfaxconf.zn[--i].c_str(),"[%[^]]]",buf))>0) 
        if (strcasecmp(buf,"global")) {
          if (!cuser.empty()) {
           if (cuser==buf) {
            ncuser.clear();
            break;
           } //            if (cuser==buf)
          } //           if (!cuser.empty())
          if (ncuser.empty()) ncuser=buf; // nehme den letzten besten user
        } //         if (strcasecmp(buf,"global"))
    } //     for(size_t i=cfaxconf.zn.size();i>0;)
    if (cuser.empty()) 
      cuser=ncuser;
    if (cuser.empty()) {
      string benutzer=curruser();
      if (benutzer!="root")
       cuser=benutzer;
      hylazuerst=1;
    }
  } // which vik 2>/dev/null || which vi
	maxcdials=capiconf[2].wert; // 14.10.16
  if (capiconf[0].wert.empty()) {
    spoolcapivz="/var/spool/capisuite";
  }  else {           
    //  if (cpplies(cfaxconfdat,capiconf,ccs,&rest)) KLA
    spoolcapivz=capiconf[0].wert;
    cfaxuservz=capiconf[1].wert;
  } // if (capiconf[0].wert.empty()) else
  if (cfaxuservz.empty())
    cfaxuservz=spoolcapivz+"/users";
  // <<rot<<"cfaxuservz in Vorgallg: "<<cfaxuservz<<schwarz<<endl;

  rueck.clear();
  systemrueck(moegl+"capisuite.conf",obverb-2,oblog,&rueck);
  if (rueck.size()) {
    ccapiconfdat=rueck[0];
  }
  if (!ccapiconfdat.empty()) {
    uchar obneuer=0;
    struct stat cstat={0};
    static time_t lgelzeit=0; // Aenderungszeitpunkt der evtl. zuletzt eingelesenen ccapiconfdat
    time_t aktgelzeit;
    if (!lstat(ccapiconfdat.c_str(),&cstat)) { // <<rot<<ccapiconfdat<<" existiert!"<<schwarz<<endl;
      aktgelzeit=cstat.st_mtime;
      if (aktgelzeit>lgelzeit) {
        lgelzeit=aktgelzeit;
        obneuer=1;
      } //       if (aktgelzeit>lgelzeit)
    } // if (!lstat(ccapiconfdat.c_str(),&cstat)) 
    if (obneuer || !cconf.zahl) {
      if (!cconf.zahl) {
        cconf.init(3,"incoming_script","log_file","log_error");
      } else {
        cconf.reset();
      } //       if (!cconf.zahl) else
      confdat ccapic(ccapiconfdat,&cconf,obverb);
      if (!cuser.empty()) {
        for(size_t j=1;j<3;j++) {
          if (!cconf[j].wert.empty()) {
            struct stat statdat={0};
            if (!lstat(cconf[j].wert.c_str(),&statdat)) {
              setfaclggf(cconf[j].wert, falsch, 6, falsch,obverb,oblog);
            } //             if (!lstat(cconf[j].wert.c_str(),&statdat))
          } // if (!cconf[j].wert.empty()) 
        } // for(size_t j=1;j<3;j++) 
      } // if (!cuser.empty()) 
    } // if (obneuer || !cconf.zahl) 
  } // if (!ccapiconfdat.empty())

  if (!spoolcapivz.empty()) {
    cdonevz = mitvtz(spoolcapivz)+"done";
    cfailedvz = mitvtz(spoolcapivz)+"failed";
  } //   if (!spoolcapivz.empty())
} // void paramcl::liescapiconf()

// wird aufgerufen in: main
// allgemeine Vorgaben, fuer Deutschland
void paramcl::VorgbAllg()
{
  Log(violetts+Tx[T_VorgbAllg]+schwarz);
  liescapiconf();
  hylazuerst=0;
  // hmodemstr="ACM";
  maxcapiv="3";
  maxhylav="3";
  maxhdials="11";
  gleichziel=1;
  obocri=1;
  obocra=0;
  anfaxstr=Tx[T_an_Fax];
  ancfaxstr=Tx[T_an_cFax];
  anhfaxstr=Tx[T_an_hFax];
  anstr=Tx[T_an];
  undstr=Tx[T_und];
  countrycode="49";
  LongDistancePrefix="0";
  InternationalPrefix="00";
  cklingelzahl="1";
  hklingelzahl="2"; // muss mindestens 2 sein, um die Nr. des anrufenden zu uebertragen
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
  Log(violetts+Tx[T_pruefcvz]+schwarz+"ccfaxuservz: "+violett+cfaxuservz+schwarz);
  kuerzevtz(&cfaxuservz);
  pruefverz(cfaxuservz,obverb,oblog);
  cfaxusersqvz=cfaxuservz+vtz+cuser+"/sendq"; //  "/var/spool/capisuite/users/<user>/sendq";
  pruefverz(cfaxusersqvz,obverb,oblog);
  cfaxuserrcvz=cfaxuservz+vtz+cuser+"/received";
  // <<violett<<"cfaxuserrcvz: "<<cfaxuserrcvz<<schwarz<<endl;
  pruefverz(cfaxuserrcvz,obverb,oblog);
  pruefverz(cfaxuservz+vtz+"/autofaxarch",obverb,oblog);
  pruefverz(cfaxuservz+vtz+"/failed",obverb,oblog);
  pruefverz(cfaxuservz+vtz+"/sendq",obverb,oblog);

} // paramcl::pruefcvz

// wird aufgerufen in lieskonfein
void paramcl::setzzielmuster(confdat& afconf)
{
  if (!zmvzn || !zmvp) {
    zmvp= new zielmustercl{"","/var/"+meinname+"/ziel"};
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
  } //     for(int iru=0;;iru++) {

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
  Log(violetts+Tx[T_lieskonfein]+schwarz);
  if (konfdatname.empty()) konfdatname = aktprogverz()+".conf";
  /*
     static cppSchluess gconf[]={{"langu"},{"obcapi"},{"obhyla"},{"hylazuerst"},{"maxcapiv"},{"maxhylav"},{"cuser"},
     {"countrycode"},{"citycode"},{"msn"},{"LongDistancePrefix"},{"InternationalPrefix"},{"LocalIdentifier"},
     {"cFaxUeberschrift"},{"cklingelzahl"},{"hmodem"},{"hklingelzahl"},{"maxdials"},
     {"gleichziel"},{"ocri"},{"ocra"},{"zufaxenvz"},{"wartevz"},{"nichtgefaxtvz"},{"empfvz"},{"cronminut"},{"anfaxstr"},{"ancfaxstr"},{"anhfaxstr"},
     {"anstr"},{"undstr"},{"host"},{"muser"},{"mpwd"},{"datenbank"},{"logvz"},{"logdname"},{"sqlz"},{"musterzahl"}};
     cgconfp=gconf;
     gcs=sizeof gconf/sizeof*gconf;
   */
  // cgconf.init muss spaetetens am Anfang von getcommandl0 kommen
  if (1) {
    //  if (cpplies(konfdatname,gconf,gcs)) KLA
    // sodann werden die Daten aus gconf den einzelenen Klassenmitgliedsvariablen zugewiesen 
    // die Reihenfolge muss der in cgconf.init (in getcommandl0) sowie der in rueckfragen entsprechen
    rzf=0;
    unsigned lfd=0;
    confdat afconf(konfdatname,&cgconf,obverb); // hier werden die Daten aus der Datei eingelesen
    // wenn die Sprache noch nicht in der Kommandozeile zugewiesen wurde
    if (langu.empty()) {
      // und in der Konfigurationsdatei enthalten war 
      if (cgconf[lfd].gelesen) {
        // dann langu auf die Sprache aus der Konfigurationsdatei setzen
        cgconf[lfd].hole(&langu); 
        lgnzuw();
      } else rzf=1; // Sprache aus der Commandline geht vor Konfiguration
      // wenn die Sprache schon in der Kommandozeile festgelegt wurde
    } else {
      // ... und sich von der aus der Konfigurationsdatei unterscheidet ...
      if (cgconf[lfd].wert.compare(langu)) {
        cgconf[lfd].setze(&langu);
        // ... und der Aufruf nicht nur einmal geschehen sollte
        if (oblgschreib)
          obkschreib=1;
      } // if (cgconf[lfd].wert.compare(langu)) 
    } //     if (langu.empty())  else
    lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&host); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&muser); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) mpwd=XOR(string(cgconf[lfd].wert),pk); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&dbq); else rzf=1; lfd++;
    // <<"lieskonfein vor  obcapi: "<<(int)obcapi<<endl;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&obcapi); else rzf=1; lfd++;
    // <<"lieskonfein nach obcapi: "<<(int)obcapi<<endl;
    konfobcapi=obcapi;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&obhyla); else rzf=1; lfd++;
    konfobhyla=obhyla;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&hylazuerst); else rzf=1;} lfd++;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&maxcapiv); else rzf=1;} lfd++;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&maxhylav); else rzf=1;} lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cuser); else rzf=1; lfd++; // auch fuer samba
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&countrycode); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&citycode); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&msn); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&LongDistancePrefix); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&InternationalPrefix); else rzf=1; lfd++;
    if (obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&LocalIdentifier); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cFaxUeberschrift); else rzf=1;} lfd++;
    if (obcapi) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cklingelzahl); else rzf=1;} lfd++;
    if (obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&hmodem); else rzf=1;} lfd++;
    if (obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&hklingelzahl); else rzf=1;} lfd++;
    if (obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&maxhdials); else rzf=1;} lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&gleichziel); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&obocri); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&obocra); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&zufaxenvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&wvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&nvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&empfvz); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&anfaxstr); else rzf=1; lfd++;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&ancfaxstr); else rzf=1;} lfd++;
    if (obcapi && obhyla) {if (cgconf[lfd].gelesen) cgconf[lfd].hole(&anhfaxstr); else rzf=1;} lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&anstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&undstr); else rzf=1; lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&cronminut); else rzf=1; lfd++;
    if (logvneu) cgconf[lfd].setze(&logvz);
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&logvz); else rzf=1; lfd++;
    if (logdneu) cgconf[lfd].setze(&logdname);
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&logdname); else rzf=1; lfd++;
    // obmodem
    lfd++;
    // obfcard
    lfd++;
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&sqlz); else rzf=1; lfd++;
    setzsql(afconf);
    if (cgconf[lfd].gelesen) cgconf[lfd].hole(&zmz); else rzf=1; lfd++;
    setzzielmuster(afconf);
    loggespfad=logvz+vtz+logdname;
    logdt=&loggespfad.front();
  } else {
    rzf=1;
  } // (1) else
  if (nrzf) rzf=0;
	// Aufrufstatistik, um in zeigweitere die Dateien korrigieren zu koennen:
	// bei jedem 3. Aufruf einen Tag, bei jedem 3. Aufruf des Tages 3 Monate und des Monats unbefristet
	string zaehlerdatei=konfdatname+".zaehl";
  schlArr zschl; // Zaehlkonfiguration
	zschl.init(4,"aufrufe","lDatum","tagesaufr","monatsaufr");
	confdat zconf(zaehlerdatei,&zschl,obverb); // hier werden die Daten aus der Datei eingelesen
	if (zschl[0].gelesen) zschl[0].hole(&aufrufe);
	aufrufe++;
  zschl[0].setze(&aufrufe);
	if (zschl[2].gelesen) zschl[2].hole(&tagesaufr);
	if (zschl[3].gelesen) zschl[3].hole(&monatsaufr);
	if (zschl[1].gelesen) zschl[1].hole(&laufrtag);
  time_t jetzt=time(0);
	struct tm heute=*localtime(&jetzt);
	if (heute.tm_year!=laufrtag.tm_year || heute.tm_yday!=laufrtag.tm_yday) {
	 tagesaufr=0;
	}
	if (heute.tm_year!=laufrtag.tm_year || heute.tm_mon!=laufrtag.tm_mon) {
	 monatsaufr=0;
	}
	zschl[1].setze(&heute);
	tagesaufr++;
  zschl[2].setze(&tagesaufr);
	monatsaufr++;
  zschl[3].setze(&monatsaufr);
  mdatei f(zaehlerdatei,ios::out,0);
	if (f.is_open()) {
     zschl.aschreib(&f);
	}
} // void paramcl::lieskonfein()

// wird aufgerufen in: main
int paramcl::getcommandline()
{
  Log(violetts+"getcommandline()"+schwarz);
  //  uchar plusverb=0;
  opts.push_back(/*2*/optioncl("zvz","zufaxenvz", &Tx, T_faxt_die_Dateien_aus_pfad_anstatt,&zufaxenvz,pverz,&cgconf,"zufaxenvz",&obkschreib));
  opts.push_back(/*2*/optioncl("wvz","wartevz", &Tx, T_Dateien_warten_in_pfad_anstatt,&wvz,pverz,&cgconf,"wartevz",&obkschreib));
  opts.push_back(/*2*/optioncl("nvz","nichtgefaxtvz", &Tx, T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,&nvz,pverz,
        &cgconf,"nichtgefaxtvz",&obkschreib));
  opts.push_back(/*2*/optioncl("evz","empfvz", &Tx, T_Empfangsverzeichnis_fuer_Faxempfang,&empfvz,pverz,&cgconf,"empfvz",&obkschreib));
  opts.push_back(/*3*/optioncl("cm","cronminut", &Tx,T_Alle_wieviel_Minuten_soll,&meinname,T_aufgerufen_werden_0_ist_gar_nicht, &cronminut, pzahl, 
        &cgconf,"cronminut",&obkschreib));
  opts.push_back(/*4*/optioncl("capi","obcapi", &Tx, T_Capisuite_verwenden ,&obcapi,1,&cgconf,"obcapi",&obkschreib));
  //  opts.push_back(/*4*/optioncl("nocapi","keincapi", &Tx, T_Capisuite_nicht_verwenden,&obcapi,0,&cgconf,"obcapi",&obkschreib));
  opts.push_back(/*4*/optioncl("hyla","obhyla", &Tx, T_hylafax_verwenden,&obhyla,1,&cgconf,"obhyla",&obkschreib));
  //  opts.push_back(/*4*/optioncl("nohyla","keinhyla", &Tx, T_hylafax_nicht_verwenden,&obhyla,0,&cgconf,"obhyla",&obkschreib));
  opts.push_back(/*4*/optioncl("cz","capizuerst", &Tx, T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken,&hylazuerst,0,&cgconf,"hylazuerst",&obkschreib));
  opts.push_back(/*4*/optioncl("hz","hylazuerst", &Tx, T_versuche_faxe_zuerst_ueber_hylafax_wegzuschicken,&hylazuerst,1,&cgconf,"hylazuerst",&obkschreib));
  //  opts.push_back(optioncl("hms","hylamodemstring",&Tx, T_sucht_nach_dev_tty_string_als_Modem_mit_string_anstatt,&hmodemstr,psons));
  opts.push_back(/*2*/optioncl("mod","hmodem",&Tx, T_Fuer_Hylafax_verwendetes_Modem,&hmodem,psons,&cgconf,"hmodem",&hylazukonf));
  opts.push_back(/*2*/optioncl("mc","maxcapiv",&Tx, T_nach_zahl_Versuchen_Capisuite_wird_Hylafax_versucht,&maxcapiv,pzahl,&cgconf,"maxcapiv",&obkschreib));
  opts.push_back(/*2*/optioncl("mh","maxhylav",&Tx, T_nach_zahl_Versuchen_Hylafax_wird_Capisuite_verwendet,&maxhylav,pzahl,&cgconf,"maxhylav",&obkschreib));
  opts.push_back(/*2*/optioncl("cuser","cuser",&Tx, T_verwendet_fuer_Capisuite_Samba_den_Linux_Benutzer_string_anstatt,&cuser,psons,
        &cgconf,"cuser",&capizukonf));
  opts.push_back(/*2*/optioncl("ckzl","cklingelzahl",&Tx, T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt,&cklingelzahl,pzahl,
        &cgconf,"cklingelzahl",&capizukonf));
  opts.push_back(/*2*/optioncl("hkzl","hklingelzahl",&Tx, T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt,&hklingelzahl,pzahl,
        &cgconf,"hklingelzahl",&hylazukonf));
  opts.push_back(/*2*/optioncl("md","maxdials",&Tx, T_Zahl_der_Wahlversuche_in_Hylafax,&maxhdials,pzahl,
        &cgconf,"maxdials",&hylazukonf));
  opts.push_back(/*4*/optioncl("gz","gleichziel", &Tx, T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,&gleichziel,1,
        &cgconf,"gleichziel",&obkschreib));
  opts.push_back(/*4*/optioncl("ocri","ocri", &Tx, T_Text_aus_empfangenen_Faxen_wird_ermittelt,&obocri,1, &cgconf,"ocri",&obkschreib));
  //  opts.push_back(/*4*/optioncl("noocri","noocri", &Tx, T_Text_aus_empfangenen_Faxen_wird_nicht_ermittelt,&obocri,0, &cgconf,"ocri",&obkschreib));
  opts.push_back(/*4*/optioncl("ocra","ocra", &Tx, T_Text_aus_gesandten_Bildern_wird_ermittelt,&obocra,0, &cgconf,"ocra",&obkschreib));
  //  opts.push_back(/*4*/optioncl("noocra","ocra", &Tx, T_Text_aus_gesandten_Bildern_wird_nicht_ermittelt,&obocra,0, &cgconf,"ocra",&obkschreib));
  //  opts.push_back(/*4*/optioncl("1ocri","1ocri", &Tx, T_Text_aus_empfangenen_Faxen_wird_bei_diesem_Aufruf_ermittelt,&obocri,1));
  //  opts.push_back(/*4*/optioncl("1noocri","1noocri", &Tx, T_Text_aus_empfangenen_Faxen_wird_bei_diesem_Aufruf_nicht_ermittelt,&obocri,0));
  //  opts.push_back(/*4*/optioncl("1ocra","1ocra", &Tx, T_Text_aus_gesandten_Bildern_wird_bei_diesem_Aufruf_ermittelt,&obocra,1));
  //  opts.push_back(/*4*/optioncl("1noocra","1ocra", &Tx, T_Text_aus_gesandten_Bildern_wird_bei_diesem_Aufruf_nicht_ermittelt,&obocra,0));
  opts.push_back(/*2*/optioncl("afs","anfaxstr",&Tx, T_faxnr_wird_hinter_string_erwartet_statt_hinter,&anfaxstr,psons,&cgconf,"anfaxstr",&obkschreib));
  opts.push_back(/*2*/optioncl("acfs","ancfaxstr",&Tx, T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter,&ancfaxstr,psons,
        &cgconf,"ancfaxstr",&obkschreib));
  opts.push_back(/*2*/optioncl("ahfs","anhfaxstr",&Tx, T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter,&anhfaxstr,psons,
        &cgconf,"anhfaxstr",&obkschreib));
  opts.push_back(/*2*/optioncl("as","anstr",&Tx, T_Adressatenname_wird_hinter_string_erwartet_statt_hinter,&anstr,psons,&cgconf,"anstr",&obkschreib));
  opts.push_back(/*2*/optioncl("us","undstr",&Tx, T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt,&undstr,psons,
        &cgconf,"undstr",&obkschreib));
  opts.push_back(/*2*/optioncl("host","host",&Tx, T_verwendet_die_Datenbank_auf_Host_string_anstatt_auf,&host,psons,&cgconf,"host",&obkschreib));
  opts.push_back(/*2*/optioncl("muser","muser",&Tx, T_verwendet_fuer_MySQL_MariaDB_den_Benutzer_string_anstatt,&muser,psons,&cgconf,"muser",&obkschreib));
  opts.push_back(/*2*/optioncl("mpwd","mpwd",&Tx, T_verwendet_fuer_MySQL_MariaDB_das_Passwort_string_anstatt,&mpwd,psons,&cgconf,"mpwd",&obkschreib));
  opts.push_back(/*2*/optioncl("db","datenbank",&Tx, T_verwendet_die_Datenbank_string_anstatt,&dbq,psons,&cgconf,"datenbank",&obkschreib));
  //  opts.push_back(optioncl("l","log", &Tx, T_protokolliert_ausfuehrlich_in_Datei+drot+loggespfad+schwarz+Tx[T_sonst_knapper],&oblog,1));
  //  logdt=&loggespfad.front();
  //  opts.push_back(optioncl("lvz","logvz",&Tx, T_waehlt_als_Logverzeichnis_pfad_anstatt,&logvz,pverz));
  //  opts.push_back(optioncl("ld","logdname",&Tx, T_logdatei_string_im_Pfad+drot+logvz+schwarz+Tx[T_wird_verwendet_anstatt],&logdname,psons));
  //  opts.push_back(optioncl("ldn","logdateineu", &Tx, T_logdatei_vorher_loeschen,&logdateineu,1));
  //  opts.push_back(optioncl("v","verbose", &Tx, T_Bildschirmausgabe_gespraechiger,&plusverb,1));
  opts.push_back(/*4*/optioncl("sqlv","sql-verbose", &Tx, T_Bildschirmausgabe_mit_SQL_Befehlen,&ZDB,255));
  opts.push_back(/*4*/optioncl("rf","rueckfragen", &Tx, T_alle_Parameter_werden_abgefragt_darunter_einige_hier_nicht_gezeigte,&rzf,1));
  opts.push_back(/*4*/optioncl("norf","keinerueckfragen", &Tx, T_keine_Rueckfragen_zB_aus_Cron,&nrzf,1));
  opts.push_back(/*4*/optioncl("loef","loeschefax", &Tx, T_ein_Fax_nach_Rueckfrage_loeschen,&loef,1));
  opts.push_back(/*6*/optioncl("loew","loeschewaise", &Tx, T_Eintraege_aus, &spooltab, 
        T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist, &loew,1));
  opts.push_back(/*6*/optioncl("loea","loescheallew", &Tx, T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus, &spooltab, T_loeschen, &loea,1));
  //  opts.push_back(optioncl("loee","loescheempf", &Tx, T_empfangene_Dateien_loeschen_die_nicht_verarbeitet_werden_koennen,&loee,1));
  opts.push_back(/*6*/optioncl("kez","korrerfolgszeichen", &Tx, T_in_der_Datenbanktabelle, &touta, T_wird_das_Erfolgszeichen_korrigiert, &kez,1));
  opts.push_back(/*6*/optioncl("bwv","bereinigewv", &Tx, T_Dateien_aus_Warteverzeichnis_gegen, &touta, T_pruefen_und_verschieben, &bwv,1));
  opts.push_back(/*4*/optioncl("st","stop", &Tx, T_autofax_anhalten,&anhl,1));
  opts.push_back(/*6*/optioncl("lista","listarchiv", &Tx, T_listet_Datensaetze_aus, &touta, T_mit_Erfolgskennzeichen_auf, &lista,1));
  opts.push_back(/*6*/optioncl("listf","listfailed", &Tx, T_listet_Datensaetze_aus, &touta, T_ohne_Erfolgskennzeichen_auf, &listf,1));
  opts.push_back(/*6*/optioncl("listi","listinca", &Tx, T_listet_Datensaetze_aus, &tinca, T__auf, &listi,1));
  opts.push_back(/*4*/optioncl("listw","listwart", &Tx, T_listet_wartende_Faxe_auf, &listw,1));
  opts.push_back(/*3*/optioncl("s","suche",&Tx, T_suche_in_verarbeiteten_Faxen_nach,&nix,T_MAX,&suchstr,psons));
  opts.push_back(/*2*/optioncl("n","dszahl", &Tx, T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt, &dszahl,pzahl));
  opts.push_back(/*4*/optioncl("info","version", &Tx, T_Zeigt_die_Programmversion_an, &zeigvers,1));
  opts.push_back(/*4*/optioncl("vi","vi", &Tx, T_Konfigurationsdatei_editieren, &obvi,1));
  opts.push_back(/*4*/optioncl("h","hilfe", &Tx, T_Zeigt_diesen_Bildschirm_an, &hilfe,1));
  opts.push_back(/*4*/optioncl("?","help", &Tx, -1, &hilfe,1));

  //   string altlogdname(logdname);
  //  string altckzl(cklingelzahl);
  //  string althkzl(hklingelzahl);

  // hier wird die Befehlszeile ueberprueft:
  for(;optslsz<opts.size();optslsz++) {
    for(size_t i=0;i<argcmv.size();i++) {
      if (opts[optslsz].pruefpar(&argcmv,&i,&hilfe,Tx.lgn)) {
        break;
      }
    } // for(size_t i=0;i<argcmv.size();i++) 
  } //   for(;optslsz<opts.size();optslsz++)
  if (nrzf) rzf=0;
  for(size_t i=0;i<argcmv.size();i++) {
    if (!argcmv[i].agef) {
      ::Log(rots+"Parameter: "+gruen+argcmv[i].argcs+rot+Tx[T_nicht_erkannt]+schwarz,1,1);
      hilfe=1;
    }
  } //   for(size_t i=0;i<argcmv.size();i++)
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

  if (capizukonf || hylazukonf)
    obkschreib=1;

  Log(string(Tx[T_Fertig_mit_Parsen_der_Befehlszeile])+(obkschreib?Tx[T_ja]:Tx[T_nein]));
  // Ausgabe der Hilfe
  if (hilfe) {
    cout<<blau<<Tx[T_Gebrauch]<<drot<<meinname<<" [-<opt>|--<longopt> [<content>]] ..."<<schwarz<<endl; 
    cout<<blau<<Tx[T_Faxt_Dateien_aus_Verzeichnis_pfad_die]<<anfaxstr<<
      Tx[T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie]
      <<drot<<dbq<<blau<<Tx[T_Tabellen]<<drot<<touta<<blau<<"`,`"<<drot<<spooltab<<blau<<Tx[T_aein]<<schwarz<<endl;
    cout<<blau<<Tx[T_Optionen_die_nicht_gespeichert_werden]<<schwarz<<endl;
    for(size_t j=0;j<opts.size();j++) {
      if (!opts[j].obschreibp)
        opts[j].hilfezeile(Tx.lgn);
    } //     for(size_t j=0;j<opts.size();j++)
    cout<<blau<<Tx[T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden]<<schwarz<<endl;
    for(size_t j=0;j<opts.size();j++) {
      if (opts[j].obschreibp)
        opts[j].hilfezeile(Tx.lgn);
    } //     for(size_t j=0;j<opts.size();j++)
    return 0;
  } // if (hilfe)
  return 1;
} // int paramcl::getcommandline(int argc, char** argv)

// wird aufgerufen in: main
void paramcl::rueckfragen()
{
  Log(violetts+Tx[T_rueckfragen]+schwarz);
  const string nix;
  if (rzf) {
    int lfd=-1;
    char *locale = setlocale(LC_CTYPE,"");
    if (langu.empty()) if (locale) if (strchr("defi",locale[0])) langu=locale[0];
    vector<string> sprachen={"e","d"/*,"f","i"*/};
    if (cgconf[++lfd].wert.empty() || rzf) {
      langu=Tippstrings(sprachstr.c_str()/*"Language/Sprache/Lingue/Lingua"*/,&sprachen, &langu);
      lgnzuw();
      cgconf[lfd].setze(&langu);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      host=Tippstring(Tx[T_Host_fuer_MySQL_MariaDB_Datenbank],&host);
      cgconf[lfd].setze(&host);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      string Frage=Tx[T_Benutzer_fuer_MySQL_MariaDB];
      muser=Tippstring(Frage.c_str(),&muser);
      cgconf[lfd].setze(&muser);
    }
		if (cgconf[++lfd].wert.empty() || rzf) {
			string mpw2;
			mpwd.clear();
			while (1) {
				do {
					mpwd=Tippstring(string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Txd[T_fuer_Benutzer]+dblau+muser+schwarz+"'",&mpwd);
				} while (mpwd.empty());
				mpw2=Tippstring(string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Txd[T_fuer_Benutzer]+dblau+muser+schwarz+"'"+" ("+Txk[T_erneute_Eingabe]+")",&mpw2);
				if (mpwd==mpw2) break;
			} //         while (1)
			while (mpwd.empty());
			string pwdstr=XOR(mpwd,pk);
			cgconf[lfd].setze(&pwdstr);
		}
    if (cgconf[++lfd].wert.empty() || rzf) {
      dbq=Tippstring(string(Tx[T_Datenbankname_fuer_MySQL_MariaDB_auf])+host+"'",&dbq);
      cgconf[lfd].setze(&dbq);
    }
    //      for(size_t zkt=0;zkt<sqlzn;zkt++) KLA
    //        <<"zkt: "<<blau<<zkt<<schwarz<<", sqlconf["<<zkt<<"]: "<<rot<<sqlconf[zkt].wert<<schwarz<<endl;
    //        <<gruen<<(sqlconf[zkt].wert.empty()?sqlconfvp[zkt].wert:sqlconf[zkt].wert)<<schwarz<<endl;
    //       KLZ

    /*
       if (cgconf[++lfd].wert.empty() || rzf) KLA
       string  nzmz=Tippzahl(Tx[T_Zahl_der_Verzeichnisse_fuer_erfolgreich_verschickte_Faxe],&zmz);
       size_t nzmzn;
       while (1) KLA
       nzmzn=atol(nzmz.c_str());
       if (nzmzn>0) break;
       nzmz="1";
       KLZ
       cgconf[lfd].setze(&nzmz);
    // zmconfp=nzmconfp;
    // static cppSchluess *nzmconfp= new cppSchluess[nzmzn+nzmzn];
    zmconf.neu(nzmzn+nzmzn);
    for(size_t akt=0;akt<(nzmzn<zmzn?nzmzn:zmzn);akt++) KLA
    if (zmconf[2*akt].wert.empty())
    zmconf[2*akt].wert=zmp[akt].holmuster();
    if (zmconf[2*akt+1].wert.empty())
    zmconf[2*akt+1].wert=zmp[akt].ziel;
    KLZ
    while (1) KLA
    int fehler=0;
    for(size_t akt=0;akt<nzmzn;akt++) KLA
    string zwi=Tippstring(string("Zielmuster Nr. ")+ltoan(akt+1)+Tx[T_beim_letzten_nichts_eingeben],&zmconf[2*akt].wert);
    zmconf[2*akt].name=string("ZMMuster_")+ltoan(akt+1);
    if (akt==nzmzn-1) zwi.clear(); // das letzte Muster muss leer sein, damit jede Datei irgendwo hinkommt
    zmconf[2*akt].setze(&zwi);
    zwi=Tippstring(string("Zielverzeichnis Nr. ")+ltoan(akt+1),&zmconf[2*akt+1].wert);
    zmconf[2*akt+1].name=string("ZMZiel_")+ltoan(akt+1);
    zmconf[2*akt+1].setze(&zwi);
    KLZ
    zmp=new zielmustercl[nzmzn];
    for(uint imu=0;imu<nzmzn;imu++) KLA
    zmp[imu].setzemuster(zmconf[2*imu].wert);
    fehler+=zmp[imu].kompilier();
    zmp[imu].ziel=zmconf[2*imu+1].wert;
    KLZ
    if (!fehler) break;
    KLZ
    zmz=nzmz;
    zmzn=nzmzn;
    KLZ // if (cgconf[++lfd].wert.empty() || rzf) 
     */
    // <<"rueckfragen 1 vor  obcapi: "<<(int)obcapi<<endl;
    if (cgconf[++lfd].wert.empty() || rzf) {
      if (!obfcgeprueft) pruefisdn();
      if (obfcard) {
        obcapi=Tippob(Tx[T_Soll_die_Capisuite_verwendet_werden],obcapi?Tx[T_j_af]:"n");
      } else {
        obcapi=0;
      }
      cgconf[lfd].setze(&obcapi);
    } //     if (cgconf[++lfd].wert.empty() || rzf)
    // <<"rueckfragen 1 nach obcapi: "<<(int)obcapi<<endl;
    if (cgconf[++lfd].wert.empty() || rzf) {
      if (!obmdgeprueft) pruefmodem();
      if (obmodem) {
        obhyla=Tippob(Tx[T_Soll_Hylafax_verwendet_werden],obhyla?Tx[T_j_af]:"n");
      } else {
        obhyla=0;
      }
      cgconf[lfd].setze(&obhyla);
    } //     if (cgconf[++lfd].wert.empty() || rzf)
    if (obcapi) {
      if (obhyla) {
        if (cgconf[++lfd].wert.empty() || rzf) {
          hylazuerst=!Tippob(Tx[T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden],hylazuerst?"n":Tx[T_j_af]);
          cgconf[lfd].setze(&hylazuerst);
        }
        if (cgconf[++lfd].wert.empty() || rzf) {
          maxcapiv=Tippzahl(Tx[T_Zahl_der_Versuche_in_Capisuite_bis_hylafax_eingeschaltet_wird],maxcapiv.c_str());
          cgconf[lfd].setze(&maxcapiv);
        }
        if (cgconf[++lfd].wert.empty() || rzf) {
          maxhylav=Tippzahl(Tx[T_Zahl_der_Versuche_in_hylafax_bis_Capisuite_eingeschaltet_wird],maxhylav.c_str());
          cgconf[lfd].setze(&maxhylav);
        }
        // also: obcapi, aber nicht obhyla
      } else {
        lfd+=3;
        hylazuerst=0;
      }
    } else {
      lfd+=3; // nicht obcapi, aber obhyla kaeme hier
      hylazuerst=1;
    } // if (obcapi) else
    if (cgconf[++lfd].wert.empty() || rzf) {
      //        string bliste, tmpcuser;
      vector<string> benutzer;
      cmd="cat /etc/passwd | grep /home/ | cut -d':' -f 1";
      systemrueck(cmd,obverb,oblog,&benutzer);
			if (benutzer.size()>1) for(size_t i=benutzer.size();i;) {
				--i;
				if (benutzer[i]=="syslog"||benutzer[i]=="ntp") {
					benutzer.erase(benutzer.begin()+i);
				}
			} // for(size_t i=benutzer.size();i;)
			for(size_t i=0;i<benutzer.size();i++) {
				//          bliste+=benutzer[i];
				//          if (i<benutzer.size()-1) bliste+=",";
				if (cuser.empty()) cuser=benutzer[i]; // Vorgabe
			}
			/*
				 string Frage=string("Linux-Benutzer fuer Capisuite (")+bliste+"):";
				 do KLA
				 tmpcuser=Tippstring(Frage.c_str(),&cuser);
				 KLZ while (benutzer.size() && bliste.find(tmpcuser)==string::npos && 
				 tmpcuser.find(',')==string::npos); // nur vorhandene User akzeptieren
				 cuser=tmpcuser;
			 */
			cuser=Tippstrings(obcapi?Tx[T_Linux_Benutzer_fuer_Capisuite_Samba]:Tx[T_Linux_Benutzer_fuer_Samba],&benutzer,&cuser);
			cgconf[lfd].setze(&cuser);
		} // if (cgconf[++lfd].wert.empty() || rzf) 
		if (cgconf[++lfd].wert.empty() || rzf) {
			countrycode=Tippstring(Tx[T_Eigene_Landesvorwahl_ohne_plus_oder_00],&countrycode);
			cgconf[lfd].setze(&countrycode);
		}
		if (cgconf[++lfd].wert.empty() || rzf) {
			citycode=Tippstring(Tx[T_Eigene_Ortsvorwahl_ohne_0],&citycode);
			cgconf[lfd].setze(&citycode);
		}

		if (obcapi || obhyla) {
			if (cgconf[++lfd].wert.empty() || rzf) {
				do {
					msn=Tippstring(Tx[T_Eigene_MSN_Faxnummer_ohne_Vorwahl],&msn);
				} while (msn.empty()||!isnumeric(msn)||isneun(msn));
				cgconf[lfd].setze(&msn);
			}
    } else {
      lfd++; 
    } //     if (obcapi || obhyla)

    if (cgconf[++lfd].wert.empty() || rzf) {
      LongDistancePrefix=Tippstring(Tx[T_Praefix_fuer_ausserorts_zB_0],&LongDistancePrefix);
      cgconf[lfd].setze(&LongDistancePrefix);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      InternationalPrefix=Tippstring(Tx[T_Praefix_fuer_das_Ausland_zB_00],&InternationalPrefix);
      cgconf[lfd].setze(&InternationalPrefix);
    }
    if (obhyla) {
      if (cgconf[++lfd].wert.empty() || rzf) {
        LocalIdentifier=Tippstring(Tx[T_Hylafax_bis_10_Buchstabe_fuer_eigenen_Namen],&LocalIdentifier);
        cgconf[lfd].setze(&LocalIdentifier);
      }
    } else {
      lfd++;
    }
    if (obcapi) {
      if (cgconf[++lfd].wert.empty() || rzf) {
        cFaxUeberschrift=Tippstring(Tx[T_Capisuite_bis_20_Buchstaben_fuer_eigenen_Namen],&cFaxUeberschrift);
        cgconf[lfd].setze(&cFaxUeberschrift);
      }
      if (cgconf[++lfd].wert.empty() || rzf) {
        cklingelzahl=Tippzahl(Tx[T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt],cklingelzahl.c_str());
        cgconf[lfd].setze(&cklingelzahl);
      }
    } else {
      lfd+=2; // nicht obcapi, aber obhyla kaeme hier
    } //     if (obcapi) else

    if (obhyla) {
      if (cgconf[++lfd].wert.empty() || rzf) {
        //        hmodem=Tippstrings(Tx[T_Fuer_Hylafax_verwendetes_Modem],&modems,hmodem.empty()?&modems[0]:&hmodem);
        if (hmodem.empty()) hmodem=modems[0];
        hmodem=Tippstrings(Tx[T_Fuer_Hylafax_verwendetes_Modem],&modems,&hmodem);
        cgconf[lfd].setze(&hmodem);
      }
      if (cgconf[++lfd].wert.empty() || rzf) {
        hklingelzahl=Tippzahl(Tx[T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt],hklingelzahl.c_str());
        cgconf[lfd].setze(&hklingelzahl);
      }
      if (cgconf[++lfd].wert.empty() || rzf) {
        maxhdials=Tippzahl(Tx[T_Zahl_der_Wahlversuche_in_Hylafax],maxhdials.c_str());
        cgconf[lfd].setze(&maxhdials);
      }
    } else {
      lfd+=3;
      hylazuerst=0;
    } //     if (obhyla) else

    if (cgconf[++lfd].wert.empty() || rzf) {
      gleichziel=Tippob(Tx[T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden],gleichziel?Tx[T_j_af]:"n");
      cgconf[lfd].setze(&gleichziel);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      obocri=Tippob(Tx[T_soll_Text_in_empfangenen_Faxen_mit_OCR_gesucht_werden],obocri?Tx[T_j_af]:"j");
      cgconf[lfd].setze(&obocri);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      obocra=Tippob(Tx[T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden],obocra?Tx[T_j_af]:"n");
      cgconf[lfd].setze(&obocra);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      zufaxenvz=Tippverz(Tx[T_Verzeichnis_mit_zu_faxenden_Dateien],&zufaxenvz);
      cgconf[lfd].setze(&zufaxenvz);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      wvz=Tippverz(Tx[T_Verzeichnis_mit_wartenden_Dateien],&wvz);
      cgconf[lfd].setze(&wvz);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      nvz=Tippverz(Tx[T_Verzeichnis_mit_gescheiterten_Dateien],&nvz);
      cgconf[lfd].setze(&nvz);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      empfvz=Tippverz(Tx[T_Verzeichnis_fuer_empfangene_Faxe],&empfvz);
      cgconf[lfd].setze(&empfvz);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      anfaxstr=Tippstring(Tx[T_Buchstabenfolge_vor_erster_Faxnummer],&anfaxstr);
      cgconf[lfd].setze(&anfaxstr);
    }

    if (obcapi && obhyla) {
      if (cgconf[++lfd].wert.empty() || rzf) {
        ancfaxstr=Tippstring(Tx[T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Capisuite],&ancfaxstr);
        cgconf[lfd].setze(&ancfaxstr);
      }
      if (cgconf[++lfd].wert.empty() || rzf) {
        anhfaxstr=Tippstring(Tx[T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Hylafax],&anhfaxstr);
        cgconf[lfd].setze(&anhfaxstr);
      }
    } else {
      lfd+=2; 
    } //     if (obcapi || obhyla)

    if (cgconf[++lfd].wert.empty() || rzf) {
      anstr=Tippstring(Tx[T_Buchstabenfolge_vor_erstem_Adressaten],&anstr);
      cgconf[lfd].setze(&anstr);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      undstr=Tippstring(Tx[T_Buchstabenfolge_vor_weiterem_Adressaten_sowie_weiterer_Faxnummer],&undstr);
      cgconf[lfd].setze(&undstr);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      cronminut=Tippzahl(Tx[T_Alle_wieviel_Minuten_soll]+meinname+Tx[T_aufgerufen_werden_0_ist_gar_nicht],&cronminut);
      cgconf[lfd].setze(&cronminut);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      logvz=Tippverz(Tx[T_Logverzeichnis],&logvz);
      cgconf[lfd].setze(&logvz);
    }
    if (cgconf[++lfd].wert.empty() || rzf) {
      logdname=Tippstring(Tx[T_Logdateiname],&logdname);
      cgconf[lfd].setze(&logdname);
    }
    loggespfad=string(logvz)+vtz+logdname;
    logdt=&loggespfad.front();

    // obmodem
    ++lfd;
    // obfcard
    ++lfd;

    if (cgconf[++lfd].wert.empty() || rzf) {
      size_t nsqlzn=0;
      vector<cppSchluess*> sqlv; 
      size_t aktsp=0;
      for(size_t akt=0;;akt++) {
        const string *vorgabe=
          akt<sqlzn?
          (sqlconf[akt].wert.empty()?&sqlconfv[akt].wert:&sqlconf[akt].wert): // wird in auswert zurueckgesetzt
          akt<sqlvzn?
          &sqlconfv[akt].wert:
          &nix;
        string zwi;
        while (1) {
          zwi=Tippstring(string(Tx[T_SQL_Befehl_Nr])+ltoan(akt+1)+(vorgabe->empty()?
                Tx[T_faxnr_wird_ersetzt_mit_der_Faxnr]:
                Tx[T_Strich_ist_SQL_Befehl_loeschen_faxnr_wird_ersetzt_mit_der_Faxnr]),
              vorgabe);
          if (zwi=="-") zwi.clear();
          if (zwi.empty()) {
            break;
          } else {
            svec dben=holdbaussql(zwi);
            // <<"dben.size(): "<<(int)dben.size()<<endl;
            uchar dbda=1;
            if (!dben.size()) {
              if (Tippob(string(Tx[T_In])+rot+zwi+blau+Tx[T_keine_Datenbank_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) continue;
              dbda=0;
            } else { // if (!dben.size()) 
              uchar nochmal=0;
              for(size_t i=0;i<dben.size();i++) {
                // <<"i: "<<blau<<i<<rot<<": "<<dben[i]<<schwarz<<endl;
                if (pruefDB(dben[i])) {
                  dbda=0;
                  if (Tippob(string(Tx[T_Datenbank])+rot+dben[i]+blau+Tx[T_nicht_ermittelbar_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) {
                    nochmal=1;
                    break;
                  } // if (strchr("jyJYoOsS",(int)erg)) 
                } // if (pruefDB(dben[i])) 
              } // for(size_t i=0;i<dben.size();i++) 
              if (nochmal) continue;     
            } // if (!dben.size()) 
            if (dbda) {
              if (zwi.find("&&faxnr&&")==string::npos) {
                if (Tippob(string(Tx[T_In])+rot+zwi+blau+Tx[T_keinmal_faxnr_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) continue;
              } else {
                RS rtest(this->My,ersetzAllezu(zwi,"&&faxnr&&","9999")); // (const char*)trimfaxnr));
                if (rtest.obfehl) {
                  if (Tippob(string(Tx[T_In])+rot+zwi+blau+Tx[T_koennte_ein_SQL_Fehler_sein_Wollen_Sie_den_SQL_Befehl_neu_eingeben])) continue;
                } // if (rtest.obfehl)
              } // if (zwi.find("&&faxnr&&")==string::npos) 
            } // if (dbda)
          } // if (zwi.empty()) else
          break;
        } // while (1)
        if (zwi.empty()) {
          if (akt>sqlzn && akt >sqlvzn) akt--;
        } else {
          // hier Sql-Dateien pruefen
          cppSchluess* neuS=new cppSchluess;
          neuS->name=string("SQL_")+ltoan(++aktsp);
          neuS->wert=zwi;
          sqlv.push_back(neuS);
          nsqlzn++;
        } // if (zwi.empty()) else
        if (akt>=sqlzn && akt>=sqlvzn) {
          if (!Tippob(Tx[T_Wolle_Sie_noch_einen_SQL_Befehl_eingeben],Tx[T_j_af])) break;
        }
      } // for(size_t akt=0;;akt++) 
      string nsqlz=ltoan(nsqlzn);
      cgconf[lfd].setze(&nsqlz);
      sqlzn=nsqlzn;
      /*
      // Vektor in Array umwandeln
      static cppSchluess *nsqlconfp = new cppSchluess[sqlv.size()];
      for(size_t sqli=0;sqli<sqlv.size();sqli++) KLA
      nsqlconfp[sqli]=*sqlv[sqli];
      KLZ
      sqlconfp=nsqlconfp;
      static schlArr *nsqlconfp = new schlArr(&sqlv);
      sqlconfp=nsqlconfp;
       */
      sqlconf.init(&sqlv);
    } // if (cgconf[++lfd].wert.empty() || rzf) 

    vector<cppSchluess*> zmv; 
    size_t akt=0;
    for(;;akt++) {
      cppSchluess* neuS=new cppSchluess;
      neuS->name=string("ZMMuster_")+ltoan(akt+1);
      neuS->wert=Tippstring(string(Tx[T_Zielmuster_Nr])+ltoan(akt+1)+Tx[T_beim_letzten_nichts_eingeben],(akt<zmzn)?&zmp[akt].holmuster():&nix);
      if (neuS->wert=="-") neuS->wert.clear();
      uchar obabbrech=(neuS->wert.empty()); // das letzte Muster muss leer sein, damit jede Datei irgendwo hinkommt
      zmv.push_back(neuS);
      neuS=new cppSchluess;
      neuS->name=string("ZMZiel_")+ltoan(akt+1);
      neuS->wert=Tippstring(string(Tx[T_Zielverzeichnis_Nr])+ltoan(akt+1),(akt<zmzn)?&zmp[akt].ziel:&nix);
      zmv.push_back(neuS);
      if (obabbrech) break;
    } //     for(;;akt++)
    zmconf.init(&zmv);
    string nzmz=ltoan(akt+1);
    // <<rot<<"lfd: "<<lfd<<" nzmz: "<<nzmz<<schwarz<<endl;
    cgconf[++lfd].setze(&nzmz);
  } // if (rzf)

  // hier wurde falls noetig ermittelt, ob Fritzcard/Modem vorhanden
  if (obverb) {
    string obmodems=ltoan(obmodem); 
    Log(blaus+"obfcard: "+schwarz+ltoan(obfcard)+blau+", obmodem: "+schwarz+obmodems);
  }

  // die Verzeichnisnamen standardisieren
  kuerzevtz(&spoolcapivz);
  kuerzevtz(&cdonevz);
  kuerzevtz(&cfailedvz);
  kuerzevtz(&logvz);
  kuerzevtz(&zufaxenvz);
  kuerzevtz(&wvz);
  kuerzevtz(&nvz);
  kuerzevtz(&empfvz);
  for(zielmustercl *zmakt=zmp;1;zmakt++){
    kuerzevtz(&zmakt->ziel);
    if (zmakt->obmusterleer()) break;
  }
} // void paramcl::rueckfragen()

// wird aufgerufen in: main
void paramcl::autofkonfschreib()
{
  Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Tx[T_ja]:Tx[T_nein]));
  /*
     capizukonf und hylazukonf hier immer 0
     char buf[200];
     sprintf(buf,"rzf: %d, capizukonf: %d, hylazukonf: %d, obkschreib: %d",(int)rzf, (int)capizukonf, (int)hylazukonf, (int)obkschreib);
     Log(blaus+buf+schwarz);
   */
  if (rzf||obkschreib) {
    Log(gruens+Tx[T_schreibe_Konfiguration]+schwarz);
    // restliche Erklaerungen festlegen
    //    cgconf.setzbem("language",sprachstr);
    cgconf.setzbemv("countrycode",&Tx,T_Eigene_Landesvorwahl_ohne_plus_oder_00);
    cgconf.setzbemv("citycode",&Tx,T_Eigene_Ortsvorwahl_ohne_0);
    cgconf.setzbemv("msn",&Tx,T_Eigene_MSN_Faxnummer_ohne_Vorwahl);
    cgconf.setzbemv("LongDistancePrefix",&Tx,T_Praefix_fuer_ausserorts_zB_0);
    cgconf.setzbemv("InternationalPrefix",&Tx,T_Praefix_fuer_das_Ausland_zB_00);
    cgconf.setzbemv("LocalIdentifier",&Tx,T_Hylafax_bis_10_Buchstabe_fuer_eigenen_Namen);
    cgconf.setzbemv("cFaxUeberschrift",&Tx,T_Capisuite_bis_20_Buchstaben_fuer_eigenen_Namen);
    cgconf.setzbemv("sqlz",&Tx,T_Zahl_der_angegebenen_sql_Befehle_zur_Suche_nach_Absendern);
    cgconf.setzbemv("musterzahl",&Tx,T_Zahl_der_Muster_Verzeichnis_Paare_zum_Speichern_ankommender_Faxe);
    for (size_t i=0;i<cgconf.zahl;i++) {
      if (cgconf[i].name=="obhyla") cgconf[i].setze(&obhyla);
      else if (cgconf[i].name=="obcapi") cgconf[i].setze(&obcapi);
    } //     for (size_t i=0;i<cgconf.zahl;i++)
    //    cppSchluess *schlp[3]={cgconfp,sqlconfp,zmconfp};
    schlArr *schlp[3]={&cgconf,&sqlconf,&zmconf};
    //    size_t groe[sizeof schlp/sizeof *schlp]={gcs,sqlzn,zmzn+zmzn};
    //    for(size_t i=0;i<sqlzn;i++) KLA _out<<"i: "<<i<<sqlconfp[i].name<<endl; KLZ
    //    multicppschreib(konfdatname, schlp, groe, sizeof schlp/sizeof *schlp);
    multischlschreib(konfdatname, schlp, sizeof schlp/sizeof *schlp, mpfad);
  } // if (rzf||obkschreib) 
  //    ::cppschreib(konfdatname, cgconfp, gcs);
} // void paramcl::autofkonfschreib()


// in pruefcapi
void paramcl::clieskonf()
{
  Log(violetts+Tx[T_clieskonf]+schwarz+", cfaxcp->name: "+violett+(cfaxcp?cfaxcp->name:"0")+schwarz);
	if (capiconf[6].wert!="+"+countrycode+" "+citycode+" "+msn  
			|| capiconf[4].wert!=msn  
			|| capiconf[7].wert!=cFaxUeberschrift  
		 ) {
		capizukonf=1;
	}
  int richtige=0;
  if (cfaxcp) {
    cfaxcp->Abschn_auswert(obverb);
    for(size_t i=0;i<cfaxcp->abschv.size();i++) {
      if (cfaxcp->abschv[i].aname==cuser) {
        richtige=0;
        // <<"abschv["<<i<<"].av.size() "<<cfaxcp->abschv[i].av.size()<<endl;
        for(size_t j=0;j<cfaxcp->abschv[i].av.size();j++) {
          if (cfaxcp->abschv[i].av[j].name=="fax_numbers") {if (cfaxcp->abschv[i].av[j].wert==capiconf[4].wert) richtige++;}
          else if (cfaxcp->abschv[i].av[j].name=="fax_stationID") {if (cfaxcp->abschv[i].av[j].wert==capiconf[6].wert) richtige++;}
          else if (cfaxcp->abschv[i].av[j].name=="fax_headline") {if (cfaxcp->abschv[i].av[j].wert==capiconf[7].wert) richtige++;}
          else if (cfaxcp->abschv[i].av[j].name=="fax_email_from") {if (cfaxcp->abschv[i].av[j].wert==capiconf[8].wert) richtige++;}
        }
        break;
      } //       if (cfaxcp->abschv[i].aname==cuser)
    } //     for(size_t i=0;i<cfaxcp->abschv.size();i++)
    if (richtige!=4) {
      capizukonf=1;
    }
  } //   if (cfaxcp)
  svec ckzlrueck;
  systemrueck("grep connect_faxG3 `grep incoming_script= "+ccapiconfdat+" 2>/dev/null|cut -d'\"' -f2 2>/dev/null`"
      "|sed 's/.*headline//;s/^,//;s/).*//'",obverb,oblog,&ckzlrueck,1);
  if (ckzlrueck.size()) {
    if (cklingelzahl!=ckzlrueck[0]) {
      // <<", ckzlrueck[0]: '"<<ckzlrueck[0]<<"', cklingelzahl: '"<<cklingelzahl<<"'"<<endl;
      capizukonf=1;
    }
  } else {
    capizukonf=1;
  }
} // void paramcl::clieskonf()


// wird  aufgerufen in: pruefcapi
void paramcl::konfcapi()
{
  Log(violetts+Tx[T_konfcapi]+schwarz+", ccapiconfdat: "+violett+ccapiconfdat+schwarz);
  // Zahl der Klingeltoene in capisuite einstellen
  /*
     cppSchluess cconf[]={{"incoming_script"}};
     size_t cs=sizeof cconf/sizeof*cconf;
   */
  // <<"cconf[0].wert: "<<cconf[0].wert<<endl;
  if (!cconf[0].wert.empty()) {
    systemrueck("sudo sed -i$(test -f "+cconf[0].wert+".orig||echo '.orig') "
        "'s/\\(^.*connect_faxG3.*headline\\).*\\().*$\\)/\\1,"+cklingelzahl+"\\2/' "+cconf[0].wert,obverb,oblog);
  }
  //    if (cpplies(ccapiconfdat,cconf,cs)) KLA
  /*
     mdatei f(cconf[0].wert,ios::in); // /usr/lib64/capisuite/incoming.py
     if (f.is_open()) KLA
     string zeile;
     const char* searchstr="connect_faxG3(";
  // <<rot<<"Lese: "<<cconf[0].wert<<schwarz<<endl;
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
  string neudatei=string(cconf[0].wert)+"_neu";
  f.close();
  mdatei fneu(neudatei,ios::out);
  mdatei falt(cconf[0].wert,ios::in);
  if (falt.is_open()) if (fneu.is_open()) KLA
  while(getline(falt,zeile)) KLA
  nk=zeile.find(searchstr);
  if (nk!=string::npos) KLA
  fneu<<neuzeile<<endl;
  KLZ else KLA
  fneu<<zeile<<endl;
  KLZ 

  KLZ // while(getline(falt,zeile)) 
  struct stat entryorig={0};
  string origdatei=string(cconf[0].wert)+"_orig";
  if (lstat(origdatei.c_str(),&entryorig)) KLA
  dorename(cconf[0].wert,origdatei,cuser,0,obverb,oblog);
  KLZ else KLA
  tuloeschen(cconf[0].wert,cuser,obverb,oblog);
  KLZ            
  dorename(neudatei,cconf[0].wert,cuser,0,obverb,oblog); 
  KLZ  // if (falt.is_open()) if (fneu.is_open()) 
  break;
  KLZ // if (nkz!=cklingelzahl) 
  KLZ // if (klap!=string::npos) 
  KLZ //           if (nkh!=string::npos) KLA
  KLZ // if ((nkz=strstr(zeile,searchstr))) 
  KLZ // while(getline(f,zeile)) 
  KLZ // if (f.is_open()) 
  KLZ // if (cpplies(ccapiconfdat,cconf,cs)) 
   */
  //  static cppSchluess capiconf[]=KLA KLA"spool_dir"KLZ,KLA"fax_user_dir"KLZ,KLA"send_tries"KLZ,KLA"send_delays"KLZ,
  //         KLA"outgoing_MSN"KLZ,KLA"dial_prefix"KLZ,KLA"fax_stationID"KLZ,KLA"fax_headline"KLZ,KLA"fax_email_from"KLZ KLZ;
  // fax_stationID
  uchar capicffehlt=0;
  // <<rot<<"capiconf[6].wert: '"<<capiconf[6].wert<<"'"<<schwarz<<endl;
  if (capiconf[6].wert.find("000 0000")!=string::npos || capiconf[6].wert.empty()) {
    //    if (cfax_stationID.find("000 0000")!=string::npos) 
    //    ::Log(string("Capisuite ist offenbar noch nicht konfiguriert(")+blau+"fax_stationID"+schwarz+" enthaelt '000 0000').\n"
    //        "Die Einstellung koennen spaeter in "+blau+cfaxconfdat+schwarz+" geaendert werden.",1,0);
    ::Log(string(Tx[T_Capisuite_ist_offenbar_noch_nicht_richtig_konfiguriert])+blau+"'fax_stationID'"+schwarz+Tx[T_ist_Apostroph]+blau+
        capiconf[6].wert+schwarz+"')."+ Tx[T_Die_Einstellungen_koennen_spaeter_in]+blau+cfaxconfdat+schwarz+Tx[T_geaendert_werden],1,1);
    // fax_stationID
    capicffehlt=1;
  } // if (capiconf[6].wert.find("000 0000")!=string::npos || capiconf[6].wert.empty()) 
  if (rzf || (capicffehlt && !nrzf)) {
    while (capiconf[6].wert.find("000 0000")!=string::npos || !istelnr(capiconf[6].wert)) {
      capiconf[6].wert="+"+countrycode+" "+citycode+" "+msn;
      capiconf[6].wert=Tippstring(string("fax_stationID: ")+Tx[T_Faxnr_die_zum_Adressaten_gesandt_wird_bis_20_Zeichen_nur_plus_und_Ziffern],
          &capiconf[6].wert);
    }
    vector<string> tok;
    aufSplit(&tok,&capiconf[6].wert,' ');
    // outgoing_MSN
    capiconf[4].wert=msn;
    if (capiconf[4].wert.empty() || isneun(capiconf[4].wert)) capiconf[4].wert=tok[tok.size()-1].c_str();
    do {
      capiconf[4].wert=Tippstring(string("outgoing_MSN: ")+
          Tx[T_ausgehende_Multiple_Subscriber_Number_Faxnummer_ohne_Vorwahl],&capiconf[4].wert);
    } while (capiconf[4].wert.empty() || !isnumeric(capiconf[4].wert) || isneun(capiconf[4].wert));
    // dial_prefix
    capiconf[5].wert=Tippstring(string("dial_prefix: ")+Tx[T_Amtsholung_ueblicherweise_kk_oder_0],&capiconf[5].wert);
    // fax_headline
    capiconf[7].wert=cFaxUeberschrift;
    capiconf[7].wert=Tippstring(string("fax_headline: ")+Tx[T_Faxueberschrift],&capiconf[7].wert);
    // fax_email_from
    capiconf[8].wert=Tippstring(string("fax_email_from: ")+
        Tx[T_Adressat_empfangener_Faxe_die_ueber_Email_verteilt_werden],&capiconf[8].wert);
    // send_tries
    if (!isnumeric(capiconf[2].wert)) capiconf[2].wert="15";
    do {
      capiconf[2].wert=Tippstring(string("send_tries: ")+Tx[T_Zahl_der_Sendeversuche],&capiconf[2].wert);
    } while (capiconf[2].wert.empty() || !isnumeric(capiconf[2].wert));
    // send_delays
    capiconf[3].wert="60,60,60,300,300,300,300,300,3600,3600,3600,3600,18000,36000";
    do {
      capiconf[3].wert=Tippstring(string("send_delays: ")+Tx[T_kommagetrennte_Liste_mit_Sekundenabstaenden_zwischen_Sendeversuchen],
          &capiconf[3].wert);
    } while (capiconf[3].wert.empty() || !isnumeric(capiconf[3].wert));
    // outgoing_timeout
    capiconf[9].wert="60";
    capiconf[9].wert=Tippstring(string("outgoing_timeout: ")+Tx[T_Geduld_bis_zum_Verbindungsaufbau_in_s],&capiconf[9].wert);
    if (obverb>0) {
      for(unsigned snr=0;snr<capiconf.zahl;snr++) {
        Log(string("snr: ")+blau+ltoan(snr)+schwarz+" "+capiconf[snr].wert+", "+capiconf[snr].wert);
      }
    } // if (obverb>0)
  } // if (rzf || (capicffehlt && !nrzf))
  string suchcuser=string("[")+cuser+"]";
  // es gibt zwei moegliche Gruende zum Neuschreiben der Datei: 1) Parameter diffierieren, 2) noch kein User angelegt
  uchar cuserda=0, paramdiff=0, neuschreiben=0;
  string zeile, neudatei;
  // iru=0 => pruefen, ob Datei geaendert werden muss; iru=1 => aendern
  for(uchar iru=0;iru<2;iru++) {
    mdatei *fneu=0;
    mdatei f(cfaxconfdat,ios::in); // /etc/capisuite/fax.conf
    if (f.is_open()) {
      if (iru) {
        neudatei=cfaxconfdat+"_neu";
        fneu=new mdatei(neudatei,ios::out,0);
        if (!fneu->is_open()) break;
      } // if (iru)
      while(f.is_open() && getline(f,zeile)) {
        size_t kommpos=zeile.find('#');
        uchar geschrieben=0;
        //          if (kommpos!=string::npos) zeile.erase(kommpos);
        //          if (!zeile.length()) continue;
        if (!cuserda) 
          if (zeile.find(suchcuser)!=string::npos) 
            cuserda=1;
        // <<rot<<"iru: "<<(int)iru<<", paramdiff: "<<(int)paramdiff<<schwarz<<endl;
        if (iru || !paramdiff) {
          size_t nkz=zeile.find('=');
          string lzeile,rzeile;
          if (nkz<kommpos) {
            lzeile=zeile.substr(0,nkz); 
            rzeile=zeile.substr(nkz+1);
            for(unsigned snr=0;snr<capiconf.zahl;snr++) {
              if (lzeile.find(capiconf[snr].name)!=string::npos) {
                // _out<<"snr: "<<snr<<", lzeile: "<<tuerkis<<lzeile<<schwarz<<", rzeile: "<<blau<<rzeile<<schwarz<<endl;
                string altwert=rzeile;
                gtrim(&altwert);
                anfzweg(altwert); // Anfuehrungszeichen entfernen
                if (snr==0 || snr==1) capiconf[snr].wert=altwert; // spool_dir und fax_user_dir hier nicht konfigurierbar
                Log(string("capiconf[")+ltoan(snr)+"].name: "+tuerkis+capiconf[snr].name+schwarz+Tx[T_komma_wert]+
                    (capiconf[snr].wert==altwert?blau:rot)+capiconf[snr].wert+schwarz+Tx[T_komma_Altwert]+
                    blau+altwert+schwarz,obverb+iru,oblog+iru);
                if (capiconf[snr].wert!=altwert) {
                  if (!iru) {
                    neuschreiben=1;
                    paramdiff=1;
                  } else {
                    *fneu<<capiconf[snr].name<<" = \""<<capiconf[snr].wert<<"\""<<endl;
                    geschrieben=1;
                  }
                }
                break; // wenn richtige Zeile gefunden, nicht mehr weitersuchen, unabhaengig vom Ergebnis
              } // if ((nkz=strstr(zeile,capiconf[snr].name))) 
            } // if ((nkz=zeile.find(capiconf[snr].wert))!=string::npos) 
          } // for(unsigned snr=0;snr<ccs;snr++) 
        } // if (!paramdiff) 
        if (iru)
          if (!geschrieben) 
            *fneu<<zeile<<endl;
      } // while( fgets(p=zeile,sizeof zeile,f) ) 
      if (!iru) {
        if (!cuserda) neuschreiben=1;
        if (!neuschreiben) break; // dann fertig
      } else { // if (iru)
        if (!cuserda)  {
          // schreibe Konfiguration fuer Benutzer in fax.conf
          *fneu<<suchcuser<<endl;
          *fneu<<"fax_numbers=\""<<capiconf[4].wert<<"\""<<endl;
          *fneu<<"fax_stationID=\""<<capiconf[6].wert<<"\""<<endl;
          *fneu<<"fax_headline=\""<<capiconf[7].wert<<"\""<<endl;
          *fneu<<"fax_email_from=\""<<capiconf[8].wert<<"\""<<endl;
          *fneu<<"fax_action=\"MailAndSave\""<<endl;
        } // if (!cuserda)
        if (fneu) delete fneu;
        setfaclggf(cfaxconfdat, falsch, 6, falsch,obverb,oblog);
        string origdatei=cfaxconfdat+"_orig";
        struct stat entryorig={0};
        if (lstat(origdatei.c_str(),&entryorig)) {
          dorename(cfaxconfdat,origdatei,cuser,0,obverb,oblog);
        } else {
          tuloeschen(cfaxconfdat,cuser,obverb,oblog);
        }
        dorename(neudatei,cfaxconfdat,cuser,0,obverb,oblog);
      } // if (iru)
      if (!capiconf[1].wert.empty()) cfaxuservz=capiconf[1].wert;
      // <<rot<<"cfaxuservz konfcapi: "<<cfaxuservz<<schwarz<<endl;
    } // if (f.is_open())
  } // for(uchar iru=0;iru<2;iru++) 
  pruefcvz();
  nextnum();
  Log(violetts+Tx[T_Ende]+Tx[T_konfcapi]+schwarz+"ccapiconfdat: "+violett+ccapiconfdat+schwarz);
} // void paramcl::konfcapi()

// in konfcapi und faxemitC (da konfacpi aus pruefcapi nicht unbedingt aufgerufen wird)
void paramcl::nextnum()
{
  // dieser Abschnitt war zuvor richtcapiher
  unsigned long nextnr=0;
  struct stat entrynextnr={0};
  // <<"cfaxusersqvz: "<<cfaxusersqvz<<endl;
  nextdatei=cfaxusersqvz+"/fax-nextnr";
  // <<ndatei<<endl;
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
    pruefverz(cfaxuservz,obverb,oblog,2);
    setfaclggf(spoolcapivz,wahr,7,wahr,obverb,oblog);
    cmd=string(" sudo echo $(( `find ")+spoolcapivz+ " -type f -name '*-fax-*.sff' 2>/dev/null "
      "| cut -d '-' -f3 | cut -d '.' -f1 | sort -rn | head -n1` + 1 )) > '"+nextdatei+"'";
    systemrueck(cmd,obverb,oblog);
  }
  setfaclggf(nextdatei,falsch,6,falsch,obverb,oblog);
} // void paramcl::nextnum()

// wird aufgerufen in: main
void paramcl::verzeichnisse()
{
  Log(violetts+Tx[T_verzeichnisse]);
  pruefcvz(); 
  pruefverz(zufaxenvz,obverb,oblog,2); // dahin soll man schreiben koennen
  pruefverz(wvz,obverb,oblog);
  pruefverz(nvz,obverb,oblog);
  pruefverz(empfvz,obverb,oblog);
  for(zielmustercl *zmakt=zmp;1;zmakt++){
    pruefverz(zmakt->ziel,obverb,oblog);
    if (zmakt->obmusterleer()) break;
  }
  for(uint imu=0;imu<this->zmzn;imu++) {
    char *imus = ltoan(imu);
    ::Log(string(Tx[T_Muster])+imus+": '"+rot+this->zmp[imu].holmuster()+schwarz+"'",this->obverb>1,this->oblog);
    ::Log(string(Tx[T_Ziel])+imus+":   '"+rot+this->zmp[imu].ziel+schwarz+"'",this->obverb>1,this->oblog);
  }
} // paramcl:: verzeichnisse()

// aufgerufen in pruefcron, pruefmodcron und anhalten
void paramcl::setztmpc()
{
  if (tmpc.empty()) {
    // Einbau von '~' ergaebe bei Aufruf mit und ohne sudo unterschiedliche Erweiterungen
    tmpc+=gethome()+"/rootscrontab";
  }
} // void setztmpc()


// wird aufgerufen in: main
void paramcl::pruefcron()
{
  //  svec rueck;
  int cronda=0;
  int cronzuplanen = (cronminut!="0");
  Log(violetts+Tx[T_pruefcron]+schwarz+Tx[T_cronzuplanen]+violetts+ltoan(cronzuplanen)+schwarz);
		for (uchar runde=0;runde<2;runde++) {
			cronda=obprogda("crontab",obverb-1,0);
			if (cronda) break;
			// systemrueck("which zypper 2>/dev/null && zypper -n in cron || 
			//              KLA which apt-get 2>/dev/null && apt-get -y install cron; KLZ",1,1);
			linst.doinst("cron",1,1);
			//  int obionice=!systemrueck("which ionice > /dev/null 2>&1",0,0);
		} //   for (uchar runde=0;runde<2;runde++) 
		if (cronda) {
			int nochkeincron = systemrueck("sudo crontab -l",obverb-1,0,0,2);
			setztmpc();
			const string cb0 = " /usr/bin/ionice -c2 -n7 /usr/bin/nice -n19 "+vaufr;// "date >/home/schade/zeit";
			const string cbef  =string("*/")+cronminut+" * * * *"+cb0; // "-"-Zeichen nur als cron
			const string czt=" \\* \\* \\* \\*";
			string vorcm;
			if (!nochkeincron) {
				cmd="bash -c 'grep \"\\*/.*"+czt+cb0+"\" <(sudo crontab -l 2>/dev/null)| sed \"s_\\*/\\([^ ]*\\) .*_\\1_\"'";
				svec cmrueck;
				systemrueck(cmd,obverb,oblog,&cmrueck);
				if (cmrueck.size()) vorcm=cmrueck[0];
			} // 		if (!nochkeincron) 
			if (vorcm.empty() && !cronzuplanen) {
				if (obverb) ::Log(Tx[T_Kein_cron_gesetzt_nicht_zu_setzen],1,oblog);
			} else {
				if (cronminut==vorcm) {
					if (obverb) ::Log(blaus+"'"+saufr+"'"+schwarz+Tx[T_wird]+Tx[T_unveraendert]+
							+blau+(vorcm.empty()?Tx[T_gar_nicht]:Tx[T_alle]+vorcm+Tx[T_Minuten])+schwarz+Tx[T_aufgerufen],1,oblog);
				} else {
					string unicmd="rm -f "+tmpc+";";
					cmd=unicmd;
					string dazu="sudo crontab -l|sed '/"+saufr+"/d'>"+tmpc+";";
				  unicmd+=dazu;	
					if (!nochkeincron)
						cmd=dazu;
					if (cronzuplanen) {
						cmd+=" echo \""+cbef+"\">>"+tmpc+";";
					}
					dazu=" sudo crontab "+tmpc+";";
					unicmd+=dazu;
					cmd+=dazu;
					systemrueck(cmd,obverb,oblog);
					anfgggf(unindt,unicmd);
					::Log(blaus+"'"+saufr+"'"+schwarz+Tx[T_wird]+blau+(cronzuplanen?Tx[T_alle]+cronminut+Tx[T_Minuten]:Tx[T_gar_nicht])+schwarz+Tx[T_statt]+
							+blau+(vorcm.empty()?Tx[T_gar_nicht]:Tx[T_alle]+vorcm+Tx[T_Minuten])+schwarz+Tx[T_aufgerufen],1,oblog);
				} // 				if (cronminut==vorcm) else
			} // 		if (vorcm.empty() && cronminut=="0")
#ifdef stumm
#define uebersichtlich
#ifdef uebersichtlich
			string befehl;
			if (!cronzuplanen) {
				if (nochkeincron) {
				} else {
					befehl=("bash -c 'grep \""+saufr+"\" -q <(sudo crontab -l)'&& (sudo crontab -l|sed '/"+saufr+"/d'>")+tmpc+";sudo crontab "+tmpc+")||true";
				}
			} else {
				if (nochkeincron) {
					befehl="rm -f "+tmpc+";";
				} else {
					befehl="bash -c 'grep \"\\*/"+cronminut+czt+cb0+"\" -q <(sudo crontab -l)'|| (sudo crontab -l|sed '/"+saufr+"/d'>"+tmpc+";";
				}
				befehl+="echo \""+cbef+"\">>"+tmpc+"; sudo crontab "+tmpc+"";
				if (!nochkeincron)
					befehl+=")";
			}
#else
			const string befehl=cronzuplanen?
				(nochkeincron?("rm -f ")+tmpc+";":
				 "bash -c 'grep \"\\*/"+cronminut+czt+cb0+"\" -q <(sudo crontab -l)' || (sudo crontab -l | sed '/"+saufr+"/d'>"+tmpc+"; ")+
				"echo \""+cbef+"\">>"+tmpc+"; sudo crontab "+tmpc+(nochkeincron?"":")")
				:
				(nochkeincron?"":("bash -c 'grep \""+saufr+"\" -q <(sudo crontab -l)' && (sudo crontab -l | sed '/"+saufr+"/d'>")+tmpc+";"
				 "sudo crontab "+tmpc+")||true")
				;
#endif      
			systemrueck(befehl,obverb,oblog);
#endif
		} //   if (cronda) 
  //  systemrueck(string("mv -i '")+mpfad+"' /root/bin",1,0);
} // pruefcron

// wird aufgerufen in: main
void paramcl::pruefsamba()
{
  Log(violetts+Tx[T_pruefsamba],obverb,oblog);
  const char* const smbdatei="/etc/samba/smb.conf";
  int gestartet=0;
  uchar conffehlt=1;
  const string quelle="/usr/share/samba/smb.conf";
  uchar obinst=0; // ob Samba installiert werden soll bzw. die smb.conf bearbeitet
  uchar obfw=0; // ob SuSEfirewall bearbeitet werden soll
	int obsfehlt=linst.obfehlt("samba",obverb,oblog);
	if (obsfehlt) {
		if (!nrzf) {
			obinst=Tippob(Tx[T_Samba_muesste_installiert_werden_soll_ich],Tx[T_j_af]);
			if (obinst)
				linst.doinst("samba",obverb,oblog);
			//        smbrestart=0;
		} // if (!nrzf) 
	} // 	if (obsfehlt)
  for(uchar iru=0;iru<2;iru++) {
		struct stat sstat={0};
		if (!(conffehlt=lstat(smbdatei,&sstat))) break;
    if (iru) break;
    pruefverz("/etc/samba",obverb,oblog,0,0);
    kopier(quelle,smbdatei,obverb,oblog);
  } //   for(uchar iru=0;iru<2;iru++)
  int dienstzahl=2;
  servc smb("smb","smbd");
  servc smbd("smbd","smbd");
  servc nmb("nmb","nmbd");
  servc nmbd("nmbd","nmbd");
	  caus<<violett<<"pruefsamba 1"<<schwarz<<endl;
  if (smb.obsvfeh(obverb,oblog)) if (smbd.obsvfeh(obverb,oblog)) dienstzahl--;
  if (nmb.obsvfeh(obverb,oblog)) if (nmbd.obsvfeh(obverb,oblog)) dienstzahl--;
  //  <<rot<<"dienstzahl: "<<dienstzahl<<endl;
  if (dienstzahl<2||conffehlt) {
    for(int aru=0;aru<2;aru++) {
      if (aru) {
      } // if (aru) 
      if (smb.svfeh!=1) {
        smb.machfit(obverb,oblog);
        gestartet=1;
      } else if (smbd.svfeh!=1) {
        smbd.machfit(obverb,oblog);
        gestartet=1;
      } //       if (!smb.svfeh)
      if (nmb.svfeh!=1) {
        nmb.machfit(obverb,oblog);
        if (gestartet==1) gestartet=2;
      } else if (nmbd.svfeh!=1) {
        nmbd.machfit(obverb,oblog);
        if (gestartet==1) gestartet=2;
      } //       if (!nmb.svfeh)
	  caus<<violett<<"pruefsamba 2"<<schwarz<<endl;
      if (!smb.svfeh) if (!smb.obsvfeh(obverb,oblog)) if (!nmb.svfeh) if (!nmb.obsvfeh(obverb,oblog)) break;
      if (!smbd.svfeh) if (!smbd.obsvfeh(obverb,oblog)) if (!nmbd.svfeh) if (!nmbd.obsvfeh(obverb,oblog)) break;
    } // for(int aru=0;aru<2;aru++) 
    //    if (gestartet==2) smbrestart=0;
  } // if (dienstzahl<2 || conffehlt) 
	struct stat sstat={0};
	if (!(conffehlt=lstat(smbdatei,&sstat))) {
    confdat smbcf(smbdatei,obverb);
    smbcf.Abschn_auswert(obverb);
    vector<string*> vzn;
		const int ISambaName[4]={T_Zufaxen,T_Warteauffax,T_Nichtgefaxt,T_Faxempfang}; 
    //={&zufaxenvz,&wvz,&nvz,&empfvz};
    vzn.push_back(&zufaxenvz);
    vzn.push_back(&wvz);
    vzn.push_back(&nvz);
    vzn.push_back(&empfvz);
    for(zielmustercl *zmakt=zmp;1;zmakt++){
      vzn.push_back(&zmakt->ziel);
      if (zmakt->obmusterleer()) break;
    } //     for(zielmustercl *zmakt=zmp;1;zmakt++)
    uchar gef[vzn.size()]; memset(gef,0,vzn.size()*sizeof(uchar));
    for(size_t i=0;i<smbcf.abschv.size();i++) {
      if (smbcf.abschv[i].aname!="global") {
        const string& pfad = smbcf.abschv[i].suche("path");
        if (!pfad.empty()) {
          for(unsigned k=0;k<vzn.size();k++) {
            if (!gef[k]) if (!vzn[k]->empty()) {
              if (!vzn[k]->find(pfad)) {
                gef[k]=1;
              }
            } // if (!gef[k]) if (!vzn[k]->empty()) 
          } // for(unsigned k=0;k<sizeof vzn/sizeof *vzn;k++) 
        } // if (!pfad.empty()) 
      } // if (smbcf.abschv.aname!="global") 
    } // for(size_t i=0;i<smbcf.abschv.size();i++) 
		uchar smbrestart=0;
		mdatei sapp(smbdatei,ios::out|ios::app);
		if (sapp.is_open()) {
			string suchstr;
			for(unsigned k=0;k<vzn.size();k++) {
				if (!gef[k]) {
					smbrestart=1;
					if (!obinst) {
						obinst=Tippob(Tx[T_Sollen_fehlende_Sambafreigaben_fuer_die_angegebenen_Verzeichnisse_ergaenzt_werden],Tx[T_j_af]);
						if (!obinst) break;
					}
					::Log(rots+Tx[T_Verzeichnis]+blau+*vzn[k]+rot+Tx[T_nicht_als_Sambafreigabe_gefunden_wird_ergaenzt]+schwarz,1,oblog);
					string abschnitt;
					if (k<4) {
						abschnitt=Tx[ISambaName[k]];
							Sprache altSpr=Tx.lgn;
							for(int akts=0;akts<Smax;akts++) {
								Tx.lgn=(Sprache)akts;
								suchstr=suchstr+"\\["+Tx[ISambaName[k]]+"\\]";
								if (k<vzn.size()-1||akts<Smax-1) suchstr+="\\|";
							} //         for(int akts=0;akts<Smax;akts++)
							Tx.lgn=altSpr;
					} else {
						abschnitt=string(Tx[T_Gefaxt])+"_"+ltoan(k-4);
						if (k==4) {
							Sprache altSpr=Tx.lgn;
							for(int akts=0;akts<Smax;akts++) {
								Tx.lgn=(Sprache)akts;
								suchstr=suchstr+"\\["+Tx[T_Gefaxt]+"_";
								if (akts<Smax-1) suchstr+="\\|";
							} //         for(int akts=0;akts<Smax;akts++)
							Tx.lgn=altSpr;
						} // 						if (k==4)
					} // 					if (k<4) else
					sapp<<"["<<abschnitt<<"]"<<endl;
					sapp<<"  comment = "<<meinname<<" "<<abschnitt<<endl;
					sapp<<"  path = "<<*vzn[k]<<endl;
					sapp<<"  directory mask = 0660"<<endl;
					sapp<<"  browseable = Yes"<<endl;
					if (!k)
						sapp<<"  read only = no"<<endl; // zufaxenvz soll beschreibbar sein
					sapp<<"  vfs objects = recycle"<<endl;
					sapp<<"  recycle:versions = Yes"<<endl;
					sapp<<"  recycle:keeptree = Yes"<<endl;
					sapp<<"  recycle:repository = Papierkorb"<<endl;
				} // if (!gef[k]) 
			} // for(unsigned k=0;k<sizeof vzn/sizeof *vzn;k++) 
			if (!suchstr.empty())
				anfgggf(unindt,"sudo sed -i.vorautofax '/^[ \\t]/{H;$!d;};x;/"+suchstr+"/d;1d' "+smbdatei);
		} // if (sapp.is_open()) 
		if (!nrzf) {
			if (systemrueck("sudo pdbedit -L | grep "+cuser+":",obverb,oblog)) {
				string pw1, pw2;
				while (1) {
					do {
						pw1=Tippstring(string(Tx[T_Passwort_fuer_samba])+Txd[T_fuer_Benutzer]+dblau+cuser+schwarz+"'",&pw1);
					} while (pw1.empty());
					pw2=Tippstring(string(Tx[T_Passwort_fuer_samba])+Txd[T_fuer_Benutzer]+dblau+cuser+schwarz+"' ("+Txk[T_erneute_Eingabe]+")",&pw2);
					if (pw1==pw2) break;
				} //         while (1)
				systemrueck("sudo smbpasswd -n -a "+cuser,obverb,oblog);
				systemrueck("(echo "+pw1+"; echo "+pw2+") | sudo smbpasswd -s "+cuser,obverb,oblog);
      } // if (systemrueck("sudo pdbedit -L | grep "+cuser+":",obverb,oblog)) 
    } // if (!nrzf)
    if (smbrestart) {
      if (smb.svfeh!=1) smb.restart(obverb-1,oblog);
      else if (smbd.svfeh!=1) smbd.restart(obverb-1,oblog);
      if (nmb.svfeh!=1) nmb.restart(obverb-1,oblog);
      else if (nmbd.svfeh!=1) nmbd.restart(obverb-1,oblog);
    } // if (smbrestart) 
		// VFS
		if (linst.pruefipr()==apt) linst.doggfinst("samba-vfs-modules",obverb,oblog);
		// Firewall(s)
		uchar obslaeuft=0;
		svec rueckr;
		systemrueck("systemctl list-units|grep firewall|grep -v init",obverb,oblog,&rueckr);
		if (rueckr.size()) if (rueckr[0].find("active running")!=string::npos ||rueckr[0].find("active exited")!=string::npos) obslaeuft=1;
		if (obslaeuft) {
			// firewall-ports, geht in SUSE und Fedora
			uchar obzu=0;
			// udp, udp, tcp, tcp
			svec ports; ports<<"137"<<"138"<<"139"<<"445";
			for(size_t i=0;i<ports.size();i++) {
				svec rueck;
				systemrueck("sudo iptables -L -n|grep "+ports[i],obverb,oblog,&rueck);
				if (rueck.size()) {
					if (obverb>1) ::Log(rueck[0],obverb-1,oblog);
					if (rueck[0].substr(0,6)=="ACCEPT" || rueck[0].substr(0,3)=="LOG") {
						if (obverb) Log(Tx[T_Firewallport]+blaus+ports[i]+schwarz+Tx[T_offen]);
						continue;
					}
				} // 			if (rueck.size())
				if (obverb) Log(Tx[T_Firewallport]+blaus+ports[i]+schwarz+Tx[T_zu]);
				obzu=1;
				break;
			} // 		for(size_t i=0;i<ports.size();i++) 
			if (obzu) {
				lsysen system=lsys.getsys(obverb,oblog);
				if (system==fed) {
					// fedora:
					// firewall-cmd --state
					systemrueck("sudo firewall-cmd --permanent --add-service=samba && sudo firewall-cmd --reload",obverb,oblog);
					anfgggf(unindt,"sudo firewall-cmd --permanent --remove-service=samba && sudo firewall-cmd --reload");
					// selinux: // offenbar unnoetig
				} else {
					// Suse-Firewall
					const string susefw="/etc/sysconfig/SuSEfirewall2";
					struct stat fstat={0};
					if (!lstat(susefw.c_str(),&fstat)) {
						string part="server";
						for(int i=1;i<3;i++) {
							int nichtfrei=systemrueck("grep '^FW_CONFIGURATIONS_EXT=\\\".*samba-"+part+"' "+susefw,obverb,oblog,0,2);
							if (nichtfrei && !nrzf && !obfw) {
								obfw=Tippob(Tx[T_Soll_die_SuSEfirewall_bearbeitet_werden],Tx[T_j_af]);
								if (!obfw) break;
							} // 					if (nichtfrei && !nrzf && !obfw)
							if (nichtfrei && obfw) {
							  string bak="bak_"+meinname+ltoan(i);
								struct stat lbak={0};
								int fehlt=lstat((susefw+"."+bak).c_str(),&lbak);
								systemrueck("sudo sed -i"+(fehlt?"."+bak:"")+
								" 's/\\(FW_CONFIGURATIONS_EXT=\\\".*\\)\\(\\\".*$\\)/\\1 samba-"+part+"\\2/g' "+susefw+
										" && sudo systemctl restart SuSEfirewall2 smb nmb",obverb,oblog); 
								anfgggf(unindt,"sudo sh -c 'cp -a \""+susefw+"."+bak+"\" \""+susefw+"\"'&&systemctl restart SuSEfirewall2 smb nmb");
							} // 					if (nichtfrei && obfw)
							part="client";
						} // for(int i=1;i<3;i++) 
					} // if (!lstat(susefw,&fstat)) 
				} // 			  if (system==fed) else 
			} // obzu
		} // obslaeuft
  } //   if (!(conffehlt=lstat(smbdatei,&sstat)))
} // pruefsamba

// wird aufgerufen in: main
int paramcl::initDB()
{
  Log(violetts+"initDB()"+schwarz);
  My = new DB(myDBS,host,muser,mpwd,dbq,0,0,0,obverb,oblog);
  if (My->fehnr) {
    ::Log(rots+Tx[Verbindung_zur_Datenbank_nicht_herstellbar]+schwarz+ltoan(My->fehnr)+rot+Tx[T_Breche_ab]+schwarz,1,1);
    return 1;
  } //   if (My->fehnr)
  return 0;
} // initDB

int paramcl::pruefDB(const string& db)
{
  Log(violetts+Tx[T_pruefDB]+db+")"+schwarz);
  My = new DB(myDBS,host,muser,mpwd,db,0,0,0,obverb,oblog,3,0);
  return (My->fehnr); 
} // pruefDB

// Parameter -kez
// wird aufgerufen in: main
void paramcl::korrigierecapi(unsigned tage/*=90*/)
{
  Log(violetts+Tx[T_korrigierecapi]+schwarz);
  // geht wegen Loeschens der Protokolldateien nur (noch) fuer Gefundene, s.u.
  if (1) {
    for(uchar runde=0;runde<1;runde++) {
      set<string>::iterator fit; // Iterator dafuer
      svec rueck[2];
      set<string> fdn; // Fax-Dateien
      size_t ruecki;
			string inse;
			string teln,zp,tries,user;
			size_t size;
			char buf[100]={0};
			switch (runde) {
        case 0: // capi
					/*
					if (0) {
						cmd="sudo find '"+cdonevz+"' -maxdepth 1 -type f -iname '*-fax-*.sff'"; //  -printf '%f\\n'"; // cfailedvz weniger wichtig
						systemrueck(cmd,obverb,oblog,&rueck);
						// sortieren
						for(ruecki=0;ruecki<rueck.size();ruecki++) {
							fdn.insert(rueck[ruecki]);
						} 
					} // if (0)
					*/
					for(int cru=0;cru<2;cru++) {
						cmd="sudo find '"+(cru?cdonevz:cfailedvz)+"' -maxdepth 1 "+(tage?string("-mtime -")+ltoan(tage):"")+" -iname '*-fax-*.sff'";//-printf '%f\\n'";
						systemrueck(cmd,obverb,oblog,&rueck[cru]);
					}
					if (rueck[0].size()||rueck[1].size()) {
						RS vgl1(My,"DROP TABLE IF EXISTS tmpc",ZDB);
						RS vgl2(My,"CREATE TABLE tmpc(submid VARCHAR(25) KEY,teln VARCHAR(25),zp DATETIME, tries INT, size INT(15), erfolg INT);",ZDB);
						for(int cru=0;cru<2;cru++) {
							for(ruecki=0;ruecki<rueck[cru].size();ruecki++) {
								teln.clear();zp.clear();tries.clear();user.clear();size=0;
								struct stat sffstat={0};
								if (!lstat(rueck[cru][ruecki].c_str(),&sffstat)) {
									size=sffstat.st_size;
									struct tm *tmp=localtime(&sffstat.st_mtime);
									strftime(buf, sizeof(buf), "%F %T", tmp);
									zp=buf;
								}
								string stamm,exten;
								getstammext(&rueck[cru][ruecki],&stamm,&exten);
								const string txtf=stamm+".txt";
								struct stat txtstat={0};
								if (!lstat(txtf.c_str(),&txtstat)) {
									// <<gruen<<txtf<<schwarz<<endl;
									schlArr txtconf; 
									txtconf.init(6,"dialstring","starttime","tries","user","addressee","subject");
									confdat txtcf(txtf,&txtconf,obverb,'='); // static wertet nichts aus
									teln=stdfaxnr(txtconf[0].wert);
									/* // liegt in der Zukunft!
									for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++) KLA
										struct tm tm={0};
										if (strptime(txtconf[1].wert.c_str(),tmmoegl[im],&tm)) KLA
											strftime(buf, sizeof(buf), "%F %T", &tm);
											zp=buf;
											break;
										KLZ // 							if (strptime(txtconf[1].wert.c_str(),"%c",&tm))
									KLZ // 								for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++)
									*/
									tries=txtconf[2].wert;
									user=txtconf[3].wert;
								} // 						if (!lstat(txtf.c_str(),&txtstat))
								// <<"txtf: "<<txtf<<endl;
								string ursp=base_name(rueck[cru][ruecki]);
								vector<string> tok; 
								aufSplit(&tok,&ursp,'-');
								ursp.clear(); for(size_t j=1;j<tok.size();j++){ursp+=tok[j];if (j<tok.size()-1) ursp+="-";}
								// <<"ursp: "<<ursp<<endl;
								inse+="('"+ursp+"','"+teln+"','"+zp+"',"+tries+","+ltoan(size)+","+(cru?"1":"0")+"),";
								if (!(ruecki % 100)||ruecki==rueck[cru].size()-1) {
									inse[inse.size()-1]=';';
									//		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_ON);
									RS vgl3(My,"INSERT INTO tmpc VALUES "+inse,ZDB);
									inse.clear();
								} // 							if (ruecki==100||rueck==rueck[cru].size()-1)
							} //           for(ruecki=0;ruecki<rueck[cru].size();ruecki++)
						} // 					for(uchar cru=0;cru<2;cru++)
//						auswe[auswe.size()-1]=')';
						// die laut tmpc uebermittelten Faxe, die in outa als Mißerfolg eintragen sind
						char ***cerg;
						RS kor1(My,"SELECT t.submid p0, t.teln p1, t.zp p2, a.submt p3, t.tries p4, t.erfolg p5, t.size p6, a.docname p7 "
								"FROM `"+touta+"` a RIGHT JOIN tmpc t ON t.submid=a.submid WHERE a.erfolg<>t.erfolg",ZDB);
						if (!kor1.obfehl) {
							size_t zru=0;
							while (cerg=kor1.HolZeile(),cerg?*cerg:0) {
								if (!zru++) {
									cout<<violett<<Tx[T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
									cout<<schwarz<<setw(19)<<"submid"<<"|"<<setw(15)<<Tx[T_Faxnr]<<"|"<<setw(19)<<"zp"<<"|"
										<<setw(19)<<"submt"<<"|"<<setw(5)<<"tries"<<"|"<<setw(6)<<Txk[T_Erfolg]<<"|"<<setw(10)<<"size"<<"|"<<"docname"<<schwarz<<endl;
								} // 								if (!zru++)
								cout<<setw(3)<<zru<<") "<<blau<<setw(14)<<*(*cerg+0)<<"|"<<violett<<setw(15)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(19)<<*(*cerg+2)<<"|"
									<<schwarz<<setw(17)<<*(*cerg+3)<<"|"<<blau<<setw(5)<<*(*cerg+4)<<"|"<<violett<<setw(6)<<*(*cerg+5)<<"|"
									<<blau<<setw(10)<<*(*cerg+6)<<"|"<<violett<<string(*(*cerg+7)).substr(0,55)<<endl;
							} // while (cerg=kor1.HolZeile(),cerg?*cerg:0) 
							RS kor2(My,"UPDATE `"+touta+"` a RIGHT JOIN tmpc t ON t.submid=a.submid SET a.erfolg=t.erfolg where a.erfolg<>t.erfolg",ZDB);
						} // 						if (!kor1.obfehl) 
						RS kor3(My,"SELECT t.submid p0,t.teln p1,t.zp p2,t.tries p3,t.erfolg p4,t.size p5,"
								"IF(ISNULL(asp.original),'',asp.original) p6,"
								"IF(ISNULL(asp.idudoc),0,asp.idudoc) p7,IF(ISNULL(asp.pages),0,asp.pages) p8,"
								"IF(ISNULL(asp.adressat) OR asp.adressat=t.teln,'',asp.adressat) p9 "
								"FROM tmpc t "
								"LEFT JOIN `"+touta+"` a ON a.submid=t.submid "
								"LEFT JOIN `"+altspool+"` asp ON asp.capispooldatei=t.submid "
								"LEFT JOIN `"+touta+"` av ON av.erfolg<>0 AND av.idudoc=asp.idudoc AND av.idudoc<>0 "
								"WHERE ISNULL(a.submid) AND (t.erfolg<>0 OR ISNULL(av.idudoc)) "
								"GROUP BY t.submid",ZDB);
						if (!kor3.obfehl) {
							size_t zru=0;
							while (cerg=kor3.HolZeile(),cerg?*cerg:0) {
								if (!zru++) {
									cout<<violett<<Tx[T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird]<<schwarz<<endl;
									cout<<schwarz<<setw(20)<<"submid"<<"|"<<setw(25)<<"tel'n."<<"|"<<setw(19)<<"zp"<<"|"
										<<setw(5)<<"tries"<<"|"<<setw(6)<<Txk[T_Erfolg]<<"|"<<setw(10)<<"size"<<schwarz<<"|"<<blau<<"docname"<<endl;
								} // 							if (!zru++)
								cout<<setw(4)<<zru<<") "<<blau<<setw(14)<<*(*cerg+0)<<"|"<<violett<<setw(25)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(19)<<*(*cerg+2)<<"|"
									<<violett<<setw(5)<<*(*cerg+3)<<"|"<<blau<<setw(6)<<*(*cerg+4)<<"|"<<violett<<setw(10)<<*(*cerg+5)<<"|"
									<<blau<<string(*(*cerg+6)).substr(0,55)<<endl;
							} // while (cerg=kor3.HolZeile(),cerg?*cerg:0) 
							RS kor4(My,"INSERT INTO `"+touta+"` (erfolg,submt,transe,submid,fsize,retries,rcfax,docname,idudoc,pages,adressat) "
									"SELECT t.erfolg,t.zp,t.zp,t.submid,t.size,t.tries,t.teln,IF(ISNULL(asp.original),'',asp.original),"
									"IF(ISNULL(asp.idudoc),0,asp.idudoc),IF(ISNULL(asp.pages),0,asp.pages),"
									"IF(ISNULL(asp.adressat) OR asp.adressat=t.teln,'',asp.adressat) "
									"FROM tmpc t "
									"LEFT JOIN `"+touta+"` a ON a.submid=t.submid "
									"LEFT JOIN `"+altspool+"` asp ON asp.capispooldatei=t.submid "
									"LEFT JOIN `"+touta+"` av ON av.erfolg<>0 AND av.idudoc=asp.idudoc AND av.idudoc<>0 "
									"WHERE ISNULL(a.submid) AND (t.erfolg<>0 OR ISNULL(av.idudoc)) "
									"GROUP BY t.submid",ZDB);
						} // 						if (!kor3.obfehl)

						// die laut tmpc uebermittelten Faxe, die nicht in outa als uebermittelt eingetragen sind, 
						// und zu denen nicht bereits eine erfolgreiche hylafax-Uebertragung eingetragen ist
						/*
							 RS ntr(My,"SELECT t.submid p0,t.teln p1,a.original p2,unix_timestamp(t.zp) p3,a.hdateidatum p4, a.idudoc p5,t.pages p6 FROM tmpc t "
							 "LEFT JOIN outa o ON t.submid = o.submid LEFT JOIN altspool a ON t.submid=a.hylanr "
							 "LEFT JOIN outa o2 ON o2.submid=a.capispooldatei AND o2.erfolg<>0 WHERE o.erfolg=0 AND t.erfolg<>0 AND ISNULL(o2.submid)",ZDB);
						 */
					} // 							if (rueck[0].size()||rueck[1].size()) 
          break;
        default: // hyla
          //        fdn.clear();
					svec rueck;
          cmd=string("sudo find ")+varsphylavz+" -name 'q*' -print0 "+(obverb?"":"2>/dev/null")+"| /usr/bin/xargs -0 grep -l ^state:7 ";
          rueck.clear();
          systemrueck(cmd,obverb,oblog,&rueck);
          for(ruecki=0;ruecki<rueck.size();ruecki++) {
            size_t pos;
            if ((pos=rueck[ruecki].rfind("/q"))!=string::npos) fdn.insert(rueck[ruecki].substr(pos+2));
          } //           for(ruecki=0;ruecki<rueck.size();ruecki++)
      } // switch (runde)
			/*
			if (0) {
      string sql="SELECT titel p0, tsid p1, submt p2, submid p3, oscht p4, subject p5, docname p6, id p7, fsize p8, pages p9, "
        "devname p10, retries p11, prio p12, rcfax p13, rcname p14, csid p15, sender p16, transs p17, transe p18, Pid p19, eind p20, Erfolg p21 "
        "FROM `"+touta+"` WHERE submid "+(runde?"RLIKE '^[0-9]+$' AND submid<>0":"LIKE '%fax-%.sff'")+" ORDER BY submt";
      RS routa(My,sql);
      if (!routa.obfehl) {
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
                  *(*cerg+3)<<schwarz<<" "<<*(*cerg+2)<<" "<<blau<<*(*cerg+6)<<schwarz;
                ::Log(ausg.str(),1,1);
//                RS vs(My,string("UPDATE `")+touta+"` SET Erfolg= !Erfolg WHERE submid = '"+*(*cerg+3)+"'",ZDB);
              } //               if (fit!=fdn.end())
            } // ((fit!=fdn.end()) != (**(*cerg+21)=='0')) else
          } // if (*(*cerg+3)) if (*(*cerg+20)) if (*(*cerg+21)) 
        } // while (cerg=routa.HolZeile(),cerg?*cerg:0) 
      } // if (!routa.obfehl) 
			} // if (0)
			*/
    } // for(uchar runde=1;runde<2;runde++) 
  } // if (1) 
  Log(violetts+"Ende "+Tx[T_korrigierecapi]+schwarz);
} // korrigierecapi

// Parameter -bwv
// wird aufgerufen in: main
void paramcl::bereinigewv()
{
  Log(violetts+Tx[T_bereinigewv]+schwarz);
  set<string> fdn; // Fax-Dateien
  set<string>::iterator fit; // Iterator dafuer
  //  cmd=string("find \"")+wvz+"\" -maxdepth 1 -type f -iname \"*.pdf\" -printf '%f\n'";
  cmd=string("sudo find \"")+wvz+"\" -maxdepth 1 -type f -printf '%f\n'";
  vector<string> rueck;
  systemrueck(cmd,obverb,oblog,&rueck);
  for(size_t i=0;i<rueck.size();i++) {
    fdn.insert(rueck[i]);
  } 
  //  for(fit=fdn.begin();fit!=fdn.end();++fit) _out<<blau<<*fit<<schwarz<<endl;
  const string vgl="Beispiel 997.doc"; // nicht existente Datei
  ::Log(string(Tx[T_DateienzahlimVz])+blau+ltoan(fdn.size())+schwarz,1,1);
  for(fit=fdn.begin();fit!=fdn.end();++fit) {
    if (*fit==vgl) {
      ::Log(blaus+*fit+schwarz,1,1);
    }
  } //   for(fit=fdn.begin();fit!=fdn.end();++fit)
  for(unsigned runde=0;runde<2;runde++) {
    string sql;
    switch (runde) {
      case 0: sql="SELECT id p0, original p1, origvu p2 FROM `"+spooltab+"`"; break;
      case 1: sql="SELECT eind p0, docname p1, Erfolg p2 FROM `"+touta+"`"; break;
    } //     switch (runde)
    RS rsp(My,sql,ZDB);
    char ***cerg;
    while (cerg=rsp.HolZeile(),cerg?*cerg:0) {
      for(unsigned cnr=1;cnr<3;cnr++) {
        if (cnr==1 || !runde) { // nur die erste Tabelle hat zwei Spalten mit Dateinamen
          if (*(*cerg+cnr)) {
            string dbdocname=*(*cerg+cnr);
            for (unsigned aru=0;aru<5;aru++) {
              string stamm,exten;
              getstammext(&dbdocname,&stamm,&exten);
              if (!aru || !exten.empty()) {
                if (aru) {
                  switch (aru) {
                    case 1: dbdocname=stamm+".doc"; break;
                    case 2: dbdocname=stamm+".xls"; break;
                    case 3: dbdocname=stamm+".jpg"; break;
                    case 4: dbdocname=stamm+".tif"; break;
                  } //                   switch (aru)
                } //                 if (aru)
                if ((fit=fdn.find(dbdocname))!=fdn.end()) { // wenn Datenbankeintrag in der sortierten Mengen der Dateinamen enthalten
                  struct stat entryfit={0};
                  const string quel=wvz+vtz+*fit;
                  if (!lstat(quel.c_str(),&entryfit)) { // duerfte immer erfuellt sein
                    if (entryfit.st_size) { // keine 0-Bytes-Dateien kopieren
                      if (runde) { // wenn nicht in der Spool-Tabelle
                        string zlvz;
                        //                        if (runde==1) zlvz=getzielvz(quel); else if (runde==2) zlvz=nvz;
                        if (runde==1) {
                          if (**(*cerg+2)=='1') zlvz=getzielvz(quel); else if (**(*cerg+2)=='0') zlvz=nvz;
                        }
                        unsigned vfehler=0;
                        if (!zlvz.empty()) {
                          const string zdt=zlvz+vtz+*fit;
                          dorename(quel,zdt,cuser,&vfehler,1,1);
                          if (vfehler) {
                            ::Log(rots+Tx[T_Fehler_beim_Verschieben_Ausrufezeichen]+": "+ltoan(vfehler)+schwarz,1,1);
                            exit(14);
                          } // if (vfehler)
                          fdn.erase(fit);
                          break;
                        } // if (!zlvz.empty()) 
                      } else { // if (runde) 
                        fdn.erase(fit); // die in der Spool-Tabelle genannten Dateien stehen lassen
                      } //    if (runde) else
                      //     ::Log(string(ltoan(entryfit.st_size))+" "+(runde==2?dblau:runde==1?blau:rot)+*fit+schwarz,1,1);
                      ::Log(string(ltoan(entryfit.st_size))+" "+(runde?(**(*cerg+2)=='1'?blau:gruen):rot)+*fit+schwarz,1,1);
                    } else {
                      ::Log(string(Tx[T_0Bytes])+gruen+wvz+vtz+*fit+schwarz+"'",1,1);
                    } // if (!lstat(quel.c_str(),&entryfit)) else
                  } // if (!lstat(quel.c_str(),&entryfit)) 
                } // if ((fit=fdn.find(dbdocname))!=fdn.end()) 
                if (!runde) break;
              } // if (!aru || !exten.empty()) 
            } // for (unsigned aru=0;aru<3;aru++) 
          } // if (*(*cerg+cnr)) 
        } // if (cnr==1 || !runde) 
      } // for(unsigned cnr=1;cnr<3;cnr++) 
    } // while (cerg=rsp.HolZeile(),cerg?*cerg:0) 
  } // for(unsigned runde=0;runde<3;runde++) 
} // bereinigewv

// Parameter -anhl
// wird aufgerufen in: main
void paramcl::anhalten()
{
  Log(violetts+Tx[T_anhalten]+schwarz);
  // crontab
  setztmpc();
  const string befehl=("bash -c 'grep \""+saufr+"\" -q <(sudo crontab -l)'&&(sudo crontab -l|sed '/"+saufr+"/d'>")+tmpc+";sudo crontab "+tmpc+");true";
  systemrueck(befehl,obverb,oblog);
  // services
  /*
     befehl="sudo systemctl stop capisuite hylafax-faxq hylafax-hfaxd hylafax-faxgetty-"+hmodem+" hylafax >/dev/null 2>&1; true";
     systemrueck(befehl,obverb,oblog);
   */

  hylasv1();
  hylasv2(hysrc);
  capisv();
  if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog);
  if (shfaxd) shfaxd->stopdis(obverb,oblog);
  if (sfaxq) sfaxq->stopdis(obverb,oblog);
  if (shylafaxd) shylafaxd->stopdis(obverb,oblog);
  if (scapisuite) scapisuite->stopdis(obverb,oblog);
} // void paramcl::anhalten()

// wird aufgerufen in: main
int paramcl::loeschefax()
{
	Log(violetts+Tx[T_loeschefax]+schwarz);
	vector<fsfcl> fsfv;
	faxord=0;
	string ergnr,erg;
	char*** cerg;
	/*
	RS zul(My,string("SELECT CONCAT_WS(' ',LEFT(CONCAT(IF(ISNULL(original),'NULL',original),SPACE(50)),50),"
				"RIGHT(CONCAT(SPACE(15),IF(ISNULL(capispooldatei),'NULL',capispooldatei)),15),")+
			"CONCAT('Capidials:',RIGHT(CONCAT(SPACE(4),IF(ISNULL(capidials),'NULL',capidials)),4)),"
			"CONCAT('Hyla:',RIGHT(CONCAT(SPACE(5),IF(ISNULL(hylanr),'NULL',hylanr)),5)), "
			"CONCAT('Hyladials:',RIGHT(CONCAT(SPACE(4),IF(ISNULL(hyladials),'NULL',hyladials)),4))) p0,"
			"id p1,"
			"IF(ISNULL(capispooldatei),'NULL',capispooldatei) p2,"
			"IF(ISNULL(capispoolpfad),'"+cfaxusersqvz+"',capispoolpfad) p3,"
		 	"hylanr p4 FROM `"+spooltab+"` ORDER BY id",ZDB);
	*/
	RS zul(My,string("SELECT CONCAT_WS(' ',LEFT(CONCAT(original,SPACE(50)),50),"
				"RIGHT(CONCAT(SPACE(15),capispooldatei),15),")+
			"CONCAT('Capidials:',RIGHT(CONCAT(SPACE(4),capidials),4)),"
			"CONCAT('Hyla:',RIGHT(CONCAT(SPACE(5),hylanr),5)), "
			"CONCAT('Hyladials:',RIGHT(CONCAT(SPACE(4),hyladials),4))) p0,"
			"id p1,"
			"capispooldatei p2,"
			"IF(capispoolpfad='','"+cfaxusersqvz+"',capispoolpfad) p3,"
		 	"hylanr p4 FROM `"+spooltab+"` ORDER BY id",ZDB);
	while (cerg=zul.HolZeile(),cerg?*cerg:0) {
		if (*(*cerg+0) && *(*cerg+1)) {
			::Log(string("Fax ")+blau+ltoan(++faxord)+schwarz+": "+*(*cerg+0),1,1);
			/*3*/fsfv.push_back(fsfcl(*(*cerg+1),*(*cerg+2),*(*cerg+4),*(*cerg+3)));
		} // if (*(*cerg+0) && *(*cerg+1)) 
	} // while (cerg=zul.HolZeile(),cerg?*cerg:0) 
	size_t ivorher=fsfv.size();
	sammlecapi(&fsfv);
	for(size_t i=ivorher;i<fsfv.size();i++) {
		//      if (i==ivorher)  ::Log("Capi:",1,0);
		stringstream aus;
		fsfv[i].capiausgeb(&aus,maxcdials,1,obverb,oblog,++faxord);
		const string auss=aus.str();
		::Log(auss,1,oblog);
	} // 	for(size_t i=ivorher;i<fsfv.size();i++)
	ivorher=fsfv.size();
	sammlehyla(&fsfv);
	for(size_t i=ivorher;i<fsfv.size();i++) {
		//      if (i==ivorher) ::Log("Hyla:",1,0);
		stringstream aus;
		fsfv[i].hylaausgeb(&aus,this,0,1,obverb,1,oblog);
		const string auss=aus.str();
		::Log(auss,1,oblog);
	} //   for(size_t i=ivorher;i<fsfv.size();i++) {

	if (!nrzf) {
		if (fsfv.size()) {
			ergnr=Tippzahl(Tx[T_Welches_Fax_soll_geloescht_werden]);
			if (ergnr=="0") return 0;
			size_t nr=atol(ergnr.c_str())-1;
			if (nr>=0 && nr<fsfv.size()) {
				if (Tippob(string(Tx[T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch])+gruen+ergnr+schwarz+Tx[T_wirklich_geloescht_werden],"n")) {
					int zdng=0; // Zahl der nicht geloeschten
					if (fsfv[nr].capisd!="NULL" && !fsfv[nr].capisd.empty()) {
						zdng+=fsfv[nr].loeschecapi(obverb,oblog);
						Log(blaus+"capi: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_Capispooldatei]+
								schwarz+fsfv[nr].capisd);
					}
					if (fsfv[nr].hylanr!="NULL" && !fsfv[nr].hylanr.empty()) {
						zdng+=fsfv[nr].loeschehyla(this,obverb,oblog);
						Log(blaus+"hyla: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_hylanr]+schwarz+fsfv[nr].capisd);
					}
					Log(blaus+Tx[T_Gesamt]+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng));
					struct stat entrysend={0};
					fsfv[nr].setzcapistat(this,&entrysend);
					string protdakt;
					uchar hyla_uverz_nr=1;
					/*fsfv[nr].*/setzhylastat(&fsfv[nr], &protdakt, &hyla_uverz_nr, 0, 0, 0); // hyla_uverz_nr, obsfehlt
					Log(violetts+"capistat: "+schwarz+FxStatS(&fsfv[nr].capistat)+violett+", hylastat: "+schwarz+FxStatS(&fsfv[nr].hylastat));
					if ((!zdng || (fsfv[nr].capistat==fehlend && fsfv[nr].hylastat==fehlend)) && !fsfv[nr].id.empty()) {
						RS loe(My,"DELETE FROM `"+spooltab+"` WHERE id="+fsfv[nr].id,-obverb);
					}
				} // if (Tippob(string(Tx[T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch])+violett+ergnr+schwarz+Tx[T_wirklich_geloescht_werden],"n")) 
			} // if (nr>=0 && nr<fsfv.size()) 
		} else {
			::Log(Tx[T_Kein_Fax_zum_Loeschen_vorhanden],1,oblog);
		} // if (fsfv.size()) 
	} // !nrzf
	return 1;
} // int paramcl::loeschefax()

// wird aufgerufen in: main
int paramcl::loeschewaise()
{
	Log(blaus+Tx[T_loeschewaise]+schwarz);
	vector<string> allec;
	vector<string> ids;
	char*** cerg;
	RS su(My,"SELECT original p0, capispooldatei p1, hylanr p2, id p3 FROM `"+spooltab+"`");
	while (cerg=su.HolZeile(),cerg?*cerg:0) {
		if (*(*cerg+0)) {
			struct stat entryo={0};
			if (!lstat((wvz+vtz+*(*cerg+0)).c_str(),&entryo)) continue; // Wenn es die Datei im Warteverzeichnis gibt
			if (*(*cerg+1)) if (!lstat((cfaxusersqvz+vtz+*(*cerg+1)).c_str(),&entryo)) continue; // wenn eine Capispooldatei drinsteht und es sie gibt
			if (*(*cerg+2)) if (!lstat((hsendqvz+"/q"+*(*cerg+2)).c_str(),&entryo)) continue; // wenn eine Hylaspooldatei drinsteht und es sie gibt
			if (*(*cerg+3)) ids.push_back(*(*cerg+3));
		} // if (*(*cerg+0)) 
	} // while (cerg=su.HolZeile(),cerg?*cerg:0) 
	for(size_t i=0;i<ids.size();i++) {
		RS loe(My,"DELETE FROM `"+spooltab+"` WHERE id="+ids[i]);
	}
	return 0;
} // int paramcl::loeschewaise()

// wird aufgerufen in: main
int paramcl::loescheallewartende()
{
	Log(blaus+Tx[T_loescheallewartenden]+schwarz);
	int erg=0;
	vector<string> allec;
	struct stat entryvz={0};
	if (!lstat(cfaxusersqvz.c_str(),&entryvz)) {
		cmd=string("sudo find '")+cfaxusersqvz+"/' -maxdepth 1 -type f -iname 'fax-*.*'";
		systemrueck(cmd,obverb,oblog,&allec);
		erg+=allec.size();
		for(size_t i=0;i<allec.size();i++) {
			tuloeschen(allec[i],cuser,1,oblog);
			if (allec[i].find(".sff")!=string::npos) {
				const string fname=base_name(allec[i]);
				RS loe(My,"DELETE FROM `"+spooltab+"` WHERE capispooldatei='"+fname+"'");
			}
		} // for(size_t i=0;i<allec.size();i++) 
	} // if (!lstat(cfaxusersqvz.c_str(),&entryvz)) 
	//  cmd=string("rm ")+cfaxuservz+vtz+cuser+vtz+"sendq"+vtz+"fax-*.*"; //  "/var/spool/capisuite/users/<user>/sendq";
	if (!lstat(hsendqvz.c_str(),&entryvz)) {
		cmd=string("sudo find '")+hsendqvz+"' -maxdepth 1 -type f -iname 'q*' -printf '%f\\n'";
		vector<string> alled;
		systemrueck(cmd,obverb,oblog, &alled);
		erg+=alled.size();
		for(size_t i=0;i<alled.size();i++) {
			string transalle=alled[i];
			ersetzAlle(&transalle,"q","");  
			/*4*/fsfcl zuloe(transalle);
			if (!zuloe.loeschehyla(this,obverb,oblog)) {
				//      cmd=string("faxrm ")+transalle;
				//      if (systemrueck(cmd,obverb,oblog)) KLA
				RS loe(My,"DELETE FROM `"+spooltab+"` WHERE hylanr="+transalle,ZDB);
			}
		} // for(size_t i=0;i<alled.size();i++) 
	} // if (!lstat(hsendqvz.c_str(),&entryvz)) 
	return erg;
} // int paramcl::loescheallewartende()

// wird aufgerufen in: main (2x)
void paramcl::tu_lista(const string& oberfolg, const string& submids)
{
// "... submid id ()" wuerde zu Mysql-Fehler fuehren
	Log(violetts+Tx[T_tu_lista]+schwarz);
	char ***cerg;
	RS lista(My,string("SELECT Ueberm p0, Submid p1, Faxname p2, Empfaenger p3, Fax p4, Erfolg p5 FROM (")+
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') Ueberm, Submid, RIGHT(CONCAT(space(75),LEFT(Docname,75)),75) Faxname, "
			"RIGHT(CONCAT(SPACE(30),LEFT(rcname,30)),30) Empfaenger, rcfax Fax, Erfolg, transe "
			"FROM `"+touta+"` WHERE "+(submids.length()<=2?"Erfolg = "+oberfolg+" ":"submid in "+submids+" ")+
			" ORDER BY transe DESC"+(submids.length()<=2?" LIMIT "+dszahl:"")+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",ZDB);

	if (submids.length()<=2)
		cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<(oberfolg=="1"?Tx[T_erfolgreich]:Tx[T_erfolglos])<<Tx[T_versandte_Faxe]<<schwarz<<endl;
	while (cerg=lista.HolZeile(),cerg?*cerg:0) {
		cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(14)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(65)<<*(*cerg+2)<<"|"
			<<schwarz<<setw(30)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
	} // while (cerg=lista.HolZeile(),cerg?*cerg:0) 
} // tu_lista

// wird aufgerufen in: main
void paramcl::tu_listi()
{
	Log(violetts+Tx[T_tu_listi]+schwarz);
	char ***cerg;
	RS listi(My,"select p0, p1, p2, p3, p4 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') p0,RIGHT(CONCAT(SPACE(85),LEFT(titel,85)),85) p1,"
			"fsize p2,tsid p3,id p4, transe FROM `"+tinca+"` i "
			" ORDER BY transe DESC LIMIT "+dszahl+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",ZDB);
	cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<Tx[T_empfangene_Faxe]<<schwarz<<endl;
	while (cerg=listi.HolZeile(),cerg?*cerg:0) {
		cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(85)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(17)<<*(*cerg+2)<<"|"
			<<schwarz<<setw(17)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
	} // while (cerg=listi.HolZeile(),cerg?*cerg:0) 
} // tu_listi

// wird aufgerufen in: main
void paramcl::suchestr()
{
	Log(violetts+Tx[T_suchestr]+schwarz);
	const string scnv=" CONVERT(\"%"+suchstr+"%\" USING utf8) ";
	for(int erf=1;erf>=0;erf--) {
		const string oberfolg=ltoan(erf);
		char ***cerg;
		RS lista(My,string("SELECT Ueberm p0, Submid p1, Faxname p2, Empfaenger p3, Fax p4, Erfolg p5 FROM (")+
				"SELECT * FROM ("
				"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') Ueberm, Submid, RIGHT(CONCAT(space(75),LEFT(Docname,75)),75) Faxname, "
				"RIGHT(CONCAT(SPACE(30),LEFT(rcname,30)),30) Empfaenger, rcfax Fax, Erfolg, transe "
				"FROM `"+touta+"` WHERE Erfolg = "+oberfolg+" AND (Docname LIKE"+scnv+"OR rcname LIKE"+scnv+"OR rcfax LIKE"+scnv+""
				"OR submid LIKE"+scnv+" OR transe LIKE CONVERT(\"%"+suchstr+"%\" USING utf8)) "
				" ORDER BY transe DESC LIMIT "+dszahl+") i "
				" ORDER BY transe LIMIT 18446744073709551615) i",ZDB);
		ulong zeile=0;
		while (cerg=lista.HolZeile(),cerg?*cerg:0) {
			if (!zeile)
				cout<<gruen<<Tx[T_Letzte]<<blau<<dszahl<<gruen<<(oberfolg=="1"?Tx[T_erfolgreich]:Tx[T_erfolglos])<<Tx[T_versandte_Faxe]<<
					Tx[T_mitstr]<<blau<<suchstr<<"':"<<schwarz<<endl;
			zeile++;
			cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(14)<<*(*cerg+1)<<schwarz<<"|"<<(erf?blau:violett)<<setw(65)<<*(*cerg+2)<<"|"
				<<schwarz<<setw(30)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
		} // while (cerg=lista.HolZeile(),cerg?*cerg:0) 
	} //   for(int erf=1;erf>=0;erf--) 

	char ***cerg;
	RS listi(My,"select p0, p1, p2, p3, p4 FROM ("
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') p0,RIGHT(CONCAT(SPACE(85),LEFT(titel,85)),85) p1,"
			"fsize p2,tsid p3,id p4, transe FROM `"+tinca+"` i WHERE (titel LIKE"+scnv+""
			"OR tsid LIKE"+scnv+"OR transe LIKE"+scnv+"OR id LIKE CONVERT(\"%"+suchstr+"%\" USING utf8))"
			" ORDER BY transe DESC LIMIT "+dszahl+") i "
			" ORDER BY transe LIMIT 18446744073709551615) i",ZDB);
	ulong zeile=0;
	while (cerg=listi.HolZeile(),cerg?*cerg:0) {
		if (!zeile)
			cout<<gruen<<Tx[T_Letzte]<<blau<<dszahl<<gruen<<Tx[T_empfangene_Faxe]<<Tx[T_mitstr]<<blau<<suchstr<<"':"<<schwarz<<endl;
		zeile++;
		cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(85)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(17)<<*(*cerg+2)<<"|"
			<<schwarz<<setw(17)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
	} // while (cerg=listi.HolZeile(),cerg?*cerg:0) 

	RS spool(My,string("SELECT p0, p1, p2, p3, p4 FROM (")+
			"SELECT * FROM ("
			"SELECT DATE_FORMAT(if(hdateidatum=0,cdateidatum,hdateidatum),'%d.%m.%y %H:%i:%s') p0,"
			"RIGHT(CONCAT(SPACE(85),LEFT(origvu,85)),85) p1,"
			"IF(capidials=0,hyladials,capidials) p2,IF(hylanr=0,capispooldatei,hylanr) p3,id p4, if(hdateidatum=0,cdateidatum,hdateidatum) so "
			"FROM `"+spooltab+"` i WHERE (origvu LIKE"+scnv+"OR original LIKE"+scnv+"OR telnr LIKE"+scnv+"OR capispooldatei LIKE"+scnv+
			"OR cdateidatum LIKE CONVERT(\"%"+suchstr+"%\" USING utf8))"
			" ORDER BY so DESC LIMIT "+dszahl+") i "
			" ORDER BY so LIMIT 18446744073709551615) i",ZDB);
	zeile=0;
	while (cerg=spool.HolZeile(),cerg?*cerg:0) {
		if (!zeile)
			cout<<gruen<<Tx[T_Letzte]<<blau<<dszahl<<gruen<<Tx[T_wartende_Faxe]<<Tx[T_mitstr]<<blau<<suchstr<<"':"<<schwarz<<endl;
		zeile++;
		cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(85)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(17)<<*(*cerg+2)<<"|"
			<<schwarz<<setw(17)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
	} // while (cerg=listi.HolZeile(),cerg?*cerg:0) 
} // suchestr

// verwendet in DateienHerricht(), empfarch()
int paramcl::pruefsoffice(uchar mitloe/*=0*/)
{
	Log(violetts+Tx[T_pruefsoffice]+schwarz);
	static uchar sofficegeprueft=0;
	static int sofficeda=0;
	if (mitloe || !sofficegeprueft) {
		//              systemrueck("which zypper 2>/dev/null && zypper -n in soffice || "
		//                          "{ which apt-get 2>/dev/null && apt-get -y install soffice; }",obverb,oblog);
		if (mitloe) linst.douninst("libreoffice-base",obverb,oblog);
		sofficeda=!linst.doinst("libreoffice-base",obverb,oblog,"soffice");
		sofficegeprueft=1;
	} //   if (!sofficegeprueft)
	return sofficeda;
} // int paramcl::pruefsoffice()

// verwendet in DateienHerricht
int paramcl::pruefconvert()
{
	Log(violetts+Tx[T_pruefconvert]+schwarz);
	static uchar convertgeprueft=0;
	static int convertda=0;
	if (!convertgeprueft) {
		//              systemrueck("which zypper 2>/dev/null && zypper -n in convert || "
		//                          "{ which apt-get 2>/dev/null && apt-get -y install convert; }",obverb,oblog);
		convertda=!linst.doinst("imagemagick",obverb,oblog,"convert");
		convertgeprueft=1;
	} //   if (!convertgeprueft)
	return convertda;
} // int paramcl::pruefconvert()

// aufgerufen in pruefocr()
void paramcl::pruefunpaper()
{
	Log(violetts+Tx[T_pruefunpaper]+schwarz);
	double vers=progvers("unpaper",obverb,oblog);
	if (vers<6.1) {
		linst.doinst("libxslt-tools",obverb,oblog,"xsltproc");
		if (linst.pruefipr()==dnf||linst.pruefipr()==yum) {
			// sudo rpm -Uvh http://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-stable.noarch.rpm 
			//               http://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-stable.noarch.rpm
			// systemrueck("sudo rpm -Uvh https://github.com/libelle17/rpmfusion_copy/blob/master/rpmfusion-free-release-stable.noarch.rpm "
			//                          " https://github.com/libelle17/rpmfusion_copy/blob/master/rpmfusion-nonfree-release-stable.noarch.rpm",obverb,oblog);
			const string rpf="rpmfusion_copy";
			holvomnetz(rpf);
			kompilbase(rpf,s_gz);
			systemrueck("sh -c 'cd \""+instvz+vtz+rpf+"\"&& sudo rpm -Uvh ./rpmfusion*rpm'",obverb+1,oblog);
			linst.doinst("ffmpeg",obverb,oblog);
			linst.doinst("ffmpeg-devel",obverb,oblog);
			linst.doinst("ffmpeg-compat",obverb,oblog);
		} else {
			linst.doggfinst("libavformat-devel",obverb+1,oblog);
			if (linst.pruefipr()==apt) {
				linst.doggfinst("pkg-config",obverb+1,oblog);
			}
		} // 		if (linst.pruefipr()==dnf||linst.pruefipr()==yum)
		/*if (linst.pruefipr()==apt||linst.pruefipr()==dnf||linst.pruefipr()==yum)*/ 
		holvomnetz("unpaper_copy");
		if (vers) systemrueck("which unpaper && rm $(which unpaper) && hash -r",obverb,oblog);
		kompiliere("unpaper_copy",s_gz);
	} // 						if (!urueck.size()||vers<6.1)
} // void paramcl::pruefunpaper()

// verwendet in empfarch() (2x) und DateienHerricht() (2x)
int paramcl::pruefocr()
{
	Log(violetts+Tx[T_pruefocr]+schwarz);
	if (!obocrgeprueft) {
		uchar tda=0, deuda=0, engda=0, osdda=0;
		systemrueck("sudo ldconfig "+lsys.getlib64(),obverb,oblog);
		string tpfad;
		svec rueck;
		if (obprogda("tesseract",obverb,oblog,&tpfad)) {
			tda=1;
			systemrueck(tpfad+" --list-langs 2>&1",obverb,oblog,&rueck); // gibt das normale Ergebnis als Fehlermeldung aus!
			if (!rueck.size()) tda=0; else if (rueck[0].find("List of available")) tda=0;
		}
		if (!tda) {
			linst.doinst("tesseract-ocr",obverb,oblog);
			systemrueck("sudo ldconfig "+lsys.getlib64(),obverb,oblog);
		} else {
			for(size_t i=1;i<rueck.size();i++) {
				if (rueck[i]=="deu") deuda=1;
				else if (rueck[i]=="eng") engda=1;
				else if (rueck[i]=="osd") osdda=1;
			} //       for(size_t i=1;i<rueck.size();i++)
		} //     if (!tda)
		if (!deuda) linst.doinst("tesseract-ocr-traineddata-german",obverb,oblog);
		if (!engda) linst.doinst("tesseract-ocr-traineddata-english",obverb,oblog);
		if (!osdda) linst.doinst("tesseract-ocr-traineddata-orientation_and_script_detection",obverb,oblog);

		pruefunpaper();
		linst.doggfinst("qpdf");
		// uchar alt=0;
		uchar ocrzuinst=1;
		// zu tun: pruefen statt dessen ~/autofax/ocrv/bin/ocrmypdf
		struct stat ostat={0};
		virtvz=instvz+"/ocrv";
		ocrmp=virtvz+"/bin/ocrmypdf";
		if (!lstat(ocrmp.c_str(),&ostat))
//		if (obprogda("ocrmypdf",obverb,oblog)) 
			if (progvers("ocrmypdf",obverb,oblog)>4.40) 
				ocrzuinst=0;
		if (ocrzuinst) {
			if (linst.pruefipr()==dnf||linst.pruefipr()==yum||linst.pruefipr()==zypper||linst.pruefipr()==apt) {
				// in fedora pip statt pip3
				linst.doinst("python3-pip",obverb+1,oblog,"pip3");
				linst.doinst("python3-devel",obverb+1,oblog,"/usr/bin/python3-config");
				linst.doggfinst("gcc");
				struct stat lffi={0};
				if (lstat("/usr/lib64/libffi.so",&lffi)) {
					if (linst.obfehlt("libffi48-devel",obverb+1,oblog))
						linst.doggfinst("libffi-devel",obverb+1,oblog);
				}
				if (linst.pruefipr()==dnf||linst.pruefipr()==yum) 
					linst.doggfinst("redhat-rpm-config",obverb+1,oblog);
				linst.doinst("ghostscript",obverb+1,oblog,"gs");
				systemrueck("sudo python3 -m pip install --upgrade setuptools pip");
//				systemrueck("sudo python3 -m pip install --upgrade ocrmypdf");  // http://www.uhlme.ch/pdf_ocr
				// python3 -m venv ocrvenv
				// python3 -m venv --upgrade ocrvenv
				// source ocrvenv/bin/activate
				// sudo pip3 install ocrmypdf
				systemrueck("sudo sh -c 'python3 -m venv \""+virtvz+"\";"
						"python3 -m venv --upgrade \""+virtvz+"\";"
						"source \""+virtvz+"/bin/activate\";"
						"pip3 install --upgrade pip;"
						"pip3 install ocrmypdf;"
						"deactivate;"
//						"grep \"sudo rm -rf \\\""+virtvz+"\\\"\" \""+unindt+"\"||printf \"sudo rm -rf \\\""+virtvz+"\\\"\\n\">>\""+unindt+"\";"
//						"grep ocrmypdf \""+unindt+"\"||printf \"sudo pip3 uninstall --yes ocrmypdf\\n\">>\""+unindt+"\";"
//						"||sed -i \"/ python3/isudo pip3 uninstall --yes ocrmypdf\" \""+unindt+"\""
						"'",obverb,oblog);
						anfgggf(unindt,"sudo rm -rf \""+virtvz+"\"");
						anfgggf(unindt,
						"sudo sh -c 'source \""+virtvz+"/bin/activate\";"
						"sudo pip3 uninstall --yes ocrmypdf;"
						"deactivate;'");
						
				// sudo pip3 uninstall --yes ocrmypdf
				// sudo dnf install ./ghostscript-9.16-4.fc24.i686.rpm
				//// sudo dnf -y install ghostscript // ghostscript 9.20 geht nicht mit pdf/a und overwrite
#ifdef sonstige
			} else {
				if (!linst.doggfinst("python3-devel",obverb+1,oblog)) {
					if (!linst.doinst("python3-pip",obverb+1,oblog,"pip3")) {
						lsysen system=lsys.getsys(obverb,oblog);
						if (system==deb) {
							linst.doggfinst("pkg-config",obverb+1,oblog);
							linst.doggfinst("python3-setuptools",obverb+1,oblog);
							linst.doggfinst("libffi-dev",obverb+1,oblog);
							linst.doggfinst("libssl-dev",obverb+1,oblog);
						}
						const string proj="ocrmypdf_copy";
						const string srcvz=instvz+vtz+proj+".tar.gz";
						holvomnetz(proj);
						if (!kompilbase(proj,s_gz)) {
							// sudo pip3 install image PyPDF2 ruffus reportlab cryptography cffi
							// sudo PKG_CONFIG_PATH=/usr/lib64/ffmpeg-compat/pkgconfig pkg-config --cflags libavcodec
							// moegliche weitere Befehle:
							// sudo dnf -y --reinstall install python3-pip
							// sudo dnf clean all
							// sudo dnf -y update
							// sudo pip install -U setuptools
							// dnf install mupdf mupdf-devel
							// pyvenv venv
							// source venv/bin/activate
							// .. pip3 install image PyPDF2 ruffus reportlab M2Crypto cryptography cffi ocrmypdf
							//  pip install --upgrade pip
							// pip3 install --upgrade git+https://github.com/jbarlow83/OCRmyPDF.git
							// /home/schade/autofax/venv/bin/pip3 install --upgrade git+https://github.com/jbarlow83/OCRmyPDF.git
							// sudo python3 -m pip install ocrmypdf
							// dnf install python3-devel (fuer Python.h)
							// sudo dnf -y install libffi libffi-devel (fuer ffi.h)
							// CFLAGS=-I/usr/include/libffi/include ./autofax/venv/bin/pip3 install pyOpenSSL
							// sudo python3 -m pip install ocrmypdf
							// sudo dnf -y install qpdf

							pruefunpaper();
							systemrueck("sh -c 'cd \""+instvz+vtz+proj+
									"\" && sudo -H python3 -m pip install image PyPDF2 ruffus reportlab M2Crypto cryptography cffi ocrmypdf'", obverb,oblog);
							linst.doinst("unpaper",obverb,oblog);
						} //    if (!kompilbase(was,endg))
					} //       if (!linst.doinst("python3-pip",obverb+1,oblog,"pip3"))
				} //     if (!linst.doggfinst("python-devel",obverb+1,oblog))
#endif
			} // if (linst.pruefipr()==dnf)
		} //     		if (ocrzuinst)
		unpaperfuercron();
		obocrgeprueft=1;
	} // if (!obocrgeprueft) 
	return 0;
} // int paramcl::pruefocr()

// ocrmypdf laueft z.T. nicht aus einam Programm, das aus cron aufgerufen wird, wenn sich nicht im selben Verzeichnis unpaper findet
void paramcl::unpaperfuercron()
{
 const string ocr="ocrmypdf", unp="unpaper";
 string prog;
 if (obprogda(ocr,obverb,oblog,&prog)) {
	const string uppfad=dir_name(prog)+"/"+unp;
	struct stat lst={0};
	if (lstat(uppfad.c_str(),&lst)) {
	 if (obprogda(unp,obverb,oblog,&prog)) {
	  systemrueck("sudo ln -s '"+prog+"' '"+uppfad+"'",obverb,oblog);
	 } // 	 if (obprogda(unp,obverb,oblog,&prog))
	} // 	if (lstat(uppfad.c_str(),&lst))
 } //  if (obprogda(ocr,obverb,oblog,&prog))
} // void paramcl::unpaperfuercron()

// in Dateinherricht und empfarch (2x)
int paramcl::zupdf(const string* quellp, const string& ziel, ulong *pseitenp/*=0*/, const int obocr/*=1*/, const int loeschen/*=1*/) // 0=Erfolg
{
	Log(violetts+Tx[T_zupdf]+schwarz+" '"+blau+*quellp+schwarz+"' '"+blau+ziel+schwarz+"'");
	int erg=1;
	string stamm,exten; // , *quellp=&quell;
	getstammext(quellp,&stamm,&exten);
	const int keinbild= (exten=="doc"||exten=="xls"||exten=="txt"||exten=="odf"||exten=="ppt"||exten=="docx"||exten=="htm"||exten=="html");
	const string* lqp=quellp; // laufender quell-pointer
	for(int aru=0;aru<2;aru++) {
		if (/*aru||*/!keinbild) {
			if (obocr) {
				if (!pruefocr()) {
				  svec rueck;
					string cmd=string(ocrmp+" -rcsl ")+(langu=="d"?"deu":"eng")+" \""+*lqp+"\" \""+ziel+"\" 2>&1";
					int zerg=systemrueck(cmd,obverb,oblog,&rueck,0,wahr,"",0,1);
					if (zerg==5) zerg=systemrueck("sudo "+cmd,obverb,oblog,&rueck,0,wahr,"",0,1); // kein Schreibrecht im Verzeichnis
					if (!zerg) {
						erg=0; // nicht umgekehrt
						for(unsigned uru=0;uru<rueck.size();uru++) {
						 if (rueck[uru].find("ERROR")!=string::npos) {
						  erg=1;
							break;
						 } // 						 if (rueck[uru].find("ERROR")!=string::npos)
						} // 						for(unsigned uru=0;uru<rueck.size();uru++)
					} // 					if (!systemrueck(string("ocrmypdf -rcsl ")+...
					if (!erg) {
					 struct stat lziel={0};
					 erg=lstat(ziel.c_str(),&lziel);
					} // 					if (!erg)
					if (!erg) {
						if (chmod(ziel.c_str(),S_IRWXU|S_IRWXG|S_IRWXO)) 
							systemrueck("sudo chmod +r \""+ziel+"\"",obverb,oblog);
						break;
					} // 					if (!erg)
				} // pruefocr()
			} // if (obocr)
		} // 		if (!keinbild)
		if (aru) break; // 1,5 Runden maximal benoetigt
		if (erg) {
			string cmd0, cmd;
			for(unsigned runde=1;runde<=2;runde++) {
				cmd.clear();
				string pname;
				switch ((runde+keinbild)%2) {
					case 0: 
						// 5.12.16 opensuse: bearbeitet jetzt nur (noch?) die erste Seite!
						pname="soffice";
						if (pruefsoffice()) {
							cmd0="cd $HOME; ";
							cmd="soffice --headless --convert-to pdf --outdir \""+dir_name(ziel)+"\" \""+*quellp+"\" 2>&1";
						} // 						if (pruefsoffice())
						break; // Ergebnis immer 0
					case 1: 
						pname="convert";
						if (pruefconvert()) {
							cmd0.clear();
							cmd=string("sudo convert \""+*quellp+"\" \""+ziel+"\""); 
						} // 						if (pruefconvert())
						break;
				} // switch (runde) 
				if (!cmd.empty()) {
					vector<string> umwd;
					if ((erg=systemrueck(cmd0+cmd, obverb,oblog,&umwd))) {
						for(unsigned uru=0;uru<umwd.size();uru++) {
							if (umwd[uru].find("failed to read path from javaldx")!=string::npos) {
								erg=systemrueck(cmd0+"sudo "+cmd, obverb,oblog);
								/* int altobverb=obverb; obverb=1; pruefsoffice(1); obverb=altobverb; */
							} // 					  if (umwd[uru].find("javaldx failed")!=string::npos)
						} // 					 for(unsigned uru=0;uru<umwd.size();uru++)
					} // 					if ((erg=systemrueck(cmd, obverb,oblog,&umwd)))
					struct stat entryziel={0};
					erg=lstat(ziel.c_str(),&entryziel); 
					::Log(string(Tx[T_Umwandlungvon])+blau+*quellp+Tx[T_inPDFmit]+tuerkis+pname+schwarz+
							Tx[T_beendetErgebnis]+(erg?rots+Tx[T_misserfolg]:blaus+Tx[T_Erfolg_af])+schwarz, 1||erg,(erg?1:oblog));
					if (!erg) break;
				} // if (cmd.empty()) erg=1; else 
			} // for(unsigned runde=1;runde<=2;runde++) 
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
		attrangleich(ziel,*quellp);
		// falls !erg und Seitenzahl gleich, dann tif loeschen
		svec rueck;
		if (pseitenp) {
			// pdf: pdfinfo (ubuntu und fedora: poppler-utils, opensuse: poppler-tools)
			linst.doinst("poppler-tools",obverb,oblog,"pdfinfo");
			systemrueck("pdfinfo \""+ziel+"\"|grep -a Pages|sed 's/[^ ]*[ ]*\\(.*\\)/\\1/'",obverb,oblog,&rueck);
			if (rueck.size()) {
				Log("PDF: "+blaus+ziel+": "+gruen+rueck[0]+schwarz+Tx[T_Seiten]);
				*pseitenp=atol(rueck[0].c_str());
			} // 			if (rueck.size())
		} // 		if (pseitenp)
		if (loeschen && exten=="tif") {
			ulong seiten=0;
			holtif(*quellp, &seiten,0,0,0,0,0,0);
			Log("TIF: "+blaus+*quellp+": "+gruen+ltoan(seiten)+schwarz+Tx[T_Seiten]);
			if (rueck.size()) {
				if (pseitenp) {
					if (*pseitenp==seiten && seiten>0) {
						tuloeschen(*quellp,cuser,obverb,oblog);
					} else if (*pseitenp<seiten || !*pseitenp) {
						tuloeschen(ziel,cuser,obverb,oblog);
					} // 		 if (*pseitenp==seiten && seiten>0) else
				} // 		 if (pseitenp)
			} // if (rueck.size())
			// pdfinfo /DATA/shome/gerald/t.pdf |grep Pages|sed 's/[^ ]*[ ]*\(.*\)/\1/'
		} // 		if (loeschen && exten=="tif")
	} // 	if (!erg)
	return erg; 
} // int paramcl::zupdf(string von, string zielvz, int obocr)

// zufaxenvz = zufaxen-Verzeichnis
// 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
// 1b. die Nicht-PDF-Dateien in dem Verzeichnis zum PDF-Druck ermitteln, in Warteverzeichnis verschieben und in die PDF-Liste spdf eintragen ...
// 2a. ... und in im Warteverzeichnis in PDF umwandeln, falls erfolgreich und gleichziel => auch in ziel kopieren
// 2b. Die originalen PDF-Dateien ins Warteverzeichnis verschieben, falls erfolgreich, nicht schon registriert und gleichziel => auch in ziel kopieren
// wird aufgerufen in: main
void paramcl::DateienHerricht() 
{
	Log(violetts+Tx[T_DateienHerricht]);
	struct stat entrynpdf={0};
	//vector<string> npdf, spdf, *npdfp=&npdf, *spdfp=&spdf;  vector<uchar> prios;
	vector<fxfcl> fxv; // Faxvektor
	vector<string> anfxstrvec; // Trennstrings fuer Faxnummer
	anfxstrvec.push_back(anfaxstr);
	if (!ancfaxstr.empty()) anfxstrvec.push_back(ancfaxstr);
	if (!anhfaxstr.empty()) anfxstrvec.push_back(anhfaxstr);
	vector <urfxcl> urfx; // urspruenglicher Dateiname
	svec iprid;
	systemrueck("sudo find \""+zufaxenvz+"\" -maxdepth 1 -type f",obverb,oblog,&iprid);
	zielmustercl mu[anfxstrvec.size()];
	for(uchar iprio=0;iprio<anfxstrvec.size();iprio++) {
		const string mstr=anfxstrvec.at(iprio)+" [ -,/;:\\\\\\.\\+]*[0123456789]"; // z.B. "an Fax +49"
		mu[iprio].setzemuster(mstr);

		// der Reihe nach nach Dateien suchen, die das jeweilige Trennzeichen enthalten
		for(size_t i=0;i<iprid.size();i++) {
			// 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
			if (!regexec(&mu[iprio].regex,iprid[i].c_str(),0,NULL,0)) {

				// for(uchar iprio=0;iprio<anfxstrvec.size();iprio++)
				//    // 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
				//    cmd=string("sudo find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*"+anfxstrvec.at(iprio)+" [ -,/;:\\\\\\.\\+]*[0123456789]+.*\"";
				//    vector<string> iprid;
				//    systemrueck(cmd,obverb,oblog, &iprid);
				//    for(size_t i=0;i<iprid.size();i++) KLA
				string stamm,exten,urname=iprid.at(i);
				getstammext(&(iprid.at(i)),&stamm,&exten);
				::Log(string(Tx[T_Endung])+tuerkis+exten+schwarz,obverb>1,oblog);
				::Log(string(Tx[T_Stamm])+tuerkis+stamm+schwarz,obverb>1,oblog);
				vector<string> tok, toknr, toktxt, tokname;
				::Log(string(Tx[T_trennenach])+blau+anfxstrvec.at(iprio)+schwarz+"'",obverb>1,oblog);
				aufiSplit(&tok,&stamm,anfxstrvec.at(iprio).c_str());
				if (tok.size()>1) { // sollte immer sein
					for(unsigned k=0;k<tok.size();k++) {
						::Log(blaus+tok[k]+schwarz,obverb>1,oblog);
					}
					// die Faxnummern auseinanderfieseln
					aufiSplit(&toknr,&tok[1],undstr.c_str());
					for(unsigned k=0;k<toknr.size();k++) {
						::Log(tuerkiss+"toknr["+ltoan(k)+"]: "+toknr[k]+schwarz,obverb>1,oblog);
					}
					// ggf. die Adressatennamen suchen ...
					aufiSplit(&toktxt,&tok[0],anstr.c_str());
					for(unsigned k=0;k<toktxt.size();k++) {
						::Log(blaus+"toktxt["+ltoan(k)+"]: "+toktxt[k]+schwarz,obverb>1,oblog);
					}
					// und ggf. aufffieseln
					if (toktxt.size()>1) {
						aufiSplit(&tokname,&toktxt[1],undstr.c_str());
						for(unsigned i=0;i<tokname.size();i++) {
							::Log(tuerkiss+"tokname["+ltoan(i)+"]: "+tokname[i]+schwarz,obverb>1,oblog);
						}
					} //         if (toktxt.size()>1)
					for(unsigned j=0;j<toknr.size();j++) { // alle bis auf die letzte Adresse
						string tmp;
						gtrim(&toknr[j]);
						gtrim(&toktxt[0]);
						if (toktxt.size()==1) {                          // keine Arztliste
							tmp= string(toktxt[0]+" "+anfxstrvec.at(iprio)+" "+toknr[j]+'.'+exten);
						} else if (tokname.size()!=toknr.size()) {         // Arztliste nicht gleich lang wie Faxnummernliste
							gtrim(&(toktxt[1]));
							tmp= string(toktxt[0]+anstr+toktxt[1]+" "+anfxstrvec.at(iprio)+" "+toknr[j]+'.'+exten);
						} else {                                       // alles optimal
							gtrim(&(tokname[j]));
							tmp= string(toktxt[0]+anstr+tokname[j]+" "+anfxstrvec.at(iprio)+" "+toknr[j]+'.'+exten);
						}
						::Log(tuerkiss+toknr[j]+schwarz,obverb>1,oblog);
						uint kfehler=0;
						if (j<toknr.size()-1) {
							const string kopiert=kopiere(iprid.at(i),tmp,&kfehler,1);
							if (kfehler) continue;
							urfx.push_back(urfxcl(kopiert,urname,iprio));
							::Log(string(Tx[T_ErstelledurchKopieren])+rot+tmp+schwarz,1,oblog);
						} else {
							if (iprid.at(i)!=tmp) {
								uint vfehler=0;
								dorename((iprid.at(i)),tmp,cuser,&vfehler,obverb,oblog);
								if (vfehler)
									::Log(rots+Tx[T_FehlerbeimUmbenennen]+": "+ltoan(vfehler)+schwarz,1,1);
								else {
									::Log(string(Tx[T_ErstelledurchBenennen])+rot+tmp+schwarz,1,oblog);
								}
							} // if (iprid.at(i)!=tmp) 
							urfx.push_back(urfxcl(tmp,urname,iprio));
						} // if (j<toknr.size()-1) 
					} // for(unsigned j=0;j<toknr.size();j++) 
				} // if (tok.size()>1) 
				iprid[i].clear(); // Datei nach Gebrauch loeschen, um dann die restlichen zu sehen
			} // 		if (!regexec(&mu[0].regex,iprid[i].c_str(),0,NULL,0))
			//		  else KLA
			//		   <<gruen<<"keine Uebereinstimmung: "<<mu[iprio].holmuster()<<" mit "<<iprid[i]<<schwarz<<endl;
			//		KLZ
		} // for(size_t i=0;i<iprid.size();i++)
	} // 	for(uchar iprio=0;iprio<anfxstrvec.size();iprio++)

	// nicht faxbare
	for(size_t i=0;i<iprid.size();i++) {
		if (!iprid[i].empty()) {
			touch(zmvp[0].ziel+vtz+Tx[T_nichtfaxbar]+" `"+base_name(iprid[i])+"`.nix",obverb,oblog);
		}
	} // 	for(size_t i=0;i<iprid.size();i++) 


	// 1b. die Nicht-PDF-Dateien in dem Verzeichnis zum PDF-Druck ermitteln, 
	//    in Warteverzeichnis verschieben und in die PDF-Liste spdfp eintragen ...
	/*
		 cmd=string("find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*\\("+
		 anfaxstr+
		 (ancfaxstr.empty()?"":string("\\|")+ancfaxstr))+
		 (anhfaxstr.empty()?"":string("\\|")+anhfaxstr+
		 "\\) [ -,/;:\\\\\\.\\+]*[0123456789]+.*\" -not -iname \"*.pdf\"";
	 */
	//    for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) KLA
	//      if (!anfxstrvec.at(iprio).empty()) KLA
	//        cmd= string("sudo find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*"+anfxstrvec.at(iprio)+" [ -,/;:\\\\\\.\\+]*[0123456789]+.*\""
	//          " -not -iname \"*.pdf\"";
	//        vector<string> npdfd;
	//        systemrueck(cmd, obverb,oblog, &npdfd);
	//        for(size_t i=0;i<npdfd.size();i++) KLA
	for(size_t i=0;i<urfx.size();i++) {
		uint vfehler=0;
		// wenn die Datei im zufaxenvz in einen Namenskonflikt geriete ...
		const string ndname=zufaxenvz+vtz+neuerdateiname(urfx.at(i).teil);
		if (ndname!=urfx.at(i).teil) {
			dorename(urfx.at(i).teil,ndname,cuser,&vfehler,obverb,oblog);
			if (vfehler) {
				cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
					blau<<urfx.at(i).teil<<schwarz<<" ->\n"<<
					blau<<ndname<<schwarz<<endl;
				continue;
			} // if (vfehler) 
			urfx.at(i).teil=ndname;
		} // if (ndname!=urfx.at(i).teil) 
		string wartedatei=verschiebe(urfx.at(i).teil,wvz,cuser,&vfehler,1,obverb,oblog);
		if (vfehler) {
			cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
				blau<<urfx.at(i).teil<<schwarz<<" ->\n"<<
				blau<<wvz<<schwarz<<endl;
			continue;
		} //     if (vfehler)
		// hier gaebe es also weder beim Kopieren ins zufaxenverzeichnis noch beim Verschieben ins Warteververzeichnis ein Problem
		string stamm,exten;
		//          npdfp->push_back(wartedatei);
		getstammext(&wartedatei,&stamm,&exten);
		string wartepdf=stamm+".pdf";
		if (!strcasecmp(exten.c_str(),"pdf")) wartedatei.clear();
		fxv.push_back(fxfcl(wartedatei,wartepdf,urfx.at(i).ur,urfx.at(i).prio));
	} //   for(size_t i=0;i<urfx.size();i++)
	//        KLZ // for(size_t i=0;i<npdfd.size();i++) 
	//      KLZ // if (!anfxstrvec.at(iprio).empty()) 
	//    KLZ // for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) 

	Log(blaus+Tx[T_Gesammelt_wurden]+schwarz);
	for(unsigned i=0;i<fxv.size();i++) {
		Log(string("npdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].npdf+schwarz);
		Log(string("spdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].spdf+schwarz);
		Log(string("prio[")+rot+ltoan(i)+schwarz+"]: "+rot+ltoan(fxv[i].prio)+schwarz);
	} // for(unsigned i=0;i<fxv.size();i++)
	// zufaxenvz = zufaxen-Verzeichnis
	::Log(string(Tx[T_aus])+drot+zufaxenvz+schwarz+vtz+Tx[T_verarbeitete_Nicht_PDF_Dateien]+drot+ltoan(fxv.size())+schwarz,1,oblog);
	//  geszahl+=npdfp->size(); // 1b

	// 2a. ... und im Warteverzeichnis in PDF umwandeln, falls erfolgreich und gleichziel => auch in ziel kopieren
	for (int nachrnr=fxv.size()-1; nachrnr>=0; --nachrnr) {
	  unsigned nfehlt=1;
	  if (!fxv[nachrnr].npdf.empty()) {
			if ((nfehlt=lstat((fxv[nachrnr].npdf.c_str()), &entrynpdf))) {
				::Log(string(Tx[T_lstatfehlgeschlagen])+rot+strerror(errno)+schwarz+Tx[T_beiDatei]+ fxv[nachrnr].npdf,1,1,1);
				continue;
      } else {
				/*erg=*/zupdf(&fxv[nachrnr].npdf, fxv[nachrnr].spdf, &fxv[nachrnr].pseiten, obocra, 0); // 0=erfolg
			}
		} // 	  if (!fxv[nachrnr].npdf.empty())
	  if (lstat((fxv[nachrnr].npdf.c_str()), &entrynpdf)) {
			// Misserfolg, zurueckverschieben und aus der Datenbank loeschen
			uint wfehler=0;
			// <<violett<<"fxv["<<(int)nachrnr<<"].npdf: "<<fxv[nachrnr].npdf<<schwarz<<endl;
			// <<violett<<"fxv["<<(int)nachrnr<<"].spdf: "<<fxv[nachrnr].spdf<<schwarz<<endl;
			struct stat npdfstat={0};
			if (!lstat(fxv[nachrnr].npdf.c_str(), &npdfstat))
				verschiebe(fxv[nachrnr].npdf,zufaxenvz,cuser,&wfehler,1,obverb,oblog);
			struct stat spdfstat={0};
			if (!lstat(fxv[nachrnr].spdf.c_str(), &spdfstat))
				verschiebe(fxv[nachrnr].spdf,zufaxenvz,cuser,&wfehler,1,obverb,oblog);
			fxv.erase(fxv.begin()+nachrnr);
		} else {
		  // Erfolg
			if (gleichziel) {
				uint kfehler=0;
				if (!nfehlt) kopiere(fxv[nachrnr].npdf, zmp, &kfehler, 1, obverb, oblog);
				/*string zield=*/kopiere(fxv[nachrnr].spdf, zmp, &kfehler, 1, obverb, oblog);
			} // if (gleichziel)
		} // 	  if (lstat((fxv[nachrnr].npdf.c_str()), &entrynpdf)) else
	} // for (int nachrnr=npdfp->size()-1; nachrnr>=0; --nachrnr)  // 2.

	// 2b. Die originalen PDF-Dateien ins Warteverzeichnis verschieben, falls erfolgreich, nicht schon registriert und gleichziel 
	//      => auch in ziel kopieren
	for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) {
		if (!anfxstrvec.at(iprio).empty()) {
			cmd=string("sudo find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*"+anfxstrvec.at(iprio)+" [ -,/;:\\\\\\.\\+]*[0123456789]+.*\""
				" -iname \"*.pdf\"";
			vector<string> spdfd;
			systemrueck(cmd,obverb, oblog, &spdfd);
			for(size_t i=0;i<spdfd.size();i++) {
				if (obocra) {
					struct stat spdfstat={0};
					if (!lstat(spdfd.at(i).c_str(),&spdfstat)) {
						struct utimbuf ubuf={0};
						ubuf.actime=ubuf.modtime=spdfstat.st_mtime;
						if (!pruefocr()) {
							string cmd=string(ocrmp+" -rcsl ")+(langu=="d"?"deu":"eng")+" \""+spdfd.at(i)+"\" \""+spdfd.at(i)+"\""
																" && chmod +r \""+spdfd.at(i)+"\"";
							int zerg=systemrueck(cmd,obverb,oblog);
							if (zerg==5) zerg=systemrueck("sudo "+cmd,obverb,oblog); // kein Schreibrecht im Verzeichnis
						}
						utime(spdfd.at(i).c_str(),&ubuf);
					} // if (!lstat(spdfd.at(i).c_str(),&spdfstat)) 
				} // if (obocra) 
				const string ndname=zufaxenvz+vtz+neuerdateiname(spdfd.at(i));
				uint vfehler=0;
				if (ndname!=spdfd.at(i)) {
					dorename(spdfd.at(i),ndname,cuser,&vfehler,obverb,oblog);
					if (vfehler) {
						cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
							blau<<spdfd.at(i)<<schwarz<<" ->\n"<<
							blau<<ndname<<schwarz<<endl;
						continue;
					} // if (vfehler) 
					//            spdfd.at(i)=ndname;
				} // if (ndname!=spdfd.at(i))
				string wartedatei=verschiebe(ndname,wvz,cuser,&vfehler,1,obverb,oblog);
				if (vfehler) {
					cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
						blau<<spdfd.at(i)<<schwarz<<" ->\n"<<
						blau<<wvz<<schwarz<<endl;
					continue; 
				}
				uchar vorhanden=0; // 1= Datei schon zuvor als nicht-PDF-Datei eingetragen
				for(size_t ii=0;ii<fxv.size()&&ii<spdfd.size();ii++) {
					if (fxv[ii].spdf==ndname) {vorhanden=1;break;} 
				}
				if (!vorhanden) {
					fxv.push_back(fxfcl(wartedatei,spdfd.at(i),iprio));
					if (gleichziel) {
						uint kfehler=0;
						/*string zield=*/kopiere(wartedatei, zmp, &kfehler, 1, obverb, oblog);
					} //  if (gleichziel)
				} //if (!vorhanden)
			} // for(size_t i=0
		} // if (!anfxstrvec.at(iprio).empty()) 
	} // for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) 
	for(unsigned i=0;i<fxv.size();i++) {
		Log(string("npdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].npdf+schwarz);
		Log(string("spdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].spdf+schwarz);
		Log(string("prio:       ")+rot+ltoan(fxv[i].prio)+schwarz);
		Log(string("pseiten:    ")+rot+ltoan(fxv[i].pseiten)+schwarz);
	} //   for(unsigned i=0;i<fxv.size();i++)

	::Log(string(Tx[T_aus])+drot+zufaxenvz+schwarz+vtz+Tx[T_verarbeitete_PDF_Dateien]+drot+ltoan(fxv.size())+schwarz,1,oblog);
	geszahl=fxv.size();
	// 3) in spooltab eintragen
	WVZinDatenbank(&fxv);
} // void DateienHerricht()

// wird aufgerufen in: main
void paramcl::faxealle()
{
	Log(violetts+Tx[T_faxealle]+schwarz+", "+blau+Tx[T_obcapimitDoppelpunkt]+schwarz+(obcapi?Tx[T_ja]:Tx[T_nein])+", "
			+blau+Tx[T_obhylamitDoppelpunkt]+schwarz+(obhyla?Tx[T_ja]:Tx[T_nein]));
	vector<fsfcl> fsfv;
	char ***cerg;
	unsigned long dbszahl=0; // Zahl der Datenbanksaetze
	//  string hzstr=ltoan(hylazuerst);
	if (!isnumeric(maxhylav)) maxhylav="3";
	if (!isnumeric(maxcapiv)) maxcapiv="3";
	/*
	RS r0(My,string("SELECT id p0, origvu p1, original p2, telnr p3, prio p4, "
				"IF(ISNULL(capispooldatei),'',capispooldatei) p5, IF(ISNULL(capidials),'',capidials) p6, "
				"IF(ISNULL(hylanr),'',hylanr) p7, IF(ISNULL(hyladials),'',hyladials) p8, "
				"((ISNULL(capispooldatei)OR capispooldatei='') AND (ISNULL(hyladials) OR hyladials>=")+maxhylav+" OR hylastate=8 OR " // hyladials=-1
			//      "    (ISNULL(prio) OR prio=1 OR (prio=0 AND NOT "+hzstr+")))) p9, "
			"    (ISNULL(prio) OR prio=2 OR prio=0))) p9, "
			"((ISNULL(hylanr) OR hylanr='') AND (ISNULL(capidials) OR capidials>=" +maxcapiv+" OR capidials=-1 OR "
			//      "      (ISNULL(prio) OR prio=2 OR (prio=0 AND "+hzstr+")))) p10, "
			"      (ISNULL(prio) OR prio=3 OR prio=1))) p10, "
			"adressat p11, pages p12 "
			"FROM `"+spooltab+"` "
			"WHERE original>''",ZDB);
	*/
	RS r0(My,"SELECT s.id p0, s.origvu p1, s.original p2, s.telnr p3, s.prio p4, s.capispooldatei p5, s.capidials p6, "
				"s.hylanr p7, s.hyladials p8, "
				"((s.capispooldatei='') AND (s.hyladials>="+maxhylav+" OR s.hylastate=8 OR " // hyladials=-1
			//      "    (prio=1 OR (prio=0 AND NOT "+hzstr+")))) p9, "
			"    (s.prio=2 OR s.prio=0))) p9, "
			"((s.hylanr='' OR s.hylanr=0) AND (s.capidials>=" +maxcapiv+" OR s.capidials=-1 OR "
			//      "      (prio=2 OR (prio=0 AND "+hzstr+")))) p10, "
			"      (s.prio=3 OR s.prio=1))) p10, "
			"s.adressat p11, s.pages p12 "
			",alts.id p13 "
			"FROM `"+spooltab+"` s "
			"LEFT JOIN `"+altspool+"` alts ON s.idudoc=alts.idudoc "
			"WHERE s.original>''",ZDB);
	if (r0.obfehl) {
		cerr<<rots<<Tx[T_Fehler_af]<<schwarz<<r0.obfehl<<rot<<Tx[T_beiSQLAbfrage]<<schwarz<<r0.sql<<endl;
	} else {
		while (cerg=r0.HolZeile(),cerg?*cerg:0) {
			(dbszahl)++;
			if (!*(*cerg+9)) *(*cerg+9)=(char*)"";
			if (!*(*cerg+10)) *(*cerg+10)=(char*)"";
			if (!*(*cerg+11)) *(*cerg+11)=(char*)"";
			if (!*(*cerg+12)) *(*cerg+12)=(char*)"";
			if (!*(*cerg+13)) *(*cerg+13)=(char*)"";
			if (*(*cerg+0) && *(*cerg+1) && *(*cerg+2) && *(*cerg+3) && *(*cerg+4) && *(*cerg+5) && 
					*(*cerg+6) && *(*cerg+7) && *(*cerg+8)) {
				// obcapi = *(*cerg+9), obhyla=*(*cerg+10)
				fsfv.push_back(/*1*/fsfcl(*(*cerg+0)/*id*/, *(*cerg+1)/*npdf*/, *(*cerg+2)/*spdf*/, *(*cerg+3)/*telnr*/, 
							atoi(*(*cerg+4))/*prio*/, *(*cerg+5)/*capisd*/, atoi(*(*cerg+6))/*capids*/, *(*cerg+7)/*hylanr*/, 
							atoi(*(*cerg+8))/*hdialsn*/, (binaer)atoi(*(*cerg+9))/*obcapi*/, (binaer)atoi(*(*cerg+10))/*obhyla*/, *(*cerg+11)/*adressat*/,
							atoi(*(*cerg+12)/*pages*/), *(*cerg+13)/*alts.id*/));
			}
		} // while (cerg=r0.HolZeile(),cerg?*cerg:0) 
		Log(string(Tx[T_ZahldDSmwegzuschickendenFaxenin])+spooltab+"`: "+blau+ltoan(fsfv.size())+schwarz,obverb,oblog);
		for(unsigned i=0;i<fsfv.size();i++) {
			Log(string(" i: ")+blau+ltoan(i)+schwarz+Tx[T_PDFDatei]+blau+fsfv[i].spdf+schwarz+
					" ."+Tx[T_obcapimitDoppelpunkt]+blau+(fsfv[i].fobcapi?Tx[T_ja]:Tx[T_nein])+schwarz+
					" ."+Tx[T_obhylamitDoppelpunkt]+blau+(fsfv[i].fobhyla?Tx[T_ja]:Tx[T_nein])+schwarz,obverb,oblog);
			if (fsfv[i].fobcapi) if (obcapi) faxemitC(My, spooltab, altspool, &fsfv[i],this,obverb,oblog);  
			if (fsfv[i].fobhyla) if (obhyla) faxemitH(My, spooltab, altspool, &fsfv[i],this,obverb,oblog);  
			//      _out<<fsfv[i].id<<" "<<rot<<fsfv[i].npdf<<" "<<schwarz<<(int)fsfv[i].obcapi<<" "<<(int)fsfv[i].obhyla<<endl;
		} // for(unsigned i=0;i<fsfv.size();i++) 
	} // if (r0.obfehl) else  
} // faxealle

// wird aufgerufen in: untersuchespool, loeschefax
void fsfcl::setzcapistat(paramcl *pmp, struct stat *entrysendp)
{
  int dateifehlt=0;
	int protpos=0;
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
					sendqgespfad=(capistat==gescheitert?pmp->cfailedvz:pmp->cdonevz)+vtz+aktuser+"-"+capisd; 
					Log(string("capistat: ")+ltoan((int)capistat)+" "+blau+sendqgespfad+schwarz,pmp->obverb,pmp->oblog);
					if (!(dateifehlt=lstat((sendqgespfad.c_str()), entrysendp))) break; 
				}  //         for(capistat=gesandt;capistat<=gescheitert;capistat=static_cast<FxStat>(capistat+1))
				// hier koennte capistat auch fehlend sein
			}
		  if (!dateifehlt) {	
				if ((protpos=holcapiprot(pmp->obverb)<0)) {
					capistat=fehlend;
				} else if (capistat!=gesandt && capistat!=gescheitert) {
					struct stat statlock={0};
					if (lstat((sendqgespfad.substr(0,protpos)+".lock").c_str(),&statlock))
						capistat=wartend;
					else
						capistat=verarb;
				} // 				if ((p3=holcapiprot(obverb))<0)
			}  //       if (!lstat(sendqgespfad.c_str(),entrysendp)) else
		} // if ((p1=cspf.rfind(vtz))) if ((p2=cspf.rfind(vtz,p1-1))) 
	} //   if (capisd.empty()) else
} // fsfcl::setzcapistat

// hylafax: bei zu faxenden Dateien stehen die Steuerdateien in /var/spool/fax/sendq/q105, benannt nach /var/spool/fax/etc/xferfaxlog, dort steht in der 6. Spalte die hyla-Index-Nummer z.B. 105, die als Rueckmeldung von sendfax erscheint ("request id is 105 (group id 105) for host localhost (1 file)")
// in der 4. Spalte steht dazu die Dokumentnummer 00000133, mit der das Dokument im Spool in /var/spool/fax/docq/doc133.pdf wartet
// hylafax-Befehl: sendfax -n -A -d  0814198765432 "/DATA/Patientendokumente/warteauffax/... .pdf"
// sendfax -n -A -d   98765432 "/DATA/Patientendokumente/warteauffax/... .pdf""  ( (mit utf8)

// Dateien in Spool-Tabelle nach inzwischen verarbeiteten durchsuchen, Datenbank- und Dateieintraege korrigieren 
// wird aufgerufen in: main (2x)
void paramcl::untersuchespool(uchar mitupd/*=1*/) // faxart 0=capi, 1=hyla 
{
	// Schaue nach, welche der gespoolten schon weggeschickt sind, Anpassung der Primaerdateien und des Datenbankeintrags
	Log(violetts+Tx[T_untersuchespool]+schwarz);
	char ***cerg;
	RS rs(My,"SELECT s.id p0,s.capispooldatei p1,s.capispoolpfad p2,s.original p3,s.cdateidatum p4,"
				" s.telnr p5,s.origvu p6,s.hylanr p7,s.capidials p8,s.hyladials p9,s.hdateidatum p10,s.adressat p11,s.idudoc p12,s.prio p13,s.pages p14 "
				",alts.id p15 "
				"FROM `"+spooltab+"` s "
				"LEFT JOIN `"+altspool+"` alts ON s.idudoc=alts.idudoc "
				"WHERE (s.hylanr RLIKE '^[0-9]+$' AND s.hylanr<>0) OR s.capispooldatei RLIKE '^fax-[0-9]+\\.sff$'",ZDB);
	if (!rs.obfehl) {
		faxord=0;
		while (cerg=rs.HolZeile(),cerg?*cerg:0) {
			faxord++;
			if (*(*cerg+0)) if (*(*cerg+3)) {
				(dbzahl)++;
				stringstream ausg; //      ausg.str(std::string()); ausg.clear();
				/*2*/fsfcl fsf(*(*cerg+0),*(*cerg+3)); // id, original
				if (*(*cerg+1)) fsf.capisd =*(*cerg+1); // capispooldatei
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
				if (*(*cerg+13)) fsf.prio = atol(*(*cerg+13));  // Prioritaet wie in Datenbank
				if (*(*cerg+14)) fsf.pseiten = atol(*(*cerg+14));  // pages wie in Datenbank
				if (*(*cerg+15)) fsf.idalt = *(*cerg+15);  // id hyla
				// <<"fsf.id: "<<violett<<fsf.id<<schwarz<<endl;
				// <<"fsf.idalt: "<<violett<<fsf.idalt<<schwarz<<endl;
				::Log(string("id: ")+fsf.id+": ",obverb?-2:0,oblog); // -2: schreibt ohne Zeilenwechsel
				ausg<<blau<<faxord<<") "<<rot<<wvz<<vtz<<fsf.original<<schwarz<<": "; // ab hier Neue-Zeile-Zeichen immer am Anfang der naechsten Zeile
				// a) ueber capisuite
				// den Status in Capi der aus spool geholten Zeile untersuchen, dort aktualisieren
				//   und ggf. in hylafax stoppen
				struct stat entrysend={0};
				if (obcapi) {
					if (faxord==1) this->pruefcapi(); // in der ersten Runde, in der Capi verwendet werden soll, Capi pruefen
					fsf.setzcapistat(this, &entrysend);
					fsf.tts=0; // fuer archiviere
					fsf.capiausgeb(&ausg,maxcdials, 0, obverb, oblog);
					if (mitupd) {
						RS rupd(My); 
						vector<instyp> einf; // fuer alle Datenbankeinfuegungen
						const string bedingung="id="+fsf.id;
						const string bedc="id="+fsf.idalt;
						if (fsf.capistat==wartend || fsf.capistat==gescheitert) {
							einf.push_back(/*2*/instyp(My->DBS,"capidials",&fsf.ctries));
							einf.push_back(/*2*/instyp(My->DBS,"capistat",fsf.capistat));
							if (!fsf.idalt.empty()) 
								rupd.update(altspool,einf,ZDB,bedc,0);
							rupd.update(spooltab,einf,ZDB,bedingung,0);
						} else if (fsf.capistat==gesandt) {
							// ... und ggf. in hylafax loeschen
							fsf.loeschehyla(this,obverb, oblog);
						} else if (fsf.capistat==fehlend) {
						} //             if (fsf.capistat==wartend)  else else else 
					} // if (mitupd) 
				} // if (obcapi) 

				// b) ueber hylafax
				if (obhyla) {
					string protdakt;
					uchar hyla_uverz_nr=0; // suche ueberall, liefere 1 zuruck, wenn weder in /doneq noch in /archive gefunden
					string number;
					int obsfehlt=-1;
					/*fsf.*/
					setzhylastat(&fsf, &protdakt, &hyla_uverz_nr, 0, &obsfehlt, &entrysend);
					// <<gruen<<"fsf.hylastat: "<<schwarz<<(int)fsf.hylastat<<endl;
					fsf.hylaausgeb(&ausg, this, obsfehlt, 0, obverb, 0, oblog);
					//          if (!obsfehlt) KLA // Protokolldatei vorhanden 12.10.16 sollte jetzt auch mit xferfax gehen
					if (mitupd) {
						RS rupd(My); 
						vector<instyp> einf; // fuer alle Datenbankeinfuegungen
						einf.push_back(/*2*/instyp(My->DBS,"hylastate",&fsf.hstate));
						if (!fsf.hstatus.empty()) einf.push_back(/*2*/instyp(My->DBS,"hylastatus",&fsf.hstatus));
						if (!fsf.hstatuscode.empty()) einf.push_back(/*2*/instyp(My->DBS,"hylastatuscode",&fsf.hstatuscode));
//						if (!hyla_uverz_nr) KLA // wenn fertig
//							if (fsf.hylastat==gescheitert) KLA // (hylastate=="8") // 8, status gescheitert, evtl. unzureichend dokumentiert, aber wahr
								//                  einf.push_back(/*6*/instyp(My->DBS,"hylanr","0",(uchar)1));
								//                  einf.push_back(instyp(My->DBS,"hyladials","-1",(uchar)1));
								//                  fsf.hdials="-1";
//							KLZ else 
							if (fsf.hylastat==gesandt) { // (hylastate=="7") // 7, status erfolgreich
								// ... und ggf. in capisuite loeschen
								fsf.loeschecapi(obverb,oblog);
							} // if (fsf.hylastat==gescheitert) else
//						KLZ // if (!hyla_uverz_nr) 
						einf.push_back(/*2*/instyp(My->DBS,"hyladials",&fsf.hdials));
						const string bedingung=string("id=")+fsf.id;
						const string bedh=string("id=")+fsf.idalt;
						if (!fsf.idalt.empty()) 
						   rupd.update(altspool,einf,ZDB,bedh,0);
						rupd.update(spooltab,einf,ZDB,bedingung,0);
					} // if (mitupd) 
					if (!protdakt.empty()) ausg<<Tx[T_bzw]<<blau<<protdakt<<schwarz;
				} // if (obhyla)
				//        KLZ // if (!obsfehlt) ... else

				if (mitupd && (obcapi || obhyla)) {
					// im Erfolgsfall zugrundeliegende Dateien verschieben
					if (fsf.capistat==gesandt || fsf.hylastat==gesandt) {
						(ezahl)++;

						// Fax gelungen, Dateien in warteauffax nach zielmuster verschieben bzw. loeschen ...
						for(unsigned iru=0;iru<2;iru++) {
							const string *datei=iru?&fsf.origvu:&fsf.original;
							if (!datei->empty()) {
								const string zuloe =wvz+vtz+*datei;
								if (gleichziel) { 
									tuloeschen(zuloe,cuser,obverb,oblog);
								} else {
									uint vfehler=0;
									verschiebe(zuloe, zmp, cuser,&vfehler, 1, obverb, oblog);
								} // if (gleichziel) else 
							} // if (!datei->empty()) 
						} // for(unsigned iru=0;iru<2;iru++) 
					} else if ((!obhyla && fsf.capistat==gescheitert) || (!obcapi && fsf.hylastat==gescheitert) || 
							(fsf.capistat==gescheitert && fsf.hylastat==gescheitert)) {
						(gzahl)++; 
					} else if ((!obhyla && fsf.capistat==fehlend) || (!obcapi && fsf.hylastat==fehlend) || 
							(fsf.capistat==fehlend && fsf.hylastat==fehlend)) {
						(fzahl)++;
					} else if (fsf.capistat==wartend || (fsf.hylastat>static_cast<FxStat>(gestrichen)&&fsf.hylastat<=static_cast<FxStat>(verarb))) {
						(wzahl)++;
					} //           if (fsf.capistat==gesandt || fsf.hylastat==gesandt) else if ...
					// Aktionen, wenn in beiden gescheitert oder fehlend
					if (obverb>0) {
						Log(violetts+"Capistat: "+schwarz+FxStatS(&fsf.capistat)+violett+", Hylastat: "+schwarz+FxStatS(&fsf.hylastat));
					} //           if (obverb>0)
					// die Flags aller aktivierten Faxwege stehen auf gescheitert
					uchar allegesch = (obcapi||obhyla) && ((!obcapi || fsf.capistat==gescheitert) && (!obhyla || fsf.hylastat==gescheitert));
					//          if (obcapi && obhyla && fsf.capistat==gescheitert && maxcapiv>=maxcdials) allegesch=1;
					//          else if (obcapi && obhyla && fsf.hylastat==gescheitert && maxhylav>=maxhdials) allegesch=1;
					// die Flags aller aktivierten Faxwege stehen auf gescheitert oder fehlend
					uchar nimmer = ((!obcapi || fsf.capistat==fehlend || fsf.capistat==gescheitert) && 
							(!obhyla || fsf.hylastat==fehlend || fsf.hylastat==gescheitert));
					// <<rot<<"\nfsf.capistat: "<<violett<<fsf.capistat<<rot<<" fsf.hylastat: "<<violett<<fsf.hylastat<<rot<<" allegesch: "<<violett<<(int)allegesch<<rot<<" nimmer: "<<violett<<(int)nimmer<<schwarz<<endl;
					uchar ogibts[2]={0};
					string odatei[2];
					if (nimmer) {
						for(unsigned iru=0;iru<2;iru++) {
							const string *datei=iru?&fsf.origvu:&fsf.original;
							if (!datei->empty()) {
								odatei[iru] = wvz+ vtz + *datei;
								struct stat ostat={0};
								ogibts[iru]=!lstat(odatei[iru].c_str(),&ostat);
								Log(blaus+"odatei["+(iru?"1":"0")+"]: "+odatei[iru]);
								Log(blaus+"ogibts["+(iru?"1":"0")+"]: "+(ogibts[iru]?"1":"0"));
							} // if (!datei->empty()
						} // for(unsigned iru=0
					} // if (nimmer)
					if (fsf.capistat==gesandt || fsf.hylastat==gesandt || allegesch || (nimmer /* && !ogibts[0] */) ) {
						uchar geloescht=0;
						// <<"\n"<<gruen<<"gesandt: "<<schwarz<<(int)gesandt<<endl;
						// <<gruen<<"gescheitert: "<<schwarz<<(int)gescheitert<<endl;
						// <<gruen<<"fehlend: "<<schwarz<<(int)fehlend<<endl;
						// <<gruen<<"allegesch: "<<schwarz<<(int)allegesch<<endl;
						// <<gruen<<"nimmer: "<<schwarz<<(int)nimmer<<endl;
						// <<gruen<<"fsf.capistat: "<<schwarz<<(int)fsf.capistat<<endl;
						// <<gruen<<"fsf.hylastat: "<<schwarz<<(int)fsf.hylastat<<endl;
						// <<"obcapi: "<<(int)obcapi<<endl;
						// <<"obhyla: "<<(int)obhyla<<endl;
						// <<"fsf.capisd: '"<<fsf.capisd<<"'"<<endl;
						// <<gruen<<"fsf.capisd.empty(): "<<schwarz<<(int)fsf.capisd.empty()<<endl;
						fsf.archiviere(My,this,&entrysend,allegesch||nimmer,
								fsf.capistat==gesandt?capi:fsf.hylastat==gesandt?hyla:fsf.capisd.empty()?hyla:capi,
								&geloescht, obverb, oblog);
					} //           if (fsf.capistat==gesandt || fsf.hylastat==gesandt || allegesch || (nimmer /* && !ogibts[0] */) )
					// wenn alle aktivierten Faxwege auf gescheitert oder fehlend stehen oder die Quelldatei fehlt ...
					if (allegesch || (nimmer && !ogibts[0])) {
						// Fax gescheitert, Dateien von warteauffax nach nichtgefaxt verschieben
						for(unsigned iru=0;iru<2;iru++) {
							uint vfehler=0;
							if (ogibts[iru]) {
								verschiebe(odatei[iru],nvz,cuser,&vfehler, 1, obverb,oblog);
								// an vorderster Stelle Scheitern erkennen lassen
								touch(zmvp[0].ziel+vtz+Tx[T_nichtgefaxt]+" `"+base_name(odatei[iru])+"`.nix",obverb,oblog);
							} // if (ogibts[iru]) 
						} // for(unsigned iru=0;iru<2;iru++) 
					} // if (allegesch || (nimmer && !ogibts[0]))
				} // if (obcapi || obhyla)
				::Log(ausg.str(),1,oblog);
			} // if (*(*cerg+0)) if (*(*cerg+3))
		} // while (cerg=rs.HolZeile(),cerg?*cerg:0) 
	} // if (!rs.obfehl) 
} // untersuchespool

// Zeige Dateien im Spool an, die nicht in der Spool-Tabelle stehen
// wird aufgerufen in: main
void paramcl::zeigweitere()
{
	Log(violetts+Tx[T_zeigweitere]+schwarz);
	static int obtitel=0;
	stringstream ausg; //      ausg.str(std::string()); ausg.clear();
	unsigned tage=0;
	if (obcapi || obhyla) {
		// bei jedem 3. Aufruf einen Tag, bei jedem 3. Aufruf des Tages 30 Tage und des Monats 200 Jahre
		if (monatsaufr==3) {
			tage=ltage; // 73000
		}	else if (tagesaufr==3) {
			tage=mtage; // 30
		}	else if (!(tagesaufr % 3)) {
			tage=ktage; // 1
		} // 		if (monatsaufr==3) else if else if
	} // 	if (obcapi || obhyla)
	// <<"Korrektur wird durchgefuehrt ueber Tage: "<<tage<<endl;
	if (obcapi) {
	  if (tage) korrigierecapi(tage);
		vector<fsfcl> fsfv;
		sammlecapi(&fsfv);
		for(size_t i=0;i<fsfv.size();i++) {
			if (!obtitel) {
				ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
				obtitel=1;
			} // 			if (!obtitel) 
			fsfv[i].capiausgeb(&ausg, maxcdials, 0, obverb, oblog, ++faxord);
		} //     for(size_t i=0;i<fsfv.size();i++)
	} // if (obcapi)
	if (obhyla) {
		if (tage) korrigierehyla(tage); // braucht bei mir mit 2500 Eintraegen in altspool ca. 30000 clocks
		vector<fsfcl> fsfv;
		sammlehyla(&fsfv);
		for(size_t i=0;i<fsfv.size();i++) {
			if (!obtitel) {
				ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
				obtitel=1;
			} // 		for(size_t i=0;i<fsfv.size();i++)
			fsfv[i].hylaausgeb(&ausg, this, 0, 0, obverb, 1, oblog);
		} //     for(size_t i=0;i<fsfv.size();i++) 
	} // if (obhyla) 
	if (obtitel) ::Log(ausg.str(),1,oblog);
} // void paramcl::zeigweitere()

// aufgerufen in loeschefax, zeigweitere
void paramcl::sammlecapi(vector<fsfcl> *fsfvp)
{
	Log(violetts+Tx[T_sammlecapi]+schwarz);
	struct stat entryvz={0};
	if (!lstat(cfaxusersqvz.c_str(),&entryvz)) {
		bereinigecapi();
		cmd=string("sudo find '")+cfaxuservz+"' -path \"*/sendq/fax*\" -type f -iname 'fax*.sff'"; //  -printf '%f\\n'";
		svec rueck;
		systemrueck(cmd,obverb,oblog,&rueck);
		for(size_t i=0;i<rueck.size();i++) {
			uchar indb=0;
			char ***cerg;
			RS rs(My,"SELECT id FROM `"+spooltab+"` WHERE CONCAT(capispoolpfad,'/',capispooldatei)='"+rueck[i]+"'",ZDB);
			if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
			if (!indb) {
				/*5*/fsfcl fsf(rueck[i],wartend);
				fsf.capisd=base_name(rueck[i]);
				fsf.hylanr="-1";
				fsf.cspf=dir_name(rueck[i]);
				struct stat entrysend={0};
				fsf.setzcapistat(this,&entrysend);
				fsfvp->push_back(fsf);
			} // if (!indb) 
		} // for(size_t i=0
	} // if (!lstat(cfaxusersqvz.c_str(),&entryvz)) 
} // void paramcl::sammlecapi(vector<fsfcl> *fsfvp)

// in sammlecapi
void paramcl::bereinigecapi()
{
	Log(violetts+Tx[T_bereinigecapi]+schwarz);
	svec rueck;
	struct stat entryvz={0};
	// 7.2.16: alte *.lock-Dateien loeschen
	cmd=string("sudo find '")+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.lock'"; //  -printf '%f\\n'";
	systemrueck(cmd,obverb,oblog,&rueck);
	for(size_t i=0;i<rueck.size();i++) {
		string stamm,exten;
		getstammext(&rueck[i],&stamm,&exten);
		const string zugeh=stamm+".sff";
		if (lstat(zugeh.c_str(),&entryvz)) {
			tuloeschen(rueck[i],cuser,obverb,oblog);
		}
	} //       for(size_t i=0;i<rueck.size();i++)
	rueck.clear();
	// 20.1.16: wenn dort eine .txt-steht ohne zugehoerige .sff-Datei, dann haelt sie den ganzen Betrieb auf
	cmd=string("sudo find '")+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.txt'"; //  -printf '%f\\n'";
	systemrueck(cmd,obverb,oblog,&rueck);
	for(size_t i=0;i<rueck.size();i++) {
		string stamm,exten;
		getstammext(&rueck[i],&stamm,&exten);
		const string zugeh=stamm+".sff";
		if (lstat(zugeh.c_str(),&entryvz)) {
			const string base=base_name(zugeh);
			RS inouta(My,"SELECT submid FROM `"+touta+"` WHERE submid = '"+base+"'",ZDB);
			if (inouta.num_rows) {
				::Log(blaus+Tx[T_Verwaiste_Datei]+gruen+rueck[i]+schwarz+Tx[T_geloescht_Fax_schon_in]+gruen+touta+schwarz+
						Tx[T_archiviert_Ausrufezeichen],1,1);
				tuloeschen(rueck[i],cuser,obverb,oblog);
				break;
			} else {
				// 31.1.16: ... und wenn diese sich nicht in outa findet ...
				const string waisen = cfaxusersqvz+"/waisen";
				pruefverz(waisen,obverb,oblog);
				uint vfehler=0;
				verschiebe(rueck[i],waisen,cuser,&vfehler,1,obverb,oblog);
			} // if (inouta.num_rows) else 
		} // if (lstat(zugeh.c_str(),&entryvz)) 
	} // for(size_t i=0;i<rueck.size();i++) 
} // void paramcl::bereinigecapi()


// aufgerufen in: zeigweitere, loeschefax
void paramcl::sammlehyla(vector<fsfcl> *fsfvp)
{
	Log(violetts+Tx[T_sammlehyla]+schwarz);
	struct stat entryvz={0};
	if (!lstat(hsendqvz.c_str(),&entryvz)) {
		cmd="sudo find '"+hsendqvz+"' -maxdepth 1 -type f -iname 'q*' -printf '%f\\n'";
		svec qrueck;
		systemrueck(cmd,obverb,oblog,&qrueck);
		for(size_t i=0;i<qrueck.size();i++) {
			uchar indb=0;
			const string hylanr=qrueck[i].substr(1);
			char ***cerg;
			RS rs(My,"SELECT id FROM `"+spooltab+"` WHERE hylanr="+hylanr,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
			if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
			if (!indb) {
				/*4*/fsfcl fsf(hylanr); // fsf(rueck[i]);
				string protdakt=hsendqvz+vtz+hylanr; // rueck[i];
				uchar hyla_uverz_nr=1;
				/*fsf.*/
				setzhylastat(&fsf, &protdakt, &hyla_uverz_nr, 2, 0, 0);
				fsfvp->push_back(fsf);
			} // if (!indb)
		} // for(size_t i=0;i<rueck.size();i++) 
	} // if (!lstat(hsendqvz.c_str(),&entryvz))
} // void paramcl::sammlehyla(vector<fsfcl> *fsfvp)

// aufgerufen in: zeigweitere
void paramcl::korrigierehyla(unsigned tage/*=90*/)
{
	Log(violetts+Tx[T_sammlefertigehyla]+schwarz);
	if (!xferfaxlog.empty()) {
		struct stat entryvz={0};
		if (!lstat(xferfaxlog.c_str(),&entryvz)) {
			// cmd=string("sudo find '")+varsphylavz+"' -type f -regex '.*/q[0123456789]+'";
			// string hylanr=qrueck[i].substr(qrueck[i].rfind('q')+1);
			// ausw+=hylanr;
			// ausw+=",";
			// ausw[ausw.size()-1]=')';
			// tac /var/spool/hylafax/etc/xferfaxlog | awk -vDate=`date -d'now-1 month' +%m/%d/%y` 'function isdate(var) KLA if (var ~ /[0-9][0-9]\/[0-9][0-9]\/[0-9][0-9]/) return 1; return 0; KLZ isdate($1) && $1 > Date KLAprint Date " " $0KLZ'
			//		  cmd="tac \""+xferfaxlog+"\" 2>/dev/null|grep '"+sep+"UNSENT"+sep+"\\|"+sep+"SEND"+sep+"'|cut -f 2,5,14,20|awk '!s[$2]++'";
			// awk-Befehl: Suche bis vor 3 Monaten von zu jeder hylanr ($5) die letzte Zeile (s[$5]==0) mit dem Befehl ($2) SEND oder UNSENT; gib mit \t aus
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
			string auswe="(", auswm="(", inse;
			for(size_t i=0;i<qrueck.size();i++) {
				vector<string> tok; 
				aufSplit(&tok,&qrueck[i],'\t');
				if (tok.size()>5) {
					// <<tok[0]<<'|'<<tok[1]<<'|'<<tok[2]<<'|'<<tok[3]<<'|'<<tok[4]<<'|'<<tok[5]<<'|'<<tok[6]<<endl;
					uchar erfolg=0;
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
				//		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_ON);
				RS vgl1(My,"DROP TABLE IF EXISTS tmph",ZDB);
				RS vgl2(My,"CREATE TABLE tmph(submid VARCHAR(11) KEY,Datum DATETIME,tel VARCHAR(30),pages INT,attr VARCHAR(20),erfolg INT);",ZDB);
				RS vgl3(My,"INSERT INTO tmph VALUES "+inse,ZDB);
				// die laut xferfaxlog uebermittelten Faxe, die nicht in outa als uebermittelt eingetragen sind, 
				// und zu denen nicht bereits eine erfolgreiche capisuite-Uebertragung eingetragen ist
				RS ntr(My,"SELECT t.submid p0,t.tel p1,a.original p2,unix_timestamp(t.Datum) p3,IF(ISNULL(a.hdateidatum),t.Datum,a.hdateidatum) p4, "
				    "a.idudoc p5,t.pages p6 FROM tmph t "
						"LEFT JOIN `"+touta+"` o ON t.submid = o.submid "
						"LEFT JOIN `"+altspool+"` a ON t.submid=a.hylanr "
						"LEFT JOIN `"+touta+"` o2 ON o2.submid=a.capispooldatei AND NOT ISNULL(a.capispooldatei) AND a.capispooldatei<>'' AND o2.erfolg<>0 "
						"WHERE ISNULL(o.erfolg) AND t.erfolg<>0 AND (ISNULL(o2.submid) OR o2.submid='') "
						"GROUP BY t.submid",ZDB);
				char ***cerg;
				// size_t znr=0;
				while (cerg=ntr.HolZeile(),cerg?*cerg:0) {
					//<<"znr: "<<rot<<++znr<<schwarz<<endl;
					const string hylanr = *(*cerg+0);
					/*4*/fsfcl fsf(hylanr); // hylanr

					svec rueckf;
					cmd="find "+varsphylavz+"/archive/"+hylanr+" -iname \"doc*\\.pdf\\."+hylanr+"\"";
					systemrueck(cmd,obverb-1,oblog,&rueckf);
					struct stat entrys={0};
					if (rueckf.size()) {
						lstat(rueckf[0].c_str(),&entrys);
					}
					if (*(*cerg+1)) fsf.telnr=*(*cerg+1);    // tel
					if (*(*cerg+2)) fsf.original=*(*cerg+2); // original
					if (*(*cerg+3)) fsf.tts=atol(*(*cerg+3)); // Datum (aus xferfaxlog, tts
					if (*(*cerg+4)) fsf.hdd=*(*cerg+4);
					if (*(*cerg+5)) fsf.idudoc=*(*cerg+5);
					if (fsf.idudoc.empty()) fsf.idudoc="0";
					if (*(*cerg+6)) fsf.pseiten=atol(*(*cerg+6));
					// <<"vor archiviere, telnr: "<<fsf.telnr<<" tts: "<<fsf.tts<<" hdd: "<<fsf.hdd<<" original: "<<fsf.original<<
					//                           " hdd: "<<fsf.hdd<<" idudoc: "<<fsf.idudoc<<endl;
					fsf.archiviere(My,this,&entrys,0,hyla,0,obverb,oblog);
				} // 				while (cerg=ntr.HolZeile(),cerg?*cerg:0)
				//		mysql_set_server_option(My->conn,MYSQL_OPTION_MULTI_STATEMENTS_OFF);
			} // 			if (inse.size()>1)
			// "select tmph.i,submid,erfolg,outa.* from tmph left join outa on tmph.i=outa.submid
			// select t.*,a.capispooldatei,o2.erfolg, o2.submid from tmph t left join outa o on t.submid = o.submid 
			// left join altspool a on a.hylanr = t.submid left join outa o2 on a.capispooldatei=o2.submid where isnull(o.submid);
			char ***cerg;
			size_t cergz=0;
			if (auswe.size()>2) {
				RS rs1(My,"SELECT submid FROM `"+touta+"` WHERE erfolg=0 AND submid IN "+auswe,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
				string auswmf="(";  // fuer die Ausgabe
				while (cerg=rs1.HolZeile(),cerg?*cerg:0) {
					if (!cergz++)
						::Log(Tx[T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Erfolg_gesetzt_werden],1,1);
					auswmf+="'";
					auswmf+=*(*cerg+0); 
					auswmf+="',";
					// <<violett<<*(*cerg+0)<<schwarz<<endl; 
				} // 				while (cerg=rs1.HolZeile(),cerg?*cerg:0)
				if (cergz) {
					auswmf[auswmf.size()-1]=')';
					tu_lista("",auswmf);
					RS k1(My,"UPDATE `"+touta+"` SET erfolg=1 WHERE erfolg=0 AND submid IN "+auswe,ZDB);
				} // 				if (cergz) 
			} // 		if (auswe.size()>1)
			if (auswm.size()>2) {
				RS rs2(My,"SELECT submid FROM `"+touta+"` WHERE erfolg=1 AND submid IN "+auswm,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
				cergz=0;
				string auswef="("; // zur Ausgabe
				while (cerg=rs2.HolZeile(),cerg?*cerg:0) {
					if (!cergz++)
						::Log(Tx[T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Misserfolg_gesetzt_werden],1,1);
					auswef+="'";
					auswef+=*(*cerg+0); 
					auswef+="',";
					// <<rot<<*(*cerg+0)<<schwarz<<endl; 
				} // 			while (cerg=rs2.HolZeile(),cerg?*cerg:0)
				if (cergz) {
					auswef[auswef.size()-1]=')';
					tu_lista("",auswef);
					RS k1(My,"UPDATE `"+touta+"` SET erfolg=0 WHERE erfolg=1 AND submid IN "+auswm,ZDB);
				} // 				if (cergz) 
			} // 		if (auswm.size()>1)
			// <<blau<<auswe<<schwarz<<endl;
			// <<rot<<auswm<<schwarz<<endl;
			return;
			// string ausw="(";
			// uchar indb;
			// string hylanr;
			//        RS rs(My,string("SELECT id FROM `")+touta+"` WHERE submid="+hylanr,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
			//        if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
			// if (!indb) KLA
			//		<<hylanr<<" fehlt"<<endl;
			//		/*4*/fsfcl fsf(hylanr); // fsf(rueck[i]);
			// KLZ // if (!indb)
			// RS rs(My,string("SELECT id FROM `")+touta+"` WHERE submid in "+ausw,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
			// while (cerg=rs.HolZeile(),cerg?*cerg:0) KLA
			// KLZ
		} // if (!lstat(hsendqvz.c_str(),&entryvz))
	} // 	if (!xferfaxlog.empty())
} // void paramcl::korrigierehyla()

// aufgerufen in: empfarch, zupdf
int paramcl::holtif(const string& datei,ulong *seitenp,struct tm *tmp,struct stat *elogp, 
                    string *absdrp,string *tsidp,string *calleridp,string *devnamep)
{
	Log(violetts+Tx[T_holtif]+schwarz);
	int erg=1;
    vector<string> tok; // fuer imagedescription
		if (tmp) {
			memset(tmp, 0, sizeof(*tmp));
			if (elogp) {
				memset(elogp,0,sizeof *elogp);
				if (!lstat(datei.c_str(),elogp))  {
//					if (chmod(datei.c_str(),S_IRWXU|S_IRWXG|S_IRWXO)) systemrueck("sudo chmod +r \""+datei+"\"",obverb,oblog);
					memcpy(tmp, localtime(&elogp->st_mtime),sizeof(*tmp));
					/*
					char buf[100];
					strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", tmp);
					// <<"Buf: "<<buf<<endl;
					*/
				} //     if (!lstat(datei.c_str(),elogp)) 
			} // if (elogp)
		} // if (tmp)
		setfaclggf(dir_name(datei),falsch,7,falsch,obverb,oblog);
		setfaclggf(datei,falsch,4,falsch,obverb,oblog,0);
		if (TIFF* tif = TIFFOpen(datei.c_str(), "r")) {
			erg=0;
			char *rdesc=0;
			if (tmp) {
				if (TIFFGetField(tif, TIFFTAG_DATETIME, &rdesc)) {
					// <<"Datetime: \n"<<rdesc<<endl;
					strptime(rdesc,"%Y:%m:%d %T",tmp);
					/*
						 char buf[100];
						 strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", tmp);
						 <<"Buf (2): "<<buf<<endl;
					 */
				} // if (TIFFGetField(tif, TIFFTAG_DATETIME, &rdesc))
			} // if (tmp)
      if (seitenp) *seitenp=TIFFNumberOfDirectories(tif);
      rdesc=0;
      if (TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &rdesc)) {
        //          printf("Beschreibung: %s\n",beschreib);
        //  out<<"Beschreibung: \n"<<rdesc<<endl;
        tok.clear();
        aufSplit(&tok,rdesc,'\n');
        if (tok.size()) {
          if (tok.size()>1) {
            // <<gruen<<"tok[0]: "<<schwarz<<tok[0]<<endl;
            if (calleridp) *calleridp=tok[0];
            // <<gruen<<"tok[1]: "<<schwarz<<tok[1]<<endl;
            *tsidp=tok[1];
            if (tok.size()>2) if (absdrp) *absdrp=tok[2];
          } else {
            if (istelnr(tok[0])) {
              // <<gruen<<"tok[0] b: "<<schwarz<<tok[0]<<endl;
              if (calleridp) *calleridp=tok[0]; 
            } else { 
              // <<gruen<<"tok[0] c: "<<schwarz<<tok[0]<<endl;
              if (absdrp) *absdrp=tok[0];
            }
          } //           if (tok.size()>1)  else
        } // if (tok.size()) 
      } // if (TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &rdesc)) 
      // rdesc=0;
      // if (TIFFGetField(tif, TIFFTAG_MODEL, &rdesc))
      rdesc=0;
			uchar obdev=0;
			if (calleridp) {if (calleridp->empty()) obdev=1;} else obdev=1;
			if (obdev) if (!devnamep) obdev=0;
      if (obdev) {
        if (TIFFGetField(tif, TIFFTAG_MAKE, &rdesc)) {
          //          printf("Beschreibung: %s\n",beschreib);
          // <<gruen<<"rdesc: "<<schwarz<<rdesc<<endl;
          if (rdesc) {
            *devnamep+=", ";
            *devnamep+=rdesc;
          }
        } // if (TIFFGetField(tif, TIFFTAG_MAKE, &rdesc)) 
      } // if (calleridp->empty()) 
      TIFFClose(tif);
    } // if (TIFF* tif = TIFFOpen(datei.c_str(), "r")) 
 return erg;
} // int paramcl::holtif(string& datei,struct tm *tmp,ulong *seitenp,string *calleridp,string *devnamep)

// wird aufgerufen in: main
void paramcl::empfarch()
{
	Log(violetts+Tx[T_empfarch]+schwarz);
	char tbuf[100]={0};
	ulong pseiten=0;
	// 1) hyla
	const string hempfavz=varsphylavz+"/autofaxarch"; // /var/spool/capisuite/empfarch/
	// Faxe in der Empfangswarteschlange auflisten, ...
	cmd=string("sudo find \"")+varsphylavz+"/recvq\" -name \"fax*.tif\"";
	vector<string> rueck;
	systemrueck(cmd,obverb,oblog, &rueck);
	for(size_t i=0;i<rueck.size();i++) {
		if (!i) {
			pruefverz(hempfavz,obverb,oblog);
		} //     if (!i)
		// ..., Informationen darueber einsammeln, ...
		string zeit;
		string absdr,tsid,callerid,devname=hmodem;
		string stamm,exten;const string ganz=rueck[i];
		getstammext(&ganz,&stamm,&exten);
		string base=base_name(stamm);
		string fnr=base.substr(3);
		fnr=fnr.substr(fnr.find_first_not_of("0"));
		struct tm tm={0};
		struct stat elog={0};
    ulong seiten=0;
		if (!holtif(rueck[i],&seiten,&tm,&elog,&absdr,&tsid,&callerid,&devname))
			ankzahl++;

    string tabsdr; // transferierter Absender
    if (callerid.empty()) {
      svec trueck;
      systemrueck(string("tac \"")+xferfaxlog+"\" 2>/dev/null |grep -m 1 \""+base_name(rueck[i])+"\" |cut -f8,9",obverb,oblog,&trueck); 
      if (trueck.size()) {
				vector<string> tok; 
        aufSplit(&tok,&trueck[0],'\t');
        if (tok.size()) {
          // <<gruen<<"tok[0] d: "<<schwarz<<tok[0]<<endl; // Tel'nr z.B. 49.8131.1234567
          callerid=tok[0];
          if (tok.size()>1) {
            // <<gruen<<"tok[1] d: "<<schwarz<<tok[1]<<endl; // Namen z.B. G.Schade
            tabsdr=tok[1];
            anfzweg(tabsdr); // Anfuehrungszeichen entfernen
          } //           if (tok.size()>1)
        } // if (tok.size()) 
      } // if (trueck.size()) 
    } // if (callerid.empty()) 
    // <<gruen<<"tsid: "<<schwarz<<tsid<<endl;
    tsid=stdfaxnr(tsid.empty()?callerid:tsid);
    if (absdr.empty()) {
      string bsname;
      getSender(this,tsid,&absdr,&bsname,obverb,oblog);
      // <<gruen<<"absdr("<<tsid<<"): "<<schwarz<<absdr<<" bsname: "<<bsname<<endl;
      if (!bsname.empty()) {
        absdr+=", ";
        absdr+=bsname;
      }
      if (absdr.empty() || istelnr(absdr)) { // wenn Nr. nicht gefunden, kommt sie in absdr wieder zurueck
        absdr=tabsdr;
      }
    } //     if (absdr.empty())
    if (absdr.length()>187) absdr.erase(187);

    strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H.%M.%S", &tm);
    if (absdr.length()>187) absdr.erase(187);
    if (absdr.length()>70) absdr.erase(70);
    const string hrumpf="Fax h"+fnr+","+Tx[T_avon]+absdr+", T."+tsid+", "+Tx[T_vom]+tbuf;
    const string hdatei=hrumpf+".tif";
    const string hpfad=empfvz+vtz+hdatei;
    const string ziel=empfvz+vtz+hrumpf+".pdf";
    ::Log(blaus+base+schwarz+" => "+gruen+hdatei+schwarz,1,1);
    // ..., die empfangene Datei in hpfad kopieren ...
    uint kfehler=0;
    string vorsoffice=kopiere(rueck[i],hpfad,&kfehler,1,obverb,oblog);
    if (!kfehler) {
      systemrueck("sudo chown --reference=\""+empfvz+"\" \""+hpfad+"\"",obverb,oblog);
      systemrueck("sudo chmod --reference=\""+empfvz+"\" \""+hpfad+"\"",obverb,oblog);
    } else {
      vorsoffice=rueck[i];
    } //     if (!kfehler) else
    struct stat entrynd={0};
		int obpdfda=0;
    int obhpfadda=!lstat(hpfad.c_str(),&entrynd);
		if (obhpfadda)
			if (chmod(hpfad.c_str(),S_IRWXU|S_IRGRP|S_IROTH))
				systemrueck("sudo chmod +r \""+hpfad+"\"",obverb,oblog);
		if (obocri) {
      obpdfda=!zupdf(&vorsoffice, ziel, &pseiten, obocri, 1); // 0=Erfolg
			if (obpdfda) if (!lstat(ziel.c_str(),&entrynd)) if (!kfehler) tuloeschen(hpfad,cuser,obverb,oblog);
    } // if (obocri) 
    if (obhpfadda||obpdfda) {
      cmd=string("sudo mv \"")+rueck[i]+"\" \""+hempfavz+"\"";
      systemrueck(cmd,obverb,oblog);
      RS zs(My);
      // ... und falls erfolgreich in der Datenbanktabelle inca eintragen
      for(int runde=0;runde<2;runde++) {
        if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
        } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
        RS rins(My); 
        vector<instyp> einf; // fuer alle Datenbankeinfuegungen
        einf.push_back(/*2*/instyp(My->DBS,"fsize",elog.st_size));
        einf.push_back(/*2*/instyp(My->DBS,"pages",seiten));
        einf.push_back(/*2*/instyp(My->DBS,"titel",&absdr));
        einf.push_back(/*2*/instyp(My->DBS,"tsid",&tsid));
        //        einf.push_back(instyp(My->DBS,"callerid",&callerid));
        einf.push_back(/*2*/instyp(My->DBS,"devname",&devname));
        einf.push_back(/*2*/instyp(My->DBS,"id",&base));
        einf.push_back(/*2*/instyp(My->DBS,"transe",&tm));
        rins.insert(tinca,einf, 1,0,ZDB?ZDB:!runde); 
        if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
        if (!rins.fnr) break;
        if (runde==1) {
          ::Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
          exit(24);
        } //         if (runde==1)
      } // for(int runde=0;runde<2;runde++) 
    } // if (!lstat(hpfad.c_str(),&entrynd)) 
  } // for(size_t i=0;i<rueck.size();i++) 

  // 2) capi
  const string cempfavz=spoolcapivz+"/autofaxarch"; // /var/spool/capisuite/empfarch/
  /*
     cppSchluess umst[]={{"filename"},{"call_from"},{"call_to"},{"time"},{"cause"}};
     size_t cs=sizeof umst/sizeof*umst;
   */
  schlArr umst; umst.init(5,"filename","call_from","call_to","time","cause");
  struct stat entryvz={0};
  //  cfaxuserrcvz="/var/spool/capisuite/users/schade/received";
  if (!lstat(cfaxuserrcvz.c_str(),&entryvz)) /* /var/spool/capisuite/users/~/received */ {
    // Faxe in der Empfangswarteschlange auflisten, ...
    cmd=string("sudo find \"")+cfaxuserrcvz+"\" -maxdepth 1 -type f -iname \"*.txt\"";
    vector<string> rueck;
    systemrueck(cmd,obverb,oblog, &rueck);
    for(size_t i=0;i<rueck.size();i++) {
      if (!i) {
        pruefverz(cempfavz,obverb,oblog);
        pruefsfftobmp();
      } // if (!i)
      ankzahl++;
      // ..., Informationen darueber einsammeln, ...
      string stamm,exten;
      getstammext(&(rueck[i]),&stamm,&exten);
      Log(string("txt: ")+tuerkis+(rueck[i])+schwarz);
      const string sffdatei=stamm+".sff";
      struct stat entrysff={0};
      uchar verschieb=0;
      confdat empfconf(rueck[i],&umst,obverb);
      //    if (cpplies(rueck[i],umst,cs)) KLA
			struct tm tm={0};
			for(unsigned i=0;i<5;i++) {
			 string *sptr=&umst[i].wert;
			 if (i==3) {
				 for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++) {
					 if (strptime(umst[i].wert.c_str(), tmmoegl[im], &tm)) break;
				 }
				 strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H.%M.%S", &tm);
				 // tbuf und tm enthalten also z.B. die in /var/spool/capisuite/users/<user>/received/fax-999999.txt unter "time" stehende Zeit
				 string s=tbuf;
				 sptr=&s;
			 }
			 Log(schwarzs+"   "+umst[i].name+": "+tuerkis+*sptr);
			}

      const string base=base_name(stamm);
      const string fnr=base.substr(4);
      tm.tm_isdst=-1; // sonst wird zufaellig ab und zu eine Stunde abgezogen
      time_t modz=mktime(&tm);
      string getname,bsname;
      getSender(this,umst[1].wert,&getname,&bsname,obverb,oblog);
      getname+=", ";
      getname+=bsname;
//      if (getname.length()>187) getname.erase(187);
      if (getname.length()>70) getname.erase(70);
      const string tifrumpf="Fax c"+fnr+","+Tx[T_avon]+getname+", T."+stdfaxnr(umst[1].wert)+","+Tx[T_vom]+tbuf;
      const string tifdatei=tifrumpf+".tif";
      string tifpfad=empfvz+vtz+tifdatei; // Tx[T_Fax_von]+umst[1].wert+Tx[T_an]+umst[2].wert+Tx[T_vom]+tbuf+".tif";
      ::Log(blaus+stamm+schwarz+" => "+gruen+tifdatei+schwarz,1,1);
      // ..., die empfangene Datei in tifpfad kopieren ...
      uint vfehler=0;
      if (lstat(sffdatei.c_str(),&entrysff)) {
        // .txt nach falsche verschieben
        verschieb=1;
      } else {
        uint kfehler=1;
        int erg=-1;
        if (entrysff.st_size) {
					// -f == force, steht nicht in --help
					svec sfferg;
          cmd=string("sfftobmp -f -d -t ")+sffdatei+" -o \""+tifpfad+"\"";
					erg=systemrueck(cmd,obverb,oblog,0,0,wahr,"",0,1);
					if (!erg) {
					 attrangleich(tifpfad,empfvz,obverb,oblog);
					 // bereits hier, da weder convert noch soffice noch ocrmypdf eine *.sff-Datei lesen kann, convert auch keine tiff-Datei
					 if (obocri) {
						 const string ziel=empfvz+vtz+tifrumpf+".pdf"; 
						 int obpdfda=!zupdf(&tifpfad, ziel, &pseiten, obocri, 1); // 0=Erfolg
						 struct stat entrynd={0};
						 if (obpdfda) if (!lstat(ziel.c_str(),&entrynd)) if (!kfehler) tuloeschen(tifpfad,cuser,obverb,oblog);
					 } // if ((erg=systemrueck(cmd,obverb,oblog))) else if (obocri)
					} else {
						verschieb=2;
						tifpfad=empfvz+vtz+tifrumpf+".sff";
						kopiere(sffdatei,tifpfad,&kfehler,1,obverb,oblog);
            if (!kfehler) {
              systemrueck("sudo chown --reference=\""+empfvz+"\" \""+tifpfad+"\"",obverb,oblog);
              systemrueck("sudo chmod --reference=\""+empfvz+"\" \""+tifpfad+"\"",obverb,oblog);
						} else {
						  tifpfad=sffdatei;
            } // if (!kfehler) else
					} // if (!erg) else
        } else {
          // empfangenes Fax mit 0 Bytes, vermutlich abgefangen von anderem System, samt Textdatei nach 'falsche' verschieben
          verschieb=2;
        } // if (entrysff.st_size)
        // wenn sfftobmp funktioniert hat // oder die Datei verschoben wurde
        if (!erg) {
#ifdef ueberfluessig 
          struct utimbuf ubuf={0};
          ubuf.modtime = modz;
          ubuf.actime = modz;
          if (utime(tifpfad.c_str(),&ubuf)) {
            ::Log(rots+Tx[T_Fehler_beim_Datumsetzen_von]+tifpfad+rot+"'"+schwarz,1,1);
          } else 
#endif
						if (!verschieb) {
							dorename(sffdatei,cempfavz+vtz+cuser+"-"+base+".sff",cuser,&vfehler,obverb,oblog);
            dorename(rueck[i],cempfavz+vtz+cuser+"-"+base_name(rueck[i]),cuser,&vfehler,obverb,oblog);
          } // if (utime(tifpfad.c_str(),&ubuf))  else
        } // if (!lstat(tifpfad.c_str(),&entrytifpfad))
      } // if (lstat(sffdatei.c_str(),&entrysff)) else  
      if (verschieb) {
//        if (loee) KLA
          const string falsche = cfaxuserrcvz+"/falsche";
          pruefverz(falsche,obverb,oblog);
          verschiebe(rueck[i],falsche,cuser,&vfehler,1,obverb,oblog);
          if (verschieb==2) {
            ::Log(string(Tx[T_Dateien])+rot+stamm+".* "+schwarz+Tx[T_nicht_verarbeitbar_Verschiebe_sie_nach]+rot+"./falsche"+schwarz+".",1,1);
            verschiebe(sffdatei,falsche,cuser,&vfehler,1,obverb,oblog);
            // so, dass es jeder merkt
            touch(empfvz+vtz+Tx[T_nicht_angekommen]+tifrumpf+".nix",obverb,oblog);
          } // if (verschieb==2) 
//      KLZ // if (loee) 
      } // if (verschieb) 
      RS zs(My);
      for(int runde=0;runde<2;runde++) {
        if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
        } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
        RS rins(My); 
        vector<instyp> einf; // fuer alle Datenbankeinfuegungen
        einf.push_back(/*2*/instyp(My->DBS,"titel",getname+", "+bsname));
        einf.push_back(/*2*/instyp(My->DBS,"tsid",&umst[1].wert));
        einf.push_back(/*2*/instyp(My->DBS,"transe",&modz));
        einf.push_back(/*2*/instyp(My->DBS,"id",&base));
        einf.push_back(/*2*/instyp(My->DBS,"fsize",entrysff.st_size));
        einf.push_back(/*2*/instyp(My->DBS,"csid",&umst[2].wert));
        einf.push_back(/*2*/instyp(My->DBS,"pages",pseiten));
        rins.insert(tinca,einf, 1,0,ZDB?ZDB:!runde); 
        if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
        if (!rins.fnr) break;
        if (runde==1) {
          ::Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
          exit(26);
        }
      } // for(int runde=0;runde<2;runde++) 
    } // for(size_t i=0;i<rueck.size();i++) 
  } // if (!lstat(cfaxuserrcvz.c_str(),&entryvz)) /* /var/spool/capisuite/users/~/received */ 
} // void paramcl::empfarch()

// wird aufgerufen in: main
void paramcl::schlussanzeige()
{
  Log(violetts+Tx[T_schlussanzeige]+schwarz);
  tende = clock();
  //  ausg.str(std::string()); ausg.clear();
  //  ausg<<schwarz<<"Pfad: "<<tuerkis<<zufaxenvz<<schwarz<<"; Dateien: "<<tuerkis<<geszahl<<schwarz<<"; Zeit: "<<drot<<setprecision(7)<<fixed<<((tende-tstart)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s";
  if (obverb>0) {
    stringstream ausg;
    ausg<<Tx[T_Zeit_Doppelpunkt]<<drot<<setprecision(7)<<fixed<<((tende-tstart)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s";
    ::Log(ausg.str(),1,oblog); 
  } //   if (obverb>0)
  ::Log(string(Tx[T_Zahl_der_empfangenen_Faxe])+drot+ltoan(ankzahl)+schwarz,1,oblog);
  ::Log(string(Tx[T_Zahl_der_ueberpruefen_Datenbankeintraege])+drot+ltoan(dbzahl)+schwarz,1,oblog);
  ::Log(string(Tx[T_davon_gescheiterte_Faxe])+drot+ltoan(gzahl)+schwarz,1,oblog);
  ::Log(string(Tx[T_davon_erfolgreiche_Faxe])+drot+ltoan(ezahl)+schwarz,1,oblog);
  ::Log(string(Tx[T_davon_noch_wartende_Faxe])+drot+ltoan(wzahl)+schwarz,1,oblog);
  ::Log(string(Tx[T_davon_nicht_in_Warteschlange])+drot+ltoan(fzahl)+schwarz,1,oblog);
  Log(string(Tx[T_Fertig_mit])+blau+meinname+schwarz+" !");
} // paramcl::schlussanzeige


// ermittelt fuer eine in ein Zielverzeichnis zu kopierende Datei den dortigen Namen, falls gewuenscht unter Beruecksichtigung 
// dort evtl. schon vorhandener Dateien
// wird aufgerufen von verschiebe (Version 1) und kopiere (Version 1), neuerdateiname, zielname (Version 2)
string zielname(const string& qdatei, const string& zielvz, uchar wieweiterzaehl/*=0*/, string* zieldatei/*=0*/, int obverb/*=0*/, int oblog/*=0*/)
{
  //  Log(violetts+Tx[T_zielname]+schwarz,obverb,oblog);
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  struct stat entryziel={0};
  string dateiname=base_name(qdatei);
  string ziel = zielvz + (zielvz[zielvz.length()-1]==vtz?"":vtzs)+ dateiname;
  Log(string(Tx[T_zielname_erstes_Ziel])+rot+ziel+schwarz+"'",obverb,oblog);
  if (wieweiterzaehl<2) {
    unsigned long ausweich=0;
    string stamm,exten;
    getstammext(&dateiname,&stamm,&exten);
    // wenn von einer vorhandenen Ausweichnummerierung aus weitergezaehlt werden soll (anstatt dateiname_1_1 ...)
    if (wieweiterzaehl) {
      size_t pos = stamm.rfind('_');
      if (pos!=string::npos) {
        const string auswstr=stamm.substr(pos+1);
        if (isnumeric(auswstr)) { 
          ausweich=atol(auswstr.c_str());
          if (ausweich) if (stamm.length()>pos) stamm.erase(pos);
        }
      } // if (pos!=string::npos) 
    } // if (wieweiterzaehl) 
    uchar ausgewichen=0;
    for(;1;) {
      if (lstat(ziel.c_str(), &entryziel)) break;
      ausweich++;
      ausgewichen=1;
      dateiname=stamm+"_"+ltoan(ausweich)+"."+exten;
      ziel=zielvz + (zielvz[zielvz.length()-1]==vtz?"":vtzs) + dateiname;
    } // for(;1;) 
    if (ausgewichen) Log(string(Tx[T_zielname_Ausweichziel])+rot+ziel+schwarz+"'",obverb,oblog);
  } // if (wieweiterzaehl<2) 
  if (zieldatei) *zieldatei=dateiname;
  return ziel;
} // zielname 

// wird aufgerufen in: verschiebe (Version 2), kopiere (Version 2), neuerdateiname, 
string zielname(const string& qdatei, zielmustercl *zmp, uchar wieweiterzaehl/*=0*/, string* zieldatei/*=0*/, int obverb/*=0*/, int oblog/*=0*/)
{
  //  Log(violetts+Tx[T_zielname]+schwarz,obverb,oblog);
  for(zielmustercl *zmakt=zmp;1;zmakt++){
    int reti=regexec(&(zmakt->regex),qdatei.c_str(),0,NULL,0);
    Log(string(Tx[T_Datei])+rot+qdatei+schwarz+Tx[T_entspricht]+(reti?Tx[T_entsprichtnicht]:Tx[T_entsprichtdoch])+
        Tx[T_Muster_Doppelpunkt]+rot+zmakt->holmuster()+schwarz+"'",obverb,oblog);
    if (!reti){
      return zielname(qdatei,zmakt->ziel,wieweiterzaehl,zieldatei,obverb,oblog);
    } //     if (!reti)
    if (zmakt->obmusterleer()) break;
  } //   for(zielmustercl *zmakt=zmp;1;zmakt++)
  return "";
} // zielname


// wird aufgerufen in: verschiebe (Version 1), verschiebe (Version 2), DateienHerricht
void dorename(const string& quelle, const string& ziel, const string& cuser, uint *vfehler, int obverb, int oblog)
{
	Log(string(Tx[T_Verschiebe])+tuerkis+quelle+schwarz+"'\n         -> '"+gruen+ziel+schwarz+"'",obverb,oblog);
	for(uchar iru=1;iru<3;iru++) {
		int renerg=rename(quelle.c_str(),ziel.c_str());
		//    if (rename(quelle.c_str(),ziel.c_str()))
		if (renerg) {
			if(cuser.empty()) iru++;
			if(iru==1) {
				setfaclggf(dir_name(quelle), wahr, 7, wahr,obverb,oblog);
			} else {
				perror(Tx[T_Fehler_beim_Verschieben]);
				const string cmd=string("sudo mv \"")+quelle+"\" \""+ziel+"\"";
				int erg=systemrueck(cmd,obverb,1);
				if (vfehler) {
					*vfehler+=erg;
				}
			} // if(iru) else
		} // if (rename(quelle.c_str(),ziel.c_str())) 
		else break;
	} // for(uchar iru=1;iru>-1;iru--)
} // dorename


// wird aufgerufen von Dateienherricht und untersuchespool; Vorsicht, wenn qdateip ein Verzeichnisname ist!
string verschiebe(const string& qdatei, const string& zielvz, const string& cuser, uint *vfehler, uchar wieweiterzaehl, int obverb,int oblog)
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  const string ziel=zielname(qdatei,zielvz,wieweiterzaehl,0,obverb,oblog);
  if (!ziel.empty()) dorename(qdatei,ziel,cuser,vfehler,obverb,oblog);
  return ziel;
} // string verschiebe

// wird aufgerufen von untersuchespool; Vorsicht, wenn qdateip ein Verzeichnisname ist!
void verschiebe(const string& qdatei, zielmustercl *zmp, const string& cuser, uint *vfehler, uchar wieweiterzaehl, int obverb, int oblog) 
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  const string ziel=zielname(qdatei,zmp,wieweiterzaehl,0,obverb,oblog);
  if (!ziel.empty()) dorename(qdatei,ziel,cuser,vfehler,obverb,oblog);
} // verschiebe

// wird aufgerufen in Dateienherricht und empfarch und kopiere (andere Definition)
string kopiere(const string& qdatei, const string& zield, uint *kfehler, uchar wieweiterzaehl, int obverb, int oblog)
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  const string dir=dir_name(zield);
  const string base=base_name(zield);
  string ziel;
  int fehler=0;
  if (!base.empty() && !dir.empty()) {
    ziel=zielname(base,dir,wieweiterzaehl,0, obverb,oblog);
    Log(string(Tx[T_Kopiere_Doppelpunkt])+rot+qdatei+schwarz+"'\n         -> '"+rot+ziel+schwarz+"'",obverb,oblog);
    fehler=kopier(qdatei,ziel,obverb,oblog);
    if (fehler) {
     kfehler+=fehler;
     Log(rots+Tx[T_Fehler_beim_Kopieren]+Tx[T_Dateiname]+blau+zield+schwarz,1,1);
    } // if (fehler) 
  } else {
    Log(rots+Tx[T_Fehler_beim_Kopieren]+Tx[T_Dateiname]+blau+zield+schwarz+Tx[T_schlechtgeformt],1,1);
  } // if (!base.empty() && !dir.empty())  else 
  return ziel;
} // string kopiere

// wird aufgerufen in Dateienherricht
string kopiere(const string& qdatei, zielmustercl *zmp, uint *kfehler, uchar wieweiterzaehl, int obverb, int oblog) 
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  const string ziel=zielname(qdatei,zmp,wieweiterzaehl,0, obverb,oblog);
  return kopiere(qdatei, ziel, kfehler, wieweiterzaehl,obverb,oblog);
} // string kopiere

// wird aufgerufen in pruefhyla
// hylafax konfigurieren 
void hfaxsetup(paramcl *pmp,int obverb/*=0*/, int oblog/*=0*/)
{
  Log(violetts+"hfaxsetup()"+schwarz,obverb,oblog);
  string faxsu;
  //  const char *faxsu="/usr/sbin/faxsetup";
  if (obprogda("faxsetup",obverb,oblog,&faxsu)) {
#ifdef autofaxsetup
    // das Skript faxsetup soll leicht veraendert als 'autofaxsetup' abgespeichert und dann aufgerufen werden
    const char *afaxsu="/usr/local/sbin/autofaxsetup";
    mdatei alt(faxsu,ios::in);
    if (alt.is_open()) {
      mdatei neu(afaxsu,ios::out);
      if (neu.is_open()) {
        string zeile, ergzeile;
        size_t znr=0,promptz=0;
        string vorgabe;
        while(getline(alt,zeile)) {
          size_t p0,p1,kla,klz,einr=0;
          uchar zukomm=0;
          if (zeile.find("INTERACTIVE=yes")!=string::npos) {
            zeile="INTERACTIVE=no" # Aenderung G.Schade 25.5.16;
          } else if (zeile.find("ok=prompt")!=string::npos) {
            // Interaktivitaet streichen
            zeile="     ok=skip    # prompt for parameters # Aenderung G.Schade 1.1.16";
          } else if (!zeile.find("PATH_EGETTY=")) {
            // suche das aktuelle Fax-Empfangsprogramm; 'which faxgetty' geht nicht immer, da z.B. /usr/lib/fax/ nicht im Standard-Befehlssuchpfad,
            // aber unter Opensuse 42.1 der Vorgabeort fuer faxgetty
            zeile="PATH_EGETTY=$(sudo find /usr/lib/fax /usr/sbin /usr/bin /root/bin /sbin -perm /111 -name faxgetty 2>/dev/null) "
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
            if (zukomm) zeile=string("# ")+zeile+" # Kommentar G.Schade 1.1.16";
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
          systemrueck(string("sudo chmod 770 '")+afaxsu+"'",0,1);
        pmp->sfaxgetty->stop(obverb,oblog);
        pmp->shfaxd->stop(obverb,oblog);
        pmp->sfaxq->stop(obverb,oblog);
        /*
           systemrueck(string("sudo systemctl stop ")+pmp->sfaxgetty->sname+" "+pmp->shfaxd->sname+" "+pmp->sfaxq->sname,obverb,oblog);
           systemrueck(string("sudo pkill ")+pmp->sfaxgetty->ename+" "+pmp->shfaxd->ename+" "+pmp->sfaxq->ename,obverb,oblog);
         */
        Log(blaus+Tx[T_Fuehre_aus_Dp]+schwarz+afaxsu+blau+Tx[T_falls_es_hier_haengt_bitte_erneut_aufrufen]+schwarz,1,oblog);
        system((string("/usr/bin/sh ")+afaxsu+(obverb?" -verbose":"")+" >/dev/null 2>&1").c_str()); 
        pmp->sfaxgetty->restart(obverb,oblog);
        pmp->shfaxd->restart(obverb,oblog);
        pmp->sfaxq->restart(obverb,oblog);
        //        systemrueck(string("source ")+afaxsu+(obverb?" -verbose":""),obverb,oblog,0,falsch); // haengt am Schluss, geht nicht mit unbuffer, unbuffer /usr/local/sbin/autofaxsetup -verbose, loeschen von exit 0 am schluss, exec, stty -echo -onlcr usw., nohup,
        Log(blaus+Tx[T_Fertig_mit]+schwarz+afaxsu,1,oblog);
        servc::daemon_reload();
        //        systemrueck(string("rm ")+afaxsu,1,1);
      } // if (neu.is_open()) 
    } // if (alt.is_open()) 
#else
    pmp->sfaxgetty->stop(obverb,oblog,1);
    pmp->shfaxd->stop(obverb,oblog,1);
    pmp->sfaxq->stop(obverb,oblog,1);
    /*
       systemrueck(string("sudo systemctl stop ")+pmp->sfaxgetty->sname+" "+pmp->shfaxd->sname+" "+pmp->sfaxq->sname,obverb,oblog);
       systemrueck(string("sudo pkill ")+pmp->sfaxgetty->ename+" "+pmp->shfaxd->ename+" "+pmp->sfaxq->ename,obverb,oblog);
     */
    Log(blaus+Tx[T_Fuehre_aus_Dp]+schwarz+"sudo "+faxsu+" -nointeractive"+blau+Tx[T_falls_es_hier_haengt_bitte_erneut_aufrufen]+schwarz,1,oblog);
    pruefplatte();
    if (!systemrueck("sudo "+faxsu+" -nointeractive"+(obverb?" -verbose":""),obverb,oblog,0,2)) {
     pmp->shfaxd->stop(obverb,oblog,1);
     pmp->sfaxq->stop(obverb,oblog,1);
     servc::daemon_reload();
    } // if (!systemrueck("sudo "+faxsu+" -nointeractive"+(obverb?" -verbose":""),obverb,oblog,0,2)) 
    /*
    int erg __attribute__((unused));
    erg=system(("sudo $(which sh) $(sudo env \"PATH=$PATH\" which faxsetup) -nointeractive"+string(obverb?" -verbose":"")+
          " && sudo pkill hfaxd faxq >/dev/null 2>&1"
          " && sudo systemctl daemon-reload").c_str()); 
    */
    pmp->sfaxgetty->start(obverb,oblog);
    pmp->shfaxd->start(obverb,oblog);
    pmp->sfaxq->start(obverb,oblog);
    pruefplatte();
    // systemrueck(string("source ")+faxsu+(obverb?" -verbose":""),obverb,oblog,0,falsch); // haengt am Schluss, geht nicht 
    // mit unbuffer, unbuffer /usr/local/sbin/autofaxsetup -verbose, loeschen von exit 0 am schluss, exec, stty -echo -onlcr usw., nohup,
    Log(blaus+Tx[T_Fertig_mit]+schwarz+faxsu,1,oblog);
    //    systemrueck(string("sudo systemctl daemon-reload"),0,1);

#endif
  } //   if (!lstat(faxsu, &entrybuf)) KLA
  pmp->setzfaxgtpfad();
} // hfaxsetup

void paramcl::setzfaxgtpfad()
{
  struct stat entryfaxgt={0};
	if (lstat(faxgtpfad.c_str(),&entryfaxgt)) {
		faxgtpfad.clear();
		//  faxgtpfad="/usr/lib/fax/faxgetty";
		//    faxgtpfad="/usr/sbin/faxgetty";
		obprogda("faxgetty",obverb,oblog,&faxgtpfad);
		if (faxgtpfad.empty() || lstat(faxgtpfad.c_str(),&entryfaxgt)) {
			svec rueckf;
			faxgtpfad.clear();
			systemrueck("sudo find /usr/lib/fax /usr/sbin /usr/bin /root/bin /sbin /usr/local/sbin /usr/local/bin -perm /111 -name faxgetty",obverb-1,oblog,&rueckf);
			if (rueckf.size()) 
				faxgtpfad=rueckf[0];
		}
	}
  // violett<<"faxgtpfad 4: "<<faxgtpfad<<schwarz<<endl;
}

// wird aufgerufen in: pruefhyla
void hconfig(paramcl *pmp,int obverb/*=0*/, int oblog/*=0*/)
{
  Log(violetts+"hconfig()"+schwarz,obverb,oblog);
  const string confd=pmp->varsphylavz+"/etc/config";
  mdatei conf(confd,ios::out);
  if (conf.is_open()) {
    conf<<"LogFacility:    daemon"<<endl;
    conf<<"CountryCode:    "<<pmp->countrycode<<endl;
    conf<<"AreaCode:   "<<pmp->citycode<<endl;
    conf<<"LongDistancePrefix: "<<pmp->LongDistancePrefix<<endl;
    conf<<"InternationalPrefix:  "<<pmp->InternationalPrefix<<endl;
    conf<<"DialStringRules:  \"etc/dialrules\""<<endl;
    conf<<"ServerTracing:    1"<<endl;
    conf<<"SessionTracing:   0xffffffff"<<endl;
		struct stat entryfaxsd={0};
		svec rueckf;
		string faxsdpfad=pmp->varsphylavz+"/bin/faxsend";
		if (lstat(faxsdpfad.c_str(),&entryfaxsd)) {
			faxsdpfad="/usr/sbin/faxsend";
			if (lstat(faxsdpfad.c_str(),&entryfaxsd)) {
				faxsdpfad.clear();
				systemrueck("sudo find /usr /root/bin /sbin -perm /111 -name faxsend",obverb-1,oblog,&rueckf);
				if (rueckf.size()) 
					faxsdpfad=rueckf[0];
			} // 			if (lstat(faxsdpfad.c_str(),&entryfaxsd))
		} // 		if (lstat(faxsdpfad.c_str(),&entryfaxsd))
		if (!faxsdpfad.empty())
			conf<<"SendFaxCmd:   "<<faxsdpfad<<endl;
		conf<<"Use2D:      \"no\""<<endl;
	} else {
		cerr<<"hconfig(): "<<Tx[T_Datei]<<confd<<Tx[T_nichtbeschreibbar]<<endl;
		exit(28);
	} //   if (conf.is_open())
	Log(violetts+Tx[T_Ende]+"hconfig()"+schwarz,obverb,oblog);
} // void hconfig(paramcl *pmp,int obverb, int oblog)

void paramcl::setzmodconfd()
{
  modconfdat=this->varsphylavz+"/etc/config"+"."+this->hmodem; 
}

void paramcl::hliesconf()
{
  schlArr hyalt; hyalt.init(8,"CountryCode","AreaCode","FAXNumber","LongDistancePrefix","InternationalPrefix",
                              "RingsBeforeAnswer","LocalIdentifier","MaxDials");
  setzmodconfd();
  struct stat mstat={0};
  if (lstat(modconfdat.c_str(),&mstat)) {
    hylazukonf=1;
  } else {
    confdat haltconf(modconfdat,&hyalt,obverb,':');
    if (hyalt.schl[0].wert!=countrycode || hyalt.schl[1].wert!=citycode || hyalt.schl[2].wert!=countrycode+"."+citycode+"."+msn 
        || hyalt.schl[3].wert!=LongDistancePrefix || hyalt.schl[4].wert!=InternationalPrefix 
        || hyalt.schl[5].wert!=hklingelzahl || hyalt.schl[6].wert!=LocalIdentifier|| hyalt.schl[7].wert!=maxhdials /*|| hyalt.schl[7].wert!=maxdials */
       ) {
      hylazukonf=1;
    } // if (hyalt.shl[0].wert ...
  } //   if (lstat(modconfdat.c_str(),&mstat)) else
  // hyalt.ausgeb();
} // void paramcl::hliesconf()

// wird aufgerufen in: pruefhyla (2x)
// Modem konfigurieren
void paramcl::hconfigtty()
{
  Log(violetts+"hconfigtty()"+schwarz);
  setzmodconfd();
  struct stat bakstat={0};
  if (lstat((modconfdat+".bak").c_str(),&bakstat)) {
   kopier(modconfdat,modconfdat+".bak",obverb,oblog);
  }
//  systemrueck("test -f '"+modconfdat+"' && test -f '"+modconfdat+".bak' || sudo cp -a '"+modconfdat+"' '"+modconfdat+".bak'",obverb,oblog);
  // <<rot<<modconfdat<<schwarz<<endl;
  // z.B. /var/spool/hylafax/etc/config.ttyACM0
  mdatei hci(modconfdat,ios::out);
  if (hci.is_open()) {
    // <<rot<<" ist offen"<<schwarz<<endl;
    time_t tim=time(0);
    struct tm *tm=localtime(&tim);
    char buf[80]={0};
    strftime(buf, sizeof(buf), "%d.%m.%y %T", tm);
    hci<<"# Konfiguration von hylafax durch "+meinname+" vom "<<buf<<endl;
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
    hci<<"RingsBeforeAnswer:  "<<this->hklingelzahl<<" #muss mindestens 2 sein zur Uebergabe der Nummer des Anrufenden"<<endl;
		hci<<"MaxDials: "<<this->maxhdials<<endl;
		hci<<"MaxTries: "<<this->maxhdials<<endl;
    hci<<"CIDNumber: NMBR="<<endl;
    hci<<"CIDName:   NAME="<<endl;
    hci<<"SpeakerVolume:    off"<<endl;
    hci<<"GettyArgs:    \"-h %l dx_%s\""<<endl;
    hci<<"LocalIdentifier:  "<<this->LocalIdentifier<<endl;
    hci<<"LogFacility:    daemon"<<endl;
    // #ifdef obhp
    struct stat Lstat={0};
    if (!lstat((this->varsphylavz+"/etc/LiberationSans-25.pcf").c_str(),&Lstat)) {
      hci<<"TagLineFont:    etc/LiberationSans-25.pcf"<<endl;
    } else {
      // #else
      hci<<"TagLineFont:    etc/lutRS18.pcf"<<endl;
      // #endif
    }
    hci<<"TagLineFormat:    \"Von %%l|%c|Seite %%P of %%T\""<<endl;
    hci<<"AdaptiveAnswer:   yes"<<endl;
    hci<<"AnswerRotary:   \"voice fax data\""<<endl;
    hci<<"MaxRecvPages:   100"<<endl;
    hci<<"JobReqBusy:   120"<<endl;
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
    cerr<<Tx[T_Datei]<<modconfdat<<Tx[T_nichtbeschreibbar]<<endl;
    // <<rot<<" nicht offen"<<schwarz<<endl;
    exit(30);
  }
  Log(violetts+Tx[T_Ende]+"hconfigtty()"+schwarz);
} // void paramcl::hconfigtty()

// wird aufgerufen in: pruefcapi
// lieftert 0, wenn die Dienstdatei gespeichert werden konnte (erg), nicht wenn der Dienst laeuft (csfehler)
int paramcl::cservice()
{
  Log(violetts+"cservice()"+schwarz);
  int csfehler=0;
  int erg=-1;
  string cspfad;
  if (obprogda("capisuite",obverb,oblog,&cspfad)) {
    scapisuite->stop(obverb,oblog,1); 
    erg=systemrueck(/*"sudo sh -c 'systemctl stop capisuite; pkill capisuite >/dev/null 2>&1; pkill -9 capisuite >/dev/null 2>&1; "*/
        "cd /etc/init.d"
        " && [ $(find . -maxdepth 1 -name \"capisuite\" 2>/dev/null | wc -l) -ne 0 ]"
        " && { sudo mkdir -p /etc/ausrangiert && sudo mv -f /etc/init.d/capisuite /etc/ausrangiert; } || true"/*'*/,obverb,oblog);
    // entweder Type=forking oder Parameter -d weglassen; was besser ist, weiss ich nicht
    csfehler+=!scapisuite->spruef("Capisuite",0,meinname,cspfad/*+" -d"*/,"","",obverb,oblog);
    if (obverb) Log("csfehler: "+gruens+ltoan(csfehler)+schwarz);
    //    return csfehler;
  } // if (obprogda("capisuite",obverb,oblog,&cspfad)) 
  return erg;
} // int paramcl::cservice()


// wird aufgerufen in: pruefhyla
// Dienste erstellen
int paramcl::hservice_faxq_hfaxd()
{
  int hylafehler=0;
  Log(violetts+"hservice_faxq_hfaxd()"+schwarz);
	struct stat hstat={0}, fstat={0};
	if (hfaxdpfad.empty()||lstat(hfaxdpfad.c_str(),&hstat)) { obprogda("hfaxd",obverb,oblog,&hfaxdpfad); }
  hylafehler+=!shfaxd->spruef("HFaxd",0/*1*/,meinname,hfaxdpfad+" -d -i hylafax"/* -s 444*/, varsphylavz+"/etc/setup.cache", "",obverb,oblog);
  this->shfaxd->machfit(obverb,oblog);
	if (faxqpfad.empty()||lstat(faxqpfad.c_str(),&fstat)) { obprogda("faxq",obverb,oblog,&faxqpfad); }
  hylafehler+=!sfaxq->spruef("Faxq",0/*1*/,meinname,faxqpfad+" -D", varsphylavz+"/etc/setup.cache", shfaxd->sname+".service", obverb,oblog);
	setzfaxgtpfad();
	hylafehler+=!this->sfaxgetty->spruef("HylaFAX faxgetty for "+this->hmodem,0,meinname,faxgtpfad+" "+this->hmodem,"","",obverb,oblog,0);
  return hylafehler;
} // void hservice_faxq_hfaxd()

void paramcl::hylasv1()
{
  if (!this->sfaxgetty) this->sfaxgetty=new servc("hylafax-faxgetty-"+this->hmodem,"faxgetty");
} // void paramcl::hylasv1()

void paramcl::hylasv2(hyinst hyinstart)
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
} // void paramcl::hylasv2()

/*
// wird aufgerufen in: pruefhyla (1x)
int paramcl::hservice_faxgetty()
KLA
  Log(violetts+"hservice_faxgetty()"+schwarz);
  return !this->sfaxgetty->spruef(("HylaFAX faxgetty for ")+this->hmodem,0, meinname,this->faxgtpfad+" "+this->hmodem,"","","",this->obverb,this->oblog);
  // /etc/inittab werde von systemd nicht gelesen
  *//*,"cat /etc/inittab 2>/dev/null | grep -E '^[^#].*respawn.*faxgetty' >/dev/null 2>&1"*//*

KLZ // void hservice_faxgetty()
*/


// wird aufgerufen in main
int paramcl::pruefhyla()
{
	Log(violetts+Tx[T_pruefhyla]+schwarz);
	int ret=0;
	hylasv1();
	lsysen system=lsys.getsys(obverb,oblog);
	hyinst hyinstart; // hyla source, hyla Paket, hylaplus Paket
	if (system==deb /* || system==fed*/) {
		hyinstart=hysrc;
	} else {
		hyinstart=hyppk;
	} 
	hylasv2(hyinstart);
	if (obhyla) {
		long br=0; // baud rate
		string brs; // Baud-Rate-String
		int hylalaeuftnicht=0;
		static uchar hylafehlt=1;
		uchar falscheshyla=0;
		uchar modemlaeuftnicht=1;
		uchar frischkonfiguriert=0;

		if (modemgeaendert) {
			cgconf.setze("hmodem",hmodem);
			hconfigtty();
			obkschreib=1;
		} //   if (modemgeaendert)

		// Baud rate ermitteln ...
		svec ruecki;
		systemrueck(("sudo stty -F /dev/")+this->hmodem+"| head -n 1 | cut -f2 -d' '",obverb,oblog,&ruecki);
		if (ruecki.size()) {
			brs=ruecki[0];
			br=atol(brs.c_str());
		}
		// .. und anzeigen
		if (br<=0) {
			::Log(string(Tx[T_Baudratevon])+blau+"/dev/"+this->hmodem+schwarz+Tx[T_mit_af]+rot+brs+schwarz+Tx[T_zugeringVerwendeHylafaxnicht],1,1);
			//    return 1;
		} else {
			Log(string("Modem '")+blau+"/dev/"+this->hmodem+schwarz+Tx[T_mit_Baudrate]+gruen+brs+schwarz+Tx[T_wird_verwendet]);
		} //   if (br<=0) else
		// ein Fehler in der Version 4.0.7 von libtiff verhindert die Zusammenarbeit mit hylafax
		linst.pruefipr();
		/*
		const string befehl="sh -c \"NACHWEIS="+lsys.getlib64()+"/sclibtiff;! test -f /usr/include/tiff.h ||! test -f \\$NACHWEIS"
		    "&&{ "+linst.schau+" cmake||"+linst.instyp+" cmake;true"
				"&& P=tiff_copy; T=\\$P.tar.gz; Z=tiff-4.0.7"
				"; wget https://github.com/libelle17/\\$P/archive/master.tar.gz -O \\$T"
				"&& tar xpvf \\$T && mv \\${P}-master \\$Z && cd \\$Z"
				"&& rm -f CMakeCache.txt"
				"&& sed -i.bak s'/uint16 Param;/uint32 Param;/' libtiff/tif_fax3.h"
				"&& cmake -DCMAKE_INSTALL_PREFIX=/usr -DLIBTIFF_ALPHA_VERSION=1 . "
				"&& make"
				"&& sudo make install"
				"&&{ grep -q \\\"cd \\\"\\$(pwd)\\\" \\\""+unindt+"\\\""
				"|| printf \\\"cd \\\"\\$(pwd)\\\" && make uninstall; cd \\\""+instvz+"\\\"\\n\\\" >> \\\""+unindt+"\\\";} "
				"&& sudo touch \\$NACHWEIS;};true\"";
		*/
		/*
      systemrueck("sh -c 'cd \""+instvz+"\";T="+datei+".tar.gz; wget https://github.com/libelle17/"+datei+"/archive/master.tar.gz -O $T'", 
    return systemrueck("sh -c 'P="+was+";T=$P.tar."+endg+";M=$P-master;cd \""+instvz+"\" && tar xpvf $T"
                       "&& rm -rf $P 2>/dev/null||sudo rm -rf $P&& mv $M $P'",obverb,oblog);
    return systemrueck("sh -c 'cd \""+instvz+vtz+was+"\" && "+vorcfg+" && ./configure "+cfgbismake+" make && sudo make install "
							"&&{ grep -q \"cd \"$(pwd)\" \""+unindt+"\""
							"|| printf \"cd \"$(pwd)\" && make uninstall; cd \""+instvz+"\"\\n\" >> \""+unindt+"\";} "
							"'"
		*/
		// Die Datei /usr/lib64/sclibtiff wird als Nachweis verwendet, dass die Installationskorrektur durchgefuert wurde
		 struct stat lnachw={0}, ltiffh={0};
		 const string nachw=lsys.getlib64()+"/sclibtiff";
		 if (lstat("/usr/include/tiff.h",&lnachw) || lstat(nachw.c_str(),&ltiffh)) {
		  linst.doggfinst("cmake",obverb,oblog); 
			const string proj="tiff_copy";
		  holvomnetz(proj);
			kompilbase(proj,s_gz);
			const string befehl="sh -c 'cd \""+instvz+vtz+proj+"\""
				"&& rm -f CMakeCache.txt"
				"&& sed -i.bak s\"/uint16 Param;/uint32 Param;/\" libtiff/tif_fax3.h"
				"&& cmake -DCMAKE_INSTALL_PREFIX=/usr -DLIBTIFF_ALPHA_VERSION=1 . "
				"&& make"
				"&& sudo make install"
//				"&&{ grep -q \"cd \\\""+instvz+vtz+proj+"\\\"\" \""+unindt+"\""
//				"|| printf \"cd \\\""+instvz+vtz+proj+"\\\" && cat install_manifest.txt|sudo xargs rm; "
//				  "cd \\\""+instvz+"\\\"\\nsudo rm -f \\\""+nachw+"\\\"\\n\" >> \""+unindt+"\";} "
        ";true'";
			systemrueck(befehl,obverb,oblog);
			anfgggf(unindt,"cd \""+instvz+vtz+proj+"\" && cat install_manifest.txt|sudo xargs rm; cd \""+instvz+"\"");
			anfgggf(unindt,"sudo rm -f \""+nachw+"\"");
			touch(nachw,obverb,oblog);
		 }

		for(unsigned versuch=0;versuch<3;versuch++) {
			// 1) Dienst(e) hylafax, (hylafax-)hfaxd, (hylafax-)faxq identifizieren
			// pruefen, ob hylafax.service laeuft
			::Log(Tx[T_Pruefe_ob_Hylafax_gestartet],-1,oblog);
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
	  caus<<violett<<"pruefhyla 1"<<schwarz<<endl;
			if ((!sfaxq->obsvfeh(obverb-1,oblog) && !shfaxd->obsvfeh(obverb-1,oblog)) /*|| this->shylafaxd->obslaeuft(obverb-1,oblog)*/) {
				Log(Tx[T_Hylafax_laeuft]);
				hylalaeuftnicht=0;
				hylafehlt=0;
			} else if (versuch>1) {
				exit(32);
			} //     if ((this->sfaxq->obslaeuft(obverb-1,oblog) && this->shfaxd->obslaeuft(obverb-1,oblog))  else
			if (hylafehlt) {
				// falls nein, dann schauen, ob startbar
				if (sfaxq->machfit(obverb?obverb-1:0,oblog) && shfaxd->machfit(obverb?obverb-1:0,oblog) && sfaxgetty->machfit(obverb?obverb-1:0,oblog)) {
					hylafehlt=0;
					hylalaeuftnicht=0;
				}
				// <<"hylafehlt: "<<(int)hylafehlt<<endl;
			} else {
				// <<"hylafehlt nicht!"<<endl;
			} //     if (hylafehlt) else

			// <<violett <<"Versuch: "<<(int)versuch<<" hylafehlt: "<<(int)hylafehlt<<" hylalaeuftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
			if (hylafehlt) {
				// 3) ggf. neu installieren
				::Log(violetts+Tx[T_Muss_Hylafax_installieren]+schwarz,1,1);
				// a) von der source
				linst.doinst("ghostscript",obverb+1,oblog,"gs");
				linst.doinst("tiff",obverb+1,oblog,"tiff2ps");
				linst.doinst("tiff",obverb+1,oblog,"fax2ps");
				linst.doinst("sendmail",obverb+1,oblog,"sendmail");
				if (obverb) ::Log(violetts+"hyinstart: "+schwarz+ltoan(hyinstart),1,1);
				hyinstart=hysrc; // spaeter zu loeschen
				if (hyinstart==hysrc) {
					::Log(violetts+Tx[T_ueber_den_Quellcode]+schwarz,1,1);
					string was;
					if (!holvomnetz("hylafax","https://sourceforge.net/projects/","/files/latest")) {
						svec hrueck;
						if (!systemrueck("sh -c 'cd \""+instvz+"\"&& sudo tar xvf hylafax.tar.gz'",obverb,oblog,&hrueck)) {
							if (hrueck.size()) {
								was=hrueck[0].substr(0,hrueck[0].length()-1);
							}
						}
					}
					if (!was.empty()) {
						const string cfgbismake=" --nointeractive && echo $? = Ergebnis nach configure && "
							"sed -i.bak \"s.PAGESIZE='\\''North American Letter'\\''.PAGESIZE='\\''ISO A4'\\''.g;"
							"s.PATH_GETTY='\\''\\.*'\\''.PATH_GETTY='\\''"
							"$(grep LIBEXEC defs | cut -d'\\''='\\'' -f2 | sed '\\''s/^[[:space:]]*//;s/[[:space:]]*$//'\\'')/faxgetty'\\''.g\" config.cache"
							"&& echo $? = Ergebnis nach sed"
							"&& sudo";
						if (!kompilfort(was,nix,cfgbismake)) {
							const string nachcfg=
								"sh -c 'sudo systemctl daemon-reload && sudo systemctl stop hylafax 2>/dev/null"
								"&& test -f /etc/init.d/hylafax && { sudo mkdir -p /etc/ausrangiert && sudo mv -f /etc/init.d/hylafax /etc/ausrangiert; }"
								"&& sudo pkill hfaxd faxq >/dev/null 2>&1 && sudo faxsetup -nointeractive >/dev/null 2>&1 "
								"&& echo $? = Ergebnis nach faxsetup -nointeractive"
								"&& sudo pkill hfaxd faxq >/dev/null 2>&1 " // wird von faxset -nointeractive gestartet und kolligiert mit dem service
								"&& sudo systemctl daemon-reload && echo $? = Ergebnis nach sudo systemctl daemon-reload; true;'";
							systemrueck(nachcfg,obverb+1,oblog);
						  mdatei confc(instvz+vtz+was+vtz+"config.cache");
							if (confc.is_open()) {
								string zeile;
								while(getline(confc,zeile)) {
									if (zeile.find("DIR_LIBEXEC")!=string::npos) {
									  string rechts=zeile.substr(zeile.find("=")+1);
										anfzweg(rechts);
										faxgtpfad=rechts+vtz+"faxgetty";
										faxqpfad=rechts+vtz+"faxq";
										hfaxdpfad=rechts+vtz+"hfaxd";
										break;
									} // 									if (zeile.find("DIR_LIBEXEC")!=string::npos)
								} // 								while(getline(confc,zeile))
								confc.close();
							} // 							if (confc.is_open())
						} // 						if (!kompilfort(was,nix,cfgbismake))
					} // !was.empty()
					// 2>/dev/null wegen tar:Schreibfehler (=> Schreibversuch durch von head geschlossene pipe)
//					systemrueck("sh -c 'cd $(sudo tar --list -f hylafax+ 2>/dev/null | head -n 1) && "
					// hservice_faxgetty();
					// hservice_faxq_hfaxd();
				} else {
					::Log(violetts+Tx[T_ueber_das_Installationspaket]+schwarz,1,1);
					// b) mit dem Installationspaket
					if (!linst.obfehlt(hff) || !linst.obfehlt(hfcf)) {
						::Log(hfftext,-1,1);
						linst.douninst(string(hff)+" "+hfcf,obverb,oblog);
						falscheshyla=1;
					}
					// <<"hfr: "<<violett<<hfr<<schwarz<<" hfcr: "<<violett<<hfcr<<schwarz<<" obverb: "<<(int)obverb<<endl;
					hylafehlt=linst.obfehlt(hfr,obverb,oblog) || linst.obfehlt(hfcr,obverb,oblog) || 
						!obprogda("faxq",obverb,oblog) || !obprogda("hfaxd",obverb,oblog) || !obprogda("faxgetty",obverb,oblog);
					const string vstring=ltoan(versuch);
					Log(gruens+Tx[T_hylafehlt]+schwarz+ltoan(hylafehlt)+gruen+Txk[T_Versuch]+schwarz+vstring);
					// b1) falsches Hylafax loeschen
					if (hylafehlt) {
						if (falscheshyla) {
							::Log(rots+Tx[T_Muss_falsches_hylafax_loeschen]+schwarz,1,1);
							if (0) {
								systemrueck("sudo sh -c 'cd /etc/init.d"
										" && [ $(find . -maxdepth 1 -name \"*faxq*\" -or -name \"*hfaxd*\" -or -name \"hylafax*\" 2>/dev/null | wc -l) -ne 0 ]"
										" && { mkdir -p /etc/ausrangiert && mv -f *faxq* *hfaxd* hylafax* /etc/ausrangiert; } || true'",-2,oblog);
								systemrueck("sudo sh -c 'cd $(dirname $(dirname $(which systemctl)))/lib/systemd/system && "
										"rm -f faxq.service hfaxd.service faxgetty*.service hylafax*.service;'",-2,oblog);
								systemrueck("sudo sh -c 'cd /etc/systemd/system && rm -f faxq.service hfaxd.service faxgetty*.service;'",-2,oblog);
								for(int iru=0;iru<2;iru++) {
									string local;
									if (iru) local="local/"; else local.clear();
									systemrueck("sudo sh -c 'cd /usr/"+local+"bin 2>/dev/null && "
											"rm -f faxalter faxcover faxmail faxrm faxstat sendfax sendpage;'",-2,oblog);
									systemrueck("sudo sh -c 'cd /usr/"+local+"sbin 2>/dev/null && "
											"rm -f choptest cqtest dialtest edit-faxcover faxabort faxaddmodem "
											"faxadduser faxanswer faxconfig faxcron faxdeluser faxinfo faxlock faxmodem faxmsg faxq faxqclean faxquit faxsetup "
											"faxsetup.linux faxstate faxwatch probemodem rchylafax* recvstats tagtest tiffcheck tsitest typetest xferfaxstats "
											"faxsetup.bsdi faxsetup.iri faxgetty faxsend hfaxd hylafax lockname ondelay pagesend textfmt;'",-2,oblog);
									systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/fax",-2,oblog,0,1);
									systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/share/hylafax",-2,oblog,0,1);
									systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/fax",-2,oblog,0,1);
									systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/hylafax",-2,oblog,0,1);
									systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/libfax*",-2,oblog,0,1);
									systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/libhylafax*",-2,oblog,0,1);
								} //                 for(int iru=0;iru<2;iru++)
								systemrueck("sudo sh -c 'rm -rf /etc/hylafax",-2,oblog,0,1);
								// es bleiben noch /var/log/hylafax und /var/spool/fax oder /var/spool/hylafax
							} // if (0)
						} // if falscheshyla
						// b2) richtiges Hylafax installieren
						hylafehlt=linst.doinst(string(hfr)+" "+string(hfcr),obverb,oblog);
					} // if (hylafehlt)
				} // if (hyinstart==hysrc)  else

				// wenn sich faxsend findet ...
				if (obprogda("faxsend",obverb,oblog)) {
					// und ein hylafax-Verzeichnis da ist ...
					if (this->setzhylavz()) {
						this->obhyla=0;
						ret=1;
						break;
					} else {
						// falls oben hylafax neu installiert wurde und zuvor eine hylafax-Installation nach Gebrauch geloescht worden war,
						// dann die alten Eintraege (xferfaxlog.rpmsave) wieder aktivieren
						struct stat entryxfer={0}, entryxfer0={0};
						const string d0=xferfaxlog+".rpmsave";
						if (!lstat(xferfaxlog.c_str(),&entryxfer)) {
							if (entryxfer.st_size<10) { // wenn neu
								if (!lstat(d0.c_str(),&entryxfer0) && entryxfer0.st_size>10) {
									kopier(d0,xferfaxlog,obverb,oblog);
									//                systemrueck("sudo cp -a "+d0+" "+xferfaxlog,obverb,oblog);
								} else {
									if (falscheshyla)  {
										char* fspoolvz=0;
										for(unsigned iru=0;iru<sizeof this->moeglhvz/sizeof this->moeglhvz;iru++) {
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
											/* // muss noch getestet werden
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
						// bei hysrc ist das folgende wohl eigentlich nicht noetig
						// Berechtigungen korrigieren
						systemrueck("sudo chown "+huser+":uucp -R "+this->varsphylavz,obverb,oblog);
					}
				} // if (obprogda("faxsend",obverb,oblog))
				/*
					 ::Log(string(Tx[T_StarteHylafax]),1,oblog);
				//      if (hyinstart==hypak) hylalaeuftnicht=hservice_faxq_hfaxd();
				<<"hylafehlt: "<<(int)hylafehlt<<endl;
				if (0) {
				if (hylafehlt || versuch) {
				//        ::Log(string(Tx[(T_)T_Installation_von_Hylafax_nicht_feststellbar_versuche_es_zu_installieren]),-2,1);

				//        string cmd("which zypper 2>/dev/null && zypper -n in hylafax hylafax-client || "
				//        "KLA which apt-get 2>/dev/null && apt-get -y install hylafax-server hylafax-client; KLZ; systemctl daemon-reload; ");
				//        hylafehlt=systemrueck(cmd,1+obverb,oblog,0,wahr,wahr,Tx[T_hylafax_faxmodem_nicht_gefunden_Versuche_es_zu_installieren_mit]); 

				}
				// falls ja, dann starten (falls erst installiert werden muss, dann bei versuch==1
				} // if (0)
				 */
			} // if (hylafehlt)
			int fglaeuftnicht=0;
			for (uchar iru=0;iru<3;iru++) {
	  caus<<violett<<"pruefhyla 2"<<schwarz<<endl;
				if ((fglaeuftnicht=sfaxgetty->obsvfeh(obverb,oblog))) {
					// falls nein, dann schauen, ob startbar
					if (sfaxgetty->machfit(obverb,oblog)) fglaeuftnicht=0;
				}
				// <<rot<<" fglaueftnicht: "<<fglaeuftnicht<<", hmodem: "<<hmodem<<schwarz<<endl;
				string pfad;
				if (obprogda("faxstat",obverb,oblog,&pfad)) {
					modemlaeuftnicht=systemrueck("sudo "+pfad+"|grep "+this->hmodem+" 2>&1",obverb,oblog) + fglaeuftnicht;
				}
				//        if (!modemlaeuftnicht) break;
				//  <<rot<<" hyinstart: "<<(int)hyinstart<<", modemlaeuftnicht: "<<(int)modemlaeuftnicht<<schwarz<<endl;
				//  <<rot<<" hylalaueftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
				if (hyinstart==hypak || hyinstart==hysrc || hyinstart==hyppk) {
					// if (0)
					hylalaeuftnicht=hservice_faxq_hfaxd()+fglaeuftnicht;
				}
				//  <<rot<<" hylalaueftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
				if (!hylalaeuftnicht && !modemlaeuftnicht) break;
				if (iru>1) {
					systemrueck(("sudo chmod 660 ")+this->varsphylavz+"/FIFO*",obverb,oblog);
					hconfig(this,obverb,oblog);
					hconfigtty();
					frischkonfiguriert=1;
				}
				if (!iru) {
					// <<rot<<"hier faxsetup!"<<endl;
					hfaxsetup(this,obverb,oblog);
					// if (0)
					// hservice_faxgetty();
				}
			} // for (uchar iru=0;iru<3;iru++)
			// wenn !hylazukonf, dann auslesen, mit den Werten vergleichen und ggf. zu 1 setzen
			if (!hylazukonf) {
				hliesconf();
			}
			// <<rot<<"fglaeuftincht: "<<(int)fglaeuftnicht<<", modemlaeuftnicht: "<<(int)modemlaeuftnicht<<", hylalaeuftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
			// if (!hylalaeuftnicht && !modemlaeuftnicht) break;

			//          cmd=string("zypper -n in uucp"); // fuer cu
			//          systemrueck(cmd,1,1,0,wahr,wahr,"installiere cu"); 
			//          cmd=string("usermod -a -G dialout root");
			//          systemrueck(cmd,1,1,0,wahr,wahr,"berechtige mich"); 
			//          cmd=string("chmod 666 ")+this->hmodem;
			//          systemrueck(cmd,1,1,0,wahr,wahr,"berechtige mich"); 
			if (this->hylazukonf && !frischkonfiguriert) {
				//    hconfig(this,obverb,oblog); // countrycode, citycode/areacode, longdistancepraefix, internationalprefix
				if (!frischkonfiguriert) {
					// dieser Aufruf geschieht z.B. nach Parameter -hkzl 7
					hconfigtty();
				}
				if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog,1);
				if (shfaxd) shfaxd->stop(obverb,oblog,1);
				if (sfaxq) sfaxq->stop(obverb,oblog,1);
				if (shylafaxd) shylafaxd->stopdis(obverb,oblog,1);
				/*
					 if (!systemrueck("sudo systemctl stop '"+this->sfaxgetty->sname+"' '"+this->shfaxd->sname+"' '"+this->sfaxq->sname+"' 2>/dev/null",
					 obverb,oblog)) KLA
					 systemrueck("sudo systemctl stop hylafax 2>/dev/null",obverb-2,oblog);
					 systemrueck("sudo systemctl disable hylafax 2>/dev/null",obverb-2,oblog);
					 systemrueck(string("sudo pkill ")+sfaxgetty->ename+" "+shfaxd->ename+" "+sfaxq->ename+" >/dev/null 2>&1",obverb-2,oblog);
					 KLZ 
				// if (!systemrueck(string("sudo systemctl stop ")+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog)) 
				 */
				if (sfaxgetty->startundenable(obverb,oblog) &&  shfaxd->startundenable(obverb,oblog) && sfaxq->startundenable(obverb,oblog)) {
					this->hylazukonf=0;
				} // if (!systemrueck(string("sudo systemctl start ")+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog)) 
			} // if (this->hylazukonf && !frischkonfiguriert) 
			// systemrueck("grep -rl 'faxcron\\|faxqclean' /etc/cron* | /usr/bin/xargs ls -l;",obverb,oblog); 
			// // in hylafax: /etc/cron.daily/suse.de-faxcron, 
			//     break; // zu Testzwecken
			if (hylalaeuftnicht || modemlaeuftnicht) {
				// hier Fehler: nach einem Versuch darf 
				if (versuch) {
					if (this->konfobhyla) this->hylazukonf=1;
				}
				if (versuch>1) {
					::Log(string(Tx[T_hylafaxspringtnichtan]),1,1);
					this->obhyla=0;
					ret=1;
					break;
				} //         if (versuch>1) 
			} else {
				break;
			} // if (hylalaeuftnicht || modemlaeuftnicht) 
		} // for(unsigned versuch=0;versuch<2;versuch++)
		// Empfangsberechtigungen sicherstellen
		//		char *uvz[2]={(char*)"/log/",(char*)"/recvq/"};
		const string uvz[2]={"/log/","/recvq/"};
		for (unsigned i=0;i<2;i++) {
			const string dt=varsphylavz+uvz[i]+"seqf";
			struct stat dstat={0};
			if (lstat(dt.c_str(),&dstat)) {
				systemrueck("sudo touch "+dt+" && sudo chown "+huser+":uucp "+dt,obverb,oblog);
			} // 		 if (lstat(dt.c_str(),&dstat))
		} // 		for (unsigned i=0;i<2;i++)
		systemrueck("sudo sh -c \"V="+varsphylavz+";L=\\$V/log;R=\\$V/recvq;chmod 774 \\$L \\$R;chmod 660 \\$L/seqf \\$R/seqf\"",obverb,oblog);
		// Archivierung ggf. aktivieren
		if (!hylalaeuftnicht) {
			struct stat hfstat={0};
			if (!lstat("/etc/cron.hourly/hylafax",&hfstat)) {
				systemrueck("! sudo grep -q 'faxqclean *$' /etc/cron.hourly/hylafax || "
						"sudo sed -i.bak 's/faxqclean *$/faxqclean -a -A/g' /etc/cron.hourly/hylafax", obverb,oblog);
			}
		} //     if (!hylalaeuftnicht)
	} else {
		if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog);
		if (shfaxd) shfaxd->stopdis(obverb,oblog);
		if (sfaxq) sfaxq->stopdis(obverb,oblog);
		if (shylafaxd) shylafaxd->stopdis(obverb,oblog);
		ret=1;
	} // (obhyla) else
	Log(violetts+Tx[T_Ende]+" "+Tx[T_pruefhyla]+schwarz);
	return ret;
} // int paramcl::pruefhyla()


/*
   long GetFileSize(string filename)
   {
   struct stat stat_buf={0};
   int rc = stat(filename.c_str(), &stat_buf);
   return rc ? -1 : stat_buf.st_size;
   } // GetFileSize

void clear_kb(void) // statt fflush(stdin) nach getchar
{
  char junk[200];
  fgets (junk,sizeof junk,stdin);
} // clear_kb
*/

// wird aufgerufen in: paramcl::setzhylavz, pruefcvz, rueckfragen
void kuerzevtz(string *vzp)
{
  if (!vzp->empty()) {
    if (vzp->at(vzp->length()-1)==vtz)
      vzp->resize(vzp->length()-1);
  }
} // kuerzevtz

// von fkn-systems
// wird aufgerufen in: paramcl::pruefcapi
void pruefrules(int obverb, int oblog) 
{
  Log(violetts+Tx[T_pruefrules]+schwarz,obverb?obverb-1:0,oblog);
  const char *rulesd="/etc/udev/rules.d/46-FKN_isdn_capi.rules";
  struct stat entrybuf={0};
  if (lstat(rulesd, &entrybuf)) { 
    mdatei rules(rulesd,ios::out);
    if (rules.is_open()) {
      rules<<"# Symlink (capi20 -> capi) zu"<<endl;
      rules<<"# Kompatibilitaetszwecken erstellen"<<endl;
      rules<<"KERNEL==\"capi\", SYMLINK=\"capi20\""<<endl;
    }
  }
} // void pruefrules() {

// wird aufgerufen in: pruefcapi
void pruefblack(int obverb, int oblog) 
{
  Log(violetts+Tx[T_pruefblack]+schwarz,obverb?obverb-1:0,oblog);
  const string blackd="/etc/modprobe.d/50-blacklist.conf";
  const char* vgl[]={"blacklist avmfritz", "blacklist mISDNipac"};
  uchar obda[]={0}, obeinsfehlt=0;
  mdatei blacki(blackd,ios::in);
  if (blacki.is_open()) {
    string zeile;
    while(getline(blacki,zeile)) {
      for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++) {
        if (zeile.find(vgl[i])!=string::npos) obda[i]=1;
      }
    } //     while(getline(blacki,zeile))
    blacki.close();
    for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++) {
      if (!obda[i]) {obeinsfehlt=1;break;}
    } //     for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++)
    if (obeinsfehlt) {
      mdatei blacka(blackd,ios::out|ios::app);
      if (blacka.is_open()) {
        for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++) {
          if (!obda[i]) {
            Log(string(Tx[T_haengean])+blau+blackd+schwarz+Tx[T_an_mdpp]+gruen+vgl[i]+schwarz,obverb,oblog);
            blacka<<vgl[i]<<endl;
          }
        } // for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++) 
      } // if (blacka.is_open()) 
    } // obeinsfehlt
  } else {
  } // if (blacki.is_open())  else
} // void pruefblack(int obverb, int oblog) 


// wird aufgerufen in: pruefcapi
void paramcl::pruefmodcron()
{
  ::Log(violetts+Tx[T_pruefmodcron]+schwarz,obverb?obverb-1:0,oblog);
  const string mp="@reboot /sbin/modprobe ";
  const string mps[]={mp+"capi",mp+"fcpci"};
  setztmpc();
  for(uchar ru=0;ru<sizeof mps/sizeof *mps;ru++) {
    svec rueck;
    systemrueck("bash -c 'grep \""+mps[ru]+"\" -q <(sudo crontab -l 2>/dev/null)'||"
        "(sudo crontab -l 2>/dev/null >"+tmpc+";echo \""+mps[ru]+"\">>"+tmpc+";sudo crontab "+tmpc+")",obverb,oblog,&rueck);
    for(size_t znr=0;znr<rueck.size();znr++) {
      ::Log(rueck[znr],1+obverb,oblog);
			const string befehl="bash -c 'grep \""+mps[ru]+"\" -q <(sudo crontab -l 2>/dev/null)'&&"
				"(sudo crontab -l 2>/dev/null|sed '/"+saufr+"/d'>"+tmpc+";sudo crontab "+tmpc+");true";
			anfgggf(unindt,befehl);
		} //     for(size_t znr=0;znr<rueck.size();znr++)
  } //   for(uchar ru=0;ru<sizeof mps/sizeof *mps;ru++)
} // void pruefmodcron(int obverb, int oblog)

// wird aufgerufen in paramcl::paramcl
int paramcl::pruefinstv()
{
	int erg=0;
	if (instvz.empty()) {
		instvz=gethome()+vtz+meinname;
		erg=pruefverz(instvz,obverb,oblog);
	} // 	if (instvz.empty()) 
	return erg;
} // void paramcl::pruefinstv()

const string defvors="https://github.com/libelle17/";
const string defnachs="/archive/master.tar.gz";
int paramcl::holvomnetz(const string& datei,const string& vors/*=defvors*/,const string& nachs/*=defnachs*/)
{
  int erg=1;
  if (!pruefinstv()) {
    svec csrueck;
    systemrueck("find \""+instvz+"\" -mtime -1 -name "+datei+".tar.gz",obverb,oblog,&csrueck);
    if (!csrueck.size()) {
      //systemrueck("sh -c 'cd "+instvz+"; wget https://github.com/larsimmisch/capisuite/archive/master.tar.gz -O capisuite.tar.gz'",
      erg=systemrueck("sh -c 'cd \""+instvz+"\";T="+datei+".tar.gz; wget "+vors+datei+nachs+" -O $T'", obverb,oblog);
    } //     if (!csrueck.size())
  } // if (!pruefinstv())
	return erg;
} // int paramcl::holvomnetz(const string& datei,const string& vors/*=defvors*/,const string& nachs/*=defnachs*/)

int paramcl::kompilbase(const string& was, const string& endg)
{
  if (!pruefinstv()) {
    return systemrueck("sh -c 'P="+was+";T=$P.tar."+endg+";M=$P-master;cd \""+instvz+"\" && tar xpvf $T"
                       "&& rm -rf $P 2>/dev/null||sudo rm -rf $P&& mv $M $P'",obverb,oblog);
  } //   if (!pruefinstv())
  return 1;
} // int paramcl::kompilbase(string& was,string& endg)

int paramcl::kompilfort(const string& was,const string& vorcfg/*=nix*/, const string& cfgbismake/*==s_dampand*/,uchar ohneconf/*=0*/)
{
		if (!pruefinstv()) {
    return systemrueck("sh -c 'cd \""+instvz+vtz+was+"\"&&"+(vorcfg.empty()?s_true:vorcfg)+(ohneconf?nix:"&& ./configure ")+cfgbismake+
				" make && echo $? = "+Tx[T_Ergebnis_nach_make]+" && sudo make install && echo $? = "+Tx[T_Ergebnis_nach_make_install]+
//				"&&{ grep -q \"P="+was+"\" \""+unindt+"\""
//						"||printf \"H="+gethome()+";A=\\$H/"+meinname+";P="+was+";cd \\\"\\$A/\\$P\\\" 2>/dev/null"
//						"||cd \\$(find \\\"\\$H\\\" -name \\$P -printf \\\"%%T@ %%p\\\\\\\\n\\\" 2>/dev/null|sort -rn|head -n1|cut -d\\\" \\\" -f2) "
//						"&& sudo make uninstall; cd \\\"\\$H\\\"\\n\" >> \""+unindt+"\";} "
						"'",obverb,oblog);
			anfgggf(unindt,"H="+gethome()+";A=$H/"+meinname+";P=i"+was+";cd \"$A/$P\" 2>/dev/null"
			"|| cd $(find \"$H\" -name $P -printf \"%T@ %p\n\" 2>/dev/null|sort -rn|head -n1|cut -d\" \" -f2)"
			"&& sudo make uninstall; cd \"$H\"");
	  } // 		if (!pruefinstv())
		return 1;
} // int paramcl::kompilfort(const string& was,const string& vorcfg/*=nix*/, const string& cfgbismake/*==s_dampand*/,uchar ohneconf/*=0*/)

int paramcl::kompiliere(const string& was,const string& endg, const string& vorcfg/*=nix*/, const string& cfgbismake/*==s_dampand*/)
{
  if (!kompilbase(was,endg)) {
		return kompilfort(was,vorcfg,cfgbismake);
  } //    if (!kompilbase(was,endg))
  return 1;
} // int paramcl::kompiliere(string was,string endg,string nachtar, string vorcfg,string cfgbismake)

// wird aufgerufen in: pruefcapi(), anhalten()
void paramcl::capisv()
{
  if (!scapisuite) scapisuite=new servc("","capisuite");
} // void paramcl::capisv(obverb,oblog)

// in empfarch() und pruefcapi()
void paramcl::pruefsfftobmp()
{
	Log(violetts+Tx[T_pruefsfftobmp]+schwarz);
	lsysen system=lsys.getsys(obverb,oblog);
	if (system==fed) {
		// P=hylafax_copy; T=$P.tar.gz; wget https://github.com/libelle17/$P/archive/master.tar.gz -O $T && tar xpvf $T && rm -f $T && mv ${P}-master/* . && rmdir ${P}-master
		uchar obboostda=!linst.doggfinst("boost-devel",obverb,oblog);
		if (!obprogda("sfftobmp",obverb,oblog)) {
			uchar obfrei= obprogda("jpegtran",obverb,oblog) && obprogda("cjpeg",obverb,oblog) && obprogda("djpeg",obverb,oblog);
			if (!obfrei) {
				const string jpeg="jpegsrc_copy";
				holvomnetz(jpeg);
				obfrei=!kompiliere(jpeg,s_gz);
			}
			if (obfrei) {
			/*
				svec brueck;
				// rpm -q boost-devel / dpkg -s libboost-dev -> evtl. besser
				systemrueck("sudo find "+lsys.getlib64()+" /usr/lib /usr/local/lib /usr/local/lib64 /lib -name libboost_python.so -print -quit",
						obverb,oblog,&brueck);
				uchar obboostda=brueck.size();
				if (!obboostda) KLA
					obboostda = !linst.doggfinst("boost",obverb,oblog) && !linst.doggfinst("boost-devel",obverb,oblog);
				KLZ
				*/
				if (obboostda) {
					if (!systemrueck("sudo grep '/usr/local/lib' /etc/ld.so.conf||{ sudo sh -c \"echo '/usr/local/lib' >> /etc/ld.so.conf\"; sudo ldconfig;}",
								obverb,oblog)) {
						const string sff="sfftobmp_copy";
						holvomnetz(sff);
						const string vorcfg="sed -i.bak -e \"s/^[[:blank:]]*\\(char \\*shortopts.*\\)/const \\1/;"
							"s/m_vFiles.push_back( fs::path(m_argv\\[n\\].*/m_vFiles.push_back( fs::path(string(m_argv[n])\\/*, fs::native*\\/) );/\" src/cmdline.cpp"
							"&& sed -i.bak -e \"s/lboost_filesystem-mt/lboost_filesystem/g\" src/Makefile.in "
							//                      " && sed -i.bak -e 's/-${am__api_version}//g' aclocal.m4 "
							//                      " && sed -i.bak -e 's/-${am__api_version}//g' configure "
							"&& sed -i.bak -e \"s/\\(-lboost_filesystem\\)/-lboost_system \\1/g\" src/Makefile.in ";
						kompiliere(sff,s_gz,vorcfg);
					} // if (!systemrueck("sudo grep
				} // if (!linst.doggfinst("boost",obverb,oblog) && !linst.doggfinst("boost-devel",obverb,oblog)) 
			} // if (!systemrueck(befehl,obverb,oblog)) 
		} // if (!obprogda("sfftobmp",obverb,oblog)) 
	} else {
		linst.doggfinst("sfftobmp",obverb+1,oblog);
	} // if (system==fed) else
} // pruefsfftobmp

// wird aufgerufen in: untersuchespool, main
// rueckgabe: wie obcapi eingestellt sein sollte
int paramcl::pruefcapi()
{
	Log(violetts+Tx[T_pruefcapi]+schwarz+" obcapi: "+(obcapi?"1":"0"));
	static uchar capiloggekuerzt=0;
	static uchar capischonerfolgreichinstalliert=0;
	int capilaeuft=0;
	unsigned versuch=0;
	capisv();
	if (obcapi) {
		for(;versuch<2;versuch++) {
			// capi4linux muss zum Laufen der Capisuite installiert sein
			// fuer fcpci muss in driver.c eingefuegt werden:
			// #if !defined(IRQF_DISABLED)
			// #  define IRQF_DISABLED 0x00
			// #endif
			//    capilaeuft=(PIDausName("capisuite")>=0);
			capilaeuft=this->scapisuite->machfit(obverb?obverb-1:0,oblog,wahr)&&!ccapiconfdat.empty()&&!cfaxconfdat.empty();
			Log(violetts+Tx[T_capilaeuft]+schwarz+ltoan(capilaeuft)+schwarz,obverb,oblog);
			if (capilaeuft) {
				capischonerfolgreichinstalliert=1;
			} else {
				//      pid_t pid = GetPIDbyName("capisuite") ; // If -1 = not found, if -2 = proc fs access error
				uchar fcpcida=0, capida=0, capidrvda=0;
				vector<string> rueck;
				systemrueck("lsmod",obverb,oblog,&rueck);
				for(size_t i=0;i<rueck.size();i++){
					if (!fcpcida) {if (!rueck[i].find("fcpci")) {fcpcida=1;continue;}}
					if (!capidrvda) {if (!rueck[i].find("capidrv")) {capidrvda=1;continue;}}
					if (!capida) {if (!rueck[i].find("capi")) {capida=1;continue;}}
					if (fcpcida && capida && capidrvda) break;
				} // for(size_t i=0;i<rueck.size();i++)
				lsysen system=lsys.getsys(obverb,oblog);
				if (!fcpcida || !capida || !capidrvda) {
					::Log(Tx[T_Lade_Capi_Module],-1,0);
					systemrueck("sudo modprobe -rf avmfritz mISDNipac hisax_fcpcipnp hisax_isac hisax",obverb,oblog,0,1);
					for(uchar ivers=0;ivers<2;ivers++) {
						if (!fcpcida)
							if (systemrueck("sudo modprobe -v fcpci 2>/dev/null",obverb-1,oblog)) {
								if (ivers) {
									::Log(rots+Tx[T_KannFcpciNInstVerwCapiNicht]+schwarz,1,1);
									return 1;
								} // if (ivers)
								utsname unbuf;
								uname(&unbuf);
								Log(string(Tx[T_Kernelversion])+blau+unbuf.release+schwarz);
								struct stat entryfc={0};
								const string fcpciko = string("/lib/modules/")+unbuf.release+"/kernel/extras/fcpci.ko";
								if (lstat(fcpciko.c_str(), &entryfc)) {
									::Log(string(Tx[T_Datei])+blau+fcpciko+schwarz+Tx[T_nichtgefFcpciMfdKinstallierwerden],obverb,1);
									//              systemrueck("which zypper 2>/dev/null && zypper -n in kernel-source || "
									//                  "{ which apt-get 2>/dev/null && apt-get -y install linux-source; }", 1+obverb,oblog);
									linst.doinst("kernel-source",1+obverb,oblog);
									/*              
																	const string qvz="/usr/src";
																	const string versi="fcpci-3.10.0";
																	const string srcf=string("fritz-")+versi+".tar.bz2";
																	pruefverz(qvz,obverb,oblog,0);
																	struct stat entrysrc={0};
																	if (lstat((qvz+vtz+srcf).c_str(),&entrysrc)) KLA
																	systemrueck(string("cd ")+qvz+";sudo wget https://belug.de/~lutz/pub/fcpci/"+srcf+" --no-check-certificate",1+obverb,oblog);
																	KLZ
																	string srcvz=qvz+vtz+versi+"/src";
																	if (lstat(srcvz.c_str(),&entrysrc)) KLA
																	systemrueck(string("cd ")+qvz+";sudo tar xjf "+srcf,obverb,oblog);
									//                sed -e '/#include <linux\/isdn\/capilli.h>/ a\#include <linux\/utsname.h>' -e '/NOTE("(%s built on %s at %s)\\n", TARGET, __DATE__, __TIME__);/ c    NOTE("(%s built on release %s, version %s)\\n", TARGET, utsname()->release, utsname()->version);' main.c >main_neu.c
									// fuer Kernel 4.3.3-3-default und gcc muss jetzt noch 1) , __DATE__ und __TIME__ aus main.c Zeile 365 entfernt werden,
									// 2) in driver.c Zeile 373 IRQF_DISABLED durch 0x00 ersetzt werden, dann kompilier- und installierbar
									KLZ
									systemrueck("cd "+srcvz+";sudo test -f driver.c.bak || sed -i.bak '/request_irq/i#if !defined(IRQF_DISABLED)\\n"
									"# define IRQF_DISABLED 0x00\\n#endif' driver.c;"
									"sudo sed -e '/#include <linux\\/isdn\\/capilli.h>/a #include <linux\\/utsname.h>' "
									"-e '/NOTE(\"(%s built on %s at %s)\\\\n\", TARGET, __DATE__, __TIME__);/"
									"c NOTE(\"(%s built on release %s, version %s)\\\\n\", TARGET, utsname()->release, utsname()->version);' "
									"main.c >main_neu.c;mv -n main.c main.c.bak;mv -n main_neu.c main.c;"
									"sudo make clean",1+obverb,oblog);
									svec rueck;
									systemrueck("sudo rm -f /root/bin/xargs",1+obverb,oblog);
									systemrueck("cd "+srcvz+";sudo make all ",1+obverb,oblog); // || { sudo dnf clean all; sudo dnf update; sudo make all; }
									systemrueck("cd "+srcvz+";sudo make install",1+obverb,oblog);
									 */
									// in Mint musste man gcc downgraden, um fcpci installieren zu koennen
									uchar obdown=0;
									string gccpfad,gpppfad;
									struct utsname unameD={0};
									uname(&unameD);
									const string rel=unameD.release;
									size_t p1=rel.find('.');
									if (p1!=string::npos) {
										size_t p2=rel.find('.',p1+1);
										if (p2!=string::npos) {
											float vers=atof(rel.substr(0,p2).c_str());
											if (vers>0 && vers<3.14) {
												if (obprogda("gcc",obverb,oblog,&gccpfad) && obprogda("g++",obverb,oblog,&gpppfad)) {
													obdown=1;
													//                 systemrueck("sudo cp \""+gccpfad+"\" \""+gccpfad+".bak\" && " "sudo cp \""+gpppfad+"\" \""+gpppfad+".bak\"",obverb,oblog);
													if (!kopier(gccpfad,gccpfad+".bak",obverb,oblog)) kopier(gpppfad,gpppfad+".bak",obverb,oblog);
													linst.doinst("gcc-4.8",1+obverb,oblog);
													linst.doinst("g++-4.8",1+obverb,oblog);
													systemrueck("sudo ln -sf \""+gccpfad+"-4.8\" \""+gccpfad+"\" && "
															"sudo ln -sf \""+gpppfad+"-4.8\" \""+gpppfad+"\"",obverb,oblog);
												} // if (!obprogda("gcc",obverb,oblog,&gccpfad) && !obprogda("g++",obverb,oblog,&gpppfad)) 
											} // if (vers>0 && vers<3.14) 
										} // if (p2!=string::npos) 
									} // if (p1!=string::npos) 
									if (systemrueck("ls /lib/modules/$(uname -r)/build",obverb,oblog)) {
										if (system==deb) {
											systemrueck("sudo apt -y install linux-headers-$(uname -r)",obverb,oblog);
										}
									}
									systemrueck("ls -l /lib/modules/$(uname -r)/build 2>/dev/null || "
											"{ NEU=$(find /lib/modules -type l -name build -print0|/usr/bin/xargs -0 -r ls -l --time-style=full-iso|"
											"sort -nk6,7|head -n1|cut -d' ' -f9); test -h $NEU && sudo cp -a $NEU /lib/modules/$(uname -r)/build; }",obverb,oblog);
									const string proj="fcpci_copy";
									const string srcvz=instvz+vtz+proj+".tar.gz";
									holvomnetz(proj);
									const string vorcfg="sudo test -f driver.c.bak || sed -i.bak \"/request_irq/i#if \\!defined(IRQF_DISABLED)\\n"
										"# define IRQF_DISABLED 0x00\\n#endif\" driver.c;"
										"sudo sed -e '\\''/#include <linux\\/isdn\\/capilli.h>/a #include <linux\\/utsname.h>'\\'' "
										"-e '\\''/NOTE(\"(%s built on %s at %s)\\\\n\", TARGET, __DATE__, __TIME__);/"
										"c NOTE(\"(%s built on release %s, version %s)\\\\n\", TARGET, utsname()->release, utsname()->version);'\\'' "
										"main.c >main_neu.c;mv -n main.c main.c.bak;mv -n main_neu.c main.c;"
										"sudo sed -i.bak \"/install: / i .PHONY: uninstall\\nuninstall:\\n\\t\\t"
										                  "sudo modprobe -r \\$\\(CARD\\).ko\\n\\t\\tsudo rm \\$\\(TARGETDIR\\)/\\$\\(CARD\\)\\n\" Makefile;"
										"sudo make clean";
									const string cfgbismake=" 2>/dev/null; sudo ";
									kompiliere(proj,s_gz,vorcfg,cfgbismake);
									systemrueck("sudo depmod",obverb,oblog);
									if (obdown) {
										systemrueck("sudo mv -f \""+gccpfad+".bak\" \""+gccpfad+"\" && "
												"sudo mv -f \""+gpppfad+".bak\" \""+gpppfad+"\"",obverb,oblog);
									}
								} // if (lstat(fcpciko.c_str(), &entryfc)) 
							} // if (systemrueck("sudo modprobe -v fcpci",obverb-1,oblog)) 
					} // for(uchar ivers=0;ivers<2;ivers++) 

					// Fedora:
					// dnf install ncurses-devel
					// cd /usr/src/kernels/4.7.3-200.fc24.x86_64
					// make olddefconfig
					// dnf install elfutils-libelf-devel

					if (systemrueck("sudo modprobe capi 2>/dev/null",obverb,oblog)) {
						if (system==fed) {
							svec vrueck1,vrueck2;
							string v1,v2;
							systemrueck("sudo ls /boot/vmlinuz-* -r|head -n 1|cut -d- -f2,3,4,5",obverb,oblog,&vrueck1);
							if (vrueck1.size()) v1=vrueck1[0];
							systemrueck("sudo dnf -y install kernel-modules-extra && "
									"{ lsmod | grep capidrv || sudo modprobe capidrv 2>/dev/null; "
									"lsmod | grep kernelcapi || sudo modprobe kernelcapi 2>/dev/null;}",obverb,oblog);
							systemrueck("sudo ls /boot/vmlinuz-* -r|head -n 1|cut -d- -f2,3,4,5",obverb,oblog,&vrueck2);
							if (vrueck2.size()) v2=vrueck2[0];
							//            <<"vi: "<<v1<<"\n"<<"v2: "<<v2<<endl;
							if (v1!=v2) {
								autofkonfschreib();
								::Log(blaus+Tx[T_Zur_Inbetriebnahme_der_Capisuite_muss_das_Modul_capi_geladen_werten]+schwarz+v1+blau+" -> "
										+schwarz+v2+blau+").\n"+blau+Tx[T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten]+schwarz+mpfad+blau+Tx[T_aufrufen]
										+schwarz,1,1);
								exit(0);
							} // if (v1!=v2) 
							//            exit(1);
							// nach kdpeter.blogspot.de/2013/10/fedora-compile-single-module-directory.html
							// int altobverb=obverb;obverb=2;
							//         systemrueck("sudo dnf -y install @\"Development Tools\" rpmdevtools yum-utils ncurses-devel",obverb,oblog);
							linst.doinst("rpmdevtools",obverb+1,oblog,"rpmdev-setuptree");
							linst.doggfinst("numactl-devel",obverb+1,oblog);
							linst.doggfinst("pesign",obverb+1,oblog);
							systemrueck("sudo rpmdev-setuptree",obverb,oblog);
							::Log(Tx[T_Moment_muss_Kernel_herunterladen],-1,oblog);
							systemrueck("cd "+instvz+" && sudo dnf download --source kernel",obverb,oblog);
							svec rueck;
							string kstring; // kernel-4.8.4-200.fc24.src.rpm
							systemrueck("cd "+instvz+" && ls -t kernel*.rpm | head -n 1",obverb,oblog,&rueck);
							if (rueck.size()) {
								kstring=rueck[0]; // "kernel-4.8.4-200.fc24.src.rpm"
								string kernel=kstring.substr(kstring.find('-')+1);
								kernel.erase(kernel.rfind('.'));
								kernel.erase(kernel.rfind('.'));
								utsname unbuf;
								uname(&unbuf);
								const string release=unbuf.release;
								const string relev=release.substr(0,release.find(unbuf.machine)-1);
								if (kernel.find(relev)) {
									::Log(Tx[T_Der_Kernel_hat_sich_offenbar_seit_dem_Einloggen_von]+blaus+relev+schwarz+Tx[T_nach]+blau+kernel+schwarz+
											Tx[T_verjuengt_Bitte_den_Rechner_neu_starten_und_dann_mich_nochmal_aufrufen],1,1);
									exit(0);
								} // 							if (kernel.find(relev))
								systemrueck("cd "+instvz+" && sudo dnf -y builddep "+kstring,obverb,oblog);
								systemrueck("cd "+instvz+" && sudo rpm -Uvh "+kstring,obverb,oblog);
								for(unsigned iru=0;iru<2;iru++) {
									if (!systemrueck("cd "+gethome()+"/rpmbuild/SPECS && rpmbuild -bp --target=$(uname -m) kernel.spec",obverb,oblog)) {
										systemrueck("sudo dnf -y install kernel-devel",obverb,oblog);
										systemrueck("KSTRING="+kstring+" && cd $HOME/rpmbuild/BUILD/$(echo $KSTRING|cut -d. -f1,2,4)/linux-`uname -r` && "
												"make -C /lib/modules/`uname -r`/build M=`pwd`/drivers/isdn/capi modules",obverb,oblog);
										break;
									}
									if (iru) break;
									systemrueck("dnf -y install $(cd '"+gethome()+"/rpmbuild/SPECS' && rpmbuild -bp --target=$(uname -m) kernel.spec 2>&1 >/dev/null "
											"| sed '/is needed by/!d;s/^[[:blank:]]*\\(.*\\) is needed by.*/\\1/')",obverb,oblog);
									// dnf install audit-libs-devel binutils-devel bison elfutils-devel flex hmaccalc newt-devel numactl-devel 
									//     pciutils-devel "perl(ExtUtils::Embed)" perl-devel xz-devel
									// dann nochmal
								} // for(unsigned iru=0;iru<2;iru++) 
								// dann nach Anleitung: dnf -y install kernel-devel
								// cd ~/rpmbuild/BUILD/kernel<version>/linux<version>
								// make -C /lib/modules/`uname -r`/build M=`pwd`/drivers/isdn/capi modules
							} // if (rueck.size()) 
							exit(70);
							// obverb=altobverb;
						} // if (system==fed) 
					} // if (systemrueck("sudo modprobe capi",obverb,oblog))
					systemrueck("sudo modprobe capidrv 2>/dev/null",obverb,oblog);
				} // if (!fcpcida || !capida || !capidrvda) 
				pruefrules(obverb,oblog);
				pruefblack(obverb,oblog);
				capischonerfolgreichinstalliert=!linst.obfehlt("capisuite capi4linux i4l-isdnlog");
				// <<violett<<"capischonerfolgreichinstalliert: "<<schwarz<<(int)capischonerfolgreichinstalliert<<endl;
				if (capischonerfolgreichinstalliert) {
					struct stat d1={0}, d2={0};
					if (lstat("/etc/capisuite",&d1) && lstat("/usr/local/etc/capisuite",&d2))
						capischonerfolgreichinstalliert=0;
				}
				// <<rot<<"capischonerfolgreichinstalliert 0: "<<(int)capischonerfolgreichinstalliert<<schwarz<<endl;
				if (!capischonerfolgreichinstalliert) {
					::Log(string(Tx[T_Konnte])+blau+"capisuite"+schwarz+Tx[T_nichtstarten],1,oblog);
					linst.doinst("ghostscript",obverb+1,oblog,"gs");
					// if (systemrueck("which zypper",-1,-1)) KLA
					//        if (linst.checkinst(-1,-1)!=zyp) KLA
					/*
						 if (linst.pruefipr()!=zypper) {
						 ::Log(rots+Tx[T_Kann_Capisuite_nicht_installieren_verwende_Capi_nicht],1,1);
						 this->obcapi=0;
						 return 1;
						 }
					 */
					if (system!=sus)
						linst.doggfinst("capiutils",obverb+1,oblog);
					pruefsfftobmp();
					linst.doggfinst("libcapi20-2",obverb+1,oblog);
					linst.doggfinst("libcapi20-3",obverb+1,oblog);
					linst.doggfinst("python-devel",obverb+1,oblog);
					linst.doinst("libxslt-tools",obverb+1,oblog,"xsltproc");
					uchar mitcservice=0;
					// 25.11.16 nicht mehr auf Repo
					/*
						 if (system==sus) {
						 linst.doggfinst("capi4linux i4l-isdnlog",obverb+1,oblog);
						 systemrueck("zypper lr | grep 'kkeil factory development project' || "
						 "sudo zypper ar -f http://download.opensuse.org/repositories/home:/kkeil:/Factory/openSUSE_Factory/home:kkeil:Factory.repo",
						 1,1);
					// i4l-isdnlog scheint nicht wirklich noetig zu sein
					//   capischonerfolgreichinstalliert=!systemrueck("zypper -n --gpg-auto-import-keys in capisuite capi4linux i4l-isdnlog", 1+obverb,oblog); 
					// i4l-base geloescht
					capischonerfolgreichinstalliert=!linst.doinst("-f capisuite capi4linux i4l-isdnlog",obverb+1,oblog);
					} // if (lsys.getsys(obverb,oblog)==sus) 
					 */
					if (!capischonerfolgreichinstalliert) {
						holvomnetz("capisuite_copy");
						svec csrueck;
						systemrueck("find /usr/lib*/python* -type f -name Makefile -printf '%h\\n' "+string(obverb?"":"2>/dev/null")+"| sort -r",
								obverb,oblog,&csrueck);
						if (csrueck.size()) {
							struct stat c20stat={0};
							if (lstat((lsys.getlib64()+"/libcapi20.so").c_str(),&c20stat)) {
								holvomnetz("capi20_copy");
								kompiliere("capi20_copy",s_gz);
								systemrueck("sh -c 'cd "+instvz+" && L="+lsys.getlib64()+"/libcapi20.so && L3=${L}.3 && test -f $L3 && ! test -f $L && "
										"ln -s $L3 $L; test -f $L;'",obverb,oblog);
							}
							//            systemrueck("sh -c 'P=capi20_copy;T=$P.tar.bz2;M=$P-master;cd "+instvz+" && tar xpvf $T && rm -rf $P; mv $M $P && cd $P "
							//                        " && ./configure && make && sudo make install '",obverb,oblog);
							//            svec rueck;
							//            systemrueck("find /usr -name capi20.h 2>/dev/null",obverb,oblog,&rueck); 
							systemrueck("sh -c 'cd "+instvz+" && { cd capisuite 2>/dev/null && { test -f Makefile && make clean; }; }'",obverb-1,oblog);
							uchar altobverb=obverb;
							obverb++;
							svec rueck;
							string pyvz;
							systemrueck("python -c \"import os; print os.path.dirname(os.__file__)\"",obverb,oblog,&rueck);
							if (rueck.size()) {
								pyvz=*sersetze(&rueck[0],"/","\\/");
							} else {
								pyvz=ersetzAllezu(lsys.getlib64(),"/","\\/")+"\\/python2.7";
							}
							if (!kompiliere("capisuite_copy",s_gz,
										"sed -i.bak \""
										// 20.11.16 diese Zeile scheint jetzt wieder in Fedora 24 unnoetig
										//													 "s/python_configdir=.*/python_configdir="+*sersetze(&csrueck[0],"/","\\/")+"/;"
										// 20.11.16 pyexecdir und pythondir mussten in Fedora 24 so gesetzt werden
										// 23.11.16: fuer openSUE muesste wohl --datarootdir=/usr/local/lib64 versucht werden, so wie es in capisuite.conf hier auch schon steht
										"s/\\( pyexecdir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										"s/\\( pythondir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										//													 "s/\\( *pyexecdir=\\).*/\\1"+pyvz+"\\/site-packages\\/capisuite/;"
										//													 "s/\\( *pythondir=\\).*/\\1"+pyvz+"\\/site-packages\\/capisuite/;"
										"s/\\( *python_configdir=\\).*/\\1\\`\\${PYTHON} -c \\\"import distutils.sysconfig;"
										"print distutils.sysconfig.get_config_var('\\''LIBPL'\\'')\\\"\\`/;"
										"s/\\( *python_moduledir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										"s/\\( *python_moduleexecdir=\\).*/\\1\\`\\${PYTHON} -c \\\"import site;"
										"print site.getsitepackages()[0]\\\"\\`/;"
										"\" configure"
										//                           " && { test -f /usr/lib64/libcapi20.so.3 && ! test -f /usr/lib64/libcapi20.so && "
										//                           "ln -s /usr/lib64/libcapi20.so.3 /usr/lib64/libcapi20.so; true; }"
										,"HAVE_NEW_CAPI4LINUX=0 --libdir=/usr/local/lib64 --datarootdir=/usr/local/lib64 --sysconfdir=/etc --localstatedir=/var && "
										"sed -i \"s/PyErr_NewException(\\\"/PyErr_NewException((char*)\\\"/g\" src/application/capisuitemodule.cpp && ")) {
											mitcservice=1;
										}
							obverb=altobverb;
							//            string befehl="sh -c 'P=capisuite; T=$P.tar.gz; M=$P-master; cd "+instvz+""
							//                  " && tar xpvf $T && rm -rf $P ; mv $M $P && cd $P"
							//                  " && sed -i.bak \"s/python_configdir=.*/python_configdir="+*sersetze(&csrueck[0],"/","\\/")+"/\" configure"
							//                  " && { test -f /usr/lib64/libcapi20.so.3 && ! test -f /usr/lib64/libcapi20.so && "
							//                        "ln -s /usr/lib64/libcapi20.so.3 /usr/lib64/libcapi20.so; true; } "
							//                  " && ./configure HAVE_NEW_CAPI4LINUX=0 --datarootdir=/usr/local/lib --sysconfdir=/etc --localstatedir=/var"
							//                  " && sed -i \"s/PyErr_NewException(\\\"/PyErr_NewException((char*)\\\"/g\" src/application/capisuitemodule.cpp"
							////                  " && sed -i.bak 's/<capi20.h>/\\\""+*sersetze(&rueck[0],"/","\\\"\\/")+"/' src/backend/capi.h"
							////                  " && sed -i.bak 's/<capi20.h>/\\\""+*sersetze(&rueck[0],"/","\\\"\\/")+"/' src/backend/connection.h"
							//                  " && make"
							//                  " && sudo make install"
							//                  " && sudo systemctl daemon-reload; "
							//                  "'";
							//            if (!systemrueck(befehl,obverb,oblog)) {
							//              //        pruefverz("/etc/capisuite",obverb,oblog,wahr);
							//              //        systemrueck("ls /etc/capisuite/capisuite.conf || cp -a "+instvz+"/capisuite/src/capisuite.conf /etc/capisuite");
							//              //        systemrueck("ls /etc/capisuite/fax.conf || cp -a "+instvz+"/capisuite/scripts/fax.conf /etc/capisuite");
							////              pruefverz("/usr/local/var/log",obverb,oblog,wahr);
							//              //         pruefverz("/usr/local/var/log");
							//              mitcservice=1;
							//            } // if (!systemrueck(sh -c ...
						} // if (csrueck.size()) 
						// aktuelles Verzeichnis
					} // if (!capischonerfolgreichinstalliert) 
					liescapiconf();
					if (mitcservice) {
						capischonerfolgreichinstalliert=!cservice() && !ccapiconfdat.empty() && !cfaxconfdat.empty();
					}
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
					// sed -i.bak 's/python_configdir=.*/python_configdir=`find \/usr\/lib*\/python* -type f -name Makefile -printf "%h\\\\n"`/' configure
					// bei mehreren Installationen koennte hier die richtigen genommen werden:
					// sed -i.bak 's/python_configdir=.*/python_configdir=`cat $(which python-config) | head -n 1| sed "s\/#\\!\\(.*\\)\/\\1\\\/config\/"`/' configure
					// auf Fedora funzt aber nur die Original-configure
					// in ubuntu: ./configure HAVE_NEW_CAPI4LINUX 0
					//            make
					//            sudo make install
					// sudo cp -ai /home/schade/autofax/capisuite/src/capisuite.conf /etc/capisuite/
					// sudo cp -ai /home/schade/autofax/capisuite/scripts/fax.conf /etc/capisuite/
					// sudo chmod 777 /usr/local/var/log
					// ln -s /usr/lib64/libcapi20.so.3.0.6 libcapi20.so
					// in ./src/application/pythonscript.cpp Zeile 104: (Py_ssize_t*)&length statt &length
					// in /usr/include/capiutils.h eine dritte Zeile einfuegen: #define CAPI_LIBRARY_V2
					// in src/backend/connection.cpp eine Zeile 26 einfuegen: #include <cstring>
				} // if (!capischonerfolgreichinstalliert)
				servc::daemon_reload();
			} // if (capilaeuft) else
			// <<rot<<"capischonerfolgreichinstalliert: "<<schwarz<<(int)capischonerfolgreichinstalliert<<endl;
			// <<rot<<"capizukonf: "<<schwarz<<(int)capizukonf<<endl;
			// <<rot<<"versuch: "<<schwarz<<versuch<<endl;
			if (capischonerfolgreichinstalliert) {
				if (!capizukonf) {
					clieskonf();
				}
				if (/*obcapi && */(versuch>0 || this->capizukonf || rzf)) {
					this->konfcapi();
					scapisuite->restart(obverb-1,oblog);
					capizukonf=0;
				} //     if (versuch>0) KLA
				// das folgende verhindert zwar den Programmabbruch bei active (exit), das nuetzt aber nichts. In dem Fall fcpci aktualisieren! 23.5.14
				//    capilaeuft = !systemrueck("systemctl status capisuite | grep ' active (running)' >/dev/null 2>&1",0,obverb,oblog);
				//     capilaeuft  = !systemrueck("systemctl is-active capisuite",0,obverb,oblog);
	  caus<<violett<<"pruefcapi"<<schwarz<<endl;
				capilaeuft = !scapisuite->obsvfeh(obverb-1,oblog);
				if (capilaeuft) {
					break;
				} else {
					servc::daemon_reload();
					systemrueck("sudo systemctl stop isdn",obverb>0?obverb:-1,oblog,0,1);
					//      systemrueck("sudo systemctl start isdn",obverb,oblog);
					::Log(string(Tx[T_StarteCapisuite]),-1,oblog);
					scapisuite->stop(-1,oblog);
					capilaeuft=scapisuite->startundenable(-1,oblog);
					if (capilaeuft) {
						::Log(Tx[T_Capisuite_gestartet],1,oblog);
					} else {
						//       ::Log("Capisuite konnte nicht gestartet werden.",1,1);
					}
				} //       if (capilaeuft) else
			} // if (capischonerfolgreichinstalliert) 
		} //  for(unsigned versuch=0;1;versuch++) (3.)
		if (capilaeuft) {
			if (!capiloggekuerzt) {
				kuerzelogdatei("/var/log/capisuite.log",obverb); // screen
				capiloggekuerzt=1;
			}
			/*if (this->obcapi) */pruefmodcron();
		} else {
			::Log(rots+Tx[T_konntecapisuiteservice]+gruen+ltoan(versuch)+rot+Tx[T_malnichtstartenverwN]+schwarz,1,1);
			return 1;
		} //   if (capilaeuft)
	// if (obcapi)
	} else {
		if (scapisuite) scapisuite->stopdis(obverb,oblog);
		return 1;
	} // 	if (obcapi) else
	return 0;
} // pruefcapi()


// wird aufgerufen in: faxemitC
void inDbc(DB *My, const string& spooltab, const string& altspool, const string& spoolg, fsfcl *fsfp, char* telnr, int obverb, int oblog)
{
  Log(violetts+Tx[T_inDbc]+schwarz,obverb?obverb-1:0,oblog);
  string spooldir, spoolfil;
  spooldir=dir_name(spoolg);
  spoolfil=base_name(spoolg);
  uint affr=0;
  Log(string(Tx[T_SpoolDateierstellt])+rot+spoolg+schwarz+"'",obverb,oblog);
  Log(string(Tx[T_SpoolDatei])+rot+spoolfil+schwarz+"'",obverb,oblog);
  Log(string(Tx[T_SpoolPfad])+rot+spooldir+schwarz+"'",obverb,oblog);
  RS zs(My);
  struct stat entryspool={0};
  if (!lstat((spoolg.c_str()), &entryspool)) {
    for(int runde=0;runde<2;runde++) {
      if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
      } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
      RS rupd(My); 
      rupd.clear();
      vector<instyp> einf; // fuer alle Datenbankeinfuegungen
      einf.push_back(/*2*/instyp(My->DBS,"capispoolpfad",&spooldir));
      einf.push_back(/*2*/instyp(My->DBS,"capispooldatei",&spoolfil));
      einf.push_back(/*2*/instyp(My->DBS,"cdateidatum",&entryspool.st_mtime));
      einf.push_back(/*2*/instyp(My->DBS,"cdateizeit",entryspool.st_mtime));
      einf.push_back(/*2*/instyp(My->DBS,"telnr",telnr));
			if (!fsfp->idalt.empty()) {
				const string bedc="id="+fsfp->idalt;
				rupd.update(altspool,einf,ZDB,bedc);
			}
      const string bedingung="id="+fsfp->id;
      rupd.update(spooltab,einf,ZDB,bedingung);

      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      affr=My->affrows();
      if (affr>0) break;
      if (runde==1) {
        Log(string(Tx[T_Fehler_af])+drot+ltoan(rupd.fnr)+schwarz+Tx[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,oblog);
        exit(34);
      } //       if (runde==1)
    }   // for(int runde=0;runde<2;runde++)
    Log(drots+string("  affected_rows(): ")+schwarz+ltoan(affr),obverb,oblog);
  }   // if (!lstat((*spoolgp->c_str()), &entryspool)) 
} // inDbc

// wird aufgerufen in: faxealle
void faxemitC(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, paramcl *pmp, int obverb, int oblog)
  // 3. wartende Dateien bestimmen
  // 4. falls welche gefunden, capisuite pruefen
  // 5. wegfaxen
  //      und wenn erfolgreich im spool, dann jeweils in Datenbank eintragen
{
  Log(violetts+Tx[T_faxemitC]+schwarz,obverb,oblog);
  // 5. wegfaxen und wenn erfolgreich im spool, dann in Datenbank eintragen
  if (fsfp->telnr.empty()) {
    Log(string(Tx[T_DieFaxnrausTabelle])+tuerkis+spooltab+schwarz+"`, id `"+tuerkis+fsfp->id+schwarz+"` "+
        drot+fsfp->spdf+schwarz+Tx[T_istleerfaxeesdahernicht],1,1);
  } else {
    Log(string(Tx[T_DieFaxnrvon])+drot+fsfp->spdf+schwarz+Tx[T_ist]+blau+fsfp->telnr+schwarz,obverb,oblog);
    struct stat entryff={0};
    const string ff=pmp->wvz+vtz+fsfp->spdf;
    if (lstat(ff.c_str(), &entryff)) {
      Log(rots+Tx[T_faxemitCFehler]+schwarz+Tx[T_Faxdatei]+blau+ff+rot+ Tx[T_fehlt]+schwarz,1,1);
      // archiviere
    } else if (!entryff.st_size) {
      Log(rots+Tx[T_faxemitCFehler]+schwarz+Tx[T_Faxdatei]+blau+ff+rot+ Tx[T_hat0Bytes]+schwarz,1,1);
    } else {
      // capisuitefax mit Userangabe nur fuer root erlaubt
			pmp->nextnum();
			string csfpfad;
			const string cmd="capisuitefax -n "+(strcmp("root",curruser())?"":"-u"+pmp->cuser)+" -d "+fsfp->telnr+" \""+pmp->wvz+vtz+fsfp->spdf+"\" 2>&1";
			vector<string> faxerg;
			systemrueck(cmd,1,1,&faxerg,0,wahr,Tx[T_Faxbefehl],0,1);
			if (faxerg.size()) {
				const char* tz1="uccessful enqueued as ", // muss sprachlich so falsch bleiben wie im python-Script
							*tz2=" for ";
				if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1)) {
					if (char *z2=strstr(z1,tz2)) {
						string spoolg(z1+strlen(tz1),z2-z1-strlen(tz1));
						//            inDatenbankc(My, &spoolg, idsp, npdfp, spdfp, nachrnr, z2+strlen(tz2), obverb, oblog);
						if (!spoolg.find("job ")) {
							const string nr=spoolg.substr(4); 
							char buf[20]={0};
							sprintf(buf,"%.3lu",atol(nr.c_str()));
							spoolg=pmp->cfaxusersqvz+vtz+"fax-"+buf+".sff";
						} //             if (!spoolg.find("job "))
						inDbc(My, spooltab, altspool, spoolg, fsfp, z2+strlen(tz2), obverb, oblog);
					}   // if (char *z2=strstr(z1,tz2)) 
					// if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1))
				} else if (faxerg.at(0).find("can't open")==0) {
					// Fax nicht in capisuite-spool gestellt, da Datei nicht zu oeffnen, also auch wieder aus Tabelle loeschen
					Log(rots+Tx[T_Datei]+blau+pmp->wvz+vtz+fsfp->spdf+rot+"' (id: "+blau+fsfp->id+rot+
							Tx[T_nichtgefundenloeschesieausDB]+schwarz,1,1);
					RS rsloe(My,"DELETE FROM `"+spooltab+"` WHERE id = "+fsfp->id,ZDB);
				} //         if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1))
			} else {
				cerr<<rot<<"capisuitefax "<<Txk[T_nicht_gefunden]<<schwarz<<endl;
			} // 	if (obprogda(prog,obverb,oblog,&csfpfad)) else
		} //     if (lstat(ff.c_str(), &entryff))  else else
	} //   if (fsfp->telnr.empty())
} // faxemitC

// wird aufgerufen in faxemitH
void inDBh(DB *My, const string& spooltab, const string& altspool, paramcl *pmp, const string& hylaid, fsfcl *fsfp,string *tel, int obverb, int oblog)
{
  Log(violetts+Tx[T_inDBh]+schwarz,obverb?obverb-1:0,oblog);
  const string spoolfil=string("q")+hylaid;
  const string spoolg= pmp->hsendqvz+vtz+spoolfil;
  uint affr=0;
  Log(string(Tx[T_SpoolDateierstellt])+rot+spoolg+schwarz+"'",pmp->obverb,pmp->oblog);
  Log(string(Tx[T_SpoolDatei])+rot+spoolfil+schwarz+"'",pmp->obverb,pmp->oblog);
  Log(string(Tx[T_SpoolPfad])+rot+pmp->hsendqvz+schwarz+"'",pmp->obverb,pmp->oblog);
  RS zs(My);
  struct stat entryspool={0};
  string spoolid;
  if (!lstat(spoolg.c_str(), &entryspool)) {
    for(int runde=0;runde<2;runde++) {
      if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
      } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
      RS rupd(My); 
      rupd.clear();
      vector<instyp> einf; // fuer alle Datenbankeinfuegungen
      einf.push_back(/*2*/instyp(My->DBS,"hylanr",hylaid));
      einf.push_back(/*2*/instyp(My->DBS,"hdateidatum",&entryspool.st_mtime));
      einf.push_back(/*2*/instyp(My->DBS,"hdateizeit",entryspool.st_mtime));
      einf.push_back(/*2*/instyp(My->DBS,"telnr",tel));
			if (!fsfp->idalt.empty()) {
				const string bedh="id="+fsfp->idalt;
				rupd.update(altspool,einf,ZDB,bedh);
			}
      const string bedingung="id="+fsfp->id;
      rupd.update(spooltab,einf,ZDB,bedingung);
      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      affr=My->affrows();
      if (affr>0) break;
      if (runde==1) {
        Log(string(Tx[T_Fehler_af])+drot+ltoan(rupd.fnr)+schwarz+Tx[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,pmp->oblog);
        exit(36);
      } //       if (runde==1)
    }   // for(int runde=0;runde<2;runde++)
    Log(drots+"  affected_rows(): "+schwarz+ltoan(affr),pmp->obverb,pmp->oblog);
  } else {
    Log(drots+Tx[T_SpoolDatei]+spoolg+Tx[T_nicht_gefunden_kein_Datenbankeintrag],1,1);
  }   // if (!lstat((*spoolgp->c_str()), &entryspool)) 
} // inDBh

// wird aufgerufen in: faxealle
void faxemitH(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, paramcl *pmp, int obverb, int oblog)
{
  // wenn in capi maxversuch ueberschritten, dann mit hylafax wegfaxen und wenn erfolgreich im spool, dann in Datenbank aktualisieren
  // 3. wartende Dateien bestimmen
  Log(violetts+Tx[T_faxemitH]+schwarz,obverb,oblog);
  // 5. wegfaxen und wenn erfolgreich im spool, dann in Datenbank eintragen
  string tel;
  char* pt=strcasestr((char*)fsfp->spdf.c_str(),(char*)pmp->anfaxstr.c_str());
  if (!pt) if (!pmp->ancfaxstr.empty()) pt=strcasestr((char*)fsfp->spdf.c_str(),(char*)pmp->ancfaxstr.c_str());
  if (!pt) if (!pmp->anhfaxstr.empty()) pt=strcasestr((char*)fsfp->spdf.c_str(),(char*)pmp->anhfaxstr.c_str());
  if (pt) pt+=5;
  for(;pt;pt++){
    if (!*pt || *pt=='_') break; // '_' ist wegen Ausweichzielen mit Unterstrichen
    if (strchr("0123456789",*pt)) tel+=*pt;
    else if (*pt=='+') tel+=pmp->InternationalPrefix;
  }
  if (tel.empty()) {
    Log(string(Tx[T_DieFaxnrvon])+drot+fsfp->spdf+schwarz+Tx[T_istleerfaxeesdahernicht],1,1);
  } else {
    Log(string(Tx[T_DieFaxnrvon])+drot+fsfp->spdf+schwarz+Tx[T_ist]+blau+tel+schwarz,obverb,oblog);
    // 27.3.16: Uebernacht wurden die Berechtigungen so eingeschraenkt, dass Faxsenden nicht mehr ging, evtl. durch faxqclean
    systemrueck("sudo find "+pmp->varsphylavz+" -name seqf -exec chmod 660 {} \\;"" -exec chown "+pmp->huser+":uucp {} \\;",obverb,oblog);
    const char* tz1="request id is ", *tz2=" (";
    string sendfax;
//    systemrueck("sudo sh -c 'which sendfax'",obverb,1,&rueck);
    if (obprogda("sendfax",obverb,oblog,&sendfax)) {
      const string cmd=sendfax+" -n -A "+(isnumeric(pmp->maxhdials)?"-T "+pmp->maxhdials:"")+" -d "+tel+" \""+pmp->wvz+vtz+fsfp->spdf+"\" 2>&1";
      svec faxerg;
      // <<rot<<"Achtung: faxemith: "<<endl<<schwarz<<cmd<<endl;
      if (!systemrueck(cmd,1,1,&faxerg,0,wahr,Tx[T_HylafaxBefehl])) {
        for(size_t i=0;i<faxerg.size();i++) {
          Log(string(Tx[T_RueckmlgZeile])+ltoan(i)+": "+faxerg.at(i),obverb-1,oblog);
          if (char *z1=strstr((char*)faxerg.at(i).c_str(),tz1)) {
            if (char *z2=strstr(z1,tz2)) {
              string hylaid(z1+strlen(tz1),z2-z1-strlen(tz1));
              if (isnumeric(hylaid)) {
                //            inDatenbankh(My, pmp->hsendqvz, &hylaid, idsp, npdfp, spdfp, nachrnr, &tel, obverb, oblog);
                inDBh(My, spooltab, altspool, pmp, hylaid, fsfp,&tel,obverb,oblog);
              } // if (isnumeric(hylaid)) 
            }   // if (char *z2=strstr(z1,tz2)) 
            break;
          } // if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1))
        } // string cmd=sendfax+" -n -A -d "+tel+" \""+pmp->wvz+vtz+fsfp->spdf+"\" 2>&1";
      } // if (!systemrueck(cmd,1,1,&faxerg,wahr,wahr,Tx[T_HylafaxBefehl]))
    } // if (rueck.size()) 
  } // tel.empty() else
} // faxemitH


string paramcl::stdfaxnr(const string& faxnr)
{
    const string land=this->InternationalPrefix+this->countrycode;
    const string vorwahl=this->LongDistancePrefix+this->citycode;
    string trimfaxnr;
    size_t p1,p2=string::npos;
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
} // string paramcl::stdfaxnr(const string& faxnr)


// wird aufgerufen in: archiviere, empfarch
void getSender(paramcl *pmp,const string& faxnr, string *getnamep, string *bsnamep,int obverb,int oblog) 
{
  Log(violetts+"getSender("+"..,"+faxnr+")"+schwarz,obverb,oblog);
  if (!faxnr.empty()) {
    pmp->My->usedb(pmp->My->db);
    const string trimfaxnr=pmp->stdfaxnr(faxnr);
    // vor den angegebenen SQL-Befehlen nachschauen, wie die gesandten Faxe benannt wurden
    string **const locsqlp=new string*[pmp->sqlzn+1];
    string sql0="SELECT adressat, titel "
		"FROM `"+pmp->touta+"` WHERE rcfax"
		//stdfaxnr(rcfax,"+pmp->InternationalPrefix+","+pmp->LongDistancePrefix+","+pmp->countrycode+","+pmp->citycode+")"
		"='&&faxnr&&' ORDER BY submt DESC";
		locsqlp[0]=&sql0;
    for(size_t snr=0;snr<pmp->sqlzn;snr++) {
      locsqlp[snr+1]=&(pmp->sqlconf)[snr].wert;
    }
    for(size_t snr=0;snr<pmp->sqlzn;snr++) {
      Log(string(rot)+"snr: "+schwarz+ltoan(snr),obverb,oblog);
      Log(string(rot)+"sql: "+schwarz+*locsqlp[snr],obverb,oblog);
      RS rhae(pmp->My,ersetzAllezu(*locsqlp[snr],"&&faxnr&&",trimfaxnr.c_str()),ZDB); // (const char*)trimfaxnr));
      if (!rhae.obfehl) {
        Log(string("obfehl: ")+ltoan((int)rhae.obfehl),obverb,oblog);
        char ***cerg;
        while (cerg=rhae.HolZeile(),cerg?*cerg:0) {
          Log(string("cerg: ")+ltoan((bool)*cerg),obverb,oblog);
          if (*(*cerg+0)) {
            Log(string("P0: ")+blau+*(*cerg+0)+schwarz,obverb,oblog);
            if (*getnamep=="") if (*(*cerg+0)) *getnamep = *(*cerg+0);
          }
          if (*(*cerg+1)) {
            Log(string("P1: ")+blau+*(*cerg+1)+schwarz,obverb,oblog);
            if (*bsnamep=="") if (*(*cerg+1)) *bsnamep = *(*cerg+1);
          }
          break;
        } // while (cerg=rhae.HolZeile(),cerg?*cerg:0) 
      } // if (!rhae.obfehl) 
      if (!obverb) if (*getnamep!="") break;
      //    if (!obverb) if (*getnamep!="" && bsname !="") break;
    } // for(size_t snr=0;snr<pmp->sqlzn;snr++) 
    if (getnamep->empty()) {
     *getnamep=trimfaxnr;
    }
  } // if (!faxnr->empty()) 
} // void getSender(paramcl *pmp,const string& faxnr, string *getnamep, string *bsnamep,int obverb,int oblog) 

// wird aufgerufen in: main
const string& pruefspool(DB *My,const string& spooltab, const string& altspool, int obverb, int oblog, uchar direkt/*=0*/)
{
  Log(violetts+Tx[T_pruefspool]+schwarz+", direkt: "+(direkt?"1":"0"),obverb,oblog);
  if (!direkt) {
    Feld felder[] = {
      Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1),
      Feld("original","varchar","1","",Tx[T_Originalname_der_Datei],1,0,1),
      Feld("origvu","varchar","1","",Tx[T_Originalname_der_Datei_vor_Umwandlung_in_PDF],0,0,1),
      Feld("idudoc","int","10","",Tx[T_Index_auf_urspruenglichen_Dateinamen],0,0,1),
      Feld("telnr","varchar","1","",Tx[T_zu_senden_an],0,0,1),
      Feld("adressat","varchar","1","",Tx[T_zu_senden_an],0,0,1),
      Feld("prio","int","1","",Tx[T_Prioritaet_aus_Dateinamen],0,0,1),
      Feld("capidials","int","10","",Tx[T_Zahl_der_bisherigen_Versuche_in_Capisuite],0,0,1),
			Feld("capistat","int","2","",Tx[T_capistat],0,0,1),
      Feld("hyladials","int","10","",Tx[T_Zahl_der_bisherigen_Versuche_in_Hylafax],0,0,1),
      Feld("capispooldatei","varchar","1","",Tx[T_Spooldatei_in_Capisuite],0,0,1),
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
      Feld("pages","int","10","",Tx[T_Seitenzahl],0,0,1),
    }; //     Feld felder[] = 
    Feld ifelder0[] = {Feld("capispooldatei")}; Index i0("capispooldatei",ifelder0,sizeof ifelder0/sizeof* ifelder0);
    Feld ifelder1[] = {Feld("cdateidatum")};    Index i1("cdateidatum",ifelder1,sizeof ifelder1/sizeof* ifelder1);
    Feld ifelder2[] = {Feld("hdateidatum")};    Index i2("hdateidatum",ifelder2,sizeof ifelder2/sizeof* ifelder2);
    //    Feld ifelder3[] = {Feld("original")};       Index i3("original",ifelder3,sizeof ifelder3/sizeof* ifelder3);
    Index indices[]={i0,i1,i2/*,i3*/};
    // auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
    Tabelle taa(altspool,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,Tx[T_capispooldateien_der_Capisuite],
				"InnoDB","utf8","utf8_general_ci","DYNAMIC");
		if (My->prueftab(&taa, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+altspool,1,1);
      return NULL;
    } // 		if (My->prueftab(&taa, obverb))
    Tabelle tab(spooltab,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,Tx[T_capispooldateien_der_Capisuite],
				"InnoDB","utf8","utf8_general_ci","DYNAMIC");
		if (My->prueftab(&tab, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+spooltab,1,1);
      return NULL;
    } // 		if (My->prueftab(&tab, obverb))
  } // if (!direkt) 
  return spooltab;
} // const char* pruefspool(DB *My,const char* spooltab, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: main
void pruefouttab(DB *My, const string& touta, int obverb, int oblog, uchar direkt/*=0*/)
{
  Log(violetts+Tx[T_pruefouta]+schwarz,obverb,oblog);
  if (!direkt) {
    Feld felder[] = {
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
      Feld("oscht","datetime","0","0",Tx[T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax],0,0,1),
      Feld("subject","varchar","1","",Tx[T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax],0,0,1),
      Feld("id","varchar","1","",Tx[T_identisch_zu_submid_nur_MSFax],0,0,1),
      Feld("prio","int","1","",Tx[T_Prioritaet_nur_MSFax],0,0,1),
      Feld("csid","varchar","1","",Tx[T_Faxnummer_des_Adressaten_nur_MSFax],0,0,1),
      Feld("sender","varchar","1","",Tx[T_Faxnummer_des_Senders_nur_MSFax],0,0,1),
      Feld("transs","datetime","0","0",Tx[T_Beginn_der_Uebertragung_nur_MSFax],0,0,1),
    };
    Feld ifelder0[] = {Feld("submt"),Feld("Erfolg")};   Index i0("submt",ifelder0,sizeof ifelder0/sizeof* ifelder0);
    Feld ifelder1[] = {Feld("Erfolg"),Feld("submt")};   Index i1("Erfolg",ifelder1,sizeof ifelder1/sizeof* ifelder1);
    Feld ifelder2[] = {Feld("docname"),Feld("Erfolg")}; Index i2("docname",ifelder2,sizeof ifelder2/sizeof* ifelder2);
    Feld ifelder3[] = {Feld("pid"),Feld("Erfolg")};     Index i3("pid",ifelder3,sizeof ifelder3/sizeof* ifelder3);
    Feld ifelder4[] = {Feld("rcfax"),Feld("Erfolg")};   Index i4("rcfax",ifelder4,sizeof ifelder4/sizeof* ifelder4);
    Feld ifelder5[] = {Feld("submid")}; Index i5("submid",ifelder5,sizeof ifelder5/sizeof* ifelder5);
    Index indices[]={i0,i1,i2,i3,i4,i5};
    // auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
    Tabelle taba(touta,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,
        Tx[T_Archiv_fuer_die_erfolgreichen_Faxe],"InnoDB","utf8","utf8_general_ci","DYNAMIC");
    if (My->prueftab(&taba, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+touta,1,1);
    }
  } // if (!direkt)
} // int pruefouttab(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: main
void pruefudoc(DB *My, const string& tudoc, int obverb, int oblog, uchar direkt/*=0*/)
{
  Log(violetts+Tx[T_pruefudoc]+schwarz,obverb,oblog);
  if (!direkt) {
    Feld felder[] = {
      Feld("id","int","10","",Tx[T_eindeutige_Identifikation],1,1),
      Feld("udocname","varchar","1","",Tx[T_Dateiname],0,0,1),
    };
    Feld ifelder0[] = {Feld("udocname")};   Index i0("udocname",ifelder0,sizeof ifelder0/sizeof* ifelder0);
    Index indices[]={i0};
    // auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
    Tabelle taba(tudoc,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,
        Tx[T_Archiv_fuer_die_Dateinamen_vor_Aufteilung],"InnoDB","utf8","utf8_general_ci","DYNAMIC");
    if (My->prueftab(&taba, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+tudoc,1,1);
    }
  } // if (!direkt)
} // int pruefudoc(DB *My, string tudoc, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: main
void pruefinctab(DB *My, const string& tinca, int obverb, int oblog, uchar direkt/*=0*/)
{
  Log(violetts+Tx[T_pruefinca]+schwarz,obverb,oblog);
  if (!direkt){
    Feld felder[] = {
      Feld("eind","int","10","",Tx[T_eindeutige_Identifikation],1,1),
      Feld("Erfolg","int","1","",Tx[T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen],0,0,1),
      //      Feld("rcname","varchar","1","",Tx[T_Name_des_Adressaten],0,0,1),
      //      Feld("submt","datetime","0","0",Tx[T_Datum_des_Losschickens],0,0,1),
      Feld("transe","datetime","0","0",Tx[T_Ende_der_Uebertragung],0,0,1),
      //      Feld("submid","varchar","1","",Tx[T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname],0,0,1),
      //      Feld("docname","varchar","1","",Tx[T_Dateiname],0,0,1),
      Feld("fsize","int","10","",Tx[T_Dateigroesse],0,0,1),
      Feld("pages","int","10","",Tx[T_Seitenzahl],0,0,1),
      Feld("retries","int","10","",Tx[T_Zahl_der_Anwahlen],0,0,1),
      //      Feld("rcfax","varchar","1","",Tx[T_Faxnummer_des_Adressaten],0,0,1),
      Feld("titel","varchar","1","",Tx[T_Titel_des_Adressaten],0,0,1),
      //      Feld("pid","int","10","",Tx[T_PID_falls_aus_Dateinamen_ermittelt],0,0,1),
      Feld("tsid","varchar","1","",Tx[T_Kurzbezeichnung_der_eigenen_Faxstelle],0,0,1),
      Feld("devname","varchar","1","",Tx[T_Geraetename],0,0,1),
      Feld("callerid","varchar","1","",Tx[T_Bezeichnung_des_Anrufers],0,0,1),
      //      Feld("oscht","datetime","0","0",Tx[T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax],0,0,1),
      //      Feld("subject","varchar","1","",Tx[T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax],0,0,1),
      Feld("id","varchar","1","",Tx[T_identisch_zu_submid_nur_MSFax],0,0,1),
      //      Feld("prio","int","10","",Tx[T_Prioritaet_nur_MSFax],0,0,1),
      Feld("csid","varchar","1","",Tx[T_Faxnummer_des_Adressaten_nur_MSFax],0,0,1),
      //      Feld("sender","varchar","1","",Tx[T_Faxnummer_des_Senders_nur_MSFax],0,0,1),
      Feld("transs","datetime","0","0",Tx[T_Beginn_der_Uebertragung_nur_MSFax],0,0,1),
    };
    Feld ifelder0[] = {Feld("transe"),Feld("Erfolg")};   Index i0("transe",ifelder0,sizeof ifelder0/sizeof* ifelder0);
    Feld ifelder1[] = {Feld("Erfolg"),Feld("transe")};   Index i1("Erfolg",ifelder1,sizeof ifelder1/sizeof* ifelder1);
    Feld ifelder2[] = {Feld("titel"),Feld("Erfolg")}; Index i2("titel",ifelder2,sizeof ifelder2/sizeof* ifelder2);
    Feld ifelder3[] = {Feld("tsid"),Feld("Erfolg")}; Index i3("tsid",ifelder3,sizeof ifelder3/sizeof* ifelder3);
    Feld ifelder4[] = {Feld("id"),Feld("Erfolg")}; Index i4("id",ifelder4,sizeof ifelder4/sizeof* ifelder4);
    Index indices[]={i0,i1,i2,i3,i4};
    // auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
    Tabelle taba(tinca,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,
        Tx[T_Archiv_fuer_die_erfolgreichen_Faxe],"InnoDB","utf8","utf8_general_ci","DYNAMIC");
    if (My->prueftab(&taba, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+tinca,1,1);
    }
  }
} // int pruefinctab(DB *My, string tinca, int obverb, int oblog, uchar direkt=0)


// wird aufgerufen in: main
void prueffuncgettel3(DB *Myp, const string& usr, const string& host, int obverb, int oblog)
{
  Log(violetts+Tx[T_prueffuncgettel3]+schwarz,obverb,oblog);
  const string body=
   "begin \n"
   " declare pos int;\n"
   " declare ch char default '0';\n"
   " declare tel varchar(100) default '';\n"
   " set pos = instr(dname,anfaxstr);\n"
   " if pos>0 then\n"
   "  set pos=pos+length(anfaxstr);\n"
   " else\n"
   "  if ancfaxstr > '' then\n"
   "   set pos = instr(dname,ancfaxstr);\n"
   "   if pos>0 then\n"
   "    set pos=pos+length(ancfaxstr);\n"
   "   else\n"
   "    if anhfaxstr > '' then\n"
   "     set pos = instr(dname,anhfaxstr);\n"
   "     if pos>0 then\n"
   "      set pos=pos+length(anhfaxstr);\n"
   "     end if;\n"
   "    end if;\n"
   "   end if;\n"
   "  end if;\n"
   " end if;\n"
   " if pos>0 then\n"
   "  wlab: loop\n"
   "   set ch = substring(dname,pos,1);\n"
   "   if ch = '_' then leave wlab; end if;\n"
   "   if instr('0123456789',ch) then set tel=concat(tel,ch);\n"
   "   else if ch='+' then set tel=concat(tel,'00'); end if; end if;\n"
   "   set pos=pos+1;\n"
   "   if pos>length(dname) then leave wlab; end if;\n"
   "  end loop;\n"
   " end if;\n"
   " return tel;\n"
   "end";
 const string para= "(dname VARCHAR(1000), anfaxstr VARCHAR(100), ancfaxstr VARCHAR(100), anhfaxstr VARCHAR(100)) \n"
        "RETURNS VARCHAR(1000) CHARSET latin1 COLLATE latin1_german2_ci DETERMINISTIC\n";
 Myp->prueffunc("gettel3", body, para, obverb,oblog);
} // void prueffuncgettel3(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)


void pruefstdfaxnr(DB *Myp, const string& usr, const string& host, int obverb, int oblog)
{
  Log(violetts+Tx[T_pruefstdfaxnr]+schwarz,obverb,oblog);
  const string body=
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
   "end";
	const string para="(faxnr VARCHAR(200), IPf VARCHAR(10), LDPf VARCHAR(20), CoCd VARCHAR(20), CiCd VARCHAR(20)) \n"
		"RETURNS VARCHAR(200) CHARSET latin1 COLLATE latin1_german2_ci DETERMINISTIC\n";
 Myp->prueffunc("stdfaxnr", body, para, obverb,oblog);
}  // void pruefstdfaxnr(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)


// wird verwendet in setzcapistat
// Ergebnis: p1 (>=0): Datei war da und enthielt Punkt, -2: Datei war nicht da oder enthielt keinen Punkt
int fsfcl::holcapiprot(int obverb)
{
  size_t p1=sendqgespfad.rfind('.');
  if (p1!=string::npos) {
    const string suchtxt=sendqgespfad.substr(0,p1)+".txt";
    schlArr cconf; cconf.init(3,"tries","starttime","dialstring");
    struct stat cstat={0};
    if (lstat(suchtxt.c_str(),&cstat)) {
      return -2; // .txt-Datei fehlt
    } else {
      confdat cpconf(suchtxt,&cconf,obverb);
      ctries=cconf[0].wert;
      starttime=cconf[1].wert;
      dialstring=cconf[2].wert;
    } //   if (lstat(suchtxt.c_str(),&cstat)) else
    return (int)p1;
  } //   if (p1)
  return -1; // sendqgespfad enthaelt keinen ., .txt-Datei nicht zu benennen
} // int fsfcl::holcapiprot()


// ermittelt die letzten Sendedaten zu sendqgespfad mit fsf.capistat, schreibt die Zahl der Versuche in ctries zurueck und ergaenzt den 
// Anzeigezeiger ausgp
// wird aufgerufen in: loeschefax, untersuchespool, zeigweitere
void fsfcl::capiausgeb(stringstream *ausgp, string& maxcdials, uchar fuerlog, int obverb, int oblog,unsigned long faxord)
{
  Log(violetts+Tx[T_capiausgeb]+schwarz+"  capistat: "+blau+FxStatS(&capistat)+schwarz+ " maxcdials: "+blau+maxcdials+schwarz,obverb,oblog);
  if (!fuerlog) *ausgp<<blau<<endl;
  if (faxord) *ausgp<<faxord<<")";
  else *ausgp<<"  ";
  *ausgp<<"Capi: "<<schwarz;
	*ausgp<<(capistat==fehlend?hgrau:(capistat>=static_cast<FxStat>(gesandt)?blau:schwarz))<<" "<<FxStatS(&capistat)<<schwarz;
	/*
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
      //    if (cpplies(suchtxt,cconf,cs)) KLA
      // RS rmod(My,string("update spool set capidials=")+cconf[0].val+" where id = "+*(*cerg+0),ZDB);
      char buf[100]={0};
      int versuzahl=atol(ctries.c_str());
      snprintf(buf,4,"%3d",versuzahl);
      *ausgp<<", "<<blau<<buf<<"/"<<maxcdials<<schwarz<<(capistat==verarb?umgek:"")<<Tx[T_Anwahlen]<<schwarz;
      //                      if (versuzahl>12) ausg<<"zu spaet, ";
      struct tm tm={0};
			for(unsigned im=0;im<sizeof tmmoegl/sizeof *tmmoegl;im++) {
				if (strptime(starttime.c_str(), tmmoegl[im], &tm)) break;
			}
			strftime(buf, sizeof(buf), "%d.%m.%y %T", &tm);
      *ausgp<<blau<<buf<<schwarz; 
      *ausgp<<", T.: "<<blau<<setw(12)<<dialstring<<schwarz; 
      *ausgp<<Tx[T_kommaDatei]<<rot<<sendqgespfad<<schwarz;
      *ausgp<<Tx[T_bzw]<<blau<<"*.txt"<<schwarz;
    if (ctries.empty()) ctries="0";
  } // if (capistat!=fehlend) 
} // void fsfcl::capiausgeb(stringstream *ausgp, int obverb, string *ctriesp, int oblog,unsigned long faxord)


// wird aufgerufen in: setzhylastat
int paramcl::xferlog(fsfcl *fsfp,string *totpages,string *ntries,string *totdials,string *tottries,string *maxtries)
{
  // mit grep braucht er fuer eine 400 kb Datei ca. 170 clock()-Einheiten (vorne und hinten)
  // rueckwaerts braucht er fuer eine 400 kb Datei bis zum letzten Satz 93 clock()-Einheiten, bis zum ersten 220000.
  // vorwaerts braucht er fuer diese Datei ca. 9000 clock()-Einheiten
  // #define profiler
#ifdef profiler
  perfcl prf("xferlog");
#endif
  int gefunden=0;
#define mitgrep
#ifdef mitgrep
  svec grueck;
#define direkt
#ifdef direkt
  // ggf. broken pipe error; schadet aber experimentell dem Ergebnis nicht, deshalb Fehler unsichtbar
//  systemrueck(string("tac \"")+xferfaxlog+"\" 2>/dev/null | grep -m 1 \""+this->hmodem+sep+jobid+sep+"\" | cut -f 14",obverb,oblog,&grueck); 
int aktion=0; // 0=andere, 1='SEND', 2='UNSENT'
  systemrueck("tac \""+xferfaxlog+"\" 2>/dev/null | grep -m 1 \"tty[^"+sep+"]*"+sep+fsfp->hylanr+sep+"\" | cut -f1,2,14,20",obverb,oblog,&grueck); 
  if (grueck.size()) {
    gefunden=1;
    vector<string> tok;
    aufSplit(&tok,&grueck[0],sep);
		if (tok.size()<=2) fsfp->hgerg=grueck[0];
		if (tok.size()) {
			struct tm tm={0};
// a) fuehrt (zumindest hier) zu grottenfalschen Daten
//			if (strptime(tok[0].c_str(),"%m/%d/%y %H:%M",&tm)) {
// b) get_time ist (zumindest hier) noch nicht in <iomanip>
//       istringstream iss(tok[0]);
//			 iss>>get_time(&tm,"%m/%d/%y %H:%M");
//			 if (!iss.fail()) {
// c) das geht:
			int y=0,M=0,d=0,h=0,m=0;
			if (sscanf(tok[0].c_str(), "%d/%d/%d %d:%d", &M, &d, &y, &h, &m)==5) {
			  tm.tm_year=y+(y<100?100:-1900);
				tm.tm_mon=M-1;
				tm.tm_mday=d;
				tm.tm_hour=h;
				tm.tm_min=m;
				fsfp->tts=mktime(&tm);
			} // 			if (sscanf(tok[0].c_str(), "%d/%d/%d %d:%d", &M, &d, &y, &h, &m)==5)
			if (tok.size()>1) {
				fsfp->hstatus=tok[1];
				if (tok[1]=="SEND") aktion=1;
				else if (tok[1]=="UNSENT") aktion=2;
				if (tok.size()>2) {
					fsfp->hgerg=tok[2];
					anfzweg(fsfp->hgerg); // Anfuehrungszeichen entfernen
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
							}
							break;
					} //         switch (aktion)
					if (tok.size()>3) {
						vector<string> toi;
						aufSplit(&toi,&tok[3],'/');
						if (toi.size()) {
							if (totpages) *totpages=toi[0];
							if (toi.size()>1) {
								if (ntries) *ntries=toi[1];
								if (toi.size()>2) {
									fsfp->hdials=toi[2];
									if (toi.size()>3) {
										if (totdials) *totdials=toi[3];
										if (toi.size()>4) {
											fsfp->maxdials=toi[4];
											if (toi.size()>5) {
												if (tottries) *tottries=toi[5];
												if (toi.size()>6) {
													if (maxtries) *maxtries=toi[6];
												} //                       if (toi.size()>6)
											} //                       if (toi.size()>5)
										} //                     if (toi.size()>4)
									} //                   if (toi.size()>3)
								} //                 if (toi.size()>2)
							} //               if (toi.size()>1) 
						} //             if (toi.size()) 
					} //           if (tok.size()>3) 
				} //         if (tok.size()>2) 
			} //       if (tok.size()>1)
		} //     if (tok.size()) else
#else
    systemrueck("tac \""+xferfaxlog+"\" 2>/dev/null | grep -m 1 \""+this->hmodem+sep+fsfp->hylanr+sep+"\"",obverb,oblog,&grueck); // ggf. broken pipe error
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
    //            if (erg->length()>1) if ((*erg)[0]=='"' && (*erg)[erg->length()-1]=='"') *erg=erg->substr(1,erg->length()-2);
    if (obverb) KLA
      Log(blaus+"tok[13]: "+schwarz+fsfp->herg);
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
#ifdef profiler
  prf.ausgeb();
#endif
  return gefunden;
} // void xferlog(string varsphylavz, string jobid, string *erg)


// wird aufgerufen in paramcl::loeschefax, paramcl::untersuchespool, paramcl::zeigweitere
void paramcl::setzhylastat(fsfcl *fsf, string *protdaktp, uchar *hyla_uverz_nrp, uchar startvznr, int *obsfehltp/*=0*/, struct stat *est/*=0*/) 
{
  Log(violetts+Tx[T_setzhylastat]+schwarz);
  uchar obsfehlt=1;
  const string startvznrs = ltoan(startvznr);
  Log(violetts+"hylanr: "+schwarz+fsf->hylanr+violetts+" "+Tx[T_setzhylastat]+schwarz+
      " hyla_uverz_nrp: "+blau+ltoan(*hyla_uverz_nrp)+schwarz+" startvznr: "+blau+startvznrs+schwarz);
  // wenn in *hyla_uverz_nrp '1' uebergeben wird, nur in sendq suchen
  // Rueckgabe: 0 = in doneq oder archive gefunden
  struct stat entryprot={0};
  const string cmd=string("sudo find ")+this->varsphylavz+"/sendq "+(*hyla_uverz_nrp?" ":this->varsphylavz+"/doneq "+this->varsphylavz+"/archive ")
    +" -name 'q"+fsf->hylanr+"'";
  svec rueck;
  systemrueck(cmd,obverb,oblog,&rueck);
  if (rueck.size()) {
    *protdaktp=rueck[0];
    obsfehlt=lstat(protdaktp->c_str(), &entryprot);
    *hyla_uverz_nrp=(rueck.at(0).find("/doneq")==string::npos && rueck.at(0).find("/archive")==string::npos);
  }
  if (obverb) {
    Log(schwarzs+"obsfehlt: "+blau+(obsfehlt?"1":"0")+schwarz+", hyla_uverz_nr: "+blau+(*hyla_uverz_nrp?"1":"0")+schwarz);
  }
  if (obsfehltp) *obsfehltp=obsfehlt;
  if (obsfehlt) {
//    this->hconfp=0;
    // wenn also die Datenbankdatei weder im Spool noch bei den Erledigten nachweisbar ist
		if (est) memset(est,0,sizeof *est);
    this->xferlog(fsf);
    fsf->sendqgespfad.clear();
  //   if (obsfehlt)
	} else {
		if (hylconf.zahl==9) {
			hylconf.reset();
		} else { 
			hylconf.init(10,"state","totdials","status","statuscode","!pdf","tts","number","maxdials","pdf","killtime");
		}
		confdat hylc(*protdaktp,&hylconf,obverb,':');
		hgelesen= hylc.obgelesen;
    //  if (cpplies(*protdaktp,hconf,cs,0,':')) KLA
    fsf->hstate=this->hylconf[0].wert;
    fsf->hdials=this->hylconf[1].wert;
    fsf->maxdials=this->hylconf[7].wert;
    fsf->hstatus=this->hylconf[2].wert;
    if (this->hylconf[3].wert.empty()) this->hylconf[3].wert="0";
    fsf->hstatuscode=this->hylconf[3].wert;
		fsf->tts=atol(hylconf[5].wert.c_str());
		fsf->killtime=atol(hylconf[9].wert.c_str());
		fsf->number=hylconf[6].wert;
    vector<string> tok;
    const string pdf=this->hylconf[4].wert==""?this->hylconf[8].wert:this->hylconf[4].wert;
    aufiSplit(&tok,&pdf,":");
    fsf->sendqgespfad=this->varsphylavz+vtz+tok[tok.size()-1];
    if (est) lstat(fsf->sendqgespfad.c_str(),est); 
		fsf->hylastat=static_cast<FxStat>(atol(hylconf[0].wert.c_str()));
		// 8, status gescheitert, evtl. unzureichend dokumentiert, aber wahr
		/*
    if (*hyla_uverz_nrp) KLA
      fsf->hylastat=static_cast<FxStat>(atol(hylconf[0].wert.c_str()));
    // if (*hyla_uverz_nrp) 
    KLZ  else KLA 
      if (this->hylconf[0].wert=="8") KLA
        fsf->hylastat=gescheitert;
        // 7, status erfolgreich
      KLZ else if (this->hylconf[0].wert=="7") KLA 
        fsf->hylastat=gesandt;
      KLZ else KLA // wird kaum vorkommen
        fsf->hylastat=woasined;
      KLZ
    KLZ // if (*hyla_uverz_nrp) 
		*/
  } // if (obsfehlt) else
  Log(violetts+Tx[T_Ende]+" "+Tx[T_setzhylastat]+", hylastat: "+blau+FxStatS(&fsf->hylastat)+schwarz);
} // setzhylastat

// wird aufgerufen in untersuchespool und zeigweitere
void fsfcl::hylaausgeb(stringstream *ausgp, paramcl *pmp, int obsfehlt, uchar fuerlog, int obverb, uchar obzaehl, int oblog)
{
  Log(violetts+Tx[T_hylaausgeb]+schwarz+"  hylastat: "+blau+FxStatS(&hylastat)+schwarz,obverb,oblog);
  if (!fuerlog) *ausgp<<blau<<endl;
  if (obzaehl) *ausgp<<++pmp->faxord<<")";
  else *ausgp<<"  ";
  *ausgp<<"Hyla: "<<schwarz;
	*ausgp<<(hylastat==fehlend?hgrau:(hylastat>=static_cast<FxStat>(gesandt)?blau:schwarz))
	      <<" "<<FxStatS(&hylastat)<<(hgerg.empty()?"":" ("+hgerg+")")<<schwarz;
	/*
  if (obsfehlt) {
    // wenn also die Datenbankdatei weder im Spool noch bei den Erledigten nachweisbar ist
    if (hylastat==gesandt) {
      *ausgp<<blau<<" "<<Tx[T_gesandt]<<schwarz;
    } else if (hylastat==gescheitert) {
      *ausgp<<blau<<" "<<Tx[T_gescheitert]<<" ("<<hgerg<<")"<<schwarz;
    } else if (hylastat==fehlend) {
      *ausgp<<hgrau<<" "<<Tx[T_nicht_in_der_Warteschlange]<<schwarz;
    }
  } else {
  } // if (obsfehlt) else
	*/
  // wenn eine Protokolldatei auslesbar war
//  if (pmp->hconfp) {
        // modemlaeuftnicht=systemrueck(("sudo faxstat | grep ")+this->hmodem+" 2>&1",obverb,oblog) + fglaeuftnicht;
  if (pmp->hgelesen && hylastat!=fehlend) {
    *ausgp<<", ";
    char buf[100]={0};
    int hversuzahl=atol(hdials.c_str()); // totdials
    snprintf(buf,4,"%3d",hversuzahl);
    *ausgp<<blau<<buf<<"/"<<maxdials<<schwarz<<(hstate=="6"?umgek:"")<<Tx[T_Anwahlen]<<schwarz;
    // hier muss noch JobReqBusy, JobReqNoAnswer, JobReqNoCarrier, JobReqNoFCon, JobReqOther, JobReqProto dazu gerechnet werden
    // time_t spoolbeg=(time_t)atol(tts.c_str());
    strftime(buf, sizeof(buf), "%d.%m.%y %T", localtime(&tts));
    *ausgp<<blau<<buf<<schwarz; 
    //              if (hversuzahl>12) ausg<<", zu spaet";
    *ausgp<<", T.: "<<blau<<setw(12)<<number<<schwarz;
    *ausgp<<Tx[T_kommaDatei]<<rot<<sendqgespfad<<schwarz;
  }
} // void fsfcl::hylaausgeb(stringstream *ausgp, paramcl *pmp, int obsfehlt, int obverb, uchar obzaehl, int oblog)


void zeigversion(string& prog,string& mpfad)
{
  struct tm tm={0};
  char buf[100]={0};
  cout<<endl<<Tx[T_Programm]<<violett<<mpfad<<schwarz<<endl;
  cout<<"Copyright: "<<blau<<Tx[T_Freie_Software]<<schwarz<<Tx[T_Verfasser]<<blau<<"Gerald Schade"<<schwarz<<endl;
  cout<<"Version: "<<blau<<version<<schwarz<<endl;
  strptime(__TIMESTAMP__,"%c", &tm);
  //<<tm.tm_sec<<" "<<tm.tm_min<<" "<<tm.tm_hour<<" "<<tm.tm_mday<<" "<<tm.tm_mon<<" "<<tm.tm_year<<" "<<tm.tm_wday<<" "<<tm.tm_yday<<" "<<tm.tm_isdst<<endl;
  strftime(buf, sizeof(buf), "%d.%m.%Y %T", &tm);
  cout<<Tx[T_Letzte_Programmaenderung]<<blau<<buf<<schwarz<<endl;
  memset(&tm, 0, sizeof(struct tm));
  strptime((string(__DATE__)+" "+__TIME__).c_str(),"%b %d %Y %T", &tm);
  strftime(buf, sizeof(buf), "%d.%m.%Y %T", &tm);
  cout<<"              "<<Tx[T_Kompiliert]<<blau<<buf<<schwarz<<endl;
  cout<<Tx[T_Quelle]<<blau<<"https://github.com/libelle17/"<<prog<<schwarz<<endl;
	cout<<Tx[T_Installationsverzeichnis]<<blau<<instvz<<schwarz<<endl;
  cout<<Tx[T_Hilfe]<<braun<<"man "<<base_name(mpfad)<<schwarz<<Tx[T_or]<<braun<<"man -Lde "<<base_name(mpfad)<<schwarz<<"'"<<endl;
} // void zeigversion(const char* const prog)

void paramcl::zeigkonf()
{
  struct stat kstat={0};
  char buf[100]={0};
  if (!lstat(konfdatname.c_str(),&kstat)) {
    struct tm tm={0};
    memcpy(&tm, localtime(&kstat.st_mtime),sizeof(tm));
    strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", &tm);
  } //   if (!lstat(konfdatname.c_str(),&kstat))
  cout<<Tx[T_aktuelle_Einstellungen_aus]<<blau<<konfdatname<<schwarz<<"' ("<<buf<<"):"<<endl;
  for(unsigned i=0;i<cgconf.zahl;i++) {
    cout<<blau<<setw(20)<<cgconf[i].name<<schwarz<<": "<<cgconf[i].wert<<endl;
  }
} // void paramcl::zeigkonf()

int main(int argc, char** argv) 
{
	string prog;
  paramcl pm(argc,argv); // Programmparameter
  pruefplatte(); // geht ohne Logaufruf, falls nicht #define systemrueckprofiler
  pm.logvorgaben();
	// Log("main(): "+pm.cl,0,1);
  pm.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
  pm.VorgbAllg();
  pm.VorgbSpeziell(); // die Vorgaben, die in einer zusaetzlichen Datei mit einer weiteren Funktion "void paramcl::VorgbSpeziell()" ueberladbar sind
  pm.lieskonfein();

  if (!pm.getcommandline()) 
    exit(40);
  if (pm.obvi) {
		exit (systemrueck("$(which vim 2>/dev/null || which vi) "+pm.konfdatname+" >/dev/tty"));
  }
  if (pm.zeigvers) {
   zeigversion(pm.meinname,pm.mpfad);
   pm.zeigkonf();
   exit(0);
  }
  if (pm.obhyla) pm.pruefmodem();
  if (pm.obcapi) pm.pruefisdn();
  pm.rueckfragen();
	pm.pruefggfmehrfach();
	pm.setzhylavz();
  pm.verzeichnisse();
  pm.pruefsamba();
	// Rueckfragen koennen auftauchen in: rueckfragen, konfcapi (<- pruefcapi), loeschefax, pruefsamba
	// als Kompromiss blockieren wir hier
	pm.pruefggfmehrfach();

  if (pm.logdateineu) tuloeschen(logdt,"",pm.obverb,pm.oblog);
  pm.Log(string(Tx[T_zufaxenvz])+drot+pm.zufaxenvz+schwarz+"'");
  pm.Log(string(Tx[T_Logpfad])+drot+pm.loggespfad+schwarz+Tx[T_oblog]+drot+ltoan((int)pm.oblog)+schwarz+")");
  if (pm.initDB())
    return 10;
  // pruefe Tabelle <spooltab> und stelle sie ggf. her
  pruefspool(pm.My,pm.spooltab, pm.altspool, pm.obverb,pm.oblog);
  pruefouttab(pm.My,pm.touta, pm.obverb,pm.oblog);
  pruefudoc(pm.My,pm.tudoc, pm.obverb,pm.oblog);
  pruefinctab(pm.My,pm.tinca, pm.obverb,pm.oblog);
  if (pm.kez) {
    if (pm.obcapi) pm.korrigierecapi(ltage);
    if (pm.obhyla) pm.korrigierehyla(ltage);
  } else if (pm.bwv) {
    pm.bereinigewv();
  } else if (pm.anhl) {
    pm.anhalten();
  } else if (pm.lista) {
    pm.tu_lista("1");
  } else if (pm.listf) {
    pm.tu_lista("0");
  } else if (pm.listi) {
    pm.tu_listi();
  } else if (pm.listw) {
    pm.untersuchespool(0);
    pm.zeigweitere();
    Log(blaus+Tx[T_Ende]+schwarz,pm.obverb,pm.oblog);
    pm.schlussanzeige();
  } else if (!pm.suchstr.empty()) {
    pm.suchestr();
  } else {
    pruefstdfaxnr(pm.My,pm.muser,pm.host,pm.obverb,pm.oblog);
    prueffuncgettel3(pm.My,pm.muser,pm.host,pm.obverb,pm.oblog);
    //  int qerg = mysql_query(My.conn,proc.c_str());
    // 1) nicht-pdf-Dateien in pdf umwandeln, 2) pdf-Dateien wegfaxen, 3) alle in warte-Verzeichnis kopieren, 4) in Spool-Tabelle eintragen
    //  vector<string> npdf, spdf;
		if (!(pm.loef||pm.loew||pm.loea)) {
			pm.DateienHerricht();  
		}
    if (pm.obfcard) pm.obcapi=!pm.pruefcapi();
    if (pm.obmodem) pm.obhyla=!pm.pruefhyla();
    Log(Tx[T_Verwende]+blaus+(pm.obcapi?"Capisuite":"")+schwarz+(pm.obcapi&&pm.obhyla?", ":"")+blau+(pm.obhyla?"Hylafax":"")+schwarz+
        (!pm.obcapi&&!pm.obhyla?(blaus+Tx[T_kein_Faxprogramm_verfuegbar]+schwarz):"")+
				Tx[T_Aufrufintervall]+blau+(pm.cronminut=="0"?Tx[T_kein_Aufruf]+schwarzs:pm.cronminut+schwarz+(pm.cronminut=="1"?Tx[T_Minute]:Tx[T_Minuten])),
				1,pm.oblog);
    if (pm.loef || pm.loew || pm.loea) {
      if (pm.loef) pm.loeschefax();
      if (pm.loew) pm.loeschewaise();
      if (pm.loea) pm.loescheallewartende();
    } else {

      // hier stehen obcapi und obhyla fest
      pm.faxealle();
      // Dateien in Spool-Tabelle nach inzwischen verarbeiteten durchsuchen, Datenbank- und Dateieintraege korrigieren 
      pm.untersuchespool();
      pm.zeigweitere();
      pm.empfarch();
      pm.Log(blaus+Tx[T_Ende]+schwarz);
      pm.schlussanzeige();
    } // if (pm.loef || pm.loew || pm.loea) else
    pm.pruefcron();
  } // if (pm.kez) else else else
  pm.autofkonfschreib();
  return 0;
} // int main(int argc, char** argv) 

// Log-Datei ueberpruefen
// Hylafax mit Fritzcard

// ausgabestring fuer hylafax befuellen
// fuer update eine Unterfunktion mit Felderweiterung schreiben
// im Fall erfolgreich erledigter Hylafaxe DAtenbankeintrag fuer capi korrigieren, im Fall gescheiterer klaeren, wie erneut reingestellt
// update auch fuer datenbankeinterne Felder ermoeglichen
// bei hyla die dateigroesse der pdf-Datei nehmen

// vor Samba-Ueberpruefung rueckfragen
// Firewallkorrektur in man einbauen
// Urspruenglichen Dateinamen speichern
// evtl. manuell umbenannte Dateien in der Datenbank registrieren
// evtl. die Ausgaben verschiedener capisuitefax -Parameter beruecksichtigen

// Tesseract:
//  zypper in  tesseract-ocr tesseract-ocr-traineddata-english tesseract-ocr-traineddata-german tesseract-ocr-traineddata-orientation_and_script_detection
// (ldconfig /usr/lib64)
// git clone https://github.com/jbarlow83/OCRmyPDF.git
// cd OCRmyPDF
// pip3 install ocrmypdf

