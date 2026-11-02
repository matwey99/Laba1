#pragma once
#include <string>
#include "slist.h"

struct Stack {
    FNode* head;
};

Stack* createStack();
void push(Stack* s, const std::string& value);
bool pop(Stack* s, std::string& result);
bool peek(Stack* s, std::string& result);
void print(Stack* s);
void freeStack(Stack* s);
