// https://leetcode.com/problems/shortest-distance-to-target-string-in-a-circular-array/description/?envType=daily-question&envId=2026-04-15



/*
🔴 Closest Target in Circular Array

🧠 Idea:
- Array is circular → can move LEFT or RIGHT
- Find minimum steps to reach target

------------------------------------------------------

📌 Step 1:
If startIndex itself is target → return 0

------------------------------------------------------

📌 Step 2: Move RIGHT

- Start from startIndex
- Keep moving:
        (i + 1) % n
- Count steps (right++)
- Stop when:
        → target found OR
        → we come back to startIndex

------------------------------------------------------

📌 Step 3: Move LEFT

- Start from startIndex
- Keep moving:
        (i - 1 + n) % n   // avoid negative
- Count steps (left++)
- Stop when:
        → target found OR
        → we come back to startIndex

------------------------------------------------------

🧠 Why "do-while"?

- Ensures at least one movement
- Needed because starting index already checked

------------------------------------------------------

📌 Step 4:

If BOTH directions returned to startIndex:
    → target not present
    → return -1

Else:
    → return min(left, right)

------------------------------------------------------

🧠 Circular Movement:

RIGHT:
    i = (i + 1) % n

LEFT:
    i = (i - 1 + n) % n

👉 +n prevents negative index

------------------------------------------------------

⚡ Complexity:

Time  → O(N)
Space → O(1)

------------------------------------------------------

🎯 Mental Model:

"From start, expand both directions in a circle and pick the closest"

------------------------------------------------------

⚠️ Subtle point:

- You are doing TWO independent searches
- Worst case → full traversal twice → still O(N)

------------------------------------------------------

🎯 One line:

"Check distance in both circular directions and take minimum"
*/
class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {
        if(words[startIndex] == target)
            return 0;
        

        int right = 0 ;
        int right_i = startIndex; 
        int left = 0; 
        int left_i = startIndex; 
        int n = words.size() ; 

        do{
            if(words[right_i] == target)
            {
                break;
            }
            right++; 
            right_i = (right_i+1) % n;
        }while(right_i!=startIndex);

        do{
            if(words[left_i] == target)
            {
                break;
            }
            left++; 
            left_i = (left_i - 1+ n) % n;
        }while(left_i!=startIndex);

        if(left_i == startIndex && right_i == startIndex)
        {
            return -1; 
        }

        return min(left, right);
    }
};