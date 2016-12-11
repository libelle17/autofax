#!/bin/sh
rot="\033[1;31m"
reset="\033[0m"
P=autofax
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

fuellTU() {
TU="{ rpm -q make >/dev/null 2>&1 ||dpkg -s make >/dev/null 2>&1;} ||
    { which zypper >/dev/null 2>&1 &&
      { sudo zypper -n --gpg-auto-import-keys in make >/dev/null 2>&1;true;} ||
    { which apt-get >/dev/null 2>&1 &&
      { sudo apt-get --assume-yes install make >/dev/null 2>&1;true;} ||
    { which dnf >/dev/null 2>&1 &&
      { sudo dnf -y install make >/dev/null 2>&1;true;} ||
    { which yum >/dev/null 2>&1 &&
      { sudo yum -y install make >/dev/null 2>&1;true;} } } } } && 
    { [ $nPWD = $P -a -f Makefile ]&& 
      { cd '$aPWD' && make && make install;true;} ||
      { echo $nPWD; echo $P;} ||
      { T=$P.tar.gz; cd ~; wget https://github.com/libelle17/$P/archive/master.tar.gz -O ($T) && tar xpvf $T && rm -f $T && { for i in "$VORIGE"; do j=\"$((i+1))\"; case $i in ""|*[!0-9]*);; *) mv ${P}_$i ${P}_$j; esac; done; test -e $P && mv $P ${P}_1; mv $P-master $P && cd $P; } }"
}
#erg=1; which rpm &&{ rpm -q make >/dev/null 2>&1;erg=$?;true;} || which dpkg &&{ dpkg -s make >/dev/null 2>&1;erg=$?;true;}; (exit $erg)|| 
SUG="root\| sudo\| wheel\| admin";
getIPR;
which sudo >/dev/null && id -Gn $USER|grep -qw "$SUG"||{ 
  echo "Bitte geben Sie bei der Frage das Passwort von 'root' ein:";
  su -c "$IPR sudo; usermod -aG $(cut -d: -f1 /etc/group|grep "$SUG"|head -n 1) "$USER";"; 
  echo "Bitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach '$PWD' und rufen Sie das Script dann nochmal auf";
  exit;
}
$SPR make >/dev/null 2>&1 ||{
 echo Installiere 'make' ....
 su -c "$IPR make;"
}
$SPR make >/dev/null || exit
# wenn schon im Verzeichnis autofax und wenn es dort einige notwendige Dateien gibt, dann nur kompilieren und installieren
[ $nPWD = $P -a -f Makefile -a -f $P.cpp ]&&{
  echo -e ${rot} Installiere ... ${reset}
  make &&
  sudo make install;
  echo Ergebniscode: $?
  true;
}||{
 echo -e ${rot} Runterladen ... ${reset}
 T=$P.tar.gz
 cd ~; 
 wget https://github.com/libelle17/$P/archive/master.tar.gz -O "$T" && 
 tar xpvf $T && 
 rm -f $T && {
	VORIGE=$(ls -d ~/${P}_* 2>/dev/null | cut -d"_" -f2 | sort -nr);
  echo -e Vorige: ${rot}$VORIGE${reset};
	for i in "$VORIGE"; do 
    j=$((i+1)); 
    case $i in ""|*[!0-9]*);; *) mv ${P}_$i ${P}_$j; esac; 
  done; 
  test -e $P && mv $P ${P}_1; 
  mv $P-master $P && 
  cd $P &&
  make &&
  sudo make install;
  echo Ergebniscode: $?
 }
}
echo Hier bin ich noch

