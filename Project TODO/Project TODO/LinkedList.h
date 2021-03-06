#include "Node.h"
#include <iostream>
#include <Windows.h>
#pragma once
class LinkedList
{
public:
	// constructor
	LinkedList();
	//members
		// public
	void add_node(int, std::string, std::string);

	void push_node(int, std::string);

	void print_forward();

	void print_backward();

	bool insert_node(int, const int&);

	void delete_index(const int&);

	node* pop_node();

	node* search_with_value(const int&);

	void node_swap(node* left, node* right);

	void swap_index(int i, int j);
	node* find_index(int i);

	int n_nodes();
	// private
private:
	node* head;
	node* tail;
	//methods
		// public
};

