#include "TODOmanager.h"
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cctype>   

namespace {
    enum class EditCmd {
        SetImportance,
        SetDDL,
        AddDependency,
        Show,
        Help,
        Back,
        SetCompleted,
        Invalid
    };

    const std::unordered_map<std::string, EditCmd> cmdMap = {
        {"importance", EditCmd::SetImportance},
        {"imp", EditCmd::SetImportance},
        {"ddl", EditCmd::SetDDL},
        {"dependency", EditCmd::AddDependency},
        {"dep", EditCmd::AddDependency},
        {"show", EditCmd::Show},
        {"help", EditCmd::Help},
        {"back", EditCmd::Back},
        {"exit", EditCmd::Back}, 
        {"complete", EditCmd::SetCompleted}
    };   
}

TODOmanager::TODOmanager(TODO& task) : TODO_now(task) {}
bool TODOmanager::execute_cmd(std::string& input) {
    std::istringstream iss(input);
    std::string s;
    iss >> s;
    if (s.empty()) return true;  
    std::transform(s.begin(), s.end(), s.begin(), ::tolower); 
    auto it = cmdMap.find(s);
    EditCmd cmd = (it != cmdMap.end()) ? it->second : EditCmd::Invalid;

    switch (cmd) {
    case EditCmd::SetImportance: {
        int val;
        if (iss >> val) {
            TODO_now.setImportance(static_cast<size_t>(val));
            std::cout << "Importance has been set to " << val%6 << "\n";
        }
        else {
            std::cout << "Usage: importance <Value>\n";
        }
        break;
    }
    case EditCmd::SetDDL: {
        std::string dateStr;
        if (iss >> dateStr) {
            TODO_now.setDate(dateStr);
            std::cout << "Date has been set to " << dateStr << "\n";
        }
        else {
            std::cout << "Usage: date <yy-mm-dd>\n";
        }
        break;
    }
    case EditCmd::AddDependency: {
        std::string depName;
        if (iss >> depName) {
            static TODO now_dependency;
            now_dependency.setTODO(depName);
            TODO_now.set_TODO_dependency(depName);
            std::cout << "Dependency added."  << "\n";
        }
        else {
            std::cout << "Usage: dep <TODO name>\n";
        }
        break;
    }
    case EditCmd::Show: {
        std::cout << "Current TODO£º\n"
            << "  Name: " << TODO_now.name << "\n"
            << "  Importance: " << TODO_now.importance << "\n"
            << "  Deadline: " << TODO_now.date << "\n"
            << "  Dependency:";
        for (const auto& v : TODO_now.dependencies)
        {
            std::cout << v << " ";
        }
        std::cout << "\n";
        std::cout << "  Internal index: " << TODO_now.index << "\n"
            << "  Complete status: " << TODO_now.completed << "\n";
       
        break;
    }
    case EditCmd::Help:
        show_help();
        break;
    case EditCmd::Back:
        return false;   
    case  EditCmd::SetCompleted:
    {
        TODO_now.set_completed();
        break;
    }
    case EditCmd::Invalid:
    default:
        std::cout << "Invalid command, use help to refer to command set\n";
        break;
    }
    return true;
}

void TODOmanager::run_TODOmanager() {
    std::cout << "Now editing: " << TODO_now.name << "\n";
    show_help();

    std::string line;
    while (true) {
        std::cout << "Edit> ";
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (!execute_cmd(line)) {
            break;  
        }
    }
    std::cout << "Back to main menu.\n";
}

void TODOmanager::show_help() const {
    std::cout << "Command£º\n"
        << "  complete - Mark current TODO as completed\n"
        << "  imp <Value>  - Set importance (0-5)\n"
        << "  ddl <yy-mm-dd>      - Set Deadline (Example: 2025-03-15)\n"
        << "  dep <Task Name>     - Set Dependency for Current TODO\n"
        << "  show             - Check Status of Current TODO\n"
        << "  help             - Display Help Information\n"
        << "  back             - Return to the Main Menu\n"
    << "\n";
}