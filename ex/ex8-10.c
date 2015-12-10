// ex8-10.c --  Linking into a LinkedList

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-10.c,v 3.0 90/05/15 22:45:55 kgorlen Rel $

#include "LinkOb.h"
#include "LinkedList.h"
#include "String.h"

main()
{
    LinkedList list;

// Add new first link
    LinkOb* firstLink = new LinkOb(*new String("first in"));
    list.addFirst(*firstLink);

// Add new last link
    LinkOb* lastLink = new LinkOb(*new String("second in"));
    list.addLast(*lastLink);
    
// Insert new link in between first and last
    LinkOb* newlink = new LinkOb(*new String("third in"));
    list.addAfter(*firstLink,*newlink);

// Print the LinkedList of LinkObs
    if (list.size() > 0) {
        LinkOb* link = (LinkOb*)list.first();
        while (!link->isListEnd()) {
            cout << *link << endl;
            link = (LinkOb*)link->nextLink();
        }
    }
}
