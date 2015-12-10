// ExString.c -- Dynamic character strings

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ExString.c,v 3.0 90/05/15 22:43:34 kgorlen Rel $

#include "ExString.h"
#include <malloc.h>

inline unsigned MAX(unsigned a, unsigned b)
     { return a >= b ? a : b; }

String::String(unsigned extra)
// Construct an empty String
{
    len = 0;
    p = new char[alloc = extra+1];
    *p = '\0';
}

String::String(const char* cs, unsigned extra)
// Construct a String from a C string
{ 
    len = strlen(cs);
    p = new char[alloc = len+extra+1];
    strcpy (p,cs); 
}

String::String(const String& s)
// Construct one String from another
{
    len = s.len;
    p = new char[alloc = s.alloc];
    strcpy (p,s.p);
}
 
String::String(const SubString& ss)
// Construct a String from a SubString
{
    len = ss.sl;
    p = new char[alloc = len + 1];
    strncpy(p,ss.sp,len);
    p[len] = '\0';
}

SubString String::operator()(unsigned pos, unsigned lgt)
// Extract a SubString from a String
{   
    return SubString(*this, pos, lgt);
}

const SubString String::operator()(unsigned pos,
                                   unsigned lgt) const
// Extract a SubString from a String
{   
    return SubString(*this, pos, lgt);
}

void String::operator=(const String& s)
// Assign one String to another
{
    if (p == s.p) return;
    len = s.len;
    if (len >= alloc) {
        delete p;
        p = new char[alloc = s.alloc];
    }
    strcpy (p,s.p);
}

void String::operator&=(const String& s)
// Concatenate a String with another
{
    if (alloc <= len + s.len) {
        alloc += s.len;
        p = realloc(p, alloc);  // this is slightly dangerous!
    }
    strcpy (&p[len],s.p);
    len += s.len;
}   

void String::printOn(ostream& strm) const
// Print this String on an ostream
{
    strm << p;
}

void String::scanFrom(istream& strm)
// Read next line of input from strm into this String.
{
    char c;
    strm.get(c);
    if (c != '\n') strm.putback(c);
    char temp[513];
    strm.get(temp,513);
    *this = String(temp);
}

ostream& operator<<(ostream& strm, const String& s)
// Print String s on ostream strm
{
    s.printOn(strm);
    return strm;
}

istream& operator>>(istream& strm, String& s)
// Read String s from istream strm
{
    s.scanFrom(strm);
    return strm;
}

String SubString::operator&(const String& s) const
// Concatenate a SubString and a String
{
    String t(sl + s.alloc - 1);
    strncpy(t.p, sp, sl);
    strcpy(&(t.p[sl]), s.p);
    t.len = sl + s.len;
    return t;
}
