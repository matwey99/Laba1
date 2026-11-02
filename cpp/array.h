#pragma once
#include <string>

struct Array {
    std::string* data;
    int size;
    int capacity;
};

Array* createArray();
void pushBack(Array* arr, const std::string& value);
bool insertAt(Array* arr, int index, const std::string& value);
bool getAt(Array* arr, int index, std::string& result);
bool setAt(Array* arr, int index, const std::string& value);
bool removeAt(Array* arr, int index);
int length(Array* arr);
void print(Array* arr);
void freeArray(Array* arr);
