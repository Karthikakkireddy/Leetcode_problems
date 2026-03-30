// https://leetcode.com/problems/combination-sum-ii/description/

/*
    Approach: Brute Force + Backtracking + Set (for deduplication)

------------------------------------------------------

    What we are doing:

    - Try ALL possible subsets (each element used at most once)
    - For each subset:
        → check if sum == target
        → if yes → insert into set (to remove duplicates)

    - We sort the array so duplicates appear together,
      but we are NOT skipping them during recursion

------------------------------------------------------

    Why this is brute force:

    - At each index, we either:
        → pick element
        → move forward

    - Total subsets explored ≈ 2^N

------------------------------------------------------

    Recursion Tree (simplified):

        []
        ├── [1]
        │   ├── [1,2]
        │   │   ├── [1,2,2]
        │   │   └── [1,2]
        │   └── [1]
        ├── [2]
        │   ├── [2,2]
        │   └── [2]
        └── []

    👉 Many duplicate combinations generated ❌
    👉 Set removes duplicates later (costly)

------------------------------------------------------

    Time Complexity (detailed):

    1. Generating subsets:
        → O(2^N)

    2. Each insertion into set:
        → O(K log M)
            where:
                K = size of combination
                M = number of elements in set

    3. Copying vectors into set:
        → O(K)

    --------------------------------------------------

    Total:

        O(2^N * K * log M)

    In worst case:
        → O(2^N * N * log(2^N))
        → O(2^N * N^2)

------------------------------------------------------

    Space Complexity:

    1. Recursion stack:
        → O(N)

    2. Temporary vector:
        → O(N)

    3. Set storage:
        → O(M * K)
        → up to O(2^N * N)

    --------------------------------------------------

    Total:
        O(2^N * N)

------------------------------------------------------

    Why this gives TLE:

    1. Duplicate generation:

        Example:
            candidates = [1,1,1,1,1]

        - You generate MANY identical combinations
        - Set removes them AFTER generation

        👉 wasted computation ❌

------------------------------------------------------

    2. Set overhead:

        - Every insertion:
            → comparison of vectors
            → tree balancing (log M)

        👉 heavy cost

------------------------------------------------------

    3. No pruning for duplicates:

        You are NOT skipping duplicates like:
            if(i > index && arr[i] == arr[i-1]) continue;

        👉 same combinations explored multiple times

------------------------------------------------------

    4. Exponential explosion:

        For N ≈ 20–25:
            → 2^N ≈ millions of calls

        Combined with set operations → TLE

------------------------------------------------------

    When exactly TLE happens:

        - Large N (15+)
        - Many duplicate elements
        - Small target (more valid combinations)

        Example worst case:
            candidates = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
            target = small

------------------------------------------------------

    Key takeaway:

    ✔ Correct but brute force
    ❌ Generates duplicates first, removes later
    ❌ Set makes it slower

    👉 Optimal approach:
        Avoid generating duplicates in the first place
*/
class Solution {
public:
    void combinationSum2Helper(int index, int sum , int target, vector<int> &temp ,vector<int> &candidatesCopy,               set<vector<int>> &res)
    {
        if(sum > target)
        {
            return ;
        }
        if(sum == target)
        {
            res.insert(temp);
            return;
        }

        for(int i= index ; i < candidatesCopy.size() ; i++)
        {

            temp.emplace_back(candidatesCopy[i]);
            combinationSum2Helper(i+1, sum + candidatesCopy[i], target , temp, candidatesCopy, res);
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> candidatesCopy;
        for(auto x : candidates)
        {
            candidatesCopy.emplace_back(x);
        }
        sort(candidatesCopy.begin() , candidatesCopy.end());

        set<vector<int>> res; 
        vector<int>temp ;
        int sum =0 ; 
        int index =0 ;

        combinationSum2Helper(index, sum, target , temp , candidatesCopy, res);

        vector<vector<int>> finalRes;

        for(auto x : res)
        {
            finalRes.emplace_back(x);
        }

        return finalRes;
    }
};
/*
    Approach: Backtracking + Sorting + Skip Duplicates (Optimized)

------------------------------------------------------

    What we are doing:

    - Generate combinations where each element is used ONLY ONCE
    - Avoid duplicates DURING recursion (not after like set)

------------------------------------------------------

    Key improvement over brute force:

    ❌ Before:
        - Generate all combinations
        - Use set to remove duplicates (slow)

    ✔ Now:
        - Sort input
        - Skip duplicates while iterating

------------------------------------------------------

    Core idea:

        for(i = index → n-1)

            pick candidates[i]
            recurse with i+1 (no reuse)

            skip duplicates:
                while(i+1 < n && arr[i] == arr[i+1]) i++

------------------------------------------------------

    Why sorting is important:

        candidates = [1,2,1,2]

        After sorting:
            [1,1,2,2]

        👉 duplicates become adjacent
        👉 easy to skip them

------------------------------------------------------

    How duplicate skipping works:

        Example:
            [1,1,2]

        At index = 0:
            i = 0 → pick first 1

            After recursion:
                skip next identical 1
                (i jumps from 0 → 1)

        👉 prevents generating same combination again

------------------------------------------------------

    Important subtlety:

        Duplicate skipping happens AFTER recursion:

            temp.push_back(...)
            recurse(...)
            while(...) i++
            temp.pop_back()

        👉 ensures:
            - we explore first occurrence
            - skip rest duplicates at same level

------------------------------------------------------

    Recursion Tree (simplified):

        []
        ├── 1
        │   ├── 1
        │   │   └── ...
        │   └── 2
        ├── (skip duplicate 1)
        └── 2

        👉 duplicate branches removed early

------------------------------------------------------

    Pruning:

        if(sum > target)
            return;

        👉 avoids unnecessary deeper calls

------------------------------------------------------

    Time Complexity:

        - Worst case still exponential
            O(2^N)

        BUT much faster than brute force because:
            ✔ duplicates are not generated
            ✔ no set overhead

------------------------------------------------------

    Space Complexity:

        O(N) → recursion depth + temp vector

        Result storage:
            depends on number of valid combinations

------------------------------------------------------

    Why this avoids TLE:

        ✔ No duplicate generation
        ✔ No set (log factor removed)
        ✔ Pruning reduces recursion

------------------------------------------------------

    Key takeaway:

        ✔ Generate ONLY unique combinations
        ✔ Skip duplicates early (not later)
        ✔ This is the expected optimal backtracking solution
*/
class Solution {
public:
    void combinationSum2Helper(int index, int sum , int target, vector<int> &temp ,vector<int> &candidatesCopy,               vector<vector<int>> &res)
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

        for(int i= index ; i < candidatesCopy.size() ; i++)
        {

            
            temp.emplace_back(candidatesCopy[i]);
            combinationSum2Helper(i+1, sum + candidatesCopy[i], target , temp, candidatesCopy, res);
            while(i+1 < candidatesCopy.size() &&  candidatesCopy[i] == candidatesCopy[i+1])
            {
                i++;
            }
            temp.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> candidatesCopy;
        for(auto x : candidates)
        {
            candidatesCopy.emplace_back(x);
        }
        sort(candidatesCopy.begin() , candidatesCopy.end());

        vector<vector<int>> res; 
        vector<int>temp ;
        int sum =0 ; 
        int index =0 ;

        combinationSum2Helper(index, sum, target , temp , candidatesCopy, res);


        return res;
    }
};