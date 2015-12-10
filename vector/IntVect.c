/* IntVect.c -- Data type-specific functions for class IntVec

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

Function:
	
Data type -specific functions for class IntVec.

Modification History:

$Log:	IntVect.c,v $
 * Revision 3.0  90/05/16  23:00:34  kgorlen
 * Release for 1st edition.
 * 
*/

#include "IntVec.h"
#include "nihclconfig.h"
#include "nihclIO.h"
#include <iomanip.h>
#include <libc.h>

#define	THIS	IntVec
#define	BASE	Vector

static int typeCmp(const void* a, const void* b)
{
	return *(const int*)a-*(const int*)b;
}

void THIS::sort()
{
	qsort(v,n,sizeof(THIS),typeCmp);
}

unsigned THIS::hash() const
{
	unsigned h = n;
	unsigned i = n;
	int* vv = v;
	while (i--) h ^= (unsigned)*vv++;
	return h;
}

void THIS::printOn(ostream& strm) const
{
	for (int i=0; i<n; i++) {
		if (i>0 && (i%8 == 0)) strm << "\n\t";
		strm << setw(10) << dec << v[i];
	}
}

void THIS::scanFrom(istream& strm)
{
	extern const int NIHCL_NYET;
	setError(NIHCL_NYET,DEFAULT,className(),"scanFrom");
}
