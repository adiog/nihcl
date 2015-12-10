// ex5-6.c -- String substitution

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-6.c,v 3.0 90/05/29 14:34:15 kgorlen Rel $

#include "ExString.h"

String replace(const String& target,
                const String& oldss,
                const String& newss)
{
    if (oldss.length() == 0) return target;     // if old is empty
    String result(target.capacity());
    unsigned i=0;       // start position for
                        // next substring comparison
    unsigned j=0;       // start position of
                        // last unmatched substring
    while (i+oldss.length() <= target.length()) {
        if (target(i,oldss.length()) == oldss) {
            result &= target(j,i-j) & newss;
            j = i += oldss.length();
        }
        else i++;
    }
    if (j != target.length())
        result &= target(j,target.length()-j);
    return result;
}

main()
{
    String orig, substr, replacement;
    while (1) {
        cout << "Enter target string: ";  cin >> orig;
        if (cin.eof()) break;
        cout << "    Replace: ";  cin >> substr;
        cout << "    With: ";  cin >> replacement;
        cout << "    replace(" << orig << ',' << substr << ','
             << replacement << ") = ";
        cout << replace(orig, substr, replacement) << endl;
    }
    cout << endl;
}
