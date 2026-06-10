// https://leetcode.com/problems/max-consecutive-ones/description/


/*
🔴 Maximum Consecutive Ones

🧠 Idea:
- counter stores current streak of consecutive 1s.
- If current element is 1 → increment counter.
- If current element is 0 → reset counter to 0.
- Keep updating maxCount with the largest streak seen so far.

🧠 Example:
nums = [1,1,0,1,1,1]

counter:
1 → 1
1 → 2
0 → 0
1 → 1
1 → 2
1 → 3

maxCount = 3

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:
"Track the current streak of 1s and remember the maximum streak."
*/
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int counter = 0 ; 
        int maxCount = 0; 

        for(auto x : nums)
        {
            if(x == 1)
            {
                counter++;
            }
            else
            {
                counter = 0 ;
            }
            maxCount = max(maxCount, counter); 
        }
        return maxCount; 
    }
};

/*
🔴 Maximum Consecutive Ones (Kadane-like Thinking)

🧠 Idea:
- Treat 1 as a contribution to the current streak.
- If x = 1:
      sum + x > sum
      so extend the streak.
- If x = 0:
      sum + x == sum
      so current streak ends.
      Update maxSum and reset sum.

🧠 Example:
nums = [1,1,0,1,1,1]

sum:
1 → 1
1 → 2
0 → reset (maxSum = 2)
1 → 1
1 → 2
1 → 3

Answer = 3

⚠️ Note:
This works only because array contains 0s and 1s.
For this problem, the counter approach is simpler and more readable.

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:
"Extend streak on 1, end streak on 0."
*/
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int counter = 0 ; 
        int maxCount = 0; 

        for(auto x : nums)
        {
            if(x == 1)
            {
                counter++;
            }
            else
            {
                counter = 0 ;
            }
            maxCount = max(maxCount, counter); 
        }
        return maxCount; 
    }
};