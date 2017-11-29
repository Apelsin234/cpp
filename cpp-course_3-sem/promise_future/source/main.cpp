//
// Created by Александр on 29.9.2017
//
#ifdef _GTEST

#include <gtest/gtest.h>
#include "hw5/FlattenTuple.h"

#include <vector>
#include <hw6/Parallel.h>

#endif

using namespace std;


template<class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr> &os,
                      const Tuple &t,
                      std::index_sequence<Is...>) {
    ((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), ...);
}

template<class Ch, class Tr, typename T>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr> &os,
                          const vector <T> &t) {
    os << "[ ";
    for (auto &i: t) {

        os << i;
        if (i != t.back())
            os << ", ";
    }
    return os << "]";
}

template<class Ch, class Tr, typename T, typename L>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr> &os,
                          const map <T, L> &t) {
    os << "[ ";
    for (auto &i: t) {
        os << "{ "<<i.first <<": " << i.second << "}, ";

    }
    return os << "]";
}

template<class Ch, class Tr, class... Args>
decltype(auto) operator<<(std::basic_ostream<Ch, Tr> &os,
                          const std::tuple<Args...> &t) {
    os << "(";
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ")";
}

int main(int argc, char *argv[]) {

    /* vector<std::string> k ={"a", "k", "l"};
     auto f = [](std::string a)  {
         return a + "poh";
     };
     ThreadPool t(3);
     auto a= k.begin();
     auto b= k.end();
     t.Parallel(a,b, f);

     std::this_thread::sleep_for(std::chrono::seconds(2));
     while(a != b){

         cout << *a <<" ";
         a++;
     }*/
    int q;
    Promise<int> q1;
    Promise<std::vector<int>> q2;
    Promise<std::map<std::string, int>> q_map;
    Promise<Future<std::vector<int>>> q3;
    q3.set(std::move(q2.getFuture()));
    auto t = make_tuple(q, q1.getFuture(), q3.getFuture(), q_map.getFuture());
    q1.set(1);
    vector<int> k = {1, 2, 3, 4, 5};
    map<std::string, int> k2 = {{"hi",     2},
                                {"lol",    337},
                                {"qwerty", 258}};
    q_map.set(k2);
    q = 0;
    q2.set(k);
    auto s = FlattenTuple(move(t));
    cout << s.get() << endl;


    return 0;
#ifdef _GTEST
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    return 0;
}