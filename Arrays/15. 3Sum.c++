// https://leetcode.com/problems/3sum/description/

/*
    🔴 Brute Force

    🧠 Idea:
        - Sort the array so duplicate triplets can be skipped easily.
        - Generate every possible triplet using three nested loops.
        - If the sum of a triplet is 0, add it to the answer.
        - Skip duplicate values for i, j and k to avoid duplicate triplets.

    -------------------------------------------------------

    Why This Works

        - Three nested loops generate every possible triplet.
        - Sorting allows us to skip repeated values, ensuring
          only unique triplets are added to the result.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Sorting:
            O(N log N)

        Three Nested Loops:
            O(N³)

        Total:
            O(N³)
            (Sorting is dominated by N³.)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Answer Vector:
            Depends on the number of valid triplets.

        Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Generate every unique triplet and keep those whose sum is zero."
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
        sort(nums.begin(), nums.end());
        vector<vector<int>>v;
        int n = nums.size(); 
        for(int i =0 ; i< n-2; i++)
        {
            if(i==0 || nums[i] != nums[i-1] )
            {
                for(int j= i+1 ; j<n-1 ; j++)
                {
                    if(j == i+1 ||  nums[j] != nums[j-1])
                    {
                        for(int k = j+1; k < n ; k++)
                        {

                            if((k==j+1 || nums[k] != nums[k-1]) && nums[i] + nums[j] + nums[k] == 0)
                            {
                                v.push_back({nums[i],nums[j],nums[k]});
                            }
                        }
                    }
                }
            }
        }

        return v;
    }
};


/*
    🔴 Better - 1

    🧠 Idea:
        - Fix one element nums[i].
        - Use a hash set to solve the remaining Two Sum problem.
        - Whenever a valid triplet is found:
            - Sort the triplet.
            - Insert it into a set to automatically remove duplicates.
        - Convert the set into the answer vector.

    -------------------------------------------------------

    Why This Works

        - Fixing one element reduces the problem to Two Sum.
        - Hash set finds the required third element in O(1)
          average time.
        - Since the original array is not sorted, the same
          triplet can appear in different orders.
        - Sorting each triplet and storing it in a set ensures
          only unique triplets are kept.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Outer Loop:
            O(N)

        Inner Loop:
            O(N)

        Hash Set Lookup:
            O(1) average

        Sorting Each Triplet:
            O(1)
            (Only 3 elements)

        Set Insertion:
            O(log M)
            where M = number of unique triplets

        Total:
            O(N² log M)

        In the worst case:
            O(N² log N)

    -------------------------------------------------------

    📦 Space Complexity

        Hash Set:
            O(N)

        Set of Triplets:
            O(M)

        Total Auxiliary Space:
            O(N + M)

    -------------------------------------------------------

    🎯 One Line

        "Fix one element, solve Two Sum using a hash set, and use a set to eliminate duplicate triplets."
*/
class Solution {
public:

    vector<vector<int>> threeSum(vector<int>& nums) {

        vector<vector<int>>v;
         
        int n = nums.size(); 
        set<vector<int>> res;
        for(int i =0 ; i< n; i++)
        {
            unordered_set<int> st;
            for(int j = i+1 ; j< n  ; j++)
            {
                int target = 0 - (nums[i] + nums[j]);

                if(st.find(target) != st.end())
                {
                    vector<int> temp = {nums[i], nums[j], target};
                    sort(temp.begin() , temp.end());
                    res.insert(temp);
                }
                st.insert(nums[j]); 
            }

        }

        for(auto x : res)
        {
            v.emplace_back(x);
        }

        return v;
    }
};

/*
    🔴 Better - 2

    🧠 Idea:
        - Sort the array.
        - Fix one element nums[i].
        - Reduce the problem to finding two numbers whose
          sum equals -nums[i].
        - Use a hash set to solve the Two Sum problem.
        - Skip duplicate values of nums[i] and duplicate
          pairs to avoid repeated triplets.

    -------------------------------------------------------

    Why This Works

        - Every triplet has one fixed element.
        - The remaining two elements must sum to -nums[i].
        - Hash set allows us to find the required complement
          in O(1) average time.
        - Sorting helps eliminate duplicate triplets.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Sorting:
            O(N log N)

        Outer Loop:
            O(N)

        Two Sum (Hash Set):
            O(N)

        Total:
            O(N²)

    -------------------------------------------------------

    📦 Space Complexity

        Hash Set:
            O(N)

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(N)

    -------------------------------------------------------

    🎯 One Line

        "Fix one element and solve the remaining Two Sum problem using a hash set."
*/
class Solution {
public:

    void twoSum(vector<int> &nums,
                                vector<vector<int>> &v,
                                 int target , int start , int end)
    {
        unordered_set<int> st; 

        int previousAnsA = INT_MIN, previousAnsB = INT_MIN;
        for(int i= start ; i<= end ; i++)
        {
            

                if(st.find(target - nums[i]) != st.end())
                {
                    if(target - nums[i] != previousAnsA && nums[i] != previousAnsB)
                        v.push_back({nums[start-1], target - nums[i], nums[i]});
                    previousAnsA = target - nums[i];
                    previousAnsB = nums[i];
                }

            st.insert(nums[i]) ;
        }

    }

    vector<vector<int>> threeSum(vector<int>& nums) {
        
        sort(nums.begin(), nums.end());
        vector<vector<int>>v;
        int n = nums.size(); 
        for(int i =0 ; i< n-2; i++)
        {
            if(i == 0 || nums[i-1] != nums[i])
                twoSum(nums,v,  0-nums[i], i+1, n-1);
        }

        return v;
    }
};


/*
    🔴 Optimal - 1

    🧠 Idea:
        - Sort the array.
        - Fix one element nums[i].
        - Use two pointers (start and end) to find the
          remaining two numbers whose sum is -nums[i].
        - Skip duplicate values of nums[i] and duplicate
          pairs to avoid repeated triplets.

    -------------------------------------------------------

    Why This Works

        - After sorting, increasing start increases the sum,
          while decreasing end decreases the sum.
        - This allows us to adjust the sum in O(1) time
          instead of checking every pair.
        - Duplicate triplets are avoided by skipping repeated
          values of the fixed element and previously found pairs.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Sorting:
            O(N log N)

        Outer Loop:
            O(N)

        Two Pointers:
            O(N)

        Total:
            O(N²)
            (Sorting is dominated by N².)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Answer Vector:
            Depends on the number of valid triplets.

        Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Sort the array, fix one element, and use two pointers to find the remaining pair."
*/
class Solution {
public:

    vector<vector<int>> threeSum(vector<int>& nums) {

       sort(nums.begin(), nums.end());
       int n = nums.size(); 
        vector<vector<int>> v;
       for(int i = 0 ; i< n-2 ; i++)
       {
            if(i ==0 || nums[i] != nums[i-1])
            {
                int start = i+1 ;
                int end = n-1; 

                int previousAnsA = INT_MIN ;
                int previousAnsB = INT_MIN;
                while(start < end )
                {
                    int sum = nums[start] + nums[end] + nums[i];

                    if(sum > 0)
                    {
                        end--;
                    }
                    else if(sum < 0)
                    {
                        start++;
                    }
                    else
                    {
                        if(nums[start] != previousAnsA && nums[end] != previousAnsB)
                            v.push_back({nums[i], nums[start], nums[end]});
                        
                        previousAnsA = nums[start];
                        previousAnsB = nums[end];

                        start++; 
                        end--;
                    }
                }
            }
       }

       return v;
    }
};