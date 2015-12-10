// ex13-2.c -- Improved vehicle linked lists

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-2.c,v 3.0 90/05/15 22:44:37 kgorlen Rel $

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
    Link* nextLink()        { return next; }
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
    Link* l = firstLink;
    while (l != 0) {
        l->printOn(strm);  strm << ' ';
        l = l->next;
    }
    cout << endl;
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

void VehicleQ::addVehicle(QLink& l)         { add(l); }

class Vehicle: public AllLink, public QLink {
    static unsigned vehicleID;
    static AllVehicles allVehicles;
    unsigned id;
public:
    Vehicle() {
        id = ++vehicleID;
        allVehicles.addVehicle(*this);
    }
    static void printAll(ostream& strm =cout) {
        allVehicles.printOn(strm);
    }
    virtual void printOn(ostream& strm =cout) const;
};

unsigned Vehicle::vehicleID = 0;
AllVehicles Vehicle::allVehicles;

void Vehicle::printOn(ostream& strm) const
{
    strm << id;
}

VehicleQ stopLightQ[2];

main()
{
    stopLightQ[0].addVehicle(*new Vehicle);
    stopLightQ[1].addVehicle(*new Vehicle);
    stopLightQ[0].addVehicle(*new Vehicle);
    stopLightQ[1].addVehicle(*new Vehicle);
    cout << "allVehicles: "; Vehicle::printAll();
    cout << "stopLightQ[0]: "; stopLightQ[0].printOn();
    cout << "stopLightQ[1]: "; stopLightQ[1].printOn();
}
