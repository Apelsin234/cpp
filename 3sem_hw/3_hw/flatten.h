#pragma once
//
// Created by Александр on 11.10.2017.
//
#include "future.h"
#include <thread>

template<typename T>
struct nested_type_getter;

template<typename T>
struct nested_type_getter<Future<T>> {
    typedef T type_t;
};

template<typename T>
struct nested_type_getter<Future<Future<T>>> {
    typedef typename nested_type_getter<Future<T>>::type_t type_t;
};




template<typename T>
T FlattenImpl(const Future<T> &future) {

    return std::move(future.get());
}
//саблинская voenkomat
template <typename T>
auto FlattenImpl(const Future<Future<T>> & future){
    return std::move(FlattenImpl(std::move(future.get())));
}

template<typename T>
auto Flatten(const Future<Future<T>> & future) {

    std::shared_ptr<Promise<typename nested_type_getter<Future<T>>::type_t>> p(new Promise<typename nested_type_getter<Future<T>>::type_t>());
    std::thread([p, &future](){

        p->set(std::move(FlattenImpl(std::move(future))));

    }).detach();
    return std::move(p->getFuture());
}


template<typename T>
auto Flatten( Future<T>  f) {
    return std::move(f);
}

template<template<typename ...> class C, typename T>
Future<C<T>> Flatten(C<Future<T> > const &col) {

    std::shared_ptr<Promise<C<T>>> p(new Promise<C<T>>);

    std::thread([p, &col]() {
        C <T> val;
        for (auto &n: col) {
            val.push_back(n.get());
        }
        p->set(val);
    }).detach();

    return p->getFuture();
}
