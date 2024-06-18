#include <vector>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>

#include "config.hpp"
#include "ReadWord.hpp"
#include "LexAnalysis.hpp"
#include "utils.hpp"
#include "keyword.hpp"
#include "exceptions.hpp"

std::string str[20] = {"void", "int", "float", "double", "long", "long long", "short", "bool", "char"};
int v1 = 0;
std::string temp3 = "ENT";

//用于产生相对地址
std::string newtemp() {
    char* pq;
    char mm[18];
    pq = (char*) malloc(18);
    v1++;
    snprintf(mm, sizeof(mm), "%d", v1);
    strcpy(pq + 1, mm);
    pq[0] = 'v';
    std::string s = pq;
    return s;
}
//判断变量类型
int findstr(std::string s) {
    int i = 0;
    for (i; i < 9; i++) {
        if (s == str[i]) {
            return i + 1;
        }
    }
    if (i == 9) {
        return 0;
    }
    return 0;
}
int k=0;
int c1=0;
int l=0;
int a=0;
int f1=0;
const int arraysize=1000;
KeyWord keywordarray[arraysize];
constant constantarray[arraysize];
LENL lenlarray[arraysize];
ALNFL alnflarray[arraysize];
function functionarray[arraysize];
void symbols(int i,int m)
{
    for(int i=0; i<m+1; i++)
    {
        std::string t=scanner->getToken().find(i)->second.first;
        std::cout<<t<<std::endl;
        if(t=="keyword")
        {
            std::string t1=scanner->getToken().find(i)->second.second;

            //优先判断常量
            if(t1=="const")
            {
                std::string s=scanner->getToken().find(i+1)->second.second;
                std::string b=scanner->getToken().find(i+2)->second.second;
                std::string x=scanner->getToken().find(i+4)->second.second;
                Type type1;
                if(b=="char")
                {
                    x=scanner->getToken().find(i+5)->second.second;
                    constantarray[c1]=constant(x);
                    type1=Type('c',NULL);
                }
                else if(b=="int")
                {
                    constantarray[c1]=constant(x);
                    type1=Type('i',NULL);
                }
                else if(b=="long")
                {
                    constantarray[c1]=constant(x);
                    type1=Type('i',NULL);
                }
                else if(b=="long long")
                {
                    constantarray[c1]=constant(x);
                    type1=Type('i',NULL);
                }
                else if(b=="bool")
                {
                    constantarray[c1]=constant(x);
                    type1=Type('b',NULL);
                }
                else if(b=="float")
                {
                    constantarray[c1]=constant(x);
                    type1=Type('r',NULL);
                }
                else if (b=="double")
                {
                    constantarray[c1]=constant(x);
                    type1=Type('r',NULL);
                }
                keywordarray[k]=KeyWord(b,type1,5,temp2);
                k++;
                c1++;
                i=i+5;
            }
            if(findstr(t1))
            {
                std::string s=scanner->getToken().find(i+1)->second.second;
                std::string b=scanner->getToken().find(i+2)->second.second;
                std::string b1=scanner->getToken().find(i+3)->second.second;
                //判断是否为函数
                if(b=="(")
                {
                    std::string z;
                    std::string z1;
                    Type type1=Type(' ',NULL);
                    keywordarray[k]=KeyWord(s,type1,4,temp2);
                    k++;
                    if(b1==")")
                    {
                        std::vector<KeyWord> keywordarray1;
                        functionarray[f1]=function(1,3,0,temp3,keywordarray1);
                    }
                    else
                    {
                        int c=i+3;
                        int y=0;
                        while(b1!=")")
                        {
                            c++;

                            b1=scanner->getToken().find(c)->second.second;
                            if(b1==","||b1==")")
                            {
                                z=scanner->getToken().find(c-2)->second.second;
                                z1=scanner->getToken().find(c-1)->second.second;
                                Type type2;
                                if(z=="char")
                                {
                                    type2=Type('c',NULL);
                                }
                                else if(z=="int"||z=="long"||z=="long long")
                                {
                                    type2=Type('i',NULL);
                                }
                                else if(z=="float"||z=="double")
                                {
                                    type2=Type('r',NULL);
                                }
                                std::string temp1=newtemp();
                                keywordarray[k]=KeyWord(z,type2,3,temp1);
                                y++;
                            }
                        }
                        std::vector<KeyWord> keywordarray1;
                        functionarray[f1]=function(1,3,y,temp3,keywordarray1);
                    }
                }
                //判断是否为数组
                else if(b=="[")
                {
                    std::string x=scanner->getToken().find(i+3)->second.second;
                    int y=stoi(x,0,10);
                    int z=i+7;
                    int e;
                    std::string d=scanner->getToken().find(z)->second.second;
                    while(d==")")
                    {
                        z++;
                        d=scanner->getToken().find(z)->second.second;
                    }
                    if(z==i+7)
                    {
                        e=0;
                    }
                    else if(z==i+8)
                    {
                        e=1;
                    }
                    else if(z>i+8)
                    {
                        e=(z-i-6)/2;
                    }
                    alnflarray[a]=ALNFL(0,y,e,std::vector<KeyWord>());
                    a++;
                    Type type1=Type('a',NULL);
                    std::string temp1=newtemp();
                    keywordarray[k]=KeyWord(b,type1,1,temp1);
                    k++;
                    i=z;
                }
                //记录数据
                else
                {
                    std::string d=scanner->getToken().find(i+3)->second.second;
                    Type type1;
                    if(t1=="char")
                    {
                        type1=Type('c',NULL);
                    }
                    else if(t1=="int")
                    {
                        type1=Type('i',NULL);
                    }
                    else if(b=="long")
                    {
                        type1=Type('i',NULL);
                    }
                    else if(b=="long long")
                    {
                        type1=Type('i',NULL);
                    }
                    else if(b=="float")
                    {
                        type1=Type('r',NULL);
                    }
                    else if(b=="double")
                    {
                        type1=Type('r',NULL);
                    }
                    std::string temp1=newtemp();
                    keywordarray[k]=KeyWord(s,type1,1,temp1);
                    k++;
                    i=i+1;
                }
            }
        }
        else
        {
            continue;
        }
    }
}
