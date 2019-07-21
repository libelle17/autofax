#define DPROG "autofax"
#include <sys/utsname.h> // utsname
// fuer verschiedene Sprachen //α
enum T_      
{
	T_virtVorgbAllg,
	T_pvirtVorgbSpeziell,
	T_virtMusterVorgb,
	T_pvirtvorrueckfragen,
	T_virtrueckfragen,
	T_virtpruefweiteres,
	T_virtmacherkl_Tx_lgn,
	T_Fehler_beim_Pruefen_von,
	T_st_k,
	T_stop_l,
	T_DPROG_anhalten,
	T_anhalten,
	T_Cron_Aufruf_von,
	T_gestoppt,
	T_n_k,
	T_dszahl_l,
	T_Zahl_der_aufzulistenden_Datensaetze_ist_zahl_statt,
	T_Datenbank_nicht_initialisierbar_breche_ab,
	T_pvirtvorpruefggfmehrfach,
	T_pvirtfuehraus,
	T_in_pvirtfuehraus_pidw,
	T_virttesterg,
	T_virtzeigversion,
	T_virtzeigueberschrift, 
	T_Fuege_ein, //ω
	T_an_Fax,
	T_an_cFax,
	T_an_hFax,
	T_an_fFax,
	T_an,
	T_und,
	T_an_Mail,
	T_klar_an,
	T_liescapiconf,
	T_MeiEinrichtung,
	T_Mei_FaxUeberschrift,
	T_Der_regulaere_Ausdruck,
	T_konnte_nicht_kompiliert_werden_Fehler,
	T_Zufaxen,
	T_zufaxen,
	T_Warteauffax,
	T_warteauffax,
	T_Nichtgefaxt,
	T_nichtgefaxt,
	T_empfvz,
	T_zvz_k,
	T_zufaxenvz_l,
	T_faxt_die_Dateien_aus_pfad_anstatt_aus,
	T_wvz_k,
	T_wartevz_l,
	T_Dateien_warten_in_pfad_anstatt,
	T_ngvz_k,
	T_nichtgefaxtvz_l,
	T_Gescheiterte_Faxe_werden_hier_gesammelt_anstatt_in,
	T_evz_k,
	T_empfvz_l,
	T_Empfangsverzeichnis_fuer_Faxempfang,
	T_fbox_k,
	T_obfbox_l,
	T_Fritzbox_verwenden,
	T_fbankvz_k,
	T_fbankvz_l,
	T_Ankunftsverzeichnis_der_Fritzbox_ueber_CIFS,
	T_capi_k,
	T_obcapi_l,
	T_Capisuite_verwenden,
	T_hyla_k,
	T_obhyla_l,
	T_hylafax_verwenden,
	T_hz_k,
	T_hylazuerst_l,
	T_versuche_faxe_zuerst_ueber_Hylafax_wegzuschicken,
	T_mod_k,
	T_hmodem_l,
	T_Fuer_Hylafax_verwendetes_Modem,
	T_cz_k,
	T_capizuerst_l,
	T_versuche_faxe_zuerst_ueber_Capisuite_wegzuschicken,
	T_mc_k,
	T_maxcapiv_l,
	T_nach_zahl_Versuchen_Capisuite_wird_andere_Methode_versucht,
	T_mh_k,
	T_maxhylav_l,
	T_nach_zahl_Versuchen_Hylafax_wird_andere_Methode_verwendet,
	T_nach_zahl_Versuchen_fbfax_wird_andere_Methode_verwendet,
	T_mf_k,
	T_maxfbfxv_l,
	T_cuser_k,
	T_cuser_l,
	T_verwendet_fuer_Capisuite_Samba_den_Linux_Benutzer_string_anstatt,
	T_ckzl_k,
	T_cklingelzahl_l,
	T_Zahl_der_Klingeltoene_bis_Capisuite_den_Anruf_annimmt_anstatt,
	T_hkzl_k,
	T_hklingelzahl_l,
	T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt_anstatt,
	T_md_k,
	T_maxdials_l,
	T_Zahl_der_Wahlversuche_in_Hylafax,
	T_gz_k,
	T_gleichziel_l,
	T_Faxe_werden_auch_ohne_Faxerfolg_ins_Zielverzeichnis_kopiert,
	T_ocri_k,
	T_ocri_l,
	T_Text_aus_empfangenen_Faxen_wird_ermittelt,
	T_ocra_k,
	T_ocra_l,
	T_Text_aus_gesandten_Bildern_wird_ermittelt,
	T_afs_k,
	T_ams_k,
	T_kams_k,
	T_anfaxstr_l,
	T_anmailstr_l,
	T_klaranmailstr_l,
	T_mv_k,
	T_mailvon_l,
	T_smtpadr_k,
	T_smtpadr_l,
	T_portnr_k,
	T_portnr_l,
	T_smtpusr_k,
	T_smtpusr_l,
	T_smtppwd_k,
	T_smtppwd_l,
	T_Absender_mailadresse,
	T_als_Absender_zu_verwendende_Mailadresse,
	T_smtp_Adresse,
	T_smtp_Adresse_ohne_port,
	T_port_Nummer,
	T_Port_Nummer,
	T_smtp_usr,
	T_Smtp_usr,
	T_smtp_pwd,
	T_Smtp_pwd,
	T_mt_k,
	T_mailtit_l,
	T_mailtitle,
	T_Mailtitle,
	T_mb_k,
	T_mailbod_l,
	T_mailbody,
	T_Mailbody,
	T_faxnr_wird_hinter_string_erwartet_statt_hinter,
	T_mailadresse_wird_hinter_string_erwartet_statt_hinter,
	T_mailadresse_fuer_unverschluesselte_Mail_wird_hinter_string_erwartet_statt_hinter,
	T_acfs_k,
	T_ancfaxstr,
	T_faxnr_fuer_primaer_Capisuite_wird_hinter_string_erwartet_statt_hinter,
	T_ahfs_k,
	T_anhfaxstr_l,
	T_faxnr_fuer_primaer_hylafax_wird_hinter_string_erwartet_statt_hinter,
	T_as_k,
	T_anstr_l,
	T_Adressatenname_wird_hinter_string_erwartet_statt_hinter,
	T_us_k,
	T_undstr_l,
	T_Trennstring_string_fuer_mehrere_Adressaten_Telefonnummern_statt,
	T_find_k,
	T_find_l,
	T_Version_1_2_oder_3_Dateisuche_anstatt,
	T_loef,
	T_loeschefax_l,
	T_ein_Fax_nach_Rueckfrage_loeschen,
	T_loew,
	T_loeschewaise_l,
	T_Eintraege_aus,
	T_loeschen_zu_denen_kein_Datei_im_Wartevz_und_kein_Capi_oder_Hylafax_nachweisbar_ist,
	T_loea_k,
	T_loescheallew_l,
	T_alle_wartenden_Faxe_und_zugehoerige_Eintraege_aus,
	T_loeschen,
	T_erneut_k,
	T_erneutempf_l,
	T_empfangenes_Fax_erneut_bereitstellen,
	T_uml_k,
	T_umleiten_l,
	T_ausgehendes_Fax_vorzeitig_auf_zweitem_Weg_schicken,
	T_kez_k,
	T_korrerfolgszeichen_l,
	T_in_der_Datenbanktabelle,
	T_wird_das_Erfolgszeichen_korrigiert,
	T_bvz_k,
	T_bereinigevz_l,
	T_Dateien_aus_Warteverzeichnis_Gescheitertenvz_und_Gefaxtvz_gegen,
	T_pruefen_und_aufraeumen,
	T_lista_k,
	T_listausg_l,
	T_listet_Datensaetze_aus,
	T_mit_Erfolgskennzeichen_auf,
	T_listf_k,
	T_listfailed_l,
	T_ohne_Erfolgskennzeichen_auf,
	T_listi_k,
	T_listinca_l,
	T__auf,
	T_listw_k,
	T_listwart_l,
	T_listet_wartende_Faxe_auf,
	T_s_k,
	T_suche_l,
	T_suche_in_verarbeiteten_Faxen_nach,
	T_vc_k,
	T_vc_l,
	T_Capisuite_Konfigurationdateien_bearbeiten,
	T_vh_k,
	T_vh_l,
	T_Hylafax_Modem_Konfigurationsdatei_bearbeiten,
	T_konfcapi,
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
	T_Verschiebe,
	T_Fehler_beim_Verschieben,
	T_FehlerbeimUmbenennenbei,
	T_Kopiere_Doppelpunkt,
	T_Fehler_beim_Kopieren,
	T_Dateiname,
	T_schlechtgeformt,
	T_zielname_erstes_Ziel,
	T_zielname_Ausweichziel,
	T_Quelle_und_Ziel_gleich,
	T_entspricht,
	T_entsprichtnicht,
	T_entsprichtdoch,
	T_Muster_Doppelpunkt,
	T_pruefcvz,
	T_prueffbox,
	T_pruefcapi,
	T_capilaeuft,
	T_Module_geladen,
	T_Lade_Capi_Module,
	T_Kernelversion,
	T_KannFcpciNInstVerwCapiNicht,
	T_eine_neuere_Version_als_die_des_aktuellen_Kernels_installiert_worden_sein_dann_bitte_erneutes_Systemupdate,
	T_nichtgefFcpciMfdKinstallierwerden,
	T_Zur_Inbetriebnahme_der_Capisuite_muss_das_Modul_capi_geladen_werten,
	T_Bitte_zu_dessen_Verwendung_den_Rechner_neu_starten,
	T_aufrufen,
	T_Moment_muss_Kernel_herunterladen,
	T_Der_Kernel_hat_sich_offenbar_seit_dem_Einloggen_von,
	T_nach_,
	T_verjuengt_Bitte_den_Rechner_neu_starten_und_dann_mich_nochmal_aufrufen,
	T_Konnte,
	T_nichtstarten,
	T_StarteCapisuite,
	T_Capisuite_gestartet,
	T_konntecapisuiteservice,
	T_malnichtstartenverwN,
	T_pruefrules,
	T_pruefblack,
	T_haengean,
	T_an_mdpp,
	T_pruefsfftobmp,
	T_clieskonf,
	T_pruefmodcron,
	T_Zahl_der_SQL_Befehle_fuer_die_Absenderermittlung,
	T_SQL_Befehl_Nr,
	T_Zielmuster_Nr,
	T_Ziel_Nr,
	T_Zielmuster,
	T_Zahl_der_Muster_Verzeichnis_Paare_zum_Speichern_ankommender_Faxe,
	T_Verzeichnis_mit_zu_faxenden_Dateien,
	T_Verzeichnis_mit_wartenden_Dateien,
	T_Verzeichnis_mit_gescheiterten_Dateien,
	T_Verzeichnis_fuer_empfangene_Faxe,
	T_Soll_die_FritzBox_verwendet_werden,
	T_Mit_CIFS_gemountetes_Verzeichnis_mit_ankommenden_Faxen_der_Fritzbox,
	T_Soll_die_Capisuite_verwendet_werden,
	T_pruefisdn,
	T_ISDN_Karte_gefunden,
	T_Keine_ISDN_Karte_gefunden,
	T_mitCapi,
	T_aauf,
	T_Setze,
	T_ob_eine_Fritzcard_drinstak,
	T_Faxt_Dateien_aus_Verzeichnis_pfad_die,
	T_faxnr_enthalten_und_durch_soffice_in_pdf_konvertierbar_sind_und_traegt_sie,
	T_Tabellen,
	T_aein,
	T_Zustand_der_Dienste,
	T_pruefmodem,
	T_gibts,
	T_nicht,
	T_Kein_Modem_gefunden,
	T_Soll_Hylafax_verwendet_werden,
	T_Soll_vorrangig_capisuite_statt_hylafax_gewaehlt_werden,
	T_Zahl_der_Versuche_in_Capisuite_bis_andere_Methode_versucht_wird,
	T_Zahl_der_Versuche_in_hylafax_bis_andere_Methode_versucht_wird,
	T_Zahl_der_Versuche_in_fbfax_bis_andere_Methode_versucht_wird,
	T_Zahl_der_Klingeltoene_bis_Hylafax_den_Anruf_annimmt,
	T_Sollen_die_Dateien_unabhaengig_vom_Faxerfolg_im_Zielverzeichnis_gespeichert_werden,
	T_soll_Text_in_empfangenen_Faxen_mit_OCR_gesucht_werden,
	T_soll_Text_in_gesandten_Bildern_mit_OCR_gesucht_werden,
	T_Buchstabenfolge_vor_erster_Faxnummer,
	T_Buchstabenfolge_vor_erster_Mailadresse,
	T_Buchstabenfolge_vor_erster_Mailadresse_fuer_unverschluesselte_Mail,
	T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Capisuite,
	T_Buchstabenfolge_vor_erster_Fax_Nummer_primaer_fuer_Hylafax,
	T_Buchstabenfolge_vor_erstem_Adressaten,
	T_Buchstabenfolge_vor_weiterem_Adressaten_sowie_weiterer_Faxnummer,
	T_faxnr_wird_ersetzt_mit_der_Faxnr,
	T_Strich_ist_SQL_Befehl_loeschen_faxnr_wird_ersetzt_mit_der_Faxnr,
	T_In,
	T_keine_Datenbank_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
	T_Datenbank,
	T_nicht_ermittelbar_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
	T_keinmal_faxnr_gefunden_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
	T_koennte_ein_SQL_Fehler_sein_Wollen_Sie_den_SQL_Befehl_neu_eingeben,
	T_Wolle_Sie_noch_einen_SQL_Befehl_eingeben,
	T_zum_Streichen_Strich_eingeben,
	T_beim_letzten_fuer_alle_Uebrigen_nichts_eingeben,
	T_Zielverzeichnis_Nr,
	T_setzhylavz,
	T_aus_systemd_fax_service_Datei_ermittelt,
	T_aus_etc_init_d_hylafax_ermittelt,
	T_aus_seiner_ausschliesslichen_Existenz_ermittelt,
	T_aus_seinem_geringen_Alter_ermittelt,
	T_aus_mangelnder_Alternative_ermittelt,
	T_aus_Existenz_von,
	T_ermittelt,
	T_hylafax_Verzeichnis,
	T_pruefhyla,
	T_Konfiguration_von_hylafax_durch,
	T_muss_mindestens_2_sein_zur_Uebergabe_der_Nr_des_Anrufenden,
	T_vom,
	T_nichtbeschreibbar,
	T_Baudratevon,
	T_mit_af,
	T_zugeringVerwendeHylafaxnicht,
	T_mit_Baudrate,
	T_wird_verwendet,
	T_Pruefe_ob_Hylafax_gestartet,
	T_Hylafax_ohne_plus_entdeckt_muss_ich_loeschen,
	T_Hylafaxplus_entdeckt_muss_ich_loeschen,
	T_Hylafax_laeuft,
	T_Fehler_in_pruefhyla,
	T_Muss_Hylafax_installieren,
	T_ueber_den_Quellcode,
	T_Ergebnis_nach,
	T_ueber_das_Installationspaket,
	T_hylafehlt,
	T_Muss_falsches_hylafax_loeschen,
	T_Fuehre_aus_Dp,
	T_falls_es_hier_haengt_bitte_erneut_aufrufen,
	T_hylafaxspringtnichtan,
	T_verzeichnisse,
	T_Muster,
	T_Ziel,
	T_rufpruefsamba,
	T_Faxempfang,
	T_Gefaxt,
	T_zufaxenvz,
	T_pruefspool,
	T_pruefouta,
	T_eindeutige_Identifikation,
	T_Originalname_der_Datei,
	T_Originalname_der_Datei_vor_Umwandlung_in_PDF,
	T_zu_senden_an,
	T_wie_mailen,
	T_Adressat,
	T_Prioritaet_aus_Dateinamen,
	T_Zahl_der_bisherigen_Versuche_in_Capisuite,
	T_Zahl_der_bisherigen_Versuche_in_fbfax,
	T_Pfad_zur_Spooldatei_in_fbfax,
	T_Zahl_der_bisherigen_Versuche_in_Hylafax,
	T_Spooldatei_in_Capisuite,
	T_Pfad_zur_Spooldatei_in_Capisuite_ohne_abschliessendes_Verzeichnistrennzeichen,
	T_Aenderungszeit_der_CapiSpoolDatei,
	T_Aenderungszeit_der_CapiSpooldatei_im_time_Format,
	T_Aenderungszeit_der_Hylaspooldatei,
	T_Aenderungszeit_der_Hylaspooldatei_im_Time_Format,
	T_jobid_in_letztem_gescheitertem_hylafax,
	T_state_Feld_in_hylafax,
	T_Index_auf_urspruenglichen_Dateinamen,
	T_capistat,
	T_statuscode_in_letztem_gescheitertem_hylafax,
	T_status_in_letztem_gescheitertem_hylafax,
	T_capispooldateien_der_Capisuite,
	T_1_ist_erfolgreiche_Uebertragung_0_ist_fehlgeschlagen,
	T_Name_des_Adressaten_aus_Faxnummer_ermittelt,
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
	T_Name_des_Adressaten_aus_Dateiname,
	T_Archiv_fuer_die_erfolgreichen_Faxe,
	T_pruefudoc,
	T_Archiv_fuer_die_Dateinamen_vor_Aufteilung,
	T_pruefinca,
	T_identisch_zu_submid_in_outa,
	T_Verwende,
	T_kein_Faxprogramm_verfuegbar,
	T_aktiv,
	T_aktiviert,
	T_inaktiv,
	T_korrigiere,
	T_korrigierefbox,
	T_korrigierecapi,
	T_Folgende_Faxe_waren_mit_falschem_Erfolgskennzeichen_eingetragen_was_korrigiert_wird,
	T_Faxnr,
	T_zp,
	T_tries,
	T_size,
	T_docname,
	T_Folgende_Faxe_waren_nicht_eingetragen_was_korrigiert_wird,
	T_telnr,
	T_wiemail,
	T_Gabelung_zu_korrigiere_misslungen,
	T_Gabelung_zu_faxemitH_misslungen,
	T_Gabelung_zu_faxemitF_misslungen,
	T_Gabelung_zu_faxemitC_misslungen,
	T_Gabelung_zu_untersuchespool_misslungen,
	T_Gabelung_zu_zeigweitere_misslungen,
	T_Gabelung_zu_empfarch_misslungen,
	T_Gabelung_zu_wegfaxen_misslungen,
	T_Gabelung_zu_bereinigevz_misslungen,
	T_Gabelung_zu_vschlmail_misslungen,
	T_Gabelung_zu_klarmail_misslungen,
	T_empfarch,
	T_empfcapi,
	T_empfhyla,
	T_was,
	T_Bilddatei,
	T_avon,
	T_zupdf,
	T_pruefocr,
	T_Umwandlungvon,
	T_inPDFmit,
	T_misserfolg,
	T_Erfolg_af,
	T_Seiten,
	T_Installiere_ocrmypdf,
	T_Ihre_Python3_Version_koennte_mit,
	T_veraltet_sein_Wenn_Sie_Ihre_Faxe_OCR_unterziehen_wollen_dann_fuehren_Sie_bitte_ein_Systemupdate_durch_mit,
	T_pruefsoffice,
	T_pruefconvert,
	T_pruefunpaper,
	T_beendetErgebnis,
	T_holtif,
	T_nicht_angekommen,
	T_Dateien,
	T_nicht_verarbeitbar_Verschiebe_sie_nach,
	T_Zahl_der_empfangenen_Faxe,
	T_bereinigevz,
	T_Bereinige_Verzeichnis,
	T_DateienzahlimVz,
	T_Fehler_beim_Verschieben_Ausrufezeichen,
	T_gefunden_in_Tabelle,
	T_kommaFaxerfolg,
	T_Fehlt,
	T_Nicht_gefaxt,
	T_Aus2,
	T_wurden_in_Unterverzeichnisse_verschoben,
	T_tu_lista, 
	T_tu_listi, 
	T_Letzte,
	T_erfolgreich,
	T_erfolglos,
	T_versandte_Faxe,
	T_empfangene_Faxe,
	T_untersuchespool,
	T_zeigweitere,
	T_Weitere_Spool_Eintraege,
	T_sammlecapi,
	T_sammlefbox,
	T_bereinigefbox,
	T_bereinigecapi,
	T_Zahl_der_ueberpruefen_Datenbankeintraege,
	T_davon_gescheiterte_Faxe,
	T_davon_erfolgreiche_Faxe,
	T_davon_noch_wartende_Faxe,
	T_davon_nicht_in_Warteschlange,
	T_Verwaiste_Datei,
	T_geloescht_Fax_schon_in,
	T_archiviert_Ausrufezeichen,
	T_sammlehyla,
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
	T_setzhylastat,
	T_archiviere,
	T_obgescheitert,
	T_loeschefbox,
	T_loeschecapi,
	T_loeschehyla,
	T_Loesche_Fax_hylanr,
	T_erfolgreich_geloescht_fax_mit,
	T_Fehlermeldung_beim_Loeschversuch_eines_Hyla_Faxes_mit_faxrm,
	T_capiausgeb,
	T_fboxausgeb,
	T_Anwahlen,
	T_kommaDatei,
	T_bzw,
	T_hylaausgeb,
	T_suchestr,
	T_mitstr,
	T_wartende_Faxe,
	T_pruefstdfaxnr,
	T_prueffuncgettel3,
	T_aendere_fax,
	T_Welches_Fax_soll_geloescht_werden,
	T_Welches_Fax_soll_umgeleitet_werden,
	T_Soll_das_Fax,
	T_wirklich_geloescht_werden,
	T_umgeleitet_werden,
	T_Zahl_der_nicht_geloeschten_Dateien,
	T_hylanr,
	T_FBoxspooldatei,
	T_Capispooldatei,
	T_Gesamt,
	T_Kein_Fax_zum_Loeschen_vorhanden,
	T_empferneut,
	T_loeschewaise,
	T_loescheallewartenden,
	T_Welches_Fax_soll_erneut_empfangen_werden_bitte_Nr_in_der_1_Spalte_eingeben_a_alle_Angezeigten,
	T_Bearbeite,
	T_Aus,
	T_zu_loeschen,
	T_Sollen_wirklich_alle,
	T_wartenden_Faxe_geloescht_werden,
	T_waisen_Faxe_geloescht_werden,
	T_Keine_waisen_Faxe_zum_Loeschen_da,
	T_Keine_wartenden_Faxe_zum_Loeschen_da,
	T_inspoolschreiben,
	T_wegfaxen,
	T_obfboxmitDoppelpunkt,
	T_obcapimitDoppelpunkt,
	T_obhylamitDoppelpunkt,
	T_obkmailmitDoppelpunkt,
	T_obvmailmitDoppelpunkt,
	T_Unterverzeichnis,
	T_passt_zu_Muster,
	T_passt_zu_keinem_Muster,
	T_war_schon,
	T_kommt_noch,
	T_Endung,
	T_Stamm,
	T_Anfangsteil,
	T_Faxnummer_zu,
	T_gefunden_dp,
	T_Name_zu,
	T_FehlerbeimUmbenennen,
	T_ErstelledurchBenennen,
	T_ErstelledurchKopieren,
	T_nichtfaxbar,
	T_abgebrochen,
	T_Gesammelt_wurden,
	T_aus,
	T_verarbeitete_Nicht_PDF_Dateien,
	T_lstatfehlgeschlagen,
	T_beiDatei,
	T_verarbeitete_PDF_Dateien,
	T_beiSQLAbfrage,
	T_ZahldDSmwegzuschickendenFaxenin,
	T_PDFDatei,
	T_Fehler_zu_faxende_Datei,
	T_nicht_gefunden_Eintrag_ggf_loeschen_mit_,
	T_in_wegfaxen,
	T_in_korrerfolgszeichen,
	T_WVZinDatenbank,
	T_inDbc,
	T_faxemitH,
	T_faxemitF,
	T_inDBh,
	T_inDBf,
	T_inDBk,
	T_SpoolDateierstellt,
	T_SpoolDatei,
	T_SpoolPfad,
	T_faxemitC,
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
	T_nicht_gefunden_kein_Datenbankeintrag,
	T_HylafaxBefehl,
	T_FbfaxBefehl,
	T_RueckmlgZeile,
	T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Erfolg_gesetzt_werden,
	T_Dateidatum,
	T_pages,
	T_Bei_folgenden_Faxen_musste_das_Erfolgskennzeichen_gemaess_Hylafax_Protkolldatei_auf_Misserfolg_gesetzt_werden,
	T_Insgesamt,
	T_Fundstellen_von,
	T_Keine_Fundstellen_von,
	T_SQL_Befehl,
	T_nurempf_k,
	T_nurempf_l,
	T_empfaengt_nur,
	T_nursend_k,
	T_nursend_l,
	T_sendet_nur,
	T_instsfftobmp,
  T_kompilier,
	T_nextnum,
	T_scheitere,
	T_korrigierehyla,
	T_oder_,
	T_bzw_,
	T_std_mailtit,
	T_std_mailbod,
	T_mail_gesandt_0_nein_1_ja,
	T_Prioritaet_von_capisuite_1_3,
	T_Prioritaet_von_hylafax_1_3,
	T_Prioritaet_von_fritzbox_1_3,
	T_cp_k,
	T_cprio_l,
	T_hp_k,
	T_hprio_l,
	T_fp_k,
	T_fprio_l,
	T_Mit_welcher_Prioritaet_soll_capisuite_verwendet_werden_1_3,
	T_Mit_welcher_Prioritaet_soll_hylafax_verwendet_werden_1_3,
	T_Mit_welcher_Prioritaet_soll_fritzbox_verwendet_werden_1_3,
	T_sortprio,
	T_standardprio,
	T_MAX //α
}; // enum T_ //ω

