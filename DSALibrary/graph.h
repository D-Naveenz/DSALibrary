#pragma once
#include "pch.h"
#include <optional>

constexpr auto obj_directed = "Directed Graph";
constexpr auto obj_undirected = "Undirected Graph";

// namespace for graph structure
namespace ds_modals
{
	struct edge
	{
		std::string l_vertex;
		std::string r_vertex;
		double weight;

		edge(std::string l, std::string r, const std::optional<double> w = std::nullopt) : l_vertex(std::move(l)), r_vertex(std::move(r))
		{
			if (w.has_value())
			{
				weight = *w;
			}
			else
			{
				weight = 1.0;
			}
		}
	};

	class graph_controller : public dsa_obj
	{
		// Pathfinder algorithm
		int path_finder(const std::string& start, const std::string& end, std::optional<int> rec_it = std::nullopt,
			std::optional<std::vector<int>*> proc_vertex = std::nullopt);

	public:
		// Constructor
		explicit graph_controller(const std::string& obj_type);

		// The number of vertexes that are currently on the graph
		[[nodiscard]] inline size_t get_vertices_count() const;
		// Get edges count
		[[nodiscard]] inline size_t size() const override;

		// Pure virtual function for adding edges
		virtual void add_edge(const std::string& a, const std::string& b, double weight) = 0;
		// Pure virtual function for remove edges
		virtual void remove_edge(std::string a, std::string b) = 0;
		// Returns number of paths between first given vertex and the second given vertex
		int trace_paths(const std::string& start, const std::string& end);
		// Returns number of cycles between first given vertex and the second given vertex
		int trace_cycles(const std::string& vertex);

	protected:
		struct edge_data
		{
			int adj_vertex;
			double weight;

			edge_data() : adj_vertex(0), weight(0) {}
			edge_data(const int r, const double w): adj_vertex(r), weight(w) {}
		};

		std::vector<std::string> vertex_list_;		// vertices mapper
		std::vector<std::vector<edge_data>> adj_list_;	// Adjacency list as a 2-D vector
		int edges_count_;

		// Initializer that helps to initialize Direct/Indirect graphs
		void init(const std::vector<edge>& edges);
		[[nodiscard]] int find_vertex_by_name(const std::string& vertex) const;
		void add_vertex(const std::string &name);
		void remove_vertex(const std::string &name);
		std::vector<std::string> str_out() override;
	};

	class directed_graph final : public graph_controller
	{
	public:
		directed_graph(): graph_controller(obj_directed)
		{
		}

		explicit directed_graph(const std::vector<edge>& edges): graph_controller(obj_directed)
		{
			init(edges);
		}

		void add_edge(const std::string& a, const std::string& b, double weight = 1) override;
		void remove_edge(std::string a, std::string b) override;
		
	};

	class undirected_graph final : public graph_controller
	{
	public:
		undirected_graph(): graph_controller(obj_undirected)
		{
		}

		explicit undirected_graph(const std::vector<edge>& edges): graph_controller(obj_undirected)
		{
			init(edges);
		}

		void add_edge(const std::string& a, const std::string& b, double weight = 1) override;
		void remove_edge(std::string a, std::string b) override;
	};
}
