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
SPR="nix"

getIPR() {
	{ which zypper  >/dev/null 2>&1 && IPR="zypper -n --gpg-auto-import-keys in ";}||
	{ which apt-get >/dev/null 2>&1 && IPR="apt-get --assume-yes install ";}||
	{ which dnf     >/dev/null 2>&1 && IPR="dnf -y install ";}||
	{ which yum     >/dev/null 2>&1 && IPR="yum -y install ";}
	{ which rpm >/dev/null 2>&1 && SPR="rpm -q ";}||
	{ which dpkg >/dev/null 2>&1 && SPR="dpkg -s ";}
}

SUG="root\| sudo\| wheel\| admin";
getIPR;
{ which sudo >/dev/null && id -Gn $USER|grep -qw "$SUG";}||{ 
	echo -e "Must allow '$USER' to call 'sudo'. Please enter root's password if asked:\nMuss '$USER' den Aufruf von 'sudo' ermoeglichen. Bitte geben Sie bei der Frage das Passwort von 'root' ein:";
	su -c "$IPR sudo; usermod -aG $(cut -d: -f1 /etc/group|grep "$SUG"|head -n 1) "$USER";"||exit
	echo -e "Please log out and in again, change to the directory ${blau}'$PWD'${reset} and then call this script again!\nBitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach ${blau}'$PWD'${reset} und rufen Sie das Script dann nochmal auf!";
	exit;
}
$SPR make >/dev/null 2>&1 ||{
	echo Installing/ Installiere 'make' ....;
	su -c "$IPR make;"
}
$SPR make >/dev/null || exit
# wenn schon im Verzeichnis $P und wenn es dort einige notwendige Dateien gibt, dann nur kompilieren und installieren
[ $nPWD = $P -a -f Makefile -a -f $P.cpp ]&&{
	echo -e ${rot} Installing/ Installiere ... ${reset}
	true;
}||{
	echo -e ${rot} Downloading/ Lade runter ... ${reset}
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
make &&
sudo make install; erg=$?;
[ $erg = 0 ] && farbe=$blau || farbe=$rot;
echo -e Result code/ Ergebniscode: ${farbe}$erg${reset}
