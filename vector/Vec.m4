/* Vec.m4 -- M4 code templates for NIHCL Vector classes

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
	Internet: kgorlen@alw.nih.gov
	May, 1986

Function:
	
This file contains M4 macro definitions for almost all of the functions
needed to implement the NIHCL vector classes.

Modification History:

$Log:	Vec.m4,v $
Revision 3.0  90/05/16  23:00:41  kgorlen
Release for 1st edition.

*/
// WARNING: Modify the M4 macros, not the C++ code they generate!
// WARNING: Assumes 8 bits per character.

define(CONCAT,$1$2$3$4$5$6$7$8$9)

define(CAP,`CONCAT(translit(substr($1,0,1),abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ),substr($1,1))')

define(PROLOGUE,

``#include'' "$1Vec.h"
``#include'' "nihclIO.h"

``#define'' THIS $1Vec
``#define'' BASE Vector
``#define'' BASE_CLASSES Vector::desc()
``#define'' MEMBER_CLASSES
``#define'' VIRTUAL_BASE_CLASSES

DEFINE_CLASS($1Vec,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/vector/RCS/Vec.m4,v 3.0 90/05/16 23:00:41 kgorlen Rel $",NULL,NULL);

typedef float Float;
typedef double Double;
typedef unsigned char Byte;
typedef short Short;
typedef int Int;
typedef long Long;

void $1Copy(const $1* src, $1* dst, unsigned long count)
// Copy n $1 elements from src to dst.
{
	const $1* sp = src;
	$1* dp = dst;
``#ifndef'' DUFF
	unsigned long n = count;
	while (n--) *dp++ = *sp++;
``#else''
//  Unrolled loop using Duff's Device:
	unsigned long n = (count+7)>>3;
	switch (count & 7) {
		case 0:	do {	*dp++ = *sp++;
		case 7:		*dp++ = *sp++;
		case 6:		*dp++ = *sp++;
		case 5:		*dp++ = *sp++;
		case 4:		*dp++ = *sp++;
		case 3:		*dp++ = *sp++;
		case 2:		*dp++ = *sp++;
		case 1:		*dp++ = *sp++;
		} while (--n > 0);
	}
``#endif''
}

void Temp$1Vec::free()		{ delete this; }

bool $1Vec::isEqual(const Object& u) const
// Test $1Vecs equal.
{
	const $1Vec* U = castdown(&u);
	if (!u.isSpecies(classDesc) || n!=U->n) return NO;
	unsigned i = n;
	$1* vp = v;
	$1* up = U->v;
	while (i--) if (*vp++ != *up++) return NO;
	return YES;
}
									
const Class* $1Vec::species() const	{ return &classDesc; }

void $1Vec::deepenShallowCopy() {}

$1Vec::$1Vec(OIOin& strm) : BASE(strm)
{
	v = new $1[n];
	strm.get(v,n);
}

void $1Vec::storer(OIOout& strm) const
{
	Vector::storer(strm);
	strm.put(v,n);
}

$1Vec::$1Vec(OIOifd& fd) : BASE(fd)
{
	v = new $1[n];
	fd.get(v,n);
}

void $1Vec::storer(OIOofd& fd) const
{
	Vector::storer(fd);
	fd.put(v,n);
}

extern const int NIHCL_INDEXRANGE;
extern const int NIHCL_SLICERANGE;
extern const int NIHCL_VECTORLENGTH;
extern const int NIHCL_VECTORSELECT;

void $1Vec::indexRangeErr() const
{
	setError(NIHCL_INDEXRANGE,DEFAULT,this,className());
}

void $1Vec::selectErr(const BitVec& V) const
{
	setError(NIHCL_VECTORSELECT,DEFAULT,this,"$1Vec",length(),sum(V),&V,V.length());
}

void $1Slice::selectErr(const BitVec& V) const
{
	NIHCL::setError(NIHCL_VECTORSELECT,DEFAULT,this,"$1Slice",length(),sum(V),&V,V.length());
}

)

define(TYPE1_lengthErr_TYPE2,
void $1::lengthErr(const $2& V) const
{
	NIHCL::setError(NIHCL_VECTORLENGTH,DEFAULT,this,"$1",length(),&V,"$2",V.length());
}
)

define(TYPEVec_CTOR_I,
$1Vec::$1Vec(unsigned lngth) : BASE(lngth)
// Construct an uninitialized $1Vec of the length specified.
{
	v = NULL;
	if (lngth != 0) v = new $1[lngth];
}
)

define(TYPEVec_CTOR_I_TYPE_TYPE,
$1Vec::$1Vec(unsigned lngth, $1 from, $1 by) : BASE(lngth)
// Construct a $1Vec of the length specified and initialize it to
// (v[0] = from, v[i] = v[i-1]+by for i = 1...n-1)
{
	v = NULL;
	if (lngth != 0) {
		v = new $1[lngth];
		$1* vp =v;
		for ($1 x =from; lngth-- >0; x += by) *vp++ = x;
	}
}
)

define(TYPEVec_CTOR_TYPEPTR_I,
$1Vec::$1Vec(const $1* src, unsigned lngth) : BASE(lngth)
// Construct a $1Vec and initialize it from the specified $1 vector.
{
	v = NULL;
	if (lngth != 0) {
		v = new $1[lngth];
		$1Copy(src,v,lngth);
	}
}
)

define(TYPEVec_CTOR_TYPEVec,
$1Vec::$1Vec(const $1Vec& U) : BASE(U.n)
// Construct a $1Vec and initialize it from the specified $1Vec U.
{
	v = NULL;
	if (n != 0) {
		v = new $1[n];
		$1Copy(U.v,v,n);
	}
}
)

define(TYPEVec_CTOR_TYPESlice,
$1Vec::$1Vec(const $1Slice& s) : BASE(s.length())
// Construct a $1Vec from a slice of another $1Vec.
{
	v = NULL;
	if (n != 0) {
		v = new $1[n];
		const $1* sp = s.pt();
		$1* dp = v;
		int i = s.length();
		int j = s.stride();
		while (i--) { *dp++ = *sp; sp += j; }
	}
}
)

define(TYPESlice_CTOR_TYPEVec_I_I_I,
$1Slice::$1Slice(const $1Vec& v, int pos, unsigned lgt, int stride)
// Construct a $1Slice from a $1Vec.
{
	if ((unsigned)(pos + (lgt-1)*stride) >= v.length())
		NIHCL::setError(NIHCL_SLICERANGE,DEFAULT,&v,v.className(),v.length(),pos,lgt,stride);
	V = &($1Vec&)v;  p = &(($1Vec&)v)[pos];  l = lgt;  k = stride;
}
)

define(TYPESlice_CTOR_TYPEPick,
$1Slice::$1Slice(const $1Pick& s)
// Construct a $1Vec slice from IntVec-subscripted elements of $1Vec.
// Can't do this with $1Slct::operator $1Slice() because of Temp$1Vec
{
	$1Vec& T = *new Temp$1Vec();
	T = (*s.V)[*s.X];
	V = &T;  p = T.pt();  l = T.length();  k = 1;
}
)

define(TYPESlice_CTOR_TYPESlice,
$1Slice::$1Slice(const $1Slice& s)
// Private $1Slice copy constructor
{
	V = s.V;
	p = s.p;
	l = s.l;
	k = s.k;
}
)

define(TYPESlice_CTOR_TYPESlct,
$1Slice::$1Slice(const $1Slct& s)
// Construct a $1Vec slice from $1Vec-selected elements of $1Vec.
// Can't do this with $1Slct::operator $1Slice() because of Temp$1Vec
{
	$1Vec& T = *new Temp$1Vec();
	T = (*s.V)[*s.B];
	V = &T;  p = T.pt();  l = T.length();  k = 1;
}
)

define(TYPEVec_ASN_TYPEVec,
void $1Vec::operator=(const $1Vec& U)
// Assign the argument $1Vec U to this $1Vec.
{
	if (v != U.v) {
		delete v;
		v = NULL;
		if ((n = U.n) != 0) {
			v = new $1[n];
			$1Copy(U.v,v,n);
		}
	}
}
)

define(TYPEVec_ASN_TYPESlice,
void $1Vec::operator=(const $1Slice& s)
// Assign a slice of a $1Vec to this $1Vec.
{
	int i = s.length();		// slice length
	if ((n = i) == 0) {		// empty slice
		delete v;
		v = NULL;
		return;
	}
	const $1* sp = s.pt();
	int j = s.stride();
	if (this == s.V) {	// V = V(i,j,k)
		$1* t = v;
		$1* dp = new $1[i];
		v = dp;
		while (i--) { *dp++ = *sp; sp += j; }
		delete t;
	}
	else {
		delete v;
		$1* dp = new $1[i];
		v = dp;
		while (i--) { *dp++ = *sp; sp += j; }
	}
}
)

define(TYPEVec_ASN_TYPESlct,
void $1Vec::operator=(const $1Slct& s)
// Assign the BitVec-selected elements of a $1Vec to this $1Vec.
{
	if ((n = sum(*s.B)) == 0) {	// return zero length result
		delete v;
		v = NULL;
		return;
	}
	$1* sp = s.V->pt();
	$1* t = v;
	if (this != s.V) delete t;	// not V = V[BitVec&]
	$1* dp = new $1[n];
	v = dp;
	BITVECSCAN(*s.B, s.length(), *dp++ = *sp;  sp++)
	if (this == s.V) delete t;	// case V = V[BitVec&]
}
)

define(TYPEVec_ASN_TYPEPick,
void $1Vec::operator=(const $1Pick& s)
// Assign the IntVec-subscripted elements of a $1Vec to this $1Vec.
{
	unsigned i = s.length();
	unsigned l;
	if ((l = i) == 0) {	// return zero length result
		delete v;
		v = NULL;  n = 0;
		return;
	}
	$1* t = v;
	if (this != s.V) delete t;	// not V = V[IntVec&]
	$1* dp = new $1[l];
	$1* u = dp;
	const int* xp = (*s.X).pt();
	$1Vec& S = *s.V;
	while (i--) { *dp++ = S[*xp++]; }
	v = u;  n = l;
	if (this == s.V) delete t;	// case V = V[IntVec&]
}
)

define(TYPEVec_ASN_TYPE,
void $1Vec::operator=($1 scalar)
// Assign a scalar to all elements of this $1Vec.
{
	unsigned i = n;
	$1* dp = v;
	$1 c = scalar;
	while (i--) *dp++ = c;
}
)

define(TYPESlice_ASN_TYPEVec,
void $1Slice::operator=(const $1Vec& U)
// Assign a $1Vec to this $1Vec slice.
{
	int i = l;
	if (i != U.length()) lengthErr(U);
	$1* dp = p;
	const $1* sp = U.pt();
	int j = k;
	while (i--) { *dp = *sp++; dp += j; }
}
)

define(TYPESlice_ASN_TYPESlice,
void $1Slice::operator=(const $1Slice& s)
// Assign a $1Vec slice to this $1Vec slice.
{
	int i = l;
	if (i != s.l) lengthErr(s);
	$1* dp = p;
	$1* sp = s.p;
	int dj = k;
	int sj = s.k;
	while (i--) { *dp = *sp; dp += dj; sp += sj; }
}
)

define(TYPESlice_ASN_TYPEPick,
void $1Slice::operator=(const $1Pick& s)
// Assign the IntVec-subscripted elements of a $1Vec to this $1Vec slice.
{
	int i = l;
	if (i != s.length()) lengthErr(*s.X);
	$1* dp = p;
	const int* xp = (*s.X).pt();
	int j = k;
	$1Vec& S = *s.V;
	while (i--) { *dp = S[*xp++]; dp += j; }
}
)

define(TYPESlice_ASN_TYPESlct,
void $1Slice::operator=(const $1Slct& s)
// Assign the BitVec-selected elements of a $1Vec to this $1Vec slice.
{
	if (l != sum(*s.B)) lengthErr(s);
	$1* sp = s.V->pt();
	$1* dp = p;
	int j = k;
	BITVECSCAN(*s.B, s.length(), { *dp = *sp;  dp += j; };  sp++)
}
)

define(TYPESlice_ASN_TYPE,
void $1Slice::operator=($1 scalar)
// Assign a scalar to all elements of this $1Vec slice.
{
	int i = l;
	int j = k;
	$1* dp = p;
	$1 c = scalar;
	while (i--) { *dp = c; dp += j; }
}
)

define(FRIEND_OP_TYPESlice__TYPEVec,
$1Vec operator$2(const $1Slice& s)
// Unary operator on $1Vec slice.
{
	int i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = T.pt();
	int j = s.stride();
	while (i--) { *dp++ = $2(*sp);  sp += j; }
	return T;
}
)

define(FRIEND_INCDECOP_TYPESlice__TYPEVec,
$1Vec operator$2($1Slice& s)
// Unary inc/dec operator on $1Vec slice.
{
	int i = s.length();
	$1Vec T(i);
	$1* sp = s.pt();
	$1* dp = T.pt();
	int j = s.stride();
	while (i--) { *dp++ = $2(*sp);  sp += j; }
	return T;
}
)

define(FRIEND_TYPESlice_OP_TYPESlice__TYPEVec,
$1Vec operator$2(const $1Slice& u, const $1Slice& v)
// Binary arithmetic operator on two $1Vec slices
{
	int i = u.length();
	if (i != v.length()) u.lengthErr(v);
	$1Vec T(i);
	const $1* up = u.pt();
	const $1* vp = v.pt();
	$1* dp = T.pt();
	int uj = u.stride();
	int vj = v.stride();
	while (i--) { *dp++ = *up $2 *vp;  up += uj; vp += vj; }
	return T;
}
)

define(FRIEND_TYPESlice_OP_TYPE__TYPEVec,
$1Vec operator$2(const $1Slice& s, $1 scalar)
// Binary arithmetic operator on $1Vec slice and scalar.
{
	int i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = T.pt();
	int j = s.stride();
	$1 c = scalar;
	while (i--) { *dp++ = *sp $2 c; sp += j; }
	return T;
}
)

define(FRIEND_TYPE_OP_TYPESlice__TYPEVec,
$1Vec operator$2($1 scalar, const $1Slice& s)
// Binary arithmetic operator on scalar and $1Vec slice.
{
	int i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = T.pt();
	int j = s.stride();
	$1 c = scalar;
	while (i--) { *dp++ = c $2 *sp; sp += j; }
	return T;
}
)

define(FRIEND_TYPESlice_OP_TYPESlice__BitVec,
BitVec operator$2(const $1Slice& u, const $1Slice& v)
// Relational operator on two $1Vec slices.
{
	if (u.length() != v.length()) u.lengthErr(v);
	BitVec B(u.length());
	const $1* up = u.pt();
	const $1* vp = v.pt();
	int uj = u.stride();
	int vj = v.stride();
	BITVECGEN(B.pt(), u.length(), *up $2 *vp, up += uj; vp += vj)
	return B;
}
)

define(FRIEND_TYPESlice_OP_TYPE__BitVec,
BitVec operator$2(const $1Slice& s, $1 scalar)
// Relational operator on $1Vec slice and scalar.
{
	BitVec B(s.length());
	const $1* vp = s.pt();
	int vj = s.stride();
	$1 c = scalar;
	BITVECGEN(B.pt(), s.length(), *vp $2 c, vp += vj)
	return B;
}
)

define(FRIEND_TYPE_OP_TYPESlice__BitVec,
BitVec operator$2($1 scalar, const $1Slice& s)
// Relational operator on scalar and $1Vec slice.
{
	BitVec B(s.length());
	const $1* vp = s.pt();
	int vj = s.stride();
	$1 c = scalar;
	BITVECGEN(B.pt(), s.length(), c $2 *vp, vp += vj)
	return B;
}
)

define(FRIEND_TYPESlice_ASNOP_TYPESlice,
void operator$2($1Slice& u, const $1Slice& v)
// Assignment arithmetic operator on two $1Vec slices.
{
	int i = u.length();
	if (i != v.length()) u.lengthErr(v);
	$1* up = u.pt();
	const $1* vp = v.pt();
	int uj = u.stride();
	int vj = v.stride();
	while (i--) { *up $2 *vp;  up += uj; vp += vj; }
}
)

define(FRIEND_TYPESlice_ASNOP_TYPE,
void operator$2($1Slice& s, $1 scalar)
// Assignment arithmetic operator on scalar and $1Vec slice.
{
	int i = s.length();
	$1* dp = s.pt();
	int j = s.stride();
	$1 c = scalar;
	while (i--) { *dp $2 c; dp += j; }
}
)

define(TYPEPick_ASN_TYPEVec,
void $1Pick::operator=(const $1Vec& U)
// Assign $1Vec to IntVec-subscripted elements of $1Vec.
{
	int i = length();
	if (i != U.length()) lengthErr(*X,U);
	const int* xp = (*X).pt();
	const $1* up = U.pt();
	$1Vec& D = *V;
	while (i--) { D[*xp++] = *up++; }
}
)

define(TYPEPick_ASN_TYPEPick,
void $1Pick::operator=(const $1Pick& s)
// Assign IntVec-subscripted elements of $1Vec to IntVec-subscripted elements of $1Vec.
{
	int i = length();
	if (i != s.length()) lengthErr(*X,*s.X);
	const int* xp = (*X).pt();
	const int* yp = (*s.X).pt();
	$1Vec& D = *V;
	$1Vec& S = *s.V;
	while (i--) { D[*xp++] = S[*yp++]; }
}
)

define(TYPEPick_ASN_TYPESlct,
void $1Pick::operator=(const $1Slct& s)
// Assign BitVec-selected elements of $1Vec to IntVec-subscripted elements of $1Vec.
{
	if (length() != sum(*s.B)) X->selectErr(*s.B);
	const int* xp = (*X).pt();
	const $1* sp = (*s.V).pt();
	$1Vec& D = *V;
	BITVECSCAN(*s.B, length(), D[*xp++] = *sp;  sp++)
}
)

define(TYPEPick_ASN_TYPESlice,
void $1Pick::operator=(const $1Slice& s)
// Assign $1Vec slice to IntVec-subscripted elements of $1Vec.
{
	int i = length();
	if (i != s.length()) s.lengthErr(*X);
	const int* xp = (*X).pt();
	const $1* sp = s.pt();
	int j = s.stride();
	$1Vec& D = *V;
	while (i--) { D[*xp++] = *sp;  sp += j; }
}
)

define(TYPEPick_ASN_TYPE,
void $1Pick::operator=($1 scalar)
// Assign scalar to all IntVec-subscripted elements of $1Vec.
{
	int i = length();
	const int* xp = (*X).pt();
	$1 c = scalar;
	$1Vec& D = *V;
	while (i--) { D[*xp++] = c; }
}
)

define(TYPESlct_ASN_TYPEVec,
void $1Slct::operator=(const $1Vec& U)
// Assign a $1Vec to BitVec-selected elements of $1Vec.
{
	if (U.length() != sum(*B)) U.selectErr(*B);
	$1* dp = V->pt();
	const $1* sp = U.pt();
	BITVECSCAN(*B, U.length(), *dp = *sp++;  dp++)
}
)

define(TYPESlct_ASN_TYPEPick,
void $1Slct::operator=(const $1Pick& s)
// Assign IntVec-subscripted elements of $1Vec to BitVec-selected elements of $1Vec.
{
	if (s.length() != sum(*B)) s.X->selectErr(*B);
	$1* dp = V->pt();
	const int* xp = (*s.X).pt();
	$1Vec& W = *s.V;
	BITVECSCAN(*B, length(), *dp = W[*xp++];  dp++)
}
)

define(TYPESlct_ASN_TYPESlct,
void $1Slct::operator=(const $1Slct& s)
// Assign BitVec-selected elements of $1Vec to BitVec-selected elements of $1Vec.
{
	$1Vec T;
	T = (*s.V)[*s.B];
	(*V)[*B] = T;
}
)

define(TYPESlct_ASN_TYPESlice,
void $1Slct::operator=(const $1Slice& s)
// Assign $1Vec slice to BitVec-selected elements of $1Vec.
{
	if (s.length() != sum(*B)) s.selectErr(*B);
	$1* dp = V->pt();
	const $1* sp = s.pt();
	int j = s.stride();
	BITVECSCAN(*B, length(), { *dp = *sp;  sp += j; };  dp++)
}
)

define(TYPESlct_ASN_TYPE,
void $1Slct::operator=($1 scalar)
// Assign scalar to all BitVec-selected elements of $1Vec.
{
	$1* dp = V->pt();
	$1 c = scalar;
	BITVECSCAN(*B, length(), *dp = c;  dp++)
}
)

define(TYPESlice_APPLY_FUN__TYPEVec,
$1Vec $1Slice::apply(mathFunTy f) const
// Apply function to each element of vector slice
{
	int i = l;
	$1Vec T(i);
	$1* sp = p;
	$1* dp = T.pt();
	int j = k;
	while (i--) { *dp++ = f(*sp);  sp += j; }
	return T;
}
)

define(FRIEND_abs_TYPESlice,
$1Vec abs(const $1Slice& s)
// Absolute value of $1Vec slice.
{
	int i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = T.pt();
	int j = s.stride();
	while (i--) { *dp++ = ABS(*sp);  sp += j; }
	return T;
}
)

define(FRIEND_atan2_TYPESlice_TYPESlice,
$1Vec atan2(const $1Slice& u,const $1Slice& v)
// Arctangent of u/v.
{
	int i = u.length();
	if (i != v.length()) u.lengthErr(v);
	$1Vec T(i);
	const $1* up = u.pt();
	const $1* vp = v.pt();
	$1* dp = T.pt();
	int uj = u.stride();
	int vj = v.stride();
	while (i--) { *dp++ = $2(*up,*vp);  up += uj;  vp += vj; }
	return T;
}
)

define(FRIEND_pow_TYPESlice_TYPESlice,
$1Vec pow(const $1Slice& u,const $1Slice& v)
// u to the v power.
{
	int i = u.length();
	if (i != v.length()) u.lengthErr(v);
	$1Vec T(i);
	const $1* up = u.pt();
	const $1* vp = v.pt();
	$1* dp = T.pt();
	int uj = u.stride();
	int vj = v.stride();
	while (i--) { *dp++ = $2(*up,*vp);  up += uj;  vp += vj; }
	return T;
}
)

define(FRIEND_cumsum_TYPESlice,
$1Vec cumsum(const $1Slice& s)
// Cumulative sum of $1Vec slice.
// Note: V == delta(cumsum(V)) == cumsum(delta(V))
{
	unsigned i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = T.pt();
	$1 c = 0;
	int j = s.stride();
	while (i--) { *dp++ = c += *sp;  sp += j; }
	return T;
}
)

define(FRIEND_delta_TYPESlice,
$1Vec delta(const $1Slice& s)
// Element differences of $1Vec slice.
// Note: V == delta(cumsum(V)) == cumsum(delta(V))
{
	unsigned i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = T.pt();
	$1 c = 0;
	int j = s.stride();
	while (i--) { *dp++ = *sp - c;  c = *sp;  sp += j; }
	return T;
}
)

define(FRIEND_dot_TYPESlice_TYPESlice,
$1 dot(const $1Slice& u,const $1Slice& v)
// Vector dot product.
{
	int i = u.length();
	if (i != v.length()) u.lengthErr(v);
	$1 t =0;
	const $1* up = u.pt();
	const $1* vp = v.pt();
	int uj = u.stride();
	int vj = v.stride();
	while (i--) { t += *up * *vp;  up += uj;  vp += vj; }
	return t;
}
)

define(FRIEND_max_TYPESlice,
int max(const $1Slice& s)
// Index of maximum element.
{
	if (s.length() == 0) s.V->emptyErr("max");
	const $1* sp = s.pt();
	$1 t = *sp;
	int j = s.stride();
	int x = 0;
	for (int i =0; i<s.length(); i++) {
		if (*sp > t) { t = *sp;  x = i; }
		sp += j;
	}
	return x;
}
)

define(FRIEND_min_TYPESlice,
int min(const $1Slice& s)
// Index of minimum element.
{
	if (s.length() == 0) s.V->emptyErr("min");
	const $1* sp = s.pt();
	$1 t = *sp;
	int j = s.stride();
	int x = 0;
	for (int i =0; i<s.length(); i++) {
		if (*sp < t) { t = *sp;  x = i; }
		sp += j;
	}
	return x;
}
)

define(FRIEND_prod_TYPESlice,
$1 prod(const $1Slice& s)
// Product of $1Vec slice elements.
{
	int i = s.length();
	const $1* sp = s.pt();
	$1 t = 1;
	int j = s.stride();
	while (i--) { t *= *sp;  sp += j; }
	return t;
}
)

define(FRIEND_reverse_TYPESlice,
$1Vec reverse(const $1Slice& s)
// Reverse vector elements.
{
	int i = s.length();
	$1Vec T(i);
	const $1* sp = s.pt();
	$1* dp = &T(i);
	int j = s.stride();
	while (i--) { *(--dp) = *sp;  sp += j; }
	return T;
}
)

define(FRIEND_sum_TYPESlice,
$1 sum(const $1Slice& s)
// Sum of vector elements.
{
	int i = s.length();
	const $1* sp = s.pt();
	$1 t = 0;
	int j = s.stride();
	while (i--) { t += *sp;  sp += j; }
	return t;
}
)

define(FRIEND_acos_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_asin_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_atan_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_ceil_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_cos_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_cosh_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_exp_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_floor_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_log_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_sin_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_sinh_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_sqrt_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_tan_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
define(FRIEND_tanh_TYPESlice,$1Vec $2(const $1Slice& V) { return V.apply($2); })
