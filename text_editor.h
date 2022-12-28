#ifndef TEXT_EDITOR_H_INCLUDED
#define TEXT_EDITOR_H_INCLUDED

#include <string>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <iostream>
#include "double_link_list.h"

using namespace std;

class text_editor
{
private:
    ifstream inFile; //输入文件流
    ofstream outFile; //输出文件流
    double_link_list buffer; //双向链表搭建的缓冲区
    char in_file_name[256] = {'\0'};
    char out_file_name[256] = {'\0'}; //文件名称
public:
    text_editor(); //构造函数，建立文件流，读入文件至缓冲区
    ~text_editor(); //析构函数，关闭文件流
    void run(); //主程序入口，根据用户命令执行不同功能
};

#endif // TEXT_EDITOR_H_INCLUDED
