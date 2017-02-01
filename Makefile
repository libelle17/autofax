# kompiliert alle *.cpp-Dateien im aktuellen Verzeichnis
# nach "touch entwickeln" wird eine Datei 'version' erstellt, deren Inhalt, eine Versionsnummer, bei jedem Kompiliervorgang um 0.0001 erhoeht wird
# und die in die man_de und man_en-Datei eingebaut wird sowie ueber
#  const double& version=
#  #include version
#  ;
# auch in den c(++)-Quellcode eingebaut werden kann

# Aufrufvarianten:
# "mitpg=1 make <..>" => es wird mit/fuer postgres kompiliert und gelinkt, die Praeprozessordirektive "mitpostgres" wird dem Compiler uebergeben
# "make glei" => der Compiler wird vorher nicht ueberprueft
# "make opt" => optimiere mit -O; kompiliere alles neu
# "make opt2" => optimiere mit -O2; kompiliere alles neu
# "make opt3" => optimiere mit -O3; kompiliere alles neu
# "make opts" => optimiere mit -Os, nach Groesse; kompiliere alles neu
# "make optfast" => optimiere mit -Ofast, nach Ausfuerungsgeschwindigkeit; kompiliere alles neu
# "make optg" => optimiere mit -Og, zum Debuggen; kompiliere alles neu
# "make new" oder "make neu" => kompiliere alles neu
# "make hierclean" => loesche Objekt- und ausfuehrbare Dateien im Kompilierverzeichnis
# "make clean" => loesche Objekt- und ausfuehrbare Dateien einschliesslich installierter Version
# "make altc" => kompiliere mit -std=gnu++11
# "make anzeig" => zeige Informationen zu Programm, Quelldateien und Compiler an
# "make install => installiere die erstellte Datei in den kuerzesten Pfad aus $PATH, der '/usr/' enthaelt,
#                  installiert man-Seiten aus man_de und man_en, ferner *.html-Dateien und eine README.md-Datei fuer den git-Server
# "make git => aktualisiert die Datei auf dem zugeordneten git-Server

ICH := $(firstword $(MAKEFILE_LIST))
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:.cpp=.o)
CFLAGSr=-c -Wall `mysql_config --cflags`
LDFLAGSr=`mysql_config --libs` -ltiff
ifdef mitpg
 CFLAGS=$(CFLAGSr) -I/usr/include/pgsql -Dmitpostgres
 LDFLAGS=$(LDFLAGSr) -lpq
else
 CFLAGS=$(CFLAGSr)
 LDFLAGS=$(LDFLAGSr)
endif
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
 CC:=$(CCName)
 CFLAGS:=$(CFLAGS) -std=gnu++11
else
 CCName=g++-6
# CC=sudo $(CCName)
 CC:=$(CCName)
endif
OR:= >/dev/null 2>&1
pgroff:=groff groff-base
dev:=devel
libmc:=libmysqlclient
ifeq ($(shell which rpm$(OR);echo $$?),0)
 schau:=rpm -q
 ifeq ($(shell which zypper$(OR);echo $$?),0)
  pgroff:=groff
  IPR:=sudo zypper -n --gpg-auto-import-keys in # -n = --non-interactive
  IP_R:=sudo zypper --gpg-auto-import-keys in
  UP_R:=sudo zypper rm -u # -u = --clean-deps
  # UPR:=for f in $$(rpm -q --configfiles $$PACK); do sudo rm -f $$f; done; sudo zypper rm -u $$PACK; // Loeschen der Konfdateien verhindert Deinst
  REPOS:=sudo zypper lr|grep 'g++\|devel_gcc'$(OR)||sudo zypper ar http://download.opensuse.org/repositories/devel:/gcc/`cat /etc/*-release | grep ^NAME= | cut -d'"' -f2 | sed 's/ /_/'`_`cat /etc/*-release | grep ^VERSION_ID= | cut -d'"' -f2`/devel:gcc.repo;
  urepo:=sudo zypper lr|grep \"g++\\|devel_gcc\"$(OR) && sudo zypper rr devel_gcc;
  COMP:=gcc gcc-c++ $(CCInst)
 else
  COMP:=make automake gcc-c++ kernel-devel
  libmc:=mysql
  ifeq ($(shell which dnf$(OR);echo $$?),0)
   IPR:=sudo dnf -y install 
   IP_R:=sudo dnf install 
   UP_R:=sudo dnf remove
  else ifeq ($(shell which yum$(OR);echo $$?),0)
   IPR:=sudo yum -y install 
   IP_R:=sudo yum install 
   UP_R:=sudo yum remove
  endif
 endif
 UPR:=$(UP_R)
