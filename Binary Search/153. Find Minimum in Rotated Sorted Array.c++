// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/


/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search on the rotated sorted array.
        - In every iteration, determine which half is sorted.
        - The minimum element of a sorted half is its
          first element.
        - Update the answer with the minimum of the
          sorted half, then continue searching in the
          unsorted half.

    -------------------------------------------------------

    Why This Works

        Left Half is Sorted:

            nums[start] <= nums[mid]

            - nums[start] is the smallest element
              in the left half.
            - Update the answer with nums[start].
            - Search the right half since the rotation,
              if any, lies there.

        Right Half is Unsorted:

            nums[start] > nums[mid]

            - Rotation lies in the left half.
            - nums[mid] is a candidate for the minimum.
            - Update the answer with nums[mid].
            - Search the left half.

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

        "Identify the sorted half, record its minimum element, and continue searching in the unsorted half."
*/
class Solution {
public:
    int findMin(vector<int>& nums) {
        int res = INT_MAX;
        int start = 0 ;
        int end = nums.size() -1;

        while(start <= end)
        {
            int mid = (start + end) /2;

            if(nums[start] <= nums[mid])
            {
                res = min(res, nums[start]);
                start = mid +1 ;
            }
            else
            {
                res = min(res, nums[mid]);
                end = mid -1; 
            }
        }

        return res;
    }
};