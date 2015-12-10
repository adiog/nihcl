/* Regex.c  -- implementation of NIHCL class Regex

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
	December, 1987

Function:

Regex is a class derived from String and containing a regular
expression and its compiled form.  It implements functions that search
Strings for and match Strings with regular expressions using the
regular expression code from GNU Emacs Version 18.41 (regex.c).

Note that when a Regex is printed, only the String portion is printed,
not the compiled form.
	
$Log:	Regex.c,v $
 * Revision 3.0  90/05/20  00:21:01  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Regex.h"
#include "nihclIO.h"
#include <ctype.h>
#include <iomanip.h>
#include <libc.h>

#ifdef SYSV

#include <memory.h>
inline void bcopy(void* from, void* to, int sz)
{
	memcpy(to,from,sz);
}

#endif

#define	THIS	Regex
#define	BASE	String
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Regex,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Regex.c,v 3.0 90/05/20 00:21:01 kgorlen Rel $",NULL,NULL);

const unsigned Regex::DEFAULT_BUFSIZE = 64;

extern const int NIHCL_BADREGEX;

/*
extern const char* re_compile_pattern(
	const char*,	// the address of the pattern string
	int size,	// the length of the pattern string
	struct re_pattern_buffer* bufp);

re_compile_pattern takes a regular-expression descriptor string in the
user's format and converts it into a buffer full of byte commands for
matching.

  pattern   is the address of the pattern string
  size      is the length of it.
  bufp	    is a  struct re_pattern_buffer *  which points to the info
	    on where to store the byte commands.
	    This structure contains a  char *  which points to the
	    actual space, which should have been obtained with malloc().
	    compile_pattern may use realloc() to grow the buffer space.

The number of bytes of commands can be found out by looking in the
struct re_pattern_buffer that bufp pointed to, after compile_pattern
returns.
*/

/*
extern int re_match(struct re_pattern_buffer*, const char*, int size,
	int pos, struct re_registers*);

extern int re_match_2(
	struct re_pattern_buffer* pbufp,
	const char* string1, int size1,
	const char* string2, int size2,
	int pos,
	struct re_registers*,
	int mstop);

Match the pattern described by `pbufp' against data which is the
virtual concatenation of `string1' and `string2'.  `size1' and `size2'
are the sizes of the two data strings.  Start the match at position
`pos'.  Do not consider matching past the position `mstop'.

If pbufp->fastmap is nonzero, then it had better be up to date.

The reason that the data to match is specified as two components which
are to be regarded as concatenated is so that this function can be
used directly on the contents of an Emacs buffer.

-1 is returned if there is no match.  Otherwise the value is the
length of the substring which was matched.

re_match just calls re_match_2 with size1=0 and mstop=size.
*/

/*
extern int re_search(struct re_pattern_buffer*,	const char*, int size,
	int startpos, int range, struct re_registers*);

extern int re_search_2(
	struct re_pattern_buffer*,
	const char*, int size1,
	const char*, int size2,
	int startpos,
	int range,
	struct re_registers*,
	int mstop);

Like re_match_2 but tries first a match starting at index `startpos',
then at startpos + 1, and so on.  `range' is the number of places to
try before giving up.  If `range' is negative, the starting positions
tried are startpos, startpos - 1, etc.  It is up to the caller to make
sure that range is not so large as to take the starting position
outside of the input strings.

The value returned is the position at which the match was found, or -1
if no match was found.

re_search just calls re_search_2 with size1=0 and mstop=size.
*/

const unsigned BYTEWIDTH = 8;	// width of a byte in bits

void Regex::re_compile_pattern()
{
	const char* error = ::re_compile_pattern(*this,length(),&pattern);
	if (error) errRegex(error);
}

int Regex::re_match(const String& str, int pos)
{
	int len = ::re_match(&pattern, str, str.length(), pos, &regs);
	setGroups(len);
	return len;
}

void Regex::init(int bufsize)
{
	pattern.buffer = (char*)malloc(bufsize);
	pattern.allocated = bufsize;
	pattern.used = 0;
	pattern.fastmap = 0;
	pattern.translate = 0;
	ngroups = 0;
	for (int i=0; i<RE_NREGS; i++) {
		regs.start[i] = regs.end[i] = -1;
	}
}

void Regex::fixCopy()
// copy heap storage in a struct re_pattern_buffer
{
	register char* oldp = pattern.buffer;
	pattern.buffer = (char*)malloc(pattern.allocated);
	bcopy(oldp,pattern.buffer,pattern.used);
	if (pattern.fastmap) {
		oldp = pattern.fastmap;
		pattern.fastmap = (char*)malloc(1<<BYTEWIDTH);
		bcopy(oldp,pattern.fastmap,1<<BYTEWIDTH);
	}
}

void Regex::setGroups(int result)
// set number of groups matched by last match/search
{
	ngroups = 0;
	if (result == -1) return;
	for (register i=0; i<RE_NREGS; i++) {
		if (regs.start[i] == -1) return;
		ngroups++;
	}
}

void Regex::errRegex(const char* s) const
{
	const char* re = *this;
	setError(NIHCL_BADREGEX,DEFAULT,s,this,re);
}

Regex::Regex(unsigned bufsize)
{
	init(bufsize);
}

