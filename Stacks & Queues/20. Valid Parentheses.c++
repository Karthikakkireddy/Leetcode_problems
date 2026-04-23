// https://leetcode.com/problems/valid-parentheses/description/

/*
🔴 Valid Parentheses (Stack)

🧠 Idea:
- Opening brackets → push
- Closing brackets → must match top of stack

--------------------------------------------

Flow:

1. If opening:
       push to stack

2. If closing:
       - stack should NOT be empty
       - top should match current bracket
       - if yes → pop
       - else → invalid

--------------------------------------------

🧠 Your trick:

mp mapping:
    '(' → 1, ')' → 2
    '{' → 3, '}' → 4
    '[' → 5, ']' → 6

👉 Matching condition:
    opening + 1 == closing

--------------------------------------------

⚠️ Important check:

    if stack empty and closing comes
        → invalid

--------------------------------------------

After loop:

    if stack empty → valid
    else → invalid

--------------------------------------------

🧠 Mental Model:

    "Every closing must cancel the latest opening"

--------------------------------------------

⚡ Complexity:

Time → O(N)
Space → O(N)

--------------------------------------------

🎯 One line:

"Push openings, match & pop on closings"
*/
class Solution {
public:
    bool isValid(string s) {
        stack<char> stck;
        map<char, int> mp = {
            {'(', 1},
            {')', 2},
            {'{',3},
            {'}',4},
            {'[',5},
            {']',6}
        };
        for(int i=0; i< s.length() ; i++)
        {
            if(s[i] == '(' || s[i] == '{' || s[i] == '[')
            {
                stck.push(s[i]);
            }
            else
            {

                if(!stck.empty() && mp[stck.top()]+1 == mp[s[i]])
                {
                    stck.pop();
                }
                else
                {
                    return false;
                }
            }
        }
        if(stck.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

/*
🔴 Valid Parentheses (Cleaner Mapping Version)

🧠 Idea:
- Map closing → corresponding opening
- Use stack to track openings

--------------------------------------------

Flow:

1. If opening bracket:
       push to stack

2. If closing bracket:
       - stack should NOT be empty
       - top must match mapped opening
       - if yes → pop
       - else → invalid

--------------------------------------------

🧠 Key Improvement over previous code:

OLD:
    used numbers (1,2,3...) and +1 trick ❌

NEW:
    direct mapping:
        ')' → '('
        '}' → '{'
        ']' → '['

👉 More readable and safer

--------------------------------------------

⚠️ Important condition:

    stk.top() == mp[curr_char]

👉 ensures correct pairing

--------------------------------------------

After loop:

    return stk.empty()

👉 if anything left → unmatched opening

--------------------------------------------

🧠 Mental Model:

    "Closing bracket should match the last opening"

--------------------------------------------

⚡ Complexity:

Time → O(N)
Space → O(N)

--------------------------------------------

🎯 One line:

"Map closing → opening, then match with stack top"
*/
class Solution {
public:
    bool isValid(string s) {
        map<char, char> mp = 
        {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        stack<char> stk; 

        for(int i =0 ; i< s.length() ; i++)
        {

            char curr_char = s[i];

            if(curr_char == '(' || curr_char == '{' ||  curr_char == '[')
            {
                stk.push(curr_char);
            }
            else
            {
                if(!stk.empty() && stk.top() == mp[curr_char])
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
            }
        }
        return stk.empty();
    }
};

/*
🔴 Same logic as before, but:

👉 We DID NOT use map here

- Instead of mapping closing → opening,
  we directly checked conditions using if statements

✔ Less overhead
✔ Slightly faster
✔ More direct control

🎯 One line:
"Manual matching instead of using map"
*/
class Solution {
public:
    bool isValid(string s) {
       

        stack<char> stk; 

        for(char ch : s)
        {
            if(ch == '(' || ch == '{' || ch == '[')
            {
                stk.push(ch);
            }
            else
            {
                if(stk.empty())
                {
                    return false; 
                }
                
                if 
                (
                    ch == ')' && stk.top()!= '(' ||
                    ch == '}' && stk.top() != '{'||
                    ch == ']' && stk.top() != '['
                )
                {
                    return false; 
                }
                else
                {
                    stk.pop();
                }
            }
        }
        return stk.empty();
    }
};