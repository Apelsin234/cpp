//
// Created by Александр on 23.11.2017.
#include "hw4/map.h"

auto Parallel(auto start, auto finish, auto func){
    std::vector<Future<int>> wait;
    std::mutex mtx;
    std::unique_lock<std::mutex> lock(mtx);
    ThreadPool *curpool = ThreadPool::thl;
    for (; start != finish; start++) {
        wait.push_back(curpool->execute(Map(*start, func)));

    }

    for(auto &i: wait){
        i.wait();
    }
}

