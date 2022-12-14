#include <list>
#include <unordered_set>
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    /*----------------------------------------CONSTRUCTOR AND DESTRUCTOR-----------------------------------*/
    Graph();
    ~Graph();
    /*----------------------------------------CONSTRUCTOR AND DESTRUCTOR-----------------------------------*/

    /*----------------------------------------ALGORITHMS-----------------------------------*/
    Node* dfs(int* local_nodes_steps);
    Node* iterativeDFS(int, int* local_nodes_steps);
    /*----------------------------------------ALGORITHMS-----------------------------------*/

    /*----------------------------------------ALGORITHMS STEPS-----------------------------------*/
    Node* dfsBySteps(int* local_nodes_steps);
    Node* iterativeDFSBySteps(int, int* local_nodes_steps);
    /*----------------------------------------ALGORITHMS STEPS-----------------------------------*/

    /*----------------------------------------FILLING VALUES AND WORK WITH NODES-----------------------------------*/
    Node* fillMatrixValues(Node* local_node);
    Node* end_or_again_or_else (Node** local_node_pointer, int* local_nodes_steps, bool local_limit_check, bool local_steps_output);
    bool compareNodes(Node* local_node);
    bool check_repeatNodes(Node* local_node);
    string getString(Node* local_node);
    void uncoverNodes(Node* local_node, int* local_nodes_steps, bool local_steps_output);
    void printDataNode(Node* local_node);
    void printMatixNode(Node* local_node);
    void printDataPath();
    /*----------------------------------------FILLING VALUES AND WORK WITH NODES-----------------------------------*/

    /*----------------------------------------RENDERING-----------------------------------*/
    void RenderLoad(Node* local_node);
    void RenderUpdate(Node* local_node);
    void RenderDraw(sf::RenderWindow&);
    /*----------------------------------------RENDERING-----------------------------------*/
    
    Node* root;
    Node* end;

private:
    static void DestroyNode(Node* node);
    typedef unordered_set<string> Dataset;
    typedef list<Node*> List;
    Dataset unsetDataNodes;
    List list_allPath;

    sf::Text cell_1, cell_2, cell_3;
    sf::Text cell_4, cell_5, cell_6;
    sf::Text cell_7, cell_8, cell_9;

    sf::RectangleShape cell_1s, cell_2s, cell_3s;
    sf::RectangleShape cell_4s, cell_5s, cell_6s;
    sf::RectangleShape cell_7s, cell_8s, cell_9s;

    sf::RectangleShape line1, line2, line3, line4;

    sf::Font font;
};

#endif