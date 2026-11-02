#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

Stack* createStack() {
    return new Stack{nullptr};
}

// Новый элемент вставляется в голову списка и становится вершиной стека, O(1).
void push(Stack* s, const string& value) {
    FNode* n = new FNode{value, s->head};
    s->head = n;
}

// Извлечение вершины: удаляем голову списка, O(1).
bool pop(Stack* s, string& result) {
    if (s->head == nullptr) return false;
    FNode* old = s->head;
    result = old->data;
    s->head = old->next;
    delete old;
    return true;
}

// Чтение вершины без её удаления.
bool peek(Stack* s, string& result) {
    if (s->head == nullptr) return false;
    result = s->head->data;
    return true;
}

// Вывод от вершины к дну.
void print(Stack* s) {
    FNode* cur = s->head;
    if (cur == nullptr) { cout << "(empty)" << endl; return; }
    cout << "top: ";
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void freeStack(Stack* s) {
    string tmp;
    while (pop(s, tmp)) {}
    delete s;
}