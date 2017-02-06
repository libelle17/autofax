<h3>Manual: 1) <a href="#english_E">english</a>, 2) <a href="#deutsch_D">deutsch (unten anschließend)</a></h3>

<h1 align="center">AUTOFAX (Version 0.42365) - english<a name="english_E"></a></h1>

<a href="#NAME_E">NAME</a><br>
<a href="#SYNOPSIS_E">SYNOPSIS</a><br>
<a href="#SHORT DESCRIPTION_E">SHORT DESCRIPTION</a><br>
<a href="#INSTALLATION_E">INSTALLATION</a><br>
<a href="#USAGE_E">USAGE</a><br>
<a href="#OPTIONS_E">OPTIONS</a><br>
<a href="#FUNCTIONALITY_E">FUNCTIONALITY</a><br>
<a href="#PRECONDITIONS_E">PRECONDITIONS</a><br>
<a href="#IMPLICATIONS_E">IMPLICATIONS</a><br>
<a href="#ERRORS_E">ERRORS</a><br>
<a href="#LIABILITY_E">LIABILITY</a><br>
<a href="#AUTHOR_E">AUTHOR</a><br>

<hr>


<h2>NAME
<a name="NAME_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em"><b>autofax</b>
&minus; fax server functionality: induces automatic fax
transmission of files, naming of received faxes and logging
of all of them in a database <br>
(manpage-Hilfe in deutsch verf&uuml;gbar: &rsquo;man
autofax&rsquo; oder &rsquo;man -Lde autofax&rsquo;)</p>

<h2>SYNOPSIS
<a name="SYNOPSIS_E"></a>
</h2>


<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="11%">


<p style="margin-top: 1em"><b>autofax</b></p></td>
<td width="1%"></td>
<td width="77%">


<p style="margin-top: 1em">[<b>&minus;v|--verbose</b>]
[<b>&minus;l|--log</b>] [<b>&minus;ldn|--logdateineu</b>]
[<b>&minus;kd|--konfdat&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;sqlv|--sql-verbose</b>]
[<b>&minus;rf|--rueckfragen</b>]
[<b>&minus;norf|--keinerueckfragen</b>]
[<b>&minus;loef|--loeschefax</b>]
[<b>&minus;loew|--loeschewaise</b>]
[<b>&minus;loea|--loescheallew</b>]
[<b>&minus;kez|--korrerfolgszeichen</b>]
[<b>&minus;bwv|--bereinigewv</b>] [<b>&minus;st|--stop</b>]
[<b>&minus;lista|--listarchiv</b>]
[<b>&minus;listf|--listfailed</b>]
[<b>&minus;listi|--listinca</b>]
[<b>&minus;listw|--listwart</b>]
[<b>&minus;s|--suche&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;n|--dszahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;info|--version</b>] [<b>&minus;vi|--vi</b>]
[<b>&minus;h|-help|-?|-hilfe</b>]
[<b>&minus;lg|--language&nbsp;</b><i>&lt;d|e&gt;</i>]
[<b>&minus;lvz|--logvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;ld|--logdname&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;zvz|--zufaxenvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;wvz|--wartevz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;nvz|--nichtgefaxtvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;evz|--empfvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;cm|--cronminut&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;capi|--obcapi</b>] [<b>&minus;hyla|--obhyla</b>]
[<b>&minus;cz|--capizuerst</b>]
[<b>&minus;hz|--hylazuerst</b>]
[<b>&minus;mod|--hmodem&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mc|--maxcapiv&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;mh|--maxhylav&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;cuser|--cuser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ckzl|--capiklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;hkzl|--hylaklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;md|--maxdials&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;gz|--gleichziel</b>] [<b>&minus;ocri|--ocri</b>]
[<b>&minus;ocra|--ocra</b>]
[<b>&minus;afs|--anfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;acfs|--ancfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ahfs|--anhfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;as|--anstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;us|--undstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;host|--host&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;muser|--muser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mpwd|--mpwd&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;db|--datenbank&nbsp;</b><i>&lt;string&gt;</i>]</p> </td></tr>
</table>

<h2>SHORT DESCRIPTION
<a name="SHORT DESCRIPTION_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">autofax is a
command line programme to remit files of a certain directory
automatically to <b>hylafax</b> (in case a linux-compatible
modem is installed) and/or <b>capisuite</b> (in case a
fritzcard 2.0 or 2.1 is installed), if the fax number is
integrated in the file name correctly. Furthermore, autofax
holds the posted faxes in a mariadb database. <br>
Additionally, received faxes from
<b>hylafax</b>/<b>capisuite</b> can be named with the
sender&rsquo;s name according to his fax number and
stored.</p>

<h2>INSTALLATION
<a name="INSTALLATION_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">First, read the
chapters &rsquo;functionality&rsquo;,
&rsquo;preconditions&rsquo; and &rsquo;implications&rsquo;
below. Then, if connected to the internet, call: <b><br>
N=autofax;P=${N}_inst.sh;cd ~;wget
https://raw.githubusercontent.com/libelle17/$N/master/install.sh
-O$P&&sh $P</b> <br>
At last, call: <b><br>
autofax</b> <br>
(answer some questions of the program) <br>
The first execution and the first processing of a fax may
take some time and need some additional input, respectively.
<br>
Preconditions see below.</p>

