#pragma once
#include <string>
#include "slist.h"

// ---------- Очередь на основе односвязного списка (префикс команд Q) ----------

// Добавление в хвост, извлечение из головы: FIFO (first in — first out).
struct Queue {
    FNode* head; // начало очереди, откуда забираем элемент
    FNode* tail; // конец очереди, куда добавляем элемент
};

Queue* createQueue();
void push(Queue* q, const std::string& value);   // добавление в конец
bool pop(Queue* q, std::string& result);          // извлечение из начала
bool peek(Queue* q, std::string& result);         // чтение первого элемента
void print(Queue* q);
void freeQueue(Queue* q);