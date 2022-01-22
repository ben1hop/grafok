#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
	Graph* graph = new Graph(Graph::Matrix, Graph::Directed);

	graph->AddNode(5);
	graph->AddNode(6);
	graph->AddNode(3);
	graph->AddNode(2);

	try {
		graph->AddEdge(2, 3);
		graph->AddEdge(5, 6);
		graph->AddEdge(2, 1);
	}
	catch (std::exception ex) {
		cout << ex.what();
	}

	graph->AddNode(1);
	
	delete graph;
}