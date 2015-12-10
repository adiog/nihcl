#ifndef	REGEX_H
#define	REGEX_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Regex.h,v 3.0 90/05/20 13:31:16 kgorlen Rel $*/

/* Regex.h -- header file for class Regex

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
	December, 1987

$Log:	Regex.h,v $
 * Revision 3.0  90/05/20  13:31:16  kgorlen
 * Release for 1st edition.
 * 
*/

#include "String.h"
#include "Range.h"
#include "regex.h"

class Regex: public String {
	DECLARE_MEMBERS(Regex);
	struct re_pattern_buffer pattern;
	unsigned ngroups;	// 1 + number of \( \) groups in pattern
	struct re_registers regs;
	void re_compile_pattern();
	int re_match(const String&, int pos=0);
	void init(int bufsize);
	void fixCopy();
	void setGroups(int);
	void errRegex(const char*) const;
public:
	static const unsigned DEFAULT_BUFSIZE;
protected:		// storer() functions for object I/O
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	Regex(unsigned bufsize =DEFAULT_BUFSIZE);
	Regex(const char*, unsigned bufsize =DEFAULT_BUFSIZE);
	Regex(const Regex&);
	~Regex();
	operator const char*() const	{ return *(const String*)this; }
	Range operator[](unsigned) const;
	unsigned groups() const	{ return ngroups; }
	bool match(const String&, int pos=0);
	int search(const String&, int startpos=0);
	int search(const String&, int startpos, int range);
	void operator=(const char*);
	void operator=(const String&);
	void operator=(const SubString&);
	void operator=(const Regex&);
	virtual void dumpOn(ostream& strm =cerr) const;
	virtual void deepenShallowCopy();
	virtual void scanFrom(istream& strm);
	virtual void toAscii();
	virtual void toLower();
	virtual void toUpper();
private:
	String& operator&=(const String&)	{ shouldNotImplement("operator&="); return *this; }
	String& operator&=(const SubString&)	{ shouldNotImplement("operator&="); return *this; }
	String& operator&=(const char*)		{ shouldNotImplement("operator&="); return *this; }
};


#endif
