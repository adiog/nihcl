// ex7-2.c -- Improved geometry class hierarchy
//            using NIH class library

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex7-2.c,v 3.0 90/05/15 22:45:50 kgorlen Rel $

#include <fstream.h>
#include <osfcn.h>
#include "Point.h"
#include "Line.h"
#include "Circle.h"
#include "Picture.h"
#include "OIOnih.h"

main()
{
    Line l(Point(1,2),Point(3,4));
    Circle c(Point(5,6),1);
    Picture subPic;
    subPic.add(l);
    subPic.add(c);

    Picture bigPic;
    bigPic.add(*(Shape*)subPic.shallowCopy());
    bigPic.add(*(Shape*)subPic.deepCopy());
    bigPic.add(l);
    cout << "\n* Original bigPic:\n";
    bigPic.draw();

    subPic.move(Point(10,10));
    cout << "\n* After moving subPic:\n";
    bigPic.draw();

    l.move(Point(10,10));
    c.move(Point(10,10));
    cout << "\n* After moving l and c:\n";
    bigPic.draw();

    ofstream out("picturefile",ios::out,0664);
                      // UNIX protection mode 0664
    if (out.fail()) {
        cerr << "Failed to open picturefile\n";
        exit(1);
    }
    bigPic.storeOn(OIOnihout(out));
}
