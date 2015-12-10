/* Stack.c -- implementation of class Stack

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
	October, 1985

Function:
	
Member function definitions for class Stack.

$Log:	Stack.c,v $
 * Revision 3.0  90/05/20  00:21:27  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Stack.h"
#include "nihclIO.h"

#define	THIS	Stack
#define	BASE	SeqCltn
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES OrderedCltn::desc()
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(Stack,2,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Stack.c,v 3.0 90/05/20 00:21:27 kgorlen Rel $",NULL,NULL);

Stack::Stack(unsigned size) : contents(size) {}

Stack::Stack(const Stack& s) : contents(s.contents) {}

Object* Stack::add(Object& ob)	{ return contents.add(ob); }

Object*& Stack::at(int i)			{ return contents.at(size()-i-1); }

const Object *const& Stack::at(int i) const	{ return contents.at(size()-i-1); }

unsigned Stack::capacity() const	{ return contents.capacity(); }

void Stack::deepenShallowCopy()
{
	BASE::deepenShallowCopy();
	contents.deepenShallowCopy();
}

unsigned Stack::hash() const		{ return contents.hash(); }

bool Stack::isEmpty() const		{ return contents.size()==0; }

Object* Stack::last() const		{ return contents.last(); }

void Stack::reSize(unsigned newSize) { contents.reSize(newSize); }

void Stack::removeAll()
{
	contents.removeAll();
}

Object* Stack::removeLast()	{ return contents.removeLast(); }

unsigned Stack::size() const		{ return contents.size(); }

Stack::Stack(OIOin& strm)
:
#ifdef MI
	Object(strm),
#endif
	BASE(strm),
	contents(strm)
{
}

void Stack::storer(OIOout& strm) const
{
	BASE::storer(strm);
	contents.storeMemberOn(strm);
}

Stack::Stack(OIOifd& fd)
:
#ifdef MI
	Object(fd),
#endif
	BASE(fd),
	contents(fd)
{
}

void Stack::storer(OIOofd& fd) const
{
	BASE::storer(fd);
	contents.storeMemberOn(fd);
}

void Stack::atAllPut(Object&)	{ shouldNotImplement("atAllPut"); }

int Stack::indexOfSubCollection(const SeqCltn& /* cltn */, int /* start */) const
{
	shouldNotImplement("indexOfSubCollection");
	return 0;
}

Object* Stack::remove(const Object&)
{
	shouldNotImplement("remove");
	return 0;
}

void Stack::replaceFrom(int /* start */, int /* stop */, const SeqCltn&  /* replacement */, int /* startAt */)
{
	shouldNotImplement("replaceFrom");
}
