/* Test class Bitset

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
	
$Log:	bitset.c,v $
 * Revision 3.0  90/05/20  00:28:52  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/bitset.c,v 3.0 90/05/20 00:28:52 kgorlen Rel $";
#include "Bitset.h"
main()
{
	Bitset a(10u),b(10u,11u);
	cout << "a = [" << a << "]" << endl;
	cout << "b = [" << b << "]" << endl;
	a = 1;
	a = a | 2 | 3;
	b = 2;
	b |= 4;
	cout << "a = [" << a << "]" << endl;
	cout << "a.size(): " << a.size() << endl;
	cout << "b = [" << b << "]" << endl;
	cout << "a&b = [" << (a&b) << "]" << endl;
}
