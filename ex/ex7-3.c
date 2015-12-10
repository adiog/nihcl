// ex7-3.c -- Object I/O readFrom()

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex7-3.c,v 3.0 90/05/15 22:45:52 kgorlen Rel $

#include <fstream.h>
#include <osfcn.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Picture.h"
#include "OIOnih.h"

main()
{
    ifstream in("picturefile");
    if (in.fail()) {
        cerr << "Failed to open picturefile\n";
        exit(1);
    }
    Picture* bigPic = Picture::readFrom(OIOnihin(in));
    bigPic->draw();
}
