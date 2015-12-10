// ex13-10.c -- MI and Object I/O readFrom()

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-10.c,v 3.0 90/05/15 22:44:32 kgorlen Rel $

#include <fstream.h>
#include <osfcn.h>
#include "LandVhcl.h"
#include "WaterVhcl.h"
#include "AmphibVhcl.h"
#include "StopLightQ.h"
#include "DrawBridgeQ.h"
#include "OrderedCltn.h"
#include "OIOnih.h"

StopLightQ* stopLightQ[2];
DrawBridgeQ* drawBridgeQ;

main()
{
    ifstream in("trafficfile");
    if (in.fail()) {
        cerr << "Failed to open trafficfile\n";
        exit(1);
    }
    OrderedCltn& allQueues = *OrderedCltn::readFrom(OIOnihin(in));
    stopLightQ[0] = StopLightQ::castdown(allQueues[1]);
    stopLightQ[1] = StopLightQ::castdown(allQueues[2]);
    drawBridgeQ = DrawBridgeQ::castdown(allQueues[3]);

    cout << "allVehicles:\n"; Vehicle::printAll();
    cout << endl;
    cout << "stopLightQ[0]:\n"; stopLightQ[0]->printOn();
    cout << endl;
    cout << "stopLightQ[1]:\n"; stopLightQ[1]->printOn();
    cout << endl;
    cout << "drawBridgeQ:\n"; drawBridgeQ->printOn();
    cout << endl;
}
