# Makefile for bpmtap
# Marc_G 2016

CPP = g++
CFLAGS = -Wall

# Sources and headers
SRC = bpmtap.cpp keypress.cpp
INC = keypress.h

# Install dir
PREFIX = /usr/local

.PHONY: bpmtap

bpmtap: $(SRC) $(INC)
	$(CPP) -o $@ $(CFLAGS) $(SRC)

install:
	cp bpmtap $(PREFIX)/bin
	cp bpmtap.1.gz $(PREFIX)/man/man1

.cpp.o:
	$(CPP) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`

