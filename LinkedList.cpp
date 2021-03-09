#include "LinkedList.h"
#include <iomanip>


using namespace std;
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

void LinkedList::edit_node(int num, int ID, std::string tsk, std::string ctg, int day, int month, int year, int hour, int minute) {
	if (head == nullptr) return;
	node* temp = search_with_value(ID);
	if (!temp) return;
	temp->task = tsk;
	temp->number = num;
	temp->category = ctg;
	temp->set_timer(year, month, day, hour, minute);
}



void LinkedList::add_node(int num, int ID , std::string tsk, std::string ctg, int day, int month, int year, int hour, int minute) {
	if (head == nullptr) {
		head = new node(num,tsk,ctg, ID);
		head->set_timer(year, month, day, hour, minute);
		head->prev = head->next = nullptr;
		tail = head;
	}
	else {
		node* temp; 
		temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new node(num,tsk,ctg, ID);
		temp->set_timer(year, month, day, hour, minute);
		temp->next->prev = temp;
		tail = temp->next;
	}
}

node LinkedList::print_forward(int index) {
	node* temp = find_index(index);
	return *temp;
}

void LinkedList::print_backward() {
	if (!tail) {
		std::cout << "The list is empty" << std::endl;
		return;
	}
	node* temp = tail;
	int counter = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << std::setw(10) << "Task ID: " << std::setw(25) << "Task Priority: " << std::setw(25) << "Task Category: " << std::setw(35) << "Task Description: " << std::endl;
	std::cout << std::string(95, '-') << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	while (temp != nullptr) {
		std::cout << std::setw(10) << (counter++) + 1 << std::setw(25) << temp->number << std::setw(25) << temp->category << std::setw(35) << temp->task << std::endl;
		temp = temp->prev;
	}
}

void LinkedList::push_node(int num, std::string tsk) {
	node* temp = new node(num, tsk, "", 0);
	if (!head) {
		head = tail = temp;
		return;
	}
	head->prev = temp;
	temp->next = head;
	head = temp;
}

bool LinkedList::insert_node(int num, const int& index) {
	int counter = 0;
	node* temp = head;
	node* add_this = new node(num, "", "",0);
	while (temp != nullptr && counter < index - 1) {
		temp = temp->next;
		counter++;
	}
	if (temp == nullptr || counter != index - 1) {
		return false;
	}
	add_this->next = temp->next;
	temp->next->prev = add_this;
	add_this->prev = temp;
	temp->next = add_this;
	return true;

}

void LinkedList::delete_index(const int& index = NULL) {
	if (index == 0) {
		node* temp = head;
		head->next->prev = nullptr;
		head = head->next;
		delete(temp);
		return;
	}
	if (index != NULL) {
		node* temp = head;
		for (int i = 0; i < index; i++) {
			if (temp->next) { temp = temp->next; }
		}
		temp->prev->next = temp->next;
		if (temp->next) {
			temp->next->prev = temp->prev;
		}
		delete(temp);
	}
}

node* LinkedList::pop_node() {
	node* pop = tail;
	tail->prev->next = nullptr;
	tail = tail->prev;
	return pop;

}

node* LinkedList::search_with_value(const int& val) {
	node* temp = head;
	while (temp)
	{
		if (temp->ID == val) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


void LinkedList::node_swap(node* left, node* right)
{
	node** p1pn;            /* & ptr1->prev->next */
	node** p1np;            /* & ptr1->next->prev */
	node** p2pn;            /* & b->prev->next */
	node** p2np;
	node* temp;
	if (head == NULL || left == NULL || right == NULL || right == left)
		return;
	if (head == right)
		p1pn = &head;
	else
		p1pn = &right->prev->next;
	if (head == left)
		p2pn = &head;
	else
		p2pn = &left->prev->next;
	if (right->next == NULL) {
		p1np = &tail;
		tail = right;
	}
	else
		p1np = &right->next->prev;

	if (left->next == NULL) {
		p2np = &tail;
		tail = left;
	}
	else
		p2np = &left->next->prev;

	*p1pn = left;
	*p1np = left;
	*p2pn = right;
	*p2np = right;
	temp = right->prev;
	right->prev = left->prev;
	left->prev = temp;
	temp = right->next;
	right->next = left->next;
	left->next = temp;

}

node* LinkedList::find_index(int i)
{
	node* temp = head;
	for (int k = 0; k < i; k++) temp = temp->next;
	return temp;
}


void LinkedList::swap_index(int i, int j)
{
	
	node* left = find_index(i);
	node* right = find_index(j);
	node_swap(left, right);
}

int LinkedList::n_nodes() // calculates number of nodes
{
	if (head == 0) return 0;
	int n = 1;
	node* temp = head;
	while (temp->next != nullptr) {
		temp = temp->next;
		n++;
	}
	return n;
}

void LinkedList::sort_priority(int high_low) //bubble sort
{
	int n = n_nodes();
	if (n < 1) return;
	node* temp1 = head;
	node* temp2 = head;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++)
		{
			temp1 = find_index(i);
			temp2 = find_index(j);
			if (temp2->number < temp1->number) {
				swap_index(i, j);
			}
		}
	}
	// 0 is low to high 1 is high to low;
	if (high_low)
	{
		for (int i = 0; i < n / 2; i++) swap_index(i, n - i - 1);
	}
}

int LinkedList::smaller(node* temp1, node* temp2)
{
	if (difftime(mktime(&temp1->timer), mktime(&temp2->timer) < 0))
		return 1;
	return 0;
}

void LinkedList::check_notifications()
{
	//cout <<endl<< "Notification" << endl;
	Sleep(1000);
	//cout << endl << "After Sleep " << n_nodes() << endl;
	node* temp = head;
	//cout << "Alarm1";
	if (head == nullptr) return;
	//cout << "Alarm2";
	//Sleep(1000);
	for (int i = 0; i < n_nodes(); i++)
	{
		temp->check_alarm();
		temp = temp->next;
	}
	//cout << endl << "Done Loop" << endl;
}

void LinkedList::sort_time(int high_low) //bubble sort
{
	int n = n_nodes();
	if (n < 1) return;
	node* temp1 = head;
	node* temp2 = head;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++)
		{
			temp1 = find_index(i);
			temp2 = find_index(j);
			if (smaller(temp2,temp1)) {
				swap_index(i, j);
			}
		}
	}
	// 0 is low to high 1 is high to low;
	if (high_low)
	{
		for (int i = 0; i < n / 2; i++) swap_index(i, n - i - 1);
	}
}



std::ostream& operator<<(std::ostream& out, LinkedList object) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << std::string(144, '-') << std::endl;
	std::cout << "|" << std::setfill(' ') << std::setw(10) << "|" << "Task ID" << "|" << std::setfill(' ') << std::setw(20) << "|" << "Task Priority" << "|" << std::setfill(' ') << std::setw(20) << "|" << "Task Category" << "|" << std::setfill(' ') << std::setw(30) << "|" << "Task Description" << "|" << setw(10) << "|" << "Date" << "|" << std::setfill(' ') << std::setw(20) << "|" << "Time" << "|" << std::setw(10) << "|" << std::endl;
	std::cout << std::string(144, '-') << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	int n = object.n_nodes();
	for (int i = 0; i < n; i++)
		cout << object.print_forward(i);
	return out;
}