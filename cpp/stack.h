#pragma once
#include <string>
#include "slist.h"

// ---------- Стек на основе односвязного списка (префикс команд S) ----------

// Вершина стека — голова списка: push и pop работают с головой, O(1).
struct Stack {
    FNode* head;
};

Stack* createStack();
void push(Stack* s, const std::string& value);   // добавление (push)
bool pop(Stack* s, std::string& result);         // удаление (pop)
bool peek(Stack* s, std::string& result);        // чтение вершины без удаления
void print(Stack* s);
void freeStack(Stack* s);