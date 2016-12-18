// define your linked list template class here
#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "abstract_list.h"
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>

template <typename T>
class LinkedList : public AbstractList<T>
{
public:

	// Constructor
	LinkedList();

	// Destructor
	~LinkedList();

	// copy constructor
	LinkedList(const LinkedList & x);

	// copy assignment
	LinkedList& operator=(LinkedList x);

	//for copy-swap idiom
	void swap(LinkedList<T>& x, LinkedList<T>& y);

	// returns true if the stack is empty
	bool isEmpty();

	// returns the length of the linked list
	size_t getLength();

	//inserts item into position in the linked list
	void insert(std::size_t position, const T& item);

	//removes whatever is at position
	void remove(std::size_t position);

	// removes everything from the list
	void clear();

	//returns the value at position
	T getEntry(std::size_t position);

	//sets the entry at position to newValue
	void setEntry(std::size_t position, const T& newValue);


private:
	template<typename U>
	struct Node {
		U data;
		Node<U> * next;
		Node<U> * prev;

		Node() : next(nullptr), prev(nullptr) {};
		Node(const U& d) : data(d), next(nullptr), prev(nullptr) {};
		//initializes a doubly linked list
	};

	Node<T> * head;
	std::size_t size;
};
#include "linked_list.txx"
#endif // _LINKED_LIST_H_