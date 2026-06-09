// https://leetcode.com/problems/move-zeroes/description/


/*
🔴 Move Zeroes (Using Extra Array)

🧠 Idea:

- Create a new array of the same size.
- Copy only the non-zero elements into it.
- Since vector elements are initialized to 0,
  the remaining positions automatically stay as 0.

------------------------------------------------------

Flow:

1. Traverse nums
2. If element is non-zero:
       store it in v[k]
       increment k
3. Replace nums with v

------------------------------------------------------

🧠 Example:

    [0,1,0,3,12]

After copying non-zeros:

    [1,3,12,0,0]

------------------------------------------------------

⏱️ TC: O(N)

📦 SC: O(N)

------------------------------------------------------

🎯 One line:

"Collect all non-zero elements first; leftover positions remain zero."
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(); 
        vector<int> v(n);
        int k =0;
        for(int i=0 ; i < n ; i++)
        {
            if(nums[i])
            {
                v[k++] = nums[i];
            }
        }

        // for(int i=0 ; i < n ; i++)
        // {
        //     nums[i] = v[i];
        // }
        nums = v;
    }
};

/*
🔴 Move Zeroes (Two Pointers)

🧠 Idea:

- zero_element_index always points to the first zero
  that should be replaced by a non-zero element.

- i traverses the array from left to right.

- If:
      nums[i] != 0
  and
      i > zero_element_index

  then a zero is sitting before a non-zero element.

- This is opposite of our goal, so swap them.

------------------------------------------------------

After swapping:

- Move zero_element_index forward
  until it points to the next zero.

- This keeps zero_element_index always pointing
  to the first available zero position.

------------------------------------------------------

🧠 Example:

    [0,1,0,3,12]

    swap(0,1)
    [1,0,0,3,12]

    swap(0,3)
    [1,3,0,0,12]

    swap(0,12)
    [1,3,12,0,0]

------------------------------------------------------

⏱️ TC: O(N)

📦 SC: O(1)

------------------------------------------------------

🎯 One line:

"Keep track of the first zero and swap every future non-zero into that position."
*/
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size(); 
        int zero_element_index = 0 ; 

        for(int i=0 ; i< n ; i++)
        {
            if(zero_element_index < i && nums[i] != 0 )
            {
                swap(nums[zero_element_index], nums[i] );
            }

            while(zero_element_index < n && nums[zero_element_index] != 0 )
            {
                zero_element_index++;
            }
        }
    }
};