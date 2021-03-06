#ifndef SUMMARY_RANGES_HPP
#define SUMMARY_RANGES_HPP

/*
https://leetcode.com/problems/summary-ranges/description/
Given a sorted integer array without duplicates, return the summary of its
ranges.

Example 1:
Input:  [0,1,2,4,5,7]
Output: ["0->2","4->5","7"]
Explanation: 0,1,2 form a continuous range; 4,5 form a continuous range.

Example 2:
Input:  [0,2,3,4,6,8,9]
Output: ["0","2->4","6","8->9"]
Explanation: 2,3,4 form a continuous range; 8,9 form a continuous range.
*/

#include <vector>
#include <string>

namespace Algo::DS::Array {

class SummaryRanges {
public:
    static std::vector<std::string> Create(const std::vector<int>& nums) {
        std::vector<std::string> result;
        if (nums.empty()) {
            return result;
        }

        for (size_t start = 0, i = 1;
             start < nums.size() && i <= nums.size(); ++i)
        {
            while(i < nums.size() && nums[i] - nums[i - 1] == 1) {
                ++i;
            }

            std::string compStr = std::to_string(nums[start]);
            if (i - start > 1) {
                compStr += "->" + std::to_string(nums[i - 1]);
            }

            result.push_back(compStr);
            start = i;
        }

        return result;
    }
};

}

#endif // SUMMARY_RANGES_HPP
