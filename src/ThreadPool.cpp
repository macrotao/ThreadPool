
#include <functional>
#include <vector>

#include "../include/NonCopyable.h"
#include "../include/Thread.h"
#include "../include/ThreadPool.h"


ThreadPool::ThreadPool(size_t queueSize, size_t poolSize)
    : m_isStarted(false),
    m_queueSize(queueSize),
    m_poolSize(poolSize)
{
    m_queue = new std::queue<Task>();

}
ThreadPool::~ThradPool() {
    if (m_queue) {
        delete m_queue;
        m_queue = NULL;
    }
}

void ThreadPool::start() {
    for (size_t i = 0; i < m_poolSize; ++i) {
        // this，调用者；i，函数参数，并固定
        m_threads.push_back(std::unique_ptr<Thread>(new Thread(bind(run, this, i))));
    }

    for (size_t i = 0; i < m_poolSize; ++i)
        m_threads[i]->start();
}

void ThreadPool::stop() {
    if (! m_isStarted) {
        return;
    }

    m_isStarted = false;

    for (size_t i = 0; i != m_poolSize; ++i) {
        m_threads[i]->join();
    }

    while (! m_queue->empty()) {
        m_queue->pop();
    }

    m_threads.clear();
}

// callback function of a thread
void ThreadPool::run(int runNum) {
    while (m_isStarted) {
        Task task(getTask());
        if (task) {
            task(runNum);
        }
    }
}

void ThreadPool::addTask(const Task &task) {
    while (m_isStarted && m_queue->size() >= m_queueSize) {
        // waiting...
    }

    m_queue->push(task);
}

Task ThreadPool::getTask() {
    while (m_isStarted && m_queue->empty())
}
