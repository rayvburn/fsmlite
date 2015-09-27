#include <cassert>
#include <type_traits>

#include "fsm.hpp"

using namespace fsmlite::detail;

void test_concat()
{
    assert((std::is_same<list<>, concat<>::type>::value));
    assert((std::is_same<list<int>, concat<int, list<>>::type>::value));
    assert((std::is_same<list<int, char>, concat<int, list<char>>::type>::value));
}

void test_filter()
{
    assert((std::is_same<list<>, filter<std::is_integral>::type>::value));
    assert((std::is_same<list<>, filter<std::is_integral, float>::type>::value));
    assert((std::is_same<list<int>, filter<std::is_integral, int>::type>::value));
    assert((std::is_same<list<int>, filter<std::is_integral, int, float>::type>::value));
    assert((std::is_same<list<int>, filter<std::is_integral, float, int>::type>::value));
    assert((std::is_same<list<int, long>, filter<std::is_integral, int, long>::type>::value));
    assert((std::is_same<list<long, int>, filter<std::is_integral, long, int>::type>::value));
}

void test_is_callable()
{
    struct foo {
        void operator()(int);
        void operator()(char*);
    };

    assert((is_callable<foo, int>::value));
    assert((is_callable<foo, int&>::value));
    assert((is_callable<foo, int const&>::value));
    assert((is_callable<foo, long>::value));
    assert((is_callable<foo, char*>::value));

    assert((!is_callable<foo>::value));
    assert((!is_callable<foo, int*>::value));
    assert((!is_callable<foo, char const*>::value));
    assert((!is_callable<foo, void*>::value));
    assert((!is_callable<foo, int, char*>::value));
}

int main()
{
    test_concat();
    test_filter();
    test_is_callable();
    return 0;
}