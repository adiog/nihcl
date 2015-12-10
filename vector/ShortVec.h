#ifndef	SHORTVEC_H
#define	SHORTVEC_H

/* ShortVec.h -- Short Integer Vectors

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

$Log:	ShortVec.h,v $
 * Revision 3.0  90/05/16  23:00:39  kgorlen
 * Release for 1st edition.
 * 
*/
#include "Vector.h"
#include "BitVec.h"
#include "IntVec.h"

class ShortSlice;
class ShortPick;
class ShortSlct;

class ShortVec : public Vector {
	DECLARE_MEMBERS(ShortVec);
	short* v;		// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	ShortVec(unsigned len =0);
	ShortVec(unsigned len, short from, short by =1);
	ShortVec(const short*, unsigned len);
	ShortVec(const ShortVec&);
	ShortVec(const ShortSlice&);
	~ShortVec()			{ delete v; }
	ShortSlice operator()(int pos, unsigned lgt, int stride =1);
	const ShortSlice operator()(int pos, unsigned lgt, int stride =1) const;
	short* pt()		{ return v; }
	const short* pt() const	{ return v; }
	operator ShortSlice();
	operator const ShortSlice() const;
	operator DoubleVec();
//	operator LongVec();
	short& operator[](int i) {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	const short& operator[](int i) const {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	short& operator()(int i)		    { return v[i]; }
	const short& operator()(int i) const  { return v[i]; }
	ShortPick operator[](const IntVec&);
	const ShortPick operator[](const IntVec&) const;
	ShortSlct operator[](const BitVec&);
	const ShortSlct operator[](const BitVec&) const;
	void /*ShortVec::*/operator=(const ShortVec&);
	void /*ShortVec::*/operator=(const ShortSlice&);
	void /*ShortVec::*/operator=(const ShortSlct&);
	void /*ShortVec::*/operator=(const ShortPick&);
	void /*ShortVec::*/operator=(short);
	void /*ShortVec::*/lengthErr(const ShortSlice&) const;
	void selectErr(const BitVec&) const;
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void scanFrom(istream& strm);
	virtual void sort();
	virtual const Class* species() const;
};

class TempShortVec : public ShortVec {
	friend ShortSlice;
	friend ShortPick;
	friend ShortSlct;
	TempShortVec(unsigned len =0) : ShortVec(len) {}
	virtual void free();
};

class ShortSlice : public NIHCL {
	ShortVec* V;	// vector pointer
	short* p;	// slice pointer
	unsigned l;	// slice length
	int k;	// slice stride
	ShortSlice(const ShortVec& v, int pos, unsigned lgt, int stride =1);
	ShortSlice(const ShortVec& v, unsigned lgt) {
		V = &(ShortVec&)v;  p = ((ShortVec&)v).pt();  l = lgt;  k = 1;
	}
	ShortSlice(const ShortSlice&);
	friend ShortVec;
public:
	ShortSlice(const ShortPick&);
	ShortSlice(const ShortSlct&);
	~ShortSlice()		{ V->free(); }
	short* pt()		{ return p; }
	const short* pt() const	{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*ShortSlice::*/operator=(const ShortVec&);
	void /*ShortSlice::*/operator=(const ShortPick&);
	void /*ShortSlice::*/operator=(const ShortSlct&);
	void /*ShortSlice::*/operator=(const ShortSlice&);
	void /*ShortSlice::*/operator=(short);
	void /*ShortSlice::*/lengthErr(const ShortVec&) const;
	void /*ShortSlice::*/lengthErr(const ShortSlice&) const;
	void /*ShortSlice::*/lengthErr(const IntVec&) const;
	void selectErr(const BitVec&) const;
friend	ShortVec	operator-(const ShortSlice&);
friend	ShortVec	operator!(const ShortSlice&);
friend	ShortVec	operator~(const ShortSlice&);
friend	ShortVec	operator++(ShortSlice&);
friend	ShortVec	operator--(ShortSlice&);
friend	ShortVec	operator*(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator/(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator%(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator+(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator-(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator&(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator^(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator|(const ShortSlice&,const ShortSlice&);
friend	ShortVec	operator*(const ShortSlice&,short);
friend	ShortVec	operator*(short s,const ShortSlice& V)  { return V*s; }
friend	ShortVec	operator/(const ShortSlice&,short);
friend	ShortVec	operator/(short,const ShortSlice&);
friend	ShortVec	operator%(const ShortSlice&,short);
friend	ShortVec	operator%(short,const ShortSlice&);
friend	ShortVec	operator+(const ShortSlice&,short);
friend	ShortVec	operator+(short s,const ShortSlice& V)  { return V+s; }
friend	ShortVec	operator-(const ShortSlice&,short);
friend	ShortVec	operator-(short,const ShortSlice&);
friend	ShortVec	operator&(const ShortSlice&,short);
friend	ShortVec	operator&(short s,const ShortSlice& V)  { return V&s; }
friend	ShortVec	operator^(const ShortSlice&,short);
friend	ShortVec	operator^(short s,const ShortSlice& V)  { return V^s; }
friend	ShortVec	operator|(const ShortSlice&,short);
friend	ShortVec	operator|(short s,const ShortSlice& V)  { return V|s; }
friend	BitVec	operator<(const ShortSlice&,const ShortSlice&);
friend	BitVec	operator>(const ShortSlice& U,const ShortSlice& V)	{ return V < U; }
friend	BitVec	operator<=(const ShortSlice&,const ShortSlice&);
friend	BitVec	operator>=(const ShortSlice& U,const ShortSlice& V) { return V <= U; }
friend	BitVec	operator==(const ShortSlice&,const ShortSlice&);
friend	BitVec	operator!=(const ShortSlice&,const ShortSlice& V);
friend	BitVec	operator<(const ShortSlice&,short);
friend	BitVec	operator<(short s,const ShortSlice& V)  { return V > s; }
friend	BitVec	operator>(const ShortSlice&,short);
friend	BitVec	operator>(short s,const ShortSlice& V)  { return V < s; }
friend	BitVec	operator<=(const ShortSlice&,short);
friend	BitVec	operator<=(short s,const ShortSlice& V) { return V >= s; }
friend	BitVec	operator>=(const ShortSlice&,short);
friend	BitVec	operator>=(short s,const ShortSlice& V) { return V <= s; }
friend	BitVec	operator==(const ShortSlice&,short);
friend	BitVec	operator==(short s,const ShortSlice& V) { return V == s; }
friend	BitVec	operator!=(const ShortSlice&,short);
friend	BitVec	operator!=(short s,const ShortSlice& V) { return V != s; }
friend	void	operator+=(ShortSlice&,const ShortSlice&);
friend	void	operator+=(ShortSlice&,short);
friend	void	operator-=(ShortSlice&,const ShortSlice&);
friend	void	operator-=(ShortSlice&,short);
friend	void	operator*=(ShortSlice&,const ShortSlice&);
friend	void	operator*=(ShortSlice&,short);
friend	void	operator/=(ShortSlice&,const ShortSlice&);
friend	void	operator/=(ShortSlice&,short);
friend	void	operator%=(ShortSlice&,const ShortSlice&);
friend	void	operator%=(ShortSlice&,short);
friend	void	operator&=(ShortSlice&,const ShortSlice&);
friend	void	operator&=(ShortSlice&,short);
friend	void	operator^=(ShortSlice&,const ShortSlice&);
friend	void	operator^=(ShortSlice&,short);
friend	void	operator|=(ShortSlice&,const ShortSlice&);
friend	void	operator|=(ShortSlice&,short);
friend	ShortVec	abs(const ShortSlice& V);
friend	ShortVec	cumsum(const ShortSlice&);
friend	ShortVec	delta(const ShortSlice&);
friend	short	dot(const ShortSlice&,const ShortSlice&);
friend	int	max(const ShortSlice&);
friend	int	min(const ShortSlice&);
friend	short	prod(const ShortSlice&);
friend	ShortVec	reverse(const ShortSlice&);
friend	short	sum(const ShortSlice&);
};

class ShortPick : public NIHCL {
	ShortVec* V;
	const IntVec* X;
	ShortPick(const ShortVec& v,const IntVec& x)	{ V = &(ShortVec&)v;  X = &x; }
	ShortPick(const ShortPick& s)			{ V = s.V; X = s.X; }
	friend ShortVec;
	friend ShortSlice;
	friend ShortSlct;
public:
	void /*ShortPick::*/operator=(const ShortVec&);
	void /*ShortPick::*/operator=(const ShortPick&);
	void /*ShortPick::*/operator=(const ShortSlct&);
	void /*ShortPick::*/operator=(const ShortSlice&);
	void /*ShortPick::*/operator=(short);
	unsigned length() const	{ return X->length(); }
};

class ShortSlct : public NIHCL {
	ShortVec* V;
	const BitVec* B;
	ShortSlct(const ShortVec& v, const BitVec& b)	{ V = &(ShortVec&)v;  B = &b; }
	ShortSlct(const ShortSlct& s)			{ V = s.V; B = s.B; }
	friend ShortVec;
	friend ShortSlice;
	friend ShortPick;
public:
	void /*ShortSlct::*/operator=(const ShortVec&);
	void /*ShortSlct::*/operator=(const ShortPick&);
	void /*ShortSlct::*/operator=(const ShortSlct&);
	void /*ShortSlct::*/operator=(const ShortSlice&);
	void /*ShortSlct::*/operator=(short);
	unsigned length() const	{ return B->length(); }
};

inline ShortSlice ShortVec::operator()(int pos, unsigned lgt, int stride)
{
	ShortSlice s(*this,pos,lgt,stride);
	return s;
}

inline const ShortSlice ShortVec::operator()(int pos, unsigned lgt, int stride) const
{
	const ShortSlice s(*this,pos,lgt,stride);
	return s;
}

inline ShortVec::operator ShortSlice()
{
	ShortSlice s(*this,length());
	return s;
}

inline ShortVec::operator const ShortSlice() const
{
	const ShortSlice s(*this,length());
	return s;
}

inline ShortPick ShortVec::operator[](const IntVec& I)
{
	return ShortPick(*this,I);
}

inline const ShortPick ShortVec::operator[](const IntVec& I) const
{
	const ShortPick t(*this,I);
	return t;
}

inline ShortSlct ShortVec::operator[](const BitVec& B)
{
	return ShortSlct(*this,B);
}

inline const ShortSlct ShortVec::operator[](const BitVec& B) const
{
	const ShortSlct t(*this,B);
	return t;
}

#endif
