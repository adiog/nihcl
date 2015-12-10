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

# Enable debug code
DEBUGDEFS =

CFLAGS = ${CCDEBUG} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS}
LFLAGS = ${CCDEBUG}

# Target Directories for Installation
LIB_ID = libC
# CLIBDIR is directory where ${LIB_ID}.a resides
CLIBDIR = /usr/lib
ERRGENDIR = /usr/local/bin
ERRTABDIR = /usr/local/lib
ERRINCDIR = $I

#include progs.all
#include classes.all
include objects.all

.SUFFIXES: .s ..c

.c.o:
	${CC} ${CFLAGS} -c $<
.c..c:
	${CC} ${CFLAGS} +i -c $<
.c.s:
	${CC} ${CFLAGS} +i -S $<

all: ${ERRTABDIR}/errgen_tab ${OBJECTS} errgen testerrs.h errtst verify

errgen:  ErrFac.o gettok.o dofile.o errgen.o
	${CC} ErrFac.o gettok.o dofile.o errgen.o -o $@ ${LFLAGS}
#	strip errgen

errors.o: errors.c
	${CC} ${CFLAGS} -F -c errors.c | sed -e 's/__0__builtin/__builtin/g' >errors..c
	cc ${CCDEBUG} -c -o errors.o errors..c
	rm errors..c

errtst:  errtst.o errors.o testerrs.o
	${CC} errtst.o errors.o testerrs.o -o $@ ${LFLAGS}

testerrs.h: errgen testerrs.err
	-chmod a+w testerrs.[ch]
	./errgen -R${ERRTABDIR} testerrs
	chmod a-w testerrs.[ch]
	${CC} -I. ${CFLAGS} -c testerrs.c

verify: errtst
	./errtst 2>&1 | cmp -s - errtst.v

${ERRTABDIR}/errgen_tab:
	cp errgen_tab ${ERRTABDIR}

install:
	-mkdir ${ERRGENDIR}
	cp errgen ${ERRGENDIR}
	-mkdir ${ERRINCDIR}
	-chmod ug+w ${ERRINCDIR}/errlib.h ${ERRINCDIR}/errors.h
	cp errlib.h ${ERRINCDIR}
	cp errors.h ${ERRINCDIR}
	ar rv ${CLIBDIR}/${LIB_ID}.a errors.o
	if test ${SYS} = BSD ; then cd ${CLIBDIR}; ranlib ${LIB_ID}.a; fi
	
depend:
	-rm -f *..c
#	echo 'PROGS =' [a-z]*[a-z0-9].c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1#g' >progs.all
#	echo 'CLASSES =' [A-Z]*[a-z0-9].c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1.o#g' >classes.all
	echo 'OBJECTS =' *.c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1.o#g' >objects.all
	touch make.tdep
	makedepend -I$I -f make.tdep -- ${CFLAGS} -- *.c
	sed -e 's# $I/[^ 	$$]*##g' make.tdep | sed -e 's# /usr/include/[^  $$]*##g' | sed -e '/:[  ]*$$/d' >make.dep
	rm make.tdep

clean:
	-chmod a+w testerrs.[ch]
	-rm -f *.o *..c *..s core errgen errtst testerrs.[ch]

include make.dep
