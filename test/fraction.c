/* Test class Fraction

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
	
$Log:	fraction.c,v $
 * Revision 3.0  90/05/20  00:29:11  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/fraction.c,v 3.0 90/05/20 00:29:11 kgorlen Rel $";

#include "Fraction.h"

main()
{
	Fraction a(40902,24140), b(7,66), c(17,12);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	cout << "7/66 + 17/12 = " << (b+c) << endl;
	cout << "7/66 - 17/12 = " << (b-c) << endl;
	cout << "7/66 * 17/12 = " << (b*c) << endl;
	cout << "7/66 / 17/12 = " << (b/c) << endl;
	cout << "7/66 < 11/100 = " << (b<Fraction(11,100)) << endl;
	cout << "Fraction(0.5) = " << Fraction(0.5) << endl;
	cout << "Fraction(0.333333e6) = " << Fraction(0.333333e6) << endl;
	cout << "Fraction(0.333333e-6) = " << Fraction(0.333333e-6) << endl;
	cout << "(double)Fraction(1,2) = " << (double)Fraction(1,2) << endl;
}
