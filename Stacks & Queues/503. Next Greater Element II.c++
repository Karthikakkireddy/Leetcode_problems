// https://leetcode.com/problems/next-greater-element-ii/description/


/*
🔴 Next Greater Element II (Circular Array)

🧠 Idea:
- Array is circular → simulate by iterating 2 times
- Use monotonic decreasing stack

------------------------------------------------------

🧠 Logic:

Loop from 2*n-1 → 0

For each i:
    curr = nums[i % n]

    - Pop all elements <= curr
    - Top of stack = next greater
    - If empty → -1

⚠️ Only fill answer when i < n
    (second pass is just for helping)

    Push curr into stack

------------------------------------------------------

🧠 Why 2*n?

- To simulate circular behavior
- Right side + wrap-around left side

------------------------------------------------------

⏱️ Time Complexity:

Each element pushed & popped once → O(N)

------------------------------------------------------

📦 Space Complexity:

stack → O(4N) - 2N for inserting and 2N for popping
ans   → O(2N)

------------------------------------------------------

🎯 One line:

"Traverse twice + monotonic stack to handle circular next greater"
*/
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        stack<int> stk; 
        int n = nums.size();
        vector<int>ans(n);
        for(int i = 2*n-1 ; i>=0 ; i--)
        {
            while(!stk.empty() && stk.top() < nums[i%n])
            {
                stk.pop(): 
            }
            if(stk.emmpty())
            {
                if(i<n)
                    ans[i%n] = -1;
            }
            else
            {
                if(i<n)
                    ans[i%n] = stk.top() ;
            }
            stk.push(nums[i%n]);
        }
        reuturn ans;
    }
};