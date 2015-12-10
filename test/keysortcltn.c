/* Test class KeySortCltn

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
	
$Log:	keysortcltn.c,v $
 * Revision 3.0  90/05/20  00:29:23  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/keysortcltn.c,v 3.0 90/05/20 00:29:23 kgorlen Rel $";

#include "KeySortCltn.h"
#include "String.h"
#include "Date.h"
#include "Float.h"
#include "Time.h"
#include "Integer.h"

KeySortCltn c;

static void part1()
{
	c.addAssoc(*new String("A"),*new String("Ant"));
	c.addAssoc(*new String("M"),*new String("Man"));
	c.addAssoc(*new String("C"),*new String("Cat"));
	c.addAssoc(*new String("E"),*new String("Emu"));
	c.addAssoc(*new String("H"),*new Date(25,"Dec",85));
	c.addAssoc(*new String("J"),*new Float(98.6));
	c.addAssoc(*new String("E"),*new String("Eeyore"));
	c.addAssoc(*new String("Z"),*new Time(Date(29,"Jan",63),21,30));

	c.printOn(cout); cout << endl;

	int k;
	k = c.findIndexOf(String("A"));
 	cout << "index " << k << " before key A" << endl;
	k = c.findIndexOf(String("M"));
 	cout << "index " << k << " before key M" << endl;
	k = c.findIndexOf(String("C"));
 	cout << "index " << k << " before key C" << endl;
	k = c.findIndexOf(String("E"));
 	cout << "index " << k << " before key E" << endl;
	k = c.findIndexOf(String("Z"));
 	cout << "index " << k << " before key Z" << endl;
	k = c.findIndexOf(String("F"));
 	cout << "index " << k << " before key F" << endl;
	k = c.findIndexOf(String("@"));
 	cout << "index " << k << " before key @" << endl;
	k = c.findIndexOf(String("["));
 	cout << "index " << k << " before key [" << endl;

	KeySortCltn clone = *KeySortCltn::castdown(c.copy());
 	cout << "clone isEqual c: " << c.isEqual(clone) << endl;
 	cout << "clone == c: " << (c == (clone)) << endl;
 	cout << "clone != c: " << (c != (clone)) << endl;
 	cout << "c.compare(clone) = " << c.compare(clone) << endl;
 	cout << "c.includesKey(String(\"J\")) = " << c.includesKey(String("J")) << endl;
 	cout << "c.includesKey(String(\"K\")) = " << c.includesKey(String("K")) << endl;
 	cout << "c.occurrencesOfKey(String(\"Q\")) = " << c.occurrencesOfKey(String("Q")) << endl;
 	cout << "c.occurrencesOfKey(String(\"M\")) = " << c.occurrencesOfKey(String("M")) << endl;
 	cout << "c.occurrencesOfKey(String(\"E\")) = " << c.occurrencesOfKey(String("E")) << endl;

	cout << "atKey(String(\"J\")) = " << *c.atKey(String("J"))
	     << endl;
	cout << "atKey(String(\"N\")) = " << *c.atKey(String("N"))
	     << endl;
}

static void part2()
{
	OrderedCltn o;
	c.addValuesTo(o);
	c.addKeysTo(o);
	cout << "\nOrderedCltn o =" << endl;
	cout << o << endl;

	SortedCltn b;
	c.addContentsBeforeTo(String("E"), b);
	cout << "\nSortedCltn b =" << endl;
	cout << b << endl;

	cout << "*c.removeKey(String(\"Z\")) = " << *c.removeKey(String("Z")) << endl;
	cout << "*c.removeKey(String(\"Q\")) = " << *c.removeKey(String("Q")) << endl;
	cout << "*c.removeKey(String(\"E\")) = " << *c.removeKey(String("E")) << endl;
	c.printOn(cout); cout << endl;

	const int ARRAY_SIZE = 4;
	ArrayOb x(ARRAY_SIZE), y(ARRAY_SIZE), z(ARRAY_SIZE);
	String s0("apple"), s1("bat"), s2("cat");
	String s3("gopher"), s4("dog"), s5("eagle");

	int i;
	for (i = 0; i < ARRAY_SIZE - 1; i++)
		switch (i) {
			case (0):
				x[i] = y[i] = z[i] = &s0;
				break;
			case (1):
				x[i] = y[i] = z[i] = &s1;
				break;
			case (2):
				x[i] = y[i] = z[i] = &s2;
				break;
		} /* switch */

	x[ARRAY_SIZE - 1] = &s3;
	y[ARRAY_SIZE - 1] = &s4;
	z[ARRAY_SIZE - 1] = &s5;

	KeySortCltn d;

	d.addAssoc(x, Integer(0));
	d.addAssoc(y, Integer(1));
	d.addAssoc(z, Integer(2));
	cout << endl; d.printOn(cout); cout << endl;
	int k;
	k = d.findIndexOf(y);
 	cout << "index "; y.printOn(cout); cout << "\nbefore key " << k << endl;
}

main()
{
	cout << "\nTest class KeySortCltn" << endl;
	part1();
	part2();
}