enum FaxTyp:uchar {keintyp=0,fritz,capi,hyla,kmail,vmail};
enum FxStat:uchar {init/*0*/,gestrichen,schwebend,wartend/*3*/,blockiert/*4*/,bereit/*5*/,verarb/*6*/,gesandt/*7*/,gescheitert/*8*/,fehlend,woasined};
enum hyinst {keineh,hysrc,hypak,hyppk}; // hyla source, hyla Paket, hylaplus Paket
class fsfcl; // Faxsendfile
class hhcl; // Programmparameter
void dorename(const string& quelle, const string& ziel, const string& cuser=nix, uint *vfehlerp=0, uchar schonda=0, int obverb=0, int oblog=0,
                  stringstream *ausgp=0);
class zielmustercl; // fuer die Verteilung der erfolgreich gefaxten Dateien auf verschiedene Dateien
string kopiere(const string& qdatei, const string& zield, uint *kfehler, const uchar wieweiterzaehl, int obverb=0, int oblog=0);
string kopiere(const string& qdatei, const vector<shared_ptr<zielmustercl>>& zmp, uint *kfehler, const uchar wieweiterzaehl, int obverb=0, int oblog=0);
string zielname(const string& qdatei, const string& zielvz,uchar wieweiterzaehl=0, string* zieldatei=0, uchar* obgleichp=0, 
                int obverb=0, int oblog=0, stringstream *ausgp=0);
