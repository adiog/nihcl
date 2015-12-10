/* Scheduler.c -- implementation of the Process Scheduler

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
	December, 1985

Function:

Class Scheduler provides an interface to the single instance of the
process scheduler, scheduler.  The idea of implementing the coroutine
context switch with setjmp(), longjmp(), and alloca() came from
Dave Jones (hpda!sun!megatest!djones@uunet.uu.net).

$Log:	Scheduler.c,v $
 * Revision 3.0  90/05/20  00:21:05  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Process.h"
#include "Scheduler.h"
#include <osfcn.h>

JMP_BUF	Scheduler::switcher;		// environment for stack switcher
Process* Scheduler::active_process = 0;
Process* Scheduler::previous_process = 0;
StackProc* Scheduler::main_stack_process = 0;
#ifndef NESTED_TYPES
stackTy* Scheduler::main_stack_bottom = 0;
#else
Process::stackTy* Scheduler::main_stack_bottom = 0;
#endif
unsigned Scheduler::runCount = 0;	// total # of runnable processes 
int Scheduler::ast_level = 0;		// AST nesting level 
LinkedList Scheduler::runList[MAXPRIORITY+1];

#ifdef HAVE_SELECT
LinkedList Scheduler::selectList;		// Processes waiting for select(2)
struct timeval Scheduler::selectTimeout;	// timeout on select
#endif

#ifdef HAVE_SELECT

#include "FDSet.h"
#include <sys/errno.h>

#endif

extern const int NIHCL_SCHEDCTOR,NIHCL_ILLEGALFCN;

void Scheduler::addProcess(Process& p)
{
	p.process_state = Process::RUNNING;
	runList[p.process_priority].addLast(p);
	runCount++;
}

void Scheduler::schedule()
{
    if (astActive()) return;
    setjmp_val val = (setjmp_val)SETJMP(active_process->env);

    while (YES) {
	switch (val) {
	    case schedule_process: {
		AST_DISABLE;
		while (runCount>0) {
		    for (register int i=MAXPRIORITY; i>=0; i--) {
			if (runList[i].size() > 0) {
			    Process* active = active_process;
			    Process* next = Process::castdown(runList[i].first());
			    if (active != next) {
				previous_process = active;
				active_process = next;
				active->switchContext(next);
			    }
			    LONGJMP(next->env, resume_current_process);
			}
		    }
		}

#ifdef HAVE_SELECT
		if (selectList.isEmpty())
#endif
		    AST_PAUSE;			// wait for AST/signal
#ifdef HAVE_SELECT
		else selectfd();	// wait for AST, signal, or I/O
#endif

		break;	// schedule process
		}

	    case resume_current_process: return;

	    case resume_new_process: {
		active_process->restore();
		return;
		}
	}
    }
}

#ifdef HAVE_SELECT

#include <errno.h>

int Scheduler::selectfd()
{
	int mcount =0;			// return value from select(2)
        FDSet rmask, wmask, xmask;
	selectTimeout.tv_sec = 10;
	selectTimeout.tv_usec = 0;
	
	if (selectList.isEmpty() ) return 0;
	register Process* p = Process::castdown(selectList.first());
	
	while (!p->isListEnd()) {	// build select masks
		rmask |= p->rdmask;
		wmask |= p->wrmask;
		xmask |= p->exmask;
		p = (Process*)p->nextLink();
	};

	AST_RESTORE(0);
/*
If a signal/AST occurs at this point that makes a process runnable (by
calling Process::resume()), it will clear selectTimeout and the
following select will return immediately.  There may still be a window
in which the runnable process will not be scheduled until after this
select returns.  Thus, the select must be done with a timeout.  A
better approach is to use asynchronous I/O instead of select, but this
is said to have bugs under 4.2 BSD.
*/
	mcount = ::select(FDSet::dtablesize(),rmask,wmask,xmask,&selectTimeout);
	AST_DISABLE;

	if (mcount < 0) { // error
		if (errno == EINTR) return mcount;
		cerr << "Scheduler: error in select (" << errno << ")\n";
		exit(1);
		};

	if (mcount == 0) return 0;	// timeout or no fd selected

	p = Process::castdown(selectList.first());
	while (!p->isListEnd()) {	// resume all selected processes
#ifdef BUG_bC3035
// sorry, not implemented: temporary of class <name> with destructor needed in <expr> expression
		if ( !(rmask & p->rdmask).isEmpty()
			|| !(wmask & p->wrmask).isEmpty()
			|| !(xmask & p->exmask).isEmpty() ) {
#else
		int resume = 0;
		if ( !(rmask & p->rdmask).isEmpty() ) resume++;
	else	if ( !(wmask & p->wrmask).isEmpty() ) resume++;
	else	if ( !(xmask & p->exmask).isEmpty() ) resume++;
		if (resume) {
#endif
			p->rdmask &= rmask;
			p->wrmask &= wmask;
			p->exmask &= xmask;
			selectList.remove(*p);
			p->process_state = Process::RUNNING;
			runList[p->process_priority].addLast(*p);
			runCount++;
		};
		p = (Process*)p->nextLink();
	};
	return mcount;
}
#endif

void Scheduler::yield()
{
	if (runList[activePriority()].size() == 1) schedule();
	else {
		activeProcess().suspend();
		activeProcess().resume();
	}
}

const char* Scheduler::className()	{ return "Scheduler"; }

void Scheduler::dumpOn(ostream& strm)
{
	AST_DISABLE;
	strm << className()
		<< "[active process: "
		<< (active_process ? active_process->name() : "NONE")
		<< "  previous process: "
		<< (previous_process ? previous_process->name() : "NONE")
		<< '\n';
	strm << "runList:\n";
	for (register i =MAXPRIORITY; i>=0; i--) {
		DO(runList[i],Process,p) p->dumpOn(strm); OD
	}

#ifdef HAVE_SELECT
	if (!selectList.isEmpty()) {
		strm << "selectList:\n";
		DO(selectList,Process,p) p->dumpOn(strm); OD
	}
#endif

	strm << "]\n";
	AST_ENABLE;
}

void Scheduler::printOn(ostream& strm)
{
	AST_DISABLE;
	strm << className()
		<< "  active process: " << active_process->name()
		<< "  previous process: " << previous_process->name() << '\n';
	strm << "runList:";
	for (register i =MAXPRIORITY; i>=0; i--) {
		DO(runList[i],Process,p) strm << ' ' << *p; OD
	}
	strm << '\n';

#ifdef HAVE_SELECT
	if (!selectList.isEmpty()) {
		strm << "selectList:";
		DO(selectList,Process,p) strm << ' ' << *p; OD
		strm << '\n';
	}
#endif

	AST_ENABLE;
}
