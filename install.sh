#!/bin/sh
{ rpm -q make >/dev/null 2>&1 || dpkg -s make >/dev/null 2>&1;} || sudo zypper -n --gpg-auto-import-keys in make || { which apt-get && sudo apt-get --assume-yes install make ;} || { which dnf && sudo dnf -y install make; } || { which yum && sudo yum -y install make; } && make && make install

