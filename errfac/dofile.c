/* dofile.c -- Miscellaneous file-handling functions

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

Miscellaneous file-handling functions.

$Log:	dofile.c,v $
 * Revision 3.0  90/05/15  22:36:54  kgorlen
 * Release for 1st edition.
 * 
*/

static const char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/errfac/RCS/dofile.c,v 3.0 90/05/15 22:36:54 kgorlen Rel $";

#include "dofile.h"
#include <string.h>
#include <fcntl.h>
#include <osfcn.h>

extern int errno;

/* base_filename -- extract base file name (drop extension) */
char* base_filename(char* p) {
  char* p0 = p;

  while ( (*p0 != '\0')&&(*p0 != '.') ) ++p0;

  char* q = new char[p0-p+1];
  char* q0 = q;
  while ( p != p0 )
    *(q++) = *(p++);
  *q = '\0';
  return q0;
}/* base_filename */

/* ext_filename -- extract extension from filename */
char* ext_filename(char* p) {
  while ( (*p != '\0')&&(*p != '.') ) ++p;
  char* q = new char[strlen(p)+1];
  strcpy(q,p);
  return q;
} /* end ext_filename*/


ostream* open_ostream(char* fname) {
  errno = 0;

  int fd;
  ostream* strm = new ostream((fd=creat(fname,0664),fd));
  if ( fd == -1 ) {
   switch ( errno ) {
     case 2:
       cerr << "errgen> file does not exist -- " << fname << "\n";
       break;
     default:
       cerr << "errgen> file not open -- " << fname << "\n";
       break;
     };
   exit(1);
   };
  cerr << "open_ostream> " << fname << "\n";
  return strm;
}

ostream* append_ostream(char* fname) {
cerr << "append_ostream> " << fname << "\n";
  int fd;
  ostream* strm = new ostream((fd=open(fname,O_APPEND),fd));
  if ( fd == -1 ) {
   cerr << "errgen> file not open -- " << fname << "\n";
   exit(1);
   };
  return strm;
}

istream* open_istream(char* fname) {
  errno = 0;
  int fd;
  istream* strm = new istream((fd=open(fname,O_RDONLY),fd));
  if ( fd == -1 ) {
    switch ( errno ) {
      case 2:
        cerr << "errgen> file does not exist -- " << fname << "\n";
        break;
      default:
        cerr << "errgen> file not open -- " << fname << "\n";
        break;
      };

   exit(1);
   };
  cerr << "open_istream> " << fname << "\n";
  return strm;
}
