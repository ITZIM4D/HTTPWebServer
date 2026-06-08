#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <iostream>

using std::thread;

/**
 * @brief A thread pool that will allocate threads to tasks
 */
class ThreadPool {
    public:
        void start();
        void queueJob(const std::function<void()>& job);
        void stop();
        bool busy();

    private:
        bool shouldTerminate = false; 
        std::mutex queueMutex;
        std::condition_variable mutexCondition; 
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> jobs;

        void threadLoop();
};

#endif
