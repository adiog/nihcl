// BigInt.h -- Multiple-precision integer class

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/BigInt.h,v 3.0 90/05/15 22:43:27 kgorlen Rel $

#include <stdio.h>
#include <iostream.h>

class BigInt {
    char* digits;           // pointer to digit array in free store
    unsigned ndigits;       // number of digits
    BigInt(char* d, unsigned n) {   // constructor function
        digits = d;
        ndigits = n;
    }
    friend DigitStream;
    char* scanChunk(istream&);      // read a chunk of digits
public:
    BigInt(const char*);            // constructor function
    BigInt(unsigned n =0);          // constructor function
    BigInt(const BigInt&);          // copy constructor function
    void operator=(const BigInt&);  // assignment
    BigInt operator+(const BigInt&) const;  // addition operator
                                            // function
    void print(FILE* f =stdout) const;      // printing function
    ~BigInt()   { delete digits; }          // destructor function
    void printOn(ostream&) const;           // printing function
    void scanFrom(istream&);                // reading function
};

inline istream& operator>>(istream& strm, BigInt& b)
{
    b.scanFrom(strm);
    return strm;
}

inline ostream& operator<<(ostream& strm, const BigInt& b)
{
    b.printOn(strm);
    return strm;
}

class DigitStream {
    char* dp;               // pointer to current digit
    unsigned nd;            // number of digits remaining
public:
    DigitStream(const BigInt& n) {  // constructor function
        dp = n.digits;
        nd = n.ndigits;
    }
    unsigned operator++() {         // return current digit
                                    // and advance
        if (nd == 0) return 0;
        else {
            nd--;
            return *dp++;
        }
    }
};
