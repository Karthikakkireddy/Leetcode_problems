// https://leetcode.com/problems/search-insert-position/description/

/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search to locate the target.
        - If the target is found, return its index.
        - Otherwise, keep track of the first element
          greater than the target.
        - That position is where the target should
          be inserted to maintain sorted order.

    -------------------------------------------------------

    Why This Works

        - If nums[mid] < target, the target or its
          insertion position lies on the right.

        - If nums[mid] > target, mid is a potential
          insertion position, but there may be an
          earlier valid position on the left.

        - If nums[mid] == target, the target already
          exists, so return its index immediately.

        - The variable 'index' always stores the leftmost
          valid insertion position found so far.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Binary Search:
            O(log N)

        Total:
            O(log N)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Use Binary Search to find the target or the first position where it can be inserted."
*/
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {

        int start = 0 ;
        int end = nums.size() - 1 ;
        int index = nums.size(); 
        while(start <= end)
        {
            int mid = (start + end) / 2;

            if(nums[mid] < target)
            {
                start = mid + 1;
            }
            else if(nums[mid] > target)
            {
                index = mid ; 
                end = mid -1;
            }
            else
            {
                return mid;
            }
        }

        return index;
    }
};