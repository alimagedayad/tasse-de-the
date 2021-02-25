#include "Node.h"
#include <iostream>
#pragma once
class LinkedList
{
public:
	// constructor
	LinkedList();
	//members
		// public
	void add_node(int );

	void push_node(int );

	void print_forward();

	void print_backward();

	bool insert_node(int , const int& );

	void delete_index(const int& );

	node* pop_node();

	node* search_with_value(const int&);
		// private
private:
	node* head;
	node* tail;
	//methods
		// public
};

