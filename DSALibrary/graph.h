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
		std::string start;
		std::string end;
	};

	class Graph
	{
	public:
		std::vector<node*> nodeList; // Adjacency list as array of pointers

		Graph(edge edges[], int edges_count);
		~Graph();

		// Print the graph
		void display();

		// Add a node
		void addEdge(const edge& _edge);

		// Remove a node
		void removeEdge(const edge& _edge);

		// Create a vertex
		void addVertex(const std::string& name);

		// Remove a vertex
		void removeVertex(const std::string& name);

		// Returns number of paths between first given vertex and the second given vertex
		int getPathsCount(const std::string& start, const std::string& end);

		// Returns number of cycles between first given vertex and the second given vertex
		int getCyclesCount(const std::string& vertex);

	private:
		static void createNode(node* ptr, std::string name);

		static void destroyNode(node* ptr, node* target);

		int findVertexByName(const std::string& vertex);

		static node* findNodeByName(node* ptr, const std::string& vertex);

		// Pathfinder algorithm
		int pathsCount(const std::string& start, const std::string& end, std::optional<int> it = std::nullopt);
	};
} // namespace graphs
