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
const char sep = 9; // geht auch: "[[:blank:]]"

const string s_true="true";
const string s_dampand=" && ";
const string s_gz="gz";

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
  T_pruefspool,
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
  T_Passwort_fuer_samba_fuer_Benutzer,
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
  // T_pruefspool
  {"pruefspool()","checkspool()"},
  // T_pruefouta
  {"pruefouta()","checkouta()"},
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
  // T_Passwort_fuer_samba_fuer_Benutzer
  {"Passwort fuer samba fuer Benutzer ","Password for samba for user "},
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
            "'sudo dnf -y install kernel-modules-extra' aufgerufen werden, des den Linux-Kernel aktualisiert hat (",
   "In order to use the capisuite, the module capi has to be loaded. In order to generate this, the command "
   "'sudo dnf -y install kernel-modules-extra' hat to be called, which updated the linux kernel ("},
  // T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten
  {"). Bitte zu dessen Verwendung den Rechner neu starten und dann nochmal ",
   "). Please reboot and afterwords call "},
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
  {"Optionen, die in der Konfigurationsdatei gespeichert werden koennen (vorausgehendes: '1'=doch nicht speichern, 'no'=Gegenteil, z.B. '-noocra','-1noocri'):",
   "Options which can be saved in the configuration file: ('1'=don't save, 'no'=contrary, e.g. '-noocra','-1noocri'):"},
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
  {"",""}
}; // char const *Txautofaxcl::TextC[T_MAX+1][Smax]=


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
} // int zielmustercl::setzemuster(const string& vmuster)

int zielmustercl::obmusterleer() {
 return muster.empty();
} // int zielmustercl::obmusterleer() 

const string& zielmustercl::holmuster() {
 return muster;
} // const string& zielmustercl::holmuster()

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
    } // switch (*i)
  } // if (i)
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
      exit(10);
    }
  } // for(int runde=0;runde<2;runde++) 
  if (!rins.fnr) { 
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
    }
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
    pmp->hylasv1(obverb,oblog);
    pmp->hylasv2(hysrc,obverb,oblog);
    for(uchar iru=0;iru<vmax;iru++) {
      if (iru) {
        if (pmp->sfaxgetty) pmp->sfaxgetty->restart(obverb+1,oblog);
        if (pmp->shfaxd) pmp->shfaxd->restart(obverb+1,oblog);
        if (pmp->sfaxq) pmp->sfaxq->restart(obverb+1,oblog);
        //      systemrueck(string("sudo systemctl restart '")+pmp->sfaxgetty->sname+"' '"+pmp->shfaxd->sname+"' '"+pmp->sfaxq->sname+"'",obverb-1,oblog);
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
      //      systemrueck("sudo su -c \"faxrm "+hylanr+"\" $(tac \""+pmp->xferfaxlog+"\"|grep -m 1 \"SUBMIT"+sep+sep+sep+hylanr+"\"|cut -f18|sed -e 's/^\"//;s/\"$//') 2>&1",2,oblog,&rmerg);
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
} // int fsfcl::loeschehyla(int obverb, int oblog)

paramcl::paramcl(int argc, char** argv)
{
  for(int i=1;i<argc;i++)
    if (argv[i][0])
      argcmv.push_back(argcl(i,argv)); 
  mpfad=meinpfad();
  meinname=base_name(mpfad); // argv[0];
  vaufr=mpfad+" -norf"; // /usr/bin/autofax -norf
  saufr=base_name(vaufr); // autofax -norf
  tstart=clock();
  cklingelzahl="1";
  hklingelzahl="2"; // muss mindestens 2 sein, um die Nr. des anrufenden zu uebertragen
//  konfdatname.clear();
} // paramcl::paramcl()

void paramcl::pruefggfmehrfach()
{
  if (!hilfe && !obvi && !zeigvers && !listi && !listf && !lista) {
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
  Log(violetts+Tx[T_WVZinDatenbank]+schwarz,obverb,oblog);
  RS rins(My); 
  RS zs(My);
  string spoolid;
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
      rins.insert(altspool,einf, 1,0,ZDB?ZDB:!runde,&spoolid);
      rins.insert(spooltab,einf, 1,0,ZDB?ZDB:!runde,&spoolid);
      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      if (spoolid!="null") break;
      if (runde==1) {
        Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
        exit(12);
      }
    }   // for(int runde=0;runde<2;runde++)
    Log(drots+string("  Spool-ID: ")+schwarz+spoolid,obverb,oblog);
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
    RS tea(My,string("UPDATE `")+altspool+"` "
        "SET telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"') "
        "WHERE ISNULL(telnr) OR telnr=''",ZDB);
    RS tel(My,string("UPDATE `")+spooltab+"` "
        "SET telnr=gettel3("+(tr?"origvu":"original")+",'"+anfaxstr+"','"+ancfaxstr+"','"+anhfaxstr+"') "
        "WHERE ISNULL(telnr) OR telnr=''",ZDB);
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
  Log(violetts+"getcommandl0()"+schwarz,obverb,oblog);
  // Reihenfolge muss koordiniert werden mit lieskonfein und rueckfragen
  cgconf.init(40, "language","host","muser","mpwd","datenbank","obcapi","obhyla","hylazuerst","maxcapiv","maxhylav","cuser",
    "countrycode","citycode","msn","LongDistancePrefix","InternationalPrefix","LocalIdentifier",
    "cFaxUeberschrift","cklingelzahl","hmodem","hklingelzahl",
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
        string f0=schwarzs+"Modem "+blau+tty+schwarz+Tx[T_gibts];
        string f1=f0+Tx[T_nicht];
        errv.push_back(errmsgcl(0,f0));
        errv.push_back(errmsgcl(1,f1));
        if (!systemrueck("sudo stty -F /dev/"+tty,obverb,oblog,&rue2,2,wahr,"",&errv)) {
          obmodem=1;
          modems<<tty;
          Log(string("Modem: ")+blau+tty+schwarz+Tx[T_gefunden],obverb,oblog);
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
        Log(string("modems[0]: ")+rot+modems[0]+schwarz,obverb,oblog);
        Log(string("hmodem:    ")+rot+hmodem+schwarz,obverb,oblog);
      }
      hmodem=modems[0];/*modemsumgesteckt=1;*/ 
      modemgeaendert=1;
    } //   if (modems.size()) if (!modems[0].empty()) if (modems[0]!=hmodem) 
  } // if (hmodem.empty()) 
  obmdgeprueft=1;
  if (!obmodem) {
    obhyla=0;
    Log(rots+Tx[T_Kein_Modem_gefunden]+schwarz,obverb,oblog);
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
  // wvdialconf oder schneller: setserial -a /dev/tty*, mit baud_base: <!=0>  als Kriterium
} // void paramcl::pruefmodem()

void paramcl::pruefisdn()
{
  Log(violetts+Tx[T_pruefisdn]+schwarz,obverb,oblog);
  svec rueck;
  cmd="{ lspci 2>/dev/null || sudo lspci 2>/dev/null;}|grep -i 'isdn'";
  systemrueck(cmd, obverb,oblog,&rueck);
  // <<"pruefmodem 1 vor  obcapi: "<<(int)obcapi<<endl;
  if (rueck.size()) {
    Log(rots+Tx[T_ISDN_Karte_gefunden]+schwarz+rueck[0]+rot+Tx[T_Setze]+Tx[T_mitCapi]+rot+Tx[T_aauf]+schwarz+"1.",obverb,oblog);
    obfcard=1;
  } else {
    Log(rots+Tx[T_Keine_ISDN_Karte_gefunden]+schwarz+Tx[T_mitCapi]+rot+Tx[T_aauf]+schwarz+"0.",obverb,oblog);
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
  string bemst; 
  svec bemv;
  for(int akts=0;akts<Smax;akts++) {
    bemst=Tx[T_ob_ein_Modem_drinstak][akts];
    bemv<<bemst;
  } //         for(int akts=0;akts<Smax;akts++)
  cgconf.setzbemv("obfcard",&Tx,T_ob_eine_Fritzcard_drinstak);
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
    const string hylacdat="/etc/init.d/hylafax";
    struct stat hstat;
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
  } // which vik 2>/dev/null || which vi
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
            struct stat statdat;
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
  Log(violetts+Tx[T_VorgbAllg]+schwarz,obverb,oblog);
  liescapiconf();
  hylazuerst=0;
  // hmodemstr="ACM";
  maxcapiv="3";
  maxhylav="3";
  gleichziel=1;
  obocri=1;
  obocra=1;
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
  Log(violetts+Tx[T_lieskonfein]+schwarz,obverb,oblog);
  if (konfdatname.empty()) konfdatname = aktprogverz()+".conf";
  /*
     static cppSchluess gconf[]={{"langu"},{"obcapi"},{"obhyla"},{"hylazuerst"},{"maxcapiv"},{"maxhylav"},{"cuser"},
     {"countrycode"},{"citycode"},{"msn"},{"LongDistancePrefix"},{"InternationalPrefix"},{"LocalIdentifier"},
     {"cFaxUeberschrift"},{"cklingelzahl"},{"hmodem"},{"hklingelzahl"},
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
} // void paramcl::lieskonfein()

// wird aufgerufen in: main
int paramcl::getcommandline()
{
  Log(violetts+"getcommandline()"+schwarz,obverb,oblog);
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
  opts.push_back(/*4*/optioncl("gz","gleichziel", &Tx, T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,&gleichziel,1,
        &cgconf,"gleichziel",&obkschreib));
  opts.push_back(/*4*/optioncl("ocri","ocri", &Tx, T_Text_aus_empfangenen_Faxen_wird_ermittelt,&obocri,1, &cgconf,"ocri",&obkschreib));
  //  opts.push_back(/*4*/optioncl("noocri","noocri", &Tx, T_Text_aus_empfangenen_Faxen_wird_nicht_ermittelt,&obocri,0, &cgconf,"ocri",&obkschreib));
  opts.push_back(/*4*/optioncl("ocra","ocra", &Tx, T_Text_aus_gesandten_Bildern_wird_ermittelt,&obocra,1, &cgconf,"ocra",&obkschreib));
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
      Log(rots+"Parameter: "+gruen+argcmv[i].argcs+rot+Tx[T_nicht_erkannt]+schwarz,1,1);
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

  Log(string(Tx[T_Fertig_mit_Parsen_der_Befehlszeile])+(obkschreib?Tx[T_ja]:Tx[T_nein]),obverb,oblog);
  // Ausgabe der Hilfe
  if (hilfe) {
    cout<<blau<<Tx[T_Gebrauch]<<drot<<meinname<<" [-<opt>|--<longopt> [<content>]] ..."<<schwarz<<endl; 
    cout<<blau<<Tx[T_Faxt_Dateien_aus_Verzeichnis_pfad_die]<<anfaxstr<<
      Tx[T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie]
      <<drot<<dbq<<blau<<Tx[T_Tabellen]<<drot<<touta<<blau<<"`,`"<<drot<<spooltab<<blau<<Tx[T_aein]<<endl;
    cout<<blau<<Tx[T_Optionen_die_nicht_gespeichert_werden]<<schwarz<<endl;
    for(size_t j=0;j<opts.size();j++) {
      if (!opts[j].obschreibp)
        opts[j].hilfezeile(Tx.lgn);
    }
    cout<<blau<<Tx[T_Optionen_die_in_der_Konfigurationsdatei_gespeichert_werden]<<schwarz<<endl;
    for(size_t j=0;j<opts.size();j++) {
      if (opts[j].obschreibp)
        opts[j].hilfezeile(Tx.lgn);
    }
    return 0;
  } // if (hilfe)
  return 1;
} // int paramcl::getcommandline(int argc, char** argv)

// wird aufgerufen in: main
void paramcl::rueckfragen()
{
  Log(violetts+Tx[T_rueckfragen]+schwarz,obverb,oblog);
  const string nix;
  if (rzf) {
    int lfd=-1;
    char *locale = setlocale(LC_CTYPE,"");
    if (langu.empty()) if (locale) if (strchr("defi",locale[0])) langu=locale[0];
    vector<string> sprachen={"e","d"/*,"f","i"*/};
    if (cgconf[++lfd].wert.empty() || rzf) {
      langu=Tippstrings("Language/Sprache/Lingue/Lingua",&sprachen, &langu);
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
      string Frage=string(Tx[T_Passwort_fuer_MySQL_MariaDB])+Tx[T_fuer_Benutzer]+drot+muser+schwarz+"'";
      do {
        mpwd=Tippstring(Frage.c_str(),&mpwd);
      }
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
      if (benutzer.size()>1) for(size_t i=0;i<benutzer.size();i++) if (benutzer[i]=="syslog") {benutzer.erase(benutzer.begin()+i);break;}
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
        msn=Tippstring(Tx[T_Eigene_MSN_Faxnummer_ohne_Vorwahl],&msn);
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
    } else {
      lfd+=2;
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
      obocra=Tippob(Tx[T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden],obocra?Tx[T_j_af]:"j");
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
    Log(blaus+"obfcard: "+schwarz+ltoan(obfcard)+blau+", obmodem: "+schwarz+obmodems,obverb,oblog);
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
  Log(violetts+Tx[T_autokonfschreib]+schwarz+", "+Tx[T_zu_schreiben]+((rzf||obkschreib)?Tx[T_ja]:Tx[T_nein]),obverb,oblog);
  /*
     capizukonf und hylazukonf hier immer 0
     char buf[200];
     sprintf(buf,"rzf: %d, capizukonf: %d, hylazukonf: %d, obkschreib: %d",(int)rzf, (int)capizukonf, (int)hylazukonf, (int)obkschreib);
     Log(blaus+buf+schwarz,obverb,oblog);
   */
  if (rzf||obkschreib) {
    Log(gruens+Tx[T_schreibe_Konfiguration]+schwarz,obverb,oblog);
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
    }
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
  Log(violetts+Tx[T_clieskonf]+schwarz+", cfaxcp->name: "+violett+cfaxcp->name+schwarz,obverb,oblog);
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
      }
    }
    if (richtige!=4) {
      capizukonf=1;
    }
  }
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
  Log(violetts+Tx[T_konfcapi]+schwarz+", ccapiconfdat: "+violett+ccapiconfdat+schwarz,obverb,oblog);
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
     const char* suchstr="connect_faxG3(";
  // <<rot<<"Lese: "<<cconf[0].wert<<schwarz<<endl;
  while(getline(f,zeile)) KLA
  size_t nk=zeile.find(suchstr);
  if (nk!=string::npos) KLA
  nk+=strlen(suchstr);
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
  nk=zeile.find(suchstr);
  if (nk!=string::npos) KLA
  fneu<<neuzeile<<endl;
  KLZ else KLA
  fneu<<zeile<<endl;
  KLZ 

  KLZ // while(getline(falt,zeile)) 
  struct stat entryorig;
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
  KLZ // if ((nkz=strstr(zeile,suchstr))) 
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
    //    Log(string("Capisuite ist offenbar noch nicht konfiguriert(")+blau+"fax_stationID"+schwarz+" enthaelt '000 0000').\n"
    //        "Die Einstellung koennen spaeter in "+blau+cfaxconfdat+schwarz+" geaendert werden.",1,0);
    Log(string(Tx[T_Capisuite_ist_offenbar_noch_nicht_richtig_konfiguriert])+blau+"'fax_stationID'"+schwarz+Tx[T_ist_Apostroph]+blau+
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
    capiconf[2].wert="15";
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
        Log(string("snr: ")+blau+ltoan(snr)+schwarz+" "+capiconf[snr].wert+", "+capiconf[snr].wert,obverb,oblog);
      }
    } // if (obverb>0)
  } // if (rzf || (capicffehlt && !nrzf))
  string suchcuser=string("[")+cuser+"]";
  // es gibt zwei moegliche Gruende zum Neuschreiben der Datei: 1) Parameter diffierieren, 2) noch kein User angelegt
  uchar cuserda=0, paramdiff=0, neuschreiben=0;
  string zeile, neudatei;
  uchar geschrieben;
  size_t kommpos;
  // iru=0 => pruefen, ob Datei geaendert werden muss; iru=1 => aendern
  for(uchar iru=0;iru<2;iru++) {
    mdatei *fneu=0;
    mdatei f(cfaxconfdat,ios::in); // /etc/capisuite/fax.conf
    if (f.is_open()) {
      if (iru) {
        neudatei=cfaxconfdat+"_neu";
        fneu=new mdatei(neudatei,ios::out);
        if (!fneu->is_open()) break;
      } // if (iru)
      while(f.is_open() && getline(f,zeile)) {
        kommpos=zeile.find('#');
        geschrieben=0;
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
                anfzweg(altwert);// Anfuehrungszeichen entfernen
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
        struct stat entryorig;
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
  Log(violetts+Tx[T_Ende]+Tx[T_konfcapi]+schwarz+"ccapiconfdat: "+violett+ccapiconfdat+schwarz,obverb,oblog);
} // void paramcl::konfcapi()

// in konfcapi und faxemitC (da konfacpi aus pruefcapi nicht unbedingt aufgerufen wird)
void paramcl::nextnum()
{
  // dieser Abschnitt war zuvor richtcapiher
  unsigned long nextnr=0;
  struct stat entrynextnr;
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
  Log(violetts+Tx[T_verzeichnisse],obverb,oblog);
  pruefcvz(); 
  pruefverz(zufaxenvz,obverb,oblog);
  pruefverz(wvz,obverb,oblog);
  pruefverz(nvz,obverb,oblog);
  pruefverz(empfvz,obverb,oblog);
  for(zielmustercl *zmakt=zmp;1;zmakt++){
    pruefverz(zmakt->ziel,obverb,oblog);
    if (zmakt->obmusterleer()) break;
  }
  for(uint imu=0;imu<this->zmzn;imu++) {
    char *imus = ltoan(imu);
    Log(string(Tx[T_Muster])+imus+": '"+rot+this->zmp[imu].holmuster()+schwarz+"'",this->obverb>1,this->oblog);
    Log(string(Tx[T_Ziel])+imus+":   '"+rot+this->zmp[imu].ziel+schwarz+"'",this->obverb>1,this->oblog);
  }
} // paramcl:: verzeichnisse()

void setztmpc(int obverb, int oblog)
{
  if (tmpc.empty()) {
    // Einbau von '~' ergaebe bei Aufruf mit und ohne sudo unterschiedliche Erweiterungen
    tmpc+=gethome()+"/rootscrontab";
  }
} // void setztmpc()


// wird aufgerufen in: main
void paramcl::pruefcron()
{
  Log(violetts+Tx[T_pruefcron],obverb,oblog);
  //  svec rueck;
  int cronda;
  int cronzuplanen = (cronminut!="0");

  for (uchar runde=0;runde<2;runde++) {
    cronda=obprogda("crontab",obverb-1,0);
    if (cronda) break;
    // systemrueck("which zypper 2>/dev/null && zypper -n in cron || 
    //              KLA which apt-get 2>/dev/null && apt-get --assume-yes install cron; KLZ",1,1);
    linst.doinst("cron",1,1);
    //  int obionice=!systemrueck("which ionice > /dev/null 2>&1",0,0);
  }
  if (cronda) {
    int nochkeincron = systemrueck("sudo crontab -l",obverb-1,0,0,2);
    setztmpc(obverb, oblog);
    string cb0 = " /usr/bin/ionice -c2 -n7 /usr/bin/nice -n19 "+vaufr;// "date >/home/schade/zeit";
    string cbef  =string("*/")+cronminut+" * * * *"+cb0; // "-"-Zeichen nur als cron
    string cbeesc=string("\\*/")+cronminut+" \\* \\* \\* \\*"+cb0; // hier vorne \\- gestrichen
#ifdef uebersichtlich
    string befehl;
    if (!cronzuplanen) {
      if (nochkeincron) {
      } else {
        befehl=("bash -c 'grep \""+saufr+"\" -q <(sudo crontab -l)' && (sudo crontab -l | sed '/"+saufr+"/d'>")+tmpc+"; sudo crontab "+tmpc+")";
      }
    } else {
      if (nochkeincron) {
        befehl=("rm -f ")+tmpc+";";
      } else {
        befehl = ("bash -c 'grep \"")+cbeesc+"\" -q <(sudo crontab -l)' || (sudo crontab -l | sed '/"+saufr+"/d'>"+tmpc+";";
      }
      befehl+=("echo \"")+cbef+"\">>"+tmpc+"; sudo crontab "+tmpc+"";
      if (!nochkeincron)
        befehl+=")";
    }
#else
    string befehl=cronzuplanen?
      (nochkeincron?("rm -f ")+tmpc+";":
       ("bash -c 'grep \"")+cbeesc+"\" -q <(sudo crontab -l)' || (sudo crontab -l | sed '/"+saufr+"/d'>"+tmpc+"; ")+
      "echo \""+cbef+"\">>"+tmpc+"; sudo crontab "+tmpc+(nochkeincron?"":")")
      :
      (nochkeincron?"":("bash -c 'grep \""+saufr+"\" -q <(sudo crontab -l)' && (sudo crontab -l | sed '/"+saufr+"/d'>")+tmpc+";"
       "sudo crontab "+tmpc+")")
      ;
#endif      
    systemrueck(befehl,obverb,oblog);
  }
  //  systemrueck(string("mv -i '")+mpfad+"' /root/bin",1,0);
} // pruefcron

// wird aufgerufen in: main
void paramcl::pruefsamba()
{
  Log(violetts+Tx[T_pruefsamba],obverb,oblog);
  const char* const smbdatei="/etc/samba/smb.conf";
  struct stat sstat;
  int gestartet=0;
  uchar conffehlt;
  const string quelle="/usr/share/samba/smb.conf";
  uchar obinst=0; // ob Samba installiert werden soll bzw. die smb.conf bearbeitet
  uchar obfw=0; // ob SuSEfirewall bearbeitet werden soll
  for(uchar iru=0;iru<2;iru++) {
    if (!(conffehlt=lstat(smbdatei,&sstat))) break;
    if (iru) break;
    pruefverz("/etc/samba",obverb,oblog,0);
    systemrueck("test -f "+quelle+" && sudo cp -a "+quelle+" "+smbdatei,obverb,oblog);
  }
  int dienstzahl=2;
  servc smb("smb","smbd");
  servc smbd("smbd","smbd");
  servc nmb("nmb","nmbd");
  servc nmbd("nmbd","nmbd");
  if (!smb.obslaeuft(obverb,oblog)) if (!smbd.obslaeuft(obverb,oblog)) dienstzahl--;
  if (!nmb.obslaeuft(obverb,oblog)) if (!nmbd.obslaeuft(obverb,oblog)) dienstzahl--;
  //  <<rot<<"dienstzahl: "<<dienstzahl<<endl;
  if (dienstzahl<2 || conffehlt) {
    for(int aru=0;aru<2;aru++) {
      if (aru) {
        if (!nrzf) {
          obinst=Tippob(Tx[T_Samba_muesste_installiert_werden_soll_ich],Tx[T_j_af]);
          if (obinst)
            linst.doinst("samba",obverb,oblog);
          //        smbrestart=0;
        } // if (!nrzf) 
      } // if (aru) 
      if (smb.serviceda) {
        smb.machfit(obverb,oblog);
        gestartet=1;
      } else if (smbd.serviceda) {
        smbd.machfit(obverb,oblog);
        gestartet=1;
      }
      if (nmb.serviceda) {
        nmb.machfit(obverb,oblog);
        if (gestartet==1) gestartet=2;
      } else if (nmbd.serviceda) {
        nmbd.machfit(obverb,oblog);
        if (gestartet==1) gestartet=2;
      }
      if (smb.serviceda) if (smb.obslaeuft(obverb,oblog)) if (nmb.serviceda) if (nmb.obslaeuft(obverb,oblog)) break;
      if (smbd.serviceda) if (smbd.obslaeuft(obverb,oblog)) if (nmbd.serviceda) if (nmbd.obslaeuft(obverb,oblog)) break;
    } // for(int aru=0;aru<2;aru++) 
    //    if (gestartet==2) smbrestart=0;
  } // if (dienstzahl<2 || conffehlt) 
  if (!(conffehlt=lstat(smbdatei,&sstat))) {
    confdat smbcf(smbdatei,obverb);
    smbcf.Abschn_auswert(obverb);
    vector<string*> vzn;
    const char* const VSambaName[4]={Tx[T_Zufaxen],Tx[T_Warteauffax],Tx[T_Nichtgefaxt],Tx[T_Faxempfang]};
    //={&zufaxenvz,&wvz,&nvz,&empfvz};
    vzn.push_back(&zufaxenvz);
    vzn.push_back(&wvz);
    vzn.push_back(&nvz);
    vzn.push_back(&empfvz);
    for(zielmustercl *zmakt=zmp;1;zmakt++){
      vzn.push_back(&zmakt->ziel);
      if (zmakt->obmusterleer()) break;
    }
    uchar gef[vzn.size()];
    for(unsigned k=0;k<vzn.size();k++) {
      gef[k]=0;
    }
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
    for(unsigned k=0;k<vzn.size();k++) {
      if (!gef[k]) {
        smbrestart=1;
        if (!obinst) {
          obinst=Tippob(Tx[T_Sollen_fehlende_Sambafreigaben_fuer_die_angegebenen_Verzeichnisse_ergaenzt_werden],Tx[T_j_af]);
          if (!obinst) break;
        }
        Log(rots+Tx[T_Verzeichnis]+blau+*vzn[k]+rot+Tx[T_nicht_als_Sambafreigabe_gefunden_wird_ergaenzt]+schwarz,1,oblog);
        mdatei sapp(smbdatei,ios::out|ios::app);
        if (sapp.is_open()) {
          if (k<4) {
            sapp<<"["<<VSambaName[k]<<"]"<<endl;
            sapp<<"  comment = "+meinname+" "<<VSambaName[k]<<endl;
          } else {
            sapp<<"["<<Tx[T_Gefaxt]<<"_"<<(k-4)<<"]"<<endl;
            sapp<<"  comment = "+meinname+" "<<Tx[T_Gefaxt]<<"_"<<(k-4)<<endl;
          }
          sapp<<"  path = "<<*vzn[k]<<endl;
          sapp<<"  directory mask = 0660"<<endl;
          sapp<<"  browseable = Yes"<<endl;
          sapp<<"  vfs objects = recycle"<<endl;
          sapp<<"  recycle:versions = Yes"<<endl;
          sapp<<"  recycle:keeptree = Yes"<<endl;
          sapp<<"  recycle:repository = Papierkorb"<<endl;
        } // if (sapp.is_open()) 
      } // if (!gef[k]) 
    } // for(unsigned k=0;k<sizeof vzn/sizeof *vzn;k++) 
    if (!nrzf) {
      if (systemrueck("sudo pdbedit -L | grep "+cuser+":",obverb,oblog)) {
        string pw1, pw2;
        while (1) {
          pw1=Tippstring(Tx[T_Passwort_fuer_samba_fuer_Benutzer]+tuerkiss+cuser+schwarz,&pw1);
          pw2=Tippstring(Tx[T_Passwort_fuer_samba_fuer_Benutzer]+tuerkiss+cuser+schwarz+" ("+Tx[T_erneute_Eingabe]+")",&pw2);
          if (pw1==pw2) break;
        }
        systemrueck("sudo smbpasswd -n -a "+cuser,obverb,oblog);
        systemrueck("(echo "+pw1+"; echo "+pw2+") | sudo smbpasswd -s "+cuser,obverb,oblog);
      } // if (systemrueck("sudo pdbedit -L | grep "+cuser+":",obverb,oblog)) 
    } // if (!nrzf)
    if (smbrestart) {
      if (smb.serviceda) smb.restart(obverb-1,oblog);
      else if (smbd.serviceda) smbd.restart(obverb-1,oblog);
      if (nmb.serviceda) nmb.restart(obverb-1,oblog);
      else if (nmbd.serviceda) nmbd.restart(obverb-1,oblog);
    } // if (smbrestart) 
    // Suse-Firewall
    struct stat fstat;
    const char *susefw="/etc/sysconfig/SuSEfirewall2";
    if (!lstat(susefw,&fstat)) {
      string part="server";
      for(int i=1;i<3;i++) {
        int nichtfrei=systemrueck("grep '^FW_CONFIGURATIONS_EXT=\\\".*samba-"+part+"' "+susefw,obverb,oblog,0,2);
        if (nichtfrei && !nrzf && !obfw) {
          obfw=Tippob(Tx[T_Soll_die_SuSEfirewall_bearbeitet_werden],Tx[T_j_af]);
          if (!obfw) break;
        }
        if (nichtfrei && obfw) {
          systemrueck("sudo sed -i.bak_"+meinname+ltoan(i)+" 's/\\(FW_CONFIGURATIONS_EXT=\\\".*\\)\\(\\\".*$\\)/\\1 samba-"+part+"\\2/g' "+susefw+
              " && sudo systemctl restart SuSEfirewall2 smb nmb",obverb,oblog); 
        }
        part="client";
      } // for(int i=1;i<3;i++) 
    } // if (!lstat(susefw,&fstat)) 
  } //   if (!(conffehlt=lstat(smbdatei,&sstat)))
} // pruefsamba

// wird aufgerufen in: main
int paramcl::initDB()
{
  Log(violetts+"initDB()"+schwarz,obverb,oblog);
  My = new DB(myDBS,host,muser,mpwd,dbq,0,0,0,obverb,oblog);
  if (My->fehnr) {
    Log(rots+Tx[Verbindung_zur_Datenbank_nicht_herstellbar]+schwarz+ltoan(My->fehnr)+rot+Tx[T_Breche_ab]+schwarz,1,1);
    return 1;
  }
  return 0;
} // initDB

int paramcl::pruefDB(const string& db)
{
  Log(violetts+"pruefDB("+db+")"+schwarz,obverb,oblog);
  My = new DB(myDBS,host,muser,mpwd,db,0,0,0,obverb,oblog,3,0);
  return (My->fehnr); 
} // pruefDB

// Parameter -kez
// wird aufgerufen in: main
void paramcl::korrerfolgszeichen()
{
  Log(violetts+Tx[T_korrerfolgszeichen]+schwarz,obverb,oblog);
  // geht wegen Loeschens der Protokolldateien nur (noch) fuer Gefundene, s.u.
  if (1) {
    for(uchar runde=1;runde<2;runde++) {
      set<string>::iterator fit; // Iterator dafuer
      vector<string> rueck;
      set<string> fdn; // Fax-Dateien
      size_t ruecki;
      switch (runde) {
        case 0: // capi
          cmd=string("sudo find '")+cdonevz+"' -maxdepth 1 -type f -iname '*-fax-*.sff'"; //  -printf '%f\\n'"; // cfailedvz weniger wichtig
          systemrueck(cmd,obverb,oblog,&rueck);
          // sortieren
          for(ruecki=0;ruecki<rueck.size();ruecki++) {
            fdn.insert(rueck[ruecki]);
          } 
          break;
        default: // hyla
          //        fdn.clear();
          cmd=string("sudo find ")+varsphylavz+" -name 'q*' -print0 "+(obverb?"":"2>/dev/null")+"| /usr/bin/xargs -0 grep -l ^state:7 ";
          rueck.clear();
          systemrueck(cmd,obverb,oblog,&rueck);
          for(ruecki=0;ruecki<rueck.size();ruecki++) {
            size_t pos;
            if ((pos=rueck[ruecki].rfind("/q"))!=string::npos) fdn.insert(rueck[ruecki].substr(pos+2));
          } 
      }
      string sql=string("SELECT titel p0, tsid p1, submt p2, submid p3, oscht p4, subject p5, docname p6, id p7, fsize p8, pages p9, ")+
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
                Log(ausg.str(),1,1);
                RS vs(My,string("UPDATE `")+touta+"` SET Erfolg= !Erfolg WHERE submid = '"+*(*cerg+3)+"'",255);
              }
            } // ((fit!=fdn.end()) != (**(*cerg+21)=='0')) else
          } // if (*(*cerg+3)) if (*(*cerg+20)) if (*(*cerg+21)) 
        } // while (cerg=routa.HolZeile(),cerg?*cerg:0) 
      } // if (!routa.obfehl) 
    } // for(uchar runde=1;runde<2;runde++) 
  } // if (0) 

} // korrerfolgszeichen

