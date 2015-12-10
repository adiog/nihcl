/* Test class OrderedCltn

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
	
$Log:	orderedcltn.c,v $
 * Revision 3.0  90/05/20  00:29:33  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/orderedcltn.c,v 3.0 90/05/20 00:29:33 kgorlen Rel $";

#include "Point.h"
#include "OrderedCltn.h"
#include "Set.h"

main()
{
	cout << "\nTest class OrderedCltn" << endl;
	Point A(1,1);
	Point B(1,2);
	Point C(1,3);
	Point D(1,3);
	OrderedCltn b(16);
	OrderedCltn c;
	b.add(A);
	b.add(B);
	b.add(C);
	b.add(D);
	cout << "b = " << b << endl;
	cout << "b.first(): " << *(b.first()) << endl;
	cout << "b.last(): " << *(b.last()) << endl;
	b.addAfter(Point(1,2),Point(1,21));
	b.addBefore(Point(1,2),Point(1,19));
	cout << "b = " << b << endl;
	cout << "b.after(Point(1,2)): " << *(b.after(Point(1,2))) << endl;
	cout << "b.before(Point(1,2)): " << *(b.before(Point(1,2))) << endl;
	c = b;
	b.reSize(30);
	cout << "b.includes(C): " << b.includes(C) << endl;
	cout << "c == b: " << (c==b) << endl;
	cout << "b.compare(c): " << b.compare(c) << endl;
	c.removeAll();
	cout << "c = " << c << endl;
	c = b;
	b.addAllLast(c);
	cout << "b = " << b << endl;
	cout << "b.compare(c): " << b.compare(c) << endl;
	cout << "c.compare(b): " << c.compare(b) << endl;
	b.remove(C);
	cout << "b.includes(C): " << b.includes(C) << endl;
	cout << "b = " << b << endl;
	cout << "c == b: " << (c==b) << endl;
	cout << "b.compare(c): " << b.compare(c) << endl;
	cout << "c&b:" << (c&b) << endl;
	cout << "b.indexOfSubCollection(c): " << b.indexOfSubCollection(c,1) << endl;
	cout << "c = " << c << endl;
	b.replaceFrom(1,3,c);
	cout << "b.replaceFrom(1,3,c): " << b << endl;
	b.sort();
	cout << "b.sort(): " << b << endl;
	cout << "b.asSet(): " << (b.asSet()) << endl;
	cout << "c.removeId(D)->isSame(D): " << c.removeId(D)->isSame(D) << endl;
}