string zielname(const string& qdatei, const vector<shared_ptr<zielmustercl>>& zmup,uchar wieweiterzaehl=0, string* zieldatei=0, uchar* obgleichp=0, int obverb=0, 
                int oblog=0, stringstream *ausgp=0);
void pruefrules(int obverb, int oblog);
void useruucp(const string& huser, const int obverb, const int oblog);
const string& pruefspool(DB *My,const string& spooltab, const string& altspool, const int obverb, const int oblog, uchar direkt=0);
void pruefouttab(DB *My, const string& touta, const int obverb, const int oblog, const uchar direkt=0);
void pruefudoc(DB *My, const string& tudoc, const int obverb, const int oblog, const uchar direkt=0);
void pruefinctab(DB *My, const string& tinca, const int obverb, const int oblog, const uchar direkt=0);
template<typename T> string verschiebe(const string& qdatei, const T/*string,zielmustercl*/& zielvz, const string& cuser=nix, uint *vfehlerp=0, const uchar wieweiterzaehl=1, int obverb=0,int oblog=0, stringstream *ausgp=0,const uchar auchgleiche=0);
const char* FxStatS(const FxStat *const i);
void pruefstdfaxnr(DB *Myp, const string& usr, const string& host, const int obverb, const int oblog);
void prueffuncgettel3(DB *const Myp, const string& usr, const string& host, int obverb, int oblog);
inline const int ppri(const int iprio);
void liesvw(const string& vwdt,string* fbzpp=0,string* minabstp=0, string* telnrp=0, string* originalp=0,string* fbdialsp=0, string* fbmaxdialsp=0, FxStat* fboxstatp=0);


