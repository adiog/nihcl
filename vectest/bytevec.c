/* Test Vector ByteVec class

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
        Ted Persky
	Bg. 12A, Rm. 2031
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892
	Phone: (301) 496-2963
	uucp: uunet!nih-csl!tpersky
	Internet:tpersky@alw.nih.gov

Function:
	
Modification History:
	
$Log:	bytevec.c,v $
 * Revision 3.0  90/05/16  23:06:33  kgorlen
 * Release for 1st edition.
 * 
*/
#include "IntVec.h"
#include "ByteVec.h"
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/vectest/RCS/bytevec.c,v 3.0 90/05/16 23:06:33 kgorlen Rel $";

static int initI[] = { 1,3,5 };
static const IntVec I(initI,3);		// I = { 1 3 5 }

#ifndef BUG_OPTYPECONST
static ByteVec A(10,1);				// A = { 1 2 3 4 5 6 7 8 9 10 }
static ByteVec B = reverse(ByteVec(10,1,1));	// B = { 10 9 8 7 6 5 4 3 2 1 }
#else
static const ByteVec A(10,1);				// A = { 1 2 3 4 5 6 7 8 9 10 }
static const ByteVec B = reverse(ByteVec(10,1,1));	// B = { 10 9 8 7 6 5 4 3 2 1 }
#endif

void test1()
{
	BitVec L;
// TYPEVec_CTOR_I
	ByteVec C;			// C = {}
// TYPEVec_CTOR_I_TYPE_TYPE
        ByteVec D(10,3,1);    // D = { 3 4 5 6 7 8 9 10 11 12 }
	cerr << "ByteVec D(10,3,1): " << D << endl;
// FRIEND_reverse_TYPESlice
	D = reverse(D);       // D = { 12 11 10 9 8 7 6 5 4 3 }
	cerr << "reverse(D): " << D << endl;
// TYPEVec_CTOR_TYPEVec	
	ByteVec T(A);			// T = A
	cerr << "ByteVec T(A): " << T << endl;
// TYPEVec_CTOR_TYPESlice
	ByteVec U(A(0,5,2));		// U = { 1 3 5 7 9 }
	cerr << "ByteVec U(A(0,5,2)): " << U << endl;
// TYPEVec_ASN_TYPEVec
	C = U;
	cerr << "C = U: " << C << endl;
// TYPEVec_ASN_TYPEVec
	C = C;
	cerr << "C = C: " << C << endl;
// TYPEVec_ASN_TYPESlice
	C = A(0,5,2);			// C = { 1 3 5 7 9 }
	cerr << "C = A(0,5,2): " << C << endl;
// TYPEVec_ASN_TYPESlice
	C = A;  C = C(0,5,2);		// C = { 1 3 5 7 9 }
	cerr << "C = A; C = C(0,5,2): " << C << endl;
// TYPEVec_ASN_TYPESlct
	C = A[A>B];			// C = { 6 7 8 9 10 }
	cerr << "C = A[A>B]: " << C << endl;
// TYPEVec_ASN_TYPESlct
	C = A;  C = C[C>B];		// C = { 6 7 8 9 10 }
	cerr << "C = A;  C = C[C>B]: " << C << endl;
// TYPEVec_ASN_TYPEPick
	C = A[I];			// C = { 2 4 6 }
	cerr << "C = A[I]: " << C << endl;
// TYPEVec_ASN_TYPEPick
	C = A;  C = C[I];		// C = { 2 4 6 }
	cerr << "C = A;  C = C[I]: " << C << endl;
// TYPEVec_ASN_TYPE
	C = 0;
	cerr << "C = 0: " << C << endl;
// TYPESlice_ASN_TYPEVec
	C = A;  C(0,5,2) = ByteVec(5,50,0);	// C = { 50 2 50 4 50 6 50 8 50 10 }
	cerr << "C = A;  C(0,5,2) = ByteVec(5,50,0): " << C << endl;
// TYPESlice_ASN_TYPESlice
	C(1,5,2) = C(0,5,2);		// C = { 50 50 50 50 50 50 50 50 50 50 }
	cerr << "C(1,5,2) = C(0,5,2): " << C << endl;
// TYPESlice_ASN_TYPEPick
	C(0,3,1) = A[I];		// C = { 2 4 6 50 50 50 50 50 50 50 }
	cerr << "C(0,3,1) = A[I]: " << C << endl;
// TYPESlice_ASN_TYPESlct
	C(3,3,1) = A[A<=3];		// C = { 2 4 6 1 2 3 50 50 50 50 }
	cerr << "C(3,3,1) = A[A<=3]: " << C << endl;
// TYPESlice_ASN_TYPE
	C(0,6,1) = 0;			// C = { 0 0 0 0 0 0 50 50 50 50 }
	cerr << "C(0,6,1) = 0:" << C << endl;
// FRIEND_INCDECOP_TYPESlice__TYPEVec
//	C++;				// C = { 1 1 1 1 1 1 51 51 51 51 }
	cerr << "C++: "; (C++).printOn(cerr); cerr << endl;
// FRIEND_TYPESlice_OP_TYPESlice__TYPEvec
	C = D-B;			// C = { 2 2 2 2 2 2 2 2 2 2 }
	cerr << "C = D-B: " << C << endl;
// FRIEND_TYPESlice_OP_TYPE__TYPEVec
	C = A-1;			// C = { 0 1 2 3 4 5 6 7 8 9 }
	cerr << "C = A-1: " << C << endl;
// FRIEND_TYPE_OP_TYPESlice__TYPEVec
	C = 1 + A;			// C = { 2 3 4 5 6 7 8 9 10 11 }
	cerr << "C = 1+A: " << C << endl;
// FRIEND_TYPESlice_OP_TYPESlice__BitVec
	L = A>B;
	cerr << "A>B: " << L << endl;	// { 0 0 0 0 0 1 1 1 1 1 }
// FRIEND_TYPESlice_OP_TYPE__BitVec
	L = A<=5;			// { 1 1 1 1 1 0 0 0 0 0 }
	cerr << "A<=5: " << L << endl;
// FRIEND_TYPE_OP_TYPESlice__BitVec
	L = 5<A;			// { 0 0 0 0 0 1 1 1 1 1 }
	cerr << "5<A: " << L << endl;
// FRIEND_TYPESlice_ASNOP_TYPESlice
	C = A;  C += A;			// { 2 4 6 8 10 12 14 16 18 20 }
	cerr << "C = A;  C += A: " << C << endl;
// FRIEND_TYPESlice_ASNOP_TYPE
	C -= 1;			        // { 1 3 5 7 9 11 13 15 17 19 }
	cerr << "C -= 1: " << C << endl;
// TYPEPick_ASN_TYPEVec
	C = A;  C[I] = ByteVec(3,50,0);	// { 1 50 3 50 5 50 7 8 9 10 }
	cerr << "C = A; C[I] =  ByteVec(3,50,0): " << C << endl;
// TYPEPick_ASN_TYPEPick
	C[I] = A[I];			// { 1 2 3 4 5 6 7 8 9 10 }
	cerr << "C[I] = A[I]: " << C << endl;
// TYPEPick_ASN_TYPESlct
	C[I] = A[A<=3];		// C = { 1 1 3 2 5 3 7 8 9 10 }
	cerr << "C[I] = A[A<=3]: " << C << endl;
// TYPEPick_ASN_TYPESlice
	C[I] = A(0,3,2);		// C = { 1 1 3 3 5 5 7 8 9 10 }
	cerr << "C[I] = A(0,3,2): " << C << endl;
// TYPEPick_ASN_TYPE
	C[I] = 50;			// C = { 1 50 3 50 5 50 7 8 9 10 }
	cerr << "C[I] = 50: " << C << endl;
}

