#ifndef OIOTBL_H
#define OIOTBL_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/OIOTbl.h,v 3.0 90/05/20 00:20:25 kgorlen Rel $*/

/* OIOTbl.h -- Specification of tables used by storeOn()/readFrom()

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	K. E. Gorlen
	Computer Systems Laboratory, DCRT
	National Institutes of Health
	Bethesda, MD 20892
	July, 1988

Modification History:

$Log:	OIOTbl.h,v $
 * Revision 3.0  90/05/20  00:20:25  kgorlen
 * Release for 1st edition.
 * 
*/

#include "IdentDict.h"
#include "OrderedCltn.h"

class StoreOnTbl : public NIHCL {
	IdentDict d;			// object address => object number
	int objNum;			// last object number used
	OrderedCltn c;			// table of classes stored, indexed by class number
	unsigned short classNum;	// last class number used
public:
	StoreOnTbl(unsigned size =256);
	~StoreOnTbl();
	bool add(const Object&, int& num);
	bool addClass(const Class*, unsigned short& num);
	void addMember(const Object&);
};

class ReadFromTbl : public NIHCL {
	OrderedCltn obs;	// table of objects for readFrom()
	OrderedCltn cls;	// table of classes for readFrom()
public:
	ReadFromTbl(unsigned size =1024);
	int add(Object&);
	int add(const Class*);
	Object* objectAt(int);
	const Class* classAt(int);
};

#endif
