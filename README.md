<b>autofax</b> − fax server functionality: induces automatic fax transmission of files, naming of received faxes and logging in a database
manpage-Hilfe in deutsch verfügbar: ’man autofax’ oder ’man -Lde autofax’.

SYNOPSIS

autofax [−lg|--language <d|e>] [−v|--verbose] [−l|--log] [−lvz|--logvz <pfad>] [−ld|--logdname <string>] [−ldn|--logdateineu] [−kd|--konfdat <string>] [−zvz|--zufaxenvz <pfad>] [−wvz|--wartevz <pfad>] [−evz|--empfvz <pfad>] [−cm|--cronminut <zahl>] [−kc|--keincapi] [−kh|--keinhyla] [−cz|--capizuerst] [−hz|--hylazuerst] [−mod|--modem <string>] [−mc|--maxcapinr <zahl>] [−mh|--maxhylanr <zahl>] [−ckzl|--capiklingelzahl <zahl>] [−cuser|--cuser <string>] [−hkzl|--hylaklingelzahl <zahl>] [−gz|--gleichziel] [−afs|--anfaxstring <string>] [−acfs|--ancfaxstring <string>] [−ahfs|--anhfaxstring <string>] [−as|--anstring <string>] [−us|--undstring <string>] [−host|--host <string>] [−muser|--muser <string>] [−mpwd|--mpwd <string>] [−db|--db <string>] [−sqlv|--sqlv] [−rf|--rueckfragen] [−loef|--loeschefax] [−loew|--loeschewaise] [−loea|--loescheallew] [−loee|--loescheempf] [−kez|--korrerfolgszeichen] [−bwv|--bereinigewv] [−lista|--listarchiv] [−listf|--listfailed] [−listi|--listinca] [−n|--dszahl <zahl>] [−h|-help|-?|-hilfe]

SHORT DESCRIPTION

autofax is a command line programme to remit files of a certain directory automatically to hylafax (in case a linux-compatible modem is installed) and/or capisuite (in case a fritzcard 2.0 or 2.1 is installed), if the fax number is integrated in the file name correctly. Furthermore, autofax holds the posted faxes in a mariadb database.
Additionally, received faxes from hylafax/capisuite can be named with the sender’s name according to his telephone number and stored.

INSTALLATION

Please as root copy the files autofax.cpp, autofax.h, vorgaben.cpp, DB.cpp, DB.h, konsole.h, makefile, viautofax.sh, man_de, man_en and maybe autofax into a directory (subsequently here called: /root/bin/autofax).
cd /root/bin/autofax
make
autofax
(anwer some questions)

USAGE

Ideally, the program should have installed itsself after a single call (see above) in a self-running way (especially on openSUSE-Leap 42.1 or Ubuntu 14.04, possibly on others; systemctl (systemd) should run).
Then a directory e.g. ’zufaxen’ exists, in which e.g. users in a network (e.g. via a samba share) can deposit files to be faxed, e.g.
"Medical report on Frank Ill to Dr. Healthy and Frank Ill to fax 099 987654321 and 088 887654321.doc" (it could also be e.g. an *.xls, a *.jpg, a *.tif, a *.txt, a *pdf file).
When autofax is called for the next time (per default 2 minutes), the above mentioned example file will initially be copied and renamed into
"Medical report on Frank Ill to Dr. Healthy to fax 099 987654321.doc" and
"Medical report on Frank Ill to Frank Ill to fax 088 887654321.doc" and converted into the pdf-files
"Medical report on Frank Ill to Dr. Healthy to fax 099 987654321.pdf" and
"Medical report on Frank Ill to Frank Ill to fax 088 887654321.pdf".
Those are subsequently being relayed to hylafax or Capisuite and from there sent.
Simultaneously they are being moved from ’zufaxen’ to the waiting directory, e.g. ’warteauffax’ and recorded in the spool table spooltab.
At each call, autofax checks the status of hylafax and/or Capisuite. The Finishing of a fax process there causes autofax to move the source files (here the above mentioned .doc- and .pdf-files) from the waiting directory to one or several archive directories or a directory for failed faxes and to move their databas record from ’spooltab’ to the archive table ’outa’.
Further on, incoming faxes via hylafax or Capisuite are being transmitted to an incoming directory and if applicable named including the sender’s name. To this purpose, customizeable sql commands are being used, if specified.
Depending on operating system, accessability and preferences the users thus could look up the status of their faxes in the above mentioned directories, in the database tables or by calling ’autofax’, ’autofax -lista’, ’autofax -listf’ or ’autofax -listi’.
autofax shall be executed as root.

