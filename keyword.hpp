#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <map>

#include "config.hpp"
#include "utils.hpp"


class Type {
private:
    unsigned char __tval;                               // type value
    void* __tpoint;
public:
    Type() = default;
    Type(unsigned char tval, void* tpoint);
    Type(const Type& type);                                   // copy constructor
    ~Type() = default;

    unsigned char getTval();
    static void display_type_table();
};

class KeyWord {
private:
    std::string __name;
    Type __type;                                   // int, float, char, double, ALNFL, RINFL,etc(--> table)
    Cat __category;                                // variable, function, constant, etc
    std::string __address;                         // address allocate table
public:
    KeyWord(){}
    KeyWord(std::string& name, const Type& type, Cat category, std::string& address);
    ~KeyWord() = default;

    std::string& getName();
    Type& getType();
    Cat getCategory();
    std::string& getAddress();

    static void display_keyword_table();
};

class function {
private:
    Position __Hierarchy_number;                    // Hierarchy number of function  层次号
    Position __off;                                 // offset of function区距
    size_t __fn;                                    // function number of function形参个数
    std::vector<KeyWord> __parameters;              // parameters of function参数列表
    std::string __returntype;                       // return type of function返回值
    //entrance__address;                            //--> entrance address of function
public:
    function() = default;
    function(Position Hierarchy_number, Position off, size_t fn, std::string& returntype, const std::vector<KeyWord>& parameters);
    ~function() = default;

    Position getHierarchyNumber();
    Position getOff();
    size_t getFn();
    std::string& getReturntype();
    static void display_function_table();
};

class constant {
private:
    std::string __value;                             // --> constant related table
public:
    constant(){}
    constant(std::string value);
    ~constant() = default;

    std::string& getValue();
    static void display_constant_table();
};

class LENL {
private:
    byte __length;                                  // length of array
public:
    LENL() = default;
    LENL(byte length);
    ~LENL() = default;

    byte getLength();
    static void display_lenl_table();
};

class ALNFL {
private:
    Position __low;                                // low bound of array
    Position __up;                                 // high bound of array
    byte __clen;                                   // length of array
    std::vector<KeyWord> __keyword;                // array of keyword
public:
    ALNFL() = default;
    ALNFL(Position low, Position up, byte clen, const std::vector<KeyWord>& keyword);
    ~ALNFL() = default;

    Position getLow();
    Position getUp();
    byte getClen();
    static void display_alnfl_table();
};

class VAIR {
    private:
    int __OSP = 0;
    Position __return_address = 0;
    Position __Disp = 0;
    Position __num = 0;
    std::vector<std::string> __parameters;
    Position __disp = 0;
    public:
    VAIR() = default;
    VAIR(int OSP, Position return_address, Position Disp, Position num, const std::vector<std::string>& parameters, Position disp){
        this->__OSP = OSP;
        this->__return_address = return_address;
        this->__Disp = Disp;
        this->__num = num;
        this->__parameters = parameters;
        this->__disp = disp;
    }
    ~VAIR() = default;

    int getOSP();
    Position getReturnAddress();
    Position getDisp();
    Position getNum();
    std::vector<std::string>& getParameters();
    Position getdisp();
};

using  ALNFLtuple = std::tuple<Position, Position, Type, byte>;

static std::vector<KeyWord> keyword_table; 
static std::vector<function> function_table;
static std::vector<constant> constant_table;
static std::vector<LENL> lenl_table;
static std::vector<ALNFL> alnfl_table;
static std::vector<Type> type_table;