// Parameter -bwv
// wird aufgerufen in: main
void paramcl::bereinigewv()
{
  Log(violetts+Tx[T_bereinigewv]+schwarz,obverb,oblog);
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
  string vgl="Beispiel 997.doc"; // nicht existente Datei
  Log(string(Tx[T_DateienzahlimVz])+blau+ltoan(fdn.size())+schwarz,1,1);
  for(fit=fdn.begin();fit!=fdn.end();++fit) {
    if (*fit==vgl) {
      Log(blaus+*fit+schwarz,1,1);
    }
  }
  for(unsigned runde=0;runde<2;runde++) {
    string sql;
    switch (runde) {
      case 0: sql=string("SELECT id p0, original p1, origvu p2 FROM `")+spooltab+"`"; break;
      case 1: sql=string("SELECT eind p0, docname p1, Erfolg p2 FROM `")+touta+"`"; break;
    }
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
                  }
                }
                if ((fit=fdn.find(dbdocname))!=fdn.end()) { // wenn Datenbankeintrag in der sortierten Mengen der Dateinamen enthalten
                  struct stat entryfit;
                  string quel=wvz+vtz+*fit;
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
                          string zdt=zlvz+vtz+*fit;
                          dorename(quel,zdt,cuser,&vfehler,1,1);
                          if (vfehler) {
                            Log(rots+Tx[T_Fehler_beim_Verschieben_Ausrufezeichen]+": "+ltoan(vfehler)+schwarz,1,1);
                            exit(14);
                          }
                          fdn.erase(fit);
                          break;
                        } // if (!zlvz.empty()) 
                      } else {// if (runde) 
                        fdn.erase(fit); // die in der Spool-Tabelle genannten Dateien stehen lassen
                      }
                      //                      Log(string(ltoan(entryfit.st_size))+" "+(runde==2?dblau:runde==1?blau:rot)+*fit+schwarz,1,1);
                      Log(string(ltoan(entryfit.st_size))+" "+(runde?(**(*cerg+2)=='1'?blau:gruen):rot)+*fit+schwarz,1,1);
                    } else {
                      Log(string(Tx[T_0Bytes])+gruen+wvz+vtz+*fit+schwarz+"'",1,1);
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
  Log(violetts+Tx[T_anhalten]+schwarz,obverb,oblog);
  // crontab
  setztmpc(obverb, oblog);
  string befehl=("bash -c 'grep \""+saufr+"\" -q <(sudo crontab -l)' && (sudo crontab -l | sed '/"+saufr+"/d'>")+tmpc+"; sudo crontab "+tmpc+"); true";
  systemrueck(befehl,obverb,oblog);
  // services
  /*
     befehl="sudo systemctl stop capisuite hylafax-faxq hylafax-hfaxd hylafax-faxgetty-"+hmodem+" hylafax >/dev/null 2>&1; true";
     systemrueck(befehl,obverb,oblog);
   */

  hylasv1(obverb,oblog);
  hylasv2(hysrc,obverb,oblog);
  capisv(obverb,oblog);
  if (sfaxgetty) sfaxgetty->stopdis(obverb,oblog);
  if (shfaxd) shfaxd->stopdis(obverb,oblog);
  if (sfaxq) sfaxq->stopdis(obverb,oblog);
  if (shylafaxd) shylafaxd->stopdis(obverb,oblog);
  if (scapisuite) scapisuite->stopdis(obverb,oblog);
} // void paramcl::anhalten()

// wird aufgerufen in: main
int paramcl::loeschefax(int obverb, int oblog)
{
  Log(violetts+Tx[T_loeschefax]+schwarz,obverb,oblog);
  vector<fsfcl> fsfv;
  size_t nr=0;
  string ergnr,erg;
  char*** cerg;
  RS zul(My,string("SELECT CONCAT_WS(' ',LEFT(CONCAT(IF(ISNULL(original),'NULL',original),SPACE(50)),50),"
        "RIGHT(CONCAT(SPACE(15),IF(ISNULL(capispooldatei),'NULL',capispooldatei)),15),")+
      "CONCAT('Capidials:',RIGHT(CONCAT(SPACE(4),IF(ISNULL(capidials),'NULL',capidials)),4)),"
      "CONCAT('Hyla:',RIGHT(CONCAT(SPACE(5),IF(ISNULL(hylanr),'NULL',hylanr)),5)), "
      "CONCAT('Hyladials:',RIGHT(CONCAT(SPACE(4),IF(ISNULL(hyladials),'NULL',hyladials)),4))) p0,"
      "id p1,"
      "IF(ISNULL(capispooldatei),'NULL',capispooldatei) p2,"
      "IF(ISNULL(capispoolpfad),'"+cfaxusersqvz+"',capispoolpfad) p3,"
      "hylanr p4 FROM `"+spooltab+"` ORDER BY id",ZDB);
  while (cerg=zul.HolZeile(),cerg?*cerg:0) {
    if (*(*cerg+0) && *(*cerg+1)) {
      Log(string("Fax ")+blau+ltoan(++nr)+schwarz+": "+*(*cerg+0),1,1);
      fsfv.push_back(fsfcl(*(*cerg+1),*(*cerg+2),*(*cerg+4),*(*cerg+3)));
    } // if (*(*cerg+0) && *(*cerg+1)) 
  } // while (cerg=zul.HolZeile(),cerg?*cerg:0) 
  if (!nrzf) {
    if (fsfv.size()) {
      ergnr=Tippzahl(Tx[T_Welches_Fax_soll_geloescht_werden]);
      if (ergnr=="0") return 0;
      if (Tippob(string(Tx[T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch])+gruen+ergnr+schwarz+Tx[T_wirklich_geloescht_werden],"n")) {
        nr=atol(ergnr.c_str())-1;
        if (nr>=0 && nr<fsfv.size()) {
          int zdng=0; // Zahl der nicht geloeschten
          if (fsfv[nr].capisd!="NULL" && !fsfv[nr].capisd.empty()) {
            zdng+=fsfv[nr].loeschecapi(obverb,oblog);
            Log(blaus+"capi: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_Capispooldatei]+
                schwarz+fsfv[nr].capisd,obverb,oblog);
          }
          if (fsfv[nr].hylanr!="NULL" && !fsfv[nr].hylanr.empty()) {
            zdng+=fsfv[nr].loeschehyla(this,obverb,oblog);
            Log(blaus+"hyla: "+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng)+blau+Tx[T_hylanr]+schwarz+fsfv[nr].capisd,obverb,oblog);
          }
          Log(blaus+Tx[T_Gesamt]+Tx[T_Zahl_der_nicht_geloeschten_Dateien]+schwarz+ltoan(zdng),obverb,oblog);
          struct stat entrysend;
          fsfv[nr].setzcapistat(this,&entrysend);
          string protdakt;
          uchar hyla_uverz_nr=1;
          int obsfehlt=-1;
          /*fsfv[nr].*/setzhylastat(&fsfv[nr], &protdakt, &hyla_uverz_nr, &obsfehlt, 0, obverb, oblog); // hyla_uverz_nr, obsfehlt
          Log(violetts+"capistat: "+schwarz+FxStatS(&fsfv[nr].capistat)+violett+", hylastat: "+schwarz+FxStatS(&fsfv[nr].hylastat),obverb,oblog);
          if (!zdng || (fsfv[nr].capistat==fehlend && fsfv[nr].hylastat==fehlend)) {
            RS loe(My,string("DELETE FROM `")+spooltab+"` WHERE id="+fsfv[nr].id,-obverb);
          }
        } // if (nr>=0 && nr<fsfv.size()) 
      } // if (Tippob(string(Tx[T_Soll_das_Fax_geloescht_werden_0_ist_Abbruch])+violett+ergnr+schwarz+Tx[T_wirklich_geloescht_werden],"n")) 
    } else {
      Log(Tx[T_Kein_Fax_zum_Loeschen_vorhanden],1,oblog);
    } // if (fsfv.size()) 
  } // !nrzf
  return 1;
} // int paramcl::loeschefax(int obverb, int oblog)

// wird aufgerufen in: main
int paramcl::loeschewaise(int obverb, int oblog)
{
  Log(blaus+Tx[T_loeschewaise]+schwarz,obverb,oblog);
  vector<string> allec;
  vector<string> ids;
  char*** cerg;
  RS su(My,string("SELECT original p0, capispooldatei p1, hylanr p2, id p3 FROM `")+spooltab+"`");
  while (cerg=su.HolZeile(),cerg?*cerg:0) {
    if (*(*cerg+0)) {
      struct stat entryo;
      if (!lstat((wvz+vtz+*(*cerg+0)).c_str(),&entryo)) continue; // Wenn es die Datei im Warteverzeichnis gibt
      if (*(*cerg+1)) if (!lstat((cfaxusersqvz+vtz+*(*cerg+1)).c_str(),&entryo)) continue; // wenn eine Capispooldatei drinsteht und es sie gibt
      if (*(*cerg+2)) if (!lstat((hsendqvz+"/q"+*(*cerg+2)).c_str(),&entryo)) continue; // wenn eine Hylaspooldatei drinsteht und es sie gibt
      if (*(*cerg+3)) ids.push_back(*(*cerg+3));
    } // if (*(*cerg+0)) 
  } // while (cerg=su.HolZeile(),cerg?*cerg:0) 
  for(size_t i=0;i<ids.size();i++) {
    RS loe(My,string("DELETE FROM `")+spooltab+"` WHERE id="+ids[i]);
  }
  return 0;
} // int paramcl::loeschewaise(int obverb, int oblog)

