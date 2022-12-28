#include "double_link_list.h"

void double_link_list::update_sn(int i)
{
    int cur_size = get_size();
    //��� i �ĺϷ���
    if(i > cur_size || i < 1)
    {
        //printf("ϵͳ��ʾ�����в����ڣ�\n");
        return;
    }
    //���ҵ� i ���ڵ�
    node *tmp_ptr = head;
    for(int j = 1; j < i; j++)
        tmp_ptr = tmp_ptr->next;
    //����sn
    while(tmp_ptr != nullptr)
    {
        //���ǰһ���ڵ��Ƿ���ڣ��ýڵ��ǲ���ͷ�ڵ㣩
        if(tmp_ptr == head)
        {
            tmp_ptr->num = 1;
            tmp_ptr = tmp_ptr->next;
            continue;
        }
        else
        {
            //����ͷ�ڵ�
            tmp_ptr->num = ((tmp_ptr->prev)->num) + 1;
            tmp_ptr = tmp_ptr->next;
        }
    }
    return;
}

double_link_list::double_link_list()
{
    head = nullptr;
    tail = nullptr;
    cur = nullptr;
}

double_link_list::~double_link_list()
{
    if(get_size() != 0) //�ձ�������
    {
        node *tmp_ptr = head; //����
        node *p = nullptr; //�ͺ�
        while(tmp_ptr != nullptr)
        {
            p = tmp_ptr;
            tmp_ptr = tmp_ptr->next;
            delete p;
            p = nullptr;
        }
    }
}

int double_link_list::get_size()
{
    node *tmp = head;
    int len = 0;
    while(tmp != nullptr)
    {
        len++;
        tmp = tmp->next;
    }

    return len;
}

int double_link_list::get_word_num()
{
    //��Ҫ��������Ƿ�Ϊ��
    if(isempty())
    {
        //����Ϊ��
        return 0;
    }
    else
    {
        //����Ϊ��
        int cnt = 0; //����������
        node *tmp_ptr = head;
        while(tmp_ptr != nullptr)
        {
            cnt += (tmp_ptr->data).length();
            tmp_ptr = tmp_ptr->next;
        }
        return cnt;
    }
}

bool double_link_list::isempty()
{
    if(head == nullptr)
        return true;
    else
        return false;
}

node* double_link_list::get_cur()
{
    return cur;
}

node* double_link_list::get_head()
{
    return head;
}

void double_link_list::go_head()
{
    cur = head;
    return;
}

void double_link_list::go_next()
{
    //��Ҫ���ָ���Ƿ�����ƶ�
    if(cur != nullptr && cur->next != nullptr)
    {
        //ָ������ƶ�
        cur = cur->next;
        return;
    }
    else
    {
        //ָ�벻���ƶ�
        if(cur == nullptr)
        {
            printf("�Բ����ļ�Ϊ�գ�\n");
            return;
        }
        else if(cur->next == nullptr)
        {
            printf("�Բ������Ѿ������һ���ˣ�\n");
            return;
        }
    }
}

void double_link_list::go_prev()
{
    //��Ҫ���ָ���Ƿ�����ƶ�
    if(cur != nullptr && cur->prev != nullptr)
    {
        //ָ������ƶ�
        cur = cur->prev;
        return;
    }
    else
    {
        //ָ�벻���ƶ�
        if(cur == nullptr)
        {
            printf("�Բ����ļ�Ϊ�գ�\n");
            return;
        }
        else if(cur->prev == nullptr)
        {
            printf("�Բ������Ѿ��ǵ�һ���ˣ�\n");
            return;
        }
    }
}

void double_link_list::go_tail()
{
    cur = tail;
    return;
}

void double_link_list::go_to(int i)
{
    //��Ҫ���� i ���Ƿ����
    if(i > get_size())
    {
        printf("�Բ��𣬵�%d�в����ڣ�\n", i);
        return;
    }
    else
    {
        node *tmp_ptr = head;
        int cnt = 0;
        while(tmp_ptr != nullptr)
        {
            cnt++;
            if(cnt == i) //�ҵ��ˣ�����������˳�
            {
                cur = tmp_ptr;
                return;
            }
            tmp_ptr = tmp_ptr->next;
        }
    }
}