<h2>USAGE
<a name="USAGE_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Ideally, the
program should have installed itsself after a single call
(see above) in a self-running way. <br>
Then a directory e.g. &rsquo;<b>zufaxen</b>&rsquo; exists,
in which e.g. users in a network (e.g. via a samba share)
can deposit files to be faxed, e.g. <br>
&quot;<b>Medical report on Frank Ill to Dr. Healthy and
Frank Ill to fax 099 987654321 and 088
887654321.doc</b>&quot; (it could also be e.g. an *.xls, a
*.jpg, a *.tif, a *.txt, a *pdf file; the section &rsquo; to
Dr. Healthy and Frank Ill&rsquo; is optional for the later
allocation of the fax number(s) in the database, it may also
be obmitted). <br>
When <b>autofax</b> is called for the next time (per default
2 minutes), the above mentioned example file will initially
be copied and renamed into <br>
&quot;<b>Medical report on Frank Ill to Dr. Healthy to fax
099 987654321.doc</b>&quot; and <br>
&quot;<b>Medical report on Frank Ill to Frank Ill to fax 088
887654321.doc</b>&quot; and converted into the pdf-files
<br>
&quot;<b>Medical report on Frank Ill to Dr. Healthy to fax
099 987654321.pdf</b>&quot; and <br>
&quot;<b>Medical report on Frank Ill to Frank Ill to fax 088
887654321.pdf</b>&quot;. <br>
Those are subsequently being relayed to <b>hylafax</b> or
<b>Capisuite</b> and from there sent. <br>
Simultaneously they are being moved from
&rsquo;<b>zufaxen</b>&rsquo; to the waiting directory, e.g.
&rsquo;<b>warteauffax</b>&rsquo; and recorded in the spool
table <b>spooltab</b>. <br>
At each call, autofax checks the status of <b>hylafax</b>
and/or <b>Capisuite</b>. The Finishing of a fax process
there causes autofax to move the source files (here the
above mentioned .doc- and .pdf-files) from the waiting
directory to one or several archive directories or a
directory for failed faxes and to move their database record
from &rsquo;<b>spooltab</b>&rsquo; to the archive table
&rsquo;<b>outa</b>&rsquo;. <br>
Further on, incoming faxes via <b>hylafax</b> or
<b>Capisuite</b> are being transmitted to an incoming
directory and if applicable named including the
sender&rsquo;s name. To this purpose, customizeable sql
commands are being used, if specified. <br>
Depending on operating system, accessability and preferences
the users thus could look up the status of their faxes in
the above mentioned directories, in the database tables or
by calling &rsquo;<b>autofax&rsquo;, &rsquo;autofax
-lista</b>&rsquo;, &rsquo;<b>autofax -listf</b>&rsquo; or
&rsquo;<b>autofax -listi</b>&rsquo;.</p>

<h2>OPTIONS
<a name="OPTIONS_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">With
&rsquo;<b>autofax -?</b>&rsquo;, all command line options
can be seen. Some options (e.g. the sql commands) cannot bei
set via the command line, but only via the configuration
file, which can be edited directly or interactively by
&rsquo;<b>autofax -rf</b>&rsquo;. <b><br>
Options which are not saved</b>: <b><br>
-v, --verbose</b>: screen output more verbose <b><br>
-l, --log</b>: put detailed logs in file
&rsquo;/var/log/autofax.log&rsquo; (otherwise shorter)
<b><br>
-ldn, --logdateineu</b>: delete log file afore <b><br>
-kd, --konfdat &lt;string&gt;</b>: uses configuration file
&lt;string&gt; instead of
&rsquo;/usr/local/sbin/autofax.conf&rsquo; <b><br>
-sqlv, --sql-verbose</b>: screen output with SQL commands
<b><br>
-rf, --rueckfragen</b>: all parameters will be prompted
(some of them not shown here) <b><br>
-norf, --keinerueckfragen</b>: no questions, e.g. for a call
of autofax within cron <b><br>
-loef, --loeschefax</b>: delete a fax with query <b><br>
-loew, --loeschewaise</b>: delete entries from
&lsquo;spool&lsquo; without detection of file in waiting
directory or capisuite fax or hylafax <b><br>
-loea, --loescheallew</b>: delete all waiting faxes and
associated entries from &lsquo;spool&lsquo; <b><br>
-kez, --korrerfolgszeichen</b>: in the database table
&lsquo;outa&lsquo; the success flag is being corrected
<b><br>
-bwv, --bereinigewv</b>: Examine files in waiting directory
against the tables &lsquo;outa&lsquo; and clean them up
<b><br>
-st, --stop</b>: stop autofax <b><br>
-lista, --listarchiv</b>: lists entries from
&lsquo;outa&lsquo; with success flag <b><br>
-listf, --listfailed</b>: lists entries from
&lsquo;outa&lsquo; without success flag <b><br>
-listi, --listinca</b>: lists entries from
&lsquo;inca&lsquo; <b><br>
-listw, --listwart</b>: list waiting faxes <b><br>
-s, --suche &lt;string&gt;</b>: Look in processed faxes for
&lt;string&gt; <b><br>
-n, --dszahl &lt;zahl&gt;</b>: No. of listed entries =
&lt;zahl&gt; instead of &rsquo;30&rsquo; <b><br>
-info, --version</b> : shows the program version <b><br>
-vi, --vi</b> : edit the configuration file <b><br>
-h, --hilfe</b>: shows this screen <b><br>
Options which can be saved in the configuration file
(preceding &rsquo;1&rsquo;=don&rsquo;t save,
&rsquo;no&rsquo;=contrary, e.g. &rsquo;-noocra&rsquo;,
&rsquo;-1noocri&rsquo;)</b>: <b><br>
-lg, --language &lt;string&gt;</b>:
language/Sprache/Lingue/Lingua [deutsch,english]
&rsquo;e&rsquo; <b><br>
-lvz, --logvz &lt;path&gt;</b>: choses &lt;path&gt; as log
directory, currently &rsquo;/var/log&rsquo; <b><br>
-ld, --logdname &lt;string&gt;</b>: log file &lt;string&gt;
(in path &rsquo;/var/log&rsquo;) will be used instead of
&rsquo;autofax.log&rsquo; <b><br>
-zvz, --zufaxenvz &lt;path&gt;</b>: faxes the files from
&lt;path&gt; instead of &rsquo;...&rsquo; <b><br>
-wvz, --wartevz &lt;path&gt;</b>: files are waiting in
&lt;path&gt; instead of &rsquo;...&rsquo; <b><br>
-evz, --empfvz &lt;path&gt;</b>: directory for recieved
faxes &rsquo;...&rsquo; <b><br>
-cm, --cronminut &lt;zahl&gt;</b>: every how many minutes
shall autofax be called in crontab (0=not at all)
&rsquo;2&rsquo; <b><br>
-capi, --obcapi</b>: use capisuite <b><br>
-hyla, --obhyla</b>: use hylafax <b><br>
-cz, --capizuerst</b>: try to send faxes primarily via
capisuite <b><br>
-hz, --hylazuerst</b>: try to send faxes primarily via
hylafax <b><br>
-mod, --hmodem &lt;string&gt;</b>: Modem used for hylafax
&rsquo;&rsquo; <b><br>
-mc, --maxcapiv &lt;zahl&gt;</b>: try Hylafax after
&lt;no&gt; tries of Capisuite instead of &rsquo;3&rsquo;
<b><br>
-mh, --maxhylav &lt;zahl&gt;</b>: try Capisuite after
&lt;no&gt; tries of Hylafax instead of &rsquo;3&rsquo;
<b><br>
-cuser, --cuser &lt;string&gt;</b>: takes the linux user
&lt;string&gt; for Capisuite instead of &rsquo;schade&rsquo;
<b><br>
-ckzl, --capiklingelzahl &lt;zahl&gt;</b>: No. of bell rings
until Capisuite accepts the call, instead of &rsquo;1&rsquo;
<b><br>
-hkzl, --hylaklingelzahl &lt;zahl&gt;</b>: No. of bell rings
until hylafax accepts the call, instead of &rsquo;2&rsquo;
<b><br>
-md, --maxdials</b>: No. of dialing retries in hylafax,
instead of &rsquo;11&rsquo; <b><br>
-gz, --gleichziel</b>: copy faxes into target directory
irrespective of faxing success <b><br>
-orci, --ocri</b>: Text from received faxed will be filtered
<b><br>
-orci, --ocri</b>: Text from sent faxed will be filtered
<b><br>
-afs, --anfaxstring &lt;string&gt;</b>: the fax number will
be expected after &lt;string&gt; instead of &rsquo;an
Fax&rsquo; <b><br>
-acfs, --ancfaxstring &lt;string&gt;</b>: fax no.for fax
with preference to capisuite is expected after
&lt;string&gt; instead of &rsquo;an cFax&rsquo; <b><br>
-ahfs, --anhfaxstring &lt;string&gt;</b>: fax no.for fax
with preference to hylafax is expected after &lt;string&gt;
instead of &rsquo;an hFax&rsquo; <b><br>
-as, --anstring &lt;string&gt;</b>: name of addressee is
expected after &lt;string&gt; instead of &rsquo; an &rsquo;
<b><br>
-us, --undstring &lt;string&gt;</b>: separating string
&lt;string&gt; for multiple addressees/fax&rsquo;numbers,
instead of &rsquo;und&rsquo; <b><br>
-host, --host &lt;string&gt;</b>: takes the database on host
&lt;string&gt; instead of &rsquo;localhost&rsquo; <b><br>
-muser, --muser &lt;string&gt;</b>: takes the user
&lt;string&gt; for MySQL/MariaDB instead of
&rsquo;praxis&rsquo; <b><br>
-mpwd, --mpwd &lt;string&gt;</b>: takes the password
&lt;string&gt; for MySQL/MariaDB instead of
&rsquo;...&rsquo; <b><br>
-db, --datenbank &lt;string&gt;</b>: uses the database
&lt;string&gt; instead of &rsquo;...&rsquo; <b><br>
-h, --help</b> : shows help</p>

