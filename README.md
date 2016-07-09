
<h1 align="center">AUTOFAX (Version 0.40271)</h1>

<a href="#NAME">NAME</a><br>
<a href="#SYNOPSIS">SYNOPSIS</a><br>
<a href="#KURZBESCHREIBUNG">KURZBESCHREIBUNG</a><br>
<a href="#INSTALLATION">INSTALLATION</a><br>
<a href="#GEBRAUCH">GEBRAUCH</a><br>
<a href="#OPTIONEN">OPTIONEN</a><br>
<a href="#FUNKTIONSWEISE">FUNKTIONSWEISE</a><br>
<a href="#VORAUSSETZUNGEN">VORAUSSETZUNGEN</a><br>
<a href="#AUSWIRKUNGEN">AUSWIRKUNGEN</a><br>
<a href="#FEHLER">FEHLER</a><br>
<a href="#HAFTUNG">HAFTUNG</a><br>
<a href="#AUTOR">AUTOR</a><br>

<hr>


<h2>NAME
<a name="NAME"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em"><b>autofax</b>
&minus; FaxServer-Funktionalit&auml;t: veranlasst
automatischen Faxversand von Dateien, Benennung empfangener
Faxe und Protokollierung in einer Datenbank <br>
manpage available in english: &rsquo;man autofax&rsquo; or
&rsquo;man -Len autofax&rsquo;.</p>

<h2>SYNOPSIS
<a name="SYNOPSIS"></a>
</h2>


<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="11%">


<p style="margin-top: 1em"><b>autofax</b></p></td>
<td width="1%"></td>
<td width="77%">



<p style="margin-top: 1em">[<b>&minus;lg|--language&nbsp;</b><i>&lt;d|e&gt;</i>]
[<b>&minus;v|--verbose</b>] [<b>&minus;l|--log</b>]
[<b>&minus;lvz|--logvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;ld|--logdname&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ldn|--logdateineu</b>]
[<b>&minus;kd|--konfdat&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;zvz|--zufaxenvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;wvz|--wartevz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;evz|--empfvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;cm|--cronminut&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;kc|--keincapi</b>] [<b>&minus;kh|--keinhyla</b>]
[<b>&minus;cz|--capizuerst</b>]
[<b>&minus;hz|--hylazuerst</b>]
[<b>&minus;mod|--modem&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mc|--maxcapinr&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;mh|--maxhylanr&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;ckzl|--capiklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;cuser|--cuser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;hkzl|--hylaklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;gz|--gleichziel</b>]
[<b>&minus;afs|--anfaxstring&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;acfs|--ancfaxstring&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ahfs|--anhfaxstring&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;as|--anstring&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;us|--undstring&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;host|--host&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;muser|--muser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mpwd|--mpwd&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;db|--db&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;sqlv|--sqlv</b>] [<b>&minus;rf|--rueckfragen</b>]
[<b>&minus;loef|--loeschefax</b>]
[<b>&minus;loew|--loeschewaise</b>]
[<b>&minus;loea|--loescheallew</b>]
[<b>&minus;loee|--loescheempf</b>]
[<b>&minus;kez|--korrerfolgszeichen</b>]
[<b>&minus;bwv|--bereinigewv</b>]
[<b>&minus;lista|--listarchiv</b>]
[<b>&minus;listf|--listfailed</b>]
[<b>&minus;listi|--listinlet</b>]
[<b>&minus;n|--dszahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;info|--version</b>] [<b>&minus;vi|--vi</b>]
[<b>&minus;h|-help|-?|-hilfe</b>]</p> </td></tr>
</table>

<h2>KURZBESCHREIBUNG
<a name="KURZBESCHREIBUNG"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">autofax ist ein
Befehlszeilenprogramm, mit dem Dateien in einem bestimmten
Verzeichnis automatisch an <b>hylafax</b> (falls ein
linux-kompatibles Fax-Modem angeschlossen ist) und/oder
<b>capisuite</b> (falls eine Fritzcard 2.0 oder 2.1
angeschlossen ist) weiterleitet werden, wenn die Faxnummer
im Dateinamen richtig eingetragen ist, weiterhin die
versandten Faxe in einer MariaDB-Datenbank abspeichert. <br>
Au&szlig;erdem k&ouml;nnen von
<b>hylafax</b>/<b>capisuite</b> empfangene Faxe nach dem
Sender anhand dessen Telefonnummer benannt und abgespeichert
werden.</p>

