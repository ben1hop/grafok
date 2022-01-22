#ifndef GRAPH_H
#define GRAPH_H

#include <stdexcept>
#include <type_traits>
#include <vector>
#include <string>
#include <algorithm>
#include "Matrix.hpp"

const int ACCEPTABLE_NODE_LIMIT = 128;

class IGraphOperations {
public:
	enum GraphDataOp { Add, Delete };
	virtual ~IGraphOperations() {}
	virtual void addEdge(const int& from , const int& to) {}
	virtual void addNode(const int& node) {}
	virtual void deleteNode(const int& node) {}
	//virtual void resizeNodes(const int& node) {}
};

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

		void addNode(const int& node) override {
			graph.currentEdgeCount == 0 ? matrix->Resize(graph.IncrementNodes()) : matrix->ResizeAndCopy(graph.IncrementNodes());
		}

		void deleteNode(const int& node) override {
			graph.currentEdgeCount == 0 ? matrix->Resize(graph.DecrementNodes()) : matrix->ResizeAndCopy(graph.DecrementNodes());
		}

		void addEdge(const int& from , const int& to) override {
			auto i = std::find(graph.nodes.begin(), graph.nodes.end(), from);
			auto j = std::find(graph.nodes.begin(), graph.nodes.end(), to);
			
			if (i == graph.nodes.end() || j == graph.nodes.end())
				throw std::invalid_argument("Edge creation: non exisiting node.");

			graph.currentEdgeCount++;
			matrix->setValue(i - graph.nodes.begin(), j - graph.nodes.begin(), 1);
		}

	};

	class GraphAsList : IGraphOperations {
		Graph& graph; // referencia a birtokos graph objektumra
	public:
		GraphAsList(Graph& graph) : graph(graph) {

		}
		~GraphAsList() {}

		void addNode(const int& node) override {}

		void addEdge(const int& from , const int& to) override {}
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
	MatrixRepPointer _instanceM = NULL;
	ListRepPointer _instanceL = NULL;

	inline const int GetNodeCount() const { return currentNodeCount; }

	inline const int IncrementNodes() { 
		currentNodeCount++;
		return currentNodeCount; };

	inline const int DecrementNodes() {
		currentNodeCount--;
		return currentNodeCount;
	};

	void DeleteNode(const int node) {
		//nodes.erase(node);
	}

	void AddNode(const int node) {
		nodes.push_back(node);
		if (this->usedRep == Both) {
			_instanceM->addNode(node);
			_instanceL->addNode(node);
		}
		else
			this->usedRep == Matrix ? _instanceM->addNode(node) : _instanceL->addNode(node);
	}

	void AddEdge(const int from, const int to) {
		if (this->usedRep == Both) {
			_instanceM->addEdge(from ,to);
			_instanceL->addEdge(from ,to);
		}
		else
			this->usedRep == Matrix ? _instanceM->addEdge(from ,to) : _instanceL->addEdge(from ,to);
	}

	Graph(GraphRepresentation rep = Both, GraphType type = Undirected) :
		usedRep(rep), dirType(type), currentNodeCount(0), currentEdgeCount(0)
	{
		switch (rep) {
		case Both:
			_instanceM = createMatrixGraph();
			_instanceL = createMatrixList();
			break;
		case Matrix:
			_instanceM = createMatrixGraph();
			break;
		case List:
			_instanceL = createMatrixList();
			break;
		}
		// c++11-es array size lekerdezes
		//if (std::extent<decltype(nodes)>::value > ACCEPTABLE_NODE_LIMIT)
		//	throw std::invalid_argument("Higher node count than acceptable.");
		//else {
			//currentNodeCount = std::extent<decltype(nodes)>::value;			
		//}	
	}


private:
	std::vector<int> nodes;

	int currentNodeCount;
	int currentEdgeCount;
	const GraphRepresentation usedRep;
	const GraphType dirType;

	MatrixRepPointer createMatrixGraph() { return new GraphAsMatrix(*this); }
	ListRepPointer createMatrixList() { return new GraphAsList(*this); }


};






#endif // !GRAPH_H
