/* Test class BitVec

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
	Internet:kgorlen@alw.nih.gov

Function:
	
Modification History:
	
$Log:	bitvec.c,v $
 * Revision 3.0  90/05/16  23:06:32  kgorlen
 * Release for 1st edition.
 * 
*/
#include "IntVec.h"
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/vectest/RCS/bitvec.c,v 3.0 90/05/16 23:06:32 kgorlen Rel $";

static int initI[] = { 1,3,5 };
static bitVecByte initA[] = { 0x0a, 0x03 };
static bitVecByte initB[] = { 0x0c, 0x02 };

static const IntVec I(initI,3);		// I = { 1 3 5 }
static const BitVec A(initA,10);	// A = { 0 1 0 1 0 0 0 0 1 1 }
static const BitVec B(initB,10);	// B = { 0 0 1 1 0 0 0 0 0 1 }

void test1()
{
// BitVec(unsigned)
	BitVec C;			// C = {}
// BitVec(const BitVec&)
	BitVec T(A);			// T = A
	cerr << "BitVec T(A): " << T << endl;
// BitVec(const BitSlice&)
	BitVec U(A(0,5,2));		// U = { 0 0 0 0 1 }
	cerr << "BitVec U(A(0,5,2)): " << U << endl;
// BitVec(unsigned,bool)
	BitVec V(10,YES);		// V = { 1 1 1 1 1 1 1 1 1 1 }
	cerr << "BitVec V(10,YES): " << V << endl;
// BitVec::operator=(const BitVec&)
	C = U;				// C = { 0 0 0 0 1 }
	cerr << "C = U: " << C << endl;
	C = C;
	cerr << "C = C: " << C << endl;
// BitVec::operator=(const BitSlice&)
	C = A(0,5,2);			// C = { 0 0 0 0 1 }
	cerr << "C = A(0,5,2): " << C << endl;
	C = A;  C = C(0,5,2);		// C = { 0 0 0 0 1 }
	cerr << "C = A; C = C(0,5,2): " << C << endl;
// BitVec::operator=(const BitSlct&)
	C = A[B];			// C = { 0 1 1 }
	cerr << "C = A[B]: " << C << endl;
	C = A;  C = C[B];		// C = { 0 1 1 }
	cerr << "C = A;  C = C[B]: " << C << endl;
// BitVec::operator=(const BitPick&)
	C = A[I];			// C = { 1 1 0 }
	cerr << "C = A[I]: " << C << endl;
	C = A;  C = C[I];		// C = { 1 1 0 }
	cerr << "C = A;  C = C[I]: " << C << endl;
// BitVec::operator=(bool)
	C = 0;				// C = { 0 0 0 }
	cerr << "C = 0: " << C << endl;
// BitVec::operator!(const BitVec&)
	C = !A;				// C = { 1 0 1 0 1 1 1 1 0 0 }
	cerr << "C = !A: " << C << endl;
// FRIEND_BitVec_OP_BitVec__BitVec
	C = A|B;			// C = { 0 1 1 1 0 0 0 0 1 1 }
	cerr << "C = A|B: " << C << endl;
// FRIEND_BitVec_ASNOP_BitVec
	C = A;  C ^= B;			// C = { 0 1 1 0 0 0 0 0 1 0 }
	cerr << "C = A;  C ^= B: " << C << endl;
}

