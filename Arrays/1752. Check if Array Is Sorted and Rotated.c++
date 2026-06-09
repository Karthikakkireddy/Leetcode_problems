// https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/description/


/*
🔴 Check if Array is Sorted and Rotated

🧠 Idea:

A sorted rotated array can have
AT MOST ONE "drop"

Example:
    [3,4,5,1,2]

Drops:
    5 > 1  ✅ (one drop)

Valid

------------------------------------------------------

🧠 What is a "drop"?

When:

    nums[i-1] > nums[i]

Example:

    [1,2,5,3,4]

Here:

    5 > 3

👉 One drop found

------------------------------------------------------

Logic:

1. Traverse array
2. Count drops

    current > nums[i]

3. If more than one drop:
       return false

------------------------------------------------------

Final Check:

If one drop exists:

    nums[0] >= nums[n-1]

must be true

Why?

Example:

    [3,4,5,1,2]
     ↑       ↑

    3 >= 2 ✅

Valid rotation

------------------------------------------------------

Invalid Example:

    [1,2,5,3,4]

Drop:
    5 > 3

But:

    1 < 4 ❌

Not a valid rotated sorted array

------------------------------------------------------

⏱️ Time Complexity:

    O(N)

------------------------------------------------------

📦 Space Complexity:

    O(1)

------------------------------------------------------

🎯 One line:

"Sorted rotated array can have at most one drop, and first element must be >= last element if a drop exists."
*/
class Solution {
public:
    bool check(vector<int>& nums) {
        int flag = 0 ;

        int current = nums[0];

        for(int i = 1 ; i< nums.size() ; i++)
        {
            if(current > nums[i])
            {
                if(flag == 1 )
                    return false;
                flag = 1; 
            }
            current = nums[i];
        }

        if(flag == 1 && nums[0] < nums[nums.size()-1] )
        {
            return false;
        }
        return true; 
    }
};