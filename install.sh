#!/bin/sh
P=autofax;
# aPWD=`pwd`
nPWD=${PWD##*/}
# wenn $P schon das aktuelle Verzeichnis ist und wenn es dort einige notwendige Dateien gibt, dann nicht mehr neu runterladen ...
[ $nPWD = $P -a -f Makefile -a -f $P.cpp -a -f configure ]&&{
	. ./configure;
	printf "${blau}Installing/ Installiere ${rot}${P}$reset ...\n";
	true;
}||{
# ... sonst moegliche alte Quelldateiverzeichnisse $P umbenennen, aktuelle Version neu herunterladen ...
	printf "Downloading/ Lade runter ${P} ...\n"
	cd ~; 
	T=$P.tar.gz;
	HOSTER=github.com
	ACC=libelle17
	wget https://$HOSTER/$ACC/$P/archive/master.tar.gz -O "$T" && 
		tar xpvf $T && 
		rm -f $T && {
			VORIGE=$(ls -d ~/${P}_* 2>/dev/null| cut -d"_" -f2 | sort -nr);
			for i in $VORIGE; do 
			case $i in ""|*[!0-9]*);; *) 
				j=$((i+1)); 
				echo mv ${P}_$i ${P}_$j; 
				mv ${P}_$i ${P}_$j; 
				esac; 
				done; 
				test -e $P && mv $P ${P}_1; 
				mv $P-master $P &&{
					cd $P; 
				  . ./configure
				  Q=../${P}_1/$UNF; test -f $Q && cp -ai $Q .||true
				}
		}|| exit;
}
$SPR make >/dev/null ||{ echo GNU make missing/fehlt; exit;}
# ... und dann kompilieren und installieren
make opts &&
sudo make install; erg=$?
[ $erg = 0 ] && farbe=$blau || farbe=$rot;
printf "Result code/ Ergebniscode: ${farbe}$erg${reset}\n"
