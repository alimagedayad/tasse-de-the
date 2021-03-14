#include "Node.h"
#include <iostream>
//#include <Windows.h>
#include <vector>
#pragma once
class LinkedList
{
public:
    // constructor
    LinkedList();
    //members
    // public
    void add_node(int, int, std::string, std::string, int day, int month, int year, int hour, int minute);

    void edit_node(int num, int ID, std::string tsk, std::string ctg, int day, int month, int year, int hour, int minute);

    void push_node(int, std::string);

    string display_list(int);

    //void print_backward();

    bool insert_node(int, const int&);

    void delete_index(const int&);

    node* pop_node();
    std::vector<std::vector<std::string>> exportNode(int);
    node* search_with_value(const int&);
    void delete_ID(const int ID);
    void node_swap(node* left, node* right);
    void sort_time(int high_low);
    void swap_index(int i, int j);
    node* find_index(int i);
    int smaller(node* temp1, node* temp2);
    int n_nodes();
    void sort_priority(int high_low);
    void check_notifications();
    //friend std::ostream& operator<<(std::ostream& out, LinkedList);
    // private
private:
    node* head;
    node* tail;
    //methods
    // public
};
