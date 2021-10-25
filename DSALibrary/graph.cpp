#include <iostream>
#include <utility>
#include "graph.h"

using namespace std;
using namespace graphs;

#pragma region Public Functions
// Constructor
Graph::Graph(edge edges[], int edges_count)
{
	// Construct directed graph by adding edges to it
	for (int j = 0; j < edges_count; j++)
	{
		addEdge(edges[j]);
	}
}

// Destructor
Graph::~Graph()
{
	// free memory of the head
	nodeList = vector<node*>();
}

void Graph::display()
{
	cout << "List of adjacent vertices" << endl;
	for (auto target : nodeList)
	{
		cout << "* " << target->vertex << " : ";
		// Go forward
		target = target->next;
		// Loop through the linked list
		while (target != nullptr)
		{
			cout << target->vertex;
			if (target->next != nullptr)
				cout << ", ";
			target = target->next;
		}
		cout << endl;
	}
}

void Graph::addEdge(const edge& _edge)
{
	// Find start index by its name
	int start_index = findVertexByName(_edge.start);
	if (start_index == -1)
	{
		// Create a new vertex
		addVertex(_edge.start);
		start_index = findVertexByName(_edge.start);
	}
	string end = _edge.end;
	// Insert in the beginning
	createNode(nodeList[start_index], end);
}

void Graph::removeEdge(const edge& _edge)
{
	node* vertex = nodeList[findVertexByName(_edge.start)];
	node* target = findNodeByName(vertex, _edge.end);
	destroyNode(vertex, target);
}

void Graph::addVertex(const string& name)
{
	node* newVertex = new node();
	newVertex->vertex = name;
	newVertex->next = nullptr;
	nodeList.push_back(newVertex);
}

void Graph::removeVertex(const string& name)
{
	int index = findVertexByName(name);
	vector<node*>::iterator index_itr;
	index_itr = nodeList.begin() + index;
	delete[] nodeList[index];
	nodeList.erase(index_itr);
}

int Graph::getPathsCount(const string& start, const string& end)
{
	if (start.compare(end) != 0)
	{
		return pathsCount(start, end);
	}
	return 0;
}

int Graph::getCyclesCount(const string& vertex)
{
	return pathsCount(vertex, vertex);
}
#pragma endregion

#pragma region Private Functions
void Graph::createNode(node* ptr, string name)
{
	node* newNode = new node;
	newNode->vertex = std::move(name);
	newNode->next = nullptr;

	while (ptr->next != nullptr)
		ptr = ptr->next;
	ptr->next = newNode;
}

void Graph::destroyNode(node* ptr, node* target)
{
	while (ptr->next != target)
	{
		ptr = ptr->next;
	}
	// Detach the target node from the linked list
	ptr->next = ptr->next->next;
	// remove target node
	delete ptr;
}

int Graph::findVertexByName(const string& vertex)
{
	for (int i = 0; i < nodeList.size(); i++)
	{
		if (nodeList[i]->vertex == vertex)
		{
			return i;
		}
	}
	return -1;
}

node* Graph::findNodeByName(node* ptr, const string& vertex)
{
	while (ptr != nullptr)
	{
		if (ptr->vertex == vertex)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return nullptr;
}

int Graph::pathsCount(const std::string& start, const std::string& end, optional<int> it)
{
	int start_i = findVertexByName(start);
	int end_i = findVertexByName(end);
	// base case 1
	if (start_i >= 0 && end_i >= 0)
	{
		node* startNode = nodeList[start_i];
		node* endNode = nodeList[end_i];

		if (it.has_value())
		{
			it = { *it + 1 };
		}
		else
			it = { 0 };

		// base case
		if (startNode == endNode && *it > 0)
		{
			return 1;
		}

		// recursive steps
		node* ptr = startNode->next;
		int count = 0;
		while (ptr != nullptr)
		{
			count += pathsCount(ptr->vertex, end, it);
			ptr = ptr->next;
		}
		return count;
	}
	else
		return 0;
}
#pragma endregion