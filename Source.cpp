#include <iostream>
#include "LinkedList.h"
#include "Node.h"

int main() {
	LinkedList mylist;
	mylist.add_node(5);
	mylist.add_node(11);
	mylist.print_forward();
	std::cin.get();
}