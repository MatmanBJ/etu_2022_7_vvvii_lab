#include <iostream>
#include "./node.h"
#include "./graph.h"

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
        DestroyNode(node->mid_left);
        DestroyNode(node->mid_right);
        DestroyNode(node->right);
        delete node;
    }
}

// --------------------------------------------------
// ---------- <<< ALGORITHMS SEARCHING >>> ----------
// --------------------------------------------------

// ---------- < DFS DEPTH > ----------
Node* Graph::dfs(int* local_nodes_steps)
{
    Node* local_node;
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    list_allPath.push_front(root);
    local_node = root;

    while (!list_allPath.empty())
    {
        local_node = *(list_allPath.begin());
        list_allPath.pop_front();
        this->uncoverNodes(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;

        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_right), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_left), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, true, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT > ----------
Node* Graph::iterativeDFS(int restriction, int* local_nodes_steps)
{
    Node* local_node;
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    list_allPath.push_front(root);
    local_node = root;

    while (!list_allPath.empty())
    {
        local_node = *(list_allPath.begin());
        list_allPath.pop_front();
        uncoverNodes(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;

        // https://cplusplus.com/doc/tutorial/operators/
        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_right), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_left), local_nodes_steps, local_node->depth < restriction ? true : false, false); // swap possibility/moving possibility
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
Node* Graph::dfsBySteps(int* local_nodes_steps)
{
    Node* local_node;
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    list_allPath.push_front(root);
    local_node = root;
    printDataPath();

    cout << "Press enter to next step...";
    fflush(stdin);
    getchar();

    while (!list_allPath.empty())
    {
        local_node = *(list_allPath.begin());
        list_allPath.pop_front();
        cout << "\n---------- BEGIN OF STEP ----------\n";
        cout << "Revealed top:\n";
        printMatixNode(local_node);
        cout << "Revealed vertices in this step:\n";
        uncoverNodes(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;
        printDataNode(local_node);

        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_right), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_left), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, true, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }

        printDataPath();

        cout << "---------- END OF STEP ----------\n\n";
        cout << "Press enter to next step...";
        fflush(stdin);
        getchar();
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT BY STEPS > ----------
Node* Graph::iterativeDFSBySteps(int restriction, int* local_nodes_steps)
{
    Node* local_node;
    Node* local_returned_node = nullptr;
    cout << "Initial State:\n";
    printMatixNode(root);
    unsetDataNodes.insert(getString(root));
    list_allPath.push_front(root);
    local_node = root;
    printDataPath();

    cout << "Press enter to next step...";
    fflush(stdin);
    getchar();

    while (!list_allPath.empty()) {
        local_node = *(list_allPath.begin());
        list_allPath.pop_front();
        cout << "\n---------- BEGIN OF STEP ----------\n";
        cout << "Revealed top: " << endl;
        printMatixNode(local_node);
        cout << "Revealed vertices in this step: " << endl;
        uncoverNodes(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;
        printDataNode(local_node);

        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_right), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_left), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, local_node->depth < restriction ? true : false, true); // swap possibility/moving possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        
        printDataPath();

        cout << "---------- END OF STEP ----------\n\n";
        cout << "Press enter to next step...";
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
    if (local_node->mid_left != nullptr) {
        printMatixNode(local_node->mid_left);
    }
    if (local_node->mid_right != nullptr) {
        printMatixNode(local_node->mid_right);
    }
    if (local_node->right != nullptr) {
        printMatixNode(local_node->right);
    }
}

// ---------- < PRINT ALL SUCCESS END STATES TO FINISH PATH > ----------
void Graph::printDataPath() {
    List::iterator iter;
    cout << "Border content: " << endl;
    for (iter = list_allPath.begin(); iter != list_allPath.end(); iter++) {
        printMatixNode(*iter);
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
void Graph::uncoverNodes(Node* local_node, int* local_nodes_steps)
{
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
        (*local_node).left = fillMatrixValues(local_node);
        (*local_node).left->elements[y][x] = (*local_node).left->elements[y][x - 1];
        (*local_node).left->elements[y][x - 1] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).left->parent = local_node;
    }
    if (x < 2) {
        (*local_node).mid_right = fillMatrixValues(local_node);
        (*local_node).mid_right->elements[y][x] = (*local_node).mid_right->elements[y][x + 1];
        (*local_node).mid_right->elements[y][x + 1] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).mid_right->parent = local_node;
    }
    if (y > 0) {
        (*local_node).mid_left = fillMatrixValues(local_node);
        (*local_node).mid_left->elements[y][x] = (*local_node).mid_left->elements[y - 1][x];
        (*local_node).mid_left->elements[y - 1][x] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).mid_left->parent = local_node;
    }
    if (y < 2) {
        (*local_node).right = fillMatrixValues(local_node);
        (*local_node).right->elements[y][x] = (*local_node).right->elements[y + 1][x];
        (*local_node).right->elements[y + 1][x] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).right->parent = local_node;
    }
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
            this->list_allPath.push_front(*local_node_pointer);
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