#include <iostream>
#include <cstdio>
#include <cstring>
#include <list>
using namespace std;

struct Node {
    int v;
    Node *prev, *next;
};

struct Link {
    Node *head, *tail, *L, *R;
    Link() {
        head = new Node(); tail = new Node();
        head->prev = tail->next = NULL;
        head->next = tail;
        tail->prev = head;
        L = R = head;
    }
    ~Link() {
        while (head->next != NULL)
        {
            Node *p = head;
            head = head->next;
            delete p;
        }
    }

    void insert(Node *pos, int v) {
        Node *p = new Node();
        p->v = v;
        pos->prev->next = p;
        p->prev = pos->prev;
        p->next = pos;
        pos->prev = p;
    }
    
    void push_back(int v) {
        insert(tail, v);
    }

    void erase(Node *pos) {
        pos->prev->next = pos->next;
        pos->next->prev = pos->prev;
        delete pos;
    }
};

int main(int argc, char *argv[])
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, a;
        scanf("%d", &n);

        Link L;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d", &a); L.push_back(a);
        }
        
        int l, r, m;
        scanf("%d%d%d", &l, &r, &m);

        for (int i = 1; i <= n; ++ i) {
            if (i <= l) L.L = L.L->next;
            if (i <= r) L.R = L.R->next;
        }

        r = 0;
        while (m--)
        {
            char cmd[50], pos[50];
            int d;
            scanf("%s", cmd);
            if (!strcmp(cmd, "Reverse")) {
                swap(L.L, L.R); r = !r;
            }
            else if (!strcmp(cmd, "Insert"))
            {
                scanf("%s%d", pos, &d);
                if (!r)
                {
                    if (!strcmp(pos, "L"))
                    {
                        L.insert(L.L, d);
                        L.L = L.L->prev;
                    }
                    else
                    {
                        L.insert(L.R->next, d);
                        L.R = L.R->next;
                    }
                }
                else
                {
                    if (!strcmp(pos, "L"))
                    {
                        L.insert(L.L->next, d);
                        L.L = L.L->next;
                    }
                    else
                    {
                        L.insert(L.R, d);
                        L.R = L.R->prev;
                    }
                }
            }
            else
            {
                scanf("%s", pos);
                if (!strcmp(cmd, "Delete"))
                {
                    if (!r)
                    {
                        if (!strcmp(pos, "L"))
                        {
                            L.L = L.L->next;
                            L.erase(L.L->prev);
                        }
                        else
                        {
                            L.R = L.R->prev;
                            L.erase(L.R->next);
                        }
                    }
                    else
                    {
                        if (!strcmp(pos, "L"))
                        {
                            L.L = L.L->prev;
                            L.erase(L.L->next);
                        }
                        else
                        {
                            L.R = L.R->next;
                            L.erase(L.R->prev);
                        }
                        if (L.L == L.R)
                            r = !r;
                    }
                }
                else if (!strcmp(cmd, "MoveLeft"))
                {
                    if (!r)
                    {
                        if (!strcmp(pos, "L"))
                        {
                            if (L.L->prev != L.head)
                                L.L = L.L->prev;
                        }
                        else
                        {
                            if (L.R->prev != L.head)
                                L.R = L.R->prev;
                        }
                    }
                    else
                    {
                        if (!strcmp(pos, "L"))
                        {
                            if (L.R->prev != L.head)
                            {
                                L.insert(L.L->next, L.R->prev->v);
                                L.L = L.L->next;
                                L.erase(L.R->prev);
                            }
                        }
                        else
                        {
                            L.insert(L.L->next, L.R->v);
                            L.R = L.R->next;
                            L.erase(L.R->prev);
                        }
                        if (L.L == L.R)
                            r = !r;
                    }
                }
                else
                {
                    if (!r)
                    {
                        if (!strcmp(pos, "L"))
                        {
                            if (L.L->next != L.tail)
                                L.L = L.L->next;
                        }
                        else
                        {
                            if (L.R->next != L.tail)
                                L.R = L.R->next;
                        }
                    }
                    else
                    {
                        if (!strcmp(pos, "L"))
                        {
                            L.insert(L.R, L.L->v);
                            L.L = L.L->prev;
                            L.erase(L.L->next);
                        }
                        else
                        {
                            if (L.L->next != L.tail)
                            {
                                L.insert(L.R, L.L->next->v);
                                L.R = L.R->prev;
                                L.erase(L.L->next);
                            }
                        }
                    }
                }
            }
        }

        Node *p;
        if (!r)
        {
            p = L.head->next;
            while (p != L.tail)
            {
                printf("%d", p->v);
                if (p->next != L.tail)
                    printf(" ");
                p = p->next;
            }
            printf("\n");
        }
        else
        {
            p = L.head->next;
            while (p != L.R)
            {
                printf("%d", p->v);
                if (p->next != L.tail)
                    printf(" ");
                p = p->next;
            }
            p = L.L;
            
            while (p != L.R->prev)
            {
                printf("%d", p->v);
                if (L.L->next != L.R->prev)
                    printf(" ");
                else if (p->prev != L.R->prev)
                    printf(" ");
                p = p->prev;
            }

            p = L.L->next;
            while (p != L.tail)
            {
                printf("%d", p->v);
                if (p->next != L.tail)
                    printf(" ");
                p = p->next;
            }
            printf("\n");
        }

        L.~Link();
    }
    return 0;
}
