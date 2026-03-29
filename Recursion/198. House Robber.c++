// https://leetcode.com/problems/house-robber/description/


/*
    What we are trying to do:

    - At each index, we decide to rob the current house.
    - If we rob current house (index), we cannot rob index+1.

    So next possible choices:
        → index + 2  (skip one house)
        → index + 3  (skip two houses)

    Why index + 3?
        - Idea was: maybe skipping one extra house gives better result
        - So we try both possibilities and take max

    Also in main:
        → start from index 0 OR index 1
        (to cover both starting possibilities)

------------------------------------------------------

    Why this leads to TLE:

    - We are recomputing the same subproblems multiple times.
    - There is NO memoization.

    Recursion Tree (example: n = 5)

        rob(0)
        ├── rob(2)
        │   ├── rob(4)
        │   └── rob(5)
        └── rob(3)
            ├── rob(5)
            └── rob(6)

        rob(1)
        ├── rob(3)   ← repeated call ❌
        └── rob(4)

    Key observation:
        rob(3), rob(4), rob(5) are called multiple times.

    This duplication grows exponentially as n increases.

------------------------------------------------------

    Root cause of inefficiency:

    - Overlapping subproblems
    - Extra branching due to:
            index + 2
            index + 3

    - index+3 is redundant:
        skipping index+2 already covers that case indirectly

------------------------------------------------------

    Time Complexity: O(2^N)

    - Each index branches into multiple recursive calls
    - Exponential growth of recursion tree

------------------------------------------------------

    Space Complexity: O(N)

    - Maximum recursion depth is N
*/
class Solution {
public:

    int robHelper(vector<int>& nums, int index)
    {
        if(index >= nums.size())
            return 0;
        if(index == nums.size() -1  || index == nums.size()-2)
        {
            return nums[index];
        }
        int left = nums[index] + robHelper(nums, index + 2 );
        int right = nums[index] + robHelper(nums, index + 3 ); 


        return max(left, right);
        
    }
    int rob(vector<int>& nums) {

        return max(robHelper(nums,0 ),
                    robHelper(nums,1));
    }
};
/*
    What changed compared to previous solution:

    - Earlier:
        Pure recursion → recomputed same subproblems many times

    - Now:
        Added DP (memoization using dp array)
        → store result for each index
        → reuse it instead of recomputing

------------------------------------------------------

    Recursion Tree Comparison

    Previous (without DP):

        rob(0)
        ├── rob(2)
        │   ├── rob(4)
        │   └── rob(5)
        └── rob(3)
            ├── rob(5)
            └── rob(6)

        rob(1)
        ├── rob(3)   ← repeated ❌
        └── rob(4)   ← repeated ❌

    👉 Same nodes like rob(3), rob(4), rob(5)
       are recomputed multiple times → exponential growth

------------------------------------------------------

    Current (with DP):

        rob(0)
        ├── rob(2)
        │   ├── rob(4)
        │   └── rob(5)
        └── rob(3)

        rob(1)
        ├── rob(3)   ← reused from dp ✅
        └── rob(4)   ← reused from dp ✅

    👉 Each index is computed ONLY once
       Later calls directly return dp[index]

------------------------------------------------------

    Why this is better:

    ✔ Eliminates repeated computations
    ✔ Reduces exponential recursion to linear
    ✔ Uses memory to trade for speed
------------------------------------------------------

    What DP (Memoization) is doing here:

    - dp[index] stores:
        "Maximum money we can rob starting from this index"

    - First time we compute robHelper(index):
        → we calculate it using recursion
        → store result in dp[index]

    - Next time we reach same index:
        → instead of recomputing whole subtree
        → we directly return dp[index]

------------------------------------------------------

    How DP reduces work (important intuition)

    Without DP:

        rob(0)
        ├── rob(2)
        │   ├── rob(4)
        │   └── rob(5)
        └── rob(3)
            ├── rob(5)
            └── rob(6)

        rob(1)
        ├── rob(3)   ← recomputed ❌
        └── rob(4)   ← recomputed ❌

    👉 Same indices appear multiple times
    👉 Work grows exponentially (2^N)

------------------------------------------------------

    With DP:

        rob(0)
        ├── rob(2)
        │   ├── rob(4)
        │   └── rob(5)
        └── rob(3)

        rob(1)
        ├── rob(3)   ← reuse dp[3] ✅
        └── rob(4)   ← reuse dp[4] ✅

    👉 Each index is solved ONCE
    👉 All future calls reuse stored result

------------------------------------------------------

    So ideally:

        Time → O(N)
        Because only N states exist (one per index)

------------------------------------------------------

    BUT why is this still giving TLE?

    -----------------------------------
    1. dp initialization bug (CRITICAL)

        vector<int> dp(nums.size());

        → default values = 0

        Your check:
            if(dp[index] != 0)

        Problem:
            0 can be a VALID answer

        Example:
            nums = [0,0,0]

        dp[index] = 0 means:
            ❌ not computed
            OR
            ✔ computed and result is 0

        → You can't distinguish

        👉 So recursion recomputes those states again
        👉 DP becomes ineffective
        👉 Leads to TLE

------------------------------------------------------

    2. Extra branching (index + 3)

        You are doing:
            left  = rob(index+2)
            right = rob(index+3)

        But logically:

            rob(index) =
                max(
                    nums[index] + rob(index+2),
                    rob(index+1)
                )

        Your approach:
            creates more branches than needed

        👉 More recursive calls than optimal
        👉 Slower execution

------------------------------------------------------

    3. Two starting calls

        rob(0) and rob(1)

        → both generate overlapping subtrees

        Even with DP, due to bug above,
        reuse is not perfect

------------------------------------------------------

    Summary:

    DP is supposed to:
        ✔ eliminate repeated work
        ✔ reduce time to O(N)

    But here it fails because:
        ❌ dp uses 0 as "not computed"
        ❌ causes recomputation
        ❌ extra branching increases calls

------------------------------------------------------

    Fix idea (conceptual):

        - Use dp initialized with -1 (or some invalid value)
        - Avoid index+3 branching
*/
class Solution {
public:

