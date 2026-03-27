// https://leetcode.com/problems/target-sum/description/


/*
    Approach: Recursion (Pick + / -)

    Idea:
    - For every number, we have two choices:
        → add it (+)
        → subtract it (-)

    - Try all possible combinations of + and -.
    - Count how many ways result in the target sum.

------------------------------------------------------

    How recursion works:

        At index i:
            sum + nums[i]
            sum - nums[i]

        Move to next index (i+1)

------------------------------------------------------

    Base Case:

        if(index == nums.size())
        {
            if(sum == target)
                counter++;
            return;
        }

    - When all elements are used,
      check if we reached target.

------------------------------------------------------

    Example:

        nums = [1,1], target = 0

        Paths:
            +1 +1 = 2 ❌
            +1 -1 = 0 ✔
            -1 +1 = 0 ✔
            -1 -1 = -2 ❌

        Answer = 2

------------------------------------------------------

    Why This Works:

    - We explore all possible sign assignments.
    - Total possibilities = 2^N

------------------------------------------------------

    Time Complexity: O(2^N)

    - Each element has 2 choices (+ / -)

------------------------------------------------------

    Space Complexity: O(N)

    - Recursion depth = N

------------------------------------------------------

    Note:

    - Uses a global variable (counter) to track result.
    - Can be improved by returning values instead of using global state.
*/
class Solution {
public:
    int counter = 0 ;

    void findTargetSumWaysHelper(vector<int>& nums, int index, int sum, int target)
    {
        
        if(index == nums.size())
        {
            if(sum == target )
            {
                counter++;
            }
            return ;
        }

        // sum = sum + (nums[index]*1);
        findTargetSumWaysHelper(nums, index+1 , sum+ (nums[index]*1), target);
        // sum = sum - (nums[index]*1); 

        // sum = sum + (nums[index] * -1);
        findTargetSumWaysHelper(nums, index+1 , sum+ (nums[index] * -1), target);
        // sum = sum - (nums[index] * -1);

    }

    int findTargetSumWays(vector<int>& nums, int target) {
        int index = 0 ; 
        int sum = 0 ;
        findTargetSumWaysHelper(nums, index, sum, target) ;

        return counter;
    }
};

/*
    Approach: Recursion (Return-based)

    Idea:
    - For every number, choose:
        → +nums[i]
        → -nums[i]

    - Instead of using a global counter,
      each recursive call returns the number of valid ways.

------------------------------------------------------

    How recursion works:

        helper(index, sum)

        → add current number
        → subtract current number

        Total ways = left + right

------------------------------------------------------

    Base Case:

        if(index == nums.size())
            return (sum == target);

    - If sum matches target → return 1 (valid way)
    - Otherwise → return 0

------------------------------------------------------

    Why This Version is Better:

    - No global variable (clean & safe)
    - Pure function → easier to reason about
    - Directly returns count instead of modifying state

------------------------------------------------------

    Example:

        nums = [1,1], target = 0

        helper explores:
            +1 +1 → 2 → 0
            +1 -1 → 0 → 1
            -1 +1 → 0 → 1
            -1 -1 → -2 → 0

        Total = 2

------------------------------------------------------

    Time Complexity: O(2^N)

    - Each element has 2 choices

------------------------------------------------------

    Space Complexity: O(N)

    - Recursion depth
*/
class Solution {
public:
    
    int helper(vector<int>& nums, int index, int sum, int target)
    {
        if(index == nums.size())
        {
            return (sum == target);
        }

        return helper(nums, index+1, sum + nums[index], target) +
            helper(nums, index+1, sum - nums[index], target);
    }

    int findTargetSumWays(vector<int>& nums, int target) {
        return helper(nums, 0, 0, target);
    }
};

//  Note on Optimization:

//     - This solution recomputes the same states multiple times.
//     - Can be optimized using Dynamic Programming (DP)
//       by storing results of (index, sum).

//     - DP reduces complexity significantly compared to O(2^N).