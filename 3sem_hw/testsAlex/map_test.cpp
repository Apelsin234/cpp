//
// Created by eugene on 11.10.2017
//
#ifdef _GTEST

#include "hw4/map.h"


#include <iostream>
#include <gtest/gtest.h>



TEST(m1, test1) {
    ThreadPool pool(4);
    Promise<int> p;
    p.setPool(&pool);
    pool.execute([&p](){
        p.set(0);
    });
    Future<long> futa = Map(std::move(p.getFuture()), [](int ii){
        return (long)(ii+1);
    });
    ASSERT_EQ(futa.get(), 1);
}

TEST(m1, test2) {
    ThreadPool pool(4);
    Promise<int> p;
    p.set(0);
    Future<long> futa = Map(std::move(p.getFuture()), [](int ii){
        return (long)(ii+1);
    });
    ASSERT_EQ(futa.get(), 1);
}

TEST(m1, test3) {
    ThreadPool pool(10);
    std::shared_ptr<Promise<int>> p(new Promise<int>());
    p->set(0);
    pool.execute([p]{
        Future<long> futa = Map(std::move(p->getFuture()), [](int ii){
            return (long)(ii+1);
        });
        ASSERT_EQ(futa.get(), 1);
    });
    //std::this_thread::sleep_for(std::chrono::seconds(1));
}


TEST(m1, test4) {
    int32_t const cnt_threads = 10;
    //ThreadPool::init();
    ThreadPool pool(cnt_threads);
    Promise<std::vector<int>> p;
    p.setPool(&pool);
    pool.execute([&p](){
        std::vector<int> v = {11, 9, 2001};
        p.set(v);
    });
    Future<int> futa = Map(std::move(p.getFuture()), [](std::vector<int> vv){
        int elmao = 0;
        for(int & ii : vv) {
            elmao += ii;
        }
        return elmao;
    });
    ASSERT_EQ(futa.get(), 2021);
}
TEST(m1, test5) {
    Promise<int> p;
    p.set(0);
    Future<long> futa = Map(std::move(p.getFuture()), [](int ii){
        return (long)(ii+1);
    });
    ASSERT_EQ(futa.get(), 1);
}


#endif // _GTEST