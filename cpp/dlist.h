#pragma once
#include <string>

// ---------- Двусвязный список (префикс команд L) ----------

struct DNode {
    std::string data;
    DNode* prev; // указатель на предыдущий узел
    DNode* next; // указатель на следующий узел
};

struct DList {
    DNode* head;
    DNode* tail;
};

DList* createDList();
DNode* findNode(DList* list, const std::string& value);

// 4 способа добавления
void pushFront(DList* list, const std::string& value);
void pushBack(DList* list, const std::string& value);
bool pushAfter(DList* list, const std::string& target, const std::string& value);
bool pushBefore(DList* list, const std::string& target, const std::string& value);

// общий помощник: отключает узел от соседей и освобождает память
void unlink(DList* list, DNode* node);

// 4 способа удаления
bool popFront(DList* list, std::string& result);   // из начала за O(1)
bool popBack(DList* list, std::string& result);    // из конца за O(1)
bool removeAfter(DList* list, const std::string& target, std::string& result);
bool removeBefore(DList* list, const std::string& target, std::string& result);
bool removeValue(DList* list, const std::string& value);

// чтение
bool getAt(DList* list, int index, std::string& result);
void print(DList* list);
void printReverse(DList* list);

void freeList(DList* list);