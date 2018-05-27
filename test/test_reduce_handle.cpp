#include <iostream>
#define BOOST_TEST_MODULE reduce_handle
#include <boost/test/unit_test.hpp>

#include "../ReduceHandle.h"
#include "../ReduceHandle.cpp"

BOOST_AUTO_TEST_SUITE(Test_ReduceHandle)

BOOST_AUTO_TEST_CASE(test_prefix1)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("mail@mail.ru");
//    reduceHandle("gmail@gmail.com");
//    reduceHandle("rumbler@rumbler.ru");
//    reduceHandle("yandex@yandex.ru");
//    reduceHandle("uac-ic@uac-ic.ru");
//    BOOST_CHECK(reduceHandle.save() == 1);
}

BOOST_AUTO_TEST_CASE(test_prefix2)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("mail@mail.ru");
//    reduceHandle("gmail@gmail.com");
//    reduceHandle("gumbler@rumbler.ru");
//    reduceHandle("yandex@yandex.ru");
//    reduceHandle("uac-ic@uac-ic.ru");
//    BOOST_CHECK(reduceHandle.save() == 2);
}

BOOST_AUTO_TEST_CASE(test_prefix3)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("mail@mail.ru");
//    reduceHandle("gmail@gmail.com");
//    reduceHandle("gumbler@rumbler.ru");
//    reduceHandle("gundex@yandex.ru");
//    reduceHandle("uac-ic@uac-ic.ru");
//    BOOST_CHECK(reduceHandle.save() == 3);
}

BOOST_AUTO_TEST_CASE(test_prefix4)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("mail@mail.ru");
//    reduceHandle("gmail@gmail.com");
//    reduceHandle("gumbler@rumbler.ru");
//    reduceHandle("gundex@yandex.ru");
//    reduceHandle("gun-ic@uac-ic.ru");
//    BOOST_CHECK(reduceHandle.save() == 4);
}

BOOST_AUTO_TEST_CASE(test_prefixAsWord1)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("mail@mail.ru");
//    reduceHandle("mail@mail.ru@gmail.com");
//    reduceHandle("gumbler@rumbler.ru");
//    reduceHandle("gundex@yandex.ru");
//    reduceHandle("gun-ic@uac-ic.ru");
//    BOOST_CHECK(reduceHandle.save() == 13);
}

BOOST_AUTO_TEST_CASE(test_prefixAsWord2)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("mail@mail.ru");
//    reduceHandle("mail@mail.ru@gmail.com");
//    reduceHandle("mail@mail.ru@gmail.com");
//    reduceHandle("gundex@yandex.ru");
//    reduceHandle("gun-ic@uac-ic.ru");
//    BOOST_CHECK(reduceHandle.save() == 23);
}

BOOST_AUTO_TEST_CASE(test_prefixEmptyString)
{
//    ReduceHandle reduceHandle;
//    reduceHandle("");
//    reduceHandle("");
//    BOOST_CHECK(reduceHandle.save() == 1);
}

BOOST_AUTO_TEST_SUITE_END()
