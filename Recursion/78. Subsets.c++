// https://leetcode.com/problems/subsets/description/

/*
    Approach: Recursion (Pick / Not Pick)

------------------------------------------------------

    What we are doing:

    - For each element, we have 2 choices:
        → include it in subset
        → exclude it

    - This naturally forms a binary decision tree

------------------------------------------------------

    How recursion works:

        subsetsHelper(index)

            1. Pick nums[index]
            2. Do NOT pick nums[index]

------------------------------------------------------

    Base Case:

        if(index == nums.size())
        {
            add current subset (temp) to result
            return;
        }

    - When all elements are processed,
      temp represents one valid subset

------------------------------------------------------

    Recursion Tree (example: [1,2]):

        []
        ├── [1]
        │   ├── [1,2]
        │   └── [1]
        └── []
            ├── [2]
            └── []

        Result:
            [], [1], [2], [1,2]

------------------------------------------------------

    Why This Works:

    - Every element has 2 choices → total subsets = 2^N
    - We explore all possible combinations

------------------------------------------------------

    Time Complexity: O(2^N * N)

    - 2^N subsets
    - Each subset takes O(N) to copy into result

------------------------------------------------------

    Space Complexity: O(N)

    - Recursion depth = N
    - temp vector size ≤ N

    (Result storage not counted in auxiliary space)

------------------------------------------------------

    Key Takeaway:

    ✔ Classic pick / not-pick pattern
    ✔ Generates ALL subsets
    ✔ Foundation for many backtracking problems
*/
class Solution {
public:

    void subsetsHelper(vector<vector<int>> &v, vector<int> &nums, vector<int> &temp, int index)
    {
        if(index == nums.size())
        {
            v.emplace_back(temp);
            return;
        }

        temp.emplace_back(nums[index]);
        subsetsHelper(v, nums, temp, index+1);
        temp.pop_back();
        subsetsHelper(v, nums, temp, index+1);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        int index = 0 ; 
        vector<vector<int>> v ;
        vector<int> temp ;

        subsetsHelper(v, nums, temp, index);

        return v;
    }
};

/*
    Approach: Backtracking (For-loop based)

------------------------------------------------------

    What we are doing:

    - Instead of pick / not-pick,
      we iteratively CHOOSE the next element.

    - At every recursion level:
        → current "temp" is already a valid subset
        → we add it immediately

------------------------------------------------------

    Key Line:

        v.emplace_back(temp);

    - This ensures:
        ✔ empty subset is included
        ✔ all intermediate subsets are captured

------------------------------------------------------

    How recursion works:

        subsetsHelper(index)

        for(i = index → n-1)
            pick nums[i]
            recurse with i+1
            backtrack

------------------------------------------------------

    Example: nums = [1,2,3]

        []
        ├── [1]
        │   ├── [1,2]
        │   │   └── [1,2,3]
        │   └── [1,3]
        ├── [2]
        │   └── [2,3]
        └── [3]

------------------------------------------------------

    Why this works:

    - At each level, we decide:
        "which element to pick NEXT"

    - No need for explicit "not pick"
        → skipping is handled by moving i forward

------------------------------------------------------

    Difference from Pick / Not Pick:

        Old:
            binary decision tree (2 branches)

        New:
            loop over choices (cleaner tree)

------------------------------------------------------

    Time Complexity: O(2^N * N)

    - Total subsets = 2^N
    - Copying each subset takes O(N)

------------------------------------------------------

    Space Complexity: O(N)

    - Recursion depth = N
    - temp vector size ≤ N

------------------------------------------------------

    Key Takeaway:

    ✔ More intuitive for combinations/subsets
    ✔ No explicit base case needed
    ✔ Standard backtracking template
*/
class Solution {
public:

    void subsetsHelper(vector<vector<int>> &v, vector<int> &nums, vector<int> &temp, int index)
    {
        v.emplace_back(temp); // add current subset

        for(int i = index; i < nums.size(); i++)
        {
            temp.emplace_back(nums[i]);          // pick
            subsetsHelper(v, nums, temp, i + 1);      // move forward
            temp.pop_back();                     // backtrack
        }
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        int index = 0 ; 
        vector<vector<int>> v ;
        vector<int> temp ;

        subsetsHelper(v, nums, temp, index);

        return v;
    }
};