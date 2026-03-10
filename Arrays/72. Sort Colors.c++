
/*
    Problem Link - https://leetcode.com/problems/sort-colors/description/
*/

/*
    Approach: Counting

    Idea:
    - First traverse the array and count the number of
      0s, 1s, and 2s.
    - Then overwrite the array with the counted number
      of 0s, followed by 1s, and then 2s.

    Time Complexity: O(N)
    - First pass → count number of 0s, 1s, and 2s.
    - Second pass → overwrite the array with sorted values.

    Total ≈ 2N → O(N)

    Space Complexity: O(1)
    - Only three integer counters are used.
*/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zeros = 0;
        int ones = 0 ; 
        int twos = 0;
        int size = nums.size();

        for(int i=0 ; i< size ; i++)
        {
            if(nums[i] == 0)
                zeros++;
            else if(nums[i] == 1)
                ones++;
            else
                twos++;
        }
        int index = 0;
        for(int i= 0 ; i< size ; i++)
        {
            if(zeros)
            {
                nums[i]= 0;
                zeros = zeros - 1; 
            }
            else if(ones)
            {
                nums[i]= 1;
                ones = ones - 1; 
            }
            else if(twos)
            {
                nums[i]= 2;
                twos = twos - 1; 
            }
        }
    }
};


/*
    Approach: Dutch National Flag

    Idea:
    - Use three pointers:
        red   → next position where 0 should go
        white → current element being checked
        blue  → next position where 2 should go

    What we do:
    - If we see 0 → swap with red side, move both red and white.
    - If we see 1 → already in correct region, just move white.
    - If we see 2 → swap with blue side, move blue back
      (white stays to re-check the swapped element).

    Why this works:
    - The array gradually forms three regions:
        left  → all 0s
        middle → all 1s
        right → all 2s
    - Each swap pushes elements into their correct region,
      so the unknown part keeps shrinking. 

    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    void sortColors(vector<int>& nums)
    {
       int red= 0 ;
       int white = 0;
       int blue = nums.size()-1;

       while(white <= blue)
       {
            if(nums[white] == 0) // Red
            {
                swap(nums[white], nums[red]);
                red++;
                white++;
            }
            else if(nums[white] == 2) // Blue
            {
                swap(nums[white], nums[blue]);
                blue--;
            }
            else // nums[white] == 1
            {
                white++;
            }
       }
    }
};


/*
    Approach: Dutch National Flag (flipped direction)

    Idea:
    - Same concept as the classic solution but the processing
      happens from right → left.

    Pointers:
        red   → boundary for 0s
        white → current pointer scanning from right
        blue  → boundary for 2s

    What we do:
    - If we see 0 → swap toward the red side.
    - If we see 2 → swap toward the blue side.
    - If we see 1 → just move the white pointer.

    Why this works:
    - Swaps gradually push 0s to the left and 2s to the right.
    - The unprocessed region keeps shrinking until everything
      ends up in the correct place.

    TC: O(N)
    SC: O(1)
*/
class Solution {
public:
    void sortColors(vector<int>& nums)
    {
       int red= 0 ;
       int white = nums.size()-1;
       int blue = nums.size()-1;

       while(red <= white)
       {
            if(nums[white] == 0) // Red
            {
                swap(nums[white], nums[red]);
                red++;
            }
            else if(nums[white] == 2) // Blue
            {
                swap(nums[white], nums[blue]);
                white--;
                blue--;
            }
            else // nums[white] == 1
            {
                white--;
            }
       }
    }
};