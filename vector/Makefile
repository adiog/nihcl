# $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/vector/RCS/Makefile,v 3.0 90/05/20 21:04:12 kgorlen Rel $
# C++ compiler
CC = CC

# C++ debug switch
CCDEBUG =
#CCDEBUG = -g

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

NIHCLLIB = ../lib/libnihcl.a
NIHVECLIB = libnihclvec.a

CFLAGS = -I${NIHCLINCDIR} ${MI} ${CCDEBUG} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS}

# Target Directories
NIHCLLIBDIR = /usr/lib
NIHCLINCDIR = ../lib

include make.all

.SUFFIXES: ..c .s
.c.a:
	echo $< >>targetlist
.c.o:
	${CC} ${CFLAGS} -c $<
.c..c:
	${CC} ${CFLAGS} +i -c $<
.c.s:
	${CC} ${CFLAGS} +i -S $<

.PRECIOUS: ${NIHVECLIB}

all: always ${NIHVECLIB}

${NIHVECLIB}: ${OBJECTS}
	${CC} ${CFLAGS} -c `cat targetlist`
	ar rv $@ *.o
	rm -f *.o
	if test ${SYS} = BSD ; then ranlib ${NIHVECLIB}; fi

always:
	-rm -f targetlist *.o
	${MAKE} generic

generic:
	${MAKE} -f genericmake ${VECS}

install:
	cp lib*.a ${NIHCLLIBDIR}
	if test ${SYS} = BSD ; then \
		for i in lib*.a; do (cd ${NIHCLLIBDIR}; ranlib -t $$i); done; \
	fi
	-mkdir ${NIHCLINCDIR}
	cp *.h ${NIHCLINCDIR}

depend:
	-rm -f *..c
	echo 'VECS =' *Vec.h | sed -e 's#\([a-zA-Z0-9_]*\)\.h#\1.c#g' >make.all
	${MAKE} generic
	echo 'OBJECTS =' *.c | sed -e 's#\([a-zA-Z0-9_]*\)\.c#${NIHVECLIB}(\1.o)#g' >>make.all
	touch make.tdep
	makedepend -I$I -I${NIHCLINCDIR} -f make.tdep -- ${CFLAGS} -- *.c
	sed -e 's#${NIHCLINCDIR}/#$${NIHCLINCDIR}/#g' make.tdep | sed -e 's# $I/[^ 	$$]*##g' | sed -e 's# /usr/include/[^  $$]*##g' | sed -e '/:[  ]*$$/d' | tee MAKE.dep | sed -e 's#\([a-zA-Z0-9_]*\.o\)#${NIHVECLIB}(\1)#g' >make.dep
	rm make.tdep

clean:
	-chmod u+w *Vec.c
	-rm -f targetlist *.o *Vec.c *..c *.s *.a make.tdep

include make.dep
