/* Test class Bag

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
	
$Log:	bag.c,v $
 * Revision 3.0  90/05/20  00:28:48  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/bag.c,v 3.0 90/05/20 00:28:48 kgorlen Rel $";

#include "Point.h"
#include "Bag.h"
#include "ArrayOb.h"

main()
{
	cout << "\nTest class Bag" << endl;
	Point A(1,1);
	Point B(1,2);
	Point C(1,3);
	Point D(1,3);
	Bag b(16);
	Bag c;
	b.add(A);
	b.add(B);
	b.add(C);
	b.add(D);
	cout << "b = ";  b.dumpOn(cout);
	cout << "b.asArrayOb: " << b.asArrayOb() << endl;
	c = b;
	cout << "c = "; c.dumpOn(cout);
	c.removeAll();
	cout << "c = "; c.dumpOn(cout);
	c = b;
	b.reSize(30);
	cout << "b.includes(C): " << b.includes(C) << endl;
	cout << "c == b: " << (c==b) << endl;
	b.remove(C);
	cout << "b.includes(C): " << b.includes(C) << endl;
	cout << "b = " << b << endl;
	b.remove(C);
	cout << "b.includes(C): " << b.includes(C) << endl;
	cout << "b = ";  b.dumpOn(cout);
	cout << "c == b: " << (c==b) << endl;
}
