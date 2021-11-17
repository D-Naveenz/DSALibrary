#include "graph.h"
#include <iostream>

using namespace std;
using namespace ds_modals;

#pragma region graph_controller - Private
int graph_controller::find_vertex_by_name(const string& vertex) const
{
	if (const auto it = ranges::find(vertex_list_, vertex); it != vertex_list_.end())
	{
		return static_cast<int>(distance(vertex_list_.begin(), it));
	}
	else
	{
		return -1;
	}
}

int graph_controller::path_finder(const string& start, const string& end, optional<int> rec_it, optional<vector<int>*> proc_vertex)
{
	// temporary variable to store processed vertexes
	if (!proc_vertex.has_value())
		proc_vertex = { new vector<int>() };
	const int start_i = find_vertex_by_name(start);
	const int end_i = find_vertex_by_name(end);

	// base case 1
	// If start or end vertex doesn't exists then return false
	if (start_i < 0 || end_i < 0)
		return 0;

	if (rec_it.has_value())
		rec_it = { *rec_it + 1 };
	else
		rec_it = { 0 };

	// base case 2
	// If its not the first iteration and both start and end vertices are the same
	if (start_i == end_i && *rec_it > 0)
	{
		return 1;
	}
	else
	{
		// base case 3
		// If the current (start) node already belongs to the path as a milestone
		if (ranges::find(*(*proc_vertex), start_i) != (*proc_vertex)->end())
		{
			return 0;
		}
	}

	// recursive steps
	(*proc_vertex)->push_back(start_i);
	int count = 0;

	for (auto& it_x : adj_list_)
	{
		for (const auto& [adj_vertex, size] : it_x)
		{
			count += path_finder(vertex_list_[adj_vertex], end, rec_it, proc_vertex);
		}
	}

	return count;
}
#pragma endregion 

#pragma region graph_controller - Public
ds_modals::graph_controller::graph_controller(const std::string& obj_type) : dsa_obj(obj_type), edges_count_(0)
{
}

inline size_t graph_controller::get_vertices_count() const
{
	return vertex_list_.size();
}

inline size_t graph_controller::size() const
{
	return edges_count_;
}

int graph_controller::trace_paths(const std::string& start, const std::string& end)
{
	if (start != end)
	{
		return path_finder(start, end);
	}
	return 0;
}

int graph_controller::trace_cycles(const std::string& vertex)
{
	return path_finder(vertex, vertex);
}

#pragma endregion

#pragma region graph_controller - Protected
void graph_controller::init(const vector<edge>& edges)
{
	for (auto& [l_vertex, r_vertex, weight] : edges)
	{
		add_edge(l_vertex, r_vertex, weight);
	}
}


void graph_controller::add_vertex(const string& name)
{
	vertex_list_.push_back(name);
	const int target = find_vertex_by_name(name);
	adj_list_.emplace(adj_list_.begin() + target, vector<edge_data>());
}

void graph_controller::remove_vertex(const string& name)
{
	if (const auto it = ranges::find(vertex_list_, name); it != vertex_list_.end())
	{
		vertex_list_.erase(it);
		const int target = find_vertex_by_name(name);
		adj_list_.erase(adj_list_.begin() + target);
	}
	else
	{
		throw out_of_range("Couldn't find the vertex named " + name + ".");
	}
}

vector<string> graph_controller::str_out()
{
	vector<string> result;
	int row_count = 0;

	for (auto& row : adj_list_)
	{
		string row_str = vertex_list_[row_count] + " ->  ";
		int cell_count = 0;

		for (auto row_obj : row)
		{
			row_str += vertex_list_[cell_count] + ", ";
			cell_count++;
		}

		row_str = row_str.substr(0, row_str.length() - 2);
		result.push_back(row_str);
		row_count++;
	}

	return result;
}
#pragma endregion

#pragma region DirectedGraph
void directed_graph::add_edge(const std::string& a, const std::string& b, const double weight)
{
	// Find indexes by its name
	int start_index = find_vertex_by_name(a);
	int end_index = find_vertex_by_name(b);

	if (start_index < 0)
	{
		// Create a new vertex
		add_vertex(a);
		start_index = find_vertex_by_name(a);
	}
	if (end_index < 0)
	{
		// Create a new vertex
		add_vertex(b);
		end_index = find_vertex_by_name(b);
	}

	// Insert in the beginning
	adj_list_[start_index].emplace_back(end_index, weight);

	edges_count_++;
}

void directed_graph::remove_edge(std::string a, std::string b)
{
	// Find indexes by its name
	const int start_index = find_vertex_by_name(a);
	const int end_index = find_vertex_by_name(b);

	for (auto it = adj_list_[start_index].begin(); it != adj_list_[start_index].end(); ++it)
	{
		if (const auto idx = it - adj_list_[start_index].begin(); adj_list_[start_index][idx].adj_vertex == end_index)
		{
			adj_list_[start_index].erase(it);
		}
	}
}
#pragma endregion

#pragma region UndirectedGraph
void ds_modals::undirected_graph::add_edge(const std::string& a, const std::string& b, double weight)
{
	// Find indexes by its name
	int start_index = find_vertex_by_name(a);
	int end_index = find_vertex_by_name(b);

	if (start_index < 0)
	{
		// Create a new vertex
		add_vertex(a);
		start_index = find_vertex_by_name(a);
	}
	if (end_index < 0)
	{
		// Create a new vertex
		add_vertex(b);
		end_index = find_vertex_by_name(b);
	}

	const edge_data result1 = { end_index, weight };
	const edge_data result2 = { start_index, weight };

	// Insert in the beginning
	adj_list_[start_index].emplace_back(end_index, weight);
	adj_list_[end_index].emplace_back(start_index, weight);

	edges_count_++;
}

void ds_modals::undirected_graph::remove_edge(std::string a, std::string b)
{
	// Find indexes by its name
	const int start_index = find_vertex_by_name(a);
	const int end_index = find_vertex_by_name(b);

	for (auto it = adj_list_[start_index].begin(); it != adj_list_[start_index].end(); ++it)
	{
		if (const auto idx = it - adj_list_[start_index].begin(); adj_list_[start_index][idx].adj_vertex == end_index)
		{
			adj_list_[start_index].erase(it);
		}
	}

	for (auto it = adj_list_[end_index].begin(); it != adj_list_[end_index].end(); ++it)
	{
		if (const auto idx = it - adj_list_[end_index].begin(); adj_list_[end_index][idx].adj_vertex == start_index)
		{
			adj_list_[end_index].erase(it);
		}
	}
}
#pragma endregion