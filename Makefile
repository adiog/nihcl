# $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/RCS/Makefile,v 3.0 90/05/22 22:58:11 kgorlen Rel $
#
# Make Targets:
#
#	errorfacility	Make and install error handling facility
#	all		Make all non-MI class libraries and test suites (default)
#	mi		Make all class libraries and test suites with support for multiple inheritance enabled
#	verify		Run all verification test suites
#	install		Install class libraries and header files in target directories
#	examples	Make example programs for book
#	exverify	Verify example programs
#	cleantest	Remove generated files from test suites
#	clean		Remove all generated files

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

# Target library for installation of Error Facility
LIB_ID = libC

# Target Directories for Installation

# directory for libnihcl.a
NIHCLLIBDIR = /usr/local/lib
# directory for NIHCL include files
NIHCLINCDIR = /usr/include/nihcl
# directory where ${LIB_ID}.a resides
CLIBDIR = /usr/local/lib/C++R2.0
# directory for errgen utility
ERRGENDIR = /usr/local/bin
# directory for errgen table file
ERRTABDIR = /usr/local/lib
# directory for errlib.h and errors.h
ERRINCDIR = $I

##########################################################
# You normally will not need to edit anything after this #
##########################################################

# Other directories
ERRFAC = errfac
CLASSES = lib
TEST = test
VECTOR = vector
VECTEST = vectest
EX = ex
SUBDIRS = ${ERRFAC} ${CLASSES} ${TEST} ${VECTOR} ${VECTEST} ${EX}
COMMONFLAGS = CC=${CC} CCDEBUG=${CCDEBUG} CCFLAGS="${CCFLAGS}" I=$I SYS=${SYS} NESTED_TYPES=${NESTED_TYPES} BUGDEFS="${BUGDEFS}" DEBUGDEFS="${DEBUGDEFS}"
 
all: nihclclasses nihcltest vectorclasses vectortest

mi: nihclmiclasses nihclmitest vectormiclasses vectormitest

errorfacility:
	cd ${ERRFAC}; \
		${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS}; \
		${MAKE} -f MAKEFILE ${MFLAGS} install ${COMMONFLAGS} \
		ERRGENDIR=${ERRGENDIR} ERRTABDIR=${ERRTABDIR} ERRINCDIR=${ERRINCDIR} \
		CLIBDIR=${CLIBDIR} LIB_ID=${LIB_ID}

nihclclasses:
	cd ${CLASSES}; ${MAKE} -f MAKEFILE ${MFLAGS} \
		${COMMONFLAGS} MAIN=${MAIN} LNFLAGS=${LNFLAGS}

nihcltest:
	cd ${TEST}; ${MAKE} -f MAKEFILE ${MFLAGS} \
		${COMMONFLAGS}

vectorclasses:
	cd ${VECTOR}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS} generic
	cd ${VECTOR}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS}

vectortest:
	cd ${VECTEST}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS}

nihclmiclasses:
	cd ${CLASSES}; ${MAKE} -f MAKEFILE ${MFLAGS} \
		${COMMONFLAGS} MAIN=${MAIN} LNFLAGS=${LNFLAGS} \
		MI=-DMI NIHCLLIB=libnihclmi.a

nihclmitest:
	cd ${TEST}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS} \
		MI=-DMI NIHCLLIB=../lib/libnihclmi.a

vectormiclasses:
	cd ${VECTOR}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS} \
		MI=-DMI NIHVECLIB=nihclvecmi.a generic
	cd ${VECTOR}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS} \
		MI=-DMI NIHVECLIB=nihclvecmi.a

vectormitest:
	cd ${VECTEST}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS} \
		MI=-DMI NIHCLLIB=../lib/libnihclmi.a NIHVECLIB=../vector/nihclvecmi.a

verify:
	cd ${TEST}; verify
	cd  ${VECTEST}; verify

install:
	for i in ${CLASSES} ${VECTOR}; do \
		(echo $$i; cd $$i; ${MAKE} -f MAKEFILE ${MFLAGS} install \
		NIHCLLIBDIR=${NIHCLLIBDIR} NIHCLINCDIR=${NIHCLINCDIR} \
		); done

examples:
	cd ${EX}; ${MAKE} -f MAKEFILE ${MFLAGS} ${COMMONFLAGS}

exverify:
	cd ${EX}; verify

cleantest:
	cd test; make -f MAKEFILE clean
	cd vectest; make -f MAKEFILE clean

clean:
	for i in ${SUBDIRS}; do \
		(echo $$i; cd $$i; ${MAKE} -f MAKEFILE ${MFLAGS} clean); done

newdistribution:
	-mkdir new-distribution
	rm -rf share/Xfiles
	echo ./RCS >>Xfiles
	cd share; for i in ${SUBDIRS} doc info; do \
		echo ./$$i/RCS >>Xfiles; \
		echo ./$$i/attic >>Xfiles; \
		echo ./$$i/core >>Xfiles; \
	done
	cd share; tar cfX - Xfiles .  | (cd ../new-distribution;tar xvf -)
	(cd new-distribution; make clean; rm -r Xfiles; cd ..)

tape:
	tar cvf /dev/rmt0 -C distribution .

cpiotape:
	find distribution -depth -print | cpio -ocv >/dev/rmt0

cartridge:
	tar cvf /dev/rst0 -C distribution .
