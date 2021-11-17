// DSAClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graph.h"

using namespace std;
using namespace ds_modals;

int main()
{
	cout << "~~~~~~ Directed Graph ~~~~~~" << endl;
	// Graph direct_edges array
	const vector<edge> d_graph = {
		{"V1", "V2"},
		{"V3", "V2"}, {"V3", "V4"},
		{"V4", "V2"}, {"V4", "V5"},
		{"V5", "V2"}, {"V5", "V1"}
	};

	// Construct graph
	directed_graph directed_graph(d_graph);
	directed_graph.display();
	cout << directed_graph.to_string() << endl;
	cout << endl;

	// Check whether there is a path from the first given vertex to the second given vertex (Question 1)
	cout << "There is " << (directed_graph.trace_paths("V3", "V1") ? "" : "not ") << "a path from V3 to V1" << endl;
	// Check whether a given directed graph contains a cycle or not (Question 2)
	cout << "There is " << (directed_graph.trace_cycles("V1") ? "" : "not ") << "a cycle from V1" << endl;
	// Returns number of paths between first given vertex and the second given vertex (Question 3)
	const int p_count = directed_graph.trace_paths("V3", "V1");
	cout << "There ";
	if (p_count == 0)
	{
		cout << "is not any path between V3 and v1" << endl;
	}
	else if (p_count == 1)
	{
		cout << "is one path between V3 and v1" << endl;
	}
	else
	{
		cout << "are " << p_count << " paths between V3 and v1" << endl;
	}

	return 0;
}
