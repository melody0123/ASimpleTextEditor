#include "text_editor.h"

text_editor::text_editor()
{
    //先建立文件流

    printf("请指定输入文件名称（位于同一目录下，例如：in.txt）：");
    fflush(stdin);
    scanf("%s", in_file_name);
    inFile.open(in_file_name, ios::in);
    if(inFile.fail())
    {
        printf("文件打开失败！\n");
        exit(2);
    }

    printf("请指定输出文件名称（位于同一目录下，例如：out.txt）：");
    fflush(stdin);
    scanf("%s", out_file_name);
    outFile.open(out_file_name, ios::out);
    if(outFile.fail())
    {
        printf("文件打开失败！\n");
        exit(2);
    }

    //然后把文件读入缓冲区
    string tmp_str; //临时保存一行字符
    while(getline(inFile, tmp_str))
        buffer.push_back(tmp_str);
}

text_editor::~text_editor()
{
    buffer.go_head(); //把cur指针移到头节点
    node *tmp_ptr = buffer.get_cur();
    if(tmp_ptr != nullptr)
    {
        //链表不为空
        while(tmp_ptr != nullptr)
        {
            outFile << tmp_ptr->data << endl;
            tmp_ptr = tmp_ptr->next;
        }
    }
    //buffer.~double_link_list(); //把双链表的内存空间释放掉
    inFile.close(); //关闭文件
    outFile.close();
    //return;
}

void text_editor::run()
{

    while(true)
    {
        cout << (buffer.get_cur())->num << "：" << (buffer.get_cur())->data << endl;
        char cmd = 0;
        printf(">>");
        fflush(stdin);
        scanf("%c", &cmd);

        if(cmd == 'i' || cmd == 'I')
        {
            int i = 0;
            string str;
            printf("请输入待插入的行索引值：");
            fflush(stdin);
            scanf("%d", &i);
            printf("请输入待插入的字符串：");
            fflush(stdin);
            getline(cin, str);
            buffer.insrt(i, str);
        }
        else if(cmd == 'd' || cmd == 'D')
        {
            int i = 0;
            printf("请输入欲删除的行索引值：");
            fflush(stdin);
            scanf("%d", &i);
            buffer.del(i);
        }
        else if(cmd == 'c' || cmd == 'C')
        {
            string str;
            printf("请输入新内容：");
            fflush(stdin);
            getline(cin, str);
            buffer.replace_cur(str);
        }
        else if(cmd == 'q' || cmd == 'Q')
        {
            break;
        }
        else if(cmd == 'h' || cmd == 'H')
        {
            printf("这是帮助信息：（不分大小写）i(nsert), d(elete), c(hange), q(uit), h(elp)\nn(ext), p(revious), b(egin), e(nd), g(oto)\nv(iew), r(ead), s(ave), l(ine), w(ord)\nf(ind), a(lternate)\n");
        }
        else if(cmd == 'n' || cmd == 'N')
        {
            buffer.go_next();
            node *tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
                cout << tmp_ptr->data << endl;
        }
        else if(cmd == 'p' || cmd == 'P')
        {
            buffer.go_prev();
            node *tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
                cout << tmp_ptr->data << endl;
        }
        else if(cmd == 'b' || cmd == 'B')
        {
            buffer.go_head();
            node *tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
                cout << tmp_ptr->data << endl;
        }
        else if(cmd == 'e' || cmd == 'E')
        {
            buffer.go_tail();
            node *tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
                cout << tmp_ptr->data << endl;
        }
        else if(cmd == 'g' || cmd == 'G')
        {
            int i = 0;
            printf("请输入欲跳转到的行号：");
            fflush(stdin);
            scanf("%d", &i);
            buffer.go_to(i);
            node *tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
                cout << tmp_ptr->data << endl;
        }
        else if(cmd == 'v' || cmd == 'V')
        {
            node *tmp_ptr = buffer.get_head();
            if(buffer.isempty())
            {
                printf("这是空文件！\n");
            }
            while(tmp_ptr != nullptr)
            {
                cout << tmp_ptr->data << endl;
                tmp_ptr = tmp_ptr->next;
            }
        }
        else if(cmd == 'r' || cmd == 'R')
        {
            inFile.close(); //重新打开文件
            inFile.open(in_file_name, ios::in);
            if(inFile.fail())
            {
                printf("文件打开失败！\n");
                exit(2);
            }
            buffer.clear(); //清空缓冲区
            string str;
            while(getline(inFile, str))
            {
                buffer.push_back(str);
            }
        }
        else if(cmd == 's' || cmd == 'S')
        {
            node *tmp_ptr = buffer.get_head(); //获取头指针
            if(tmp_ptr != nullptr)
            {
                //链表不为空
                while(tmp_ptr != nullptr)
                {
                    outFile << tmp_ptr->data << endl;
                    tmp_ptr = tmp_ptr->next;
                }
            }
            outFile.close();
            printf("请指定新的输出文件：");
            fflush(stdin);
            scanf("%s", out_file_name);
            outFile.open(out_file_name, ios::out);
            if(outFile.fail())
            {
                printf("文件打开失败！\n");
                exit(2);
            }
        }
        else if(cmd == 'l' || cmd == 'L')
        {
            printf("行数统计：共 %d 行\n", buffer.get_size());
        }
        else if(cmd == 'w' || cmd == 'W')
        {
            printf("字数统计：共 %d 字\n", buffer.get_word_num());
        }
        else if(cmd == 'f' || cmd == 'F')
        {
            node* tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
            {
                printf("请输入要查找的子串：");
                fflush(stdin);
                string pt;
                getline(cin, pt);
                int idx = tmp_ptr->data.find(pt);
                if(idx < (int)(tmp_ptr->data.length()))
                    printf("首次出现在：%d\n", idx);
                else
                    printf("未出现！\n");
            }
            else
                printf("当前行是空行！\n");
        }
        else if(cmd == 'a' || cmd == 'A')
        {
            node* tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
            {
                printf("请输入要替换的子串：");
                fflush(stdin);
                string pt;
                getline(cin, pt);

                printf("请输入新内容：");
                fflush(stdin);
                string ct;
                getline(cin, ct);
                if((tmp_ptr->data).find(pt) >= 0)
                {
                    (tmp_ptr->data).replace((tmp_ptr->data).find(pt), pt.length(), ct);
                }
                else
                    printf("对不起，没有找到模式串！\n");
            }

        }
        else
            printf("无效的命令！输入 h 查看帮助\n");
    }
    return;
}

