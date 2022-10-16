#include <iostream>
#include "./node.h"
#include "./graph.h"

// ---------- < Default Graph constructor > ----------
Graph::Graph()
{
    Node* startNode = new Node(0);
    Node* endNode = new Node(0);

    (*startNode).elements[0][0] = ' ';
    (*startNode).elements[0][1] = '4';
    (*startNode).elements[0][2] = '3';
    (*startNode).elements[1][0] = '6';
    (*startNode).elements[1][1] = '2';
    (*startNode).elements[1][2] = '1';
    (*startNode).elements[2][0] = '7';
    (*startNode).elements[2][1] = '5';
    (*startNode).elements[2][2] = '8';

    // ^^^^^^^^^ //
    // ^ - 4 3 ^ //
    // ^^^^^^^^^ //
    // ^ 6 2 1 ^ //
    // ^^^^^^^^^ //
    // ^ 7 5 8 ^ //
    // ^^^^^^^^^ //

    (*endNode).elements[0][0] = '1';
    (*endNode).elements[0][1] = '2';
    (*endNode).elements[0][2] = '3';
    (*endNode).elements[1][0] = '4';
    (*endNode).elements[1][1] = ' ';
    (*endNode).elements[1][2] = '5';
    (*endNode).elements[2][0] = '6';
    (*endNode).elements[2][1] = '7';
    (*endNode).elements[2][2] = '8';

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
    printArr(root);
    cont.unset.insert(getString(root));
    (cont.list).push_front(root);
    local_node = root;

    while (!cont.list.empty())
    {
        local_node = *(cont.list.begin());
        cont.list.pop_front();
        this->unlock(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;

        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, true); // moving
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_right), local_nodes_steps, true); // swap possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_left), local_nodes_steps, true); // swap possibility
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, true); // moving
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
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    local_node = root;

    while (!cont.list.empty())
    {
        local_node = *(cont.list.begin());
        cont.list.pop_front();
        unlock(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;

        // https://cplusplus.com/doc/tutorial/operators/
        local_returned_node = this->end_or_again_or_else (&(local_node->right), local_nodes_steps, local_node->depth < restriction ? true : false);
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_right), local_nodes_steps, local_node->depth < restriction ? true : false);
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->mid_left), local_nodes_steps, local_node->depth < restriction ? true : false);
        if (local_returned_node != nullptr)
        {
            return local_returned_node;
        }
        local_returned_node = this->end_or_again_or_else (&(local_node->left), local_nodes_steps, local_node->depth < restriction ? true : false);
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
    cout << "Initial State:\n";
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    local_node = root;
    printDataKaim();
    system("pause");

    while (!cont.list.empty())
    {
        local_node = *(cont.list.begin());
        cont.list.pop_front();
        cout << "Revealed top: " << endl;
        printArr(local_node);
        cout << "Revealed vertices in this step: " << endl;
        unlock(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;
        printData(local_node);
        if (local_node->right != nullptr) {
            if (repeat(local_node->right)) {
                if (compare(local_node->right)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->right);
                    return local_node->right;
                }
                cont.unset.insert(getString(local_node->right));
                cont.list.push_front(local_node->right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->right);
                delete(local_node->right);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (local_node->mid_right != nullptr) {
            if (repeat(local_node->mid_right)) {
                if (compare(local_node->mid_right)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->mid_right);
                    return local_node->mid_right;
                }
                cont.unset.insert(getString(local_node->mid_right));
                cont.list.push_front(local_node->mid_right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->mid_right);
                delete(local_node->mid_right);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (local_node->mid_left != nullptr) {
            if (repeat(local_node->mid_left)) {
                if (compare(local_node->mid_left)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->mid_left);
                    return local_node->mid_left;
                }
                cont.unset.insert(getString(local_node->mid_left));
                cont.list.push_front(local_node->mid_left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->mid_left);
                delete(local_node->mid_left);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (local_node->left != nullptr) {
            if (repeat(local_node->left)) {
                if (compare(local_node->left)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->left);
                    return local_node->left;
                }
                cont.unset.insert(getString(local_node->left));
                cont.list.push_front(local_node->left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->left);
                delete(local_node->left);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        printDataKaim();
        system("pause");
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT BY STEPS > ----------
Node* Graph::iterativeDFSBySteps(int restriction, int* local_nodes_steps)
{
    Node* local_node;
    cout << "Initial State:\n";
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    local_node = root;
    printDataKaim();
    system("pause");

    while (!cont.list.empty()) {
        local_node = *(cont.list.begin());
        cont.list.pop_front();
        cout << "Revealed top: " << endl;
        printArr(local_node);
        cout << "Revealed vertices in this step: " << endl;
        unlock(local_node, local_nodes_steps);
        local_nodes_steps[1] = local_nodes_steps[1] + 1;
        printData(local_node);
        if (local_node->right != nullptr && local_node->depth < restriction) {
            if (repeat(local_node->right)) {
                if (compare(local_node->right)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->right);
                    return local_node->right;
                }
                cont.unset.insert(getString(local_node->right));
                cont.list.push_front(local_node->right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->right);
                delete(local_node->right);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (local_node->mid_right != nullptr && local_node->depth < restriction) {
            if (repeat(local_node->mid_right)) {
                if (compare(local_node->mid_right)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->mid_right);
                    return local_node->mid_right;
                }
                cont.unset.insert(getString(local_node->mid_right));
                cont.list.push_front(local_node->mid_right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->mid_right);
                delete(local_node->mid_right);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (local_node->mid_left != nullptr && local_node->depth < restriction) {
            if (repeat(local_node->mid_left)) {
                if (compare(local_node->mid_left)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->mid_left);
                    return local_node->mid_left;
                }
                cont.unset.insert(getString(local_node->mid_left));
                cont.list.push_front(local_node->mid_left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->mid_left);
                delete(local_node->mid_left);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (local_node->left != nullptr && local_node->depth < restriction) {
            if (repeat(local_node->left)) {
                if (compare(local_node->left)) {
                    cout << "End state found: " << endl;
                    printArr(local_node->left);
                    return local_node->left;
                }
                cont.unset.insert(getString(local_node->left));
                cont.list.push_front(local_node->left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(local_node->left);
                delete(local_node->left);
                local_nodes_steps[0] = local_nodes_steps[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        printDataKaim();
        system("pause");
    }
    return nullptr;
}

// --------------------------------------------------
// ---------- <<< OTHER FUNTIONS >>> ----------
// --------------------------------------------------

// ---------- < REPEAT NODES > ----------
bool Graph::repeat(Node* local_node) {
    if (cont.unset.find(getString(local_node)) == cont.unset.end()) {
        return true;
    }
    else {
        return false;
    }

}

// ---------- < COMPARE NODES > ----------
bool Graph::compare(Node* local_node) {
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
void Graph::printData(Node* local_node) {
    if (local_node->left != nullptr) {
        printArr(local_node->left);
    }
    if (local_node->mid_left != nullptr) {
        printArr(local_node->mid_left);
    }
    if (local_node->mid_right != nullptr) {
        printArr(local_node->mid_right);
    }
    if (local_node->right != nullptr) {
        printArr(local_node->right);
    }
}

// ---------- < PRINT ALL SUCCESS END STATES TO FINISH PATH > ----------
void Graph::printDataKaim() {
    list <Node*>::iterator iter;
    cout << "Border content: " << endl;
    for (iter = cont.list.begin(); iter != cont.list.end(); iter++) {
        printArr(*iter);
    }
}

// ---------- < PRINT ONLY NODE MATRIX > ----------
void Graph::printArr(Node* local_node) {
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

// ---------- < ??????????? > ----------
void Graph::unlock(Node* local_node, int* local_nodes_steps)
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
        (*local_node).left = fillArr(local_node);
        (*local_node).left->elements[y][x] = (*local_node).left->elements[y][x - 1];
        (*local_node).left->elements[y][x - 1] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).left->parent = local_node;
    }
    if (x < 2) {
        (*local_node).mid_right = fillArr(local_node);
        (*local_node).mid_right->elements[y][x] = (*local_node).mid_right->elements[y][x + 1];
        (*local_node).mid_right->elements[y][x + 1] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).mid_right->parent = local_node;
    }
    if (y > 0) {
        (*local_node).mid_left = fillArr(local_node);
        (*local_node).mid_left->elements[y][x] = (*local_node).mid_left->elements[y - 1][x];
        (*local_node).mid_left->elements[y - 1][x] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).mid_left->parent = local_node;
    }
    if (y < 2) {
        (*local_node).right = fillArr(local_node);
        (*local_node).right->elements[y][x] = (*local_node).right->elements[y + 1][x];
        (*local_node).right->elements[y + 1][x] = ' ';
        local_nodes_steps[0] = local_nodes_steps[0] + 1;
        (*local_node).right->parent = local_node;
    }
}

// ---------- < FILL MATRIX VALUES > ----------
Node* Graph::fillArr(Node* local_node)
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
Node* Graph::end_or_again_or_else (Node** local_node_pointer, int* local_nodes_steps, bool local_limit_check)
{
    if (*local_node_pointer != nullptr && local_limit_check == true)
    {
        if (this->repeat(*local_node_pointer))
        {
            if (this->compare(*local_node_pointer))
            {
                cout << "End state found:\n";
                this->printArr(*local_node_pointer);
                return *local_node_pointer;
            }
            this->cont.unset.insert(getString(*local_node_pointer));
            this->cont.list.push_front(*local_node_pointer);
            return nullptr;
        }
        else
        {
            delete(*local_node_pointer);
            *local_node_pointer = nullptr;
            local_nodes_steps[0] = local_nodes_steps[0] - 1;
            return *local_node_pointer;
        }
    }
    return nullptr;
}