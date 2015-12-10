/* StackProc.c -- Implementation of Process with stack shared with main() process

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
	Internet: kgorlen@alw.nih.gov
	January, 1988

Function:
	
Modification History:

$Log:	StackProc.c,v $
 * Revision 3.0  90/05/20  00:21:30  kgorlen
 * Release for 1st edition.
 * 
*/

#include "StackProc.h"
#include "Scheduler.h"
#include "nihclIO.h"

#define	THIS	StackProc
#define	BASE	Process
#define	BASE_CLASSES BASE::desc()
#define	MEMBER_CLASSES
#define	VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(StackProc,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/StackProc.c,v 3.0 90/05/20 00:21:30 kgorlen Rel $",NULL,NULL);

StackProc::StackProc(const char* name, stackTy* bottom, int priority, unsigned long size)
	: BASE(name, bottom, priority)
{
	stack_top = topOfStack();
	stack_save_size = size;
	if (size != 0) stack_save = new stackTy[size];
	else stack_save = 0;
	saveStack();
}

StackProc::StackProc(stackTy* bottom, int priority)
	: BASE(bottom, priority)
// contructor for MAIN process
{
	stack_top = bottom;
	stack_save = 0;
	stack_save_size = 0;
	Scheduler::main_stack_process = this;
	add();			// add MAIN process to Scheduler runlist
}

StackProc::StackProc(OIOifd& fd) : BASE(fd) {}

StackProc::StackProc(OIOin& strm) : BASE(strm) {}

StackProc::~StackProc()
{
	delete stack_save;
}

void StackProc::saveStack()
// save the stack for this Process
{
#if STACK_GROWS_DOWN
	unsigned long size = stack_bottom - stack_top;
#else
	unsigned long size = stack_top - stack_bottom;
#endif
	if (stack_save_size < size) {
		if (stack_save_size != 0) delete stack_save;
		stack_save = new stackTy[size];
		stack_save_size = size;
	}

#ifdef sparc
	asm("t	0x03");	    // ST_FLUSH_WINDOWS
#endif

#if STACK_GROWS_DOWN
	copyStack(stack_top+1, stack_save, size);
#else
	copyStack(stack_bottom, stack_save, size);
#endif
}

void StackProc::restoreStack(const stackTy* palloc)
{
	Scheduler::main_stack_process = (StackProc*)Scheduler::active_process;

#if STACK_GROWS_DOWN
	if (palloc != stack_top+1) {
		cerr << "StackProc::restoreStack() assertion failed\n";
		abort();
	}
	copyStack(stack_save, stack_top+1, stack_bottom-stack_top);
#else
	if (palloc != Scheduler::main_stack_bottom) {
		cerr << "StackProc::restoreStack() assertion failed\n";
		abort();
	}
	copyStack(stack_save, stack_bottom, stack_top-stack_bottom);
#endif

	LONGJMP(((StackProc*)Scheduler::active_process)->env, Scheduler::resume_new_process);
}

unsigned StackProc::size() const
{
#if STACK_GROWS_DOWN
	return stack_bottom - stack_top;
#else
	return stack_top - stack_bottom;
#endif
}

void StackProc::switchContext(Process* new_process)
{
	stack_top = topOfStack();
	save();
	new_process->switchFrom(this);
}

void StackProc::switchFrom(HeapProc*)
// switch from active HeapProc to next StackProc
{
	if (Scheduler::main_stack_process == this)
		LONGJMP(env, Scheduler::resume_new_process);
	Scheduler::main_stack_process->saveStack();
	_LONGJMP(Scheduler::switcher, 1);
}

void StackProc::switchFrom(StackProc* active)
// switch from active StackProc to next StackProc
{
	active->saveStack();
	_LONGJMP(Scheduler::switcher, 1);
}
