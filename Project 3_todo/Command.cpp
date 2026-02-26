#include "Command.h"
#include "TODOmanager.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

enum class CmdType { Add, Delete, List, SortImp, SortDate, Exit, Invalid, ManageTODO, Edit, Export, Help};
//list all types of commands

static const std::unordered_map<std::string, CmdType> cmdMap = {
    {"add", CmdType::Add},
    {"delete", CmdType::Delete},
    {"list", CmdType::List},
    {"sortimp", CmdType::SortImp},
    {"sortdate", CmdType::SortDate},
    {"exit", CmdType::Exit},
    {"TODO setting", CmdType::ManageTODO},
    { "edit", CmdType::Edit },
    {"export", CmdType::Export},
    {"help",CmdType::Help }
};
//using map to construct string-cmd relation

Command::Command(TODOlist& list) : todoList(list) {}
//implementation of constructor

bool Command::execute(const std::string& input) {
    std::istringstream iss(input);
    std::string cmdStr;
    iss >> cmdStr;
    //using isstream to extract from current line and cmdStr to store first word of current line, which is current cmd

    std::transform(cmdStr.begin(), cmdStr.end(), cmdStr.begin(), ::tolower);
    //using transform to standardrize input

    auto it = cmdMap.find(cmdStr);
    CmdType type = (it != cmdMap.end()) ? it->second : CmdType::Invalid;
    //search for corresponding cmd and initialize cmdtype using iterator

    switch (type) {
    case CmdType::Add: {
        std::string name;
        if (iss >> name) {
            TODO task;
            task.name = name;
            todoList.add_TODO_to_list(task);
            std::cout << R"(")" << name << R"(")" << " has been successfully added to the list" << std::endl;
            todoList.display_list();
            //display list after amending it
        }
        else {
            std::cout << "Invalid input format. Use \"add <TODO name>\"" << std::endl;
        }
        break;
    }
    case CmdType::Delete: {
        std::string name;
        if (iss >> name) {
            todoList.delete_by_name(name);
            std::cout << R"(")" <<name << R"(")" << " has been successfully deleted from the list" << std::endl;
            todoList.display_list();

            //display list after amending it

        }
        else {
            std::cout << "Invalid input format. Use \"delete <TODO name>\"" << std::endl;
        }
        break;
    }
    case CmdType::List:
        todoList.display_list();
        break;
    case CmdType::SortImp:
        todoList.sort_list_by_importance();
        std::cout << "The list has been sorted based on importance" << std::endl;

        todoList.display_list();
        //display list after amending it
        break;
    case CmdType::SortDate:
        todoList.sort_list_by_date();
        std::cout << "The list has been sorted based on date" << std::endl;

        todoList.display_list();
        //display list after amending it
        break;
    case CmdType::Edit: {
        std::cout << "Please input index of the task to be edited: ";
        size_t idx;
        if (std::cin >> idx) {
            std::cin.ignore(); //clear "\n"
            try {
                TODO& task = todoList.get_item(idx - 1);
                TODOmanager mgr(task);
                mgr.run_TODOmanager();
            }
            catch (const std::out_of_range&) {
                std::cout << "Invalid index\n";
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
        }
        break;
    }
    case CmdType::Export: {
        todoList.ExportCurrentList();
        break;
    }
    case CmdType::Help: {
        TODOlist::Help();
    }
    case CmdType::Exit:
        return false; 
    
    default:
        std::cout << "Invalid command type, please refer to the instruction using \"help\"" << std::endl;
        break;
    }
    return true;
}