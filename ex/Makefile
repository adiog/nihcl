# $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Makefile,v 3.0 90/05/20 21:05:15 kgorlen Rel $
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

NIHCLINCDIR = /usr/include/nihcl
NIHCLLIBDIR = /usr/local/lib
NIHCLVECINCDIR = ${NIHCLINCDIR}
NIHCLLIB = ${NIHCLLIBDIR}/libnihcl.a
NIHCLMILIB = ${NIHCLLIBDIR}/libnihclmi.a
NIHCLVECLIB = ${NIHCLLIBDIR}/libnihclvec.a

CFLAGS = -I${NIHCLINCDIR} ${CCDEBUG} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS}
LFLAGS = -lm ${CCDEBUG}

include progs.all
include classes.all

.SUFFIXES: ..c .s .C
.c:
	$(CC) $(CFLAGS) $< -o $* $(LFLAGS)
.c.o:
	$(CC) $(CFLAGS) -c $<
.C.o:
	$(CC) $(CFLAGS) -c $<
.c..c:
	${CC} ${CFLAGS} +i -c $<
.c.s:
	${CC} ${CFLAGS} +i -S $<

all:${CLASSES} ${PROGS} ${SUBDIRS}

# C program to add ints
ex2-1.o: ex2-1.c
	cc ${CCDEBUG} -c $<

ex2-1: $$@.o
	cc $@.o -o $@ ${LFLAGS}

# C program to add multiple-precision integers using mp library
ex2-2.o: ex2-2.c
	cc ${CCDEBUG} -c $<

ex2-2: $$@.o
	cc $@.o -o $@ -lmp ${LFLAGS}

# C++ program to add instances of class BigInt
ex2-3: $$@.o BigInt.o
	$(CC) $@.o -o $@ BigInt.o ${LFLAGS}

# Writing to the standard output stream
ex5-1: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Reading from the standard input stream
ex5-2: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Writing a BigInt to the standard output
ex5-3: $$@.o BigInt.o
	$(CC) $@.o -o $@ BigInt.o ${LFLAGS}

# Extending stream I/O for class BigInt
ex5-4: $$@.o BigInt.o
	$(CC) $@.o -o $@ BigInt.o ${LFLAGS}

# Opening a stream for an output file
ex5-5: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# String substitution
ex5-6: $$@.o ExString.o
	$(CC) $@.o -o $@ ExString.o ${LFLAGS}

# Find dates of working days
ex5-7: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Vector operations
ex5-8.o: ex5-8.c
	$(CC) $(CFLAGS) -I${NIHCLVECINCDIR} -c $*.c

ex5-8: $$@.o ${NIHCLLIB} ${NIHCLVECLIB}
	$(CC) $@.o -o $@ ${NIHCLVECLIB} ${NIHCLLIB} ${LFLAGS}

# Matrix algebra with Class Matrix
ex5-9: $$@.o Matrix.o
	$(CC) $@.o -o $@ Matrix.o ${LFLAGS}

# One dimensional automatic derivatives with class AutoDeriv
ex5-10: $$@.o AutoDeriv.o
	$(CC) $@.o -o $@ AutoDeriv.o ${LFLAGS}

# Newton's method with Partial automatic derivatives
ex5-11: $$@.o ArrayPartial.o Partial.o Matrix.o
	$(CC) $@.o -o $@ ArrayPartial.o Partial.o Matrix.o ${LFLAGS}

# Geometry class hierarchy
ex6-1: $$@.o 
	$(CC) $@.o -o $@ ${LFLAGS}

# Improved geometry class hierarchy
ex6-2: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Order of construction of base and member classes
ex6-3: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Calling a virtual function from a base class constructor
ex6-4: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Geometry class hierarchy using NIH class library
ex7-1: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Improved geometry class hierarchy using NIH class library
ex7-2: $$@.o Circle.o Line.o Picture.o Shape.o ${NIHCLLIB}
	$(CC) $@.o Circle.o Line.o Picture.o Shape.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Object I/O readFrom()
ex7-3: $$@.o Circle.o Line.o Picture.o Shape.o ${NIHCLLIB}
	$(CC) $@.o Circle.o Line.o Picture.o Shape.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Description of a Patient object
ex8-1: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Use of an Iterator with container for objects of unknown class
ex8-2: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Nested Iterators
ex8-3: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Incorrectly modifying a container during iteration
ex8-4: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Modifying a container during iteration
ex8-5: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Sequential access to Objects in an OrderedCltn
ex8-6: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Sorting Patient records by name
ex8-7: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Sorting Patient records with a KeySortCltn
ex8-8: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Sorting on Multiple Keys with ArrayOb and KeySortCltn
ex8-9: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Linking into a LinkedList
ex8-10: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Test if date falls on a weekday
ex8-11: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Binary Set operators
ex8-12: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Comparison of classes Set and IdentSet
ex8-13: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  A Dictionary of Patient records keyed by name
ex8-14: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Comparison of classes Dictionary and IdentDict
ex8-15: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

