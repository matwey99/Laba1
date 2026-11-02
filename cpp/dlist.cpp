#include <iostream>
#include <string>
#include "dlist.h"
using namespace std;

DList* createDList() {
    return new DList{nullptr, nullptr};
}

DNode* findNode(DList* list, const string& value) {
    DNode* cur = list->head;
    while (cur != nullptr) {
        if (cur->data == value) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void pushFront(DList* list, const string& value) {
    DNode* n = new DNode{value, nullptr, list->head};
    if (list->head != nullptr) list->head->prev = n;
    else list->tail = n;
    list->head = n;
}

void pushBack(DList* list, const string& value) {
    DNode* n = new DNode{value, list->tail, nullptr};
    if (list->tail != nullptr) list->tail->next = n;
    else list->head = n;
    list->tail = n;
}

bool pushAfter(DList* list, const string& target, const string& value) {
    DNode* p = findNode(list, target);
    if (p == nullptr) return false;
    DNode* n = new DNode{value, p, p->next};
    if (p->next != nullptr) p->next->prev = n;
    else list->tail = n;
    p->next = n;
    return true;
}

bool pushBefore(DList* list, const string& target, const string& value) {
    DNode* p = findNode(list, target);
    if (p == nullptr) return false;
    DNode* n = new DNode{value, p->prev, p};
    if (p->prev != nullptr) p->prev->next = n;
    else list->head = n;
    p->prev = n;
    return true;
}

void unlink(DList* list, DNode* node) {
    if (node->prev != nullptr) node->prev->next = node->next;
    else list->head = node->next;
    if (node->next != nullptr) node->next->prev = node->prev;
    else list->tail = node->prev;
    delete node;
}

bool popFront(DList* list, string& result) {
    if (list->head == nullptr) return false;
    result = list->head->data;
    unlink(list, list->head);
    return true;
}

bool popBack(DList* list, string& result) {
    if (list->tail == nullptr) return false;
    result = list->tail->data;
    unlink(list, list->tail);
    return true;
}

bool removeAfter(DList* list, const string& target, string& result) {
    DNode* p = findNode(list, target);
    if (p == nullptr || p->next == nullptr) return false;
    result = p->next->data;
    unlink(list, p->next);
    return true;
}

bool removeBefore(DList* list, const string& target, string& result) {
    DNode* p = findNode(list, target);
    if (p == nullptr || p->prev == nullptr) return false;
    result = p->prev->data;
    unlink(list, p->prev);
    return true;
}

bool removeValue(DList* list, const string& value) {
    DNode* p = findNode(list, value);
    if (p == nullptr) return false;
    unlink(list, p);
    return true;
}

bool getAt(DList* list, int index, string& result) {
    if (index < 0) return false;
    DNode* cur = list->head;
    for (int i = 0; i < index && cur != nullptr; i++) {
        cur = cur->next;
    }
    if (cur == nullptr) return false;
    result = cur->data;
    return true;
}

void print(DList* list) {
    DNode* cur = list->head;
    if (cur == nullptr) { cout << "(empty)" << endl; return; }
    while (cur != nullptr) {
        cout << cur->data;
        if (cur->next != nullptr) cout << " <-> ";
        cur = cur->next;
    }
    cout << endl;
}

void printReverse(DList* list) {
    DNode* cur = list->tail;
    if (cur == nullptr) { cout << "(empty)" << endl; return; }
    while (cur != nullptr) {
        cout << cur->data;
        if (cur->prev != nullptr) cout << " <-> ";
        cur = cur->prev;
    }
    cout << endl;
}

void freeList(DList* list) {
    string tmp;
    while (popFront(list, tmp)) {}
    delete list;
}
