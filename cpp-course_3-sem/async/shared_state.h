#pragma once
//
// Created by Александр on 25.09.2017.
//

#include <condition_variable>
#include <atomic>

template<typename>
class Promise;

template<typename>
class Future;

class State {

public:
    std::atomic<bool> isReady;
    std::atomic<bool> hasPromise;
    std::exception_ptr except;
    std::mutex mx;
    std::condition_variable cv;
};

template<typename T>
class FutureState : private State {
public:

    friend class Promise<T>;

    friend class Future<T>;

private:

    T value;
};

template<>
class FutureState<void> : private State {
public:

    friend class Promise<void>;

    friend class Future<void>;

};

template<typename T>
class FutureState<T &> : private State {
public:
    friend class Promise<T &>;

    friend class Future<T &>;

private:
    T *value;

};
