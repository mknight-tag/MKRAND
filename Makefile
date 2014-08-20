#############################################################################
# Makefile for building: mkrand
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = 
CFLAGS        = -std=gnu99 -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIE $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT -fPIE $(DEFINES)
INCPATH       = -I.
LINK          = g++
LFLAGS        = -m64
LIBS          = $(SUBLIBS)
AR            = ar cqs
RANLIB        = 
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = cell_logic.c \
		command.c \
		fmt_cp.c \
		fmt_vec.c \
		machine_logic.c 
OBJECTS       = cell_logic.o \
		command.o \
		fmt_cp.o \
		fmt_vec.o \
		machine_logic.o
DIST          = 
DESTDIR       = 
TARGET        = mkrand
VERSION_TAG   = TA1
TAGGED_TARGET = $(TARGET)-$(VERSION_TAG)

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)


dist: 
	@test -d .tmp/$(TAGGED_TARGET) || mkdir -p .tmp/$(TAGGED_TARGET)
	$(COPY_FILE) $(SOURCES) $(DIST) .tmp/$(TAGGED_TARGET)/ && $(COPY_FILE) cell_logic.h command.h fmt_cp.h fmt_vec.h machine_logic.h .tmp/$(TAGGED_TARGET)/ && $(COPY_FILE) cell_logic.c command.c fmt_cp.c fmt_vec.c machine_logic.c Makefile .tmp/$(TAGGED_TARGET)/ && (cd `dirname .tmp/$(TAGGED_TARGET)` && $(TAR) $(TAGGED_TARGET).tar $(TAGGED_TARGET) && $(COMPRESS) $(TAGGED_TARGET).tar) && $(MOVE) `dirname .tmp/$(TAGGED_TARGET)`/$(TAGGED_TARGET).tar.gz . && $(DEL_FILE) -r .tmp/$(TAGGED_TARGET)


clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core

####### Compile

cell_logic.o: cell_logic.c cell_logic.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o cell_logic.o cell_logic.c

command.o: command.c command.h \
		machine_logic.h \
		cell_logic.h \
		fmt_vec.h \
		fmt_cp.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o command.o command.c

fmt_cp.o: fmt_cp.c fmt_vec.h \
		cell_logic.h \
		machine_logic.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o fmt_cp.o fmt_cp.c

fmt_vec.o: fmt_vec.c cell_logic.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o fmt_vec.o fmt_vec.c

machine_logic.o: machine_logic.c command.h \
		fmt_vec.h \
		cell_logic.h \
		machine_logic.h
	$(CC) -c $(CFLAGS) $(INCPATH) -o machine_logic.o machine_logic.c

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

