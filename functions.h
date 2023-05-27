#pragma once

#include <iomanip>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>

#undef max
using namespace std;

enum PriorityLevel : unsigned char
{
    Low = 1,
    Medium = 2,
    High = 3
};

enum EStatus : unsigned char
{
    Preparation = 1,
    InProgress = 2,
    Done = 3
};


enum SortBy : unsigned char
{
    Date,
    DateReverse,
    Username,
    Priority,
    Status
};



// User structure
struct User
{
    uint64_t user_id;
    string username;
    string name;
};

// Task structure
struct Task
{
    uint64_t user_id;
    uint64_t project_id;
    uint64_t task_id;
    string task_name;
    tm due_date;
    EStatus status;
    PriorityLevel priority_level;
};

// Project structure
struct Project
{
    uint64_t user_id;
    uint64_t project_id;
    string project_name;
    tm due_date;
};

class BadFileName
{
};

inline vector<User> users;
inline vector<Task> tasks;
inline vector<Project> projects;

int GetUserId(string username);
void printMenu();
void choiceA();
void choiceP();
void printUsers();
void printTasks();
void printProjects();
void write_txs(const string fname);
void read_txs(const string fname);
void deleteTab();
void deleteAllProjectTasks(string projectName, int& counter);
