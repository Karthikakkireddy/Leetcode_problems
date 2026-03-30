// https://leetcode.com/problems/combination-sum/description/


/*
    Approach: Backtracking (Pick same element multiple times)

    What we are doing:

    - We try to build combinations whose sum = target
    - At each step, we choose a number and keep adding it

------------------------------------------------------

    Key idea:

        for(i = index → n-1)
            pick candidates[i]
            recurse with SAME i

    Why SAME i?

        → Because we are allowed to reuse elements
        → So we don’t move to i+1

------------------------------------------------------

    Flow (example):

        candidates = [2,3,6,7], target = 7

        Start:
            []

        Pick 2:
            [2]
            → [2,2]
            → [2,2,2]
            → [2,2,2,2] ❌ (sum > target → stop)

        Backtrack:
            → [2,2,3] ✔ (sum = 7)

        Try 3:
            [3]
            → [3,3] → 6
            → [3,3,3] ❌

        Try 7:
            [7] ✔

------------------------------------------------------

    Why no duplicates?

        - We always start loop from "index"
        - This ensures:
            ✔ combinations are built in non-decreasing order
            ✔ no permutations like [2,3] and [3,2]

------------------------------------------------------

    Pruning (important):

        if(sum > target)
            return;

        → stops unnecessary recursion early

------------------------------------------------------

    Recursion Tree (simplified):

        []
        ├── 2
        │   ├── 2
        │   │   ├── 2
        │   │   │   └── ...
        │   │   └── 3
        │   └── 3
        ├── 3
        │   └── 3
        ├── 6
        └── 7

------------------------------------------------------

    Time Complexity:

        Exponential (roughly O(2^target * k))

        - Because we try many combinations
        - Exact depends on input + pruning

------------------------------------------------------

    Space Complexity: O(target)

        - Recursion depth depends on how many elements
          we add to reach target

------------------------------------------------------

    Key Takeaways:

    ✔ Use index to avoid duplicates
    ✔ Use same index for reuse
    ✔ Backtracking = choose → explore → undo
    ✔ Pruning improves performance
*/
class Solution {
public:
    void combinationSumHelper(int index, int sum , int target, vector<int> &temp ,vector<int> &candidates,               vector<vector<int>> &res)
    {
        if(sum > target)
        {
            return ;
        }
        if(sum == target)
        {
            res.emplace_back(temp);
            return;
        }

        for(int i= index ; i < candidates.size() ; i++)
        {

            temp.emplace_back(candidates[i]);
            combinationSumHelper(i, sum + candidates[i], target , temp, candidates, res);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res; 
        vector<int>temp ;
        int sum =0 ; 
        int index =0 ;
        combinationSumHelper(index, sum, target , temp , candidates, res);
        return res;
    }
};