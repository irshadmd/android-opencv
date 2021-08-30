//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// type_traits

// add_rvalue_reference
// If T names a referenceable type then the member typedef type
//   shall name T&&; otherwise, type shall name T.

#include <type_traits>
#include "test_macros.h"

#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES

template <class T, class U>
void test_add_rvalue_reference()
{
    static_assert((std::is_same<typename std::add_rvalue_reference<T>::type, U>::value), "");
#if TEST_STD_VER > 11
    static_assert((std::is_same<std::add_rvalue_reference_t<T>, U>::value), "");
#endif
}

template <class F>
void test_function0()
{
    static_assert((std::is_same<typename std::add_rvalue_reference<F>::type, F&&>::value), "");
#if TEST_STD_VER > 11
    static_assert((std::is_same<std::add_rvalue_reference_t<F>, F&&>::value), "");
#endif
}

template <class F>
void test_function1()
{
    static_assert((std::is_same<typename std::add_rvalue_reference<F>::type, F>::value), "");
#if TEST_STD_VER > 11
    static_assert((std::is_same<std::add_rvalue_reference_t<F>, F>::value), "");
#endif
}
#endif  // _LIBCPP_HAS_NO_RVALUE_REFERENCES

struct Foo {};

int main()
{
#ifndef _LIBCPP_HAS_NO_RVALUE_REFERENCES
    test_add_rvalue_reference<void, void>();
    test_add_rvalue_reference<int, int&&>();
    test_add_rvalue_reference<int[3], int(&&)[3]>();
    test_add_rvalue_reference<int&, int&>();
    test_add_rvalue_reference<const int&, const int&>();
    test_add_rvalue_reference<int*, int*&&>();
    test_add_rvalue_reference<const int*, const int*&&>();
    test_add_rvalue_reference<Foo, Foo&&>();

//  LWG 2101 specifically talks about add_rvalue_reference and functions.
//  The term of art is "a referenceable type", which a cv- or ref-qualified function is not.
    test_function0<void()>();
#if TEST_STD_VER >= 11
    test_function1<void() const>();
    test_function1<void() &>();
    test_function1<void() &&>();
    test_function1<void() const &>();
    test_function1<void() const &&>();
#endif

//  But a cv- or ref-qualified member function *is* "a referenceable type"
    test_function0<void (Foo::*)()>();
#if TEST_STD_VER >= 11
    test_function0<void (Foo::*)() const>();
    test_function0<void (Foo::*)() &>();
    test_function0<void (Foo::*)() &&>();
    test_function0<void (Foo::*)() const &>();
    test_function0<void (Foo::*)() const &&>();
#endif
#endif
}