<h2>INSTALLATION
<a name="INSTALLATION"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">wget
https://github.com/libelle17/autofax/archive/master.tar.gz
-O autofax.tar.gz && tar xpvf autofax.tar.gz
&& rm autofax.tar.gz <br>
mv autofax-master autofax <br>
cd autofax <br>
make <br>
sudo make install <br>
autofax <br>
(einige Rueckfragen des Programms beantworten) <br>
Voraussetzungen s.u.</p>

<h2>GEBRAUCH
<a name="GEBRAUCH"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Im Idealfall
sollte sich das Programm nach einmaligem Aufruf (s.o.) so
eingerichtet haben, dass es von selbst weiter l&auml;uft
(insbesondere auf openSUSE-Leap 42.1 oder Ubuntu 16.04 (nur
mit Modem &uuml;ber hylafax), evtl. auch andere; es
sollte systemctl (systemd) laufen). <br>
Es existiert dann ein Verzeichnis z.B.
&rsquo;<b>zufaxen</b>&rsquo;, in das z.B. Benutzer im
Netzwerk (z.B. &uuml;ber eine Samba-Freigabe) zu faxende
Dateien stellen k&ouml;nnen wie z.B. <br>
&quot;<b>Arztbericht zu Franz Krank an Dr. Gesund und Franz
Krank an Fax 099 987654321 und 088 887654321.doc</b>&quot;
(es k&ouml;nnte auch z.B. eine *.xls, eine *.jpg, eine
*.tif, eine *.txt oder eine *.pdf-Datei sein; die Passage
&rsquo;an Dr. Gesund und Franz Krank &rsquo; ist optional
f&uuml;r die sp&auml;tere Zordnung der Faxnummer(n)
in der Datenbank, sie darf auch fehlen). <br>
Wenn <b>autofax</b> beim n&auml;chsten Mal automatisch
aufgerufen wird (standardm&auml;&szlig;ig alle 2
Minuten), wird die o.g. Beispieldatei zun&auml;chst
kopiert und umbenannt in <br>
&quot;<b>Arztbericht zu Franz Krank an Dr. Gesund an Fax 099
987654321.doc</b>&quot; und <br>
&quot;<b>Arztbericht zu Franz Krank an Franz Krank an Fax
088 887654321.doc</b>&quot; und in die PDF-Dateien <br>
&quot;<b>Arztbericht zu Franz Krank an Dr. Gesund an Fax 099
987654321.pdf</b>&quot; und <br>
&quot;<b>Arztbericht zu Franz Krank an Franz Krank an Fax
088 887654321.pdf</b>&quot; umgewandelt. <br>
Diese werden dann automatisch an <b>hylafax</b> oder
<b>Capisuite</b> weitergeleitet und von dort aus verschickt.
<br>
Gleichzeitig werden sie aus &rsquo;<b>zufaxen</b>&rsquo; in
das Warteverzeichnis, z.B. &rsquo;<b>warteauffax</b>&rsquo;
verschoben und in die Spooltabelle <b>spooltab</b>
eingetragen. <br>
Bei jedem Aufruf &uuml;berpr&uuml;ft autofax den
Status von <b>hylafax</b> und/oder <b>Capisuite</b>. Der
Abschluss des Faxvorgangs dort hat zur Folge, dass autofax
die Quelldateien (also hier die o.g. .doc- und .pdf-Dateien)
aus dem Warteverzeichnis in ein oder mehrere alternative
Archivverzeichnisse oder ein Verzeichnis f&uuml;r
gescheiteterte Faxe ablegt und den Datenbankeintrag von
&rsquo;<b>spooltab</b>&rsquo; in die Archivtabelle
&rsquo;<b>outa</b>&rsquo; verschiebt. <br>
Weiterhin werden &uuml;ber <b>hylafax</b> oder
<b>Capisuite</b> angekommene Faxe in ein Empfangsverzeichnis
kopiert und ggf. nach dem Sender benannt. Hierzu werden,
falls angegeben, konfigurierbare SQL-Befehle verwendet, die
in frei festlegbarer Zahl der Reihe nach so lange aufgerufen
werden, bis einer einen Datensatz zu der Telefonnummer
findet. <br>
Der Benutzer k&ouml;nnte also je nach Betriebssystem,
Zugriffsm&ouml;glichkeit und Pr&auml;ferenz in den
genannten Verzeichnissen, in den Datenbanktabellen oder
durch Aufruf von z.B. &rsquo;<b>autofax&rsquo;,
&rsquo;autofax -lista</b>&rsquo;, &rsquo;<b>autofax
-listf</b>&rsquo; oder &rsquo;<b>autofax -listi</b>&rsquo;
den Stand des Faxens &uuml;berpr&uuml;fen. <br>
autofax soll als root ausgefuehrt werden.</p>

