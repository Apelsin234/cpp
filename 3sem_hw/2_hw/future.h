#pragma once
//
// Created by Александр on 20.09.2017.
//

#include "shared_state.h"
#include <algorithm>
#include "promise.h"

template<typename T>
class Future {

    explicit Future(std::shared_ptr<FutureState<T> > state) : state_(state), useGet(false) {

    }

    void ensureInitialized() const {
        if (!state_) {
            throw std::runtime_error("Future have not state");
        }
    }


public:


    Future(Future &&f) noexcept : state_(std::move(f.state_)), useGet(f.useGet.load()) {

    }

    Future &operator=(Future &&f) noexcept {
        useGet = f.useGet.load();
        state_ = std::move(f.state_);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    ThreadPool * getPool(){
        return state_->curPool;
    }

    T get() const {
        if (useGet) {
            throw std::runtime_error("get has been already used.");
        }
        useGet = true;
        wait();
        if (!state_->hasPromise && !isReady()) {
            throw std::runtime_error("Future hasn't promise");
        } else if (state_->except) {
            std::rethrow_exception(state_->except);
        } else
            return std::move(state_->value);
            //return state_->value;
    }

    bool isReady() const {
        ensureInitialized();
        return state_->isReady;
    }

    void wait() const {
        ensureInitialized();
        std::unique_lock<std::mutex> lock(state_->mx);
        if (isReady()) {
            return;
        }
        state_->cv.wait(lock, [this]() {
            return isReady() || !state_->hasPromise;
        });

    }

    Future() = default;
    friend class Promise<T>;

private:

    std::shared_ptr<FutureState<T> > state_;
    mutable std::atomic<bool> useGet;

};

template<typename T>
class Future<T &> {

    explicit Future(std::shared_ptr<FutureState<T &> > state) : state_{state}, useGet(false) {

    }

    void ensureInitialized() const {
        if (!state_) {
            throw std::runtime_error("Future have not state");
        }
    }

public:


    Future(Future &&f) noexcept : state_(std::move(f.state_)), useGet(f.useGet.load()) {

    }

    Future &operator=(Future &&f) noexcept {
        useGet = f.useGet.load();
        state_ = std::move(f.state_);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    T &get() const {

        if (useGet) {
            throw std::runtime_error("get has been already used.");
        }
        useGet = true;
        wait();
        if (!state_->hasPromise && !isReady()) {
            throw std::runtime_error("Future hasn't promise");
        } else if (state_->except) {
            std::rethrow_exception(state_->except);
        } else
            return *state_->value;
    }

    bool isReady() const {
        ensureInitialized();
        return state_->isReady;
    }

    void wait() const {
        ensureInitialized();
        std::unique_lock<std::mutex> lock(state_->mx);
        if (isReady()) {
            return;
        }
        state_->cv.wait(lock, [this]() {
            return isReady() || !state_->hasPromise;
        });

    }

    friend class Promise<T &>;

private:


    mutable std::atomic<bool> useGet;
    std::shared_ptr<FutureState<T &> > state_;

};

template<>
class Future<void> {

    explicit Future(std::shared_ptr<FutureState<void> > state) : state_{state}, useGet(false) {

    }

    void ensureInitialized() const {
        if (!state_) {
            throw std::runtime_error("Future have not state");
        }
    }


public:

    Future(Future &&f) noexcept : state_(std::move(f.state_)), useGet(f.useGet.load()) {

    }

    Future &operator=(Future &&f) noexcept {
        useGet = f.useGet.load();
        state_ = std::move(f.state_);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    void get() const {

        if (useGet) {
            throw std::runtime_error("get has been already used.");
        }
        useGet = true;
        wait();
        if (!state_->hasPromise && !isReady()) {
            throw std::runtime_error("Future hasn't promise");
        } else if (state_->except) {
            std::rethrow_exception(state_->except);
        }
    }

    bool isReady() const {
        ensureInitialized();
        return state_->isReady;
    }

    void wait() const {
        ensureInitialized();
        std::unique_lock<std::mutex> lock(state_->mx);
        if (isReady()) {
            return;
        }
        state_->cv.wait(lock, [this]() {
            return isReady() || !state_->hasPromise;
        });

    }

    friend class Promise<void>;

private:

    std::shared_ptr<FutureState<void> > state_;
    mutable std::atomic<bool> useGet;
};




