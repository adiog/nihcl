#ifndef	DOUBLEVEC_H
#define	DOUBLEVEC_H

/* DoubleVec.h -- Double Precision Vectors

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

$Log:	DoubleVec.h,v $
 * Revision 3.0  90/05/16  23:00:29  kgorlen
 * Release for 1st edition.
 * 
*/
#include "Vector.h"
#include "BitVec.h"
#include "IntVec.h"

class DoubleSlice;
class DoublePick;
class DoubleSlct;

class DoubleVec : public Vector {
	DECLARE_MEMBERS(DoubleVec);
	double* v;	// pointer to data, NULL if empty vector
	void indexRangeErr() const;
protected:
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	DoubleVec(unsigned len =0);
	DoubleVec(unsigned len, double from, double by =1.0);
	DoubleVec(const double*, unsigned len);
	DoubleVec(const DoubleVec&);
	DoubleVec(const DoubleSlice&);
	DoubleVec(const FloatVec&);
	~DoubleVec()		{ delete v; }
	DoubleSlice operator()(int pos, unsigned lgt, int stride =1);
	const DoubleSlice operator()(int pos, unsigned lgt, int stride =1) const;
	double*	pt()			{ return v; }
	const double* pt() const	{ return v; }
	operator DoubleSlice();
	operator const DoubleSlice() const;
//	operator ComplexVec();
	double&	operator[](int i) {		// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	const double& operator[](int i) const {	// vector element
		if ((unsigned)i >= n) indexRangeErr();
		return v[i];
	}
	double& operator()(int i)		{ return v[i]; }
	const double& operator()(int i) const	{ return v[i]; }
	DoublePick operator[](const IntVec&);
	const DoublePick operator[](const IntVec&) const;
	DoubleSlct operator[](const BitVec&);
	const DoubleSlct operator[](const BitVec&) const;
	void /*DoubleVec::*/operator=(const DoubleVec&);
	void /*DoubleVec::*/operator=(const DoubleSlice&);
	void /*DoubleVec::*/operator=(const DoubleSlct&);
	void /*DoubleVec::*/operator=(const DoublePick&);
	void /*DoubleVec::*/operator=(double);
	void /*DoubleVec::*/lengthErr(const DoubleSlice&) const;
	void selectErr(const BitVec&) const;
	virtual void	deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool	isEqual(const Object&) const;
	virtual void	printOn(ostream& strm =cout) const;
	virtual void	scanFrom(istream& strm);
	virtual void	sort();
	virtual const Class* species() const;
};

class TempDoubleVec : public DoubleVec {
	friend DoubleSlice;
	friend DoublePick;
	friend DoubleSlct;
	TempDoubleVec(unsigned len =0) : DoubleVec(len) {}
	virtual void free();
};

