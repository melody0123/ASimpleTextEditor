#include "double_link_list.h"

void double_link_list::update_sn(int i)
{
    int cur_size = get_size();
    //检查 i 的合法性
    if(i > cur_size || i < 1)
    {
        //printf("系统提示：该行不存在！\n");
        return;
    }
    //查找第 i 个节点
    node *tmp_ptr = head;
    for(int j = 1; j < i; j++)
        tmp_ptr = tmp_ptr->next;
    //更新sn
    while(tmp_ptr != nullptr)
    {
        //检查前一个节点是否存在（该节点是不是头节点）
        if(tmp_ptr == head)
        {
            tmp_ptr->num = 1;
            tmp_ptr = tmp_ptr->next;
            continue;
        }
        else
        {
            //不是头节点
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
    if(get_size() != 0) //空表不用析构
    {
        node *tmp_ptr = head; //先驱
        node *p = nullptr; //滞后
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
    //需要检查链表是否为空
    if(isempty())
    {
        //链表为空
        return 0;
    }
    else
    {
        //链表不为空
        int cnt = 0; //字数计数器
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
    //需要检查指针是否可以移动
    if(cur != nullptr && cur->next != nullptr)
    {
        //指针可以移动
        cur = cur->next;
        return;
    }
    else
    {
        //指针不能移动
        if(cur == nullptr)
        {
            printf("对不起，文件为空！\n");
            return;
        }
        else if(cur->next == nullptr)
        {
            printf("对不起，这已经是最后一行了！\n");
            return;
        }
    }
}

void double_link_list::go_prev()
{
    //需要检查指针是否可以移动
    if(cur != nullptr && cur->prev != nullptr)
    {
        //指针可以移动
        cur = cur->prev;
        return;
    }
    else
    {
        //指针不能移动
        if(cur == nullptr)
        {
            printf("对不起，文件为空！\n");
            return;
        }
        else if(cur->prev == nullptr)
        {
            printf("对不起，这已经是第一行了！\n");
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
    //需要检查第 i 行是否存在
    if(i > get_size())
    {
        printf("对不起，第%d行不存在！\n", i);
        return;
    }
    else
    {
        node *tmp_ptr = head;
        int cnt = 0;
        while(tmp_ptr != nullptr)
        {
            cnt++;
            if(cnt == i) //找到了，程序从这里退出
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
    //这个函数用于在第 i 行前插入一行
    //需要考虑：在头部插入，在中间插入，在尾部插入
    //首先检查 i 的合法性
    if(i <= 0)
    {
        printf("插入失败，行索引应该是正整数!\n");
        return;
    }
    else
    {
        //进一步地，需要考虑链表是否为空
        if(isempty())
        {
            //链表为空
            push_back(str);
        }
        else
        {
            //链表不为空
            if(i == 1) //在头部插入
            {
                node *tmp_ptr = head;
                head = new node(str, nullptr, tmp_ptr, 1); //新建节点并与原头节点建立连接
                if(head == nullptr)
                {
                    printf("内存分配失败！\n");
                    exit(1);
                }
                tmp_ptr->prev = head;
                update_sn(1);
                return;
            }
            else if(i > get_size()) //在尾部插入
            {
                push_back(str);
                return;
            }
            else //在中间插入
            {
                node *tmp_ptr = head, *tmp_new = nullptr;
                int cnt = 1; //与 tmp_ptr 同步
                while(cnt < i)
                {
                    cnt++;
                    tmp_ptr = tmp_ptr->next;
                }
                //此时cnt == i
                tmp_new = new node(str, tmp_ptr->prev, tmp_ptr, i); //新建节点并建立前后连接
                if(tmp_new == nullptr)
                {
                    printf("内存分配失败！\n");
                    exit(1);
                }
                (tmp_ptr->prev)->next = tmp_new; //修改原指针指向
                tmp_ptr->prev = tmp_new;
                update_sn(i);
            }
        }
    }
}

void double_link_list::del(int i)
{
    //需要检查 i 的合法性
    if(i >= 1 && i <= get_size())
    {
        //合法的 i
        //接下来考虑删除的是头节点，尾节点，还是中间节点
        node *tmp_ptr = nullptr;
        if(i == 1)
        {
            //删除头节点，要考虑 head ?= tail
            if(get_size() == 1)
            {
                tail = nullptr;
                cur = nullptr;
            }
            tmp_ptr = head;
            if(cur == head)
                cur = cur->next; //检查当前行指针是否指向头节点
            head = head->next;
            delete tmp_ptr;
            tmp_ptr = nullptr;
            update_sn(1);
            return;
        }
        else if(i == get_size())
        {
            //删除尾节点,同样的考虑
            if(get_size() == 1)
            {
                head = nullptr;
                cur = nullptr;
            }
            tmp_ptr = tail;
            if(cur == tail) //检查当前行指针是否指向尾节点
                cur = cur->prev;
            tail = tail->prev;
            tail->next = nullptr;
            delete tmp_ptr;
            tmp_ptr = nullptr;
            return;
        }
        else
        {
            //删除中间节点
            tmp_ptr = head;
            int cnt = 1; //与 tmp_ptr 同步
            while(cnt < i)
            {
                cnt++;
                tmp_ptr = tmp_ptr->next;
            }
            //此时tmp_ptr 已经指向第 i 行
            (tmp_ptr->prev)->next = tmp_ptr->next;
            (tmp_ptr->next)->prev = tmp_ptr->prev; //改变指针指向
            if(cur == tmp_ptr)
                cur = cur->prev; //检查当前指针是否指向被删除的行
            delete tmp_ptr;
            tmp_ptr = nullptr;
            update_sn(i);
            return;
        }
    }
    else
    {
        //非法的 i
        printf("第%d行不存在！\n", i);
        return;
    }
}

void double_link_list::replace_cur(string str)
{
    //首先检查当前指针是否合法
    if(cur != nullptr)
    {
        cur->data = str;
        return;
    }
    else
    {
        //指针不合法
        printf("对不起，当前文件为空！\n");
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
    //分链表为空和链表不为空两种情况讨论
    if(!isempty())
    {
        //链表不为空
        node *tmp_ptr = new node(str, tail, nullptr, (tail->num) + 1); //新建节点并与旧尾节点建立连接
        if(tmp_ptr == nullptr)
        {
            printf("内存分配失败！\n");
            exit(1);
        }
        tail->next = tmp_ptr; //建立旧尾节点到新尾节点的连接
        tail = tmp_ptr; //更新尾指针
        cur = tmp_ptr; //更新当前行指针
        return;
    }
    else
    {
        //链表为空
        head = new node(str, nullptr, nullptr, 1); //新建节点并写入内容
        if(head == nullptr)
        {
            printf("内存分配失败！\n");
            exit(1);
        }
        tail = head; //更新尾指针
        cur = head; //更新当前行指针
        return;
    }
}