// wird aufgerufen in: main
int paramcl::loescheallewartende(int obverb, int oblog)
{
  Log(blaus+Tx[T_loescheallewartenden]+schwarz,obverb,oblog);
  int erg=0;
  vector<string> allec;
  struct stat entryvz;
  if (!lstat(cfaxusersqvz.c_str(),&entryvz)) {
    cmd=string("sudo find '")+cfaxusersqvz+"/' -maxdepth 1 -type f -iname 'fax-*.*'";
    systemrueck(cmd,obverb,oblog,&allec);
    erg+=allec.size();
    for(size_t i=0;i<allec.size();i++) {
      tuloeschen(allec[i],cuser,1,oblog);
      if (allec[i].find(".sff")!=string::npos) {
        string fname=base_name(allec[i]);
        RS loe(My,string("DELETE FROM `")+spooltab+"` WHERE capispooldatei='"+fname+"'");
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
      fsfcl zuloe(transalle);
      if (!zuloe.loeschehyla(this,obverb,oblog)) {
        //      cmd=string("faxrm ")+transalle;
        //      if (systemrueck(cmd,obverb,oblog)) KLA
        RS loe(My,string("DELETE FROM `")+spooltab+"` WHERE hylanr="+transalle,ZDB);
      }
    } // for(size_t i=0;i<alled.size();i++) 
  } // if (!lstat(hsendqvz.c_str(),&entryvz)) 
  return erg;
} // int paramcl::loescheallewartende(int obverb, int oblog)

// wird aufgerufen in: main (2x)
void paramcl::tu_lista(const string& oberfolg)
{
  Log(violetts+Tx[T_tu_lista]+schwarz,obverb,oblog);
  char ***cerg;
  RS lista(My,string("SELECT Ueberm p0, Submid p1, Faxname p2, Empfaenger p3, Fax p4, Erfolg p5 FROM (")+
      "SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') Ueberm, Submid, RIGHT(CONCAT(space(75),LEFT(Docname,75)),75) Faxname, "
      "RIGHT(CONCAT(SPACE(30),LEFT(rcname,30)),30) Empfaenger, rcfax Fax, Erfolg, transe FROM `"+
      touta+"` WHERE Erfolg = "+oberfolg+" ORDER BY eind desc limit "+dszahl+
      ") i ORDER BY transe",ZDB);

  cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<(oberfolg=="1"?Tx[T_erfolgreich]:Tx[T_erfolglos])<<Tx[T_versandten_Faxe]<<endl;
  while (cerg=lista.HolZeile(),cerg?*cerg:0) {
    cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(14)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(65)<<*(*cerg+2)<<"|"
      <<schwarz<<setw(30)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
  } // while (cerg=lista.HolZeile(),cerg?*cerg:0) 
} // tu_lista

// wird aufgerufen in: main
void paramcl::tu_listi()
{
  Log(violetts+Tx[T_tu_listi]+schwarz,obverb,oblog);
  char ***cerg;
  RS listi(My,string("SELECT * FROM (SELECT DATE_FORMAT(transe,'%d.%m.%y %H:%i:%s') p0,RIGHT(CONCAT(SPACE(85),LEFT(titel,85)),85) p1,"
        "fsize p2,tsid p3,id p4 FROM `")+tinca+"` i ORDER BY transe desc limit "+dszahl+") i ORDER BY p0",ZDB);
  cout<<violett<<Tx[T_Letzte]<<blau<<dszahl<<violett<<Tx[T_empfangene_Faxe]<<schwarz<<endl;
  while (cerg=listi.HolZeile(),cerg?*cerg:0) {
    cout<<blau<<setw(17)<<*(*cerg+0)<<"|"<<violett<<setw(85)<<*(*cerg+1)<<schwarz<<"|"<<blau<<setw(17)<<*(*cerg+2)<<"|"
      <<schwarz<<setw(17)<<*(*cerg+3)<<"|"<<blau<<*(*cerg+4)<<schwarz<<endl;
  } // while (cerg=listi.HolZeile(),cerg?*cerg:0) 
} // tu_listi

// verwendet in DateienHerricht(), empfarch()
int paramcl::pruefsoffice()
{
  static uchar sofficegeprueft=0;
  static int sofficeda=0;
  if (!sofficegeprueft) {
    //              systemrueck("which zypper 2>/dev/null && zypper -n in soffice || "
    //                          "{ which apt-get 2>/dev/null && apt-get --assume-yes install soffice; }",obverb,oblog);
    sofficeda=!linst.doinst("libreoffice-base",obverb,oblog,"soffice");
    sofficegeprueft=1;
  }
  return sofficeda;
} // int paramcl::pruefsoffice()

// verwendet in DateienHerricht
int paramcl::pruefconvert()
{
  static uchar convertgeprueft=0;
  static int convertda=0;
  if (!convertgeprueft) {
    //              systemrueck("which zypper 2>/dev/null && zypper -n in convert || "
    //                          "{ which apt-get 2>/dev/null && apt-get --assume-yes install convert; }",obverb,oblog);
    convertda=!linst.doinst("imagemagick",obverb,oblog,"convert");
    convertgeprueft=1;
  } //   if (!convertgeprueft)
  return convertda;
} // int paramcl::pruefconvert()

// verwendet in empfarch()
int paramcl::pruefocr()
{
  if (!obocrgeprueft) {
    uchar tda=1, deuda=0, engda=0, osdda=0;
    svec rueck;
    systemrueck("tesseract --list-langs 2>&1",obverb,oblog,&rueck); // gibt das normale Ergebnis als Fehlermeldung aus!
    if (!rueck.size()) tda=0; else if (rueck[0].find("List of available")) tda=0;
    if (!tda) {
      linst.doinst("tesseract-ocr",obverb,oblog);
      systemrueck("sudo ldconfig /usr/lib64",obverb,oblog);
    } else {
      for(size_t i=1;i<rueck.size();i++) {
       if (rueck[i]=="deu") deuda=1;
       else if (rueck[i]=="eng") engda=1;
       else if (rueck[i]=="osd") osdda=1;
      }
    }
    if (!deuda) linst.doinst("tesseract-ocr-traineddata-german",obverb,oblog);
    if (!engda) linst.doinst("tesseract-ocr-traineddata-english",obverb,oblog);
    if (!osdda) linst.doinst("tesseract-ocr-traineddata-orientation_and_script_detection",obverb,oblog);

    if (!obprogda("ocrmypdf",oblog,obverb)) {
      if (!linst.doggfinst("python-devel",obverb+1,oblog)) {
        if (!linst.doinst("python3-pip",obverb+1,oblog,"pip3")) {
          lsysen system=lsys.getsys(obverb,oblog);
          if (system==deb)  linst.doggfinst("python3-setuptools",obverb+1,oblog);
          string proj="ocrmypdf_copy";
          string srcvz=instverz+vtz+proj+".tar.gz";
          holvongithub(proj);
          if (!kompilbase(proj,s_gz)) {
            systemrueck("sh -c 'cd \""+instverz+vtz+proj+"\" &&  sudo -H pip3 install ocrmypdf'",obverb,oblog);
            linst.doinst("unpaper",obverb,oblog);
          } //    if (!kompilbase(was,endg))
        } //       if (!linst.doinst("python3-pip",obverb+1,oblog,"pip3"))
      } //     if (!linst.doggfinst("python-devel",obverb+1,oblog))
    } //     if (!obprogda("ocrmypdf",oblog,obverb))
    obocrgeprueft=1;
  } // if (!obocrgeprueft) 
  return 0;
} // int paramcl::pruefocr()

// zufaxenvz = zufaxen-Verzeichnis
// 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
// 1b. die Nicht-PDF-Dateien in dem Verzeichnis zum PDF-Druck ermitteln, in Warteverzeichnis verschieben und in die PDF-Liste spdf eintragen ...
// 2a. ... und in im Warteverzeichnis in PDF umwandeln, falls erfolgreich und gleichziel => auch in ziel kopieren
// 2b. Die originalen PDF-Dateien ins Warteverzeichnis verschieben, falls erfolgreich, nicht schon registriert und gleichziel => auch in ziel kopieren
// wird aufgerufen in: main
void paramcl::DateienHerricht() 
{
  Log(violetts+Tx[T_DateienHerricht],obverb,oblog);
  struct stat entrynpdf;
  //vector<string> npdf, spdf, *npdfp=&npdf, *spdfp=&spdf;  vector<uchar> prios;
  vector<fxfcl> fxv;
  vector<string> anfxstrvec;
  anfxstrvec.push_back(anfaxstr);
  if (!ancfaxstr.empty()) anfxstrvec.push_back(ancfaxstr);
  if (!anhfaxstr.empty()) anfxstrvec.push_back(anhfaxstr);
  for(uchar iprio=0;iprio<anfxstrvec.size();iprio++) {
    // 1a. die (Nicht-PDF- und PDF-) Dateien in dem Verzeichnis ermitteln und im Fall mehrerer Zielfaxnummern aufteilen ...
    cmd=string("sudo find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*"+anfxstrvec.at(iprio)+" [ -,/;:\\\\\\.\\+]*[0123456789]+.*\"";
    vector<string> iprid;
    systemrueck(cmd,obverb,oblog, &iprid);
    for(size_t i=0;i<iprid.size();i++) {
      string stamm,exten;
      getstammext(&(iprid.at(i)),&stamm,&exten);
      Log(string(Tx[T_Endung])+tuerkis+exten+schwarz,obverb>1,oblog);
      Log(string(Tx[T_Stamm])+tuerkis+stamm+schwarz,obverb>1,oblog);
      vector<string> tok, toknr, toktxt, tokname;
      Log(string(Tx[T_trennenach])+blau+anfxstrvec.at(iprio)+schwarz+"'",obverb>1,oblog);
      aufiSplit(&tok,&stamm,anfxstrvec.at(iprio).c_str());
      if (tok.size()>1) { // sollte immer sein
        for(unsigned k=0;k<tok.size();k++) {
          Log(blaus+tok[k]+schwarz,obverb>1,oblog);
        }
        aufiSplit(&toknr,&tok[1],undstr.c_str());
        for(unsigned k=0;k<toknr.size();k++) {
          Log(tuerkiss+"toknr["+ltoan(k)+"]: "+toknr[k]+schwarz,obverb>1,oblog);
        }
        aufiSplit(&toktxt,&tok[0],anstr.c_str());
        for(unsigned k=0;k<toktxt.size();k++) {
          Log(blaus+"toktxt["+ltoan(k)+"]: "+toktxt[k]+schwarz,obverb>1,oblog);
        }
        if (toktxt.size()>1) {
          aufiSplit(&tokname,&toktxt[1],undstr.c_str());
          for(unsigned i=0;i<tokname.size();i++) {
            Log(tuerkiss+"tokname["+ltoan(i)+"]: "+tokname[i]+schwarz,obverb>1,oblog);
          }
        }
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
          Log(tuerkiss+toknr[j]+schwarz,obverb>1,oblog);
          uint kfehler=0;
          if (j<toknr.size()-1) {
            kopiere(iprid.at(i),tmp,&kfehler,1);
            if (kfehler) break;
            Log(string(Tx[T_ErstelledurchKopieren])+rot+tmp+schwarz,1,oblog);
          } else {
            if (iprid.at(i)!=tmp) {
              uint vfehler=0;
              dorename((iprid.at(i)),tmp,cuser,&vfehler,obverb,oblog);
              if (vfehler)
                Log(rots+Tx[T_FehlerbeimUmbenennen]+": "+ltoan(vfehler)+schwarz,1,1);
              Log(string(Tx[T_ErstelledurchBenennen])+rot+tmp+schwarz,1,oblog);
            } // if (iprid.at(i)!=tmp) 
          } // if (j<toknr.size()-1) 
        } // for(unsigned j=0;j<toknr.size();j++) 
      } // if (tok.size()>1) 
    } // for(size_t i=0;i<iprid.size();i++) 
  } // for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) 

  // 1b. die Nicht-PDF-Dateien in dem Verzeichnis zum PDF-Druck ermitteln, 
  //    in Warteverzeichnis verschieben und in die PDF-Liste spdfp eintragen ...
    /*
       cmd=string("find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*\\("+
       anfaxstr+
       (ancfaxstr.empty()?"":string("\\|")+ancfaxstr))+
       (anhfaxstr.empty()?"":string("\\|")+anhfaxstr+
       "\\) [ -,/;:\\\\\\.\\+]*[0123456789]+.*\" -not -iname \"*.pdf\"";
     */
    for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) {
      if (!anfxstrvec.at(iprio).empty()) {
        cmd= string("sudo find \"")+zufaxenvz+"\" -maxdepth 1 -type f -iregex \".*"+anfxstrvec.at(iprio)+" [ -,/;:\\\\\\.\\+]*[0123456789]+.*\""
          " -not -iname \"*.pdf\"";
        vector<string> npdfd;
        systemrueck(cmd, obverb,oblog, &npdfd);
        for(size_t i=0;i<npdfd.size();i++) {
          uint vfehler=0;
          string ndname=zufaxenvz+vtz+neuerdateiname(npdfd.at(i));
          if (ndname!=npdfd.at(i)) {
            dorename(npdfd.at(i),ndname,cuser,&vfehler,obverb,oblog);
            if (vfehler) {
              cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
                blau<<npdfd.at(i)<<schwarz<<" ->\n"<<
                blau<<ndname<<schwarz<<endl;
              exit(16);
            }
            npdfd.at(i)=ndname;
          }
          string wartedatei=verschiebe(npdfd.at(i),wvz,cuser,&vfehler,1,obverb,oblog);
          if (!vfehler) {
            string stamm,exten;
            //          npdfp->push_back(wartedatei);
            getstammext(&wartedatei,&stamm,&exten);
            string zupdf=stamm+".pdf"; 
            //          spdfp->push_back(zupdf);
            //          prios.push_back(iprio);
            fxv.push_back(fxfcl(wartedatei,zupdf,iprio));
          } else {
            cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
              blau<<npdfd.at(i)<<schwarz<<" ->\n"<<
              blau<<wvz<<schwarz<<endl;
            exit(18);
          } // if (!vfehler) 
        } // for(size_t i=0;i<npdfd.size();i++) 
      } // if (!anfxstrvec.at(iprio).empty()) 
    } // for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) 

  for(unsigned i=0;i<fxv.size();i++) {
    Log(string("npdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].npdf+schwarz,obverb,oblog);
    Log(string("spdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].spdf+schwarz,obverb,oblog);
    Log(string("prio[")+rot+ltoan(i)+schwarz+"]: "+rot+ltoan(fxv[i].prio)+schwarz,obverb,oblog);
  } // for(unsigned i=0;i<fxv.size();i++)
  // zufaxenvz = zufaxen-Verzeichnis
  Log(string(Tx[T_aus])+drot+zufaxenvz+schwarz+vtz+Tx[T_verarbeitete_Nicht_PDF_Dateien]+drot+ltoan(fxv.size())+schwarz,1,oblog);
  //  geszahl+=npdfp->size(); // 1b

  // 2a. ... und im Warteverzeichnis in PDF umwandeln, falls erfolgreich und gleichziel => auch in ziel kopieren
  for (int nachrnr=fxv.size()-1; nachrnr>=0; --nachrnr) {
    unsigned erg=-1;
    if (lstat((fxv[nachrnr].npdf.c_str()), &entrynpdf)) {
      // ZPKT(" nach lstat: "hh;
      Log(string(Tx[T_lstatfehlgeschlagen]) + strerror(errno) + Tx[T_beiDatei]+ fxv[nachrnr].npdf,1,1,1);
      continue;
    } // (lstat((*pfad + vtz + dirEntry->d_name).c_str(), &entrynpdf)) 
    for(unsigned runde=1;runde<=2;runde++) {
      cmd.clear();
      switch (runde) {
        case 1: 
          if (pruefsoffice())
            cmd=string("cd $HOME; soffice --headless --convert-to pdf --outdir \"")+wvz+"\" \""+fxv[nachrnr].npdf+"\"";
          break; // Ergebnis immer 0
        case 2: 
          if (pruefconvert())
            cmd=string("sudo convert \""+fxv[nachrnr].npdf+"\" \""+fxv[nachrnr].spdf+"\""); 
          break;
      } // switch (runde) 
      if (cmd.empty()) erg=1; else {
        vector<string> umwd;
        systemrueck(cmd, obverb,oblog,&umwd);
        erg=lstat(fxv[nachrnr].spdf.c_str(),&entrynpdf); 
        Log(string(Tx[T_Umwandlungvon])+blau+fxv[nachrnr].npdf+Tx[T_inPDFmit]+tuerkis+(runde==1?"soffice":"convert")+schwarz+
            Tx[T_beendetErgebnis]+rot+(erg?Tx[T_misserfolg]:Tx[T_Erfolg_af])+schwarz, 1||erg,(erg?1:oblog));
        if (!erg) break; 
      } // if (cmd.empty()) erg=1; else 
    } // for(unsigned runde=1;runde<=2;runde++) 
    if (!erg) {
      if (gleichziel) {
        uint kfehler=0;
        kopiere(fxv[nachrnr].npdf, zmp, &kfehler, 1, obverb, oblog);
        string zield=kopiere(fxv[nachrnr].spdf, zmp, &kfehler, 1, obverb, oblog);
        if (obocra) if (!zield.empty()) {
          if (!pruefocr()) {
            systemrueck(string("ocrmypdf -rcsl ")+(langu=="d"?"deu":"eng")+" \""+zield+"\" \""+zield+"\""
                " && chmod +r \""+zield+"\"" ,obverb,oblog);
          } // pruefocr()
        } // if (obocra) if (!zield.empty()) 
      } // if (gleichziel)
    } else {
      //      spdfp->erase(spdfp->begin()+nachrnr);
      // Misserfolg, zurueckverschieben und aus der Datenbank loeschen
      uint wfehler;
     // <<violett<<"fxv["<<(int)nachrnr<<"].npdf: "<<fxv[nachrnr].npdf<<schwarz<<endl;
     // <<violett<<"fxv["<<(int)nachrnr<<"].spdf: "<<fxv[nachrnr].spdf<<schwarz<<endl;
      struct stat npdfstat;
      if (!lstat(fxv[nachrnr].npdf.c_str(), &npdfstat))
        verschiebe(fxv[nachrnr].npdf,zufaxenvz,cuser,&wfehler,1,obverb,oblog);
      struct stat spdfstat;
      if (!lstat(fxv[nachrnr].spdf.c_str(), &spdfstat))
        verschiebe(fxv[nachrnr].spdf,zufaxenvz,cuser,&wfehler,1,obverb,oblog);
      fxv.erase(fxv.begin()+nachrnr);
    } // if (!erg) else
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
          string ndname=zufaxenvz+vtz+neuerdateiname(spdfd.at(i));
          uint vfehler=0;
          if (ndname!=spdfd.at(i)) {
            dorename(spdfd.at(i),ndname,cuser,&vfehler,obverb,oblog);
            if (vfehler) {
              cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
                blau<<spdfd.at(i)<<schwarz<<" ->\n"<<
                blau<<ndname<<schwarz<<endl;
              exit(20);
            }
            spdfd.at(i)=ndname;
          }
          string wartedatei=verschiebe(spdfd.at(i),wvz,cuser,&vfehler,1,obverb,oblog);
          if (!vfehler) {
            int vorhanden=0; // 1= Datei schon zuvor als nicht-PDF-Datei eingetragen
            for(unsigned i=0;i<fxv.size();i++) {
              if (i>=spdfd.size()) break;
              if (fxv[i].spdf==spdfd.at(i)) {vorhanden=1;break;} 
            }
            if (!vorhanden) {
              fxv.push_back(fxfcl(wartedatei,iprio));
              if (gleichziel) {
                uint kfehler=0;
                string zield=kopiere(wartedatei, zmp, &kfehler, 1, obverb, oblog);
                if (obocra) if (!zield.empty()) {
                  if (pruefocr()) {
                    systemrueck(string("ocrmypdf -rcsl ")+(langu=="d"?"deu":"eng")+" \""+zield+"\" \""+zield+"\""
                        " && chmod +r \""+zield+"\"" ,obverb,oblog);
                  } // pruefocr()
                } // if (obocra) if (!zield.empty()) 
              } //  if (gleichziel)
            } //if (!vorhanden)
          } else {
            cerr<<rot<<meinname<<" "<<Tx[T_abgebrochen]<<schwarz<<vfehler<<Tx[T_FehlerbeimUmbenennenbei]<<endl<<
              blau<<spdfd.at(i)<<schwarz<<" ->\n"<<
              blau<<wvz<<schwarz<<endl;
            exit(22);
          } // if (!vfehler) else 
        } // for(size_t i=0
      } // if (!anfxstrvec.at(iprio).empty()) 
    } // for(unsigned iprio=0;iprio<anfxstrvec.size();iprio++) 
  for(unsigned i=0;i<fxv.size();i++) {
    Log(string("npdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].npdf+schwarz,obverb,oblog);
    Log(string("spdf[")+rot+ltoan(i)+schwarz+"]: "+rot+fxv[i].spdf+schwarz,obverb,oblog);
    Log(string("prio:       ")+rot+ltoan(fxv[i].prio)+schwarz,obverb,oblog);
  } //   for(unsigned i=0;i<fxv.size();i++)

  Log(string(Tx[T_aus])+drot+zufaxenvz+schwarz+vtz+Tx[T_verarbeitete_PDF_Dateien]+drot+ltoan(fxv.size())+schwarz,1,oblog);
  geszahl=fxv.size();
  // 3) in spooltab eintragen
  WVZinDatenbank(&fxv);
} // void DateienHerricht(DB *My, string *wvz, string *zufaxenvz, zielmustercl zmp, unsigned long *geszahl,uchar gleichziel, int obverb=0,int oblog=0)

// wird aufgerufen in: main
void paramcl::faxealle()
{
  Log(violetts+Tx[T_faxealle]+schwarz+", "+blau+Tx[T_obcapimitDoppelpunkt]+schwarz+(obcapi?Tx[T_ja]:Tx[T_nein])+", "
      +blau+Tx[T_obhylamitDoppelpunkt]+schwarz+(obhyla?Tx[T_ja]:Tx[T_nein]),obverb,oblog);
  vector<fsfcl> fsfv;
  char ***cerg;
  unsigned long dbszahl=0; // Zahl der Datenbanksaetze
  string hzstr=ltoan(hylazuerst);
  if (!isnumeric(maxhylav)) maxhylav="3";
  if (!isnumeric(maxcapiv)) maxcapiv="3";
  RS r0(My,string("SELECT id p0, origvu p1, original p2, telnr p3, prio p4, "
        "IF(ISNULL(capispooldatei),'',capispooldatei) p5, IF(ISNULL(capidials),'',capidials) p6, "
        "IF(ISNULL(hylanr),'',hylanr) p7, IF(ISNULL(hyladials),'',hyladials) p8, "
        "((ISNULL(capispooldatei)or capispooldatei='') AND (ISNULL(hyladials) OR hyladials>")+maxhylav+" OR hyladials=-1 OR "
      "    (ISNULL(prio) OR prio=1 OR (prio=0 AND NOT "+hzstr+")))) p9, "
      "((ISNULL(hylanr) OR hylanr='') AND (ISNULL(capidials) OR capidials>" +maxcapiv+" OR capidials=-1 OR "
      "      (ISNULL(prio) OR prio=2 OR (prio=0 AND "+hzstr+")))) p10, "
      "adressat p11 "
      "FROM `"+spooltab+"` "
      "WHERE original>''",ZDB);
  if (r0.obfehl) {
    cerr<<rots<<Tx[T_Fehler_af]<<schwarz<<r0.obfehl<<rot<<Tx[T_beiSQLAbfrage]<<schwarz<<r0.sql<<endl;
  } else {
    while (cerg=r0.HolZeile(),cerg?*cerg:0) {
      (dbszahl)++;
      if (!*(*cerg+9)) *(*cerg+9)=(char*)"";
      if (!*(*cerg+10)) *(*cerg+10)=(char*)"";
      if (*(*cerg+0) && *(*cerg+1) && *(*cerg+2) && *(*cerg+3) && *(*cerg+4) && *(*cerg+5) && 
          *(*cerg+6) && *(*cerg+7) && *(*cerg+8) && *(*cerg+9) && *(*cerg+10)) {
        // obcapi = *(*cerg+9), obhyla=*(*cerg+10)
        fsfv.push_back(fsfcl(*(*cerg+0), *(*cerg+1), *(*cerg+2), *(*cerg+3), atoi(*(*cerg+4)), *(*cerg+5),
              atoi(*(*cerg+6)), *(*cerg+7), atoi(*(*cerg+8)), (binaer)atoi(*(*cerg+9)), (binaer)atoi(*(*cerg+10)), *(*cerg+11)));
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
  if (capisd.empty()) {
    capistat=fehlend;
  } else {
    string aktuser;
    sendqgespfad = cspf+vtz+capisd;
    size_t p1,p2;
    if ((p1=cspf.rfind(vtz))) if ((p2=cspf.rfind(vtz,p1-1))) {
      aktuser=cspf.substr(p2+1,p1-p2-1);
      if (!lstat(sendqgespfad.c_str(),entrysendp)) {
        capistat=wartend;
      } else {
        // gesandte und gescheiterte Faxe wurden von capisuite entsprechend umbenannt
        for(capistat=gesandt;capistat<=gescheitert;capistat=static_cast<FxStat>(capistat+1)) { 
          // entspr. gefaxte/gescheiterte Datei in capisuite
          sendqgespfad = (capistat==gescheitert?pmp->cfailedvz:pmp->cdonevz)+vtz+aktuser+"-"+capisd; 
          if (!lstat((sendqgespfad.c_str()), entrysendp)) break; 
        } 
        // hier koennte capistat auch fehlend sein
      } 
    }
  }
} // fsfcl::setzcapistat

// hylafax: bei zu faxenden Dateien stehen die Steuerdateien in /var/spool/fax/sendq/q105, benannt nach /var/spool/fax/etc/xferfaxlog, dort steht in der 6. Spalte die hyla-Index-Nummer z.B. 105, die als Rueckmeldung von sendfax erscheint ("request id is 105 (group id 105) for host localhost (1 file)")
// in der 4. Spalte steht dazu die Dokumentnummer 00000133, mit der das Dokument im Spool in /var/spool/fax/docq/doc133.pdf wartet
// hylafax-Befehl: sendfax -n -A -d  0814198765432 "/DATA/Patientendokumente/warteauffax/... .pdf"
// sendfax -n -A -d   98765432 "/DATA/Patientendokumente/warteauffax/... .pdf""  ( (mit utf8)

// Dateien in Spool-Tabelle nach inzwischen verarbeiteten durchsuchen, Datenbank- und Dateieintraege korrigieren 
// wird aufgerufen in: main
void paramcl::untersuchespool() // faxart 0=capi, 1=hyla
{
  // Schaue nach, welche der gespoolten schon weggeschickt sind, Anpassung der Primaerdateien und des Datenbankeintrags
  Log(violetts+Tx[T_untersuchespool]+schwarz,obverb,oblog);
  char ***cerg;
  RS rs(My,string("SELECT id p0,capispooldatei p1,capispoolpfad p2,original p3,cdateidatum p4,"
        " telnr p5,origvu p6,hylanr p7,capidials p8,hyladials p9,hdateidatum p10, adressat p11 "
        "FROM `")+spooltab+"` WHERE (hylanr RLIKE '^[0-9]+$' AND hylanr<>0) OR capispooldatei RLIKE '^fax-[0-9]+\\.sff$'",ZDB);
  if (!rs.obfehl) {
    faxord=0;
    while (cerg=rs.HolZeile(),cerg?*cerg:0) {
      faxord++;
      if (*(*cerg+0)) if (*(*cerg+3)) {
        (dbzahl)++;
        stringstream ausg; //      ausg.str(std::string()); ausg.clear();
        fsfcl fsf(*(*cerg+0),*(*cerg+3)); // id, original
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
        Log(string("id: ")+fsf.id+": ",obverb?-2:0,oblog); // -2: schreibt ohne Zeilenwechsel
        ausg<<blau<<faxord<<") "<<rot<<wvz<<vtz<<fsf.original<<schwarz<<": "; // ab hier Neue-Zeile-Zeichen immer am Anfang der naechsten Zeile
        // a) ueber capisuite
        // den Status in Capi der aus spool geholten Zeile untersuchen, dort aktualisieren
        //   und ggf. in hylafax stoppen
        struct stat entrysend;
        if (obcapi) {
          if (faxord==1) this->pruefcapi(); // in der ersten Runde, in der Capi verwendet werden soll, Capi pruefen
          fsf.setzcapistat(this, &entrysend);
          string ctries;
          fsf.capiwausgeb(&ausg, &capiconf[2].wert, obverb, &ctries, oblog);

          if (fsf.capistat==wartend) {
            RS rupd(My); 
            vector<instyp> einf; // fuer alle Datenbankeinfuegungen
            einf.push_back(instyp(My->DBS,"capidials",&ctries));
            string bedingung=string("id=")+fsf.id;
            rupd.update(altspool,einf,ZDB,bedingung);
            rupd.update(spooltab,einf,ZDB,bedingung);

          } else if (fsf.capistat==gesandt) {
            // ... und ggf. in hylafax loeschen
            fsf.loeschehyla(this,obverb, oblog);
          } else if (fsf.capistat==gescheitert) {
          } else if (fsf.capistat==fehlend) {
          }
        } // if (obcapi) 

        // b) ueber hylafax
        if (obhyla) {
          string protdakt;
          uchar hyla_uverz_nr; // kleine Runde
          int obsfehlt=-1;
          string hylastate, hyladials, hylastatus, hylastatuscode, number;
          /*fsf.*/
          setzhylastat(&fsf, &protdakt, &hyla_uverz_nr, &obsfehlt, 0, obverb, oblog, &hylastate, &hyladials, &hylastatus, &hylastatuscode);
          fsf.hylaausgeb(&ausg, this, obsfehlt, hylastate, obverb, 0, oblog);
          if (!obsfehlt) { // Protokolldatei vorhanden
            RS rupd(My); 
            vector<instyp> einf; // fuer alle Datenbankeinfuegungen
            einf.push_back(instyp(My->DBS,"hylastate",&hylastate));
            if (!hyla_uverz_nr) { // wenn fertig
              if (fsf.hylastat==gescheitert) { // (hylastate=="8") // 8, status gescheitert, evtl. unzureichend dokumentiert, aber wahr
                einf.push_back(instyp(My->DBS,"hylanr","0",(uchar)1));
                //                  einf.push_back(instyp(My->DBS,"hyladials","-1",(uchar)1));
                hyladials="-1";
                einf.push_back(instyp(My->DBS,"hylastatus",&hylastatus));
                einf.push_back(instyp(My->DBS,"hylastatuscode",&hylastatuscode));
              } else if (fsf.hylastat==gesandt) { // (hylastate=="7") // 7, status erfolgreich
                // ... und ggf. in capisuite loeschen
                fsf.loeschecapi(obverb,oblog);
              } // if (fsf.hylastat==gescheitert) else
            } // if (!hyla_uverz_nr) 
            einf.push_back(instyp(My->DBS,"hyladials",&hyladials));
            string bedingung=string("id=")+fsf.id;
            rupd.update(altspool,einf,ZDB,bedingung);
            rupd.update(spooltab,einf,ZDB,bedingung);
            ausg<<Tx[T_bzw]<<blau<<protdakt<<schwarz;
          } // if (!warteirgendwo)
        } // if (!obsfehlt) ... else
        if (obcapi || obhyla) {
          // im Erfolgsfall zugrundeliegende Dateien verschieben
          if (fsf.capistat==gesandt || fsf.hylastat==gesandt) {
            (ezahl)++;

            // Fax gelungen, Dateien in warteauffax nach zielmuster verschieben bzw. loeschen ...
            for(unsigned iru=0;iru<2;iru++) {
              string *datei=iru?&fsf.origvu:&fsf.original;
              if (!datei->empty()) {
                string zuloe = wvz+ vtz + *datei;
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
          } else if (fsf.capistat==wartend || fsf.hylastat==wartend) {
            (wzahl)++;
          }
          // Aktionen, wenn in beiden gescheitert oder fehlend
          if (obverb>0) {
            Log(violetts+"Capistat: "+schwarz+FxStatS(&fsf.capistat)+violett+", Hylastat: "+schwarz+FxStatS(&fsf.hylastat),obverb,oblog);
          }
          uchar allegesch = ((!obcapi || fsf.capistat==gescheitert) && (!obhyla || fsf.hylastat==gescheitert));
          uchar nimmer = ((!obcapi || fsf.capistat==fehlend || fsf.capistat==gescheitert) && 
              (!obhyla || fsf.hylastat==fehlend || fsf.hylastat==gescheitert));
          uchar ogibts[2] = {0,0};
          string odatei[2];
          if (nimmer) {
            for(unsigned iru=0;iru<2;iru++) {
              string *datei=iru?&fsf.origvu:&fsf.original;
              if (!datei->empty()) {
                odatei[iru] = wvz+ vtz + *datei;
                struct stat ostat;
                ogibts[iru]=!lstat(odatei[iru].c_str(),&ostat);
                Log(blaus+"odatei["+(iru?"1":"0")+"]: "+odatei[iru],obverb,oblog);
                Log(blaus+"ogibts["+(iru?"1":"0")+"]: "+(ogibts[iru]?"1":"0"),obverb,oblog);
              } // if (!datei->empty()
            } // for(unsigned iru=0
          } // if (nimmer)
          if (fsf.capistat==gesandt || fsf.hylastat==gesandt || allegesch || (nimmer /* && !ogibts[0] */) ) {
            uchar geloescht=0;
            fsf.archiviere(My,this,&entrysend,allegesch||nimmer,fsf.capistat==gesandt?capi:fsf.hylastat==gesandt?hyla:fsf.capisd.empty()?capi:hyla, 
                &geloescht, obverb, oblog);
          } 
          if (allegesch || (nimmer && !ogibts[0])) {
            // Fax gescheitert, Dateien von warteauffax nach nichtgefaxt verschieben
            for(unsigned iru=0;iru<2;iru++) {
              uint vfehler=0;
              if (ogibts[iru]) {
                verschiebe(odatei[iru],nvz,cuser,&vfehler, 1, obverb,oblog);
                // an vorderster Stelle Scheitern erkennen lassen
                systemrueck("touch '"+zmvp[0].ziel+vtz+Tx[T_nichtgefaxt]+" "+odatei[iru]+".nix'",1,1);
              } // if (ogibts[iru]) 
            } // for(unsigned iru=0;iru<2;iru++) 
          } // if (allegesch || (nimmer && !ogibts[0]))
        } // if (obcapi || obhyla)
        Log(ausg.str(),1,oblog);
      } // if (*(*cerg+0)) if (*(*cerg+3))
    } // while (cerg=rs.HolZeile(),cerg?*cerg:0) 
  } // if (!rs.obfehl) 
} // untersuchespool

// Zeige Dateien im Spool an, die nicht in der Spool-Tabelle stehen
// wird aufgerufen in: main
void paramcl::zeigweitere()
{
  Log(violetts+Tx[T_zeigweitere]+schwarz,obverb,oblog);
  static int obtitel=0;
  stringstream ausg; //      ausg.str(std::string()); ausg.clear();
  vector<string> rueck;
  struct stat entryvz;
  if (obcapi) {
    if (!lstat(cfaxusersqvz.c_str(),&entryvz)) {
      // 7.2.16: alte *.lock-Dateien loeschen
      cmd=string("sudo find '")+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.lock'"; //  -printf '%f\\n'";
      systemrueck(cmd,obverb,oblog,&rueck);
      for(size_t i=0;i<rueck.size();i++) {
        string stamm,exten;
        getstammext(&rueck[i],&stamm,&exten);
        string zugeh=stamm+".sff";
        if (lstat(zugeh.c_str(),&entryvz)) {
          tuloeschen(rueck[i],cuser,obverb,oblog);
        }
      }
      rueck.clear();
      // 20.1.16: wenn dort eine .txt-steht ohne zugehoerige .sff-Datei, dann haelt sie den ganzen Betrieb auf
      cmd=string("sudo find '")+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.txt'"; //  -printf '%f\\n'";
      systemrueck(cmd,obverb,oblog,&rueck);
      for(size_t i=0;i<rueck.size();i++) {
        string stamm,exten;
        getstammext(&rueck[i],&stamm,&exten);
        string zugeh=stamm+".sff";
        if (lstat(zugeh.c_str(),&entryvz)) {
          string base=base_name(zugeh);
          RS inouta(My,string("SELECT submid FROM `")+touta+"` WHERE submid = '"+base+"'",ZDB);
          if (inouta.num_rows) {
            Log(blaus+Tx[T_Verwaiste_Datei]+gruen+rueck[i]+schwarz+Tx[T_geloescht_Fax_schon_in]+gruen+touta+schwarz+
                Tx[T_archiviert_Ausrufezeichen],1,1);
            tuloeschen(rueck[i],cuser,obverb,oblog);
            break;
          } else {
            // 31.1.16: ... und wenn diese sich nicht in outa findet ...
            string waisen = cfaxusersqvz+"/waisen";
            pruefverz(waisen,obverb,oblog,1);
            uint vfehler=0;
            verschiebe(rueck[i],waisen,cuser,&vfehler,1,obverb,oblog);
          } // if (inouta.num_rows) else 
        } // if (lstat(zugeh.c_str(),&entryvz)) 
      } // for(size_t i=0;i<rueck.size();i++) 
      cmd=string("sudo find '")+cfaxusersqvz+"' -maxdepth 1 -type f -iname 'fax*.sff'"; //  -printf '%f\\n'";
      rueck.clear();
      systemrueck(cmd,obverb,oblog,&rueck);
      for(size_t i=0;i<rueck.size();i++) {
        uchar indb=0;
        char ***cerg;
        ZDB=0;
        RS rs(My,string("SELECT id FROM `")+spooltab+"` WHERE CONCAT(capispoolpfad,'/',capispooldatei)='"+rueck[i]+"'",ZDB);
        if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
        if (!indb) {
          if (!obtitel) {
            ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
            obtitel=1;
          }
          fsfcl fsf(rueck[i],wartend);
          fsf.capiwausgeb(&ausg, &capiconf[2].wert, obverb, 0, oblog, ++faxord);
        }
      } // for(size_t i=0
    }
  }
  if (obhyla) {
    if (!lstat(hsendqvz.c_str(),&entryvz)) {
      cmd=string("sudo find '")+hsendqvz+"' -maxdepth 1 -type f -iname 'q*' -printf '%f\\n'";
      rueck.clear();
      systemrueck(cmd,obverb,oblog,&rueck);
      for(size_t i=0;i<rueck.size();i++) {
        uchar indb=0;
        string hylanr=rueck[i].substr(1);
        char ***cerg;
        RS rs(My,string("SELECT id FROM `")+spooltab+"` WHERE hylanr="+hylanr,ZDB); // "` where concat('q',hylanr)='"+rueck[i]+"'",ZDB);
        if (cerg=rs.HolZeile(),cerg?*cerg:0) indb=1;
        if (!indb) {
          if (!obtitel) {
            ausg<<rot<<Tx[T_Weitere_Spool_Eintraege]<<schwarz;
            obtitel=1;
          }
          fsfcl fsf(hylanr); // fsf(rueck[i]);
          string protdakt=hsendqvz+vtz+hylanr; // rueck[i];
          uchar hyla_uverz_nr=1;
          int obsfehlt=-1;
          /*fsf.*/
          string hylastate;
          setzhylastat(&fsf, &protdakt, &hyla_uverz_nr, &obsfehlt, 2, obverb, oblog, &hylastate);
          fsf.hylaausgeb(&ausg, this, 0, hylastate, obverb, 0, oblog);
        } // if (!indb)
      } // for(size_t i=0;i<rueck.size();i++) 
    } // if (!lstat(hsendqvz.c_str(),&entryvz))
  } // if (obhyla) 
  if (obtitel) Log(ausg.str(),1,oblog);
} // void zeigweitere(DB *My, paramcl *pmp, int obverb=0,int oblog=0)


// wird aufgerufen in: main
void paramcl::empfarch()
{
  Log(violetts+Tx[T_empfarch]+schwarz,obverb,oblog);
  char tbuf[255];
  // 1) hyla
  string hempfavz=varsphylavz+"/autofaxarch"; // /var/spool/capisuite/empfarch/
  // Faxe in der Empfangswarteschlange auflisten, ...
  cmd=string("sudo find \"")+varsphylavz+"/recvq\" -name \"fax*.tif\"";
  vector<string> rueck;
  systemrueck(cmd,obverb,oblog, &rueck);
  for(size_t i=0;i<rueck.size();i++) {
    if (!i) {
      pruefverz(hempfavz,obverb,oblog);
    }
    // ..., Informationen darueber einsammeln, ...
    string zeit;
    string absdr,tsid,callerid,devname=hmodem;
    ulong seiten=0;
    string stamm,exten,ganz=rueck[i];
    getstammext(&ganz,&stamm,&exten);
    string base=base_name(stamm);
    string fnr=base.substr(3);
    fnr=fnr.substr(fnr.find_first_not_of("0"));
    vector<string> tok; // fuer imagedescription
    char buf[255];
    char *rdesc=buf;
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    struct stat entrylog;
    memset(&entrylog,0,sizeof entrylog);
    if (!lstat(rueck[i].c_str(),&entrylog))  {
      systemrueck("sudo chmod 777 "+rueck[i],obverb,oblog);
      memcpy(&tm, localtime(&entrylog.st_mtime),sizeof(tm));
      strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", &tm);
      // <<"Buf: "<<buf<<endl;
    } //     if (!lstat(rueck[i].c_str(),&entrylog)) 
    if (TIFF* tif = TIFFOpen(rueck[i].c_str(), "r")) {
      ankzahl++;
      rdesc=0;
      if (TIFFGetField(tif, TIFFTAG_DATETIME, &rdesc)) {
        // <<"Datetime: \n"<<rdesc<<endl;
        strptime(rdesc,"%Y:%m:%d %H:%M:%S",&tm);
        /*
           char buf[255];
           strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", &tm);
           <<"Buf (2): "<<buf<<endl;
         */
      }
      seiten=TIFFNumberOfDirectories(tif);
      rdesc=0;
      if (TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &rdesc)) {
        //          printf("Beschreibung: %s\n",beschreib);
        //  out<<"Beschreibung: \n"<<rdesc<<endl;
        tok.clear();
        aufSplit(&tok,rdesc,'\n');
        if (tok.size()) {
          if (tok.size()>1) {
            // <<gruen<<"tok[0]: "<<schwarz<<tok[0]<<endl;
            callerid=tok[0];
            // <<gruen<<"tok[1]: "<<schwarz<<tok[1]<<endl;
            tsid=tok[1];
            if (tok.size()>2) absdr=tok[2];
          } else {
            if (istelnr(tok[0])) {
              // <<gruen<<"tok[0] b: "<<schwarz<<tok[0]<<endl;
              callerid=tok[0]; 
            } else { 
              // <<gruen<<"tok[0] c: "<<schwarz<<tok[0]<<endl;
              absdr=tok[0];
            }
          } //           if (tok.size()>1)  else
        } // if (tok.size()) 
      } // if (TIFFGetField(tif, TIFFTAG_IMAGEDESCRIPTION, &rdesc)) 
      // rdesc=0;
      // if (TIFFGetField(tif, TIFFTAG_MODEL, &rdesc))
      rdesc=0;
      if (callerid.empty()) {
        if (TIFFGetField(tif, TIFFTAG_MAKE, &rdesc)) {
          //          printf("Beschreibung: %s\n",beschreib);
          // <<gruen<<"rdesc: "<<schwarz<<rdesc<<endl;
          if (rdesc) {
            devname+=", ";
            devname+=rdesc;
          }
        } // if (TIFFGetField(tif, TIFFTAG_MAKE, &rdesc)) 
      } // if (callerid.empty()) 
      TIFFClose(tif);
    } // if (TIFF* tif = TIFFOpen(rueck[i].c_str(), "r")) 
    string tabsdr; // transferierter Absender
    if (callerid.empty()) {
      svec trueck;
      systemrueck(string("tac \"")+xferfaxlog+"\" 2>/dev/null | grep -m 1 \""+base_name(rueck[i])+"\" | cut -f 8,9",obverb,oblog,&trueck); 
      if (trueck.size()) {
        tok.clear();
        aufSplit(&tok,&trueck[0],'\t');
        if (tok.size()) {
          // <<gruen<<"tok[0] d: "<<schwarz<<tok[0]<<endl; // Tel'nr z.B. 49.8131.1234567
          callerid=tok[0];
          if (tok.size()>1) {
            // <<gruen<<"tok[1] d: "<<schwarz<<tok[1]<<endl; // Namen z.B. G.Schade
            tabsdr=tok[1];
            anfzweg(tabsdr);
          }
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
    }
    if (absdr.length()>187) absdr.erase(187);

    strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H.%M.%S", &tm);
    if (absdr.length()>187) absdr.erase(187);
    if (absdr.length()>70) absdr.erase(70);
    string hrumpf="Fax h"+fnr+","+Tx[T_avon]+absdr+", T."+tsid+", "+Tx[T_vom]+tbuf;
    string hdatei=hrumpf+".tif";
    string hpfad=empfvz+vtz+hdatei;
    string ziel=empfvz+vtz+hrumpf+".pdf";
    Log(blaus+base+schwarz+" => "+gruen+hdatei+schwarz,1,1);
    // ..., die empfangene Datei in hpfad kopieren ...
    uint kfehler=0;
    string vorsoffice=kopiere(rueck[i],hpfad,&kfehler,1,obverb,oblog);
    if (!kfehler) {
      systemrueck("sudo chown --reference=\""+empfvz+"\" \""+hpfad+"\"",obverb,oblog);
      systemrueck("sudo chmod --reference=\""+empfvz+"\" \""+hpfad+"\"",obverb,oblog);
    } else {
      vorsoffice=rueck[i];
    }
    struct stat entrynd;
    uchar obhpfadda=!lstat(hpfad.c_str(),&entrynd);
    if (obhpfadda) systemrueck("sudo chmod +r \""+hpfad+"\"",obverb,oblog);
    if (obocri) {
      string quelle;
      if (pruefsoffice()) {
        if (systemrueck("cd $HOME; soffice --headless --convert-to pdf --outdir \""+empfvz+"\" \""+vorsoffice+"\"",obverb,oblog)) {
          string stamm,exten;
          getstammext(&vorsoffice,&stamm,&exten);
          quelle=empfvz+vtz+base_name(stamm)+".pdf"; 
        }
      } // if (pruefsoffice()) 
      if (quelle.empty()) quelle=rueck[i];
      if (!pruefocr()) {
        if (!systemrueck(string("ocrmypdf -rcsl ")+(langu=="d"?"deu":"eng")+" \""+quelle+"\" \""+ziel+"\" && chmod +r \""+ziel+"\""
            ,2,oblog)) {
         if (!kfehler) tuloeschen(hpfad,cuser,obverb,oblog);
         hpfad=ziel;
        }
      } // if (pruefocr()) 
    } // if (obocri) 
    memset(&entrynd,0,sizeof entrynd);
    uchar obpdfda=!lstat(ziel.c_str(),&entrynd);
    if (obpdfda) {
      struct stat st0;
      if (!lstat(rueck[i].c_str(),&st0)) {
        struct utimbuf ubuf;
        ubuf.modtime = st0.st_mtime;
        ubuf.actime = st0.st_mtime;
        if (utime(ziel.c_str(),&ubuf)) {
            Log(rots+Tx[T_Fehler_beim_Datumsetzen_von]+ziel+rot+"'"+schwarz,1,1);
        }
      } // if (!lstat(rueck[i].c_str(),&st0)) 
    } // if (obpdfda)
    if (obhpfadda||obpdfda) {
      cmd=string("sudo mv -i \"")+rueck[i]+"\" \""+hempfavz+"\"";
      systemrueck(cmd,obverb,oblog);
      RS zs(My);
      // ... und falls erfolgreich in der Datenbanktabelle inca eintragen
      for(int runde=0;runde<2;runde++) {
        if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
        } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
        RS rins(My); 
        vector<instyp> einf; // fuer alle Datenbankeinfuegungen
        einf.push_back(instyp(My->DBS,"fsize",entrylog.st_size));
        einf.push_back(instyp(My->DBS,"pages",seiten));
        einf.push_back(instyp(My->DBS,"titel",&absdr));
        einf.push_back(instyp(My->DBS,"tsid",&tsid));
        //        einf.push_back(instyp(My->DBS,"callerid",&callerid));
        einf.push_back(instyp(My->DBS,"devname",&devname));
        einf.push_back(instyp(My->DBS,"id",&base));
        einf.push_back(instyp(My->DBS,"transe",&tm));
        rins.insert(tinca,einf, 1,0,ZDB?ZDB:!runde); 
        if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
        if (!rins.fnr) break;
        if (runde==1) {
          Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
          exit(24);
        }
      } // for(int runde=0;runde<2;runde++) 
    } // if (!lstat(hpfad.c_str(),&entrynd)) 
  } // for(size_t i=0;i<rueck.size();i++) 

  // 2) capi
  int erg;
  string cempfavz=spoolcapivz+"/autofaxarch"; // /var/spool/capisuite/empfarch/
  /*
     cppSchluess umst[]={{"filename"},{"call_from"},{"call_to"},{"time"},{"cause"}};
     size_t cs=sizeof umst/sizeof*umst;
   */
  schlArr umst; umst.init(5,"filename","call_from","call_to","time","cause");
  struct stat entryvz;
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
      Log(string("txt: ")+tuerkis+(rueck[i])+schwarz,obverb,oblog);
      string sffname=stamm+".sff";
      struct stat entrysff;
      uchar verschieb=0;
      confdat empfconf(rueck[i],&umst,obverb);
      //    if (cpplies(rueck[i],umst,cs)) KLA
      struct tm tm;
      memset(&tm, 0, sizeof(struct tm));
      strptime(umst[3].wert.c_str(), "%a %b %d %H:%M:%S %Y", &tm);
      strftime(tbuf, sizeof(tbuf), "%d.%m.%Y %H.%M.%S", &tm);
      Log(rots+"   "+umst[0].name+": "+schwarz+umst[0].wert,obverb,oblog);
      Log(rots+"   "+umst[1].name+": "+schwarz+umst[1].wert,obverb,oblog);
      Log(rots+"   "+umst[2].name+": "+schwarz+umst[2].wert,obverb,oblog);
      Log(rots+"   "+umst[3].name+": "+schwarz+tbuf,obverb,oblog);
      Log(rots+"   "+umst[4].name+": "+schwarz+umst[4].wert,obverb,oblog);

      string base=base_name(stamm);
      string fnr=base.substr(4);
      tm.tm_isdst=-1; // sonst wird zufaellig ab und zu eine Stunde abgezogen
      time_t modz=mktime(&tm);
      string getname,bsname;
      getSender(this,umst[1].wert,&getname,&bsname,obverb,oblog);
      getname+=", ";
      getname+=bsname;
      if (getname.length()>187) getname.erase(187);
      if (getname.length()>70) getname.erase(70);
      string crumpf="Fax c"+fnr+","+Tx[T_avon]+getname+", T."+stdfaxnr(umst[1].wert)+","+Tx[T_vom]+tbuf;
      string cdatei=crumpf+".tif";
      string cpfad=empfvz+vtz+cdatei; // Tx[T_Fax_von]+umst[1].wert+Tx[T_an]+umst[2].wert+Tx[T_vom]+tbuf+".tif";
      Log(blaus+stamm+schwarz+" => "+gruen+cdatei+schwarz,1,1);
      // ..., die empfangene Datei in hpfad kopieren ...
      uint vfehler=0;
      if (lstat(sffname.c_str(),&entrysff)) {
        // .txt nach falsche verschieben
        verschieb=1;
      } else {
        uint kfehler=1;
        if (entrysff.st_size) {
          cmd=string("sfftobmp -f -t ")+sffname+" -o \""+cpfad+"\"";
          if ((erg=systemrueck(cmd,obverb,oblog))) {
            verschieb=2;
            cpfad=empfvz+vtz+crumpf+".sff";
            cpfad=kopiere(sffname,cpfad,&kfehler,1,obverb,oblog);
            if (!kfehler) {
              systemrueck("sudo chown --reference=\""+empfvz+"\" \""+cpfad+"\"",obverb,oblog);
              systemrueck("sudo chmod --reference=\""+empfvz+"\" \""+cpfad+"\"",obverb,oblog);
            }
          } else if (obocri) {
            string quelle;
            if (pruefsoffice()) {
              if (systemrueck("cd $HOME; soffice --headless --convert-to pdf --outdir \""+empfvz+"\" \""+cpfad+"\"",obverb,oblog)) {
                quelle=empfvz+vtz+crumpf+".pdf"; 
              }
            } // if (pruefsoffice()) 
            if (quelle.empty()) quelle=cpfad;
            if (!pruefocr()) {
              string ziel=empfvz+vtz+crumpf+".pdf";
              if (!systemrueck(string("ocrmypdf -rcsl ")+(langu=="d"?"deu":"eng")+" \""+quelle+"\" \""+ziel+"\"&&chmod +r \""+ziel+"\""
                   ,2,oblog)) {
                if (!tuloeschen(cpfad,cuser,obverb,oblog))
                cpfad=ziel; // fuer unten
              }
            } // if (pruefocr()) 
          } // if ((erg=systemrueck(cmd,obverb,oblog))) else if (obocri)
        } else {
          // empfangenes Fax mit 0 Bytes, vermutlich abgefangen von anderem System, samt Textdatei nach 'falsche' verschieben
          verschieb=2;
        } // if (entrysff.st_size)
        // wenn sfftobmp funktioniert hat // oder die Datei verschoben wurde
        if (!erg) {
          struct utimbuf ubuf;
          ubuf.modtime = modz;
          ubuf.actime = modz;
          if (utime(cpfad.c_str(),&ubuf)) {
            Log(rots+Tx[T_Fehler_beim_Datumsetzen_von]+cpfad+rot+"'"+schwarz,1,1);
          } else if (!verschieb) {
            dorename(sffname,cempfavz+vtz+cuser+"-"+base+".sff",cuser,&vfehler,obverb,oblog);
            dorename(rueck[i],cempfavz+vtz+cuser+"-"+base_name(rueck[i]),cuser,&vfehler,obverb,oblog);
          } // if (utime(cpfad.c_str(),&ubuf))  else
        } // if (!lstat(cpfad.c_str(),&entrycpfad))
      } // if (lstat(sffname.c_str(),&entrysff)) else  
      if (verschieb) {
//        if (loee) KLA
          string falsche = cfaxuserrcvz+"/falsche";
          pruefverz(falsche,obverb,oblog);
          verschiebe(rueck[i],falsche,cuser,&vfehler,1,obverb,oblog);
          if (verschieb==2) {
            Log(string(Tx[T_Dateien])+rot+stamm+".* "+schwarz+Tx[T_nicht_verarbeitbar_Verschiebe_sie_nach]+rot+"./falsche"+schwarz+".",1,1);
            verschiebe(sffname,falsche,cuser,&vfehler,1,obverb,oblog);
            // so, dass es jeder merkt
            systemrueck("touch '"+empfvz+vtz+Tx[T_nicht_angekommen]+crumpf+".nix'",1,1);
          } // if (verschieb==2) 
//      KLZ // if (loee) 
      } // if (verschieb) 
      RS zs(My);
      for(int runde=0;runde<2;runde++) {
        if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
        } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
        RS rins(My); 
        vector<instyp> einf; // fuer alle Datenbankeinfuegungen
        einf.push_back(instyp(My->DBS,"titel",getname+", "+bsname));
        einf.push_back(instyp(My->DBS,"tsid",&umst[1].wert));
        einf.push_back(instyp(My->DBS,"transe",&modz));
        einf.push_back(instyp(My->DBS,"id",&base));
        einf.push_back(instyp(My->DBS,"fsize",entrysff.st_size));
        einf.push_back(instyp(My->DBS,"csid",&umst[2].wert));
        rins.insert(tinca,einf, 1,0,ZDB?ZDB:!runde); 
        if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
        if (!rins.fnr) break;
        if (runde==1) {
          Log(string(Tx[T_Fehler_af])+drot+ltoan(rins.fnr)+schwarz+Tx[T_bei]+tuerkis+rins.sql+schwarz+": "+blau+rins.fehler+schwarz,1,oblog);
          exit(26);
        }
      } // for(int runde=0;runde<2;runde++) 
    } // for(size_t i=0;i<rueck.size();i++) 
  } // if (!lstat(cfaxuserrcvz.c_str(),&entryvz)) /* /var/spool/capisuite/users/~/received */ 
} // void paramcl::empfarch()

// wird aufgerufen in: main
void paramcl::schlussanzeige()
{
  Log(violetts+Tx[T_schlussanzeige]+schwarz,obverb,oblog);
  tende = clock();
  //  ausg.str(std::string()); ausg.clear();
  //  ausg<<schwarz<<"Pfad: "<<tuerkis<<zufaxenvz<<schwarz<<"; Dateien: "<<tuerkis<<geszahl<<schwarz<<"; Zeit: "<<drot<<setprecision(7)<<fixed<<((tende-tstart)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s";
  if (obverb>0) {
    stringstream ausg;
    ausg<<Tx[T_Zeit_Doppelpunkt]<<drot<<setprecision(7)<<fixed<<((tende-tstart)/CLOCKS_PER_SEC)<<schwarz<<setprecision(0)<<" s";
    Log(ausg.str(),1,oblog); 
  } //   if (obverb>0)
  Log(string(Tx[T_Zahl_der_empfangenen_Faxe])+drot+ltoan(ankzahl)+schwarz,1,oblog);
  Log(string(Tx[T_Zahl_der_ueberpruefen_Datenbankeintraege])+drot+ltoan(dbzahl)+schwarz,1,oblog);
  Log(string(Tx[T_davon_gescheiterte_Faxe])+drot+ltoan(gzahl)+schwarz,1,oblog);
  Log(string(Tx[T_davon_erfolgreiche_Faxe])+drot+ltoan(ezahl)+schwarz,1,oblog);
  Log(string(Tx[T_davon_noch_wartende_Faxe])+drot+ltoan(wzahl)+schwarz,1,oblog);
  Log(string(Tx[T_davon_nicht_in_Warteschlange])+drot+ltoan(fzahl)+schwarz,1,oblog);
  Log(string(Tx[T_Fertig_mit])+blau+meinname+schwarz+" !",obverb,oblog);
} // paramcl::schlussanzeige


// ermittelt fuer eine in ein Zielverzeichnis zu kopierende Datei den dortigen Namen, falls gewuenscht unter Beruecksichtigung 
// dort evtl. schon vorhandener Dateien
// wird aufgerufen von verschiebe (Version 1) und kopiere (Version 1), neuerdateiname, zielname (Version 2)
string zielname(const string& qdatei, const string& zielverz, uchar wieweiterzaehl=0, string* zieldatei=0, int obverb=0, int oblog=0)
{
  //  Log(violetts+Tx[T_zielname]+schwarz,obverb,oblog);
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  struct stat entryziel;
  string dateiname=base_name(qdatei);
  string ziel = zielverz + (zielverz[zielverz.length()-1]==vtz?"":vtzs)+ dateiname;
  Log(string(Tx[T_zielname_erstes_Ziel])+rot+ziel+schwarz+"'",obverb,oblog);
  if (wieweiterzaehl<2) {
    unsigned long ausweich=0;
    string stamm,exten;
    getstammext(&dateiname,&stamm,&exten);
    // wenn von einer vorhandenen Ausweichnummerierung aus weitergezaehlt werden soll (anstatt dateiname_1_1 ...)
    if (wieweiterzaehl) {
      size_t pos = stamm.rfind('_');
      if (pos!=string::npos) {
        string auswstr=stamm.substr(pos+1);
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
      ziel=zielverz + (zielverz[zielverz.length()-1]==vtz?"":vtzs) + dateiname;
    } // for(;1;) 
    if (ausgewichen) Log(string(Tx[T_zielname_Ausweichziel])+rot+ziel+schwarz+"'",obverb,oblog);
  } // if (wieweiterzaehl<2) 
  if (zieldatei) *zieldatei=dateiname;
  return ziel;
} // zielname 

// wird aufgerufen in: verschiebe (Version 2), kopiere (Version 2), neuerdateiname, 
string zielname(const string& qdatei, zielmustercl *zmp, uchar wieweiterzaehl=0, string* zieldatei=0, int obverb=0, int oblog=0)
{
  //  Log(violetts+Tx[T_zielname]+schwarz,obverb,oblog);
  for(zielmustercl *zmakt=zmp;1;zmakt++){
    int reti=regexec(&(zmakt->regex),qdatei.c_str(),0,NULL,0);
    Log(string(Tx[T_Datei])+rot+qdatei+schwarz+Tx[T_entspricht]+(reti?Tx[T_entsprichtnicht]:Tx[T_entsprichtdoch])+
        Tx[T_Muster_Doppelpunkt]+rot+zmakt->holmuster()+schwarz+"'",obverb,oblog);
    if (!reti){
      return zielname(qdatei,zmakt->ziel,wieweiterzaehl,zieldatei,obverb,oblog);
    }
    if (zmakt->obmusterleer()) break;
  }
  return "";
} // zielname


// wird aufgerufen in: verschiebe (Version 1), verschiebe (Version 2), DateienHerricht
void dorename(const string& quelle, const string& ziel, const string& cuser, uint *vfehler, int obverb, int oblog)
{
  Log(string(Tx[T_Verschiebe])+rot+quelle+schwarz+"'\n         -> '"+rot+ziel+schwarz+"'",obverb,oblog);
  for(uchar iru=1;iru<3;iru++) {
    if (rename(quelle.c_str(),ziel.c_str())) {
      if(cuser.empty()) iru++;
      if(iru==1) {
        setfaclggf(dir_name(quelle), wahr, 7, wahr,obverb,oblog);
      } else {
        perror(Tx[T_Fehler_beim_Verschieben]);
        string cmd=string("sudo mv \"")+quelle+"\" \""+ziel+"\"";
        int erg=systemrueck(cmd,obverb,1);
        if (vfehler) *vfehler+=erg;
      } // if(iru) else
    } // if (rename(quelle.c_str(),ziel.c_str())) 
    else break;
  } // for(uchar iru=1;iru>-1;iru--)
} // dorename


// wird aufgerufen von Dateienherricht und untersuchespool; Vorsicht, wenn qdateip ein Verzeichnisname ist!
string verschiebe(const string& qdatei, const string& zielvz, const string& cuser, uint *vfehler, uchar wieweiterzaehl, int obverb,int oblog)
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  string ziel=zielname(qdatei,zielvz,wieweiterzaehl,0,obverb,oblog);
  if (!ziel.empty()) dorename(qdatei,ziel,cuser,vfehler,obverb,oblog);
  return ziel;
} // string verschiebe

// wird aufgerufen von untersuchespool; Vorsicht, wenn qdateip ein Verzeichnisname ist!
void verschiebe(const string& qdatei, zielmustercl *zmp, const string& cuser, uint *vfehler, uchar wieweiterzaehl, int obverb, int oblog) 
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  string ziel=zielname(qdatei,zmp,wieweiterzaehl,0,obverb,oblog);
  if (!ziel.empty()) dorename(qdatei,ziel,cuser,vfehler,obverb,oblog);
} // verschiebe

// wird aufgerufen in Dateienherricht und empfarch und kopiere (andere Definition)
string kopiere(const string& qdatei, const string& zield, uint *kfehler, uchar wieweiterzaehl, int obverb, int oblog)
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  string dir=dir_name(zield);
  string base=base_name(zield);
  string ziel;
  int fehler=0;
  if (!base.empty() && !dir.empty()) {
    ziel=zielname(base,dir,wieweiterzaehl,0, obverb,oblog);
    Log(string(Tx[T_Kopiere_Doppelpunkt])+rot+qdatei+schwarz+"'\n         -> '"+rot+ziel+schwarz+"'",obverb,oblog);
    string cmd=string("sudo cp -a \"")+qdatei+"\" \""+ziel+"\"";
    fehler= systemrueck(cmd,obverb>1,oblog);
    if (fehler) {
     kfehler+=fehler;
     Log(rots+Tx[T_Fehler_beim_Kopieren]+Tx[T_Dateiname]+blau+zield+schwarz,1,1);
    }
  } else {
    Log(rots+Tx[T_Fehler_beim_Kopieren]+Tx[T_Dateiname]+blau+zield+schwarz+Tx[T_schlechtgeformt],1,1);
  }
  return ziel;
} // string kopiere

// wird aufgerufen in Dateienherricht
string kopiere(const string& qdatei, zielmustercl *zmp, uint *kfehler, uchar wieweiterzaehl, int obverb, int oblog) 
{
  // wieweiterzaehl: 0: auf *_1_1 nach *_1, 1: auf *_2 nach *_1, 2: gar nicht
  string ziel=zielname(qdatei,zmp,wieweiterzaehl,0, obverb,oblog);
  return kopiere(qdatei, ziel, kfehler, wieweiterzaehl,obverb,oblog);
} // string kopiere

// wird aufgerufen in pruefhyla
// hylafax konfigurieren 
void hfaxsetup(paramcl *pmp,int obverb=0, int oblog=0)
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
            }
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
    int erg __attribute__((unused));
    pruefplatte();
    if (!systemrueck("sudo "+faxsu+" -nointeractive"+(obverb?" -verbose":""),obverb,oblog,0,2)) {
     pmp->shfaxd->stop(obverb,oblog,1);
     pmp->sfaxq->stop(obverb,oblog,1);
     servc::daemon_reload();
    } // if (!systemrueck("sudo "+faxsu+" -nointeractive"+(obverb?" -verbose":""),obverb,oblog,0,2)) 
    /*
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

  struct stat entryfaxgt;
  pmp->faxgtpfad.clear();
  //  pmp->faxgtpfad="/usr/lib/fax/faxgetty";
  //    pmp->faxgtpfad="/usr/sbin/faxgetty";
  obprogda("faxgetty",obverb,oblog,&pmp->faxgtpfad);
  if (pmp->faxgtpfad.empty() || lstat(pmp->faxgtpfad.c_str(),&entryfaxgt)) {
    svec rueckf;
    pmp->faxgtpfad.clear();
    systemrueck("sudo find /usr/lib/fax /usr/sbin /usr/bin /root/bin /sbin -perm /111 -name faxgetty",obverb-1,oblog,&rueckf);
    if (rueckf.size()) 
      pmp->faxgtpfad=rueckf[0];
  }
  // violett<<"pmp->faxgtpfad 4: "<<pmp->faxgtpfad<<schwarz<<endl;
} // hfaxsetup

// wird aufgerufen in: pruefhyla
void hconfig(paramcl *pmp,int obverb=0, int oblog=0)
{
  Log(violetts+"hconfig()"+schwarz,obverb,oblog);
  string confd=pmp->varsphylavz+"/etc/config";
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
    {
      struct stat entryfaxsd;
      svec rueckf;
      string faxsdpfad=pmp->varsphylavz+"/bin/faxsend";
      if (lstat(faxsdpfad.c_str(),&entryfaxsd)) {
        faxsdpfad="/usr/sbin/faxsend";
        if (lstat(faxsdpfad.c_str(),&entryfaxsd)) {
          faxsdpfad.clear();
          systemrueck("sudo find /usr /root/bin /sbin -perm /111 -name faxsend",obverb-1,oblog,&rueckf);
          if (rueckf.size()) 
            faxsdpfad=rueckf[0];
        }
      }
      if (!faxsdpfad.empty())
        conf<<"SendFaxCmd:   "<<faxsdpfad<<endl;
    }
    conf<<"Use2D:      \"no\""<<endl;
  } else {
    cerr<<"hconfig(): "<<Tx[T_Datei]<<confd<<Tx[T_nichtbeschreibbar]<<endl;
    exit(28);
  }
  Log(violetts+Tx[T_Ende]+"hconfig()"+schwarz,obverb,oblog);
} // void hconfig(paramcl *pmp,int obverb=0, int oblog=0)

void paramcl::setzmodconfd()
{
  modconfdat=this->varsphylavz+"/etc/config"+"."+this->hmodem; 
}

void paramcl::hliesconf()
{
  schlArr hyalt; hyalt.init(7,"CountryCode","AreaCode","FAXNumber","LongDistancePrefix","InternationalPrefix","RingsBeforeAnswer","LocalIdentifier");
  setzmodconfd();
  struct stat mstat;
  if (lstat(modconfdat.c_str(),&mstat)) {
    hylazukonf=1;
  } else {
    confdat haltconf(modconfdat,&hyalt,obverb,':');
    if (hyalt.schl[0].wert!=countrycode || hyalt.schl[1].wert!=citycode || hyalt.schl[2].wert!=countrycode+"."+citycode+"."+msn 
        || hyalt.schl[3].wert!=LongDistancePrefix || hyalt.schl[4].wert!=InternationalPrefix 
        || hyalt.schl[5].wert!=hklingelzahl || hyalt.schl[6].wert!=LocalIdentifier
       ) {
      hylazukonf=1;
    } // if (hyalt.shl[0].wert ...
  } //   if (lstat(modconfdat.c_str(),&mstat)) else
  // hyalt.ausgeb();
}

// wird aufgerufen in: pruefhyla (2x)
// Modem konfigurieren
void paramcl::hconfigtty()
{
  Log(violetts+"hconfigtty()"+schwarz,obverb,oblog);
  setzmodconfd();
  systemrueck("test -f '"+modconfdat+"' && test -f '"+modconfdat+".bak' || sudo cp -a '"+modconfdat+"' '"+modconfdat+".bak'",obverb,oblog);
  // <<rot<<modconfdat<<schwarz<<endl;
  // z.B. /var/spool/hylafax/etc/config.ttyACM0
  mdatei hci(modconfdat,ios::out);
  if (hci.is_open()) {
    // <<rot<<" ist offen"<<schwarz<<endl;
    time_t tim=time(0);
    struct tm *tm=localtime(&tim);
    char buf[80];
    strftime(buf, sizeof(buf), "%d.%m.%y %H:%M:%S", tm);
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
    hci<<"CIDNumber: NMBR="<<endl;
    hci<<"CIDName:   NAME="<<endl;
    hci<<"SpeakerVolume:    off"<<endl;
    hci<<"GettyArgs:    \"-h %l dx_%s\""<<endl;
    hci<<"LocalIdentifier:  "<<this->LocalIdentifier<<endl;
    hci<<"LogFacility:    daemon"<<endl;
    // #ifdef obhp
    struct stat Lstat;
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
    hci<<" die folgenden sind aus dem Internet"<<endl;
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
  Log(violetts+Tx[T_Ende]+"hconfigtty()"+schwarz,obverb,oblog);
} // void hconfigtty(paramcl *pmp,int obverb=0, int oblog=0)

// wird aufgerufen in: pruefcapi
// lieftert 0, wenn die Dienstdatei gespeichert werden konnte (erg), nicht wenn der Dienst laeuft (csfehler)
int paramcl::cservice()
{
  Log(violetts+"cservice()"+schwarz,this->obverb,this->oblog);
  int csfehler=0;
  int erg;
  string cspfad;
  if (obprogda("capisuite",obverb,oblog,&cspfad)) {
    scapisuite->stop(obverb,oblog,1); 
    erg=systemrueck(/*"sudo sh -c 'systemctl stop capisuite; pkill capisuite >/dev/null 2>&1; pkill -9 capisuite >/dev/null 2>&1; "*/
        "cd /etc/init.d"
        " && [ $(find . -maxdepth 1 -name \"capisuite\" 2>/dev/null | wc -l) -ne 0 ]"
        " && { mkdir -p /etc/ausrangiert && mv -f /etc/init.d/capisuite /etc/ausrangiert; } || true'",obverb,oblog);
    // entweder Type=forking oder Parameter -d weglassen; was besser ist, weiss ich nicht
    csfehler+=!scapisuite->spruef("Capisuite",0,meinname,cspfad/*+" -d"*/,"","","",obverb,oblog);
    if (obverb) Log("csfehler: "+gruens+ltoan(csfehler)+schwarz,obverb,oblog);
    //    return csfehler;
  } // if (obprogda("capisuite",obverb,oblog,&cspfad)) 
  return erg;
} // int paramcl::cservice()


