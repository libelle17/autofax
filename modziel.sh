#!/bin/bash
Start=1;
[ $# -ne 1 ]&&{ Start=0;true;}||[ ! -d $1 ]&& Start=0;
if [ $Start = 0 ]; then
 echo Kopiert Dateien eines github-Repositorys abzüglich Kommentaren ins Reine
 echo Synatax: $0 \<zielverzeichnis\>
 exit 1
fi
for D in $(find . -maxdepth 1 -name "*.cpp" -or -name "*.h"); do
# loesche alles zwischen /*// und */ (suche solche Abschnitte, loesche sonst leere erste und letzte Zeilen daraus, loesche Zwischenzeilen daraus, loesche Text vor und nach den Grenzen), loesche Zeilen mit //// am Anfang, loesche alles hinter ////
 sed '/\/\*\/\//,/\*\//{/^[[:space:]]*\/\*\/\//d;/[^*]*\*\/[[:space:]]*$/d;/\/\*\/\//!{/\*\//!d};s/\/\*\/\/.*//;s/[^*]*\*\///};/^\/\/\/\/.*/d;s/\/\/\/\/.*//' $D>$1/$D
done
for D in .exrc Makefile.roh configure install.sh man_?? versdt viall modziel.sh; do
 [ -f $D ]&& sed '/^#\/\/.*/d;s/#\/\/.*//g' $D>$1/$D;
done
