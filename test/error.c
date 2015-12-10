/* Test classes Catch, ExceptionAction, and ExceptionTrap

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
	
$Log:	error.c,v $
 * Revision 3.0  90/05/20  00:29:02  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/error.c,v 3.0 90/05/20 00:29:02 kgorlen Rel $";

#include "Stack.h"
#include "Exception.h"
#include "nihclIO.h"
#include "nihclerrs.h"

void xtrap(unsigned& err, int& sev, ...)
{
	cerr << "xtrap(" << err << ',' << sev << ") called\n";
}

class MyClass : public VIRTUAL Object {
	DECLARE_MEMBERS(MyClass);
	int n;
	Catch catcherr;
public:
	MyClass(int i) : catcherr(this) {
		n = i;
		cerr << "MyClass(" << n << ") constructed\n";
	}
	virtual void deepenShallowCopy();
	virtual void destroyer() {
		cerr << "MyClass(" << n << ") destroyed\n";
	}
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
private:			// shouldNotImplement()
	virtual int compare(const Object&) const;
};

#define	THIS	MyClass
#define	BASE	Object
#define	BASE_CLASSES BASE::desc()
#define	MEMBER_CLASSES
#define	VIRTUAL_BASE_CLASSES

DEFINE_CLASS(MyClass,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/error.c,v 3.0 90/05/20 00:29:02 kgorlen Rel $",NULL,NULL);

MyClass::MyClass(OIOifd& fd) : Object(fd) { fd >> n; }
 
MyClass::MyClass(OIOin& strm) : Object(strm) { strm >> n; }

void MyClass::deepenShallowCopy() {};

unsigned MyClass::hash() const	{ return (unsigned)this; }

bool MyClass::isEqual(const Object& a) const { return isSame(a); }

void MyClass::printOn(ostream& strm) const {}

int MyClass::compare(const Object&) const
{
	shouldNotImplement("compare");
	return 0;
}

main()
{
	cerr << "Test classes Catch, ExceptionAction, and ExceptionTrap\n";
	Stack s;
	MyClass* p = new MyClass(-1);
	MyClass* q = new MyClass(-2);
	{
		MyClass a(1);
		MyClass b(2);
		RaiseException x(NIHCL__CLTNEMPTY);
		BEGINX
			MyClass c(3);
			MyClass d(4);
			{
				MyClass e(5);
				MyClass f(6);
				delete p;
				s.pop();
			}
		EXCEPTION
			case NIHCL__CLTNEMPTY: {
				MyClass g(7);
				MyClass h(8);
				cerr << "CLTNEMPTY error handled\n";
			}
		ENDX
	}
	delete q;
	{
		ExceptionTrap x(xtrap);
		s.pop();
	}
}
