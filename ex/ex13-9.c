// ex13-9.c -- MI with the NIH Class Library

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-9.c,v 3.0 90/05/15 22:44:51 kgorlen Rel $

#include "LandVhcl.h"
#include "WaterVhcl.h"
#include "AmphibVhcl.h"
#include "StopLightQ.h"
#include "DrawBridgeQ.h"

StopLightQ stopLightQ[2];
DrawBridgeQ drawBridgeQ;

main()
{
    stopLightQ[0].addVehicle(*new LandVhcl(4.1, 12.0));
    stopLightQ[1].addVehicle(*new LandVhcl(4.2, 12.0));
    stopLightQ[0].addVehicle(*new LandVhcl(4.3, 12.0));
    stopLightQ[1].addVehicle(*new LandVhcl(4.4, 12.0));
    drawBridgeQ.addVehicle(*new WaterVhcl(21.0, 19.0, 3.5));
    drawBridgeQ.addVehicle(*new WaterVhcl(10.0, 30.0, 2.0));
    stopLightQ[0].addVehicle(*new AmphibVhcl(5.0, 15.0, 3.0));
    drawBridgeQ.addVehicle(*new AmphibVhcl(5.1, 15.0, 3.0));

    cout << "allVehicles:\n"; Vehicle::printAll();
    cout << endl;
    cout << "stopLightQ[0]:\n"; stopLightQ[0].printOn();
    cout << endl;
    cout << "stopLightQ[1]:\n"; stopLightQ[1].printOn();
    cout << endl;
    cout << "drawBridgeQ:\n"; drawBridgeQ.printOn();
    cout << endl;

    cout << "Test deepCopy()" << endl;
    Vehicle* copy =
        Vehicle::castdown(drawBridgeQ.last()->deepCopy());
    cout << *copy << endl;
    cout << "allVehicles:\n"; Vehicle::printAll(); cout << endl;
    delete copy;
    cout << "allVehicles:\n"; Vehicle::printAll(); cout << endl;

    Vehicle::saveQueues("trafficfile",
        &stopLightQ[0], &stopLightQ[1], &drawBridgeQ, 0);
}
