#pragma once

#include <cstdlib>
#include <vector>
#include <utility>

typedef size_t ReadHead;
typedef size_t WordLength;
typedef size_t Position;
typedef size_t Cat;
typedef size_t byte;

using mypair = std::pair<std::string, std::string>;     // type, value

const std::vector<std::string> keywords_pool = {"int", "void", "break", "float", "while", "do", "struct", "const", "case", "for", "return", "if", "default", "else", "switch", "continue", "enum", "typedef", "union", "sizeof", "auto", "extern", "register", "static", "volatile", "char", "double", "long", "short", "unsigned", "signed", "include", "define", "main", "printf", "scanf", "NULL", "true", "false", "bool", "string", "vector", "map", "set", "cin", "cout", "endl", "std", "using", "namespace", "return", "new", "delete", "this", "friend", "class", "public", };
const std::vector<std::string> operators_pool = {"+", "-", "*", "/", "=", "==", "!=", ">", "<", ">=", "<=", "&&", "||", "!", "&", "|", "++", "--", "+=", "-=", "*=", "/=", "(", ")", "{", "}", "[", "]", ",", ";", ":", ".", "/*", "*/", "//"};

enum VarCategory {
    v = 1,          // variable变量
    vf = 2,         // 换名variable
    vn = 3,         // 赋值variable
    f = 4,          // function函数
    c = 5,          // constant常量
    t = 6,          // type类型
    d = 7           // domain域
};
