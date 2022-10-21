#include <iostream>
#include "./node.h"
#include "./graph.h"
#include <SFML/Graphics.hpp>

using namespace sf;

// ---------- < Default Graph constructor > ----------
Graph::Graph()
{
    Node* startNode = new Node(0);
    Node* endNode = new Node(0);

    startNode -> elements[0][0] = ' ';
    startNode -> elements[0][1] = '4';
    startNode -> elements[0][2] = '3';
    startNode -> elements[1][0] = '6';
    startNode -> elements[1][1] = '2';
    startNode -> elements[1][2] = '1';
    startNode -> elements[2][0] = '7';
    startNode -> elements[2][1] = '5';
    startNode -> elements[2][2] = '8';

    // ^^^^^^^^^ //
    // ^ - 4 3 ^ //
    // ^^^^^^^^^ //
    // ^ 6 2 1 ^ //
    // ^^^^^^^^^ //
    // ^ 7 5 8 ^ //
    // ^^^^^^^^^ //

    endNode -> elements[0][0] = '1';
    endNode -> elements[0][1] = '2';
    endNode -> elements[0][2] = '3';
    endNode -> elements[1][0] = '4';
    endNode -> elements[1][1] = ' ';
    endNode -> elements[1][2] = '5';
    endNode -> elements[2][0] = '6';
    endNode -> elements[2][1] = '7';
    endNode -> elements[2][2] = '8';

    // ^^^^^^^^^ //
    // ^ 1 2 3 ^ //
    // ^^^^^^^^^ //
    // ^ 4 - 5 ^ //
    // ^^^^^^^^^ //
    // ^ 6 7 8 ^ //
    // ^^^^^^^^^ //

    root = startNode;
    end = endNode;
}

// ---------- < Default Graph destructor > ----------
Graph::~Graph()
{
    DestroyNode(root);
}

// ---------- < Funtion for destroy node of graph > ----------
void Graph::DestroyNode(Node* node)
{
    if (node)
    {
        DestroyNode(node->left);
        DestroyNode(node->up);
        DestroyNode(node->down);
        DestroyNode(node->right);
        delete node;
    }
}

// --------------------------------------------------
// ---------- <<< ALGORITHMS SEARCHING >>> ----------
// --------------------------------------------------

// ---------- < DFS DEPTH > ----------
Node* Graph::dfs(int* local_nodes_steps, int choose)
{
    Node* local_node =  new Node(0);
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    priority_queue.push(root);
    //list_allPath.push_front(root);
    local_node = root;

    /*----------------------------------------------RENDERING------------------------------------------------*/
    RenderWindow window(VideoMode(300, 300), "My window");
    this->RenderLoad(local_node);
    /*----------------------------------------------RENDERING------------------------------------------------*/

    while (!priority_queue.empty())
    {
        //local_node = *(list_allPath.begin());
        local_node = priority_queue.top();
        priority_queue.pop();
        //list_allPath.pop_front();
        this->uncoverNodes(local_node, local_nodes_steps, false, choose);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;

        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->down), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->up), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }

        /*----------------------------------------------RENDERING------------------------------------------------*/
        if (local_node != nullptr) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            this->RenderUpdate(local_node);
            window.clear(Color::Yellow);
            this->RenderDraw(window);
            window.display();
        }
        /*----------------------------------------------RENDERING------------------------------------------------*/
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT > ----------
Node* Graph::iterativeDFS(int restriction, int* local_nodes_steps, int choose)
{
    Node* local_node = new Node(0);
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    //list_allPath.push_front(root);
    priority_queue.push(root);
    local_node = root;
    uncoverNodes(local_node, local_nodes_steps, false, choose);

    /*----------------------------------------------RENDERING------------------------------------------------*/
    RenderWindow window(VideoMode(300, 300), "My window");
    this->RenderLoad(local_node);
    /*----------------------------------------------RENDERING------------------------------------------------*/

    while (!priority_queue.empty())
    {
        //local_node = *(list_allPath.begin());
        local_node = priority_queue.top();
        priority_queue.pop();
        //list_allPath.pop_front();
        uncoverNodes(local_node, local_nodes_steps, false, choose);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;

        /*----------------------------------------------RENDERING------------------------------------------------*/
        if (local_node != nullptr) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            this->RenderUpdate(local_node);
            window.clear(Color::Yellow);
            this->RenderDraw(window);
            window.display();
        }
        /*----------------------------------------------RENDERING------------------------------------------------*/

        // https://cplusplus.com/doc/tutorial/operators/
        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->down), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->up), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
    }
    return nullptr;
}

