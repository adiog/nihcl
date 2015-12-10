#ifndef	BITVEC_H
#define	BITVEC_H

/* BitVec.h -- Bit Vectors

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
	Internet:kgorlen@alw.nih.gov

Modification History:

$Log:	BitVec.h,v $
 * Revision 3.0  90/05/16  23:00:22  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Vector.h"

typedef unsigned char bitVecByte;

class BitSlice;
class BitPick;
class BitSlct;
class BitSliceIstream;
class BitSliceOstream;
class BitPickIstream;
class BitPickOstream;

class BitRef : public NIHCL {
	bitVecByte* p;	// pointer to byte containing bit
	bitVecByte m;	// mask for bit
	BitRef(bitVecByte* v, int i) {
		p = v + (i>>3);
		m = 1 << (i&7);
	}
	BitRef(const BitRef& b)	{ p = b.p; m = b.m; }
	friend BitVec;
public:
	operator bool() const	{ return ((*p & m) != 0); }
	bool operator=(bool b) {
		if (b) *p |= m;
		else *p &= ~m;
		return b;
	}
	void operator&=(bool b) { if (!b) *p &= ~m; }
	void operator|=(bool b) { if (b) *p |= m; }
	void operator^=(bool b) { if (b) *p ^= m; }
};

class BitVec : public Vector {
	DECLARE_MEMBERS(BitVec);
	bitVecByte* v;	// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	BitVec(unsigned len =0);
	BitVec(unsigned len, bool init);
	BitVec(const bitVecByte*, unsigned len);
	BitVec(const BitVec&);
	BitVec(const BitSlice&);
	~BitVec()			{ delete v; }
	BitSlice operator()(int pos, unsigned lgt, int stride =1);
	const BitSlice operator()(int pos, unsigned lgt, int stride =1) const;
	bitVecByte* pt()		{ return v; }
	const bitVecByte* pt() const	{ return v; }
	operator BitSlice();
	operator const BitSlice() const;
	BitRef operator[](int i);
	BitRef operator()(int i)		{ return BitRef(v,i); }
	const BitRef operator[](int i) const;
	const BitRef operator()(int i) const	{ return BitRef(v,i); }
	BitPick	operator[](const IntVec&);
	const BitPick operator[](const IntVec&) const;
	BitSlct	operator[](const BitVec&);
	const BitSlct operator[](const BitVec&) const;
	void /*BitVec::*/operator=(const BitVec&);
	void /*BitVec::*/operator=(const BitSlice&);
	void /*BitVec::*/operator=(const BitSlct&);
	void /*BitVec::*/operator=(const BitPick&);
	void /*BitVec::*/operator=(bool);
	unsigned nbytes() const	{ return (n+7) >> 3; }
	void /*BitVec::*/lengthErr(const BitSlice&) const;
	void selectErr(const BitVec&) const;
friend	BitVec	operator!(const BitVec&);
friend	BitVec	operator&(const BitVec&,const BitVec&);
friend	BitVec	operator^(const BitVec&,const BitVec&);
friend	BitVec	operator|(const BitVec&,const BitVec&);
friend	void	operator&=(BitVec&,const BitVec&);
friend	void	operator^=(BitVec&,const BitVec&);
friend	void	operator|=(BitVec&,const BitVec&);
friend	int	sum(const BitVec&);
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void scanFrom(istream& strm);
	virtual const Class* species() const;
};

inline BitRef BitVec::operator[](int i)
{
	if ((unsigned)i >= n) indexRangeErr();
	return BitRef(v,i);
}
	
inline const BitRef BitVec::operator[](int i) const
{
	if ((unsigned)i >= n) indexRangeErr();
	return BitRef(v,i);
}
	
class TempBitVec : public BitVec {
	friend BitSlice;
	friend BitPick;
	friend BitSlct;
	TempBitVec(unsigned len =0) : BitVec(len) {}
	virtual void free() { delete this; }
};

