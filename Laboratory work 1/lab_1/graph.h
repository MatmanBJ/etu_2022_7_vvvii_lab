#include <./node.h>

// "error: redefinition of 'Node' '././node.h' included multiple times, additional include site here"
// https://stackoverflow.com/questions/3246803/why-use-ifndef-class-h-and-define-class-h-in-h-file-but-not-in-cpp
// https://stackoverflow.com/questions/14290026/linking-h-files-with-c-with-ifdef-header-guards
#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    Graph();
    ~Graph();
    Node* contPreOrder(int*);
    Node* contPreOrderRestriction(int, int*);
    Node* iterativeDeepingDFS(int restriction, int* data);
    Node* contPreOrderBySteps(int*);
    Node* contPreOrderRestrictionBySteps(int, int*);
    bool compare(Node*);
    bool repeat(Node*);
    void unlock(Node*, int*);
    string getString(Node*);
    Node* fillArr(Node*);
    void printData(Node*);
    void printArr(Node*);
    void printDataKaim();
    Node* root;
    Node* end;

private:
    static void DestroyNode(Node* node);
    Containers cont;
};

#endif