// Steuerung der Abspeicherung gesendeter Faxe je nach Muster
struct zielmustercl 
{
    string muster;
    string ziel;
  // beim letzten Element muss ziel leer sein!
    regex_t regex;
    // wird nur in Vorgaben gebraucht:
    zielmustercl(const char * const muster,const char * const ziel);
    zielmustercl(const char * const muster,const string& ziel);
    zielmustercl(const string& muster,const string& ziel);
    zielmustercl();
    int kompilier(const uchar obext=1);
    int setzemuster(const string& vmuster,const uchar obext=1);
    const string& holmuster() const;
    const string& holziel() const;
    int obmusterleer() const;
}; // class zielmustercl

struct urfxcl // urspruengliche Dateidaten vor Aufteilung an verschiedene Faxadressaten
{
    string teil;
    string ur;
	  unsigned pprio; // Prioritaet der Fax-Programme: 0= per Konfigurationsdatei, 1=capi, 2=hyla, 3=fbfax per Faxdateiname, 
										// s. anfaxstr-Befuellung in inspoolschreiben() 
    urfxcl(const string& teil, const string& ur,unsigned pprio): teil(teil), ur(ur), pprio(pprio) {}
};

struct fxfcl // Faxfile
{
    string npdf; // nicht-PDF
    string spdf; // schon-PDF
    string ur;   // urspruenglicher Dateinamen
	  unsigned pprio;// Prioritaet der Fax-Programme: 1=fbfax, 2=capi, 3=hyla per Konfigurationsdatei, 11=fbfax, 12=capi, 13=hyla, 14=vschlmail, 15=klarmail per Faxdateiname
		ulong pseiten; // PDF-Seitenzahl
    fxfcl(const string& npdf,const string& spdf,const string& ur,unsigned pprio): npdf(npdf),spdf(spdf),ur(ur),pprio(pprio),pseiten(0) {}
    // nur fuer Initialisierung in fsfcl, Konstruktur /*1*/, nur fuer wegfaxen
    fxfcl(unsigned pprio, const string& npdf,const string& spdf,ulong pseiten): npdf(npdf),spdf(spdf),pprio(pprio),pseiten(pseiten) {}
    fxfcl(const string& spdf,const string& ur,unsigned pprio): npdf(""),spdf(spdf),pprio(pprio),pseiten(0) {}
    fxfcl() {}
};

