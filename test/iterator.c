/* Test class Iterator

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
	
$Log:	iterator.c,v $
 * Revision 3.0  90/05/20  00:29:20  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/iterator.c,v 3.0 90/05/20 00:29:20 kgorlen Rel $";

#include "Iterator.h"
#include "LinkedList.h"
#include "OrderedCltn.h"
#include "Set.h"
#include "Heap.h"
#include "Point.h"
#include "LinkOb.h"
#include "OIOnih.h"
#include <fcntl.h>
#include <osfcn.h>

const char* fileName = "iterator.obj";

main()
{
	cout << "\nTest class Iterator" << endl;
	OrderedCltn c,x;
	{ for (int j=0; j<6; j++) c.add(*new Point(j,j)); }
	c.dumpOn(cout);  cout.flush();
	Set s;
	s = c.asSet();
	s.dumpOn(cout);  cout.flush();
	LinkedList l;
	Iterator i(s);
	Object* p;
	while (p = i++) l.add(*new LinkOb(*p));
	l.dumpOn(cout);  cout.flush();
	Heap h;
	h = c.asHeap();
	h.dumpOn(cout); cout.flush();
	x.add(c); x.add(l); x.add(h);

    DO(x,Collection,cp) {
	cout << "\nTest Iterator(" << cp->className() << ").storeOn()" << endl;
	ostream* out = new ostream(creat(fileName,0664));
	Iterator ii(*cp);
	ii.dumpOn(cout);  cout.flush();
	{ for (int j=0; j<3; j++) cout << *ii++; }
	cout << endl;
	ii.dumpOn(cout);  cout.flush();
	ii.storeOn(OIOnihout(*out));
	delete out;

	cout << "\nTest Iterator(" << cp->className() << ") readFrom()" << endl;
	istream* in = new istream(open(fileName,O_RDONLY));
	Iterator* ip = Iterator::readFrom(OIOnihin(*in));
	ip->dumpOn(cout);  cout.flush();
	while (p = (*ip)++) cout << *p;
	delete in;
	Collection* tcp=(Collection*)ip->collection();
	delete ip;
	delete tcp;

	cout << "\nTest Iterator(" << cp->className() << ").deepCopy()" << endl;
	ip = Iterator::castdown(ii.deepCopy());
	ip->dumpOn(cout);  cout.flush();
	while (p = (*ip)++) cout << *p;
	cout << "\nTest Iterator(" << cp->className() << ").reset()" << endl;
	ip->reset();
	ip->dumpOn(cout);  cout.flush();
	while (p = (*ip)++) cout << *p;
	cout << endl;
	tcp=(Collection*)ip->collection();
	delete ip;
	delete tcp;
    } OD;
}
