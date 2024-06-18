#include <string>

#include "LexAnalysis.hpp"
#include "utils.hpp"
#include "exceptions.hpp"

LexAnalysis::LexAnalysis(std::string& code) {
    this->setCode(code);
}

void LexAnalysis::setCode(std::string& code) {
    this->code = code;
}

void LexAnalysis::setCode(const std::string&& code) {
    this->code = code;
}

bool LexAnalysis::Judge(const std::string str) {
    auto it1 = std::distance(std::find(keywords_pool.begin(), keywords_pool.end(), str), keywords_pool.end());
    if (it1 != 0) {
        setKeyword(str);
        mypair p = {"keyword", str};
        token.insert({token.size() + 1, p});
        return true;
    }
    auto it2 = std::distance(std::find(operators_pool.begin(), operators_pool.end(), str), operators_pool.end());
    if (it2 != 0) {
        setOperator(str);
        mypair p = {"operator", str};
        token.insert({token.size() + 1, p});
        return true;
    }

    if (is_constant(str) == 1) {
        setConstantnum(str);
        mypair p = {"constantnum", str};
        token.insert({token.size() + 1, p});
        return true;
    }
    if (is_constant(str) == 2) {
        setConstantchar(str);
        mypair p = {"constantchar", str};
        token.insert({token.size() + 1, p});
        return true;
    }
    if (is_constant(str) == 3) {
        setConstantstr(str);
        mypair p = {"constantstr", str};
        token.insert({token.size() + 1, p});
        return true;
    }

    if ((str[0] == '"' && str[str.size() - 1] != '"') || (str[0] == '\'' && str[str.size() - 1] != '\''))
        throw UnEnclosedQuotation(str);

    if (is_identifier(str)) {
        setIdentifiers(str);
        mypair p = {"identifiers", str};
        token.insert({token.size() + 1, p});
        return true;
    }
    else {
        throw NoIdentifierException(str);
    }
}

void LexAnalysis::setOperator(const std::string& str) {
    operators.insert({operators.size() + 1, str});
}

void LexAnalysis::setIdentifiers(const std::string& str) {
    identifiers.insert({identifiers.size() + 1, str});
}

void LexAnalysis::setKeyword(const std::string& str) {
    keywords.insert({keywords.size() + 1, str});
}
std::multimap<Position, std::string>& LexAnalysis::getIdentifiers() {
    return identifiers;
}

std::multimap<Position, std::string>& LexAnalysis::getConstantnum() {
    return constantnum;
}

std::multimap<Position, std::string>& LexAnalysis::getConstantchar() {
    return constantchar;
}

std::multimap<Position, std::string>& LexAnalysis::getConstantstr() {
    return constantstr;
}

std::multimap<Position, std::string>& LexAnalysis::getOperators() {
    return operators;
}

std::multimap<Position, std::string>& LexAnalysis::getKeywords() {
    return keywords;
}

std::multimap<Position, mypair>& LexAnalysis::getToken() {
    return token;
}

void LexAnalysis::setConstantnum(const std::string& str) {
    constantnum.insert({constantnum.size() + 1, str});
}

void LexAnalysis::setConstantchar(const std::string& str) {
    constantchar.insert({constantchar.size() + 1, str});
}

void LexAnalysis::setConstantstr(const std::string& str) {
    constantstr.insert({constantstr.size() + 1, str});
}