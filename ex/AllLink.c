// AllLink.c -- Link used by AllVehicles LinkedList

#include "AllLink.h"
#include "nihclIO.h"

#define THIS    AllLink
#define BASE    Link
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(AllLink,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AllLink.c,v 3.0 90/05/15 22:43:11 kgorlen Rel $",NULL,NULL);

AllLink::AllLink(OIOin& strm) : BASE(strm) {}

AllLink::AllLink(OIOifd& fd) : BASE(fd) {}
