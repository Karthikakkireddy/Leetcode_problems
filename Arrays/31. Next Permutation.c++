// https://leetcode.com/problems/next-permutation/description/


/*
🔴 Next Permutation

🧠 Idea:
- Traverse from right and find the first position where:

      nums[i] > nums[i-1]

- This means nums[i-1] is the breakpoint.
- Elements to the right of the breakpoint are in decreasing order.

------------------------------------------------------

Steps:

1. Find breakpoint index.

2. From the right side, find the first element
   greater than the breakpoint element.

3. Swap them.

4. Reverse the suffix (elements after breakpoint)
   to get the smallest possible arrangement.

------------------------------------------------------

🧠 Example:

[1,2,3]

Breakpoint:
    2 < 3

Swap:
    2 ↔ 3

[1,3,2]

Reverse suffix:
    [2]

Answer:
    [1,3,2]

------------------------------------------------------

⚠️ Missing Edge Case in Your Code:

If the array is completely decreasing:

    [3,2,1]

No breakpoint exists.

In that case:

    reverse(nums.begin(), nums.end());

Answer:

    [1,2,3]

Your code currently uses:

    breakPointElementIndex

without initializing it when no breakpoint is found.

------------------------------------------------------

⏱️ TC: O(N)

📦 SC: O(1)

------------------------------------------------------

🎯 One line:

"Find the breakpoint, swap with the next greater element on the right, then reverse the suffix."
*/
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size(); 
        int i = n-1;
        int j = n-1;

        int breakPointElementIndex;

        while(i > 0 )
        {
            if(nums[i] > nums[i-1])
            {
                breakPointElementIndex = i-1;
                break;
            }
            i--;
        }

       
        while(i >0 && j >= 0)
        {
            if(nums[breakPointElementIndex] < nums[j])
            {
                swap(nums[breakPointElementIndex], nums[j]);
                break;
            }
            j--;
        }
    
        reverse(nums.begin()+i, nums.end());
    }
};