OPTIONS

With ’autofax -?’, all command line options can be seen. Some options (e.g. the sql commands) cannot bei set via the command line, but only via the configuration file, which can be edited directly or interactively by ’autofax -rf’.
-lg, --language <string>: language/Sprache/Lingue/Lingua [deutsch,english] ’e’
-v, --verbose: screen output more verbose
-l, --log: put detailed logs in file ’/var/log/autofax.log’ (otherwise shorter)
-lvz, --logvz <path>: choses <path> as log directory, currently ’/var/log’
-ld, --logdname <string>: log file <string> (in path ’/var/log’) will be used instead of ’autofax.log’
-ldn, --logdateineu: delete log file afore
-kd, --konfdat <string>: uses configuration file <string> instead of ’/usr/local/sbin/autofax.conf’
-zvz, --zufaxenvz <path>: faxes the files from <path> instead of ’...’
-wvz, --wartevz <path>: files are waiting in <path> instead of ’...’
-evz, --empfvz <path>: directory for recieved faxes ’...’
-cm, --cronminut <zahl>: every how many minutes shall autofax be called in crontab (0=not at all) ’2’
-kc, --keincapi: do not use capisuite
-kh, --keinhyla: do not use hylafax
-cz, --capizuerst: try to send faxes primarily via capisuite
-hz, --hylazuerst: try to send faxes primarily via hylafax
-mod, --modem <string>: Modem used for hylafax ’’
-mc, --maxcapinr <zahl>: try Hylafax after <no> tries of Capisuite instead of ’3’
-mh, --maxhylanr <zahl>: try Capisuite after <no> tries of Hylafax instead of ’3’
-ckzl, --capiklingelzahl <zahl>: No. of bell rings until Capisuite accepts the call, instead of ’1’
-cuser, --cuser <string>: takes the linux user <string> for Capisuite instead of ’schade’
-hkzl, --hylaklingelzahl <zahl>: No. of bell rings until hylafaxs accepts the call, instead of ’2’
-gz, --gleichziel: copy faxes into target directory irrespective of faxing success
-afs, --anfaxstring <string>: the fax number will be expected after <string> instead of ’an Fax’
-acfs, --ancfaxstring <string>: fax no.for fax with preference to capisuite is expected after <string> instead of ’an cFax’
-ahfs, --anhfaxstring <string>: fax no.for fax with preference to hylafax is expected after <string> instead of ’an hFax’
-as, --anstring <string>: name of addressee is expected after <string> instead of ’ an ’
-us, --undstring <string>: separating string <string> for multiple addressees/tel’numbers, instead of ’und’
-host, --host <string>: takes the database on host <string> instead of ’localhost’
-muser, --muser <string>: takes the user <string> for MySQL/MariaDB instead of ’praxis’
-mpwd, --mpwd <string>: takes the password <string> for MySQL/MariaDB instead of ’...’
-db, --db <string>: uses the database <string> instead of ’...’
-sqlv, --sql-verbose: screen output with SQL commands
-rf, --rueckfragen: all parameters will be prompted (some of them not shown here)
-loef, --loeschefax: delete a fax with query
-loew, --loeschewaise: delete entries from ‘spool‘ without detection of file in waiting directory or capisuite fax or hyla-fax
-loea, --loescheallew: delete all waiting faxes and associated entries from ‘spool‘
-loee, --loescheempf: delete received files that could not be processed
-kez, --korrerfolgszeichen: in the database table ‘outa‘ the success flag is being corrected
-bwv, --bereinigewv: Examine files in waiting directory against the tables ‘outa‘ and clean them up
-lista, --listarchiv: lists entries from ‘outa‘ with success flag
-listf, --listfailed: lists entries from ‘outa‘ without success flag
-listi, --listinlet: lists entries from ‘inca‘
-n, --dszahl <zahl>: No. of listed entries = <zahl> instead of ’30’

