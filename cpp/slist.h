#pragma once
#include <string>

struct FNode {
    std::string data;
    FNode* next;
};

struct FList {
    FNode* head;
    FNode* tail;
};

FList* createFList();
FNode* findNode(FList* list, const std::string& value);

void pushFront(FList* list, const std::string& value);
void pushBack(FList* list, const std::string& value);
bool pushAfter(FList* list, const std::string& target, const std::string& value);
bool pushBefore(FList* list, const std::string& target, const std::string& value);

bool popFront(FList* list, std::string& result);
bool popBack(FList* list, std::string& result);
bool removeAfter(FList* list, const std::string& target, std::string& result);
bool removeBefore(FList* list, const std::string& target, std::string& result);
bool removeValue(FList* list, const std::string& value);

bool getAt(FList* list, int index, std::string& result);
void print(FList* list);
void printReverse(FList* list);

void freeList(FList* list);
