/* Test class Arraychar

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
	
$Log:	arraychar.c,v $
 * Revision 3.0  90/05/20  00:26:06  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/arraychar.c,v 3.0 90/05/20 00:26:06 kgorlen Rel $";

#include "Arraychar.h"

main()
{
	cout << "\nTest class Arraychar" << endl;
	Arraychar v(10);
	Arraychar t(2),u(2);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	cout << v << endl;
	t[0] = 1; t[1] = 2;
	u = t;
	cout << "t = " << t << endl;
	cout << "t == u: " << (t==u) << endl;
	cout << "t.isEqual(u): " << t.isEqual(u) << endl;
	cout << "t.isEqual(v): " << t.isEqual(v) << endl;
	cout << "t.compare(u): " << t.compare(u) << endl;
	cout << "t.compare(v): " << t.compare(v) << endl;
	cout << "v.compare(t): " << v.compare(t) << endl;
	v.removeAll();
	cout << v << endl;
}
