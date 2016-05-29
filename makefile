ICH := $(firstword $(MAKEFILE_LIST))
SRCS = $(wildcard *.cpp)
objs = $(SRCS:.cpp=.o)
CFLAGS=-c -Wall `mysql_config --cflags` -std=gnu++11
LDFLAGS=`mysql_config --libs` -ltiff
ERG=$(shell basename $(CURDIR))
EXPFAD=/usr/local/sbin
EXEC=$(EXPFAD)/$(ERG)
CINST="gcc-c++"

DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td

CC = g++
POSTCOMPILE = mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d 2>/dev/null

MANP=/usr/share/man
MANPD=${MANP}/de/man1/${ERG}.1.gz
MANPE=${MANP}/man1/${ERG}.1.gz
MANPDH=${PWD}/man_de.html
MANPEH=${PWD}/man_en.html


alles: anzeig compiler $(EXEC) man fertig

anzeig:
	@echo -e GNU Make, Zieldatei: "\033[1;31m" $(EXEC)"\033[0;30m" , vorher:
	@echo -e "\033[0;34m" $(shell ls -l $(EXEC)) "\033[0;30m" 
	@echo -e Quelldateien: "\033[1;31m" $(SRCS) "\033[0;30m" 
	-@$(shell rm fehler.txt 2>/dev/null)

$(EXEC): $(objs)
	@echo -n "verlinke $(OBJ) zu $@ ..."
	-$(CC) $(LDFLAGS) $^ -o $@

%.o : %.cpp
%.o : %.cpp $(DEPDIR)/%.d
	@echo -n "kompiliere $< ..."
	-$(CC) $(DEPFLAGS) $(CFLAGS) -c $< 2>> fehler.txt
	-@if test -s fehler.txt; then vi +0/error fehler.txt; else rm fehler.txt; fi;
	-@$(shell $(POSTCOMPILE))
	@if test -s fehler.txt; then false; fi;

$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d

compiler:
	@echo -n "Untersuche Compiler ..."
	@echo -e -n "\r" 
	-@which g++ >/dev/null 2>&1 || { which zypper && zypper -n in $(CINST) || { which apt-get && apt-get --assume-yes install build-essential; } }
	-@/sbin/ldconfig; /sbin/ldconfig -p | grep -q "libmysqlclient.so " || { which zypper && zypper -n in libmysqlclient-devel || { which apt-get && apt-get --assume-yes install libmysqlclient-dev; }; /sbin/ldconfig; }
	-@test -f /usr/include/tiff.h || { which zypper && zypper -n in libtiff-devel || { which apt-get && apt-get --assume-yes install libtiff-dev; } }

man: ${MANPD} ${MANPE} ${MANPDH} ${MANPEH}

${MANPD}: ${PWD}/man_de 
	-gzip -c ${PWD}/man_de >${MANPD}
${MANPE}: ${PWD}/man_en
	-gzip -c ${PWD}/man_en >${MANPE}

${MANPDH}: ${PWD}/man_de 
	-sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g' man_de | groff -mandoc -Thtml | sed 's/&amp;/\&/g;s/<h1 align="center">man/<h1 align="center">Autofax/g' > man_de.html

${MANPEH}: ${PWD}/man_en 
	-sed -e 's/Ä/\&Auml;/g;s/Ö/\&Ouml;/g;s/Ü/\&Uuml;/g;s/ä/\&auml;/g;s/ö/\&ouml;/g;s/ü/\&uuml;/g;s/ß/\&szlig;/g' man_en | groff -mandoc -Thtml | sed 's/&amp;/\&/g;s/<h1 align="center">man/<h1 align="center">Autofax/g' > man_en.html

fertig:
	@echo -e "Fertig mit $(ICH), nachher:                                "  
	@echo -e "\033[0;34m" $(shell ls -l $(EXEC)) "\033[0;30m" 

.PHONY: clean

clean: 
	@echo -n "Bereinige ..."
	@echo -e -n "\r" 
	-@$(shell rm $(EXEC) $(OBJ) 2>/dev/null)
	@echo -e "Fertig mit Bereinigen!"  

-include $(patsubst %,$(DEPDIR)/%.d,$(basename $(SRCS)))
