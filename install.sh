#!/bin/sh
DN=/dev/null
KR=">$DN 2>&1" # keine Rueckmeldung
KF=" 2>$DN" # keine Fehlermeldung
UNROH=uninstall
UNF=${UNROH}inv # Name muss identisch sein mit Ende von uindt in kons.cpp 
pgroff="groff groff-base"
dev=devel
libmc=libmysqlclient
fed=0
CCInst=gcc6-c++

# Installationsprogramm ermitteln
getIPR() {
  CTAGS=ctags;
	{ which zypper  >$DN 2>&1 &&{ 
		Z=zypper;g=--gpg-auto-import-keys;IPR="$Z -n $g in ";IP_R="$Z $g in ";UPR="sudo zypper rm -u ";pgroff=groff;
  REPOS="sudo zypper lr|grep 'g++\|devel_gcc'\$(KR)||sudo zypper ar http://download.opensuse.org/repositories/devel:/gcc/\`cat /etc/*-release|grep ^NAME= |cut -d'\"' -f2|sed 's/ /_/'\`_\`cat /etc/*-release|grep ^VERSION_ID= |cut -d'\"' -f2\`/devel:gcc.repo;";
  urepo="sudo zypper lr|grep \\\\\"g++\\\\\|devel_gcc\\\\\"\$(KR) && sudo zypper rr devel_gcc;";
  COMP="gcc gcc-c++ \$(CCInst)";
	} }||
	{ which apt-get >$DN 2>&1 &&{ IPR="sudo apt-get --assume-yes install ";IP_R=$IPR;
	                                    UPR="sudo apt-get --auto-remove purge ";
																			dev=devel;
																			COMP="build-essential linux-headers-\`uname -r\`";
																			CTAGS=exuberant-ctags;} }||
	{ which dnf     >$DN 2>&1 &&{ fed=1;IPR="sudo dnf -y install ";UPR="sudo dnf remove ";} }||
	{ which yum     >$DN 2>&1 &&{ fed=1;IPR="sudo yum -y install ";UPR="sudo yum remove ";} }
	[ $fed = 1 ] &&{ libmc=mysql;COMP="make automake gcc-c++ kernel-devel";IP_R=$IPR;}
	{ which rpm >$DN 2>&1 && SPR="rpm -q ";}||
	{ which dpkg >$DN 2>&1 && SPR="dpkg -s ";}
}

exportvars() {
	rm -f vars;
	for v in KR KF IPR IP_R UPR SPR UNROH UNF pgroff dev libmc REPOS urepo COMP; do eval nv=\$$v; printf "$v:=$nv\n">>vars; done
}

basenam=$(basename $0)
ext=${basenam##*.}

# diese Datei wird wegen obigem in viall gesourct, deshalb dort der Rest zu uebergehen
if [ $ext = sh ]; then
P=autofax
AUNF=$HOME/$P/$UNF
HOSTER=github.com
ACC=libelle17
rot="\033[1;31m"
gruen="\033[1;32m"
blau="\033[1;34m"
reset="\033[0m"
aPWD=`pwd`
nPWD=${PWD##*/}

# Gruppen, deren Mitglieder sudo aufrufen koennen; fuer Debian muss zuerst 'sudo' genannt werden, weil eine Zuordnung zu 'root' nichts hilft (s.u. tail)
SUG="admin\|root\|sudo\|wheel\|ntadmin";

# hier geht's los
getIPR;
# falls der Benutzer 'sudo' fehlt oder der aktuelle Benutzer ihn nicht aufrufen darf, weil er nicht Mitglied einer Administratorgruppe ist ...
{ which sudo >/dev/null && id -Gzn $USER|grep -qw "$SUG";}||{ 
	printf "Must allow '$blau$USER$reset' to call '${blau}sudo$reset'. Please enter ${blau}root$reset's password if asked:\n"
	printf "Muss '$blau$USER$reset' den Aufruf von '${blau}sudo$reset' ermoeglichen. Bitte geben Sie bei der Frage das Passwort von '${blau}root$reset' ein:\n";
	su -c "$IPR sudo;";grep -q \"sudo\" $AUNF||printf \"${UPR}sudo\n\">>$AUNF;
	su -c "usermod -aG $(cut -d: -f1 /etc/group|grep -w "$SUG"|tail -n1) "$USER";"||exit
	printf "Please log out and in again, change to the directory '$blau$PWD$reset' and then call '${blau}sh $0$reset' again!\n"
	printf "Bitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach '$blau$PWD$reset' und rufen Sie '${blau}sh $0$reset' dann nochmal auf!\n";
	exit;
}
# falls make fehlt, dann installieren ...
$SPR make >$DN 2>&1 ||{
	echo Installing/ Installiere 'make' ....;
  id su >$DN 2>&1 && { su -c "$IPR make;";true;} || sudo $IPR make;
	grep -q make $AUNF|printf "${UPR}make\n">>$AUNF;
}
$SPR make >/dev/null || exit
# wenn $P schon das aktuelle Verzeichnis ist und wenn es dort einige notwendige Dateien gibt, dann nicht mehr neu runterladen ...
[ $nPWD = $P -a -f Makefile -a -f $P.cpp ]&&{
	printf "${rot}Installing/ Installiere ... $reset\n"
	true;
}||{
# ... sonst moegliche alte Quelldateiverzeichnisse $P umbenennen, aktuelle Version neu herunterladen ...
	printf "${rot}Downloading/ Lade runter ... $reset\n"
	T=$P.tar.gz;
	cd ~; 
	wget https://$HOSTER/$ACC/$P/archive/master.tar.gz -O "$T" && 
		tar xpvf $T && 
		rm -f $T && {
			VORIGE=$(ls -d ~/${P}_* 2>$DN| cut -d"_" -f2 | sort -nr);
			for i in $VORIGE; do 
			case $i in ""|*[!0-9]*);; *) 
				j=$((i+1)); 
				echo mv ${P}_$i ${P}_$j; 
				mv ${P}_$i ${P}_$j; 
				esac; 
				done; 
				test -e $P && mv $P ${P}_1; 
				mv $P-master $P &&{
				  Q=${P}_1/$UNF; test -f $Q && cp -ai $Q $P
					cd $P; }
		}|| exit;
}
exportvars;
# ... und dann kompilieren und installieren
make opts &&
sudo make install; erg=$?;
[ $erg = 0 ] && farbe=$blau || farbe=$rot;
printf "Result code/ Ergebniscode: ${farbe}$erg${reset}\n"
fi
