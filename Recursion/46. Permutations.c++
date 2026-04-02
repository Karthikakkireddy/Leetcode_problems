// https://leetcode.com/problems/permutations/description/


/*
    What this code does:

    - Generates ALL permutations of the given array
    - Uses backtracking + visited array

    ------------------------------------------------------

    Core Idea:

    - At each position, try placing any element
      that has NOT been used yet

    ------------------------------------------------------

    How it works:

    - visited[i] = 1 → element already used
    - visited[i] = 0 → element available

    - temp → current permutation being built

    ------------------------------------------------------

    Logic:

    For every position:

        Loop through all elements:
            If not visited:
                → pick it
                → mark visited
                → recurse
                → backtrack (unmark + remove)

    ------------------------------------------------------

    Base Case:

        if(temp.size() == nums.size())
            → one full permutation formed
            → add to answer

    ------------------------------------------------------

    Dry Run (nums = [1,2]):

        temp = []

        pick 1 → [1]
            pick 2 → [1,2] ✅

        backtrack

        pick 2 → [2]
            pick 1 → [2,1] ✅

    ------------------------------------------------------

    Time Complexity:

        O(N! * N)

    - N! permutations
    - Each permutation takes O(N) to build/copy

    ------------------------------------------------------

    Space Complexity:

        O(N)

    - recursion stack + temp + visited

    ------------------------------------------------------

    Important Observation:

    - visited array ensures:
        → no element is reused in same permutation

    ------------------------------------------------------

    Pattern:

        This is classic "choose any unused element" backtracking

    ------------------------------------------------------

    Note:

    - This is NOT the only way to generate permutations
    - Can also be done using swapping (more optimal space-wise)
*/
class Solution {
public:

