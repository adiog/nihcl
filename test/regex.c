/* Test class Regex

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
	
$Log:	regex.c,v $
 * Revision 3.0  90/05/29  13:46:19  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/regex.c,v 3.0 90/05/29 13:46:19 kgorlen Rel $";

#include "Regex.h"
#include "OIOnih.h"
#include <fcntl.h>
#include <osfcn.h>

void printGroups(const Regex& r, const String& s, ostream& strm =cout)
{
	for (int i=0; i<r.groups(); i++) {
		strm << '\\' << i << ":	" << ((String&)s)(r[i])
			<< "	[" << s << '(' << r[i] << ")]" << endl;
	}
}

void testPattern(Regex& r, const String& s, ostream& strm =cout)
{
	strm << r << " match(" << s << ")? "
		<< (r.match(s) ? "YES" : "NO") << endl;
	printGroups(r,s);
	strm << r << " search(" << s << ")? "
		<< (r.search(s) != -1 ? "YES" : "NO") << endl;
	printGroups(r,s);
	strm << r << " search(" << s << ',' << s.length()-1 << ',' << -(int)s.length()+1 << ")? "
		<< (r.search(s,s.length()-1,-s.length()+1) != -1 ? "YES" : "NO") << endl;
	printGroups(r,s);
	cout << "---" << endl;
}

const char* fileName = "regex.obj";

main()
{
	cout << "\nTest Class Regex" << endl;
	Regex r = "\\([^a-zA-Z]*\\)\\([a-zA-Z]+\\)\\([^a-zA-Z]*\\)";
	testPattern(r,"123First123456789");
	Regex r2 = r;
	testPattern(r2,"123First123456789");
	Regex r3;
	r3 = r;
	testPattern(r3,"123First123456789");
	ostream* out = new ostream(creat(fileName,0664));
	r3.storeOn(OIOnihout(*out));
	delete out;
	istream* in = new istream(open(fileName,O_RDONLY));
	Regex* rp = Regex::readFrom(OIOnihin(*in));
	delete in;
	testPattern(*rp,"123First123456789");

	String s;
	while (YES) {
		cout << "Enter PATTERN: "; cin >> r;
		if (cin.eof()) {
			cout << endl;
			exit(0);
		}
		while (YES) {
			cout << "Enter STRING: "; cin >> s;
			if (cin.eof()) {
				cout << endl;
				exit(0);
			}
			if (s.length()==0) break;
			testPattern(r,s);
		}
	}
}
