ICH := $(firstword $(MAKEFILE_LIST))
SRCS = $(wildcard *.cpp)
OBJ = $(SRCS:.cpp=.o)
CFLAGS=-c -Wall `mysql_config --cflags` 
LDFLAGS=`mysql_config --libs` -ltiff
ERG=$(shell basename $(CURDIR))
EXPFAD=/usr/local/sbin
EXEC=$(ERG)
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
MANPD=${MANP}/de/man1/${ERG}.1.gz
MANPE=${MANP}/man1/${ERG}.1.gz
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
	git commit -m "Commit durch make"
	git push

anzeig:
	@echo -e " GNU Make, Zieldatei:""\033[1;31m" $(EXEC)"\033[0;30m", vorher:
	@echo -e "\033[0;34m" $(shell ls -l $(EXEC) 2>/dev/null) "\033[0;30m" 
	@echo -e " Quelldateien:""\033[1;31m" $(SRCS)"\033[0;30m" 
	@echo -e " Verwende Compiler: ""\033[1;31m" $(CCName) "\033[0;30m"
	-@$(shell rm fehler.txt 2>/dev/null)

$(EXEC): $(OBJ)
	@echo -n " verlinke $(OBJ) zu $@ ..."
	-$(CC) $^ -o $@ $(LDFLAGS)

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	@echo -n " kompiliere $< ..."
	-$(CC) $(DEPFLAGS) $(CFLAGS) -c $< 2>> fehler.txt
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

man: ${MANPD} ${MANPE} ${MANPDH} ${MANPEH}

${MANPD}: ${CURDIR}/man_de 
	-sudo mkdir -p $(MANP)/de/man1
	-sudo gzip -c $(CURDIR)/man_de >${ERG}.1.gz
	-sudo mv ${ERG}.1.gz ${MANPD}
${MANPE}: ${CURDIR}/man_en
	-sudo mkdir -p $(MANP)/man1
	-sudo gzip -c $(CURDIR)/man_en >${ERG}.1.gz
	-sudo mv ${ERG}.1.gz ${MANPE}

${MANPDH}: $(CURDIR)/man_de 
	-@rm -f man_de.html
	-@sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g' man_de | groff -mandoc -Thtml | sed 's/&amp;/\&/g;s/<h1 align="center">man/<h1 align="center">Autofax/g' > man_de.html
	@echo -e "\033[0;34m"   man_de.html"\033[0;30m" neu aus"\033[0;34m" man_de"\033[0;30m" erstellt

${MANPEH}: $(CURDIR)/man_en 
	-@rm -f man_en.html
	-@sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g' man_en | groff -mandoc -Thtml | sed 's/&amp;/\&/g;s/<h1 align="center">man/<h1 align="center">Autofax/g' > man_en.html
	-@rm -f README.md
	-@sed -n '20,$$p' man_en.html > README.md 
	@echo -e "\033[0;34m"   man_en.html"\033[0;30m" und"\033[0;34m" README.md"\033[0;30m" neu aus"\033[0;34m" man_de"\033[0;30m" erstellt

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
install:
	sudo cp "$(EXEC)" "$(INSTEXEC)"

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
