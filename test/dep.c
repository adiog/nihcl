/* Test Object dependencies

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
	Internet:kgorlen@alw.nih.gov

Function:
	
Modification History:
	
$Log:	dep.c,v $
 * Revision 3.0  90/05/20  00:28:58  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/dep.c,v 3.0 90/05/20 00:28:58 kgorlen Rel $";

#include "Point.h"
#include "OrderedCltn.h"

class MyPoint: public Point {
	DECLARE_MEMBERS(MyPoint);
public:
	MyPoint(int newx, int newy) : Point(newx,newy) {}
	~MyPoint()	{ release(); }
	int x() const	{ return Point::xc; }
	int y() const	{ return Point::yc; }
	int x(int newx)	{ Point::xc = newx; changed(); return Point::xc; }
	int y(int newy)	{ Point::yc = newy; changed(); return Point::yc; }
#ifndef BUG_38
// internal <<AT&T C++ Translator 2.00 06/30/89>> error: bus error (or something nasty like that)
protected:		// storer() functions for object I/O
	virtual	void storer(OIOofd& fd)	const	{ Point::storer(fd); }
	virtual	void storer(OIOout& strm) const	{ Point::storer(strm); }
#endif
};

MyPoint::MyPoint(OIOin&) {}

MyPoint::MyPoint(OIOifd&) {}

#define BASE Point
#define BASE_CLASSES Point::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(MyPoint,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/dep.c,v 3.0 90/05/20 00:28:58 kgorlen Rel $",NULL,NULL);

class PointView: public VIRTUAL Object {
	DECLARE_MEMBERS(PointView);
	Point* p;
public:
	PointView(Point& newp)	{ p = &newp; p->addDependent(*this); update(*p,*nil); }
	~PointView()		{ p->removeDependent(*this); }
	virtual int compare(const Object&) const;
	virtual void deepenShallowCopy();
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void update(const Object&, const Object&);
	virtual void printOn(ostream& strm =cout) const;
};

#undef BASE
#define BASE Object
#undef BASE_CLASSES
#define BASE_CLASSES Object::desc()

DEFINE_CLASS(PointView,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/dep.c,v 3.0 90/05/20 00:28:58 kgorlen Rel $",NULL,NULL);

int PointView::compare(const Object& a) const { return p->compare(a); }

void PointView::deepenShallowCopy()
{
	p = Point::castdown(p->deepCopy());
}

unsigned PointView::hash() const    { return p->hash(); }

bool PointView::isEqual(const Object& a) const	{ return p->isEqual(a); }

void PointView::update(const Object& p, const Object& /*unused*/)
{
	cout << p.className() << " changed: " << p << endl;
	cout.flush();
}

void PointView::printOn(ostream& strm) const
{
	strm << *p << endl;
}

PointView::PointView(OIOin&) {}

PointView::PointView(OIOifd&) {}

main()
{
	cout << "Test Object Dependencies" << endl;
	MyPoint p(0,0);
	PointView* v = new PointView(p);
	p.dependents().dumpOn(cout);
	p.x(1); p.y(2);		/* should print changes */
	delete v;
	p.dependents().dumpOn(cout);
	p.x(3); p.y(4);		/* should not print changes */
	v = new PointView(p);
	p.x(5); p.y(6);		/* should print changes */
	p.release();
	p.dependents().dumpOn(cout);
	p.x(7); p.y(8);		/* should not print changes */
}
