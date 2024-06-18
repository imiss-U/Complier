#include <vector>
#include <map>
#include <vector>
#include <iostream>

#include "config.hpp"
#include "ReadWord.hpp"
#include "LexAnalysis.hpp"
#include "utils.hpp"
#include "keyword.hpp"
#include "exceptions.hpp"
#include "quat.hpp"
#include "parse.hpp"
#include "symbol.hpp"

LexAnalysis* scanner = new LexAnalysis();

int main() {
    std::string code = input();
    ReadWord reader;
    while (reader.getPosition() < code.size()) {
        std::string tmp = std::move(reader.readWord(code));
        scanner->Judge(tmp);
    }
    // int a = scanner->getToken().size();
    std::cout << "Token table: " << std::endl;
    for (auto& x : scanner->getToken()) {
        std::cout << x.first << " " << x.second.first << " " << x.second.second << std::endl;
    }
    std::cout << "Keyword table: " << std::endl;
    for (auto& x : scanner->getKeywords()) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    std::cout << "Operators table: " << std::endl;
    for (auto& x : scanner->getOperators()) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    std::cout << "Identifiers table: " << std::endl;
    for (auto& x : scanner->getIdentifiers()) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    std::cout << "Constant number table: " << std::endl;
    for (auto& x : scanner->getConstantnum()) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    std::cout << "Constant char table: " << std::endl;
    for (auto& x : scanner->getConstantchar()) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    std::cout << "Constant string table: " << std::endl;
    for (auto& x : scanner->getConstantstr()) {
        std::cout << x.first << " " << x.second << std::endl;
    }
    // int a = scanner->getToken().size();
    // usingq(a);
    // symbols(0, a - 1);
    // for (auto x :keywordarray) {
    //     std::cout << x.getName() << " " << x.getType().getTval() << " " << x.getCategory() << " " << x.getAddress() << std::endl;
    // }
    return 0;
}
