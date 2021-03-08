#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <iomanip>
int tskID = 0;
using namespace std;

void display_list(LinkedList todo)
{
	int n = todo.n_nodes();
	for (int i = 0; i < n; i++)
		cout << todo.print_forward(i);
}

int main() {
	int command = NULL;
	LinkedList todo_list;


	while (command != -1) {
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 13);
		cout << setw(50) << "Welcome to the TODO List application" << endl;
		cout << "We are now entering the terminal verion of the todo list: " << endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Please choose an intruction from the following list: " << endl;
		cout << "1-> Add a new task \n2->Delete an existing task with index \n3->Print list forward\n4->Print list backward\n5->Swap tasks\n-1->Terminate program" << endl;
		cout << "Enter command: ";
		cin >> command;
		if (command == 1) {
			int val;
			string task, ctg;
			cout << "Enter task description: ";
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			getline(cin, task);
			cout << "Enter task priority: ";
			cin >> val;
			cout << "Enter task category: ";
			cin >> ctg;
			todo_list.add_node(val, task, ctg,tskID);
			tskID++;
		}
		else if (command == 2) {
			int del_indx;
			cout << "Enter the task index you want to delete: " << endl;
			cout << "'''INDECES ARE IN 0 BASE'''" << endl;
			cin >> del_indx;
			todo_list.delete_index(del_indx);
		}
		else if (command == 3) { 
			cout << todo_list;
			system("PAUSE");

		}
		else if (command == 4) { todo_list.print_backward(); system("PAUSE");}
		else if (command == 5)
		{
			int i = 0; 
			int j = 0;
			cout << "Enter the indeces you want to swap: "<<endl;
			cout << "'''INDECES ARE IN 0 BASE'''" << endl;
			cin >> i >> j;
			todo_list.swap_index(i, j);
			
		}
	}
	cout << "nice to meet you sir, hope we cured your procrastination :)" << endl;
	std::cin.get();




}
