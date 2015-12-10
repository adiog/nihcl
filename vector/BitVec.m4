/* BitVec.m4 -- M4 code templates for NIHCL BitVec class

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
	June, 1986

Function:
	
This file contains M4 macro definitions for some of the functions
needed to implement the NIHCL bit vector class.

Modification History:

$Log:	BitVec.m4,v $
Revision 3.0  90/05/16  23:00:24  kgorlen
Release for 1st edition.

*/
// WARNING: Modify the M4 macros, not the C++ code they generate!
// WARNING: Assumes 8 bits per character.

`#include' "IntVec.h"
`#include' "bitstreams.h"
`#include' "nihclconfig.h"
`#include' "nihclIO.h"

`#define'	THIS	BitVec
`#define'	BASE	Vector
`#define'	BASE_CLASSES Vector::desc()
`#define'	MEMBER_CLASSES
`#define'	VIRTUAL_BASE_CLASSES

DEFINE_CLASS(BitVec,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/vector/RCS/BitVec.m4,v 3.0 90/05/16 23:00:24 kgorlen Rel $",NULL,NULL);

extern const int NIHCL_INDEXRANGE;
extern const int NIHCL_SLICERANGE;
extern const int NIHCL_VECTORLENGTH;
extern const int NIHCL_VECTORSELECT;

inline unsigned nbytes(unsigned n)	{ return (n+7) >> 3; }

void byteCopy(const bitVecByte* src, bitVecByte* dst, unsigned long count)
// Copy n bytes from src to dst.
{
	const bitVecByte* sp = src;
	bitVecByte* dp = dst;
#ifndef DUFF
	unsigned long n = count;
	while (n--) *dp++ = *sp++;
#else
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
#endif
}

static union hash_byte_mask {
	unsigned in[sizeof(int)];
	char ch[sizeof(int)*sizeof(int)];
	hash_byte_mask();
} mask;

hash_byte_mask::hash_byte_mask()
{
	for (unsigned i=0; i<sizeof(int); i++) {
		for (unsigned j=0; j<sizeof(int); j++) ch[sizeof(int)*i+j] = j<i ? 0xff : 0;
	}
}

unsigned THIS::hash() const
{
	unsigned h = nbytes();
	unsigned i = div_sizeof_int(nbytes());
	unsigned* vp = (unsigned*)v;
	while (i--) h ^= *vp++;
	if ((i = mod_sizeof_int(nbytes())) != 0)
		h ^= *vp & mask.in[i];
	return h;
}

void THIS::printOn(ostream& strm) const
{
	for (unsigned i=0; i<length(); i++) {
		if (i>0 && (i%25 == 0)) strm << "\n\t";
		strm << ((*this)(i) ? "1 " : "0 ");
	}
}

void THIS::scanFrom(istream& strm)
{
	extern const int NIHCL_NYET;
	setError(NIHCL_NYET,DEFAULT,className(),"scanFrom");
}

THIS::THIS(OIOin& strm) : BASE(strm)
{
	v = new bitVecByte[nbytes()];
	strm.get(v,nbytes());
}

void THIS::storer(OIOout& strm) const
{
	BASE::storer(strm);
	strm.put(v,nbytes());
}

THIS::THIS(OIOifd& fd) : BASE(fd)
{
	v = new bitVecByte[nbytes()];
	fd.get(v,nbytes());
}

void THIS::storer(OIOofd& fd) const
{
	BASE::storer(fd);
	fd.put(v,nbytes());
}

bool BitVec::isEqual(const Object& u) const
// Test for two BitVecs equal.
{
	const BitVec* U = castdown(&u);
	if (!u.isSpecies(classDesc) || n!=U->n) return NO;
	unsigned i = nbytes();
	bitVecByte* vp = v;
	bitVecByte* up = U->v;
	while (i--) if (*vp++ != *up++) return NO;
	return YES;
}
									
const Class* BitVec::species() const	{ return &classDesc; }

void BitVec::deepenShallowCopy() {}

void BitVec::indexRangeErr() const
{
	setError(NIHCL_INDEXRANGE,DEFAULT,this,className());
}

void BitVec::selectErr(const BitVec& V) const
{
	setError(NIHCL_VECTORSELECT,DEFAULT,this,"BitVec",length(),sum(V),&V,V.length());
}

void BitSlice::selectErr(const BitVec& V) const
{
	setError(NIHCL_VECTORSELECT,DEFAULT,this,"BitSlice",length(),sum(V),&V,V.length());
}

BitVec::BitVec(unsigned lngth) : BASE(lngth)
// Construct an uninitialized BitVec of the length specified.
{
	v = NULL;
	if (lngth != 0) v = new bitVecByte[nbytes()];
}

BitVec::BitVec(unsigned lngth, bool init) : BASE(lngth)
// Construct a BitVec of the length specified and initialize it.
{
	v = NULL;
	if ((lngth) != 0) {
		v = new bitVecByte[nbytes()];
		*this = init;
	}
}

BitVec::BitVec(const bitVecByte* src, unsigned lngth) : BASE(lngth)
// Construct a BitVec and initialize it from the specified byte vector.
{
	v = NULL;
	if (lngth != 0) {
		int l = nbytes();
		v = new bitVecByte[l];
		byteCopy(src,v,l);
	}
}

BitVec::BitVec(const BitVec& U) : BASE(U.n)
// Construct a BitVec and initialize it from the specified BitVec U.
{
	v = NULL;
	if (n != 0) {
		int l = nbytes();
		v = new bitVecByte[l];
		byteCopy(U.v,v,l);
	}
}

BitVec::BitVec(const BitSlice& s) : BASE(0)
// Construct a BitVec from a slice of another BitVec.
{
	v = NULL;
	*this = s;
}

BitSlice::BitSlice(const BitVec& v, int pos, unsigned lgt, int stride)
// Construct a BitSlice from a BitVec.
{
	if ((unsigned)(pos + (lgt-1)*stride) >= v.length())
		setError(NIHCL_SLICERANGE,DEFAULT,&v,v.className(),v.length(),pos,lgt,stride);
	V = &(BitVec&)v;  p = pos;  l = lgt;  k = stride;
}

BitSlice::BitSlice(const BitSlice& s)
// private BitSlice copy constructor
{
	V = s.V;
	p = s.p;
	l = s.l;
	k = s.k;
}

BitSlice::BitSlice(const BitSlct& s)
// Construct a BitVec slice from IntVec-subscripted elements of BitVec
// Can't do this with BitSlct::operator BitSlice() because of TempBitVec
{
	BitVec& T = *new TempBitVec();
	T = (*s.V)[*s.B];
	V = &T;  p = 0;  l = T.length();  k = 1;
}

BitSlice::BitSlice(const BitPick& s)
// Construct a BitVec slice from IntVec-subscripted elements of BitVec
// Can't do this with BitPick::operator BitSlice() because of TempBitVec
{
	BitVec& T = *new TempBitVec();
	T = (*s.V)[*s.X];
	V = &T;  p = 0;  l = T.length();  k = 1;
}

void BitVec::operator=(const BitVec& U)
// Assign the argument BitVec U to this BitVec.
{
	if (v != U.v) {
		delete v;
		v = NULL;
		if ((n = U.n) != 0) {
			int l = nbytes();
			v = new bitVecByte[l];
			byteCopy(U.pt(),v,l);
		}
	}
}

void BitVec::operator=(const BitSlice& s)
// Assign a slice of a BitVec to this BitVec.
{
	if ((n = s.length()) == 0) {		// empty slice
		delete v;
		v = NULL;
		return;
	}
	bitVecByte* t = v;
	if (this != s.V) delete t;	// not V = V(i,j,k)
	bitVecByte* u = new bitVecByte[nbytes()];
	BitSliceIstream src(s);
	BITVECGEN(u, length(), src)
	v = u;
	if (this == s.V) delete t;	// case V = V[BitVec&]
}

void BitVec::operator=(const BitSlct& s)
// Assign the BitVec-selected elements of a BitVec to this BitVec.
{
	if ((n = sum(*s.B)) == 0) {	// return zero length result
		delete v;
		v = NULL;
		return;
	}
	BitVecIstream src(*s.V);
	BitVecIstream slct(*s.B);
	bitVecByte* t = v;
	if (this != s.V) delete t;	// not V = V[BitVec&]
	v = new bitVecByte[nbytes()];
	BitVecOstream dst(*this);
	unsigned i = s.length();
	while(i--) {
		if (slct) dst << src;
		slct++;
		src++;
	}
	if (this == s.V) delete t;	// case V = V[BitVec&]
}

void BitVec::operator=(const BitPick& s)
// Assign the IntVec-subscripted elements of a BitVec to this BitVec.
{
	unsigned l = s.length();
	if (l == 0) {		// empty IntVec
		delete v;
		n = 0;  v = NULL;
		return;
	}
	bitVecByte* t = v;
	if (this != s.V) delete t;	// not V = V[IntVec]
	bitVecByte* u = new bitVecByte[::nbytes(l)];
	BitPickIstream src(s);
	BITVECGEN(u, l, src)
	n = l;  v = u;
	if (this == s.V) delete t;	// case V = V[IntVec&]
}

void BitVec::operator=(bool scalar)
// Assign a scalar Boolean to all elements of this BitVec.
{
	int i = nbytes();
	bitVecByte* dp = v;
	if (i>0) {
		if (scalar) {
			while (--i) *dp++ = 0xff;
			*dp = charBitMask(n&7)-1;
		}
		else while (i--) *dp++ = 0;
	}
}

BitVec operator!(const BitVec& U)
// Unary bitwise operator on a BitVec.
{
	int i = U.nbytes();
	BitVec T(U.length());
	bitVecByte* dp = T.pt();
	const bitVecByte* up = U.pt();
	while (i--) *dp++ = ~(*up++);
	if ((i = U.length()&7) != 0) {
		--dp;
		*dp &= NIHCL::charBitMask(i)-1;
	}
	return T;
}

void BitSlice::operator=(const BitVec& U)
// Assign a BitVec to this BitVec slice.
{
	if (length() != U.length()) lengthErr(U);
	BitSliceOstream dst(*this);
	bitVecByte m;
	const bitVecByte* bp = U.pt();
	unsigned i = length() >> 3;
	while (i--) {
		m = *bp++;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);
	}
	i = length() & 7;
	m = *bp;
	while (i--) {
		dst << (m&1);  m >>= 1;
	}
}

void BitSlice::operator=(const BitSlice& s)
// Assign a BitVec slice to this BitVec slice.
{
	unsigned i = length();
	if (i != s.length()) lengthErr(s);
	BitSliceIstream src(s);
	BitSliceOstream dst(*this);
	while (i--) dst << src;
}

void BitSlice::operator=(const BitPick& s)
// Assign the IntVec-subscripted elements of a BitVec to this BitVec slice.
{
	int i = length();
	if (i != s.length()) lengthErr(*s.X);
	BitSliceOstream dst(*this);
	BitPickIstream src(s);
	while (i--) dst << src;
}

void BitSlice::operator=(const BitSlct& s)
// Assign the BitVec-selected elements of a BitVec to this BitVec slice.
{
	if (l != sum(*s.B)) selectErr(*s.B);
	BitVecIstream src(*s.V);
	BitVecIstream slct(*s.B);
	BitSliceOstream dst(*this);
	unsigned i = s.length();
	while(i--) {
		if (slct) { dst << src; }
		slct++;
		src++;
	}
}

void BitSlice::operator=(bool scalar)
// Assign a scalar to all elements of this BitVec slice.
{
	int i = length();
	int j = stride();
	int x = pos();
	BitVec& D = *V;
	bool c = scalar;
	while (i--) { D(x) = c; x += j; }
}

BitVec operator!(const BitSlice& s)
// Unary operator on BitVec slice.
{
	BitVec T(s.length());
	BitSliceIstream src(s);
	BITVECGEN(T.pt(), s.length(), !src)
	return T;
}

void BitPick::operator=(const BitVec& U)
// Assign a BitVec to the IntVec-subscripted elements of this BitVec.
{
	if (length() != U.length()) lengthErr(*X,U);
	BitPickOstream dst(*this);
	bitVecByte m;
	const bitVecByte* bp = U.pt();
	unsigned i = length() >> 3;
	while (i--) {
		m = *bp++;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
		dst << (m&1);  m >>= 1;
	}
	i = length() & 7;
	m = *bp;
	while (i--) {
		dst << (m&1);  m >>= 1;
	}
}

void BitPick::operator=(const BitPick& s)
// Assign the IntVec-subscripted elements of a BitVec to the IntVec-subscripted elements of this BitVec.
{
	int i = length();
	if (i != s.length()) lengthErr(*X,*s.X);
	BitPickIstream src(s);
	BitPickOstream dst(*this);
	while (i--) dst << src;
}

void BitPick::operator=(const BitSlct& s)
// Assign the BitVec-selected elements of a BitVec to the IntVec-subscripted elements of this BitVec.
{
	if (length() != sum(*s.B)) X->selectErr(*s.B);
	BitVecIstream src(*s.V);
	BitVecIstream slct(*s.B);
	BitPickOstream dst(*this);
	unsigned i = s.length();
	while(i--) {
		if (slct) { dst << src; }
		slct++;
		src++;
	}
}

void BitPick::operator=(const BitSlice& s)
// Assign a BitVec slice to the IntVec-subscripted elements of this BitVec.
{
	int i = length();
	if (i != s.length()) s.lengthErr(*X);
	BitSliceIstream src(s);
	BitPickOstream dst(*this);
	while (i--) dst << src;
}

void BitPick::operator=(bool scalar)
// Assign a scalar to the IntVec-subscripted elements of this BitVec.
{
	int i = length();
	bool c = scalar;
	BitPickOstream dst(*this);
	while (i--) { dst << c; }
}

void BitSlct::operator=(const BitVec& U)
// Assign a BitVec to the BitVec-selected elements of this BitVec.
{
	if (U.length() != sum(*B)) U.selectErr(*B);
	BitVecIstream src(U);
	BitVecOstream dst(*V);
	BITVECSCAN(*B, length(), { dst << src;  src++; }  else dst++)
}

void BitSlct::operator=(const BitPick& s)
// Assign the IntVec-subscripted elements of a BitVec to the BitVec-selected elements of this BitVec.
{
	if (s.length() != sum(*B)) s.X->selectErr(*B);
	BitPickIstream src(s);
	BitVecOstream dst(*V);
	BITVECSCAN(*B, length(), dst << src;  else dst++)
}

void BitSlct::operator=(const BitSlct& s)
// Assign the BitVec-selected elements of a BitVec to the BitVec-selected elements of this BitVec.
{
	BitVec T;
	T = (*s.V)[*s.B];
	(*V)[*B] = T;
}

void BitSlct::operator=(const BitSlice& s)
// Assign a BitVec slice to the BitVec-selected elements of this BitVec.
{
	if (s.length() != sum(*B)) s.selectErr(*B);
	BitSliceIstream src(s);
	BitVecOstream dst(*V);
	BITVECSCAN(*B, length(), dst << src;  else dst++)
}

void BitSlct::operator=(bool scalar)
// Assign a scalar to the BitVec-selected elements of this BitVec.
{
	BitVecOstream dst(*V);
	BITVECSCAN(*B, length(), dst << scalar;  else dst++)
}

BitVec reverse(const BitSlice& s)
// Reverse bit order of BitSlice.
{
	int i = s.length();
	BitVec T(i);
	int k = s.pos();
	int j = s.stride();
	BitVec& S = *s.V;
	while (i--) { T(i) = S[k];  k += j; }
	return T;
}

int sum(const BitVec& U)
// Count of ones in the specified BitVec.
{
	int i = U.nbytes();
	const bitVecByte* sp = U.pt();
	int t = 0;
	while (i--) t += NIHCL::bitCount(*sp++);
	return t;
}

int sum(const BitSlice& s)
// Count of ones in the specified BitSlice.
{
	int i = s.length();
	int t = 0;
	int k = s.pos();
	int j = s.stride();
	BitVec& S = *s.V;
	while (i--) { if (S[k]) t++;  k += j; }
	return t;
}

define(CONCAT,$1$2$3$4$5$6$7$8$9)

define(CAP,`CONCAT(translit(substr($1,0,1),abcdefghijklmnopqrstuvwxyz,ABCDEFGHIJKLMNOPQRSTUVWXYZ),substr($1,1))')

