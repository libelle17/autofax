#!/bin/sh
{ rpm -q g++ >/dev/null 2>&1 || dpkg -s g++ >/dev/null 2>&1;} || sudo zypper -n --gpg-auto-import-keys in g++ || { which apt-get && sudo apt-get -y --force-yes install g++ ;} || { which dnf && sudo dnf -y install g++; } || { which yum && sudo yum -y install g++; }
{ rpm -q make >/dev/null 2>&1 || dpkg -s make >/dev/null 2>&1;} || sudo zypper -n --gpg-auto-import-keys in make || { which apt-get && sudo apt-get --assume-yes install make ;} || { which dnf && sudo dnf -y install make; } || { which yum && sudo yum -y install make; } && make && make install


