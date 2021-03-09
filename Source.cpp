#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <iomanip>
#include <thread>
int tskID = 0;

using namespace std;




void check_alerts(LinkedList * todo, int * command)
{
	while (true)
	{
		todo->check_notifications();
		if (*command == -1)
			break;
	}
}

void todo_list_thread(LinkedList *todo_list, int* command)
{
	while (*command != -1) {
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, 13);
		cout << setw(50) << "Welcome to the TODO List application" << endl;
		cout << "We are now entering the terminal verion of the todo list: " << endl;
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Please choose an intruction from the following list: " << endl;
		cout << "1-> Add a new task \n2->Delete an existing task with index \n3->Print list forward\n4->Print list backward\n5->Edit a task\n6->sort list by priority (descending)\n7->sort list by priority (ascending)\n8-> sort list by soonest task\n-1->Terminate program" << endl;
		cout << "Enter command: ";
		cin >> *command;
		if (*command == 1) {
			int val, day, month, year, hour, minute;
			string task, ctg;
			cout << "Enter task description: ";
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			getline(cin, task);
			cout << "Enter task priority: ";
			cin >> val;
			cout << "Enter task category: ";
			cin >> ctg;
			cout << "DATE/TIME " << endl;
			cout << "Enter day: ";
			cin >> day;
			cout << "Enter month (1-12): ";
			cin >> month;
			cout << "Enter year (1900+): ";
			cin >> year;
			cout << "Enter hour (0-23): ";
			cin >> hour;
			cout << "Enter minute (0-59): ";
			cin >> minute;
			todo_list->add_node(val, tskID, task, ctg, day, month - 1, year - 1900, hour, minute);
			tskID++;
		}
		else if (*command == 2) { // delete with id not index  NEW FUNCTION NOT TESTED (DELETE ID)
			int del_indx;
			cout << "Enter the task index you want to delete: " << endl;
			cout << "'''INDECES ARE IN 0 BASE'''" << endl;
			cin >> del_indx;
			todo_list->delete_index(del_indx);
		}
		else if (*command == 3) { cout << *todo_list; system("PAUSE"); }
		else if (*command == 4) { todo_list->print_backward(); system("PAUSE"); }
		else if (*command == 5) // remove
		{
			int i = 0;
			cout << "Which task do you want to edit " << endl;
			cout << "'''ENTER ID'''" << endl;
			cin >> i;
			int val, day, month, year, hour, minute;
			string task, ctg;
			cout << "Enter task description: ";
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			getline(cin, task);
			cout << "Enter task priority: ";
			cin >> val;
			cout << "Enter task category: ";
			cin >> ctg;
			cout << "DATE/TIME "<< endl;
			cout << "Enter day: ";
			cin >> day;
			cout << "Enter month (1-12): ";
			cin >> month;
			cout << "Enter year (1900+): ";
			cin >> year;
			cout << "Enter hour (0-23): ";
			cin >> hour;
			cout << "Enter minute (0-59): ";
			cin >> minute;
			todo_list->edit_node(val, i, task, ctg, day, month-1, year-1900, hour, minute);

		}
		else if (*command == 6)
		{
			todo_list->sort_priority(1);
			cout << *todo_list;
			system("PAUSE");
		}
		else if (*command == 7)
		{
			todo_list->sort_priority(0);
			cout << *todo_list;
			system("PAUSE");
		}
		else if (*command == 8)
		{
			todo_list->sort_time(0); // doesn't work BUG
			cout << *todo_list;
			system("PAUSE");
		}
	}
}

int main() {
	int command = NULL;
	LinkedList todo_list;
	


	thread t1{ [&]() {todo_list_thread(&todo_list, &command); } };
	thread t2{ [&]() {check_alerts(&todo_list, &command); } };
	t1.join();
	t2.join();


	cout << "nice to meet you sir, hope we cured your procrastination :)" << endl;
	std::cin.get();




}
