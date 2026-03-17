/* 
    Problem Link - https://leetcode.com/problems/two-sum/description/
*/

/*
    Approach: Brute Force

    Idea:
    - Check every possible pair of elements.
    - If their sum equals the target, return their indices.

    Why This Works:
    - We are exhaustively checking all combinations,
      so we are guaranteed to find the correct pair.

    Time Complexity: O(N^2)
    - Two nested loops.

    Space Complexity: O(1)
    - Only a small output vector is used.
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int sum = 0; 
        pair<int, int > p;
        vector<int> v(2);
        for(int i = 0 ; i< nums.size() ; i++)
        {
            for(int j = i+1 ; j < nums.size(); j++)
            {
                int sum = nums[i] + nums[j] ; 
                if(sum == target)
                {
                   v[0]= i;
                   v[1] = j;
                }
            }
        }
        return v; 
    }
};