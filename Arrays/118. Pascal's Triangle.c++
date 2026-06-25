// https://leetcode.com/problems/pascals-triangle/description/


class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res; 
        res.push_back({1});

        for(int i= 2 ; i <= numRows ; i++)
        {
            vector<int> previousRow = res.back(); 

            vector<int> v; 
            for(int j= 0 ; j < i ; j++)
            {

                if(j == 0 || j == i-1)
                {
                    v.emplace_back(1);
                }
                else
                {
                    v.emplace_back( previousRow[j-1] + previousRow[j] );
                }
            }
            res.emplace_back(v);
        }

        return res;
    }
};


