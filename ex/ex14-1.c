// ex14-1.c -- Exception handling in the NIH Class Library

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex14-1.c,v 3.0 90/05/15 22:44:55 kgorlen Rel $

#include "IdentDict.h"
#include "Dictionary.h"
#include "String.h"
#include "Date.h"
#include "Exception.h"
#include "nihclerrs.h"

class Property: public NIHCL {
    static IdentDict prop;      // object property lists
public:
    static Object* add(Object& ob, String& name, Object& value);
    static Object* get(const Object& ob, const String& name);
};

IdentDict Property::prop;

Object* Property::add(
    Object& ob,         // object to receive property
    String& name,       // name of property
    Object& value)      // property value
{
    Object* oldvalue = &value;
    Dictionary* d;
    if (!prop.includesKey(ob)) {
        d = new Dictionary;
        d->addAssoc(*new String(name),value);
        prop.addAssoc(ob,*d);
    }
    else {
        d = (Dictionary*)prop.atKey(ob);
        if (d->includesKey(name))
            oldvalue = d->atKey(name,value);
        else d->addAssoc(*new String(name),value);
    }
    return oldvalue;
}

Object* Property::get(
    const Object& ob,   // object with property
    const String& name) // name of property
{
    RaiseException x(NIHCL__KEYNOTFOUND);
    BEGINX
        return ((Dictionary*)prop.atKey(ob))->atKey(name);
    EXCEPTION
        case NIHCL__KEYNOTFOUND: return Object::nil;
        default: RAISE(EXCEPTION_CODE);
    ENDX
}

main()
{
    String gregory = "person";
    Property::add(gregory,*new String("birthdate"),
                  *new Date(10,"Mar",86));
    Property::add(gregory,*new String("eye-color"),
                  *new String("brown"));
    cout << *Property::get(gregory,"birthdate") << endl;
    cout << *Property::get(gregory,"eye-color") << endl;
    cout << *Property::get(gregory,"weight") << endl;
}
