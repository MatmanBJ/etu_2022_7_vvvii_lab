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