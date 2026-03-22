/*
    Problem link - https://leetcode.com/problems/powx-n/description/
*/

/*
    Approach: Brute Force (Simple Recursion)

    Idea:
    - Multiply x with itself n times.
    - If n is negative:
        → compute x^|n|
        → take reciprocal (1 / result)

    Example:
        x = 2, n = 3
        → 2 * 2 * 2 = 8

------------------------------------------------------

    Why This Works

    - Directly follows definition:
            x^n = x * x * x ... (n times)

------------------------------------------------------

    Why This Fails for Large Inputs

    1. Time Complexity: O(N)
        - We make n recursive calls.
        - For large n (e.g. 10^9), this is too slow → TLE.

    2. Stack Overflow Risk
        - Each recursive call uses stack space.
        - Deep recursion (large n) can crash the program.

    3. Integer Overflow Issue
        - When n = INT_MIN (-2^31),
          doing (n * -1) overflows.
        - Because INT_MAX < |INT_MIN|.

------------------------------------------------------

    Time Complexity: O(N)

    Space Complexity: O(N)
    - Due to recursion stack.
*/

class Solution {
public:

    double myPowHelper(double x, double number)
    {
        if(number == 0 )    
            return 1;

        return x * myPowHelper(x, number -1);
    }
    double myPow(double x, int n) {
       
        double res ;
        if(n < 0 )
        {
            res = myPowHelper(x, n* -1);
            res = 1 / res;
        }
        else
        {   
            res = myPowHelper(x, n);
        }
        
        return res;
        
    }
};


/*
    Approach: Fast Exponentiation (Binary Exponentiation)

    Idea:
    - Instead of multiplying x n times,
      reduce the exponent by half each time.

    Key Observation:
        x^n
        = (x^2)^(n/2)          if n is even
        = x * x^(n-1)          if n is odd

    This drastically reduces the number of operations.

------------------------------------------------------

    Example:

        x = 2, n = 10

        2^10
        → (2^2)^5 = 4^5
        → 4 * 4^4
        → 4 * (4^2)^2 = 4 * 16^2
        → ...

    Instead of 10 multiplications → only ~log N steps.

------------------------------------------------------

    Why This Works

    - Each step reduces exponent:
            n → n/2  (for even case)

    - So total steps become:
            log₂(n)

------------------------------------------------------

    Handling Negative Powers

    - Convert n to long long to avoid overflow (INT_MIN case)
    - If n < 0:
            x^(-n) = 1 / x^n

------------------------------------------------------

    Time Complexity: O(log N)

    - Exponent is halved each step.

    Space Complexity: O(log N)

    - Due to recursion stack.

------------------------------------------------------

    Why This is Better than Brute Force

    - Brute force → O(N)
    - This approach → O(log N)

    Huge improvement for large n.
*/
class Solution {
public:

    double myPowHelper(double base, long exponent)
    {
        if(exponent == 0 || base == 1)
            return 1;
        if(exponent == 1 )
            return base;
        
        double res ;
        if(exponent%2 == 0)
        {
            res = myPowHelper(base* base , exponent/2);
        }
        else
        {
            res = base * myPowHelper(base, exponent-1);
        }
        return res;

    }
    double myPow(double x, int n) {
        long long num = n; // To handle case of int overflow in -ve integer
        double res ;
        if(n < 0 )
        {
            res = myPowHelper(x, num* -1);
            res = 1 / res;
        }
        else
        {   
            res = myPowHelper(x, num);
        }
        
        return res;
        
    }
};