/* 
    Problem Link - https://leetcode.com/problems/two-sum/description/
*/
/*
🔴 Two Sum (Brute Force)

🧠 Idea:
- Pick every element as the first number.
- Search all elements to its right as the second number.
- If their sum equals target, return their indices.

🧠 Example:
nums = [2,7,11,15]
target = 9

i = 0
    j = 1

    2 + 7 = 9 ✅

Answer = {0,1}

🧠 Why j starts from i+1?
- Avoid using the same element twice.
- Avoid checking the same pair again.

Example:
    (2,7) is checked
    (7,2) need not be checked again.

⏱️ TC: O(N²)
📦 SC: O(1)

🎯 One line:
"Check every possible pair and return the one whose sum equals target."
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
       for(int i = 0; i< nums.size(); i++)
       {
            int sum = nums[i];
            for(int j= i+1 ; j< nums.size() ; j++)
            {
                int sum = nums[i] + nums[j];
                if(sum == target)
                {
                    return {i, j};
                }
                
            }
       }
       return {};
    }
};

/*
🔴 Two Sum (Hash Map)

🧠 Idea:
- For every element nums[i], calculate the value needed
  to reach the target:

      required = target - nums[i]

- Check if required has already been seen.
- If yes, we found the pair.
- Otherwise store the current number and its index.

🧠 Example:
nums = [2,7,11,15]
target = 9

i=0:
    required = 7
    not found
    store 2 → 0

i=1:
    required = 2
    found ✅

Answer = {1,0}

🧠 Why check before inserting?
- We cannot use the same element twice.
- So first search for the complement among previously seen elements.
- Then insert the current element.

⏱️ TC: O(N)
📦 SC: O(N)

🎯 One line:
"Store previously seen numbers and look for the required complement."
*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> mp; 
        for(int i= 0 ; i< nums.size(); i++)
        {
            // auto it = mp.find( target - nums[i] ); 
            // if(it != mp.end())
            // {
            //     return {i, it->second};
            // }

            if(mp.find( target - nums[i] ) != mp.end())
            {
                return {i, mp[target - nums[i]]}; // Guranteed 
            }
            mp[nums[i]] = i;
        }
        return {}; // Controller does not get till here
    }
};