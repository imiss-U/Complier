#pragma once

#include <cstdlib>
#include <string>
#include <cctype>
#include <regex>
#include <iostream>
#include <algorithm>
#include <map>

#include "config.hpp"

inline std::string input() {
    std::string str;
    std::cout << "Please input the code: " << std::endl;
    std::string result = "";
    while (std::getline(std::cin, str)) {
    result = result + std::move(str);
    }
    return std::move(result);
}

inline bool is_separator(const std::string& str, size_t i) {           // judge whether is separator
    std::string temp(1, str[i]);
    if (std::find(operators_pool.begin(), operators_pool.end(), temp) != operators_pool.end())
        return true;
    return false;
}

inline bool is_identifier(const std::string& str) {                    // judge whether is identifier
    if (isalpha(str[0]) == 0 && str[0] != '_')
        return false;
    for (auto x : str) {
        if (isalnum(x) == 0 && x != '_')
            return false;
    }
    return true;
}

inline int is_constant(const std::string& str) {
    std::regex pattern("^(\\-|\\+)?\\d+(\\.\\d+)?$");               // common number including int, float/double
    if (std::regex_match(str, pattern)) {
        return 1;
    }
    std::regex pattern2("^(\\-|\\+)?\\d+e(\\-|\\+)?\\d+$");         // scientific number like 3e6,-9e-9
    if (std::regex_match(str, pattern2)) {
        return 1;
    }
    std::regex pattern3("^\".*\"$");                                //  string type constant
    if (std::regex_match(str, pattern3)) {
        return 3;
    }
    std::regex pattern4("^'.*'$");                                  // char type constant
    if (std::regex_match(str, pattern4)) {
        return 2;
    }
    return 0;
}
