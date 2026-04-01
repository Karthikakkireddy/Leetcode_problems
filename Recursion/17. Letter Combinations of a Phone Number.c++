// https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/

/*
    Approach: Backtracking (Digit → Letters mapping)

------------------------------------------------------

    What we are trying to do:

    - Each digit maps to multiple letters (like phone keypad)
    - For each digit, we must choose ONE letter
    - Build all possible combinations

------------------------------------------------------

    Core idea:

        At index i:
            try all letters mapped to digits[i]

        Move to next index (i+1)

------------------------------------------------------

    Base Case:

        if(s.length() == digits.length())
        {
            ans.push_back(s);
            return;
        }

    👉 When we pick one letter for each digit,
        we get a valid combination

------------------------------------------------------

    Important observation (BUG in your code):

        You wrote:

            for(int i = index; i < digits.length(); i++)

        ❌ This is unnecessary and incorrect

        Why?
            - At each recursion, we only care about ONE digit
            - Not a range of digits

------------------------------------------------------

    Correct thinking:

        Use ONLY:

            digits[index]

        NOT loop over digits

------------------------------------------------------

    What your code is currently doing:

    - It is mixing:
        ✔ subset-style looping
        ❌ with fixed-position recursion

    👉 This leads to:
        - redundant calls
        - incorrect structure
        - potential duplicates / inefficiency

------------------------------------------------------

    Correct recursion structure:

        At index:
            get letters for digits[index]

            for each letter:
                add letter
                recurse to index+1
                remove letter

------------------------------------------------------

    Example:

        digits = "23"

        Mapping:
            2 → abc
            3 → def

        Tree:

            ""
            ├── a
            │   ├── ad
            │   ├── ae
            │   └── af
            ├── b
            │   ├── bd
            │   ├── be
            │   └── bf
            └── c
                ├── cd
                ├── ce
                └── cf

------------------------------------------------------

    Time Complexity:

        O(4^N)

        - Each digit can map to up to 4 letters
        - Total combinations = product of choices

------------------------------------------------------

    Space Complexity: O(N)

        - Recursion depth = digits length

------------------------------------------------------

    Key Takeaway:

    ✔ This is NOT subset pattern
    ✔ This is "fixed-position choice" pattern
    ✔ One digit → many choices → move forward

    ❌ Remove outer loop over digits
*/
class Solution {
public:
    void letterCombinationsHelper(vector<string> &ans, 
                                string &digits, int index, string &s, map<int, string> &mp)
    {

        if(s.length() == digits.length())
        {
            ans.push_back(s);
            return;
        }
            
        for(int i = index ; i < digits.length() ; i++)
        {
            string digitToLetter = mp[digits[index] - '0'];

            for(int j = 0; j < digitToLetter.length() ; j++)
            {
                s.push_back(digitToLetter[j]);
                letterCombinationsHelper(ans, digits, i+1, s, mp);
                s.pop_back();
            }

        }
    }
    vector<string> letterCombinations(string digits) {
         map<int, string> mp = 
         {
            {2, "abc"},
            {3, "def"},
            {4, "ghi"},
            {5, "jkl"},
            {6, "mno"},
            {7, "pqrs"},
            {8, "tuv"},
            {9, "wxyz"}
         }; 
        vector<string> ans;
         int index = 0 ; 
         string s = "";
        letterCombinationsHelper(ans, digits, index, s, mp);

        return ans;
    }
};

