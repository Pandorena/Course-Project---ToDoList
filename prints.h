#pragma once

#include "functions.h"



using namespace std;

static string PriorityNames[] = {
    "none",
    "Low",
    "Medium",
    "High"
};

static string StatusNames[] = {
    "none",
    "Preparation",
    "InProgress",
    "Done"
};



void printMenu();
int GetUserId(string username);
void printAdding();
void printPrinting();
void printPrintingByUsername();
void printPrintingBySorting();
void printDeleting();
void printTask(const Task& task);
void printProject(const Project& project);
void printProjects();
void printUsers();
void printTasks();
bool printTasksForUser(string userName, PriorityLevel prio = (PriorityLevel)0);
bool printProjectsForUser(string userName);
void printCounting();