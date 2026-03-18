/*
    Problem link - https://leetcode.com/problems/power-of-two/description/?envType=problem-list-v2&envId=recursion
*/

/*
    Note on Approach:

    - This recursive solution is correct and intuitive,
      but not the most optimal.

    - Time Complexity  → O(log N)
    - Space Complexity → O(log N) (recursion stack)

    - Extra space is used due to recursion,
      which can be avoided using a non-recursive approach.
*/


/*
    Approach: Recursion

    Idea:
    - A number is a power of 2 if it can be repeatedly divided
      by 2 and eventually becomes 1.

    Steps:
    - If n == 1 → return true (base case).
    - If n is divisible by 2 → recurse on n/2.
    - Otherwise → not a power of 2.

    Why This Works:
    - Powers of 2 look like:
        1, 2, 4, 8, 16...
    - Dividing by 2 repeatedly should always land at 1.

    Time Complexity: O(log N)
    - We divide n by 2 each time.

    Space Complexity: O(log N)
    - Due to recursion stack.
*/
class Solution {
public:
    bool isPowerOfTwo(int n) {
        
        if( n==1)
        {
            return true;
        }
        if(n%2 == 0 && n!= 0)
        {
            return isPowerOfTwo(n/2);
        }
        else
        {
            return false;
        }
    }
};

/*
    Improvement over previous version:

    - Earlier code only checked:
            n % 2 == 0 && n != 0
      which indirectly handled some negative cases,
      but did NOT explicitly reject them.

    - That made the logic unclear:
        Negative numbers were handled accidentally,
        not intentionally.

------------------------------------------------------

    Key Fix:

        if(n <= 0)
            return false;

    Why this matters:

    - Power of 2 is defined ONLY for positive numbers.
    - This immediately rejects:
            0, -1, -2, -4, ...

    - Avoids unnecessary recursion on invalid inputs.
    - Makes the intent very clear.

------------------------------------------------------

    Why this version is cleaner:

    - Explicit validation step (n <= 0)
    - Clear base case (n == 1)
    - Simple recursive rule (divide by 2)

    Flow becomes:

        invalid → reject early
        base case → return true
        divisible → recurse
        else → false

    No hidden behavior, no accidental correctness.
*/
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<=0)
        {
            return false;
        }
        if( n==1)
        {
            return true;
        }
        if(n%2 == 0 )
        {
            return isPowerOfTwo(n/2);
        }
        else
        {
            return false;
        }
    }
};