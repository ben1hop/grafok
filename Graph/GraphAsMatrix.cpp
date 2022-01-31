#include "Graph.h"

void Graph::GraphAsMatrix::addNode(const int& node) {
	graph.currentEdgeCount == 0 ? matrix->Resize(graph.IncrementNodes()) : matrix->ResizeAndCopy(graph.IncrementNodes());
}

void Graph::GraphAsMatrix::deleteNode(const int& node) {
	graph.currentEdgeCount == 0 ? matrix->Resize(graph.DecrementNodes()) : matrix->ResizeAndCopy(graph.DecrementNodes());
}

void Graph::GraphAsMatrix::addEdge(const int& from, const int& to) {
	auto i = std::find(graph.nodes.begin(), graph.nodes.end(), from);
	auto j = std::find(graph.nodes.begin(), graph.nodes.end(), to);

	if (i == graph.nodes.end() || j == graph.nodes.end())
		throw std::invalid_argument("Edge creation: non exisiting node.");

	graph.currentEdgeCount++;
	matrix->setValue(i - graph.nodes.begin(), j - graph.nodes.begin(), 1);
}

void Graph::AddNode(const int node) {
	nodes.push_back(node);
	if (this->usedRep == Both) {
		_instanceM->addNode(node);
		_instanceL->addNode(node);
	}
	else
		this->usedRep == Matrix ? _instanceM->addNode(node) : _instanceL->addNode(node);
}

void Graph::AddEdge(const int from, const int to) {
	if (this->usedRep == Both) {
		_instanceM->addEdge(from, to);
		_instanceL->addEdge(from, to);
	}
	else
		this->usedRep == Matrix ? _instanceM->addEdge(from, to) : _instanceL->addEdge(from, to);
}