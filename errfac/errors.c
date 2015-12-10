/* errors.c -- Error reporting library routines

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

Function:

$Log:	errors.c,v $
 * Revision 3.0  90/05/15  22:37:00  kgorlen
 * Release for 1st edition.
 * 
*/

static const char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/errfac/RCS/errors.c,v 3.0 90/05/15 22:37:00 kgorlen Rel $";

#include "errors.h"
#include "errlib.h"
#include <libc.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

ErrFac errfac[MAX_FACILITIES];	// error reporting facilities
static FILE* fout = stderr;		// current error FILE
static int print_severity = WARNING;	// print threshhold
static int exit_severity  = ERROR;	// exit threshhold
#define format_severity 1
#define format_facility 2
static char* sevmsg[5] = { "success","info","warning","error","fatal" };
static int format_cntl    = 3;	// format control: 0=~facility&~severity,
				// 1=~facility, 2=~severity, 3=all
static int dump_cntl = 0;	// dump control: not implemented

static char* bad_fac_msg = "*** Invalid Facility (%d) -- from error (%d)\n";
static char* bad_err_msg="*** Error No.(%d) out of range -- from error (%d)\n";

void seterropt(int esev, int psev, int dump, int fmt, FILE* filep) 
{
	exit_severity = esev;
	print_severity = psev;
	dump_cntl = dump;
	format_cntl = fmt;
	if ( filep == 0 )
	  fout = stderr;
         else // use stdout
          fout = filep;
}

void geterropt(int& esev,int& psev,int& dump,int& fmt,FILE*& filep) 
{
	esev = exit_severity;
	psev = print_severity;
	fmt = format_cntl;
	dump = dump_cntl;
	filep = fout;
	}

static void printerror(int sev,const char* prefix,char* msg) 
{
	char facnameprefix[80];
	char severityprefix[80];
	if ( format_cntl&format_facility ) 
	  sprintf(facnameprefix,"%s: ",errfac[FACILITY_CODE(errno)].longname);
         else // no facility prefix
	  facnameprefix[0] = '\0';
        if ( format_cntl&format_severity )
	  sprintf(severityprefix,"%s: ",sevmsg[-sev]);
	 else // no severity prefix
          severityprefix[0] = '\0';
	fprintf(fout,"%s%s%s%s\n",prefix,facnameprefix,severityprefix,msg);
}

void errfac_prepNextArg(char* p,char* q) 
{
	int flag = 1;
	while ( *p != '\0' ) {
	  if ( flag&&(*p == '\001') ) {
	    *(q++) = '%';
	    ++p;
	    flag = 0;
	    }
           else // transfer character
            *(q++) = *(p++);
          }
        *q = '\0';
}

void errfac_prepText(char* p, char* q)
{
     while ( *p != '\0' ) {
	if ( *p == '%' ) {
	  if ( *(p+1) == '%' ) {// skip "%%"
	        *q++ = *p++;
		*q++ = *p++;
		}
	    else {// change '%' to '^A'
		*q++ = '\001';	
		++p;
	        }
	  }
	 else // transfer character
	  *q++ = *p++;
	}
     *q = '\0';
}

void errfac_errorMessage(int sev,char* msg)
{
	if ( errfac_isPrintSeverity(sev) )  // print error msg
	  printerror(sev,"",msg);

	if ( errfac_isExitSeverity(sev) ) {
	    if ( dump_cntl ) abort();
	      else exit(1);
	    }
}

ErrFac* errfac_at(int err)
{
	char buf[128];
	/* facility code */
	int fac_code = FACILITY_CODE(err);

	if ( (fac_code < 0)||(fac_code > MAX_FACILITIES) ) { // bad facility
	   sprintf(buf,bad_fac_msg,fac_code,err);
	   errfac_errorMessage(ERROR,buf);
	   }
	// valid facility
        ErrFac fac = errfac[fac_code];

#ifdef TRACE
printf("seterror> Facility Code: %d  Facility Name: %s  Last Error: %d\n",
	fac_code,fac.longname,fac.last);
#endif
	   /* error number */
	   int err_code = OFFSET_INDEX(err);
	   int first_code = err&FAC_MASK;

	   if ( (err < first_code)||(err > fac.last) ) { // bad error
	     sprintf(buf,bad_err_msg,err_code,err);
	     errfac_errorMessage(ERROR,buf);
	     }
	return &errfac[fac_code];
}

char* errfac_argumentCodes(int err)
{
	ErrFac* fac = errfac_at(err);
	int err_code = OFFSET_INDEX(err);
	return fac->errlist[err_code].args;
}

char* errfac_errorText(int err,char* buf)
{
	ErrFac* fac = errfac_at(err);
	int err_code = OFFSET_INDEX(err);
	char* txt = fac->errlist[err_code].text;
	if ( buf )
	   errfac_prepText(txt/*IN*/,buf/*OUT*/);
	return txt;
}

int errfac_severity(int err)
{
	ErrFac* fac = errfac_at(err);
	int err_code = OFFSET_INDEX(err);
	return fac->errlist[err_code].severity;
}

int errfac_printSeverity() { return print_severity; }
int errfac_exitSeverity() { return exit_severity; }
int errfac_isPrintSeverity(int s) { return (s<=print_severity); }
int errfac_isExitSeverity(int s) { return (s<=exit_severity); }

#ifdef sparc
// Use magic name to make stdarg work
#define sev __builtin_va_alist
#endif

int seterror(int err, int sev, ...)
{
#ifdef TRACE
printf("seterror> Error No: %d  Severity: %d\n",err,sev);
#endif
	errno = err;
        char buf[132],buf0[132];

	errfac_errorText(err,buf/*OUT*/);
     
	char* p = errfac_argumentCodes(err);
#ifdef TRACE
printf("seterror> argument codes %s\n",p);
#endif
	va_list ap;
	va_start(ap,sev);
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

	int severity = (sev < 0)? sev:(errfac_severity(err));
	errfac_errorMessage(severity,buf);
	if ( errfac_isExitSeverity(severity) ) {
	   printf("NIHCL: fatal: Tried to continue after error %d\n",err);
	   abort();
	   }
	return severity;
}
