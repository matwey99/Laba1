#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "array.h"
#include "slist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "cbtree.h"
using namespace std;

struct Container {
    string name;
    char type;
    Array* arr;
    FList* flist;
    DList* dlist;
    Stack* stack;
    Queue* queue;
    CbTree* tree;
    Container* next;
};

struct Database {
    Container* head;
};

Container* findContainer(Database* db, const string& name) {
    Container* cur = db->head;
    while (cur != nullptr) {
        if (cur->name == name) return cur;
        cur = cur->next;
    }
    return nullptr;
}

Container* getOrCreate(Database* db, const string& name, char type) {
    Container* c = findContainer(db, name);
    if (c != nullptr) {
        if (c->type != type) return nullptr;
        return c;
    }
    c = new Container;
    c->name = name;
    c->type = type;
    c->arr = nullptr;
    c->flist = nullptr;
    c->dlist = nullptr;
    c->stack = nullptr;
    c->queue = nullptr;
    c->tree = nullptr;
    c->next = nullptr;
    if (type == 'M') c->arr = createArray();
    else if (type == 'F') c->flist = createFList();
    else if (type == 'L') c->dlist = createDList();
    else if (type == 'S') c->stack = createStack();
    else if (type == 'Q') c->queue = createQueue();
    else if (type == 'T') c->tree = createCbTree();

    if (db->head == nullptr) {
        db->head = c;
    } else {
        Container* last = db->head;
        while (last->next != nullptr) last = last->next;
        last->next = c;
    }
    return c;
}

Container* getExisting(Database* db, const string& name, char type) {
    Container* c = findContainer(db, name);
    if (c == nullptr || c->type != type) return nullptr;
    return c;
}

void freeDatabase(Database* db) {
    Container* cur = db->head;
    while (cur != nullptr) {
        Container* next = cur->next;
        if (cur->type == 'M') freeArray(cur->arr);
        else if (cur->type == 'F') freeList(cur->flist);
        else if (cur->type == 'L') freeList(cur->dlist);
        else if (cur->type == 'S') freeStack(cur->stack);
        else if (cur->type == 'Q') freeQueue(cur->queue);
        else if (cur->type == 'T') freeTree(cur->tree);
        delete cur;
        cur = next;
    }
    db->head = nullptr;
}

void loadFile(Database* db, const string& filename) {
    ifstream in(filename);
    if (!in.is_open()) return;
    string line;
    while (getline(in, line)) {
        istringstream ss(line);
        string typeStr, name, item;
        if (!(ss >> typeStr >> name)) continue;
        char type = typeStr[0];
        if (type != 'M' && type != 'F' && type != 'L' && type != 'S' && type != 'Q' && type != 'T') continue;
        Container* c = getOrCreate(db, name, type);
        if (c == nullptr) continue;
        while (ss >> item) {
            if (type == 'M') pushBack(c->arr, item);
            else if (type == 'F') pushBack(c->flist, item);
            else if (type == 'L') pushBack(c->dlist, item);
            else if (type == 'S') push(c->stack, item);
            else if (type == 'Q') push(c->queue, item);
            else if (type == 'T') insert(c->tree, item);
        }
    }
}

static void saveStackRec(FNode* node, ofstream& out) {
    if (node == nullptr) return;
    saveStackRec(node->next, out);
    out << " " << node->data;
}

static void saveTreeRec(CbTree* tree, ofstream& out) {
    for (int i = 0; i < tree->size; i++) {
        out << " " << tree->data[i];
    }
}

void saveFile(Database* db, const string& filename) {
    ofstream out(filename);
    Container* c = db->head;
    while (c != nullptr) {
        out << c->type << " " << c->name;
        if (c->type == 'M') {
            for (int i = 0; i < c->arr->size; i++) out << " " << c->arr->data[i];
        }
        else if (c->type == 'F') {
            for (FNode* cur = c->flist->head; cur != nullptr; cur = cur->next) out << " " << cur->data;
        }
        else if (c->type == 'L') {
            for (DNode* cur = c->dlist->head; cur != nullptr; cur = cur->next) out << " " << cur->data;
        }
        else if (c->type == 'S') {
            saveStackRec(c->stack->head, out);
        }
        else if (c->type == 'Q') {
            for (FNode* cur = c->queue->head; cur != nullptr; cur = cur->next) out << " " << cur->data;
        }
        else if (c->type == 'T') {
            saveTreeRec(c->tree, out);
        }
        out << endl;
        c = c->next;
    }
}