// ---------- < DFS DEPTH BY STEPS > ----------
Node* Graph::dfsBySteps(int* local_nodes_steps, int choose)
{
    Node* local_node = new Node(0);
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    priority_queue.push(root);
    list_allPath.push_front(root);
    local_node = root;
    printDataPath(priority_queue);

    cout << "Press enter to next step...";
    fflush(stdin);
    getchar();

    /*----------------------------------------------RENDERING------------------------------------------------*/
    RenderWindow window(VideoMode(300, 300), "My window");
    this->RenderLoad(local_node);
    /*----------------------------------------------RENDERING------------------------------------------------*/

    while (!priority_queue.empty())
    {
        //local_node = *(list_allPath.begin());
        local_node = priority_queue.top();
        priority_queue.pop();
        //list_allPath.pop_front();
        cout << "\n---------- BEGIN OF STEP ----------\n";
        cout << "Revealed top:\n";
        printMatixNode(local_node);
        cout << "Revealed vertices in this step:\n";
        uncoverNodes(local_node, local_nodes_steps, true, choose);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;
        printDataNode(local_node);

        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->down), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->up), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }

        printDataPath(priority_queue);

        local_node = priority_queue.top();
        cout << "Prioritet: " << local_node->priority << endl;

        cout << "---------- END OF STEP ----------\n\n";
        cout << "Press enter to next step...";

        /*----------------------------------------------RENDERING------------------------------------------------*/
        if (local_node != nullptr) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            this->RenderUpdate(local_node);
            window.clear(Color::Yellow);
            this->RenderDraw(window);
            window.display();
        }
        /*----------------------------------------------RENDERING------------------------------------------------*/

        fflush(stdin);
        getchar();
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT BY STEPS > ----------
Node* Graph::iterativeDFSBySteps(int restriction, int* local_nodes_steps, int choose)
{
    Node* local_node = new Node(0);
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    priority_queue.push(root);
    //list_allPath.push_front(root);
    local_node = root;
    printDataPath(priority_queue);

    cout << "Press enter to next step...";
    fflush(stdin);
    getchar();

    /*----------------------------------------------RENDERING------------------------------------------------*/
    RenderWindow window(VideoMode(300, 300), "My window");
    this->RenderLoad(local_node);
    /*----------------------------------------------RENDERING------------------------------------------------*/

    while (!priority_queue.empty()) {
        //local_node = *(list_allPath.begin());
        local_node = priority_queue.top();
        priority_queue.pop();
        //list_allPath.pop_front();
        cout << "\n---------- BEGIN OF STEP ----------\n";
        cout << "Revealed top: " << endl;
        printMatixNode(local_node);

        cout << "Revealed vertices in this step: " << endl;
        uncoverNodes(local_node, local_nodes_steps, true, choose);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;
        printDataNode(local_node);

        local_returned_node = this->end_or_again_or_else(&(local_node->right), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else(&(local_node->down), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else(&(local_node->up), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else(&(local_node->left), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }

        printDataPath(priority_queue);
        if(!priority_queue.empty())
            local_node = priority_queue.top();
        cout << "Prioritet: " << local_node->priority << endl;

        cout << "---------- END OF STEP ----------\n\n";
        cout << "Press enter to next step...";

        /*----------------------------------------------RENDERING------------------------------------------------*/
        if (local_node != nullptr) {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
            this->RenderUpdate(local_node);
            window.clear(Color::Yellow);
            this->RenderDraw(window);
            window.display();
        }
        /*----------------------------------------------RENDERING------------------------------------------------*/

        fflush(stdin);
        getchar();
    }
    return nullptr;
}

// --------------------------------------------------
// ---------- <<< OTHER FUNTIONS >>> ----------
// --------------------------------------------------

// ---------- < REPEAT NODES > ----------
bool Graph::check_repeatNodes(Node* local_node) {
    if (unsetDataNodes.find(getString(local_node)) == unsetDataNodes.end()) {
        return true;
    }
    else {
        return false;
    }

}

// ---------- < COMPARE NODES > ----------
bool Graph::compareNodes(Node* local_node) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (local_node->elements[i][j] == end->elements[y][x]) {
                        if (i != y || j != x) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

// ---------- < PRINT DATA NODE> ----------
void Graph::printDataNode(Node* local_node) {
    if (local_node->left != nullptr) {
        printMatixNode(local_node->left);
    }
    if (local_node->up != nullptr) {
        printMatixNode(local_node->up);
    }
    if (local_node->down != nullptr) {
        printMatixNode(local_node->down);
    }
    if (local_node->right != nullptr) {
        printMatixNode(local_node->right);
    }
}

// ---------- < PRINT ALL SUCCESS END STATES TO FINISH PATH > ----------
void Graph::printDataPath(Queue_p queue_prioritet) {
    Node* cur = new Node(0);
    cout << "Border content: " << endl;
    while (!queue_prioritet.empty())
    {
        cur = queue_prioritet.top();
        printMatixNode(cur);
        queue_prioritet.pop();
    }
}

// ---------- < PRINT ONLY NODE MATRIX > ----------
void Graph::printMatixNode(Node* local_node) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << local_node->elements[i][j] << " ";
            
        }
        cout << endl;
    }
    cout << endl;
}

// ---------- < GETSTRING > ----------
string Graph::getString(Node* local_node)
{
    string str;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            str.push_back((*local_node).elements[i][j]);
        }
    }
    return str;
}