// wird aufgerufen in: pruefhyla
// Dienste erstellen
int paramcl::hservice_faxq_hfaxd()
{
  int hylafehler=0;
  Log(violetts+"hservice_faxq_hfaxd()"+schwarz,this->obverb,this->oblog);
  string faxqpfad,hfaxdpfad;
  obprogda("hfaxd",obverb,oblog,&hfaxdpfad);
  hylafehler+=!this->shfaxd->spruef("HFaxd",0/*1*/,meinname,hfaxdpfad+" -d -i hylafax"/* -s 444*/,
      this->varsphylavz+"/etc/setup.cache", "", "", this->obverb,this->oblog);
  this->shfaxd->machfit(obverb,oblog);
  obprogda("faxq",obverb,oblog,&faxqpfad);
  hylafehler+=!this->sfaxq->spruef("Faxq",0/*1*/,meinname,faxqpfad+" -D",
      this->varsphylavz+"/etc/setup.cache", this->shfaxd->sname+".service", "",this->obverb,this->oblog);
  return hylafehler;
} // void hservice_faxq_hfaxd()

void paramcl::hylasv1(int obverb,int oblog)
{
  if (!this->sfaxgetty) this->sfaxgetty=new servc("hylafax-faxgetty-"+this->hmodem,"faxgetty");
} // void paramcl::hylasv1(obverb,oblog)

