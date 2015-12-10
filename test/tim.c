/* Test class Time

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
	
$Log:	tim.c,v $
 * Revision 3.0  90/05/20  00:30:06  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/tim.c,v 3.0 90/05/20 00:30:06 kgorlen Rel $";

#include "Date.h"
#include "Time.h"
#include "SortedCltn.h"

main()
{
	cout << "\nTest class Time" << endl;
	Time now;
	int hr,mn,sc;
	char junk[512];
	SortedCltn timelist;
	cerr << "It is now " << now << endl;
	while (YES) {
		cout << "Enter date and time: ";
		Date& date = *new Date(cin);
		if (cin.eof()) break;
		if (cin.fail()) {
			cout << "Bad date" << endl;
			cin.clear();  cin >> junk;
			continue;
		}
		cin >> hr >> mn >> sc;
		cout << endl;
		if (cin.eof()) break;
		if (cin.fail()) {
			cout << "Bad time" << endl;
			cin.clear();  cin.get(junk,sizeof junk);
			continue;
		}
		Time& time = *new Time(date,hr,mn,sc);
		timelist.add(time);
		cout << time << endl;
	}
	cout << endl << timelist << endl;
}