<h2>OPTIONEN
<a name="OPTIONEN"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Mit
&rsquo;<b>autofax -?</b>&rsquo; werden alle
Befehlszeilenoptionen sichtbar. Einige Optionen (z.B.
SQL-Befehle) k&ouml;nnen nicht &uuml;ber die
Befehlszeile, sondern nur &uuml;ber die
Konfigurationsdatei eingegeben werden, die wiederum direkt
editiert oder auch &uuml;ber &rsquo;<b>autofax
-rf</b>&rsquo; interaktiv gepflegt werden kann. <b><br>
-lg, --language &lt;string&gt;</b>:
language/Sprache/Lingue/Lingua [deutsch,englisch] <b><br>
-v, --verbose</b>: Bildschirmausgabe gespraechiger <b><br>
-l, --log</b>: protokolliert ausfuehrlich in Datei
&rsquo;/var/log/autofax.log&rsquo; (sonst knapper) <b><br>
-lvz, --logvz &lt;pfad&gt;</b>: waehlt als Logverzeichnis
&lt;pfad&gt;, derzeit &rsquo;/var/log&rsquo; <b><br>
-ld, --logdname &lt;string&gt;</b>: logdatei &lt;string&gt;
(im Pfad &rsquo;/var/log&rsquo;) wird verwendet anstatt
&rsquo;autofax.log&rsquo; <b><br>
-ldn, --logdateineu</b>: logdatei vorher loeschen <b><br>
-kd, --konfdat &lt;string&gt;</b>: verwendet
Konfigurationsdatei &lt;string&gt; anstatt
&rsquo;/usr/local/sbin/autofax.conf&rsquo; <b><br>
-zvz, --zufaxenvz &lt;pfad&gt;</b>: faxt die Dateien aus
&lt;pfad&gt; anstatt &rsquo;...&rsquo; <b><br>
-wvz, --wartevz &lt;pfad&gt;</b>: Dateien warten in
&lt;pfad&gt; anstatt &rsquo;...&rsquo; <b><br>
-evz, --empfvz &lt;pfad&gt;</b>: Empfangsverzeichnis fuer
Faxempfang &rsquo;...&rsquo; <b><br>
-cm, --cronminut &lt;zahl&gt;</b>: alle wieviel Minuten soll
autofax ueber crontab aufgerufen werden (0=gar nicht)
&rsquo;2&rsquo; <b><br>
-kc, --keincapi</b>: capisuite nicht verwenden <b><br>
-kh, --keinhyla</b>: hylafax nicht verwenden <b><br>
-cz, --capizuerst</b>: versuche faxe zuerst ueber Capisuite
wegzuschicken <b><br>
-hz, --hylazuerst</b>: versuche faxe zuerst ueber hylafax
wegzuschicken <b><br>
-mod, --modem &lt;string&gt;</b>: Fuer Hylafax verwendetes
Modem &rsquo;&rsquo; <b><br>
-mc, --maxcapinr &lt;zahl&gt;</b>: nach &lt;zahl&gt;
Versuchen Capisuite wird Hylafax versucht, anstatt nach
&rsquo;3&rsquo; <b><br>
-mh, --maxhylanr &lt;zahl&gt;</b>: nach &lt;zahl&gt;
Versuchen Hylafax wird Capisuite versucht, anstatt nach
&rsquo;3&rsquo; <b><br>
-ckzl, --capiklingelzahl &lt;zahl&gt;</b>: Zahl der
Klingeltoene, bis Capisuite den Anruf annimmt, anstatt
&rsquo;1&rsquo; <b><br>
-cuser, --cuser &lt;string&gt;</b>: verwendet fuer Capisuite
den Linux-Benutzer &lt;string&gt; anstatt
&rsquo;schade&rsquo; <b><br>
-hkzl, --hylaklingelzahl &lt;zahl&gt;</b>: Zahl der
Klingeltoene, bis Hylafax den Anruf annimmt, anstatt
&rsquo;2&rsquo; <b><br>
-gz, --gleichziel</b>: Faxe werden auch ohne Faxerfolg ins
Zielverzeichnis kopiert <b><br>
-afs, --anfaxstring &lt;string&gt;</b>: faxnr wird hinter
&lt;string&gt; erwartet statt hinter &rsquo;an Fax&rsquo;
<b><br>
-acfs, --ancfaxstring &lt;string&gt;</b>: faxnr fuer primaer
Capisuite wird hinter &lt;string&gt; erwartet statt hinter
&rsquo;an cFax&rsquo; <b><br>
-ahfs, --anhfaxstring &lt;string&gt;</b>: faxnr fuer primaer
hylafax wird hinter &lt;string&gt; erwartet statt hinter
&rsquo;an hFax&rsquo; <b><br>
-as, --anstring &lt;string&gt;</b>: Adressatenname wird
hinter &lt;string&gt; erwartet statt hinter &rsquo; an
&rsquo; <b><br>
-us, --undstring &lt;string&gt;</b>: Trennstring
&lt;string&gt; fuer mehrere Adressaten/Telefonnummern statt
&rsquo;und&rsquo; <b><br>
-host, --host &lt;string&gt;</b>: verwendet die Datenbank
auf Host &lt;string&gt; anstatt auf &rsquo;localhost&rsquo;
<b><br>
-muser, --muser &lt;string&gt;</b>: verwendet fuer
MySQL/MariaDB den Benutzer &lt;string&gt; anstatt
&rsquo;praxis&rsquo; <b><br>
-mpwd, --mpwd &lt;string&gt;</b>: verwendet fuer
MySQL/MariaDB das Passwort &lt;string&gt; anstatt
&rsquo;...&rsquo; <b><br>
-db, --db &lt;string&gt;</b>: verwendet die Datenbank
&lt;string&gt; anstatt &rsquo;...&rsquo; <b><br>
-sqlv, --sql-verbose</b>: Bildschirmausgabe mit SQL-Befehlen
<b><br>
-rf, --rueckfragen</b>: alle Parameter werden abgefragt
(darunter einige hier nicht gezeigte) <b><br>
-loef, --loeschefax</b>: ein Fax nach Rueckfrage loeschen
<b><br>
-loew, --loeschewaise</b>: Eintraege aus &lsquo;spool&lsquo;
loeschen, zu denen keine Datei im Wartevz.und kein Capi-
oder Hylafax nachweisbar ist <b><br>
-loea, --loescheallew</b>: alle wartenden Faxe und
zugehoerige Eintraege aus &lsquo;spool&lsquo; loeschen
<b><br>
-loee, --loescheempf</b>: empfangene Dateien loeschen, die
nicht verarbeitet werden koennen <b><br>
-kez, --korrerfolgszeichen</b>: in der Datenbanktabelle
&lsquo;outa&lsquo; wird das Erfolgszeichen korrigiert
<b><br>
-bwv, --bereinigewv</b>: Dateien aus Warteverzeichnis gegen
&lsquo;outa&lsquo; pruefen und ggf. verschieben <b><br>
-lista, --listarchiv</b>: listet Datensaetze aus
&lsquo;outa&lsquo; mit Erfolgskennzeichen auf <b><br>
-listf, --listfailed</b>: listet Datensaetze aus
&lsquo;outa&lsquo; ohne Erfolgskennzeichen auf <b><br>
-listi, --listinca</b>: listet Datensaetze aus
&lsquo;inca&lsquo; auf <b><br>
-n, --dszahl &lt;zahl&gt;</b>: Zahl der aufzulistenden
Datensaetze = &lt;zahl&gt; statt &rsquo;30&rsquo; <b><br>
-info, --version</b> : Zeigt die Programmversion an <b><br>
-vi, --vi</b> : Konfigurationsdatei editieren <b><br>
-h, --hilfe</b>: Zeigt Hilfe an</p>

