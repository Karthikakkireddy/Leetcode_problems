// https://leetcode.com/problems/combination-sum-iii/description/

/*
    Approach: Backtracking (Combinations from 1 to 9)

------------------------------------------------------

    What we are doing:

    - Choose exactly k numbers from [1...9]
    - Such that their sum = n
    - Each number can be used ONLY once

------------------------------------------------------

    How recursion works:

        combinationSum3Helper(index, sum, temp)

        for(i = index → 9)
            pick i
            recurse with i+1 (no reuse)
            backtrack

------------------------------------------------------

    Base Case:

        if(temp.size() == k)
        {
            if(sum == n)
                add to answer
            return;
        }

    👉 Once we pick k elements:
        - check sum
        - stop further recursion

------------------------------------------------------

    Pruning:

        if(sum > n)
            return;

    👉 If sum exceeds n:
        - no need to continue
        - saves time

------------------------------------------------------

    Example: k = 3, n = 7

        []
        ├── [1]
        │   ├── [1,2]
        │   │   ├── [1,2,3] → sum=6 ❌
        │   │   └── [1,2,4] → sum=7 ✔
        │   └── [1,3]
        │       └── [1,3,3+] (invalid)
        └── [2]
            └── ...

------------------------------------------------------

    Important Constraints Handling:

    ✔ Numbers from 1 to 9 only
    ✔ No repetition → i+1
    ✔ Exactly k elements → size check

------------------------------------------------------

    Why no duplicates:

        - We move forward (i+1)
        - No element reused
        - No permutations like [2,1]

------------------------------------------------------

    Time Complexity:

        Roughly O(C(9, k))

        - We are choosing k elements from 9
        - Much smaller than 2^N

------------------------------------------------------

    Space Complexity: O(k)

        - Recursion depth ≤ k
        - temp stores at most k elements

------------------------------------------------------

    Key Takeaway:

    ✔ Classic combination problem with constraints
    ✔ Backtracking + pruning makes it efficient
    ✔ Very clean template for "choose k elements" problems
*/
class Solution {
public:
    void combinationSum3Helper(vector<vector<int>> & ans, vector<int> &temp , int sum, int index,
                                int k , int n)
    {
        if(temp.size() == k)
        {
            if(sum == n)
            {
                ans.emplace_back(temp);
            }
            return ;
        }
        if(sum > n)
            return ;
        
        for(int i = index ; i <=9 ; i++)
        {
            temp.emplace_back(i); 
            combinationSum3Helper(ans, temp, sum + i, i+1, k , n );
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> temp; 
        int index = 1; 
        int sum = 0 ;  
        combinationSum3Helper(ans, temp, sum , index, k , n);

        return ans;

    }
};