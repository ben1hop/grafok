#pragma once
class IGraphOperations {
public:
	enum GraphDataOp { Add, Delete };
	virtual ~IGraphOperations() {}
	virtual void addEdge(const int& from, const int& to) = 0;
	virtual void addNode(const int& node) = 0;
	virtual void deleteNode(const int& node) = 0;
	//virtual void resizeNodes(const int& node) {}
};