const int MAX_WORDS = 8;

void printError(const string& msg) {
    cout << "-> ERROR: " << msg << endl;
}

void printBool(bool ok) {
    cout << "-> " << (ok ? "TRUE" : "FALSE") << endl;
}

bool printResult(const string& value, bool ok, const string& errMsg) {
    if (ok) cout << "-> " << value << endl;
    else printError(errMsg);
    return ok;
}

bool runArray(Database* db, string* w, int n) {
    string cmd = w[0];
    if (n < 2) { printError("no name"); return false; }

    if (cmd == "MPUSH" && n == 3) {
        Container* c = getOrCreate(db, w[1], 'M');
        if (c == nullptr) { printError("name used by another type"); return false; }
        pushBack(c->arr, w[2]);
        cout << "-> " << w[2] << endl;
        return true;
    }
    if (cmd == "MINSERT" && n == 4) {
        Container* c = getOrCreate(db, w[1], 'M');
        if (c == nullptr) { printError("name used by another type"); return false; }
        int index = stoi(w[2]);
        return printResult(w[3], insertAt(c->arr, index, w[3]), "bad index");
    }

    Container* c = getExisting(db, w[1], 'M');
    if (c == nullptr) { printError("array not found"); return false; }

    if (cmd == "MLEN" && n == 2) {
        cout << "-> " << length(c->arr) << endl;
        return false;
    }
    if (n < 3) { printError("unknown command or wrong arguments"); return false; }
    int index = stoi(w[2]);

    if (cmd == "MGET" && n == 3) {
        string res;
        if (getAt(c->arr, index, res)) cout << "-> " << res << endl;
        else printError("bad index");
        return false;
    }
    if (cmd == "MSET" && n == 4) {
        return printResult(w[3], setAt(c->arr, index, w[3]), "bad index");
    }
    if (cmd == "MDEL" && n == 3) {
        return printResult("deleted", removeAt(c->arr, index), "bad index");
    }
    printError("unknown command or wrong arguments");
    return false;
}

bool runFList(Database* db, string* w, int n) {
    string cmd = w[0];
    if (n < 2) { printError("no name"); return false; }

    if ((cmd == "FPUSH" || cmd == "FPUSHTAIL" || cmd == "FPUSHHEAD") && n == 3) {
        Container* c = getOrCreate(db, w[1], 'F');
        if (c == nullptr) { printError("name used by another type"); return false; }
        if (cmd == "FPUSHHEAD") pushFront(c->flist, w[2]);
        else pushBack(c->flist, w[2]);
        cout << "-> " << w[2] << endl;
        return true;
    }

    Container* c = getExisting(db, w[1], 'F');
    if (c == nullptr) { printError("list not found"); return false; }
    string res;

    if (cmd == "FPUSHAFTER" && n == 4) {
        return printResult(w[3], pushAfter(c->flist, w[2], w[3]), "target not found");
    }
    if (cmd == "FPUSHBEFORE" && n == 4) {
        return printResult(w[3], pushBefore(c->flist, w[2], w[3]), "target not found");
    }
    if (cmd == "FDELHEAD" && n == 2) {
        string tmp;
        bool ok = popFront(c->flist, tmp);
        return printResult(tmp, ok, "list is empty");
    }
    if (cmd == "FDELTAIL" && n == 2) {
        string tmp;
        bool ok = popBack(c->flist, tmp);
        return printResult(tmp, ok, "list is empty");
    }
    if (cmd == "FDELAFTER" && n == 3) {
        bool ok = removeAfter(c->flist, w[2], res);
        if (!ok) printError("nothing to delete");
        else cout << "-> " << res << endl;
        return ok;
    }
    if (cmd == "FDELBEFORE" && n == 3) {
        bool ok = removeBefore(c->flist, w[2], res);
        if (!ok) printError("nothing to delete");
        else cout << "-> " << res << endl;
        return ok;
    }
    if (cmd == "FDEL" && n == 3) {
        bool ok = removeValue(c->flist, w[2]);
        printBool(ok);
        return ok;
    }
    if (cmd == "FGET" && n == 3) {
        if (getAt(c->flist, stoi(w[2]), res)) cout << "-> " << res << endl;
        else printError("bad index");
        return false;
    }
    if (cmd == "FFIND" && n == 3) {
        printBool(findNode(c->flist, w[2]) != nullptr);
        return false;
    }
    if (cmd == "FPRINTREV" && n == 2) {
        cout << "-> ";
        printReverse(c->flist);
        return false;
    }
    printError("unknown command or wrong arguments");
    return false;
}

