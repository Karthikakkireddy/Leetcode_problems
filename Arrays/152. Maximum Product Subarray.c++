// https://leetcode.com/problems/maximum-product-subarray/description/

/*
    🔴 Brute Force

    🧠 Idea:
        - Consider every possible subarray.
        - Maintain the product while extending the subarray.
        - Update the maximum product after every extension.

    -------------------------------------------------------

    Why This Works

        - Every possible subarray is generated exactly once.
        - Instead of recomputing the product from scratch,
          keep multiplying the next element as the subarray
          grows.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Outer Loop:
            O(N)

        Inner Loop:
            O(N)

        Product Update:
            O(1)

        Total:
            O(N²)

    -------------------------------------------------------

    📦 Space Complexity

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Generate every subarray, maintain its product, and keep track of the maximum product."
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxi = INT_MIN; 
        int n = nums.size();

        for(int i =0 ; i< n ; i++)
        {
            int product = 1;
            for(int j = i ; j< n; j++)
            {
                product *= nums[j];
                maxi = max(maxi , product);
            }
        }

        return maxi;
    }
};


/*
    🔴 Optimal

    🧠 Idea:
        - Traverse the array from both directions
          simultaneously.
        - Maintain:
            - Prefix Product  (Left → Right)
            - Suffix Product  (Right → Left)
        - Update the maximum product using both.
        - Whenever a product becomes 0, reset it to 1
          and start a new subarray.

    -------------------------------------------------------

    Why This Works

        - A negative number can turn a small negative
          product into a large positive product.
        - By considering both prefix and suffix products,
          we handle cases with odd/even numbers of negatives.
        - Resetting after a zero starts a new subarray,
          since no subarray crossing a zero can have a
          non-zero product.

    -------------------------------------------------------

    ⏱️ Time Complexity

        Single Traversal:
            O(N)

        Product Updates:
            O(1)

        Total:
            O(N)

    -------------------------------------------------------

    📦 Space Complexity

        Prefix Product:
            O(1)

        Suffix Product:
            O(1)

        Extra Variables:
            O(1)

        Total Auxiliary Space:
            O(1)

    -------------------------------------------------------

    🎯 One Line

        "Maintain prefix and suffix products simultaneously, resetting at zeros, to find the maximum product subarray."
*/
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxi = INT_MIN; 
        int n = nums.size();

        for(int i =0 ; i< n ; i++)
        {
            int product = 1;
            for(int j = i ; j< n; j++)
            {
                product *= nums[j];
                maxi = max(maxi , product);
            }
        }

        return maxi;
    }
};