// ex13-11.c -- Limitation of Object I/O

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex13-11.c,v 3.0 90/05/15 22:44:35 kgorlen Rel $

#include <fstream.h>
#include <osfcn.h>
#include "QLink.h"
#include "LandVhcl.h"
#include "OIOnih.h"

main()
{
    QLink* qlp = new LandVhcl(4.1, 12.0);
    Link* lp = (QLink*) new LandVhcl(4.2, 12.0);
    ofstream outstrm("badfile",ios::out,0664);  // UNIX protection
                                                // mode 0664
    if (outstrm.fail()) {
        cerr << "Failed to open badfile";
        exit(1);
    }
    OIOnihout out(outstrm);
    qlp->storeOn(out);
    lp->storeOn(out);
    outstrm.close();
    LandVhcl* t = LandVhcl::castdown((Object*)qlp);
    delete t;
    t = LandVhcl::castdown((Object*)lp);
    delete t;

    ifstream instrm("badfile");
    if (instrm.fail()) {
        cerr << "Failed to open badfile\n";
        exit(1);
    }
    OIOnihin in(instrm);
    qlp = QLink::readFrom(in);  // OK
    cout << *qlp << endl;
    lp = Link::readFrom(in);    // error: ambiguous downward cast
}
