// WaterVhcl.c -- Water Vehicle

#include "WaterVhcl.h"
#include "nihclIO.h"

#define THIS    WaterVhcl
#define BASE    Vehicle
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES Vehicle::desc()

DEFINE_CLASS(WaterVhcl,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/WaterVhcl.c,v 3.0 90/05/15 22:44:13 kgorlen Rel $",NULL,NULL);

void WaterVhcl::_printOn(ostream& strm) const
{
    Vehicle::_printOn(strm);
    strm << "  draft " << draft;
}

void WaterVhcl::deepenShallowCopy()
{
    Vehicle::deepenVBase();
}

WaterVhcl::WaterVhcl(OIOin& strm) :
    Object(strm),
    BASE(strm)
{
    strm >> draft;
}

void WaterVhcl::storer(OIOout& strm) const
{
    Vehicle::storeVBaseOn(strm);
    strm << draft;
}

WaterVhcl::WaterVhcl(OIOifd& fd) :
    Object(fd),
    BASE(fd)
{
    fd >> draft;
}

void WaterVhcl::storer(OIOofd& fd) const
{
    Vehicle::storeVBaseOn(fd);
    fd << draft;
}
