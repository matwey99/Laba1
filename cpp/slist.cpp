#include <iostream>
#include <string>
#include "slist.h"
using namespace std;

FList* createFList() {
    return new FList{nullptr, nullptr};
}

FNode* findNode(FList* list, const string& value) {
    FNode* cur = list->head;
    while (cur != nullptr) {
        if (cur->data == value) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void pushFront(FList* list, const string& value) {
    FNode* n = new FNode{value, list->head};
    list->head = n;
    if (list->tail == nullptr) list->tail = n;
}

void pushBack(FList* list, const string& value) {
    FNode* n = new FNode{value, nullptr};
    if (list->tail == nullptr) {
        list->head = n;
        list->tail = n;
    } else {
        list->tail->next = n;
        list->tail = n;
    }
}

bool pushAfter(FList* list, const string& target, const string& value) {
    FNode* p = findNode(list, target);
    if (p == nullptr) return false;
    FNode* n = new FNode{value, p->next};
    p->next = n;
    if (p == list->tail) list->tail = n;
    return true;
}

bool pushBefore(FList* list, const string& target, const string& value) {
    if (list->head == nullptr) return false;
    if (list->head->data == target) {
        pushFront(list, value);
        return true;
    }
    FNode* prev = list->head;
    while (prev->next != nullptr && prev->next->data != target) {
        prev = prev->next;
    }
    if (prev->next == nullptr) return false;
    FNode* n = new FNode{value, prev->next};
    prev->next = n;
    return true;
}

bool popFront(FList* list, string& result) {
    if (list->head == nullptr) return false;
    FNode* old = list->head;
    result = old->data;
    list->head = old->next;
    if (list->head == nullptr) list->tail = nullptr;
    delete old;
    return true;
}

bool popBack(FList* list, string& result) {
    if (list->head == nullptr) return false;
    if (list->head == list->tail) {
        result = list->head->data;
        delete list->head;
        list->head = nullptr;
        list->tail = nullptr;
        return true;
    }
    FNode* prev = list->head;
    while (prev->next != list->tail) {
        prev = prev->next;
    }
    result = list->tail->data;
    delete list->tail;
    list->tail = prev;
    list->tail->next = nullptr;
    return true;
}

bool removeAfter(FList* list, const string& target, string& result) {
    FNode* p = findNode(list, target);
    if (p == nullptr || p->next == nullptr) return false;
    FNode* victim = p->next;
    result = victim->data;
    p->next = victim->next;
    if (victim == list->tail) list->tail = p;
    delete victim;
    return true;
}

bool removeBefore(FList* list, const string& target, string& result) {
    if (list->head == nullptr || list->head->data == target) return false;
    if (list->head->next == nullptr) return false;
    if (list->head->next->data == target) return popFront(list, result);
    FNode* prev = list->head;
    while (prev->next->next != nullptr && prev->next->next->data != target) {
        prev = prev->next;
    }
    if (prev->next->next == nullptr) return false;
    FNode* victim = prev->next;
    result = victim->data;
    prev->next = victim->next;
    delete victim;
    return true;
}

bool removeValue(FList* list, const string& value) {
    if (list->head == nullptr) return false;
    if (list->head->data == value) {
        string tmp;
        return popFront(list, tmp);
    }
    FNode* prev = list->head;
    while (prev->next != nullptr && prev->next->data != value) {
        prev = prev->next;
    }
    if (prev->next == nullptr) return false;
    FNode* victim = prev->next;
    prev->next = victim->next;
    if (victim == list->tail) list->tail = prev;
    delete victim;
    return true;
}

bool getAt(FList* list, int index, string& result) {
    if (index < 0) return false;
    FNode* cur = list->head;
    for (int i = 0; i < index && cur != nullptr; i++) {
        cur = cur->next;
    }
    if (cur == nullptr) return false;
    result = cur->data;
    return true;
}

void print(FList* list) {
    FNode* cur = list->head;
    if (cur == nullptr) { cout << "(empty)" << endl; return; }
    while (cur != nullptr) {
        cout << cur->data;
        if (cur->next != nullptr) cout << " -> ";
        cur = cur->next;
    }
    cout << endl;
}

static void printReverseRec(FNode* node) {
    if (node == nullptr) return;
    printReverseRec(node->next);
    cout << node->data << " ";
}

void printReverse(FList* list) {
    if (list->head == nullptr) { cout << "(empty)" << endl; return; }
    printReverseRec(list->head);
    cout << endl;
}

void freeList(FList* list) {
    string tmp;
    while (popFront(list, tmp)) {}
    delete list;
}
