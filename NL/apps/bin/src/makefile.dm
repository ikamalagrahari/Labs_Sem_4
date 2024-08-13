# makefile.dm	Makefile for building with Digital Mars.
# Copyright (c) 2002 by Christopher Heng. All rights reserved.

# $Id: makefile.dm 1.2 2002/06/26 06:57:52 chris Exp $

# WARNING: This makefile produces a version of TODOS.EXE and FROMDOS.EXE
# that does *not* handle wildcards on the command line. If you want the
# executable to handle wildcards, used the supplied executables. I haven't
# figured out how to get wildcard preprocessing of command line arguments
# with Digital Mars yet. Is there a obj file somewhere that I can link into
# the application without having to write my own command line globbing routine?

# This makefile assumes the Digital Mars default MAKE.EXE
# It creates a Win32 console application.
# Unlike the other makefiles, this is a barebones makefile -
# I created it mainly to check that the source code compiles
# cleanly with this compiler.

# programs
CC = sc
CP = copy
LD = sc
RM = deltree /y

# flags
CFLAGS = -o -c -Ilib

# directories
LIBDIR = lib

# filenames
FROMDOS = fromdos.exe
TODOS = todos.exe
OBJS = init.obj tofrodos.obj utility.obj lib\getopt.obj

# implicit rules
.c.obj:
	$(CC) $(CFLAGS) $<


# targets

all: $(FROMDOS) $(TODOS)

clean:
	$(RM) $(OBJS)

clobber: clean
	$(RM) $(FROMDOS) $(TODOS)

$(FROMDOS): $(TODOS)
	$(CP) $(TODOS) $(FROMDOS)

$(TODOS): $(OBJS)
	$(LD) -o$(TODOS) $(OBJS)


# objects

init.obj: init.c config.h emsg.h tofrodos.h utility.h version.h

tofrodos.obj: tofrodos.c config.h emsg.h tofrodos.h utility.h version.h

utility.obj: utility.c config.h emsg.h tofrodos.h utility.h

lib\getopt.obj: lib\getopt.c lib\getopt.h
	$(CC) $(CFLAGS) -olib\getopt.obj lib\getopt.c
