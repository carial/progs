/*
 * test181.cpp
 *
 *  Created on: May 5, 2018
 *      Author: yinqingzhao
 */
#include <iostream>
#include <cstdint>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

/*
There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5
*/

/*
 * complexity: O(log(m)*log(n))
 */
class Solution1 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        if (len1 == 0) {
            if (len2 == 0) {
                return INT32_MIN;
            } else {
                return double((nums2[len2 / 2 ] + nums2[(len2 - 1) / 2])) / 2;
            }
        }
        if (len2 == 0) {
            return double((nums1[len1 / 2] + nums1[(len1 - 1) / 2])) / 2;
        }
        //@nums1 @nums2 not empty
        int start1 = 0, end1 = len1 - 1, start2 = 0, end2 = len2 - 1;
        int middle1, middle2, middle3 = 0, middle4 = 0, middlePos = (len1 + len2 - 1) / 2;
        //assume all integers are different
        //get middle point @middle1 of [start1, end1] and search in [start2, end2], @middle3
        //@middle1 position in total array is (middle1 + middle3 + 1), compare with (len1 + len2 - 1) / 2
        //if less, check [(middle1+1), end1]; if more, check [start1, (middle1-1)]
        //get middle point @middle2 of [start2, end2] and search in [start1, end1], @middle4
        //@middle2 position in total array  is (middle2 + middle4 + 1), compare with (len1 + len2 - 1) / 2
        //if less, check [(middle2+1), end2]; if more, check [start2, (middle2-1)]
        //so two searches per round
        while (1) {
            if (start1 <= end1) {
                middle1 = (start1 + end1) / 2;
                middle3 = findPosition(nums1[middle1], nums2, 0, len2 - 1);
                int pos;
                bool found = false;
                if (middle3 > -1 && nums1[middle1] == nums2[middle3]) {
                    for (int i = middle3; i < nums2.size() && nums2[i] == nums1[middle1]; ++i) {
                        //@middle1 can be positioned before or after i
                        pos = middle1 + i;
                        if (pos == middlePos) {
                            found = true;
                            middle3 = i - 1;
                            break;
                        }
                        pos = middle1 + i + 1;
                        if (pos == middlePos) {
                            found = true;
                            middle3 = i;
                            break;
                        }
                    }
                } else {
                    pos = middle1 + middle3 + 1;
                    if (pos == middlePos) {
                        found = true;
                    }
                }
                if (found) {
                    if ((len1 + len2) % 2) {
                        return nums1[middle1];
                    } else {
                        //check next bigger than nums1[middle1]
                        int nextNum = INT32_MAX;
                        if (middle1 + 1 < len1) {
                            nextNum = nums1[middle1 + 1];
                        }
                        if (middle3 + 1 < len2 && nums2[middle3 + 1] < nextNum) {
                            nextNum = nums2[middle3 + 1];
                        }
                        return double(nums1[middle1] + nextNum) / 2;
                    }
                } else if (pos < middlePos) {
                    start1 = middle1 + 1;
                } else {
                    end1 = middle1 - 1;
                }
            }
            if (start2 <= end2) {
                middle2 = (start2 + end2) / 2;
                middle4 = findPosition(nums2[middle2], nums1, 0, len1 - 1);
                int pos;
                bool found = false;
                if (middle4 > -1 && nums2[middle2] == nums1[middle4]) {
                    for (int i = middle4; i < nums1.size() && nums1[i] == nums2[middle2]; ++i) {
                        pos = middle2 + i;
                        if (pos == middlePos) {
                            found = true;
                            middle4 = i - 1;
                            break;
                        }
                        pos = middle2 + i + 1;
                        if (pos == middlePos) {
                            found = true;
                            middle4 = i;
                            break;
                        }
                    }
                } else {
                    pos = middle2 + middle4 + 1;
                    if (pos == middlePos) {
                        found = true;
                    }
                }
                if (found) {
                    if ((len1 + len2) % 2) {
                        return nums2[middle2];
                    } else {
                        //check next bigger than nums2[middle2]
                        int nextNum = INT32_MAX;
                        if (middle2 + 1 < len2) {
                            nextNum = nums2[middle2 + 1];
                        }
                        if (middle4 + 1 < len1 && nums1[middle4 + 1] < nextNum) {
                            nextNum = nums1[middle4 + 1];
                        }
                        return double(nums2[middle2] + nextNum) / 2;
                    }
                } else if (pos < middlePos) {
                    start2 = middle2 + 1;
                } else {
                    end2 = middle2 - 1;
                }
            }
        }
    }
    private:
    int findPosition(int target, const vector<int>& nums, int start, int end) {
        //search @target in @nums in range [@start, @end]
        //return position of integer that just less than or equal to target
        //if none, return -1;
        int middle;
        while (1) {
            middle = (start + end) / 2;
            if (target < nums[middle]) {
                end = middle - 1;
            } else if (target > nums[middle]) {
                //check if target < nums[middle+1]
                if (middle < nums.size() - 1) {
                    if (target < nums[middle + 1]) {
                        return middle;
                    } else if (target > nums[middle + 1]) {
                        start = middle + 1;
                    } else if (target == nums[middle + 1]) {
                        return middle;
                    }
                } else {
                    return middle;
                }
            } else if (target == nums[middle]) {
                if (middle > 0) {
                    if (target > nums[middle - 1]) {
                        return middle;
                    } else {
                        end = middle - 1;
                    }
                } else {
                    return middle;
                }
            }
            if (end < start) {
                return -1;
            }
        }
    }
};

