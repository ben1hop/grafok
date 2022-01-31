#pragma once

class Node {
public:
	Node(int value = 0) : _value(value), next(nullptr) {}
	int _value;
	Node* next;
};