struct fsfcl : public fxfcl // Faxsendfile
{
	  void ausgeb() {
			cout<<"id : "<<blau<<id<<schwarz<<", telnr: "<<blau<<telnr<<schwarz<<", mailges: "<<blau<<mailges<<schwarz<<", original: "<<blau<<original
				<<schwarz<<", origvu: "<<blau<<origvu<<schwarz<<", fobfbox: "<<blau<<(int)fobfbox<<schwarz<<", fobcapi: "<<blau<<(int)fobcapi<<schwarz<<", fobhyla: "<<
				blau<<(int)fobhyla<<schwarz<<", fobkmail: "<<blau<<(int)fobkmail<<schwarz<<", fobvmail: "<<blau<<(int)fobvmail<<schwarz<<", idalt: "<<blau<<idalt<<
				schwarz<<", fbdials: "<<blau<<fbdials<<schwarz<<", fbsdt: "<<blau<<fbsdt<<schwarz<<endl;
		}
    string id;   // id in spooltab
    string telnr;    // Telnr. des Adressaten
    string capisd; // capispooldatei
    int capids;  //capidials
    string hylanr; // hylanr
		string hqdt; // z.B. /var/spool/hylafax/doneq/q9902
    int hdialsn; // hyladials
		string hpages; // Seitenzahl
    uchar fobfbox{0}; // ob es jetzt mit Fritzbox weggefaxt werden muss
    uchar fobcapi{0}; // ob es jetzt mit Capi weggefaxt werden muss
    uchar fobhyla{0}; // ob es jetzt mit Hyla weggefaxt werden muss
    uchar fobkmail{0}; // ob es jetzt mit klarmail weggeschickt werden muss
    uchar fobvmail{0}; // ob es jetzt mit vschlmail weggeschickt werden muss
    string adressat; // Name des Adressaten aus Faxdatei
		string idalt; // id in altspool
		string mailges; // ob mail gesandt
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
		time_t xtts=0;  // Datum aus xferfaxlog
		time_t killtime=0;
		string number;   // Telefonnummer
    string hdials;   // hyladials
		string maxdials; // maxdials (hylafax)
    string hdd;      // hdateidatum
		string fbdials;  // fbdials
	  string fbmaxdials;// maxdials (fbox)
		string fbsdt;    // fbspooldt
		time_t fbzp;     // fbzeitpunkt
    string sendqgespfad; // kann fuer capi oder hyla verwendet werden
    string hgerg;  // hyla_gescheitert_erg
    int hversuzahl;
    FxStat fboxstat=init;// 1=wartend, 2=gesandt, 3=gescheitert, 4=fehlend (in spool keine Capi-Datei eingetragen oder die eingetragene gibts nicht)
    FxStat capistat=init;// 1=wartend, 2=gesandt, 3=gescheitert, 4=fehlend (in spool keine Capi-Datei eingetragen oder die eingetragene gibts nicht)
    FxStat hylastat=init;// 1=wartend, 2=gesandt, 3=gescheitert, 4=fehlend (in spool keine hyla-Datei eingetragen oder die eingetragene gibts nicht)
		int wiemail{0};
  private:
  public:
		void archiviere(DB *const My, hhcl *const hhip, const struct stat *const entryp,const uchar obgescheitert, const FaxTyp ftyp, 
		                uchar *gel, const size_t aktc, const int obverb, const int oblog);
		int loeschefbox(hhcl *const hhip, const int obverb, const int oblog);
		int loeschecapi(const int obverb, const int oblog);
    int loeschehyla(hhcl *const hhip, const int obverb, const int oblog);
    /*1*/fsfcl(const string id, const string npdf, const string spdf, const string telnr, unsigned pprio, const string capisd, int capids, 
		           const string hylanr, int hdialsn, uchar fobfbox, uchar fobcapi, uchar fobhyla, const string adressat, ulong pseiten, string idalt,int wiemail):
         fxfcl(pprio,npdf,spdf,pseiten), id(id), telnr(telnr), capisd(capisd), capids(capids), 
         hylanr(hylanr), hdialsn(hdialsn), fobfbox(fobfbox), fobcapi(fobcapi), fobhyla(fobhyla), adressat(adressat),idalt(idalt),wiemail(wiemail) {}
    /*2*/fsfcl(const string id,const string original): id(id), original(original) {}
    /*3*/fsfcl(const string id, const string capisd, const string hylanr, string const cspf): id(id), capisd(capisd), hylanr(hylanr), cspf(cspf) {}
    /*4*/fsfcl(const string& hylanr): hylanr(hylanr) {}
    /*5*/fsfcl(const string sendqgespfad, FxStat capistat): sendqgespfad(sendqgespfad), capistat(capistat) {}
		/*6*/fsfcl(const string& original, const string& origvu, uchar cnr): original(original), origvu(origvu) {}
		/*7*/fsfcl() {}
    void setzfboxstat(hhcl *hhip, struct stat *entrysendp,uchar erweitert=0);
    void setzcapistat(hhcl *hhip, struct stat *entrysendp);
    void fboxausgeb(hhcl *const hhip, stringstream *ausgp, uchar fuerlog=0, int obverb=0, int oblog=0,ulong faxord=0);
    void capiausgeb(hhcl *const hhip, stringstream *ausgp, const string& maxctrials, uchar fuerlog=0, int obverb=0, int oblog=0,ulong faxord=0);
    void hylaausgeb(stringstream *ausgp, hhcl *hhip/*, int obsfehlt*/, uchar fuerlog=0, int obverb=0, uchar obzaehl=0, int oblog=0);
    int holcapiprot(int obverb);
		void scheitere(const string& wvz, const string& ngvz, const string& cuser, const string* const ziel=0, const int obverb=0, const int oblog=0);
}; // class fsfcl


