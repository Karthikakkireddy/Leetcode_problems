/*
    Problem link - https://leetcode.com/problems/string-to-integer-atoi/description/
*/

/*
    This problem can be even solved iteratively 
    Recursion is not optimal solution
*/

/*
    Approach: Recursion + Simulation

    Idea:
    - Simulate how atoi works:
        1. Ignore leading spaces
        2. Handle optional sign (+ / -)
        3. Convert digits into a number
        4. Stop when a non-digit is found
        5. Clamp result within 32-bit integer range

------------------------------------------------------

    Helper Function (myAtoiHelper)

    - Processes the string recursively digit by digit.
    - Builds the number using:
            num = num * 10 + current_digit

    - Stops when:
        • end of string is reached
        • a non-digit character is found

------------------------------------------------------

    Overflow Handling

    - Before going deeper, we check:
            sign * num <= INT_MIN
            sign * num >= INT_MAX

    - If overflow is detected, return boundary values:
            INT_MIN (-2147483648)
            INT_MAX (2147483647)

------------------------------------------------------

    Why This Works

    - Recursion processes digits one by one,
      similar to iterative parsing.
    - Each step builds the number safely.

------------------------------------------------------

    Time Complexity: O(N)

    - Each character is processed at most once.

    Space Complexity: O(N)

    - Due to recursion stack.
*/

class Solution {
public:
    
    int myAtoiHelper(string &s, int index , double num, int sign)
    {
        if(index >= s.length() || !isdigit(s[index]) )
        {
            return (int) (sign * num);
        }

        num = (s[index] - '0')  + num* 10;

        if (sign * num <= -2147483648) return -2147483648;
        if (sign * num >= 2147483647) return 2147483647;

        return myAtoiHelper(s, index+1, num, sign);
    }

    int myAtoi(string s) {
        
        int index = 0;
        int sign = 1 ;
        for(int i=0 ;  i < s.length() ; i++)
        {
            if(s[i] != ' ')
            {
                index = i;
                break;
            }
        }

        if(s[index] == '-')
        {
            sign = -1;
            index++;
        }
        else if(s[index] == '+')
        {
            sign = 1;
            index++;
        }

        return myAtoiHelper(s, index, 0, sign);
    }
};