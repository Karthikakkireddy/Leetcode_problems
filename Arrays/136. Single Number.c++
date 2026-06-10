// https://leetcode.com/problems/single-number/description/


/*
🔴 Single Number (Hash Map)

🧠 Idea:
- Count the frequency of every number using a hash map.
- The number appearing once will have frequency = 1.
- Traverse the map and return the key whose frequency is 1.

🧠 Example:
nums = [2,2,1]

Map:
2 → 2
1 → 1

Answer = 1

⚠️ Note:
The order of traversal in unordered_map is not guaranteed,
but that does not matter because there is exactly one answer.

⏱️ TC: O(N)
📦 SC: O(N)

🎯 One line:
"Count frequencies and return the element that appears exactly once."
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        for(auto x : nums)
        {
            mp[x]++;
        }

        for(auto &x : mp)
        {
            if(x.second == 1)
            {
                return x.first;
            }
        }
        return -1; 
    }
};

/*
🔴 Single Number (XOR)

🧠 Idea:
- XOR all elements of the array.
- Duplicate numbers cancel each other.
- The number appearing once remains.

🧠 XOR Properties:
a ^ a = 0
a ^ 0 = a
XOR is commutative and associative.

🧠 Example:
nums = [4,1,2,1,2]

xor:
4 ^ 1 ^ 2 ^ 1 ^ 2

= 4 ^ (1 ^ 1) ^ (2 ^ 2)
= 4 ^ 0 ^ 0
= 4

Answer = 4

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:
"Equal numbers cancel out in XOR, leaving only the unique number."
*/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xor1 = 0; 

        for(auto x : nums)
        {
            xor1 ^= x;
        }

        return xor1;
    }
};