void paramcl::hylasv2(hyinst hyinstart,int obverb,int oblog)
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
} // void paramcl::hylasv2(obverb,oblog)

/*
// wird aufgerufen in: pruefhyla (1x)
int paramcl::hservice_faxgetty()
KLA
  Log(violetts+"hservice_faxgetty()"+schwarz,obverb,oblog);
  return !this->sfaxgetty->spruef(("HylaFAX faxgetty for ")+this->hmodem,0, meinname,this->faxgtpfad+" "+this->hmodem,"","","",this->obverb,this->oblog);
  // /etc/inittab werde von systemd nicht gelesen
  *//*,"cat /etc/inittab 2>/dev/null | grep -E '^[^#].*respawn.*faxgetty' >/dev/null 2>&1"*//*

KLZ // void hservice_faxgetty()
*/


// wird aufgerufen in main
int paramcl::pruefhyla()
{
  Log(violetts+Tx[T_pruefhyla]+schwarz,obverb,oblog);
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
    Log(string(Tx[T_Baudratevon])+blau+"/dev/"+this->hmodem+schwarz+Tx[T_mit_af]+rot+brs+schwarz+Tx[T_zugeringVerwendeHylafaxnicht],1,1);
    //    return 1;
  } else {
    Log(string("Modem '")+blau+"/dev/"+this->hmodem+schwarz+Tx[T_mit_Baudrate]+gruen+brs+schwarz+Tx[T_wird_verwendet],obverb,oblog);
  } //   if (br<=0) else
  if (1) {
    hylasv1(obverb,oblog);
    for(unsigned versuch=0;versuch<3;versuch++) {
      // 1) Dienst(e) hylafax, (hylafax-)hfaxd, (hylafax-)faxq identifizieren
      // pruefen, ob hylafax.service laeuft
      Log(Tx[T_Pruefe_ob_Hylafax_gestartet],-1,oblog);
      const char* const c_hfs="hylafax";
      const char* const c_hfc="hylafax-client";
      const char* const c_hfps="hylafax+";
      const char* const c_hfpc="hylafax+-client";
      char *hfr, *hfcr, *hff, *hfcf; // hylafax richtig, hylafax client richtig, hylafax falsch, hylafax client falsch
      hyinst hyinstart; // hyla source, hyla Paket, hylaplus Paket
      string hfftext;
      hylalaeuftnicht=1;
      hylafehlt=1;
      lsysen system=lsys.getsys(obverb,oblog);
      if (system==deb /* || system==fed*/) {
        hyinstart=hysrc;
      } else {
        hyinstart=hyppk;
      } 
      hylasv2(hyinstart,obverb,oblog);
      if (hyinstart==hysrc || hyinstart==hyppk) {
        hfr=(char*)c_hfps; hfcr=(char*)c_hfpc; hff=(char*)c_hfs; hfcf=(char*)c_hfc;
        hfftext=Tx[T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen];
        // => hyinstart==hypak
      } else {
        hfr=(char*)c_hfs; hfcr=(char*)c_hfc; hff=(char*)c_hfps; hfcf=(char*)c_hfpc;
        hfftext=Tx[T_Hylafaxplus_entdeckt_muss_ich_loeschen];
      } // if (hyinstart==hysrc || hyinstart==hyppk) else
      // 2) deren Existenz, Betrieb und ggf. Startbarkeit pruefen
      // wenn die richtigen Dienste laufen, dann nichts weiter ueberpruefen ..
      if ((this->sfaxq->obslaeuft(obverb-1,oblog) && this->shfaxd->obslaeuft(obverb-1,oblog)) /*|| this->shylafaxd->obslaeuft(obverb-1,oblog)*/) {
        Log(Tx[T_Hylafax_laeuft],obverb,oblog);
        hylalaeuftnicht=0;
        hylafehlt=0;
      } else if (versuch>1) {
        exit(32);
      } 
      if (hylafehlt) {
        // falls nein, dann schauen, ob startbar
        if (sfaxq->machfit(obverb-1,oblog) && shfaxd->machfit(obverb-1,oblog) && sfaxgetty->machfit(obverb-1,oblog)) {
          hylafehlt=0;
          hylalaeuftnicht=0;
        }
        // <<"hylafehlt: "<<(int)hylafehlt<<endl;
      } else {
        // <<"hylafehlt nicht!"<<endl;
      }

      // <<violett <<"Versuch: "<<(int)versuch<<" hylafehlt: "<<(int)hylafehlt<<" hylalaeuftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
      if (hylafehlt) {
        // 3) ggf. neu installieren
        Log(rots+Tx[T_Muss_Hylafax_installieren]+schwarz,1,1);
        // a) von der source
        linst.doinst("ghostscript",obverb+1,oblog,"gs");
        linst.doinst("tiff",obverb+1,oblog,"tiff2ps");
        linst.doinst("tiff",obverb+1,oblog,"fax2ps");
        linst.doinst("sendmail",obverb+1,oblog,"sendmail");
        if (obverb) Log(blaus+"hyinstart: "+schwarz+ltoan(hyinstart),obverb,oblog);
        if (hyinstart==hysrc) {
            Log(rots+Tx[T_ueber_den_Quellcode]+schwarz,1,1);
            systemrueck("sudo wget -O hylafax+ https://sourceforge.net/projects/hylafax/files/latest",obverb,oblog);
            systemrueck("sudo tar xvf hylafax+",obverb,oblog);
            // 2>/dev/null wegen tar:Schreibfehler (=> Schreibversuch durch von head geschlossene pipe)
            systemrueck("sudo sh -c 'cd $(sudo tar --list -f hylafax+ 2>/dev/null | head -n 1) && "
                "./configure --nointeractive && echo $? = Ergebnis nach configure && "
                "sed -i.bak \"s.PAGESIZE='\\''North American Letter'\\''.PAGESIZE='\\''ISO A4'\\''.g;"
                "s.PATH_GETTY='\\''\\.*'\\''.PATH_GETTY='\\''"
                "$(grep LIBEXEC defs | cut -d'\\''='\\'' -f2 | sed '\\''s/^[[:space:]]*//;s/[[:space:]]*$//'\\'')/faxgetty'\\''.g\" config.cache"
                " && echo $? = Ergebnis nach sed"
                " && sudo make && echo $? = Ergebnis nach make && sudo make install && echo $? = Ergebnis nach make install"
                " && sudo systemctl daemon-reload && sudo systemctl stop hylafax 2>/dev/null"
                " && test -f /etc/init.d/hylafax && { mkdir -p /etc/ausrangiert && sudo mv -f /etc/init.d/hylafax /etc/ausrangiert; }"
                " && sudo pkill hfaxd faxq >/dev/null 2>&1 && sudo faxsetup -nointeractive >/dev/null 2>&1 "
                " && echo $? = Ergebnis nach faxsetup -nointeractive"
                " && sudo pkill hfaxd faxq >/dev/null 2>&1 " // wird von faxset -nointeractive gestartet und kolligiert mit dem service
                " && sudo systemctl daemon-reload && echo $? = Ergebnis nach sudo systemctl daemon-reload"
                "'"
                ,2,oblog);
            // hservice_faxgetty();
            // hservice_faxq_hfaxd();
        } else {
          Log(rots+Tx[T_ueber_das_Installationspaket]+schwarz,1,1);
          // b) mit dem Installationspaket
          if (!linst.obfehlt(hff) || !linst.obfehlt(hfcf)) {
            Log(hfftext,-1,1);
            linst.douninst(string(hff)+" "+hfcf,obverb,oblog);
            falscheshyla=1;
          }
          // <<"hfr: "<<violett<<hfr<<schwarz<<" hfcr: "<<violett<<hfcr<<schwarz<<" obverb: "<<(int)obverb<<endl;
          hylafehlt=linst.obfehlt(hfr,obverb,oblog) || linst.obfehlt(hfcr,obverb,oblog) || 
            !obprogda("faxq",obverb,oblog) || !obprogda("hfaxd",obverb,oblog) || !obprogda("faxgetty",obverb,oblog);
          string vstring=ltoan(versuch);
          Log(gruens+Tx[T_hylafehlt]+schwarz+ltoan(hylafehlt)+gruen+Txk[T_Versuch]+schwarz+vstring,obverb,oblog);
          // b1) falsches Hylafax loeschen
          if (hylafehlt) {
            if (falscheshyla) {
              Log(rots+Tx[T_Muss_falsches_hylafax_loeschen]+schwarz,1,1);
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
                      "faxsetup.linux faxstate faxwatch probemodem rchylafax* recvstats tagtest tiffcheck tsitest  typetest xferfaxstats "
                      "faxsetup.bsdi faxsetup.iri faxgetty faxsend hfaxd hylafax lockname ondelay pagesend textfmt;'",-2,oblog);
                  systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/fax",-2,oblog,0,1);
                  systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/share/hylafax",-2,oblog,0,1);
                  systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/fax",-2,oblog,0,1);
                  systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/hylafax",-2,oblog,0,1);
                  systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/libfax*",-2,oblog,0,1);
                  systemrueck("sudo sh -c 'rm -rf /usr/"+local+"/lib/libhylafax*",-2,oblog,0,1);
                }
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
            return 1;
          }
          // falls oben hylafax neu installiert wurde und zuvor eine hylafax-Installation nach Gebrauch geloescht worden war,
          // dann die alten Eintraege (xferfaxlog.rpmsave) wieder aktivieren
          struct stat entryxfer, entryxfer0;
          memset(&entryxfer0,0,sizeof entryxfer0);
          string d0=xferfaxlog+".rpmsave";
          if (!lstat(xferfaxlog.c_str(),&entryxfer)) {
            if (entryxfer.st_size<10) { // wenn neu
              if (!lstat(d0.c_str(),&entryxfer0) && entryxfer0.st_size>10) {
                systemrueck("sudo cp -a "+d0+" "+xferfaxlog,obverb,oblog);
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
          if (hyinstart==hyppk || hyinstart==hysrc)
            systemrueck("sudo chown uucp:uucp -R "+this->varsphylavz,obverb,oblog);
          else
            systemrueck("sudo chown fax:uucp -R "+this->varsphylavz,obverb,oblog);
        } // if (obprogda("faxsend",obverb,oblog))
        /*
           Log(string(Tx[T_StarteHylafax]),1,oblog);
        //      if (hyinstart==hypak) hylalaeuftnicht=hservice_faxq_hfaxd();
        <<"hylafehlt: "<<(int)hylafehlt<<endl;
        if (0) {
        if (hylafehlt || versuch) {
        //        Log(string(Tx[(T_)T_Installation_von_Hylafax_nicht_feststellbar_versuche_es_zu_installieren]),-2,1);

        //        string cmd("which zypper 2>/dev/null && zypper -n in hylafax hylafax-client || "
        //        "KLA which apt-get 2>/dev/null && apt-get --assume-yes install hylafax-server hylafax-client; KLZ; systemctl daemon-reload; ");
        //        hylafehlt=systemrueck(cmd,1+obverb,oblog,0,wahr,wahr,Tx[T_hylafax_faxmodem_nicht_gefunden_Versuche_es_zu_installieren_mit]); 

        }
        // falls ja, dann starten (falls erst installiert werden muss, dann bei versuch==1
        } // if (0)
         */
      } // if (hylafehlt)
      int fglaeuftnicht=0;
      if (1) {
        for (uchar iru=0;iru<3;iru++) {
          if ((fglaeuftnicht=!this->sfaxgetty->obslaeuft(obverb,oblog))) {
            // falls nein, dann schauen, ob startbar
            if (sfaxgetty->machfit(obverb,oblog)) fglaeuftnicht=0;
          }
          // <<rot<<" fglaueftnicht: "<<fglaeuftnicht<<", hmodem: "<<hmodem<<schwarz<<endl;
          modemlaeuftnicht=systemrueck(("sudo faxstat | grep ")+this->hmodem+" 2>&1",obverb,oblog) + fglaeuftnicht;
          //        if (!modemlaeuftnicht) break;
          //  <<rot<<" hyinstart: "<<(int)hyinstart<<", modemlaeuftnicht: "<<(int)modemlaeuftnicht<<schwarz<<endl;
          //  <<rot<<" hylalaueftnicht: "<<(int)hylalaeuftnicht<<schwarz<<endl;
          if (hyinstart==hypak || hyinstart==hysrc) {
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
             KLZ // if (!systemrueck(string("sudo systemctl stop ")+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog)) 
           */
          if (sfaxgetty->startundenable(obverb,oblog) &&  shfaxd->startundenable(obverb,oblog) && sfaxq->startundenable(obverb,oblog)) {
            this->hylazukonf=0;
          } // if (!systemrueck(string("sudo systemctl start ")+this->sfaxgetty->sname+" "+this->shfaxd->sname+" "+this->sfaxq->sname,obverb,oblog)) 
        } // if (this->hylazukonf && !frischkonfiguriert) 
        // systemrueck("grep -rl 'faxcron\\|faxqclean' /etc/cron* | /usr/bin/xargs ls -l;",obverb,oblog); 
        // // in hylafax: /etc/cron.daily/suse.de-faxcron, 
      } // if (1)
      //     break; // zu Testzwecken
      if (hylalaeuftnicht || modemlaeuftnicht) {
        // hier Fehler: nach einem Versuch darf 
        if (versuch) {
          if (this->konfobhyla) this->hylazukonf=1;
        }
        if (versuch>1) {
          Log(string(Tx[T_hylafaxspringtnichtan]),1,1);
          this->obhyla=0;
          return 1;
        }
      } else {
        break;
      } // if (hylalaeuftnicht || modemlaeuftnicht) 
    } // for(unsigned versuch=0;versuch<2;versuch++)
    // Archivierung ggf. aktivieren
    struct stat hfstat;
    if (!lstat("/etc/cron.hourly/hylafax",&hfstat)) {
      systemrueck("! sudo grep -q 'faxqclean *$' /etc/cron.hourly/hylafax || "
          "sudo sed -i.bak 's/faxqclean *$/faxqclean -a -A/g' /etc/cron.hourly/hylafax", obverb,oblog);
    }
  } // if (1)
  Log(violetts+Tx[T_Ende]+" "+Tx[T_pruefhyla]+schwarz,obverb,oblog);
  return 0;
} // int paramcl::pruefhyla()

/*
long GetFileSize(string filename)
{
  struct stat stat_buf;
  int rc = stat(filename.c_str(), &stat_buf);
  return rc ? -1 : stat_buf.st_size;
} // GetFileSize

void clear_kb(void) // statt fflush(stdin) nach getchar
{
  char junk[255];
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
  struct stat entrybuf;
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
  uchar obda[]={0,0}, obeinsfehlt=0;
  mdatei blacki(blackd,ios::in);
  if (blacki.is_open()) {
    string zeile;
    while(getline(blacki,zeile)) {
      for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++) {
        if (zeile.find(vgl[i])!=string::npos) obda[i]=1;
      }
    }
    blacki.close();
    for(unsigned i=0;i<sizeof vgl/sizeof *vgl;i++) {
      if (!obda[i]) {obeinsfehlt=1;break;}
    }
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
void pruefmodcron(int obverb, int oblog)
{
  Log(violetts+Tx[T_pruefmodcron]+schwarz,obverb?obverb-1:0,oblog);
  const string mp="@reboot /sbin/modprobe ";
  const string mps[]={mp+"capi",mp+"fcpci"};
  setztmpc(obverb, oblog);
  for(uchar ru=0;ru<sizeof mps/sizeof *mps;ru++) {
    svec rueck;
    systemrueck("bash -c 'grep \""+mps[ru]+"\" -q <(sudo crontab -l 2>/dev/null)' || "
        "(sudo crontab -l 2>/dev/null >"+tmpc+"; echo \""+mps[ru]+"\">>"+tmpc+"; sudo crontab "+tmpc+")",obverb,oblog,&rueck);
    for(size_t znr=0;znr<rueck.size();znr++) {
      Log(rueck[znr],1+obverb,oblog);
    }
  }
} // void pruefmodcron(int obverb, int oblog)

int paramcl::pruefinstv()
{
  if (instverz.empty()) instverz=string(getenv("HOME"))+'/'+meinname;
  return pruefverz(instverz,obverb,oblog);
} // void paramcl::pruefinstv()

void paramcl::holvongithub(string datei)
{
  if (!pruefinstv()) {
    svec csrueck;
    systemrueck("find \""+instverz+"\" -mtime -1 -name "+datei+".tar.gz",obverb,oblog,&csrueck);
    if (!csrueck.size()) {
      //systemrueck("sh -c 'cd "+instverz+"; wget https://github.com/larsimmisch/capisuite/archive/master.tar.gz -O capisuite.tar.gz'",
      systemrueck("sh -c 'cd \""+instverz+"\";T="+datei+".tar.gz; wget https://github.com/libelle17/"+datei+"/archive/master.tar.gz -O $T'", 
          obverb,oblog);
    } //     if (!csrueck.size())
  } // if (!pruefinstv())
} // void paramcl::holvongithub(string datei)

int paramcl::kompilbase(const string& was, const string& endg)
{
  if (!pruefinstv()) {
    return systemrueck("sh -c 'P="+was+";T=$P.tar."+endg+";M=$P-master;cd \""+instverz+"\" && tar xpvf $T && rm -rf $P; mv $M $P'",obverb,oblog);
  } //   if (!pruefinstv())
  return 1;
} // int paramcl::kompilbase(string& was,string& endg)

int paramcl::kompiliere(const string& was,const string& endg, const string& vorcfg, const string& cfgbismake)
{
  if (!kompilbase(was,endg)) {
    return systemrueck("sh -c 'cd \""+instverz+vtz+was+"\" && "+vorcfg+" && ./configure "+cfgbismake+" make && sudo make install '",obverb,oblog);
  } //    if (!kompilbase(was,endg))
  return 1;
} // int paramcl::kompiliere(string was,string endg,string nachtar, string vorcfg,string cfgbismake)

// wird aufgerufen in: pruefcapi(), anhalten()
void paramcl::capisv(int obverb,int oblog)
{
  if (!scapisuite) scapisuite=new servc("","capisuite");
} // void paramcl::capisv(obverb,oblog)

void paramcl::pruefsfftobmp()
{
  Log(violetts+Tx[T_pruefsfftobmp]+schwarz,obverb,oblog);
  lsysen system=lsys.getsys(obverb,oblog);
  if (system==fed) {
    // P=hylafax_copy; T=$P.tar.gz; wget https://github.com/libelle17/$P/archive/master.tar.gz -O $T && tar xpvf $T && rm -f $T && mv ${P}-master/* . && rmdir ${P}-master
    if (!obprogda("sfftobmp",obverb,oblog)) {
      string befehl = "cd "+instverz+
        " && { P=jpegsrc_copy; T=$P.tar.gz; wget https://github.com/libelle17/$P/archive/master.tar.gz -O $T && tar xpvf $T && rm -f $T && mv ${P}-master $P && cd $P && ./configure && make >/dev/null 2>&1 && sudo make install; } ";
      if (!systemrueck(befehl,obverb,oblog)) {
        if (!linst.doggfinst("boost",obverb,oblog) && !linst.doggfinst("boost-devel",obverb,oblog)) {
          befehl= "cd "+instverz+
            " && { sudo grep '/usr/local/lib' /etc/ld.so.conf || "
            "{ sudo sh -c \"echo '/usr/local/lib' >> /etc/ld.so.conf\"; sudo ldconfig; } } "
            " && { P=sfftobmp_copy; T=$P.tar.gz; wget https://github.com/libelle17/$P/archive/master.tar.gz -O $T && tar xpvf $T && rm -f $T"
            " && mv ${P}-master ${P}; } "
            " && cd ${P} "
            //                    " && unzip sfftobmp_3_1_src.zip >/dev/null && cd sfftobmp3.1 "
            " && sed -i.bak -e 's/\\(char \\*shortopts.*\\)/const \\1/;s/m_vFiles.push_back( fs::path(m_argv\\[n\\].*/m_vFiles.push_back( fs::path(string(m_argv[n])\\/*, fs::native*\\/) );/' src/cmdline.cpp"
            //                      " && sed -i.bak -e 's/-${am__api_version}//g' aclocal.m4 "
            //                      " && sed -i.bak -e 's/-${am__api_version}//g' configure "
            " && sed -i.bak -e 's/\\(-lboost_filesystem\\)/-lboost_system \\1/g' src/Makefile.in "
            " && ./configure && make && sudo make install "
            ;
          //                      <<gruen<<befehl<<schwarz<<endl;
          systemrueck(befehl,obverb,oblog);
        } // if (!linst.doggfinst("boost",obverb,oblog) && !linst.doggfinst("boost-devel",obverb,oblog)) 
      } // if (!systemrueck(befehl,obverb,oblog)) 
    } // if (!obprogda("sfftobmp",obverb,oblog)) 
  } else {
    linst.doggfinst("sfftobmp",obverb+1,oblog);
  } // if (system==fed) else
} // pruefsfftobmp

// wird aufgerufen in: untersuchespool, main
int paramcl::pruefcapi()
{
  Log(violetts+Tx[T_pruefcapi]+schwarz,obverb,oblog);
  static uchar capiloggekuerzt=0;
  static uchar capischonerfolgreichinstalliert=0;
  int capilaeuft=0;
  unsigned versuch=0;
  capisv(obverb,oblog);
  for(;versuch<2;versuch++) {
    // capi4linux muss zum Laufen der Capisuite installiert sein
    // fuer fcpci muss in driver.c eingefuegt werden:
    // #if !defined(IRQF_DISABLED)
    // #  define IRQF_DISABLED 0x00
    // #endif
    //    capilaeuft=(PIDausName("capisuite")>=0);
    capilaeuft = this->scapisuite->machfit(obverb-1,oblog,wahr);
    Log(violetts+Tx[T_capilaeuft]+schwarz+ltoan(capilaeuft)+schwarz,obverb,oblog);
    if (capilaeuft) {
     capischonerfolgreichinstalliert=1;
    } else {
      //      pid_t pid = GetPIDbyName("capisuite") ; // If -1 = not found, if -2 = proc fs access error
      uchar fcpcida=0, capida=0, capidrvda=0;
      pruefinstv();
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
        Log("Lade Capi-Module ...",-1,0);
        systemrueck("sudo modprobe -rf avmfritz mISDNipac hisax_fcpcipnp hisax_isac hisax",obverb,oblog,0,1);
        for(uchar ivers=0;ivers<2;ivers++) {
          if (!fcpcida)
          if (systemrueck("sudo modprobe -v fcpci",obverb-1,oblog)) {
            if (ivers) {
              Log(rots+Tx[T_KannFcpciNInstVerwCapiNicht]+schwarz,1,1);
              return 1;
            } // if (ivers)
            utsname unbuf;
            uname(&unbuf);
            Log(string(Tx[T_Kernelversion])+blau+unbuf.release+schwarz,obverb,oblog);
            struct stat entryfc;
            string fcpciko = string("/lib/modules/")+unbuf.release+"/kernel/extras/fcpci.ko";
            if (lstat(fcpciko.c_str(), &entryfc)) {
              Log(string(Tx[T_Datei])+blau+fcpciko+schwarz+Tx[T_nichtgefFcpciMfdKinstallierwerden],obverb,1);
              //              systemrueck("which zypper 2>/dev/null && zypper -n in kernel-source || "
              //                  "{ which apt-get 2>/dev/null && apt-get --assume-yes install linux-source; }", 1+obverb,oblog);
              linst.doinst("kernel-source",1+obverb,oblog);
/*              
              const string qvz="/usr/src";
              const string versi="fcpci-3.10.0";
              const string srcf=string("fritz-")+versi+".tar.bz2";
              pruefverz(qvz,obverb,oblog,0);
              struct stat entrysrc;
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
              struct utsname unameD;
              uname(&unameD);
              string rel=unameD.release;
              size_t p1=rel.find('.');
              if (p1!=string::npos) {
               size_t p2=rel.find('.',p1+1);
               if (p2!=string::npos) {
                float vers=atof(rel.substr(0,p2).c_str());
                if (vers>0 && vers<3.14) {
                 if (obprogda("gcc",obverb,oblog,&gccpfad) && obprogda("g++",obverb,oblog,&gpppfad)) {
                 obdown=1;
                 systemrueck("sudo cp \""+gccpfad+"\" \""+gccpfad+".bak\" && "
                             "sudo cp \""+gpppfad+"\" \""+gpppfad+".bak\"",obverb,oblog);
                 linst.doinst("gcc-4.8",1+obverb,oblog);
                 linst.doinst("g++-4.8",1+obverb,oblog);
                 systemrueck("sudo ln -sf \""+gccpfad+"-4.8\" \""+gccpfad+"\" && "
                             "sudo ln -sf \""+gpppfad+"-4.8\" \""+gpppfad+"\"",obverb,oblog);
                 } // if (!obprogda("gcc",obverb,oblog,&gccpfad) && !obprogda("g++",obverb,oblog,&gpppfad)) 
                } // if (vers>0 && vers<3.14) 
               } // if (p2!=string::npos) 
              } // if (p1!=string::npos) 
              systemrueck("ls -l /lib/modules/$(uname -r)/build 2>/dev/null || "
                  "{ NEU=$(find /lib/modules -type l -name build -print0|/usr/bin/xargs -0 -r ls -l --time-style=full-iso|"
                  "sort -nk6,7|head -n1|cut -d' ' -f9); test -h $NEU && sudo cp -a $NEU /lib/modules/$(uname -r)/build; }",obverb,oblog);
              string proj="fcpci_copy";
              string srcvz=instverz+vtz+proj+".tar.gz";
              holvongithub(proj);
              const string vorcfg="sudo test -f driver.c.bak || sed -i.bak \"/request_irq/i#if !defined(IRQF_DISABLED)\\n"
                  "# define IRQF_DISABLED 0x00\\n#endif\" driver.c;"
                  "sudo sed -e '\\''/#include <linux\\/isdn\\/capilli.h>/a #include <linux\\/utsname.h>'\\'' "
                  "-e '\\''/NOTE(\"(%s built on %s at %s)\\\\n\", TARGET, __DATE__, __TIME__);/"
                  "c NOTE(\"(%s built on release %s, version %s)\\\\n\", TARGET, utsname()->release, utsname()->version);'\\'' "
                  "main.c >main_neu.c;mv -n main.c main.c.bak;mv -n main_neu.c main.c;"
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
        
        if (systemrueck("sudo modprobe capi",obverb,oblog)) {
          if (system==fed) {
            svec vrueck1,vrueck2;
            string v1,v2;
            systemrueck("sudo ls /boot/vmlinuz-* -r|head -n 1|cut -d- -f2,3,4,5",obverb,oblog,&vrueck1);
            if (vrueck1.size()) v1=vrueck1[0];
            systemrueck("sudo dnf -y install kernel-modules-extra && "
                "{ lsmod | grep capidrv || sudo modprobe capidrv; lsmod | grep kernelcapi || sudo modprobe kernelcapi; }",obverb,oblog);
            systemrueck("sudo ls /boot/vmlinuz-* -r|head -n 1|cut -d- -f2,3,4,5",obverb,oblog,&vrueck2);
            if (vrueck2.size()) v2=vrueck2[0];
//            cout<<"vi: "<<v1<<"\n"<<"v2: "<<v2<<endl;
            if (v1!=v2) {
              Log(blaus+Tx[T_Zur_Inbetriebnahme_der_Capisuite_muss_das_Modul_capi_geladen_werten]+schwarz+v1+blau+" -> "
                  +schwarz+v2+blau+Tx[T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten]+schwarz+mpfad+blau+Tx[T_aufrufen]
                  +schwarz,1,1);
              exit(0);
            } // if (v1!=v2) 
//            exit(1);
            // nach kdpeter.blogspot.de/2013/10/fedora-compile-single-module-directory.html
            int altobverb=obverb;obverb=2;
            //         systemrueck("sudo dnf -y install @\"Development Tools\" rpmdevtools yum-utils ncurses-devel",obverb,oblog);
            systemrueck("sudo rpmdev-setuptree",obverb,oblog);
            Log(Tx[T_Moment_muss_Kernel_herunterladen],-1,oblog);
            systemrueck("cd "+instverz+" && sudo dnf download --source kernel",obverb,oblog);
            svec rueck;
            string kstring;
            systemrueck("cd "+instverz+" && ls -t kernel*.rpm | head -n 1",obverb,oblog,&rueck);
            if (rueck.size()) {
              kstring=rueck[0];
              systemrueck("cd "+instverz+" && sudo dnf -y builddep "+kstring,obverb,oblog);
              systemrueck("cd "+instverz+" && rpm -Uvh "+kstring,obverb,oblog);
              for(unsigned iru=0;iru<2;iru++) {
                if (!systemrueck("cd "+gethome()+"/rpmbuild/SPECS && rpmbuild -bp --target=$(uname -m) kernel.spec",obverb,oblog)) {
                  systemrueck("dnf -y install kernel-devel",obverb,oblog);
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
            obverb=altobverb;
          } // if (system==fed) 
        } // if (systemrueck("sudo modprobe capi",obverb,oblog))
        systemrueck("sudo modprobe capidrv",obverb,oblog);
      } // if (!fcpcida || !capida || !capidrvda) 
      pruefrules(obverb,oblog);
      pruefblack(obverb,oblog);
      capischonerfolgreichinstalliert=!linst.obfehlt("capisuite capi4linux i4l-isdnlog");
      if (capischonerfolgreichinstalliert) {
       struct stat d1, d2;
       if (lstat("/etc/capisuite",&d1) && lstat("/usr/local/etc/capisuite",&d2))
         capischonerfolgreichinstalliert=0;
      }
      // <<rot<<"capischonerfolgreichinstalliert 0: "<<(int)capischonerfolgreichinstalliert<<schwarz<<endl;
      if (!capischonerfolgreichinstalliert) {
        Log(string(Tx[T_Konnte])+blau+"capisuite"+schwarz+Tx[T_nichtstarten],1,oblog);
        // if (systemrueck("which zypper",-1,-1)) KLA
        //        if (linst.checkinst(-1,-1)!=zyp) KLA
        /*
           if (pruefipr()!=zypper) {
           Log(rots+Tx[T_Kann_Capisuite_nicht_installieren_verwende_Capi_nicht],1,1);
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
        if (!capischonerfolgreichinstalliert) {
          holvongithub("capisuite_copy");
          svec csrueck;
          systemrueck("find /usr/lib*/python* -type f -name Makefile -printf '%h\\n' "+string(obverb?"":"2>/dev/null")+"| sort -r",
                      obverb,oblog,&csrueck);
          if (csrueck.size()) {
            struct stat c20stat;
            if (lstat("/usr/lib64/libcapi20.so",&c20stat)) {
              holvongithub("capi20_copy");
              kompiliere("capi20_copy",s_gz);
              systemrueck("sh -c 'cd "+instverz+" && L=/usr/lib64/libcapi20.so && L3=${L}.3 && test -f $L3 && ! test -f $L && "
                          "ln -s $L3 $L; test -f $L;'",obverb,oblog);
            }
//            systemrueck("sh -c 'P=capi20_copy;T=$P.tar.bz2;M=$P-master;cd "+instverz+" && tar xpvf $T && rm -rf $P; mv $M $P && cd $P "
//                        " && ./configure && make && sudo make install '",obverb,oblog);
//            svec rueck;
//            systemrueck("find /usr -name capi20.h 2>/dev/null",obverb,oblog,&rueck); 
            systemrueck("sh -c 'cd "+instverz+" && { cd capisuite 2>/dev/null && { test -f Makefile && make clean; }; }'",obverb-1,oblog);
            if (!kompiliere("capisuite_copy",s_gz,
                           "sed -i.bak \"s/python_configdir=.*/python_configdir="+*sersetze(&csrueck[0],"/","\\/")+"/\" configure"
//                           " && { test -f /usr/lib64/libcapi20.so.3 && ! test -f /usr/lib64/libcapi20.so && "
//                           "ln -s /usr/lib64/libcapi20.so.3 /usr/lib64/libcapi20.so; true; }"
                           ,"HAVE_NEW_CAPI4LINUX=0 --datarootdir=/usr/local/lib --sysconfdir=/etc --localstatedir=/var && "
                           "sed -i \"s/PyErr_NewException(\\\"/PyErr_NewException((char*)\\\"/g\" src/application/capisuitemodule.cpp && ")) {
              mitcservice=1;
            }
//            string befehl="sh -c 'P=capisuite; T=$P.tar.gz; M=$P-master; cd "+instverz+""
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
//              //            pruefverz("/etc/capisuite",obverb,oblog,wahr);
//              //            systemrueck("ls /etc/capisuite/capisuite.conf || cp -a "+instverz+"/capisuite/src/capisuite.conf /etc/capisuite");
//              //            systemrueck("ls /etc/capisuite/fax.conf || cp -a "+instverz+"/capisuite/scripts/fax.conf /etc/capisuite");
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
      if (obcapi && (versuch>0 || this->capizukonf)) {
        this->konfcapi();
        scapisuite->restart(obverb-1,oblog);
        capizukonf=0;
      } //     if (versuch>0) KLA
      // das folgende verhindert zwar den Programmabbruch bei active (exit), das nuetzt aber nichts. In dem Fall fcpci aktualisieren! 23.5.14
      //    capilaeuft = !systemrueck("systemctl status capisuite | grep ' active (running)' >/dev/null 2>&1",0,obverb,oblog);
      //     capilaeuft  = !systemrueck("systemctl is-active capisuite",0,obverb,oblog);
      capilaeuft = this->scapisuite->obslaeuft(obverb-1,oblog);
      if (capilaeuft) {
        break;
      } else {
        servc::daemon_reload();
        systemrueck("sudo systemctl stop isdn",obverb>0?obverb:-1,oblog,0,1);
        //      systemrueck("sudo systemctl start isdn",obverb,oblog);
        Log(string(Tx[T_StarteCapisuite]),-1,oblog);
        scapisuite->stop(-1,oblog);
        capilaeuft=scapisuite->startundenable(-1,oblog);
        if (capilaeuft) {
          Log(Tx[T_Capisuite_gestartet],1,oblog);
        } else {
          //       Log("Capisuite konnte nicht gestartet werden.",1,1);
        }
      } //       if (capilaeuft) else
    } // if (capischonerfolgreichinstalliert) 
  } //  for(unsigned versuch=0;1;versuch++) (3.)
  if (capilaeuft) {
    if (!capiloggekuerzt) {
      kuerzelogdatei("/var/log/capisuite.log",obverb); // screen
      capiloggekuerzt=1;
    }
    if (this->obcapi) pruefmodcron(obverb,oblog);
  } else {
    Log(rots+Tx[T_konntecapisuiteservice]+gruen+ltoan(versuch)+rot+Tx[T_malnichtstartenverwN]+schwarz,1,1);
    return 1;
  } //   if (capilaeuft)
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
  struct stat entryspool;
  if (!lstat((spoolg.c_str()), &entryspool)) {
    for(int runde=0;runde<2;runde++) {
      if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
      } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
      RS rupd(My); 
      rupd.clear();
      vector<instyp> einf; // fuer alle Datenbankeinfuegungen
      einf.push_back(instyp(My->DBS,"capispoolpfad",&spooldir));
      einf.push_back(instyp(My->DBS,"capispooldatei",&spoolfil));
      einf.push_back(instyp(My->DBS,"cdateidatum",&entryspool.st_mtime));
      einf.push_back(instyp(My->DBS,"cdateizeit",entryspool.st_mtime));
      einf.push_back(instyp(My->DBS,"telnr",telnr));
      string bedingung=string("id=")+fsfp->id;
      rupd.update(altspool,einf,ZDB,bedingung);
      rupd.update(spooltab,einf,ZDB,bedingung);

      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      affr=My->affrows();
      if (affr>0) break;
      if (runde==1) {
        Log(string(Tx[T_Fehler_af])+drot+ltoan(rupd.fnr)+schwarz+Tx[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,oblog);
        exit(34);
      }
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
    struct stat entryff;
    string ff=pmp->wvz+vtz+fsfp->spdf;
    if (lstat(ff.c_str(), &entryff)) {
      Log(rots+Tx[T_faxemitCFehler]+schwarz+Tx[T_Faxdatei]+blau+ff+rot+ Tx[T_fehlt]+schwarz,1,1);
      // archiviere
    } else if (!entryff.st_size) {
      Log(rots+Tx[T_faxemitCFehler]+schwarz+Tx[T_Faxdatei]+blau+ff+rot+ Tx[T_hat0Bytes]+schwarz,1,1);
    } else {
      // capisuitefax mit Userangabe nur fuer root erlaubt
      pmp->nextnum();
      string cmd=string("capisuitefax -n ")+(strcmp("root",curruser())?"":"-u"+pmp->cuser)+" -d "+fsfp->telnr+" \""+pmp->wvz+vtz+fsfp->spdf+"\" 2>&1";
      vector<string> faxerg;
      systemrueck(cmd,obverb,oblog,&faxerg,0,wahr,Tx[T_Faxbefehl]);
      if (faxerg.size()) {
        const char* tz1="uccessful enqueued as ", // muss sprachlich so falsch bleiben wie im python-Script
              *tz2=" for ";
        if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1)) {
          if (char *z2=strstr(z1,tz2)) {
            string spoolg(z1+strlen(tz1),z2-z1-strlen(tz1));
            //            inDatenbankc(My, &spoolg, idsp, npdfp, spdfp, nachrnr, z2+strlen(tz2), obverb, oblog);
            if (!spoolg.find("job ")) {
             string nr=spoolg.substr(4); 
             char buf[20];
             sprintf(buf,"%.3lu",atol(nr.c_str()));
             spoolg=pmp->cfaxusersqvz+vtz+"fax-"+buf+".sff";
            }
            inDbc(My, spooltab, altspool, spoolg, fsfp, z2+strlen(tz2), obverb, oblog);
          }   // if (char *z2=strstr(z1,tz2)) 
          // if (char *z1=strstr((char*)faxerg.at(0).c_str(),tz1))
        } else if (faxerg.at(0).find("can't open")==0) {
          Log(rots+Tx[T_Datei]+blau+pmp->wvz+vtz+fsfp->spdf+rot+"' (id: "+blau+fsfp->id+rot+
              Tx[T_nichtgefundenloeschesieausDB]+schwarz,1,1);
          RS rsloe(My,string("DELETE FROM `")+spooltab+"` WHERE id = "+fsfp->id,ZDB);
        }
      } else {
        Log(rots+string(Tx[T_KeinErgebnisbeimFaxen])+schwarz,1,1);
      }
    }
  }
} // faxemitC

