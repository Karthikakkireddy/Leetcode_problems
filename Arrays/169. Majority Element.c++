// https://leetcode.com/problems/majority-element/description/


/*
🔴 Majority Element (Hash Map)

🧠 Idea:
- Count frequency of every element.
- Majority element appears more than n/2 times.
- Return the element whose frequency exceeds n/2.

🧠 Example:
[2,2,1,1,1,2,2]

2 → 4
1 → 3

4 > 7/2

Answer = 2

⏱️ TC: O(N)
📦 SC: O(N)

🎯 One line:
"Count frequencies and return the element occurring more than n/2 times."
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> mp; 

        for(auto x : nums)
        {
            mp[x]++;
        }

        for(auto &x: mp)
        {
            if(x.second > nums.size()/2)
            {
                return x.first;
            }
        }

        return -1;
    }
};


/*
🔴 Majority Element (Sorting)

🧠 Idea:
- Sort the array.
- Since the majority element appears more than n/2 times,
  it must occupy the middle position after sorting.
- Return nums[n/2].

🧠 Example:
[2,2,1,1,1,2,2]

After sorting:

[1,1,1,2,2,2,2]

Middle index = 7/2 = 3

nums[3] = 2

Answer = 2

⏱️ TC: O(N log N)
📦 SC: O(1)   // Ignoring sorting space used internally

🎯 One line:
"After sorting, the majority element must be at the middle index."
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        return nums[nums.size() / 2 ];
    }
};


/*
🔴 Majority Element (Moore's Voting Algorithm)

🧠 Idea:
- Maintain a candidate element and its count.
- If count becomes 0, choose the current element as the new candidate.
- If current element equals candidate, increment count.
- Otherwise decrement count.

🧠 Why does it work?
- Every occurrence of a non-majority element cancels one occurrence
  of the majority element.
- Since the majority element appears more than n/2 times,
  it can never be completely cancelled.

🧠 Example:
[2,2,1,1,1,2,2]

2 → count=1
2 → count=2
1 → count=1
1 → count=0
1 → candidate=1, count=1
2 → count=0
2 → candidate=2, count=1

Answer = 2

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:
"Keep cancelling different elements; the majority element survives."
*/
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int count =0 ; 
        int element ; 
        for(auto x : nums)
        {
            if(count == 0)
            {
                element = x;
            }
            if(x == element)
            {
                count++;
            }
            else
            {
                count--;
            }
        }
        return element;
    }
};