<h2>FUNCTIONALITY
<a name="FUNCTIONALITY_E"></a>
</h2>


<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) The current hardware is being
checked.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) with the command
&rsquo;<b>lspci | grep -i isdn</b>&rsquo; for a fritz
card.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) with the command
&rsquo;<b>stty -F</b>&rsquo; for a fax modem.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">2) The fax configuration file
<b>fax.conf</b> of capisuite is read, if it exists</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">3) Further defaults from the
program code are assigned which can be overloaded by the
autofax configuration file (see 4), command line arguments
or anwers to questions (see 5).</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">4) Defaults are loaded from the
configuration file, if it exists (per default
<b>autofax.conf</b> in the same directory as <b>autofax</b>,
per default <b>/usr/local/sbin/autofax</b>))</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">5) Questions are asked, if
values are missing from the configuration file (see 4) or if
a command line option demands interacitivity.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">6) The directory of
<b>hylafax</b> is beeing determined
(<b>/var/spool/hylafax</b> or <b>/var/spool/fax</b>), if
hylafax is installed.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">7) Directories used by the users
for fax files to be sent, for waiting faxes, for fax files
already sent, for failed faxes and for received faxes are
being checked and created if needed. Thereby user defined
file name patterns can be respected to store successfully
sent faxes in different directories.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">8) The program inserts itsself
if wanted and necessary in <b>crontab</b> in order to be
called in adjustable intervals. To avoid this, either
&rsquo;<b>cronminut</b>&rsquo; can be set to <b>0</b>, or
the already generated autofax entry can be commented out
with a leading &rsquo;<b>#</b>&rsquo;.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">In case a Suse firewall is
present, allow samba-server for &quot;external
zone&quot;.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">9) The program checks if all
user-relevant directories (see 7) are being included in
samba shares in <b>/etc/samba/smb.conf</b>; such are being
added if needed.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">10) Working of MariaDB is being
checked, if necessary it is being (installed and) started,
the database tables <b>spooltab</b> (for faxes just in
spool), <b>outa</b> (for sent and failed faxes) and
<b>inca</b> (for received faxes) are being checked and if
necessary created or amended.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">11) In case of the respective
command line options corrections in the contents of the
waiting directory or of the database tables are being
commited or their contents is being listed and then the
program is being finished.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">12) Otherwise, file in the
outgoing directory are being analysed. Each file with some
identifiable fax number(s) within its file name which is or
can be converted in/into pdf format will be moved to to
waiting directory and recorded in <b>spooltab</b>.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">If a file contains more than one
recepients and/or a conversion to pdf is necessary,
additional files are generated and the original file may be
renamed. If necessary, additional numbers near the end of
the file name(s) may be added in order not to conflict with
any other file name in one of the directories mentioned in
7).</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">If more files have been
generated, the successive movements and recordings are being
carried out with all of them.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">13) Depending on the
configuration the functionaliy of <b>hylafax</b> and/or
<b>capisuite</b> is being checked and if necessary and
possible restored (including by installation of those
programs; in case of a fritzcard 2.0 or a fax modem USR5637
an additional automatic configuration can be done).</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">14) In case of respective
command line options faxes are being deleted and the program
is finished.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">15) Otherwise the files which
have been recorded under 12) in <b>spooltab</b> are being
forwarded to <b>hylafax</b> or <b>capisuite</b> and this is
being protocolled in <b>spooltab</b>.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">16) All faxes which are recorded
in <b>spooltab</b> as waiting are being checked in
<b>hylafax</b>/<b>capisuite</b> as to their status which is
being updated in <b>spooltab</b> (number of tries
hitherto).</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">If hylafax and capisuite are
working simultaneously and a prespecified number of send
tries has been reached without success in the programs of
the first preference of those two, the fax is additionally
forwarded to the second of the two programs.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">If the fax transmission is
finished (with/without success), the file is being moved
from the waiting directory to the respective directory for
sent faxes or for failed faxes, optionally modified by ocr
via ocrmypdf, and the database entry is being transferred
from <b>spooltab</b> to <b>outa</b>.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">The status of the mentioned
faxes is being displayed.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">17) If additional faxes in the
spool of hylafax/capisuite are detected which are not
created via autofax, they are displayed. In intervals they
will be integrated into the autofax database (without the
not available information on the original file name).</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">18) Via
<b>hylafax</b>/<b>capisuite</b> received faxes are copied to
a receiving directory and there named with the name of the
sender, if possible, by means of their fax number which is
being looked up using a predefineable number of
predefineable sql commands, which are applied one after
another until the fax number is found.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Such sql commands shall deliver
2 fields, whose contents, separated by a comma, will be used
to name to received faxes. When applied, within the sql
commands the string &rsquo;&&faxnr&&&rsquo;
will be replaced by the current fax number. Example:</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">
</td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">select concat(haname,&rsquo;,
&rsquo;,ort,&rsquo;, &rsquo;,kvnu) name, zulg, fax1k from
kvaerzte.hae where
concat(if(mid(fax1k,1,1)=&rsquo;0&rsquo;,&rsquo;&rsquo;,&rsquo;08131&rsquo;),
replace(replace(replace(replace(fax1k,&rsquo;
&rsquo;,&rsquo;&rsquo;),&rsquo;-&rsquo;,&rsquo;&rsquo;),&rsquo;/&rsquo;,&rsquo;&rsquo;),&rsquo;&acute;&rsquo;,&rsquo;&rsquo;))
= &rsquo;&&faxnr&&&rsquo;</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">
</td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">If more sql commands are
specified and one of them does not give a result, the next
one will be tried.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Optionally, the received faxes
are subjected to ocr via a call of ocrmypdf.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">19) The configuration file is
being written, if necessary.</p></td></tr>
</table>

