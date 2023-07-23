#include "todo.hpp"
#include <vector>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <string>
#include <ios>
#include <filesystem>
#include <fstream>

Task::Task(std::string t, std::string d)
{
    title = t;
    description = d;
}

size_t ToDoList::tasksCount()   { return task_list.size(); }

void ToDoList::clearAll()
{
    std::vector<Task>().swap(task_list);
    std::cout << "Task list was successfully cleared." << '\n';
}

bool ToDoList::validateInput(const std::string& s)
{
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char * p;
    strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

void ToDoList::insertTask()
{
    Task temp;
    std::cout << "To add a new task, "
            << "fill out a title, "
            << "and description (optional)." << '\n';
    
    while (true)
    {
        std::cout << "Please enter title: ";
        std::getline(std::cin >> std::ws, temp.title);
        
        if(temp.title != ""){
            std::cout << "\nPlease enter a description:\n";
            std::getline(std::cin >> std::ws, temp.description);
            std::cout << '\n';
            break;
        }

        continue;
    }

    task_list.push_back(temp);

    char option;

    while (true)
    {
        std::cout << "Do you want to add another task?\n";
        std::cout << "Y/y (yes), N/n (no): ";
        std::cin >> option;
        if (tolower(option) == 'y' || tolower(option) == 'n')
        {
            if (tolower(option) == 'y')
            {
                insertTask();
                return;
            }
            else
            {
                mainMenu();
                return;
            }
        }
        else
        {
            std::cout << "Invalid option." << '\n';
            continue;
        }
    }
}

void ToDoList::deleteTaskMenu()
{
    int choice;
    std::string input;
    std::cout << "1. Delete recent task" << '\n'
        << "2. Delete a certain task" << '\n'
        << "3. Back to menu" << '\n'
        << "\nEnter your choice: ";
    std::cin >> input;

    std::cin.clear();
    std::cin.ignore();

    if (validateInput(input))
    {
       choice = std::stoi(input);
    }
    else
    {
        std::cout << "Invalid input. Please, try again." << '\n';
        deleteTaskMenu();
    }

    switch(choice){
        case 1:
            deleteRecentTask();
            break;
        case 2:
            deleteTaskAt();
            break;
        case 3:
            mainMenu();
            break;
        default:
            std::cout << "No such option." << '\n';
            deleteTaskMenu();
            break;    
    }
}


void ToDoList::deleteTaskAt()
{
    if (tasksCount() == 0)
    {
        std::cout << "O-ops! No task here! Come back later." << '\n';
        deleteTaskMenu();
    }

    std::string input;
    std::cout << "Name the title of that task:\n";
    std::getline(std::cin >> std::ws, input);
    
    size_t list_size = tasksCount();

    for (size_t i = 0; i < list_size; ++i)
    {
        if (task_list[i].title == input)
        {
            task_list.erase(task_list.begin() + i);
            std::cout << "Task was deleted." << '\n';
            deleteTaskMenu();
        }
    }
 
    std::cout << "Task with such title wasn't found." << '\n';
    deleteTaskMenu();
}


void ToDoList::deleteRecentTask()
{
    if (tasksCount() == 0){
        std::cout << "O-ops! No task here! Come back later." << '\n';
        deleteTaskMenu();
    }

    task_list.pop_back();
    std::cout << "The most recent task was deleted." << '\n';

    deleteTaskMenu();

}

void taskListHeadline(std::ostream& os)
{
    const int WIDTH = 40;
    os << "\t" << std::setw(WIDTH) << std::setfill(' ')  << std::left << "TASK" << "DONE" << '\n';
	os << "\t" << std::setw(WIDTH) << std::left << "----" << std::setfill(' ') << "----" << '\n';
    os.std::ios::unsetf(std::ios::left);
}

void ToDoList::showAllTasks()
{
    if (tasksCount() == 0)
    {
        std::cout << "O-ops! No task here! Come back later." << '\n';
        showTaskMenu();
    }

    taskListHeadline(std::cout);

    for (const auto& task: task_list)
    {
        std::cout << "--- " << task.title << '\n';
    }

    showTaskMenu();
}

void ToDoList::showTaskDetailed()
{
    if (tasksCount()== 0)
    {
        std::cout << "O-ops! No task here! Come back later." << '\n';
        showTaskMenu();
    }

    std::string input;
    std::cout << "Name the title of that task:\n";
    std::getline(std::cin >> std::ws, input);
    std::cout << '\n';

    for(const auto& task: task_list)
    {
        if (task.title == input)
        {
            std::cout << "Title: " << task.title << '\n';
            std::cout << "Description:\n" << task.description << '\n';
            mainMenu();
        }
    }

    std::cout << "Task with such title wasn't found." << '\n';
    showTaskMenu();


}

void ToDoList::showTaskMenu()
{
    int choice;
    std::string input; 

    std::cout << "1. View all tasks" << '\n';
    std::cout << "2. View certain task" << '\n';
    std::cout << "3. Back to menu" << '\n';

    std::cout << "\nEnter your choice: ";
    std::cin >> input;

    std::cin.clear();
    std::cin.ignore();

    if (validateInput(input))
    {
       choice = std::stoi(input);
    }
    else
    {
        std::cout << "Invalid input. Please, try again." << '\n';
        showTaskMenu();
    }
    
    switch(choice){

        case 1:
            showAllTasks();
            break;
        
        case 2:
            showTaskDetailed();
            break;

        case 3:
            mainMenu();
            break;
        
        default:
            std::cout << "No such option." << '\n';
            showAllTasks();
            break;
    }
}


void ToDoList::loadFromFile(){
    std::string file_path;
    std::cout << "What is the file path?" << '\n';
    std::cin >> file_path;

    std::fstream fs(file_path.c_str(), std::fstream::in);

    if (!fs.is_open())
    {
        std::cout << "Couldn't open such file: " << file_path << '\n';
        mainMenu();
    }

    if (fs.peek() == std::fstream::traits_type::eof())
    {
        std::cout << "No tasks to retrieve in file." << '\n';
        mainMenu();
    }

    int line_counter{0};
    Task temp;
    std::string line;
    while (std::getline(fs, line))
    {
        if (line_counter == 0)
        {
            temp.title = line;
            ++line_counter;
        }
        else if (line_counter == 1)
        {
            temp.description = line;
            line_counter = 0;
            task_list.push_back(temp);
        }
    }

    std::cout << "All tasks successfully retrieved." << '\n';

    mainMenu();
}

void ToDoList::loadToFile()
{
    if (tasksCount() == 0)
    {
        std::cout << "No task to load into file." << '\n';
        mainMenu();
    }

    std::string file_path;

    std::cout << "What is the file path? (Write 'Default' to set path to your current directory)" << '\n';
    std::cin >> file_path;
    
    if (file_path == "Default" || file_path == "default")
    {
        std::cout << "Setting path to your current directory.\n";
        std::filesystem::path curr_path = std::filesystem::current_path();
        file_path = curr_path.u8string() + "\\tasks.txt";
    }
    
    std::fstream out_file(file_path.c_str(), std::fstream::app);

    if (!out_file.is_open())
    {
        std::cout << "Couldn't open such file: " << file_path << '\n';
        mainMenu();
    }
    
    for (const auto& task: task_list)
    {
        out_file << task.title << "\n" << task.description << '\n';
    }

    out_file.close();

    std::cout << "Tasks saved successfully." << '\n';
    mainMenu();

}

void startingGreeting(std::ostream& os, const std::string& starting_string)
{
    const int WIDTH = 60;
    os << std::setfill('*') << std::setw(WIDTH) << '\n'; 
    os << std::setfill(' ') << std::setw(WIDTH-20)
            << std::internal << starting_string << '\n';
    os << std::setfill('*') << std::setw(WIDTH) << '\n';
}


void ToDoList::mainMenu()
{
    int choice;
    std::string input;
    
    startingGreeting(std::cout, "Welcome to the starting menu!");

    std::cout << "Here's your options:" << '\n'
        << "1. Add new task" << '\n'
        << "2. Delete task" << '\n'
        << "3. View tasks" << '\n'
        << "4. Save to file" << '\n'
        << "5. Load from file" << '\n'
        << "6. Exit" << '\n';

    std::cout << "Enter your choice: ";
    std::cin >> input;
    
    std::cout << '\n';
    std::cin.clear();
    std::cin.ignore();

    if (validateInput(input))
    {
       choice = std::stoi(input);
    }
    else
    {
        std::cout << "Invalid input. Please, try again." << '\n';
        mainMenu();
    }

    switch(choice){
        case 1:
            insertTask();
            break;
        
        case 2:
            deleteTaskMenu();
            break;
        
        case 3:
            showTaskMenu();
            break;
        
        case 4:
            loadToFile();
            break;

        case 5:
            loadFromFile();
            break;

        case 6:
            exit(99);
            break;
        
        default:
            std::cout << "Unknown option." << '\n';
            break;
    }
}