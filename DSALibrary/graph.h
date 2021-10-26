#pragma once

#include <optional>
#include <string>
#include <vector>

// namespace for graph structure
namespace graphs
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
		_graph();
		~_graph();

		// The number of edges that are currently on the graph
		int getEdgeCount();

		// The number of vertexes that are currently on the graph
		int getVertexCount();

		// Returns number of paths between first given vertex and the second given vertex
		int tracePaths(const std::string& start, const std::string& end);

		// Returns number of cycles between first given vertex and the second given vertex
		int traceCycles(const std::string& vertex);

		// Print the graph
		void display();

		// Create a vertex
		void addVertex(const std::string& name);

		// Remove a vertex
		void removeVertex(const std::string& name);

	private:
		// std::vector<std::string>* proc_vertex; // temporary variable to store processed vertexes

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
	};

	class DirectedGraph : public _graph
	{
	public:
		DirectedGraph(edge edges[], int edges_count);

		// Add a node
		void addEdge(const edge& _edge);

		// Remove a node
		void removeEdge(const edge& _edge);
	};

	class IndirectedGraph : public _graph
	{
	public:
		IndirectedGraph(edge edges[], int edges_count);
		~IndirectedGraph();

		// Add a node
		void addEdge(const edge& _edge);

		// Remove a node
		void removeEdge(const edge& _edge);
	};
} // namespace graphs
