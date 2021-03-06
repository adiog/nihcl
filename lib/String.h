#ifndef	STRING_H
#define	STRING_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/String.h,v 3.0 90/05/20 00:21:38 kgorlen Rel $*/

/* String.h -- declarations for character strings

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Authors:
	C. J. Eppich and K. E. Gorlen
	Bg. 12A, Rm. 2033
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892

$Log:	String.h,v $
 * Revision 3.0  90/05/20  00:21:38  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Object.h"
#include <string.h>
#include <malloc.h>

const unsigned DEFAULT_STRING_EXTRA = 15;
class String;
class Range;

class SubString : public NIHCL {
	char* sp;		// substring pointer 
        unsigned sl;		// substring length 
	String* st;		// String this is a SubString of
	SubString(const String&, unsigned, unsigned);
	SubString(const SubString& ss) {
		sp = ss.sp; sl = ss.sl; st = ss.st;
	}
	int compare(const char*) const;
	int compare(const String&) const;
	int compare(const SubString&) const;
	void replace(const char* st, unsigned ln);
	void checkSubStr() const;
	friend String;
public:
	const char* ptr() const	{ return sp; }
	unsigned position() const;
	unsigned length() const	{ return sl; }

	void operator=(const String&);
	void operator=(const SubString&);
	void operator=(const char*);

	bool operator<(const String&) const;
	bool operator>(const String&) const;
	bool operator<=(const String&) const;
	bool operator>=(const String&) const;
	bool operator==(const String&) const; 
	bool operator!=(const String&) const;

	bool operator<(const SubString& ss) const	{ return compare(ss)<0; } 
	bool operator>(const SubString& ss) const	{ return compare(ss)>0; }
	bool operator<=(const SubString& ss) const	{ return compare(ss)<=0; }
	bool operator>=(const SubString& ss) const	{ return compare(ss)>=0; }
	bool operator==(const SubString& ss) const	{ return compare(ss)==0; }
	bool operator!=(const SubString& ss) const	{ return compare(ss)!=0; }

	bool operator<(const char* cs) const	{ return compare(cs) < 0; }   
	bool operator>(const char* cs) const	{ return compare(cs) > 0; }   
	bool operator<=(const char* cs) const	{ return compare(cs) <= 0; }
	bool operator>=(const char* cs) const	{ return compare(cs) >= 0; }
	bool operator==(const char* cs) const	{ return compare(cs) == 0; }
	bool operator!=(const char* cs) const	{ return compare(cs) != 0; }

	friend bool operator<(const char* cs, const SubString& ss) {
	    return ss.compare(cs) > 0;
	}
	friend bool operator>(const char* cs, const SubString& ss) {	 
	    return ss.compare(cs) < 0;
	}
	friend bool operator<=(const char* cs, const SubString& ss) { 
	    return ss.compare(cs) >= 0; 
	}
	friend bool operator>=(const char* cs, const SubString& ss) { 
	    return ss.compare(cs) <= 0;
	}
	friend bool operator==(const char* cs, const SubString& ss) {
	    return ss.compare(cs) == 0; 
	}
	friend bool operator!=(const char* cs, const SubString& ss) {
	    return ss.compare(cs) != 0; 
	}

	String operator&(const String&) const;
	String operator&(const SubString&) const;
	String operator&(const char*) const;
	friend String operator&(const char*, const SubString&);

	void dumpOn(ostream& strm =cerr) const;
	void printOn(ostream& strm =cout) const;
};

class String: public VIRTUAL Object {
	DECLARE_MEMBERS(String);
	char* p;		// character string
	unsigned len;		// length of string, excluding null character
	unsigned alloc;		// amount of storage allocated
	void indexRangeErr() const;
	friend SubString;
protected:		// storer() functions for object I/O
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;		
public:
	String(const char& c, unsigned l=1, unsigned extra=DEFAULT_STRING_EXTRA);
	String();
	String(unsigned extra);
	String(const char*);
	String(const char*, unsigned extra);
	String(const String&);
	String(const String&, unsigned extra);
	String(const SubString&);
	String(const SubString&, unsigned extra);
	~String();
	operator const char*() const	{ return p; }
	SubString operator()(unsigned pos, unsigned lgt);
	const SubString operator()(unsigned pos, unsigned lgt) const;
	SubString operator()(const Range& r);
	const SubString operator()(const Range& r) const;
	char& operator[](unsigned i) {
		if (i >= len) indexRangeErr();
		return p[i];
    	}
	char operator[](unsigned i) const {
		if (i >= len) indexRangeErr();
		return p[i];
    	}

	void operator=(const String&);
	void operator=(const SubString&);
	void operator=(const char*);

	bool operator<(const String& s) const	{ return strcmp(p, s.p) < 0; }
	bool operator>(const String& s) const	{ return strcmp(p, s.p) > 0; }
	bool operator<=(const String& s) const	{ return strcmp(p, s.p) <= 0; }
	bool operator>=(const String& s) const	{ return strcmp(p, s.p) >= 0; }
	bool operator==(const String& s) const;
	bool operator!=(const String& s) const	{ return !(*this==s); }

	bool operator<(const SubString& ss) const 	{ return ss.compare(*this) > 0; }
	bool operator>(const SubString& ss) const	{ return ss.compare(*this) < 0; }
	bool operator<=(const SubString& ss) const	{ return ss.compare(*this) >= 0; }
	bool operator>=(const SubString& ss) const	{ return ss.compare(*this) <= 0; }
	bool operator==(const SubString& ss) const	{ return ss.compare(*this) == 0; }
	bool operator!=(const SubString& ss) const	{ return ss.compare(*this) != 0; }

	bool operator<(const char* cs) const	{ return strcmp(p,cs) < 0; }   
	bool operator>(const char* cs) const	{ return strcmp(p,cs) > 0; }   
	bool operator<=(const char* cs) const	{ return strcmp(p,cs) <= 0; }
	bool operator>=(const char* cs) const	{ return strcmp(p,cs) >= 0; }
	bool operator==(const char* cs) const	{ return strcmp(p,cs) == 0; }
	bool operator!=(const char* cs) const	{ return strcmp(p,cs) != 0; }

	friend bool operator<(const char* cs, const String& s) {
	    return strcmp(cs, s.p) < 0;
	}
	friend bool operator>(const char* cs, const String& s) {	 
	    return strcmp(cs, s.p) > 0;
	}
	friend bool operator<=(const char* cs, const String& s) { 
	    return strcmp(cs, s.p) <= 0; 
	}
	friend bool operator>=(const char* cs, const String& s) { 
	    return strcmp(cs, s.p) >= 0;
	}
	friend bool operator==(const char* cs, const String& s) {
	    return strcmp(cs, s.p) == 0; 
	}
	friend bool operator!=(const char* cs, const String& s) {
	    return strcmp(cs, s.p) != 0; 
	}

	String operator&(const String& s) const;
	String operator&(const SubString& ss) const;
	String operator&(const char* cs) const;
	friend String operator&(const char*, const SubString&);
	friend String operator&(const char* cs, const String& s);

	String& operator&=(const String&);
	String& operator&=(const SubString&);
	String& operator&=(const char* cs);

	char& at(unsigned i)			{ return (*this)[i]; }
	char at(unsigned i) const		{ return (*this)[i]; }
	unsigned length() const	{ return len; } 
	unsigned reSize(unsigned new_capacity);

	virtual void toAscii();
	virtual void toLower();
	virtual void toUpper();
	virtual unsigned capacity() const;
	virtual int compare(const Object& ob) const;
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual void scanFrom(istream& strm);
	virtual unsigned size() const;
	virtual const Class* species() const;
};

inline ostream& operator<<(ostream& strm, const SubString& ss)
{
	ss.printOn(strm);
	return(strm);
}

inline SubString::SubString(const String& s, unsigned pos, unsigned lgt)
{ 
	sp = &((String&)s).p[pos];
	sl = lgt;
	st = &(String&)s;
	checkSubStr();
}
	
inline unsigned SubString::position() const	{ return sp - st->p; }

inline SubString String::operator()(unsigned pos, unsigned lgt)
{	
	return SubString(*this, pos, lgt);
}

inline const SubString String::operator()(unsigned pos, unsigned lgt) const
{	
	return SubString(*this, pos, lgt);
}

inline bool SubString::operator<(const String& s) const { return compare(s) < 0; }
inline bool SubString::operator>(const String& s) const { return compare(s) > 0; }
inline bool SubString::operator<=(const String& s) const { return compare(s) <= 0; }
inline bool SubString::operator>=(const String& s) const { return compare(s) >= 0; }
inline bool SubString::operator==(const String& s) const { return compare(s) == 0; }
inline bool SubString::operator!=(const String& s) const { return compare(s) != 0; }

#endif

