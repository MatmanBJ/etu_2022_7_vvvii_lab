#include <iostream>
#include <unordered_set>
#include <list>
#include <SFML\Graphics.hpp>
#include <queue>

#ifndef NODE_H
#define NODE_H

using namespace std;

struct Node
{
public:
    Node(int local_depth);
    char** elements;
    int depth;
    struct Node* left;
    struct Node* up;
    struct Node* down;
    struct Node* right;
    struct Node* parent;
    static void finalPath(Node*);

    int priority;
};


#endif