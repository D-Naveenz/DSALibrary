#include "graph.h"
#include <iostream>

using namespace std;
using namespace ds_modals;
using namespace nlohmann;

#pragma region graph_controller - Private
int graph_controller::path_finder(const string& start, const string& end, optional<int> rec_it, optional<vector<string>*> proc_vertex)
{
	// temporary variable to store processed vertexes
	if (!proc_vertex.has_value())
		proc_vertex = { new vector<string>() };

	// base case 1
	// If start or end vertex doesn't exists then return false
	if (!adj_list_.contains(start) || !adj_list_.contains(end))
	{
		return 0;
	}

	if (rec_it.has_value())
		rec_it = { *rec_it + 1 };
	else
		rec_it = { 0 };

	// base case 2
	// If its not the first iteration and both start and end vertices are the same
	if (start == end && *rec_it > 0)
	{
		return 1;
	}
	else
	{
		// base case 3
		// If the current (start) node already belongs to the path as a milestone
		if (ranges::find(*(*proc_vertex), start) != (*proc_vertex)->end())
		{
			return 0;
		}
	}

	// recursive steps
	(*proc_vertex)->push_back(start);
	int count = 0;
	for (auto& [fst, snd] : adj_list_)
	{
		for (auto& it : snd)
		{
			count += path_finder(it.adj_vertex, end, rec_it, proc_vertex);
		}
	}

	return count;
}
#pragma endregion 

#pragma region graph_controller - Public
graph_controller::graph_controller(const std::string& obj_type) : dsa_obj(obj_type), edges_count_(0)
{
}

inline size_t graph_controller::get_vertices_count() const
{
	return adj_list_.size();
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

void graph_controller::display()
{
	serialize();
	cout << ds_modal_.dump(4) << endl;
}

void graph_controller::serialize()
{
	auto& a_list = ds_modal_["data"]["adjacency_list"];
	auto& vct = ds_modal_["data"]["vectors"];
	vct.clear();
	for (auto& [left, right] : adj_list_)
	{
		vct.push_back(left);
		a_list[left].clear();
		for (auto& it : right)
		{
			a_list[left].push_back({ {"adj_vertex", it.adj_vertex}, {"weight", it.weight} });
		}
	}
}

void graph_controller::deserialize(ifstream ifs)
{
	json j;
	try
	{
		j = json::parse(ifs);
	}
	catch (json::parse_error& ex)
	{
		std::cerr << "parse error at byte " << ex.byte << std::endl;
	}
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
	adj_list_[name] = vector<edge_data>();
}

void graph_controller::remove_vertex(const string& name)
{
	if (adj_list_.contains(name))
	{
		adj_list_[name].clear();
		// unbind target vertex from the edges
		for (auto& [fst, snd] : adj_list_)
		{
			for (auto it = snd.begin(); it != snd.end(); ++it)
			{
				if ((*it).adj_vertex == name)
				{
					snd.erase(it);
				}
			}
		}
		// remove vertex at last
		adj_list_.erase(name);
	}
	else
	{
		throw out_of_range("Couldn't find the vertex named " + name + ".");
	}
}
#pragma endregion

#pragma region DirectedGraph
void directed_graph::add_edge(const std::string& a, const std::string& b, const double weight)
{
	if (!adj_list_.contains(a))
	{
		// Create a new vertex
		add_vertex(a);
	}
	if (!adj_list_.contains(b))
	{
		// Create a new vertex
		add_vertex(b);
	}

	// Insert in the beginning
	adj_list_[a].emplace_back(b, weight);
	edges_count_++;
}

void directed_graph::remove_edge(std::string a, std::string b)
{
	for (auto it = adj_list_[a].begin(); it != adj_list_[a].end(); ++it)
	{
		if ((*it).adj_vertex == b)
		{
			adj_list_[a].erase(it);
		}
	}
}
#pragma endregion

#pragma region UndirectedGraph
void ds_modals::undirected_graph::add_edge(const std::string& a, const std::string& b, double weight)
{
	if (!adj_list_.contains(a))
	{
		// Create a new vertex
		add_vertex(a);
	}
	if (!adj_list_.contains(b))
	{
		// Create a new vertex
		add_vertex(b);
	}

	// Insert in the beginning
	adj_list_[a].emplace_back(b, weight);
	adj_list_[b].emplace_back(a, weight);
	edges_count_++;
}

void ds_modals::undirected_graph::remove_edge(std::string a, std::string b)
{
	for (auto it = adj_list_[a].begin(); it != adj_list_[a].end(); ++it)
	{
		if ((*it).adj_vertex == b)
		{
			adj_list_[a].erase(it);
		}
	}

	for (auto it = adj_list_[b].begin(); it != adj_list_[b].end(); ++it)
	{
		if ((*it).adj_vertex == a)
		{
			adj_list_[b].erase(it);
		}
	}
	edges_count_--;
}
#pragma endregion