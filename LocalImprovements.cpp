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

	int newCost = tmp.cost - g.getWeight(tmp.tour[i], tmp.tour[(i + 1) % n]) - g.getWeight(tmp.tour[j], tmp.tour[(j + 1) % n]) + g.getWeight(tmp.tour[i], tmp.tour[(j + 1) % n]) + g.getWeight(tmp.tour[j], tmp.tour[(i + 1) % n]);

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

		if (sol.cost == currentSol.cost)
		{
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

void copySolution(TSPSolution &solution, vector<int> &newTour, int &index, Graph &g, int start, int finish)
{
	if (start > finish) {
		for (int i = start+1; i < g.getN(); i++) {
			newTour[index] = solution.tour[i];
			index++; //Index gets incremented outside as well??????????????????
		}
		for (int j = 0; j < finish; j++) {
			newTour[index] = solution.tour[j];
			index++;
		}
	}
	else {
		for (int k = start+1; k < finish; k++) {
			newTour[index] = solution.tour[k];
			index++;
		}
	}
}

void copySolutionReversed(TSPSolution &solution, vector<int> &newTour, int &index, Graph &g, int start, int finish) 
{
	if (start < finish) {
		for (int i = start-1; i > 0 ; i--) {
			newTour[index] = solution.tour[i];
			index++;
		}
		for (int j = g.getN(); j > finish; j--) {
			newTour[index] = solution.tour[j];
			index++;
		}
	}
	else {
		for (int k = start-1; k > finish; k--) {
			newTour[index] = solution.tour[k];
			index++;
		}
	}
}

void changeSolution(TSPSolution &solution, Graph &g, int i, int j, int k, int variant)
{
	int n = g.getN(); 
	vector<int> newTour(n);
	int index = 0;
	switch (variant)
	{
	case 1:
		newTour[index] = solution.tour[j];
		index++;

		newTour[index] = solution.tour[k+1];
		index++;
		copySolution(solution, newTour, index, g, k+1, i);
		newTour[index] = solution.tour[i];
		index++;

		newTour[index] = solution.tour[j+1];
		index++;
		copySolution(solution, newTour, index, g, j+1, k);
		newTour[index] = solution.tour[k];
		index++;

		newTour[index] = solution.tour[i+1];
		index++;
		copySolution(solution, newTour, index, g, i+1, j);
		
		break;
	case 2:
		newTour[index] = solution.tour[j];
		index++;

		copySolutionReversed(solution, newTour, index, g, j, i+1);
		newTour[index] = solution.tour[i+1];
		index++;

		newTour[index] = solution.tour[k+1];
		index++;
		copySolution(solution, newTour, index, g, k+1, i);
		newTour[index] = solution.tour[i];
		index++;

		newTour[index] = solution.tour[j+1];
		index++;
		copySolution(solution, newTour, index, g, j+1, k);
		newTour[index] = solution.tour[k];
		index++;
		break;
	case 3:
		newTour[index] = solution.tour[j];
		index++;

		newTour[index] = solution.tour[k+1];
		index++;
		copySolution(solution, newTour, index, g, k+1, i);
		newTour[index] = solution.tour[i];
		index++;

		newTour[index] = solution.tour[k];
		index++;
		copySolutionReversed(solution, newTour, index, g, k, j+1);
		newTour[index] = solution.tour[j+1];
		index++;

		newTour[index] = solution.tour[i+1];
		index++;
		copySolution(solution, newTour, index, g, i+1, j);
		break;
	case 4:
		newTour[index] = solution.tour[j];
		index++;

		newTour[index] = solution.tour[i];
		index++;
		copySolutionReversed(solution, newTour, index, g, i, k+1);
		newTour[index] = solution.tour[k+1];
		index++;

		newTour[index] = solution.tour[j+1];
		index++;
		copySolution(solution, newTour, index, g, j+1, k);
		newTour[index] = solution.tour[k];
		index++;

		newTour[index] = solution.tour[i+1];
		index++;
		copySolution(solution, newTour, index, g, i+1, j);
		break;
	case 5:
		reverse(solution.tour.begin() + j + 1, solution.tour.begin() + k + 1);
		return;
	case 6:
		reverse(solution.tour.begin() + i + 1, solution.tour.begin() + k + 1);
		return;
	default: // Variant 7
		reverse(solution.tour.begin() + i + 1, solution.tour.begin() + j + 1);
		return;
	}
	solution.tour = newTour;
}

void printSolution1(TSPSolution &solution, Graph &g)
{
    int n = solution.tour.size();
    for(int i = 0; i < n-1; i++)
    {
        cout << solution.tour[i] << " -> "; 
    }
	cout << solution.tour[n-1] << endl;
}

int bestSolution(TSPSolution &solution, Graph &g, int i, int j, int k)
{
	int minAddedCost = numeric_limits<int>::max();
	int minVariant;
	int n = g.getN();
	int newCost = solution.cost - g.getWeight(solution.tour[i], solution.tour[(i + 1) % n]) - g.getWeight(solution.tour[j], solution.tour[(j + 1) % n]) - g.getWeight(solution.tour[k], solution.tour[(k + 1) % n]);

	int v1Cost = g.getWeight(solution.tour[i], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[j], solution.tour[(k + 1) % n]) + g.getWeight(solution.tour[k], solution.tour[(i + 1) % n]);
	int v2Cost = g.getWeight(solution.tour[i], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[k], solution.tour[j]) + g.getWeight(solution.tour[(i + 1) % n], solution.tour[(k + 1) % n]);
	int v3Cost = g.getWeight(solution.tour[j], solution.tour[(k + 1) % n]) + g.getWeight(solution.tour[i], solution.tour[k]) + g.getWeight(solution.tour[(j + 1) % n], solution.tour[(i + 1) % n]);
	int v4Cost = g.getWeight(solution.tour[j], solution.tour[i]) + g.getWeight(solution.tour[(k + 1) % n], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[k], solution.tour[(i + 1) % n]);

	// two opt (j, k)
	int v5Cost = g.getWeight(solution.tour[j], solution.tour[(k + 1) % n]) + g.getWeight(solution.tour[k], solution.tour[(j + 1) % n]);

	// two opt ( i, k)
	int v6Cost = g.getWeight(solution.tour[i], solution.tour[(k + 1) % n]) + g.getWeight(solution.tour[k], solution.tour[(i + 1) % n]);

	// two opt (i, j)
	int v7Cost = g.getWeight(solution.tour[i], solution.tour[(j + 1) % n]) + g.getWeight(solution.tour[j], solution.tour[(i + 1) % n]);

	vector<int> costs = {v1Cost, v2Cost, v3Cost, v4Cost, v5Cost, v6Cost, v7Cost};

	for (int i = 1; i <= costs.size(); i++)
	{
		if (costs[i - 1] < minAddedCost)
		{
			minAddedCost = costs[i - 1];
			minVariant = i;
		}
	}

	if (newCost + minAddedCost < solution.cost)
	{
		
		solution.cost = newCost + minAddedCost;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "Better solution found! New Cost is: " << solution.cost << endl; 
		cout << "Edges: " << solution.tour[i] << " - " << solution.tour[(i+1)%n] << " , " << solution.tour[j] << " - " << solution.tour[(j+1)%n] << " , " << solution.tour[k] << " - " << solution.tour[(k+1)%n] << endl; 
		cout << "Variant: v" << minVariant << endl;

		cout << "Previous path:" << endl; 
		printSolution1(solution, g); 
		changeSolution(solution, g, i, j, k, minVariant);
		cout << "New path:" << endl; 
		printSolution1(solution, g); 
		
		


		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		cout << "------------------------------------------------------------------------------" << endl;
		return 1;
	}
	return 0; 
}

void threeOpt(TSPSolution &solution, Graph &g)
{
	int N = solution.tour.size();
	int improved = 1;
	int tempImproved;
	// while (improved)
	// {
		improved = 0;

		for (int i = 0; i < N - 2; i++)
		{
			for (int j = i+1; j < N - 1; j++)
			{
				for (int k = j+1; k < N; k++)
				{
					tempImproved = bestSolution(solution, g, i, j, k);
					if (tempImproved == 1) {
						// cout << "are we improving? " << endl; 
						improved = tempImproved;
					}
				}
			}
		}
		
	// }
}