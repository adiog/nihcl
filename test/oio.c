/* Test Object I/O

	THIS SOFTWARE FITS THE DESCRIPTION IN THE U.S. COPYRIGHT ACT OF A
	"UNITED STATES GOVERNMENT WORK".  IT WAS WRITTEN AS A PART OF THE
	AUTHOR'S OFFICIAL DUTIES AS A GOVERNMENT EMPLOYEE.  THIS MEANS IT
	CANNOT BE COPYRIGHTED.  THIS SOFTWARE IS FREELY AVAILABLE TO THE
	PUBLIC FOR USE WITHOUT A COPYRIGHT NOTICE, AND THERE ARE NO
	RESTRICTIONS ON ITS USE, NOW OR SUBSEQUENTLY.

Author:
	K. E. Gorlen
	Bg. 12A, Rm. 2033
	Computer Systems Laboratory
	Division of Computer Research and Technology
	National Institutes of Health
	Bethesda, Maryland 20892
	Phone: (301) 496-1111
	uucp: uunet!nih-csl!kgorlen
	Internet:kgorlen@alw.nih.gov

Function:
	
Modification History:
	
$Log:	oio.c,v $
 * Revision 3.0  90/05/20  00:29:29  kgorlen
 * Release for 1st edition.
 * 
*/
static char rcsid[] = "$Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/test/RCS/oio.c,v 3.0 90/05/20 00:29:29 kgorlen Rel $";

#include <osfcn.h>
#include "nihclconfig.h"
#include "ArrayOb.h"
#include "Arraychar.h"
#include "Assoc.h"
#include "Bag.h"
#include "Bitset.h"
#include "Date.h"
#include "Dictionary.h"
#include "FDSet.h"
#include "Float.h"
#include "Fraction.h"
#include "Heap.h"
#include "LinkedList.h"
#include "LinkOb.h"
#include "OrderedCltn.h"
#include "Point.h"
#include "Range.h"
#include "Rectangle.h"
#include "Set.h"
#include "SortedCltn.h"
#include "Stack.h"
#include "String.h"
#include "Time.h"
#include "OIOnih.h"
#include "OIOfd.h"

Object* testStore()
{
	ArrayOb& arrayob = *new ArrayOb(4);
	Arraychar& arraychar = *new Arraychar(26);
	Bag& bag = *new Bag(100);
	Bitset& bitset = *new Bitset(4,6);
	Date& date = *new Date(11,"Nov",48);
	Dictionary& dict = *new Dictionary(100);
	FDSet& fdset = *new FDSet(); fdset[0] = fdset[1] = fdset[19] = 1;
	Float& flt = *new Float(3.1415);
	Fraction& fract = *new Fraction(22,7);
	Heap& heap = *new Heap;
	LinkedList& linkedlist = *new LinkedList;
	OrderedCltn& orderedcltn = *new OrderedCltn;
	Point& point = *new Point(1,2);
	Range& range = *new Range(-1,1);
	Rectangle& rect = *new Rectangle(0,1,2,3);
	Set& set = *new Set(100);
	SortedCltn& sortedcltn = *new SortedCltn;
	Stack& stack = *new Stack;
	String& str = *new String("123456789a123456789b123456789c123456789d123456789e123456789f123456789g12345678\012h Hello, world!\t{\033\"\\}");
	Time& time = *new Time(date,1,2,3);
	
	arrayob[0] = &bitset; arrayob[1] = &point; arrayob[2] = &str;
	for (int i = 0; i < 26; i++) arraychar[i] = "abcdefghijklmnopqrstuvwxyz"[i];
	orderedcltn.add(point); orderedcltn.add(rect); orderedcltn.add(str);
	orderedcltn.add(flt); orderedcltn.add(fract); orderedcltn.add(range);
	orderedcltn.add(date); orderedcltn.add(time); orderedcltn.add(fdset);
	stack.push(bitset); stack.push(orderedcltn);
	bag.addWithOccurrences(point,1);
	bag.addWithOccurrences(rect,2);
	bag.addWithOccurrences(str,3);
	bag.add(orderedcltn);
	sortedcltn.add(*new String("Huey"));
	sortedcltn.add(*new String("Dewey"));
	sortedcltn.add(*new String("Louie"));
	heap.add(*new String("Dasher"));
	heap.add(*new String("Dancer"));
	heap.add(*new String("Prancer"));
	heap.add(*new String("Vixen"));
	heap.add(*new String("Comet"));
	heap.add(*new String("Cupid"));
	heap.add(*new String("Donder"));
	heap.add(*new String("Blitzen"));
	dict.add(*new Assoc(orderedcltn,point));
	dict.add(*new Assoc(bag,rect));
	dict.add(*new Assoc(sortedcltn,stack));
	linkedlist.add(*new LinkOb(point));
	linkedlist.add(*new LinkOb(rect));
	linkedlist.add(*new LinkOb(bitset));
	linkedlist.add(*new LinkOb(str));
	
	set.add(arrayob);
	set.add(arraychar);
	set.add(bag);
	set.add(dict);
	set.add(heap);
	set.add(linkedlist);
	set.add(orderedcltn);
	set.add(sortedcltn);
	set.add(stack);
	
	OrderedCltn& monster = *new OrderedCltn;
	monster.add(set); monster.add(*set.deepCopy());
	return &monster;
}

