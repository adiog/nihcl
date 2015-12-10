# $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/doc/RCS/Makefile,v 3.0 90/05/23 09:34:49 kgorlen Rel $

.SUFFIXES: .nihcl .tr .ps
.nihcl.tr:
	ezprint -t $*.nihcl | soelim >$@
.tr.ps:
	psroff -t $*.tr >$@

DOCS = ../README readme.ps ../INSTALL install.ps

all: ${DOCS}

../README: readme.tr
	-chmod ug+w $@
	nroff $? | col -b >$@
	chmod -w $@

../INSTALL: install.tr
	-chmod ug+w $@
	nroff $? | col -b >$@
	chmod -w $@

clean:
	rm -f ${DOCS} readme.tr install.tr
