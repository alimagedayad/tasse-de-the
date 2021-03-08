#pragma once
#include <iostream>
class node
{
public:
	node(int num, std::string task, std::string category, int ID);
	int number, ID;
	std::string task;
	std::string category;
	node* next = nullptr;
	node* prev = nullptr;
	friend std::ostream& operator<<(std::ostream& out, node);
};

