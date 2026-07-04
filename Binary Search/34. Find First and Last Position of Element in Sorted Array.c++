// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/


/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search twice:
            1. Find the first occurrence of the target.
            2. Find the last occurrence of the target.
        - Return both indices as the answer.
        - If the target is not present, both searches
          return -1.

    -------------------------------------------------------

    Why This Works

        Finding First Occurrence:
            - When target is found, store its index.
            - Continue searching on the left to check
              for an earlier occurrence.

        Finding Last Occurrence:
            - When target is found, store its index.
            - Continue searching on the right to check
              for a later occurrence.

        Thus, we obtain the complete range of the target.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Find First Occurrence:
            O(log N)

        Find Last Occurrence:
            O(log N)

        Total:
            O(2 log N)
            = O(log N)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Use Binary Search twice to find the first and last occurrence of the target."
*/
class Solution {
public:


    int findFirst(vector<int> & nums, int target)
    {
        int index= -1; 
        int start = 0; 
        int end = nums.size()-1;

        while(start <= end)
        {
            int mid = (start + end) / 2; 

            if(nums[mid] < target)
            {
                start = mid + 1;
            }
            else if(nums[mid] > target)
            {
                end = mid - 1;
            }
            else
            {
                index = mid; 
                end  = mid - 1; 
            }
        }

        return index;
    }
    int findLast(vector<int> & nums, int target)
    {
        int index= -1; 
        int start = 0; 
        int end = nums.size()-1;

        while(start <= end)
        {
            int mid = (start + end) / 2; 

            if(nums[mid] < target)
            {
                start = mid + 1;
            }
            else if(nums[mid] > target)
            {
                end = mid - 1;
            }
            else
            {
                index = mid; 
                start  = mid + 1; 
            }
        }

        return index; 
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() == 0)
        {
            return {-1,-1};
        }
        return {findFirst(nums, target), findLast(nums, target)};
    }
};