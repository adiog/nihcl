/* Test class Heap

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Modification History:
	
$Log:	heap.c,v $
 * Revision 3.0  90/05/20  00:29:12  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/heap.c,v 3.0 90/05/20 00:29:12 kgorlen Rel $";

#include "Heap.h"
#include "Integer.h"
#include "OrderedCltn.h"
#include "Set.h"
#include "Point.h"

const int test1[] = {100, 70, 76, 22, 101, 54, 60, 2, 5, 601};
const int test2[] = {57, 36, 45, 59, 20, 14, 32, 18, 5, 28,
	17, 30, 16, 65, 34, 27, 30, 31, 80, 8,
	37, 39,	38, 45, 50, 15, 12, 13, 10, 25, 15};

main()
{
 	cout << "Testing Heap" << endl;
	OrderedCltn oc(10);
	for (int i = 0; i < sizeof test1/sizeof(int); i++)
		oc.add(*new Integer(test1[i]));
	cout << oc << endl;

	cout << "Test asHeap function" << endl;
	cout << "OrderedCltn as Heap:\n" << oc.asHeap() << endl;
	Heap heap1 = oc.asHeap();

	Heap heap2(1);		// Check reSize function
	for (i = (sizeof test1/sizeof(int))-1; i >=0; i--)
		heap2.add(*new Integer(test1[i]));
	cout << "Test isEqual function" << endl;
	cout <<  (heap1.isEqual(heap2) ? "SUCCESS" : "FAILURE") << endl;
	heap2.add(*new Integer(60));
	cout <<  (heap1!=heap2 ? "SUCCESS" : "FAILURE") << endl;
	heap2.removeFirst();
	cout <<  (heap1==heap2 ? "FAILURE" : "SUCCESS") << endl;

	Point A(1,1);
	Point B(1,2);
	Point C(1,3);
	Point D(1,3);
	Heap b(16);
	b.add(A);
	b.add(B);
	b.add(C);
	b.add(D);
	Heap c = b;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	c.removeAll();
	cout << "c = " << c << endl;
	c = b;
	cout << "c.removeId(D)->isSame(D): " << c.removeId(D)->isSame(D) << endl;
	cout << "b.first(): " << *(b.first()) << endl;
	cout << "b.last(): " << *(b.last()) << endl;
	Point E(4,5);
	b.add(E);
	cout << "b = " << b << endl;
	cout << "remove min from b " << *b.removeFirst() << endl;
	cout << "remove max from b " << *b.removeLast() << endl;
	Point F(3,2);
	Point G(1,4);
	Point H(5,6);
	Point I(0,1);
	Point J(9,8);
	b.add(F);
	b.add(G);
	b.add(H);
	b.add(I);
	b.add(J);
	b.add(I);
	b.add(B);
	b.add(A);
	b.add(B);
	cout << "b= " << b << endl; 
	cout << "\noccurrencesOf((1,2)): " << b.occurrencesOf(B) << endl;
	cout << "b.sort(): " << b.sort() << endl;
	cout << "b.asSet(): " << (b.asSet()) << "\n" << endl;

	cout << "Testing remove(Object&)" << endl;
	Heap aheap(15);
	for (i = 0; i < sizeof test2/sizeof(int); i++)
		aheap.add(*new Integer(test2[i]));
	cout << aheap << '\n' << endl;
	aheap.remove(*new Integer(10));
	cout << aheap << '\n' << endl;
	aheap.remove(*new Integer(80));	
	cout << aheap << '\n' << endl;
	aheap.remove(*new Integer(18));
	cout << aheap << '\n' << endl;
}
