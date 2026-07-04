// https://leetcode.com/problems/search-in-rotated-sorted-array/description/


/*
    🔴 Brute Force

    🧠 Idea:
        - Traverse the array from left to right.
        - Compare each element with the target.
        - If a match is found, return its index.
        - If the traversal completes without finding
          the target, return -1.

    -------------------------------------------------------

    Why This Works

        - Linear Search examines every element until
          the target is found.
        - If the target exists, its index is returned.
        - Otherwise, all elements are checked and -1
          is returned.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Best Case:
            O(1)
            (Target is the first element.)

        Worst Case:
            O(N)
            (Target is the last element or absent.)

        Total:
            O(N)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Perform a linear search and return the index of the target if found."
*/
class Solution {
public:
    int search(vector<int>& nums, int target) {
        
        for(int i=0; i< nums.size() ; i++)
        {
            if(nums[i] == target)
            {
                return i;
            }
        }

        return -1;
    }
};

/*
    🔴 Optimal

    🧠 Idea:
        - Use Binary Search on the rotated sorted array.
        - In every iteration, at least one half of the
          array is guaranteed to be sorted.
        - Determine which half is sorted and check
          whether the target lies within that range.
        - Discard the other half and continue searching.

    -------------------------------------------------------

    Why This Works

        If Left Half is Sorted:

            arr[start] <= arr[mid]

            - If target lies within this range,
              search the left half.

            - Otherwise,
              search the right half.

        If Right Half is Sorted:

            arr[mid] <= arr[end]

            - If target lies within this range,
              search the right half.

            - Otherwise,
              search the left half.

        Since one half is discarded every iteration,
        Binary Search is preserved.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Binary Search:
            O(log N)

        Total:
            O(log N)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Identify the sorted half in each iteration and use Binary Search to eliminate half of the search space."
*/
class Solution {
public:
    int search(vector<int>& arr, int x) {
        
        int start = 0 ; 
        int end = arr.size()-1; 

        while(start <= end)
        {
            int mid = (start + end ) / 2; 
            cout << start << " : " << mid << " : " << end << "\n";
            if(arr[mid] == x)
            {
                return mid;
            }
            else if(arr[start] <= arr[mid])
            {
                if(arr[start] <= x && x <= arr[mid])
                {
                    end = mid -1;
                }
                else
                {
                    start = mid + 1;
                }
            }
            else if(arr[mid] < arr[end])
            {
                if(arr[mid] <= x && x<= arr[end])
                {
                    start = mid + 1;
                }
                else
                {
                    end = mid -1;
                }
            }
        }

        return -1;
    }
};