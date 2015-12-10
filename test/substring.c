/* Test class SubString

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
	
$Log:	substring.c,v $
 * Revision 3.0  90/05/20  00:30:04  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/substring.c,v 3.0 90/05/20 00:30:04 kgorlen Rel $";

#include "String.h"

main()
{
	cout << "\nTest Class SubString" << endl;
	String s4 = "0123456789";
	String s;
cout << "void SubString::operator=(const String&): ";
	s = s4;
	s(1,3) = String("xxx");
	cout << s << endl;			// "0xxx456789"
cout << "void SubString::operator=(const SubString&): ";
	s = s4;
	s(1,3) = String('x',10)(0,3);
	cout << s << endl;			// "0xxx456789"
cout << "void SubString::operator=(const char*): ";
	s = s4;
	s(1,3) = "xxx";
	cout << s << endl;			// "0xxx456789"
	s = s4;
	s(10,0) = "";
	cout << s << endl;			// "0123456789"
cout << "void replace(const char* st, unsigned ln):" << endl;
	s = s4; s.reSize(11);
	s(1,0) = "*";
	cout << s << endl;			// "0*123456789"
	s = s4; s.reSize(11);
	s(0,0) = "*";
	cout << s << endl;			// "*0123456789"
	s = s4; s.reSize(11);
	s(10,0) = "*";
	cout << s << endl;			// "0123456789*"
	s = s4; s.reSize(0);
	s(1,1) = "";
	cout << s << endl;			// "023456789"
	s = s4; s.reSize(0);
	s(0,1) = "";
	cout << s << endl;			// "123456789"
	s = s4; s.reSize(0);
	s(9,1) = "";
	cout << s << endl;			// "012345678"
	s = s4; s.reSize(0);
	s(10,0) = "";
	cout << s << endl;			// "0123456789"
	s = s4; s.reSize(0);
	s(2,0) = s(0,1);
	cout << s << endl;			// "01023456789"
	s = s4; s.reSize(0);
	s(0,0) = s(0,1);
	cout << s << endl;			// "00123456789"
	s = s4; s.reSize(0);
	s(0,1) = s(9,0);
	cout << s << endl;			// "123456789"
	s = s4; s.reSize(0);
	s(0,1) = s(0,2);
	cout << s << endl;			// "01123456789"
cout << "bool SubString::operator<(const String&): ";
	cout << (s4(0,9) < s4) << endl;		// 1
cout << "bool SubString::operator<(const SubString& ss): ";
	cout << (s4(0,8) < s4(0,9)) << endl;	// 1
cout << "bool SubString::operator<(const char* cs): ";
	cout << (s4(0,9) < "01234567890") << endl;	// 1
cout << "friend bool operator<(const char* cs, const SubString& ss): ";
	cout << ("01234567" < s4(0,9)) << endl;	// 1
cout << "String SubString::operator&(const String&): ";
	cout << (s4(0,1) & s4) << endl;		// "00123456789"
cout << "String SubString::operator&(const SubString&): ";
	cout << (s4(0,2) & s4(8,2)) << endl;	// "0189"
cout << "String SubString::operator&(const char*): ";
	cout << (s4(0,2) & "*") << endl;	// "01*"
cout << "friend String operator&(const char*, const SubString&): ";
	cout << ("*" & s4(0,2)) << endl;	// "*01"
}
