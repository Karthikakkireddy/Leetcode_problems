// https://leetcode.com/problems/reverse-pairs/description/


/*
    🔴 Brute Force

    🧠 Idea:
        - Generate every possible pair (i, j)
          where i < j.
        - Check whether:

              nums[i] > 2 * nums[j]

        - If true, it forms a reverse pair.
        - Count all such pairs.

    -------------------------------------------------------

    Why This Works

        - Every possible pair is examined exactly once.
        - If the condition is satisfied, the pair is
          counted as a reverse pair.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Outer Loop:
            O(N)

        Inner Loop:
            O(N)

        Total:
            O(N²)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Check every pair and count those satisfying nums[i] > 2 × nums[j]."
*/
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        int cnt = 0 ; 
        for(int i = 0 ; i< n ; i++)
        {
            for(int j =i+1 ; j < n ; j++)
            {
                if(nums[i] > 2 * nums[j])
                {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

/*
    🔴 Optimal

    🧠 Idea:
        - Use Merge Sort to divide the array into
          smaller sorted halves.
        - Before merging, count reverse pairs across
          the two sorted halves.
        - For each element in the left half, move a
          pointer in the right half while:

              nums[left] > 2 * nums[right]

        - Since both halves are sorted, the right
          pointer never moves backwards.

    -------------------------------------------------------

    Why This Works

        - Merge Sort guarantees both halves are sorted.
        - Once nums[left] satisfies the condition for
          nums[right], it also satisfies it for all
          previous right-side elements.
        - The right pointer only moves forward once,
          making the counting process linear during
          each merge.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Merge Sort Divisions:
            O(log N) levels

        Counting Reverse Pairs:
            O(N) per level

        Merge:
            O(N) per level

        Total:
            O(N log N)

    -------------------------------------------------------

    📦 Space Complexity

        Temporary Array:
            O(N)

        Recursive Call Stack:
            O(log N)

        Total Auxiliary Space:
            O(N)

    -------------------------------------------------------

    🎯 One Line

        "Count reverse pairs during merge using two sorted halves, then merge them back."
*/
class Solution {
public:

    int checkReversePairs(vector<int> &nums, int start, int mid , int end)
    {
        int left = start ; 
        int right = mid+1; 
        int cnt = 0 ;
        while(left <= mid)
        {
            while(right <= end &&  nums[left] > 1LL * 2*nums[right] )
            {
                right++;
            }
            cnt = cnt + (right - (mid+1)  );
            left++;
        }
        return cnt;
    }

    int merge(vector<int> &nums, int start, int mid, int end)
    {
        int left = start; 
        int right = mid+1; 
        vector<int> temp; 
        int cnt = 0 ; 
        cnt = checkReversePairs(nums,  start , mid ,  end);

        while(left <= mid && right <= end)
        {
            if(nums[left] <= nums[right])
            {
                temp.push_back(nums[left]);
                left++;
            }
            else
            {
                
                temp.push_back(nums[right]);
                right++;
            }
        }
        while(left<=mid)
        {
            temp.push_back(nums[left]);
            left++;
        }
        while(right<=end)
        {
            temp.push_back(nums[right]);
            right++;
        }

        for(int i = start ; i<= end ; i++)
        {
            nums[i] = temp[i - start ] ;
        }

        return cnt;
    }

    int mergeSort(vector<int> &nums, int start, int end )
    {
        int cnt = 0; 
        if(start >= end)
        {
            return cnt ; 
        }

        int mid = (start+ end) / 2;

        cnt += mergeSort(nums, start , mid);
        cnt+= mergeSort(nums, mid+1, end);

        cnt+= merge(nums, start, mid , end);

        return cnt;

    }
    int reversePairs(vector<int>& nums) {
        int n = nums.size();

        return mergeSort(nums, 0, n-1);
    }
};