/* Semaphore.c -- implementation of Semaphore

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

Objects of class Semaphore are used to synchronize Processes.

$Log:	Semaphore.c,v $
 * Revision 3.0  90/05/20  00:21:08  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Semaphore.h"
#include "Process.h"
#include "Scheduler.h"
#include "nihclIO.h"

#define	THIS	Semaphore
#define	BASE	Object
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES LinkedList::desc()
#define VIRTUAL_BASE_CLASSES Object::desc()

DEFINE_CLASS(Semaphore,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Semaphore.c,v 3.0 90/05/20 00:21:08 kgorlen Rel $",NULL,NULL);

extern const int NIHCL_ASTBLK,NIHCL_DLSEMWAIT,NIHCL_CPSEMWAIT,NIHCL_STSEMWAIT;

Semaphore::Semaphore(int initialCount)	{ count = initialCount; }

#ifndef BUG_TOOBIG
// yacc stack overflow

Semaphore::Semaphore(const Semaphore& s) : waitList(s.waitList)
{
	count = s.count;
}

#endif

void Semaphore::signal(unsigned n)
{
	if (n == 0) return;
	AST_DISABLE;
		register Process* next;
		while (count<0 && n>0) {
			next = Process::castdown(waitList.removeFirst());
			if (next->state() != Process::TERMINATED) {
				next->resume();
				n--;
			}
			count++;
		}
		count += n;
	AST_ENABLE;
}

void Semaphore::wait()
{
	AST_DISABLE;
		if (--count < 0) {
			if (Scheduler::astActive()) setError(NIHCL_ASTBLK,DEFAULT,this,className(),"wait");
			Scheduler::activeProcess().suspend();
			waitList.addLast(Scheduler::activeProcess());
		}
	AST_ENABLE;
	if (count < 0) Scheduler::schedule();
}

Semaphore::~Semaphore()
{
	if (count<0) setError(NIHCL_DLSEMWAIT,DEFAULT,-count,this,className());
}

Object* Semaphore::copy() const	{ return deepCopy(); }

void Semaphore::deepenShallowCopy()
{
	if (count < 0) setError(NIHCL_CPSEMWAIT,DEFAULT,-count,this,className());
}

unsigned Semaphore::hash() const	{ return (unsigned)this; }

bool Semaphore::isEqual(const Object& ob) const	{ return isSame(ob); }

void Semaphore::dumpOn(ostream& strm) const
{
	strm << className() << "[count: " << count << '\n';
	DO(waitList,Process,p) p->dumpOn(strm); OD
	strm << "]\n";
}

void Semaphore::printOn(ostream& strm) const
{
	strm << "count: " << count;
	if (count < 0) strm << "  waitList:";
	DO(waitList,Process,p) strm << ' ' << *p; OD
}

bool Semaphore::includes(const Process& p) const
{
	AST_DISABLE;
	bool i = waitList.includes(p);
	AST_ENABLE;
	return i;
}

Process* Semaphore::remove(Process& p)
{
	AST_DISABLE;
	if (count < 0 && waitList.includes(p)) {
		waitList.remove(p);
		++count;
		AST_ENABLE;
		return &p;
	}
	else {
		AST_ENABLE;
		return 0;
	}
}

Process* Semaphore::removeFirst()
{
	AST_DISABLE;
	if (count < 0) {
		Process* p = Process::castdown(waitList.removeFirst());
		++count;
		AST_ENABLE;
		return p;
	}
	else {
		AST_ENABLE;
		return 0;
	}
}

Process* Semaphore::removeLast()
{
	AST_DISABLE;
	if (count < 0) {
		Process* p = Process::castdown(waitList.removeLast());
		++count;
		AST_ENABLE;
		return p;
	}
	else {
		AST_ENABLE;
		return 0;
	}
}

int Semaphore::value() const	{ return count; }

Semaphore::Semaphore(OIOin& strm)
	: BASE(strm)
{
	strm >> count;
}

void Semaphore::storer(OIOout& strm) const
{
	if (count < 0) setError(NIHCL_STSEMWAIT,DEFAULT,-count,this,className());
	BASE::storer(strm);
	strm << count;
}

Semaphore::Semaphore(OIOifd& fd)
	: BASE(fd)
{
	fd >> count;
}

void Semaphore::storer(OIOofd& fd) const
{
	if ( count < 0 )
		setError(NIHCL_STSEMWAIT,DEFAULT,-count,this,className());
	BASE::storer(fd);
	fd << count;
}

int Semaphore::compare(const Object&) const
{
	shouldNotImplement("compare");
	return 0;
}
