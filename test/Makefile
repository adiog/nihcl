# $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/Makefile,v 3.0 90/05/22 10:10:14 kgorlen Rel $
# C++ compiler
CC = CC

# C++ debug switch
#CCDEBUG =
CCDEBUG = -g

# C++ flags
# NOTE: Disable +p option when compiling with AT&T R2.1
CCFLAGS = +p
#CCFLAGS =

# C++ include files
I = /usr/include/CC

# If using BSD
SYS = BSD
# If using System V
#SYS = SYSV

# Compile with nested types (works with AT&T R2.1 and GNU C++)
NESTED_TYPES =
#NESTED_TYPES = -DNESTED_TYPES

# Disable AT&T R2.0/R2.1 bug work-around code
BUGDEFS =
#BUGDEFS = -DBUG_bC2728 -DBUG_38 -DBUG_39 -DBUG_OPTYPECONST
# Defining BUG_TOOBIG disables code that prevents C compiler "yacc stack overflows"
#BUGDEFS = -DBUG_bC2728 -DBUG_38 -DBUG_39 -DBUG_OPTYPECONST -DBUG_TOOBIG

# Enable debug code
DEBUGDEFS =
#DEBUGDEFS = -DDEBUG_OBJIO -DDEBUG_PROCESS

# For no multiple inheritance support
MI =
# Enable support for multiple inheritance
#MI = -DMI

NIHCLINC = ../lib
NIHCLLIB = ../lib/libnihcl.a

CFLAGS = -I${NIHCLINC} ${MI} ${CCDEBUG} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS}
LFLAGS = ${NIHCLLIB} ${CCDEBUG}

include progs.all
#include classes.all
include objects.all

.SUFFIXES: ..c .s
.c:
	${CC} ${CFLAGS} $< -o $* ${LFLAGS}
.c.o:
	${CC} ${CFLAGS} -c $<
.c..c:
	${CC} ${CFLAGS} +i -c $<
.c.s:
	${CC} ${CFLAGS} +i -S $<

all:${PROGS}

${PROGS}: $$@.o ${NIHCLLIB}
	${CC} $@.o -o $@ ${LFLAGS}

depend:
	-rm -f *..c
	echo 'PROGS =' [a-z]*[a-z0-9].c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1#g' >progs.all
#	echo 'CLASSES =' [A-Z]*[a-z0-9].c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1.o#g' >classes.all
	echo 'OBJECTS =' *.c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1.o#g' >objects.all
	touch make.tdep
	makedepend -I$I -I${NIHCLINC} -f make.tdep -- ${CFLAGS} -- *.c
	sed -e 's#${NIHCLINC}/#$${NIHCLINC}/#g' make.tdep | sed -e 's# $I/[^ 	$$]*##g' | sed -e 's# /usr/include/[^  $$]*##g' | sed -e '/:[  ]*$$/d' >make.dep
	rm make.tdep

clean:
	rm -f *.o ${PROGS} *..c *.s core

include make.dep
