// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

/*
🔴 Best Time to Buy and Sell Stock (Brute Force)

🧠 Idea:
- Treat every day as a buying day.
- For each buying day, try every future day as a selling day.
- Calculate profit and keep track of the maximum profit.

🧠 Example:
prices = [7,1,5,3,6,4]

Buy at 1:
    Sell at 5 → profit = 4
    Sell at 6 → profit = 5 ✅

Answer = 5

⚠️ Note:
- This solution checks every possible buy-sell pair.
- It gave TLE (Time Limit Exceeded) for large inputs because
  the number of comparisons grows very quickly.

⏱️ TC: O(N²)
📦 SC: O(1)

🎯 One line:
"Try every possible buy day with every future sell day and keep the maximum profit."
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxi = 0;
        int n = prices.size();

        for(int i =0 ; i< n-1 ; i++)
        {
            for(int j = i+1 ; j< n; j++)
            {
                maxi = max(maxi , prices[j] - prices[i]);
            }
        }

        return maxi;
    }
};

/*
🔴 Best Time to Buy and Sell Stock (Optimal)

🧠 Idea:
- Traverse from left to right.
- Keep track of the minimum stock price seen so far.
- Treat the current day as the selling day.
- Calculate profit if sold today:

      prices[i] - minimumStock

- Update the maximum profit.

🧠 Example:
prices = [7,1,5,3,6,4]

7:
    min = 7
    profit = 0

1:
    min = 1
    profit = 0

5:
    profit = 5 - 1 = 4

3:
    profit = 3 - 1 = 2

6:
    profit = 6 - 1 = 5 ✅

4:
    profit = 4 - 1 = 3

Answer = 5

🧠 Traversals:
- Single traversal of the array.
- For each day:
    1. Update minimum stock till date.
    2. Calculate profit if sold today.

⏱️ TC: O(N)
📦 SC: O(1)

🎯 One line:
"Keep the cheapest buying price so far and compute the profit for each selling day."
*/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxi = 0;
        int minimumStock = prices[0];
        int n = prices.size();

        for(int i =0 ; i< n ; i++)
        {
            minimumStock = min(minimumStock , prices[i]);
            maxi = max(maxi , prices[i] - minimumStock);
            
        }

        return maxi;
    }
};