// https://leetcode.com/problems/single-element-in-a-sorted-array/description/


/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search on the sorted array.
        - Before the single element:
            - The first occurrence of every pair is at
              an even index.
            - The second occurrence is at an odd index.
        - After the single element, this pattern breaks.
        - Use the parity of mid to decide which half
          to continue searching.

    -------------------------------------------------------

    Why This Works

        If mid is Even:

            nums[mid] == nums[mid + 1]

                - Pair is complete.
                - Single element lies on the right.

            nums[mid] == nums[mid - 1]

                - Pattern has already broken.
                - Single element lies on the left.

        If mid is Odd:

            nums[mid] == nums[mid - 1]

                - Pair is complete.
                - Single element lies on the right.

            nums[mid] == nums[mid + 1]

                - Pattern has broken.
                - Single element lies on the left.

        If neither neighbor matches,
        nums[mid] itself is the single element.

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

        "Use Binary Search and the even-odd pairing pattern to locate the single non-duplicate element."
*/
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int start = 0; 
        int n = nums.size();
        int end = n-1;

        while(start <= end)
        {
            int mid = (start  + end ) /2;

            if(mid % 2 == 0)
            {
                if(mid != n-1 && nums[mid] == nums[mid+1] )
                {
                    start = mid +2;
                }
                else if(mid!=0 && nums[mid] == nums[mid-1])
                {
                    end = mid -2;
                }
                else
                {
                    return nums[mid];
                }
            }
            else
            {
                if(mid!= 0 && nums[mid] == nums[mid-1])
                {
                    start = mid +1;
                }
                else if(mid!=n-1 && nums[mid] == nums[mid + 1])
                {
                    end = mid -1;
                }
                else
                {
                    return nums[mid];
                }
            }
        }

        return -1;
    }
};