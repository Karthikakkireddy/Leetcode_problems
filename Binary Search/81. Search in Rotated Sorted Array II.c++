// https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/


/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search on the rotated sorted array.
        - In every iteration, at least one half is
          normally sorted.
        - Determine the sorted half and check whether
          the target lies within it.
        - If duplicates make it impossible to identify
          the sorted half, shrink the search space by
          moving both pointers inward.

    -------------------------------------------------------

    Why This Works

        Duplicate Case:

            nums[start] == nums[mid] == nums[end]

            - We cannot determine which half is sorted.
            - Shrink the search space:

                  start++
                  end--

        Left Half is Sorted:

            nums[start] <= nums[mid]

            - If target lies within this range,
              search the left half.

            - Otherwise,
              search the right half.

        Right Half is Sorted:

            nums[mid] <= nums[end]

            - If target lies within this range,
              search the right half.

            - Otherwise,
              search the left half.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Average Case:
            O(log N)

        Worst Case:
            O(N)

        Reason:
            When many duplicate elements exist,
            repeatedly shrinking the search space by
            one element degrades Binary Search to
            Linear Search.

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Use Binary Search on the rotated array and handle duplicate ambiguity by shrinking both ends."
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int start = 0 ; 
        int end = nums.size() -1 ; 

        while(start <= end)
        {
            int mid = (start + end ) /2; 

            if(nums[mid] == target)
            {
                return true; 
            }
            else if(nums[start] == nums[mid] && nums[mid] == nums[end])
            {
                start++ ;
                end--;
            }
            else if(nums[start] <= nums[mid])
            {
                if(nums[start ] <= target && target <= nums[mid])
                {
                    end = mid -1 ;
                }
                else
                {
                    start = mid + 1; 
                }
            }
            else
            {
                if(nums[mid] <= target && target <= nums[end])
                {
                    start = mid +1;
                }
                else
                {
                    end = mid -1;
                }
            }
        }

        return false;
    }
};