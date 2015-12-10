#ifndef	VECTOR_H
#define	VECTOR_H

/* Vector.h -- declarations for generic vector objects

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
	May, 1986


Function:


Modification History:

$Log:	Vector.h,v $
 * Revision 3.0  90/05/16  23:00:45  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Object.h"

#include <math.h>

typedef double (*mathFunTy)(double);

class BitVec;
class ByteVec;
class ComplexVec;
class DoubleVec;
class FloatVec;
class IntVec;
class LongVec;
class ShortVec;

class Vector : public VIRTUAL Object {
	DECLARE_MEMBERS(Vector);
protected:
	unsigned n;		// number of elements in vector
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	Vector(unsigned len=0)	{ n = len; }
	unsigned length() const	{ return n; }
	void emptyErr(const char* fname) const;
	virtual unsigned capacity() const;
	virtual void	deepenShallowCopy();	// {}
	virtual void	free();			// {}
	virtual unsigned hash() const = 0;
	virtual bool isEqual(const Object&) const = 0;
	virtual void printOn(ostream& strm =cout) const = 0;
	virtual unsigned size() const;
friend	void lengthErr(const Vector&, const Vector&);
private:			// shouldNotImplement()
	int compare(const Object&) const;
};

#endif
