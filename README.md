
<h1 align="center">AUTOFAX (Version 0.40784)</h1>

<a href="#NAME">NAME</a><br>
<a href="#SYNOPSIS">SYNOPSIS</a><br>
<a href="#SHORT DESCRIPTION">SHORT DESCRIPTION</a><br>
<a href="#INSTALLATION">INSTALLATION</a><br>
<a href="#USAGE">USAGE</a><br>
<a href="#OPTIONS">OPTIONS</a><br>
<a href="#FUNCTIONALITY">FUNCTIONALITY</a><br>
<a href="#PRECONDITIONS">PRECONDITIONS</a><br>
<a href="#IMPACT">IMPACT</a><br>
<a href="#ERRORS">ERRORS</a><br>
<a href="#LIABILITY">LIABILITY</a><br>
<a href="#AUTHOR">AUTHOR</a><br>

<hr>


<h2>NAME
<a name="NAME"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em"><b>autofax</b>
&minus; fax server functionality: induces automatic fax
transmission of files, naming of received faxes and logging
of all of them in a database <br>
manpage-Hilfe in deutsch verf&uuml;gbar: &rsquo;man
autofax&rsquo; oder &rsquo;man -Lde autofax&rsquo;.</p>

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
[<b>&minus;v|--verbose</b>]
[<b>&minus;lvz|--logvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;ld|--logdname&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;l|--log</b>] [<b>&minus;ldn|--logdateineu</b>]
[<b>&minus;kd|--konfdat&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;zvz|--zufaxenvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;wvz|--wartevz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;nvz|--nichtgefaxtvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;evz|--empfvz&nbsp;</b><i>&lt;pfad&gt;</i>]
[<b>&minus;cm|--cronminut&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;capi|--obcapi</b>]
[<b>&minus;nocapi|--keincapi</b>]
[<b>&minus;hyla|--obhyla</b>]
[<b>&minus;nohyla|--keinhyla</b>]
[<b>&minus;cz|--capizuerst</b>]
[<b>&minus;hz|--hylazuerst</b>]
[<b>&minus;mod|--hmodem&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mc|--maxcapiv&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;mh|--maxhylav&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;cuser|--cuser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ckzl|--capiklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;hkzl|--hylaklingelzahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;gz|--gleichziel</b>]
[<b>&minus;afs|--anfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;acfs|--ancfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;ahfs|--anhfaxstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;as|--anstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;us|--undstr&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;host|--host&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;muser|--muser&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;mpwd|--mpwd&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;db|--datenbank&nbsp;</b><i>&lt;string&gt;</i>]
[<b>&minus;sqlv|--sql-verbose</b>]
[<b>&minus;rf|--rueckfragen</b>]
[<b>&minus;norf|--keinerueckfragen</b>]
[<b>&minus;loef|--loeschefax</b>]
[<b>&minus;loew|--loeschewaise</b>]
[<b>&minus;loea|--loescheallew</b>]
[<b>&minus;loee|--loescheempf</b>]
[<b>&minus;kez|--korrerfolgszeichen</b>]
[<b>&minus;bwv|--bereinigewv</b>] [<b>&minus;st|--stop</b>]
[<b>&minus;lista|--listarchiv</b>]
[<b>&minus;listf|--listfailed</b>]
[<b>&minus;listi|--listinca</b>]
[<b>&minus;n|--dszahl&nbsp;</b><i>&lt;zahl&gt;</i>]
[<b>&minus;info|--version</b>] [<b>&minus;vi|--vi</b>]
[<b>&minus;h|-help|-?|-hilfe</b>]</p> </td></tr>
</table>

<h2>SHORT DESCRIPTION
<a name="SHORT DESCRIPTION"></a>
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
<a name="INSTALLATION"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">- If the
program &rsquo;git&rsquo; is installed, You can start with:
<br>
git clone http://github.com/libelle17/autofax && cd
autofax <br>
- otherwise e.g. (if &rsquo;wget&rsquo; ist installed, which
is mostly the case) with: <br>
P=autofax; T=$P.tar.gz; cd ~; wget
https://github.com/libelle17/$P/archive/master.tar.gz -O $T
&& tar xpvf $T && rm -f $T && { for
i in $(ls -d ${P}_* 2&gt;/dev/null | cut -d&quot;_&quot; -f2
| sort -nr); do j=$((i+1)); case $i in
&quot;&quot;|*[!0-9]*);; *) mv ${P}_$i ${P}_$j; esac; done;
test -e $P && mv $P ${P}_1; mv $P-master $P
&& cd $P; } <br>
there, if the program &rsquo;make&rsquo; is not available,
You can call &rsquo;install.sh&rsquo;, this should install
&rsquo;make&rsquo;; otherwise, You also can call: <br>
- if You want to have ensured the currentness of
&rsquo;gcc6&rsquo; before compilation: <br>
make <br>
- otherwise: <br>
make glei <br>
furtheron: <br>
sudo make install <br>
autofax <br>
(answer some questions of the program) <br>
The first execution may take some time. <br>
Preconditions see below</p>

