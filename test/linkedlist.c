/* Test class LinkedList

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
	
$Log:	linkedlist.c,v $
 * Revision 3.0  90/05/20  00:29:25  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/linkedlist.c,v 3.0 90/05/20 00:29:25 kgorlen Rel $";

#include "Point.h"
#include "LinkedList.h"
#include "LinkOb.h"
#include "Set.h"

main()
{
	cout << "\nTest class LinkedList" << endl;
	Point A(1,1);
	Point B(1,2);
	Point C(1,3);
	Point D(1,3);
	LinkOb bA(A);
	LinkOb bB(B);
	LinkOb bC(C);
	LinkOb bD(D);
	LinkedList b;
	b.add(bA);
	b.add(bB);
	b.add(bC);
	b.add(bD);
	LinkedList& c = *LinkedList::castdown(b.deepCopy());
	cout << "b = " << b << endl;
	cout << "b.first(): " << *(b.first()) << endl;
	cout << "b.last(): " << *(b.last()) << endl;
	cout << "b[3]: " << *b[3] << endl;
	b.reSize(30);
	cout << "b.includes(C): " << b.includes(C) << endl;
	cout << "c == b: " << (c==b) << endl;
	b.addFirst(*new LinkOb(*new Point(1,0)));
	b.addLast(*new LinkOb(*new Point(1,19)));
	cout << "b = " << b << endl;
	b.addAll(c);
	cout << "b = " << b << endl;
	b.remove(*b[1]);
	cout << "b.includes(A): " << b.includes(A) << endl;
	cout << "b = " << b << endl;
	cout << "c == b: " << (c==b) << endl;
	cout << "b.indexOf(D): " << b.indexOf(D) << endl;
	cout << "c = " << c << endl;
	DO(c,Object,ob) cout << *ob; OD
	cout << endl;
	cout << "c.size() = " << c.size() << endl;
	LinkOb::castdown(c[1])->value(A);
	cout << "c = " << c << endl;
	while (c.size() != 0) {
		c.remove(*c.first());
		cout << "c = " << c << endl;
	}
	cout << "b.asSet(): " << (b.asSet()) << endl;
	b.removeAll();
	b.add(bA);
	b.add(bC);
	b.addAfter(bA,bB);
	b.addAfter(bC,bD);
	D = Point(1,4);
	cout << "b = " << b << endl;
	cout << "b.first(): " << *(b.first()) << endl;
	cout << "b.last(): " << *(b.last()) << endl;
	cout << "b.size(): " << b.size() << endl;
	b.removeAll();
}
