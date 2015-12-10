// Vehicle.c -- Abstract base class for various kinds of Vehicles

#include "Vehicle.h"
#include "AllVehicles.h"
#include "VehicleQ.h"
#include "OrderedCltn.h"
#include "nihclIO.h"
#include "OIOnih.h"
#include <fstream.h>
#include <stdarg.h>

#define THIS    Vehicle
#define BASE_CLASSES AllLink::desc(),QLink::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS_MI(Vehicle,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Vehicle.c,v 3.0 90/05/15 22:44:08 kgorlen Rel $",NULL,NULL);

AllVehicles Vehicle::allVehicles;
IdentSet Vehicle::v;

void* Vehicle::_castdown(const Class& target) const
{
    if (&target == desc()) return (void*)this;
    void* p = AllLink::_castdown(target);
    void* q = p;
    if (p = QLink::_castdown(target)) ambigCheck(p,q,target);
    return q;
}

Vehicle::Vehicle(float h, float l)
{
    id = allVehicles.size()+1;          // assign an ID number
    height = h; length = l;
    allVehicles.addVehicle(*this);      // add to list of
                                        // all Vehicles
}

Vehicle::~Vehicle()
{
    allVehicles.removeVehicle(*this);   // remove from list of
                                        // all Vehicles
}

bool Vehicle::operator==(const Vehicle& v) const
{
    return id == v.id;
}

int Vehicle::compare(const Object& v) const
{
    assertArgSpecies(v,classDesc,"compare");
    return id - castdown(v).id;
}

void Vehicle::deepenShallowCopy()
{
    AllLink::deepenShallowCopy();
    QLink::deepenShallowCopy();
    allVehicles.addVehicle(*this);  // add to list of all Vehicles
}

unsigned Vehicle::hash() const  { return id; }

bool Vehicle::isEqual(const Object& v) const
{
    return v.isSpecies(classDesc) && *this == castdown(v);
}

void Vehicle::_printOn(ostream& strm) const
{
    if (v.includes(*(Object*)(void*)this)) return;
                                      // members already printed
    v.add(*(Object*)(void*)this);
    strm << '#' << id << " height " << height << "  length "
        << length;
}

void Vehicle::printOn(ostream& strm) const
{
    v.removeAll();
    _printOn(strm);
}

Vehicle::Vehicle(OIOin& strm) :
    Object(strm),
    AllLink(strm),
    QLink(strm)
{
    strm >> id >> height >> length;
    allVehicles.addVehicle(*this);  // add to list of all Vehicles
}

void Vehicle::storer(OIOout& strm) const
{
    AllLink::storer(strm);
    QLink::storer(strm);
    strm << id << height << length;
}

Vehicle::Vehicle(OIOifd& fd) :
    Object(fd),
    AllLink(fd),
    QLink(fd)
{
    fd >> id >> height >> length;
    allVehicles.addVehicle(*this);  // add to list of all Vehicles
}

void Vehicle::storer(OIOofd& fd) const
{
    AllLink::storer(fd);
    QLink::storer(fd);
    fd << id << height << length;
}

void Vehicle::printAll(ostream& strm)
{
    allVehicles.printOn(strm);
}

#ifdef sparc
// Use magic name to make stdarg work
#define fname __builtin_va_alist
#endif

void Vehicle::saveQueues(const char* fname, ...)
{
    ofstream out(fname,ios::out,0664);  // UNIX protection
                                        // mode 0664
    if (out.fail()) {
        cerr << "Failed to open " << fname << endl;
        exit(1);
    }
    OrderedCltn allQueues;
    allQueues.add(allVehicles);     // allVehicles is allQueues[0]
    va_list ap;
    va_start(ap, fname);
    VehicleQ* q;
    while (q = va_arg(ap, VehicleQ*)) allQueues.add(*q);
    va_end(ap);
    allQueues.storeOn(OIOnihout(out));
}
