#include "Graph.h"

Graph::Graph(GraphRepresentation rep, GraphType type) :
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