class BitSlice : public NIHCL {
	BitVec*	V;	// vector pointer
	int p;		// slice bit number
	unsigned l;	// slice length
	int k;		// slice stride
	BitSlice(const BitVec& v, int pos, unsigned lgt, int stride =1);
	BitSlice(const BitVec& v, unsigned lgt) {
		V = &(BitVec&)v;  p = 0;  l = lgt;  k = 1;
	}
	BitSlice(const BitSlice&);
	friend BitVec;
	friend BitSliceIstream;
	friend BitSliceOstream;
public:
	BitSlice(const BitPick&);
	BitSlice(const BitSlct&);
	~BitSlice()		{ V->free(); }
	int pos() const		{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*BitSlice::*/operator=(const BitVec&);
	void /*BitSlice::*/operator=(const BitPick&);
	void /*BitSlice::*/operator=(const BitSlct&);
	void /*BitSlice::*/operator=(const BitSlice&);
	void /*BitSlice::*/operator=(bool);
	void /*BitSlice::*/lengthErr(const BitVec&) const;
	void /*BitSlice::*/lengthErr(const BitSlice&) const;
	void /*BitSlice::*/lengthErr(const IntVec&) const;
	void selectErr(const BitVec&) const;
friend	BitVec	operator!(const BitSlice&);
friend	BitVec	operator&(const BitSlice&,const BitSlice&);
friend	BitVec	operator^(const BitSlice&,const BitSlice&);
friend	BitVec	operator|(const BitSlice&,const BitSlice&);
friend	void	operator&=(BitSlice&,const BitSlice&);
friend	void	operator^=(BitSlice&,const BitSlice&);
friend	void	operator|=(BitSlice&,const BitSlice&);
friend	BitVec	reverse(const BitSlice&);
friend	int	sum(const BitSlice&);
};

class BitPick : public NIHCL {
	BitVec* V;
	const IntVec* X;
	BitPick(const BitVec& v,const IntVec& x)    { V = &(BitVec&)v;  X = &x; }
	BitPick(const BitPick& s)		    { V = s.V; X = s.X; }
	friend BitVec;
	friend BitSlice;
	friend BitSlct;
	friend BitPickIstream;
	friend BitPickOstream;
public:
	void /*BitPick::*/operator=(const BitVec&);
	void /*BitPick::*/operator=(const BitPick&);
	void /*BitPick::*/operator=(const BitSlct&);
	void /*BitPick::*/operator=(const BitSlice&);
	void /*BitPick::*/operator=(bool);
	unsigned length() const;
};

class BitSlct : public NIHCL {
	BitVec* V;
	const BitVec* B;
	BitSlct(const BitVec& v, const BitVec& b)   { V = &(BitVec&)v;  B = &b; }
	BitSlct(const BitSlct& s)		    { V = s.V; B = s.B; }
	friend BitVec;
	friend BitSlice;
	friend BitPick;
public:
	void /*BitSlct::*/operator=(const BitVec&);
	void /*BitSlct::*/operator=(const BitPick&);
	void /*BitSlct::*/operator=(const BitSlct&);
	void /*BitSlct::*/operator=(const BitSlice&);
	void /*BitSlct::*/operator=(bool);
	unsigned length() const	{ return B->length(); }
};

inline BitSlice BitVec::operator()(int pos, unsigned lgt, int stride)
{
	BitSlice s(*this,pos,lgt,stride);
	return s;
}

inline const BitSlice BitVec::operator()(int pos, unsigned lgt, int stride) const
{
	const BitSlice s(*this,pos,lgt,stride);
	return s;
}

inline BitVec::operator BitSlice()
{
	BitSlice s(*this,length());
	return s;
}

inline BitVec::operator const BitSlice() const
{
	const BitSlice s(*this,length());
	return s;
}

inline BitPick BitVec::operator[](const IntVec& I)
{
	return BitPick(*this,I);
}

inline const BitPick BitVec::operator[](const IntVec& I) const
{
	const BitPick t(*this,I);
	return t;
}

inline BitSlct BitVec::operator[](const BitVec& B)
{
	return BitSlct(*this,B);
}

inline const BitSlct BitVec::operator[](const BitVec& B) const
{
	const BitSlct t(*this,B);
	return t;
}

#endif