else ifeq ($(shell which apt-get$(OR);echo $$?),0)
 schau:=dpkg -s
 IPR:=sudo apt-get -y --force-yes install 
 IP_R:=sudo apt-get --force-yes install 
 UP_R:=sudo apt-get autoremove
 UPR:=sudo apt-get purge --auto-remove
 COMP:=build-essential linux-headers-`uname -r`
 dev:=dev
endif
libmcd:=$(libmc)-$(dev)
pgd:=postgresql-$(dev)
slc:=sudo /sbin/ldconfig
UN:=uninstall.sh
GROFFCHECK:=$(schau) $(pgroff)$(OR)||{ $(IPR) $(pgroff);printf '$(UPR) $(pgroff)\n'>>$(UN);};true

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

.PHONY: alles
alles: anzeig weiter

.PHONY: glei
glei: anzeig $(EXEC) README.md fertig

.PHONY: opt
opt: CFLAGS += -O
opt: neu

.PHONY: opt2
opt2: CFLAGS+= -O2
opt2: neu

.PHONY: opt3
opt3: CFLAGS+= -O3
opt3: neu

.PHONY: optfast
optfast: CFLAGS+= -Ofast
optfast: neu

.PHONY: optc
opts: CFLAGS+= -Os
opts: neu

.PHONY: optg
optg: CFLAGS+= -Og
optg: neu

.PHONY: altc
altc: CFLAGS+= -std=gnu++11
altc: CCInst=gcc-c++
altc: CCName=g++
altc: opts

.PHONY: neu
new: neu
neu: anzeig hierclean weiter

.PHONY: weiter
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
#	@git config --global user.name "Gerald Schade"
#	@git config --global user.email "gerald.schade@gmx.de"
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
	-@test -f version || echo 0.1>version; if test -f entwickeln; then awk "BEGIN {print `cat version`+0.00001}">version; else echo " Datei 'entwickeln' fehlt, lasse die Version gleich"; fi;
	-@printf " verlinke %s zu %b%s%b ..." "$(OBJ)" $(blau) "$@" $(reset)
	-@df --output=ipcent / |tail -n1|grep - && sudo killall postdrop; true
ifneq ("$(wildcard $(CURDIR)/man_en)","")
	-@$$(sed -i "s/\(Version \)[^\"]*/\1$$(cat version)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$(date +'%d.%m.%y')/" man_en)
endif
ifneq ("$(wildcard $(CURDIR)/man_de)","")
	-@$$(sed -i "s/\(Version \)[^\"]*/\1$$(cat version)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$(date +'%d.%m.%y')/" man_de)
