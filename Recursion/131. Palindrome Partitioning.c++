// https://leetcode.com/problems/palindrome-partitioning/description/

//   ⚠️ Important Note (Optimization Insight):

//     👉 This solution is NOT fully optimal

//     Reason:
//         - isPalindrome() runs in O(N) time
//         - It is called repeatedly for overlapping substrings

//    

//     📁 Practical Note:

//     👉 This implementation focuses on recursion/backtracking
//     👉 Optimized DP version should be maintained separately
//        (e.g., in DP folder)

/*
    🔴 Problem: Palindrome Partitioning (LeetCode 131)

    ------------------------------------------------------

    🧠 What this code is doing:

    - We are splitting the string into ALL possible partitions
    - Such that EVERY substring in the partition is a palindrome

    Example:
        s = "aab"

        Output:
            ["a","a","b"]
            ["aa","b"]

    ------------------------------------------------------

    🧭 High-level idea (Backtracking):

    At each index:
        → Try all possible substrings starting from that index
        → If substring is palindrome:
            - pick it
            - recurse for remaining string
            - backtrack

    ------------------------------------------------------

    🔍 isPalindrome(index, i, s)

    - Checks if substring from index → i is palindrome

    Logic:
        Compare characters from both ends
        Move inward

    Time: O(N) per check

    ------------------------------------------------------

    🔁 partitionHelper(...)

    Parameters:

    - index → where we are currently in string
    - partition → current path (list of chosen substrings)
    - ans → final result

    ------------------------------------------------------

    🧱 Base Case:

        if(index == s.length())
            ans.emplace_back(partition);

    👉 Meaning:
        We have used the entire string
        → current partition is valid
        → store it

    ------------------------------------------------------

    🔄 Main loop:

        for(int i = index; i < s.length(); i++)

    👉 Try all substrings starting from index:

        index → i

    ------------------------------------------------------

    ✅ Condition:

        if(isPalindrome(index, i, s))

    👉 Only proceed if substring is valid palindrome

    ------------------------------------------------------

    📌 Choosing substring:

        s.substr(index, i - index + 1)

    👉 IMPORTANT:
        substr(start, length)
        length = i - index + 1

    ------------------------------------------------------

    🔁 Recursive call:

        partitionHelper(..., i + 1)

    👉 Move to next part of string

    ------------------------------------------------------

    🔙 Backtracking:

        partition.pop_back();

    👉 Undo the choice
        → try next substring

    ------------------------------------------------------

    🧠 Dry Run (s = "aab"):

    index = 0

    i = 0 → "a" ✔
        → ["a"]
        index = 1

            i = 1 → "a" ✔
                → ["a","a"]
                index = 2

                    i = 2 → "b" ✔
                        → ["a","a","b"] ✅

            i = 2 → "ab" ❌

    i = 1 → "aa" ✔
        → ["aa"]
        index = 2

            i = 2 → "b" ✔
                → ["aa","b"] ✅

    ------------------------------------------------------

    ⚡ Time Complexity:

        O(2^N * N)

        - 2^N → number of partitions
        - N → palindrome check + substring

    ------------------------------------------------------

    ⚡ Space Complexity:

        O(N)
        - recursion stack
        - temp partition

        + O(result) for storing answers

    ------------------------------------------------------

    🎯 Key Insights:

    ✔ Try ALL partitions (backtracking)
    ✔ Only continue if substring is palindrome (pruning)
    ✔ Backtrack after recursion

    ------------------------------------------------------

    ⚠️ Common mistakes (you already hit one):

    ❌ Wrong substring usage:
        substr(index, i+1)

    ✅ Correct:
        substr(index, i - index + 1)

    ------------------------------------------------------

    🧠 Pattern recognition:

    This is classic:
        "Partition + Validation + Backtracking"

    Similar to:
        - Combination Sum
        - Subsets
        - Word Break

*/
class Solution {
public:

    bool isPalindrome(int index, int i , string s)
    {
        while(index <= i)
        {
            if(s[index] != s[i])
            {
                return false;
            }
            index++; 
            i--;
        }
        return true;
    }

    void partitionHelper(vector<vector<string>> &ans, vector<string> &partition, string s, int index)
    {
        if(index == s.length())
        {
            ans.emplace_back(partition);
            return ; 
        }
      
        for(int i = index; i < s.length(); i++)
        {    
            if(isPalindrome(index, i, s))
            {
                partition.emplace_back(s.substr(index, i - index + 1));
                partitionHelper(ans, partition, s, i + 1);
                partition.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<string> partition;
        vector<vector<string>> ans; 

        partitionHelper(ans, partition, s, 0);
        return ans;
    }
};


// ------------------------------------------------------

//     🚀 Optimized Approach (DP + Backtracking):

//     - We can precompute a DP table:

//         dp[i][j] = true if substring s[i..j] is palindrome

//     - This reduces palindrome check from:
//             O(N) → O(1)

//     - Then use same backtracking with dp table

//     ------------------------------------------------------