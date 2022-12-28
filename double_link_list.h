#ifndef DOUBLE_LINK_LIST_H_INCLUDED
#define DOUBLE_LINK_LIST_H_INCLUDED

#include "node.h"
#include <cstdio>
#include <string>

using namespace std;

class double_link_list //双链表
{
private:
    node *head; //头节点指针
    node *tail; //尾节点指针
    node *cur; //当前行的节点指针
    void update_sn(int i); //从第 i 个节点开始，更新所有后续节点的序号（包括第 i 个），由于其实现依赖于get_size()所以应该在链表增删改完毕后最后执行
public:
    double_link_list(); //构造函数

    ~double_link_list(); //析构函数

    int get_size(); //计算链表长度，即文本行数

    int get_word_num(); //计算总字数

    node* get_cur(); //获得cur指针，即显示当前行内容

    node* get_head(); //获得head指针

    void go_head(); //把cur指向头节点，即到第一行

    void go_tail(); //把cur指向尾节点，即到最后一行

    void go_prev(); //把cur指向前一个节点，即到前一行

    void go_next(); //把cur指向下一个节点，即到下一行

    void go_to(int); //把cur指向指定的节点，即到指定的某一行

    bool isempty(); //判断是否为空

    void push_back(string); //在尾部插入节点

    void insrt(int, string); //在特定位置插入

    void del(int); //删除指定位置的元素

    void clear(); //清空链表

    void replace_cur(string); //替换当前行

//    void find_substr(string); //查找给定子串
//
//    void replace_substr(string); //替代给定子串
};

#endif // DOUBLE_LINK_LIST_H_INCLUDED
