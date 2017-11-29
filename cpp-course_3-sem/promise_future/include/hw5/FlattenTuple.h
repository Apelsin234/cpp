//
// Created by Александр on 14.11.2017.
//
#include "promise.h"
#include "future.h"
#include <tuple>


template<typename T, typename Q = void>
struct nested_type_getter;


template<typename T>
struct nested_type_getter<T> {
    typedef T type_t;
};

template<typename T>
struct nested_type_getter<Future<T>> {
    typedef typename nested_type_getter<T>::type_t type_t;
};

template <typename ...Args>
struct nested_type_getter<std::tuple<Args...>> {
    typedef std::tuple<typename nested_type_getter<Args>::type_t...> type_t;
};


template<typename T>
T K(const T &future) {
    return std::move(future);
}
template <typename T>
auto K(const Future<T> & future){
    return std::move(K(std::move(future.get())));
}

template<typename ...Args, std::size_t... I>
auto FlattenTupleImpl(const std::tuple<Args...>& a, std::index_sequence<I...>)
{
    return std::make_tuple(K(std::get<I>(a))...);
}

template <class ...TParams, typename Indices = std::make_index_sequence<sizeof...( TParams )>>
auto FlattenTuple(std::tuple<TParams...> tuple){
    using K = typename nested_type_getter<std::tuple<TParams...>>::type_t;
    std::shared_ptr<Promise<K > > q (new Promise<K >);
    std::thread([q, &tuple](){
        auto t = FlattenTupleImpl(tuple, Indices{});
        q->set(t);
    }).detach();
    return q->getFuture();
}