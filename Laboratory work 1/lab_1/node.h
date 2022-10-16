#include <iostream>
#include <unordered_set>
#include <list>

#ifndef NODE_H
#define NODE_H

using namespace std;

class Node
{
public:
    Node(int local_depth);
    char** elements;
    int depth;
    struct Node* left;
    struct Node* mid_left;
    struct Node* mid_right;
    struct Node* right;
    struct Node* parent;
    static void finalPath(Node*);
};

#endif