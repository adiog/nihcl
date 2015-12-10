/* Test class IdentSet

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
	
$Log:	identset.c,v $
 * Revision 3.0  90/05/20  00:29:19  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/identset.c,v 3.0 90/05/20 00:29:19 kgorlen Rel $";

#include "Point.h"
#include "IdentSet.h"

main()
{
	cout << "\nTest class IdentSet" << endl;
	Point A(1,1);
	Point B(1,1);
	IdentSet s(16);
	IdentSet t;
	s.add(A);
	cout << "s = " << s << endl;
	cout << "s.includes(A): " << s.includes(A) << endl;
	cout << "s.includes(B): " << s.includes(B) << endl;
}
