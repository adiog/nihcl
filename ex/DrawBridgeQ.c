// DrawBridgeQ.c -- Stop Light Vehicle Queue LinkedList

#include "DrawBridgeQ.h"
#include "WaterVhcl.h"
#include "nihclIO.h"

#define THIS    DrawBridgeQ
#define BASE    VehicleQ
#define BASE_CLASSES BASE::desc()
#define MEMBER_CLASSES
#define VIRTUAL_BASE_CLASSES

DEFINE_CLASS(DrawBridgeQ,1,"$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/DrawBridgeQ.c,v 3.0 90/05/15 22:43:31 kgorlen Rel $",NULL,NULL);

void DrawBridgeQ::addVehicle(WaterVhcl& l)
   { BASE::addVehicle(l); }

DrawBridgeQ::DrawBridgeQ(OIOin& strm) : BASE(strm) {}

DrawBridgeQ::DrawBridgeQ(OIOifd& fd) : BASE(fd) {}
