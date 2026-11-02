#include <iostream>
#include <string>
#include "array.h"
using namespace std;

Array* createArray() {
    Array* arr = new Array;
    arr->capacity = 4;
    arr->size = 0;
    arr->data = new string[arr->capacity];
    return arr;
}

static void grow(Array* arr) {
    arr->capacity *= 2;
    string* newData = new string[arr->capacity];
    for (int i = 0; i < arr->size; i++) {
        newData[i] = arr->data[i];
    }
    delete[] arr->data;
    arr->data = newData;
}

void pushBack(Array* arr, const string& value) {
    if (arr->size == arr->capacity) grow(arr);
    arr->data[arr->size] = value;
    arr->size++;
}

bool insertAt(Array* arr, int index, const string& value) {
    if (index < 0 || index > arr->size) return false;
    if (arr->size == arr->capacity) grow(arr);
    for (int i = arr->size; i > index; i--) {
        arr->data[i] = arr->data[i - 1];
    }
    arr->data[index] = value;
    arr->size++;
    return true;
}

bool getAt(Array* arr, int index, string& result) {
    if (index < 0 || index >= arr->size) return false;
    result = arr->data[index];
    return true;
}

bool setAt(Array* arr, int index, const string& value) {
    if (index < 0 || index >= arr->size) return false;
    arr->data[index] = value;
    return true;
}

bool removeAt(Array* arr, int index) {
    if (index < 0 || index >= arr->size) return false;
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
    return true;
}

int length(Array* arr) {
    return arr->size;
}

void print(Array* arr) {
    cout << "[";
    for (int i = 0; i < arr->size; i++) {
        cout << arr->data[i];
        if (i < arr->size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

void freeArray(Array* arr) {
    delete[] arr->data;
    delete arr;
}
