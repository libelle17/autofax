#!/bin/bash
Start=1;
[ $# -ne 1 ]&&{ Start=0;true;}||[ ! -d $1 ]&& Start=0;
if [ $Start = 0 ]; then
 echo Kopiert Dateien eines github-Repositorys abzüglich Kommentaren ins Reine
 echo Synatax: $0 \<zielverzeichnis\>
 echo Das Zielverzeichnis muss vorher schon da sein.
 exit 1
fi
. ./configure
for D in $(find . -maxdepth 1 -name "*.cpp" -or -name "*.h"); do
# loesche alles zwischen /*// und */ (loesche einzeilige Muster(-zeilen), suche solche Abschnitte, loesche sonst leere erste und letzte Zeilen daraus, loesche Zwischenzeilen daraus, loesche Text vor und nach den Grenzen), loesche Zeilen mit //// am Anfang, loesche alles hinter ////
 sed '/^[[:space:]]*\/\*\/\/.*\*\/[[:space:]]*$/d;s_/\*//[^*]*\*/__g;/\/\*\/\//,/\*\//{/^[[:space:]]*\/\*\/\//d;/\*\/[[:space:]]*$/d;/\/\*\/\//!{/\*\//!d};s_/\*//.*__;s_.*\*/__};/^[[:space:]]*\/\/\/\/.*/d;s_////.*__;s/\r$//' $D>$1/$D;
 ((DAT++));
 chmod --reference=$D $1/$D;
 chown --reference=$D $1/$D;
done;
for D in .exrc Makefile install.sh man_?? versdt viall modziel.sh configure; do
 [ -f $D ]&&{ sed '/^#\/\/.*/d;s_#//.*__g' $D>$1/$D;((DAT+=1)); printf "$blau$D$reset nach $blau$1/$reset kopiert\n"; };
 chmod --reference=$D $1/$D;
 chown --reference=$D $1/$D;
 [ "$D" = "Makefile" ]&&{ ROH=$D.roh; mv $1/$D $1/$ROH; printf "$blau$1/$D$reset in $blau$1/$ROH/$reset umbenannt\n"; };
done;
printf "Insgesamt $blau$DAT$reset Dateien kopiert\n"
