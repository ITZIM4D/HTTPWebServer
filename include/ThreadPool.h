/**
 * @file ThreadPool.h
 *
 * @brief A pool of threads constantly running and taking open jobs
 */

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <iostream>

using std::thread;

/**
 * @class ThreadPool
 *
 * @brief A thread pool that will allocate threads to tasks
 */
class ThreadPool {
    public:
        /**
         * @brief Creates the threads and starts the threadpool loop
         */
        void start();
        
        /**
         * @brief Queues up a job for one of the threads to take
         *
         * @param[in] job The job that is being queued up
         */
        void queueJob(const std::function<void()>& job);
        
        /**
         * @brief Stops the Threadpool and joins the threads
         */
        void stop();

        /**
         * @brief Checks and returns if there is a job running or not
         *
         * @return True if there is a job in the queue and False if not 
         */
        bool busy();

    private:
        bool shouldTerminate = false; 
        std::mutex queueMutex; /// Mutex that all the threads refer to 
        std::condition_variable mutexCondition; /// Wake condition for threads  
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> jobs;

        /**
         * @brief Loop that threads run through and check/wait for a job to open up
         */
        void threadLoop();
};

#endif
