ICH := $(firstword $(MAKEFILE_LIST))
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:.cpp=.o)
CFLAGS=-c -Wall `mysql_config --cflags` 
LDFLAGS=`mysql_config --libs` -ltiff
PROGRAM=$(shell basename $(CURDIR))
PROGGROSS=`echo $(PROGRAM) | tr a-z A-Z`
EXPFAD=/usr/local/sbin
EXEC=$(PROGRAM)
INSTEXEC=$(EXPFAD)/$(EXEC)
CINST=gcc6-c++
ifneq ($(shell g++-6 --version >/dev/null 2>&1),0)
 CCName=g++
 CC=sudo $(CCName)
 $(eval CFLAGS=$(CFLAGS) -std=gnu++11)
else
 CCName=g++-6
 CC=sudo $(CCName)
endif

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d 2>/dev/null

MANP=/usr/share/man
MANPD=${MANP}/de/man1/${PROGRAM}.1.gz
MANPE=${MANP}/man1/${PROGRAM}.1.gz
MANPDH=$(CURDIR)/man_de.html
MANPEH=$(CURDIR)/man_en.html


alles: anzeig weiter

glei: anzeig $(EXEC) man fertig

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
altc: CINST=gcc-c++
altc: CCname=g++
altc: opts

neu: anzeig clean weiter

weiter: compiler $(EXEC) man fertig

# davor: xclip -sel clip < ~/.ssh/id_rsa.pub
#      : auf http://github.com -> view profile and more -> settings -> SSH and GPG keys -> New SSH key <Titel> <key> einfuegen
#      : git clone ssh://git@github.com/<user>/<reponame>.git
git:
	git add -u
	git commit -m "Version $$(cat version)"
	git push

anzeig:
	@echo -e " GNU Make, Zieldatei:""\033[1;31m" $(EXEC)"\033[0;30m", vorher:
	@echo -e "\033[0;34m" $(shell ls -l $(EXEC) 2>/dev/null) "\033[0;30m" 
	@echo -e " Quelldateien:""\033[1;31m" $(SRCS)"\033[0;30m" 
	@echo -e " Verwende Compiler: ""\033[1;31m" $(CCName) "\033[0;30m"
	-@$(shell rm fehler.txt 2>/dev/null)

$(EXEC): $(OBJ)
	-@echo $$(if ! test -f version; then echo 0.1>version;fi;awk "BEGIN {print `cat version`+0.00001}")>version
	-@echo -n " verlinke $(OBJ) zu $@ ..."
ifneq ("$(wildcard $(CURDIR)/man_en)","")
	-@$$(sed -i "s/\(Version \)[^\"]*/\1$$(cat version)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$(date +'%d.%m.%y')/" man_en)
endif
ifneq ("$(wildcard $(CURDIR)/man_de)","")
	-@$$(sed -i "s/\(Version \)[^\"]*/\1$$(cat version)/;s/\(\.TH[^\"]*\)\"[^\"]*/\1\"$$(date +'%d.%m.%y')/" man_de)