void test2()
{
	BitVec L;
// TYPEVec_CTOR_I
	ByteVec C;			// C = {}
// TYPESlct_ASN_TYPEVec
	C = A;  C[A<=5] = ByteVec(5,50,0);	// C = { 50 50 50 50 50 6 7 8 9 10 }
	cerr << "C = A; C[A<=5] = ByteVec(5,50,0): " << C << endl;
// TYPESlct_ASN_TYPEPick
	C = A;  C[A<=3] = A[I];	// C = { 2 4 6 4 5 6 7 8 9 10 }
	cerr << "C = A; C[A<=3] = A[I]: " << C << endl;
// TYPESlct_ASN_TYPESlct
	C = A;  C[A<=5] = B[A<=5];	// C = { 10 9 8 7 6 6 7 8 9 10 }
	cerr << "C = A; C[A<=5] = B[A<=5]: " << C << endl;
// TYPESlct_ASN_TYPESlice
	C[A<=5] = A(0,5,1);		// C = { 1 2 3 4 5 6 7 8 9 10 }
	cerr << "C = A; C[A<=5] = A(0,5,1): " << C << endl;
// TYPESlct_ASN_TYPE
	C[A<=5] = 0;			// C = { 0 0 0 0 0 6 7 8 9 10 }
	cerr << "C = A; C[A<=5] = 0: " << C << endl;
// TYPESlice_CTOR_TYPESlct
	C = A[A<=5] + B[B<=5];	// C = { 6 6 6 6 6 }
	cerr << "C = A[A<=5] + B[B<=5]: " << C << endl;
// FRIEND_cumsum_TYPESlice
	C = cumsum(ByteVec(10,1));
	cerr << "cumsum(ByteVec(10,1)): " << C << endl;
// FRIEND_delta_TYPESlice
	C = delta(C);
	cerr << "delta(cumsum(ByteVec(10,1))): " << C << endl;
// FRIEND_dot_TYPESlice_TYPESlice
	cerr << "dot(A,B): " << int(dot(A,B)) << endl;
// FRIEND_max_TYPESlice
	cerr << "max(A): " << max(A) << endl;
// FRIEND_min_TYPESlice
	cerr << "min(A): " << min(A) << endl;
// FRIEND_prod_TYPESlice
	cerr << "prod(A(0,5,1)): " << int(prod(A(0,5,1))) << endl;
// FRIEND_sum_TYPESlice
	cerr << "sum(A): " << int(sum(A)) << endl;
//TYPESlice_CTOR_TYPEPick
        C = A[I] + B[I];             // C = { 11 11 11 }
	cerr << "C = A[I] + B[I]: " << C << endl;
}

main()
{
	cerr << "Test Vector ByteVec class\n";
// TYPEVec_CTOR_TYPEPTR_I
	cerr << "IntVec I(3,1,2): " << I << endl;
// TYPEVec_CTOR_I_TYPE_TYPE
	cerr << "ByteVec A(10,1): " << A << endl;
// TYPEVec_CTOR_I_TYPE_TYPE
	cerr << "ByteVec B = reverse(ByteVec(10,1,1)): " << B << endl;
	test1();
	test2();
}
