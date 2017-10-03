
//
// Created by Александр on 29.9.2017
//

#ifdef _GTEST

#include "promise.h"
#include "future.h"

#include <thread>
#include <gtest/gtest.h>
//Promise
//#define A B --- Вместо B вписать название соответствующего метода в своем классе Promise
#define Set set
#define SetException setException
#define GetFuture getFuture
//Future

//#define A B --- Вместо B вписать название соответствующего метода в своем классе Future
#define IsReady isReady
#define Get get
#define Wait wait

TEST(promise, IsReady) {
    Promise<int> promise;
    Future<int> f = promise.GetFuture();

    ASSERT_FALSE(f.IsReady());

    int const x = 10;
    promise.Set(x);
    ASSERT_TRUE(f.IsReady());
}

TEST(promise, Set_int) {
    Promise<int> promise;
    Future<int> f = promise.GetFuture();

    int const x = 10;
    promise.Set(x);
    ASSERT_EQ(f.Get(), x);
}

TEST(promise, Set_int_ampersand) {
    Promise<int &> promise;
    Future<int &> f = promise.GetFuture();

    int const y = 100;
    int x = 10;

    promise.Set(x);

    f.Get() = y;

    ASSERT_EQ(x, y);
}

TEST(promise, Set_void) {
    Promise<void> promise;
    Future<void> f = promise.GetFuture();

    ASSERT_FALSE(f.IsReady());

    promise.Set();

    f.Get();

    ASSERT_TRUE(f.IsReady());
}

TEST(promise, two_threads_get_set) {
    Promise<int> promise;
    Future<int> future = promise.GetFuture();

    int x = 777;

    std::thread t(
            [x](Promise<int> promise) {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                promise.Set(x);
            }, std::move(promise)
    );

    for (int i = 0; !future.IsReady(); ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    ASSERT_EQ(future.Get(), x);

    t.join();
}

TEST(promise, SetAndGet) {

    Promise<int> p;
    Future<int> f = p.GetFuture();
    const int x = 100;

    [x](Promise<int> &p) {
        p.Set(x);
    }(p);

    ASSERT_EQ(f.Get(), x);
}

TEST(promise, Wait) {

    Promise<int> p;
    Future<int> f = p.GetFuture();
    const int x = 100;

    ASSERT_FALSE(f.IsReady());

    std::thread t([x](Promise<int> &p) {

        std::this_thread::sleep_for(std::chrono::seconds(2));
        p.Set(x);
    }, std::ref(p));
    f.Wait();

    ASSERT_TRUE(f.IsReady());
    t.join();
}

TEST(promise, SetException) {

    Promise<int> p;
    Future<int> f = p.GetFuture();
    const int x = 100;
    [](Promise<int> &p) {
        try {
            std::string().at(1);
        } catch (const std::exception &e) {
            p.SetException(std::current_exception());
        }
    }(p);
    ASSERT_ANY_THROW(f.Get());

}

TEST(promise, SetException2) {

    Promise<int> p;
    Future<int> f = p.GetFuture();
    [](Promise<int> &p) {
        try {
            std::string().at(1);
        } catch (const std::exception &e) {
            p.SetException(std::current_exception());
            ASSERT_ANY_THROW(p.SetException(std::current_exception()));
        }
    }(p);

}

TEST(promise, SetExceptionSet2) {

    Promise<int> p;
    Future<int> f = p.GetFuture();
    [](Promise<int> &p) {
        p.Set(7);
        ASSERT_ANY_THROW(p.Set(100));
    }(p);

}

TEST(promise, withThread) {

    Promise<std::string> p;
    Future<std::string> f = p.GetFuture();

    std::string s = "Hello, world";

    std::thread thread([s](Future<std::string> &future) {
        ASSERT_EQ(s, future.Get());
    }, std::ref(f));

    std::this_thread::sleep_for(std::chrono::seconds(2));
    p.Set(s);
    thread.join();

}

TEST(promise, withThread2) {

    Promise<std::string> p;
    Future<std::string> f = p.GetFuture();

    std::string s;

    std::thread thread([](Future<std::string> &future) {
        ASSERT_ANY_THROW(future.Get());
    }, std::ref(f));

    std::this_thread::sleep_for(std::chrono::seconds(2));
    try {
        s.at(1);
    } catch (...) {
        p.SetException(std::current_exception());
    }
    thread.join();

}

TEST(promise, SetIntAmper) {


    Promise<int &> dsa;
    Future<int &> f = dsa.GetFuture();

    int test = 10;
    dsa.Set(test);
    int &y = f.Get();

    y = 100;
    ASSERT_EQ(y, test);

}

#endif // _GTEST