bool runDList(Database* db, string* w, int n) {
    string cmd = w[0];
    if (n < 2) { printError("no name"); return false; }

    if ((cmd == "LPUSH" || cmd == "LPUSHTAIL" || cmd == "LPUSHHEAD") && n == 3) {
        Container* c = getOrCreate(db, w[1], 'L');
        if (c == nullptr) { printError("name used by another type"); return false; }
        if (cmd == "LPUSHHEAD") pushFront(c->dlist, w[2]);
        else pushBack(c->dlist, w[2]);
        cout << "-> " << w[2] << endl;
        return true;
    }

    Container* c = getExisting(db, w[1], 'L');
    if (c == nullptr) { printError("list not found"); return false; }
    string res;

    if (cmd == "LPUSHAFTER" && n == 4) {
        return printResult(w[3], pushAfter(c->dlist, w[2], w[3]), "target not found");
    }
    if (cmd == "LPUSHBEFORE" && n == 4) {
        return printResult(w[3], pushBefore(c->dlist, w[2], w[3]), "target not found");
    }
    if (cmd == "LDELHEAD" && n == 2) {
        string tmp;
        bool ok = popFront(c->dlist, tmp);
        return printResult(tmp, ok, "list is empty");
    }
    if (cmd == "LDELTAIL" && n == 2) {
        string tmp;
        bool ok = popBack(c->dlist, tmp);
        return printResult(tmp, ok, "list is empty");
    }
    if (cmd == "LDELAFTER" && n == 3) {
        bool ok = removeAfter(c->dlist, w[2], res);
        if (!ok) printError("nothing to delete");
        else cout << "-> " << res << endl;
        return ok;
    }
    if (cmd == "LDELBEFORE" && n == 3) {
        bool ok = removeBefore(c->dlist, w[2], res);
        if (!ok) printError("nothing to delete");
        else cout << "-> " << res << endl;
        return ok;
    }
    if (cmd == "LDEL" && n == 3) {
        bool ok = removeValue(c->dlist, w[2]);
        printBool(ok);
        return ok;
    }
    if (cmd == "LGET" && n == 3) {
        if (getAt(c->dlist, stoi(w[2]), res)) cout << "-> " << res << endl;
        else printError("bad index");
        return false;
    }
    if (cmd == "LFIND" && n == 3) {
        printBool(findNode(c->dlist, w[2]) != nullptr);
        return false;
    }
    if (cmd == "LPRINTREV" && n == 2) {
        cout << "-> ";
        printReverse(c->dlist);
        return false;
    }
    printError("unknown command or wrong arguments");
    return false;
}

bool runStack(Database* db, string* w, int n) {
    string cmd = w[0];
    if (cmd == "SPUSH" && n == 3) {
        Container* c = getOrCreate(db, w[1], 'S');
        if (c == nullptr) { printError("name used by another type"); return false; }
        push(c->stack, w[2]);
        cout << "-> " << w[2] << endl;
        return true;
    }
    if (cmd == "SPOP" && n == 2) {
        Container* c = getExisting(db, w[1], 'S');
        if (c == nullptr) { printError("stack not found"); return false; }
        string res;
        bool ok = pop(c->stack, res);
        return printResult(res, ok, "stack is empty");
    }
    if (cmd == "SGET" && n == 2) {
        Container* c = getExisting(db, w[1], 'S');
        if (c == nullptr) { printError("stack not found"); return false; }
        string res;
        bool ok = peek(c->stack, res);
        return printResult(res, ok, "stack is empty");
    }
    printError("unknown command or wrong arguments");
    return false;
}

