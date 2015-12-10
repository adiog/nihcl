/* Process.c -- implementation of processes

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

Class Process serves as a base class for user processes (co-routines).

$Log:	Process.c,v $
 * Revision 3.0  90/05/20  00:20:48  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Process.h"
#include "Scheduler.h"
#include "ExceptAct.h"
#include <osfcn.h>

#define	THIS	Process
#define	BASE	Link
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES String::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_ABSTRACT_CLASS(Process,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Process.c,v 3.0 90/05/20 00:20:48 kgorlen Rel $",NULL,NULL);

extern const int NIHCL_STACKOV,NIHCL_BADPRI,NIHCL_RESRUN,NIHCL_RESTERM,NIHCL_INVALIDPS,
	NIHCL_SUSTERM,NIHCL_ILLEGALFCN,NIHCL_NOTINIT;

#define DUFF

void Process::copyStack(const stackTy* src, stackTy* dst, unsigned long count)
{
#ifdef DEBUG_PROCESS
cerr    << Scheduler::activeProcess().name()
	<< "\tProcess::copyStack() src=0x" << hex << (unsigned)src
	<< "  dst=0x" << hex << (unsigned)dst
	<< "  count=" << count
	<< " (0x" << hex << (unsigned)(count*sizeof(stackTy)) << ")"
	<< endl;
#endif
#ifndef DUFF
	while (count--) *dst++ = *src++;
#else
//  Unrolled loop using Duff's Device:
	register unsigned long n = (count+7)>>3;
	switch (count & 7) {
		case 0:	do {	*dst++ = *src++;
		case 7:		*dst++ = *src++;
		case 6:		*dst++ = *src++;
		case 5:		*dst++ = *src++;
		case 4:		*dst++ = *src++;
		case 3:		*dst++ = *src++;
		case 2:		*dst++ = *src++;
		case 1:		*dst++ = *src++;
		} while (--n > 0);
	}
#endif
}

Process::Process(const char* name, stackTy* bottom, int priority)
	: process_name(name)
{
	stack_bottom = bottom;
	process_priority = priority;
	process_state = SUSPENDED;
	saved_exception_env_stack_top = ExceptionEnv::lastResort;
	saved_exception_action = new ExceptionActionTbl;
}

Process::Process(stackTy* bottom, int priority)
	: process_name("MAIN")
// MAIN Process constructor
{
	stack_bottom = bottom;
	process_priority = priority;
	process_state = SUSPENDED;
	saved_exception_env_stack_top = 0;
	saved_exception_action = 0;
	saved_catch_stack_top = 0;
	PC() = 0;
}

Process::~Process()
{
	terminate();
	delete saved_exception_action;
}

void Process::add()	{ Scheduler::addProcess(*this); }

unsigned char Process::priority() const	{ return process_priority; }

unsigned char Process::priority(unsigned char newPriority)
{
	register unsigned char oldPriority =process_priority;
	if (newPriority > MAXPRIORITY) setError(NIHCL_BADPRI,DEFAULT,newPriority,MAXPRIORITY);
	AST_DISABLE;
	process_priority = newPriority;
	if (newPriority != oldPriority && process_state == RUNNING) {
		Scheduler::runList[oldPriority].remove(*this);
		Scheduler::runList[newPriority].addLast(*this);
	}
	AST_ENABLE;
	return oldPriority;
}

unsigned Process::capacity() const	{ return size(); }

void Process::resume()
{
	AST_DISABLE;
	switch (process_state) {
		case SUSPENDED: {
			Scheduler::addProcess(*this);
			if (Scheduler::astActive()) {	// force any pending select to time out
#ifdef HAVE_SELECT
				Scheduler::selectTimeout.tv_sec = 0;
				Scheduler::selectTimeout.tv_usec = 0; 
#endif
				break;
			}
			else Scheduler::schedule();
			break;
		}
		case RUNNING: setError(NIHCL_RESRUN,DEFAULT,name(),this);
		case TERMINATED: setError(NIHCL_RESTERM,DEFAULT,name(),this);
		default: setError(NIHCL_INVALIDPS,DEFAULT,name(),this,className(),process_state);
	}
	AST_ENABLE;
}

void Process::suspend()
{
	AST_DISABLE;
	switch (process_state) {
		case SUSPENDED: break;
		case RUNNING: {
			process_state = SUSPENDED;
			Scheduler::runList[process_priority].remove(*this);
			Scheduler::runCount--;
			break;
		}
		case TERMINATED: {
			AST_ENABLE;
			setError(NIHCL_SUSTERM,DEFAULT,name(),this);
		}
		default: {
			AST_ENABLE;
			setError(NIHCL_INVALIDPS, DEFAULT, name(), this, className(), process_state);
		}
	}
	AST_ENABLE;
}

void Process::terminate()
{
	AST_DISABLE;
	switch (process_state) {
		case SUSPENDED: {
			process_state =	TERMINATED;
#ifdef HAVE_SELECT
			if (Scheduler::selectList.includes(*this))
				Scheduler::selectList.remove(*this);
#endif
			AST_ENABLE;
			return;
		}
		case RUNNING: {
			suspend();
			process_state = TERMINATED;
			AST_ENABLE;
			Scheduler::schedule();
			return;
		}
		case TERMINATED: break;
		default: {
			AST_ENABLE;
			setError(NIHCL_INVALIDPS, DEFAULT, name(), this, className(), process_state);
		}
	}
	AST_ENABLE;
}

#ifdef HAVE_SELECT
void Process::select(FDSet& readfds, FDSet& writefds, FDSet& exceptfds)
{
	rdmask = readfds;	// save fd masks
	wrmask = writefds;
	exmask = exceptfds;
	AST_DISABLE;
	suspend();
	Scheduler::selectList.addLast(*this);
	AST_ENABLE;
	Scheduler::schedule();
	readfds = rdmask;	// return results of select
	writefds = wrmask;
	exceptfds = exmask;
}
#endif

int Process::compare(const Object& ob) const	// compare process priorities 
{
	assertArgSpecies(ob,classDesc,"compare");
	return process_priority - castdown(ob).process_priority;
}

Process::Process(const Process&) { shouldNotImplement("Process"); }

Object* Process::copy() const
{
	shouldNotImplement("copy");
	return 0;
}

void Process::deepenShallowCopy()
{
	shouldNotImplement("deepCopy");
}

unsigned Process::hash() const	{ return (unsigned)this; }

bool Process::isEqual(const Object& ob) const	{ return isSame(ob); }
	
void Process::dumpOn(ostream& strm) const
{
	strm	<< className() << '[' << process_name
		<< " @0x" << hex << (unsigned)this
		<< "  pri: " << (int)process_priority
		<< "  state: ";
	switch (process_state) {
		case SUSPENDED: strm << "SUSPENDED"; break;
		case RUNNING:	strm << "RUNNING"; break;
		case TERMINATED: strm << "TERMINATED"; break;
		default: strm << "INVALID";
	}
	if (PC()) {
		strm	<< "  PC: 0x" << hex << PC()
		        << "  SP: 0x" << hex << SP()
			<< "  FP: 0x" << hex << FP();
	}
	else strm << "  PC: 0x0  SP: ?  FP: ?";
	strm 	<< "  stack_bottom: 0x" << hex << (unsigned)stack_bottom
		<< "  size: " << size();

#ifdef HAVE_SELECT
	strm	<< "  rd: <" << rdmask << '>'
		<< "  wr: <" << wrmask << '>'
		<< "  ex: <" << exmask << '>';
#endif

	strm	<< "]\n";
}

void Process::printOn(ostream& strm) const
{
	strm << process_name;
}

void Process::restore()
{
	ExceptionEnv::stackTop = saved_exception_env_stack_top;
	ExceptionActionTbl::active = saved_exception_action;
	Catch::stackTop = saved_catch_stack_top;
}

void Process::save()
{
	saved_exception_env_stack_top = ExceptionEnv::stackTop;
	saved_exception_action = ExceptionActionTbl::active;
	saved_catch_stack_top = Catch::stackTop;
}

Process::Process(OIOifd&) {}

Process::Process(OIOin&) {}

void Process::storer(OIOout&) const
{
	shouldNotImplement("storeOn");
}

void Process::storer(OIOofd&) const
{
	shouldNotImplement("storeOn");
}
