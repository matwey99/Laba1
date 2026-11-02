#pragma once
#include <string>

// ---------- Односвязный список (префикс команд F) ----------

struct FNode {
    std::string data;
    FNode* next; // указатель на следующий узел; у последнего узла next = nullptr
};

struct FList {
    FNode* head;
    FNode* tail; // для добавления в конец за O(1)
};

FList* createFList();
FNode* findNode(FList* list, const std::string& value);

// 4 способа добавления
void pushFront(FList* list, const std::string& value);                             // в начало
void pushBack(FList* list, const std::string& value);                              // в конец
bool pushAfter(FList* list, const std::string& target, const std::string& value);  // после элемента
bool pushBefore(FList* list, const std::string& target, const std::string& value); // перед элементом

// 4 способа удаления
bool popFront(FList* list, std::string& result);                      // из начала
bool popBack(FList* list, std::string& result);                       // из конца
bool removeAfter(FList* list, const std::string& target, std::string& result);
bool removeBefore(FList* list, const std::string& target, std::string& result);
bool removeValue(FList* list, const std::string& value);              // удаление по значению

// чтение
bool getAt(FList* list, int index, std::string& result);  // по индексу
void print(FList* list);                                  // от головы к хвосту
void printReverse(FList* list);                           // от хвоста к голове

void freeList(FList* list);