//α
class hhcl:public dhcl
{
	private: 
		uchar anhl{0};    // <DPROG> anhalten
		string dszahl{"30"}; // Datensatzzahl fuer Tabellenausgaben
		//ω
		static const string initdhyladt; // /etc/init.d/hylafax
		uchar initdhyladt_gibts{0}; // Datei initdhyladt existiert
		svec modems;       // gefundene Modems
		uchar modemgeaendert{0}; // hmodem neu gesetzt
		int prios[3]{0}; // prios[0] = Priorität von fritzbox, prios[1] = Priorität von capisuite, prios[2] = Priorität von hylafax
    int clprios[3]; // commandline-Prioritaeten
		// int hylazuerst{-1};  // ob ein Fax zuerst ueber Hylafax versucht werden soll zu faxen
		//    string hmodemstr; // Erkennung des Faxgeraetes nach /dev/tty, Standard ACM
		string maxcapiv; // maximale Versuchnr in Capi, bis andere Methode versucht wird
		string maxhylav; // maximale Versuchsnr in Hylafax, bis andere Methode versucht wird
		string maxfbfxv; // maximale Versuchsnr in fbfax, bis andere Methode verwendet wird
		string maxhdials;     // Zahl der Wahlversuche in Hylafax
		string maxcdials;    // Zahl der Wahlversuche in Capisuite
		int gleichziel{-1}; // faxe auch ohne Fax-Erfolg auf Zielverzeichnis abspeichern
		int obocri{-1}; // empfangene Faxe OCR unterziehen
		int obocra{-1}; // gesandte Bilder OCR unterziehen
		string anfaxstr, ancfaxstr, anhfaxstr, anffaxstr; // 'an Fax', "an cFax", "an hFax", "an fFax"
		string anstr; // ' an '
		string undstr;  //  'und'
		string anmailstr, klaranmailstr; // 'an Mail', 'klar an'
		string mailvon, smtpadr, portnr, smtpusr, smtppwd;
		string mailtit,mailbod;

		uchar capizukonf{0}; // capi zu konfigurieren
		uchar hylazukonf{0}; // hyla zu konfigurieren
		int findv{1}; // find-Version (1=linux find, 2=intern mit readdir, 3=intern mit nftw 

		confdcl *cfaxcp{0}; // Zeiger auf ausgelesene /etc/capisuite/fax.conf
		const string s1{"mv -n "};
		//		const string s2{"/2200/* "};
		//schlArr hylcnfA; // fuer q1234 o.ae.
		uchar hgelesen{0}; // Protokolldatei war auslesbar
		static constexpr const char *moeglhvz[2]{"/var/spool/fax","var/spool/hylafax"};
		string huser{"uucp"}; // "uucp" oder "fax"
		uchar obfrbox{1};    // ob Fritzbox im System gefunden
		uchar obfcard{1};    // ob Fritzcard eingesteckt
		uchar obfcgeprueft{0}; // ob schon geprueft, ob Fritzcard eingesteckt
		uchar obmodem{1};    // ob Modem angeschlossen
		uchar obmdgeprueft{0}; // ob schon geprueft, ob Modem verfuegbar
		uchar obocrgeprueft{0}; // ob ocrmypdf installiert ist
		const string altspool{"altspool"}; // Historie der Spooltabelle
		const string udoctab{"udoc"};
		uchar obvi{0};   // ob Konfigurationsdatei editiert werden soll
		uchar obvc{0};   // ob Capisuite-Konfigurationsdateien betrachtet werden sollen
		uchar obvh{0};   // ob Hylafax-Konfigurations- und Logdateindatei betrachtet werden sollen
		uchar obvs{0};   // ob Quelldateien bearbeitet werden sollen
		uchar loef{0};   // loesche eine Fax-Datei
		uchar loew{0};  // loeschewaise in der Datenbank, aber nicht mehr real nachweisbare Dateien in der Datenbank loeschen
		uchar loea{0}; // loesche alle wartenden Faxe und zugehoerige Dateieintraege
		uchar loee{0}; // empfangene Dateien loeschen, die nicht verarbeitet werden koennen
		uchar erneut{0};  // empfangenes Fax erneut bereitstellen
		uchar uml{0}; // umleiten: vorzeitig den zweiten Weg aktivieren
		uchar kez{0};    // korrigiere Erfolgskennzeichen
		uchar bvz{0};    // bereinige Gescheitertenverzeichnis, letztes Gefaxtverzeichnis und Warteverzeichnis
		uchar tulista{0};   // liste Archiv auf
		uchar tulistf{0};   // liste gescheiterte auf
		uchar tulisti{0};   // liste Eingegangene auf
		uchar tulistw{0};   // liste wartende auf
		uchar nurempf{0}; // nur Empfang aufrufen
		uchar nursend{0}; // nur Senden aufrufen
		string suchstr;  // Wortteil, nach dem in alten Faxen gesucht werden soll
		size_t faxord{0}; // Ordinalzahl des Faxes unter allen anstehenden Faxen
		ulong geszahl{0};
		ulong ankzahl{0}; // Zahl der angekommenen Faxe
		ulong dbzahl{0}; // Zahl der ueberprueften Datenbankeintraege
		ulong wzahl{0};
		ulong ezahl{0}; // Zahl der Erfolgreichen
		ulong gzahl{0};
		ulong fzahl{0};
		ulong weizahl{0}; // Zahl der weiteren wartenden Faxe, die nicht in der Spooltabelle dieses Programms eingetragen sind
		int obfa[3]{-1}; // ob jew.faxart verwendet: 0=fbox, 1=capi, 2=hyla, gesetzt in: pruefisdn(), lieskonfein(), rueckfragen(), getcommandline(), main()
		//    string hmodemstr; // Erkennung des Faxgeraetes nach /dev/tty, Standard ACM
		string fbwvz; // /var/spool/fbfax/waiting
		string fbgvz; // /var/spool/fbfax/faxed
		string fbnvz; // /var/spool/fbfax/notfaxed
		string hmodem;    // erkanntes und laufendes Modem ttyACM0
		//    string hmodname;  // ttyACM0
		string cuser; // Linux-Benutzer fuer Capisuite, Samba
		const string tudoc{"udoc"}; // MariaDB-Tabelle fuer gesandte oder gescheiterte Faxe
		const string tinca{"inca"}; // MariaDB-Tabelle fuer empfangene Faxe
		const string touta{"outa"}; // MariaDB-Tabelle fuer gesandte oder gescheiterte Faxe; in fsfcl->archiviere benoetigt
		const string spooltab{"spool"}; // in fsfcl->archiviere benoetigt