/*
 * complexity O(log(min(m, n)))
 * main point: there will be a cut at middle1 in nums1 and pos in nums2
 * once middle1 is known, pos can be derived (we know the length of nums1 and nums2)
 * And the definition of Median: it divides the numbers into two parts. number of elements in first and second parts at most differ at one
 */
class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size(), len2 = nums2.size();
        if (len1 == 0) {
            if (len2 == 0) {
                return INT32_MIN;
            } else {
                return double(nums2[len2 / 2] + nums2[(len2 - 1) / 2]) / 2;
            }
        }
        if (len2 == 0) {
            return double(nums1[len1 / 2] + nums1[(len1 - 1) / 2]) / 2;
        }
        //take the middle position @middle1 in nums1, check the position @pos in nums2
        //(middle1+pos+1+1) = (len1+len2)/2 => (middle1+pos)=(len1+len2)/2-2
        //@middle1, @pos takes [-1...len1/len2-1], -1 means no element
        int start1 = 0, end1 = len1 - 1, middle1, pos;
        bool found = false;
        while (1) {
            middle1 = (start1 + end1) / 2;
            //find @pos
            pos = (len1 + len2) / 2 - 2 - middle1;
            if (pos < -1) {
                //[0...middle1] is more than (len1+len2)/2
                //reduce middle1
                end1 = middle1 - 1;
            } else if (pos > len2 - 1) {
                start1 = middle1 + 1;
            } else if (pos == -1) {
                //[0...middle1] is just (len1+len2)/2
                //check nums1[middle1] and nums1[middle1+1] and nums2[0]
                if (nums1[middle1] <= nums2[0]) {
                    found = true;
                } else {
                    end1 = middle1 - 1;
                }
            } else if (pos == len2 - 1) {
                if (nums2[pos] <= nums1[middle1 + 1]) {
                    found = true;
                } else {
                    start1 = middle1 + 1;
                }
            } else {
                //[0...middle1] and [0...pos] are one part
                //check nums1[middle1]/nums2[pos] with nums1[middle1+1] and nums2[pos+1]
                if (((middle1 == len1 - 1) || nums2[pos] <= nums1[middle1 + 1]) && ((pos == len2 - 1) || nums1[middle1] <= nums2[pos + 1])) {
                    found = true;
                } else {
                    if (middle1 == len1 - 1) {
                        //nums1[middle1] > nums2[pos + 1]
                        end1 = middle1 - 1;
                    } else if (pos == len2 - 1) {
                        //nums2[pos] > nums1[middle + 1]
                        start1 = middle1 + 1;
                    } else if (nums2[pos] > nums1[middle1 + 1]) {
                        start1 = middle1 + 1;
                    } else if (nums1[middle1] > nums2[pos + 1]) {
                        end1 = middle1 - 1;
                    }
                }
            }
            if (found) {
                if ((len1 + len2) % 2 == 0) {
                    //max of nums1[middle1] and nums2[pos], and min of nums1[middle1+1] and nums2[pos+1]
                    int maxNum = nums1[middle1], minNum = INT32_MAX;
                    if (pos > -1 && maxNum < nums2[pos]) {
                        maxNum = nums2[pos];
                    }
                    if (middle1 < len1 - 1 && nums1[middle1 + 1] < minNum) {
                        minNum = nums1[middle1 + 1];
                    }
                    if (pos < len2 - 1 && nums2[pos + 1] < minNum) {
                        minNum = nums2[pos + 1];
                    }
                    return double(maxNum + minNum) / 2;
                } else {
                    //min of nums1[middle1+1] and nums2[pos+1]
                    int minNum = INT32_MAX;
                    if (middle1 < len1 - 1 && nums1[middle1 + 1] < minNum) {
                        minNum = nums1[middle1 + 1];
                    }
                    if (pos < len2 - 1 && nums2[pos + 1] < minNum) {
                        minNum = nums2[pos + 1];
                    }
                    return minNum;
                }
            }
            if (start1 > end1) {
                if (end1 < 0) {
                    middle1 = -1;
                    pos = (len1 + len2) / 2 - 2 - middle1;
                    if ((len1 + len2) % 2 == 0) {
                        if (pos + 1 < len2) {
                            if (nums2[pos + 1] <= nums1[0]) {
                                return double(nums2[pos] + nums2[pos + 1]) / 2;
                            } else {
                                return double(nums2[pos] + nums1[0]) / 2;
                            }
                        } else {
                            return double(nums2[pos] + nums1[0]) / 2;
                        }
                    } else {
                        if (pos + 1 < len2) {
                            if (nums2[pos + 1] <= nums1[0]) {
                                return nums2[pos + 1];
                            } else {
                                return nums1[0];
                            }
                        } else {
                            return nums1[0];
                        }
                    }
                } else if (start1 > len1 - 1) {
                    middle1 = len1 - 1;
                    pos = (len1 + len2) / 2 - 2 - middle1;
                    if (pos <= -1) {
                        if ((len1 + len2) % 2 == 0) {
                            return double(nums1[len1 - 1] + nums2[0]) / 2;
                        } else {
                            return nums2[0];
                        }
                    } else {
                        if ((len1 + len2) %2 == 0) {
                            if (nums1[len1 - 1] <= nums2[pos]) {
                                return double(nums2[pos] + nums2[pos + 1]) / 2;
                            } else {
                                return double(nums1[len1 - 1] + nums2[pos + 1]) / 2;
                            }
                        } else {
                            return nums2[pos + 1];
                        }
                    }
                }
            }
        }
    }
};
