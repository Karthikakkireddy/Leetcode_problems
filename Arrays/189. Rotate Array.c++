// https://leetcode.com/problems/rotate-array/description/

/*
* Approach:
* Rotate the array to the right by 1 position, k times.
* For each rotation:
* 1. Store the last element because it will be lost during shifting.
*    This element must become the first element after rotation.
* 2. Shift all elements one position to the right.
*    Traverse from right to left to avoid overwriting values
*    that are still needed.
* 3. Place the stored last element at index 0.
* Example:
* nums = [1,2,3,4,5]
* After 1 rotation:
* [5,1,2,3,4]
*
* After 2 rotations:
* [4,5,1,2,3]

TC - O(n * K)
SC - O(1)
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        for(int itr = 1 ; itr<=k ; itr++)
        {
            int last = nums[n-1];

            for(int i=n-2 ; i>=0 ; i--)
            {
                nums[i+1] = nums[i];
            }
            nums[0] = last;
        }
    }
};



/*
🔴 Rotate Array

🧠 Idea:

- For each element at index i,
  place it at:

      (i + k) % n

- Use a temporary array to store
  rotated positions.

------------------------------------------------------

🧠 Formula:

    (i + k) % n

asks:

    "Where should nums[i] go?"

------------------------------------------------------

⏱️ TC: O(N)

📦 SC: O(N)

------------------------------------------------------

🎯 One line:

"Place every element directly into its final rotated position."
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n= nums.size();
        vector<int> v(n);
        for(int i=0 ; i<n ; i++)
        {
            v[(i + k ) % n ] = nums[i];
        
        }
        for(int i=0 ; i<n ; i++)
        {
            nums[i] = v[i];
        }
    }
};

/*
🔴 Rotate Array (Optimal - 3 Reversals)

🧠 Idea:

- After rotating right by k,
  the last k elements should come to the front.

- Reverse everything first.
- Then fix the first part.
- Then fix the second part.

------------------------------------------------------

🧠 Example:

    [1,2,3,4,5,6,7]
    k = 3

Reverse all:
    [7,6,5,4,3,2,1]

Reverse first k:
    [5,6,7,4,3,2,1]

Reverse remaining:
    [5,6,7,1,2,3,4]

------------------------------------------------------

⚠️ Important:

    k %= n

handles cases where k > n

------------------------------------------------------

⏱️ TC: O(N)

📦 SC: O(1)

------------------------------------------------------

🎯 One line:

"Reverse whole array, then reverse the two resulting parts."
*/
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k = k % nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k  , nums.end());
    }
};