#ifndef	RANDOM_H
#define	RANDOM_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Random.h,v 3.0 90/05/20 17:40:51 kgorlen Rel $*/

/* Random.h -- declarations for pseudo-random number generator

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

$Log:	Random.h,v $
 * Revision 3.0  90/05/20  17:40:51  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Object.h"

class Random: public VIRTUAL Object {
	DECLARE_MEMBERS(Random);
	long	s1,s2;
	void checkSeeds();
protected:		// storer() functions for object I/O
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	Random();
	Random(long seed1, long seed2);
	float next();
	virtual void deepenShallowCopy();	// {}
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
private:			    // shouldNotImplement()
	virtual int compare(const Object&) const;
};

#endif
