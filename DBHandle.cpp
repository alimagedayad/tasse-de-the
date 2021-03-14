//
// Created by Ali Ayad on 12/03/2021.
//
#include<iostream>
#include "DBHandle.h"
#include <string>

DBHandle::DBHandle(std::string u){
    url = u;
};

json DBHandle::constructJSON(std::vector<std::vector<std::string>> arr) {
    json res;
    if (!arr.empty()) {
        for (int i = 0; i < arr.size(); i++) {
            res[i]["taskPriority"] = arr[i][0];
            res[i]["tid"] = arr[i][1];
            res[i]["content"] = arr[i][2];
            res[i]["category"] = arr[i][3];
            res[i]["taskDay"] = arr[i][4];
            res[i]["taskMonth"] = arr[i][5];
            res[i]["taskYear"] = arr[i][6];
            res[i]["taskHour"] = arr[i][7];
            res[i]["taskMinute"] = arr[i][8];
            res[i]["taskSecond"] = arr[i][9];
        }
    }
    return res;
}

json DBHandle::fetchTasks() {
    std::string fetchURL = url + "tasks/all";
    cpr::Response r = cpr::Get(cpr::Url{fetchURL.c_str()});
    json j = json::parse(r.text);
    return j;
}

void DBHandle::create2DVector(std::vector<std::vector<std::string>>& data, std::vector<std::string>*a, std::vector<std::string> *b, std::vector<std::string> *c,
                  std::vector<std::string> *d, std::vector<std::string> *e){
    if(a != nullptr){
        data.push_back(a[0]);
    }
    if(b != nullptr){
        data.push_back(b[0]);
    }
    if(c != nullptr){
        data.push_back(c[0]);
    }
    if(d != nullptr){
        data.push_back(d[0]);
    }
    if(e != nullptr){
        data.push_back(e[0]);
    }
}

void DBHandle::printDB(){
    json j = fetchTasks();
    for(auto & i : j){
        std::cout << i << std::endl;
    }
}

json DBHandle::emptyDB() {
    std::string fetchURL = url + "tasks/delete";
    cpr::Response r = cpr::Post(cpr::Url{fetchURL.c_str()});
    json j = json::parse(r.text);
    return j;
}

int DBHandle::insertTask(const json& data) {
    std::string fetchURL = url + "task/add";

    cpr::Response r = Post(cpr::Url{fetchURL.c_str()},
                           cpr::Body{data.dump()},
                           cpr::Header{{"Content-Type", "application/json"}});

    json j = json::parse(r.text);
    if (j["code"] == 200 && j["response"] == "success") {
//        std::cout << "Data is inserted successfully" << std::endl;
        return 200;
    }

//    else{
//        std::cout << "An error occurred while inserting the data " << std::endl << std::endl << "For debugging: " << std::endl << "code: " << j["code"] << std::endl  << "response: " << j["response"] << std::endl <<  "body: " << j["body"] << std::endl;
//    }
}

void DBHandle::printVector(std::vector<std::vector<std::string>> x){
    for(int i = 0; i < x.size(); i++){
        for(int y = 0; y < x[i].size(); y++){
            std::cout << "Element [" << i << "][" << y <<  "]: " << x[i][y] << std::endl;
        }
    }
}

void DBHandle::printJSON(json x) {
    for(auto & i : x){
        std::cout << i << std::endl;
    }
}



void DBHandle::initLinkedList(json DBData, LinkedList* list) {
    if(!DBData.empty()){

        std::cout << "Populating " << DBData.size() << " records from the database!" << std::endl;

        for(auto & i : DBData){
            list->add_node(i["priority"].get<int>(),
                  i["tID"].get<int>(), i["task"].get<std::string>(),i["category"].get<std::string>(),
                          i["taskDay"].get<int>(), ((i["taskMonth"].get<int>()) - 1), ((i["taskYear"].get<int>()) - 1900),
                                  i["taskHour"].get<int>(), i["taskMinute"].get<int>()
                           );

//                        list->add_node((int)i["priority"], (int)i["tID"], i["task"], i["category"], (int)i["taskDay"]
//            , ((int)i["taskMonth"]) - 1, ((int)i["taskYear"] - 1900), (int)i["taskHour"], (int)i["taskMinute"]);
        }
    }
}

std::string DBHandle::getURL(){
    return url;
}