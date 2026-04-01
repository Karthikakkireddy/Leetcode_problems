// https://leetcode.com/problems/count-good-numbers/description/

/*
    ⚠️ IMPORTANT NOTE:

    This problem *can* be solved using recursion/backtracking,
    but that approach is NOT optimal.

    ------------------------------------------------------

    Why recursion fails:

    - Recursion generates all possible valid strings
    - Total combinations ≈ 20^(n/2)
    - For large n (up to 10^15), this becomes impossible (TLE)

    👉 So recursion is only useful for:
        - Understanding the problem
        - Very small inputs

    ------------------------------------------------------

    Optimal approach:

    - This is a mathematical counting problem
    - Use:
        total = 5^(even positions) * 4^(odd positions)

    - Implement using fast exponentiation (O(log n))

    ------------------------------------------------------

    Conclusion:

    ✔ This file contains recursion-based thinking
    ❌ But NOT the optimal solution

    👉 Optimal solution is implemented separately
*/


/*
    What I tried:

    - I used recursion to generate all possible valid strings.
    - At each index:
        even index → try {0,2,4,6,8} → 5 choices
        odd index  → try {2,3,5,7} → 4 choices

    - When index == n → increment count

    ------------------------------------------------------

    Why this works for small n:

    - For n = 1,2,3 → total combinations are small
    - So recursion completes quickly

    ------------------------------------------------------

    Why this fails (TLE):

    - Total number of recursive calls:

        ≈ 5^(ceil(n/2)) * 4^(floor(n/2))
        ≈ 20^(n/2)

    - For n = 50:

        ≈ 20^25 ≈ 10^32 calls ❌

    - This is exponential growth → impossible to compute

    ------------------------------------------------------

    Core mistake:

    - I treated this as a "generate all combinations" problem
    - But the problem only asks for COUNT

    👉 Generating everything is unnecessary and too expensive

    ------------------------------------------------------

    Key realization:

    - Each position is independent
    - So instead of recursion:

        total = 5^(even positions) * 4^(odd positions)

    ------------------------------------------------------

    Final insight:

    👉 If the problem asks only for COUNT,
       avoid generating all possibilities

    👉 Use math instead of recursion when combinations explode
*/
class Solution {
public:

    void countGoodNumbersHelper(long long n, string &curr ,long long  index , long long &count, vector<char> &primeNumber )
    {
       
        if(index == n)
        {
           
           count = (count + 1) % 1000000007;
            return ;
        }

        if(index%2 == 0)
        {

            for(int i=0; i<=8 ; i=i+2)
            {

                curr.push_back(i + '0');
                // cout << curr << "\n";
                    countGoodNumbersHelper(n, curr , index+1, count, primeNumber);
                curr.pop_back();
            }
        }
        else
        {

            for(int i=0; i< primeNumber.size() ; i++)
            {
                curr.push_back(primeNumber[i]);
                // cout << curr << "\n";

                countGoodNumbersHelper(n, curr , index+1, count, primeNumber);
                curr.pop_back();
            }
        }
    }
    int countGoodNumbers(long long n) {
        long long count = 0 ;
        long long index = 0 ; 
        string curr = "";
        vector<char> primeNumber = {'2','3','5','7'}; 


        
        countGoodNumbersHelper(n, curr, index, count, primeNumber);

        return count;
    }
};

/*
    What changed in this version:

    - Instead of using a global/reference `count`,
      you made recursion return the count directly.

    👉 This is GOOD
    - Cleaner
    - No side effects
    - More functional style

    ------------------------------------------------------

    What this code is doing:

    - At each index:
        even index → try 5 digits
        odd index  → try 4 digits

    - Recursively explore all possibilities
    - Each valid string contributes "1"
    - Final answer = sum of all paths

    ------------------------------------------------------

    Why this still gives TLE:

    - Total recursive calls:

        T(n) = 5 * 4 * 5 * 4 * ... (n times)
             ≈ 20^(n/2)

    - For n = 50:

        ≈ 20^25 ≈ 10^32 ❌

    👉 Even though code is clean,
       the algorithm is still exponential

    ------------------------------------------------------

    Important realization:

    - You removed mutable state (good)
    - But did NOT reduce the number of calls (bad)

    👉 Clean code ≠ efficient code

    ------------------------------------------------------

    Hidden inefficiency:

    - `string curr` is completely unnecessary
    - You are building strings but never using them

    👉 Extra overhead + memory operations

    ------------------------------------------------------

    Core mistake:

    - Still treating it like a backtracking problem
    - But this is a pure counting problem

    ------------------------------------------------------

    Final takeaway:

    - This version is structurally better than previous
    - But fundamentally still exponential → TLE

    👉 Optimization requires changing the IDEA,
       not just cleaning the implementation
*/
class Solution {
public:

    int countGoodNumbersHelper(long long n, string &curr ,long long  index  )
    {
       
        if(index == n)
        {
            return 1;
        }

        int result = 0; 
        const int MOD = 1000000007;
        if(index%2 == 0)
        {

            for(int digit : {0,2,4,6,8})
            {

                curr.push_back(digit + '0');
                // cout << curr << "\n";
                    result = (result + countGoodNumbersHelper(n, curr , index+1)) % MOD;
                curr.pop_back();
            }
        }
        else
        {

            for(int digit : {2,3,5,7})
            {
                curr.push_back(digit + '0');
                // cout << curr << "\n";

                result = (result + countGoodNumbersHelper(n, curr , index+1)) % MOD;
                curr.pop_back();
            }
        }

        return result;
    }
    int countGoodNumbers(long long n) {
       
        long long index = 0 ; 
        string curr = "";
        return countGoodNumbersHelper(n, curr, index);


    }
};