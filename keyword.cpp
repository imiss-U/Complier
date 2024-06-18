#include <string>
#include <vector>
#include "config.hpp"

#include "keyword.hpp"

function::function(Position Hierarchy_number, Position off, size_t fn, std::string& returntype, const std::vector<KeyWord>& parameters) {
    __Hierarchy_number = Hierarchy_number;
    __off = off;
    __fn = fn;
    __returntype = returntype;
    __parameters = parameters;
}

    
std::string& function::getReturntype() {
    return __returntype;
}

Position function::getHierarchyNumber() {
    return __Hierarchy_number;
}

Position function::getOff() {
    return __off;
}

size_t function::getFn() {
    return __fn;
}

void function::display_function_table() {
    std::cout << "Function table: " << std::endl;
    for (auto x : function_table) {
        std::cout << "__Hierarchy_number: " << x.getHierarchyNumber() << std::endl;
        std::cout << "__off: " << x.getOff() << std::endl;
        std::cout << "__fn: " << x.getFn() << std::endl;
        std::cout << "__returntype: " << x.getReturntype() << std::endl;
    }
}

constant::constant(std::string value) : __value(value) {}

std::string& constant::getValue() {
    return __value;
}

void constant::display_constant_table() {
    std::cout << "Constant table: " << std::endl;
    for (auto x : constant_table) {
        std::cout << "__value: " << x.getValue() << std::endl;
    }
}

LENL::LENL(byte length) : __length(length) {}

byte LENL::getLength() {
    return __length;
}

void LENL::display_lenl_table() {
    std::cout << "LENL table: " << std::endl;
    for (auto x : lenl_table) {
        std::cout << "__length: " << x.getLength() << std::endl;
    }
}

ALNFL::ALNFL(Position low, Position up, byte clen, const std::vector<KeyWord>& keyword) {
    __low = low;
    __up = up;
    __clen = clen;
    __keyword = keyword;
}

Position ALNFL::getLow() {
    return __low;
}

Position ALNFL::getUp() {
    return __up;
}

byte ALNFL::getClen() {
    return __clen;
}

void ALNFL::display_alnfl_table() {
    std::cout << "ALNFL table: " << std::endl;
    for (auto x : alnfl_table) {
        std::cout << "__low: " << x.getLow() << std::endl;
        std::cout << "__up: " << x.getUp() << std::endl;
        std::cout << "__clen: " << x.getClen() << std::endl;
    }
}

Type::Type(unsigned char tval, void* tpoint) : __tval(tval), __tpoint(tpoint) {}

Type::Type(const Type& type) {
    this->__tval = type.__tval;
    this->__tpoint = type.__tpoint;
}

unsigned char Type::getTval() {
    return __tval;
}

void Type::display_type_table() {
    std::cout << "Type table: " << std::endl;
    for (auto x : type_table) {
        std::cout << "__tval: " << x.getTval() << std::endl;
    }
}

KeyWord::KeyWord(std::string& name, const Type& type, Cat category, std::string& address) : __name(name), __type(type), __category(category), __address(address) {}

std::string& KeyWord::getName() {
    return __name;
}

Type& KeyWord::getType() {
    return __type;
}

Cat KeyWord::getCategory() {
    return __category;
}

std::string& KeyWord::getAddress() {
    return __address;
}

void KeyWord::display_keyword_table() {
    std::cout << "KeyWord table: " << std::endl;
    for (auto x : keyword_table) {
        std::cout << "__name: " << x.getName() << std::endl;
    }
}

int VAIR::getOSP() {
    return __OSP;
}

Position VAIR::getReturnAddress() {
    return __return_address;
}

Position VAIR::getDisp() {
    return __Disp;
}

Position VAIR::getNum() {
    return __num;
}

std::vector<std::string>& VAIR::getParameters() {
    return __parameters;
}

Position VAIR::getdisp() {
    return __disp;
}