<h2>FUNKTIONSWEISE
<a name="FUNKTIONSWEISE"></a>
</h2>


<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) Die aktuelle Hardware wird
&uuml;berpr&uuml;ft: a) mit dem Befehl
&rsquo;<b>lspci | grep -i isdn</b>&rsquo; bez&uuml;glich
einer ISDN-Karte b) mit dem Befehl &rsquo;<b>stty
-F</b>&rsquo; bez&uuml;glich eines Fax-Modems.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">2) Die Fax-Konfigurationsdatei
<b>fax.conf</b> der Capisuite wird eingelesen, falls es sie
gibt</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">3) Weitere Vorgaben aus dem
Programmcode werden zugewiesen, die durch die
autofax-Konfigurationsdatei (siehe 4),
Kommandozeilenargumente oder Antworten auf
R&uuml;ckfragen (siehe 5) &uuml;berdeckt werden
k&ouml;nnen.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">4) Vorgaben werden geladen aus
der Konfigurationsdatei, falls existent
(standardm&auml;&szlig;ig <b>autofax.conf</b> im
selben Verzeichnis wie <b>autofax</b>,
standardm&auml;&szlig;ig
<b>/usr/local/sbin/autofax</b>))</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">5) R&uuml;ckfragen werden
gestellt, falls in der Konfigurationsdatei Werte fehlen oder
falls eine Kommandozeilenoption Interaktivit&auml;t
verlangt.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">6) Das Verzeichnis von
<b>hylafax</b> wird ermittelt (<b>/var/spool/hylafax</b>
oder <b>/var/spool/fax</b>), falls hylafax installiert
ist.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">7) Von Benutzern verwendete
Verzeichnisse f&uuml;r zu verschickende, wartende,
versandte und gescheiterte und empfangene Fax-Dateien werden
&uuml;berpr&uuml;ft und ggf. erstellt. Dabei
k&ouml;nnen in der Konfiguration angegebene
Dateinamensmuster ber&uuml;cksichtigt werden, um
erfolgreich versandte Faxe je nach Dateinamen in
verschiedenen Verzeichnissen zu speichern.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">8) Das Programm tr&auml;gt
sich ggf. in <b>crontab</b> ein, um auf Wunsch in
(einstellbaren) Abst&auml;nden aufgerufen zu werden. Um
dies zu verhindern, kann entweder
&rsquo;<b>cronminut</b>&rsquo; auf <b>0</b> eingestellt
werden oder der bereits erstellte autofax-Eintrag mit
<b>crontab -e</b> mit einem vorangestellten
&rsquo;<b>#</b>&rsquo; auskommentiert werden.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">9) Das Programm
&uuml;berpr&uuml;ft, ob alle benutzerreleventen
Verzeichnisse (s. 7) von Sambafreigaben in
/etc/samba/smb.conf <b>erfasst werden, solche werden
n&ouml;tigenfalls erg&auml;nzt.</b></p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">10) Der Betrieb von MariaDB wird
&uuml;berpr&uuml;ft, ggf. wird es (installiert und)
in Betrieb gesetzt, die Datenbanktabellen <b>spooltab</b>
(f&uuml;r gerade laufende Faxe), <b>outa</b>
(f&uuml;r gesandte und gescheiterte Faxe) und
<b>inca</b> (f&uuml;r angekommene Faxe) werden
&uuml;berpr&uuml;ft und ggf. erstellt oder
erweitert.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">11) Im Fall der entsprechenden
Kommandozeilenoptionen werden Korrekturen bei Dateien im
Warteverzeichnis oder den Protokolltabellen
durchgef&uuml;hrt oder deren Inhalt aufgelistet und das
Programm dann beendet.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">12) Andernfalls werden Dateien
im <b>Zufaxenverzeichnis</b> analysiert. Jede Datei, deren
im Dateinamen enthaltene Faxnummer(n) ermittelbar ist/sind
und die in eine PDF-Datei umwandelbar ist (oder schon so
vorliegt), wird ins Warteverzeichnis verschoben und in
<b>spooltab</b> eingetragen. Falls eine Datei mehrere
Faxnummern enth&auml;lt und/oder eine PDF-Umwandlung
n&ouml;tig ist, werden zus&auml;tzliche Dateien
erstellt und die urspr&uuml;ngliche Datei ggf.
umbenannt. Falls n&ouml;tig, k&ouml;nnen die Dateien
zus&auml;tzliche Zifferm nahe ihrem Namensende bekommen,
so dass die Namen mit keinem anderen der unter 7) genannten
Verzeichnisse in Konflikt steht. Falls neue Dateien erstellt
wurden, werden die nachfolgenden Verschiebungen und
Protokollierungen mit allen durchgef&uuml;hrt.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">13) Je nach Konfiguration wird
die Funktionsf&auml;higkeit von <b>hylafax</b> und/oder
<b>capisuite</b> &uuml;berpr&uuml;ft und ggf.
versucht herzustellen (falls n&ouml;tig und
m&ouml;glich auch mit Installation dieser Programme;
f&uuml;r eine Fritzcard 2.0 sowie f&uuml;r ein
Faxmodem USR5637 kann auch eine automatische Konfiguration
erfolgen).</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">14) Im Fall entsprechender
Kommandozeilenoptionen werden Faxe gel&ouml;scht und das
Programm dann beendet.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">15) Andernfalls werden die unter
12) in <b>spooltab</b> eingetragenen Dateien an
<b>hylafax</b> oder <b>capisuite</b> weitergeleitet und dies
in <b>spooltab</b> protokolliert.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">16) Alle in <b>spooltab</b> als
wartend stehenden Faxe werden in
<b>hylafax</b>/<b>capisuite</b> auf ihren Status
&uuml;berpr&uuml;ft, dieser wird in <b>spooltab</b>
aktualisiert (Zahl der bisherigen Faxversuche). Falls sowohl
hylafax als auch capisuite aktiv sind und eine
voreingestellte Zahl an Anwahlversuchen im Programm der
ersten Pr&auml;ferenz dieser beiden erfolglos erreicht
ist, wird das Fax auch noch an das jeweils andere Programm
weitergeleiet. Falls der Faxvorgang (erfolgreich oder
erfolglos) beendet ist, wird die Datei aus dem
Warteverzeichnis in die Verzeichnisse f&uuml;r fertige
bzw. gescheiterte Faxe verschoben und der Datenbankeintrag
aus <b>spooltab</b> in die Tabelle <b>outa</b> verschoben.
Der Status der genannten Faxe wird angezeigt.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">17) Weitere in der Warteschleife
von hylafax/capisuite befindliche, nicht &uuml;ber
autofax erstellte Faxe werden ggf. angezeigt.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">18) &Uuml;ber
<b>hylafax</b>/<b>capisuite</b> empfangene Faxe werden ggf.
mit Hilfe der Telefonnummer anhand voreingestellter
SQL-Befehle nach dem Namen des Absenders benannt und in ein
Empfangsverzeichnis gestellt.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">19) Die Konfigurationsdatei
<b>autofax.conf</b> wird ggf. geschrieben.</p></td></tr>
</table>

