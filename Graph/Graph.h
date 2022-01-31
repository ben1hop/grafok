#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept>
#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>
#include "IGraphOperation.h"
#include "Matrix.hpp"
#include "LinkedList.hpp"

const int ACCEPTABLE_NODE_LIMIT = 128;

class Graph {
private:
	friend class GraphAsMatrix;
	friend class GraphAsList;
/*
* Beagyazott Graf reprezentaciok a muveleti algoritmusok hasznalatahoz , a megjeleniteshez nincs szukseg rajuk
*/
#pragma region Graph Representations
	class GraphAsMatrix : IGraphOperations {

		typedef Matrix Matrix;
		typedef Matrix* MatrixPointer; // lokalis matrix tipus definicio
		Graph& graph; // referencia a birtokos graph objektumra	
		MatrixPointer matrix;

	public:
		GraphAsMatrix(Graph& graph) : graph(graph) {
			matrix = new Matrix(graph.GetNodeCount());
		}
		~GraphAsMatrix() {
			delete matrix;
		}

		void addNode(const int& node) final;

		void deleteNode(const int& node) final;

		void addEdge(const int& from, const int& to) final;

	};

	class GraphAsList : IGraphOperations {
		Graph& graph; // referencia a birtokos graph objektumra
	public:
		GraphAsList(Graph& graph) : graph(graph) {

		}
		~GraphAsList() {}

		void addNode(const int& node) override {}

		void addEdge(const int& from , const int& to) override {}

		void deleteNode(const int& node) override {}
	};
#pragma endregion


public:
	enum GraphRepresentation { Matrix, List, Both };
	enum GraphType { Directed, Undirected };


	typedef GraphAsMatrix MatrixRep;
	typedef GraphAsList ListRep;

	typedef GraphAsMatrix* MatrixRepPointer;
	typedef GraphAsList* ListRepPointer;

	// csak egy begyazott peldanyra mutathatnak es a konstruktorban seteljuk
	MatrixRepPointer _instanceM = nullptr;
	ListRepPointer _instanceL = nullptr;

	inline const int GetNodeCount() const { return currentNodeCount; }

	inline const int IncrementNodes() {
		return ++currentNodeCount;
	}

	inline const int DecrementNodes() {
		return --currentNodeCount;
	};

	void DeleteNode(const int node) {
		//nodes.erase(node);
	}

	void AddNode(const int node);

	void AddEdge(const int from, const int to);

	Graph(GraphRepresentation rep = Both, GraphType type = Undirected);
	~Graph();
	
private:
	LinkedList* nodes;

	int currentNodeCount;
	int currentEdgeCount;
	const GraphRepresentation usedRep;
	const GraphType dirType;

	MatrixRepPointer createMatrixGraph() { return new GraphAsMatrix(*this); }
	ListRepPointer createMatrixList() { return new GraphAsList(*this); }

};

#endif // !GRAPH_H