class DoubleSlice : public NIHCL {
	DoubleVec* V;	// vector pointer
	double* p;	// slice pointer
	unsigned l;	// slice length
	int k;		// slice stride
	DoubleSlice(const DoubleVec& v, int pos, unsigned lgt, int stride =1);
	DoubleSlice(const DoubleVec& v, unsigned lgt) {
		V = &(DoubleVec&)v;  p = ((DoubleVec&)v).pt();  l = lgt;  k = 1;
	}
	DoubleSlice(const DoubleSlice&);
	friend DoubleVec;
public:
	DoubleSlice(const DoublePick&);
	DoubleSlice(const DoubleSlct&);
	~DoubleSlice()		{ V->free(); }
	double*	pt()			{ return p; }
	const double* pt() const	{ return p; }
	unsigned length() const	{ return l; }
	int stride() const	{ return k; }
	void /*DoubleSlice::*/operator=(const DoubleVec&);
	void /*DoubleSlice::*/operator=(const DoublePick&);
	void /*DoubleSlice::*/operator=(const DoubleSlct&);
	void /*DoubleSlice::*/operator=(const DoubleSlice&);
	void /*DoubleSlice::*/operator=(double);
	void /*DoubleSlice::*/lengthErr(const DoubleVec&) const;
	void /*DoubleSlice::*/lengthErr(const DoubleSlice&) const;
	void /*DoubleSlice::*/lengthErr(const IntVec&) const;
	void selectErr(const BitVec&) const;
friend	DoubleVec	operator-(const DoubleSlice&);
friend	DoubleVec	operator++(DoubleSlice&);
friend	DoubleVec	operator--(DoubleSlice&);
friend	DoubleVec	operator*(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	operator/(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	operator+(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	operator-(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	operator*(const DoubleSlice&,double);
friend	DoubleVec	operator*(double s,const DoubleSlice& V)  { return V*s; }
friend	DoubleVec	operator/(const DoubleSlice&,double);
friend	DoubleVec	operator/(double,const DoubleSlice&);
friend	DoubleVec	operator+(const DoubleSlice&,double);
friend	DoubleVec	operator+(double s,const DoubleSlice& V)  { return V+s; }
friend	DoubleVec	operator-(const DoubleSlice&,double);
friend	DoubleVec	operator-(double,const DoubleSlice&);
friend	BitVec		operator<(const DoubleSlice&,const DoubleSlice&);
friend	BitVec		operator>(const DoubleSlice& U,const DoubleSlice& V)  { return V < U; }
friend	BitVec		operator<=(const DoubleSlice&,const DoubleSlice&);
friend	BitVec		operator>=(const DoubleSlice& U,const DoubleSlice& V)  { return V <= U; }
friend	BitVec		operator==(const DoubleSlice&,const DoubleSlice&);
friend	BitVec		operator!=(const DoubleSlice&,const DoubleSlice&);
friend	BitVec		operator<(const DoubleSlice&,double);
friend	BitVec		operator<(double s,const DoubleSlice& V)  { return V>s; }
friend	BitVec		operator>(const DoubleSlice&,double);
friend	BitVec		operator>(double s,const DoubleSlice& V)  { return V<s; }
friend	BitVec		operator<=(const DoubleSlice&,double);
friend	BitVec		operator<=(double s,const DoubleSlice& V)  { return V>=s; }
friend	BitVec		operator>=(const DoubleSlice&,double);
friend	BitVec		operator>=(double s,const DoubleSlice& V)  { return V<=s; }
friend	BitVec		operator==(const DoubleSlice&,double);
friend	BitVec		operator==(double s,const DoubleSlice& V)  { return V==s; }
friend	BitVec		operator!=(const DoubleSlice&,double);
friend	BitVec		operator!=(double s,const DoubleSlice& V)  { return V!=s; }
friend	void		operator+=(DoubleSlice&,const DoubleSlice&);
friend	void		operator+=(DoubleSlice&,double);
friend	void		operator-=(DoubleSlice&,const DoubleSlice&);
friend	void		operator-=(DoubleSlice&,double);
friend	void		operator*=(DoubleSlice&,const DoubleSlice&);
friend	void		operator*=(DoubleSlice&,double);
friend	void		operator/=(DoubleSlice&,const DoubleSlice&);
friend	void		operator/=(DoubleSlice&,double);
	DoubleVec	apply(mathFunTy) const;
friend	DoubleVec	abs(const DoubleSlice& V);
friend	DoubleVec	acos(const DoubleSlice& V)	{ return V.apply(acos); }
friend	DoubleVec	asin(const DoubleSlice& V)	{ return V.apply(asin); }
friend	DoubleVec	atan(const DoubleSlice& V)	{ return V.apply(atan); }
friend	DoubleVec	atan2(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	ceil(const DoubleSlice& V)	{ return V.apply(ceil); }
friend	DoubleVec	cos(const DoubleSlice& V)	{ return V.apply(cos); }
friend	DoubleVec	cosh(const DoubleSlice& V)	{ return V.apply(cosh); }
friend	DoubleVec	cumsum(const DoubleSlice&);
friend	DoubleVec	delta(const DoubleSlice&);
friend	double		dot(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	exp(const DoubleSlice& V)	{ return V.apply(exp); }
friend	DoubleVec	floor(const DoubleSlice& V)	{ return V.apply(floor); }
friend	DoubleVec	log(const DoubleSlice& V)	{ return V.apply(log); }
friend	int		max(const DoubleSlice&);
friend	int		min(const DoubleSlice&);
friend	double		prod(const DoubleSlice&);
friend	DoubleVec	pow(const DoubleSlice&,const DoubleSlice&);
friend	DoubleVec	reverse(const DoubleSlice&);
friend	DoubleVec	sin(const DoubleSlice& V)	{ return V.apply(sin); }
friend	DoubleVec	sinh(const DoubleSlice& V)	{ return V.apply(sinh); }
friend	DoubleVec	sqrt(const DoubleSlice& V)	{ return V.apply(sqrt); }
friend	double		sum(const DoubleSlice&);
friend	DoubleVec	tan(const DoubleSlice& V)	{ return V.apply(tan); }
friend	DoubleVec	tanh(const DoubleSlice& V)	{ return V.apply(tanh); }
};

class DoublePick : public NIHCL {
	DoubleVec* V;
	const IntVec* X;
	DoublePick(const DoubleVec& v,const IntVec& x)	{ V = &(DoubleVec&)v;  X = &x; }
	DoublePick(const DoublePick& s)			{ V = s.V; X = s.X; }
	friend DoubleVec;
	friend DoubleSlice;
	friend DoubleSlct;
public:
	void /*DoublePick::*/operator=(const DoubleVec&);
	void /*DoublePick::*/operator=(const DoublePick&);
	void /*DoublePick::*/operator=(const DoubleSlct&);
	void /*DoublePick::*/operator=(const DoubleSlice&);
	void /*DoublePick::*/operator=(double);
	unsigned length() const	{ return X->length(); }
};

class DoubleSlct: public NIHCL {
	DoubleVec* V;
	const BitVec* B;
	DoubleSlct(const DoubleVec& v, const BitVec& b)	{ V = &(DoubleVec&)v;  B = &b; }
	DoubleSlct(const DoubleSlct& s)			{ V = s.V; B = s.B; }
	friend DoubleVec;
	friend DoubleSlice;
	friend DoublePick;
public:
	void /*DoubleSlct::*/operator=(const DoubleVec&);
	void /*DoubleSlct::*/operator=(const DoublePick&);
	void /*DoubleSlct::*/operator=(const DoubleSlct&);
	void /*DoubleSlct::*/operator=(const DoubleSlice&);
	void /*DoubleSlct::*/operator=(double);
	unsigned length() const	{ return B->length(); }
};

inline DoubleSlice DoubleVec::operator()(int pos, unsigned lgt, int stride)
{
	DoubleSlice s(*this,pos,lgt,stride);
	return s;
}

inline const DoubleSlice DoubleVec::operator()(int pos, unsigned lgt, int stride) const
{
	const DoubleSlice s(*this,pos,lgt,stride);
	return s;
}

inline DoubleVec::operator DoubleSlice()
{
	DoubleSlice s(*this,length());
	return s;
}

inline DoubleVec::operator const DoubleSlice() const
{
	const DoubleSlice s(*this,length());
	return s;
}

inline DoublePick DoubleVec::operator[](const IntVec& I)
{
	return DoublePick(*this,I);
}

inline const DoublePick DoubleVec::operator[](const IntVec& I) const
{
	const DoublePick t(*this,I);
	return t;
}

inline DoubleSlct DoubleVec::operator[](const BitVec& B)
{
	return DoubleSlct(*this,B);
}

inline const DoubleSlct DoubleVec::operator[](const BitVec& B) const
{
	const DoubleSlct t(*this,B);
	return t;
}

#endif
