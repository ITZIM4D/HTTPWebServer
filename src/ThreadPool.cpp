#include "ThreadPool.h"

void ThreadPool::start() {
    int numThreads = std::thread::hardware_concurrency();
    for (int i = 0; i < numThreads; i++) {
        try {
            threads.emplace_back(std::thread(&ThreadPool::threadLoop, this));
        } catch (std::exception e) {
            std::cout << "Error creating thread " << e.what() << std::endl;
        }
    }
}

void ThreadPool::threadLoop() {
    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            mutexCondition.wait(lock, [this]{
                return !jobs.empty() || shouldTerminate;
            });
            if (shouldTerminate) {
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
    std::unique_lock<std::mutex> lock(queueMutex);
    jobs.push(job);
    }    
    mutexCondition.notify_one();    
}

bool ThreadPool::busy() {
    bool poolBusy;
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        poolBusy = !jobs.empty();
    }
    return poolBusy;
}

void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        shouldTerminate = true;
    }
    mutexCondition.notify_all();
    for (std::thread& active_thread : threads) {
        active_thread.join();
    }
    threads.clear();
}
