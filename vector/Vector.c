/* Vector.c -- abstract base class for vectors

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
	February, 1987

Function:
	
Modification History:

$Log:	Vector.c,v $
 * Revision 3.0  90/05/16  23:00:44  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Vector.h"
#include "nihclIO.h"

#define	THIS	Vector
#define	BASE	Object
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(Vector,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/vector/RCS/Vector.c,v 3.0 90/05/16 23:00:44 kgorlen Rel $",NULL,NULL);

extern const int NIHCL_RDABSTCLASS;
extern const int NIHCL_VECTOREMPTY;
extern const int NIHCL_VECTORLENGTH;

unsigned Vector::capacity() const   { return n; }

unsigned Vector::size()	const	    { return n; }

void Vector::free() {}	// used by Slice classes to free TempVecs

void Vector::emptyErr(const char* fname) const
{
	setError(NIHCL_VECTOREMPTY,DEFAULT,className(),fname,(int)this);
}

void lengthErr(const Vector& U, const Vector& V)
{
	NIHCL::setError(NIHCL_VECTORLENGTH,DEFAULT,(int)&U,U.className(),U.length(),(int)&V,V.className(),V.length());
}

void Vector::deepenShallowCopy()
// Called by deepCopy() to convert a shallow copy to a deep copy.
{
}

#ifndef BUG_bC2728
// call of pure virtual function OIOin::operator >>() in constructor Vector::Vector()
static unsigned hack(OIOin& strm)	{ unsigned n; strm >> n; return n; }
#endif

Vector::Vector(OIOin& strm)
// Construct an object from istream "strm" at address "where".
	: BASE(strm)
{
#ifndef BUG_bC2728
	n = hack(strm);
#else
// call of pure virtual function OIOin::operator >>() in constructor Vector::Vector()
	strm >> n;
#endif
}

void Vector::storer(OIOout& strm) const
// Store the member variables of this object on ostream "strm".
{
	BASE::storer(strm);
	strm << n;
}

Vector::Vector(OIOifd& fd)
// Construct an object from file descriptor "fd" at address "where".
	: BASE(fd)
{
	fd >> n;
}

void Vector::storer(OIOofd& fd) const
// Store an object on file descriptor "fd".
{
	BASE::storer(fd);
	fd << n;
}

int Vector::compare(const Object&) const
{
	shouldNotImplement("compare");
	return 0;
}
