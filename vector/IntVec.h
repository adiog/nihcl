#ifndef	INTVEC_H
#define	INTVEC_H

/* IntVec.h -- Integer Vectors

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

$Log:	IntVec.h,v $
 * Revision 3.0  90/05/16  23:00:32  kgorlen
 * Release for 1st edition.
 * 
*/
#include "Vector.h"
#include "BitVec.h"

class IntSlice;
class IntPick;
class IntSlct;

class IntVec : public Vector {
	DECLARE_MEMBERS(IntVec);
	int* v;		// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	IntVec(unsigned len =0);
	IntVec(unsigned len, int from, int by =1);
	IntVec(const int*, unsigned len);
	IntVec(const IntVec&);
	IntVec(const IntSlice&);
	~IntVec()			{ delete v; }
	IntSlice operator()(int pos, unsigned lgt, int stride =1);
	const IntSlice operator()(int pos, unsigned lgt, int stride =1) const;
	int* pt()		{ return v; }
	const int* pt() const	{ return v; }
	operator IntSlice();
	operator const IntSlice() const;
	operator DoubleVec();
//	operator LongVec();
	int& operator[](int i) {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	const int& operator[](int i) const {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	int& operator()(int i)		    { return v[i]; }
	const int& operator()(int i) const  { return v[i]; }
	IntPick operator[](const IntVec&);
	const IntPick operator[](const IntVec&) const;
	IntSlct operator[](const BitVec&);
	const IntSlct operator[](const BitVec&) const;
	void /*IntVec::*/operator=(const IntVec&);
	void /*IntVec::*/operator=(const IntSlice&);
	void /*IntVec::*/operator=(const IntSlct&);
	void /*IntVec::*/operator=(const IntPick&);
	void /*IntVec::*/operator=(int);
	void /*IntVec::*/lengthErr(const IntSlice&) const;
	void selectErr(const BitVec&) const;
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void scanFrom(istream& strm);
	virtual void sort();
	virtual const Class* species() const;
};

inline unsigned BitPick::length() const { return X->length(); }
	
class TempIntVec : public IntVec {
	friend IntSlice;
	friend IntPick;
	friend IntSlct;
	TempIntVec(unsigned len =0) : IntVec(len) {}
	virtual void free();
};

class IntSlice : public NIHCL {
	IntVec* V;	// vector pointer
	int* p;		// slice pointer
	unsigned l;	// slice length
	int k;		// slice stride
	IntSlice(const IntVec& v, int pos, unsigned lgt, int stride =1);
	IntSlice(const IntVec& v, unsigned lgt) {
		V = &(IntVec&)v;  p = ((IntVec&)v).pt();  l = lgt;  k = 1;
	}
	IntSlice(const IntSlice&);
	friend IntVec;
public:
	IntSlice(const IntPick&);
	IntSlice(const IntSlct&);
	~IntSlice()		{ V->free(); }
	int* pt()		{ return p; }
	const int* pt() const	{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*IntSlice::*/operator=(const IntVec&);
	void /*IntSlice::*/operator=(const IntPick&);
	void /*IntSlice::*/operator=(const IntSlct&);
	void /*IntSlice::*/operator=(const IntSlice&);
	void /*IntSlice::*/operator=(int);
	void /*IntSlice::*/lengthErr(const IntVec&) const;
	void /*IntSlice::*/lengthErr(const IntSlice&) const;
	void selectErr(const BitVec&) const;
friend	IntVec	operator-(const IntSlice&);
friend	IntVec	operator!(const IntSlice&);
friend	IntVec	operator~(const IntSlice&);
friend	IntVec	operator++(IntSlice&);
friend	IntVec	operator--(IntSlice&);
friend	IntVec	operator*(const IntSlice&,const IntSlice&);
friend	IntVec	operator/(const IntSlice&,const IntSlice&);
friend	IntVec	operator%(const IntSlice&,const IntSlice&);
friend	IntVec	operator+(const IntSlice&,const IntSlice&);
friend	IntVec	operator-(const IntSlice&,const IntSlice&);
friend	IntVec	operator&(const IntSlice&,const IntSlice&);
friend	IntVec	operator^(const IntSlice&,const IntSlice&);
friend	IntVec	operator|(const IntSlice&,const IntSlice&);
friend	IntVec	operator*(const IntSlice&,int);
friend	IntVec	operator*(int s,const IntSlice& V)  { return V*s; }
friend	IntVec	operator/(const IntSlice&,int);
friend	IntVec	operator/(int,const IntSlice&);
friend	IntVec	operator%(const IntSlice&,int);
friend	IntVec	operator%(int,const IntSlice&);
friend	IntVec	operator+(const IntSlice&,int);
friend	IntVec	operator+(int s,const IntSlice& V)  { return V+s; }
friend	IntVec	operator-(const IntSlice&,int);
friend	IntVec	operator-(int,const IntSlice&);
friend	IntVec	operator&(const IntSlice&,int);
friend	IntVec	operator&(int s,const IntSlice& V)  { return V&s; }
friend	IntVec	operator^(const IntSlice&,int);
friend	IntVec	operator^(int s,const IntSlice& V)  { return V^s; }
friend	IntVec	operator|(const IntSlice&,int);
friend	IntVec	operator|(int s,const IntSlice& V)  { return V|s; }
friend	BitVec	operator<(const IntSlice&,const IntSlice&);
friend	BitVec	operator>(const IntSlice& U,const IntSlice& V)	{ return V < U; }
friend	BitVec	operator<=(const IntSlice&,const IntSlice&);
friend	BitVec	operator>=(const IntSlice& U,const IntSlice& V) { return V <= U; }
friend	BitVec	operator==(const IntSlice&,const IntSlice&);
friend	BitVec	operator!=(const IntSlice&,const IntSlice& V);
friend	BitVec	operator<(const IntSlice&,int);
friend	BitVec	operator<(int s,const IntSlice& V)  { return V > s; }
friend	BitVec	operator>(const IntSlice&,int);
friend	BitVec	operator>(int s,const IntSlice& V)  { return V < s; }
friend	BitVec	operator<=(const IntSlice&,int);
friend	BitVec	operator<=(int s,const IntSlice& V) { return V >= s; }
friend	BitVec	operator>=(const IntSlice&,int);
friend	BitVec	operator>=(int s,const IntSlice& V) { return V <= s; }
friend	BitVec	operator==(const IntSlice&,int);
friend	BitVec	operator==(int s,const IntSlice& V) { return V == s; }
friend	BitVec	operator!=(const IntSlice&,int);
friend	BitVec	operator!=(int s,const IntSlice& V) { return V != s; }
friend	void	operator+=(IntSlice&,const IntSlice&);
friend	void	operator+=(IntSlice&,int);
friend	void	operator-=(IntSlice&,const IntSlice&);
friend	void	operator-=(IntSlice&,int);
friend	void	operator*=(IntSlice&,const IntSlice&);
friend	void	operator*=(IntSlice&,int);
friend	void	operator/=(IntSlice&,const IntSlice&);
friend	void	operator/=(IntSlice&,int);
friend	void	operator%=(IntSlice&,const IntSlice&);
friend	void	operator%=(IntSlice&,int);
friend	void	operator&=(IntSlice&,const IntSlice&);
friend	void	operator&=(IntSlice&,int);
friend	void	operator^=(IntSlice&,const IntSlice&);
friend	void	operator^=(IntSlice&,int);
friend	void	operator|=(IntSlice&,const IntSlice&);
friend	void	operator|=(IntSlice&,int);
friend	IntVec	abs(const IntSlice& V);
friend	IntVec	cumsum(const IntSlice&);
friend	IntVec	delta(const IntSlice&);
friend	int	dot(const IntSlice&,const IntSlice&);
friend	int	max(const IntSlice&);
friend	int	min(const IntSlice&);
friend	int	prod(const IntSlice&);
friend	IntVec	reverse(const IntSlice&);
friend	int	sum(const IntSlice&);
};

class IntPick : public NIHCL {
	IntVec* V;
	const IntVec* X;
	IntPick(const IntVec& v,const IntVec& x)    { V = &(IntVec&)v;  X = &x; }
	IntPick(const IntPick& s)		    { V = s.V; X = s.X; }
	friend IntVec;
	friend IntSlice;
	friend IntSlct;
public:
	void /*IntPick::*/operator=(const IntVec&);
	void /*IntPick::*/operator=(const IntPick&);
	void /*IntPick::*/operator=(const IntSlct&);
	void /*IntPick::*/operator=(const IntSlice&);
	void /*IntPick::*/operator=(int);
	unsigned length() const	{ return X->length(); }
};

class IntSlct : public NIHCL {
	IntVec* V;
	const BitVec* B;
	IntSlct(const IntVec& v, const BitVec& b)   { V = &(IntVec&)v;  B = &b; }
	IntSlct(const IntSlct& s)		    { V = s.V; B = s.B; }
	friend IntVec;
	friend IntSlice;
	friend IntPick;
public:
	void /*IntSlct::*/operator=(const IntVec&);
	void /*IntSlct::*/operator=(const IntPick&);
	void /*IntSlct::*/operator=(const IntSlct&);
	void /*IntSlct::*/operator=(const IntSlice&);
	void /*IntSlct::*/operator=(int);
	unsigned length() const	{ return B->length(); }
};

inline IntSlice IntVec::operator()(int pos, unsigned lgt, int stride)
{
	IntSlice s(*this,pos,lgt,stride);
	return s;
}

inline const IntSlice IntVec::operator()(int pos, unsigned lgt, int stride) const
{
	const IntSlice s(*this,pos,lgt,stride);
	return s;
}

inline IntVec::operator IntSlice()
{
	IntSlice s(*this,length());
	return s;
}

inline IntVec::operator const IntSlice() const
{
	const IntSlice s(*this,length());
	return s;
}

inline IntPick IntVec::operator[](const IntVec& I)
{
	return IntPick(*this,I);
}

inline const IntPick IntVec::operator[](const IntVec& I) const
{
	const IntPick t(*this,I);
	return t;
}

inline IntSlct IntVec::operator[](const BitVec& B)
{
	return IntSlct(*this,B);
}

inline const IntSlct IntVec::operator[](const BitVec& B) const
{
	const IntSlct t(*this,B);
	return t;
}

#endif
