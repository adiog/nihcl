/* Test class Set

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
	
$Log:	sets.c,v $
 * Revision 3.0  90/05/20  00:29:54  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/sets.c,v 3.0 90/05/20 00:29:54 kgorlen Rel $";

#include "Point.h"
#include "Set.h"
#include "OrderedCltn.h"

main()
{
	cout << "\nTest class Set" << endl;
	Point A(1,1);
	Point B(1,2);
	Point C(1,3);
	Point D(1,3);
	Point E(1,4);
	Set s(16);
	Set t;
	s.add(A);
	s.add(B);
	s.add(C);
	s.add(D);
	cout << "s = " << s << endl;
	t = s;
	cout << "t = " << t << endl;
	t.removeAll();
	cout << "t = " << t << endl;
	t = s;
	s.reSize(30);
	cout << "s.includes(C): " << s.includes(C) << endl;
	cout << "t == s: " << (t==s) << endl;
	s.remove(C);
	cout << "s.includes(C): " << s.includes(C) << endl;
	cout << "t == s: " << (t==s) << endl;
	s.add(E);
	cout << "s = " << s << endl;
	cout << "t = " << t << endl;
	cout << "s&t = " << (s&t) << endl;
	cout << "s|t = " << (s|t) << endl;
	cout << "s-t = " << (s-t) << endl;
	cout << "s.asOrderedCltn: " << (s.asOrderedCltn()) << endl;
}
