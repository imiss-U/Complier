#pragma once

#include <map>
#include <string>
#include <map>
#include <utility>

#include "config.hpp"

class LexAnalysis {
public:
    LexAnalysis() {}                                        // Constructor
    LexAnalysis(std::string& code);                         // Constructor
    ~LexAnalysis() {};                                      // Destructor
    void setCode(std::string& code);                        // Set code
    void setCode(const std::string&& code);                 // Set code

    bool Judge(const std::string str);                      // judge which type the word belong to
    void setKeyword(const std::string& str);                // set to keyword
    void setOperator(const std::string& str);               // set to operators_pool
    void setIdentifiers(const std::string& str);            // set to identifier
    void setConstantnum(const std::string& str);            // set to constants number
    void setConstantchar(const std::string& str);           // set to constant char table
    void setConstantstr(const std::string& str);            // set to constant string table

    std::multimap<Position, std::string>& getIdentifiers();             // get identifiers table
    std::multimap<Position, std::string>& getConstantnum();             // get constant number table
    std::multimap<Position, std::string>& getConstantchar();            // get constant char table
    std::multimap<Position, std::string>& getConstantstr();             // get constant string table
    std::multimap<Position, std::string>& getOperators();               // get operators table
    std::multimap<Position, std::string>& getKeywords();                // get keywords table
    std::multimap<Position, mypair>& getToken();                        // get token
private:
    std::string code;                                                  // Code
    std::multimap<Position, mypair> token;                              // token
    std::multimap<Position, std::string> identifiers;                   // Identifiers
    std::multimap<Position, std::string> constantnum;                   // constants number
    std::multimap<Position, std::string> constantchar;                  // constant char
    std::multimap<Position, std::string> constantstr;                   // constant string
    std::multimap<Position, std::string> keywords;                      // keywords
    std::multimap<Position, std::string> operators;                     // operators
};
extern LexAnalysis* scanner;