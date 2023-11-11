#include "LocalImprovements.h"

using namespace std;

TSPSolution twoOpt(TSPSolution solution, Graph &g)
{
	int n = solution.tour.size();
	bool solutionImproved = true;
	while (solutionImproved)
	{
		solutionImproved = false;
		for (int i = 0; i <= n - 2; i++)
		{
			for (int j = i + 1; j <= n - 1; j++)
			{
				int newCost = solution.cost - g.getWeight(solution.tour[i], solution.tour[i + 1]) - g.getWeight(solution.tour[j], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[i], solution.tour[j]) + g.getWeight(solution.tour[i + 1], solution.tour[(j + 1) % n]);
				// int newCost = solution.cost - g.getWeight(solution.tour[i], solution.tour[(i + 1) % n]) - g.getWeight(solution.tour[j], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[i], solution.tour[(j+1)%n]) + g.getWeight(solution.tour[j], solution.tour[(i + 1) % n]);

				// Only do the swap if it improves the solution
				if (newCost < solution.cost)
				{
					reverse(solution.tour.begin() + i + 1, solution.tour.begin() + j + 1);
					solution.cost = newCost;
					solutionImproved = true;
				}
			}
		}
	}

	return solution;
}

double probabilityFunc(double oldCost, double newCost, double T)
{
	return exp(-((newCost - oldCost) / T));
}

// TSPSolution tinyTwoOpt(TSPSolution solution, Graph &g)
// {
// 	int n = solution.tour.size();
// 	// bool solutionImproved = true;
// 	// solutionImproved = false;

// 	for (int i = 0; i <= n - 2; i++)
// 	{
// 		for (int j = i + 1; j <= n - 1; j++)
// 		{
// 			int newCost = solution.cost - g.getWeight(solution.tour[i], solution.tour[i + 1]) - g.getWeight(solution.tour[j], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[i], solution.tour[j]) + g.getWeight(solution.tour[i + 1], solution.tour[(j + 1) % n]);
// 			// Only do the swap if it improves the solution
// 			reverse(solution.tour.begin() + i + 1, solution.tour.begin() + j + 1);
// 			solution.cost = newCost;
// 			// solutionImproved = true;
// 		}
// 	}
// 	return solution;
// }

TSPSolution tinyTwoOpt(TSPSolution solution, Graph &g, int i, int j)
{
	TSPSolution tmp = solution; 
	int n = tmp.tour.size();

	int newCost = tmp.cost - g.getWeight(tmp.tour[i], tmp.tour[(i + 1) % n]) - g.getWeight(tmp.tour[j], tmp.tour[(j + 1) % n]) + g.getWeight(tmp.tour[i], tmp.tour[(j+1)%n]) + g.getWeight(tmp.tour[j], tmp.tour[(i + 1) % n]);

	reverse(tmp.tour.begin() + i + 1, tmp.tour.begin() + j + 1);
	tmp.cost = newCost;

	return tmp;
}

TSPSolution simmulated_annealing_with_twoOpt(TSPSolution solution, Graph &g)
{

	TSPSolution currentSol = solution;
	random_device e;
	mt19937 gen(e());

	int keepLooking = 1;
	double p = -1.0;
	double T = 150000.0; // TODO: CHANGE!!
	double r = -1.0;
	double a = 0.99;

	int n = g.getN();
	int i = -1;
	int j = -1;
	int loopCounter = 0;
	cout << "INITIAL COST??? " << currentSol.cost << endl; 

	while (keepLooking)
	{
		loopCounter++;

		uniform_real_distribution<double> distribution(0.0, 1.0);
		uniform_int_distribution<int> distribution_int(0, g.getN());
		// gen.seed(static_cast<unsigned int>(time(0)));


		i = distribution_int(gen); // fetch random first node.
		j = distribution_int(gen);

		TSPSolution sol = tinyTwoOpt(currentSol, g, i, j);

		p = sol.cost <= currentSol.cost ? 1 : probabilityFunc(currentSol.cost, sol.cost, T);

		if (sol.cost == currentSol.cost) {
			cout << "suuuuuuuuuuh" << endl;
		}
		r = distribution(gen); // generate random number

		if (loopCounter < 5)
		{
			cout << "RANDOM I IS: " << i << endl;
			cout << "RANDOM j IS: " << j << endl;
			cout << "RANDOM r IS: " << r << endl;
			cout << "RANDOM p IS: " << p << endl;
			
		}

		if (r <= p)
		{
			goto add_new;
		}
		else
		{
			goto decrease_T;
		}

	add_new:
		cout << "ARE WE ADDING NEW SOLUTION?? YES!! " << endl; 

		currentSol.tour = sol.tour;
		currentSol.cost = sol.cost;

	decrease_T:
		T = T * a; // TODO: CHANGE!!!
		cout << "AT DECREASE t: WHAT IS T? " << T << endl;
		keepLooking = T < 100 ? 0 : 1; // TODO: CHANGE!!
	}
	cout << " FINISHED SIMMULATED ANNEALING, AMOUNT OF TIMES LOOPED: " << loopCounter << endl;
	return currentSol;
}