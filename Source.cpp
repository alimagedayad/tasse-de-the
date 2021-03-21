#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <iomanip>
#include <thread>
#include "DBHandle.h"
#include <vector>
#include <nlohmann/json.hpp>
#include "fort.hpp"
#include<unistd.h>

using json = nlohmann::json;

int tskID = 1;

using namespace std;

vector<vector<string>> taskReq;

std::vector<std::vector<std::string>> exportedNode;

void check_alerts(LinkedList * todo, int * command)
{
    while (true)
    {
        todo->check_notifications();
        if (*command == -1)
            break;
    }
}

void todo_list_thread(LinkedList *todo_list, int* command, DBHandle *db)
{
    cpr::Response tempJS = db->fetchTasks();
    db->initLinkedList(json::parse(tempJS.text), todo_list, tskID);
    while (*command != -1) {
        string table;
        #ifdef __APPLE__
        system("clear");
        #elif __Win32
        system("cls");
        #endif

        vector<string> taskArr;




//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole, 13);
        cout << setw(50) << "Welcome to the TODO List application" << endl;
        cout << "We are now entering the terminal verion of the todo list: " << endl;
//        SetConsoleTextAttribute(hConsole, 2);
        table = todo_list->display_list(0);
        cout << table << endl;
//        SetConsoleTextAttribute(hConsole, 15);
        cout << "Please choose an intruction from the following list: " << endl;
        cout << "1-> Add a new task \n2->Delete an existing task with ID \n3->Edit a task\n4->sort list by priority (descending)\n5->sort list by priority (ascending)\n6-> sort list by soonest task\n-1->Terminate program" << endl;
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

            taskArr.push_back(to_string(val));
            taskArr.push_back(to_string(tskID));
            taskArr.push_back(task);
            taskArr.push_back(ctg);
            taskArr.push_back(to_string(day));
            taskArr.push_back(to_string(month));
            taskArr.push_back(to_string(year));
            taskArr.push_back(to_string(hour));
            taskArr.push_back(to_string(minute));
            taskArr.push_back(to_string(0));
            db->create2DVector(taskReq, &taskArr);
            json req = db->constructJSON(taskReq);
            cpr::Response reqCode = db->insertTask(req);
            auto reqRes = json::parse(reqCode.text);
            int responseCode = db->requestCheck(reqRes);
            db->printStatusCode(responseCode);
            taskReq.clear();
            todo_list->add_node(val, tskID, task, ctg, day, month - 1, year - 1900, hour, minute);
            tskID++;
        }

        else if (*command == 2) {
            int del_id;
            cout << "Enter the task ID you want to delete: " << endl;
            cin >> del_id;
            todo_list->delete_ID(del_id);
            exportedNode = todo_list->exportNode(todo_list->n_nodes());

            cpr::Response reqCode = db->emptyDB();
            auto reqRes = json::parse(reqCode.text);
            int responseCode = db->requestCheck(reqRes);
            db->printStatusCode(responseCode);

            // Insert the populated records
            json dReq = db->constructJSON(exportedNode);
            cout << "exportedNode size: " << dReq.size() << endl;
            db->printJSON(dReq);
            reqCode = db->insertTask(dReq);
            reqRes = json::parse(reqCode.text);
            responseCode = db->requestCheck(reqRes);

//            cpr::Response reqCode = db->insertTask(req);
//            auto reqRes = json::parse(reqCode.text);
//            int responseCode = db->requestCheck(reqRes);
//            db->printStatusCode(responseCode);
//            taskReq.clear();

            // Debugging only
            // TODO: Remove in production
//            cout << "dReq size " << dReq.size() << endl;
//            db->printJSON(dReq);
//            exportedNode = todo_list->exportNode(0);
//            db->emptyDB();
//            json req = db->constructJSON(exportedNode);
//            int reqCode = db->insertTask(req);
//            if(reqCode == 200){
//                cout << "Task edited successfully!" << endl;
//            }

            // TODO: Uncomment when the test is passed
//            int reqCode = db->insertTask(req);
//            if(reqCode == 200){
//                cout << "Task deleted successfully!" << endl;
//            }
        }
            /*else if (*command == 3) {
                cout << todo_list->print_forward(0); system("PAUSE");
            }

            else if (*command == 4) { todo_list->print_backward(); system("PAUSE"); }*/
        else if (*command == 3)
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

            exportedNode = todo_list->exportNode(0);

            //resetting IDs
            cpr::Response reqCode = db->emptyDB();
            auto reqRes = json::parse(reqCode.text);
            int responseCode = db->requestCheck(reqRes);
            db->printStatusCode(responseCode);

            // Inserting edited records
            json req = db->constructJSON(exportedNode);
            reqCode = db->insertTask(req);
            reqRes = json::parse(reqCode.text);
            responseCode = db->requestCheck(reqRes);
            db->printStatusCode(responseCode);

//            int reqCode = db->insertTask(req);
//            if(reqCode == 200){
//                cout << "Task edited successfully!" << endl;
//            }
        }
        else if (*command == 4)
        {
            todo_list->sort_priority(1);
        }
        else if (*command == 5)
        {
            todo_list->sort_priority(0);
        }
        else if (*command == 6)
        {
            todo_list->sort_time(0);
        }
        /*else if (*command == 9) {
            mciSendString("open \"Alarm.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
            mciSendString("play mp3", NULL, 0, NULL);
            PlaySound("TF050.WAV", NULL, SND_SYNC);
            PlaySound("TF050.WAV", NULL, SND_SYNC);
            PlaySound("TF050.WAV", NULL, SND_SYNC);
            Sleep(1500);
            cout << "Audio file playing...\n\n"<<endl;
            system("PAUSE");
        }*/
    }
}

int main() {


    int command = NULL;
    LinkedList todo_list;

    DBHandle db("https://TDTDatabase.alimagedayad.repl.co/");

    thread t1{ [&]() {todo_list_thread(&todo_list, &command, &db); } };
    thread t2{ [&]() {check_alerts(&todo_list, &command); } };
    t1.join();
    t2.join();

    cout << "nice to meet you sir, hope we cured your procrastination :)" << endl;
}