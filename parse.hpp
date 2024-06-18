#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

class parse {
private:
	std::string str;
	int flag = 1;
	std::vector<std::string> fname = {"iostream", "algorithm", "string", "vector"};
	std::vector<std::string> datatypename = {"int", "float", "long", "long long", "double", "void", "char", "short", "bool"};
	std::vector<char>arioperator = {'+', '-', '*', '/'};
public:
	parse() {};
	parse(std::string st) :str(st), flag(1) {};
	bool Start();
	void program(std::string::iterator& it);

	void headlist(std::string::iterator& it);
	void filename(std::string::iterator& it);
	void fileend(std::string::iterator& it);
	void definelist(std::string::iterator& it);
	void define(std::string::iterator& it);
	void nametype(std::string::iterator& it);
	void nametypeend(std::string::iterator& it);
	
	void parlist(std::string::iterator& it);
	void argu(std::string::iterator& it);
	void arguend(std::string::iterator& it);

	void codeblocks(std::string::iterator& it);
	void codelist(std::string::iterator& it);
	void code(std::string::iterator& it);
	void codeend(std::string::iterator& it);
	void takefunend(std::string::iterator& it);
	void takefun(std::string::iterator& it);

	void inputstate(std::string::iterator& it);
	void outputstate(std::string::iterator& it);

	void constate(std::string::iterator& it);
	void elseif(std::string::iterator& it);
	void ifend(std::string::iterator& it);
	void conend(std::string::iterator& it);
	
	void cirstate(std::string::iterator& it);
	void cirend(std::string::iterator& it);
	void arifor(std::string::iterator& it);
	void forcodeend(std::string::iterator& it);
	
	void ariexpression(std::string::iterator& it);
	void T(std::string::iterator& it);
	void F(std::string::iterator& it);
	void E(std::string::iterator& it);
	
	std::string getnum(std::string::iterator& it);
	std::string getid(std::string::iterator& it);
	int isinclu(std::string::iterator& it);
	int isuns(std::string::iterator& it);
	int isdatatype(std::string::iterator& it);
	int ismain(std::string::iterator& it);
	void movblank(std::string::iterator& it);
	void movid(std::string::iterator& it);
};