<h2>PRECONDITIONS
<a name="PRECONDITIONS_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">The program was
adjusted to an installation of Opensuse 42.1, Debian 8.60,
Ubuntu 16.04, Mint 18 or Fedora 24 with standard options. In
Debian, it may be advantageous to check that in the file
/etc/apt/sources.list no dvd is mentioned before the
standard online-repositories. systemctl (systemd) must run,
sudo is needed (missing per default in Debian), the user
must be allowed to call the command &rsquo;sudo&rsquo; (must
be member of a group mentioned in /etc/sudoers, otherwise,
the above mentioned installation program tries to enter him
there), &rsquo;GNU make&rsquo; has to be installed (which
shall be accomplished if necessary by calling ./install.sh).
Further needed programs will be installed by the makefile or
by autofax itsself including preconditioned programs via
zypper, apt, dnf or yum, python3 pip, if needed and
possible, especially:</p>


<p style="margin-left:11%; margin-top: 1em"><b>makefile:</b></p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">gcc V.6, g++ V.6, groff,
libmysqlclient-dev(el), libtiff-dev(el) (in case of version
4.0.7 with a slight modification, see Makefile)</p></td></tr>
</table>

<p style="margin-left:15%;"><b>autofax:</b></p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">boost, boost-devel, cron,
ghostscript, imagemagick, libreoffice-common,
libreoffice-base, mariadb-server, policycoreutils,
policycoreutils-python-utils, poppler-tools, samba,
sfftobmp, (in debian-derivates, for mariadb, additionally:
apt-transport-https)</p> </td></tr>
</table>

<p style="margin-left:15%;">in case capisuite shall be
used:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">capisuite, capiutils,
capi4linux, fcpci-3.10.0, gcc-4.8, g++-4.8, kernel-source
(linux-source), libcapi20-2, libcapi20-3, libxslt-tools,
linux-headers-$(uname -r), python-devel, (in fedora,
additionally: kernel, kernel-devel, kernel-modules-extra,
numactl-devel, pesign, rpmdevtools; this may install a
current kernel),</p></td></tr>
</table>

<p style="margin-left:15%;">in case hylafax shall be
used:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">hylafax+, hylafax+-client,
sendmail, tiff (in case of version 4.0.7 with a slight
modification, see Makefile)</p></td></tr>
</table>