// ---------- < Uncover Nodes > ----------
void Graph::uncoverNodes(Node* local_node, int* local_nodes_steps, bool local_steps_output, int choose)
{
    if(local_steps_output)cout << "\nMOVEMENT VARIANTS: ";
    int x, y;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((*local_node).elements[i][j] == ' ') {
                x = j;
                y = i;
                break;
            }
        }
    }
    if (x > 0) {
        if(local_steps_output)cout << "<- ";
        (*local_node).left = fillMatrixValues(local_node);
        (*local_node).left->elements[y][x] = (*local_node).left->elements[y][x - 1];
        (*local_node).left->elements[y][x - 1] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).left->parent = local_node;
    }
    if (x < 2) {
        if(local_steps_output)cout << "V ";
        (*local_node).down = fillMatrixValues(local_node);
        (*local_node).down->elements[y][x] = (*local_node).down->elements[y][x + 1];
        (*local_node).down->elements[y][x + 1] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).down->parent = local_node;
    }
    if (y > 0) {
        if(local_steps_output)cout << "^ ";
        (*local_node).up = fillMatrixValues(local_node);
        (*local_node).up->elements[y][x] = (*local_node).up->elements[y - 1][x];
        (*local_node).up->elements[y - 1][x] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).up->parent = local_node;
    }
    if (y < 2) {
        if(local_steps_output)cout << "-> ";
        (*local_node).right = fillMatrixValues(local_node);
        (*local_node).right->elements[y][x] = (*local_node).right->elements[y + 1][x];
        (*local_node).right->elements[y + 1][x] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).right->parent = local_node;
    }
    
    choiceOfHeuristic(local_node, choose); 
    if(local_steps_output)cout << "\n";
}

// ---------- < FILL MATRIX VALUES > ----------
Node* Graph::fillMatrixValues(Node* local_node)
{
    Node* NewNode = new Node(local_node->depth + 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*NewNode).elements[i][j] = (*local_node).elements[i][j];
        }
    }
    return NewNode;
}

// ---------- < COMPARING IF IT'S END, OR IF IT'S EXISTING NODE, OR IF IT'S NEW, BUT NOT THE END > ----------
Node* Graph::end_or_again_or_else (Node** local_node_pointer, int* local_nodes_steps, bool local_limit_check, bool local_steps_output)
{
    if (*local_node_pointer != nullptr && local_limit_check == true)
    {
        if (this->check_repeatNodes(*local_node_pointer))
        {
            if (this->compareNodes(*local_node_pointer))
            {
                cout << "End state found:\n";
                this->printMatixNode(*local_node_pointer);
                return *local_node_pointer;
            }
            if (local_steps_output == true)
            {
                cout << "The node has NOT been created before, including it to graph:\n";
                printMatixNode(*local_node_pointer);
            }
            this->unsetDataNodes.insert(getString(*local_node_pointer));
            this->priority_queue.push(*local_node_pointer);
            //this->list_allPath.push_front(*local_node_pointer);
            if (local_steps_output == true)
            {
                cout << "Number of UNIQUE nodes we created: " << local_nodes_steps[0] << "\n"; // UNIQUE means we don't count any of similar nodes
                cout << "Number of CURRENT step we passed: " << local_nodes_steps[1] << "\n\n";
            }
            return nullptr;
        }
        else
        {
            if (local_steps_output == true)
            {
                cout << "The node, that has been created before, created again:\n";
                printMatixNode(*local_node_pointer);
            }
            delete(*local_node_pointer);
            *local_node_pointer = nullptr;
            local_nodes_steps[0] = local_nodes_steps[0] - 1;
            if (local_steps_output == true)
            {
                cout << "Number of UNIQUE nodes we created: " << local_nodes_steps[0] << "\n"; // UNIQUE means we don't count any of similar nodes
                cout << "Number of CURRENT step we passed: " << local_nodes_steps[1] << "\n\n";
            }
            return *local_node_pointer;
        }
    }
    return nullptr;
}

