// https://takeuforward.org/data-structure/count-good-numbers

/*
    🧮 What I learned from this problem (Math + Implementation)

    ------------------------------------------------------

    1. Multiplication Principle (Core Idea)

    - If one step has A choices
      and next step has B choices

      → Total ways = A × B

    Example:
        2 shirts × 3 pants = 6 combinations

    👉 In this problem:
        - Each index has fixed choices
        - So total = multiply choices of all indices

    ------------------------------------------------------

    2. Applying to this problem

    - Even index → 5 choices {0,2,4,6,8}
    - Odd index  → 4 choices {2,3,5,7}

    Example (n = 3):
        index 0 → 5
        index 1 → 4
        index 2 → 5

        total = 5 × 4 × 5 = 100

    ------------------------------------------------------

    3. General Formula

    Count how many even and odd positions:

        even positions = (n + 1) / 2
        odd positions  = n / 2

    So:

        total = 5^(even) × 4^(odd)

    ------------------------------------------------------

    4. Why MOD is necessary

    - Numbers grow extremely fast:
        5^25 ≈ 10^17
        20^25 ≈ 10^32

    - This exceeds long long limit (~10^18)

    👉 Without MOD:
        → overflow
        → wrong answers / runtime error

    ------------------------------------------------------

    5. Why MOD must be applied at EVERY multiplication

    ❌ Wrong:
        result = a * b * c % MOD

        (overflow happens before MOD)

    ✅ Correct:
        result = ((a % MOD) * (b % MOD)) % MOD

    In fast power:
        base = (base * base) % MOD
        result = (result * base) % MOD

    👉 This keeps values small at every step

    ------------------------------------------------------

    🎯 Final Insight:

    - Count choices instead of generating
    - Multiply independent choices
    - Use fast exponentiation + MOD to handle large values
*/

class Solution {
public:

    long long power(long long base, long long exponent, int &MOD)
    {
        if(exponent == 0)
        {
            return 1;
        }
        if(exponent ==1 )
        {
            return base;
        }

        if(exponent%2 == 0)
        {
            return  power((base*base)%MOD, exponent/2, MOD);
        }
        else
        {
            return ((base)* power(base, exponent-1, MOD))% MOD;
        }
    }
    int countGoodNumbers(long long n) {
       
        
        int MOD = 1000000007;

        return (power(5, (n+1)/2, MOD) * power(4, (n/2), MOD)) % MOD;


    }
};