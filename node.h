#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>

using namespace std;

struct node
{
    string data; //������
    node *prev; //ǰ��ָ��
    node *next; //���ָ��
    int num; //���

    //���캯��
    node();
    node(string, node*, node*, int);
    //��������
    ~node(){}
};

#endif // NODE_H_INCLUDED
