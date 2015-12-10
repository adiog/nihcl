/* Test class Stack

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
	
$Log:	stack.c,v $
 * Revision 3.0  90/05/20  00:29:58  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/stack.c,v 3.0 90/05/20 00:29:58 kgorlen Rel $";

#include "Point.h"
#include "Rectangle.h"
#include "Stack.h"

main()
{
	cout << "\nTest class Stack" << endl;
	Rectangle a(0,0,10,10);
	Point A(1,2);
	Point B(3,4); 
	Object* C = A.copy();
	Stack s(10);
	s.push(a);
	s.push(A);
	cout << s << endl;
	cout << "top compare C = " << s.top()->compare(*C) << endl;
	cout << *(s.pop()) << endl;
	cout << *(s.top()) << endl;
	s.pop();
	s.pop();	/* should get underflow error */
}
