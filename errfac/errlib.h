#ifndef ERRLIBH
#define ERRLIBH

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/errfac/RCS/errlib.h,v 3.0 90/05/15 22:36:58 kgorlen Rel $

/* errlib.h -- header file for portable error facility

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	S.M. Orlow
	Systex,Inc.
	Beltsville, MD 20705
	301-474-0111
	June, 1986

Contractor:
	K. E. Gorlen
	Bg. 12A, Rm. 2017
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892
	Phone: (301) 496-5363
	uucp: uunet!nih-csl!kgorlen
	Internet: kgorlen@alw.nih.gov

$Log:	errlib.h,v $
 * Revision 3.0  90/05/15  22:36:58  kgorlen
 * Release for 1st edition.
 * 
*/

#include <stdio.h>

extern "C" {
void errprefix(const char*);
void errpostfix(const char*);
void formaterror(const char*,char*,int);
void seterropt(int esev,int psev,int dump,int fmt,FILE* filep);
void geterropt(int& esev,int& psev,int& dump,int& fmt,FILE*& filep);
void printerror(const char* prefix);
int seterror(int err,int sev, ... );

typedef int (*perrtrap)();
void seterrtrap(perrtrap func,int sev);
void clrerrtrap(int sev);
}
#endif /* ERRLIBH */

