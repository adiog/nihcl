#ifndef VEHICLE_H
#define VEHICLE_H

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/Vehicle.h,v 3.0 90/05/15 22:44:10 kgorlen Rel $

// Vehicle.h -- Abstract base class for various kinds of Vehicles

#ifndef MI
#define MI
#endif

#include "AllLink.h"
#include "QLink.h"
#include "AllVehicles.h"
#include "IdentSet.h"

class Vehicle: public AllLink, public QLink {
    DECLARE_MEMBERS(Vehicle);
    static AllVehicles allVehicles;
    static IdentSet v;                  // used by printOn()
    unsigned id;
    float height;
    float length;
public:         // static member functions
    static void printAll(ostream& strm =cout);
    static void saveQueues(const char* fname, ...);
protected:      // storer() functions for object I/O
    virtual void storer(OIOofd&) const;
    virtual void storer(OIOout&) const;
protected:
    Vehicle(float h = 0.0, float l = 0.0);
    virtual void _printOn(ostream& strm =cout) const;
public:
    virtual ~Vehicle();
    bool operator==(const Vehicle&) const;
    bool operator!=(const Vehicle& a) const { return !(*this==a); }
    virtual int compare(const Object&) const;
    virtual void deepenShallowCopy();
    virtual unsigned hash() const;
    virtual bool isEqual(const Object&) const;
    virtual void printOn(ostream& strm =cout) const;
};

#endif
