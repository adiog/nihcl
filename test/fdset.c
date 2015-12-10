/* Test class FDSet

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
	
$Log:	fdset.c,v $
 * Revision 3.0  90/05/20  00:29:09  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/fdset.c,v 3.0 90/05/20 00:29:09 kgorlen Rel $";
#include "FDSet.h"
main()
{
	FDSet a,b,c;
	a.set(0);
	b |= a;
	b[b.capacity()-1] = 1;
	cout << "a = [" << a << ']' << endl;
	cout << "b = [" << b << ']' << endl;
	cout << "a.size(): " << a.size() << endl;
	cout << "b.size(): " << b.size() << endl;
	cout << "a|b = [" << (a|b) << ']' << endl;
	cout << "a&b = [" << (a&b) << ']' << endl;
	cout << "a^b = [" << (a^b) << ']' << endl;
	cout << "b-a = [" << (b-a) << ']' << endl;
	c |= a;
	c |= b;
	cout << "c == b: " << (c==b) << endl;
	cout << "c.includes(0): " << c.includes(0) << endl;
	cout << "c.includes(1): " << c.includes(1) << endl;
	c &= a;
	cout << "c = [" << c << ']' << endl;
	c = a|b;
	c -= a;
	cout << "c = [" << c << ']' << endl;
	c = a|b;
	c ^= a;
	cout << "c = [" << c << ']' << endl;
	cout << "c.isEmpty(): " << c.isEmpty() << endl;
	c.clr(c.capacity()-1);
	cout << "c.isEmpty(): " << c.isEmpty() << endl;
}
