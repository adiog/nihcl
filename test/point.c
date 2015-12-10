/* Test class Point

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
	
$Log:	point.c,v $
 * Revision 3.0  90/05/20  00:29:39  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/point.c,v 3.0 90/05/20 00:29:39 kgorlen Rel $";

#include "Point.h"

main()
{
	Point A(1,2);
	Point B(3,4); 
	Point C = A;
	cout << "\nTest class Point" << endl;
	cout << "A = " << A << endl;
	cout << "B = " << B << endl;
	cout << "A+B = " << (A+B) << endl;
	cout << "A-B = " << (A-B) << endl;
	cout << "A isEqual C: " << A.isEqual(C) << endl;
	cout << "10*A = " << (10*A) << endl;
	cout << "A max B = " << (A.max(B)) << endl;
	cout << "A min B = " << (A.min(B)) << endl;
	cout << "A transpose = " << A.transpose() << endl;
	cout << "A compare B = " << A.compare(B) << endl;
	A += B;
	cout << "A+=B = " << A << endl;
}
