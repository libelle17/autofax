
IPR="nix"
UPR="nix"
SPR="nix"
UN="uninstall.sh"
pgroff="groff groff-base"
dev=devel
libmc=libmysqlclient
fed=0
REPOS=
urepo=
CCInst=gcc6-c++

# Installationsprogramm ermitteln
getIPR() {
	{ which zypper  >/dev/null 2>&1 &&{ 
		Z=zypper;g=--gpg-auto-import-keys;IPR="$Z -n $g in ";IP_R="$Z $g in ";UPR="sudo zypper rm -u ";pgroff=groff;
  REPOS="sudo zypper lr|grep 'g++\|devel_gcc'\$(OR)||sudo zypper ar http://download.opensuse.org/repositories/devel:/gcc/\`cat /etc/*-release|grep ^NAME= |cut -d'\"' -f2|sed 's/ /_/'\`_\`cat /etc/*-release|grep ^VERSION_ID= |cut -d'\"' -f2\`/devel:gcc.repo;";
  urepo="sudo zypper lr|grep \\\"g++\\\\\|devel_gcc\\\"\$(OR) && sudo zypper rr devel_gcc;";
  COMP="gcc gcc-c++ \$(CCInst)";
	} }||
	{ which apt-get >/dev/null 2>&1 &&{ IPR="sudo apt-get --assume-yes install ";IP_R=$IPR;
	                                    UPR="sudo apt-get --auto-remove purge ";
																			dev=devel;
																			COMP:="build-essential linux-headers-\`uname -r\`";} }||
	{ which dnf     >/dev/null 2>&1 &&{ fed=1;IPR="sudo dnf -y install ";UPR="sudo dnf remove ";} }||
	{ which yum     >/dev/null 2>&1 &&{ fed=1;IPR="sudo yum -y install ";UPR="sudo yum remove ";} }
	[ $fed = 1 ] &&{ libmc=mysql;COMP="make automake gcc-c++ kernel-devel";IP_R=$IPR;}
	{ which rpm >/dev/null 2>&1 && SPR="rpm -q ";}||
	{ which dpkg >/dev/null 2>&1 && SPR="dpkg -s ";}
}