<p style="margin-left:15%;">in case ocr shall be used:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">ffmpeg, ffmpeg-devel,
ffmpeg-compat, gcc, libavformat-devel, libffi-devel,
ocrmypdf, python3-devel, python3-pip, python3-setuptools,
rpmfusion, qpdf, redhat-rpm-config, tesseract-ocr, unpaper,
and via &rsquo;python3 pip&rsquo;: cryptography, cffi,
image, M2Crypto, ocrmypdf, PyPDF2, reportlab, ruffus.</p></td></tr>
</table>

<p style="margin-left:15%;">All those installations may
include dependent programs. <br>
If You don&rsquo;t want one of those programs or want to
keep an older version of one, You may not install autofax or
use the respective program parts.</p>

<h2>IMPLICATIONS
<a name="IMPLICATIONS_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">The program has
to take the following measures for its neat function:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) Installation of
<b>hylafax+</b>, in case a modem is connected and hylafax+
is not installed. If necessary configuration of hylafax+ by
calling &rsquo;<b>faxsetup -nointeracitve</b>&rsquo;, by
editing the configuration files <b>config</b> and
<b>config.*</b> (e.g. <b>config.ttyACM0</b>) in the hylafax
configuration directory (default e.g.
<b>/var/spool/hylafax/etc</b>).</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">2) Installation of
<b>capisuite</b>, in case a fritzcard is inserted and
capisuite is not installed. If necessary configuration of
<b>/etc/capisuite/capisuite.conf</b> and
<b>/etc/capisuite/fax.conf</b>. If necessary edition of the
python-script for received faxes (default e.g.
<b>/usr/lib64/capisuite/incoming.py</b>) in order to
determine the rings before answer, creation and edition of
the files
&rsquo;<b>/etc/udev/rules.d/46-FKN_isdn_capi.rules</b>&rsquo;,
&rsquo;<b>/etc/modprobe.d/50-blacklist.conf</b>&rsquo;.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">3) Installation of services:</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) in systemd (in the directory
/usr/lib/systemd/system or /lib/systemd/system),
especially:</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em"><b>hylafax-faxq.service</b>,
<b>hylafax-hfaxd.service</b>,
<b>hylafax-faxgetty-....service</b> (e.g.
<b>hylafax-faxgetty-ttyACM0</b>),</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em"><b>capisuite.service</b>,</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) Moving of existing service
files from the directory /etc/init.d to a newly created
directory /etc/ausrangiert: <b>hylafax</b>,
<b>capisuite</b></p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">c) In case <b>selinux</b> is
active (as per default in fedora), it impedes per default
hylafax; in this case, a module for selinux is silently
arranged in order to allow running hylafax-hfaxd. Furtheron,
up to the possible construction of a better fitting
solution, the domain &rsquo;getty&rsquo; has to be
deactivated with the command &rsquo;<b>semanage permissive
-a getty_t</b>&rsquo; in order to receive faxes.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">4) Creation of a logfile, per
default <b>/var/log/autofax.log</b>.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">5) if necessary creation and
making accessible of the configurable <b>directories</b> for
faxes to be sent, waiting, finished and failed.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">6) if necessary creation and
making accessible of the configuration file
<b>autofax.conf</b> in the same directory where the program
is located by itsself (default:
<b>/usr/local/sbin/autofax</b>).</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">7) Insertion of a line for the
program in crontab (of root)</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">8) if necessary insertion of
sections for the directories mentioned under 3) in
/etc/samba/smb.conf, if necessary insertion of the program
user or (if root) the user chosen for the capisuite as samba
user.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">9) if necessary insertion of a
database in mariadb with a configurable name, creation and
modification of several tables and a procedure in this
database, if necessary insertion of a user with a
configurable name in mariadb for the data management within
those tables.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">10) With specific command line
options for autofax, faxes can be deleted, especially:</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) in hylafax by callinng
&rsquo;faxrm&rsquo;</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) in capisuite: by deleting
files like
/var/spool/capisuite/users/&lt;user&gt;/sendq/*.txt und
~/*.sff. In capisuite, an orphaned lock file
(/var/spool/capisuite/users/&lt;user&gt;/sendq/*.lock) can
be deleted, too.</p></td></tr>
</table>

<h2>ERRORS
<a name="ERRORS_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Please report
any errors with the word &rsquo;autofax&rsquo; included in
the headline. <br>
Please report as well, if different hard- or software yields
a requirement for a program modification.</p>

<h2>LIABILITY
<a name="LIABILITY_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">The program has
been written with the best aim and has been tested by the
author. <br>
Nevertheless the author cannot be liable for any damage
caused by the program.</p>

<h2>AUTHOR
<a name="AUTHOR_E"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Gerald Schade
(geraldschade@gmx.de; www.diabdachau.de)</p>
<hr>
</body>
</html>

<h1 align="center">AUTOFAX (Version 0.42365) - deutsch<a name="deutsch_D"></a></h1>

<a href="#NAME_D">NAME</a><br>
<a href="#SYNOPSIS_D">SYNOPSIS</a><br>
<a href="#KURZBESCHREIBUNG_D">KURZBESCHREIBUNG</a><br>
<a href="#INSTALLATION_D">INSTALLATION</a><br>
<a href="#GEBRAUCH_D">GEBRAUCH</a><br>
<a href="#OPTIONEN_D">OPTIONEN</a><br>
<a href="#FUNKTIONSWEISE_D">FUNKTIONSWEISE</a><br>
<a href="#VORAUSSETZUNGEN_D">VORAUSSETZUNGEN</a><br>
<a href="#AUSWIRKUNGEN_D">AUSWIRKUNGEN</a><br>
<a href="#FEHLER_D">FEHLER</a><br>
<a href="#HAFTUNG_D">HAFTUNG</a><br>
<a href="#AUTOR_D">AUTOR</a><br>

<hr>


<h2>NAME
<a name="NAME_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em"><b>autofax</b>
&minus; FaxServer-Funktionalit&auml;t: veranlasst
automatischen Faxversand von Dateien, Benennung empfangener
Faxe und Protokollierung aller Faxe in einer Datenbank <br>
(manpage available in english: &rsquo;man autofax&rsquo; or
&rsquo;man -Len autofax&rsquo;)</p>

<h2>SYNOPSIS
<a name="SYNOPSIS_D"></a>
</h2>


<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="11%">


<p style="margin-top: 1em"><b>autofax</b></p></td>
<td width="1%"></td>
<td width="77%">


<p style="margin-top: 1em">[<b>&minus;v|--verbose</b>]
[<b>&minus;l|--log</b>] [<b>&minus;ldn|--logdateineu</b>]
[<b>&minus;kd|--konfdat&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;sqlv|--sql-verbose</b>]
[<b>&minus;rf|--rueckfragen</b>]
[<b>&minus;norf|--keinerueckfragen</b>]
[<b>&minus;loef|--loeschefax</b>]
[<b>&minus;loew|--loeschewaise</b>]
[<b>&minus;loea|--loescheallew</b>]
[<b>&minus;kez|--korrerfolgszeichen</b>]
[<b>&minus;bwv|--bereinigewv</b>] [<b>&minus;st|--stop</b>]
[<b>&minus;lista|--listarchiv</b>]
[<b>&minus;listf|--listfailed</b>]
[<b>&minus;listi|--listinca</b>]
[<b>&minus;listw|--listwart</b>]
[<b>&minus;s|--suche&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;n|--dszahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;info|--version</b>] [<b>&minus;vi|--vi</b>]
[<b>&minus;h|-help|-?|-hilfe</b>]
[<b>&minus;lg|--language&nbsp;</b><i>&lt;d|e&gt;</i>]
[<b>&minus;lvz|--logvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;ld|--logdname&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;zvz|--zufaxenvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;wvz|--wartevz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;nvz|--nichtgefaxtvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;evz|--empfvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;cm|--cronminut&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;capi|--obcapi</b>] [<b>&minus;hyla|--obhyla</b>]
[<b>&minus;cz|--capizuerst</b>]
[<b>&minus;hz|--hylazuerst</b>]
[<b>&minus;mod|--hmodem&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mc|--maxcapiv&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;mh|--maxhylav&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;cuser|--cuser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ckzl|--capiklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;hkzl|--hylaklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;md|--maxdials&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;gz|--gleichziel</b>] [<b>&minus;ocri|--ocri</b>]
[<b>&minus;ocra|--ocra</b>]
[<b>&minus;afs|--anfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;acfs|--ancfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ahfs|--anhfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;as|--anstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;us|--undstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;host|--host&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;muser|--muser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mpwd|--mpwd&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;db|--datenbank&nbsp;</b><i>&lt;string&gt;</i>]</p> </td></tr>
</table>

<h2>KURZBESCHREIBUNG
<a name="KURZBESCHREIBUNG_D"></a>
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
Sender anhand dessen Faxnummer benannt und abgespeichert
werden.</p>

<h2>INSTALLATION
<a name="INSTALLATION_D"></a>
</h2>



<p style="margin-left:11%; margin-top: 1em">Zun&auml;chst
lesen Sie bitte die Kapitel &rsquo;Funktionsweise&rsquo;,
&rsquo;Voraussetzungen&rsquo; und
&rsquo;Auswirkungen&rsquo;. A <br>
Anschlie&szlig;end verbinden Sie den Rechner falls
n&ouml;tig mit dem Internet und rufen Sie auf: <b><br>
N=autofax;P=${N}_inst.sh;cd ~;wget
https://raw.githubusercontent.com/libelle17/$N/master/install.sh
-O$P&&sh $P</b> <br>
Zuletzt rufen Sie auf: <b><br>
autofax</b> <br>
(einige Rueckfragen des Programms beantworten) <br>
Der erste Programmaufruf und die erste Faxverarbeitung
k&ouml;nnen jeweils etwas dauern und ein paar
zus&auml;tzliche Eingaben erfordern. <br>
Voraussetzungen s.u.</p>

<h2>GEBRAUCH
<a name="GEBRAUCH_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Im Idealfall
sollte sich das Programm nach einmaligem Aufruf (s.o.) so
eingerichtet haben, dass es von selbst weiter
l&auml;uft. <br>
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
werden, bis einer einen Datensatz zu der Faxnummer findet.
<br>
Der Benutzer k&ouml;nnte also je nach Betriebssystem,
Zugriffsm&ouml;glichkeit und Pr&auml;ferenz in den
genannten Verzeichnissen, in den Datenbanktabellen oder
durch Aufruf von z.B. &rsquo;<b>autofax&rsquo;,
&rsquo;autofax -lista</b>&rsquo;, &rsquo;<b>autofax
-listf</b>&rsquo; oder &rsquo;<b>autofax -listi</b>&rsquo;
den Stand des Faxens &uuml;berpr&uuml;fen.</p>

<h2>OPTIONEN
<a name="OPTIONEN_D"></a>
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
&lt;string&gt; fuer mehrere Adressaten/Faxnummern statt
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
<a name="FUNKTIONSWEISE_D"></a>
</h2>


<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) Die aktuelle Hardware wird
&uuml;berpr&uuml;ft:</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) mit dem Befehl
&rsquo;<b>lspci | grep -i isdn</b>&rsquo; bez&uuml;glich
einer ISDN-Karte</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) mit dem Befehl &rsquo;<b>stty
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
<b>spooltab</b> eingetragen.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Falls eine Datei mehrere
Faxnummern enth&auml;lt und/oder eine PDF-Umwandlung
n&ouml;tig ist, werden zus&auml;tzliche Dateien
erstellt und die urspr&uuml;ngliche Datei ggf.
umbenannt. Falls n&ouml;tig, k&ouml;nnen die Dateien
zus&auml;tzliche Zifferm nahe ihrem Namensende bekommen,
so dass die Namen mit keinem anderen der unter 7) genannten
Verzeichnisse in Konflikt steht.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Falls neue Dateien erstellt
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
aktualisiert (Zahl der bisherigen Faxversuche).</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Falls sowohl hylafax als auch
capisuite aktiv sind und eine voreingestellte Zahl an
Anwahlversuchen im Programm der ersten Pr&auml;ferenz
dieser beiden erfolglos erreicht ist, wird das Fax auch noch
an das jeweils andere Programm weitergeleiet.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Falls der Faxvorgang
(erfolgreich oder erfolglos) beendet ist, wird die Datei aus
dem Warteverzeichnis in die Verzeichnisse f&uuml;r
fertige bzw. gescheiterte Faxe verschoben, optional mit
ocrmypdf einer Texterkennung unterzogen, und der
Datenbankeintrag aus <b>spooltab</b> in die Tabelle
<b>outa</b> verschoben.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Der Status der genannten Faxe
wird angezeigt.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">17) Weitere in der Warteschleife
von hylafax/capisuite befindliche, nicht &uuml;ber
autofax erstellte Faxe werden ggf. angezeigt. In Intervallen
werden sie in die Autofax-Datenbank integriert (ohne die
fehlende Information &uuml;ber den
urspr&uuml;nglichen Dateinamen)</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">18) &Uuml;ber
<b>hylafax</b>/<b>capisuite</b> empfangene Faxe werden ggf.
mit Hilfe der Faxnummer anhand voreingestellter SQL-Befehle
nach dem Namen des Absenders benannt und in ein
Empfangsverzeichnis gestellt.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Solche SQL-Befehle sollen zwei
Ergebnisfelder liefern, deren Inhalt dann, durch ein Komma
getrennt, zur Benennung eines empfangenen Faxes verwendet
werden. Bei der Anwendung des SQL-Befehls wird die
Zeichenfolge &rsquo;&&faxnr&&&rsquo; zur
aktuellen Faxnummer erweitert. Beispiel fuer einen solchen
SQL-Befehl:</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">
</td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">select concat(haname,&rsquo;,
&rsquo;,ort,&rsquo;, &rsquo;,kvnu) name, zulg, fax1k from
kvaerzte.hae where
concat(if(mid(fax1k,1,1)=&rsquo;0&rsquo;,&rsquo;&rsquo;,&rsquo;08131&rsquo;),
replace(replace(replace(replace(fax1k,&rsquo;
&rsquo;,&rsquo;&rsquo;),&rsquo;-&rsquo;,&rsquo;&rsquo;),&rsquo;/&rsquo;,&rsquo;&rsquo;),&rsquo;&acute;&rsquo;,&rsquo;&rsquo;))
= &rsquo;&&faxnr&&&rsquo;</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">
</td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Wenn mehrere SQL-Befehle
angegeben werden, so wird der jeweils naechste angewandt,
wenn einer kein Ergebnis liefert.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Optional werden die empfangenen
Dateien mit Hilfe von ocrmypdf einer Texterkennung
unterzogen.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">19) Die Konfigurationsdatei
<b>autofax.conf</b> wird ggf. geschrieben.</p></td></tr>
</table>

<h2>VORAUSSETZUNGEN
<a name="VORAUSSETZUNGEN_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Das Programm
wurde auf eine Installation von Opensuse 42.1, Debian 8.60,
Ubuntu 16.04, Mint 18 oder Fedora 24 mit den
Standardoptionen abgestimmt. In Debian kann es vorteilhaft
sein, darauf zu achten, dass in der Datei
/etc/apt/sources.list kein DVD-Eintrag vor den
Standard-Online-Repositories steht. systemctl (systemd) muss
laufen, sudo muss installiert sein (fehlt anfangs bei
Standardinstallation in Debian), der Benutzer muss den
Befehl &rsquo;sudo&rsquo; ausf&uuml;hren d&uuml;rfen
(Mitglied einer Gruppe sein, die in /etc/sudoers genannt
wird, andernfalls versucht das o.g. Installationsprogramm,
ihn dort einzutragen), &rsquo;GNU make&rsquo; wird
ben&ouml;tigt, was durch Aufruf von ./install.sh ggf.
installiert werden kann. Weitere ben&ouml;tigte Programm
werden falls m&ouml;glich vom makefile oder von autofax
bei Bedarf selbst mitsamt vorausgesetzter Programme mithilfe
von zypper, apt, dnf oder yum nachstalliert, insbesondere:
<b><br>
makefile:</b></p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">gcc V.6, g++ V.6, groff,
libmysqlclient-dev(el), libtiff-dev(el) (im Fall von Version
0.42365</p> </td></tr>
</table>

<p style="margin-left:15%;"><b>autofax:</b></p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">boost, boost-devel, cron,
ghostscript, imagemagick, libreoffice-common,
libreoffice-base, mariadb-server, policycoreutils,
policycoreutils-python-utils, poppler-tools, samba,
sfftobmp, (in debian-derivates, f&uuml;r mariadb,
zus&auml;tzlich: apt-transport-https)</p></td></tr>
</table>

<p style="margin-left:15%;">falls capisuite benutzt werden
soll:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">capisuite, capiutils,
capi4linux, fcpci-3.10.0, gcc-4.8, g++-4.8, kernel-source
(linux-source), libcapi20-2, libcapi20-3, libxslt-tools,
linux-headers-$(uname -r), python-devel, (in fedora,
zus&auml;tzlich: kernel, kernel-devel,
kernel-modules-extra, numactl-devel, pesign, rpmdevtools;
dadurch kann in aktueller kernel installiert werden),</p></td></tr>
</table>

<p style="margin-left:15%;">falls hylafax benutzt werden
soll:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">hylafax+, hylafax+-client,
sendmail, tiff (im Fall von Version 0.42365</p></td></tr>
</table>

<p style="margin-left:15%;">falls ocr benutzt werden
soll:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">ffmpeg, ffmpeg-devel,
ffmpeg-compat, gcc, libavformat-devel, libffi-devel,
ocrmypdf, python3-devel, python3-pip, python3-setuptools,
rpmfusion, qpdf, redhat-rpm-config, tesseract-ocr, unpaper,
and via &rsquo;python3 pip&rsquo;: cryptography, cffi,
image, M2Crypto, ocrmypdf, PyPDF2, reportlab, ruffus.</p></td></tr>
</table>

<p style="margin-left:15%;">All diese Installationen
k&ouml;nnen abh&auml;ngige Programme
einschlie&szlig;en. <br>
Falls Sie eines dieser Programme nicht wollen oder eine
&auml;ltere Version 0.42365</p>

<h2>AUSWIRKUNGEN
<a name="AUSWIRKUNGEN_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Das Programm
muss zum ordentlichen Funktionieren folgende
Ma&szlig;nahmen ergreifen:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) Installieren von
<b>Hylafax+</b>, falls ein Modem angeschlossen ist und
Hylafax+ nicht installiert ist. Ggf. Konfiguration von
Hylafax+ durch Aufruf von &rsquo;<b>faxsetup
-nointeracitve</b>&rsquo;, durch Editieren der
Konfigurationsdateien <b>config</b> und <b>config.*</b>
(z.B. <b>config.ttyACM0</b>) im
hylafax-Konfigurationsverzeichnis (Vorgabe z.B.:
<b>/var/spool/hylafax/etc/</b>)</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">2) Installieren von
<b>capisuite</b>, falls eine Fritzkarte eingebaut ist und
capisuite nicht installiert ist. Ggf. Bearbeitung der
Konfigurationsdateien <b>/etc/capisuite/capisuite.conf</b>
und <b>/etc/capisuite/fax.conf</b>. Ggf. Bearbeitung des
Python-Scripts f&uuml;r ankommende Faxe (Vorgabe z.B.:
<b>/usr/lib64/capisuite/incoming.py</b>) zur Bestimmung der
Zahl der Klingelt&ouml;ne bis zur Faxannahme, Erstellung
bzw. Bearbeitung der Dateien
&rsquo;<b>/etc/udev/rules.d/46-FKN_isdn_capi.rules</b>&rsquo;,
&rsquo;<b>/etc/modprobe.d/50-blacklist.conf</b>&rsquo;.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">3) Einrichten von Diensten:</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) in systemd (im Verzeichnis
/usr/lib/systemd/system oder /lib/systemd/system),
insbesondere:</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em"><b>hylafax-faxq.service</b>,
<b>hylafax-hfaxd.service</b>,
<b>hylafax-faxgetty-....service</b> (z.B.
<b>hylafax-faxgetty-ttyACM0</b>),</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">capisuite.service,</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) Verschieben von Diensten aus
dem Verzeichnis /etc/init.d in ein neu eingerichtes
Verzeichnis /etc/ausrangiert: <b>hylafax</b>,
<b>capisuite</b></p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">c) falls <b>selinux</b> aktiv
ist (wie standardm&auml;&szlig;ig in fedora), dann
behindert es standardm&auml;&szlig;ig
<b>hylafax</b>; in diesem Fall wird im Hintergrund ein Modul
f&uuml;r selinux eingerichtet, um den Betrieb von
hylafax-hfaxd wieder zu erlauben. Ferner muss (bis zur
eventuellen Erstellung einer ma&szlig;geschneiderteren
L&ouml;sung) die Dom&auml;ne &rsquo;getty&rsquo; mit
dem Befehl &rsquo;<b>semanage permissive -a
getty_t</b>&rsquo; in selinux entsch&auml;rft werden, um
faxe &uuml;ber hylafax empfangen zu k&ouml;nnen.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">4) Erstellen einer
Protokolldatei, standardm&auml;&szlig;ig
<b>/var/log/autofax.log</b>.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">5) ggf. Erstellen und
Zugreifbarmachen der bestimmbaren <b>Verzeichnisse</b>
f&uuml;r zu sendende, wartende, abgearbeitete und
empfangene Faxe.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">6) ggf. Erstellen und
Ver&auml;ndern der Konfigurationsdatei autofax.conf in
dem Verzeichnis, in dem auch es selbst steht (Vorgabe:
/usr/local/sbin/autofax).</p> </td></tr>
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
Verzeichnisse in /etc/samba/smb.conf, ggf.
Einf&uuml;gen/Passwortzuteilen des Programmbenutzers
bzw. (falls root) des f&uuml;r die Capisuite
gew&auml;hlten Benutzers als Samba-Bentzer.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">Falls Suse-Firewall vorhanden,
samba-Server fuer &quot;externe Zone&quot; eintragen.</p></td></tr>
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
insbesondere:</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) in hylafax: durch Aufruf von
&rsquo;faxrm&rsquo;</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) in capisuite: durch
L&ouml;schen der Dateien wie
/var/spool/capisuite/users/&lt;user&gt;/sendq/*.txt und
~/*.sff. In capisuite kann auch eine verwaiste Lock-Datei
(/var/spool/capisuite/users/&lt;user&gt;/sendq/*.lock)
gel&ouml;scht werden.</p></td></tr>
</table>

<h2>FEHLER
<a name="FEHLER_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Fehler bitte
mit u.a. dem Wort &rsquo;autofax&rsquo; in der Ueberschrift
melden. <br>
Bitte auch melden, wenn sich &Auml;nderungsbedarf durch
andere Hard- bzw. Software ergeben.</p>

<h2>HAFTUNG
<a name="HAFTUNG_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Das Programm
wurde mit bester Absicht entwickelt und durch den Autor
getestet. <br>
Trotzdem kann der Autor f&uuml;r keine Sch&auml;den
haften, die durch das Programm entstehen
k&ouml;nnten</p>

<h2>AUTOR
<a name="AUTOR_D"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Gerald Schade
(geraldschade@gmx.de; www.diabdachau.de)</p>
<hr>
</body>
</html>
