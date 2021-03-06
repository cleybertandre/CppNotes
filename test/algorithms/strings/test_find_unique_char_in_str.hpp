#ifndef TEST_FIND_UNIQUE_CHAR_IN_STR_HPP
#define TEST_FIND_UNIQUE_CHAR_IN_STR_HPP

#include <boost/test/unit_test.hpp>

#include "algorithms/strings/find_unique_char_in_str.hpp"

BOOST_AUTO_TEST_CASE(test_fucis_empty_str)
{
    FindUnique::Solution solution;
    std::string str;
    int expected = -1;
    BOOST_CHECK(expected == solution.firstUniqChar(str));
}

BOOST_AUTO_TEST_CASE(test_fucis_str_size_one)
{
    FindUnique::Solution solution;
    std::string str("a");
    int expected = 0;
    BOOST_CHECK(expected == solution.firstUniqChar(str));
}

BOOST_AUTO_TEST_CASE(test_fucis_str_no_unique)
{
    FindUnique::Solution solution;
    std::string str("aaaabbb");
    int expected = -1;
    BOOST_CHECK(expected == solution.firstUniqChar(str));
}

BOOST_AUTO_TEST_CASE(test_fucis_str_have_unique)
{
    FindUnique::Solution solution;

    {
        std::string str("leetcode");
        int expected = 0;
        BOOST_CHECK(expected == solution.firstUniqChar(str));
    }

    {
        std::string str("loveleetcode");
        int expected = 2;
        BOOST_CHECK(expected == solution.firstUniqChar(str));
    }
}
#endif // TEST_FIND_UNIQUE_CHAR_IN_STR_HPP
