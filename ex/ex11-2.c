// ex11-2.c -- Managing N resources with a Semaphore

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex11-2.c,v 3.0 90/05/15 22:44:23 kgorlen Rel $

#define BASE StackProc
#if BASE == StackProc
#include "StackProc.h"
#endif
#if BASE == HeapProc
#include "HeapProc.h"
#endif

#include "OrderedCltn.h"
#include "Scheduler.h"
#include "Semaphore.h"
#include "String.h"

class TestProcess : public BASE {
public:
    TestProcess(Semaphore*,OrderedCltn*,stackTy*);
    static TestProcess* create(Semaphore*,OrderedCltn*);
};

TestProcess::TestProcess(Semaphore* resourceAvailable,
                         OrderedCltn* resourceQ,
                         stackTy* bot)
            : BASE("TestProcess",bot,1)
{
    // parent process yields to allow this process to start
    if ( FORK() ) { Scheduler::yield(); return; }

    // obtain 2 resources
    Object* resource[2];
    int i;
    for (i=0; i<2; i++) {
        resourceAvailable->wait();
        resource[i] = resourceQ->remove(*resourceQ->first());
        cout << name() << ": obtained " 
             << *resource[i] << endl;
        }

    // release 2 resources
    for (i=0; i<2; i++) {
        resourceQ->addLast(*resource[i]);
        resourceAvailable->signal();
        cout << name() << ": released " 
             << *resource[i] << endl;
        }

    // terminate to avoid return
    terminate();
}

TestProcess* TestProcess::create(Semaphore* sem, OrderedCltn* cltn)
{
    // the next two statements must be in the same scope
    // for the address of the stack bottom to be correct
    auto stackTy bottom;
    return new TestProcess(sem,cltn,&bottom);
}

main()
{
    // start Scheduler
    // create main context with priority 0
    MAIN_PROCESS(0);

    // manage a resource queue of size = N
    const int N = 2;
    OrderedCltn* resourceQ = new OrderedCltn(N);
    Semaphore* resourceAvailable = new Semaphore(N);
    resourceQ->addLast(*new String("resource1"));
    resourceQ->addLast(*new String("resource2"));
    cout << "main: " << resourceQ->size() 
         << " resources available" << endl;

    // construct process to use resources
    TestProcess::create(resourceAvailable,resourceQ);

    do { // wait for resource to be returned
        resourceAvailable->wait();
        resourceAvailable->signal();
        cout << "main: " << resourceQ->size() 
             << " resources available" << endl;
       } while (resourceQ->size()<N);
}
