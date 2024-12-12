#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cmath>


int test_func3();

std::vector<std::string> split(const std::string& s, const std::string& delimiter = " ") {
    std::vector<std::string> tokens;
    std::string token = s;
    std::size_t pos = 0;
    while ((pos = token.find(delimiter)) != std::string::npos) {
        tokens.push_back(token.substr(0, pos));
        token = token.substr(pos + delimiter.length());
    }
    tokens.push_back(token);

    return tokens;
}

void print_solve1(long long answer, int day) {
    std::cout << "The first answer to day " << day << " is " << answer << "." << std::endl;
}

void print_solve2(long long answer, int day) {
    std::cout << "The second answer to day " << day << " is " << answer << "." << std::endl;
}

bool in_range(int value, int min, int max) {
    return value >= min && value <= max;
}

std::vector<int> satia(std::vector<std::string> list) {
    std::vector<int> res;
    for (int i = 0; i < list.size(); i++) {
        res.push_back(stoi(list[i]));
    }
    return res;
}

std::string get_nary(long long num, long long n = 2) {
    std::string res = "";
    long long biggest_exp = 0;
    while (std::pow(n, biggest_exp + 1) < num + 1) {
        biggest_exp++;
        if (biggest_exp > 64) {
            std::cout << "get_nary: biggest_exp is too big";
            break;
        }
    }
    // if (std::pow(n, biggest_exp) != num) {
    //     biggest_exp--;
    // }
    for (int digit = std::max((int)biggest_exp, 0); digit >= 0; digit--) {
        for (int power = 1; power <= n; power++) {
            // std::cout << num - std::pow(n, digit) * power << std::endl;
            // std::cout <<  digit << power << std::endl;
            if (num - std::pow(n, digit) * power < 0) {
                res += std::to_string(power - 1);
                num -= std::pow(n, digit) * (power - 1);
                break;
            }
        }
    }
    return res;
}

int get_nary_digit(long long num, long long n = 2, int index = 0) {
    auto res = get_nary(num, n);
    if (index >= res.size()) {return 0;}
    return res[res.size() - index - 1] - '0';
}

void test_get_nary() {
    for (int i = 0; i < 16; i++) {
        auto num = get_nary(i, 2);
        std::cout << i << " is " << num << std::endl;
    }

    for (int i = 0; i < 27; i++) {
        auto num = get_nary(i, 3);
        std::cout << i << " is ";
        for (int j = 0; j < num.size(); j++) {
           std::cout << get_nary_digit(i, 3, j);

        }
        std::cout << std::endl;
    }

}