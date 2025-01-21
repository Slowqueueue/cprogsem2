//Объединение двух односвязных списков.
#include <iostream>
using namespace std;

struct list {
    char letter;
    list* next;
};

list* start_list(char letter);
list* merge(list** top, list** top2);
void push(list** top, char letter);
char pop(list** top);

int main() {
    char letter;
    cout << "Enter first list with '.' at the end" << endl;
    cin >> letter;
    list* list1 = start_list(letter);
    cin >> letter;
    while (letter != '.') {
        push(&list1, letter);
        cin >> letter;
    }
    cout << "Enter second list with '.' at the end" << endl;
    cin >> letter;
    list* list2 = start_list(letter);
    cin >> letter;
    while (letter != '.') {
        push(&list2, letter);
        cin >> letter;
    }
    list* result = merge(&list1, &list2);
    while (result) cout << pop(&result) << ' ';
    return 0;
}

list* start_list(char letter) {
    list* p = new list;
    p->letter = letter;
    p->next = 0;
    return p;
}

list* merge(list** list1, list** list2) {
    char temp;
    temp = pop(list2);
    list* p = start_list(temp);
    while (*list2 != NULL) {
        char temp2 = pop(list2);
        push(&p, temp2);
    }
    while (*list1 != NULL) {
        char temp2 = pop(list1);
        push(&p, temp2);
    }
    return p;
}

void push(list** listpush, char letter) {
    list* p = new list;
    p->letter = letter;
    p->next = *listpush;
    *listpush = p;
}

char pop(list** listpop) {
    char temp = (*listpop)->letter;
    list* p = *listpop;
    *listpop = (*listpop)->next;
    delete p;
    return temp;
}