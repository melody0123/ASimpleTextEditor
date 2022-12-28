#include "text_editor.h"

text_editor::text_editor()
{
    //�Ƚ����ļ���

    printf("��ָ�������ļ����ƣ�λ��ͬһĿ¼�£����磺in.txt����");
    fflush(stdin);
    scanf("%s", in_file_name);
    inFile.open(in_file_name, ios::in);
    if(inFile.fail())
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(2);
    }

    printf("��ָ������ļ����ƣ�λ��ͬһĿ¼�£����磺out.txt����");
    fflush(stdin);
    scanf("%s", out_file_name);
    outFile.open(out_file_name, ios::out);
    if(outFile.fail())
    {
        printf("�ļ���ʧ�ܣ�\n");
        exit(2);
    }

    //Ȼ����ļ����뻺����
    string tmp_str; //��ʱ����һ���ַ�
    while(getline(inFile, tmp_str))
        buffer.push_back(tmp_str);
}

text_editor::~text_editor()
{
    buffer.go_head(); //��curָ���Ƶ�ͷ�ڵ�
    node *tmp_ptr = buffer.get_cur();
    if(tmp_ptr != nullptr)
    {
        //����Ϊ��
        while(tmp_ptr != nullptr)
        {
            outFile << tmp_ptr->data << endl;
            tmp_ptr = tmp_ptr->next;
        }
    }
    //buffer.~double_link_list(); //��˫������ڴ�ռ��ͷŵ�
    inFile.close(); //�ر��ļ�
    outFile.close();
    //return;
}

void text_editor::run()
{

    while(true)
    {
        cout << (buffer.get_cur())->num << "��" << (buffer.get_cur())->data << endl;
        char cmd = 0;
        printf(">>");
        fflush(stdin);
        scanf("%c", &cmd);

        if(cmd == 'i' || cmd == 'I')
        {
            int i = 0;
            string str;
            printf("������������������ֵ��");
            fflush(stdin);
            scanf("%d", &i);
            printf("�������������ַ�����");
            fflush(stdin);
            getline(cin, str);
            buffer.insrt(i, str);
        }
        else if(cmd == 'd' || cmd == 'D')
        {
            int i = 0;
            printf("��������ɾ����������ֵ��");
            fflush(stdin);
            scanf("%d", &i);
            buffer.del(i);
        }
        else if(cmd == 'c' || cmd == 'C')
        {
            string str;
            printf("�����������ݣ�");
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
            printf("���ǰ�����Ϣ�������ִ�Сд��i(nsert), d(elete), c(hange), q(uit), h(elp)\nn(ext), p(revious), b(egin), e(nd), g(oto)\nv(iew), r(ead), s(ave), l(ine), w(ord)\nf(ind), a(lternate)\n");
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
            printf("����������ת�����кţ�");
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
                printf("���ǿ��ļ���\n");
            }
            while(tmp_ptr != nullptr)
            {
                cout << tmp_ptr->data << endl;
                tmp_ptr = tmp_ptr->next;
            }
        }
        else if(cmd == 'r' || cmd == 'R')
        {
            inFile.close(); //���´��ļ�
            inFile.open(in_file_name, ios::in);
            if(inFile.fail())
            {
                printf("�ļ���ʧ�ܣ�\n");
                exit(2);
            }
            buffer.clear(); //��ջ�����
            string str;
            while(getline(inFile, str))
            {
                buffer.push_back(str);
            }
        }
        else if(cmd == 's' || cmd == 'S')
        {
            node *tmp_ptr = buffer.get_head(); //��ȡͷָ��
            if(tmp_ptr != nullptr)
            {
                //����Ϊ��
                while(tmp_ptr != nullptr)
                {
                    outFile << tmp_ptr->data << endl;
                    tmp_ptr = tmp_ptr->next;
                }
            }
            outFile.close();
            printf("��ָ���µ�����ļ���");
            fflush(stdin);
            scanf("%s", out_file_name);
            outFile.open(out_file_name, ios::out);
            if(outFile.fail())
            {
                printf("�ļ���ʧ�ܣ�\n");
                exit(2);
            }
        }
        else if(cmd == 'l' || cmd == 'L')
        {
            printf("����ͳ�ƣ��� %d ��\n", buffer.get_size());
        }
        else if(cmd == 'w' || cmd == 'W')
        {
            printf("����ͳ�ƣ��� %d ��\n", buffer.get_word_num());
        }
        else if(cmd == 'f' || cmd == 'F')
        {
            node* tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
            {
                printf("������Ҫ���ҵ��Ӵ���");
                fflush(stdin);
                string pt;
                getline(cin, pt);
                int idx = tmp_ptr->data.find(pt);
                if(idx < (int)(tmp_ptr->data.length()))
                    printf("�״γ����ڣ�%d\n", idx);
                else
                    printf("δ���֣�\n");
            }
            else
                printf("��ǰ���ǿ��У�\n");
        }
        else if(cmd == 'a' || cmd == 'A')
        {
            node* tmp_ptr = buffer.get_cur();
            if(tmp_ptr != nullptr)
            {
                printf("������Ҫ�滻���Ӵ���");
                fflush(stdin);
                string pt;
                getline(cin, pt);

                printf("�����������ݣ�");
                fflush(stdin);
                string ct;
                getline(cin, ct);
                if((tmp_ptr->data).find(pt) >= 0)
                {
                    (tmp_ptr->data).replace((tmp_ptr->data).find(pt), pt.length(), ct);
                }
                else
                    printf("�Բ���û���ҵ�ģʽ����\n");
            }

        }
        else
            printf("��Ч��������� h �鿴����\n");
    }
    return;
}

