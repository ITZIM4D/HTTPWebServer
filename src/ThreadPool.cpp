#include "ThreadPool.h"

ThreadPool::ThreadPool(int poolSize) {
    // Create requested number of threads (defaults to thread::hardware_concurrency()
    for (int i = 0; i < poolSize; i++) {
        threadPool.emplace_back(thread(&ThreadPool::ThreadLoop, this));
    }

}

