#include "graph.h"
#include <utility>

using namespace std;
using namespace ds_graph;

#pragma region Public - _graph
// Constructor
ds_graph::graph::graph(std::string graph_type): dsa_obj(std::move(graph_type)), edge_count_(0)
{
}

// Destructor
graph::~graph()
{
    // free memory of the node list
    node_list_.clear();
}

void graph::init(edge edges[], int edges_count)
{
    // Construct graph by adding edges to it
	for (int j = 0; j < edges_count; j++)
    {
        add_edge(edges[j]);
    }
}

int graph::get_edge_count() const
{
    return edge_count_;
}



int graph::trace_paths(const string &start, const string &end)
{
    if (start != end)
    {
        return path_finder(start, end);
    }
    return 0;
}

int graph::trace_cycles(const string &vertex)
{
    return path_finder(vertex, vertex);
}

void graph::add_vertex(const string &name)
{
	const auto new_vertex = new node();
    new_vertex->vertex = name;
    new_vertex->next = nullptr;
    node_list_.push_back(new_vertex);
}

void graph::remove_vertex(const string &name)
{
	const int index = find_vertex_by_name(name);
	const auto index_itr = node_list_.begin() + index;
    delete[] node_list_[index];
    node_list_.erase(index_itr);
}

size_t ds_graph::graph::get_size()
{
    return node_list_.size();
}
#pragma endregion

#pragma region Private - _graph
int graph::path_finder(const std::string &start, const std::string &end, optional<int> it,
                       optional<vector<string> *> proc_vertex)
{
    // temporary variable to store processed vertexes
    if (!proc_vertex.has_value())
        proc_vertex = {new vector<string>()};
    const int start_i = find_vertex_by_name(start);
    const int end_i = find_vertex_by_name(end);

    // base case 1
    // If start or end vertex doesn't exists then return false
    if (start_i < 0 || end_i < 0)
        return 0;

    node *start_node = node_list_[start_i];
    node *end_node = node_list_[end_i];

    if (it.has_value())
        it = {*it + 1};
    else
        it = {0};

    // base case 2
    // If its not the first iteration and both start and end nodes are the same
    if (start_node == end_node && *it > 0)
    {
        return 1;
    }
    else
    {
        // base case 3
        // If the current (start) node already belongs to the path as a milestone
        if (ranges::find(*(*proc_vertex), start_node->vertex) != (*proc_vertex)->end())
        {
            return 0;
        }
    }

    // recursive steps
    (*proc_vertex)->push_back(start_node->vertex);
    node *ptr = start_node->next;
    int count = 0;
    while (ptr != nullptr)
    {
        count += path_finder(ptr->vertex, end, it, proc_vertex);
        ptr = ptr->next;
    }
    return count;
}
#pragma endregion

#pragma region Protected - _graph
void graph::create_node(node *ptr, string name)
{
    node *newNode = new node;
    newNode->vertex = std::move(name);
    newNode->next = nullptr;

    while (ptr->next != nullptr)
        ptr = ptr->next;
    ptr->next = newNode;
}

void graph::destroy_node(node *ptr, node *target)
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

int graph::find_vertex_by_name(const string &vertex) const
{
    for (int i = 0; i < node_list_.size(); i++)
    {
        if (node_list_[i]->vertex == vertex)
        {
            return i;
        }
    }
    return -1;
}

node *graph::find_node_by_name(node *ptr, const string &vertex)
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

vector<string> ds_graph::graph::str_out()
{
    vector<string> result;

    for (auto target : node_list_)
    {
        string row = target->vertex + " -> ";
        // Go forward
        target = target->next;
        // Loop through the linked list
        while (target != nullptr)
        {
	        row += target->vertex;
	        if (target->next != nullptr)
		        row += ", ";
	        target = target->next;
        }
        result.push_back(row);
    }

    return result;
}
#pragma endregion

#pragma region DirectedGraph
void directed_graph::add_edge(const edge &_edge_)
{
    // Find start index by its name
    int start_index = find_vertex_by_name(_edge_.a);
    if (start_index == -1)
    {
        // Create a new vertex
        add_vertex(_edge_.a);
        start_index = find_vertex_by_name(_edge_.a);
    }
    const string end = _edge_.b;
    // Insert in the beginning
    create_node(node_list_[start_index], end);

    edge_count_++;
}

void directed_graph::remove_edge(const edge &_edge_)
{
    node *vertex = node_list_[find_vertex_by_name(_edge_.a)];
    node *target = find_node_by_name(vertex, _edge_.b);
    destroy_node(vertex, target);

    edge_count_--;
}
#pragma endregion

#pragma region IndirectedGraph
void undirected_graph::add_edge(const edge &_edge_)
{
    // Find indexes by its name
    int start_index = find_vertex_by_name(_edge_.a);
    const int end_index = find_vertex_by_name(_edge_.b);
    if (start_index < 0)
    {
        // Create a new vertex
        add_vertex(_edge_.a);
        start_index = find_vertex_by_name(_edge_.a);
    }
    if (end_index < 0)
    {
        // Create a new vertex
        add_vertex(_edge_.b);
        start_index = find_vertex_by_name(_edge_.b);
    }
    const string start = _edge_.a;
    const string end = _edge_.b;

    // Insert in the beginning
    create_node(node_list_[start_index], end);
    create_node(node_list_[end_index], start);

    edge_count_++;
}

void undirected_graph::remove_edge(const edge &_edge_)
{
    node *vertex = node_list_[find_vertex_by_name(_edge_.a)];
    node *target = find_node_by_name(vertex, _edge_.b);
    destroy_node(vertex, target);

    vertex = node_list_[find_vertex_by_name(_edge_.b)];
    target = find_node_by_name(vertex, _edge_.a);
    destroy_node(vertex, target);

    edge_count_--;
}
#pragma endregion
