/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Array_h.m4,v 3.0 90/05/20 00:18:58 kgorlen Rel $*/

/* Array_h.m4 -- template for declarations for generic array objects

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	K. E. Gorlen
	Bg. 12A, Rm. 2033
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892
	Phone: (301) 496-1111
	uucp: uunet!nih-csl!kgorlen
	Internet: kgorlen@alw.nih.gov
	September, 1985

Function:

m4 macro template for the .h files for arrays of the specified
fundamental type: char, int, short, long, unsigned, float, and double.
For example, to generate the declarations for an array of chars:

	echo "ARRAYDECLARE(Arraychar,char,friend SubString;)" | m4 Array.h.m4 - >Arraychar.h

$Log:	Array_h.m4,v $
Revision 3.0  90/05/20  00:18:58  kgorlen
Release for 1st edition.

*/

define(ARRAYDECLARE,
``#ifndef'' $1_H
``#define'' $1_H

``#include'' "Collection.h"
``#include'' <malloc.h>

inline $2* REALLOC($2* ptr, unsigned size)
{
	return ($2*)realloc((char*)ptr,sizeof($2)*size);
}

inline void DELETE($2* ptr) { free((char*)ptr); }

class $1: public Collection {
	DECLARE_MEMBERS($1);
	$2* v;
	unsigned sz;
	void AllocSizeErr() const;
	void IndexRangeErr() const;
// friends go here
	$3
protected:		// storer() functions for object I/O
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	$1(unsigned size =DEFAULT_CAPACITY);
	$1(const $1&);
	~$1();
	$2& elem(int i)			{ return v[i]; }
	const $2& elem(int i) const	{ return v[i]; }
	bool operator!=(const $1& a) const { return !(*this==a); }
	void operator=(const $1&);
	bool operator==(const $1&) const;
	$2& operator[](int i) {
		if ((unsigned)i >= sz) IndexRangeErr();
		return v[i];
	}
	$2 operator[](int i) const {
		if ((unsigned)i >= sz) IndexRangeErr();
		return v[i];
	}
	virtual unsigned capacity() const;
	virtual int compare(const Object&) const;
	virtual void deepenShallowCopy();
	virtual void dumpOn(ostream& strm =cerr) const;
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void removeAll();
	virtual void reSize(unsigned);
	virtual unsigned size() const;
	virtual void sort();
	virtual const Class* species() const;
private:					// shouldNotImplement()
	virtual Object* add(Object&);
	virtual Object*& at(int);
	virtual const Object *const& at(int) const;
	virtual Object* doNext(Iterator&) const;
	virtual unsigned occurrencesOf(const Object&) const;
	virtual Object* remove(const Object&);
};

``#endif''
)
