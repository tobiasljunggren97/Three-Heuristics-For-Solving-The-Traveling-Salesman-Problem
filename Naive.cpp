#include "Naive.h"



// Below is an implementation of the pseudocode from Kattis, this naive solution is 
// only used for testing and is not part of the final solution. 

TSPSolution naive(Graph &g) 
{
    int n = g.getN();
    TSPSolution sol(n);
    vector<int> used(n);
    int best = -1; 
    sol.tour[0] = 0; // Start in vertex 0. 
    used[0] = 1; 
    for (int i = 1; i < n; i++)
    {
        best = -1; 
        for (int j = 0; j < n; j++)
        {
            if (used[j] == 0 && (best == -1 || g.getWeight(sol.tour[i-1], j) < g.getWeight(sol.tour[i-1], best))) {
                best = j; 

            }
        }
        sol.tour[i] = best;
        used[best] = 1;          
    }
    return sol; 

}

