#ifndef TEST_READ_LAST_LINES_HPP_
#define TEST_READ_LAST_LINES_HPP_

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <queue>

#include "files/read_last_lines.hpp"

BOOST_AUTO_TEST_CASE(test_rll_invalid_args)
{
    BOOST_CHECK(std::queue<std::string>() == ReadLastLines(std::string(), 0));
    BOOST_CHECK(std::queue<std::string>() == ReadLastLines(std::string(), 10));
}

BOOST_AUTO_TEST_CASE(test_rll_invalid_file)
{
    BOOST_CHECK(std::queue<std::string>() == ReadLastLines("hhh", 10));
}

BOOST_AUTO_TEST_CASE(test_rll)
{
    // Show current working dir of executable
    // std::cout << boost::filesystem::initial_path() << std::endl;

    std::queue<std::string> expected;
    expected.push("third line");
    expected.push("fourth line");
    expected.push("last line");

    // WARNING: check that path to txt-file is valid!
    BOOST_CHECK(expected ==
            ReadLastLines("./test/data/text_file.txt", 3));
}

#endif /* TEST_READ_LAST_LINES_HPP_ */
