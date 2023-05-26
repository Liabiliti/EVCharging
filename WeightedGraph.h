/*
 * WeightedGraph.h
 *
 *  Created on: 29 Apr 2023
 *      Author: 2002345
 */
#ifndef H_weightedGraph
#define H_weightedGraph

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <queue>
#include <stack>

using namespace std;

class WeightedGraphType
{
protected:
	int gSize;		  // number of vertices
	list<int> *graph; // Store adjacency list
	double **weights; // Store weights of edges
public:
	WeightedGraphType(int size = 0);
	~WeightedGraphType();
	double getWeight(int i, int j)
	{
		return weights[i][j];
	}
	void printAdjacencyList();
	void printAdjacencyMatrix();
	list<int> breadthFirstTraversal(int key);
	vector<vector<double> > shortestPath(int vertex);
	double cheapestPath(int vertex, int destination);
};

WeightedGraphType::WeightedGraphType(int size)
{
	gSize = 0;
	ifstream infile;
	char fileName[50] = "Weights.txt";

	infile.open(fileName);

	if (!infile)
	{
		cout << "Cannot open input file." << endl;
		return;
	}

	gSize = size;

	graph = new list<int>[gSize]; /* The data type of graph would be list<int>, it would be a list of lists, the data to be stored
   would be the depth of each column, in the weights.txt, so if it was 7 deep, in ascending order the input would be:
	   0, 1, 2, 3, 4, 5, 6, 7*/

	weights = new double *[gSize]; /* This creates a 2d dynamic array of doubles, by using the key in the map
	 it will identify which column belongs to the location, so weights[0][1], according to the weights.txt would be equal to 8.5*/

	for (int i = 0; i < gSize; i++)
		weights[i] = new double[gSize];

	for (int i = 0; i < gSize; i++)
	{
		for (int j = 0; j < gSize; j++)
		{
			double value;
			infile >> value;
			if (value == 0)
				weights[i][j] = DBL_MAX; // system constant - maximum value of double
			else
			{
				weights[i][j] = value;
				graph[i].push_back(j);
			}
		}
	}
	infile.close();
}

WeightedGraphType::~WeightedGraphType()
{
	for (int i = 0; i < gSize; i++)
		delete[] weights[i];

	delete[] weights;

	for (int index = 0; index < gSize; index++)
		graph[index].clear();

	delete[] graph;
}

void WeightedGraphType::printAdjacencyMatrix()
{ // print adjacency matrix for debug purpose
	cout << "\nAdjacency Matrix" << endl;
	for (int i = 0; i < gSize; i++)
	{
		for (int j = 0; j < gSize; j++)
		{
			cout << setw(8) << (weights[i][j] == DBL_MAX ? 0.0 : weights[i][j]); // as adjacency value, zero means no direct connection
		}
		cout << endl;
	}
}

void WeightedGraphType::printAdjacencyList()
{ // print adjacency list for debug purpose
	cout << "\nAdjacency List" << endl;
	for (int index = 0; index < gSize; index++)
	{
		cout << index << ": ";
		for (auto e : graph[index])
			cout << e << " ";
		cout << endl;
	}

	cout << endl;
}

vector<vector<double> > WeightedGraphType::shortestPath(int vertex)
{
	vector<vector<double> > retrace(gSize, vector<double>());
	double *smallestWeight = new double[gSize];
	for (int j = 0; j < gSize; j++) // Initialising smallest weights with distance
	{
		retrace[0].push_back(0);
		retrace[1].push_back(0);
		smallestWeight[j] = weights[vertex][j];
		if(weights[vertex][j] != DBL_MAX)
			retrace[1][j] = vertex+1;
	}

	bool *weightFound;
	weightFound = new bool[gSize];

	for (int j = 0; j < gSize; j++) // Initialising bool array with false for all
		weightFound[j] = false;

	weightFound[vertex] = true; // Set starting vertex as false
	smallestWeight[vertex] = 0; // Set starting vertex as 0

	for (int i = 0; i < gSize - 1; i++) // For amount of vertices
	{
		double minWeight = DBL_MAX;
		int v;

		for (int j = 0; j < gSize; j++)			   // For amount of vertices
			if (!weightFound[j])				   // If false in bool array
				if (smallestWeight[j] < minWeight) // Finds smallest weight in the entire double array
				{
					v = j;
					minWeight = smallestWeight[v]; // minWeight now equals the smallerWeight
				}

		weightFound[v] = true; // The index of the smallest weight is now true

		for (int j = 0; j < gSize; j++)
			if (!weightFound[j]) // If weight found is false
				if (minWeight + weights[v][j] < smallestWeight[j])
				{
					smallestWeight[j] = minWeight + weights[v][j];
					retrace[1][j] = v+1;
				}

	} // end for
	for (int g = 0; g < gSize; g++)
	{
		retrace[0][g] = smallestWeight[g];
	}
	delete[] smallestWeight; 
	delete[] weightFound;
	return retrace;
} // end shortestPath

list<int> WeightedGraphType::breadthFirstTraversal(int key)
{
	queue<int> queue;  // Used to order the exploration of the graph
	list<int> indices; // Stores breadth first search result

	bool *visited;
	visited = new bool[gSize];

	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; // creates an array sized of vertices
							  // and initialises each to false

	list<int>::iterator graphIt;

	for (int index = key; index < gSize; index++)
		if (!visited[index])
		{						   // if it is false
			queue.push(index);	   // push index into list
			visited[index] = true; // change index to true
			// cout << " " << index << " "; Prints out the first one being 0;

			while (!queue.empty())
			{
				int u = queue.front();
				indices.push_back(u);
				queue.pop();

				for (graphIt = graph[u].begin(); graphIt != graph[u].end();
					 ++graphIt)
				{
					int w = *graphIt;
					if (!visited[w])
					{
						queue.push(w);
						visited[w] = true;
						// cout << " " << w << " "; Print out the rest of the numbers if they have not been visited.
					}
				}
			}
		}
	delete[] visited;
	return indices;
} // end breadthFirstTraversal

#endif