bool runQueue(Database* db, string* w, int n) {
    string cmd = w[0];
    if (cmd == "QPUSH" && n == 3) {
        Container* c = getOrCreate(db, w[1], 'Q');
        if (c == nullptr) { printError("name used by another type"); return false; }
        push(c->queue, w[2]);
        cout << "-> " << w[2] << endl;
        return true;
    }
    if (cmd == "QPOP" && n == 2) {
        Container* c = getExisting(db, w[1], 'Q');
        if (c == nullptr) { printError("queue not found"); return false; }
        string res;
        bool ok = pop(c->queue, res);
        return printResult(res, ok, "queue is empty");
    }
    if (cmd == "QGET" && n == 2) {
        Container* c = getExisting(db, w[1], 'Q');
        if (c == nullptr) { printError("queue not found"); return false; }
        string res;
        bool ok = peek(c->queue, res);
        return printResult(res, ok, "queue is empty");
    }
    printError("unknown command or wrong arguments");
    return false;
}

bool runTree(Database* db, string* w, int n) {
    string cmd = w[0];
    if (cmd == "TINSERT" && n == 3) {
        Container* c = getOrCreate(db, w[1], 'T');
        if (c == nullptr) { printError("name used by another type"); return false; }
        if (search(c->tree, w[2])) { printError("value already exists"); return false; }
        insert(c->tree, w[2]);
        cout << "-> " << w[2] << endl;
        return true;
    }

    if (n < 2) { printError("no name"); return false; }
    Container* c = getExisting(db, w[1], 'T');
    if (c == nullptr) { printError("tree not found"); return false; }

    if ((cmd == "TGET" || cmd == "ISMEMBER") && n == 3) {
        printBool(search(c->tree, w[2]));
        return false;
    }
    if (cmd == "TISCOMPLETE" && n == 2) {
        printBool(isComplete(c->tree));
        return false;
    }
    if (cmd == "TISFULL" && n == 2) {
        printBool(isFull(c->tree));
        return false;
    }
    if (cmd == "TSIZE" && n == 2) {
        cout << "-> " << size(c->tree) << endl;
        return false;
    }
    if (n == 2 && (cmd == "TINORDER" || cmd == "TPREORDER" || cmd == "TPOSTORDER" || cmd == "TBFS")) {
        cout << "-> ";
        if (cmd == "TINORDER") inorder(c->tree);
        else if (cmd == "TPREORDER") preorder(c->tree);
        else if (cmd == "TPOSTORDER") postorder(c->tree);
        else bfs(c->tree);
        cout << endl;
        return false;
    }
    printError("unknown command or wrong arguments");
    return false;
}

void runPrint(Database* db, string* w, int n) {
    if (n != 2) { printError("usage: PRINT name"); return; }
    Container* c = findContainer(db, w[1]);
    if (c == nullptr) { printError("not found"); return; }
    if (c->type == 'M') { cout << "-> "; print(c->arr); }
    else if (c->type == 'F') { cout << "-> "; print(c->flist); }
    else if (c->type == 'L') { cout << "-> "; print(c->dlist); }
    else if (c->type == 'S') { cout << "-> "; print(c->stack); }
    else if (c->type == 'Q') { cout << "-> "; print(c->queue); }
    else if (c->type == 'T') { cout << "->" << endl; print(c->tree); }
}

bool execute(Database* db, const string& query) {
    string w[MAX_WORDS];
    int n = 0;
    istringstream ss(query);
    while (n < MAX_WORDS && ss >> w[n]) n++;
    if (n == 0) { printError("empty query"); return false; }

    string cmd = w[0];
    if (cmd == "PRINT") { runPrint(db, w, n); return false; }

    if (cmd == "ISMEMBER") return runTree(db, w, n);

    switch (cmd[0]) {
    case 'M': return runArray(db, w, n);
    case 'F': return runFList(db, w, n);
    case 'L': return runDList(db, w, n);
    case 'S': return runStack(db, w, n);
    case 'Q': return runQueue(db, w, n);
    case 'T': return runTree(db, w, n);
    }
    printError("unknown command");
    return false;
}

int main(int argc, char* argv[]) {
    string filename, query;
    for (int i = 1; i < argc - 1; i++) {
        string arg = argv[i];
        if (arg == "--file") filename = argv[i + 1];
        else if (arg == "--query") query = argv[i + 1];
    }
    if (filename.empty() || query.empty()) {
        cout << "Usage: ./dbms --file <file> --query '<COMMAND args>'" << endl;
        return 1;
    }

    Database db{nullptr};
    loadFile(&db, filename);

    bool changed = false;
    try {
        changed = execute(&db, query);
    } catch (const exception& e) {
        printError("number expected");
    }

    if (changed) saveFile(&db, filename);
    freeDatabase(&db);
    return 0;
}
