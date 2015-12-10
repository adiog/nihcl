/* Test class Random

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
	
$Log:	random.c,v $
 * Revision 3.0  90/05/20  00:29:45  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/random.c,v 3.0 90/05/20 00:29:45 kgorlen Rel $";

#include "Random.h"

main()
{
	Random rangen;
	for (register i=10; i>0; i--) cerr << rangen.next() << endl;
	Random rand(0,0);
	for (i=10; i>0; i--) cout << rand.next() << endl;
}
