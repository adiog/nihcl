/* DoubleVect.c -- Data type-specific functions for class DoubleVec

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
	June, 1986

Function:
	
Data type -specific functions for class DoubleVec.

Modification History:

$Log:	DoubleVect.c,v $
 * Revision 3.0  90/05/16  23:00:30  kgorlen
 * Release for 1st edition.
 * 
*/

#include "DoubleVec.h"
#include "FloatVec.h"
#include "nihclconfig.h"
#include "nihclIO.h"
#include <iomanip.h>
#include <libc.h>

#define	THIS	DoubleVec
#define	BASE	Vector

// Conversion from float to double.  Added by tk.
DoubleVec::DoubleVec(const FloatVec& fv) :
       BASE(fv.length())
{
  v = NULL;
  if(n){
    v = new double[n];
    double* dp = v;
    const float* fp = fv.pt();
    unsigned i = n;
    while(i--) *dp++ = double(*fp++);
  }
}

static int typeCmp(const void* a, const void* b)
{
	double t = *(double*)a-*(double*)b;
	if (t < 0) return -1;
	if (t > 0) return 1;
	return 0;
}

void THIS::sort()
{
	qsort(v,n,sizeof(double),typeCmp);
}

unsigned THIS::hash() const
{
	unsigned h = n;
	unsigned i = n*div_sizeof_int(sizeof(double));
	unsigned* vv = (unsigned*)v;
	while (i--) h ^= *vv++;
	return h;
}

void THIS::printOn(ostream& strm) const
{
	for (unsigned i=0; i<n; i++) {
		if (i>0 && (i%6 == 0)) strm << "\n\t";
		strm << setw(13) << setprecision(5) << v[i];
	}
}

void THIS::scanFrom(istream& strm)
{
	extern const int NIHCL_NYET;
	setError(NIHCL_NYET,DEFAULT,className(),"scanFrom");
}
