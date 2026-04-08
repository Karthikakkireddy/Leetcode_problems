// https://leetcode.com/problems/sudoku-solver/description/



/*
    🧠 What this code does:

    - Solves Sudoku using BACKTRACKING
    - Try placing numbers → go forward → if stuck → backtrack

    ------------------------------------------------------

    🔥 Core Idea:

    - Find an empty cell ('.')
    - Try numbers from '1' → '9'
    - Check if valid
    - Place number
    - Recursively solve rest
    - If fails → remove number (backtrack)

    ------------------------------------------------------

    🧩 solveSudokuHelper():

    - Traverse entire board
    - As soon as you find EMPTY cell:
        → Try all digits 1 to 9
        → If any works → move forward
        → If none works → return false (trigger backtracking)

    ------------------------------------------------------

    ⚠️ VERY IMPORTANT:

    👉 The moment you find ONE empty cell:
        - You must fill it correctly before moving ahead

    👉 That’s why:
        return false is inside the loop

    ------------------------------------------------------

    🔍 isValid():

    Checks 3 things:

    1. Row check
    2. Column check
    3. 3x3 subgrid check  ← MOST IMPORTANT PART

    ------------------------------------------------------

    🧠 Row Check:

        if(board[row][i] == c)

        → Is number already present in that row?

    ------------------------------------------------------

    🧠 Column Check:

        if(board[i][column] == c)

        → Is number already present in that column?

    ------------------------------------------------------

    🔥 3x3 Subgrid Check (IMPORTANT):

        board[ 3*(row/3) + (i/3) ][ 3*(column/3) + (i%3) ]

    ------------------------------------------------------

    🧠 Understanding 3x3 logic (THIS IS THE KEY)

    Step 1 → Identify which 3x3 box we are in

        row = 5, col = 7

        row/3 = 1
        col/3 = 2

    So starting point of box:

        startRow = 3 * (row/3) = 3 * 1 = 3
        startCol = 3 * (col/3) = 3 * 2 = 6

    👉 So box starts at:
        (3,6)

    ------------------------------------------------------

    🧠 Now we need to traverse ALL 9 cells in this box

    We use single loop i = 0 → 8

    Mapping:

        i = 0 → (0,0)
        i = 1 → (0,1)
        i = 2 → (0,2)

        i = 3 → (1,0)
        i = 4 → (1,1)
        i = 5 → (1,2)

        i = 6 → (2,0)
        i = 7 → (2,1)
        i = 8 → (2,2)

    ------------------------------------------------------

    🧠 How we get this mapping:

        row offset → i/3
        col offset → i%3

    ------------------------------------------------------

    🧠 Final formula:

        actualRow = startRow + (i/3)
        actualCol = startCol + (i%3)

    👉 So:

        board[ 3*(row/3) + (i/3) ][ 3*(column/3) + (i%3) ]

    ------------------------------------------------------

    🧪 Dry Run Example:

    Suppose:

        row = 5, col = 7

    startRow = 3
    startCol = 6

    Loop i:

        i=0 → (3+0, 6+0) → (3,6)
        i=1 → (3+0, 6+1) → (3,7)
        i=2 → (3+0, 6+2) → (3,8)

        i=3 → (3+1, 6+0) → (4,6)
        i=4 → (4,7)
        i=5 → (4,8)

        i=6 → (5,6)
        i=7 → (5,7)
        i=8 → (5,8)

    👉 Covers entire 3x3 box

    ------------------------------------------------------

    🔁 Backtracking Flow:

        - Place number
        - Go deeper
        - If fail → undo ('.')
        - Try next number

    ------------------------------------------------------

    ⏱ Time Complexity:

        Roughly O(9^(empty cells))

        - Each empty cell tries 9 options

    ------------------------------------------------------

    🧠 Space Complexity:

        O(1)

        - Board modified in-place
        - Recursion stack exists but constant board size

    ------------------------------------------------------

    🎯 Final Insight:

        This is NOT brute force blindly

        👉 isValid() prunes invalid paths early
        👉 That makes it feasible

*/
class Solution {
public:

    bool isValid(vector<vector<char>>& board, int row, int column, char c)
    {
        for(int i=0 ; i<9 ; i++)
        {
            if(board[row][i] == c) // Vertical checking 
            {
                return false;
            }
            if(board[i][column] == c) // Horizontal checking 
            {
                return false;
            }

            if(board[ 3* (row/3) + (i/3)][ 3* (column/3) + (i%3)] == c) // Sub 3*3 Matrix checking 
            {
                return false;
            }
        }
        return true;
    }

    bool solveSudokuHelper(vector<vector<char>>& board)
    {
        for(int i=0 ; i< board.size() ; i++)
        {
            for(int j=0 ; j< board[0].size(); j++)
            {
                if(board[i][j] == '.') // Empty cell 
                {
                    for(char c= '1' ; c<='9' ; c++) // Try all the possible numbers on that empty cell
                    {
                        if(isValid(board, i, j , c)) // Check if I keep the number by checking with 3 rules
                        {
                            board[i][j] = c;

                            if(solveSudokuHelper(board)) // It goes forward with next empty cell and then eventually all the number are covered that means the suduko is solved and I do not need to check next possible answer.
                                return true;
                            else // In case I cannot move on with the current number I need to backtrack
                                board[i][j] = '.';
                        }
                    }
                    return false; // This means I cannot keep any numbers in the empty cell. Thus I need to say to my parent function call to backtrack
                }
            }
        }
        return true;
    }

    void solveSudoku(vector<vector<char>>& board) {
        solveSudokuHelper(board);
    }
};