<h2>USAGE
<a name="USAGE"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Ideally, the
program should have installed itsself after a single call
(see above) in a self-running way (especially on
openSUSE-Leap 42.1 or Ubuntu 16.040 (only with a modem via
hylafax), possibly on others; systemctl (systemd) should
run). <br>
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
directory for failed faxes and to move their databas record
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
<a name="OPTIONS"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">With
&rsquo;<b>autofax -?</b>&rsquo;, all command line options
can be seen. Some options (e.g. the sql commands) cannot bei
set via the command line, but only via the configuration
file, which can be edited directly or interactively by
&rsquo;<b>autofax -rf</b>&rsquo;. <b><br>
-lg, --language &lt;string&gt;</b>:
language/Sprache/Lingue/Lingua [deutsch,english]
&rsquo;e&rsquo; <b><br>
-v, --verbose</b>: screen output more verbose <b><br>
-l, --log</b>: put detailed logs in file
&rsquo;/var/log/autofax.log&rsquo; (otherwise shorter)
<b><br>
-lvz, --logvz &lt;path&gt;</b>: choses &lt;path&gt; as log
directory, currently &rsquo;/var/log&rsquo; <b><br>
-ld, --logdname &lt;string&gt;</b>: log file &lt;string&gt;
(in path &rsquo;/var/log&rsquo;) will be used instead of
&rsquo;autofax.log&rsquo; <b><br>
-ldn, --logdateineu</b>: delete log file afore <b><br>
-kd, --konfdat &lt;string&gt;</b>: uses configuration file
&lt;string&gt; instead of
&rsquo;/usr/local/sbin/autofax.conf&rsquo; <b><br>
-zvz, --zufaxenvz &lt;path&gt;</b>: faxes the files from
&lt;path&gt; instead of &rsquo;...&rsquo; <b><br>
-wvz, --wartevz &lt;path&gt;</b>: files are waiting in
&lt;path&gt; instead of &rsquo;...&rsquo; <b><br>
-evz, --empfvz &lt;path&gt;</b>: directory for recieved
faxes &rsquo;...&rsquo; <b><br>
-cm, --cronminut &lt;zahl&gt;</b>: every how many minutes
shall autofax be called in crontab (0=not at all)
&rsquo;2&rsquo; <b><br>
-kc, --keincapi</b>: do not use capisuite <b><br>
-kh, --keinhyla</b>: do not use hylafax <b><br>
-cz, --capizuerst</b>: try to send faxes primarily via
capisuite <b><br>
-hz, --hylazuerst</b>: try to send faxes primarily via
hylafax <b><br>
-mod, --modem &lt;string&gt;</b>: Modem used for hylafax
&rsquo;&rsquo; <b><br>
-mc, --maxcapinr &lt;zahl&gt;</b>: try Hylafax after
&lt;no&gt; tries of Capisuite instead of &rsquo;3&rsquo;
<b><br>
-mh, --maxhylanr &lt;zahl&gt;</b>: try Capisuite after
&lt;no&gt; tries of Hylafax instead of &rsquo;3&rsquo;
<b><br>
-ckzl, --capiklingelzahl &lt;zahl&gt;</b>: No. of bell rings
until Capisuite accepts the call, instead of &rsquo;1&rsquo;
<b><br>
-cuser, --cuser &lt;string&gt;</b>: takes the linux user
&lt;string&gt; for Capisuite instead of &rsquo;schade&rsquo;
<b><br>
-hkzl, --hylaklingelzahl &lt;zahl&gt;</b>: No. of bell rings
until hylafaxs accepts the call, instead of &rsquo;2&rsquo;
<b><br>
-gz, --gleichziel</b>: copy faxes into target directory
irrespective of faxing success <b><br>
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
-db, --db &lt;string&gt;</b>: uses the database
&lt;string&gt; instead of &rsquo;...&rsquo; <b><br>
-sqlv, --sql-verbose</b>: screen output with SQL commands
<b><br>
-rf, --rueckfragen</b>: all parameters will be prompted
(some of them not shown here) <b><br>
-loef, --loeschefax</b>: delete a fax with query <b><br>
-loew, --loeschewaise</b>: delete entries from
&lsquo;spool&lsquo; without detection of file in waiting
directory or capisuite fax or hyla-fax <b><br>
-loea, --loescheallew</b>: delete all waiting faxes and
associated entries from &lsquo;spool&lsquo; <b><br>
-loee, --loescheempf</b>: delete received files that could
not be processed <b><br>
-kez, --korrerfolgszeichen</b>: in the database table
&lsquo;outa&lsquo; the success flag is being corrected
<b><br>
-bwv, --bereinigewv</b>: Examine files in waiting directory
against the tables &lsquo;outa&lsquo; and clean them up
<b><br>
-lista, --listarchiv</b>: lists entries from
&lsquo;outa&lsquo; with success flag <b><br>
-listf, --listfailed</b>: lists entries from
&lsquo;outa&lsquo; without success flag <b><br>
-listi, --listinlet</b>: lists entries from
&lsquo;inca&lsquo; <b><br>
-n, --dszahl &lt;zahl&gt;</b>: No. of listed entries =
&lt;zahl&gt; instead of &rsquo;30&rsquo; <b><br>
-info, --version</b> : shows the program version <b><br>
-vi, --vi</b> : edit the configuration file <b><br>
-h, --help</b> : shows help</p>

