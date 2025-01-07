#include <iostream>
#include "utils/utils.h"
#include "dec01/dec1.hpp"
#include "dec03/decx.hpp"
#include "dec04/decx.hpp"
#include "dec05/decx.hpp"
#include "dec07/decx.hpp"
#include "dec08/decx.hpp"
#include "dec09/decx.hpp"
#include "dec10/decx.hpp"


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
            break;
        case 2:
            std::cout << "Day not solved in c++.";
        case 3:
            solve03();
            break;
        case 4:
            solve04();
            break;
        case 5:
            solve05();
            break;
        case 6:
            std::cout << "Day not solved in c++.";
        case 7:
            solve07();
            break;
        case 8:
            solve08();
            break;
        case 9:
            solve09();
            break;
        case 10:
            solve10();
            break;
    }
}
