#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>

using namespace std;

struct node
{
    string data; //数据域
    node *prev; //前驱指针
    node *next; //后继指针
    int num; //序号

    //构造函数
    node();
    node(string, node*, node*, int);
    //析构函数
    ~node(){}
};

#endif // NODE_H_INCLUDED