    int robHelper(vector<int>& nums, int index, vector<int> &dp)
    {
        
        
        if(dp[index] != 0 )
        {
            return dp[index];
        }
        if(index == nums.size() -1  || index == nums.size()-2)
        {
            dp[index] = nums[index];
            return nums[index];
        }

        
        int left = 0;
        int right =0;

        if(index+2 < nums.size())
            left = nums[index] + robHelper(nums, index + 2, dp );
        if(index+3 < nums.size())
            right = nums[index] + robHelper(nums, index + 3, dp ); 

        if(dp[index] == 0 )
        {
            return dp[index] = max(left, right);
        }
        return dp[index];
        
    }
    int rob(vector<int>& nums) {
        if(nums.size() == 1 ) 
            return nums[0];
        vector<int> dp(nums.size());
        return max(robHelper(nums,0,  dp ),
                    robHelper(nums,1, dp));
    }
};

/*
    ------------------------------------------------------

    Why dp[index] = -1 fix matters:

        - Earlier dp used 0 → ambiguous:
            0 could mean:
                • not computed
                • computed result = 0

        - Now:
            -1 clearly means "not computed"

        👉 memoization works correctly now

------------------------------------------------------

    Time Complexity: O(N)

    - Each index is solved once
    - dp ensures no repeated recursion

------------------------------------------------------

    Space Complexity: O(N)

    - dp array → O(N)
    - recursion stack → O(N)

------------------------------------------------------

    Still not ideal (important insight):

    1. Extra branching:

        You are doing:
            index+2 and index+3

        But optimal recurrence is:
            rob(index) =
                max(
                    nums[index] + rob(index+2),
                    rob(index+1)
                )

        👉 index+3 is redundant
        👉 increases recursion calls unnecessarily

------------------------------------------------------

    2. Two starting calls:

        rob(0) and rob(1)

        → overlap exists but dp handles it

------------------------------------------------------

    Final takeaway:

    ✔ Much better than previous (no repeated work)
    ✔ Correct DP usage now
    ⚠ Slightly inefficient structure due to extra branching
*/
class Solution {
public:

    int robHelper(vector<int>& nums, int index, vector<int> &dp)
    {
        
        
        if(dp[index] != -1 )
        {
            return dp[index];
        }
        if(index == nums.size() -1  || index == nums.size()-2)
        {
            dp[index] = nums[index];
            return nums[index];
        }

        
        int left = 0;
        int right =0;

        if(index+2 < nums.size())
            left = nums[index] + robHelper(nums, index + 2, dp );
        if(index+3 < nums.size())
            right = nums[index] + robHelper(nums, index + 3, dp ); 

        if(dp[index] == -1)
        {
            dp[index] = max(left, right);
        }
        return dp[index];
        
    }
    int rob(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        vector<int> dp(nums.size(), -1);
        return max(robHelper(nums,0,  dp ),
                    robHelper(nums,1, dp));
    }
};

