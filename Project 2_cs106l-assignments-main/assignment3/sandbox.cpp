#include "class.h"
#include <iostream>

void sandbox() {
    character c1;  
    std::cout << "Name: " << c1.getName() << std::endl;

    character c2("Oblivionis", "Muzumi-Chan", "Suki");
    std::cout << "Name: " << c2.getName() << ", LP: " << c2.getLp() << std::endl;
}