// wird aufgerufen in faxemitH
void inDBh(DB *My, const string& spooltab, const string& altspool, paramcl *pmp, const string& hylaid, fsfcl *fsfp,string *tel, int obverb, int oblog)
{
  Log(violetts+Tx[T_inDBh]+schwarz,obverb?obverb-1:0,oblog);
  string spoolfil=string("q")+hylaid;
  string spoolg= pmp->hsendqvz + vtz + spoolfil;
  uint affr=0;
  Log(string(Tx[T_SpoolDateierstellt])+rot+spoolg+schwarz+"'",pmp->obverb,pmp->oblog);
  Log(string(Tx[T_SpoolDatei])+rot+spoolfil+schwarz+"'",pmp->obverb,pmp->oblog);
  Log(string(Tx[T_SpoolPfad])+rot+pmp->hsendqvz+schwarz+"'",pmp->obverb,pmp->oblog);
  RS zs(My);
  struct stat entryspool;
  string spoolid="";
  if (!lstat(spoolg.c_str(), &entryspool)) {
    for(int runde=0;runde<2;runde++) {
      if (runde==0) { zs.Abfrage("SET NAMES 'utf8'");
      } else if (runde==1) zs.Abfrage("SET NAMES 'latin1'");
      RS rupd(My); 
      rupd.clear();
      vector<instyp> einf; // fuer alle Datenbankeinfuegungen
      einf.push_back(instyp(My->DBS,"hylanr",hylaid));
      einf.push_back(instyp(My->DBS,"hdateidatum",&entryspool.st_mtime));
      einf.push_back(instyp(My->DBS,"hdateizeit",entryspool.st_mtime));
      einf.push_back(instyp(My->DBS,"telnr",tel));
      string bedingung=string("id=")+fsfp->id;
      rupd.update(altspool,einf,ZDB,bedingung);
      rupd.update(spooltab,einf,ZDB,bedingung);
      if (runde==1) zs.Abfrage("SET NAMES 'utf8'");
      affr=My->affrows();
      if (affr>0) break;
      if (runde==1) {
        Log(string(Tx[T_Fehler_af])+drot+ltoan(rupd.fnr)+schwarz+Tx[T_bei]+tuerkis+rupd.sql+schwarz+": "+blau+rupd.fehler+schwarz,1,pmp->oblog);
        exit(36);
      }
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
    systemrueck("sudo find "+pmp->varsphylavz+" -name seqf -exec chmod 660 {} \\;"" -exec chown fax:uucp {} \\;",obverb,oblog);
    const char* tz1="request id is ", *tz2=" (";
    string sendfax;
//    systemrueck("sudo sh -c 'which sendfax'",obverb,1,&rueck);
    if (obprogda("sendfax",obverb,oblog,&sendfax)) {
      string cmd=sendfax+" -n -A -d "+tel+" \""+pmp->wvz+vtz+fsfp->spdf+"\" 2>&1";
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
      }
    }
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
    string trimfaxnr=pmp->stdfaxnr(faxnr);
    // vor den angegebenen SQL-Befehlen nachschauen, wie die gesandten Faxe benannt wurden
    string **locsqlp=new string*[pmp->sqlzn+1];
    string sql0=string("SELECT adressat, titel FROM `")+pmp->touta+
      "` WHERE rcfax" // stdfaxnr(rcfax,"+pmp->InternationalPrefix+","+pmp->LongDistancePrefix+","+pmp->countrycode+","+pmp->citycode+")"
                        "='&&faxnr&&' ORDER BY subMT DESC";
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
} // void getSender(paramcl *pmp,const char* faxnrc, string *getnamep, string *bsnamep,int obverb=0,int oblog=0) 

// wird aufgerufen in: main
const string& pruefspool(DB *My,const string& spooltab, const string& altspool, int obverb, int oblog, uchar direkt=0)
{
  Log(violetts+Tx[T_pruefspool]+schwarz+", direkt: "+(direkt?"1":"0"),obverb,oblog);
  if (!direkt) {
    Feld felder[] = {
      Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1),
      Feld("original","varchar","1","",Tx[T_Originalname_der_Datei],1,0,1),
      Feld("origvu","varchar","1","",Tx[T_Originalname_der_Datei_vor_Umwandlung_in_PDF],0,0,1),
      Feld("telnr","varchar","1","",Tx[T_zu_senden_an],0,0,1),
      Feld("adressat","varchar","1","",Tx[T_zu_senden_an],0,0,1),
      Feld("prio","int","1","",Tx[T_Prioritaet_aus_Dateinamen],0,0,1),
      Feld("capidials","int","10","",Tx[T_Zahl_der_bisherigen_Versuche_in_Capisuite],0,0,1),
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
    };
    Feld ifelder0[] = {Feld("capispooldatei")}; Index i0("capispooldatei",ifelder0,sizeof ifelder0/sizeof* ifelder0);
    Feld ifelder1[] = {Feld("cdateidatum")};    Index i1("cdateidatum",ifelder1,sizeof ifelder1/sizeof* ifelder1);
    Feld ifelder2[] = {Feld("hdateidatum")};    Index i2("hdateidatum",ifelder2,sizeof ifelder2/sizeof* ifelder2);
    //    Feld ifelder3[] = {Feld("original")};       Index i3("original",ifelder3,sizeof ifelder3/sizeof* ifelder3);
    Index indices[]={i0,i1,i2/*,i3*/};
    // auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
    Tabelle taa(altspool,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,Tx[T_capispooldateien_der_Capisuite],"InnoDB","utf8","utf8_general_ci","DYNAMIC");
    if (My->prueftab(&taa, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+altspool,1,1);
      return NULL;
    }
    Tabelle tab(spooltab,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,Tx[T_capispooldateien_der_Capisuite],"InnoDB","utf8","utf8_general_ci","DYNAMIC");
    if (My->prueftab(&tab, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+spooltab,1,1);
      return NULL;
    }
  } // if (!direkt) 
  return spooltab;
} // const char* pruefspool(DB *My,const char* spooltab, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: main
void pruefouttab(DB *My, const string& touta, int obverb, int oblog, uchar direkt=0)
{
  Log(violetts+Tx[T_pruefouta]+schwarz,obverb,oblog);
  if (!direkt) {
    Feld felder[] = {
      Feld("eind","int","10","",Tx[T_eindeutige_Identifikation],1,1),
      Feld("Erfolg","int","1","",Tx[T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen],0,0,1),
      Feld("rcname","varchar","1","",Tx[T_Name_des_Adressaten],0,0,1),
      Feld("submt","datetime","0","0",Tx[T_Datum_des_Losschickens],0,0,1),
      Feld("transe","datetime","0","0",Tx[T_Ende_der_Uebertragung],0,0,1),
      Feld("submid","varchar","1","",Tx[T_Kennung_im_Faxsystem_hylafax_Nr_Capisuite_Datei_MSFax_Fax_Dateiname],0,0,1),
      Feld("docname","varchar","1","",Tx[T_Dateiname],0,0,1),
      Feld("fsize","int","10","",Tx[T_Dateigroesse],0,0,1),
      Feld("pages","int","10","",Tx[T_Seitenzahl],0,0,1),
      Feld("retries","int","10","",Tx[T_Zahl_der_Anwahlen],0,0,1),
      Feld("rcfax","varchar","1","",Tx[T_FAxnummer_des_Adressaten],0,0,1),
      Feld("adressat","varchar","1","",Tx[T_Name_des_Adressaten],0,0,1),
      Feld("titel","varchar","1","",Tx[T_Titel_des_Adressaten],0,0,1),
      Feld("pid","int","10","",Tx[T_PID_falls_aus_Dateinamen_ermittelt],0,0,1),
      Feld("tsid","varchar","1","",Tx[T_Kurzbezeichnung_der_eigenen_Faxstelle],0,0,1),
      Feld("devname","varchar","1","",Tx[T_Geraetename],0,0,1),
      Feld("oscht","datetime","0","0",Tx[T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax],0,0,1),
      Feld("subject","varchar","1","",Tx[T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax],0,0,1),
      Feld("id","varchar","1","",Tx[T_identisch_zu_submid_nur_MSFax],0,0,1),
      Feld("prio","int","10","",Tx[T_Prioritaet_nur_MSFax],0,0,1),
      Feld("csid","varchar","1","",Tx[T_FAxnummer_des_Adressaten_nur_MSFax],0,0,1),
      Feld("sender","varchar","1","",Tx[T_Faxnummer_des_Senders_nur_MSFax],0,0,1),
      Feld("transs","datetime","0","0",Tx[T_Beginn_der_Uebertragung_nur_MSFax],0,0,1),
    };
    Feld ifelder0[] = {Feld("submt"),Feld("Erfolg")};   Index i0("submt",ifelder0,sizeof ifelder0/sizeof* ifelder0);
    Feld ifelder1[] = {Feld("Erfolg"),Feld("submt")};   Index i1("Erfolg",ifelder1,sizeof ifelder1/sizeof* ifelder1);
    Feld ifelder2[] = {Feld("docname"),Feld("Erfolg")}; Index i2("docname",ifelder2,sizeof ifelder2/sizeof* ifelder2);
    Feld ifelder3[] = {Feld("pid"),Feld("Erfolg")};     Index i3("pid",ifelder3,sizeof ifelder3/sizeof* ifelder3);
    Feld ifelder4[] = {Feld("rcfax"),Feld("Erfolg")};   Index i4("rcfax",ifelder4,sizeof ifelder4/sizeof* ifelder4);
    Index indices[]={i0,i1,i2,i3,i4};
    // auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
    Tabelle taba(touta,felder,sizeof felder/sizeof* felder,indices,sizeof indices/sizeof *indices,
        Tx[T_Archiv_fuer_die_erfolgreichen_Faxe],"InnoDB","utf8","utf8_general_ci","DYNAMIC");
    if (My->prueftab(&taba, obverb)) {
      Log(string(Tx[T_Fehler_beim_Pruefen_von])+touta,1,1);
    }
  } // if (!direkt)
} // int pruefouttab(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in: main
void pruefinctab(DB *My, const string& tinca, int obverb, int oblog, uchar direkt=0)
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
      //      Feld("rcfax","varchar","1","",Tx[T_FAxnummer_des_Adressaten],0,0,1),
      Feld("titel","varchar","1","",Tx[T_Titel_des_Adressaten],0,0,1),
      //      Feld("pid","int","10","",Tx[T_PID_falls_aus_Dateinamen_ermittelt],0,0,1),
      Feld("tsid","varchar","1","",Tx[T_Kurzbezeichnung_der_eigenen_Faxstelle],0,0,1),
      Feld("devname","varchar","1","",Tx[T_Geraetename],0,0,1),
      Feld("callerid","varchar","1","",Tx[T_Bezeichnung_des_Anrufers],0,0,1),
      //      Feld("oscht","datetime","0","0",Tx[T_outgoing_schedule_time_oder_so_aehnlich_nur_MSFax],0,0,1),
      //      Feld("subject","varchar","1","",Tx[T_Hinweis_auf_Dateiinhalt_oder_Adressat_nur_MSFax],0,0,1),
      Feld("id","varchar","1","",Tx[T_identisch_zu_submid_nur_MSFax],0,0,1),
      //      Feld("prio","int","10","",Tx[T_Prioritaet_nur_MSFax],0,0,1),
      Feld("csid","varchar","1","",Tx[T_FAxnummer_des_Adressaten_nur_MSFax],0,0,1),
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
void pruefprocgettel3(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)
{
  Log(violetts+Tx[T_pruefprocgettel3]+schwarz,obverb,oblog);
  string body;
  body+= "begin \n";
  body+= " declare pos int;\n";
  body+= " declare ch char default '0';\n";
  body+= " declare tel varchar(100) default '';\n";
  body+= " set pos = instr(dname,anfaxstr);\n";
  body+= " if pos>0 then\n";
  body+= "  set pos=pos+length(anfaxstr);\n";
  body+= " else\n";
  body+= "  if ancfaxstr > '' then\n";
  body+= "   set pos = instr(dname,ancfaxstr);\n";
  body+= "   if pos>0 then\n";
  body+= "    set pos=pos+length(ancfaxstr);\n";
  body+= "   else\n";
  body+= "    if anhfaxstr > '' then\n";
  body+= "     set pos = instr(dname,anhfaxstr);\n";
  body+= "     if pos>0 then\n";
  body+= "      set pos=pos+length(anhfaxstr);\n";
  body+= "     end if;\n";
  body+= "    end if;\n";
  body+= "   end if;\n";
  body+= "  end if;\n";
  body+= " end if;\n";
  body+= " if pos>0 then\n";
  body+= "  wlab: loop\n";
  body+= "   set ch = substring(dname,pos,1);\n";
  body+= "   if ch = '_' then leave wlab; end if;\n";
  body+= "   if instr('0123456789',ch) then set tel=concat(tel,ch);\n";
  body+= "   else if ch='+' then set tel=concat(tel,'00'); end if; end if;\n";
  body+= "   set pos=pos+1;\n";
  body+= "   if pos>length(dname) then leave wlab; end if;\n";
  body+= "  end loop;\n";
  body+= " end if;\n";
  body+= " return tel;\n";
  body+= "end";
  string mhost = host=="localhost"?host:"%";
  string owner=string("`")+usr+"`@`"+mhost+"`";
  for(uchar runde=0;runde<2;runde++) {
    uchar fehlt=1;
    char ***cerg;
    RS rs(Myp,"SHOW CREATE FUNCTION gettel3",2-obverb);
    while (cerg=rs.HolZeile(),cerg?*cerg:0) {
      for(uint i=1;i<=2;i++) {
        if (*(*cerg+i)) if (strstr(*(*cerg+i),body.c_str())) if (strstr(*(*cerg+i),owner.c_str())) {
          fehlt=0;
          break;
        }
      }
      break;
    } 
    //   RS rs(Myp,string("select definer from mysql.proc where definer like '`")+usr+"`@`"+mhost+"`'",255);
    if (fehlt) {
      DB *aktMyp;
      if (!runde) aktMyp=Myp; else {
        DB MySup(myDBS,Myp->host.c_str(),"root",Myp->rootpwd.c_str(),Myp->db.c_str(),0,0,0,obverb,oblog);
        aktMyp=&MySup;
      }
      string proc= "DROP FUNCTION IF EXISTS `gettel3`";
      RS rs0(aktMyp, proc);
      proc = "CREATE DEFINER="+owner+" FUNCTION `gettel3`\n"
        "(dname VARCHAR(1000), anfaxstr VARCHAR(100), ancfaxstr VARCHAR(100), anhfaxstr VARCHAR(100)) \n"
        "RETURNS VARCHAR(1000) CHARSET latin1 COLLATE latin1_german2_ci DETERMINISTIC\n";
      proc+=body;
      RS rs1(aktMyp, proc);
    } else 
      break; // runde
  }
} // void pruefprocgettel3(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)


