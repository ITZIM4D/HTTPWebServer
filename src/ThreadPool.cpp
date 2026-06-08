#include "ThreadPool.h"

ThreadPool::ThreadPool(int poolSize) {
    // Create requested number of threads (defaults to thread::hardware_concurrency()
    for (int i = 0; i < poolSize; i++) {
        threadPool.emplace_back(thread(&ThreadPool::ThreadLoop, this));
    }
}

void ThreadPool::threadLoop() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, []{
                return !jobs.empty() || should_terminate;
            });
            if (should_terminate) {
                return;
            }
            job = jobs.front();
            jobs.pop();
        }
        job();
    }
}

void ThreadPool::queueJob(const std::function<void()>& job) {
    {
    std::unique_lock<std::mutex> lock(queue_mutex);
    jobs.push(job);
    }
    mutex_condition.notify_one();
}
