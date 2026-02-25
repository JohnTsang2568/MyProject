#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "TODOlist.h"   
#include "TODO.h"

class Command {
public:
    explicit Command(TODOlist& list);  
    bool execute(const std::string& input);  
private:
    TODOlist& todoList;  
   
};

#endif