Regex::Regex(const char* rexp, unsigned bufsize) : BASE(rexp)
{
	init(bufsize);
	re_compile_pattern();
}

Regex::Regex(const Regex& rexp) : BASE(rexp)
{
// A copy is more efficient than re_compile_pattern()
	pattern = rexp.pattern;
	regs = rexp.regs;
	fixCopy();
}

Regex::~Regex()
{
	free(pattern.buffer);
	if (pattern.fastmap) free(pattern.fastmap);
}

Range Regex::operator[](unsigned i) const
{
	if (i >= ngroups) return Range(0,-1);	// should raise exception
	return Range(regs.start[i],regs.end[i]-regs.start[i]);
}

void Regex::operator=(const char* cs)
{
	*(String*)this=cs;
	re_compile_pattern();
}

void Regex::operator=(const Regex& rexp)
{
	if (this == &rexp) return;	// watch out for x = x
	*(String*)this=rexp;		// copy the String part
	free(pattern.buffer);
	pattern = rexp.pattern;
	regs = rexp.regs;
	fixCopy();
}

void Regex::operator=(const String& str)
{
	*(String*)this = str;
	re_compile_pattern();
}

void Regex::operator=(const SubString& substr)
{
	*(String*)this = substr;
	re_compile_pattern();
}

void Regex::deepenShallowCopy()
// Called by deepCopy() to convert a shallow copy to a deep copy.
{
	BASE::deepenShallowCopy();
	fixCopy();
}

void Regex::scanFrom(istream& strm)
{
	String::scanFrom(strm);
	re_compile_pattern();
}

void Regex::toAscii()
{
	String::toAscii();
	re_compile_pattern();
}

void Regex::toLower()
{
	String::toLower();
	re_compile_pattern();
}

void Regex::toUpper()
{
	String::toUpper();
	re_compile_pattern();
}

void Regex::storer(OIOout& strm) const
{
	BASE::storer(strm);
	strm << pattern.allocated << ngroups;
	for (int i=0; i<ngroups; i++) {
		strm << regs.start[i] << regs.end[i];
	}
}

Regex::Regex(OIOin& strm)
:
#ifdef MI
	Object(strm),
#endif
	BASE(strm)	
{
	int bufsize;
	strm >> bufsize;
	init(bufsize);
	re_compile_pattern();
	strm >> ngroups;
	for (int i=0; i<ngroups; i++) {
		strm >> regs.start[i] >> regs.end[i];
	}
}

void Regex::storer(OIOofd& fd) const
{
	BASE::storer(fd);
	fd << pattern.allocated;
	fd << ngroups;
	for (int i=0; i<ngroups; i++) {
		fd << regs.start[i];
		fd << regs.end[i];
	}
}

Regex::Regex(OIOifd& fd)
:
#ifdef MI
	Object(fd),
#endif
	BASE(fd)	
{
	int bufsize;
	fd >> bufsize;
	init(bufsize);
	re_compile_pattern();
	fd >> ngroups;
	for (int i=0; i<ngroups; i++) {
		fd >> regs.start[i];
		fd >> regs.end[i];
	}
}

bool Regex::match(const String& s, int pos)
// Check for match of Regex at index pos of String s.
{
	return re_match(s,pos) != -1;
}		

int Regex::search(const String& str, int startpos)
// Search for next match of Regex in str beginning at startpos.
// Return position of match or -1 if no match.
{
	return search(str,startpos,str.length()-startpos);
}

int Regex::search(const String& str, int startpos, int range)
// Search for next match of Regex in str beginning at startpos.
// Try no more than abs(range) times.
// Search backwards if range < 0.
// Return position of match or -1 if no match.
{
	if (!pattern.fastmap) pattern.fastmap = (char*)malloc(1 << BYTEWIDTH);
	int pos = ::re_search(&pattern, str, str.length(), startpos, range, &regs);
	setGroups(pos);
	return pos;
}

static void printByte(ostream& strm, char b)
{
	if (isprint(b)) {
		if (b == '\\') strm << '\\';
		strm.put(b);
	}
 	else strm << "\\" << setfill('0') << setw(3) << oct << (b&0377);
}

void Regex::dumpOn(ostream& strm) const
{
	strm << "regular expression: " << *this << '\n';
	strm << "compiled form: ";
	for (int i=0; i<pattern.used; i++) printByte(strm,pattern.buffer[i]);
	strm << '\n';
	strm << "allocated: " << pattern.allocated << '\n';
	strm << "used: " << pattern.used << '\n';
	if (pattern.fastmap) {
		strm << "fastmap: ";
		for (i=0; i < (1 << BYTEWIDTH); i++) {
			if (pattern.fastmap[i]) printByte(strm,i);
		}
		strm << '\n';
	}
	strm << "fastmap accurate: " << (pattern.fastmap_accurate ? "YES" : "NO") << '\n';
	strm << "match null string: " << (pattern.can_be_null ? "YES" : "NO") << '\n';
	strm << "groups: " << groups() << '\n';
	for (i=0; i<RE_NREGS; i++) {
		if (regs.start[i] == -1) break;
		strm << "regs[" << i << "]:	" << regs.start[i] << ',' << regs.end[i] << '\n';
	}
}
