# $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Makefile,v 3.0 90/05/20 21:03:20 kgorlen Rel $
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

# Flags for ln
#LNFLAGS =
LNFLAGS = -s

# If using "patch"
MAIN = _main.c_p
# If using "munch"
#MAIN = _main.c_m

# For no multiple inheritance support
MI =
# Enable support for multiple inheritance
#MI = -DMI

NIHCLLIB = libnihcl.a

CFLAGS = ${MI} ${CCDEBUG} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS}

# Target Directories
NIHCLLIBDIR = /usr/lib
NIHCLINCDIR = /usr/include/nihcl
ERRGENDIR = /usr/local/bin
ERRTABDIR = /usr/local/lib

include make.all

.SUFFIXES: ..c .s
.c.a:
	echo $< >>targetlist
.c..c:
	${CC} ${CFLAGS} +i -c $<
.c.s:
	${CC} ${CFLAGS} +i -S $<

.PRECIOUS: ${NIHCLLIB}

all: always nihclerrsx.h ${NIHCLLIB}(regex.o) ${NIHCLLIB}

always:
	-rm -f targetlist *.o _main.c
	touch targetlist
	${MAKE} generic _main.c

nihclerrsx.h: nihclerrs.err
	if test -f /usr/bin/errcom ; then errcom nihclerrs.err ; else ${ERRGENDIR}/errgen -R${ERRTABDIR} nihclerrs.err; fi
	sed -f nihclerrs.sed <nihclerrs.c >nihclerrs.tmp
	mv nihclerrs.tmp nihclerrs.c
	sed -n -e "s/^\([A-Z][a-zA-Z]*\).*/int NIHCL_\1	= NIHCL__\1;/p" <nihclerrs.err >nihclerrsx.h

generic: Arraychar.h Arraychar.c

_main.c:
	ln ${LNFLAGS} ${MAIN} _main.c

Arraychar.h: Array_h.m4
	-chmod u+w $@; rm -f $@
	echo "ARRAYDECLARE(Arraychar,char)" | m4 Array_h.m4 - >Arraychar.h
	chmod a-w $@

Arraychar.c: Array_c.m4 Arraychar.p
	-chmod u+w $@; rm -f $@
	m4 Array_c.m4 Arraychar.p >Arraychar.c
	chmod a-w $@

${NIHCLLIB}(regex.o): regex/regex.c regex.h
#	cc -O -I. -D'SIGN_EXTEND_CHAR(c)=(((c) & 0x80) ? ((c) | 0xffffff80) : (c))' -c regex/regex.c
	cc -O -I. -c regex/regex.c
	touch targetlist

# Hack to make stdarg work on sparc

Class.o ${NIHCLLIB}(Class.o): Class.c
#	${CC} ${CFLAGS} -F -c Class.c | sed -e 's/__0__builtin/__builtin/g' >Class..c
	${CC} ${MI} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS} -F -c Class.c | sed -e 's/__0__builtin/__builtin/g' >Class..c
	cc ${CCDEBUG} -c -o Class.o Class..c
	rm Class..c

Exception.o ${NIHCLLIB}(Exception.o): Exception.c
#	${CC} ${CFLAGS} -F -c Exception.c | sed -e 's/__0__builtin/__builtin/g' >Exception..c
	${CC} ${MI} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS} -F -c Exception.c | sed -e 's/__0__builtin/__builtin/g' >Exception..c
	cc ${CCDEBUG} -c -o Exception.o Exception..c
	rm Exception..c

${NIHCLLIB}: ${OBJECTS} targetlist
	if test -s targetlist ; then ${CC} ${CFLAGS} -c `cat targetlist`; fi
	for f in *.o; \
	do \
		if test '*.o' != $$f ;then \
			ar rv $@ *.o; \
			rm -f *.o; \
			if test ${SYS} = BSD ; then ranlib ${NIHCLLIB}; fi; \
		fi; \
		break; \
	done

install:
	cp lib*.a ${NIHCLLIBDIR}
	if test ${SYS} = BSD ; then \
		for i in lib*.a; do (cd ${NIHCLLIBDIR}; ranlib -t $$i); done; \
	fi
	-mkdir ${NIHCLINCDIR}
	-chmod u+w ${NIHCLINCDIR}/*.h ${NIHCLINCDIR}/Template_[ch]
	-rm -f ${NIHCLINCDIR}/*.h ${NIHCLINCDIR}/Template_[ch]
	cp *.h Template_[ch] ${NIHCLINCDIR}

depend:	nihclerrsx.h generic _main.c
	-rm -f *..c
	echo 'OBJECTS = $${NIHCLLIB}(regex.o)' *.c | sed -e 's#\([a-zA-Z0-9_]*\)\.c#$${NIHCLLIB}(\1.o)#g' >make.all
	touch make.tdep
	makedepend -I$I -f make.tdep -- ${CFLAGS} -- *.c
	sed -e 's# $I/[^ 	$$]*##g' make.tdep | sed -e 's# /usr/include/[^  $$]*##g' | sed -e '/:[  ]*$$/d' | tee MAKE.dep | sed -e 's#\([a-zA-Z0-9_]*\.o\)#$${NIHCLLIB}(\1)#g' >make.dep
	rm make.tdep

clean:
	-rm -f targetlist *.o *..c ${NIHCLLIB} nihclerrsx.h ${GENERICS} _main.c make.tdep*

include make.dep
