#include "graph.h"
#include <iostream>
#include <utility>

using namespace std;
using namespace graphs;

#pragma region Public - _graph
// Constructor
_graph::_graph()
{
    edge_count = 0;
    // proc_vertex = nullptr;
}

// Destructor
_graph::~_graph()
{
    // free memory of the head
    // nodeList = vector<node*>();
    nodeList.clear();
    // proc_vertex->clear();
}

int _graph::getEdgeCount()
{
    return edge_count;
}

int _graph::getVertexCount()
{
    return nodeList.size();
}

int _graph::tracePaths(const string &start, const string &end)
{
    // proc_vertex = new vector<string>();
    if (start.compare(end) != 0)
    {
        return pathFinder(start, end);
    }
    return 0;
}

int _graph::traceCycles(const string &vertex)
{
    // proc_vertex = new vector<string>();
    return pathFinder(vertex, vertex);
}

void _graph::display()
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

void _graph::addVertex(const string &name)
{
    node *newVertex = new node();
    newVertex->vertex = name;
    newVertex->next = nullptr;
    nodeList.push_back(newVertex);
}

void _graph::removeVertex(const string &name)
{
    int index = findVertexByName(name);
    vector<node *>::iterator index_itr;
    index_itr = nodeList.begin() + index;
    delete[] nodeList[index];
    nodeList.erase(index_itr);
}
#pragma endregion

#pragma region Private - _graph
int _graph::pathFinder(const std::string &start, const std::string &end, optional<int> it,
                       optional<vector<string> *> proc_vertex)
{
    // temporary variable to store processed vertexes
    if (!proc_vertex.has_value())
        proc_vertex = {new vector<string>()};
    int start_i = findVertexByName(start);
    int end_i = findVertexByName(end);

    // base case 1
    // If start or end vertex doesn't exists then return false
    if (start_i < 0 || end_i < 0)
        return 0;

    node *startNode = nodeList[start_i];
    node *endNode = nodeList[end_i];

    if (it.has_value())
        it = {*it + 1};
    else
        it = {0};

    // base case 2
    // If its not the first iteration and both start and end nodes are the same
    if (startNode == endNode && *it > 0)
    {
        return 1;
    }
    else
    {
        // base case 3
        // If the current (start) node already belongs to the path as a milestone
        if (std::find((*proc_vertex)->begin(), (*proc_vertex)->end(), startNode->vertex) != (*proc_vertex)->end())
        {
            return 0;
        }
    }

    // recursive steps
    (*proc_vertex)->push_back(startNode->vertex);
    node *ptr = startNode->next;
    int count = 0;
    while (ptr != nullptr)
    {
        count += pathFinder(ptr->vertex, end, it, proc_vertex);
        ptr = ptr->next;
    }
    return count;
}
#pragma endregion

#pragma region Protected - _graph
void _graph::createNode(node *ptr, string name)
{
    node *newNode = new node;
    newNode->vertex = std::move(name);
    newNode->next = nullptr;

    while (ptr->next != nullptr)
        ptr = ptr->next;
    ptr->next = newNode;
}

void _graph::destroyNode(node *ptr, node *target)
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

int _graph::findVertexByName(const string &vertex)
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

node *_graph::findNodeByName(node *ptr, const string &vertex)
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
#pragma endregion

#pragma region DirectedGraph
// Constructor
DirectedGraph::DirectedGraph(edge edges[], int edges_count)
{
    // Construct directed graph by adding edges to it
    for (int j = 0; j < edges_count; j++)
    {
        addEdge(edges[j]);
    }
}

void DirectedGraph::addEdge(const edge &_edge)
{
    // Find start index by its name
    int start_index = findVertexByName(_edge.a);
    if (start_index == -1)
    {
        // Create a new vertex
        addVertex(_edge.a);
        start_index = findVertexByName(_edge.a);
    }
    string end = _edge.b;
    // Insert in the beginning
    createNode(nodeList[start_index], end);

    edge_count++;
}

void DirectedGraph::removeEdge(const edge &_edge)
{
    node *vertex = nodeList[findVertexByName(_edge.a)];
    node *target = findNodeByName(vertex, _edge.b);
    destroyNode(vertex, target);

    edge_count--;
}
#pragma endregion

#pragma region IndirectedGraph
// Constructor
IndirectedGraph::IndirectedGraph(edge edges[], int edges_count)
{
    // Construct indirected graph by adding edges to it
    for (int j = 0; j < edges_count; j++)
    {
        addEdge(edges[j]);
    }
}

void IndirectedGraph::addEdge(const edge &_edge)
{
    // Find indexes by its name
    int start_index = findVertexByName(_edge.a);
    int end_index = findVertexByName(_edge.b);
    if (start_index < 0)
    {
        // Create a new vertex
        addVertex(_edge.a);
        start_index = findVertexByName(_edge.a);
    }
    if (end_index < 0)
    {
        // Create a new vertex
        addVertex(_edge.b);
        start_index = findVertexByName(_edge.b);
    }
    string start = _edge.a;
    string end = _edge.b;

    // Insert in the beginning
    createNode(nodeList[start_index], end);
    createNode(nodeList[end_index], start);

    edge_count++;
}

void IndirectedGraph::removeEdge(const edge &_edge)
{
    node *vertex = nodeList[findVertexByName(_edge.a)];
    node *target = findNodeByName(vertex, _edge.b);
    destroyNode(vertex, target);

    vertex = nodeList[findVertexByName(_edge.b)];
    target = findNodeByName(vertex, _edge.a);
    destroyNode(vertex, target);

    edge_count--;
}
#pragma endregion
