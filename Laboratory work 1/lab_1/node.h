// https://stackoverflow.com/questions/32515585/xcode-error-null-5-duplicate-symbols-for-architecture-x86-64
// You are including not the header file (*.hpp),
// but the source file (*.cpp) into your main.
// As a consequence, all code is compiled twice and the symbols are duplicated.

#include <iostream>
#include <unordered_set>
#include <list>

#ifndef NODE_H
#define NODE_H

using namespace std;

struct Node
{
    Node(int hig);
    char** arr;
    int height;
    struct Node* left;
    struct Node* mid_left;
    struct Node* mid_right;
    struct Node* right;
    struct Node* parent;
    static void thePath(Node*);
};

typedef unordered_set<string> Myset;
typedef list<Node*> List;

struct Containers {
    Myset unset;
    List list;
    List list_caim;
};

#endif