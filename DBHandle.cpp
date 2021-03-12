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
            res[i]["name"] = arr[i][0];
            res[i]["category"] = arr[i][1];
            res[i]["checked"] = arr[i][2];
        }
    }
    return res;
}

void DBHandle::printDB(){
    cpr::Response r = cpr::Get(cpr::Url{url.c_str()});
    json j = json::parse(r.text);
    for(int i = 0; i < j.size(); i++){
        std::cout << j[i] << std::endl;
    }
}

