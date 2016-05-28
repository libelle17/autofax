ich := $(firstword $(MAKEFILE_LIST))
ERG=autofax
CC=g++
CINST="gcc-c++"
#CFLAGS=-c -Wall -lvmime -lgnutls -lgsasl
CFLAGS=-c -Wall `mysql_config --cflags` -std=gnu++11
LDFLAGS=`mysql_config --libs` -ltiff
PFAD=${PWD}
EXPFAD=/usr/local/sbin
FILES=autofax.cpp vorgaben.cpp konsole.cpp DB.cpp
SRC= $(FILES:%.cpp=$(PWD)/%.cpp)
#OBJ=$(FILES:.cpp=.o)
OBJ=$(SRC:.cpp=.o) 
EXEC=$(EXPFAD)/$(ERG)
DEPFILE= ${PWD}/$(ERG).d
MANP=/usr/share/man
MANPD=${MANP}/de/man1/${ERG}.1.gz
MANPE=${MANP}/man1/${ERG}.1.gz

all: compiler anzeig dep $(OBJ) $(EXEC) man
#	$(EXEC)
	@echo "Fertig mit $(ich)!" 
#	@if test -s fehler.txt; then vi +0/error fehler.txt; exit; fi;

man: ${MANPD} ${MANPE}

${MANPD}: ${PWD}/man_de
	gzip -c ${PWD}/man_de >${MANPD}

${MANPE}: ${PWD}/man_en
	gzip -c ${PWD}/man_en >${MANPE}

compiler:
	-@which g++ >/dev/null 2>&1 || { which zypper && zypper -n in $(CINST) || { which apt-get && apt-get --assume-yes install build-essential; } }
	-@/sbin/ldconfig; /sbin/ldconfig -p | grep -q "libmysqlclient.so " || { which zypper && zypper -n in libmysqlclient-devel || { which apt-get && apt-get --assume-yes install libmysqlclient-dev; }; /sbin/ldconfig; }
	-@test -f /usr/include/tiff.h || { which zypper && zypper -n in libtiff-devel || { which apt-get && apt-get --assume-yes install libtiff-dev; } }

anzeig:
	@echo "Zeige an:"
	@echo "SRC: $(SRC)"
	@echo "OBJ: $(OBJ)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "DEPFILE: $(DEPFILE)"
	@echo "EXEC: $(EXEC)"

dep: $(SRC)
	-@rm fehler.txt
	@echo "erstelle $(DEPFILE)"
	-$(CC) -MM $(SRC) > $(DEPFILE) 2>> fehler.txt
#	@if test -s fehler.txt; then vi +0/error fehler.txt; exit; fi;

#.cpp.o:
%.o: %.cpp
#%.o: $(PFAD)/%.cpp
	@echo "kompiliere $<"
	-$(CC) $(CFLAGS) -o $@ $< 2>> fehler.txt
	@if test -s fehler.txt; then vi +0/error fehler.txt; exit; fi;

$(EXEC): $(OBJ) 
	@echo "verlinke $(OBJ) zu $@"
	-$(CC) $(OBJ) -o $@ $(LDFLAGS) 2>> fehler.txt
	@if test -s fehler.txt; then vi +0/error fehler.txt; exit; fi;

-include $(DEPFILE)

.PHONY: clean

clean: 
	rm $(EXEC) $(OBJ)
