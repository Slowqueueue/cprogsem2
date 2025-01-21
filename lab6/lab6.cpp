//Элемент дерева содержит либо данные(строка текста), либо указатели на правое и левое поддеревья.
//Строки в дереве упорядочены в порядке обхода концевых вершин.Написать функцию включения новой строки. 
//(Обратить внимание на то, что элемент с указателями не содержит данных, 
//и при включении новой вершины вершину с данными следует заменить на вершину с указателями).
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

struct binnode
{
    int element;
    string str;
    binnode* LL; //left link
    binnode* RL; //right link
    binnode() { element = 0; LL = 0; RL = 0; };
    ~binnode()
    {
        if (LL) LL->~binnode();
        if (RL) RL->~binnode();
        if (LL) { delete LL; LL = 0; }
        if (RL) { delete RL; RL = 0; }
    }
    void put_element(int new_element, string new_str) { this->element = new_element; this->str = new_str; }
    void clear_leftlink() { this->LL = 0; }
    void clear_rightlink() { this->RL = 0; }
    void add_string(int new_element, string new_str)
    {
        if (LL && (new_element < element)) LL->add_string(new_element, new_str);
        if (RL && (new_element > element)) RL->add_string(new_element, new_str);

        if (!LL && (new_element < element))
        {
            binnode* N = new binnode;
            N->element = new_element;
            N->str = new_str;
            N->LL = 0;
            N->RL = 0;
            LL = N;
        }
        if (!RL && (new_element > element))
        {
            binnode* N = new binnode;
            N->element = new_element;
            N->str = new_str;
            N->LL = 0;
            N->RL = 0;
            RL = N;
        }
    }
    void print(int tab)
    {
        if (RL) RL->print(tab + 1);
        for (int i = 1; i != tab; i++)cout << "  "; cout << this->element << "-" << this->str << endl;
        if (LL) LL->print(tab + 1);
    }


};

struct bintree
{
    binnode* link;
    bintree() { link = 0; };
    void add_string(int new_element, string new_str)
    {
        if (link) link->add_string(new_element, new_str);
        else
        {
            binnode* N = new binnode();
            N->put_element(new_element, new_str);
            N->clear_leftlink();
            N->clear_rightlink();
            link = N;
        }
    };
    void print_tree() { if (link)link->print(1); else cout << "The tree does not exist\n"; }
};

void input(bintree* T) {
    int eltree;
    string strtree; //значение
    cout << "Enter element number: "; cin >> eltree;
    cout << "Enter string: "; cin >> strtree;
    T->add_string(eltree, strtree);
}

void print(bintree* T) {
    printf("~~~~~~~~~~~~~~~:\n");
    T->print_tree();
    printf("~~~~~~~~~~~~~~~:\n");
}
int main()
{
    bintree* T = new bintree;
    int cmd = 0;
    do {
        printf("Commands:\n");
        printf("#1 Input string\n");
        printf("#2 Show tree\n");
        printf("#0 Quit\n");
        printf("Your command: ");
        scanf("%d", &cmd);
        switch (cmd)
        {
        case 0: break;
        case 1: input(T); break;
        case 2: print(T); break;
        default: printf("Wrong command number\n"); break;
        }
    } while (cmd != 0);
    delete T;
}