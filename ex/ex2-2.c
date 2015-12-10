/* ex2-2.c -- Add multiple-precision integers using mp library */

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex2-2.c,v 3.0 90/05/15 22:45:02 kgorlen Rel $*/

#include <mp.h>

MINT* dtom(d)
char *d;
{
    MINT *t, *ten;
    t = itom(0);
    ten = itom(10);
    while (*d) {
        MINT *u;
        u = itom(*d++ - '0');
        mult(t,ten,t);
        madd(t,u,t);
        mfree(u);
    }
    mfree(ten);
    return t;
}

main()
{
    MINT *a, *b, *c, *t;
    a = dtom("25123654789456");
    b = dtom("456023398798362");
    c = itom(0);
    t = itom(47);
    madd(a,b,c);
    madd(c,t,c);
    mout(c);
    printf("\n");
    mfree(a); mfree(b); mfree(c); mfree(t);
}
