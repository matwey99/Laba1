#pragma once
#include <string>
#include "slist.h"

struct Queue {
    FNode* head;
    FNode* tail;
};

Queue* createQueue();
void push(Queue* q, const std::string& value);
bool pop(Queue* q, std::string& result);
bool peek(Queue* q, std::string& result);
void print(Queue* q);
void freeQueue(Queue* q);
