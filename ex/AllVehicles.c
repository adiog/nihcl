// AllVehicles.c -- LinkedList of all Vehicles

#include "AllVehicles.h"
#include "AllLink.h"
#include "nihclIO.h"

#define THIS    AllVehicles
#define BASE    LinkedList
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(AllVehicles,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AllVehicles.c,v 3.0 90/05/15 22:43:14 kgorlen Rel $",NULL,NULL);

Link& AllVehicles::linkCastdown(Object& p) const
{
    return AllLink::castdown(p);
}

void AllVehicles::addVehicle(AllLink& l)    { add(l); }

void AllVehicles::removeVehicle(AllLink& l) { remove(l); }

AllVehicles::AllVehicles(OIOin& strm) :
    Object(strm),
    LinkedList()
{
    unsigned n;
    strm >> n;
    while (n--) AllLink::readFrom(strm);
}

AllVehicles::AllVehicles(OIOifd& fd) :
    Object(fd),
    LinkedList()
{
    unsigned n;
    fd >> n;
    while (n--) AllLink::readFrom(fd);
}
