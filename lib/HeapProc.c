/* HeapProc.c -- Implementation of Process with stack on free storage heap

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
	January, 1988

Function:
	
Modification History:

$Log:	HeapProc.c,v $
 * Revision 3.0  90/05/20  00:19:45  kgorlen
 * Release for 1st edition.
 * 
*/

#include "HeapProc.h"
#include "Scheduler.h"
#include "nihclIO.h"

#define	THIS	HeapProc
#define	BASE	Process
#define	BASE_CLASSES BASE::desc()
#define	MEMBER_CLASSES
#define	VIRTUAL_BASE_CLASSES

extern const int NIHCL_BADTRACETBL,NIHCL_STACKOV;

DEFINE_ABSTRACT_CLASS(HeapProc,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/HeapProc.c,v 3.0 90/05/20 00:19:45 kgorlen Rel $",NULL,NULL);

HeapProc::HeapProc(const char* name, stackTy* bottom, int priority, unsigned long size)
	: BASE(name, bottom, priority)
{
	stack_size = size; 
}

HeapProc::HeapProc(OIOifd& fd) : BASE(fd) {}

HeapProc::HeapProc(OIOin& strm) : BASE(strm) {}

HeapProc::~HeapProc()
{
	delete stack_bottom;
}

void HeapProc::setupStack()
{
	stackTy* top = topOfStack();
	stackTy* bottom = stack_bottom;
	stack_bottom = new stackTy[stack_size];

#ifdef sparc
	asm("t	0x03");	    // ST_FLUSH_WINDOWS
#endif

#if STACK_GROWS_DOWN
	stack_bottom[0] = (stackTy)UNINITIALIZED;
	unsigned long size = bottom-top;
	copyStack(top+1, stack_bottom+stack_size-size, size);
	long delta = (stack_bottom+stack_size-1 - bottom) * sizeof(stackTy);
#else
	stack_bottom[stack_size-1] = (stackTy)UNINITIALIZED;
	unsigned long size = top-bottom;
	copyStack(bottom, stack_bottom, size);
	long delta = (stack_bottom - bottom) * sizeof(stackTy);
#endif

#if defined(mc68000) || defined(sparc)
	SP() += delta;	// adjust stack pointer
	FP() += delta;	// adjust frame pointer
#endif

#ifdef ibm032

#ifdef UCB43BSD
/* jmpbuf layout:

	jmpbuf[0]	r1	stack pointer
	jmpbuf[1]	r6
	jmpbuf[2]	r7
	jmpbuf[3]	r8
	jmpbuf[4]	r9
	jmpbuf[5]	r10
	jmpbuf[6]	r11
	jmpbuf[7]	r12
	jmpbuf[8]	r13
	jmpbuf[9]	r14
	jmpbuf[10]	r15	return address
	jmpbuf[11]		saved sigmask
	jmpbuf[12] - jmpbuf[15] unused
*/

struct TT_D_COM	{		// structure of AOS 4.3 trace table
	unsigned magic1:8,	// = 0xDF
		code:8,		// = 7
		magic2:8,	// = 0xDF
		first_gpr:4,	// first general register saved
		optw:1,	optx:1,	opty:1, :1;   // option flags
	char	npars:4,	// number of parameters
		frame_reg:4;	// frame pointer register number
	char	fpr_save:8;	// saved fp register mask (if opty==1)
	char	lcl_off_size:2,	// size of lcl_offset
		lcl_offset1:6,	// # words to top of stack frame from frame_reg
		lcl_offsetn[3];	// 6, 14, 22, or 30 bits
};

// Find trace table
	register short* p = (short*)PC();
	while (((*p++ & 0xff00) != 0xdf00) || ((*p & 0xff00) != 0xdf00));
	TT_D_COM* ttp = (TT_D_COM*)--p;
	if (ttp->code != 7) {
		setNIHCLerror(NIHCL_BADTRACETBL,FATAL,ttp,className(),this);
		return;
	}
// Adjust frame pointer register
	if (ttp->frame_reg >= 6) env[ttp->frame_reg-6+1] += delta;
// Adjust stack pointer register
	SP() += delta;
#endif

#ifdef SYSVR2
	SP() += delta;
#endif

#endif

}

unsigned HeapProc::size() const   { return stack_size; }

void HeapProc::switchContext(Process* new_process)
{
// check for stack overflow
#if STACK_GROWS_DOWN
	if (topOfStack() < stack_bottom || stack_bottom[0] != (stackTy)UNINITIALIZED)
		setError(NIHCL_STACKOV,DEFAULT,name());
#else
	if (topOfStack() >= stack_bottom+stack_size || stack_bottom[stack_size-1] != (stackTy)UNINITIALIZED)
		setError(NIHCL_STACKOV,DEFAULT,name());
#endif
	save();
	new_process->switchFrom(this);
}

void HeapProc::switchFrom(HeapProc*)
// switch from active HeapProc to next HeapProc
{
	LONGJMP(env, Scheduler::resume_new_process);
}

void HeapProc::switchFrom(StackProc*)
// switch from active StackProc to next HeapProc
{
	LONGJMP(env, Scheduler::resume_new_process);
}
