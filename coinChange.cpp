//Leet Code DP Problem
//Available at: https://leetcode.com/problems/coin-change-2/
//From video: https://www.youtube.com/watch?v=pwpOC1dph6U&list=PLl0KD3g-oDOGJUdmhFk19LaPgrfmAGQfo&index=3

//we use dp where dp[i][j] := the number of ways of having amount i using first j coin values
// dp[i][j] = dp[i][j-1] + dp[i-coins[j]][j]
class Solution {
#include <vector>
#include <cstring>
public:
    int change(int amount, vector<int>& coins) {
        if(amount == 0)
            return 1;
        
        int size = coins.size();
        if(size == 0)
            return 0;
        
        int dp[amount+1][size];
        for(int i = 0; i < amount+1; ++i)
            memset(dp[i], 0, sizeof(dp[i]));
        
        for(int i = 0; i < size; ++i)
        	dp[0][i] = 1;
        
        
        for(int i = 1; i <= amount; ++i)
        for(int j = 0; j < size; ++j){
        	if(j > 0)
            	dp[i][j] += dp[i][j-1];
            if(i >= coins[j] )
                dp[i][j] += dp[i - coins[j]][j];
        }
        return dp[amount][size-1];
    }
};