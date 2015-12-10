// ex11-3.c -- Protecting a critical section of code
//             with an AutoSignal

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex11-3.c,v 3.0 90/05/15 22:44:25 kgorlen Rel $

#define BASE StackProc
#if BASE == StackProc
#include "StackProc.h"
#endif
#if BASE == HeapProc
#include "HeapProc.h"
#endif

#include "Scheduler.h"
#include "Semaphore.h"
#include "String.h"

static Semaphore protect_critical(1);

class AutoSignal {
    Semaphore* as;
public:
    AutoSignal(Semaphore& s) { as= &s; as->wait(); }
    ~AutoSignal() { as->signal(); }
};

class TestProcess : public BASE {
public:
    TestProcess(const char* name, stackTy* bot, int pri);
    static TestProcess* create(const char* name, int pri);
};

TestProcess::TestProcess(const char* pname,stackTy* bot,int pri)
            : BASE(pname,bot,pri)
{
    // parent process yields to allow this process to start
    if ( FORK() ) { Scheduler::yield(); return; }

    while (1) {
        // this block represents a critical section
        // although it does nothing critical
        AutoSignal autosig(protect_critical);
        cout << name() << pri << " enter critical section" << endl;
        break;
        }

    // terminate to avoid return
    terminate();
}

TestProcess* TestProcess::create(const char* name, int pri)
{
    // the next two statements must be in the same scope
    // for the address of the stack bottom to be correct
    auto stackTy bottom;
    return new TestProcess(name,&bottom,pri);
}

main()
{
    // start Scheduler
    // create main context with priority 0
    MAIN_PROCESS(0);

    String* pname = new String("P"); 
    for (register int i=MAXPRIORITY; i>=1; i--)
        TestProcess::create(*pname,i);

    cout << "main Process" << endl;
}
