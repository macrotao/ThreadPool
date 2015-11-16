#include <assert>
#include "../include/Thread.h"

Thread::Thread()
    :m_tid(0),
{
}

Thread::Thread(const CALLBACK& callback) 
    :m_tid(0),
    m_callback(callback)
{
}

Thread::~Thread() {

}

void Thread::start() {
    pthread_create(&m_tid, NULL, threadFunc, this);
}

void Thread::join() {
    pthread_join(m_tid, NULL);
}

void* Thread::threadFunc(void* arg) {
    Thread *thread = static_cast<Thread*>(arg);
    assert(thread);
    assert(thread->m_callback);
    thread->m_callback();
}

#endif // _THREAD_H_