<h2>FUNCTIONALITY
<a name="FUNCTIONALITY"></a>
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
sent faxes or for failed faxes and the database entry is
being transferred from <b>spooltab</b> to <b>outa</b>.</p></td></tr>
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
created via autofax, they are displayed.</p></td></tr>
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


<p style="margin-top: 1em">19) The configuration file is
being written, if necessary.</p></td></tr>
</table>

<h2>PRECONDITIONS
<a name="PRECONDITIONS"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">The program was
adjusted to an installation of Opensuse 42.1 or Ubuntu 16.04
with standard options. The user must be allowed to call the
command &rsquo;sudo&rsquo;. &rsquo;GNU make&rsquo; has to be
installed (which shall be accomplished if necessary by
calling install.sh). Further needed programs will be
installed by the makefile or by autofax itsself via zypper
or apt-get, if possible. Those are: <b><br>
makefile:</b> <br>
g++, libmysqlclient-dev(el), libtiff-dev(el) <b><br>
autofax:</b> <br>
cron, soffice, convert, hylafax+, hylafax+-client,
kernel-source, fcpci-3.10.0, kkeil Factory repository,
capisuite, capi4linux, i4l-isdnlog, mariadb.</p>

<h2>IMPACT
<a name="IMPACT"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">The program has
to take the following measures for its neat function:</p>

<table width="100%" border="0" rules="none" frame="void"
       cellspacing="0" cellpadding="0">
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">1) Installation of hylafax+, in
case a modem is connected and hylafax+ is not installed. If
necessary configuration of hylafax+ by calling
&rsquo;faxsetup -nointeracitve&rsquo;, by editing the
configuration files config and config.* in the hylafax
configuration directory (default e.g.
/var/spool/hylafax/etc)</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">2) Installation of capisuite, in
case a fritzcard is inserted and capisuite is not installed.
If necessary configuration of /etc/capisuite/capisuite.conf
and /etc/capisuite/fax.conf. If necessary edition of the
python-script for received faxes (default e.g.
/usr/lib64/capisuite/incoming.py) in order to determine the
rings before answer, creation and edition of the files
&rsquo;/etc/udev/rules.d/46-FKN_isdn_capi.rules&rsquo;,
&rsquo;/etc/modprobe.d/50-blacklist.conf&rsquo;.</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">3) Installation of services</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">a) in systemd (in the directory
/usr/lib/systemd/system or /lib/systemd/system),
especially:</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">hylafax-faxq.service,
hylafax-hfaxd.service, hylafax-faxgetty-....service,</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">capisuite.service,</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">b) Moving of existing service
files from the directory /etc/init.d to a newly created
directory /etc/ausrangiert:</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">hylafax, capisuite</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">4) Creation of a logfile
/var/log/autofax.log</p> </td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">5) if necessary creation and
making accessible of the configurable directories for faxes
to be sent, waiting, finished and failed.</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">6) if necessary creation and
making accessible of the configuration file autofax.conf in
the same directory where the program is located by itsself
(default: /usr/local/sbin/autofax).</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">7) Insertion of a line for the
program in crontab (of root)</p></td></tr>
<tr valign="top" align="left">
<td width="11%"></td>
<td width="89%">


<p style="margin-top: 1em">8) if necessary insertion of
sections for the directories mentioned unter 3) in
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
<a name="ERRORS"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Please report
any errors. Please report as well, if different hard- or
software yield a requirement for a program modification.</p>

<h2>LIABILITY
<a name="LIABILITY"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">The program has
been written with the best aim and has been tested by the
author. <br>
Nevertheless the author cannot be liable for any damage by
the program.</p>

<h2>AUTHOR
<a name="AUTHOR"></a>
</h2>


<p style="margin-left:11%; margin-top: 1em">Gerald Schade
(geraldschade@gmx.de; www.diabdachau.de)</p>
<hr>
</body>
</html>
