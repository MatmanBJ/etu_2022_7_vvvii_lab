#include <./node.h>
#include <list>
#include <unordered_set>

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

    Node* fillMatrixValues(Node* local_node);
    Node* end_or_again_or_else (Node** local_node_pointer, int* local_nodes_steps, bool local_limit_check, bool local_steps_output);

    bool compareNodes(Node* local_node);
    bool check_repeatNodes(Node* local_node);

    string getString(Node* local_node);
   
    void uncoverNodes(Node* local_node, int* local_nodes_steps);
    void printDataNode(Node* local_node);
    void printMatixNode(Node* local_node);
    void printDataPath();
    Node* root;
    Node* end;

private:
    static void DestroyNode(Node* node);
    typedef unordered_set<string> Dataset;
    typedef list<Node*> List;
    Dataset unsetDataNodes;
    List list_allPath;
};

#endif