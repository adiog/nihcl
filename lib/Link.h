#ifndef	LINK_H
#define	LINK_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Link.h,v 3.0 90/05/20 00:20:02 kgorlen Rel $*/

/* Link.h -- declarations for singly-linked list element

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

$Log:	Link.h,v $
 * Revision 3.0  90/05/20  00:20:02  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Object.h"

class LinkedList;

class Link: public VIRTUAL Object {	// abstract class
	DECLARE_MEMBERS(Link);
	Link* next;			// pointer to next Link or nil 
	static Link *const nilLink;	// end of list marker
	friend LinkedList;
protected:
	Link()				{ next = NULL; }
	Link(Link* nextlink)		{ next = nextlink; }
	Link(const Link&)		{ next = NULL; }
public:
	~Link();
	Link* nextLink() const		{ return next; }
	Link* nextLink(Link* nextlink)	{ next = nextlink; return next; }
	bool isListEnd() const		{ return this == nilLink; }
	virtual int compare(const Object&) const = 0;
	virtual Object* copy() const;	// deepCopy()
	virtual void deepenShallowCopy();
	virtual unsigned hash() const = 0;
	virtual bool isEqual(const Object&) const = 0;
	virtual void printOn(ostream& strm =cout) const = 0;
};

#endif
