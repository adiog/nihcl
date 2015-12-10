/* Arraychar.p -- type-specific functions for class Arraychar

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
	
Type-specific functions for class Arraychar, such as hash() and
printOn().  Generic functions are generated from the m4 template file
Array.c.m4.

WARNING -- Make changes to the .p or .m4 files, not to the .c file
they generate.

$Log:	Arraychar.p,v $
 * Revision 3.0  90/05/20  00:19:00  kgorlen
 * Release for 1st edition.
 * 
*/

`#include' "Arraychar.h"
`#include' "nihclconfig.h"
`#include' <iomanip.h>
`#include' <libc.h>
`#include' "nihclIO.h"

`#define'	THIS	Arraychar
`#define'	BASE	Collection
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Arraychar,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Arraychar.p,v 3.0 90/05/20 00:19:00 kgorlen Rel $",NULL,NULL);

static int charCmp(const void* a, const void* b)
{
	return *(const unsigned char*)a - *(const unsigned char*)b;
}

union hash_char_mask {
	unsigned in[sizeof(int)];
	char ch[sizeof(int)*sizeof(int)];
	hash_char_mask();
} mask;

hash_char_mask::hash_char_mask()
{
	for (register unsigned i=0; i<sizeof(int); i++) {
		for (register unsigned j=0; j<sizeof(int); j++) ch[sizeof(int)*i+j] = j<i ? 0xff : 0;
	}
}

unsigned THIS::hash() const
{
	register unsigned h = sz;
	register unsigned i = div_sizeof_int(sz);
	register unsigned* vv = (unsigned*)v;
	while (i--) h ^= *vv++;
	if ((i = mod_sizeof_int(sz)) != 0)
		h ^= *vv & mask.in[i];
	return h;
}

void THIS::printOn(ostream& strm) const
{
	for (register unsigned i=0; i<sz; i++) {
		if (i > 0) strm << "  ";
 		strm << "0x" << setfill('0') << setw(2)
 		     << hex << ((unsigned int)(unsigned char)v[i]);
	}
	strm << dec;
}

THIS::THIS(OIOin& strm)
:
#ifdef MI
	Object(strm),
#endif
	BASE(strm)
{
	strm >> sz;
	v = NEW(char,sz);
	strm.get(v,sz);
}

void THIS::storer(OIOout& strm) const
{
	BASE::storer(strm);
	strm << sz;
	strm.put(v,sz);
}

Arraychar::Arraychar(OIOifd& fd)
:
#ifdef MI
	Object(fd),
#endif
	BASE(fd)
{
	fd >> sz;
	v = NEW(char,sz);
	fd.get(v,sz);
}

void Arraychar::storer(OIOofd& fd) const
{
	BASE::storer(fd);
	fd << sz;
	fd.put(v,sz);
}

ARRAYIMPLEMENT(Arraychar,char)
