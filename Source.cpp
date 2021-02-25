#include <iostream>
#include "LinkedList.h"
#include "Node.h"

using namespace std;
int main() {
	int command = NULL;
	LinkedList todo_list;


	std::cout << "we are now entering the terminal verion of the todo list: " << std::endl;
	
	while (command != -1) {
		cout << "command palette: " << endl;
		cout << "1-> add node \n2->delete node with index \n3->print list forward\n4->print list backward" << endl;
		cin >> command;
		if (command == 1) {
			int val;
			cout << "enter the value to add it to the list: " << endl;
			cin >> val;
			todo_list.add_node(val);
		}
		else if (command == 2) {
			int del_indx;
			cout << "enter the index you want to delete: " << endl;
			cout << "'''INDECES ARE IN 0 BASE'''" << endl;
			cin >> del_indx;
			todo_list.delete_index(del_indx);
		}
		else if (command == 3) {todo_list.print_forward();	}
		else if (command == 4) { todo_list.print_backward(); }
	}
	cout << "nice to meet you sir, hope we cured your procrastination :)" << endl;
	std::cin.get();
	

	
	
}
