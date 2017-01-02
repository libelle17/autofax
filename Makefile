ICH := $(firstword $(MAKEFILE_LIST))
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:.cpp=.o)
CFLAGS=-c -Wall `mysql_config --cflags` 
LDFLAGS=`mysql_config --libs` -ltiff
PROGRAM=$(shell basename $(CURDIR))
PROGGROSS=`echo $(PROGRAM) | tr a-z A-Z`
#EXPFAD=/usr/local/sbin
EXPFAD := $(shell echo ${PATH} | tr -s ':' '\n' | grep /usr/ | head -n 1)
EXPFAD := $(shell echo ${PATH} | tr -s ':' '\n' | grep /usr/ | awk '{ print length, $$0 }' | sort -n -s | cut -d" " -f2- | head -n1)
EXEC=$(PROGRAM)
INSTEXEC=$(EXPFAD)/$(EXEC)
CCInst=gcc6-c++
ifneq ($(shell g++-6 --version >/dev/null 2>&1),0)
 CCName=g++
# CC=sudo $(CCName)
 CC=$(CCName)
 $(eval CFLAGS=$(CFLAGS) -std=gnu++11)
else
 CCName=g++-6
# CC=sudo $(CCName)
 CC=$(CCName)
endif
GROFFCHECK={ rpm -q groff >/dev/null 2>&1 || dpkg -s groff groff-base >/dev/null 2>&1;} ||{ which zypper >/dev/null 2>&1 &&{ sudo zypper -n --gpg-auto-import-keys in groff 2>/dev/null;true;} ||{ which apt-get >/dev/null 2>&1 &&{ sudo apt-get -y --force-yes install groff groff-base;true;} ||{ which dnf >/dev/null 2>&1 &&{ sudo dnf -y install groff groff-base;true;} ||{ which yum >/dev/null 2>&1 && sudo yum -y install groff groff-base;true;} } } }

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

# POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d 2>/dev/null

MANP=/usr/share/man
MANPD=${MANP}/de/man1/${PROGRAM}.1.gz
MANPE=${MANP}/man1/${PROGRAM}.1.gz
MANPDH=$(CURDIR)/man_de.html
MANPEH=$(CURDIR)/man_en.html
blau="\033[0;34;1;47m"
blau="\033[1;34m"
gruen="\033[0;32m"
rot="\033[1;31m"
reset="\033[0m"

alles: anzeig weiter

glei: anzeig $(EXEC) README.md fertig

opt: CFLAGS += -O
opt: neu

opt2: CFLAGS+= -O2
opt2: neu

opt3: CFLAGS+= -O3
opt3: neu

optfast: CFLAGS+= -Ofast
optfast: neu

opts: CFLAGS+= -Os
opts: neu

optg: CFLAGS+= -Og
optg: neu

altc: CFLAGS+= -std=gnu++11
altc: CCInst=gcc-c++
altc: CCName=g++
altc: opts

new: neu
neu: anzeig clean weiter

weiter: compiler $(EXEC) README.md fertig

# davor:
# git clone ssh://git@github.com/<user>/<reponame>.git
# git clone ssh://git@github.com/libelle17/autofax.git # https://www.github.com/libelle17/autofax
# ssh-keygen -t rsa -b 4096 -f ~/.ssh/id_rsa_git -C "gerald.schade@gmx.de@github.com"
# eval "$(ssh-agent -s)"
# ssh-add ~/.ssh/id_rsa_git
# xclip -sel clip < ~/.ssh/id_rsa_git.pub
# auf http://github.com -> view profile and more -> settings -> SSH and GPG keys -> New SSH key <Titel> <key> einfuegen
git:
	@git config --global user.name "Gerald Schade"
	@git config --global user.email "gerald.schade@gmx.de"
	@git config --global push.default simple
	@git add -u
	@git commit -m "Version $$(cat version)"
	@git push

anzeig:
# 'echo -e' geht nicht z.B. in ubuntu
	@printf " %bGNU Make%b, Zieldatei: %b%s%b, vorher:                                      \n" $(gruen) $(reset) $(rot) "$(EXEC)" $(reset)
	@printf " '%b%s%b'\n" $(blau) "$(shell ls -l --time-style=+' %d.%m.%Y %H:%M:%S' --color=always $(EXEC) 2>/dev/null)" $(reset) 
	@printf " Quelldateien: %b%s%b\n" $(blau) "$(SRCS)" $(reset) 
	@printf " Compiler: %b%s%b, installiert als: %b%s%b; Zielpfad fuer '%bmake install%b': %b%s%b\n" $(blau) "$(CCName)" $(reset) $(blau) "$(CCInst)" $(reset) $(blau) $(reset) $(blau) "'$(EXPFAD)'" $(reset)
	-@$(shell rm fehler.txt 2>/dev/null)

