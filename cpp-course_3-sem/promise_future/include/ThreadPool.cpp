//
// Created by Александр on 13.09.2017.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t num_thread) : enable(true) {
    for (size_t i = 0; i < num_thread; i++) {
        threads.emplace_back([this]() {
            thl = this;
            while (true) {

                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cond.wait(lock, [this]() {
                        return !tasks.empty() || !enable;
                    });
                    if (!enable && tasks.empty()) return;
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}




ThreadPool::~ThreadPool() {

    {
        enable = false;
        std::unique_lock<std::mutex> lock(mtx);
    }
    cond.notify_all();

    for (auto &th: threads) {
        th.join();
    }
}


thread_local ThreadPool * ThreadPool::thl= nullptr;