//---------- < SELECT HEURISTIC LOGIC > ----------
void Graph::choiceOfHeuristic(Node* local_node, int choose) {
    if (choose == 1) {
        f_h1(local_node);
    }
    if (choose == 2) {
        f_h2(local_node);
    }
    if (choose == 3) {
        f_Ah1(local_node);
    }
    if (choose == 4) {
        f_Ah2(local_node);
    }
}

//---------- <COMPARE PRIORITY OF NODE FOR H1 > ----------
int Graph::compareH1(Node* local_node) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (local_node->elements[i][j] == end->elements[y][x] && local_node->elements[i][j] != ' ') {
                        if (i != y || j != x) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
}
//---------- <COMPARE PRIORITY OF NODE FOR H1 > ----------
int Graph::compareH2(Node* local_node) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (local_node->elements[i][j] == end->elements[y][x] && local_node->elements[i][j] != ' ') {
                        count = count + abs(i - y) + abs(j - x);
                    }
                }
            }
        }
    }
    return count;
}
//---------- < h1 LOGIC > ----------
void Graph::f_h1(Node* local_node) {
    if (local_node->left != nullptr) {
        local_node->left->priority = compareH1(local_node->left);
    }
    if (local_node->down != nullptr) {
        local_node->down->priority = compareH1(local_node->down);
    }
    if (local_node->up != nullptr) {
        local_node->up->priority = compareH1(local_node->up);
    }
    if (local_node->right != nullptr) {
        local_node->right->priority = compareH1(local_node->right);
    }
}
//---------- < h2 LOGIC > ----------
void Graph::f_h2(Node* local_node) {
    if (local_node->left != nullptr) {
        local_node->left->priority = compareH2(local_node->left);
    }
    if (local_node->down != nullptr) {
        local_node->down->priority = compareH2(local_node->down);
    }
    if (local_node->up != nullptr) {
        local_node->up->priority = compareH2(local_node->up);
    }
    if (local_node->right != nullptr) {
        local_node->right->priority  = compareH2(local_node->right);
    }
}
//---------- <COMPARE PRIORITY OF NODE FOR A* H1 > ----------
int Graph::compareAH1(Node* cur) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (cur->elements[i][j] == end->elements[y][x] && cur->elements[i][j] != ' ') {
                        if (i != y || j != x) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return (count + cur->depth);
}
//---------- <COMPARE PRIORITY OF NODE FOR A* H2 > ----------
int Graph::compareAH2(Node* cur) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (cur->elements[i][j] == end->elements[y][x] && cur->elements[i][j] != ' ') {
                        count = count + abs(i - y) + abs(j - x);
                    }
                }
            }
        }
    }
    return (count + cur->depth);
}
//---------- <A* h1 LOGIC > ----------
void Graph::f_Ah1(Node* local_node) {
    if (local_node->left != nullptr) {
        local_node->left->priority = compareAH1(local_node->left);
    }
    if (local_node->down != nullptr) {
        local_node->down->priority = compareAH1(local_node->down);
    }
    if (local_node->up != nullptr) {
        local_node->up->priority = compareAH1(local_node->up);
    }
    if (local_node->right != nullptr) {
        local_node->right->priority = compareAH1(local_node->right);
    }
}
//---------- <A* h2 LOGIC > ----------
void Graph::f_Ah2(Node* local_node) {
    if (local_node->left != nullptr) {
        local_node->left->priority = compareAH2(local_node->left);
    }
    if (local_node->down != nullptr) {
        local_node->down->priority = compareAH2(local_node->down);
    }
    if (local_node->up != nullptr) {
        local_node->up->priority = compareAH2(local_node->up);
    }
    if (local_node->right != nullptr) {
        local_node->right->priority = compareAH2(local_node->right);
    }
}

