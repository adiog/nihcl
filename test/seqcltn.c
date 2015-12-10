/* Test class SeqCltn

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
	
$Log:	seqcltn.c,v $
 * Revision 3.0  90/05/20  00:26:38  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/seqcltn.c,v 3.0 90/05/20 00:26:38 kgorlen Rel $";

#include "Point.h"
#include "OrderedCltn.h"
#include "Set.h"

main()
{
	cout << "\nTest class SeqCltn" << endl;
	Point A(1,1);
	Point B(1,2);
	Point C(1,3);
	Point D(1,3);
	OrderedCltn b(16);
	b.add(A);
	b.add(B);
	b.add(C);
	b.add(D);
	cout << "b = " << b << endl;
	cout << "b.first() == b.SeqCltn::first(): " << (b.first() == b.SeqCltn::first()) << endl;
	cout << "b.last() == b.SeqCltn::last(): " << (b.last() == b.SeqCltn::last()) << endl;
	cout << "b.hash() == b.SeqCltn::hash(): " << (b.hash() == b.SeqCltn::hash()) << endl;
	cout << "b.indexOf(D) == b.SeqCltn::indexOf(D): " << (b.indexOf(D) == b.SeqCltn::indexOf(D)) << endl;
	cout << "b.occurrencesOf(D) == b.SeqCltn::occurrencesOf(D): "
		<< (b.occurrencesOf(D) == b.SeqCltn::occurrencesOf(D)) << endl;
	OrderedCltn c;
	Point E = D;
	c.add(A); c.add(B); c.add(C); c.add(E);
	cout << "c = " << c << endl;
	cout << "b.isEqual(c) == b.SeqCltn::isEqual(c): " << (b.isEqual(c) == b.SeqCltn::isEqual(c)) << endl;
	E = Point(0,0);
	cout << "c = " << c << endl;
	cout << "b.isEqual(c) == b.SeqCltn::isEqual(c): " << (b.isEqual(c) == b.SeqCltn::isEqual(c)) << endl;
}