		string zufaxenvz;
		string wvz; // Warteverzeichnis
		string ngvz; // Nichtgefaxt-Verzeichnis (Gescheiterte)
		string empfvz; // Empfangsverzeichnis
		string fbankvz;  // auf CIFS gemountetes NAS-Verzeichnis der Fritzbox mit ankommenden Faxen

		string countrycode; // Landesvorwahl
		string LongDistancePrefix; // Vorsatz fuer ausserorts
		string InternationalPrefix; // Vorsatz fuer ausserlandes
		string cklingelzahl; // Zahl der Klingeltoene, bis Capisuite einen Anruf annnimmt
		string hklingelzahl; // Zahl der Klingeltoene, bis Hylafax einen Anruf annnimmt
		string cfaxconfdt; // /etc/capisuite/fax.conf oder /usr/local/etc/capisuite/fax.conf laut Handbuch
		string cfaxconfeigdt; // ~/autofax/cfaxconfdt
		string spoolcapivz; // Verzeichnis der Capi-Spool-Dateien /var/spool/capisuite/
		string ccapiconfdt; // /etc/capisuite/capisuite.conf oder /usr/local/etc/capisuite/capisuite.conf laut Handbuch
		string cempfavz; //  /var/spool/capisuite/" DPROG "arch/
		string cfaxuservz;    // /var/spool/capisuite/users/
		string nextdatei;  // /var/spool/capisuite/users/<user>/sendq/fax-nextnr
		string cfaxusersqvz;    // /var/spool/capisuite/users/<user>/sendq
		string cfaxuserrcvz;    // /var/spool/capisuite/users/<user>/received
		string cfaxuserrcfalschevz;  // /var/spool/capisuite/users/<user>/received/falsche
		string cdonevz; // Capisuite-Archiv: /var/spool/capisuite/done
		string cfailedvz; // Capisuite-Archiv der gescheiterten /var/spool/capisuite/failed
		string /*spool_dir(spoolcapivz),*/fax_user_dir,/*send_tries(maxcdials),*/send_delays,outgoing_MSN, dial_prefix,fax_stationID,fax_headline,fax_email_from,outgoing_timeout; // capisuite: fax.conf
		string cdn[4]; // in capisuite.conf genannte Dateien: incoming_script, log_file, log_error, idle_script
		string citycode;    // Ortsvorwahl
		string msn;         // MSN fuer Fax
		string LocalIdentifier; // eigener Namen fuer Hylafax bis 10 Buchstaben
		string varsphylavz; // Verzeichnis der Hyla-Spool-Dateien /var/spool/hylafax oder /var/spool/fax
		string spoolvz; // Kandidat SPOOL in Konfigurkationsdatei dafür
		string hylafax_homevz; // Kandidat HYLAFAX_HOME in Konfigurkationsdatei dafür
		string cFaxUeberschrift; // eigener Namen fuer Capisuite bis 20 Buchstaben
		schAcl<optcl> opvsql=schAcl<optcl>("opvsql"),opvzm=schAcl<optcl>("opvzm"); // Optionen
		string host{"localhost"};  // fuer MySQL/MariaDB

		schAcl<WPcl> *cfcnfCp{0}/*schAcl<WPcl>("cfcnfC")*/; // Capikonfiguration aus fax.conf
		schAcl<WPcl> *cccnfCp=0; // Capikonfiguration aus capisuite.conf
		schAcl<WPcl> *hfcnfCp=0; // Hylakonfiguration
		schAcl<WPcl> *hyaltcnfCp=0; // Hylakonfiguration
		string hempfavz;    // var/spool/(hyla)fax/" DPROG "arch
		string hdoneqvz; // /var/spool/hylafax/doneq
		string harchivevz; // /var/spool/hylafax/archive
		string modconfdt; // hylafax-Konfigurationsdatei, z.B. /var/spool/hylafax/etc/config.ttyACM0
		string faxgtpfad;   // /usr/lib/fax/faxgetty oder /usr/local/sbin/faxgetty
		string faxqpfad,hfaxdpfad; // /usr/local/sbin/faxq, /usr/local/sbin/hfaxq
		string countrycode_dt,areacode_dt,faxnumber_dt,longdistanceprefix_dt,internationalprefix_dt,ringsbeforeanswer_dt,localidentifier_dt,maxdials_dt;
    svec vinca;
		unsigned tage{0}; // fuer korrigierecapi und korrigierehyla 
		string hsendqvz; // /var/spool/hylafax/sendq // in fsf->loeschehyla benoetigt
		servc*sfaxq{0}, *shfaxd{0}, *shylafaxd{0}, *scapis{0}, *sfaxgetty{0};  // benoetigt in loeschehyla
		string xferfaxlog; // varsphylavz + "/etc/xferfaxlog";  // benoetigt in loeschehyla
	protected: //α
		string p1;
		int p2;
		string p3;
		uchar oblista{0};
		long listz{30}; //ω

		size_t sqlz0{0}; // Index in opn mit erster SQL-Option
		size_t sqlzn{0}; // Zahl der SQL-Befehle numerisch
		string* sqlp{0}; // Array der SQL-Befehle
		//    string sqlz;  // Zahl der SQL-Befehle
		//    size_t sqlzn=0; // Zahl der SQL-Befehle numerisch
		svec sqlVp; // Vector der Vorgabe-SQL-Befehl
		vector<shared_ptr<string>> sqlrp; // vector der rueckfrage-SQL-Befehle

