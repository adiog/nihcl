#ifndef	TIME_H
#define	TIME_H

/*$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/lib/RCS/Time.h,v 3.0 90/05/20 00:21:46 kgorlen Rel $*/

/* Time.h -- declarations for class Time

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	K. E. Gorlen
	Computer Systems Laboratory, DCRT
	National Institutes of Health
	Bethesda, MD 20892

$Log:	Time.h,v $
 * Revision 3.0  90/05/20  00:21:46  kgorlen
 * Release for 1st edition.
 * 
*/

#include "Object.h"

class Date;

#ifndef NESTED_TYPES
typedef unsigned short hourTy;
typedef unsigned short minuteTy;
typedef unsigned short secondTy;
typedef unsigned long clockTy;
#endif

class Time: public VIRTUAL Object {
	DECLARE_MEMBERS(Time);
public:			// type definitions
#ifdef NESTED_TYPES
	typedef unsigned short hourTy;
	typedef unsigned short minuteTy;
	typedef unsigned short secondTy;
	typedef unsigned long clockTy;
#endif
private:
	clockTy sec;			/* seconds since 1/1/1901 */
	bool isDST() const;
	Time localTime() const;
private:		// static member functions
	static Time localTime(const Date& date, hourTy h=0, minuteTy m=0, secondTy s=0);
	static Time beginDST(unsigned year);
	static Time endDST(unsigned year);
protected:		// storer() functions for object I/O
	virtual void storer(OIOofd&) const;
	virtual void storer(OIOout&) const;
public:
	Time();				// current time 
	Time(clockTy s)			{ sec = s; }
	Time(hourTy h, minuteTy m, secondTy s =0, bool dst =NO);
	Time(const Date&, hourTy h =0, minuteTy m =0, secondTy s=0, bool dst =NO);
	operator Date() const;
	bool operator<(const Time& t) const	{ return sec < t.sec; }
	bool operator<=(const Time& t) const	{ return sec <= t.sec; }
	bool operator>(const Time& t) const	{ return sec > t.sec; }
	bool operator>=(const Time& t) const	{ return sec >= t.sec; }
	bool operator==(const Time& t) const	{ return sec == t.sec; }
	bool operator!=(const Time& t) const	{ return sec != t.sec; }
	friend Time operator+(const Time& t, long s)	{ return Time(t.sec+s); }
	friend Time operator+(long s, const Time& t)	{ return Time(t.sec+s); }
	long operator-(const Time& t) const	{ return sec - t.sec; }
	Time operator-(long s) const	{ return Time(sec-s); }
	void operator+=(long s)		{ sec += s; }
	void operator-=(long s)		{ sec -= s; }
	bool between(const Time& a, const Time& b) const;
	hourTy hour() const;		// hour in local time 
	hourTy hourGMT() const;		// hour in GMT 
	minuteTy minute() const;	// minute in local time 
	minuteTy minuteGMT() const;	// minute in GMT 
	secondTy second() const;	// second in local time or GMT 
	clockTy	seconds() const		{ return sec; }
	Time max(const Time&) const;
	Time min(const Time&) const;
	virtual int compare(const Object&) const;
	virtual void deepenShallowCopy();	// {}
	virtual unsigned hash() const;
	virtual bool isEqual(const Object&) const;
	virtual void printOn(ostream& strm =cout) const;
	virtual const Class* species() const;
};

#endif /* TIMEH */
