#ifndef DOUBLE_LINK_LIST_H_INCLUDED
#define DOUBLE_LINK_LIST_H_INCLUDED

#include "node.h"
#include <cstdio>
#include <string>

using namespace std;

class double_link_list //˫����
{
private:
    node *head; //ͷ�ڵ�ָ��
    node *tail; //β�ڵ�ָ��
    node *cur; //��ǰ�еĽڵ�ָ��
    void update_sn(int i); //�ӵ� i ���ڵ㿪ʼ���������к����ڵ����ţ������� i ������������ʵ��������get_size()����Ӧ����������ɾ����Ϻ����ִ��
public:
    double_link_list(); //���캯��

    ~double_link_list(); //��������

    int get_size(); //���������ȣ����ı�����

    int get_word_num(); //����������

    node* get_cur(); //���curָ�룬����ʾ��ǰ������

    node* get_head(); //���headָ��

    void go_head(); //��curָ��ͷ�ڵ㣬������һ��

    void go_tail(); //��curָ��β�ڵ㣬�������һ��

    void go_prev(); //��curָ��ǰһ���ڵ㣬����ǰһ��

    void go_next(); //��curָ����һ���ڵ㣬������һ��

    void go_to(int); //��curָ��ָ���Ľڵ㣬����ָ����ĳһ��

    bool isempty(); //�ж��Ƿ�Ϊ��

    void push_back(string); //��β������ڵ�

    void insrt(int, string); //���ض�λ�ò���

    void del(int); //ɾ��ָ��λ�õ�Ԫ��

    void clear(); //�������

    void replace_cur(string); //�滻��ǰ��

//    void find_substr(string); //���Ҹ����Ӵ�
//
//    void replace_substr(string); //��������Ӵ�
};

#endif // DOUBLE_LINK_LIST_H_INCLUDED
