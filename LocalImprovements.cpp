#include "LocalImprovements.h"

using namespace std;

TSPSolution twoOpt (TSPSolution solution, const Graph &g){
  int n = solution.tour.size();
  bool solutionImproved = true;
	while (solutionImproved) {
		solutionImproved = false;
		for (int i = 0; i <= n - 2; i++) {
			for (int j = i + 1; j <= n - 1; j++) {
        		int newCost = solution.cost 
							- g.getWeight(solution.tour[i], solution.tour[i+1]) - g.getWeight(solution.tour[j], solution.tour[(j+1) % n]) 
							+ g.getWeight(solution.tour[i], solution.tour[j]) + g.getWeight(solution.tour[i+1], solution.tour[(j+1) % n]);
        		//Only do the swap if it improves the solution
				if (newCost < solution.cost) {
					reverse(solution.tour.begin() + i + 1, solution.tour.begin() + j + 1);
          			solution.cost = newCost;
					solutionImproved = true;
				}
			}
		}
	} 

  return solution;
}