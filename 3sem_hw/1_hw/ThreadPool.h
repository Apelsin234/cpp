//
// Created by Александр on 13.09.2017.
//

#ifndef HOMEWORKCPPSEM3_THREADPOOL_H
#define HOMEWORKCPPSEM3_THREADPOOL_H


#include <functional>
#include <vector>
#include <queue>
#include <memory>
#include <future>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadPool {
public :
    ThreadPool(size_t num_threads);

    void execute(std::function<void()> foo);

    ~ThreadPool();

private:

    std::queue<std::function<void()> > tasks;
    std::vector<std::thread> threads;
    std::atomic<bool> enable;
    std::mutex mtx;
    std::condition_variable cond;


};


#endif //HOMEWORKCPPSEM3_THREADPOOL_H
