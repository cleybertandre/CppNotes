#ifndef TEST_DUPLICATES_IN_ARRAY_HPP
#define TEST_DUPLICATES_IN_ARRAY_HPP

#include <boost/test/unit_test.hpp>

#include "algorithms/data_structures/duplicates_in_array.hpp"

BOOST_AUTO_TEST_CASE(test_dia_empty_arr)
{
    DuplicatesInArray::Solution solution;
    std::vector<int> numbers = {};
    BOOST_CHECK(false == solution.containsDuplicate(numbers));
}

BOOST_AUTO_TEST_CASE(test_dia_no_duplicates)
{
    DuplicatesInArray::Solution solution;
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6};
    BOOST_CHECK(false == solution.containsDuplicate(numbers));
}

BOOST_AUTO_TEST_CASE(test_dia_have_duplicates)
{
    DuplicatesInArray::Solution solution;
    std::vector<int> numbers = {1, 2, 3, 4, 5, 3};
    BOOST_CHECK(true == solution.containsDuplicate(numbers));
}

#endif // TEST_DUPLICATES_IN_ARRAY_HPP