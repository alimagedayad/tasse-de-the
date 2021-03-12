//
// Created by Ali Ayad on 12/03/2021.
//

#pragma once

#include <string>
#include <vector>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class DBHandle {

public:
    DBHandle(std::string url);
    json fetchTasks();
    void printDB();
    void insertTask();
    void create2DVector(std::vector<std::vector<std::string>>&, std::vector<std::string>*, std::vector<std::string> *, std::vector<std::string> *,
                        std::vector<std::string> *, std::vector<std::string> *);
    json constructJSON(std::vector<std::vector<std::string>> );
    std::string getURL();
    private:
    std::string url;
};