#  Property list
ex8-16: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o Patient.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Class ArrayOb example
ex9-1: $$@.o ArrayOb.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Incorrect handling of member pointers to class instances
ex9-2: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Correct handling of member pointers to class instances
ex9-3: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Virtual inline function calls
ex9-4: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Variations of isEqual()
ex10-1K.o: ex10-1K.c
	$(CC) $(CFLAGS) -c -DKINDOF $*.c

ex10-1S.o: ex10-1S.c
	$(CC) $(CFLAGS) -c -DSTRICT $*.c

ex10-1SK.o: ex10-1SK.c
	$(CC) $(CFLAGS) -c -DSTRICT -DKINDOF $*.c

ex10-1: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

ex10-1K: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

ex10-1S: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

ex10-1SK: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Scheduling lightweight processes in the NIH class library
ex11-1: $$@.o
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Managing N resources with a Semaphore
ex11-2: $$@.o
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Protecting a critical section of code with an AutoSignal
ex11-3: $$@.o
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Communication between lightweight processes with a SharedQueue
ex11-4: $$@.o
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Class Vehicle with multiple links
ex13-1: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Improved vehicle linked lists
ex13-2: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Virtual functions and multiple inheritance
ex13-3: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Class AmphibiousVehicle with virtual base class
ex13-4: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Virtual base classes and virtual functions
ex13-5: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Order of construction of multiple base, virtual base, and member classes
ex13-6: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Calling a virtual function from a base class constructor
ex13-7: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# Static method for avoiding undesired multiple calls to member functions of virtual base classes
ex13-8: $$@.o
	$(CC) $@.o -o $@ ${LFLAGS}

# MI with the NIH Class Library

VEHICLEOBJS = AllLink.o AllVehicles.o AmphibVhcl.o DrawBridgeQ.o LandVhcl.o QLink.o StopLightQ.o Vehicle.o VehicleQ.o WaterVhcl.o

# Hack to make stdarg work on sparc

Vehicle.o: Vehicle.c
#	${CC} ${CFLAGS} -F -c Vehicle.c | sed -e 's/__0__builtin/__builtin/g' >Vehicle..c
	${CC} -I${NIHCLINCDIR} ${CCFLAGS} ${NESTED_TYPES} ${BUGDEFS} ${DEBUGDEFS} -F -c Vehicle.c | sed -e 's/__0__builtin/__builtin/g' >Vehicle..c
	cc ${CCDEBUG} -c -o Vehicle.o Vehicle..c
	rm Vehicle..c

ex13-9: $$@.o ${VEHICLEOBJS} ${NIHCLMILIB}
	$(CC) $@.o -o $@ ${VEHICLEOBJS} ${NIHCLMILIB} ${LFLAGS}

# MI and Object I/O readFrom()
ex13-10: $$@.o ${VEHICLEOBJS} ${NIHCLMILIB}
	$(CC) $@.o -o $@ ${VEHICLEOBJS} ${NIHCLMILIB} ${LFLAGS}

# Limitation of Object I/O
ex13-11: $$@.o ${VEHICLEOBJS} ${NIHCLMILIB}
	$(CC) $@.o -o $@ ${VEHICLEOBJS} ${NIHCLMILIB} ${LFLAGS}

# Exception handling in the NIH Class Library
ex14-1: $$@.o ${NIHCLLIB}
	$(CC) $@.o -o $@ ${NIHCLLIB} ${LFLAGS}

# Counted pointers
ex14-2: $$@.o Patient.o ${NIHCLLIB}
	$(CC) $@.o -o $@ Patient.o ${NIHCLLIB} ${LFLAGS}

depend:
	echo 'PROGS =' [a-z]*.c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1#g' >progs.all
	echo 'CLASSES =' [A-Z]*.c | sed -e 's#\([a-zA-Z0-9]*\)\.c#\1.o#g' >classes.all
	touch make.tdep
	makedepend -I$I -I${NIHCLINCDIR} -I${NIHCLVECINCDIR} -f make.tdep -- ${CFLAGS} -- *.c
	sed -e 's#${NIHCLINCDIR}/#$${NIHCLINCDIR}/#g' make.tdep | sed -e 's#${NIHCLVECINCDIR}/#$${NIHCLVECINCDIR}/#g' | sed -e 's# $I/[^ 	$$]*##g' | sed -e 's# /usr/include/[^  $$]*##g' | sed -e '/:[  ]*$$/d' >make.dep
	rm make.tdep

clean:
	-rm -f *.o $(PROGS) *..c *..s core

include make.dep
