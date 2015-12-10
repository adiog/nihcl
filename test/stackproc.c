/* Test class StackProc

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
	
$Log:	stackproc.c,v $
 * Revision 3.0  90/05/20  00:30:00  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/stackproc.c,v 3.0 90/05/20 00:30:00 kgorlen Rel $";

#include "StackProc.h"
#include "SharedQueue.h"
#include "Scheduler.h"
#include "String.h"

class TestStackProc : public StackProc {
protected:
	TestStackProc(const char* name, stackTy* bottom, int pri, SharedQueue& in, SharedQueue& out);
public:
	static TestStackProc* create(const char* name, int pri, SharedQueue& in, SharedQueue& out);
};

TestStackProc::TestStackProc(const char* pname, stackTy* bottom, int pri, SharedQueue& in, SharedQueue& out)
	: StackProc(pname,bottom,pri)
{
	if (FORK()) return;
	while (YES) {
		Object* msg = in.next();
		cout << "process " << name() << " received " << *msg << endl;
		out.nextPut(*msg);
		cout << "process " << name() << " sent " << *msg << endl;
	}
}

TestStackProc* TestStackProc::create(const char* name, int pri, SharedQueue& in, SharedQueue& out)
{
#ifndef NESTED_TYPES
	auto stackTy bottom;
#else
	auto Process::stackTy bottom;
#endif
	return new TestStackProc(name, &bottom, pri, in, out);
}

main(int /* argc */, char** /* argv */)
{
	MAIN_PROCESS(0);
	SharedQueue* q0 = new SharedQueue(2);
	SharedQueue* qin = q0;
	SharedQueue* qout;
	for (int i=1; i <= MAXPRIORITY; i++) {
		String pname = "P";
		pname &= (char)('0'+i);
		qout = new SharedQueue(2);
		TestStackProc::create(pname,i,*qin,*qout);
		qin = qout;
	}
	String& msg = *new String("THE MESSAGE");
	Scheduler::dumpOn(cerr);
	q0->dumpOn(cerr);
	Scheduler::yield();
	q0->nextPut(msg);
	cout << *qout->next() << endl;
}