void pruefstdfaxnr(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)
{
  Log(violetts+Tx[T_pruefstdfaxnr]+schwarz,obverb,oblog);
  string body;
  body+= "begin \n";
  body+= " declare anfg varchar(100) default concat(IPf,'+');\n";
  body+= " declare pos int default 0;\n";
  body+= " declare it char default '';\n";
  body+= " declare land varchar(100) default concat(IPf,CoCd);\n";
  body+= " declare trimfaxnr varchar(100) default '';\n";
  body+= " glp: loop\n";
  body+= "   set it = substring(faxnr,pos,1);\n";
  body+= "   if instr('+0123456789',it) then\n";
  body+= "    if trimfaxnr='' and not instr(anfg,it) then\n";
  body+= "     set trimfaxnr=concat(LDPf,CiCd);\n";
  body+= "    end if;\n";
  body+= "   end if;\n";
  body+= "   if (it='+') then\n";
  body+= "    set trimfaxnr=concat(trimfaxnr,IPf);\n";
  body+= "   else\n";
  body+= "    set trimfaxnr=concat(trimfaxnr,it);\n";
  body+= "   end if;\n";
  body+= "   set pos=pos+1;\n";
  body+= "   if pos>length(faxnr) then leave glp; end if;\n";
  body+= " end loop;\n";
  body+= " if instr(trimfaxnr,land)=1 then\n";
  body+= "  set trimfaxnr=concat(LDPf,substr(trimfaxnr,length(land)+1));\n";
  body+= " end if;\n";
  body+= " return trimfaxnr;\n";
  body+= "end";
  string mhost = host=="localhost"?host:"%";
  string owner=string("`")+usr+"`@`"+mhost+"`";
  for(uchar runde=0;runde<2;runde++) {
    uchar fehlt=1;
    char ***cerg;
    RS rs(Myp,"SHOW CREATE FUNCTION stdfaxnr",2-obverb);
    while (cerg=rs.HolZeile(),cerg?*cerg:0) {
      for(uint i=1;i<=2;i++) {
        if (*(*cerg+i)) if (strstr(*(*cerg+i),body.c_str())) if (strstr(*(*cerg+i),owner.c_str())) {
          fehlt=0;
          break;
        }
      }
      break;
    } 
    //   RS rs(Myp,string("select definer from mysql.proc where definer like '`")+usr+"`@`"+mhost+"`'",255);
    if (fehlt) {
      DB *aktMyp;
      if (!runde) aktMyp=Myp; else {
        DB MySup(myDBS,Myp->host.c_str(),"root",Myp->rootpwd.c_str(),Myp->db.c_str(),0,0,0,obverb,oblog);
        aktMyp=&MySup;
      }
      string proc= "DROP FUNCTION IF EXISTS `stdfaxnr`";
      RS rs0(aktMyp, proc);
      proc = "CREATE DEFINER="+owner+" FUNCTION `stdfaxnr`\n"
        "(faxnr VARCHAR(200), IPf VARCHAR(10), LDPf VARCHAR(20), CoCd VARCHAR(20), CiCd VARCHAR(20)) \n"
        "RETURNS VARCHAR(200) CHARSET latin1 COLLATE latin1_german2_ci DETERMINISTIC\n";
      proc+=body;
      RS rs1(aktMyp, proc);
    } else 
      break; // runde
  }
}  // void pruefstdfaxnr(DB *Myp, const string& usr, const string& pwd, const string& host, int obverb, int oblog)




