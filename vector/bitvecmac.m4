/* bitvecmac.m4 -- m4 macro templates for BitVecs

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	K. E. Gorlen
	Bg. 12A, Rm. 2017
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892
	Phone: (301) 496-5363
	uucp: uunet!nih-csl!keith
	Internet: keith@alw.nih.gov

Function:
	
Modification History:

$Log:	bitvecmac.m4,v $
Revision 3.0  90/05/16  23:00:47  kgorlen
Release for 1st edition.

Revision 2.206  90/05/13  22:06:59  kgorlen
Pre-release.

Revision 2.204  89/10/08  09:43:16  keith
Pre-release

Revision 2.203  89/08/14  13:13:48  ted
Pre-release

Revision 2.202.1.1  89/08/04  13:35:06  ted
Removed register declarations

Revision 2.203  89/08/04  10:36:43  ted
Removed all register declarations for integers.

Revision 2.202  89/06/28  23:34:01  keith
Base revision for AT&T C++ R2.0 release (Cycle 20)

Revision 2.201.1.2  89/06/28  22:47:28  keith
Change name of 1st argument to BITVECGEN.

Revision 2.201.1.1  89/06/19  21:51:02  keith
Base revision for R2.0 Cycle 18.

Revision 2.201  89/05/12  13:46:52  keith
Release for R2.0 Beta test.

Revision 2.200  89/05/03  23:36:19  keith
Utilize abstract classes.

Revision 2.122  89/05/03  23:33:29  keith


Revision 2.121  89/04/25  13:33:52  keith
Base revision for C++ R1.2.1 compatible version.

Revision 2.0  88/03/29  21:56:45  keith
Version 2 Release 2

Revision 1.1  88/01/17  09:47:26  keith
Initial revision

	
*/

// BITVECGEN(BitVecPt,Length,Condition,Advance)
define(BITVECGEN,
{
	bitVecByte m;
	bitVecByte* bp = $1;
	unsigned i = ($2) >> 3;
	while (i--) {
		m = 0;
		if ($3) m |= 0x01;  $4;
		if ($3) m |= 0x02;  $4;
		if ($3) m |= 0x04;  $4;
		if ($3) m |= 0x08;  $4;
		if ($3) m |= 0x10;  $4;
		if ($3) m |= 0x20;  $4;
		if ($3) m |= 0x40;  $4;
		if ($3) m |= 0x80;  $4;
		*bp++ = m;		 
	}				 
	if ((i = ($2)&7) != 0) {
		m = 0;
		int mm = 1;
		while (i--) {
			if ($3) m |= mm;
			mm <<= 1;
			$4;
		}
		*bp = m;
	};
}
)

// BITVECSCAN(BitVec,Length,Statement)
define(BITVECSCAN,
{
	bitVecByte m;
	const bitVecByte* bp = ($1).pt();
	unsigned i = ($2) >> 3;
	while(i--) {
		m = *bp++;
		if (m&0x01) $3;
		if (m&0x02) $3;
		if (m&0x04) $3;
		if (m&0x08) $3;
		if (m&0x10) $3;
		if (m&0x20) $3;
		if (m&0x40) $3;
		if (m&0x80) $3;
	}	
	m = *bp;
	i = ($2) & 7;
	while (i--) {
		if (m&0x01) $3;
		m >>= 1;
	}
}
)
