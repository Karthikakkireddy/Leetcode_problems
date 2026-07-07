// https://leetcode.com/problems/find-peak-element/description/

/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search to find a peak element.
        - Compare the middle element with its neighbors.
        - If a neighboring element is larger, a peak must
          exist in that direction.
        - Otherwise, the current element is a peak.

    -------------------------------------------------------

    Why This Works

        If:

            nums[mid] < nums[mid - 1]

            - The left neighbor is larger.
            - A peak must exist in the left half.
            - Search the left half.

        Else If:

            nums[mid] < nums[mid + 1]

            - The right neighbor is larger.
            - A peak must exist in the right half.
            - Search the right half.

        Else:

            - nums[mid] is greater than or equal to both
              neighbors.
            - Therefore, it is a peak element.

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

        "Move toward the larger neighbor until a peak element is found using Binary Search."
*/
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int start =0 ; 
        int end = nums.size() -1 ;

        while(start <= end)
        {
            int mid = (start + end) /2 ;

            if(mid!=0 && nums[mid] < nums[mid-1])
            {
                end = mid-1;
            }
            else if(mid!= nums.size()-1 && nums[mid] < nums[mid+1])
            {
                start = mid +1;
            }
            else
            {
                return mid;
            }
        }

        return -1;
    }
};