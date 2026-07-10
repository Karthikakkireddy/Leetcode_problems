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

/*
    🔴 Optimal

    🧠 Idea:
        - The answer lies between:
              0 and the maximum bloom day.
        - Use Binary Search on the number of days.
        - For each candidate day, check whether it is
          possible to make m bouquets.
        - If possible, try a smaller day.
        - Otherwise, search for a larger day.

    -------------------------------------------------------

    Why This Works

        Checking a Day:

            - Traverse the array.
            - Count consecutive flowers that have bloomed:

                  bloomDay[i] <= currentDay

            - Whenever k consecutive flowers are found,
              form one bouquet.

            - If m bouquets can be formed,
              the current day is valid.

        Since the feasibility changes monotonically
        (if bouquets can be made on day d, they can
        also be made on any day > d),
        Binary Search can be applied.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Finding Maximum Bloom Day:
            O(N)

        Binary Search:
            O(log MaxBloomDay)

        Checking One Day:
            O(N)

        Total:
            O(N log(MaxBloomDay))

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    ⚠️ Note

        Before applying Binary Search, check:

            if ((long long)m * k > bloomDay.size())
                return -1;

        If the required number of flowers exceeds the
        total flowers available, forming the bouquets
        is impossible.

    -------------------------------------------------------

    🎯 One Line

        "Use Binary Search on the number of days and check whether m bouquets can be formed on each candidate day."
*/
class Solution {
public:

    
    bool check(vector<int> & bloomDay, int m,  int k, int currentDay)
    {
        int n = bloomDay.size() ; 
        int counter = 0 ; 
        
        int requiredNumberOfBoquet = m;
        for(int j = 0 ; j< n ; j++)
        {
            if(bloomDay[j] != -1 && bloomDay[j] <= currentDay )
            {
                counter++; 
                if(counter == k)
                {
                    requiredNumberOfBoquet = requiredNumberOfBoquet-1; 
                    if(requiredNumberOfBoquet==0)
                    {
                        return true;
                    }
                    counter = 0; 
                }
            }
            else
            {
                counter = 0; 
            }

        }

        return false;
    }
    int minDays(vector<int>& bloomDay, int m, int k) {
        int longest = INT_MIN;
        for(auto x : bloomDay)
        {
            longest = max(longest, x);
        }

        int start = 0 ; 
        int end = longest ;
        int mini = -1; 
        while(start <= end)
        {
            int mid = (start + end) /2; 

            bool flag =  check(bloomDay, m, k , mid);

            if(flag == false)
            {
                start = mid+ 1;
            }
            else
            {
                mini = mid; 
                end = mid -1; 
            }

        }
        return mini ;
    }
};