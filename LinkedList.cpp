#include "LinkedList.h"
LinkedList::LinkedList() {
	head = nullptr;
}

void LinkedList::add_node(int num) {

	if (head == nullptr) {
		head = new node(num);
	}
	else {
		node* temp;
		temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new node(num);
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