#include <fcntl.h>
#include <osfcn.h>

#ifndef BSD

const char* optarg;
int optind = 1;
static char* optchar = "?";

int getopt(int /*argc*/, const char** argv, const char* optstr) {
  int optlen = strlen(optstr);
  int inx;

  if ( argv[optind]==0 || strlen(argv[optind]) < 2 || *argv[optind] != '-' ) { /* not a switch */
     return EOF; 
     };
   *optchar = argv[optind][1];
     
//  inx = strcspn(optstr,optchar);
  for(inx=0; inx<= strlen(optstr); inx++)
    if ( optstr[inx] == *optchar ) break;
     
  if ( inx == optlen ) {			/* illegal switch */
    ++optind;
    fprintf(stderr,"getopt> illegal switch\n");
    return '?';
    };

  if ( (inx+1 <= optlen-1) && (optstr[inx+1] == ':') ) {/*switch has argument*/
    if (strlen(argv[optind]) == 2)
      optarg = argv[++optind];	       /* optarg is next argv */
    else 
      optarg = &argv[optind][2];	       /* optarg in this argv */
    };
  ++optind;
    return *optchar;
}

#endif

main(int argc, char** argv)
{
	extern int optind;		// used by getopt()
	extern char* optarg;		// used by getopt()
	char* filea = "oio.obj";
	char* fileb;
	bool binaryIO = NO;	// test binary storeOn/readFrom flag
	bool dumpOpt = NO;	// dump read object on cout
	bool filebOpt = NO;	// file to store object read specified

// parse command options	

	int c;
	while ((c = getopt (argc, argv, "bd")) != EOF)
		switch	(c) {
			case 'b': binaryIO = YES; break;
			case 'd': dumpOpt = YES; break;
			case '?':
				cerr << "usage: [ -bd ] [ filea [ fileb ] ]\n ";
				exit(2);
		}
	if (optind < argc) filea = argv[optind++];
	if (optind < argc) {
		fileb = argv[optind++];
		filebOpt = YES;
	}
				
	Object* a = testStore();
	Object* b;
	
	if (binaryIO) {
		cout << "Test storeOn(OIOofd&)" << endl;
		int fd = creat(filea,0664);
		a->storeOn(OIOofd(fd));
		close(fd);
		cout << "Test readFrom(OIOifd&)" << endl;
		fd = open(filea,O_RDONLY);
		b = Object::readFrom(OIOifd(fd));
		close(fd);
	}
	else {
		cout << "Test storeOn(OIOout&)" << endl;
		ostream* out = new ostream(creat(filea,0664));
		a->storeOn(OIOnihout(*out));
		delete out;
		cout << "Test readFrom(OIOin&)" << endl;
		istream* in = new istream(open(filea,O_RDONLY));
		b = Object::readFrom(OIOnihin(*in));
		delete in;
	}

	
// compare object stored with object read	
	
	if (a->isEqual(*b)) {
		cout << "SUCCESS! -- stored object equals object read" << endl;
		if (dumpOpt) {
			b->dumpOn(cout);
			cout << endl;
		}
	}
	else {
		cout << "FAILURE! -- stored object does not equal object read" << endl;
		cout << "*** object stored:" << endl;  a->dumpOn(cout);  cout << endl;
		cout << "*** object read:" << endl;  b->dumpOn(cout);  cout << endl;
	}
	
// store object read	

	if (filebOpt) {
		if (binaryIO) {
			int fd =creat(fileb,0664);
			b->storeOn(OIOofd(fd));
			close(fd);
		}
		else {
			ostream out(creat(fileb,0664));
			b->storeOn(OIOnihout(out));
		}
	}
}

