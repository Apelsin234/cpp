//
// Created by Александр on 02.11.2017.
//

#include <iostream>
#include "ThreadPool.h"
#include "promise.h"
#include "future.h"

template<typename T, typename F>
Future<typename std::result_of<F(T)>::type> Map(Future<T> futa, const F & func) {
	using K = typename std::result_of<F(T)>::type;
    ThreadPool * curPool = nullptr;
    if(futa.getPool()) {
        curPool = futa.getPool();
    } else if(ThreadPool::thl) {
        curPool = ThreadPool::thl;
    }
	std::shared_ptr<Promise<K>> p = std::shared_ptr<Promise<K>>(new Promise<K>());

    if(curPool) {
        curPool -> execute([&futa, &func, p] {
            p->set(std::move(func(futa.get())));

        });
    } else {
        std::thread([&futa, &func, p](){
            p->set(std::move(func(futa.get())));
        }).detach();
    }
	return std::move(p->getFuture());
}

