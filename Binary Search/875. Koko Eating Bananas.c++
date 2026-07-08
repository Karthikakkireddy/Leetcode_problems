// https://leetcode.com/problems/koko-eating-bananas/description/

/*
    🔴 Optimal

    🧠 Idea:
        - The eating speed can range from:
              1 banana/hour to max(piles) bananas/hour.
        - Use Binary Search on this range.
        - For every candidate speed k, compute the total
          hours required to finish all piles.
        - If the total hours are within h, try a smaller
          speed.
        - Otherwise, increase the speed.

    -------------------------------------------------------

    Why This Works

        If:

            totalHours <= h

            - Current speed is sufficient.
            - Store it as the current best answer.
            - Search for a smaller valid speed.

        If:

            totalHours > h

            - Current speed is too slow.
            - Search for a larger speed.

        Binary Search finds the minimum valid speed.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Finding Maximum Pile:
            O(N)

        Binary Search:
            O(log M)
            where M = maximum pile size

        Checking Time for One Speed:
            O(N)

        Total:
            O(N log M)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Use Binary Search on the eating speed and check whether all bananas can be eaten within h hours."
*/
class Solution {
public:
    long long checkTime(vector<int> &piles, int k){
        long long totalTime = 0;

        for(auto x : piles){
            long long num = x/(1LL * k);
            totalTime += num;

            if((x%k) != 0){
                totalTime = totalTime+1;
            }
        }

        return totalTime;
    }
    int minEatingSpeed(vector<int>& piles, int h) {

        int maxi = INT_MIN;

        for(auto x : piles)
            {
                maxi = max(maxi, x);
            }

        int start = 1;
        int end = maxi;
        int mini = INT_MAX;

        while(start<=end)
            {
                int mid =(start + end) /2;

                long long totalHours = checkTime(piles, mid);

                if(totalHours <= h)
                {
                    mini = mid;
                    end = mid -1;
                }
                else{
                    start = mid +1;
                }
            }

        return mini;
    }
};