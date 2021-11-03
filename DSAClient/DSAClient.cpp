// DSAClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graph.h"

using namespace std;
using namespace ds_graph;

int main()
{
	cout << "~~~~~~ Directed Graph ~~~~~~" << endl;
	// Graph direct_edges array
	edge direct_edges[] = {
		// {start, end}
		{"V1", "V2"},
		{"V3", "V2"}, {"V3", "V4"},
		{"V4", "V2"}, {"V4", "V5"},
		{"V5", "V2"}, {"V5", "V1"}
	};
	int edge_count = sizeof direct_edges / sizeof direct_edges[0];
	// Construct graph
	DirectedGraph directedGraph(direct_edges, edge_count);
	directedGraph.display();
	cout << directedGraph.toString() << endl;
	cout << endl;

	// Check whether there is a path from the first given vertex to the second given vertex (Question 1)
	cout << "There is " << (directedGraph.tracePaths("V3", "V1") ? "" : "not ") << "a path from V3 to V1" << endl;
	// Check whether a given directed graph contains a cycle or not (Question 2)
	cout << "There is " << (directedGraph.traceCycles("V1") ? "" : "not ") << "a cycle from V1" << endl;
	// Returns number of paths between first given vertex and the second given vertex (Question 3)
	int pCount = directedGraph.tracePaths("V3", "V1");
	cout << "There ";
	if (pCount == 0)
	{
		cout << "is not any path between V3 and v1" << endl;
	}
	else if (pCount == 1)
	{
		cout << "is one path between V3 and v1" << endl;
	}
	else
	{
		cout << "are " << pCount << " paths between V3 and v1" << endl;
	}

	return 0;
}
