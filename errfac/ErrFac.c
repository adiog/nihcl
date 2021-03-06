/* ErrFac.c -- member functions of class ErrorFacility

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

Class for describing all error messages for a particular facility.
	
$Log:	ErrFac.c,v $
 * Revision 3.0  90/05/15  22:36:51  kgorlen
 * Release for 1st edition.
 * 
*/

static const char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/errfac/RCS/ErrFac.c,v 3.0 90/05/15 22:36:51 kgorlen Rel $";

#include "ErrFac.h"
#include <string.h>

#define DEFAULT_EXPANSION_FACTOR 2
#define expand_by(F,X) (X) + (X)/(F)
#define DEFAULT_FACILITY_CAPACITY 16

const char* left_cmt = "/*";
const char* rght_cmt = "*/";

ErrorSpecs :: ErrorSpecs(int err_sev,char* err_args,char* err_text) {
	severity = err_sev;
	args = new char[strlen(err_args)+1];
	strcpy(args,err_args);
	text = new char[strlen(err_text)+1];
	strcpy(text,err_text);
	}

void ErrorSpecs :: printOn(ostream& strm) {
	strm << severity << ", \042" << args << "\042, " << text;
	}

ErrorFacility :: ErrorFacility(char* long_name,char* short_name,
				int fac_code,char* base_name) {
	longname  = new char[strlen(long_name)+1];
	strcpy(longname,long_name);
	shortname  = new char[strlen(short_name)+1];
	strcpy(shortname,short_name);
	basename  = new char[strlen(base_name)+1];
	strcpy(basename,base_name);
	Code = fac_code;

	capacity = DEFAULT_FACILITY_CAPACITY;
	errlist = new ErrorSpecsPt[capacity];
	size = 0;
	}

void ErrorFacility :: resize(int newcapacity) {
	if ( newcapacity <= capacity ) return;
	ErrorSpecsPt* tmp = errlist;
	errlist = new ErrorSpecsPt[newcapacity];

	for(int i=0; i<=capacity; i++)
	  errlist[i] = tmp[i];

	capacity = newcapacity;
	delete tmp;
	}

void ErrorFacility :: add(ErrorSpecs& sp) {
//cerr << "ErrorFacility: capacity=" << capacity << " size = " << size << "\n";
	if ( size == capacity ) 
	  resize(expand_by(DEFAULT_EXPANSION_FACTOR,capacity));
	errlist[size++] = &sp;
	}
void ErrorFacility :: h_init(ostream& strm) {
	strm << "#ifndef " << basename << "_H\n"
	     << "#define " << basename << "_H\n";
	strm << left_cmt << "\n"
 	     << "* " << basename << ".h\n"
 	     << "* C include file created by errgen utility.  DO NOT EDIT!\n"
	     << rght_cmt << "\n";

	strm << left_cmt << "\n *     ***** " << longname 
			  << " facility *****\n " << rght_cmt << "\n";

	strm << "\nextern void " << shortname << "errinit();\n\n";
	}

void ErrorFacility :: h_define(ostream& strm,char* name,int val) {
	strm << "#define " << shortname << name << "\011\011" << val << "\n";
	}

void ErrorFacility :: h_finish(ostream& strm) {
	strm << "#endif\n";
	}

void ErrorFacility :: printOn(ostream& strm) {
	strm << left_cmt << "\n" << " * " << basename << ".c --"
             << " Error definition file generated by errgen.  DO NOT EDIT!\n"
	     << rght_cmt << "\n";
	strm << "#include <errors.h>\n"
	     << "#include \042" << basename << ".h\042\n"
	     << "extern ErrFac errfac[MAX_FACILITIES];\n";
	strm << left_cmt << "\n"
	     << "*	***** " << longname << " facility *****\n"
	     << rght_cmt << "\n";
	strm << "ErrSpecs " << shortname << "errlist[] = {\n";

	for(int i=0; i<size; i++) {
	  strm << " {";
	  errlist[i]->printOn(strm);
	  strm << " }";
	  if ( i < size-1 ) strm << ",";
	  strm << "\n";
	  };
	strm << "};\n";

	strm << left_cmt << "\n"
	     << "* Error initialization routine for " << longname 
	     << " facility.\n" << rght_cmt << "\n";

	strm << "void " << shortname << "errinit() {\n"
	     << "errfac[" << Code << "].last = " 
	     << shortname << "LAST_ERROR;\n"
	     << "errfac[" << Code << "].longname = \042" <<longname<< "\042;\n"
	     << "errfac[" << Code << "].errlist = " << shortname <<"errlist;\n"
	     << "};\n";
	}
