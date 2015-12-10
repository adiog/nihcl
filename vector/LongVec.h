#ifndef	LONGVEC_H
#define	LONGVEC_H

/* LongVec.h -- Long Integer Vectors

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

$Log:	LongVec.h,v $
 * Revision 3.0  90/05/16  23:00:35  kgorlen
 * Release for 1st edition.
 * 
*/
#include "Vector.h"
#include "BitVec.h"
#include "IntVec.h"

class LongSlice;
class LongPick;
class LongSlct;

class LongVec : public Vector {
	DECLARE_MEMBERS(LongVec);
	long* v;		// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	LongVec(unsigned len =0);
	LongVec(unsigned len, long from, long by =1);
	LongVec(const long*, unsigned len);
	LongVec(const LongVec&);
	LongVec(const LongSlice&);
	~LongVec()			{ delete v; }
	LongSlice operator()(int pos, unsigned lgt, int stride =1);
	const LongSlice operator()(int pos, unsigned lgt, int stride =1) const;
	long* pt()		{ return v; }
	const long* pt() const	{ return v; }
	operator LongSlice();
	operator const LongSlice() const;
	operator DoubleVec();
//	operator LongVec();
	long& operator[](int i) {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	const long& operator[](int i) const {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	long& operator()(int i)		    { return v[i]; }
	const long& operator()(int i) const  { return v[i]; }
	LongPick operator[](const IntVec&);
	const LongPick operator[](const IntVec&) const;
	LongSlct operator[](const BitVec&);
	const LongSlct operator[](const BitVec&) const;
	void /*LongVec::*/operator=(const LongVec&);
	void /*LongVec::*/operator=(const LongSlice&);
	void /*LongVec::*/operator=(const LongSlct&);
	void /*LongVec::*/operator=(const LongPick&);
	void /*LongVec::*/operator=(long);
	void /*LongVec::*/lengthErr(const LongSlice&) const;
	void selectErr(const BitVec&) const;
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void scanFrom(istream& strm);
	virtual void sort();
	virtual const Class* species() const;
};

class TempLongVec : public LongVec {
	friend LongSlice;
	friend LongPick;
	friend LongSlct;
	TempLongVec(unsigned len =0) : LongVec(len) {}
	virtual void free();
};

class LongSlice : public NIHCL {
	LongVec* V;	// vector pointer
	long* p;	// slice pointer
	unsigned l;	// slice length
	int k;	// slice stride
	LongSlice(const LongVec& v, int pos, unsigned lgt, int stride =1);
	LongSlice(const LongVec& v, unsigned lgt) {
		V = &(LongVec&)v;  p = ((LongVec&)v).pt();  l = lgt;  k = 1;
	}
	LongSlice(const LongSlice&);
	friend LongVec;
public:
	LongSlice(const LongPick&);
	LongSlice(const LongSlct&);
	~LongSlice()		{ V->free(); }
	long* pt()		{ return p; }
	const long* pt() const	{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*LongSlice::*/operator=(const LongVec&);
	void /*LongSlice::*/operator=(const LongPick&);
	void /*LongSlice::*/operator=(const LongSlct&);
	void /*LongSlice::*/operator=(const LongSlice&);
	void /*LongSlice::*/operator=(long);
	void /*LongSlice::*/lengthErr(const LongVec&) const;
	void /*LongSlice::*/lengthErr(const LongSlice&) const;
	void /*LongSlice::*/lengthErr(const IntVec&) const;
	void selectErr(const BitVec&) const;
friend	LongVec	operator-(const LongSlice&);
friend	LongVec	operator!(const LongSlice&);
friend	LongVec	operator~(const LongSlice&);
friend	LongVec	operator++(LongSlice&);
friend	LongVec	operator--(LongSlice&);
friend	LongVec	operator*(const LongSlice&,const LongSlice&);
friend	LongVec	operator/(const LongSlice&,const LongSlice&);
friend	LongVec	operator%(const LongSlice&,const LongSlice&);
friend	LongVec	operator+(const LongSlice&,const LongSlice&);
friend	LongVec	operator-(const LongSlice&,const LongSlice&);
friend	LongVec	operator&(const LongSlice&,const LongSlice&);
friend	LongVec	operator^(const LongSlice&,const LongSlice&);
friend	LongVec	operator|(const LongSlice&,const LongSlice&);
friend	LongVec	operator*(const LongSlice&,long);
friend	LongVec	operator*(long s,const LongSlice& V)  { return V*s; }
friend	LongVec	operator/(const LongSlice&,long);
friend	LongVec	operator/(long,const LongSlice&);
friend	LongVec	operator%(const LongSlice&,long);
friend	LongVec	operator%(long,const LongSlice&);
friend	LongVec	operator+(const LongSlice&,long);
friend	LongVec	operator+(long s,const LongSlice& V)  { return V+s; }
friend	LongVec	operator-(const LongSlice&,long);
friend	LongVec	operator-(long,const LongSlice&);
friend	LongVec	operator&(const LongSlice&,long);
friend	LongVec	operator&(long s,const LongSlice& V)  { return V&s; }
friend	LongVec	operator^(const LongSlice&,long);
friend	LongVec	operator^(long s,const LongSlice& V)  { return V^s; }
friend	LongVec	operator|(const LongSlice&,long);
friend	LongVec	operator|(long s,const LongSlice& V)  { return V|s; }
friend	BitVec	operator<(const LongSlice&,const LongSlice&);
friend	BitVec	operator>(const LongSlice& U,const LongSlice& V)	{ return V < U; }
friend	BitVec	operator<=(const LongSlice&,const LongSlice&);
friend	BitVec	operator>=(const LongSlice& U,const LongSlice& V) { return V <= U; }
friend	BitVec	operator==(const LongSlice&,const LongSlice&);
friend	BitVec	operator!=(const LongSlice&,const LongSlice& V);
friend	BitVec	operator<(const LongSlice&,long);
friend	BitVec	operator<(long s,const LongSlice& V)  { return V > s; }
friend	BitVec	operator>(const LongSlice&,long);
friend	BitVec	operator>(long s,const LongSlice& V)  { return V < s; }
friend	BitVec	operator<=(const LongSlice&,long);
friend	BitVec	operator<=(long s,const LongSlice& V) { return V >= s; }
friend	BitVec	operator>=(const LongSlice&,long);
friend	BitVec	operator>=(long s,const LongSlice& V) { return V <= s; }
friend	BitVec	operator==(const LongSlice&,long);
friend	BitVec	operator==(long s,const LongSlice& V) { return V == s; }
friend	BitVec	operator!=(const LongSlice&,long);
friend	BitVec	operator!=(long s,const LongSlice& V) { return V != s; }
friend	void	operator+=(LongSlice&,const LongSlice&);
friend	void	operator+=(LongSlice&,long);
friend	void	operator-=(LongSlice&,const LongSlice&);
friend	void	operator-=(LongSlice&,long);
friend	void	operator*=(LongSlice&,const LongSlice&);
friend	void	operator*=(LongSlice&,long);
friend	void	operator/=(LongSlice&,const LongSlice&);
friend	void	operator/=(LongSlice&,long);
friend	void	operator%=(LongSlice&,const LongSlice&);
friend	void	operator%=(LongSlice&,long);
friend	void	operator&=(LongSlice&,const LongSlice&);
friend	void	operator&=(LongSlice&,long);
friend	void	operator^=(LongSlice&,const LongSlice&);
friend	void	operator^=(LongSlice&,long);
friend	void	operator|=(LongSlice&,const LongSlice&);
friend	void	operator|=(LongSlice&,long);
friend	LongVec	abs(const LongSlice& V);
friend	LongVec	cumsum(const LongSlice&);
friend	LongVec	delta(const LongSlice&);
friend	long	dot(const LongSlice&,const LongSlice&);
friend	int	max(const LongSlice&);
friend	int	min(const LongSlice&);
friend	long	prod(const LongSlice&);
friend	LongVec	reverse(const LongSlice&);
friend	long	sum(const LongSlice&);
};

class LongPick : public NIHCL {
	LongVec* V;
	const IntVec* X;
	LongPick(const LongVec& v,const IntVec& x)	{ V = &(LongVec&)v;  X = &x; }
	LongPick(const LongPick& s)			{ V = s.V; X = s.X; }
	friend LongVec;
	friend LongSlice;
	friend LongSlct;
public:
	void /*LongPick::*/operator=(const LongVec&);
	void /*LongPick::*/operator=(const LongPick&);
	void /*LongPick::*/operator=(const LongSlct&);
	void /*LongPick::*/operator=(const LongSlice&);
	void /*LongPick::*/operator=(long);
	unsigned length() const	{ return X->length(); }
};

class LongSlct : public NIHCL {
	LongVec* V;
	const BitVec* B;
	LongSlct(const LongVec& v, const BitVec& b)	{ V = &(LongVec&)v;  B = &b; }
	LongSlct(const LongSlct& s)			{ V = s.V; B = s.B; }
	friend LongVec;
	friend LongSlice;
	friend LongPick;
public:
	void /*LongSlct::*/operator=(const LongVec&);
	void /*LongSlct::*/operator=(const LongPick&);
	void /*LongSlct::*/operator=(const LongSlct&);
	void /*LongSlct::*/operator=(const LongSlice&);
	void /*LongSlct::*/operator=(long);
	unsigned length() const	{ return B->length(); }
};

inline LongSlice LongVec::operator()(int pos, unsigned lgt, int stride)
{
	LongSlice s(*this,pos,lgt,stride);
	return s;
}

inline const LongSlice LongVec::operator()(int pos, unsigned lgt, int stride) const
{
	const LongSlice s(*this,pos,lgt,stride);
	return s;
}

inline LongVec::operator LongSlice()
{
	LongSlice s(*this,length());
	return s;
}

inline LongVec::operator const LongSlice() const
{
	const LongSlice s(*this,length());
	return s;
}

inline LongPick LongVec::operator[](const IntVec& I)
{
	return LongPick(*this,I);
}

inline const LongPick LongVec::operator[](const IntVec& I) const
{
	const LongPick t(*this,I);
	return t;
}

inline LongSlct LongVec::operator[](const BitVec& B)
{
	return LongSlct(*this,B);
}

inline const LongSlct LongVec::operator[](const BitVec& B) const
{
	const LongSlct t(*this,B);
	return t;
}

#endif
