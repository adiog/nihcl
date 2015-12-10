/* FloatVect.c -- Data type-specific functions for class FloatVec

Author:
	Tom Keffer
	School of Oceanography, WB-10
	Univ. of Washington
	Seattle, WA 98195
	(206) 543-6455

	Internet: keffer@sperm.ocean.washington.edu
	uucp:     uw-beaver!sperm.ocean.washington.edu!keffer
	BITNET:   keffer%sperm.ocean.washington.edu@UWAVM
	Telemail: T.KEFFER/OMNET	 

Copied and modified from Gorlen's DoubleVect.c.

Function:
	
Data type -specific functions for class FloatVec.

Modification History:

$Log:	FloatVect.c,v $
 * Revision 3.0  90/05/16  23:00:32  kgorlen
 * Release for 1st edition.
 * 
*/

#include "FloatVec.h"
#include "DoubleVec.h"
#include "nihclconfig.h"
#include <iomanip.h>
#include <libc.h>

#define	THIS	FloatVec
#define	BASE	Vector

// Conversion from double to float.  Added by tk.
FloatVec::FloatVec(const DoubleVec& dv) :
       BASE(dv.length())
{
  v = NULL;
  if(n){
    v = new float[n];
    float* fp = v;
    const double* dp = dv.pt();
    unsigned i = n;
    while(i--) *fp++ = float(*dp++);
  }
}

static int typeCmp(const void* a, const void* b)
{
	float t = (const float*)a-(const float*)b;
	if (t < 0) return -1;
	if (t > 0) return 1;
	return 0;
}

void THIS::sort()
{
	qsort(v,n,sizeof(float),typeCmp);
}

unsigned THIS::hash() const
{
	unsigned h = n;
#ifdef LOG2_INT
	unsigned i = n*sizeof(float) >> LOG2_INT;
#else
	unsigned i = n*sizeof(float)/sizeof(int);
#endif
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
	seterror(NIHCL_NYET,DEFAULT,className(),"scanFrom");
}
