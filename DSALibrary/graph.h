#pragma once

#include "ds_model.h"
#include <optional>

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

	class _graph
	{
	public:
		// Default constructor
		_graph();
		// Copy constructor
		_graph(const _graph& obj);
		// Destructor
		~_graph();

		// Initializer that helps to initialize Direct/Indirect graphs
		void init(edge edges[], int edges_count);

		// The number of edges that are currently on the graph
		int getEdgeCount();

		// Returns number of paths between first given vertex and the second given vertex
		int tracePaths(const std::string& start, const std::string& end);

		// Returns number of cycles between first given vertex and the second given vertex
		int traceCycles(const std::string& vertex);

		// Create a vertex
		void addVertex(const std::string& name);

		// Remove a vertex
		void removeVertex(const std::string& name);

		// Pure virtual function for adding edges
		virtual void addEdge(const edge& _edge) = 0;

		// Pure virtual function for removing edges
		virtual void removeEdge(const edge& _edge) = 0;

	private:
		// Pathfinder algorithm
		int pathFinder(const std::string& start, const std::string& end, std::optional<int> it = std::nullopt,
			std::optional<std::vector<std::string>*> proc_vertex = std::nullopt);

	protected:
		std::vector<node*> nodeList; // Adjacency list as array of pointers
		int edge_count;               // The number of edges that are currently on the graph

		static void createNode(node* ptr, std::string name);

		static void destroyNode(node* ptr, node* target);

		int findVertexByName(const std::string& vertex);

		static node* findNodeByName(node* ptr, const std::string& vertex);

		int getVertexCount();

		std::vector<std::string> strOutput();
	};

	class DirectedGraph : public _graph, public ds_common::dsaObj<DirectedGraph>
	{
	public:
		DirectedGraph(edge edges[], int edges_count)
		{
			init(edges, edges_count);
		}

		DirectedGraph(const DirectedGraph& _graph) : _graph(_graph) {}

		// Add a node
		void addEdge(const edge& _edge);

		// Remove a node
		void removeEdge(const edge& _edge);

		// The number of vertexes that are currently on the graph
		inline int getSize()
		{
			return getVertexCount();
		}

	private:
		inline std::vector<std::string> str_out()
		{
			return strOutput();
		}
	};

	class IndirectedGraph : public _graph, public ds_common::dsaObj<IndirectedGraph>
	{
	public:
		IndirectedGraph(edge edges[], int edges_count)
		{
			init(edges, edges_count);
		}

		IndirectedGraph(const IndirectedGraph& _graph) : _graph(_graph) {}

		// Add a node
		void addEdge(const edge& _edge);

		// Remove a node
		void removeEdge(const edge& _edge);

		// The number of vertexes that are currently on the graph
		inline int getSize()
		{
			return getVertexCount();
		}

	private:
		inline std::vector<std::string> str_out()
		{
			return strOutput();
		}
	};
} // namespace ds_graph
