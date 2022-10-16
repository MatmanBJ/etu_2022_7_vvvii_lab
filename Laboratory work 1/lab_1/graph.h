#include <./node.h>

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    Graph();
    ~Graph();
    Node* dfs(int*);
    Node* iterativeDFS(int, int*);
    
    Node* dfsBySteps(int*);
    Node* iterativeDFSBySteps(int, int*);

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