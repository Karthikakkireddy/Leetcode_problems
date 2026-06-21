// https://leetcode.com/problems/spiral-matrix/description/

/*
🔴 Spiral Matrix

🧠 Idea:
- Maintain four boundaries:
      top, bottom, left, right

- Traverse the current layer in clockwise order:
      1. Top row    → Left to Right
      2. Right col  → Top to Bottom
      3. Bottom row → Right to Left
      4. Left col   → Bottom to Top

- After each traversal, shrink the corresponding boundary.

------------------------------------------------------

Boundary Updates:

Top Row:
    top++

Right Column:
    right--

Bottom Row:
    bottom--

Left Column:
    left++

------------------------------------------------------

⚠️ Why:

    if(top <= bottom)

?

After traversing the top row and right column,
the matrix may have no remaining bottom row.

This check prevents visiting elements twice.

------------------------------------------------------

⚠️ Why:

    if(left <= right)

?

After shrinking boundaries,
there may be no remaining left column.

This check prevents duplicate traversal.

------------------------------------------------------

🧠 Example:

1 2 3
4 5 6
7 8 9

Layer 1:
    1 2 3
        6
    9 8 7
    4

Layer 2:
    5

Result:
[1,2,3,6,9,8,7,4,5]

------------------------------------------------------

⏱️ TC: O(M × N)

📦 SC: O(1)
(Output vector not counted)

------------------------------------------------------

🎯 One line:
"Traverse the matrix layer by layer while continuously shrinking the four boundaries."
*/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
       
        int top = 0 ; 
        int left= 0 ;
        int right = matrix[0].size()-1;
        int bottom = matrix.size()-1;


        vector<int> v;

        while(top<= bottom && left <= right)
        {
           for(int i= left; i<= right ; i++)
           {
                v.emplace_back(matrix[top][i]);
           }
           top++;

           for(int i= top ; i<= bottom ; i++)
           {
                v.emplace_back(matrix[i][right]);
           }
           right--;

           if(top <= bottom)
           {
                for(int i= right ; i>= left; i--)
                {
                    v.emplace_back(matrix[bottom][i]);
                }
                bottom--;
           }
           if(left <= right)
           {
                for(int i= bottom ; i >= top ; i--)
                {
                    v.emplace_back(matrix[i][left]);
                }
                left++;
           }
        }

        return v;
    }
};