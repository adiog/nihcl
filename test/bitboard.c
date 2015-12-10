/* Test class BitBoard

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
	
$Log:	bitboard.c,v $
 * Revision 3.0  90/05/20  00:28:50  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/bitboard.c,v 3.0 90/05/20 00:28:50 kgorlen Rel $";

#include "BitBoard.h"

main()
{
	cout << "Test class BitBoard" << endl;
	BitBoard a(0,0),b(0,0);
	for (register i=0; i<8; i++) {
		for (register j=0; j<=i; j++) {
			a |= BitBoard(8*i+j);
		}
	}
	cout << "a:" << a << endl;
	b = ~a;
	cout << "b:" << b << endl;
	cout << "a-rankBitBoard[4]:" << (a-rankBitBoard[4]) << endl;
	cout << "a|fileBitBoard[5]:" << (a|fileBitBoard[5]) << endl;
	cout << "a.count() = " << a.count() << endl;
}
