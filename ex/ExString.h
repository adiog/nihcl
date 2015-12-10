// ExString.h -- Dynamic character strings

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ExString.h,v 3.0 90/05/15 22:43:35 kgorlen Rel $

#include <string.h>
#include <iostream.h>

const unsigned EXTRA = 7;   // default # characters extra
typedef int bool;
class String;

class SubString {
    char* sp;               // substring pointer 
    unsigned sl;            // substring length 
    SubString(const String&, unsigned, unsigned);
    SubString(const SubString&);        // private copy constructor
    friend String;
public:
    void operator=(const SubString& from);
    bool operator==(const String&) const;
    String operator&(const String&) const;
};

class String  {
    char* p;            // pointer to character string
    unsigned len;       // length of string
    unsigned alloc;     // amount of storage allocated
    friend SubString;
public:
    String(unsigned extra=EXTRA);   // construct an empty String
    String(const char* cs, unsigned extra=EXTRA);
                                    // construct from C string
    String(const String&);          // construct one String
                                    // from another
    String(const SubString&);       // construct from a SubString
    ~String() { delete(p); }
    operator const char*() const { return p; }
                                    // convert to a C string
    SubString operator()(unsigned pos, unsigned lgt);
    const SubString operator()(unsigned pos, unsigned lgt) const;
    char& operator[](unsigned pos) {
//      if (pos >= len)  error
        return p[pos];
        }
    char operator[](unsigned pos) const {
//      if (pos >= len)  error
        return p[pos];
        }
    void operator=(const String&);
    bool operator==(const String& s) const {
        return strcmp(p, s.p) == 0;
    }
    String operator&(const String& s) const;
    void operator&=(const String& s);
    unsigned length() const   { return len; }
    unsigned capacity() const { return alloc-1; }
    void printOn(ostream& strm) const;
    void scanFrom(istream& strm);
};

inline SubString::SubString(const String& s,
                            unsigned pos, unsigned lgt)
{
    sp = &((String&)s)[pos];
//  if (pos+lgt >= s.len)  error
    sl = lgt;
}

inline SubString::SubString(const SubString& ss)
{
    sp = ss.sp;  sl = ss.sl;
}

inline void SubString::operator=(const SubString& from)
{
    strncpy(sp, from.sp, sl);
}

inline bool SubString::operator==(const String& s) const
{
    return strncmp(sp, s.p, sl) == 0;
}

extern ostream& operator<<(ostream&, const String&);
extern istream& operator>>(istream&, String&);
