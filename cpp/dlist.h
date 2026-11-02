#pragma once
#include <string>

struct DNode {
    std::string data;
    DNode* prev;
    DNode* next;
};

struct DList {
    DNode* head;
    DNode* tail;
};

DList* createDList();
DNode* findNode(DList* list, const std::string& value);

void pushFront(DList* list, const std::string& value);
void pushBack(DList* list, const std::string& value);
bool pushAfter(DList* list, const std::string& target, const std::string& value);
bool pushBefore(DList* list, const std::string& target, const std::string& value);

void unlink(DList* list, DNode* node);

bool popFront(DList* list, std::string& result);
bool popBack(DList* list, std::string& result);
bool removeAfter(DList* list, const std::string& target, std::string& result);
bool removeBefore(DList* list, const std::string& target, std::string& result);
bool removeValue(DList* list, const std::string& value);

bool getAt(DList* list, int index, std::string& result);
void print(DList* list);
void printReverse(DList* list);

void freeList(DList* list);
