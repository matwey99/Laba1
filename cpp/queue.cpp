#include <iostream>
#include <string>
#include "queue.h"
using namespace std;

Queue* createQueue() {
    return new Queue{nullptr, nullptr};
}

void push(Queue* q, const string& value) {
    FNode* n = new FNode{value, nullptr};
    if (q->tail == nullptr) {
        q->head = n;
        q->tail = n;
    } else {
        q->tail->next = n;
        q->tail = n;
    }
}

bool pop(Queue* q, string& result) {
    if (q->head == nullptr) return false;
    FNode* old = q->head;
    result = old->data;
    q->head = old->next;
    if (q->head == nullptr) q->tail = nullptr;
    delete old;
    return true;
}

bool peek(Queue* q, string& result) {
    if (q->head == nullptr) return false;
    result = q->head->data;
    return true;
}

void print(Queue* q) {
    FNode* cur = q->head;
    if (cur == nullptr) { cout << "(empty)" << endl; return; }
    cout << "front: ";
    while (cur != nullptr) {
        cout << cur->data << " ";
        cur = cur->next;
    }
    cout << endl;
}

void freeQueue(Queue* q) {
    string tmp;
    while (pop(q, tmp)) {}
    delete q;
}
