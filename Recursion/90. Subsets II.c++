// https://leetcode.com/problems/subsets-ii/description/



/*
    Approach: Backtracking (For-loop) + Sorting + Skip Duplicates

------------------------------------------------------

    What we are doing:

    - Generate ALL subsets
    - BUT avoid duplicate subsets caused by duplicate numbers

    Steps:
        1. Sort the array
        2. Use backtracking (for-loop style)
        3. Skip duplicates while iterating

------------------------------------------------------

    Why sorting is required:

        nums = [1,2,1]

        After sorting:
            [1,1,2]

        👉 duplicates become adjacent
        👉 easier to skip them

------------------------------------------------------

    Core idea:

        for(i = index → n-1)
            pick sortedNums[i]
            recurse with i+1
            skip duplicates
            backtrack

------------------------------------------------------

    Important line:

        while(i+1 < n && sortedNums[i] == sortedNums[i+1])
            i++;

    👉 This skips duplicate elements at SAME LEVEL

------------------------------------------------------

    Why skipping works (intuition):

        Example: [1,1,2]

        At index = 0:

            i = 0 → pick first 1
                → explore all subsets starting with [1]

            After returning:
                skip second 1

        👉 prevents generating duplicate subsets like:
            [1] again from second 1

------------------------------------------------------

    Very important subtle point:

        Skipping happens AFTER recursion

        temp.push_back(...)
        recurse(...)
        skip duplicates
        temp.pop_back()

    👉 ensures:
        ✔ first occurrence is explored
        ✔ duplicates at same level are ignored

------------------------------------------------------

    Recursion Tree (simplified):

        []
        ├── [1]
        │   ├── [1,1]
        │   │   └── [1,1,2]
        │   └── [1,2]
        ├── (skip duplicate 1)
        └── [2]

------------------------------------------------------

    Why this avoids duplicates:

        - Same value at same recursion level is skipped
        - But deeper levels are allowed

------------------------------------------------------

    Time Complexity: O(2^N * N)

    - Total subsets ≈ 2^N
    - Each subset copied → O(N)

------------------------------------------------------

    Space Complexity: O(N)

    - Recursion depth
    - temp vector

------------------------------------------------------

    Key Takeaway:

    ✔ Sorting + skipping avoids duplicate subsets
    ✔ No need for set (faster)
    ✔ Standard pattern for "with duplicates" problems
*/
class Solution {
public:

    void subsetsWithDupHelper(vector<vector<int>> &ans, vector<int> &sortedNums, vector<int> &temp, int index)
    {
        ans.emplace_back(temp);

        for(int i= index ; i< sortedNums.size() ; i++)
        {
            temp.emplace_back(sortedNums[i]);
            subsetsWithDupHelper(ans, sortedNums, temp , i+1);
            while(i+1 < sortedNums.size() && sortedNums[i] == sortedNums[i+1])
                i++;
            temp.pop_back();
        }  
    }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> sortedNums; 
        for(auto x : nums)
        {
            sortedNums.emplace_back(x);
        }
        sort(sortedNums.begin() , sortedNums.end());

        vector<vector<int>> ans;

        vector<int> temp;
        int index=0;
        subsetsWithDupHelper(ans, sortedNums, temp, index);
        return ans;
    }
};