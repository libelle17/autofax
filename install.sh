#!/bin/sh
PWD=`pwd`
TU="{ rpm -q make >/dev/null 2>&1 || dpkg -s make >/dev/null 2>&1;} || sudo zypper -n --gpg-auto-import-keys in make || { which apt-get && sudo apt-get --assume-yes install make ;} || { which dnf && sudo dnf -y install make; } || { which yum && sudo yum -y install make; } && cd '$PWD' && make && make install"
{ which sudo >/dev/null && id -Gn $USER|grep -qw sudo; } && sh -c "$TU" || { echo "Bitte geben Sie bei der Frage das Passwort von 'root' ein:";su -c "apt-get -y install sudo;usermod -aG sudo $USER;"; echo "Bitte loggen Sie sich jetzt aus und nochmal ein, wechseln Sie nach '$PWD' und rufen Sie das Script dann nochmal auf";}


