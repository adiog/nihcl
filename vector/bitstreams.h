#ifndef	BITSTREAMS_H
#define	BITSTREAMS_H

/* bitstreams.h -- Utility functions for manipulating bit streams

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
	Internet: keith%nih-csl@ncifcrf.gov

Function:
	
Modification History:

$Log:	bitstreams.h,v $
 * Revision 3.0  90/05/16  23:00:46  kgorlen
 * Release for 1st edition.
 * 
 * Revision 2.206  90/05/13  22:06:52  kgorlen
 * Pre-release.
 * 
 * Revision 2.204  89/10/08  09:43:04  keith
 * Pre-release
 * 
 * Revision 2.203  89/08/14  12:39:21  ted
 * Removed register decl's
 * 
 * Revision 2.202  89/06/28  23:33:59  keith
 * Base revision for AT&T C++ R2.0 release (Cycle 20)
 * 
 * Revision 2.201.1.2  89/06/28  22:45:06  keith
 * Replace ambiguous operator bitVecByte*() with pt().
 * 
 * Revision 2.201.1.1  89/06/19  21:50:56  keith
 * Base revision for R2.0 Cycle 18.
 * 
 * Revision 2.201  89/05/12  13:46:47  keith
 * Release for R2.0 Beta test.
 * 
 * Revision 2.200  89/05/03  23:36:16  keith
 * Utilize abstract classes.
 * 
 * Revision 2.122  89/05/03  23:33:27  keith
 * 
 * 
 * Revision 2.121  89/04/25  13:33:48  keith
 * Base revision for C++ R1.2.1 compatible version.
 * 
 * Revision 2.0  88/03/29  21:56:39  keith
 * Version 2 Release 2
 * 
 * Revision 1.1  88/01/17  09:47:13  keith
 * Initial revision
 * 
	
*/
#include "BitVec.h"

class BitVecIstream : public NIHCL {
	const bitVecByte* p;	// pointer to current byte
	unsigned i;		// current bit index
public:
	BitVecIstream(const BitVec& B)	{ p = B.pt();  i = 0; }
	operator bool() const 	{ return (p[i>>3] >> (i&7)) & 1; }
	void operator++()	{ i++; }
};

class BitVecOstream : public NIHCL {
	bitVecByte* p;		// pointer to current byte
	unsigned i;		// current bit index
	BitVecOstream(BitVec& B)	{ p = B.pt();  B = 0;  i = 0; }
	void operator<<(bool b) { if (b) p[i>>3] |= 1 << (i&7);  i++; }
	void operator++()	{ i++; }
	friend BitVec;
	friend BitSlice;
	friend BitPick;
	friend BitSlct;
};

class BitSliceIstream : public NIHCL {
	bitVecByte* p;		// pointer to current byte
	unsigned i;		// current bit index
	int k;			// stride
public:
	BitSliceIstream(const BitSlice& s)	{ p = s.V->pt();  i = s.pos();  k = s.stride(); }
	operator bool()	{ 
		bool b = (p[i>>3] >> (i&7)) & 1;
		i += k;
		return b;
	}
};

class BitSliceOstream : public NIHCL {
	bitVecByte* p;		// pointer to current byte
	unsigned i;		// current bit index
	int k;			// stride
	BitSliceOstream(BitSlice& s)	{ p = s.V->pt();  i = s.pos();  k = s.stride(); }
	void operator<<(bool b) {
		bitVecByte* q = &p[i>>3];
		bitVecByte m = 1 << (i&7);
		if (b) *q |= m;
		else *q &= ~m;
		i += k;
	}
	friend BitVec;
	friend BitSlice;
	friend BitPick;
	friend BitSlct;
};

class BitPickIstream : public NIHCL {
	const BitVec* V;	// pointer to input BitVec
	const int* p;		// pointer to current index element
public:
	BitPickIstream(const BitPick& s)  { V = s.V;  p = (*s.X).pt(); }
	operator bool() 	{ return (*V)[*p++]; }
};

class BitPickOstream : public NIHCL {
	BitVec* V;		// pointer to input BitVec
	const int* p;		// pointer to current index element
	BitPickOstream(BitPick& s)	{ V = s.V;  p = s.X->pt(); }
	void operator<<(bool b) { (*V)[*p++] = b; }
	friend BitVec;
	friend BitSlice;
	friend BitPick;
	friend BitSlct;
};

#endif
