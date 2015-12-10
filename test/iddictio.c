/* Test class IdentDict

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
	
$Log:	iddictio.c,v $
 * Revision 3.0  90/05/20  00:29:16  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/iddictio.c,v 3.0 90/05/20 00:29:16 kgorlen Rel $";

#include "Assoc.h"
#include "Bitset.h"
#include "IdentDict.h"
#include "OrderedCltn.h"
#include "Point.h"
#include "Rectangle.h"
#include "Set.h"
#include "SortedCltn.h"
#include "Stack.h"
#include "String.h"
#include "OIOnih.h"

Object* testStore()
{
	Bitset& bitset = *new Bitset(Bitset::bit(4)|Bitset::bit(6));
	IdentDict& iddict = *new IdentDict;
	OrderedCltn& orderedcltn = *new OrderedCltn;
	Point& point = *new Point(1,2);
	Rectangle& rect = *new Rectangle(0,1,2,3);
	Set& set = *new Set;
	SortedCltn& sortedcltn = *new SortedCltn;
	Stack& stack = *new Stack;
	String& str = *new String("Hello, world!");
	orderedcltn.add(point); orderedcltn.add(rect); orderedcltn.add(str);
	stack.push(bitset); stack.push(orderedcltn);
	sortedcltn.add(*new String("Huey"));
	sortedcltn.add(*new String("Dewey"));
	sortedcltn.add(*new String("Louie"));
	iddict.add(*new Assoc(orderedcltn,point));
	iddict.add(*new Assoc(bitset,rect));
	iddict.add(*new Assoc(sortedcltn,stack));
	set.add(orderedcltn);
	set.add(stack);
	set.add(sortedcltn);
	set.add(iddict);
	OrderedCltn& monster = *new OrderedCltn;
	monster.add(set); monster.add(*set.deepCopy());
	return &monster;
}

#include <fcntl.h>
#include <osfcn.h>

main()
{
	cout << "Test storeOn" << endl;
	ostream* out = new ostream(creat("iddicta",0664));
	Object* a = testStore();
	a->storeOn(OIOnihout(*out));
	delete out;

	cout << "Test readFrom" << endl;
	istream* in = new istream(open("iddicta",O_RDONLY));
	Object* b = Object::readFrom(OIOnihin(*in));
	delete in;
	cout << "*** object stored:" << endl << *a << endl;
	cout << "*** object read:" << endl << *b << endl;
	out = new ostream(creat("iddictb",0664));
	b->storeOn(OIOnihout(*out));
	delete out;
}
