#ifndef _THREAD_H_
#define _THREAD_H_

#include <functional>
#include <pthread.h>

// 基于对象的封装方式
class Thread : private NonCopyable {
public:
    typedef std::function<void ()> CALLBACK;

    Thread();
    explicit Thread(const CALLBACK& callback);
    ~Thread();

    void start();
    void join();

private:
    static void* threadFunc(void*); // 用static保证参数不是this指针

private:
    pthread_t m_tid;
    CALLBACK m_callbak
};

#endif // _THREAD_H_
