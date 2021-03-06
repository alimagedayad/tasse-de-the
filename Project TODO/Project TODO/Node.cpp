#include "Node.h"
node::node(int num, std::string tsk, std::string ctg) {
	task = tsk;
	number = num;
	category = ctg;
	prev = nullptr;
	next = nullptr;
}