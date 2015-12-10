// ex9-4.c -- Virtual inline function calls

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex9-4.c,v 3.0 90/05/15 22:46:38 kgorlen Rel $

class X {
    int n;
public:
    X(int i=0)          { n = i; }
    virtual void inc()  { n++; }
};

main()
{
    X x;
    X* xp = new X;
// virtual function with scope resolution applied
// to class instance
    x.X::inc();
// virtual function with scope resolution applied
// through pointer to class instance
    xp->X::inc();
// virtual function applied to class instance
    x.inc();
// virtual function applied through pointer to class instance
    xp->inc();
}
