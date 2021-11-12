#pragma once

#include "ds_model.h"
#include <optional>

constexpr auto obj_directed = "Directed Graph";
constexpr auto obj_undirected = "Undirected Graph";

// namespace for graph structure
namespace ds_graph
{
	// Node that store adjacency list items
	struct node
	{
		std::string vertex;
		node* next{};
	};

	// structure to store edge data of the graph
	struct edge
	{
		std::string a;
		std::string b;
	};

	class graph : public ds_common::dsa_obj
	{
	public:
		// Default constructor
		graph(std::string graph_type);
		// Destructor
		~graph() override;

		// Initializer that helps to initialize Direct/Indirect graphs
		void init(edge edges[], int edges_count);

		// The number of edges that are currently on the graph
		[[nodiscard]] int get_edge_count() const;

		// Returns number of paths between first given vertex and the second given vertex
		int trace_paths(const std::string& start, const std::string& end);

		// Returns number of cycles between first given vertex and the second given vertex
		int trace_cycles(const std::string& vertex);

		// Create a vertex
		void add_vertex(const std::string& name);

		// Remove a vertex
		void remove_vertex(const std::string& name);

		// Pure virtual function for adding edges
		virtual void add_edge(const edge& _edge_) = 0;

		// Pure virtual function for removing edges
		virtual void remove_edge(const edge& _edge_) = 0;

		// The number of vertexes that are currently on the graph
		size_t get_size() override;

	private:
		// Pathfinder algorithm
		int path_finder(const std::string& start, const std::string& end, std::optional<int> it = std::nullopt,
			std::optional<std::vector<std::string>*> proc_vertex = std::nullopt);

	protected:
		std::vector<node*> node_list_; // Adjacency list as array of pointers
		int edge_count_;               // The number of edges that are currently on the graph

		static void create_node(node* ptr, std::string name);

		static void destroy_node(node* ptr, node* target);

		[[nodiscard]] int find_vertex_by_name(const std::string& vertex) const;

		static node* find_node_by_name(node* ptr, const std::string& vertex);

		std::vector<std::string> str_out() override;
	};

	class directed_graph final : public graph
	{
	public:
		directed_graph(edge edges[], const int edges_count): graph(obj_directed)
		{
			init(edges, edges_count);
		}

		// Add a node
		void add_edge(const edge& _edge_) override;

		// Remove a node
		void remove_edge(const edge& _edge_) override;
	};

	class undirected_graph final : public graph
	{
	public:
		undirected_graph(edge edges[], const int edges_count): graph(obj_undirected)
		{
			init(edges, edges_count);
		}

		// Add a node
		void add_edge(const edge& _edge_) override;

		// Remove a node
		void remove_edge(const edge& _edge_) override;
	};
} // namespace ds_graph
