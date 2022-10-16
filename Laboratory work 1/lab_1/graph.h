#include <./node.h>

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    Graph();
    ~Graph();
    Node* dfs(int* local_nodes_steps);
    Node* iterativeDFS(int, int* local_nodes_steps);
    
    Node* dfsBySteps(int* local_nodes_steps);
    Node* iterativeDFSBySteps(int, int* local_nodes_steps);

    bool compare(Node* local_node);
    bool repeat(Node* local_node);
    void unlock(Node* local_node, int* local_nodes_steps);
    string getString(Node* local_node);
    Node* fillArr(Node* local_node);
    Node* end_or_again_or_else (Node** local_node_pointer, int* local_nodes_steps, bool local_limit_check);
    void printData(Node* local_node);
    void printArr(Node* local_node);
    void printDataKaim();
    Node* root;
    Node* end;

private:
    static void DestroyNode(Node* node);
    Containers cont;
};

#endif