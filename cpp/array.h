#pragma once
#include <string>

// ---------- Массив (префикс команд M) ----------

struct Array {
    std::string* data; // блок памяти, элементы лежат подряд
    int size;          // число занятых элементов
    int capacity;      // размер блока памяти
};

Array* createArray();
void pushBack(Array* arr, const std::string& value);                      // добавление в конец
bool insertAt(Array* arr, int index, const std::string& value);          // добавление по индексу
bool getAt(Array* arr, int index, std::string& result);                  // чтение по индексу
bool setAt(Array* arr, int index, const std::string& value);              // замена по индексу
bool removeAt(Array* arr, int index);                                     // удаление по индексу
int length(Array* arr);                                                   // длина массива
void print(Array* arr);
void freeArray(Array* arr);