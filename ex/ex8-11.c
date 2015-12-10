// ex8-11.c -- Test if date falls on a weekday

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex8-11.c,v 3.0 90/05/29 14:34:17 kgorlen Rel $

#include "Date.h"
#include "Set.h"
#include "String.h"

main ()
{
    Set weekdays;       // Set of weekday names
    String mon = "Monday", tue = "Tuesday", wed = "Wednesday",
        thu = "Thursday", fri = "Friday";
    weekdays.add(mon);  weekdays.add(tue);  weekdays.add(wed);
        weekdays.add(thu);  weekdays.add(fri);

    Date date;
    while (YES) {
        cout << "Enter date: ";  cin >> date;
        if (cin.eof()) break;
// Convert date to String containing name of day and
// search Set for match
        if (weekdays.includes(
            String(Date::nameOfDay(date.weekDay()))))
            cout << date << " is a weekday" << endl;
        else
            cout << date << " is not a weekday" << endl;
    }
    cout << endl;
}
