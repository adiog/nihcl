// QLink.c -- Link used by AllVehicles LinkedList

#include "QLink.h"
#include "nihclIO.h"

#define THIS    QLink
#define BASE    Link
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(QLink,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/QLink.c,v 3.0 90/05/15 22:44:01 kgorlen Rel $",NULL,NULL);

QLink::QLink(OIOin& strm) : BASE(strm) {}

QLink::QLink(OIOifd& fd) : BASE(fd) {}