void double_link_list::insrt(int i, string str)
{
    //������������ڵ� i ��ǰ����һ��
    //��Ҫ���ǣ���ͷ�����룬���м���룬��β������
    //���ȼ�� i �ĺϷ���
    if(i <= 0)
    {
        printf("����ʧ�ܣ�������Ӧ����������!\n");
        return;
    }
    else
    {
        //��һ���أ���Ҫ���������Ƿ�Ϊ��
        if(isempty())
        {
            //����Ϊ��
            push_back(str);
        }
        else
        {
            //����Ϊ��
            if(i == 1) //��ͷ������
            {
                node *tmp_ptr = head;
                head = new node(str, nullptr, tmp_ptr, 1); //�½��ڵ㲢��ԭͷ�ڵ㽨������
                if(head == nullptr)
                {
                    printf("�ڴ����ʧ�ܣ�\n");
                    exit(1);
                }
                tmp_ptr->prev = head;
                update_sn(1);
                return;
            }
            else if(i > get_size()) //��β������
            {
                push_back(str);
                return;
            }
            else //���м����
            {
                node *tmp_ptr = head, *tmp_new = nullptr;
                int cnt = 1; //�� tmp_ptr ͬ��
                while(cnt < i)
                {
                    cnt++;
                    tmp_ptr = tmp_ptr->next;
                }
                //��ʱcnt == i
                tmp_new = new node(str, tmp_ptr->prev, tmp_ptr, i); //�½��ڵ㲢����ǰ������
                if(tmp_new == nullptr)
                {
                    printf("�ڴ����ʧ�ܣ�\n");
                    exit(1);
                }
                (tmp_ptr->prev)->next = tmp_new; //�޸�ԭָ��ָ��
                tmp_ptr->prev = tmp_new;
                update_sn(i);
            }
        }
    }
}

void double_link_list::del(int i)
{
    //��Ҫ��� i �ĺϷ���
    if(i >= 1 && i <= get_size())
    {
        //�Ϸ��� i
        //����������ɾ������ͷ�ڵ㣬β�ڵ㣬�����м�ڵ�
        node *tmp_ptr = nullptr;
        if(i == 1)
        {
            //ɾ��ͷ�ڵ㣬Ҫ���� head ?= tail
            if(get_size() == 1)
            {
                tail = nullptr;
                cur = nullptr;
            }
            tmp_ptr = head;
            if(cur == head)
                cur = cur->next; //��鵱ǰ��ָ���Ƿ�ָ��ͷ�ڵ�
            head = head->next;
            delete tmp_ptr;
            tmp_ptr = nullptr;
            update_sn(1);
            return;
        }
        else if(i == get_size())
        {
            //ɾ��β�ڵ�,ͬ���Ŀ���
            if(get_size() == 1)
            {
                head = nullptr;
                cur = nullptr;
            }
            tmp_ptr = tail;
            if(cur == tail) //��鵱ǰ��ָ���Ƿ�ָ��β�ڵ�
                cur = cur->prev;
            tail = tail->prev;
            tail->next = nullptr;
            delete tmp_ptr;
            tmp_ptr = nullptr;
            return;
        }
        else
        {
            //ɾ���м�ڵ�
            tmp_ptr = head;
            int cnt = 1; //�� tmp_ptr ͬ��
            while(cnt < i)
            {
                cnt++;
                tmp_ptr = tmp_ptr->next;
            }
            //��ʱtmp_ptr �Ѿ�ָ��� i ��
            (tmp_ptr->prev)->next = tmp_ptr->next;
            (tmp_ptr->next)->prev = tmp_ptr->prev; //�ı�ָ��ָ��
            if(cur == tmp_ptr)
                cur = cur->prev; //��鵱ǰָ���Ƿ�ָ��ɾ������
            delete tmp_ptr;
            tmp_ptr = nullptr;
            update_sn(i);
            return;
        }
    }
    else
    {
        //�Ƿ��� i
        printf("��%d�в����ڣ�\n", i);
        return;
    }
}

void double_link_list::replace_cur(string str)
{
    //���ȼ�鵱ǰָ���Ƿ�Ϸ�
    if(cur != nullptr)
    {
        cur->data = str;
        return;
    }
    else
    {
        //ָ�벻�Ϸ�
        printf("�Բ��𣬵�ǰ�ļ�Ϊ�գ�\n");
        return;
    }
}

void double_link_list::clear()
{
    while(!isempty())
    {
        del(1);
    }
    return;
}

void double_link_list::push_back(string str)
{
    //������Ϊ�պ�����Ϊ�������������
    if(!isempty())
    {
        //����Ϊ��
        node *tmp_ptr = new node(str, tail, nullptr, (tail->num) + 1); //�½��ڵ㲢���β�ڵ㽨������
        if(tmp_ptr == nullptr)
        {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }
        tail->next = tmp_ptr; //������β�ڵ㵽��β�ڵ������
        tail = tmp_ptr; //����βָ��
        cur = tmp_ptr; //���µ�ǰ��ָ��
        return;
    }
    else
    {
        //����Ϊ��
        head = new node(str, nullptr, nullptr, 1); //�½��ڵ㲢д������
        if(head == nullptr)
        {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1);
        }
        tail = head; //����βָ��
        cur = head; //���µ�ǰ��ָ��
        return;
    }
}
