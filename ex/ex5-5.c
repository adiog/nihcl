// ex5-5 -- Opening a stream for a file

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-5.c,v 3.0 90/05/15 22:45:27 kgorlen Rel $

#include <fcntl.h>
#include <osfcn.h>
#include <libc.h>
#include <fstream.h>

const char* fname = "ex5-5.1.out";
const char* fdname = "ex5-5.2.out";

main() 
{
    // open ofstream attached to
    // file on default directory
    ofstream ostrm(fname,ios::out|ios::nocreate);

    //  since ios::nocreate is set
    // construction fails when file doesn't already exist
    if ( !ostrm.good() ) {
        perror("ofstream");
        exit(1);
        }
    ostrm << "output to ofstream attached to named file" 
          << endl;

    // old-style open to get open file descriptor
    int fd;
    if ( (fd=open(fdname,O_WRONLY,0644)) <0 ) {
        perror("open");
        exit(1);
        }

    // close ofstream and 
    // reattach to open file descriptor
    ostrm.close();
    ostrm.attach(fd);
    ostrm << "output to ofstream reattached"
          << " to open file descriptor"
          << endl;
}
