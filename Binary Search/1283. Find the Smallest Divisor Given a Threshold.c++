// https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/description/

/*
    🔴 Brute Force

    🧠 Idea:
        - Try every possible divisor from 1 to the
          largest element in the array.
        - For each divisor, compute the sum of:

              ceil(nums[i] / divisor)

          for every element.
        - Return the first divisor whose total sum is
          less than or equal to the threshold.

    -------------------------------------------------------

    Why This Works

        - Every possible divisor is checked in
          increasing order.
        - The first divisor satisfying the threshold
          condition is the smallest valid divisor.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Finding Largest Element:
            O(N)

        Trying Every Divisor:
            O(MaxElement)

        Computing Sum for One Divisor:
            O(N)

        Total:
            O(N × MaxElement)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Try every possible divisor and return the first one whose rounded division sum is within the threshold."
*/
class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        
        int largestNumber = INT_MIN; 

        for(auto x : nums)
        {
            largestNumber = max(largestNumber, x);
        }

        for(int divisor= 1 ; divisor<= largestNumber ; divisor++)
        {
            int sum = 0 ;

            for(int j = 0 ; j<nums.size() ; j++)
            {
                int quotient = nums[j] / divisor;
                int remainder = nums[j] % divisor; 
                int result; 

                remainder ?  result = (quotient +1) :  result =  quotient ;

                sum+= result;
            }

            if(sum <= threshold)
            {
                return divisor;
            }
        }

        return -1;
    }
};






/*
    🔴 Optimal

    🧠 Idea:
        - The divisor lies between:
              1 and the largest element in the array.
        - Use Binary Search on this range.
        - For every candidate divisor, compute:

              ceil(nums[i] / divisor)

          for every element and sum the results.
        - If the total sum is within the threshold,
          try a smaller divisor.
        - Otherwise, increase the divisor.

    -------------------------------------------------------

    Why This Works

        Checking a Divisor:

            - Divide every element by the divisor.
            - Round up the result.
            - Add all rounded values.

        If:

            sum <= threshold

            - Current divisor is valid.
            - Store it as the current answer.
            - Search for a smaller valid divisor.

        Else:

            - Current divisor is too small.
            - Search for a larger divisor.

        Since increasing the divisor always decreases
        (or keeps the same) the resulting sum,
        Binary Search can be applied.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Finding Largest Element:
            O(N)

        Binary Search:
            O(log MaxElement)

        Checking One Divisor:
            O(N)

        Total:
            O(N log(MaxElement))

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Use Binary Search on the divisor and check whether the rounded division sum is within the threshold."
*/
class Solution {
public:

    int divisorFunction(vector<int>& nums, int divisor)
    {
        int sum = 0 ;

        for(int j = 0 ; j<nums.size() ; j++)
        {
            int quotient = nums[j] / divisor;
            int remainder = nums[j] % divisor; 
            int result; 

            remainder ?  result = (quotient +1) :  result =  quotient ;

            sum+= result;
        }      
        return sum; 
    }
    int smallestDivisor(vector<int>& nums, int threshold) {
        
        int largestNumber = INT_MIN; 

        for(auto x : nums)
        {
            largestNumber = max(largestNumber, x);
        }

        int start =1 ; 
        int end =largestNumber;

        int res = INT_MAX;
        while(start<= end)
        {
            int mid = (start + end) /2;

            int resultSum = divisorFunction(nums, mid);

            if(resultSum <= threshold)
            {
                res = mid;
                end = mid - 1;
            }
            else
            {
                start = mid  + 1; 
            }

        }
        return res;
    }
};