FUNCTIONALITY

1) The current hardware is being checked.

a) with the command ’lspci | grep -i isdn’ for a fritz card.
b) with the command ’stty -F’ for a fax modem.

2) The fax configuration file fax.conf of capisuite is read, if it exists
	

3) Further defaults from the program code are assigned which can be overloaded by the autofax configuration file (see 4), command line arguments or anwers to questions (see 5).
	

4) Defaults are loaded from the configuration file, if it exists (per default autofax.conf in the same directory as autofax, per default /usr/local/sbin/autofax))
	

5) Questions are asked, if values are missing from the configuration file (see 4) or if a command line option demands interacitivity.
	

6) The directory of hylafax is beeing determined (/var/spool/hylafax or /var/spool/fax), if hylafax is installed.
	

7) Directories used by the users for fax files to be sent, for waiting faxes, for fax files already sent, for failed faxes and for received faxes are being checked and created if needed. Thereby user defined file name patterns can be respected to store successfully sent faxes in different directories.
	

8) The program inserts itsself if wanted and necessary in crontab in order to be called in adjustable intervals. To avoid this, either ’cronminut’ can be set to 0, or the already generated autofax entry can be commented out with a leading ’#’.
	

9) The program checks if all user-relevant directories (see 7) are being included in samba shares in /etc/samba/smb.conf; such are being added if needed.
	

10) Working of MariaDB is being checked, if necessary it is being (installed and) started, the database tables spooltab (for faxes just in spool), outa (for sent and failed faxes) and inca (for received faxes) are being checked and if necessary created or amended.
	

11) In case of the respective command line options corrections in the contents of the waiting directory or of the database tables are being commited or their contents is being listed and then the program is being finished.
	

12) Otherwise, file in the outgoing directory are being analysed. Each file with some identifiable fax number(s) within its file name which is or can be converted in/into pdf format will be moved to to waiting directory and recorded in spooltab.

If a file contains more than one recepients and/or a conversion to pdf is necessary, additional files are generated and the original file may be renamed. If necessary, additional numbers near the end of the file name(s) may be added in order not to conflict with any other file name in one of the directories mentioned in 7).
If more files have been generated, the successive movements and recordings are being carried out with all of them.
	

13) Depending on the configuration the functionaliy of hylafax and/or capisuite is being checked and if necessary and possible restored (including by installation of those programs)
	

14) In case of respective command line options faxes are being deleted and the program is finished.
	

15) Otherwise the files which have been recorded under 12) in spooltab are being forwarded to hylafax or capisuite and this is being protocolled in spooltab.
	

16) All faxes which are recorded in spooltab as waiting are being checked in hylafax/capisuite as to their status which is being updated in spooltab (number of tries hitherto).

If hylafax and capisuite are working simultaneously and a prespecified number of send tries has been reached without success in the programs of the first preference of those two, the fax is additionally forwarded to the second of the two programs.
If the fax transmission is finished (with/without success), the file is being moved from the waiting directory to the respective directory for sent faxes or for failed faxes and the database entry is being transferred from spooltab to outa.
The status of the mentioned faxes is being displayed.
	

17) If additional faxes in the spool of hylafax/capisuite are detected which are not created via autofax, they are displayed.
	

18) With hylafax/capisuite received faxes are copied to a receiving directory and there named with the name of the sender, if possible, by means of their telephone number which is being looked up using a predefineable number of predefineable sql commands, which are applied one after another until the telephone number is found.
	

19) The configuration file is being written, if necessary.

ERRORS

Please report any errors

LIABILITY

The program has been written with the best aim and has been tested extensively by the author.
Nevertheless the author cannot be liable for any damage by the program.

AUTHOR

Gerald Schade (geraldschade@gmx.de)