define(TYPE1_lengthErr_TYPE2,
void $1::lengthErr(const $2& V) const
{
	setError(NIHCL_VECTORLENGTH,DEFAULT,this,"$1",length(),&V,"$2",V.length());
}
)

define(FRIEND_BitVec_OP_BitVec__BitVec,
BitVec operator$2(const BitVec& U, const BitVec& V)
// Binary bitwise operator on two BitVecs.
{
	if (U.length() != V.length()) lengthErr(U,V);
	int i = U.nbytes();
	BitVec T(U.length());
	bitVecByte* dp = T.pt();
	const bitVecByte* up = U.pt();
	const bitVecByte* vp = V.pt();
	while (i--) *dp++ = *up++ $2 *vp++;
	return T;
}
)

define(FRIEND_BitVec_ASNOP_BitVec,
void operator$2(BitVec& U, const BitVec& V)
// Binary bitwise assignment operator on two BitVecs.
{
	if (U.length() != V.length()) lengthErr(U,V);
	int i = U.nbytes();
	bitVecByte* up = U.pt();
	const bitVecByte* vp = V.pt();
	while (i--) *up++ $2 *vp++;
}
)

define(FRIEND_BitSlice_OP_BitSlice__BitVec,
BitVec operator$2(const BitSlice& u, const BitSlice& v)
// Binary arithmetic operator on two BitVec slices
{
	if (u.length() != v.length()) u.lengthErr(v);
	BitVec T(u.length());
	BitSliceIstream usrc(u);
	BitSliceIstream vsrc(v);
	BITVECGEN(T.pt(), u.length(), (bool)usrc $2 (bool)vsrc)
	return T;
}
)

define(FRIEND_BitSlice_ASNOP_BitSlice,
void operator$2(BitSlice& u, const BitSlice& v)
// Assignment arithmetic operator on two BitVec slices.
{
	unsigned i;
	if ((i=u.length()) != v.length()) u.lengthErr(v);
	BitVec& U = *u.V;
	BitVec& V = *v.V;
	int uj = u.pos();
	int vj = v.pos();
	int uk = u.stride();
	int vk = v.stride();
	while (i--) {
		U[uj] $2 V[vj];
		uj += uk;  vj += vk;
	}
}
)