    void permuteHelper(vector<vector<int>> &ans , vector<int> &nums , vector<int> &temp, vector<int> &visited)
    {
        if(temp.size() == nums.size())
        {
            ans.emplace_back(temp);
            return ;
        }

        for(int i =0 ; i< nums.size() ; i++)
        {
            if(visited[i] == 0) // not visited
            {
                temp.emplace_back(nums[i]);
                visited[i] = 1 ;
                permuteHelper(ans, nums, temp, visited);
                temp.pop_back();
                visited[i] = 0; 
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> temp ; 
        vector<int> visited(nums.size());
        vector<vector<int>> ans;

        permuteHelper(ans, nums, temp, visited);

        return ans;
    }
};

/*
    🔥 What is different from previous (visited approach)?

    Previous:
        - Used visited[] to track used elements
        - Built permutation using temp

    This version:
        - Uses SWAPPING to fix elements in-place
        - temp is just tracking order (can even be removed)

    👉 No visited array needed
    👉 Uses positions instead of “used tracking”

    ------------------------------------------------------

    🧠 Core Intuition:

    Think like this:

        "At index = i,
         which element should I place here?"

    Instead of asking:
        "Which element is unused?"

    👉 You FIX positions one by one

    ------------------------------------------------------

    🧠 How this idea comes naturally:

    For permutations:

        Position 0 → can be any element
        Position 1 → remaining elements
        Position 2 → remaining...

    So:

        For index i:
            try every element from i → n-1

    👉 Swap that element to position i
    👉 Recursively fix next positions

    ------------------------------------------------------

    ⚙️ Why swapping works:

    - swap(nums[i], nums[index]) puts a candidate at correct position
    - After recursion, we swap back (backtracking)
    - This restores original state

    👉 No duplicates, no missed cases

    ------------------------------------------------------

    🔁 Simple Dry Run (nums = [1,2,3]):

    index = 0

    i = 0:
        swap(0,0) → [1,2,3]
        temp = [1]
            index = 1
            i = 1:
                swap(1,1) → [1,2,3]
                temp = [1,2]
                    index = 2
                    i = 2:
                        swap(2,2) → [1,2,3]
                        temp = [1,2,3] ✅

            i = 2:
                swap(2,1) → [1,3,2]
                temp = [1,3]
                    → [1,3,2] ✅

    i = 1:
        swap(1,0) → [2,1,3]
        → generate [2,1,3], [2,3,1]

    i = 2:
        swap(2,0) → [3,2,1]
        → generate [3,2,1], [3,1,2]

    ------------------------------------------------------

    🔒 Why this guarantees correctness:

    - Every index gets every possible element exactly once
    - Swapping ensures:
        → No element repeats at same position
    - Backtracking restores original state for next choices

    👉 Covers all permutations (N!)

    ------------------------------------------------------

    ⚠️ Important Note:

    - temp is actually unnecessary here
    - nums itself represents current permutation

    Better version:
        just push nums directly into ans

    ------------------------------------------------------

    ⏱ Time Complexity:

        O(N! * N)

        - N! permutations
        - Each takes O(N) to copy

    ------------------------------------------------------

    🧠 Space Complexity:

        O(N)

        - Recursion depth

        (No extra visited array → better than previous)

    ------------------------------------------------------

    🎯 Final Insight:

        visited approach → track "used elements"
        swap approach    → fix "positions"

    👉 Swap approach is more natural + optimal
*/
class Solution {
public:

    void permuteHelper(vector<vector<int>> &ans , vector<int> &nums , vector<int> &temp, int index)
    {
        if(index == nums.size())
        {
            ans.emplace_back(temp);
            return ;
        }

        for(int i =index; i< nums.size() ; i++)
        {
            temp.push_back(nums[i]);
            swap(nums[i], nums[index]);
            permuteHelper(ans, nums, temp, index+1);
            temp.pop_back();
            swap(nums[i], nums[index]);
            
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> temp ; 
        int index = 0 ; 
        vector<vector<int>> ans;

        permuteHelper(ans, nums, temp, index);

        return ans;
    }
};


/*
    🔁 COMPLETE DRY RUN + RECURSION TREE (nums = [1,2,3])

    👉 Important:
    We ONLY push when:
        index == nums.size()  → index == 3

    That’s the "i = 3" moment you were expecting.

    ------------------------------------------------------

    🌳 Recursion Tree (with swaps)

    Start:
        permute([1,2,3], index=0)

    ------------------------------------------------------
    Level 0 (index = 0)

    i = 0:
        swap(0,0) → [1,2,3]
        ↓
        permute([1,2,3], index=1)

            --------------------------------------------------
            Level 1 (index = 1)

            i = 1:
                swap(1,1) → [1,2,3]
                ↓
                permute([1,2,3], index=2)

                    ------------------------------------------
                    Level 2 (index = 2)

                    i = 2:
                        swap(2,2) → [1,2,3]
                        ↓
                        permute([1,2,3], index=3)

                            👉 index == 3 → PUSH [1,2,3] ✅

                    (backtrack)

            i = 2:
                swap(2,1) → [1,3,2]
                ↓
                permute([1,3,2], index=2)

                    i = 2:
                        swap(2,2) → [1,3,2]
                        ↓
                        permute([1,3,2], index=3)

                            👉 PUSH [1,3,2] ✅

                    (backtrack)

    ------------------------------------------------------
    Back to Level 0

    i = 1:
        swap(1,0) → [2,1,3]
        ↓
        permute([2,1,3], index=1)

            i = 1:
                swap(1,1) → [2,1,3]
                ↓
                permute([2,1,3], index=2)

                    i = 2:
                        swap(2,2)
                        ↓
                        index=3 → PUSH [2,1,3] ✅

            i = 2:
                swap(2,1) → [2,3,1]
                ↓
                permute([2,3,1], index=2)

                    i = 2:
                        swap(2,2)
                        ↓
                        index=3 → PUSH [2,3,1] ✅

    ------------------------------------------------------
    Back to Level 0

    i = 2:
        swap(2,0) → [3,2,1]
        ↓
        permute([3,2,1], index=1)

            i = 1:
                swap(1,1) → [3,2,1]
                ↓
                index=3 → PUSH [3,2,1] ✅

            i = 2:
                swap(2,1) → [3,1,2]
                ↓
                index=3 → PUSH [3,1,2] ✅

    ------------------------------------------------------

    ✅ Final Output:
        [1,2,3]
        [1,3,2]
        [2,1,3]
        [2,3,1]
        [3,2,1]
        [3,1,2]

    ------------------------------------------------------

    🧠 Key Insight (IMPORTANT):

    - "i" loop controls WHAT goes at current index
    - "index" tells WHICH position we are fixing

    👉 The actual push happens ONLY when:
        index == n

    👉 That’s why you didn’t see explicit "i=3"
        because "i" stops at n-1

    BUT recursion moves index → n

    ------------------------------------------------------

    🔁 Think like this:

        index = 0 → fix 1st position
        index = 1 → fix 2nd position
        index = 2 → fix 3rd position
        index = 3 → DONE → PUSH

    ------------------------------------------------------

    🎯 Final clarity:

        Loop (i) → chooses element
        Index     → fixes position
        Base case → when ALL positions are fixed

*/
class Solution {
public:

    void permuteHelper(vector<vector<int>> &ans , vector<int> &nums, int index)
    {
        if(index == nums.size())
        {
            ans.emplace_back(nums);
            return ;
        }

        for(int i =index; i< nums.size() ; i++)
        {

            swap(nums[i], nums[index]);
            permuteHelper(ans, nums, index+1);
            swap(nums[i], nums[index]);
            
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {

        int index = 0 ; 
        vector<vector<int>> ans;

        permuteHelper(ans, nums, index);

        return ans;
    }
};