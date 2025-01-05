#include <iostream>
#include "utils/utils.h"
#include "dec01/dec1.hpp"
#include "dec03/decx.hpp"
#include "dec04/decx.hpp"
#include "dec05/decx.hpp"
#include "dec07/decx.hpp"
#include "dec08/decx.hpp"


int get_day(const std::vector<std::string> args) {
    // std::vector<string>
    for (int i = 0; i < args.size(); i++) {
        if (args[i].find("-d") != std::string::npos) {
            return stoi(args[i].substr(2));
        }
    }
    return -1;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    std::cout << "Hello, from AoC-2024!\n";

    switch (get_day(args)) {
        case 1:
            solve01();
            std::cout << "After solve01 call\n";
            break;
        case 3:
            solve03();
            std::cout << "After solve03 call\n";
            break;
        case 4:
            solve04();
            std::cout << "After solve04 call\n";
            break;
        case 5:
            solve05();
            std::cout << "After solve05 call\n";
            break;
        case 7:
            solve07();
            std::cout << "After solve07 call\n";
            break;
        case 8:
            solve08();
            std::cout << "After solve08 call\n";
            break;
    }
}