$(EXEC): $(OBJ)
	-@test -f version || echo 0.1>version; test -f entwickeln && awk "BEGIN {print `cat version`+0.00001}">version
	-@printf " verlinke %s zu %b%s%b ..." "$(OBJ)" $(blau) "$@" $(reset)
	-@df --output=ipcent / |tail -n1|grep - && sudo killall postdrop; true
ifneq ("$(wildcard $(CURDIR)/man_en)","")
	-@$$(sed -i "s/\(Version \)[^\"]*/\1$$(cat version)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$(date +'%d.%m.%y')/" man_en)
endif
ifneq ("$(wildcard $(CURDIR)/man_de)","")
	-@$$(sed -i "s/\(Version \)[^\"]*/\1$$(cat version)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$(date +'%d.%m.%y')/" man_de)
endif
	-@printf " (Version: %b%s%s%b\n " $(blau) "$$(cat version)" ")" $(reset)
	-$(CC) $^ -o $@ $(LDFLAGS)
	$(shell for datei in .d/*.Td; do mv -f $${datei} $${datei%.Td}.d; done)
	$(shell touch *.o $${EXEC})

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	@printf " kompiliere %b%s%b: " $(blau) "$<" $(reset)
	-$(CC) $(DEPFLAGS) $(CFLAGS) -c $< 2>> fehler.txt
	-@sed -i 's/version //g' $(DEPDIR)/*.Td
	-@if test -s fehler.txt; then vi +0/error fehler.txt; else rm fehler.txt; fi;
#	-@$(shell $(POSTCOMPILE))
	@if test -s fehler.txt; then false; fi;

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

compiler:
	@printf " Untersuche Compiler ...\r"
#	@printf " CCName: %b%s%b                  \n" $(blau) "${CCName}" $(reset)
#	@printf " CCInst: %b%s%b\n" $(blau) "$(CCInst)" $(reset)
	-@which $(CCName) >/dev/null 2>&1 || { which zypper >/dev/null 2>&1 && { sudo zypper lr | grep 'g++\|devel_gcc' || sudo zypper ar http://download.opensuse.org/repositories/devel:/gcc/`cat /etc/*-release | grep ^NAME= | cut -d'"' -f2 | sed 's/ /_/'`_`cat /etc/*-release | grep ^VERSION_ID= | cut -d'"' -f2`/devel:gcc.repo; sudo zypper --gpg-auto-import-keys in gcc gcc-c++ $(CCInst);true;} || { which apt-get >/dev/null 2>&1 && { sudo apt-get -y --force-yes install build-essential linux-headers-`uname -r`;true;} || { which dnf >/dev/null 2>&1 && { sudo dnf -y install make automake gcc-c++ kernel-devel;true;} || { which yum >/dev/null 2>&1 && yum install -y make automake gcc-c++ kernel-devel;true;} } } }
	-@if { sudo /sbin/ldconfig; ! sudo /sbin/ldconfig -p | grep -q "libmysqlclient.so ";} || ! test -f /usr/include/mysql/mysql.h; then { which zypper >/dev/null 2>&1 && { sudo zypper -n --gpg-auto-import-keys in libmysqlclient-devel;true;} || { which apt-get >/dev/null 2>&1 && { sudo apt-get -y --force-yes --reinstall install libmysqlclient-dev;true;} || { which dnf >/dev/null 2>&1 && { sudo dnf -y install mysql-devel;true;} || { which yum >/dev/null 2>&1 && sudo yum install -y mysql-devel;true;} } }; sudo /sbin/ldconfig;}; fi
	-@test -f /usr/include/tiff.h || { which zypper >/dev/null 2>&1 && { sudo zypper -n --gpg-auto-import-keys in libtiff-devel;true;} || { which apt-get >/dev/null 2>&1 && { sudo apt-get -y --force-yes install libtiff-dev;true;} || { which dnf >/dev/null 2>&1 && { sudo dnf -y install libtiff-devel;true;} || { which yum >/dev/null 2>&1 && sudo yum install -y libtiff-devel;true;} } } }

.PHONY: install
ifneq ("$(wildcard $(CURDIR)/man_de)","")
ifneq ("$(wildcard $(CURDIR)/man_en)","")
README.md: ${MANPEH} ${MANPDH} 
	-@rm -f README.md
	-@echo "<h3>Manual: 1) <a href=\"#english_E\">english</a>, 2) <a href=\"#deutsch_D\">deutsch (unten anschließend)</a></h3>" > README.md
	-@sed -n '20,$$p' man_en.html >> README.md 
	-@sed -n '20,$$p' man_de.html >> README.md 
	@printf " %b%s%b neu aus %b%s%b und %b%s%b erstellt\n" $(blau) "README.md" $(reset) $(blau) "man_en" $(reset) $(blau) "man_de" $(reset)
install: $(INSTEXEC) ${MANPE} ${MANPD} 
else
README.md: ${MANPDH}
	-@rm -f README.md
	-@sed -n '20,$$p' man_de.html >> README.md 
	@printf " %b%s%b neu aus %b%s%b erstellt\n" $(blau) "README.md" $(reset) $(blau) "man_de" $(reset)
install: $(INSTEXEC) ${MANPD}
endif
else
ifneq ("$(wildcard $(CURDIR)/man_en)","")
README.md: ${MANPEH}
	-@rm -f README.md
	-@sed -n '20,$$p' man_en.html >> README.md 
	@printf " %b%s%b neu aus %b%s%b erstellt\n" $(blau) "README.md" $(reset) $(blau) "man_en" $(reset)
install: $(INSTEXEC) ${MANPE} 
else
README.md: 
install: $(INSTEXEC)
endif
endif

$(INSTEXEC): $(EXEC)
	@printf " Kopiere Programmdatei: %b%s%b -> %b%s%b\n" $(blau) "$(EXEC)" $(reset) $(blau) "$(INSTEXEC)" $(reset)
	-@sudo killall $(EXEC) 2>/dev/null; sudo killall -9 $(EXEC) 2>/dev/null; sudo cp -p "$(EXEC)" "$(INSTEXEC)"

ifneq ("$(wildcard $(CURDIR)/man_en)","")
${MANPE}: ${CURDIR}/man_en
	@printf " "
	-sudo mkdir -p $(MANP)/man1
	@printf " "
	-sudo gzip -c $(CURDIR)/man_en >${PROGRAM}.1.gz
	@printf " "
	-sudo mv ${PROGRAM}.1.gz ${MANPE}
${MANPEH}: $(CURDIR)/man_en 
	-@$(GROFFCHECK)
	-@rm -f man_en.html
	-@sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g;/\.SH FUNCTIONALITY/,/^\.SH/ {s/\.br/.LP\n\.HP 3/g};/\.SH IMPLICATIONS/,/^\.SH/ {s/\.br/\.LP\n\.HP 3/g}' man_en | groff -mandoc -Thtml | sed "s/&amp;/\&/g;s@<h1 align=\"center\">man@<h1 align=\"center\">$(PROGGROSS) (Version $$(cat version)) - english<a name=\"english\"></a>@g;s/\(<a \(href\|name\)=\"[^\"]*\)/\1_E/g" > man_en.html
	@printf " %b%s%b neu aus %b%s%b erstellt\n" $(blau) "man_en.html" $(reset) $(blau) "man_en" $(reset)
endif

ifneq ("$(wildcard $(CURDIR)/man_de)","")
${MANPD}: ${CURDIR}/man_de 
	@printf " "
	-sudo mkdir -p $(MANP)/de/man1
	@printf " "
	-sudo gzip -c $(CURDIR)/man_de >${PROGRAM}.1.gz
	@printf " "
	-sudo mv ${PROGRAM}.1.gz ${MANPD}
${MANPDH}: $(CURDIR)/man_de 
	-@$(GROFFCHECK)
	-@rm -f man_de.html
	-@sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g;/\.SH FUNKTIONSWEISE/,/^\.SH/ {s/\.br/.LP\n\.HP 3/g};/\.SH AUSWIRKUNGEN/,/^\.SH/ {s/\.br/\.LP\n\.HP 3/g}' man_de | groff -mandoc -Thtml | sed "s/&amp;/\&/g;s@<h1 align=\"center\">man@<h1 align=\"center\">$(PROGGROSS) (Version $$(cat version)) - deutsch<a name=\"deutsch\"></a>@g;s/\(<a \(href\|name\)=\"[^\"]*\)/\1_D/g" > man_de.html
#	-@rm -f README.md
	@printf " %b%s%b neu aus %b%s%b erstellt\n" $(blau) "man_de.html" $(reset) $(blau) "man_de" $(reset)
endif

fertig:
	@printf " Fertig mit %s, nachher:\n" "$(ICH)"
	@printf " '%b%s%b'\n" $(blau) "$(shell ls -l --time-style=+' %d.%m.%Y %H:%M:%S' --color=always $(EXEC))" $(reset) 

.PHONY: clean
clean: 
	@printf " Bereinige ...\r"
	@$(shell rm -f $(EXEC) $(OBJ) .d/* 2>/dev/null)
	@$(shell sudo rm -f $(INSTEXEC) 2>/dev/null)
	@$(shell sudo rm -f ${MANPEH} ${MANPDH} 2>/dev/null)
	@printf " %b%s,%s,%s,%s,%s%b geloescht!\n" $(blau) "$(EXEC)" "$(OBJ)" "$(INSTEXEC)" "$(MANPEH)" "$(MANPDH)" $(reset)

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
