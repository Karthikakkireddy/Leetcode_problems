https://leetcode.com/problems/minimum-distance-to-the-target-element/description/?envType=daily-question&envId=2026-04-13

/*
🔴 Find Minimum Distance to Target

🧠 Idea:
- Traverse entire array
- Whenever nums[i] == target:
      compute distance from start
- Keep track of minimum distance

--------------------------------------------

Distance calculation:

    abs(i - start)

👉 You manually did:
    i - start > 0 ? i-start : (i-start)*-1

⚠️ Could be simplified using abs()

--------------------------------------------

🧠 Flow:

for each index i:
    if nums[i] == target:
        update minimum distance

--------------------------------------------

⚡ Complexity:

Time → O(N)
Space → O(1)

--------------------------------------------

🎯 One line:

"Scan all target positions and take minimum distance"
*/
class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        
        int ans= INT_MAX ; 

        for(int i=0 ; i< nums.size() ; i++)
        {
            if(nums[i] == target )
            {
                ans =  min(i - start > 0 ? i-start : (i-start)*-1  , ans);
            }

        }

        return ans;
    }
};