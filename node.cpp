#include "node.h"

node::node()
{
    next = nullptr;
    prev = nullptr;
    num = -1;
}
node::node(string str,
     node *link_prev = nullptr,
     node *link_next = nullptr,
     int seq = -1)
{
    data = str;
    prev = link_prev;
    next = link_next;
    num = seq;
}
