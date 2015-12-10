/* Exception.c -- NIHCL exception handling

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
	February, 1986

Function:

NIHCL exception handling.
	
$Log:	Exception.c,v $
 * Revision 3.0  90/05/20  00:19:30  kgorlen
 * Release for 1st edition.
 * 
*/

#include "ExceptAct.h"
#include <osfcn.h>
#include <libc.h>
#include <errlib.h>
#include <stdarg.h>

#include "nihclconfig.h"
#include "nihclerrs.h"
#include "nihclerrsx.h"

static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Exception.c,v 3.0 90/05/20 00:19:30 kgorlen Rel $";

static ExceptionEnv topExceptionEnv;

static Catch topCatch;
Catch* Catch::stackTop = &topCatch;
ExceptionEnv* ExceptionEnv::stackTop = 0;
ExceptionEnv* ExceptionEnv::lastResort = 0;

void ExceptionEnv::raise(int exception)
{
	if (exception == 0) {
		cerr << "Tried to RAISE exception code 0\n";
		abort();
	}
	if (prev == 0) {	// i.e.,  this == lastResort
		cerr << "NIHCL: fatal: Unhandled exception code " << exception << '\n';
		exit(1);
	}
	pop();
#if STACK_GROWS_DOWN
	for (register Catch* p = Catch::stackTop->next; p < (Catch*)this && p != Catch::stackTop; p = p->next)
#else
	for (register Catch* p = Catch::stackTop->next; p > (Catch*)this && p != Catch::stackTop; p = p->next)
#endif
		p->obj->destroyer();
	Catch::stackTop->next = p;
	p->prev = Catch::stackTop;
	longjmp(env,exception);
}

Catch::Catch()
{
	next = prev = this;
	obj = Object::nil;
}

Catch::Catch(Object* ob)
{
	obj = ob;
	void* top[2];
#if STACK_GROWS_DOWN
	if ((void*)this < (void*)ExceptionEnv::stackTop && (void*)this > (void*)top) {	// this on stack
#else
	if ((void*)this > (void*)ExceptionEnv::stackTop && (void*)this < (void*)top) {	// this on stack
#endif
		next = stackTop->next;
		prev = stackTop;
		stackTop->next = this;
		next->prev = this;
	}
	else next = 0;		// Catch object was allocated by new
}

Catch::~Catch()
{
	if (next != 0) {
		next->prev = prev;
		prev->next = next;
	}
	obj->destroyer();
}

static ExceptionActionTbl mainExceptionActionTbl;
ExceptionActionTbl* ExceptionActionTbl::active = &mainExceptionActionTbl;

#ifdef sparc
// Use magic name to make stdarg work
#define sev_ __builtin_va_alist
#endif

void NIHCL::setError(int err, int sev_, ...)
{
	ExceptionActionTbl::active->act((unsigned)err,sev_);
#ifdef TRACE
printf("seterror> Error No: %d  Severity: %d\n",err,sev_);
#endif
	errno = err;
        char buf[132],buf0[132];

	errfac_errorText(err,buf/*OUT*/);
     
	char* p = errfac_argumentCodes(err);
#ifdef TRACE
printf("seterror> argument codes %s\n",p);
#endif
	va_list ap;
	va_start(ap,sev_);
	while ( *p != '\0' ) { // set up next arg
	  errfac_prepNextArg(buf/*IN*/,buf0/*OUT*/);
	  switch ( *(p++) ) {
	     case 'I': 
		int i = va_arg(ap,int);
	     	sprintf(buf,buf0,i);
    	      	break;
	     case 'S':
		char* s = va_arg(ap,char*);
	     	sprintf(buf,buf0,s);
	        break;
	     case 'D':
	        double d = va_arg(ap,double);
	     	sprintf(buf,buf0,d);
	        break;
	     default : // ignored
	        break;
	     }// end switch
          }// end while
	va_end(ap);

	int severity = (sev_ < 0)? sev_:(errfac_severity(err));
	errfac_errorMessage(severity,buf);
	if ( errfac_isExitSeverity(severity) ) {
	   cerr << "NIHCL: fatal: Tried to continue after error "
		<< err <<'\n';
	   abort();
	   }
}

ExceptionActionTbl::ExceptionActionTbl()
{
	client_exception_trap = NULL;
	for (register int i=NIHCL__LAST_ERROR-NIHCL__FIRSTERROR; i>=0; i--)
		action[i] = ExceptionAction::ABORT;
}

void ExceptionActionTbl::act(unsigned error, int sev)
{
	if (client_exception_trap != NULL) {
		(*client_exception_trap)(error,sev);
	}
	if (error >= NIHCL__FIRSTERROR && error <= NIHCL__LAST_ERROR) {
		switch (action[error-NIHCL__FIRSTERROR]) {
			case ExceptionAction::RAISE: RAISE(error);
			case ExceptionAction::ABORT: return;
		}
	}
}

ExceptionAction::ExceptionAction(unsigned error)
{
	if ( (error < NIHCL__FIRSTERROR)||(error > NIHCL__LAST_ERROR) ) {
		setError(NIHCL_BADERRNUM,DEFAULT,"ExceptionAction",error);
		return;
	}
	error_code = error;
	old_action = ExceptionActionTbl::active->action[error-NIHCL__FIRSTERROR];
}

ExceptionAction::~ExceptionAction()
{
	ExceptionActionTbl::active->action[error_code-NIHCL__FIRSTERROR] = old_action;
}

AbortException::AbortException(unsigned error) : ExceptionAction(error)
{
	ExceptionActionTbl::active->action[error-NIHCL__FIRSTERROR] = ExceptionAction::ABORT;
}

RaiseException::RaiseException(unsigned error) : ExceptionAction(error)
{
	ExceptionActionTbl::active->action[error-NIHCL__FIRSTERROR] = ExceptionAction::RAISE;
}

ExceptionTrap::ExceptionTrap(exceptionTrapTy xtrap)
{
	old_trap = ExceptionActionTbl::active->client_exception_trap;
	ExceptionActionTbl::active->client_exception_trap = xtrap;
}

ExceptionTrap::~ExceptionTrap()
{
	ExceptionActionTbl::active->client_exception_trap = old_trap;
}
