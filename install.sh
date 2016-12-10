#!/bin/sh
PWD=`pwd`
TU="{ rpm -q make >/dev/null 2>&1 ||dpkg -s make >/dev/null 2>&1;} ||{ which zypper >/dev/null 2>&1 &&{ sudo zypper -n --gpg-auto-import-keys in make >/dev/null 2>&1;true;} ||{ which apt-get >/dev/null 2>&1 &&{ sudo apt-get --assume-yes install make >/dev/null 2>&1;true;} ||{ which dnf >/dev/null 2>&1 &&{ sudo dnf -y install make >/dev/null 2>&1;true;} ||{ which yum >/dev/null 2>&1 &&{ sudo yum -y install make;true;} } } } } && cd '$PWD' && make && make install;"
#erg=1; which rpm &&{ rpm -q make >/dev/null 2>&1;erg=$?;true;} || which dpkg &&{ dpkg -s make >/dev/null 2>&1;erg=$?;true;}; (exit $erg)|| 
echo $TU
{ which sudo >/dev/null && id -Gn $USER|grep -qw sudo; } && sh -c "$TU" || { echo "Bitte geben Sie bei der Frage das Passwort von 'root' ein:";su -c "apt-get -y install sudo;usermod -aG sudo $USER;"; echo "Bitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach '$PWD' und rufen Sie das Script dann nochmal auf";}