// ermittelt die letzten Sendedaten zu sendqgespfad mit fsf.capistat, schreibt die Zahl der Versuche in ctries zurueck und ergaenzt den 
// Anzeigezeiger ausgp
// wird aufgerufen in: untersuchespool, zeigweitere
void fsfcl::capiwausgeb(stringstream *ausgp, string *maxtries, int obverb, string *ctriesp, int oblog,unsigned long faxord)
{
  Log(violetts+Tx[T_capiwausgeb]+schwarz+"  capistat: "+blau+FxStatS(&capistat)+schwarz+ " maxtries: "+blau+*maxtries+schwarz,obverb,oblog);
  *ausgp<<blau<<endl;
  if (faxord) *ausgp<<faxord<<")";
  else *ausgp<<"  ";
  *ausgp<<"Capi: "<<schwarz;
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
  if (capistat!=fehlend) {
    size_t p1=sendqgespfad.rfind('.');
    if (p1) {
      string suchtxt = sendqgespfad.substr(0,p1)+".txt";
      /*
      cppSchluess cconf[]={{"tries"},{"starttime"},{"dialstring"}};
      size_t cs=sizeof cconf/sizeof*cconf;
      */
      schlArr cconf; cconf.init(3,"tries","starttime","dialstring");
      struct stat cstat;
      if (!lstat(suchtxt.c_str(),&cstat)) {
        confdat cpconf(suchtxt,&cconf,obverb);
        //    if (cpplies(suchtxt,cconf,cs)) KLA
        // RS rmod(My,string("update spool set capidials=")+cconf[0].val+" where id = "+*(*cerg+0),ZDB);
        if (ctriesp) *ctriesp=cconf[0].wert;
        char buf[255];
        int versuzahl=atol(cconf[0].wert.c_str());
        snprintf(buf,4,"%3d",versuzahl);
        struct stat statlock;
        int objetzt=!lstat((sendqgespfad.substr(0,p1)+".lock").c_str(),&statlock);
        *ausgp<<", "<<blau<<buf<<"/"<<*maxtries<<schwarz<<(objetzt?umgek:"")<<Tx[T_Anwahlen]<<schwarz;
        //                      if (versuzahl>12) ausg<<"zu spaet, ";
        struct tm tm;
        memset(&tm, 0, sizeof(struct tm));
        strptime(cconf[1].wert.c_str(), "%a %b %d %H:%M:%S %Y", &tm);
        strftime(buf, sizeof(buf), "%d.%m.%y %H:%M:%S", &tm);
        *ausgp<<blau<<buf<<schwarz; 
        *ausgp<<", T.: "<<blau<<setw(12)<<cconf[2].wert<<schwarz; 
        *ausgp<<Tx[T_kommaDatei]<<rot<<sendqgespfad<<schwarz;
        *ausgp<<Tx[T_bzw]<<blau<<"*.txt"<<schwarz;
      } // if (!lstat(suchtxt.c_str(),&cstat))
    } // if (p1)
    if (ctriesp) if (ctriesp->empty()) *ctriesp="0";
  } // if (capistat!=fehlend) 
} // void fsfcl::capiwausgeb(stringstream *ausgp, string *maxtries, int obverb, string *ctriesp, int oblog,unsigned long faxord)


// wird aufgerufen in: setzhylastat
int paramcl::xferlog(const string& jobid, string *erg, int obverb, int oblog)
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
  systemrueck(string("tac \"")+xferfaxlog+"\" 2>/dev/null | grep -m 1 \"tty[^"+sep+"]*"+sep+jobid+sep+"\" | cut -f 14",obverb,oblog,&grueck); 
  if (grueck.size()) {
    gefunden=1;
    *erg=grueck[0];
#else
    systemrueck(string("tac \"")+xferfaxlog+"\" 2>/dev/null | grep -m 1 \""+this->hmodem+sep+jobid+sep+"\"",obverb,oblog,&grueck); // ggf. broken pipe error
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
      if (tok[4]==jobid) KLA
        gefunden=1;
    *erg=tok[13];
    if ((*erg)=="\"\"") erg->clear();
    //            if (erg->length()>1) if ((*erg)[0]=='"' && (*erg)[erg->length()-1]=='"') *erg=erg->substr(1,erg->length()-2);
    if (obverb) KLA
      Log(blaus+"tok[13]: "+schwarz+*erg,obverb,oblog);
    KLZ
#ifndef mitgrep
#ifdef rueckwaerts
      break;
    KLZ // if (tok[4]==jobid) KLA
      KLZ // if (tok.size()>15)
      rzeile.clear();
    KLZ else KLA
      rzeile+=ch;
#endif // rueckwaerts
#endif // not mitgrep
    KLZ // 
      KLZ // if (ch==10)
#endif  // not direkt
  } // if f.is_open() oder (grueck.size()
#ifdef profiler
  prf.ausgeb();
#endif
  return gefunden;
} // void xferlog(string varsphylavz, string jobid, string *erg)

// wird aufgerufen in setzhylastat
uchar paramcl::setzhconfp(string *protdaktp,int obverb)
{
  /*
  static cppSchluess hconf[]={{"state"},{"totdials"},{"status"},{"statuscode"},{"!pdf"},{"tts"},{"number"},{"maxdials"},{"pdf"}};
  static size_t cs=sizeof hconf/sizeof*hconf;
  */
  if (hylconf.zahl==9) {
    hylconf.reset();
  } else { 
    hylconf.init(9,"state","totdials","status","statuscode","!pdf","tts","number","maxdials","pdf");
  }
//  static string *alt_protdaktp=0;
//  if (alt_protdaktp!=protdaktp) KLA
    confdat hylc(*protdaktp,&hylconf,obverb,':');
    return hylc.obgelesen;
//    alt_protdaktp=protdaktp;
//  KLZ
//  hconfp= hconf;
} // paramcl::setzhconfp

// wird aufgerufen in paramcl::loeschefax, paramcl::untersuchespool, paramcl::zeigweitere
void paramcl::setzhylastat(fsfcl *fsf, string *protdaktp, uchar *hyla_uverz_nrp, int *obsfehltp, uchar startvznr,
    int obverb, int oblog, string *hylastatep, string *hyladialsp, string *hylastatusp, string *hylastatuscodep) 
{
  Log(violetts+Tx[T_setzhylastat]+schwarz,obverb,oblog);
  string startvznrs = ltoan(startvznr);
  Log(violetts+"hylanr: "+schwarz+fsf->hylanr+violetts+" "+Tx[T_setzhylastat]+schwarz+
      " hyla_uverz_nrp: "+blau+ltoan(*hyla_uverz_nrp)+schwarz+" startvznr: "+blau+startvznrs+schwarz,
      obverb,oblog);
  // wenn in *hyla_uverz_nrp '1' uebergeben wird, nur in sendq suchen
  // Rueckgabe: 0 = in doneq oder archive gefunden
  struct stat entryprot;
  string cmd=string("sudo find ")+this->varsphylavz+"/sendq "+(*hyla_uverz_nrp?" ":this->varsphylavz+"/doneq "+this->varsphylavz+"/archive ")
    +" -name 'q"+fsf->hylanr+"'";
  svec rueck;
  systemrueck(cmd,obverb,oblog,&rueck);
  if (rueck.size()) {
    *protdaktp=rueck[0];
    *obsfehltp=lstat(protdaktp->c_str(), &entryprot);
    *hyla_uverz_nrp=rueck.at(0).find("/doneq")==string::npos && rueck.at(0).find("/archive")==string::npos;
  }
  if (obverb) {
    Log(schwarzs+"*obsfehltp: "+blau+(*obsfehltp?"1":"0")+schwarz+", hyla_uverz_nr: "+blau+(*hyla_uverz_nrp?"1":"0")+schwarz,obverb,oblog);
  }
  if (*obsfehltp) {
//    this->hconfp=0;
    // wenn also die Datenbankdatei weder im Spool noch bei den Erledigten nachweisbar ist
    if (this->xferlog(fsf->hylanr, &fsf->hgerg,obverb,oblog)) {
      anfzweg(fsf->hgerg);
      if (fsf->hgerg.empty()) {
        fsf->hylastat=gesandt;
      } else {
        fsf->hylastat=gescheitert;
      }
    } else {
      fsf->hylastat=fehlend;
    }
  //   if (*obsfehltp)
  } else {
    hgelesen = setzhconfp(protdaktp,obverb);
    //  if (cpplies(*protdaktp,hconf,cs,0,':')) KLA
    if (hylastatep) *hylastatep=this->hylconf[0].wert;
    if (hyladialsp) *hyladialsp=this->hylconf[1].wert;
    if (hylastatusp) *hylastatusp=this->hylconf[2].wert;
    if (this->hylconf[3].wert.empty()) this->hylconf[3].wert="0";
    if (hylastatuscodep) *hylastatuscodep=this->hylconf[3].wert;
    vector<string> tok;
    string pdf=this->hylconf[4].wert==""?this->hylconf[8].wert:this->hylconf[4].wert;
    aufiSplit(&tok,&pdf,":");
    fsf->sendqgespfad = this->varsphylavz + vtz + tok[tok.size()-1];
    //    struct stat entryh;
    //    lstat(sendqgespfad.c_str(),&entryh); 
    // 8, status gescheitert, evtl. unzureichend dokumentiert, aber wahr
    if (*hyla_uverz_nrp) {
      fsf->hylastat=wartend;
    // if (*obsfehltp) 
    }  else { 
      if (this->hylconf[0].wert=="8") {  
        fsf->hylastat=gescheitert;
        // 7, status erfolgreich
      } else if (this->hylconf[0].wert=="7") { 
        fsf->hylastat=gesandt;
      } else {
        fsf->hylastat=woasined;
      }
    } // if (*hyla_uverz_nrp) 
  } // if (*obsfehltp) else
  Log(violetts+Tx[T_Ende]+" "+Tx[T_setzhylastat]+", hylastat: "+blau+FxStatS(&fsf->hylastat)+schwarz,obverb,oblog);
} // setzhylastat

// wird aufgerufen in untersuchespool und zeigweitere
void fsfcl::hylaausgeb(stringstream *ausgp, paramcl *pmp, int obsfehlt, string& hylastate, int obverb, uchar obzaehl, int oblog)
{
  Log(violetts+Tx[T_hylaausgeb]+schwarz+"  hylastat: "+blau+FxStatS(&hylastat)+schwarz,obverb,oblog);
  *ausgp<<blau<<endl;
  if (obzaehl) *ausgp<<++pmp->faxord<<")";
  else *ausgp<<"  ";
  *ausgp<<"Hyla: "<<schwarz;
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
    if (hylastat==wartend) {
      *ausgp<<schwarz<<" "<<Tx[T_wartend]<<schwarz;
    } else if (hylastat==gescheitert) {
      *ausgp<<blau<<Tx[T_gescheitert]<<schwarz;
    } else if (hylastat==gesandt) {
      *ausgp<<blau<<" "<<Tx[T_gesandt]<<schwarz;
    }
  }
  // wenn eine Protokolldatei auslesbar war
//  if (pmp->hconfp) {
        // modemlaeuftnicht=systemrueck(("sudo faxstat | grep ")+this->hmodem+" 2>&1",obverb,oblog) + fglaeuftnicht;
  if (pmp->hgelesen) {
    *ausgp<<", ";
    char buf[100];
    int hversuzahl=atol(pmp->hylconf[1].wert.c_str()); // totdials
    snprintf(buf,4,"%3d",hversuzahl);
    *ausgp<<blau<<buf<<schwarz<<"/"<<pmp->hylconf[7].wert<<(hylastate=="6"?umgek:"")<<Tx[T_Anwahlen]<<schwarz;
    // hier muss noch JobReqBusy, JobReqNoAnswer, JobReqNoCarrier, JobReqNoFCon, JobReqOther, JobReqProto dazu gerechnet werden
    time_t spoolbeg=(time_t)atol(pmp->hylconf[5].wert.c_str());
    strftime(buf, sizeof(buf), "%d.%m.%y %H:%M:%S", localtime(&spoolbeg));
    *ausgp<<blau<<buf<<schwarz; 
    //              if (hversuzahl>12) ausg<<", zu spaet";
    *ausgp<<", T.: "<<blau<<setw(12)<<pmp->hylconf[6].wert<<schwarz;
    *ausgp<<Tx[T_kommaDatei]<<rot<<sendqgespfad<<schwarz;
  }
} // void fsfcl::hylaausgeb(stringstream *ausgp, paramcl *pmp, int obsfehlt, int obverb, uchar obzaehl, int oblog)


void zeigversion(string& prog,string& mpfad)
{
  struct tm tm;
  char buf[255];
  cout<<endl<<Tx[T_Programm]<<violett<<mpfad<<schwarz<<endl;
  cout<<"Copyright: "<<blau<<Tx[T_Freie_Software]<<schwarz<<Tx[T_Verfasser]<<blau<<"Gerald Schade"<<schwarz<<endl;
  cout<<"Version: "<<blau<<version<<schwarz<<endl;
  memset(&tm, 0, sizeof(struct tm));
  strptime(__TIMESTAMP__,"%a %b %d %H:%M:%S %Y", &tm);
  //<<tm.tm_sec<<" "<<tm.tm_min<<" "<<tm.tm_hour<<" "<<tm.tm_mday<<" "<<tm.tm_mon<<" "<<tm.tm_year<<" "<<tm.tm_wday<<" "<<tm.tm_yday<<" "<<tm.tm_isdst<<endl;
  strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", &tm);
  cout<<Tx[T_Letzte_Programmaenderung]<<blau<<buf<<schwarz<<endl;
  memset(&tm, 0, sizeof(struct tm));
  strptime((string(__DATE__)+" "+__TIME__).c_str(),"%b %d %Y %H:%M:%S", &tm);
  strftime(buf, sizeof(buf), "%d.%m.%Y %H:%M:%S", &tm);
  cout<<"              "<<Tx[T_Kompiliert]<<blau<<buf<<schwarz<<endl;
  cout<<Tx[T_Quelle]<<blau<<"https://github.com/libelle17/"<<prog<<schwarz<<endl;
  cout<<Tx[T_Hilfe]<<braun<<"man "<<base_name(mpfad)<<schwarz<<Tx[T_or]<<braun<<"man -Lde "<<base_name(mpfad)<<schwarz<<"'"<<endl;
} // void zeigversion(const char* const prog)

void paramcl::zeigkonf()
{
  struct stat kstat;
  char buf[255];
  if (!lstat(konfdatname.c_str(),&kstat)) {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    memcpy(&tm, localtime(&kstat.st_mtime),sizeof(tm));
    strftime(buf, sizeof(buf), "%d.%m.%Y %H.%M.%S", &tm);
  }
  cout<<Tx[T_aktuelle_Einstellungen_aus]<<blau<<konfdatname<<schwarz<<"' ("<<buf<<"):"<<endl;
  for(unsigned i=0;i<cgconf.zahl;i++) {
    cout<<blau<<setw(20)<<cgconf[i].name<<schwarz<<": "<<cgconf[i].wert<<endl;
  }
} // void paramcl::zeigkonf()

int main(int argc, char** argv) 
{
  paramcl pm(argc,argv); // Programmparameter
  pruefplatte(); // geht ohne Logaufruf, falls nicht #define systemrueckprofiler
  pm.logvorgaben();
  pm.getcommandl0(); // anfangs entscheidende Kommandozeilenparameter abfragen
  pm.VorgbAllg();
  pm.VorgbSpeziell();
  pm.lieskonfein();

  if (!pm.getcommandline()) 
    exit(40);
  pm.pruefggfmehrfach();
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
  pm.setzhylavz();
  pm.verzeichnisse();
  pm.pruefsamba();

  if (pm.logdateineu) tuloeschen(logdt,"",pm.obverb,pm.oblog);
  Log(string(Tx[T_zufaxenvz])+drot+pm.zufaxenvz+schwarz+"'",pm.obverb,pm.oblog);
  Log(string(Tx[T_Logpfad])+drot+pm.loggespfad+schwarz+Tx[T_oblog]+drot+ltoan((int)pm.oblog)+schwarz+")",pm.obverb,pm.oblog);
  if (pm.initDB())
    return 10;
  // pruefe Tabelle <spooltab> und stelle sie ggf. her
  pruefspool(pm.My,pm.spooltab, pm.altspool, pm.obverb,pm.oblog);
  pruefouttab(pm.My,pm.touta, pm.obverb,pm.oblog);
  pruefinctab(pm.My,pm.tinca, pm.obverb,pm.oblog);
  if (pm.kez) {
    pm.korrerfolgszeichen();
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
  } else {
    pruefstdfaxnr(pm.My,pm.muser,pm.mpwd,pm.host,pm.obverb,pm.oblog);
    pruefprocgettel3(pm.My,pm.muser,pm.mpwd,pm.host,pm.obverb,pm.oblog);
    //  int qerg = mysql_query(My.conn,proc.c_str());
    // 1) nicht-pdf-Dateien in pdf umwandeln, 2) pdf-Dateien wegfaxen, 3) alle in warte-Verzeichnis kopieren, 4) in Spool-Tabelle eintragen
    //  vector<string> npdf, spdf;
    pm.DateienHerricht();  
    if (pm.obfcard) if (pm.obcapi) pm.obcapi= !pm.pruefcapi();
    if (pm.obmodem) if (pm.obhyla) pm.obhyla= !pm.pruefhyla();
    Log(Tx[T_Verwende]+blaus+(pm.obcapi?"Capisuite":"")+schwarz+(pm.obcapi&&pm.obhyla?", ":"")+blau+(pm.obhyla?"Hylafax":"")+schwarz+
        (!pm.obcapi&&!pm.obhyla?(blaus+Tx[T_kein_Faxprogramm_verfuegbar]+schwarz):""),1,pm.oblog);
    if (pm.loef || pm.loew || pm.loea) {
      if (pm.loef) pm.loeschefax(pm.obverb,pm.oblog);
      if (pm.loew) pm.loeschewaise(pm.obverb,pm.oblog);
      if (pm.loea) pm.loescheallewartende(pm.obverb,pm.oblog);
    } else {

      // hier stehen obcapi und obhyla fest
      pm.faxealle();
      // Dateien in Spool-Tabelle nach inzwischen verarbeiteten durchsuchen, Datenbank- und Dateieintraege korrigieren 
      pm.untersuchespool();
      pm.zeigweitere();
      pm.empfarch();
      Log(blaus+Tx[T_Ende]+schwarz,pm.obverb,pm.oblog);
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

