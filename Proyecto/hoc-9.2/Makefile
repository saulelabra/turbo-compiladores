###############################################################################
#   @(#)HOC 9.2 makefile, 1.13 Sun Aug 12 23:27:08 IDT 2007
###############################################################################



prefix = /usr/local
exec_prefix = ${prefix}
bindir=${exec_prefix}/bin
libdir=${exec_prefix}/lib

CC=gcc
YACC=bison -y
INSTALL=/usr/bin/install -c
INSTALL_PROGRAM=${INSTALL}

DEFS=-DPACKAGE_NAME=\"\" -DPACKAGE_TARNAME=\"\" -DPACKAGE_VERSION=\"\" -DPACKAGE_STRING=\"\" -DPACKAGE_BUGREPORT=\"\" -DHAVE_LIBM=1 -DSTDC_HEADERS=1 -DRETSIGTYPE=void -Dpointer_sized_int=long -DHAVE_LGAMMA=1 -DHAVE_SIGLONGJMP=1 -DLIBPREFIX="\"$(libdir)/hoc/lib\""
CFLAGS=-g -O2
LDFLAGS=
LIBS=-lm 
LIBOBJS=


YFLAGS = -d

OBJS = hoc.o code.o init.o math.o symbol.o memory.o version.o $(LIBOBJS)

all:	hoc

hoc:	$(OBJS)
	$(CC) $(CFLAGS) $(LD_FLAGS) -o hoc $(OBJS) $(LIBS)

install:	hoc
	$(INSTALL_PROGRAM) -s hoc $(bindir)
uninstall:
	rm -i $(bindir)/hoc

clean:
	rm -f hoc $(OBJS) $(LIBOBJS) [xy].tab.[cho] hoc.c
	rm -f mon.out core y.output conflicts.list $(MSOBJS) y.c
distclean:
	rm -f hoc $(OBJS) $(LIBOBJS) [xy].tab.[cho] hoc.c
	rm -f mon.out core y.output conflicts.list $(MSOBJS) y.c
	rm -f config.cache config.log config.status Makefile

# check for warnings, with gcc
gcclint:
	$(CC) -fsyntax-only -Wall -Wstrict-prototypes -Wmissing-prototypes $(CFLAGS) $(DEFS) code.c gamma.c hoc.c init.c math.c memory.c symbol.c version.c

######################################################################

hoc.c:	hoc.y
	$(YACC) $(YFLAGS) hoc.y
	mv y.tab.c hoc.c

y.c:	hoc.y
	rm -f y.c
	$(YACC) $(YFLAGS) hoc.y

hoc.o code.o init.o symbol.o memory.o:	hoc.h
code.o init.o symbol.o: x.tab.h
x.tab.h:	y.tab.h
	@-cmp -s x.tab.h y.tab.h || cp y.tab.h x.tab.h

.c.o:
	$(CC) -c $(CFLAGS) $(DEFS) $<
######################################################################
#MSOBJS = y.obj code.obj init.obj math.obj symbol.obj memory.obj gamma.obj \
#	 version.obj
#MSLIBS = $(MSLIBDIR)setargv.obj $(MSLIBDIR)binmode.obj
#hoc.exe:	$(MSOBJS)
#	$(CC) $(CFLAGS) -o hoc $(MSOBJS) $(MSLIBS) /LINK /NOE
