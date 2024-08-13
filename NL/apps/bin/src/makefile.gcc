# makefile.gcc	Makefile for building with the GNU C compiler on Linux.
# Copyright (c) 1996,1997 by Christopher Heng. All rights reserved.

# $Id: makefile.gcc 1.7 2002/06/20 06:44:48 chris Exp $ /*

# This makefile requires the GNU make to work (we use the GNU extensions).

# Define the following if you need
#
#	DEBUG	to add debugging information, eg "make DEBUG=1 all"


ifdef DEBUG
CDEBUG = -g
LDEBUG = -g
else
CDEBUG = -O2
LDEBUG = -s
endif

ifndef VERSTR
VERSTR = 0.0
endif

# programs
CC = gcc
CD = cd
CP = cp
GZIP = gzip
INSTALL = install
LN = ln
LD = gcc
MAKE = make
MKDIR = mkdir
MV = mv
RM = rm -f
TAR = tar
ZIP = zip

# flags
CFLAGS = $(DEFINES) $(TFLAG) $(CDEBUG) -c -Wall
GZIPFLAGS = -9
INSTALLBINFLAGS = -m 755
INSTALLDATAFLAGS = -m 644
LDFLAGS = $(LDEBUG)
LNFLAGS = -sf
RMRECURFLAGS = -rf
TARFLAGS = cvf
ZIPSRCFLAGS = -r -9

# directories
BINDIR = /usr/local/bin
DISTDIR = tofrodos-$(VERSTR)
LIBDIR = lib
LIBDISTDIR = $(DISTDIR)/lib
MANDIR = /usr/local/man/man1

# filenames
FROMDOS = fromdos
FROMDOSMAN = fromdos.1
FROMDOSTXT = fromdos.txt
TARGZNAME = $(TARNAME).gz
TARNAME = tofrodos-$(VERSTR).tar
TODOS = todos
ZIPSRCNAME = tfd.zip

# lists of filenames
DISTFILES = config.h \
	copying \
	emsg.h \
	fromdos \
	init.c \
	makefile.bc \
	makefile.gcc \
	makefile.vc \
	makefile.wcc \
	readme.txt \
	todos16.exe \
	todos32.exe \
	tofrodos.c \
	tofrodos.h \
	tofrodos.lsm \
	utility.c \
	utility.h \
	version.h \
	$(FROMDOSMAN)
LIBDISTFILES = $(LIBDIR)/getopt.c \
	$(LIBDIR)/getopt.h \
	$(LIBDIR)/mktemp.c \
	$(LIBDIR)/mktemp.h
OBJS = init.o \
	tofrodos.o \
	utility.o

# implicit rules
.c.o:
	$(CC) $(CFLAGS) $<

# user visible rules
all: $(FROMDOS) $(TODOS)

clean:
	$(RM) $(OBJS)

clobber: clean
	$(RM) $(FROMDOS) $(TODOS)

dist: $(DISTFILES) $(DISTDIR) $(LIBDISTDIR)
	$(CP) $(DISTFILES) $(DISTDIR)
	$(CP) $(LIBDISTFILES) $(LIBDISTDIR)
	$(MV) $(DISTDIR)/makefile.gcc $(DISTDIR)/Makefile
	$(MV) $(DISTDIR)/copying $(DISTDIR)/COPYING
	$(MV) $(DISTDIR)/readme.txt $(DISTDIR)/README.TXT
	($(CD) $(DISTDIR) ; $(LN) $(LNFLAGS) fromdos todos)

distclean: clobber
	$(RM) $(RMRECURFLAGS) $(DISTDIR)

install: installman
	$(INSTALL) $(INSTALLBINFLAGS) $(FROMDOS) $(BINDIR)
	($(CD) $(BINDIR) ; $(LN) $(LNFLAGS) fromdos todos)

installman: $(FROMDOSMAN)
	$(INSTALL) $(INSTALLDATAFLAGS) $(FROMDOSMAN) $(MANDIR)
	($(CD) $(MANDIR) ; $(LN) $(LNFLAGS) fromdos.1 todos.1)

save:
	$(ZIP) $(ZIPSRCFLAGS) $(ZIPSRCNAME) *

tardist: $(TARGZNAME)


# real rules
$(DISTDIR):
	$(MKDIR) $(DISTDIR)

$(FROMDOS): $(OBJS)
	$(CC) $(LDFLAGS) -o $(FROMDOS) $(OBJS)

$(FROMDOSTXT): $(FROMDOSMAN)
	gtbl $(FROMDOSMAN) | groff -Tascii -mandoc | \
		troff -Tascii -mandoc | grotty > $@

$(LIBDISTDIR):
	$(MKDIR) $(LIBDISTDIR)

$(TARGZNAME): dist
	$(TAR) $(TARFLAGS) $(TARNAME) $(DISTDIR)
	$(GZIP) $(GZIPFLAGS) $(TARNAME)

$(TODOS): $(FROMDOS)
	$(LN) $(LNFLAGS) $(FROMDOS) $(TODOS)

# objects
init.o: init.c config.h emsg.h tofrodos.h utility.h version.h

tofrodos.o: tofrodos.c config.h emsg.h tofrodos.h utility.h version.h

utility.o: utility.c config.h emsg.h tofrodos.h utility.h


# The following information is for the information of the maintainer of
# the package only.

# To make the distribution tar file, you need to define VERSTR to the
# version number. Eg, for a version 1.0 release, define VERSTR=1.0
# Hence a make command line would read
#	make VERSTR=1.0 tardist
# If VERSTR is not defined at any time, it defaults to 0.0 (to remind
# you that you forgot something!).
#
# Before making tardist, you need to compile in DOS first.

