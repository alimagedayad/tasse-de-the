#include "LinkedList.h"
LinkedList::LinkedList() {
	head = nullptr;
	tail = nullptr;
}

void LinkedList::add_node(int num) {
	if (head == nullptr) {
		head = new node(num);
		head->prev = head->next = nullptr;
		tail = head;
	}
	else {
		node* temp;
		temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new node(num);
		temp->next->prev = temp;
		tail = temp->next;
	}
}

void LinkedList::print_forward() {
	if (!head) {
		std::cout << " empty linked list" << std::endl;
		return;
	}
	node* temp = head;
	int counter = 0;
	while (temp->next) {
		std::cout << "node number" << (counter++) + 1 << " with value: " << temp->number << std::endl;
		temp = temp->next;
	}
	std::cout << "node number" << (counter++) + 1 << " with value: " << temp->number << std::endl;

}

void LinkedList::print_backward() {
	if (!tail) {
		std::cout << "empty linked list" << std::endl;
		return;
	}
	node* temp = tail;
	int counter = 0;
	while (temp != nullptr) {
		std::cout << "node number " << (counter++) + 1 << " with value " << temp->number << std::endl;
		temp = temp->prev;
	}
}

void LinkedList::push_node(int num) {
	node* temp = new node(num);
	if (!head) {
		head =tail =  temp;
		return;
	}
	head->prev = temp;
	temp->next = head;
	head = temp;
}

bool LinkedList::insert_node(int num, const int& index) {
	int counter = 0;
	node* temp = head;
	node* add_this = new node(num);
	while (temp != nullptr && counter < index-1) {
		temp = temp->next;
		counter++;
	}
	if (temp == nullptr || counter != index-1 ) {
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
	if (index!= NULL) {
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