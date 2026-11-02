#include <iostream>
#include <string>
#include "cbtree.h"
using namespace std;

CbTree* createCbTree() {
    CbTree* tree = new CbTree;
    tree->capacity = 4;
    tree->size = 0;
    tree->data = new string[tree->capacity];
    return tree;
}

static void grow(CbTree* tree) {
    tree->capacity *= 2;
    string* newData = new string[tree->capacity];
    for (int i = 0; i < tree->size; i++) {
        newData[i] = tree->data[i];
    }
    delete[] tree->data;
    tree->data = newData;
}

// ---------- Вставка ----------

// Классический способ вставки в дерево полной структуры: обход по уровням слева направо,
// берём первый узел, у которого нет левого потомка, иначе — первый узел без правого
// потомка, и заполняем свободное место. В неявном представлении это и есть позиция size,
// поэтому вставка выполняется без обхода дерева, O(1) амортизированно.
bool insert(CbTree* tree, const string& value) {
    if (tree->size == tree->capacity) grow(tree);
    tree->data[tree->size] = value;
    tree->size++;
    return true;
}

// ---------- Поиск ----------

// Порядок элементов в полном дереве не задан (это не дерево поиска),
// поэтому единственный способ проверки наличия элемента — линейный просмотр, O(n).
bool search(CbTree* tree, const string& value) {
    for (int i = 0; i < tree->size; i++) {
        if (tree->data[i] == value) return true;
    }
    return false;
}

// ---------- Проверка структуры ----------

// Дерево полное (complete), если у каждого узла, у которого есть правый потомок,
// есть и левый. Иначе на последнем уровне окажется пропуск, и уровень
// окажется заполнен не подряд слева направо.
bool isComplete(CbTree* tree) {
    for (int i = 0; i < tree->size; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (right < tree->size && left >= tree->size) return false;
    }
    return true;
}

// Дерево полное бинарным (full), если у каждого узла либо нет потомков, либо есть оба.
bool isFull(CbTree* tree) {
    for (int i = 0; i < tree->size; i++) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        bool hasLeft = left < tree->size;
        bool hasRight = right < tree->size;
        if (hasLeft != hasRight) return false;
    }
    return true;
}

int size(CbTree* tree) {
    return tree->size;
}

// ---------- Обходы ----------

// Индексы потомков в неявном представлении: left(i) = 2*i+1, right(i) = 2*i+2.
static void inorderRec(CbTree* tree, int i) {
    if (i >= tree->size) return;
    inorderRec(tree, 2 * i + 1);
    cout << tree->data[i] << " ";
    inorderRec(tree, 2 * i + 2);
}

static void preorderRec(CbTree* tree, int i) {
    if (i >= tree->size) return;
    cout << tree->data[i] << " ";
    preorderRec(tree, 2 * i + 1);
    preorderRec(tree, 2 * i + 2);
}

static void postorderRec(CbTree* tree, int i) {
    if (i >= tree->size) return;
    postorderRec(tree, 2 * i + 1);
    postorderRec(tree, 2 * i + 2);
    cout << tree->data[i] << " ";
}

void inorder(CbTree* tree) { inorderRec(tree, 0); }
void preorder(CbTree* tree) { preorderRec(tree, 0); }
void postorder(CbTree* tree) { postorderRec(tree, 0); }

// Обход в ширину: элементы массива уже расположены в порядке обхода по уровням.
void bfs(CbTree* tree) {
    for (int i = 0; i < tree->size; i++) {
        cout << tree->data[i] << " ";
    }
}

// Иерархический вывод сверху вниз. Метка L/R явно показывает сторону потомка,
// в том числе когда у узла есть только один потомок.
static void printRec(CbTree* tree, int i, const string& prefix,
                     bool isLast, char side) {
    if (i >= tree->size) return;

    cout << prefix << (isLast ? "\\-- " : "|-- ")
         << side << ": " << tree->data[i] << endl;

    int left = 2 * i + 1;
    int right = 2 * i + 2;
    bool hasLeft = left < tree->size;
    bool hasRight = right < tree->size;
    string childPrefix = prefix + (isLast ? "    " : "|   ");

    if (hasLeft) printRec(tree, left, childPrefix, !hasRight, 'L');
    if (hasRight) printRec(tree, right, childPrefix, true, 'R');
}

void print(CbTree* tree) {
    if (tree->size == 0) { cout << "(empty)" << endl; return; }
    cout << tree->data[0] << endl;

    int left = 1;
    int right = 2;
    bool hasLeft = left < tree->size;
    bool hasRight = right < tree->size;
    if (hasLeft) printRec(tree, left, "", !hasRight, 'L');
    if (hasRight) printRec(tree, right, "", true, 'R');
}

void freeTree(CbTree* tree) {
    delete[] tree->data;
    delete tree;
}
