#include "thread.h"
#include "defin.h"
#include "timer.h"
#include "pcb.h"

Thread::Thread(StackSize stackSize, Time timeSlice){
    if(stackSize > maxStackSize) stackSize = maxStackSize;
    HARD_LOCK
    myPCB = new PCB(this, stackSize, timeSlice);
    HARD_UNLOCK
}

Thread::~Thread(){
    waitToComplete();
    HARD_LOCK
    delete myPCB;
    HARD_UNLOCK
}

void Thread::start(){
    myPCB->reschedule();
}

void Thread::waitToComplete(){
    myPCB->waitToComplete();
}

ID Thread::getID() {
    return myPCB->getID();
}

ID Thread::getRunningId(){
    return Timer::runningPCB->getID();
}

Thread *Thread::getThreadById(ID id){
    return PCB::getThreadById(id);
}

void dispatch(){
    HARD_LOCK
    Timer::req = 1;
    Timer::timerInt();
    HARD_UNLOCK
}
