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
#include "termcolor.hpp"
//#include <unistd.h>

string condition = "All";
using json = nlohmann::json;

int tskID = 1;

using namespace std;

vector<vector<string>> taskReq;

std::vector<std::vector<std::string>> exportedNode;

void check_alerts(LinkedList* todo, int* command, int* backround, int* time)
{
    while (true)
    {
        *time = *time + 1;
        if (todo->check_notifications()) ShowWindow(GetConsoleWindow(), SW_RESTORE);
        if (*time > *backround) ShowWindow(GetConsoleWindow(), SW_RESTORE);
        if (*command == -1)
            break;
    }
}

void todo_list_thread(LinkedList* todo_list, int* command, DBHandle* db, int* backround, int* time)
{
    //cout << "Try 1:" << endl;
    cpr::Response tempJS = db->fetchTasks();
    //cout << tempJS.text << endl; 
    //cout << "Try 2:" << endl;
    db->initLinkedList(json::parse(tempJS.text), todo_list, tskID);
    //cout << "Try 3:" << endl;
    while (*command != -1) {
#ifdef __APPLE__
        system("clear");
#elif _WIN32
        system("cls");
#endif

        cout << "tskID: " << tskID << endl;

        vector<string> taskArr;

        string table;
        cout << termcolor::magenta << setw(50) << "Welcome to the TODO List application" << endl;
        cout << "We are now entering the terminal verion of the todo list: " << endl;

        table = todo_list->display_list(0, condition);
        cout << termcolor::green << table << endl;
        cout << termcolor::reset << "Please choose an intruction from the following list: " << endl;
        cout << "1-> Add a new task \n2-> Delete an existing task with ID \n3-> Edit a task\n4-> Sort list by priority (descending)\n5-> Sort list by priority (ascending)\n6-> Sort list by soonest task\n7-> Mark task as completed\n8-> Show all completed tasks\n9-> Show all incompleted tasks\n10-> Show tasks in specific category\n11-> Restore to default\n12-> set backround processing\n-1->Terminate program" << endl;
        cout << "Enter command: ";
        cin >> *command;
        switch (*command) {
        case 1:
        {
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
            taskArr.push_back(to_string(false));
            db->create2DVector(taskReq, &taskArr);
            json req = db->constructJSON(taskReq);
            cpr::Response reqCode = db->insertTask(req);
            auto reqRes = json::parse(reqCode.text);
            int responseCode = db->requestCheck(reqRes);
            db->printStatusCode(responseCode);
            taskReq.clear();
            todo_list->add_node(val, tskID, task, ctg, day, month - 1, year - 1900, hour, minute);
            tskID++;
            break;
        }
        case 2:
        {
            int del_id;
            cout << "Enter the task ID you want to delete: " << endl;
            cin >> del_id;
            todo_list->delete_index(del_id);
            exportedNode = todo_list->exportNode(0);

            cpr::Response reqCode = db->emptyDB();
            auto reqRes = json::parse(reqCode.text);
            int responseCode = db->requestCheck(reqRes);
            db->printStatusCode(responseCode);

            // Insert the populated records
            json dReq = db->constructJSON(exportedNode);
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
            break;
        }
        case 3:
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
            todo_list->edit_node(val, i, task, ctg, day, month - 1, year - 1900, hour, minute);
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
            break;
        }
        case 4:
            todo_list->sort_priority(1);
            break;
        case 5:
            todo_list->sort_priority(0);
            break;
        case 6:
            todo_list->sort_time(0);
            break;
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
        case 7: {
            int id;
            cout << "Enter Node ID: " << endl;
            cin >> id;
            todo_list->complete_node(id);
            cpr::Response reqCode = db->emptyDB();
            auto reqRes = json::parse(reqCode.text);
            int responseCode = db->requestCheck(reqRes);
            //            db->printStatusCode(responseCode);
            exportedNode = todo_list->exportNode(0);
            json dReq = db->constructJSON(exportedNode);
            cout << "exportedNode size: " << dReq.size() << endl;
            reqCode = db->insertTask(dReq);
            reqRes = json::parse(reqCode.text);
            responseCode = db->requestCheck(reqRes);
            break;
        }
        case 8:
            condition = "Completed";
            break;
        case 9:
            condition = "Incomplete";
            break;
        case 10:
            cout << "Enter category";
            cin >> condition;
            break;
        case 11:
            condition = "All";
            break;
        case 12:
            cout << "Enter time (in seconds) and -1 for until notifications : ";
            cin >> *backround;
            *time = 0;
            ShowWindow(GetConsoleWindow(), SW_HIDE);
            break;
        }
    }
}

int main() {

    cout << "Hi world!";

    int command = NULL;
    LinkedList todo_list;
    int backround = NULL;
    int time = NULL;
    
    DBHandle db("https://tasse-de-the-web-h5bxp.ondigitalocean.app/");
    
    thread t1{ [&]() {todo_list_thread(&todo_list, &command, &db, &backround, &time); } };
    thread t2{ [&]() {check_alerts(&todo_list, &command, &backround, &time); } };
    t1.join();
    t2.join();
    
    cout << "nice to meet you sir, hope we cured your procrastination :)" << endl;
}