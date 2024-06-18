#include <vector>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

#include "config.hpp"
#include "ReadWord.hpp"
#include "LexAnalysis.hpp"
#include "utils.hpp"
#include "keyword.hpp"
#include "exceptions.hpp"

int num = 0;
std::string temp2 = "";
struct qua {
    std::string symbal;  //符号
    std::string op_a;   //第一个操作数
    std::string op_b;   //第二个操作数
    std::string result;  //结果
};
struct qua quat[1000];
int quanum = 0;      //用于记录四元式的下标
std::string temp = "";    //设置空标量，方便实现跳转
//用于生成临时变量
std::string new_temp() {
    char* pq;
    char mm[18];
    pq = (char*) malloc(18);
    num++;
    snprintf(mm, sizeof(mm), "%d", num);
    strcpy(pq + 1, mm);
    pq[0] = 't';
    std::string s = pq;
    return s;
}
//用于记录四元式的顺序
void quats(std::string a, std::string b, std::string c, std::string d) {
    quat[quanum].symbal = a;
    quat[quanum].op_a = b;
    quat[quanum].op_b = c;
    quat[quanum].result = d;
    quanum++;
}
//进行相关算符比较
char bijiao(std::string a, std::string b) {
    int c, d;
    std::string s[8] = {"+", "-", "*", "/", "<", ">", "(", ")"};
    char str[8][8] =
    {
        {'=', '=', '<', '<', '>', '>', '<', '<'},
        {'=', '=', '<', '<', '>', '>', '<', '<'},
        {'>', '>', '=', '=', '>', '>', '<', '<'},
        {'>', '>', '=', '=', '>', '>', '<', '<'},
        {'<', '<', '<', '<', '=', '=', '<', '<'},
        {'<', '<', '<', '<', '=', '=', '<', '<'},
        {'<', '<', '<', '<', '<', '<', '=', '='},
        {'<', '<', '<', '<', '<', '<', '=', '='},
    };
    int i;
    for (i = 0; i < 8; i++) {
        if (s[i] == a) {
            c = i;
        }
        if (s[i] == b) {
            d = i;
        }
    }
    if (i = 8) {
        std::cout << "error" << std::endl;             //此处抛出错误
    }
    return str[c][d];
}
//表达式四元式生成
void ariquat(int a, int b) {
    std::stack<std::string> d, c;
    for (a; a < b + 1; a++) {
        std::string x = scanner->getToken().find(a)->second.second;
        std::string y = scanner->getToken().find(a)->second.first;
        if (y == "identifiers") {
            int c = a + 1;
            std::string z = scanner->getToken().find(c)->second.second;
            if (z == "(") {
                std::string z1 = scanner->getToken().find(c + 1)->second.second;
                std::string z2 = scanner->getToken().find(c + 2)->second.second;
                if (z2 == ")") {
                    quats("PARAM", z1, "_", "_");
                }
                while (z != ")") {
                    c++;
                    z = scanner->getToken().find(c)->second.second;
                    z1 = scanner->getToken().find(c - 1)->second.second;
                    if (z == "," || z == ")") {
                        quats("PARAM", z1, "_", "_");
                    }
                }
                a = c;
                std::string new1 = new_temp();
                quats("CALL", x, "_", new1);
                x = new1;
            }
            d.push(x);
        }
        else if (y == "constantnum") {
            d.push(x);
        }
        else if (y == "operator") {
            if (c.size() == 0) {
                c.push(x);
            }
            else {
                std::string e = c.top();
                char f = bijiao(x, e);
                if (f == '>') {
                    c.push(x);
                }
                while (f == '<' || f == '=') {
                    c.pop();
                    std::string h = d.top();
                    d.pop();
                    std::string g = d.top();
                    d.pop();
                    std::string i = new_temp();
                    d.push(i);
                    quats(e, g, h, i);
                    if (c.empty()) {
                        c.push(x);
                        break;
                    }
                    e = c.top();
                    f = bijiao(x, e);
                    if (f == '>') {
                        c.push(x);
                    }
                }
            }
        }
    }
    if ((a == b + 1) && (!d.empty()) && (!c.empty())) {
        while (!d.empty() && !c.empty()) {
            std::string e = c.top();
            c.pop();
            std::string h = d.top();
            d.pop();
            std::string g = d.top();
            d.pop();
            std::string i = new_temp();
            d.push(i);
            quats(e, g, h, i);
        }
    }
}
//存储四元式
void outputquat(int i, int a) {
    for (i; i < a + 1; i++) {
        std::string s = scanner->getToken().find(i)->second.second;
        std::string t = scanner->getToken().find(i)->second.first;
        std::string q = scanner->getToken().find(i + 1)->second.second;
        //无返回函数
        if (t == "identifiers" && q == "(") {
            //std::cout<<"!";
            int c = i + 2;
            std::string z = scanner->getToken().find(c)->second.second;
            std::string z1 = scanner->getToken().find(c + 1)->second.second;
            if (z1 == ")") {
                quats("PARAM", z, "_", "_");
            }
            while (z != ")") {
                c++;
                z = scanner->getToken().find(c)->second.second;
                z1 = scanner->getToken().find(c - 1)->second.second;
                if (z == "," || z == ")") {
                    quats("PARAM", z1, "_", "_");
                }
            }
            i = c + 1;
            quats("CALL", s, "_", "_");
        }
        //if else的四元式生成
        else if (s == "if") {
            std::string x = scanner->getToken().find(i + 2)->second.second;
            int y = i + 2;
            while (x != ")") {
                y++;
                x = scanner->getToken().find(y)->second.second;
            }
            ariquat(i + 2, y - 1);
            i = y + 2;
            y = i;
            std::string res = quat[quanum - 1].result;
            int num1 = quanum;
            quats("if", res, "_", temp);
            x = scanner->getToken().find(i)->second.second;
            while (x != "}") {
                y++;
                x = scanner->getToken().find(y)->second.second;
            }
            outputquat(i, y - 1);
            i = y;
            x = scanner->getToken().find(i + 1)->second.second;
            if (x == "else") {
                int num2 = quanum;
                quats("el", "_", "_", temp);
                quat[num1].result = std::to_string(quanum);
                i = i + 3;
                y = i;
                x = scanner->getToken().find(i)->second.second;
                while (x != "}") {
                    y++;
                    x = scanner->getToken().find(y)->second.second;
                }
                outputquat(i, y - 1);
                quat[num2].result = std::to_string(quanum);
                i = y;
            }
            else {
                quat[num1].result = std::to_string(quanum);
            }
            quats("ie", "_", "_", "_");
        }
        //迭代的四元式生成
        else if (s == "whlie") {
            //std::cout<<"!";
            quats("wh", "_", "_", "_");
            int num2 = quanum;
            std::string x = scanner->getToken().find(i + 1)->second.second;
            int y = i + 1;
            while (x != ")") {
                y++;
                x = scanner->getToken().find(y)->second.second;
            }
            ariquat(i + 2, y - 1);
            i = y + 2;
            y = i;
            std::string res = quat[quanum - 1].result;
            int num1 = quanum;
            quats("do", res, "_", temp);
            x = scanner->getToken().find(i)->second.second;
            while (x != "}") {
                y++;
                x = scanner->getToken().find(y)->second.second;
            }
            outputquat(i, y - 1);
            i = y;
            std::string z = std::to_string(num2);
            quats("we", "_", "_", z);
            quat[num1].result = std::to_string(quanum);
        }
        //赋值四元式生成
        else if (s == "=") {
            // std::cout<<"!";
            int y = i + 1;
            std::string x = scanner->getToken().find(i + 1)->second.second;
            std::string x1 = scanner->getToken().find(i + 1)->second.first;
            std::string x2 = scanner->getToken().find(i + 2)->second.second;
            std::string res;
            if (x2 == ";") {
                res = x;
            }
            else if (x1 == "identifiers" && x2 == "(") {
                int c = i + 1;
                std::string z = scanner->getToken().find(c)->second.second;
                std::string z1 = scanner->getToken().find(c + 1)->second.second;
                std::string z2 = scanner->getToken().find(c + 2)->second.second;
                if (z2 == ")") {
                    quats("PARAM", z1, "_", "_");
                }
                while (z != ")") {
                    c++;
                    z = scanner->getToken().find(c)->second.second;
                    z1 = scanner->getToken().find(c - 1)->second.second;
                    if (z == "," || z == ")") {
                        quats("PARAM", z1, "_", "_");
                    }
                }
                a = c;
                std::string new1 = new_temp();
                quats("CALL", x, "_", new1);
                res = new1;
            }
            else {
                while (x != ";") {
                    y++;
                    x = scanner->getToken().find(y)->second.second;
                }
                ariquat(i + 1, y - 1);
                res = quat[quanum - 1].result;
            }
            std::string z = scanner->getToken().find(i - 1)->second.second;
            quats("=", res, "_", z);
            i = y;
        }
        else if (s == "") {
            std::cout << "1";
        }
    }
}
//输出四元式
void coutquat() {
    std::ofstream ofs;
    ofs.open("test.txt", std::ios::out);
    for (int i = 0; quat[i].symbal[0] != '\0'; i++) {
        ofs << quat[i].symbal << ' ' << quat[i].op_a << ' ' << quat[i].op_b << ' ' << quat[i].result << std::endl;
    }
    ofs.close();
}

void usingq(int a) {
    outputquat(0, a - 1);
    coutquat();
}
