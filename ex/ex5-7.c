// ex5-7.c -- Find dates of working days

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex5-7.c,v 3.0 90/05/15 22:45:32 kgorlen Rel $

#include "Date.h"
#include "String.h"

bool isHoliday(const Date& day)
{
    const unsigned NUMHOLIDAYS = 10;    
    int yr=day.year();
    Date holiday[NUMHOLIDAYS];

// Generate the holidays

// New Year's Day
    holiday[0] = Date(1,"Jan",yr);
// M.L. King's b'day - Third Mon, Jan.
    holiday[1] = (Date(21,"Jan",yr)).previous("Mon");
// Washington's b'day - Third Mon., Feb.
    holiday[2] = (Date(21,"Feb",yr)).previous("Mon");
// Memorial Day - Last Mon., May
    holiday[3] = (Date(31,"May",yr)).previous("Mon");
// Independence Day
    holiday[4] = Date(4,"July",yr);
// Labor Day - First Mon., Sept.
    holiday[5] = (Date(7,"Sept",yr)).previous("Mon");
// Columbus Day - Second Mon., Oct.
    holiday[6] = (Date(14,"Oct",yr)).previous("Mon");
// Veteran's Day
    holiday[7] = Date(11,"Nov",yr);
// Thanksgiving - Fourth Thurs., Nov.
    holiday[8] = (Date(28,"Nov",yr)).previous("Thur");
// Christmas
    holiday[9] = Date(25,"Dec",yr);

// See if day in question falls on a holiday

    register i;
    for (i = 0; i<=NUMHOLIDAYS-1; i++)
        if (day==holiday[i]) return YES;
    return NO;  
}

/*
Find the dates for every specified day-of-the-week (e.g., Wed)
after the specified date until the end of the year.
*/
main ()
{
    Date date, day;
    String day_of_week;

    cout << "Enter date:   ";
    cin >> date;
    cout << "Enter day of week:   ";
    cin >> day_of_week;
    day = (date+7).previous(day_of_week); // Exclude specified
                                          // date
    Date end_of_year(31,"Dec",date.year());
    while(day.between(date,end_of_year)) {
        if (!isHoliday(day)) cout << day << endl;
        day = day+7;
    }
}
