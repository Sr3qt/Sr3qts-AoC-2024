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
#include "dec11/decx.hpp"
#include "dec12/decx.hpp"
// #include "dec13/decx.hpp"
#include "dec14/decx.hpp"
// #include "dec15/decx.hpp"
// #include "dec16/decx.hpp"
// #include "dec17/decx.hpp"
// #include "dec18/decx.hpp"
// #include "dec19/decx.hpp"
// #include "dec20/decx.hpp"
// #include "dec21/decx.hpp"
// #include "dec22/decx.hpp"
// #include "dec23/decx.hpp"
// #include "dec24/decx.hpp"
// #include "dec25/decx.hpp"


int get_day(const std::vector<std::string> args) {
    for (int i = 0; i < args.size(); i++) {
        if (args[i].find("-d") != std::string::npos) {
            if (args[i].substr(2) != "") {
                return stoi(args[i].substr(2));
            } else {
                return stoi(args[i + 1]);
            }
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
            std::cout << "Day not solved in c++.\n";
            break;
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
            std::cout << "Day not solved in c++.\n";
            break;
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
        case 11:
            solve11();
            break;
        case 12:
            solve12();
            break;
        // case 13:
        //     solve13();
        //     break;
        case 14:
            solve14();
            break;
        // case 15:
        //     solve15();
        //     break;
        // case 16:
        //     solve16();
        //     break;
        // case 17:
        //     solve17();
        //     break;
        // case 18:
        //     solve18();
        //     break;
        // case 19:
        //     solve19();
        //     break;
        // case 20:
        //     solve20();
        //     break;
        // case 21:
        //     solve21();
        //     break;
        // case 22:
        //     solve22();
        //     break;
        // case 23:
        //     solve23();
        //     break;
        // case 24:
        //     solve24();
        //     break;
        // case 25:
        //     solve25();
        //     break;
        default:
            std::cout << "Sorry, that is an unsolved day." << std::endl;
            break;
    }
}
