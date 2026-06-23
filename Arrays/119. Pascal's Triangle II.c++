// https://leetcode.com/problems/pascals-triangle-ii/description/


/*
🔴 Pascal's Triangle - Row Index (1st Approach Without formula)

🧠 Idea:
- Build Pascal's Triangle row by row.
- Start with the first row: [1].
- Every new row:
    - First and last elements are always 1.
    - Middle elements are the sum of the two elements
      directly above them from the previous row.

🧠 Example:

Row 0:
    [1]

Row 1:
    [1,1]

Row 2:
    [1,2,1]

Row 3:
    [1,3,3,1]

If rowIndex = 3

Answer:
    [1,3,3,1]

🧠 Why does:

    previousRow[j-1] + previousRow[j]

work?

For Pascal's Triangle:

          1
        1   1
      1   2   1
    1   3   3   1

Each middle element is formed by adding the two
elements above it.

Example:

    3 = 1 + 2
    3 = 2 + 1

⏱️ TC Analysis:

Rows generated:
    2 to (rowIndex + 1)

For row size k:
    Inner loop runs k times.

Total operations:

    2 + 3 + 4 + ... + (rowIndex + 1)

    = O(rowIndex²)

📦 SC Analysis:

previousRow:
    Stores at most (rowIndex + 1) elements

v:
    Stores at most (rowIndex + 1) elements

Extra variables:
    O(1)

Total Space:
    O(rowIndex)

🎯 One line:
"Build Pascal's Triangle row by row using the previous row."
*/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> previousRow = {1};

        for(int i = 2; i <= rowIndex +1 ; i++)
        {
            vector<int> v; 
            for(int j= 0; j< i; j++)
            {
                if(j==0 || j == i-1)
                {
                    v.push_back(1);
                }
                else
                {
                    v.push_back( previousRow[j-1] + previousRow[j] );
                }
            }
            previousRow = v;            
        }
        return previousRow;
    }
};

/*
🔴 Pascal's Triangle - Row Index (1st Approach with formula)

🧠 Idea:
- Every element in a row can be calculated using nCr.

For rowIndex = n:

    Row = nC0, nC1, nC2, ... , nCn

- Compute each nCr and store it in the result vector.

🧠 Example:

rowIndex = 3

3C0 = 1
3C1 = 3
3C2 = 3
3C3 = 1

Result:

[1,3,3,1]

🧠 Why compute nCr this way?

nCr = n! / (r! * (n-r)!)

Using factorials may overflow.

Instead:

    ans *= (R - i)
    ans /= (i + 1)

Builds the result incrementally while keeping numbers manageable.

⏱️ TC Analysis:

Outer Loop:
    Runs (rowIndex + 1) times

nCr(R, C):
    Runs C iterations

Total Work:

    nC0 -> 0 iterations
    nC1 -> 1 iteration
    nC2 -> 2 iterations
    ...
    nCn -> n iterations

Total:

    0 + 1 + 2 + ... + n

    = n(n+1)/2

    = O(n²)

where n = rowIndex

📦 SC Analysis:

Result Vector:
    Stores (rowIndex + 1) elements

Extra Variables:
    ans, i, etc. → O(1)

Total Space:

    O(rowIndex)

If output array is ignored:
    Auxiliary Space = O(1)

🎯 One line:
"Generate the row by computing each binomial coefficient independently."
*/
class Solution {
public:
    int nCr(int R, int C)
    {
        long long ans =1 ;
        for(long long i=0 ; i< C ; i++)
        {
            ans = ans * (R - i );
            ans = ans / ( i + 1 );
        }
        return ans; 
    }

    vector<int> getRow(int rowIndex) {
        vector<int> res;

        for(int i = 1 ; i <= rowIndex +1 ; i++)
        {
            res.push_back( nCr(rowIndex  , i-1 ) );
        }
        return res;
    }
};

/*
🔴 Pascal's Triangle - Row Index (Optimal)

🧠 Idea:
- Generate each element directly from the previous one.
- Use the relation:

      nCr = nC(r-1) * (n-r+1) / r

- Start with:
      nC0 = 1

- Generate the remaining elements one by one.

🧠 Example:

rowIndex = 4

N = 5

Start:
    1

Next:
    1 * 4 / 1 = 4

Next:
    4 * 3 / 2 = 6

Next:
    6 * 2 / 3 = 4

Next:
    4 * 1 / 4 = 1

Result:
    [1,4,6,4,1]

🧠 Why does:

    ans = ans * (N - i) / i

work?

Current ans stores:

    nC(i-1)

Using the relation:

    nCi = nC(i-1) * (n-i+1) / i

we derive the next element from the previous one
instead of recomputing nCr from scratch.

⏱️ TC Analysis:

Single loop:
    Runs (rowIndex) times

Work per iteration:
    O(1)

Total:
    O(rowIndex)

📦 SC Analysis:

Result vector:
    Stores (rowIndex + 1) elements

Extra variables:
    ans, N, i → O(1)

Total Space:
    O(rowIndex)

Auxiliary Space:
    O(1)

🎯 One line:
"Generate each Pascal Triangle element directly from the previous one using the nCr recurrence relation."
*/
class Solution {
public:
    vector<int> getRow(int rowIndex) {
        int N = rowIndex + 1 ;

        vector<int> res ; 
        res.push_back(1);
        long long  ans = 1; 

        for(int i = 1 ; i< N ; i++)
        {
            ans = ans * (N - i );
            ans = ans / ( i );

            res.push_back(ans);
        }

        return res;
    }
};