void test2()
{
// BitVec(unsigned)
	BitVec C;			// C = {}
// BitSlice::operator=(const BitVec&)
	C = A;  C(0,5,2) = BitVec(5,YES);	// C = { 1 1 1 1 1 0 1 0 1 1 }
	cerr << "C = A;  C(0,5,2) = BitVec(5,YES): " << C << endl;
// BitSlice::operator=(const BitSlice&)
	C(1,5,2) = C(0,5,2);		// C = { 1 1 1 1 1 1 1 1 1 1 }
	cerr << "C(1,5,2) = C(0,5,2): " << C << endl;
// BitSlice::operator=(const BitPick&)
	C(0,3,1) = A[I];		// C = { 1 1 0 1 1 1 1 1 1 1 }
	cerr << "C(0,3,1) = A[I]: " << C << endl;
// BitSlice::operator=(const BitSlct&)
	C(3,3,1) = A[B];		// C = { 1 1 0 0 1 1 1 1 1 1 }
	cerr << "C(3,3,1) = A[B]: " << C << endl;
// BitSlice::operator=(bool)
	C(0,6,1) = 0;			// C = { 0 0 0 0 0 0 1 1 1 1 }
	cerr << "C(0,6,1) = 0: " << C << endl;
// BitVec operator!(const BitSlice&)
	C = !A(0,5,2);			// C = { 1 1 1 1 0 }
	cerr << "C = !A(0,5,2): " << C << endl;
// FRIEND_BitSlice_OP_BitSlice__Bitvec
	C = A(0,5,2)^B(1,5,2);		// C = { 0 1 0 0 0 }
	cerr << "C = A(0,5,2)^B(1,5,2): " << C << endl;
// FRIEND_BitSlice_ASNOP_BitSlice
	C = A;  C(0,5,2) ^= B(1,5,2);	// C = { 0 1 1 1 0 0 0 0 0 1 }
	cerr << "C = A;  C(0,5,2) ^= B(1,5,2): " << C << endl;
// BitPick::operator=(const BitVec&)
	C = A;  C[I] = BitVec(initA,3);	// C = { 0 0 0 1 0 0 0 0 1 1 }
	cerr << "C = A; C[I] =  BitVec(initA,3): " << C << endl;
// BitPick::operator=(const BitPick&)
	C[I] = A[I];			// C = { 0 1 0 1 0 0 0 0 1 1 }
	cerr << "C[I] = A[I]: " << C << endl;
// BitPick::operator=(const BitSlct&)
	C[I] = A[B];			// C = { 0 0 0 1 0 1 0 0 1 1 }	
	cerr << "C[I] = A[B]: " << C << endl;
// BitPick::operator=(const BitSlice&)
	C = A;  C[I] = A(0,3,2);	// C = { 0 0 0 0 0 0 0 0 1 1 }
	cerr << "C[I] = A(0,3,2): " << C << endl;
// BitPick::operator=(bool scalar)
	C[I] = YES;			// C = { 0 1 0 1 0 1 0 0 1 1 }
	cerr << "C[I] = YES: " << C << endl;
// BitPick::operator BitSlice()
	C = A[I]|B[I];			// C = { 1 1 0 }
	cerr << "C = A[I]|B[I]: " << C << endl;
// BitSlct::operator=(const BitVec&)
	C = A;  C[A] = BitVec(4,NO);
	cerr << "C = A;  C[A] = BitVec(4,NO): " << C << endl;	// C = { 0 0 0 0 0 0 0 0 0 0 }
// BitSlct::operator=(const BitPick&)
	C = B;  C[B] = A[I];
	cerr << "C = B;  C[B] = A[I]: " << C << endl;		// C = { 0 0 1 1 0 0 0 0 0 0 }
// BitSlct::operator=(const BitSlct&)
	C = A;  C[A] = B[A];					// C = { 0 0 0 1 0 0 0 0 0 1 }
	cerr << "C = A;  C[A] = B[A]: " << C << endl;
// BitSlct::operator=(const BitSlice&)
	C = A;  C[A] = B(0,4,1);				// C = { 0 0 0 0 0 0 0 0 1 1 }
	cerr << "C = A;  C[A] = B(0,4,1): " << C << endl;
// BitSlct::operator=(bool)
	C = A;  C[A] = NO;					// C = { 0 0 0 0 0 0 0 0 0 0 }
	cerr << "C = A;  C[A] = NO: " << C << endl;
// BitSlct::operator BitSlice()
	C = A[B]|B(0,3,1);					// C = { 0 1 1 }
	cerr << "C = A[B]|B(0,3,1): " << C << endl;
// BitVec reverse(const BitSlice&)
	C = reverse(B(0,4,1));
	cerr << "reverse(B(0,4,1)): " << C << endl;		// { 1 1 0 0 }
// int sum(const BitSlice&)
	cerr << "sum(A(1,5,2)): " << sum(A(1,5,2)) << endl;	// 3
}

main()
{
	cerr << "Test class BitVec\n";
	cerr << "IntVec I(3,1,2): " << I << endl;
// BitVec(bitVecByte*,unsigned)
	cerr << "BitVec A(initA,10): " << A << endl;
	cerr << "BitVec B(initB,10): " << B << endl;
	test1();
	test2();
}