/*
    Why "index+3" is redundant (with intuition + recursion tree)

------------------------------------------------------

    What your code is doing:

        rob(index) =
            max(
                nums[index] + rob(index+2),
                nums[index] + rob(index+3)
            )

    Meaning:
        - Take current house
        - Then either go to index+2 or index+3

------------------------------------------------------

    What the correct logic is:

        rob(index) =
            max(
                nums[index] + rob(index+2),   // take current
                rob(index+1)                 // skip current
            )

------------------------------------------------------

    Key Insight:

    "index+3" is already covered inside rob(index+1)

------------------------------------------------------

    Example:

        nums = [2, 7, 9, 3, 1]

------------------------------------------------------

    Your recursion (simplified):

        rob(0)
        ├── 2 + rob(2)
        │       ├── 9 + rob(4)
        │       └── 9 + rob(5)
        │
        └── 2 + rob(3)
                ├── 3 + rob(5)
                └── 3 + rob(6)

------------------------------------------------------

    Correct recursion:

        rob(0)
        ├── take:
        │     2 + rob(2)
        │
        └── skip:
              rob(1)

------------------------------------------------------

    Expand rob(1):

        rob(1)
        ├── 7 + rob(3)
        └── rob(2)

------------------------------------------------------

    Now notice something important:

        In rob(1), we already explore:
            rob(3)

        Which corresponds to your:
            index+3 from index 0

------------------------------------------------------

    So:

        Your:
            nums[0] + rob(3)

        is already explored via:
            rob(1) → rob(3)

------------------------------------------------------

    Visual overlap:

        Your tree:

            rob(0)
            ├── rob(2)
            └── rob(3)

        Correct tree:

            rob(0)
            ├── rob(2)
            └── rob(1)
                    └── rob(3)   ← already included

------------------------------------------------------

    Why correct recurrence works:

        At each index:
            - Either you take current → jump to index+2
            - Or skip current → go to index+1

        Skipping handles ALL future possibilities,
        including index+2, index+3, index+4, etc.

------------------------------------------------------

    Intuition:

        "Skip" is more powerful than "jump"

        - skip → explores entire future
        - jump (index+3) → explores only one path

------------------------------------------------------

    Final takeaway:

        ✔ index+3 is redundant
        ✔ rob(index+1) already covers that path
        ✔ adding index+3 only increases recursion branches
        ✔ no extra benefit, just slower execution
*/

/*
    Approach: Recursion + Memoization (Top-Down DP)

    What we are doing:

    - At each index, we have 2 choices:
        1. Take current house → nums[index] + rob(index+2)
        2. Skip current house → rob(index+1)

    - We choose the maximum of these two options.

------------------------------------------------------

    Why this recurrence works:

        rob(index) =
            max(
                nums[index] + rob(index+2),   // take
                rob(index+1)                 // skip
            )

    - If we take current → we MUST skip next → jump to index+2
    - If we skip current → we explore all future options via index+1

    👉 No need for index+3 anymore (already covered via skip path)

------------------------------------------------------

    Recursion Tree (without DP):

        rob(0)
        ├── take → nums[0] + rob(2)
        │           ├── rob(4)
        │           └── rob(3)
        │
        └── skip → rob(1)
                    ├── rob(3)
                    └── rob(2)

    👉 rob(2), rob(3), rob(4) repeat multiple times ❌

------------------------------------------------------

    With DP (Memoization):

        rob(0)
        ├── rob(2)
        │   ├── rob(4)
        │   └── rob(3)
        │
        └── rob(1)
            ├── rob(3)   ← reused from dp ✅
            └── rob(2)   ← reused from dp ✅

    👉 Each index computed only once

------------------------------------------------------

    Base Cases:

        if(index >= nums.size())
            return 0

        if(index == last index)
            return nums[index]

------------------------------------------------------

    Why DP works:

    - Overlapping subproblems:
        rob(2), rob(3) etc repeat

    - dp[index] stores result so:
        → no recomputation
        → huge speed improvement

------------------------------------------------------

    Time Complexity: O(N)

    - Each index is computed once
    - DP eliminates repeated calls

------------------------------------------------------

    Space Complexity: O(N)

    - dp array → O(N)
    - recursion stack → O(N)

------------------------------------------------------

    Final Takeaway:

    ✔ Correct recurrence (take vs skip)
    ✔ No unnecessary branching
    ✔ Memoization removes exponential blow-up
    ✔ This is the expected optimal recursive solution
*/
class Solution {
public:

    int robHelper(vector<int>& nums, int index, vector<int> &dp)
    {
        
        if(index >= nums.size())
        {
            return 0;
        }
        if(dp[index] != -1 )
        {
            return dp[index];
        }
        if(index == nums.size() -1)
        {
            dp[index] = nums[index];
            return nums[index];
        }
        int maxSumTillIndex = max ( nums[index] + robHelper(nums, index+2, dp),
                                    robHelper(nums,index+1, dp));
        if(dp[index] == -1) 
        {
            dp[index] = maxSumTillIndex;
        }
        return dp[index];
        
    }
    int rob(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0];
        vector<int> dp(nums.size(), -1);
        return robHelper(nums,0, dp );
    }
};