		size_t zmz0{0}; // Index in opn mit erster Zielmusterpaaroption, wird vielleicht nicht gebraucht
		size_t zmzn{0}; // Zahl der Zielmusterpaare numerisch
		string *zmmp{0}; // Array der Zielmuster
		string *zmzp{0}; // Array der Ziele
		vector<shared_ptr<zielmustercl>> zmsp; // Zielmusterzeiger
		vector<zielmustercl> zmVp; // Zielmuster aus Vorgaben
		vector<shared_ptr<string>> zmmrp; // vector der rueckfrage-Zielmuster
		vector<shared_ptr<string>> zmzrp; // vector der rueckfrage-Ziele
		string virtvz; //	instvz+"/ocrv";
	  string ocrmp; //	virtvz+"/bin/ocrmypdf";

	public: //α //ω
	private: //α //ω
		void liescapiconf();
		void konfcapi(); // aufgerufen in pruefcapi
		void capisv();
    int prueffbox();
		int pruefcapi();
		void pruefisdn();
		int cservice();
		void clieskonf();
		void pruefcvz();
		void pruefsfftobmp();
		void instsfftobmp();
		void nextnum();
		void pruefmodcron();
		void dovc();
		void virttesterg(); //α
		void virtlieskonfein();
		void virtautokonfschreib();
		void anhalten(); //ω
		int setzhylavz(); // sucht das Hylaverzeichnis und setzt varsphylavz darauf, return 0, wenn nicht gefunden dann varsphylavz="", return 1
		void setzmodconfd();
		int hconfigtty();
		int pruefhyla();
		void dovh();
    int hservice_faxq_hfaxd();
		void setzfaxgtpfad();
		int hconfig() const;
		void hfaxsetup();
    void hliesconf();
		void machopvzm();
		void verzeichnisse();
    void rufpruefsamba();
    void korrigierefbox(const unsigned tage=90,const size_t aktc=1);
    void korrigierecapi(const unsigned tage=90,const size_t aktc=1);
    void korrigierehyla(const unsigned tage=90,const size_t aktc=2);
    int pruefsoffice(const string soffname,uchar mitloe=0);
    void bereinigevz(const size_t aktc/*=0*/);
		void dober(const string& wvz, set<string>& fdn,uchar aucherfolg,stringstream *ausgp,const size_t aktc,
				set<string> *cmisslp,set<string> *cgelup,set<string> *hmisslp,set<string> *hgelup);
    string getzielvz(const string& datei); // in bereinigevz
    string neuerdateiname(const string& qpfad); // in wegfaxen
    void tu_lista(const string& oberfolg,const string& submids=nix);
		void tu_listi(const uchar zurauswahl=0);
		void untersuchespool(uchar mitupd=1,const size_t aktc=3); // faxart 0=capi, 1=hyla 
		void bestimmtage();
    void zeigweitere();
    void sammlefbox(vector<fsfcl> *fsfvp,const size_t aktc);
    void sammlecapi(vector<fsfcl> *fsfvp,const size_t aktc);
    void bereinigefbox(const size_t aktc);
    void bereinigecapi(const size_t aktc);
    void sammlehyla(vector<fsfcl> *fsfvp,const size_t aktc);
		void setzhylastat(fsfcl *fsf, uchar *hyla_uverz_nrp, uchar startvznr,int *obsfehltp=0, 
				struct stat *est=0);
    int xferlog(fsfcl *fsfp/*, string *totpages=0, string *ntries=0, string *totdials=0, string *tottries=0, string *maxtries=0*/);
    string stdfaxnr(const string& faxnr); // benoetigt in fsfcl->archviere
		void getSender(const string& faxnr, string *getnamep, string *bsnamep,const size_t aktc); // benoetigt in fsfcl->archiviere
		void hylasv1(); // in loeschehyla benoetigt
		void hylasv2(hyinst hyinstart); // // in loeschehyla benoetigt
		void suchestr();
		int aenderefax(const int aktion=0,const size_t aktc=0); // aktion: 0=loeschen, 1=umleiten
		void empferneut();
    size_t  loeschewaise();
		size_t loescheallewartenden();
		void inspoolschreiben(const size_t aktc);
		void wegfaxen(const size_t aktc);
		int obvorbei(const string& vzname,uchar *auchtag);
    void WVZinDatenbank(vector<fxfcl> *const fxvp, size_t aktc); // in wegfaxen
		void inDbc(DB *My, const string& spooltab, const string& altspool, const string& spoolg, const fsfcl *const fsfp, 
		           const string& telnr, const size_t aktc);
		void faxemitC(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& ff);
		void faxemitH(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& ff);
		void faxemitF(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& ff);
		void vschlmail(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& ff);
		void klarmail(DB *My, const string& spooltab, const string& altspool, fsfcl *fsfp, const string& ff);
		void inDBh(DB *My, const string& spooltab, const string& altspool, const string& hylaid, 
				const fsfcl *const fsfp,const string *const tel, const size_t aktc);
		void inDBf(DB *My, const string& spooltab, const string& altspool, const string& fbvwdt,const fsfcl *const fsfp,const size_t aktc);
		void inDBk(DB *My, const string& spooltab, const string& altspool, const fsfcl *const fsfp, const size_t aktc);
		void standardprio(const int obmitsetz);
		int priorang(const int rnr);
	protected: //α
		// void virtlgnzuw(); // wird aufgerufen in: virtrueckfragen, parsecl, lieskonfein, hcl::hcl nach holsystemsprache
		void virtVorgbAllg();
		void pvirtVorgbSpeziell()
#ifdef VOMHAUPTCODE
			__attribute__((weak)) // implementationsspezifische Vorgaben, Modul vgb.cpp)
#endif
			;
		void virtinitopt(); // (programm-)spezifische Optionen
		void pvirtmacherkl();
		void virtMusterVorgb();
		void pvirtvorzaehler();
		void virtzeigversion(const string& ltiffv=string());
		void pvirtvorrueckfragen();
		void virtrueckfragen();
		void neurf();
		void pvirtnachvi();
		void pvirtvorpruefggfmehrfach();
		void virtpruefweiteres();
		void virtzeigueberschrift();
		void pvirtfuehraus();
		void virtschlussanzeige();
		void zeigdienste(); //ω
		void pruefmodem();
    void empfarch(uchar obalte=0);
		void empfhyla(const string& ganz,size_t aktc, const uchar was,const string& nr=nix);
		void empfcapi(const string& stamm,size_t aktc, const uchar was,const string& nr=nix);
	  int zupdf(const string* quell, const string& ziel, ulong *pseitenp=0, int obocr=1, int loeschen=1); // 0=Erfolg
    int pruefocr();
    int pruefconvert();
		int holtif(const string& datei,ulong *seitenp=0,struct tm *tmp=0,struct stat *elogp=0,
		           string *absdrp=0,string *tsidp=0,string *calleridp=0,string *devnamep=0);
		void pruefunpaper();
		void unpaperfuercron(const string& ocrprog);
	public: //α
		hhcl(const int argc, const char *const *const argv);
		~hhcl();
		friend class fsfcl;
}; // class hhcl //ω
