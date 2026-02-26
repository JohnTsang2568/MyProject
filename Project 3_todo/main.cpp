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
    while (true) {
        Intro(ini);
        ini = false;
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (!cmd.execute(line)) break;
    }
    return 0;
}