endif
	-@echo " (Version:" $$(cat version)")"
	-$(CC) $^ -o $@ $(LDFLAGS)

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	@echo -n " kompiliere $< ..."
	-$(CC) $(DEPFLAGS) $(CFLAGS) -c $< 2>> fehler.txt
	-@sudo sed -i 's/version //g' $(DEPDIR)/*.Td
	-@if test -s fehler.txt; then vi +0/error fehler.txt; else rm fehler.txt; fi;
	-@$(shell $(POSTCOMPILE))
	@if test -s fehler.txt; then false; fi;

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

compiler:
	@echo -e "Untersuche Compiler ..."
	@echo -e -n "\r" 
	-@which $(CCname) >/dev/null 2>&1 || { which zypper && sudo zypper -n in $(CINST) || { which apt-get && sudo apt-get --assume-yes install build-essential; } }
	-@sudo /sbin/ldconfig; sudo /sbin/ldconfig -p | grep -q "libmysqlclient.so " || { which zypper && sudo zypper -n in libmysqlclient-devel || { which apt-get && sudo apt-get --assume-yes install libmysqlclient-dev; }; sudo /sbin/ldconfig; }
	-@test -f /usr/include/tiff.h || { which zypper && sudo zypper -n in libtiff-devel || { which apt-get && sudo apt-get --assume-yes install libtiff-dev; } }

ifneq ("$(wildcard $(CURDIR)/man_de)","")
ifneq ("$(wildcard $(CURDIR)/man_en)","")
man: ${MANPDH} ${MANPEH}
install: $(INSTEXEC) ${MANPD} ${MANPE} 
else
man: ${MANPDH}
install: $(INSTEXEC) ${MANPD}
endif
else
ifneq ("$(wildcard $(CURDIR)/man_en)","")
man: ${MANPEH}
install: $(INSTEXEC) ${MANPE} 
else
man: 
install: $(INSTEXEC)
endif
endif

$(INSTEXEC): $(EXEC)
	@echo -e "Kopiere Programmdatei: ""\033[0;34m"$(EXEC)"\033[0;30m" "->" "\033[0;34m"$(INSTEXEC)"\033[0;30m"
	-@sudo killall $(EXEC) 2>/dev/null; sudo killall -9 $(EXEC) 2>/dev/null; sudo cp -p "$(EXEC)" "$(INSTEXEC)"

ifneq ("$(wildcard $(CURDIR)/man_de)","")
${MANPD}: ${CURDIR}/man_de 
	-sudo mkdir -p $(MANP)/de/man1
	-sudo gzip -c $(CURDIR)/man_de >${PROGRAM}.1.gz
	-sudo mv ${PROGRAM}.1.gz ${MANPD}
${MANPDH}: $(CURDIR)/man_de 
	-@{ rpm -q groff >/dev/null 2>&1 || dpkg -s groff groff-base >/dev/null 2>&1;} || sudo zypper -n --gpg-auto-import-keys in groff || { which apt-get && sudo apt-get --assume-yes install groff groff-base;}
	-@rm -f man_de.html
	-@sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g' man_de | groff -mandoc -Thtml | sed "s/&amp;/\&/g;s/<h1 align=\"center\">man/<h1 align=\"center\">$(PROGGROSS) (Version $$(cat version))/g" > man_de.html
	@echo -e "\033[0;34m"   man_de.html"\033[0;30m" neu aus"\033[0;34m" man_de"\033[0;30m" erstellt
endif

ifneq ("$(wildcard $(CURDIR)/man_en)","")
${MANPE}: ${CURDIR}/man_en
	-sudo mkdir -p $(MANP)/man1
	-sudo gzip -c $(CURDIR)/man_en >${PROGRAM}.1.gz
	-sudo mv ${PROGRAM}.1.gz ${MANPE}
${MANPEH}: $(CURDIR)/man_en 
	-@{ rpm -q groff >/dev/null 2>&1 || dpkg -s groff groff-base >/dev/null 2>&1;} || sudo zypper -n --gpg-auto-import-keys in groff || { which apt-get && sudo apt-get --assume-yes install groff groff-base;}
	-@rm -f man_en.html
	-@sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g' man_en | groff -mandoc -Thtml | sed "s/&amp;/\&/g;s/<h1 align=\"center\">man/<h1 align=\"center\">$(PROGGROSS) (Version $$(cat version))/g" > man_en.html
	-@rm -f README.md
	-@sed -n '20,$$p' man_en.html > README.md 
	@echo -e "\033[0;34m"   man_en.html"\033[0;30m" und"\033[0;34m" README.md"\033[0;30m" neu aus"\033[0;34m" man_de"\033[0;30m" erstellt
endif

fertig:
	@echo -e " Fertig mit $(ICH), nachher:                                "  
	@echo -e "\033[0;34m" $(shell ls -l $(EXEC)) "\033[0;30m" 

.PHONY: clean

clean: 
	@echo -n " Bereinige ..."
	@echo -e -n "\r" 
	@$(shell rm -f $(EXEC) $(OBJ) 2>/dev/null)
	@$(shell sudo rm -f $(INSTEXEC) 2>/dev/null)
	@echo -e " Fertig mit Bereinigen!"  

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
