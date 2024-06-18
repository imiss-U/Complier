#pragma once

#include <string>
#include <cctype>

#include "config.hpp"
#include "utils.hpp"

class ReadWord {
private:
    char* data;
    WordLength wordlength;
    Position position = 0;
public:
    ReadWord() :data(nullptr), wordlength(0) {};
    size_t getPosition();
    size_t getLength();
    std::string readWord(const std::string& code);
    ~ReadWord() {};
};

size_t ReadWord::getPosition() {
    return position;
}

size_t ReadWord::getLength() {
    return wordlength;
}

std::string ReadWord::readWord(const std::string& code) {
    std::string tmp = "";
    wordlength = 0;
    while (code[position] == ' ')                                       // whitespace
        position++;
    if (is_separator(code, position)) {                                 // += -= *= /= ++ -- >= <= != && ||
        std::string current = std::string(1, code[position]) + std::string(1, code[position + 1]);
        if (current == "+=" || current == "-=" || current == "*=" || current == "/=" || current == "++" || current == "--" || current == ">=" || current == "<=" || current == "!=" || current == "&&" || current == "||") {
            tmp = current;
            wordlength = 2;
            position += 2;
            return std::move(tmp);
        }
        tmp.append(1, code[position]);
        wordlength = 1;
        position++;
        return std::move(tmp);
    }
    if (code[position] == '"') {                                        // ""
        Position next_position = code.find('"', position + 1);
        if (next_position != std::string::npos) {
            wordlength = next_position - position + 1;
            tmp = code.substr(position, wordlength);
            position += wordlength;
            return std::move(tmp);
        }
    }
    if (code[position] == '\'') {                                       // ''
        wordlength = 3;
        tmp = code.substr(position, 3);
        position += wordlength;
        return std::move(tmp);
    }
    for (ReadHead i = position; code[i] != ' ' && i != code.size(); ++i) {
        if (is_separator(code, i) && code[i] != '.') {
            break;
        }
        if (code[i] == '.') {
            if (isdigit(code[i + 1]) == 0 || isdigit(code[i - 1]) == 0) {
                break;
            }
        }
        tmp = tmp + code[i];
        wordlength++;
    }
    position += wordlength;
    return std::move(tmp);
}