#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include "fort.hpp"
using namespace std;
class node
{
public:
    node(int num, std::string task, std::string category, int cnt, bool check = false);
    int number;
    int ID;
    tm timer;
    std::string task;
    std::string category;
    node* next = nullptr;
    node* prev = nullptr;
    int notification;
    bool completed;
    void set_timer(int year, int month, int day, int hour, int min);
    void check_alarm();
    //friend std::ostream& operator<<(std::ostream& out, node);
};
