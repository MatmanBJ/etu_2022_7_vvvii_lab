// https://stackoverflow.com/questions/32515585/xcode-error-null-5-duplicate-symbols-for-architecture-x86-64
// You are including not the header file (*.hpp),
// but the source file (*.cpp) into your main.
// As a consequence, all code is compiled twice and the symbols are duplicated.

#include <iostream>

#ifndef NODE_H
#define NODE_H

struct Node {
    Node(int hig);
    char** arr;
    int height;
    struct Node* left;
    struct Node* mid_left;
    struct Node* mid_right;
    struct Node* right;
    struct Node* parent;
};

#endif