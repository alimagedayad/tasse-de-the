#pragma once
#include <iostream>
class node
{
public:
	node(int num, std::string task, std::string category);
	int number;
	std::string task;
	std::string category;
	node* next = nullptr;
	node* prev = nullptr;
};

