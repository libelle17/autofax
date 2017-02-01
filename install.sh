#!/bin/sh
P=autofax
HOSTER=github.com
ACC=libelle17
rot="\033[1;31m"
blau="\033[1;34m"
reset="\033[0m"
aPWD=`pwd`
nPWD=${PWD##*/}
IPR="nix"
UPR="nix"
SPR="nix"
UN="uninstall.sh"

# Installationsprogramm ermitteln
getIPR() {
	{ which zypper  >/dev/null 2>&1 &&{ IPR="zypper -n --gpg-auto-import-keys in ";UPR="sudo zypper rm -u ";} }||
	{ which apt-get >/dev/null 2>&1 &&{ IPR="apt-get --assume-yes install ";UPR="sudo apt-get purge --auto-remove ";} }||
	{ which dnf     >/dev/null 2>&1 &&{ IPR="dnf -y install ";UPR="sudo dnf remove ";} }||
	{ which yum     >/dev/null 2>&1 &&{ IPR="yum -y install ";UPR="sudo yum remove ";} }
	{ which rpm >/dev/null 2>&1 && SPR="rpm -q ";}||
	{ which dpkg >/dev/null 2>&1 && SPR="dpkg -s ";}
}

# Gruppen, deren Mitglieder sudo aufrufen koennen; fuer Debian muss zuerst 'sudo' genannt werden, weil eine Zuordnung zu 'root' nichts hilft (s.u. tail)
SUG="admin\|root\|sudo\|wheel\|ntadmin";

# hier geht's los
getIPR;
# falls der Benutzer 'sudo' fehlt oder der aktuelle Benutzer ihn nicht aufrufen darf, weil er nicht Mitglied einer Administratorgruppe ist ...
{ which sudo >/dev/null && id -Gzn $USER|grep -qw "$SUG";}||{ 
	printf "Must allow '$blau$USER$reset' to call '${blau}sudo$reset'. Please enter ${blau}root$reset's password if asked:\n"
	printf "Muss '$blau$USER$reset' den Aufruf von '${blau}sudo$reset' ermoeglichen. Bitte geben Sie bei der Frage das Passwort von '${blau}root$reset' ein:\n";
	su -c "$IPR sudo; printf '$(UPR) sudo\n'>>$(UN); usermod -aG $(cut -d: -f1 /etc/group|grep -w "$SUG"|tail -n1) "$USER";"||exit
	printf "Please log out and in again, change to the directory '$blau$PWD$reset' and then call '${blau}sh $0$reset' again!\n"
	printf "Bitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach '$blau$PWD$reset' und rufen Sie '${blau}sh $0$reset' dann nochmal auf!\n";
	exit;
}
# falls make fehlt, dann installieren ...
$SPR make >/dev/null 2>&1 ||{
	echo Installing/ Installiere 'make' ....;
  id su >/dev/null 2>&1 && { su -c "$IPR make;";true;} || sudo $IPR make;
	printf '$(UPR) make\n'>>$(UN);
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
			VORIGE=$(ls -d ~/${P}_* 2>/dev/null | cut -d"_" -f2 | sort -nr);
			for i in $VORIGE; do 
			case $i in ""|*[!0-9]*);; *) 
				j=$((i+1)); 
				echo mv ${P}_$i ${P}_$j; 
				mv ${P}_$i ${P}_$j; 
				esac; 
				done; 
				test -e $P && mv $P ${P}_1; 
				mv $P-master $P && 
					cd $P;
		}|| exit;
}
# ... und dann kompilieren und installieren
make &&
sudo make install; erg=$?;
[ $erg = 0 ] && farbe=$blau || farbe=$rot;
printf "Result code/ Ergebniscode: ${farbe}$erg${reset}\n"

