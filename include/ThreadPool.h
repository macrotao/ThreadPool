#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <functional>
#include <vector>

#include "NonCopyable.h"
#include "Thread.h"

class Thread;
class ThreadPool : private NonCopyable {
public:
    typedef std::function<void (int)> Task;
    ThreadPool(size_t queueSize, size_t poolSize);
    ~ThradPool();
    void start();
    void stop();
    void addTask(const Task &task);

private:
    void run(int runNum);

private:
    bool m_isStarted;
    size_t m_queueSize;
    size_t m_poolSize;
    std::vector<std::queue_ptr<Thread> > m_threads;
    std::queue<Task>* m_queue;

};
#endif // _THREADPOOL_H_
