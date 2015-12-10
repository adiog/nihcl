// VehicleQ.c -- Vehicle Queue LinkedList

#include "VehicleQ.h"
#include "QLink.h"
#include "nihclIO.h"

#define THIS    VehicleQ
#define BASE    LinkedList
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(VehicleQ,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/VehicleQ.c,v 3.0 90/05/15 22:44:11 kgorlen Rel $",NULL,NULL);

Link& VehicleQ::linkCastdown(Object& p) const
{
    return QLink::castdown(p);
}

void VehicleQ::addVehicle(QLink& l) { add(l); }

void VehicleQ::removeVehicle(QLink& l)  { remove(l); }

VehicleQ::VehicleQ(OIOin& strm) :
    Object(strm),
    LinkedList()
{
    unsigned n;
    strm >> n;
    while (n--) add(*QLink::readFrom(strm));
}

VehicleQ::VehicleQ(OIOifd& fd) :
    Object(fd),
    LinkedList()
{
    unsigned n;
    fd >> n;
    while (n--) add(*QLink::readFrom(fd));
}
