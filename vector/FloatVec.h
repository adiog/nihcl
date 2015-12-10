#ifndef	FLOATVEC_H
#define	FLOATVEC_H

/* FloatVec.h -- Float Precision Vectors

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

Function:
	
Modification History:

$Log:	FloatVec.h,v $
 * Revision 3.0  90/05/16  23:00:31  kgorlen
 * Release for 1st edition.
 * 
*/
#include "Vector.h"
#include "BitVec.h"
#include "IntVec.h"

class FloatSlice;
class FloatPick;
class FloatSlct;

class FloatVec : public Vector {
	DECLARE_MEMBERS(FloatVec);
	float* v;	// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	FloatVec(unsigned len =0);
	FloatVec(unsigned len, float from, float by =1.0);
	FloatVec(const float*, unsigned len);
	FloatVec(const FloatVec&);
	FloatVec(const FloatSlice&);
	FloatVec(const DoubleVec&);
	~FloatVec()		{ delete v; }
	FloatSlice operator()(int pos, unsigned lgt, int stride =1);
	const FloatSlice operator()(int pos, unsigned lgt, int stride =1) const;
	float*	pt()			{ return v; }
	const float* pt() const	{ return v; }
	operator FloatSlice();
	operator const FloatSlice() const;
//	operator ComplexVec();
	float&	operator[](int i) {		// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	const float& operator[](int i) const {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	float& operator()(int i)		{ return v[i]; }
	const float& operator()(int i) const	{ return v[i]; }
	FloatPick operator[](const IntVec&);
	const FloatPick operator[](const IntVec&) const;
	FloatSlct operator[](const BitVec&);
	const FloatSlct operator[](const BitVec&) const;
	void /*FloatVec::*/operator=(const FloatVec&);
	void /*FloatVec::*/operator=(const FloatSlice&);
	void /*FloatVec::*/operator=(const FloatSlct&);
	void /*FloatVec::*/operator=(const FloatPick&);
	void /*FloatVec::*/operator=(float);
	void /*FloatVec::*/lengthErr(const FloatSlice&) const;
	void selectErr(const BitVec&) const;
	virtual void	deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool	isEqual(const Object&) const;
	virtual void	printOn(ostream& strm =cout) const;
	virtual void	scanFrom(istream& strm);
	virtual void	sort();
	virtual const Class* species() const;
};

class TempFloatVec : public FloatVec {
	friend FloatSlice;
	friend FloatPick;
	friend FloatSlct;
	TempFloatVec(unsigned len =0) : FloatVec(len) {}
	virtual void free();
};

class FloatSlice : public NIHCL {
	FloatVec* V;	// vector pointer
	float* p;	// slice pointer
	unsigned l;	// slice length
	int k;		// slice stride
	FloatSlice(const FloatVec& v, int pos, unsigned lgt, int stride =1);
	FloatSlice(const FloatVec& v, unsigned lgt) {
		V = &(FloatVec&)v;  p = ((FloatVec&)v).pt();  l = lgt;  k = 1;
	}
	FloatSlice(const FloatSlice&);
	friend FloatVec;
public:
	FloatSlice(const FloatPick&);
	FloatSlice(const FloatSlct&);
	~FloatSlice()		{ V->free(); }
	float*	pt()			{ return p; }
	const float* pt() const	{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*FloatSlice::*/operator=(const FloatVec&);
	void /*FloatSlice::*/operator=(const FloatPick&);
	void /*FloatSlice::*/operator=(const FloatSlct&);
	void /*FloatSlice::*/operator=(const FloatSlice&);
	void /*FloatSlice::*/operator=(float);
	void /*FloatSlice::*/lengthErr(const FloatVec&) const;
	void /*FloatSlice::*/lengthErr(const FloatSlice&) const;
	void /*FloatSlice::*/lengthErr(const IntVec&) const;
	void selectErr(const BitVec&) const;
friend	FloatVec	operator-(const FloatSlice&);
friend	FloatVec	operator++(FloatSlice&);
friend	FloatVec	operator--(FloatSlice&);
friend	FloatVec	operator*(const FloatSlice&,const FloatSlice&);
friend	FloatVec	operator/(const FloatSlice&,const FloatSlice&);
friend	FloatVec	operator+(const FloatSlice&,const FloatSlice&);
friend	FloatVec	operator-(const FloatSlice&,const FloatSlice&);
friend	FloatVec	operator*(const FloatSlice&,float);
friend	FloatVec	operator*(float s,const FloatSlice& V)  { return V*s; }
friend	FloatVec	operator/(const FloatSlice&,float);
friend	FloatVec	operator/(float,const FloatSlice&);
friend	FloatVec	operator+(const FloatSlice&,float);
friend	FloatVec	operator+(float s,const FloatSlice& V)  { return V+s; }
friend	FloatVec	operator-(const FloatSlice&,float);
friend	FloatVec	operator-(float,const FloatSlice&);
friend	BitVec		operator<(const FloatSlice&,const FloatSlice&);
friend	BitVec		operator>(const FloatSlice& U,const FloatSlice& V)  { return V < U; }
friend	BitVec		operator<=(const FloatSlice&,const FloatSlice&);
friend	BitVec		operator>=(const FloatSlice& U,const FloatSlice& V)  { return V <= U; }
friend	BitVec		operator==(const FloatSlice&,const FloatSlice&);
friend	BitVec		operator!=(const FloatSlice&,const FloatSlice&);
friend	BitVec		operator<(const FloatSlice&,float);
friend	BitVec		operator<(float s,const FloatSlice& V)  { return V>s; }
friend	BitVec		operator>(const FloatSlice&,float);
friend	BitVec		operator>(float s,const FloatSlice& V)  { return V<s; }
friend	BitVec		operator<=(const FloatSlice&,float);
friend	BitVec		operator<=(float s,const FloatSlice& V)  { return V>=s; }
friend	BitVec		operator>=(const FloatSlice&,float);
friend	BitVec		operator>=(float s,const FloatSlice& V)  { return V<=s; }
friend	BitVec		operator==(const FloatSlice&,float);
friend	BitVec		operator==(float s,const FloatSlice& V)  { return V==s; }
friend	BitVec		operator!=(const FloatSlice&,float);
friend	BitVec		operator!=(float s,const FloatSlice& V)  { return V!=s; }
friend	void		operator+=(FloatSlice&,const FloatSlice&);
friend	void		operator+=(FloatSlice&,float);
friend	void		operator-=(FloatSlice&,const FloatSlice&);
friend	void		operator-=(FloatSlice&,float);
friend	void		operator*=(FloatSlice&,const FloatSlice&);
friend	void		operator*=(FloatSlice&,float);
friend	void		operator/=(FloatSlice&,const FloatSlice&);
friend	void		operator/=(FloatSlice&,float);
	FloatVec	apply(mathFunTy) const;
friend	FloatVec	abs(const FloatSlice& V);
friend	FloatVec	acos(const FloatSlice& V)	{ return V.apply(acos); }
friend	FloatVec	asin(const FloatSlice& V)	{ return V.apply(asin); }
friend	FloatVec	atan(const FloatSlice& V)	{ return V.apply(atan); }
friend	FloatVec	atan2(const FloatSlice&,const FloatSlice&);
friend	FloatVec	ceil(const FloatSlice& V)	{ return V.apply(ceil); }
friend	FloatVec	cos(const FloatSlice& V)	{ return V.apply(cos); }
friend	FloatVec	cosh(const FloatSlice& V)	{ return V.apply(cosh); }
friend	FloatVec	cumsum(const FloatSlice&);
friend	FloatVec	delta(const FloatSlice&);
friend	float		dot(const FloatSlice&,const FloatSlice&);
friend	FloatVec	exp(const FloatSlice& V)	{ return V.apply(exp); }
friend	FloatVec	floor(const FloatSlice& V)	{ return V.apply(floor); }
friend	FloatVec	log(const FloatSlice& V)	{ return V.apply(log); }
friend	int		max(const FloatSlice&);
friend	int		min(const FloatSlice&);
friend	float		prod(const FloatSlice&);
friend	FloatVec	pow(const FloatSlice&,const FloatSlice&);
friend	FloatVec	reverse(const FloatSlice&);
friend	FloatVec	sin(const FloatSlice& V)	{ return V.apply(sin); }
friend	FloatVec	sinh(const FloatSlice& V)	{ return V.apply(sinh); }
friend	FloatVec	sqrt(const FloatSlice& V)	{ return V.apply(sqrt); }
friend	float		sum(const FloatSlice&);
friend	FloatVec	tan(const FloatSlice& V)	{ return V.apply(tan); }
friend	FloatVec	tanh(const FloatSlice& V)	{ return V.apply(tanh); }
};

class FloatPick : public NIHCL {
	FloatVec* V;
	const IntVec* X;
	FloatPick(const FloatVec& v,const IntVec& x)	{ V = &(FloatVec&)v;  X = &x; }
	FloatPick(const FloatPick& s)			{ V = s.V; X = s.X; }
	friend FloatVec;
	friend FloatSlice;
	friend FloatSlct;
public:
	void /*FloatPick::*/operator=(const FloatVec&);
	void /*FloatPick::*/operator=(const FloatPick&);
	void /*FloatPick::*/operator=(const FloatSlct&);
	void /*FloatPick::*/operator=(const FloatSlice&);
	void /*FloatPick::*/operator=(float);
	unsigned length() const	{ return X->length(); }
};

class FloatSlct: public NIHCL {
	FloatVec* V;
	const BitVec* B;
	FloatSlct(const FloatVec& v, const BitVec& b)	{ V = &(FloatVec&)v;  B = &b; }
	FloatSlct(const FloatSlct& s)			{ V = s.V; B = s.B; }
	friend FloatVec;
	friend FloatSlice;
	friend FloatPick;
public:
	void /*FloatSlct::*/operator=(const FloatVec&);
	void /*FloatSlct::*/operator=(const FloatPick&);
	void /*FloatSlct::*/operator=(const FloatSlct&);
	void /*FloatSlct::*/operator=(const FloatSlice&);
	void /*FloatSlct::*/operator=(float);
	unsigned length() const	{ return B->length(); }
};

inline FloatSlice FloatVec::operator()(int pos, unsigned lgt, int stride)
{
	FloatSlice s(*this,pos,lgt,stride);
	return s;
}

inline const FloatSlice FloatVec::operator()(int pos, unsigned lgt, int stride) const
{
	const FloatSlice s(*this,pos,lgt,stride);
	return s;
}

inline FloatVec::operator FloatSlice()
{
	FloatSlice s(*this,length());
	return s;
}

inline FloatVec::operator const FloatSlice() const
{
	const FloatSlice s(*this,length());
	return s;
}

inline FloatPick FloatVec::operator[](const IntVec& I)
{
	return FloatPick(*this,I);
}

inline const FloatPick FloatVec::operator[](const IntVec& I) const
{
	const FloatPick t(*this,I);
	return t;
}

inline FloatSlct FloatVec::operator[](const BitVec& B)
{
	return FloatSlct(*this,B);
}

inline const FloatSlct FloatVec::operator[](const BitVec& B) const
{
	const FloatSlct t(*this,B);
	return t;
}

#endif
