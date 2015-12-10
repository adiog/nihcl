// AmphibVhcl.c -- Amphibious Vehicle

#include "AmphibVhcl.h"
#include "nihclIO.h"

#define THIS    AmphibVhcl
#define BASE_CLASSES LandVhcl::desc(),WaterVhcl::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS_MI(AmphibVhcl,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/AmphibVhcl.c,v 3.0 90/05/15 22:43:16 kgorlen Rel $",NULL,NULL);

void* AmphibVhcl::_castdown(const Class& target) const
{
    if (&target == desc()) return (void*)this;
    void* p = LandVhcl::_castdown(target);
    void* q = p;
    if (p = WaterVhcl::_castdown(target)) ambigCheck(p,q,target);
    return q;
}

void AmphibVhcl::_printOn(ostream& strm) const
{
    LandVhcl::_printOn(strm);
    WaterVhcl::_printOn(strm);
}

void AmphibVhcl::deepenShallowCopy()
{
    LandVhcl::deepenShallowCopy();
    WaterVhcl::deepenShallowCopy();
}

AmphibVhcl::AmphibVhcl(OIOin& strm) :
    Object(strm),
    Vehicle(strm),
    LandVhcl(strm),
    WaterVhcl(strm)
{
}

void AmphibVhcl::storer(OIOout& strm) const
{
    Vehicle::storeVBaseOn(strm);
    LandVhcl::storer(strm);
    WaterVhcl::storer(strm);
}

AmphibVhcl::AmphibVhcl(OIOifd& fd) :
    Object(fd),
    Vehicle(fd),
    LandVhcl(fd),
    WaterVhcl(fd)
{
}

void AmphibVhcl::storer(OIOofd& fd) const
{
    Vehicle::storeVBaseOn(fd);
    LandVhcl::storer(fd);
    WaterVhcl::storer(fd);
}