endif
	-@printf " (Version: %b%s%s%b\n " $(blau) "$$(cat version)" ")" $(reset)
	$(CC) $^ -o $@ $(LDFLAGS)
	-@for datei in .d/*.Td; do mv -f $${datei} $${datei%.Td}.d; done
	$(shell touch *.o $${EXEC})

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	@printf " kompiliere %b%s%b: " $(blau) "$<" $(reset)
	-@if ! test -f instvz; then printf \"$$(pwd)\">instvz; fi;
	-$(CC) $(DEPFLAGS) $(CFLAGS) -c $< 2>> fehler.txt
	-@sed -i 's/version //g' $(DEPDIR)/*.Td
	-@if test -s fehler.txt; then vi +0/error fehler.txt; else rm fehler.txt; fi;
#	-@$(shell $(POSTCOMPILE))
	@if test -s fehler.txt; then false; fi;

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

.PHONY: compiler
compiler:
	@printf " Untersuche Compiler ...\r"
#	@printf " CCName: %b%s%b                  \n" $(blau) "${CCName}" $(reset)
#	@printf " CCInst: %b%s%b\n" $(blau) "$(CCInst)" $(reset)
	@which $(CCName)$(OR)||{ $(REPOS)$(IP_R) $(COMP);printf '$(UPR) $(COMP);$(urepo)\n'>>$(UN);};
	@if { $(slc);! $(slc) -p|grep -q "libmysqlclient.so ";}||! test -f /usr/include/mysql/mysql.h;then $(IPR) $(libmcd);printf '$(UPR) $(libmcd)\n'>>$(UN);fi
	@[ -z $$mitpg ]||$(schau) $(pgd)$(OR)||{ $(IPR) $(pgd);printf '$(UPR) $(pgd)\n'>>$(UN);$(slc);};
	@test -f /usr/include/tiff.h||{ $(IPR) libtiff-$(dev);printf '$(UPR) libtiff-$(dev)\n'>>$(UN);}
# ggf. Korrektur eines Fehlers in libtiff 4.0.7, notwendig fuer hylafax+
# 17.1.17 in Programm verlagert
#	-@NACHWEIS=/usr/lib64/sclibtiff;! test -f /usr/include/tiff.h ||! test -f $$NACHWEIS &&{ \
	$(schau) cmake||$(IPR) cmake;true && \
	P=tiff_copy; T=$$P.tar.gz; Z=tiff-4.0.7; \
	wget https://github.com/libelle17/$$P/archive/master.tar.gz -O $$T && \
	tar xpvf $$T && mv $${P}-master $$Z && cd $$Z && \
	rm -f CMakeCache.txt && \
	sed -i.bak s'/uint16 Param;/uint32 Param;/' libtiff/tif_fax3.h && \
	cmake -DCMAKE_INSTALL_PREFIX=/usr -DLIBTIFF_ALPHA_VERSION=1 . && \
	make && \
	sudo make install && \
	sudo touch $$NACHWEIS;};true

ifneq ("$(wildcard $(CURDIR)/man_de)","")
ifneq ("$(wildcard $(CURDIR)/man_en)","")
README.md: ${MANPEH} ${MANPDH} 
	-@rm -f README.md
	-@echo "<h3>Manual: 1) <a href=\"#english_E\">english</a>, 2) <a href=\"#deutsch_D\">deutsch (unten anschließend)</a></h3>" > README.md
	-@sed -n '20,$$p' man_en.html >> README.md 
	-@sed -n '20,$$p' man_de.html >> README.md 
	@printf " %b%s%b neu aus %b%s%b und %b%s%b erstellt\n" $(blau) "README.md" $(reset) $(blau) "man_en" $(reset) $(blau) "man_de" $(reset)

.PHONY: install
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

.PHONY: fertig
fertig:
	@printf " Fertig mit %s, nachher:\n" "$(ICH)"
	@printf " '%b%s%b'\n" $(blau) "$(shell ls -l --time-style=+' %d.%m.%Y %H:%M:%S' --color=always $(EXEC))" $(reset) 

.PHONY: hierclean
hierclean: 
	@printf " Bereinige ...\r"
	@$(shell rm -f $(EXEC) $(OBJ) .d/* 2>/dev/null)
	@$(shell sudo rm -f ${MANPEH} ${MANPDH} 2>/dev/null)
	@printf " %b%s,%s,%s,%s%b geloescht!\n" $(blau) "$(EXEC)" "$(OBJ)" "$(MANPEH)" "$(MANPDH)" $(reset)

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
.PHONY: clean
clean: hierclean
	@$(shell sudo rm -f $(INSTEXEC) 2>/dev/null)
	@printf " %b%s%b geloescht!\n" $(blau) "$(INSTEXEC)" $(reset) 

.PHONY: uninstall
uninstall:
	-@sh uninstall.sh

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
