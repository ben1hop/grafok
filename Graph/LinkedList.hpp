#pragma once

#include "Node.hpp"

class LinkedList {
private:
	Node* head;
	int size;
public:
	LinkedList() : head(nullptr) , size(0) {}

	~LinkedList() {
		if (head == nullptr)
			return;
		while (head != nullptr) {
			Node* tmp = head->next;
			delete head;
			head = tmp;
		}
	}

	int length() const { return size; }

	// Appends to the front of the list.
	void append(const int value) {
		Node* temp = new Node(value);
		temp->next = head;
		head = temp;
		++size;
	}

	// Removes from the list.
	void remove(const int value) {
		if (head == nullptr)
			return;
		// head delete
		if (head->_value == value) {
			Node* temp = head->next;
			delete head;
			head = temp;
			return;
		}
		// inside element delete
		Node* curr = head->next;
		Node* prev = head;
		while (curr != nullptr) {
			if (value == curr->_value) {
				prev->next = curr->next;
				delete curr;
				return;
			}
			prev = curr;
			curr = curr->next;	
		}
	}

	// Returns the first occurences index or -1.
	int findIndex(const int value) {
		if (head == nullptr)
			return -1;
		Node* curr = head;
		int i = 0;
		while (curr != nullptr && curr->_value != value) {
			curr = curr->next;
			i++;
		}
		return (curr == nullptr) ? -1 : i;
	}
};