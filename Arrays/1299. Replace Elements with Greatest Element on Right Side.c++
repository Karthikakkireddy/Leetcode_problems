// https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/description/



/*
🔴 Replace Elements with Greatest Element on Right Side

🧠 Idea:
- Traverse from right to left.
- Maintain the maximum element seen so far on the right.
- Replace the current element with that maximum.
- Then update the maximum using the original value.

🧠 Example:
arr = [17,18,5,4,6,1]

Start:

maxi = -1

i = 5:
    arr[5] = -1
    maxi = 1

i = 4:
    arr[4] = 1
    maxi = 6

i = 3:
    arr[3] = 6
    maxi = 6

i = 2:
    arr[2] = 6
    maxi = 6

i = 1:
    arr[1] = 6
    maxi = 18

i = 0:
    arr[0] = 18
    maxi = 18

Result:
[18,6,6,6,1,-1]

🧠 Why temp?
- arr[i] is overwritten before updating maxi.
- temp preserves the original value.

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:
"Traverse from right to left while keeping track of the maximum seen so far."
*/
class Solution {
public:
    vector<int> replaceElements(vector<int>& arr) {
        int n= arr.size();

        // vector<int> v(n);
        int maxi = -1;
        for(int i = n-1 ; i>=0 ; i--)
        {
            int temp = arr[i];

            arr[i] = maxi; 
            
            maxi = max(maxi, temp);
            
        }

        return arr;
    }
};