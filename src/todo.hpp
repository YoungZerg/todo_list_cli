#pragma once
#include <iostream>
#include <vector>

struct Task{
    std::string title;
    std::string description;
    
    Task(std::string t = "Default title", std::string d = ""); 
};

class ToDoList{
private:
    
    std::vector<Task> task_list;
public:
    void insertTask(); 
    void deleteTaskAt();
    void deleteRecentTask();
    void deleteTaskMenu(); 
    void showTaskMenu();
    void showAllTasks();
    void showTaskDetailed();
    void clearAll(); 
    void mainMenu(); 
    void loadToFile();
    void loadFromFile();
    size_t tasksCount(); 
    bool validateInput(const std::string& input); 

};
