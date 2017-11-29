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
#include <iostream>
//#include "hw4/map.h"

class ThreadPool {
public :
    ThreadPool(size_t num_threads);
    static thread_local ThreadPool * thl;

    template<class F, class... Args>
    auto execute(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(mtx);


            tasks.emplace([task](){ (*task)(); });
        }
        cond.notify_one();
        return res;
    }


    template<class F>
    void Parallel(auto start, auto finish, const F& func){
        for (; start  != finish; start++)
        {
            auto sd = (execute(func, *(start)));
            (*start) = sd.get();
        }

    }


    ~ThreadPool();

private:

    std::queue<std::function<void()> > tasks;
    std::vector<std::thread> threads;
    std::atomic<bool> enable;
    std::mutex mtx;
    std::condition_variable cond;


};


#endif //HOMEWORKCPPSEM3_THREADPOOL_H
