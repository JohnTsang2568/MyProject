#include "TODOlist.h"
#include "Command.h"
#include <iomanip>

int main() {
    TODOlist myList;
    Command cmd(myList);
    std::string line;
    bool ini = true;
    while (true) {
        if (ini) {
            std::cout << "Welcome to the TODOlist Manager" << std::endl;
            std::cout << "Please Enter Command as Follows to Proceed" << std::endl;
            for (size_t i = 0; i < 50; i++)std::cout << "-";
            std::cout << std::endl;
            std::cout << "\"add <TODOname>\" to add a new TODO to your TODOlist" << std::endl;
            std::cout << "\"delete <TODOname>\" to  delete a TODO from your TODOlist:" << std::endl;
            std::cout << "\"list\" to show current TODOlist" << std::endl;
            std::cout << "\"edit\" to edit the status of TODO" << std::endl;
            std::cout << "\"sortimp\" to sort current TODOlist by importance" << std::endl;
            std::cout << "\"sortdate\" to sort current TODOlist by date" << std::endl;
            std::cout << "\"exit\" to exit this application" << std::endl;
            for (size_t i = 0; i < 50; i++)std::cout << "-";
            std::cout << std::endl;
            ini = false;
        }
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (!cmd.execute(line)) break;
    }
    return 0;
}