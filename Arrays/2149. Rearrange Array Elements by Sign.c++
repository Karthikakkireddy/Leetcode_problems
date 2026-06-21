// https://leetcode.com/problems/rearrange-array-elements-by-sign/description/


/*
🔴 Rearrange Array Elements by Sign

🧠 Idea:
- Store positive and negative numbers in separate arrays.
- Rebuild the original array by alternately placing:
      positive, negative, positive, negative...

🧠 Example:

nums = [3,1,-2,-5,2,-4]

positives = [3,1,2]
negatives = [-2,-5,-4]

Result:

[3,-2,1,-5,2,-4]

🧠 Traversals:
1. First traversal:
      Separate positives and negatives
      → O(N)

2. Second traversal:
      Place elements back alternately
      → O(N/2)

Total work:
      N + N/2 operations

Which simplifies to:

⏱️ TC: O(N) - (N + N/2 traversals)

📦 SC: O(N)
(positive array + negative array)

🎯 One line:
"Separate positives and negatives, then place them alternately."
*/
class Solution {
public:
    
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> positiveNumberArray ;
        vector<int> negativeNumberArray ;

        for(auto x : nums)
        {
            if(x > 0)
            {
                positiveNumberArray.emplace_back(x);
            }
            else
            {
                negativeNumberArray.emplace_back(x);
            }
        }

        for(int i=0 ; i< n/2 ; i++)
        {
            nums[2 * i] = positiveNumberArray[i];
            nums[2* i + 1] = negativeNumberArray[i];
        }

        return nums;

    } 
};

/*
🔴 Rearrange Array Elements by Sign

🧠 Idea:
- Positive numbers must be placed at:
      0, 2, 4, 6, ...

- Negative numbers must be placed at:
      1, 3, 5, 7, ...

- Maintain two indices:
      positiveIndex = 0
      negativeIndex = 1

- Traverse the array once and place each element
  in its designated position.

🧠 Example:

nums = [3,1,-2,-5,2,-4]

Place:

3  → index 0
1  → index 2
-2 → index 1
-5 → index 3
2  → index 4
-4 → index 5

Result:

[3,-2,1,-5,2,-4]

⚠️ This works because the problem guarantees:
- Equal number of positive and negative elements.
- Result must start with a positive element.

⏱️ TC: O(N)
📦 SC: O(N)

🎯 One line:
"Place positives at even indices and negatives at odd indices."
*/
class Solution {
public:
    
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size(); 

        vector<int> v(n);
        int positiveIndex =0 ;
        int negativeIndex = 1; 

        for(int i =0 ; i< n ; i++)
        {
            if(nums[i] > 0 )
            {
                v[positiveIndex] = nums[i];
                positiveIndex = positiveIndex + 2;
            }
            else
            {
                v[negativeIndex] = nums[i];
                negativeIndex = negativeIndex + 2;

            }
        }

        return v;
    } 
};