// https://leetcode.com/problems/majority-element-ii/description/


/*
🔴 Brute Force - 1

🧠 Idea:
- For every unique element, count its frequency by
  traversing the entire array.
- If frequency > n/3, add it to the answer.
- Use a set to avoid processing the same element
  multiple times.

🧠 Example:

nums = [3,2,3]

3 → count = 2

2 → count = 1

n = 3
n/3 = 1

2 > 1 ✅

Answer:
[3]

🧠 Why use a set?
- Prevents adding the same majority element multiple times.
- Prevents repeating frequency counting for elements
  already identified as majority elements.

⏱️ TC Analysis:

Outer loop:
    O(N)

For each element:
    Frequency count → O(N)

Total:
    O(N²)

📦 SC Analysis:

Set:
    Stores at most 2 elements
    (There can be at most 2 elements occurring > n/3 times)

Answer vector:
    At most 2 elements

Total:
    O(1)

🎯 One line:
"Count the frequency of each unique element and collect those occurring more than n/3 times."
*/
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_set<int> st; 
        int n = nums.size(); 
        for(int i = 0 ; i< n ; i++)
        {
            int count = 0; 
            if(st.count(nums[i]) == 0)
            for(int j=0; j< nums.size(); j++)
            {
                if(nums[j] == nums[i])
                {
                    count++;
                }

            }
            if(count  > n/3)
            {
                st.insert(nums[i]);
            }
        }

        return vector<int>{st.begin(), st.end()};
    }
};

/*
🔴 Majority Element II (Improved Brute Force)

🧠 Improvement over Previous Brute Force:
- Previous solution used an unordered_set to avoid
  storing duplicate majority elements.
- This solution uses the answer vector itself to avoid
  reprocessing elements already found.

Previous:
    Extra set + answer creation

Current:
    Only answer vector

🧠 Idea:
- For each element, count its frequency.
- If frequency > n/3, add it to the answer.
- Stop once 2 majority elements are found because
  there can be at most 2 elements occurring more than n/3 times.

⚠️ Improvement:
- Early termination:

      if(v.size() == 2)
          break;

- No separate set required.

⏱️ TC:
Still O(N²)

📦 SC:
O(1)
(Answer size is at most 2)

🎯 One line:
"Same brute-force frequency counting, but uses the answer vector to avoid extra set storage and stops after finding two valid elements."
*/
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> v;
        int n = nums.size(); 
        for(int i = 0 ; i< n ; i++)
        {
            int count = 0; 
            if(v.size() == 0 || v[0] != nums[i] )
            for(int j=0; j< nums.size(); j++)
            {
                if(nums[j] == nums[i])
                {
                    count++;
                }

            }
            if(count  > n/3)
            {
                v.push_back(nums[i]);
            }
            if(v.size() == 2)
            {
                break;
            }
        }

        return v;
    }
};

/*
    Optimal Solution
🧠 Idea:
- There can be at most 2 elements occurring more than n/3 times.
- Maintain two candidate elements and their counts.
- Similar to Moore's Voting for n/2, but now track
  two possible candidates.

Phase 1:
- Find two potential candidates by cancelling out
  different elements.

Phase 2:
- Verify whether the candidates actually occur
  more than n/3 times.

🧠 Why verification?
- Voting only gives potential candidates.
- Count frequencies again to confirm.

🧠 Improvement over Brute Force:
- Brute Force:
    Count frequency for every element.

- Moore's Voting:
    Narrow search to at most 2 candidates,
    then verify only those.

⏱️ TC:
First pass      → O(N)
Verification    → O(N)

Total           → O(N)

📦 SC:
O(1)

🎯 One line:
"Use voting to find at most two candidates, then verify them."
*/
class Solution {
public:
    void insertMajorityElement2(vector<int> &v, vector<int> &nums, int element)
    {
        int n =nums.size();

        int count =0 ;
        for(auto x: nums)
        {
            if(x == element)
            {
                count++;
            }
        }

        if(count > n/3)
        {
            v.push_back(element);
        }
    }
    vector<int> majorityElement(vector<int>& nums) {
        int ele1 = INT_MIN, ele2 = INT_MIN ;
        int cnt1 =0, cnt2 = 0;
        int n =nums.size();
        vector<int> v;
        
        for(int i =0 ;i< n ; i++)
        {
            if( cnt1 == 0 && ele2 != nums[i]   )
            {
                cnt1= 1; 
                ele1 = nums[i];
            }
            else if(nums[i] == ele1 )
            {
                cnt1++;
            }
            else if(cnt2 ==0 && ele1 != nums[i]  )
            {
                cnt2 = 1 ;
                ele2= nums[i];
            }
            else if(nums[i] == ele2)
            {
                cnt2++;
            }
            else
            {
                cnt1--;
                cnt2--;
            }
        }

        if(cnt1 != 0 )
        {
            insertMajorityElement2(v, nums, ele1);
        }
        if(cnt2 != 0)
        {
            insertMajorityElement2(v, nums, ele2);
        }

        return v;
    }
};