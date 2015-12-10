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
	
$Log:	identdict.c,v $
 * Revision 3.0  90/05/20  18:12:42  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/identdict.c,v 3.0 90/05/20 18:12:42 kgorlen Rel $";

#include "Point.h"
#include "IdentDict.h"
#include "Assoc.h"
#include "AssocInt.h"
#include "SortedCltn.h"

main()
{
	cout << "\nTest class IdentDict" << endl;
	IdentDict d(16);
	Point a(1,1), b(1,2), c(1,3);
	AssocInt asc(c,3);
	d.add(*new AssocInt(a,1));
	d.add(*new AssocInt(b,2));
	d.add(asc);
	cerr << "d = ";  d.dumpOn(cerr);
	cout << "d.atKey(a): " << *(d.atKey(a)) << endl;
	cout << "d.includesKey(Point(1,1)): " << d.includesKey(Point(1,1)) << endl;
	d.atKey(a,*new Integer(0));
	cout << "d.atKey(a): " << *(d.atKey(a)) << endl;
	cout << "d.includesAssoc(asc): " << d.includesAssoc(asc) << endl;
	cout << "d.includesKey(" << (*asc.key()) << "): " << d.includesKey(*asc.key()) << endl;
	cout << "d.keyAtValue(Integer(0)) = " << *d.keyAtValue(Integer(0)) << endl;
	d.removeKey(c);
	cout << "d.includesAssoc(asc): " << d.includesAssoc(asc) << endl;
	cout << "d.includesKey(" << (*asc.key()) << "): " << d.includesKey(*asc.key()) << endl;
	SortedCltn keys,vals;
	cout << "d.addKeysTo(keys): " << d.addKeysTo(keys) << endl;
	cout << "d.addValuesTo(vals): " << d.addValuesTo(vals) << endl;
}
