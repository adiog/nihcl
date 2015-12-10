/* Test class Date

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
	
$Log:	date.c,v $
 * Revision 3.0  90/05/20  00:28:55  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/date.c,v 3.0 90/05/20 00:28:55 kgorlen Rel $";

#include <osfcn.h>
#include "Date.h"
#include "SortedCltn.h"

main()
{
	cout << "\nTest class Date" << endl;
	char junk[100];
	Date today;
	Date tomorrow(today+1);
	Date yesterday(today-1);
	Date reference(25,"Dec",1985);
	Date ref_copy = reference;
	SortedCltn datelist;
	dayTy   d;
	
//      This portion is to check those functions of Date which only need
//      to be tested once.
	
	cerr << "Today is " << Date::nameOfDay(today.weekDay()) << ", " << today << endl;
	cerr << "Tomorrow is " << Date::nameOfDay(tomorrow.weekDay()) << ", " << tomorrow << endl;
	cerr << "Yesterday was " << Date::nameOfDay(yesterday.weekDay()) << ", " << yesterday << endl;

	cout << "Date(5) = "  << Date(5L) << endl;
	cout << "Date(-3) = " << Date(-3L) << endl;
	cout << "Date(367, 1984) = " << Date(367,1984) << endl;
	cout << "Date(-1, 1984) = " << Date(-1,1984) << endl;
	cout << "nameOfMonth(6) = " << Date::nameOfMonth(6) << endl;

	cout << "Enter string for dayOfWeek: ";
 	cin  >> junk;
	if (cin.eof()) { cout << endl; exit(1); }	
 	cout << "dayOfWeek(" << junk << ") = " << Date::dayOfWeek(junk) << endl;
	cout << "Enter string for numberOfMonth: ";
	cin  >> junk;
	if (cin.eof()) { cout << endl; exit(1); }	
 	cout << "numberOfMonth(" << junk << ") = " << Date::numberOfMonth(junk) << endl;
	cout << "Enter number for nameOfDay: ";
	cin  >> d;
	if (cin.eof()) { cout << endl; exit(1); }	
 	cout << "nameOfDay(" << d << ") = " << Date::nameOfDay(d) << endl;

	cout << "Reference date is " << ref_copy << endl;
	cout << "Enter date for scanFrom: ";
	ref_copy.scanFrom(cin);
	cout << "Replaced ref_copy by " << ref_copy << endl;

//	Now do the repetitive stuff.

	while (YES) {
		cout << "Enter date: "; Date& date = *new Date(cin); cout << endl;
		if (cin.eof()) break;
		if (cin.fail()) { cout << "Bad date" << endl;  cin.clear();  cin.get(junk,sizeof junk);  continue; }
		cout << Date::nameOfDay(date.weekDay()) << ", " << date << endl;
		cout << reference << " - " << date << " = " << (reference-date) << endl;
		cout << date << " between(1-Jan-85, 31-Dec-85): " << (date.between(Date(1,"Jan",85), Date(31,"Dec",85))) << endl;
		cout << date << " max(" << reference << ") = " << date.max(reference) << endl;
		cout << date << " min(" << reference << ") = " << date.min(reference) << endl;
		cout << "The date of the previous Sunday is " << date.previous("Sun") << endl;
		cout << "The date of the previous Thursday is " << date.previous("Thursday") << endl;
		cout << "date.compare(reference) = " << date.compare(reference) << endl;
		cout << "date.day() = "     << date.day()          << endl;
		cout << "date.dayOfMonth() = "       << date.dayOfMonth()       << endl;
		cout << "daysInYear(date.year()) = " << Date::daysInYear(date.year()) << endl;
		cout << "date.firstDayOfMonth() = "  << date.firstDayOfMonth()  << endl;
		cout << "date.hash() = "	     << date.hash()		<< endl;
		cout << "date.isEqual(reference) = " << date.isEqual(reference)	<< endl;
		cout << "this + 50 = " 		     << date + 50		<< endl;
		cout << "50 + this = "		     << 50 + date		<< endl;
		cout << "this - 60  = "		     << date - 60		<< endl;
		cout << "this < reference = "	     << (date < reference)	<< endl;
		cout << "this > reference = "	     << (date > reference)	<< endl;
		cout << "this <= reference = "	     << (date <= reference)	<< endl;
		cout << "this >= reference = "	     << (date >= reference)	<< endl;
		cout << "this == reference = "	     << (date == reference)	<< endl;
		cout << "this != reference = "	     << (date != reference)	<< endl;
		Date date1=date;
		date1 += 50;
		cout << "this += 50 = "		     << date1			<< endl;
		Date date2=date;
		date2 -= 60;
		cout << "this -=60 = "		     << date2			<< endl;
		datelist.add(date);
		cout << datelist << endl;

	} // while(YES)
	cout << endl;	
}
