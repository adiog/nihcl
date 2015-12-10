/* Array_c.m4 -- template for implementations of generic array objects

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
	September, 1985

Function:

m4 macro template for the .c files for arrays of the specified
fundamental type: char, int, short, long, unsigned, float, and double.
For example, to generate the implementation of an array of chars:

	m4 Array.c.m4 Arraychar.p >Arraychar.c

The type-specific part of the implementation is in the file
Arraychar.p, for example.

WARNING -- Make changes to the .p or .m4 files, not to the .c file
they generate.

$Log:	Array_c.m4,v $
Revision 3.0  90/05/20  00:18:57  kgorlen
Release for 1st edition.

*/

`#define' NEW(type,size)	((type*)malloc(sizeof(type)*(size)))

define(ARRAYIMPLEMENT,
$1::$1(unsigned size)
{
	sz = size;
	if (size==0) AllocSizeErr();
	v = NEW($2,sz);
	removeAll();
}

$1::$1(const $1& a)
{
	register unsigned i = a.sz;
	sz = i;
	v = NEW($2,i);
	register $2* vv = v;
	register $2* av = a.v;
	while (i--) *vv++ = *av++;
}

$1::~$1()	{ DELETE(v); }

void $1::operator=(const $1& a)
{
	if (v != a.v) {
		DELETE(v);
		v = NEW($2,sz=a.sz);
		register unsigned i = a.sz;
		register $2* vv = v;
		register $2* av = a.v;
		while (i--) *vv++ = *av++;
	}
}

bool $1::operator==(const $1& a) const
{
	if (sz != a.sz) return NO;
	register unsigned i = sz;
	register $2* vv = v;
	register $2* av = a.v;
	while (i--) if (*vv++ != *av++) return NO;
	return YES;
}

unsigned $1::capacity()	const { return sz; }

int $1::compare(const Object& p) const
{
	assertArgSpecies(p,classDesc,"compare");
	const $1& a = castdown(p);
	register unsigned i = MIN(sz,a.sz);
	register $2* vv = v;
	register $2* av = a.v;
	while (i--) {
		if (*vv != *av) {
			if (*vv > *av) return 1;
			return -1;
		}
	}
	if (sz > a.sz) return 1;
	if (sz == a.sz) return 0;
	return -1;
}

void $1::dumpOn(ostream& strm) const
{
	strm << className() << '[';
	printOn(strm);
	strm << "]\n";
}

bool $1::isEqual(const Object& a) const
{
	return a.isSpecies(classDesc) && *this==castdown(a);
}

void $1::removeAll()
{
	register unsigned i = sz;
	register $2* vv = v;
	while (i--) *vv++ = 0;
}

const Class* $1::species() const { return $1::desc(); }

void $1::reSize(unsigned newsz)
{
	if (newsz<=0) AllocSizeErr();
	v = REALLOC(v,newsz);
	sz = newsz;
}

void $1::deepenShallowCopy()
{
	BASE::deepenShallowCopy();
}

unsigned $1::size() const	{ return sz; }

void $1::sort()
{
	qsort(v,sz,sizeof($2),$2Cmp);
}

extern const int NIHCL_ALLOCSIZE;
extern const int NIHCL_INDEXRANGE;

void $1::AllocSizeErr() const
{
	setError(NIHCL_ALLOCSIZE,DEFAULT,this,className());
}

void $1::IndexRangeErr() const
{
	setError(NIHCL_INDEXRANGE,DEFAULT,this,className());
}

Object* $1::add(Object&)
{
	shouldNotImplement("add");
	return 0;
}

Object*& $1::at(int)
{
	shouldNotImplement("at");
	return (Object*&)nil;
}

const Object *const& $1::at(int) const
{
	shouldNotImplement("at");
	return (Object *const&)nil;
}

Object* $1::doNext(Iterator&) const
{
	shouldNotImplement("doNext");
	return 0;
}

unsigned $1::occurrencesOf(const Object&) const
{
	shouldNotImplement("occurrencesOf");
	return 0;
}

Object* $1::remove(const Object&)
{
	shouldNotImplement("remove");
	return 0;
}
)
