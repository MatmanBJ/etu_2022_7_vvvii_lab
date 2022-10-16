#include <iostream>
#include "./node.h"
#include "./graph.h"

// ---------- < Default Graph constructor > ----------
Graph::Graph()
{
    Node* startNode = new Node(0);
    Node* endNode = new Node(0);

    (*startNode).arr[0][0] = ' ';
    (*startNode).arr[0][1] = '4';
    (*startNode).arr[0][2] = '3';
    (*startNode).arr[1][0] = '6';
    (*startNode).arr[1][1] = '2';
    (*startNode).arr[1][2] = '1';
    (*startNode).arr[2][0] = '7';
    (*startNode).arr[2][1] = '5';
    (*startNode).arr[2][2] = '8';

    // ^^^^^^^^^ //
    // ^ - 4 3 ^ //
    // ^^^^^^^^^ //
    // ^ 6 2 1 ^ //
    // ^^^^^^^^^ //
    // ^ 7 5 8 ^ //
    // ^^^^^^^^^ //

    (*endNode).arr[0][0] = '1';
    (*endNode).arr[0][1] = '2';
    (*endNode).arr[0][2] = '3';
    (*endNode).arr[1][0] = '4';
    (*endNode).arr[1][1] = ' ';
    (*endNode).arr[1][2] = '5';
    (*endNode).arr[2][0] = '6';
    (*endNode).arr[2][1] = '7';
    (*endNode).arr[2][2] = '8';

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
Node* Graph::dfs(int* data)
{
    Node* cur;
    cout << "Initial State: " << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    (cont.list).push_front(root);
    cur = root;

    while (!cont.list.empty()) {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        unlock(cur, data);
        data[1] = data[1] + 1;
        if (cur->right != nullptr) {
            if (repeat(cur->right)) {
                if (compare(cur->right)) {
                    cout << "End state found: " << endl;
                    printArr(cur->right);
                    return cur->right;
                }
                cont.unset.insert(getString(cur->right));
                cont.list.push_front(cur->right);
            }
            else {
                delete(cur->right);
                cur->right = nullptr;
                data[0] = data[0] - 1;
            }
        }
        if (cur->mid_right != nullptr) {
            if (repeat(cur->mid_right)) {
                if (compare(cur->mid_right)) {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_right);
                    return cur->mid_right;
                }
                cont.unset.insert(getString(cur->mid_right));
                cont.list.push_front(cur->mid_right);
            }
            else {
                delete(cur->mid_right);
                cur->mid_right = nullptr;
                data[0] = data[0] - 1;
            }
        }
        if (cur->mid_left != nullptr) {
            if (repeat(cur->mid_left)) {
                if (compare(cur->mid_left)) {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_left);
                    return cur->mid_left;
                }
                cont.unset.insert(getString(cur->mid_left));
                cont.list.push_front(cur->mid_left);
            }
            else {
                delete(cur->mid_left);
                cur->mid_left = nullptr;
                data[0] = data[0] - 1;
            }
        }
        if (cur->left != nullptr) {
            if (repeat(cur->left)) {
                if (compare(cur->left)) {
                    cout << "End state found: " << endl;
                    printArr(cur->left);
                    return cur->left;
                }
                cont.unset.insert(getString(cur->left));
                cont.list.push_front(cur->left);
            }
            else {
                delete(cur->left);
                cur->left = nullptr;
                data[0] = data[0] - 1;
            }
        }
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT > ----------
Node* Graph::iterativeDFS(int restriction, int* data)
{
    Node* cur;
    cout << "Initial State:" << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    cur = root;

    while (!cont.list.empty())
    {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        unlock(cur, data);
        data[1] = data[1] + 1;
        if (cur->right != nullptr && cur->height < restriction)
        {
            if (repeat(cur->right))
            {
                if (compare(cur->right))
                {
                    cout << "End state found:" << endl;
                    printArr(cur->right);
                    return cur->right;
                }
                cont.unset.insert(getString(cur->right));
                cont.list.push_front(cur->right);
            }
            else
            {
                delete(cur->right);
                cur->right = nullptr;
                data[0] = data[0] - 1;
            }
        }
        if (cur->mid_right != nullptr && cur->height < restriction)
        {
            if (repeat(cur->mid_right))
            {
                if (compare(cur->mid_right))
                {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_right);
                    return cur->mid_right;
                }
                cont.unset.insert(getString(cur->mid_right));
                cont.list.push_front(cur->mid_right);
            }
            else
            {
                delete(cur->mid_right);
                cur->mid_right = nullptr;
                data[0] = data[0] - 1;
            }
        }
        if (cur->mid_left != nullptr && cur->height < restriction)
        {
            if (repeat(cur->mid_left))
            {
                if (compare(cur->mid_left))
                {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_left);
                    return cur->mid_left;
                }
                cont.unset.insert(getString(cur->mid_left));
                cont.list.push_front(cur->mid_left);
            }
            else
            {
                delete(cur->mid_left);
                cur->mid_left = nullptr;
                data[0] = data[0] - 1;
            }
        }
        if (cur->left != nullptr && cur->height < restriction)
        {
            if (repeat(cur->left))
            {
                if (compare(cur->left))
                {
                    cout << "End state found: " << endl;
                    printArr(cur->left);
                    return cur->left;
                }
                cont.unset.insert(getString(cur->left));
                cont.list.push_front(cur->left);
            }
            else {
                delete(cur->left);
                cur->left = nullptr;
                data[0] = data[0] - 1;
            }
        }
    }
    return nullptr;
}

