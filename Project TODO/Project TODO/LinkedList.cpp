#include "LinkedList.h"
#include <iomanip>

using namespace std;
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

void LinkedList::add_node(int num, std::string tsk, std::string ctg) {
	if (head == nullptr) {
		head = new node(num,tsk,ctg);
		head->prev = head->next = nullptr;
		tail = head;
	}
	else {
		node* temp; 
		temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new node(num,tsk,ctg);
		temp->next->prev = temp;
		tail = temp->next;
	}
}

void LinkedList::print_forward() {
	if (!head) {
		std::cout << "The list is empty" << std::endl;
		return;
	}
	node* temp = head;
	int counter = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << std::setw(10)<<"Task ID: "<< std::setw(25) << "Task Priority: " << std::setw(25) << "Task Category: " << std::setw(35) << "Task Description: "<<std::endl;
	std::cout << std::string(95, '-') << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
	while (temp->next) {
		std::cout << std::setw(10) << (counter++) + 1 << std::setw(25) << temp->number << std::setw(25) << temp->category << std::setw(35) << temp->task << std::endl;
		temp = temp->next;
	}
	std::cout << std::setw(10) << (counter++) + 1 << std::setw(25) << temp->number << std::setw(25) << temp->category << std::setw(35) << temp->task << std::endl;
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
	node* temp = new node(num,tsk,"");
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
	node* add_this = new node(num,"","");
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
		if (temp->number == val) {
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
	/*temp = left->prev;
	if (temp) temp->next = right;
	right->prev = temp;
	left->prev = right;
	left->next = right->next;
	right->next = left;
	if (left->next != null)
		left->next->prev = left;
		*/
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