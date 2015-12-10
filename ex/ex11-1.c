// ex11-1.c -- Scheduling lightweight processes in
//             the NIH class library

// $Header: /afs/alw.nih.gov/unix/sun4_40c/usr/local/src/nihcl-3.0/share/ex/RCS/ex11-1.c,v 3.0 90/05/15 22:44:19 kgorlen Rel $

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

class TestProcess : public BASE {
public:
    TestProcess(const char* name, stackTy* bot, int pri,
                Process* parent);
    static TestProcess* create(const char* name, int pri,
                               Process* parent);
};

TestProcess::TestProcess(const char* pname,stackTy* bot,int pri,
                         Process* parent)
            : BASE(pname,bot,pri)
{
    // parent process yields to allow this process to start
    if ( FORK() ) { Scheduler::yield(); return; }

    cout << name() << pri << " start" << endl;

    // yield to parent process
    if (parent) {
        parent->resume();
        Scheduler::yield();
        }
    // suspend until child yields
    suspend();
    Scheduler::schedule();

    cout << name() << pri << " resume" << endl;

    // terminate to avoid return
    terminate();
}

TestProcess* TestProcess::create(const char* name, int pri,
                                 Process* parent)
{
    // the next two statements must be in the same scope
    // for the address of the stack bottom to be correct
    auto stackTy bottom;
    return new TestProcess(name,&bottom,pri,parent);
}

main()
{
    // start Scheduler
    // create main context with priority 0
    MAIN_PROCESS(0);

    Process* parent =0;
    String* pname = new String("P"); 
    for (register int i=MAXPRIORITY; i>=1; i--)
        parent = TestProcess::create(*pname,i,parent);

    cout << "main Process" << endl;
    parent->resume();
    Scheduler::yield();
}
