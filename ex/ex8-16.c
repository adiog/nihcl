// ex-16.c -- Property list

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-16.c,v 3.0 90/05/15 22:46:13 kgorlen Rel $

#include "IdentDict.h"
#include "Dictionary.h"
#include "String.h"
#include "Date.h"
#include "Patient.h"

class Property: public NIHCL {
    static IdentDict prop;      // object property lists
public:
    static Object* add(Object& owner, String& name, Object& value);
    static Object* get(const Object& owner, const String& name);
};

IdentDict Property::prop;

Object* Property::add(
    Object& owner,      // object to receive property
    String& name,       // name of property
    Object& value)      // property value
{
    Object* oldvalue = &value;
    Dictionary* d;
    if (!prop.includesKey(owner)) {
        d = new Dictionary;
        d->addAssoc(*new String(name),value);
        prop.addAssoc(owner,*d);
    }
    else {
        d = (Dictionary*)prop.atKey(owner);
        if (d->includesKey(name))
            oldvalue = d->atKey(name,value);
        else d->addAssoc(*new String(name),value);
    }
    return oldvalue;
}

Object* Property::get(
    const Object& owner,// object with property
    const String& name) // name of property
{
    if (!prop.includesKey(owner)) return Object::nil;
    Dictionary* d = (Dictionary*)prop.atKey(owner);
    if (d->includesKey(name)) return d->atKey(name);
    else return Object::nil;
}

main()
{
// First patient
    Patient p1("Fried Harry I.","987-65-4321",22221);
    Property::add(p1,
        *new String("admission date"),*new Date(10,"Mar",86));
    Property::add(p1,
        *new String("complaint"),*new String("fever"));

// Second patient
    Patient p2("Chavez Maria G.","444-555-6666",22223);
    Property::add(p2,
        *new String("admission date"),*new Date(20,"Mar",86));
    Property::add(p2,
        *new String("complaint"),*new String("broken leg"));

// Print some properties of Patient objects
    cout << *Property::get(p1,"admission date") << endl;
    cout << *Property::get(p1,"complaint") << endl;
    cout << *Property::get(p2,"admission date") << endl;
// Non-existent property
    cout << *Property::get(p2,"birthdate") << endl;
}
