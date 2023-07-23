#pragma once
#include <iostream>
#include <vector>

struct Task{
    std::string title;
    std::string description;
    
    Task(std::string t = "Default title", std::string d = ""); //done
};

class ToDoList{
private:
    
    std::vector<Task> task_list;
public:
    void insertTask(); //done
    void deleteTaskAt();//done
    void deleteRecentTask();//done
    void deleteTaskMenu(); //done
    void showTaskMenu();// done
    void showAllTasks();//done
    void showTaskDetailed();//done
    void clearAll(); //done
    void mainMenu(); //done
    void loadToFile();
    void loadFromFile();
    size_t tasksCount(); //done
    bool validateInput(const std::string& input); //done

};