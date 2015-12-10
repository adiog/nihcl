/* ShortVect.c -- Data type-specific functions for class ShortVec

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
        Ted Persky
	Bg. 12A, Rm. 2031
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892
	Phone: (301) 496-2963
	uucp: uunet!nih-csl!tpersky
	Internet: tpersky@alw.nih.gov

Function:
	
Data type -specific functions for class ShortVec.

Modification History:

$Log:	ShortVect.c,v $
 * Revision 3.0  90/05/16  23:00:40  kgorlen
 * Release for 1st edition.
 * 
*/

#include "ShortVec.h"
#include "nihclconfig.h"
#include "nihclIO.h"
#include <iomanip.h>
#include <libc.h>

#define	THIS	ShortVec
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
	short* vv = v;
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
