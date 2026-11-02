#pragma once
#include <string>

struct CbNode {
    std::string data;
};

struct CbTree {
    std::string* data;
    int size;
    int capacity;
};

CbTree* createCbTree();

bool insert(CbTree* tree, const std::string& value);

bool search(CbTree* tree, const std::string& value);

bool isComplete(CbTree* tree);

bool isFull(CbTree* tree);

int size(CbTree* tree);

void inorder(CbTree* tree);
void preorder(CbTree* tree);
void postorder(CbTree* tree);
void bfs(CbTree* tree);

void print(CbTree* tree);
void freeTree(CbTree* tree);
