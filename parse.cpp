#include "exceptions.hpp"
#include"parse.hpp"

bool parse::Start() {
	std::string::iterator it = str.begin();
	while (it != str.end() && *it == ' ') {
		it++;
	}
	program(it);
	if (flag && it == str.end()) {
        return true;
	}
	else {
        throw WrongParseException("");
	}
}
void parse::program(std::string::iterator& it) {
	headlist(it);
	if (flag == 0)
		return;
	definelist(it);
	if (flag == 0)
		return;
}

void parse::headlist(std::string::iterator& it) {
	if (it != str.end() && *it == '#') {
		it++;
		while (it != str.end() && *it == ' ') {
			it++;
		}
		if (it != str.end() && isinclu(it)) {
			if (*it == '<') {
				it++;
				while (it != str.end() && *it == ' ') {
					it++;
				}
				filename(it);
				if (flag == 0)
					return;
				if (it != str.end() && *it == '>') {
					it++;
					while (it != str.end() && *it == ' ') {
						it++;
					}
					fileend(it);
					if (flag == 0)
						return;
				}
				else {
					flag = 0;
					return;
				}
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
}

void parse::filename(std::string::iterator& it) {
	while (it != str.end() && *it == ' ') {
		it++;
	}
	if (it != str.end() && (isalpha(*it) || *it == '_')) {
		std::string tem;
		while (it != str.end() && (*it == '_' || isalnum(*it))) {
			tem += *it;
			it++;
		}
		while (it != str.end() && *it == ' ') {
			it++;
		}
		if (tem.size() == 0 || std::find(fname.begin(), fname.end(), tem) == fname.end()) {
			flag = 0;
			return;
		}
	}
}
void parse::fileend(std::string::iterator& it) {
	if (it != str.end() && *it == 'u') {
		if (isuns(it)) {
			return;
		}
		else {
			flag = 0;
			return;
		}
	}
	else if (it != str.end()) {
		headlist(it);
		if (flag == 0)return;
	}
}

void parse::definelist(std::string::iterator& it) {
	define(it);
	if (flag == 0)
		return;
	if (ismain(it)) {
		parlist(it);
		if (flag == 0)return;
		if (*it == ')') {
			it++;
			while (it != str.end() && *it == ' ') {
				it++;
			}
			codeblocks(it);
			if (flag == 0)
				return;
			define(it);
			if (flag == 0)
				return;
		}
		else {
			flag = 0;
			return;
		}
	}
	else {
		flag = 0;
		return;
	}
}

void parse::define(std::string::iterator& it) {
	std::string::iterator t1 = it;
	if (ismain(it)) {
		it = t1;
		return;
	}
	else if (isdatatype(it)) {
		if (it != str.end() && *it == '_' || isalpha(*it)) {
			while (it != str.end() && (*it == '_' || isalnum(*it))) {
				it++;
			}
			while (it != str.end() && *it == ' ') {
				it++;
			}
			nametype(it);
			if (flag == 0)
				return;
			nametypeend(it);
			if (!flag)
				return;
			define(it);
			if (flag == 0)
				return;
		}
		else {
			flag = 0;
			return;
		}
	}
}

void parse::nametype(std::string::iterator& it) {
	if (it != str.end() && *it == '=') {
		it++;
		movblank(it);
		ariexpression(it);
		if (flag == 0)
			return;
	}
	else if (it != str.end() && *it == '(') {
		it++;
		while (it != str.end() && *it == ' ') {
			it++;
		}
		parlist(it);
		if (flag == 0)
			return;
		if (it != str.end() && *it == ')') {
			it++;
			while (it != str.end() && *it == ' ') {
				it++;
			}
			if (it != str.end() && *it == '{') {
				codeblocks(it);
				if (flag == 0)
					return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
	else {
		flag = 0;
		return;
	}
}

void parse::nametypeend(std::string::iterator& it) {
	if (it != str.end() && *it == ',') {
		it++;
		movblank(it);
		std::string::iterator t1 = it;
		std::string tem = getid(it);
		if (tem.size()) {
			if (it != str.end() && *it == '=') {
				it++;
				movblank(it);
				ariexpression(it);
				if (flag == 0)
					return;
			}
			else if (it != str.end() && *it == '(') {
				it++;
				movblank(it);
				parlist(it);
				if (flag == 0)
					return;
				if (it != str.end() && *it == ')') {
					it++;
					while (it != str.end() && *it == ' ') {
						it++;
					}
				}
				else {
					flag = 0;
					return;
				}
			}
			else {
			}
		}
		else {
			flag = 0;
			return;
		}
		nametypeend(it);
		if (!flag)
		return;
	}
	else if (it != str.end() && *it == ';') {
		it++;
		movblank(it);
	}
	else
		return;
}

void parse::parlist(std::string::iterator& it) {
	if (*it == ')') {
		return;
	}
	else {
		argu(it);
		if (flag == 0)
			return;
		arguend(it);
		if (flag == 0)
			return;
	}
}

void parse::argu(std::string::iterator& it) {
	if (isdatatype(it)) {
		movid(it);
	}
	else {
		flag = 0;
		return;
	}
}

void parse::arguend(std::string::iterator& it) {
	if (it != str.end() && *it == ')') {
		return;
	}
	else {
		if (it != str.end() && *it == ',') {
			it++;
			movblank(it);
			argu(it);
			if (flag == 0)
				return;
			arguend(it);
			if (flag == 0)
				return;
		}
		else {
			flag = 0;
			return;
		}
	}
}

void parse::codeblocks(std::string::iterator& it) {
	if (it != str.end() && *it == '{') {
		it++;
		movblank(it);
		codelist(it);
		if (flag == 0)
			return;
		if (it != str.end() && *it == '}') {
			it++;
			movblank(it);
		}
		else {
			flag = 0;
			return;
		}
	}
	else {
		flag = 0;
		return;
	}
}

void parse::codelist(std::string::iterator& it) {
	if (it != str.end() && *it == '}'){
		return;
	}
	else if (it != str.end() && *it == ';') {
		it++;
		movblank(it);
		codelist(it);
		if (flag == 0)
			return;
		return;
	}
	std::string tem;
	std::string::iterator t1 = it;
	tem = getid(it);
	it = t1;
	if (tem == "if"){
		constate(it);
		if (flag == 0)
			return;
		codelist(it);
		if (flag == 0)
			return;
	}
	else if (tem == "while" || tem == "for" || tem == "do"){
		cirstate(it);
		if (flag == 0)
			return;
		codelist(it);
		if (flag == 0)
			return;
	}
	else {
		code(it);
		if (flag == 0)
			return;
		codeend(it);
		if (flag == 0)
			return;
		codelist(it);
		if (flag == 0)
			return;
	}
}

void parse::code(std::string::iterator& it) {
	if (isdatatype(it)) {
		std::string::iterator t1 = it;
		movid(it);
		if (t1 == it) {
			flag = 0; return;
		}
		if (it != str.end() && *it == '=') {
			it++;
			while (it != str.end() && *it == ' ') {
				it++;
			}
			ariexpression(it);
			if (flag == 0)
				return;
		}
		else if (it != str.end() && *it == '(') {
			it++;
			while (it != str.end() && *it == ' ') {
				it++;
			}
			parlist(it);
			if (flag == 0)
				return;
			if (it != str.end() && *it == ')') {
				it++;
				while (it != str.end() && *it == ' ') {
					it++;
				}
				return;
			}
			else {
				flag = 0;
				return;
			}
		}
		return;
	}
	std::string::iterator t2 = it;
	std::string tem = getid(it);
	if (it != str.end() && std::find(arioperator.begin(), arioperator.end(), *it) != arioperator.end()) {
		it = t2;
		ariexpression(it);
		if (flag == 0)
			return;
	}
	else if (it != str.end() && *it == '=') {
		it++;
		movblank(it);
		ariexpression(it);
		if (flag == 0)
			return;
	}
	else if (it != str.end() && *it == '(') {
		takefun(it);
		if (!flag)
			return;
	}
	else {
		if (tem == "cin") {
			inputstate(it);
			if (flag == 0)
				return;
		}
		else if (tem == "cout") {
			outputstate(it);
			if (flag == 0)
				return;
		}
		else if (tem == "return") {
			if (it != str.end() && *it == ';') {
				return;
			}
			else {
				std::string::iterator t2 = it;
				std::string tem2 = getid(it);
				if (tem2.size() != 0) {
					if (it != str.end() && *it == '(') {
						takefun(it);
					}
					else {
						it = t2;
						ariexpression(it);
						if (flag == 0)
							return;
					}
				}
				else {
					ariexpression(it);
					if (flag == 0)
						return;
				}
			}
		}
		else if (tem.size() == 0) {
			tem = getnum(it);
			if (tem.size() == 0)
				flag = 0;
				return;
		}
		else {
			return;
		}
	}
}

void parse::codeend(std::string::iterator& it) {
	if (it != str.end() && *it == ';') {
		it++;
		movblank(it);
		return;
	}
	else if (it != str.end() && *it == ',') {
		it++;
		movblank(it);
		code(it);
		if (flag == 0)
			return;
		codeend(it);
		if (flag == 0)
			return;
	}
	else {
		flag = 0;
		return;
	}
}

void parse::takefunend(std::string::iterator& it) {
	if (it != str.end() && *it == ',') {
		it++;
		movblank(it);
		std::string::iterator t1 = it;
		std::string tem;
		tem = getid(it);
		if (!tem.size()) {
			ariexpression(it);
			if (!flag)
				return;
		}
		else {
			if (it != str.end() && *it == '(') {
				takefun(it);
				if (!flag)
					return;
			}
			else {
				it = t1;
				ariexpression(it);
				if (!flag)
					return;
			}
		}
		takefunend(it);
		if (!flag)
			return;
	}
}

void parse::takefun(std::string::iterator& it) {
	if (it != str.end() && *it == '(') {
		it++;
		movblank(it);
		if (it != str.end() && *it == ')') {
			it++;
			movblank(it);
		}
		else {
			std::string::iterator t1 = it;
			std::string tem1 = getid(it);
			if (tem1.size() == 0) {
				ariexpression(it);
				if (!flag)
					return;
			}
			else {
				if (it != str.end() && *it == '(') {
					takefun(it);
					if (!flag)
						return;
				}
				else {
					it = t1;
					ariexpression(it);
					if (!flag)
						return;
				}
			}
			takefunend(it);
			if (flag == 0)
				return;
			if (it != str.end() && *it == ')') {
				it++;
				movblank(it);
			}
			else {
				flag = 0;
					return;
			}
		}
	}
	else {
		flag = 0;
		return;
	}
}

void parse::inputstate(std::string::iterator& it) {
	if (it != str.end() && *it == ',') {
		code(it);
		if (flag == 0)
			return;
		codeend(it);
		if (flag == 0)
			return;
	}
	else if (it != str.end() && *it == '>') {
		it++;
		movblank(it);
		if (it != str.end() && *it == '>') {
			it++;
			movblank(it);
			std::string tem = getid(it);
			if (tem.size()) {
				inputstate(it);
				if (flag == 0)
					return;
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
}

void parse::outputstate(std::string::iterator& it) {
	if (it != str.end() && *it == ',') {
		code(it);
		if (flag == 0)
			return;
		codeend(it);
		if (flag == 0)
			return;
	}
	else if (it != str.end() && *it == '<') {
		it++;
		movblank(it);
		if (it != str.end() && *it == '<') {
			it++;
			movblank(it);
			std::string::iterator t1 = it;
			std::string tem = getid(it);
			if (tem.size()) {

				if (it != str.end() && *it == '(') {
					takefun(it);
					outputstate(it);
					if (flag == 0)
						return;
				}
				else {
					it = t1;
					ariexpression(it);
					if (!flag)
						return;
					outputstate(it);
					if (flag == 0)
						return;
				}
			}
			else {
				tem = getnum(it);
				if (tem.size()) {
					it = t1;
					ariexpression(it);
					if (!flag)
						return;
					outputstate(it);
					if (flag == 0)
						return;
				}
				else {
					if (it != str.end() && *it == '\'') {
						it++;
						movblank(it);
						int tem1 = 1;
						while (it != str.end() && *it != '\'') {
							it++;
							if (*it == '\'') {
								tem1 = 0;
							}
						}
						movblank(it);
						if (tem1) {
							flag = 0;
							return;
						}
						else {
							it++;
							movblank(it);
							outputstate(it);
							if (flag == 0)
							return;
						}
					}
					else if (it != str.end() && *it == '\"') {
						it++;
						movblank(it);
						int tem1 = 1;
						while (it != str.end() && *it != '\"') {
							it++;
							if (it != str.end() && *it == '\"') {
								tem1 = 0;
							}
						}
						movblank(it);
						if (tem1) {
							flag = 0;
							return;
						}
						else {
							it++;
							movblank(it);
							outputstate(it);
							if (flag == 0)
								return;
						}
					}
					else {
						ariexpression(it);
						if (!flag)
							return;
					}
				}
			}
		}
		else {
			flag = 0;
			return;
		}
	}
}
void parse::constate(std::string::iterator& it) {
	std::string tem = getid(it);
	if (tem == "if") {
		if (it != str.end() && *it == '(') {
			it++;
			movblank(it);
			ariexpression(it);
			if (flag == 0)
				return;
			if (it != str.end() && *it == ')') {
				it++;
				movblank(it);
				ifend(it);
				if (flag == 0)
					return;
				elseif(it);
				if (flag == 0)
					return;
				conend(it);
				if (flag == 0)
					return;
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
	else {
		flag = 0;
		return;
	}
}

void parse::ifend(std::string::iterator& it) {
	if (it != str.end() && *it == '{') {
		codeblocks(it);
		if (flag == 0)
			throw UnEnclosedQuotation("if");
	}
	else {
		if (it != str.end() && *it == ';') {
			it++;
			movblank(it);
			return;
		}
		std::string tem;
		std::string::iterator t1 = it;
		tem = getid(it);
		it = t1;
		if (tem == "if")
		{
			constate(it);
			if (flag == 0)
				return;
		}
		else if (tem == "while" || tem == "for" || tem == "do")
		{
			cirstate(it);
			if (flag == 0)
				return;
		}
		else {
			code(it);
			if (flag == 0)
				return;
			codeend(it);
			if (flag == 0)
				return;
		}
	}
}

void parse::elseif(std::string::iterator& it) {
	std::string tem;
	std::string::iterator t1 = it;
	tem = getid(it);
	if (it != str.end() && *it != ' ') {
		it = t1;
		return;
	}
	movblank(it);
	tem += getid(it);
	if (tem == "elseif") {
		if (it != str.end() && *it == '(') {
			it++;
			movblank(it);
			ariexpression(it);
			if (flag == 0)
				return;
			if (it != str.end() && *it == ')') {
				it++;
				movblank(it);
				ifend(it);
				if (flag == 0)
					return;
				elseif(it);
				if (flag == 0)
					return;
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
	else {
		it = t1;
	}
}

void parse::conend(std::string::iterator& it) {
	std::string::iterator t1 = it;
	std::string tem = getid(it);
	if (tem == "else") {
		ifend(it);
		if (flag == 0)
			return;
	}
	else {
		it = t1;
	}
}

void parse::ariexpression(std::string::iterator& it) {
	E(it);
	if (flag == 0)
		return;
}

void parse::E(std::string::iterator& it) {
	T(it);
	if (flag == 0) {
		return;
	}
	while (it != str.end() && *it == '+' || *it == '-') {
		it++;
		movblank(it);
		T(it);
		if (flag == 0) {
			return;
		}
	}
}

void parse::T(std::string::iterator& it) {
	F(it);
	if (!flag)return;
	while (it != str.end() && *it == '*' || *it == '/') {
		it++;
		movblank(it);
		F(it);
		if (!flag)
			return;
	}
}

void parse::F(std::string::iterator& it) {
	std::string tem = getid(it);
	if (tem.size() == 0) {
		tem = getnum(it);
	}
	else {
		if (it != str.end() && *it == '(') {
			takefun(it);
			if (!flag)
				return;
		}
	}
	if (tem.size() != 0) {
		return;
	}
	else {
		if (it != str.end() && *it == '(') {
			it++;
			movblank(it);
			E(it);
			if (!flag)
				return;
			if (it != str.end() && *it == ')') {
				it++;
				movblank(it);
				return;
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
}

void parse::cirstate(std::string::iterator& it) {
	std::string tem = getid(it);
	if (tem == "while") {
		if (it != str.end() && *it == '(') {
			it++;
			movblank(it);
			ariexpression(it);
			if (flag == 0)
				return;
			if (it != str.end() && *it == ')') {
				it++;
				movblank(it);
				cirend(it);
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
	else if (tem == "for") {
		if (it != str.end() && *it == '(') {
			it++;
			movblank(it);
			arifor(it);
			if (flag == 0)
				return;
			arifor(it);
			if (flag == 0)
				return;
			if (it != str.end() && *it != ')') {
				code(it);
				if (flag == 0)
					return;
				forcodeend(it);
				if (flag == 0)
					return;
			}
			if (it != str.end() && *it == ')') {
				it++;
				movblank(it);
				cirend(it);
				if (flag == 0)
					return;
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
	else if (tem == "do") {
		cirend(it);
		if (flag == 0)
			return;
		std::string tem1 = getid(it);
		if (tem1 == "while") {
			if (it != str.end() && *it == '(') {
				it++;
				movblank(it);
				ariexpression(it);
				if (flag == 0)
					return;
				if (it != str.end() && *it == ')') {
					it++;
					movblank(it);
					if (it != str.end() && *it == ';') {
						it++;
						movblank(it);
					}
					else {
						flag = 0;
						return;
					}
				}
				else {
					flag = 0;
					return;
				}
			}
			else {
				flag = 0;
				return;
			}
		}
		else {
			flag = 0;
			return;
		}
	}
	else {
		flag = 0;
		return;
	}
}

void parse::cirend(std::string::iterator& it) {
	if (it != str.end() && *it == '{') {
		codeblocks(it);
		if (flag == 0)
			return;
	}
	else {
		if (it != str.end() && *it == ';') {
			it++;
			movblank(it);
			return;
		}
		std::string tem;
		std::string::iterator t1 = it;
		tem = getid(it);
		it = t1;
		if (tem == "if"){
			constate(it);
			if (flag == 0)
				return;
		}
		else if (tem == "while" || tem == "for" || tem == "do")
		{
			cirstate(it);
			if (flag == 0)
				return;
		}
		else {
			code(it);
			if (flag == 0)
				return;
			codeend(it);
			if (flag == 0)
				return;
		}
	}
}

void parse::arifor(std::string::iterator& it) {
	if (it != str.end() && *it == ';') {
		it++;
		movblank(it);
	}
	else {
		code(it);
		if (flag == 0)
			return;
		codeend(it);
		if (flag == 0)
			return;
	}
}

void parse::forcodeend(std::string::iterator& it) {
	if (it != str.end() && *it == ',') {
		code(it);
		if (flag == 0)
			return;
		forcodeend(it);
		if (flag == 0)
			return;
	}
}

std::string parse::getid(std::string::iterator& it) {
	std::string tem;
	if (it != str.end() && (isalpha(*it) || *it == '_')) {
		while (it != str.end() && (*it == '_' || isalnum(*it))) {
			tem += *it;
			it++;
		}
		while (it != str.end() && *it == ' ') {
			it++;
		}
	}
	return tem;
}

std::string parse::getnum(std::string::iterator& it) {
	std::string tem;
	int tem1 = 1;
	while (it != str.end() && isdigit(*it)) {
		tem += *it;
		it++;
		if (it != str.end() && tem1 && *it == '.') {
			tem += *it;
			it++;
			tem1 = 0;
			if (it == str.end() || !isdigit(*it)) {
				it--;
				break;
			}
		}
	}
	movblank(it);
	return tem;
}

int parse::isdatatype(std::string::iterator& it) {
	std::string::iterator t1 = it;
	std::string tem;
	while (t1 != str.end() && isalpha(*t1)) {
		tem += *t1;
		t1++;
	}
	while (t1 != str.end() && *t1 == ' ') {
		t1++;
	}
	if (std::find(datatypename.begin(), datatypename.end(), tem) != datatypename.end()) {

		if (tem == "long") {
			std::string tem1;
			std::string::iterator t2 = t1;
			while (t2 != str.end() && isalpha(*it)) {
				tem1 += *t2;
				t2++;
			}
			while (t2 != str.end() && *t2 == ' ') {
				t2++;
			}
			if (tem1 == "long") {
				tem += " long";
				t1 = t2;
			}
		}
		it = t1;
		return 1;
	}
	return 0;
}

int parse::isuns(std::string::iterator& it) {
	if (it != str.end()) {
		std::string::iterator t1 = it;
		std::string tem;
		for (int i = 0; i < 6 && t1 != str.end(); i++){//using
			tem += *t1;
			t1++;
		}
		while (t1 != str.end() && *t1 == ' ') {
			t1++;
		}
		for (int i = 0; i < 10 && t1 != str.end(); i++){//namespace
			tem += *t1;
			t1++;
		}
		while (t1 != str.end() && *t1 == ' ') {
			t1++;
		}
		for (int i = 0; i < 3 && t1 != str.end(); i++){//std
			tem += *t1;
			t1++;
		}
		while (t1 != str.end() && *t1 == ' ') {
			t1++;
		}
		if (t1 != str.end()) {
			tem += *t1;
			t1++;
			while (t1 != str.end() && *t1 == ' ') {
				t1++;
			}
		}
		if (tem.size() == 0 || tem != "using namespace std;") {
			return 0;
		}
		else {
			it = t1;
			return 1;
		}
	}
	return 0;
}

int parse::isinclu(std::string::iterator& it) {
	std::string::iterator i1 = it;
	std::string tem;
	for (int i = 0; i < 7 && i1 != str.end(); i++) {
		tem = tem + *i1;
		i1++;
	}
	while (i1 != str.end() && *i1 == ' ') {
		i1++;
	}
	if (tem == "include") {
		it = i1;
		return 1;
	}
	else {
		throw InvalidIncludeException(tem);
	}
}

int parse::ismain(std::string::iterator& it) {
	std::string tem;
	std::string::iterator t1 = it;
	for (int i = 0; i < 4 && t1 != str.end(); i++) {
		tem += *t1;
		t1++;
	}
	while (t1 != str.end() && *t1 == ' ') {
		t1++;
	}
	for (int i = 0; i < 5 && t1 != str.end(); i++) {
		tem += *t1;
		t1++;
	}
	while (t1 != str.end() && *t1 == ' ') {
		t1++;
	}
	if (tem == "int main(") {
		it = t1;
		return 1;
	}
	else {
        return 0;
	}
}

void parse::movblank(std::string::iterator& it) {
	while (it != str.end() && *it == ' ') {
		it++;
	}
}

void parse::movid(std::string::iterator& it) {
	if (it != str.end() && (isalpha(*it) || *it == '_')) {
		while (it != str.end() && (*it == '_' || isalnum(*it))) {
			it++;
		}
		while (it != str.end() && *it == ' ') {
			it++;
		}
	}
}
