#ifndef	PROCESS_H
#define	PROCESS_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Process.h,v 3.0 90/05/20 00:20:51 kgorlen Rel $*/

/* Process.h -- Declarations for lightweight processes

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	K. E. Gorlen
	Computer Systems Laboratory, DCRT
	National Institutes of Health
	Bethesda, MD 20892

$Log:	Process.h,v $
 * Revision 3.0  90/05/20  00:20:51  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Link.h"
#include "String.h"
#include "nihclconfig.h"

#ifdef HAVE_SELECT
#include "FDSet.h"
#endif

const int MAXPRIORITY = 7;	// maximum process priority

class Catch;
class ExceptionActionTbl;
class ExceptionEnv;
class HeapProc;
class Scheduler;
class Semaphore;
class StackProc;

#ifndef NESTED_TYPES
typedef char* stackTy;
#endif

class Process: public Link {
	DECLARE_MEMBERS(Process);
public:			// type definitions
#ifdef NESTED_TYPES
	typedef char* stackTy;
#endif
	enum processState { SUSPENDED, RUNNING, TERMINATED };
public:			// static member functions
	static void copyStack(const stackTy* src, stackTy* dst, unsigned long count);
	static stackTy* topOfStack() {
		auto stackTy top;
		stackTy* temp = &top;	// to avoid warning message
		return temp;
	}
private:
	String process_name;
	processState process_state;	// SUSPENDED, RUNNING, or TERMINATED 
	unsigned char process_priority;
	ExceptionEnv* saved_exception_env_stack_top;
	ExceptionActionTbl* saved_exception_action;
	Catch* saved_catch_stack_top;
protected:
#ifdef HAVE_SELECT
	FDSet rdmask, wrmask, exmask;	// masks for select(2)
#endif
	JMP_BUF env;			// environment save structure for setjmp/longjmp
	stackTy* stack_bottom;		// pointer to stack bottom

	friend Scheduler;
	friend Semaphore;
protected:
	Process(const char* name, stackTy* bottom, int priority =0);
	Process(stackTy* bottom, int priority =0);	// MAIN Process constructor
	Process(const Process&);			// shouldNotImplement()
	unsigned& PC()		{ return ENV_PC(env); }
	unsigned PC() const	{ return ENV_PC(env); }
	unsigned& SP()		{ return ENV_SP(env); }
	unsigned SP() const	{ return ENV_SP(env); }
	unsigned& FP()		{ return ENV_FP(env); }
	unsigned FP() const	{ return ENV_FP(env); }
	void add();					// add this process to Scheduler runlist
	virtual	void deepenShallowCopy();		// shouldNotImplement()
	virtual void restore();
	virtual void save();
	virtual void storer(OIOofd&) const;		// shouldNotImplement()
	virtual void storer(OIOout&) const;		// shouldNotImplement()
	virtual void switchContext(Process*) = 0;
public:
	~Process();
	const char* name() const	{ return process_name; }
	processState state() const	{ return process_state; }

#ifdef HAVE_SELECT
	virtual void select(FDSet&, FDSet&, FDSet&);	// add to select list
#endif

	virtual unsigned capacity() const;		// returns stack size 
	virtual int compare(const Object&) const;	// compare process priorities 
	virtual void dumpOn(ostream& strm =cerr) const;
	virtual unsigned hash() const;
	virtual bool isEqual(const Object& ob) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual unsigned char priority() const;
	virtual unsigned char priority(unsigned char newPriority);
	virtual void resume();
	virtual	unsigned size() const = 0;
	virtual void suspend();
	virtual void switchFrom(HeapProc*) = 0;
	virtual	void switchFrom(StackProc*) = 0;
	virtual void terminate();
private:				// shouldNotImplement()
	virtual Object* copy() const;
};

#endif