void Graph::RenderLoad(Node* local_node) 
{
    if (font.loadFromFile("Fonts/arial.ttf"))
    {
        cell_1.setFont(font);
        cell_2.setFont(font);
        cell_3.setFont(font);
        cell_4.setFont(font);
        cell_5.setFont(font);
        cell_6.setFont(font);
        cell_7.setFont(font);
        cell_8.setFont(font);
        cell_9.setFont(font);
    }
    else
    {
        std::cout << "Failed to load font" << std::endl;
    }

    cell_1s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_2s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_3s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_4s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_5s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_6s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_7s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_8s.setSize(sf::Vector2f(100.0f, 100.0f));
    cell_9s.setSize(sf::Vector2f(100.0f, 100.0f));

    cell_1.setCharacterSize(75);
    cell_2.setCharacterSize(75);
    cell_3.setCharacterSize(75);
    cell_4.setCharacterSize(75);
    cell_5.setCharacterSize(75);
    cell_6.setCharacterSize(75);
    cell_7.setCharacterSize(75);
    cell_8.setCharacterSize(75);
    cell_9.setCharacterSize(75);

    cell_1.setPosition(0, 0);
    cell_2.setPosition(100, 0);
    cell_3.setPosition(200, 0);
    cell_1s.setPosition(0, 0);
    cell_2s.setPosition(100, 0);
    cell_3s.setPosition(200, 0);

    cell_4.setPosition(0, 100);
    cell_5.setPosition(100, 100);
    cell_6.setPosition(200, 100);
    cell_4s.setPosition(0, 100);
    cell_5s.setPosition(100, 100);
    cell_6s.setPosition(200, 100);

    cell_7.setPosition(0, 200);
    cell_8.setPosition(100, 200);
    cell_9.setPosition(200, 200);
    cell_7s.setPosition(0, 200);
    cell_8s.setPosition(100, 200);
    cell_9s.setPosition(200, 200);

    line1.setSize(sf::Vector2f(300.0f, 5.0f));
    line1.setPosition(0, 100);
    line2.setSize(sf::Vector2f(300.0f, 5.0f));
    line2.setPosition(0, 200);
    line3.setSize(sf::Vector2f(300.0f, 5.0f));
    line3.rotate(90.0f);
    line3.setPosition(100, 0);
    line4.setSize(sf::Vector2f(300.0f, 5.0f));
    line4.rotate(90.0f);
    line4.setPosition(200, 0);
}
void Graph::RenderUpdate(Node* local_node)
{
    cell_1.setString(local_node->elements[0][0]);
    cell_2.setString(local_node->elements[0][1]);
    cell_3.setString(local_node->elements[0][2]);

    cell_4.setString(local_node->elements[1][0]);
    cell_5.setString(local_node->elements[1][1]);
    cell_6.setString(local_node->elements[1][2]);

    cell_7.setString(local_node->elements[2][0]);
    cell_8.setString(local_node->elements[2][1]);
    cell_9.setString(local_node->elements[2][2]);

    cell_1s.setFillColor(sf::Color::Black);
    cell_2s.setFillColor(sf::Color::Black);
    cell_3s.setFillColor(sf::Color::Black);
    cell_4s.setFillColor(sf::Color::Black);
    cell_5s.setFillColor(sf::Color::Black);
    cell_6s.setFillColor(sf::Color::Black);
    cell_7s.setFillColor(sf::Color::Black);
    cell_8s.setFillColor(sf::Color::Black);
    cell_9s.setFillColor(sf::Color::Black);

    if (local_node->elements[0][0] == ' ')
        cell_1s.setFillColor(sf::Color::Red);
    if (local_node->elements[0][1] == ' ')
        cell_2s.setFillColor(sf::Color::Red);
    if (local_node->elements[0][2] == ' ')
        cell_3s.setFillColor(sf::Color::Red);
    if (local_node->elements[1][0] == ' ')
        cell_4s.setFillColor(sf::Color::Red);
    if (local_node->elements[1][1] == ' ')
        cell_5s.setFillColor(sf::Color::Red);
    if (local_node->elements[1][2] == ' ')
        cell_6s.setFillColor(sf::Color::Red);
    if (local_node->elements[2][0] == ' ')
        cell_7s.setFillColor(sf::Color::Red);
    if (local_node->elements[2][1] == ' ')
        cell_8s.setFillColor(sf::Color::Red);
    if (local_node->elements[2][2] == ' ')
        cell_9s.setFillColor(sf::Color::Red);
}

void Graph::RenderDraw(sf::RenderWindow& window)
{
    window.draw(cell_1s);
    window.draw(cell_2s);
    window.draw(cell_3s);
    window.draw(cell_4s);
    window.draw(cell_5s);
    window.draw(cell_6s);
    window.draw(cell_7s);
    window.draw(cell_8s);
    window.draw(cell_9s);

    window.draw(cell_1);
    window.draw(cell_2);
    window.draw(cell_3);
    window.draw(cell_4);
    window.draw(cell_5);
    window.draw(cell_6);
    window.draw(cell_7);
    window.draw(cell_8);
    window.draw(cell_9);

    window.draw(line1);
    window.draw(line2);
    window.draw(line3);
    window.draw(line4);
}