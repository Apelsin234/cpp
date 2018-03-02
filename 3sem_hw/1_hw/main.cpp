#include <iostream>
#include <functional>
#include <vector>
#include <thread>
#include <future>
#include "async/Promise.h"
#include "ThreadPool.h"

struct A {
    A(int &xx) {
        x = &xx;
    }

    int *x;
};


int main() {
    int xxx = 5;
    A x(xxx);
    *x.x = 10;
    // std::cout << xxx;

    // Test for ThreadPool
    /*    std::mutex mtx;
    ThreadPool threadPool(3);
    int a,bl;
    for (size_t i = 0; i < 20; i++) {
        threadPool.execute([i, &mtx]()->void {
            mtx.lock();
            std::cout << "QWER" << i << std::endl;
            mtx.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            mtx.lock();
            std::cout << "YUI" << i << std::endl;
            mtx.unlock();
        });
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Test for Future and Promise
    std::vector<std::function<void(Promise<int> &)> > v = {
            //1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
            [](Promise<int> &p) {
                p.set(100);
            },
            //2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
            [](Promise<int> &p) {
                try {
                    std::string().at(1);
                } catch (...) {
                    p.setException(std::current_exception());
                }
            },
            //3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
            [](Promise<int> &p) {
                try {
                    std::string().at(1);
                } catch (...) {
                    p.setException(std::current_exception());
                    p.setException(std::current_exception());
                }
            },
            //4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
            [](Promise<int> &p) {
                try {
                    int y = 1000;
                    p.set(std::move(y));
                    p.set(50);

                } catch (...) {
                    p.setException(std::current_exception());\

                }
            }


    };

    int t = 1;

    for (auto &i: v) {

        std::cout << "Test " << t++ << " - int.\n";
        try {
            Promise<int> p;
            Future<int> f = p.getFuture();
            i(p);

            std::cout << "Return: " << f.get() << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Return: " << e.what() << std::endl;
        }

        std::cout << std::endl;
    }
    ////////////////////////////////////////////////////////////////////////
    {
        std::cout << "Test " << t++ << " - void.\n";
        try {
            Promise<void> p;
            Future<void> f = p.getFuture();
            [](Promise<void> &p) {
                int k = 5;
                p.set();
            }(p);

            f.get();
        } catch (const std::exception &e) {
            std::cout << "Return: " << e.what() << std::endl;
        }

        std::cout << std::endl;
    }
    ////////////////////////////////////////////////////////////////////////
    {
        std::cout << "Test " << t++ << " - string." << std::endl;

        Promise<std::string> p1;
        Future<std::string> f = p1.getFuture();
        Promise<std::string> p(std::move(p1));

        std::thread thread([](Future<std::string> &future) {
            std::cout << "Return: " << future.get() << std::endl;
        }, std::ref(f));

        std::cout << "\n\\\\\\\\\\\\Wait 2 seconds\\\\\\\\\\\\\n\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        p.set("Hello, world");
        thread.join();
    }
    ////////////////////////////////////////////////////////////////////////
    {

        std::cout << "\nTest " << t++ << " - T&.\n";

        Promise<int &> pint;
        Promise<int &> dsa;
        Future<int &> f = pint.getFuture();

        int test = 10;
        dsa = std::move(pint);
        dsa.set(test);

        int &y = f.get();

        y = 100;

        std::cout << "int y = " << test << ".\n";
    }

    std::cout << "\n\nThe End\n";
    return 0;
}


