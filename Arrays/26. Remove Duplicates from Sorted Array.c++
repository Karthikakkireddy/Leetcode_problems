// https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/

//Brute Force
    // Store all unique elements in a temporary vector.
    // Since the array is sorted, compare each element with the last
    // inserted element to avoid duplicates.
    // Copy the unique elements back to the original array.
    // Return the count of unique elements.
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int> v ;
        for(int i =0 ; i< nums.size() ; i++)
        {
            if(v.size() == 0 || v.back()!= nums[i])
            {
                v.emplace_back(nums[i]);
            }
        }
        for(int i =0 ; i< v.size(); i++)
        {
            nums[i] = v[i];
        }

        return v.size();
    }
};

/*
🔴 Intuition

- ptr points to the last unique element found so far.

- The subarray:

      nums[0 ... ptr]

  contains all unique elements without duplicates.

- i scans the array from left to right.

- Whenever:

      nums[i] != nums[ptr]

  we have discovered a new unique element.

- So:
      1. Move ptr forward
      2. Store this new unique element at nums[ptr]

      nums[++ptr] = nums[i];

- This gradually builds the duplicate-free array
  in-place at the beginning of nums.

------------------------------------------------------

🧠 Invariant:

At any point during the algorithm:

    nums[0 ... ptr]

contains all unique elements seen so far.

------------------------------------------------------

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:

"ptr marks the end of the unique portion, and i searches for the next unique element."
*/
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int ptr = 0 ; 
        for(int i=1 ; i< nums.size() ; i++)
        {
            if(nums[ptr] != nums[i])
            {
                nums[++ptr] = nums[i];
            }
        }
        return ptr+1;
    }
};