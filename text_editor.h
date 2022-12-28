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
    ifstream inFile; //�����ļ���
    ofstream outFile; //����ļ���
    double_link_list buffer; //˫�������Ļ�����
    char in_file_name[256] = {'\0'};
    char out_file_name[256] = {'\0'}; //�ļ�����
public:
    text_editor(); //���캯���������ļ����������ļ���������
    ~text_editor(); //�����������ر��ļ���
    void run(); //��������ڣ������û�����ִ�в�ͬ����
};

#endif // TEXT_EDITOR_H_INCLUDED