<h2>VORAUSSETZUNGEN
<a name="VORAUSSETZUNGEN"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Das Programm
wurde auf eine Installation von Opensuse 41.2 oder Ubuntu
16.04 mit den Standardoptionen abgestimmt. Weitere
ben&ouml;tigte Programm werden falls m&ouml;glich
vom makefile oder von autofax selbst nachstalliert. Diese
sind: <b><br>
makefile:</b> <br>
g++, libmysqlclient-dev(el), libtiff-dev(el) <b><br>
autofax:</b> <br>
cron, soffice, convert, hylafax+, hylafax+-client,
kernel-source, fcpci-3.10.0, kkeil Factory repository,
capisuite, capi4linux, i4l-isdnlog, mariadb</p>

<h2>AUSWIRKUNGEN
<a name="AUSWIRKUNGEN"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Das Programm
muss zum ordentlichen Funktionieren folgende
Ma&szlig;nahmen ergreifen:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) Installieren von Hylafax+,
falls ein Modem angeschlossen ist und Hylafax+ nicht
installiert ist. Ggf. Konfiguration von Hylafax+ durch
Aufruf von &rsquo;faxsetup -nointeracitve&rsquo;, durch
Editieren der Konfigurationsdateien config und config.* im
hylafax-Konfigurationsverzeichnis (Vorgabe z.B.:
/var/spool/hylafax/etc/)</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">2) Installieren von capisuite,
falls eine Fritzkarte eingebaut ist und capisuite nicht
installiert ist. Ggf. Bearbeitung der Konfigurationsdateien
/etc/capisuite/capisuite.conf und /etc/capisuite/fax.conf
Ggf. Bearbeitung des Python-Scripts f&uuml;r ankommende
Faxe (Vorgabe z.B.: /usr/lib64/capisuite/incoming.py) zur
Bestimmung der Zahl der Klingelt&ouml;ne bis zur
Faxannahme, Erstellung bzw. Bearbeitung der Dateien
&rsquo;/etc/udev/rules.d/46-FKN_isdn_capi.rules&rsquo;,
&rsquo;/etc/modprobe.d/50-blacklist.conf&rsquo;,</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">3) Einrichten von Diensten a) in
systemd (im Verzeichnis /usr/lib/systemd/system oder
/lib/systemd/system), insbesondere: hylafax-faxq.service,
hylafax-hfaxd.service, hylafax-faxgetty-....service,
capisuite.service, b) Verschieben von Diensten aus dem
Verzeichnis /etc/init.d in ein neu eingerichtes Verzeichnis
/etc/ausrangiert: hylafax capisuite</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">4) Erstellen einer
Protokolldatei /var/log/autofax.log</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">5) ggf. Erstellen und
Zugreifbarmachen der Verzeichnisse f&uuml;r zu sendende,
wartende, abgearbeitete und empfangene Faxe</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">6) ggf. Erstellen und
Ver&auml;ndern der Konfigurationsdatei autofax.conf in
dem Verzeichnis, in dem auch es selbst steht (Vorgabe:
/usr/local/sbin/autofax)</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">7) ggf. Einf&uuml;gen einer
Zeile zum Aufruf des Programms in das crontab (von root)</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">8) ggf. Einf&uuml;gen von
Abschnitten f&uuml;r die unter 3) genannten
Verzeichnisse in /etc/samba/smb.conf.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">9) ggf. Einf&uuml;gen einer
Datenbank f&uuml;r die Faxe in mariadb unter einem
bestimmbaren Namen, Anlage und Ver&auml;nderung mehrerer
Tabellen und einer Prozedur in dieser Datenbank, ggf.
Einf&uuml;gen eines Benutzers mit bestimmbarem Namen in
mariadb zur Datenpflege in diesen Tabellen</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">10) durch entsprechende
Befehlszeilenoptionen von autofax k&ouml;nnen innerhalb
von hylafax und capisuite Faxe gel&ouml;scht werden,
insbesondere: a) in hylafax: durch Aufruf von
&rsquo;faxrm&rsquo; b) in capisuite: durch L&ouml;schen
der Dateien wie
/var/spool/capisuite/users/&lt;user&gt;/sendq/*.txt und
~/*.sff</p> </td></tr>
</table>

<h2>FEHLER
<a name="FEHLER"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Fehler bitte
melden. Bitte auch melden, wenn sich
&Auml;nderungsbedarf durch andere Hard- bzw. Software
ergeben.</p>

<h2>HAFTUNG
<a name="HAFTUNG"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Das Programm
wurde mit bester Absicht entwickelt und durch den Autor
getestet. <br>
Trotzdem kann der Autor f&uuml;r keine Sch&auml;den
haften, die durch das Programm entstehen
k&ouml;nnten</p>

<h2>AUTOR
<a name="AUTOR"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Gerald Schade
(geraldschade@gmx.de; www.diabdachau.de)</p>
<hr>
</body>
</html>
