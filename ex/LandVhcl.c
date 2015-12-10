// LandVhcl.c -- Land Vehicle

#include "LandVhcl.h"
#include "nihclIO.h"

#define THIS    LandVhcl
#define BASE    Vehicle
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES Vehicle::desc()

DEFINE_CLASS(LandVhcl,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/LandVhcl.c,v 3.0 90/05/15 22:43:37 kgorlen Rel $",NULL,NULL);

void LandVhcl::_printOn(ostream& strm) const
{
    Vehicle::_printOn(strm);
    strm << "  axles " << axles;
}

void LandVhcl::deepenShallowCopy()
{
    Vehicle::deepenVBase();
}

LandVhcl::LandVhcl(OIOin& strm) :
    Object(strm),
    BASE(strm)
{
    strm >> axles;
}

void LandVhcl::storer(OIOout& strm) const
{
    Vehicle::storeVBaseOn(strm);
    strm << axles;
}

LandVhcl::LandVhcl(OIOifd& fd) :
    Object(fd),
    BASE(fd)
{
    fd >> axles;
}

void LandVhcl::storer(OIOofd& fd) const
{
    Vehicle::storeVBaseOn(fd);
    fd << axles;
}
