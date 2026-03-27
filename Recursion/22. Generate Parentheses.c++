// https://leetcode.com/problems/generate-parentheses/description/


/*
    Approach: Backtracking

    Idea:
    - We build the string step by step.
    - At each step, we can add:
        → '('  if we still have left parentheses remaining
        → ')'  only if it won't make the string invalid

------------------------------------------------------

    Key Rules:

    1. We can add '(' if:
            left < n

    2. We can add ')' if:
            right < left

       (ensures valid parentheses structure)

------------------------------------------------------

    Base Case:

        if(left == n && right == n)
            → valid combination formed
            → add to result

------------------------------------------------------

    Why This Works:

    - Ensures we NEVER create invalid strings.
    - We only build valid sequences instead of generating
      all possibilities and filtering later.

------------------------------------------------------

    Example (n = 2):

        ""
        ├── "("
        │   ├── "(("
        │   │   └── "(())"
        │   └── "()"
        │       └── "()()"

------------------------------------------------------

    Time Complexity: O(Catalan(n))

    - Number of valid combinations is:
            (1 / (n+1)) * (2n choose n)

    - Much smaller than 2^(2n)

------------------------------------------------------

    Space Complexity: O(n)

    - Recursion depth + temporary string

------------------------------------------------------

    Key Insight:

    - This is NOT simple subset generation.
    - Constraints (left >= right) prune invalid paths early.

------------------------------------------------------

    Final Takeaway:

    ✔ Only valid sequences are generated
    ✔ Efficient due to pruning
    ✔ Standard backtracking pattern
*/
class Solution {
public:
    vector<string> res;
    void generateParenthesisHelper(int n , int left , int right, string &s)
    {
        if(left == n && right == n)
        {
            res.emplace_back(s);
            return;
        }
        if(left < n)
        {
            s.push_back('(');
            generateParenthesisHelper(n, left + 1, right , s);
            s.pop_back();
        }
        if(left > right )
        {
            s.push_back(')');
            generateParenthesisHelper(n, left , right + 1 , s);
            s.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        string s = "";
        int left = 0 ;
        int right = 0; 
        
        generateParenthesisHelper(n, left ,right , s);
        return res;
    }
};