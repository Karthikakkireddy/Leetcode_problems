// https://leetcode.com/problems/next-greater-element-i/?envType=problem-list-v2&envId=monotonic-stack

/*
🔴 Next Greater Element (Brute Force)

🧠 Idea:
- For each element in nums1:
    1. Find its index in nums2
    2. Scan right side of nums2
    3. First greater element → answer
    4. If none → -1

------------------------------------------------------

⚠️ What your code is doing:

functionHelper:
    → finds index of element in nums2 (linear search)

Main logic:
    → for each element in nums1
    → scan right side in nums2 to find next greater

------------------------------------------------------

⏱️ Time Complexity:

- Finding index → O(N)
- Scanning right → O(N)

Total:
    O(N * N)   ❌ (Not optimal)

------------------------------------------------------

📦 Space Complexity:

- ans vector → O(N)

Total:
    O(N)

------------------------------------------------------

⚠️ Limitation:

- Repeats work again and again
- No reuse of computed results

👉 This is pure brute force
*/
class Solution {
public:
    
    int functionHelper(int number, vector<int>& nums2)
    {
        for(int j=0; j<nums2.size() ; j++)
        {
            if(nums2[j] == number)
                return j;
        }
        return 0;
    }

    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans; 
        for(int i=0 ; i<nums1.size() ; i++)
        {
            int get_j_index = functionHelper(nums1[i], nums2);
            bool is_next_greater_value_present = false;
            for(int j= get_j_index+1; j<nums2.size() ; j++)
            {
                if(nums2[get_j_index] < nums2[j])
                {
                    ans.push_back(nums2[j]);
                    is_next_greater_value_present = true;
                    break;
                }

            }
            if(is_next_greater_value_present == false)
            {
                ans.push_back(-1);
            }
        }

        return ans; 
    }
};




/*
🔴 Next Greater Element (Monotonic Stack + Mapping via index)

🧠 Idea:

STEP 1:
    Precompute next greater for every element in nums2 using stack

STEP 2:
    For each nums1[i], find its index in nums2
    → pick answer from precomputed array (mem)

------------------------------------------------------

🧠 What stack is doing:

- Traverse nums2 from RIGHT → LEFT
- Maintain decreasing stack

For each element:
    - Remove all smaller elements (they are useless)
    - Top of stack → next greater
    - Push current element

👉 This ensures each element is processed once

------------------------------------------------------

⏱️ Time Complexity:

Step 1 (building mem):
    Each element pushed & popped once → O(N)

Step 2:
    functionHelper → O(N) for each nums1 element

Total:
    O(N) + O(M * N)

👉 Overall:
    O(M * N) ❌ (still not optimal due to functionHelper)

------------------------------------------------------

📦 Space Complexity:

- stack → O(N)
- mem array → O(N)
- ans → O(M)

Total:
    O(N + M)

------------------------------------------------------

⚠️ Important flaw:

👉 You optimized next greater computation
BUT

👉 Still doing linear search (functionHelper)

This kills performance.

------------------------------------------------------

🎯 Key Insight:

- You solved half the problem optimally
- The bottleneck is "finding index"

👉 Replace functionHelper with map:
    value → next greater

Then TC becomes:
    O(N + M) ✅ optimal

------------------------------------------------------

🧠 One line:

"Stack optimized next greater, but lookup still brute force"
*/
class Solution {
public:
    
    int functionHelper(int number, vector<int>& nums2)
    {
        for(int j=0; j<nums2.size() ; j++)
        {
            if(nums2[j] == number)
                return j;
        }
        return 0;
    }

    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> mem(nums2.size()); 
        vector<int> ans(nums1.size());
        stack<int> stk; 
        for(int i = nums2.size()-1 ; i>=0 ; --i)
        {
            while(!stk.empty() && stk.top()<nums2[i])
            {
                stk.pop();
            }
            if(!stk.empty())
            {
                mem[i] = stk.top();
                stk.push(nums2[i]);
            }
            else
            {
                mem[i] = -1; 
                stk.push(nums2[i]); 
            } 
                
        }
        
        for(int i = 0 ; i<nums1.size() ; i++)
        {
            ans[i] =  mem[functionHelper(nums1[i], nums2)] ; 
        }
       
        return ans; 
    }
};

/*
🔴 Next Greater Element (Optimal - Monotonic Stack + HashMap)

🧠 Idea:

STEP 1:
    Use monotonic decreasing stack on nums2
    → find next greater for every element

STEP 2:
    Store result in hashmap:
        value → next greater

STEP 3:
    Directly answer nums1 using map

------------------------------------------------------

🧠 Stack Logic:

Traverse nums2 from RIGHT → LEFT

For each element:
    - Pop all smaller elements (they can't be next greater)
    - If stack not empty → top = next greater
    - Else → no greater → -1
    - Push current element

👉 Each element is pushed & popped once

------------------------------------------------------

⏱️ Time Complexity:

- Stack processing → O(N)
- Map lookup for nums1 → O(M)

Total:
    O(N + M) ✅ Optimal

------------------------------------------------------

📦 Space Complexity:

- stack → O(N)
- hashmap → O(N)
- ans → O(M)

Total:
    O(N + M)

------------------------------------------------------

🎯 Why this is optimal:

- No repeated scanning
- No linear search (unlike previous version)
- Precompute once → reuse everywhere

------------------------------------------------------

🧠 One line:

"Precompute next greater once → answer in O(1) using hashmap"
*/
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans(nums1.size());
        unordered_map<int, int> mp; 
        stack<int> stk; 
        for(int i = nums2.size()-1 ; i>=0 ; --i)
        {
            while(!stk.empty() && stk.top()<nums2[i])
            {
                stk.pop();
            }
            if(!stk.empty())
            {
               mp[nums2[i]] = stk.top();
              
            }
            else
            {
               mp[nums2[i]] = -1;
            } 
            stk.push(nums2[i]);
                
        }
        
        for(int i = 0 ; i<nums1.size() ; i++)
        {
            ans[i] = mp[nums1[i]]; 
        }
       
        return ans; 
    }
};