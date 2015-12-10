/* Test class Dictionary

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
	
$Log:	dict.c,v $
 * Revision 3.0  90/05/20  00:29:00  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/dict.c,v 3.0 90/05/20 00:29:00 kgorlen Rel $";

#include "Point.h"
#include "Dictionary.h"
#include "Assoc.h"
#include "Bag.h"
#include "OrderedCltn.h"

main()
{
	cout << "\nTest class Dictionary" << endl;
	Dictionary d(16);
	Assoc c(*new Point(1,3),*new Point(2,3));
	d.add(*new Assoc(*new Point(1,1),*new Point(2,1)));
	d.add(*new Assoc(*new Point(1,2),*new Point(2,2)));
	d.add(c);
	cout << "d = " << d << endl;
	cout << "d.atKey(Point(1,1)): " << *(d.atKey(Point(1,1))) << endl;
	d.atKey(Point(1,1),*new Point(3,1));
	cout << "d = " << d << endl;
	cout << "d.includesAssoc(c): " << d.includesAssoc(c) << endl;
	cout << "d.includesKey(*c.key()): " << d.includesKey(*c.key()) << endl;
	cout << "d.keyAtValue(Point(3,1)) = " << *d.keyAtValue(Point(3,1)) << endl;
	d.removeKey(*c.key());
	cout << "d.includesAssoc(c): " << d.includesAssoc(c) << endl;
	cout << "d.includesKey(*c.key()): " << d.includesKey(*c.key()) << endl;
	cout << "d.asBag: " << d.asBag() << endl;
	OrderedCltn keys,vals;
	cout << "d.addKeysTo(keys): " << d.addKeysTo(keys) << endl;
	cout << "d.addValuesTo(vals): " << d.addValuesTo(vals) << endl;
}
