#!/bin/sh
# Installationsprogramm ermitteln
getIPR() {
  CTAGS=ctags;
	{ which zypper  >$DN 2>&1 &&{ 
		Z=zypper;g=--gpg-auto-import-keys;IdPR="$Z -n $g in ";IP_R="sudo $Z $g in ";UPR="sudo $Z rm -u ";pgroff=groff;
  REPOS="sudo $Z lr|grep 'g++\|devel_gcc'\>$KR||sudo $Z ar http://download.opensuse.org/repositories/devel:/gcc/\`cat /etc/*-release|grep ^NAME= |cut -d'\"' -f2|sed 's/ /_/'\`_\`cat /etc/*-release|grep ^VERSION_ID= |cut -d'\"' -f2\`/devel:gcc.repo;";
  urepo="sudo $Z lr|grep \\\\\"g++\\\\\|devel_gcc\\\\\"\>$KR && sudo $Z rr devel_gcc;";
  COMP="gcc gcc-c++ \$(CCInst)";
	} }||
	{ which apt-get >$DN 2>&1 &&{ IdPR="apt-get --assume-yes install ";IP_R="sudo $IdPR";
	                                    UPR="sudo apt-get --auto-remove purge ";
																			dev=dev;
																			COMP="build-essential linux-headers-\$(shell uname -r)";
																			CTAGS=exuberant-ctags;} }||
	{ which dnf     >$DN 2>&1 &&{ fed=1;IdPR="dnf -y install ";UPR="sudo dnf remove ";} }||
	{ which yum     >$DN 2>&1 &&{ fed=1;IdPR="yum -y install ";UPR="sudo yum remove ";} }
	[ $fed = 1 ] &&{ libmc=mysql;COMP="make automake gcc-c++ kernel-devel";IP_R="sudo $IdPR";}
	{ which rpm >$DN 2>&1 && SPR="rpm -q ";}||
	{ which dpkg >$DN 2>&1 && SPR="dpkg -s ";}
	IPR="sudo $IdPR";
}

exportvars() {
	rm -f vars;
	for v in KR KF IPR IP_R UPR SPR UNROH UNF AUNF pgroff dev libmc REPOS urepo COMP; do eval nv=\$$v; printf "$v:=$nv\n">>vars; done
}

einricht() {
 which $1 >$DN 2>$DN||{
   getIPR;
	 printf "Installing/ Installiere $1 ...\n";
	 ${IPR}$2;
   test -f $AUNF&&grep -q " $2" $AUNF||{
	  T=${UPR}$2;
#		printf "$T\nprintf \"%%b$T%%b\\\n\" \"\\033[1;34m\" \"\\033[0m\"\n">>$AUNF;
		printf "$T\nprintf \"\$blau%%s\$reset\\\n\" \"$T\"\n">>$AUNF;
	 }
 }
}

DN=/dev/null
KR="$DN 2>&1" # keine Rueckmeldung
KF=" 2>$DN" # keine Fehlermeldung
UNROH=uninstall
UNF=${UNROH}inv # Name muss identisch sein mit Ende von uindt in kons.cpp 
pgroff="groff groff-base"
dev=devel
libmc=libmysqlclient
fed=0
CCInst=gcc6-c++

basenam=$(basename $0)
ext=${basenam##*.}

P=autofax
mkdir -p $HOME/$P
AUNF=$HOME/$P/$UNF
# diese Datei wird wegen obigem in viall gesourct, deshalb dort der Rest zu uebergehen
if [ $ext = sh ]; then
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
	printf "Must allow '$blau$USER$reset' to call '${blau}sudo$reset'. Please enter ${blau}root$reset's password at the next two questions:\n"
	printf "Muss '$blau$USER$reset' den Aufruf von '${blau}sudo$reset' ermoeglichen. "
	printf "Bitte geben Sie bei den beiden Fragen das Passwort von '${blau}root$reset' ein:\n";
	test -f $AUNF&&grep -q "[^;] sudo" $AUNF||printf "${UPR}sudo\nprintf \"\$blau%%s\$reset\\\n\" \"${UPR}sudo\"\n">>$AUNF;
	su -c "$IdPR sudo;";
	su -c "usermod -aG $(cut -d: -f1 /etc/group|grep -w "$SUG"|tail -n1) "$USER";"||exit
	printf "Please log out and in again, change to the directory '$blau$PWD$reset' and then call '${blau}sh $0$reset'!\n"
	printf "Bitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach '$blau$PWD$reset' und rufen Sie '${blau}sh $0$reset' auf!\n";
	exit;
}
# falls make fehlt, dann installieren ...
einricht make make
# $SPR make >$DN 2>&1 ||{ echo Installing/ Installiere 'make' ....; id su >$DN 2>&1 && { su -c "$IPR make;";true;} || sudo $IPR make; grep -q make $AUNF||printf "${UPR}make\necho \"${UPR}make\"\n">>$AUNF; }
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
