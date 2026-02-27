#include "TODOlist.h"
#include "Command.h"
#include <iomanip>
#include<fstream>
#include<sstream>

namespace
{
    void Intro(bool ini) //intro
    {
        if (ini) {
            std::cout << "Welcome to the TODOlist Manager" << std::endl;
            std::cout << "Please Enter Command as Follows to Proceed" << std::endl;
            TODOlist::Help();
            ini = false;
        }
    }
}

int main() {
    TODOlist myList;
    myList.items = myList.ImportExistedList();
    Command cmd(myList);
    std::string line;
    bool ini = true;
    Intro(ini);
    ini = false;
    std::cout << "> ";

    while (true) {
        if (!std::getline(std::cin, line)) break;
        if (!cmd.execute(line)) break;
    }
    return 0;
}