/* Test class Object

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
	
$Log:	object.c,v $
 * Revision 3.0  90/05/20  00:29:27  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/object.c,v 3.0 90/05/20 00:29:27 kgorlen Rel $";

#include "Point.h"
#include "Rectangle.h"

main()
{
	cout << "\nTest class Object" << endl;
	Point A(1,2);
	Object* C = A.copy();
	cout << "C is an instance of class " << C->className() << endl;
	cout << "C = " << *C << endl;
	cout << "C->isKindOf(*Object::desc()): " << C->isKindOf(*Object::desc()) << endl;
	cout << "C->isKindOf(*Class::desc()): " << C->isKindOf(*Class::desc()) << endl;
	cout << "C->isKindOf(*Rectangle::desc()): " << C->isKindOf(*Rectangle::desc()) << endl;
	cout << "C->isA()->isKindOf(*Object::desc()): " << C->isA()->isKindOf(*Object::desc()) << endl;
	cout << "C->isA()->isKindOf(*Class::desc()): " << C->isA()->isKindOf(*Class::desc()) << endl;
	cout << "C->isA()->isKindOf(*Rectangle::desc()): " << C->isA()->isKindOf(*Rectangle::desc()) << endl;
}
