/* Test class Fraction

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
	
$Log:	fc.c,v $
 * Revision 3.0  90/05/20  00:29:06  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/fc.c,v 3.0 90/05/20 00:29:06 kgorlen Rel $";

#include <osfcn.h>
#include "Fraction.h"

Fraction readf(istream& strm)
{
	char delim;
	int u,v;
	strm >> u; strm.get(delim); strm >> v;
	if (strm.eof()) exit(0);
	return Fraction(u,v);
}

main()
{
	Fraction x,y,z;
	char op;
	while (YES) {
		cout << "Enter x: "; x = readf(cin); cout << endl;
		cout << "Enter y: "; y = readf(cin); cout << endl;
		cout << "Enter op: "; cin >> op; cout << endl;
		switch (op) {
			case '+': { z = x+y; break; }
			case '-': { z = x-y; break; }
			case '*': { z = x*y; break; }
			case '/': { z = x/y; break; }
			case '<': { z = x<y; break; }
			case '>': { z = x>y; break; }
			case '=': { z = x==y; break; }
			default: { cout << "Incorrect op" << endl; continue; }
		}
		cout << x << ' '; cout.put(op); cout << ' ' << y << " = " << z << endl;
	}
}
