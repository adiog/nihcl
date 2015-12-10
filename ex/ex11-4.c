// ex11-4.c -- Communication between lightweight processes
//             with a SharedQueue

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex11-4.c,v 3.0 90/05/15 22:44:27 kgorlen Rel $

#define BASE StackProc
#if BASE == StackProc
#include "StackProc.h"
#endif
#if BASE == HeapProc
#include "HeapProc.h"
#endif
#include "SharedQueue.h"
#include "Scheduler.h"
#include "String.h"

class TestProcess : public BASE {
public:
    TestProcess(const char* name, int pri, 
                SharedQueue& in, SharedQueue& out,
                stackTy* bot);
    static TestProcess* create(const char* name, int pri, 
                SharedQueue& in, SharedQueue& out);
};

TestProcess::TestProcess(const char* pname, int pri, 
                         SharedQueue& in, SharedQueue& out,
                         stackTy* bot) : 
                         BASE(pname,bot,pri)
{
    // parent lwp yields so this lwp can start
    if ( FORK() ) { Scheduler::yield(); return; }

    while (YES) {
        Object* msg = in.next();
        cout << className() << ": " << name() 
             << " received " << *msg << endl;
        out.nextPut(*msg);
        cout << className() << ": " << name() 
             << " sent " << *msg << endl;
        }
    // terminate to avoid return
    terminate();
}
TestProcess* TestProcess::create(const char* pname, int pri, 
                                 SharedQueue& in, SharedQueue& out)
{
    auto stackTy bottom;
    return new TestProcess(pname, pri, in, out, &bottom);
}
main()
{
    // construct Scheduler
    // and create main context with priority 0
    MAIN_PROCESS(0);

    SharedQueue* q0 = new SharedQueue(2);
    SharedQueue* qin = q0;
    SharedQueue* qout;

    // start up lightweight processes coupled by SharedQueues: 
    // qout for kTH Process is qin for (k+1)TH Process
    for (register int i=1; i<=MAXPRIORITY; i++) {
        String* pname = new String("P");
        *pname &= (char)('0'+i);
        qout = new SharedQueue(2);
        TestProcess::create(*pname, i, *qin, *qout);
        qin = qout;
        }

    // put a message on the first input SharedQueue
    String& inmsg = *new String("THE MESSAGE");
    cout << "process Main sending: " << inmsg << endl;
    q0->nextPut(inmsg);
    
    // main Process waits for message on last output SharedQueue
    String& outmsg = *(String*)qout->next();
    cout << "process Main received: " << outmsg << endl;
}
