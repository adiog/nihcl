#ifndef	BYTEVEC_H
#define	BYTEVEC_H

/* ByteVec.h -- Unsigned Character Vectors

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
	Internet:tpersky@alw.nih.gov

Modification History:

$Log:	ByteVec.h,v $
 * Revision 3.0  90/05/16  23:00:27  kgorlen
 * Release for 1st edition.
 * 
*/
#include "Vector.h"
#include "BitVec.h"
#include "IntVec.h"

typedef unsigned char bytevecbyte;

class ByteSlice;
class BytePick;
class ByteSlct;

class ByteVec : public Vector {
	DECLARE_MEMBERS(ByteVec);
	bytevecbyte* v;		// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	ByteVec(unsigned len =0);
	ByteVec(unsigned len, bytevecbyte from, bytevecbyte by =1);
	ByteVec(const bytevecbyte*, unsigned len);
	ByteVec(const ByteVec&);
	ByteVec(const ByteSlice&);
	~ByteVec()			{ delete v; }
	ByteSlice operator()(int pos, unsigned lgt, int stride =1);
	const ByteSlice operator()(int pos, unsigned lgt, int stride =1) const;
	bytevecbyte* pt()		{ return v; }
	const bytevecbyte* pt() const	{ return v; }
	operator ByteSlice();
	operator const ByteSlice() const;
	operator DoubleVec();
//	operator LongVec();
	bytevecbyte& operator[](int i) {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	const bytevecbyte& operator[](int i) const {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	bytevecbyte& operator()(int i)		    { return v[i]; }
	const bytevecbyte& operator()(int i) const  { return v[i]; }
	BytePick operator[](const IntVec&);
	const BytePick operator[](const IntVec&) const;
	ByteSlct operator[](const BitVec&);
	const ByteSlct operator[](const BitVec&) const;
	void /*ByteVec::*/operator=(const ByteVec&);
	void /*ByteVec::*/operator=(const ByteSlice&);
	void /*ByteVec::*/operator=(const ByteSlct&);
	void /*ByteVec::*/operator=(const BytePick&);
	void /*ByteVec::*/operator=(bytevecbyte);
	void /*ByteVec::*/lengthErr(const ByteSlice&) const;
	void selectErr(const BitVec&) const;
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void scanFrom(istream& strm);
	virtual void sort();
	virtual const Class* species() const;
};

class TempByteVec : public ByteVec {
	friend ByteSlice;
	friend BytePick;
	friend ByteSlct;
	TempByteVec(unsigned len =0) : ByteVec(len) {}
	virtual void free();
};

class ByteSlice : public NIHCL {
	ByteVec* V;	// vector pointer
	bytevecbyte* p;	// slice pointer
	unsigned l;	// slice length
	int k;	// slice stride
	ByteSlice(const ByteVec& v, int pos, unsigned lgt, int stride =1);
	ByteSlice(const ByteVec& v, unsigned lgt) {
		V = &(ByteVec&)v;  p = ((ByteVec&)v).pt();  l = lgt;  k = 1;
	}
	ByteSlice(const ByteSlice&);
	friend ByteVec;
public:
	ByteSlice(const BytePick&);
	ByteSlice(const ByteSlct&);
	~ByteSlice()		{ V->free(); }
	bytevecbyte* pt()		{ return p; }
	const bytevecbyte* pt() const	{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*ByteSlice::*/operator=(const ByteVec&);
	void /*ByteSlice::*/operator=(const BytePick&);
	void /*ByteSlice::*/operator=(const ByteSlct&);
	void /*ByteSlice::*/operator=(const ByteSlice&);
	void /*ByteSlice::*/operator=(bytevecbyte);
	void /*ByteSlice::*/lengthErr(const ByteVec&) const;
	void /*ByteSlice::*/lengthErr(const ByteSlice&) const;
	void /*ByteSlice::*/lengthErr(const IntVec&) const;
	void selectErr(const BitVec&) const;
friend	ByteVec	operator!(const ByteSlice&);
friend	ByteVec	operator~(const ByteSlice&);
friend	ByteVec	operator++(ByteSlice&);
friend	ByteVec	operator--(ByteSlice&);
friend	ByteVec	operator*(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator/(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator%(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator+(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator-(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator&(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator^(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator|(const ByteSlice&,const ByteSlice&);
friend	ByteVec	operator*(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator*(bytevecbyte s,const ByteSlice& V)  { return V*s; }
friend	ByteVec	operator/(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator/(bytevecbyte,const ByteSlice&);
friend	ByteVec	operator%(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator%(bytevecbyte,const ByteSlice&);
friend	ByteVec	operator+(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator+(bytevecbyte s,const ByteSlice& V)  { return V+s; }
friend	ByteVec	operator-(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator-(bytevecbyte,const ByteSlice&);
friend	ByteVec	operator&(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator&(bytevecbyte s,const ByteSlice& V)  { return V&s; }
friend	ByteVec	operator^(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator^(bytevecbyte s,const ByteSlice& V)  { return V^s; }
friend	ByteVec	operator|(const ByteSlice&,bytevecbyte);
friend	ByteVec	operator|(bytevecbyte s,const ByteSlice& V)  { return V|s; }
friend	BitVec	operator<(const ByteSlice&,const ByteSlice&);
friend	BitVec	operator>(const ByteSlice& U,const ByteSlice& V)	{ return V < U; }
friend	BitVec	operator<=(const ByteSlice&,const ByteSlice&);
friend	BitVec	operator>=(const ByteSlice& U,const ByteSlice& V) { return V <= U; }
friend	BitVec	operator==(const ByteSlice&,const ByteSlice&);
friend	BitVec	operator!=(const ByteSlice&,const ByteSlice& V);
friend	BitVec	operator<(const ByteSlice&,bytevecbyte);
friend	BitVec	operator<(bytevecbyte s,const ByteSlice& V)  { return V > s; }
friend	BitVec	operator>(const ByteSlice&,bytevecbyte);
friend	BitVec	operator>(bytevecbyte s,const ByteSlice& V)  { return V < s; }
friend	BitVec	operator<=(const ByteSlice&,bytevecbyte);
friend	BitVec	operator<=(bytevecbyte s,const ByteSlice& V) { return V >= s; }
friend	BitVec	operator>=(const ByteSlice&,bytevecbyte);
friend	BitVec	operator>=(bytevecbyte s,const ByteSlice& V) { return V <= s; }
friend	BitVec	operator==(const ByteSlice&,bytevecbyte);
friend	BitVec	operator==(bytevecbyte s,const ByteSlice& V) { return V == s; }
friend	BitVec	operator!=(const ByteSlice&,bytevecbyte);
friend	BitVec	operator!=(bytevecbyte s,const ByteSlice& V) { return V != s; }
friend	void	operator+=(ByteSlice&,const ByteSlice&);
friend	void	operator+=(ByteSlice&,bytevecbyte);
friend	void	operator-=(ByteSlice&,const ByteSlice&);
friend	void	operator-=(ByteSlice&,bytevecbyte);
friend	void	operator*=(ByteSlice&,const ByteSlice&);
friend	void	operator*=(ByteSlice&,bytevecbyte);
friend	void	operator/=(ByteSlice&,const ByteSlice&);
friend	void	operator/=(ByteSlice&,bytevecbyte);
friend	void	operator%=(ByteSlice&,const ByteSlice&);
friend	void	operator%=(ByteSlice&,bytevecbyte);
friend	void	operator&=(ByteSlice&,const ByteSlice&);
friend	void	operator&=(ByteSlice&,bytevecbyte);
friend	void	operator^=(ByteSlice&,const ByteSlice&);
friend	void	operator^=(ByteSlice&,bytevecbyte);
friend	void	operator|=(ByteSlice&,const ByteSlice&);
friend	void	operator|=(ByteSlice&,bytevecbyte);
friend	ByteVec	cumsum(const ByteSlice&);
friend	ByteVec	delta(const ByteSlice&);
friend	bytevecbyte	dot(const ByteSlice&,const ByteSlice&);
friend	int	max(const ByteSlice&);
friend	int	min(const ByteSlice&);
friend	bytevecbyte	prod(const ByteSlice&);
friend	ByteVec	reverse(const ByteSlice&);
friend	bytevecbyte	sum(const ByteSlice&);
};

class BytePick : public NIHCL {
	ByteVec* V;
	const IntVec* X;
	BytePick(const ByteVec& v,const IntVec& x)	{ V = &(ByteVec&)v;  X = &x; }
	BytePick(const BytePick& s)			{ V = s.V; X = s.X; }
	friend ByteVec;
	friend ByteSlice;
	friend ByteSlct;
public:
	void /*BytePick::*/operator=(const ByteVec&);
	void /*BytePick::*/operator=(const BytePick&);
	void /*BytePick::*/operator=(const ByteSlct&);
	void /*BytePick::*/operator=(const ByteSlice&);
	void /*BytePick::*/operator=(bytevecbyte);
	unsigned length() const	{ return X->length(); }
};

class ByteSlct : public NIHCL {
	ByteVec* V;
	const BitVec* B;
	ByteSlct(const ByteVec& v, const BitVec& b)	{ V = &(ByteVec&)v;  B = &b; }
	ByteSlct(const ByteSlct& s)			{ V = s.V; B = s.B; }
	friend ByteVec;
	friend ByteSlice;
	friend BytePick;
public:
	void /*ByteSlct::*/operator=(const ByteVec&);
	void /*ByteSlct::*/operator=(const BytePick&);
	void /*ByteSlct::*/operator=(const ByteSlct&);
	void /*ByteSlct::*/operator=(const ByteSlice&);
	void /*ByteSlct::*/operator=(bytevecbyte);
	unsigned length() const	{ return B->length(); }
};

inline ByteSlice ByteVec::operator()(int pos, unsigned lgt, int stride)
{
	ByteSlice s(*this,pos,lgt,stride);
	return s;
}

inline const ByteSlice ByteVec::operator()(int pos, unsigned lgt, int stride) const
{
	const ByteSlice s(*this,pos,lgt,stride);
	return s;
}

inline ByteVec::operator ByteSlice()
{
	ByteSlice s(*this,length());
	return s;
}

inline ByteVec::operator const ByteSlice() const
{
	const ByteSlice s(*this,length());
	return s;
}

inline BytePick ByteVec::operator[](const IntVec& I)
{
	return BytePick(*this,I);
}

inline const BytePick ByteVec::operator[](const IntVec& I) const
{
	const BytePick t(*this,I);
	return t;
}

inline ByteSlct ByteVec::operator[](const BitVec& B)
{
	return ByteSlct(*this,B);
}

inline const ByteSlct ByteVec::operator[](const BitVec& B) const
{
	const ByteSlct t(*this,B);
	return t;
}

#endif
