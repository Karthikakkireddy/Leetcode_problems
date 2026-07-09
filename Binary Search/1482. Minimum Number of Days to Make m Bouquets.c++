// https://leetcode.com/problems/minimum-number-of-days-to-make-m-bouquets/description/

/*
    🔴 Brute Force

    🧠 Idea:
        - Try each possible day starting from day 1.
        - For every day, traverse the array and count
          consecutive flowers that have bloomed.
        - Whenever k consecutive flowers are found,
          form one bouquet.
        - If m bouquets can be formed, return the
          current day.

    -------------------------------------------------------

    Why This Works

        - Each day simulates the state of the garden.
        - Only flowers with:

              bloomDay[i] <= currentDay

          are considered bloomed.

        - Consecutive bloomed flowers are grouped to
          form bouquets.

        - The first day on which m bouquets can be
          formed is the minimum answer.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Finding Maximum Bloom Day:
            O(N)

        Simulating Every Day:
            O(MaxBloomDay)

        Traversing the Array Each Day:
            O(N)

        Total:
            O(N × MaxBloomDay)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Simulate each day and return the first day on which m bouquets of k consecutive flowers can be formed."
*/

class Solution {
public:

    
    int check(vector<int> & bloomDay,int m,  int k, int longest)
    {
        int n = bloomDay.size() ; 
        int counter = 0 ; 
        for(int i = 1 ; i<= longest ; i++)
        {
            int requiredNumberOfBoquet = m;
            for(int j = 0 ; j< n ; j++)
            {
                if(bloomDay[j] != -1 && bloomDay[j] <= i )
                {
                    counter++; 
                    if(counter == k)
                    {
                        requiredNumberOfBoquet = requiredNumberOfBoquet-1; 
                        if(requiredNumberOfBoquet==0)
                        {
                            return i;
                        }
                        counter = 0; 
                    }
                }
                else
                {
                    counter = 0; 
                }

            }
            counter = 0; 
        }
        return -1;
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        int longest = INT_MIN;
        for(auto x : bloomDay)
        {
            longest = max(longest, x);
        }

        return check(bloomDay, m, k , longest);
    }
};