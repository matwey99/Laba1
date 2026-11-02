#include <iostream>
#include <string>
#include "stack.h"
using namespace std;

Stack* createStack() {
    return new Stack{nullptr};
}

void push(Stack* s, const string& value) {
    FNode* n = new FNode{value, s->head};
    s->head = n;
}

bool pop(Stack* s, string& result) {
    if (s->head == nullptr) return false;
    FNode* old = s->head;
    result = old->data;
    s->head = old->next;
    delete old;
    return true;
}

bool peek(Stack* s, string& result) {
    if (s->head == nullptr) return false;
    result = s->head->data;
    return true;
}

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
