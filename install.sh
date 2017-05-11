#!/bin/bash
[ -z "$BASH_SOURCE" ]&&{ bash "$0";}
PROG=autofax;
HOSTER=github.com
SITZV=libelle17
# aPWD=`pwd`
nPWD=${PWD##*/}
# wenn $PROG schon das aktuelle Verzeichnis ist und wenn es dort einige notwendige Dateien gibt, dann nicht mehr neu runterladen ...
[ $nPWD = $PROG -a -f Makefile -a -f $PROG.cpp -a -f configure ]&&{
	. ./configure;
	printf "${blau}Installing/ Installiere $rot$PROG$reset ...\n";
	true;
}||{
# ... sonst moegliche alte Quelldateiverzeichnisse $PROG umbenennen, aktuelle Version neu herunterladen ...
	printf "Downloading/ Lade runter $PROG ...\n"
		cd ~; 
	T=$PROG.tar.gz;
		wget https://$HOSTER/$SITZV/$PROG/archive/master.tar.gz -O "$T" && 
		tar xpvf $T && 
		rm -f $T && {
			VORIGE=$(ls -d ~/${PROG}_* 2>/dev/null| cut -d"_" -f2 | sort -nr);
			for i in $VORIGE; do 
			case $i in ""|*[!0-9]*);; *) 
				j=$((i+1)); 
				echo mv ${PROG}_$i ${PROG}_$j; 
				mv ${PROG}_$i ${PROG}_$j; 
				esac; 
				done; 
				test -e $PROG && mv $PROG ${PROG}_1; 
				mv $PROG-master $PROG &&{
					cd $PROG; 
					. ./configure
						Q=../${PROG}_1/$INSTLOG; test -f $Q && cp -a $Q .||true
						Q=../${PROG}_1/$UNF; test -f $Q && cp -a $Q .||true
				}
		}|| exit;
}
$SPR make >/dev/null ||{ echo GNU make missing/fehlt; exit;}
# ... und dann kompilieren und installieren
make opts &&
sudo make install; erg=$?
[ $erg = 0 ] && farbe=$blau || farbe=$rot;
printf "Result code/ Ergebniscode: ${farbe}$erg${reset}\n"
