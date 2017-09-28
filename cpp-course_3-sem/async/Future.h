//
// Created by Александр on 20.09.2017.
//

#include "FutureState.h"

using ulock = std::unique_lock<std::mutex>;


template<typename T>
class Future {

    explicit Future(std::shared_ptr<FutureState<T> > state) : state_{state} {

    }


public:
    Future(Future &&f) : state_(std::move(f.state_)) {

    }

    Future &operator=(Future &&f) {
        *this = std::move(f);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    T get() const {
        wait();
        if (state_->except) {
            std::rethrow_exception(state_->except);
        } else if (!state_->hasPromise) {
            throw std::runtime_error("Future hasn't promise");
        } else
            return std::move(state_->value);
    }

    bool isReady() const {
        return state_->isReady;
    }

    void wait() const {
        ulock lock(state_->mx);
        if (isReady()) {
            return;
        }
        state_->cv.wait(lock, [this]() {
            return isReady();
        });

    }

    friend class Promise<T>;

private:

    std::shared_ptr<FutureState<T> > state_;

};

template<typename T>
class Future<T &> {

    explicit Future(std::shared_ptr<FutureState<T &> > state) : state_{state} {

    }

public:


    Future(Future &&f) : state_(std::move(f.state_)) {

    }

    Future &operator=(Future &&f) {
        *this = std::move(f);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    T &get() const {
        wait();
        if (state_->except) {
            std::rethrow_exception(state_->except);
        } else if (!state_->hasPromise) {
            throw std::runtime_error("Future hasn't promise");
        } else
            return *state_->value;
    }

    bool isReady() const {
        return state_->isReady;
    }

    void wait() const {
        ulock lock(state_->mx);
        if (isReady()) {
            return;
        }
        state_->cv.wait(lock, [this]() {
            return isReady();
        });

    }

    friend class Promise<T &>;

private:

    std::shared_ptr<FutureState<T &> > state_;

};

template<>
class Future<void> {

    explicit Future(std::shared_ptr<FutureState<void> > state) : state_{state} {

    }


public:

    Future(Future &&f) : state_(std::move(f.state_)) {

    }

    Future &operator=(Future &&f) {
        *this = std::move(f);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    void get() const {
        wait();
        if (state_->except) {
            std::rethrow_exception(state_->except);

        } else if (!state_->hasPromise) {
            throw std::runtime_error("Future hasn't promise");
        }
    }

    bool isReady() const {
        return state_->isReady;
    }

    void wait() const {
        ulock lock(state_->mx);
        if (isReady()) {
            return;
        }
        state_->cv.wait(lock, [this]() {
            return isReady();
        });

    }

    friend class Promise<void>;

private:

    std::shared_ptr<FutureState<void> > state_;

};