// ---------- < DFS DEPTH BY STEPS > ----------
Node* Graph::dfsBySteps(int* data)
{
    Node* cur;
    cout << "Initial State: " << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    cur = root;
    printDataKaim();
    system("pause");

    while (!cont.list.empty())
    {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        cout << "Revealed top: " << endl;
        printArr(cur);
        cout << "Revealed vertices in this step: " << endl;
        unlock(cur, data);
        data[1] = data[1] + 1;
        printData(cur);
        if (cur->right != nullptr) {
            if (repeat(cur->right)) {
                if (compare(cur->right)) {
                    cout << "End state found: " << endl;
                    printArr(cur->right);
                    return cur->right;
                }
                cont.unset.insert(getString(cur->right));
                cont.list.push_front(cur->right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->right);
                delete(cur->right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_right != nullptr) {
            if (repeat(cur->mid_right)) {
                if (compare(cur->mid_right)) {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_right);
                    return cur->mid_right;
                }
                cont.unset.insert(getString(cur->mid_right));
                cont.list.push_front(cur->mid_right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->mid_right);
                delete(cur->mid_right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_left != nullptr) {
            if (repeat(cur->mid_left)) {
                if (compare(cur->mid_left)) {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_left);
                    return cur->mid_left;
                }
                cont.unset.insert(getString(cur->mid_left));
                cont.list.push_front(cur->mid_left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->mid_left);
                delete(cur->mid_left);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->left != nullptr) {
            if (repeat(cur->left)) {
                if (compare(cur->left)) {
                    cout << "End state found: " << endl;
                    printArr(cur->left);
                    return cur->left;
                }
                cont.unset.insert(getString(cur->left));
                cont.list.push_front(cur->left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->left);
                delete(cur->left);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        printDataKaim();
        system("pause");
    }
    return nullptr;
}

// ---------- < DFS DEPTH LIMIT BY STEPS > ----------
Node* Graph::iterativeDFSBySteps(int restriction, int* data)
{
    Node* cur;
    cout << "Initial State: " << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    cur = root;
    printDataKaim();
    system("pause");

    while (!cont.list.empty()) {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        cout << "Revealed top: " << endl;
        printArr(cur);
        cout << "Revealed vertices in this step: " << endl;
        unlock(cur, data);
        data[1] = data[1] + 1;
        printData(cur);
        if (cur->right != nullptr && cur->height < restriction) {
            if (repeat(cur->right)) {
                if (compare(cur->right)) {
                    cout << "End state found: " << endl;
                    printArr(cur->right);
                    return cur->right;
                }
                cont.unset.insert(getString(cur->right));
                cont.list.push_front(cur->right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->right);
                delete(cur->right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_right != nullptr && cur->height < restriction) {
            if (repeat(cur->mid_right)) {
                if (compare(cur->mid_right)) {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_right);
                    return cur->mid_right;
                }
                cont.unset.insert(getString(cur->mid_right));
                cont.list.push_front(cur->mid_right);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->mid_right);
                delete(cur->mid_right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_left != nullptr && cur->height < restriction) {
            if (repeat(cur->mid_left)) {
                if (compare(cur->mid_left)) {
                    cout << "End state found: " << endl;
                    printArr(cur->mid_left);
                    return cur->mid_left;
                }
                cont.unset.insert(getString(cur->mid_left));
                cont.list.push_front(cur->mid_left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->mid_left);
                delete(cur->mid_left);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->left != nullptr && cur->height < restriction) {
            if (repeat(cur->left)) {
                if (compare(cur->left)) {
                    cout << "End state found: " << endl;
                    printArr(cur->left);
                    return cur->left;
                }
                cont.unset.insert(getString(cur->left));
                cont.list.push_front(cur->left);
            }
            else {
                cout << "Found duplicate state: " << endl;
                printArr(cur->left);
                delete(cur->left);
                data[0] = data[0] - 1;
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
bool Graph::repeat(Node* cur) {
    if (cont.unset.find(getString(cur)) == cont.unset.end()) {
        return true;
    }
    else {
        return false;
    }

}

// ---------- < COMPARE NODES > ----------
bool Graph::compare(Node* cur) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    if (cur->arr[i][j] == end->arr[y][x]) {
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
void Graph::printData(Node* cur) {
    if (cur->left != nullptr) {
        printArr(cur->left);
    }
    if (cur->mid_left != nullptr) {
        printArr(cur->mid_left);
    }
    if (cur->mid_right != nullptr) {
        printArr(cur->mid_right);
    }
    if (cur->right != nullptr) {
        printArr(cur->right);
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
void Graph::printArr(Node* cur) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << cur->arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ---------- < GETSTRING > ----------
string Graph::getString(Node* cur)
{
    string str;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            str.push_back((*cur).arr[i][j]);
        }
    }
    return str;
}

// ---------- < ??????????? > ----------
void Graph::unlock(Node* cur, int* data)
{
    int x, y;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((*cur).arr[i][j] == ' ') {
                x = j;
                y = i;
                break;
            }
        }
    }
    if (x > 0) {
        (*cur).left = fillArr(cur);
        (*cur).left->arr[y][x] = (*cur).left->arr[y][x - 1];
        (*cur).left->arr[y][x - 1] = ' ';
        data[0] = data[0] + 1;
        (*cur).left->parent = cur;
    }
    if (x < 2) {
        (*cur).mid_right = fillArr(cur);
        (*cur).mid_right->arr[y][x] = (*cur).mid_right->arr[y][x + 1];
        (*cur).mid_right->arr[y][x + 1] = ' ';
        data[0] = data[0] + 1;
        (*cur).mid_right->parent = cur;
    }
    if (y > 0) {
        (*cur).mid_left = fillArr(cur);
        (*cur).mid_left->arr[y][x] = (*cur).mid_left->arr[y - 1][x];
        (*cur).mid_left->arr[y - 1][x] = ' ';
        data[0] = data[0] + 1;
        (*cur).mid_left->parent = cur;
    }
    if (y < 2) {
        (*cur).right = fillArr(cur);
        (*cur).right->arr[y][x] = (*cur).right->arr[y + 1][x];
        (*cur).right->arr[y + 1][x] = ' ';
        data[0] = data[0] + 1;
        (*cur).right->parent = cur;
    }
}

// ---------- < FILL MATRIX VALUES > ----------
Node* Graph::fillArr(Node* cur)
{
    Node* NewNode = new Node(cur->height + 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*NewNode).arr[i][j] = (*cur).arr[i][j];
        }
    }
    return NewNode;
}