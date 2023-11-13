#include "Greedy.h"
#include "LocalImprovements.h"

TSPSolution nearestNeighbor(Graph &g, int startNode) {
    int numVertices = g.getN();
    if(startNode < 0 || startNode >= numVertices) {
        throw "Invalid start node";
    }
    int currentVertex = startNode;
    TSPSolution tspSolution = TSPSolution(numVertices);
    tspSolution.tour[0] = currentVertex;
    vector<int> visited(numVertices);
    visited[currentVertex] = 1;
    int counter = 1;
    const vector<int> weights;


    int minWeight = numeric_limits<int>::max();
    int currentWeight;
    int minWeightNode;
    while (counter < numVertices) {

        for (int i = 0; i < numVertices; i++) {
            if (i != currentVertex && !visited[i]) {
                currentWeight = g.getWeight(currentVertex, i);
                if (currentWeight < minWeight) {
                    minWeight = currentWeight;
                    minWeightNode = i;
                }
            }
        }

        tspSolution.tour[counter] = minWeightNode;
        visited[minWeightNode] = 1;
        tspSolution.cost += minWeight;
        minWeight = numeric_limits<int>::max();
        currentVertex = minWeightNode;
        counter++;
    }
    tspSolution.cost += g.getWeight(currentVertex, startNode);
    TSPSolution localImpr = twoOpt(tspSolution, g);
    return localImpr;
}

struct Node {
    Node *next;
    Node *prev;
    Node() {
        next = NULL;
        prev = NULL;
    }
};



TSPSolution tinyGraphEdgeCase(Graph &g){
    int n = g.getN();
    if(n == 2){
        TSPSolution solution;
        solution.tour = vector<int>(n);
        solution.cost = 0;
        solution.tour[0] = 0;
        solution.tour[1] = 1;
        solution.cost = g.getWeight(0, 1);
        return solution;
    } else {
        TSPSolution solution;
        solution.tour = vector<int>(n);
        solution.cost = 0;
        solution.tour[0] = 0;
        return solution;
    }
}


int findPrematureCycle(Node *node, int n, vector<Node> &nodes) {
    Node *currentNode = node;
    int counter = 0;
    int completeCycle = 0;
    
    while (currentNode != NULL) {
        currentNode = currentNode->next;
        counter++;
        if (currentNode == node) {
            if (counter != n) {
                // Cycle found but not full tour
                completeCycle = 1;
            } else {
                // Full tour found
                completeCycle = 2;
            }
            break;
        }
    }
    return completeCycle;
}



TSPSolution greedy(Graph &g) {
    int n = g.getN();
    if(n < 3){
        TSPSolution solution = tinyGraphEdgeCase(g);
        return solution;
    }


    int currentVertex = 0;

    // Sort all edges by weight
    vector<tuple<int, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (i != j) {
                edges.push_back(make_tuple(i, j));
            }
        }
    }
    sort(edges.begin(), edges.end(), [&](const tuple<int, int> &a, const tuple<int, int> &b) {
        return g.getWeight(get<0>(a), get<1>(a)) < g.getWeight(get<0>(b), get<1>(b));
    });

    TSPSolution solution;
    solution.tour = vector<int>(n);
    solution.cost = 0;
    vector<Node> nodes(n, Node());

    //Iterate through edges and add to tour if no cycle is formed
    for (int i = 0; i < edges.size(); i++) {
        tuple<int, int> edge = edges[i];
        Node *node1ptr = &nodes[get<0>(edge)];
        Node *node2ptr = &nodes[get<1>(edge)];
        if(node1ptr->next == NULL && node2ptr->prev == NULL) {
            node1ptr->next = node2ptr;
            node2ptr->prev = node1ptr;
            //Iterate through to see that a cycle is not formed
            int prematureCycle = findPrematureCycle(node1ptr, n, nodes);
            if(prematureCycle == 1) {
                node1ptr->next = NULL;
                node2ptr->prev = NULL;
            //Full tour found
            } else if(prematureCycle == 2) {
                break;
            }
        } else if(node1ptr->prev == NULL && node2ptr->next == NULL) {
            node1ptr->prev = node2ptr;
            node2ptr->next = node1ptr;
            //Iterate through to see that a cycle is not formed
            int prematureCycle = findPrematureCycle(node2ptr, n, nodes);
            if(prematureCycle == 1) {
                node1ptr->prev = NULL;
                node2ptr->next = NULL;
            //Full tour found
            } else if(prematureCycle == 2) {
                break;
            }
        }
    }

    Node *currentNode = &nodes[0];
    //Add to TSPSolution
    for(int i = 0; i < n; i++) {
        solution.tour[i] = currentNode - &nodes[0];
        solution.cost += g.getWeight(currentNode - &nodes[0], currentNode->next - &nodes[0]);
        currentNode = currentNode->next;
    }


    TSPSolution localImpr = twoOpt(solution, g);
    return localImpr;
}
