// https://leetcode.com/problems/combinations/description/


/*
    Approach: Backtracking (Pick / Not Pick)

    Idea:
    - For every number from 1 to n, we have two choices:
        → include it in the current combination
        → skip it

    - We explore all possibilities and collect only those
      where size == k.

------------------------------------------------------

    How recursion works:

        combineHelper(i)

        At each step:
            1. Pick i  → add to vector
            2. Don't pick i → skip

        Move to next number (i+1)

------------------------------------------------------

    Base Case:

        if(i > n)
            check if size == k → add to result

------------------------------------------------------

    Example:

        n = 3, k = 2

        Possible paths:
            [1,2] ✔
            [1,3] ✔
            [2,3] ✔
            others ignored

------------------------------------------------------

    Why This Works

    - We explore all subsets (2^n possibilities)
    - Only valid combinations of size k are stored

------------------------------------------------------

    Time Complexity: O(2^N)

    - Every number has 2 choices → pick / not pick

    Space Complexity: O(N)

    - Recursion depth up to N
*/
class Solution {
public:
    void combineHelper(vector<vector<int>> &res,
                        vector<int> &v, 
                        int i,
                        int n,
                        int k)
    {
       
        if(i > n)
        {
            if(v.size() == k)
            {
                res.emplace_back(v);
            }
            return;
        }
        v.emplace_back(i);
        combineHelper(res, v, i+1, n , k);
        v.pop_back();
        combineHelper(res, v, i+1, n , k);
    }
    vector<vector<int>> combine(int n, int k) {
        
        vector<vector<int>> res;
        vector<int> temp;
        combineHelper(res, temp , 1,  n, k);
        return res;
    }
};
/*
    Improvement over Previous Version:

    - Earlier approach:
        • Generated ALL subsets (2^N)
        • Then filtered only those of size k
        → Lots of unnecessary work

------------------------------------------------------

    What’s better in this version:

    1. Build only required combinations

        - Instead of checking size at the end,
          we track "k" (how many more elements we need).

        - When k == 0:
              we already have a valid combination
              → add immediately and stop further recursion

        ✔ Avoids exploring unnecessary branches

------------------------------------------------------

    2. Early stopping (pruning)

        - If i > n → stop
        - If k == 0 → stop immediately

        ✔ Prevents extra recursive calls

------------------------------------------------------

    3. More efficient recursion

        Previous:
            Explore full tree → filter later

        Now:
            Only explore paths that can lead to valid answers

------------------------------------------------------

    Key difference:

        Old approach:
            Work done ≈ O(2^N)

        New approach:
            Work done ≈ O(C(N, K))

        (Only valid combinations are generated)

------------------------------------------------------

    Final takeaway:

        ✔ Less unnecessary work
        ✔ Faster in practice
        ✔ Cleaner logic (goal-driven recursion)
*/
class Solution {
public:
    void combineHelper(vector<vector<int>> &res,
                        vector<int> &v, 
                        int i,
                        int n,
                        int k)
    {
       
      
            
        if(k==0)
        {
            res.emplace_back(v);
            return;
        }
        if(i > n)   
            return;

        v.emplace_back(i);
     
        combineHelper(res, v, i+1, n , k-1);

        v.pop_back();

        combineHelper(res, v, i+1, n , k);


    }
    vector<vector<int>> combine(int n, int k) {
        
        vector<vector<int>> res;
        vector<int> temp;
        combineHelper(res, temp , 1,  n, k);
        return res;
    }
};

/*
    Improvement over Previous Version (Pick / Not Pick)

    Previous Approach:
    - Used binary recursion:
        → take element
        → skip element
    - This creates a recursion tree of size ~2^N
    - Many unnecessary paths were explored and later discarded

------------------------------------------------------

    Current Approach: Loop-based Backtracking

    Idea:
    - At each step, choose ONE element from range [i ... n]
    - Then recursively choose remaining (k-1) elements

    Instead of:
        "take or skip"
    we do:
        "choose next valid element"

------------------------------------------------------

    Key Difference

    Old:
        combine(i)
            → take i
            → skip i

    New:
        for(j = i → n)
            → pick j
            → recurse

    ✔ Removes unnecessary "skip" calls
    ✔ Directly builds valid combinations

------------------------------------------------------

    Why This Is Better

    1. No redundant recursion
        - Old approach explores invalid paths
        - New approach only explores valid ones

    2. Matches problem definition
        - "Choose k elements from [1...n]"
        - This approach literally builds combinations step-by-step

    3. Cleaner recursion tree

        Old:
            binary tree (many useless branches)

        New:
            controlled branching using loop

------------------------------------------------------

    Efficiency

    Old approach:
        O(2^N)

    New approach:
        O(C(N, K))

    - Only valid combinations are generated

------------------------------------------------------

    Important Property

        combineHelper(res, v, j+1, n, k-1)

    - Ensures:
        ✔ No duplicates
        ✔ Increasing order
        ✔ No permutations like [2,1]

------------------------------------------------------

    (Optional Optimization)

        for(j = i; j <= n - k + 1; j++)

    - Prunes unnecessary iterations
    - If remaining elements < k → stop early

------------------------------------------------------

    Final Takeaway

    ✔ More efficient than previous version
    ✔ Cleaner logic
    ✔ Standard backtracking pattern for combinations
*/
class Solution {
public:
    void combineHelper(vector<vector<int>> &res,
                        vector<int> &v, 
                        int i,
                        int n,
                        int k)
    {
       
      
            
        if(k==0)
        {
            res.emplace_back(v);
            return;
        }
        // if(i > n)   
        //     return;
        for(int j=i ; j<=n ; j++)
        {
              v.emplace_back(j);
     
                combineHelper(res, v, j+1, n , k-1);

                v.pop_back();
        }


    }
    vector<vector<int>> combine(int n, int k) {
        
        vector<vector<int>> res;
        vector<int> temp;
        combineHelper(res, temp , 1,  n, k);
        return res;
    }
};