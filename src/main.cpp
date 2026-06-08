#include <iostream>
#include "ThreadPool.h"

int main () {
    ThreadPool threadPool;
    threadPool.start();
    int num = 0;

    while (num < 100) {
        threadPool.queueJob([&]{
            num++;
            std::cout << num << std::endl;
        });
    }
    

    threadPool.stop();
    return 0;
}


