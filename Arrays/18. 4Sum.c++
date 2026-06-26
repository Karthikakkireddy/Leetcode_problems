// https://leetcode.com/problems/4sum/description/

/*
    🔴 Brute Force

    🧠 Idea:
        - Sort the array.
        - Generate every possible quadruplet using
          four nested loops.
        - If the sum equals the target, add the
          quadruplet to the answer.
        - Skip duplicate values at each loop to
          avoid duplicate quadruplets.

    -------------------------------------------------------

    Why This Works

        - Four nested loops generate every possible
          combination of four elements.
        - Sorting allows duplicate values to be skipped,
          ensuring only unique quadruplets are added.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Sorting:
            O(N log N)

        Four Nested Loops:
            O(N⁴)

        Total:
            O(N⁴)
            (Sorting is dominated by N⁴.)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Answer Vector:
            Depends on the number of valid quadruplets.

        Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Generate every unique quadruplet and keep those whose sum equals the target."
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        sort(nums.begin(), nums.end()); 
        int n = nums.size();
        vector<vector<int>> v;
        for(int i = 0 ; i< n  ; i++)
        {
            if(i ==0 || nums[i] != nums[i-1])
            {

                for(int j = i+1 ; j < n ; j++)
                {
                    if(j == i+1 || nums[j] != nums[j-1])
                    {
                        for(int k = j+1; k < n ; k++)
                        {
                            if(k == j+1 || nums[k] != nums[k-1])
                            {
                                for(int l = k+1 ; l < n ; l++)
                                {
                                    // cout << i << " " << j << " " << k << " " << l << '\n';
                                    if(l == k+1 || nums[l] != nums[l-1])
                                    {
                                        long long sumA = nums[i] + nums[j]; 
                                        long long sumB = nums[k] + nums[l];
                                        long long sumC = sumA + sumB ;
                                        
                                        if(sumC == target)
                                        {
                                            v.push_back({nums[i], nums[j], nums[k],nums[l]});
                                        }
                                    }
                                }
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
    🔴 Better

    🧠 Idea:
        - Fix the first two elements using two loops.
        - Reduce the remaining problem to Two Sum.
        - Use a hash set to find the fourth element.
        - Store every valid quadruplet in a set to
          automatically remove duplicates.

    -------------------------------------------------------

    Why This Works

        - After fixing two elements, only two numbers
          remain to be found.
        - Hash set finds the required fourth element
          in O(1) average time.
        - Since duplicate quadruplets can be generated,
          each quadruplet is sorted before inserting
          into the set.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Sorting:
            O(N log N)

        First Loop:
            O(N)

        Second Loop:
            O(N)

        Third Loop:
            O(N)

        Hash Set Lookup:
            O(1) average

        Set Insertion:
            O(log M)

        Total:
            O(N³ log M)

        Worst Case:
            O(N³ log N)

    -------------------------------------------------------

    📦 Space Complexity

        Hash Set:
            O(N)

        Set of Quadruplets:
            O(M)

        Total Auxiliary Space:
            O(N + M)

    -------------------------------------------------------

    🎯 One Line

        "Fix two elements, solve Two Sum using a hash set, and use a set to remove duplicate quadruplets."
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        sort(nums.begin(), nums.end()); 
        int n = nums.size();
        vector<vector<int>> v;
        set<vector<int>> ans; 

        for(int i = 0 ; i< n  ; i++)
        {
            for(int j = i+1 ; j < n ; j++)
            {
                unordered_set<long long > st;
                
                for(int k = j+1; k < n ; k++)
                {
                    
                    long long sum = (long long)nums[i] + nums[j] + nums[k];
                    long long remainingTarget = (long long)target - sum;

                    if(st.find(remainingTarget) != st.end() )
                    {
                        vector<int> temp = {nums[i], nums[j], nums[k], (int) remainingTarget};

                        sort(temp.begin(), temp.end());

                        ans.insert(temp); 
                    }
                    st.insert(nums[k]);
                }
            }
        }

        v.assign(ans.begin(), ans.end());
        return v;
    }
};


/*
    🔴 Optimal

    🧠 Idea:
        - Sort the array.
        - Fix the first two elements using two loops.
        - Reduce the remaining problem to Two Sum.
        - Use two pointers (start and end) to find the
          remaining two elements.
        - Skip duplicate values for i, j, start and end
          to avoid duplicate quadruplets.

    -------------------------------------------------------

    Why This Works

        - After fixing two elements, only two numbers
          remain to be found.
        - Since the array is sorted, two pointers can
          efficiently move towards the required sum.
        - Duplicate values are skipped to ensure only
          unique quadruplets are added.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Sorting:
            O(N log N)

        First Loop:
            O(N)

        Second Loop:
            O(N)

        Two Pointers:
            O(N)

        Total:
            O(N³)
            (Sorting is dominated by N³.)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Answer Vector:
            Depends on the number of valid quadruplets.

        Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Sort the array, fix two elements, and use two pointers to find the remaining pair."
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {

        sort(nums.begin(), nums.end()); 
        int n = nums.size();
        vector<vector<int>> v;
        

        for(int i = 0 ; i< n  ; i++)
        {
            if(i ==0  || nums[i] != nums[i-1])
            {
                for(int j = i+1 ; j < n ; j++)
                {
                    if(j == i+1 || nums[j] != nums[j-1])
                    {
                        int start = j+1; 
                        int end = n-1 ;
                        long long remainingTarget = (long long) target - (nums[i] + nums[j]);

                        while(start < end )
                        {
                            long long sum = nums[start] + nums[end];

                            if(sum == remainingTarget)
                            {
                                v.push_back({nums[i], nums[j], nums[start], nums[end]});

                                while(start < end && nums[start] == nums[start+1] )
                                {
                                    start++;
                                }
                                while(start < end && nums[end] == nums[end-1])
                                {
                                    end--;
                                }
                                start++;
                                end--;
                            }
                            else if(sum < remainingTarget)
                            {
                                start++;
                            }
                            else
                            {
                                end--;
                            }

                        }
                    }
                }
            }
        }

        // v.assign(ans.begin(), ans.end());
        return v;
    }
};