// ex13-4.c -- Class AmphibVhcl with virtual base class

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-4.c,v 3.0 90/05/15 22:44:41 kgorlen Rel $

#include <iostream.h>

class Link;

class LinkedList {
    Link* firstLink;    // pointer to first Link of list 
    Link* lastLink;     // pointer to last Link of list 
public:
    LinkedList()        { firstLink = lastLink = 0; }
    Link* add(Link& l);
    virtual void printOn(ostream& strm =cout) const;
};

class Link {
    Link* next;
    friend LinkedList;
public:
    Link()                  { next = 0; }
    Link* nextLink() const  { return next; }
    virtual void printOn(ostream& strm =cout) const =0;
};

Link* LinkedList::add(Link& l)
{
    if (firstLink == 0) firstLink = lastLink = &l;
    else {
        lastLink->next = &l;
        lastLink = &l;
    }
    return &l;
}

void LinkedList::printOn(ostream& strm) const
{
    int n = 0;
    Link* l = firstLink;
    while (l != 0) {
        if (n++ != 0) strm << endl;
        l->printOn(strm);
        l = l->next;
    }
}

//--------------------------------------------

class AllLink: public Link {
protected:
    AllLink() {};
    virtual void printOn(ostream& strm =cout) const =0;
};

class QLink: public Link {
protected:
    QLink() {};
    virtual void printOn(ostream& strm =cout) const =0;
};

class AllVehicles: public LinkedList {
public:
    virtual void addVehicle(AllLink&);
};

void AllVehicles::addVehicle(AllLink& l)    { add(l); }

class VehicleQ: public LinkedList {
public:
    virtual void addVehicle(QLink&);
};

void VehicleQ::addVehicle(QLink& l)     { add(l); }

class Vehicle: public AllLink, public QLink {
    static unsigned vehicleID;
    static AllVehicles allVehicles;
    unsigned id;
    float height;
    float length;
protected:
    Vehicle(float h = 0.0, float l = 0.0) {
        id = ++vehicleID;
        height = h; length = l;
        allVehicles.addVehicle(*this);
    }
public:
    static void printAll(ostream& strm =cout) {
        allVehicles.printOn(strm);
    }
    virtual void printOn(ostream& strm =cout) const;
// ...
};

unsigned Vehicle::vehicleID = 0;
AllVehicles Vehicle::allVehicles;

void Vehicle::printOn(ostream& strm) const
{
    strm << '#' << id << " height " << height << "  length "
        << length;
}

class LandVhcl: public virtual Vehicle {
    unsigned axles;
public:
    LandVhcl(float h, float l, unsigned a =2) : Vehicle(h,l)
        { axles = a; }
    virtual void printOn(ostream& strm =cout) const;
// ...
};

void LandVhcl::printOn(ostream& strm) const
{
    Vehicle::printOn(strm);
    strm << "  axles " << axles;
}

class WaterVhcl: public virtual Vehicle {
    float draft;
public:
    WaterVhcl(float h, float l, float d) : Vehicle(h,l)
        { draft = d; }
    virtual void printOn(ostream& strm =cout) const;
// ...
};

void WaterVhcl::printOn(ostream& strm) const
{
    Vehicle::printOn(strm);
    strm << "  draft " << draft;
}

class AmphibVhcl: public LandVhcl, public WaterVhcl {
public:
    AmphibVhcl(float h, float l, float d, unsigned a=2)
        : Vehicle(h,l), LandVhcl(h,l,a), WaterVhcl(h,l,d) {}
    virtual void printOn(ostream& strm =cout) const;
// ...
};

void AmphibVhcl::printOn(ostream& strm) const
{
    LandVhcl::printOn(strm);
    WaterVhcl::printOn(strm);
}

class StopLightQ: public VehicleQ {
public:
    virtual void addVehicle(LandVhcl&);
};

void StopLightQ::addVehicle(LandVhcl& v)
{
    VehicleQ::addVehicle(v);
}

class DrawBridgeQ: public VehicleQ {
public:
    virtual void addVehicle(WaterVhcl&);
};

void DrawBridgeQ::addVehicle(WaterVhcl& v)
{
    VehicleQ::addVehicle(v);
}

StopLightQ stopLightQ[2];
DrawBridgeQ drawBridgeQ;

main()
{
    stopLightQ[0].addVehicle(*new LandVhcl(4.1, 12.0));
    stopLightQ[1].addVehicle(*new LandVhcl(4.2, 12.0));
    stopLightQ[0].addVehicle(*new LandVhcl(4.3, 12.0));
    stopLightQ[1].addVehicle(*new LandVhcl(4.4, 12.0));
    drawBridgeQ.addVehicle(*new WaterVhcl(21.0, 19.0, 3.5));
    drawBridgeQ.addVehicle(*new WaterVhcl(10.0, 30.0, 2.0));
    stopLightQ[0].addVehicle(*new AmphibVhcl(5.0, 15.0, 3.0));
    drawBridgeQ.addVehicle(*new AmphibVhcl(5.1, 15.0, 3.0));
    cout << "allVehicles:\n"; Vehicle::printAll();
    cout << endl;
    cout << "stopLightQ[0]:\n"; stopLightQ[0].printOn();
    cout << endl;
    cout << "stopLightQ[1]:\n"; stopLightQ[1].printOn();
    cout << endl;
    cout << "drawBridgeQ:\n"; drawBridgeQ.printOn();
    cout << endl;
}
