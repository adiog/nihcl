/* gettok.c -- get token from a String object

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

$Log:	gettok.c,v $
 * Revision 3.0  90/05/15  22:37:04  kgorlen
 * Release for 1st edition.
 * 
*/

static const char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/errfac/RCS/gettok.c,v 3.0 90/05/15 22:37:04 kgorlen Rel $";

#include "gettok.h"

/* is_char_of -- return 1 when char is in string */
int is_char_of(char ch,char* q) {
      while ( *q != '\0' ) 
        if ( ch == *(q++) ) return 1;
      return 0;
    }/* end is_char_of */

static char* lastp = 0;

char* gettok(char* inbuf,char* tmnl) {
   char* retp;

   if ( inbuf != 0 ) {
     lastp = inbuf;
     retp = inbuf;
     }
    else
     retp = lastp;

    while ( *lastp != '\0' ) { /* find next terminal char */
      if ( is_char_of(*lastp,tmnl) ) break;
      ++lastp;
      };/* end while */
    if ( *lastp != '\0' ) {
      *(lastp++) = '\0';
      while ( *lastp != '\0' ) {/* skip all adjacent terminal chars */
          if ( !is_char_of(*lastp,tmnl) ) break;
	  ++lastp;
	  };/*end while*/
      };/* end if*/
   return retp;
}/* end gettok */
