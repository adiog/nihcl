#ifndef	EXCEPTACT_H
#define	EXCEPTACT_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/ExceptAct.h,v 3.0 90/05/20 00:19:28 kgorlen Rel $*/

/* ExceptAct.h -- declarations for exception actions

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

$Log:	ExceptAct.h,v $
 * Revision 3.0  90/05/20  00:19:28  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Exception.h"
#include "nihclerrs.h"

class ExceptionAction;
class Process;

class ExceptionActionTbl : public NIHCL {
private:
	static ExceptionActionTbl* active;
	friend ExceptionAction;
	friend void NIHCL::setError(int error, int sev, ...);
	friend Process;
private:
#ifndef NESTED_TYPES
	exceptionTrapTy client_exception_trap;
	exceptionActionTy action[NIHCL__LAST_ERROR-NIHCL__FIRSTERROR+1];
#else
	ExceptionTrap::exceptionTrapTy client_exception_trap;
	ExceptionAction::exceptionActionTy
		action[NIHCL__LAST_ERROR-NIHCL__FIRSTERROR+1];
#endif
	friend ExceptionAction;
	friend AbortException;
	friend RaiseException;
	friend ExceptionTrap;
public:
	ExceptionActionTbl();
	void act(unsigned error, int sev);
};

#endif
