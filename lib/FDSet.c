/* FDSet.c -- Class for manipulating fd_set objects used by select(2)

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
	May, 1989

Modification History:

$Log:	FDSet.c,v $
 * Revision 3.0  90/05/22  10:42:05  kgorlen
 * Release for 1st edition.
 * 
*/

#include "FDSet.h"
#include "nihclIO.h"
#include "nihclconfig.h"
#include <osfcn.h>

#define	THIS	FDSet
#define	BASE	Object
#define	BASE_CLASSES BASE::desc()
#define	MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES Object::desc()

DEFINE_CLASS(FDSet,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/FDSet.c,v 3.0 90/05/22 10:42:05 kgorlen Rel $",NULL,NULL);

unsigned FDSet::dtablesz = getdtablesize();

FDSet FDSet::operator-(const FDSet& a) const
{
	FDSet result;
	register const long* p = (long*)&fs;
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&result.fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) *dst++ = *p++ & ~*q++;
	return result;
}

FDSet FDSet::operator&(const FDSet& a) const
{
	FDSet result;
	register const long* p = (long*)&fs;
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&result.fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) *dst++ = *p++ & *q++;
	return result;
}

FDSet FDSet::operator|(const FDSet& a) const
{
	FDSet result;
	register const long* p = (long*)&fs;
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&result.fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) *dst++ = *p++ | *q++;
	return result;
}

FDSet FDSet::operator^(const FDSet& a) const
{
	FDSet result;
	register const long* p = (long*)&fs;
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&result.fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) *dst++ = *p++ ^ *q++;
	return result;
}

void FDSet::operator-=(const FDSet& a)
{
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) { *dst = *dst & ~*q++; dst++; }
}

void FDSet::operator&=(const FDSet& a)
{
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) { *dst = *dst & *q++; dst++; }
}

void FDSet::operator|=(const FDSet& a)
{
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) { *dst = *dst | *q++; dst++; }
}

void FDSet::operator^=(const FDSet& a)
{
	register const long* q = (long*)&a.fs;
	register long* dst = (long*)&fs;
	unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) { *dst = *dst ^ *q++; dst++; }
}

bool FDSet::isEmpty() const
{
	register const long* p = (long*)&fs;
	register unsigned long n = div_sizeof_long(sizeof(fd_set));
	while (n--) if (*p++ != 0) return NO;
	return YES;
}

const Class* FDSet::species() const
// Return a pointer to the descriptor of the species of this class
{
	return &classDesc;
}

bool FDSet::isEqual(const Object& p) const
// Test two objects for equality
{
	return p.isSpecies(classDesc) && *this==castdown(p);
}

unsigned FDSet::hash() const
{
	register unsigned h = 0;
	register const unsigned* p = (unsigned*)&fs;
	unsigned n = div_sizeof_int(sizeof(fd_set));
	while (n--) h ^= *p++;
	return h;
}

unsigned FDSet::capacity() const
{
	return dtablesz;
}

unsigned FDSet::size() const
{
	register unsigned k = 0;
	register const unsigned char* p = (unsigned char*)&fs;
	unsigned n = sizeof(fs);
	while (n--) k += bitCount(*p++);
	return k;
}

int FDSet::compare(const Object&) const
{
	shouldNotImplement("compare");
	return 0;
}

void FDSet::deepenShallowCopy()
{
}

void FDSet::printOn(ostream& strm) const
{
	unsigned n = dtablesz;
	for (int i = 0, j = 0; i < n; i++) {
		if (isSet(i)) {
			if (j++) strm << ',';
			strm << i;
		}
	}
}

FDSet::FDSet(OIOin& strm)
	: BASE(strm)
{
	zero();
	int n;
	strm >> n;
	while (n--) {
		int i;
		strm >> i;
		set(i);
	}
}

void FDSet::storer(OIOout& strm) const
{
	BASE::storer(strm);
	strm << size();
	for (int i = 0; i<dtablesz; i++) {
		if (isSet(i)) strm << i;
	}
}

FDSet::FDSet(OIOifd& fd)
	: BASE(fd)
{
	fd.get((char*)&fs,sizeof(fs));
}

void FDSet::storer(OIOofd& fd) const
{
	BASE::storer(fd);
	fd.put((const char*)&fs,(unsigned)sizeof(fs));
}
