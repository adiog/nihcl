// StopLightQ.c -- Stop Light Vehicle Queue LinkedList

#include "StopLightQ.h"
#include "LandVhcl.h"
#include "nihclIO.h"

#define THIS    StopLightQ
#define BASE    VehicleQ
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(StopLightQ,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/StopLightQ.c,v 3.0 90/05/15 22:44:07 kgorlen Rel $",NULL,NULL);

void StopLightQ::addVehicle(LandVhcl& l)
   { BASE::addVehicle(l); }

StopLightQ::StopLightQ(OIOin& strm) : BASE(strm) {}

StopLightQ::StopLightQ(OIOifd& fd) : BASE(fd) {}
