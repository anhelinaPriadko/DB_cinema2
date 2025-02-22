#include <iostream>
#include <windows.h>
#include "CommandController.h"
#include "HallController.h"
#include "HallTypeController.h"

int main()
{
    CommandController controller;
    std::string input;

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;
        controller.get_command(input);
    }

    return 0;
}
