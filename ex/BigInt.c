// BigInt.c -- Multiple-precision integer class

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/BigInt.c,v 3.0 90/05/15 22:43:26 kgorlen Rel $

#include "BigInt.h"
#include <string.h>
#include <ctype.h>

BigInt::BigInt(const char* digitString)
{
    unsigned n = strlen(digitString);
    if (n != 0) {
        digits = new char[ndigits=n];
        char* p = digits;
        const char* q = &digitString[n];
        while (n--) *p++ = *--q - '0';  // convert ASCII digit
                                        // to binary
    }
    else {                              // empty string
        digits = new char[ndigits=1];
        digits[0] = 0;
    }
}

BigInt::BigInt(unsigned n)
{
    char d[3*sizeof(unsigned)+1];   // buffer for decimal digits
    char* dp = d;                   // pointer to next
                                    // decimal digit
    ndigits = 0;
    do {                            // convert integer to
                                    // decimal digits
        *dp++ = n%10;
        n /= 10;
        ndigits++;
    } while (n > 0);
    digits = new char[ndigits];     // allocate space for
                                    // decimal digits
    for (register i=0; i<ndigits; i++) digits[i] = d[i];
}

BigInt::BigInt(const BigInt& n)
{
    unsigned i = n.ndigits;
    digits = new char[ndigits=i];
    char* p = digits;
    char* q = n.digits;
    while (i--) *p++ = *q++;
}

void BigInt::operator=(const BigInt& n)
{
    if (this == &n) return;     // to handle x = x correctly
    delete digits;
    unsigned i = n.ndigits;
    digits = new char[ndigits=i];
    char* p = digits;
    char* q = n.digits;
    while (i--) *p++ = *q++;
}

BigInt BigInt::operator+(const BigInt& n) const
{
    unsigned maxDigits =
        (ndigits>n.ndigits ? ndigits : n.ndigits)+1;
    char* sumPtr = new char[maxDigits];
    BigInt sum(sumPtr,maxDigits); // allocate storage for sum
    DigitStream a(*this);
    DigitStream b(n);
    unsigned i = maxDigits;
    unsigned carry = 0;
    while (i--) {
        *sumPtr = (a++) + (b++) + carry;
        if (*sumPtr >= 10) {
            carry = 1;
            *sumPtr -= 10;
        }
        else carry = 0;
        sumPtr++;
    }
    return sum;
}

void BigInt::print(FILE* f) const
{
    for (int i = ndigits-1; i >= 0; i--) fprintf(f,"%d",digits[i]);
}

void BigInt::scanFrom(istream& strm)
{
    delete digits;
    ndigits = 0;  digits = NULL;
    strm >> ws;                     // skip leading whitespace
    scanChunk(strm);
}

char* BigInt::scanChunk(istream& strm)
{
    const unsigned CHUNKSIZE = 3;   // read CHUNKSIZE digits
                                    // at a time
    char chunk[CHUNKSIZE];          // buffer to hold digits read
    register char* p = chunk;       // pointer to digit buffer
    register char* q;               // pointer to BigInt
                                    // object digits
    register i;                     // digits read in this chunk
// read a chunk of digits until eof or non-digit
    for (i=0; i<CHUNKSIZE; i++) {   // read a chunk of digits
        strm.get(*p);               // get next character
        if (!strm.eof() && isdigit(*p)) 
            *p++ -= '0';            // convert to digit
        else {                      // encountered eof or non-digit
            ndigits += i;           // now we know the number
                                    // of digits
            if (ndigits != 0) {     // save digits just read
                q = digits = new char[ndigits];
                for (; i>0; i--) *q++ = *--p;
                return q;           // q now points after
                                    // last digit
            }
            else {                  // failed to find any digits,
                                    // so set istream state to fail
                strm.clear(strm.rdstate() | ios::failbit);
                return NULL;
            }
        }
    }
// At his point we have read CHUNKSIZE digits into chunk, and
// there may still be digits left on the input stream, so
// call scanChunk() recursively to read the next chunk.
    ndigits += i;                   // add no. of digits just read
    q = scanChunk(strm);            // q now points after
                                    // last digit
    if ( q==NULL ) return NULL;
    for (; i>0; i--) *q++ = *--p;   // add digits just read
    return q;                       // q now points after
                                    // last digit
}

void BigInt::printOn(ostream& strm) const
{
    for (register i = ndigits-1; i >= 0; i--)
        strm << (int)digits[i];
}
