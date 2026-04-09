// https://leetcode.com/problems/word-search/description/


/*
    🔴 Problem: Word Search (LeetCode 79)

    ------------------------------------------------------

    🧠 What this code is doing:

    - We try to find if a given "word" exists in the board
    - We can move in 4 directions (left, up, right, down)
    - We cannot reuse the same cell (visited array)

    ------------------------------------------------------

    🧭 High-level idea:

    1. Start from every cell that matches word[0]
    2. From there, try to build the word character by character
    3. Use backtracking:
        → mark visited
        → explore neighbors
        → unmark if path fails

    ------------------------------------------------------

    ⚠️ Why this code feels heavy / unclean:

    Because:

    ❌ Multiple base cases
    ❌ Separate isSafe function
    ❌ Extra visited matrix
    ❌ Repeated checks (board[row][col] == word[index])
    
    👉 All these add cognitive load

    ------------------------------------------------------

    🔍 Let's break existHelper()

    ------------------------------------------------------

    Base Case 1:

        if(index == word.length())
            return true;

    👉 This means:
        We matched ALL characters successfully

    ⚠️ But in practice, this is redundant
       (because we already handle last character separately)

    ------------------------------------------------------

    Base Case 2 (IMPORTANT FIX):

        if(index == word.length()-1 && board[row][column] == word[index])
            return true;

    👉 Meaning:
        If current character matches AND it's the last character
        → we found the word → stop immediately

    👉 This fixes the 1x1 case like:
        [["a"]], "a"

    ------------------------------------------------------

    Matching condition:

        if(board[row][column] == word[index])

    👉 Only proceed if current cell matches current character

    ------------------------------------------------------

    Backtracking step:

        isVisited[row][column] = 1;

    👉 Mark current cell as used

    ------------------------------------------------------

    Explore all 4 directions:

        for(int i = 0; i < 4; i++)

    👉 Try moving in:
        left, up, right, down

    ------------------------------------------------------

    isSafe():

        - Checks boundaries
        - Ensures cell is not already visited

    👉 Prevents:
        ❌ going out of bounds
        ❌ revisiting same cell

    ------------------------------------------------------

    Recursive call:

        existHelper(..., index + 1)

    👉 Move to next character in word

    ------------------------------------------------------

    Early stopping:

        if(existHelper(...))
            return true;

    👉 As soon as one path works → stop everything

    ------------------------------------------------------

    Backtracking undo:

        isVisited[row][column] = 0;

    👉 Restore state so other paths can reuse this cell

    ------------------------------------------------------

    🔴 Why this feels "too heavy"

    Compared to cleaner version:

    ❌ Separate visited matrix (extra space + complexity)
    ❌ Separate isSafe() function (extra indirection)
    ❌ Multiple base cases (harder to reason)

    ------------------------------------------------------

    🧠 Cleaner mental model (what you're actually doing):

    At each cell:

        1. Check match
        2. If last char → return true
        3. Mark visited
        4. Try all 4 directions
        5. Undo (backtrack)

    ------------------------------------------------------

    ⚡ Time Complexity:

        O(N * M * 4^L)

        N*M → starting points
        4^L → branching (4 directions for each char)

    ------------------------------------------------------

    ⚡ Space Complexity:

        O(N * M) → visited matrix
        + O(L) → recursion stack

    ------------------------------------------------------

    🎯 Final takeaway:

    ✔ Logic is correct now
    ❌ Implementation is verbose
    👉 Can be simplified by:
        - removing isSafe()
        - using in-place marking instead of visited
        - reducing base cases

    ------------------------------------------------------
*/
class Solution {
public:

    bool isSafe(int checkRow, int checkCol, vector<vector<char>> &board, vector<vector<int>> &isVisited)
    {
        if(checkRow < 0 || checkCol < 0 || checkRow >= board.size() || checkCol >= board[0].size())
        {

            return false;
        }
        if(isVisited[checkRow][checkCol] == 1)
        {
            return false;
        }
        return true;
    }

    bool existHelper(   
                        vector<vector<char>> &board, 
                        int row, int column , 
                        vector<vector<int>> &isVisited,
                        vector<int> &rowCord, vector<int> &colCord,
                        int index,
                        string word
                    )
    {
        if(index == word.length())
        {

            return true; 
        }
        if(index == word.length()-1 && board[row][column] == word[index]) 
        {
            return true;
        }
        

        if(board[row][column] == word[index] )
        {
            isVisited[row][column] = 1; 
            for(int i =0 ; i<4 ;i++)
            {
                bool flag = isSafe(row+rowCord[i], column+colCord[i], board, isVisited);


                if(flag)
                {

                    if(existHelper(board, row+rowCord[i], column+colCord[i], isVisited, rowCord, colCord, index+1, word))
                    {
                        return true;
                    }
                    
                    
                }
            }
            
            isVisited[row][column] = 0;

         }
         return false;
    }
    bool exist(vector<vector<char>>& board, string word) {

        int rowsSize = board.size();
        int colSize = board[0].size();
        vector<int>  rowCord ={ 0, -1, 0, 1};
        vector<int> colCord = {-1, 0, 1, 0};

        vector<vector<int>> isVisited(rowsSize, vector<int>(colSize, 0));

        for(int i = 0 ; i< rowsSize ; i++)
        {
            for(int j= 0 ; j< colSize ; j++)
            {
                if(board[i][j] == word[0])
                {
                   
                    if(existHelper(board, i, j , isVisited, rowCord, colCord,0, word))
                    {
                        return true; 
                    }
                }
            }
        }
        return false;
    }
};