/*
    Approach: Backtracking (Fixed Position Choice)

------------------------------------------------------

    What we are doing:

    - Each digit represents a FIXED position
    - For each position, we choose one letter

    👉 Build the string one position at a time

------------------------------------------------------

    Key idea:

        At index:
            get letters for digits[index]

            for each letter:
                add letter
                go to next index

------------------------------------------------------

    Base Case:

        if(s.length() == digits.length())
        {
            ans.emplace_back(s);
            return;
        }

    👉 When we fill all positions → valid combination

------------------------------------------------------

    How recursion flows:

        digits = "23"

        index = 0 → '2' → "abc"
            pick 'a' → index = 1 → '3' → "def"
                → "ad", "ae", "af"

            pick 'b'
                → "bd", "be", "bf"

            pick 'c'
                → "cd", "ce", "cf"

------------------------------------------------------

    Why this works:

    ✔ Each level handles ONE digit
    ✔ No skipping, no reordering
    ✔ Depth = number of digits

------------------------------------------------------

    Important difference from subsets:

        Subsets:
            loop over indices (i = index → n)

        Here:
            NO loop over digits
            only process current index

------------------------------------------------------

    Time Complexity: O(4^N)

    - Each digit has up to 4 choices

------------------------------------------------------

    Space Complexity: O(N)

    - Recursion depth = digits length

------------------------------------------------------

    Edge Case (you missed this):

        if(digits == "")
            return {}

    👉 Otherwise you'll push empty string

------------------------------------------------------

    Final Takeaway:

    ✔ This is a "position-based recursion"
    ✔ Not subset / combination pattern
    ✔ One digit → many choices → move forward
*/
class Solution {
public:
    void letterCombinationsHelper(vector<string> &ans, 
                                string &digits, int index, string &s, map<int, string> &mp)
    {

        if(s.length() == digits.length())
        {
            ans.emplace_back(s);
            return ; 
        }

        string currentLettersFromDigit = mp[digits[index] - '0'];
        for(int i = 0 ; i<currentLettersFromDigit.length() ; i++)
        {
            s.push_back(currentLettersFromDigit[i]);
            letterCombinationsHelper(ans, digits, index+1, s , mp);
            s.pop_back();
        }

    }
    vector<string> letterCombinations(string digits) {
         map<int, string> mp = 
         {
            {2, "abc"},
            {3, "def"},
            {4, "ghi"},
            {5, "jkl"},
            {6, "mno"},
            {7, "pqrs"},
            {8, "tuv"},
            {9, "wxyz"}
         }; 
        vector<string> ans;
         int index = 0 ; 
         string s = "";
        letterCombinationsHelper(ans, digits, index, s, mp);

        return ans;
    }
};






class Solution {
public:
    void letterCombinationsHelper(vector<string> &ans, 
                                string &digits, int index, string &s, vector<string> &v)
    {
        // 🔄 CHANGED: Better base condition
        // Before: s.length() == digits.length()
        // Now: index == digits.length()
        // 👉 More natural → “processed all digits”
        if(index == digits.length())
        {
            ans.emplace_back(s);
            return ; 
        }

        // 🔄 CHANGED: Using vector instead of map
        // Before: mp[digits[index] - '0']
        // Now: v[digits[index] - '0']
        // 👉 O(1) direct access (faster than map lookup)

        // 🔄 CHANGED: const string & (no copy)
        // Before: string currentLettersFromDigit = ...
        // Now: const string &currentLettersFromDigit = ...
        // 👉 avoids copying string every recursion call
        // 👉 safer (cannot modify original)
        const string &currentLettersFromDigit = v[digits[index] - '0'];

        for(int i = 0 ; i<currentLettersFromDigit.length() ; i++)
        {
            s.push_back(currentLettersFromDigit[i]);

            // 🔄 SAME LOGIC: move to next digit
            letterCombinationsHelper(ans, digits, index+1, s , v);

            s.pop_back(); // backtrack
        }
    }

    vector<string> letterCombinations(string digits) {

        // 🔄 CHANGED: Added edge case
        // Before: no check → returned [""] for empty input ❌
        // Now: return {} ✔
        if(digits.empty()) 
            return {};

        // 🔄 CHANGED: map → vector
        // Before: map<int, string>
        // Now: vector<string>
        // 👉 faster (no log lookup)
        // 👉 cleaner indexing
        vector<string> v = {
            "","", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
        }; 

        vector<string> ans;

        // 🔄 CHANGED: removed unnecessary variable
        // Before: int index = 0;
        // Now: directly passing 0
        string s = "";

        letterCombinationsHelper(ans, digits, 0, s, v);

        return ans;
    }
};