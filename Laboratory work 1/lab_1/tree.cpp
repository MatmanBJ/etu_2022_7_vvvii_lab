#include <iostream>
#include "./node.h"
#include "./tree.h"

Tree::Tree() // tree default constructor with given numbers
{
    Node* start = new Node(0);
    Node* enda = new Node(0);
    (*start).arr[0][0] = '6';
    (*start).arr[0][1] = '3';
    (*start).arr[0][2] = '4';
    (*start).arr[1][0] = '2';
    (*start).arr[1][1] = '5';
    (*start).arr[1][2] = '8';
    (*start).arr[2][0] = '7';
    (*start).arr[2][1] = '1';
    (*start).arr[2][2] = ' ';
    (*enda).arr[0][0] = ' ';
    (*enda).arr[0][1] = '1';
    (*enda).arr[0][2] = '2';
    (*enda).arr[1][0] = '3';
    (*enda).arr[1][1] = '4';
    (*enda).arr[1][2] = '5';
    (*enda).arr[2][0] = '6';
    (*enda).arr[2][1] = '7';
    (*enda).arr[2][2] = '8';
    root = start;
    end = enda;
}

Tree::~Tree() // tree default destructor
{
    DestroyNode(root);
}

void Tree::DestroyNode(Node* node) // tree destroyng node method
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

Node* Tree::contPreOrder(int* data) // in-depth method
{
    Node* cur;
    cout << "Начальное состояние:" << endl;
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
                    cout << "Найдено конечное состояние:" << endl;
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
                    cout << "Найдено конечное состояние:" << endl;
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
                    cout << "Найдено конечное состояние:" << endl;
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
                    cout << "Найдено конечное состояние:" << endl;
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

Node* Tree::contPreOrderRestriction(int restriction, int* data) // in-depth method w/ restriction
{
    Node* cur;
    cout << "Начальное состояние:" << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    cur = root;
    while (!cont.list.empty()) {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        unlock(cur, data);
        data[1] = data[1] + 1;
        if (cur->right != nullptr && cur->height < restriction) {
            if (repeat(cur->right)) {
                if (compare(cur->right)) {
                    cout << "Найдено конечное состояние:" << endl;
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
        if (cur->mid_right != nullptr && cur->height < restriction) {
            if (repeat(cur->mid_right)) {
                if (compare(cur->mid_right)) {
                    cout << "Найдено конечное состояние:" << endl;
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
        if (cur->mid_left != nullptr && cur->height < restriction) {
            if (repeat(cur->mid_left)) {
                if (compare(cur->mid_left)) {
                    cout << "Найдено конечное состояние:" << endl;
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
        if (cur->left != nullptr && cur->height < restriction) {
            if (repeat(cur->left)) {
                if (compare(cur->left)) {
                    cout << "Найдено конечное состояние:" << endl;
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

Node* Tree::contPreOrderBySteps(int* data) // in-depth method by steps
{
    Node* cur;
    cout << "Начальное состояние:" << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    cur = root;
    printDataKaim();
    system("pause");
    while (!cont.list.empty()) {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        cout << "Раскрываемая вершина:" << endl;
        printArr(cur);
        cout << "Раскрытые вершины на этом шаге:" << endl;
        unlock(cur, data);
        data[1] = data[1] + 1;
        printData(cur);
        if (cur->right != nullptr) {
            if (repeat(cur->right)) {
                if (compare(cur->right)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->right);
                    return cur->right;
                }
                cont.unset.insert(getString(cur->right));
                cont.list.push_front(cur->right);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
                printArr(cur->right);
                delete(cur->right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_right != nullptr) {
            if (repeat(cur->mid_right)) {
                if (compare(cur->mid_right)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->mid_right);
                    return cur->mid_right;
                }
                cont.unset.insert(getString(cur->mid_right));
                cont.list.push_front(cur->mid_right);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
                printArr(cur->mid_right);
                delete(cur->mid_right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_left != nullptr) {
            if (repeat(cur->mid_left)) {
                if (compare(cur->mid_left)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->mid_left);
                    return cur->mid_left;
                }
                cont.unset.insert(getString(cur->mid_left));
                cont.list.push_front(cur->mid_left);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
                printArr(cur->mid_left);
                delete(cur->mid_left);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->left != nullptr) {
            if (repeat(cur->left)) {
                if (compare(cur->left)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->left);
                    return cur->left;
                }
                cont.unset.insert(getString(cur->left));
                cont.list.push_front(cur->left);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
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

Node* Tree::contPreOrderRestrictionBySteps(int restriction, int* data) // in-depth method w/ restriction by steps
{
    Node* cur;
    cout << "Начальное состояние:" << endl;
    printArr(root);
    cont.unset.insert(getString(root));
    cont.list.push_front(root);
    cur = root;
    printDataKaim();
    system("pause");
    while (!cont.list.empty()) {
        cur = *(cont.list.begin());
        cont.list.pop_front();
        cout << "Раскрываемая вершина:" << endl;
        printArr(cur);
        cout << "Раскрытые вершины на этом шаге:" << endl;
        unlock(cur, data);
        data[1] = data[1] + 1;
        printData(cur);
        if (cur->right != nullptr && cur->height < restriction) {
            if (repeat(cur->right)) {
                if (compare(cur->right)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->right);
                    return cur->right;
                }
                cont.unset.insert(getString(cur->right));
                cont.list.push_front(cur->right);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
                printArr(cur->right);
                delete(cur->right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_right != nullptr && cur->height < restriction) {
            if (repeat(cur->mid_right)) {
                if (compare(cur->mid_right)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->mid_right);
                    return cur->mid_right;
                }
                cont.unset.insert(getString(cur->mid_right));
                cont.list.push_front(cur->mid_right);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
                printArr(cur->mid_right);
                delete(cur->mid_right);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->mid_left != nullptr && cur->height < restriction) {
            if (repeat(cur->mid_left)) {
                if (compare(cur->mid_left)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->mid_left);
                    return cur->mid_left;
                }
                cont.unset.insert(getString(cur->mid_left));
                cont.list.push_front(cur->mid_left);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
                printArr(cur->mid_left);
                delete(cur->mid_left);
                data[0] = data[0] - 1;
                cout << "////////////////" << endl;
            }
        }
        if (cur->left != nullptr && cur->height < restriction) {
            if (repeat(cur->left)) {
                if (compare(cur->left)) {
                    cout << "Найдено конечное состояние:" << endl;
                    printArr(cur->left);
                    return cur->left;
                }
                cont.unset.insert(getString(cur->left));
                cont.list.push_front(cur->left);
            }
            else {
                cout << "Найдено повторное состояние:" << endl;
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

bool Tree::repeat(Node* cur) {
    if (cont.unset.find(getString(cur)) == cont.unset.end()) {
        return true;
    }
    else {
        return false;
    }

}

bool Tree::compare(Node* cur) {
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
}

void Tree::printData(Node* cur) {
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

void Tree::printDataKaim() {
    list <Node*>::iterator iter;
    cout << "Содержание каймы:" << endl;
    for (iter = cont.list.begin(); iter != cont.list.end(); iter++) {
        printArr(*iter);
    }
}

void Tree::printArr(Node* cur) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << cur->arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

string Tree::getString(Node* cur)
{
    string str;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            str.push_back((*cur).arr[i][j]);
        }
    }
    return str;
}

void Tree::unlock(Node* cur, int* data)
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

Node* Tree::fillArr(Node* cur)
{
    Node* NewNode = new Node(cur->height + 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*NewNode).arr[i][j] = (*cur).arr[i][j];
        }
    }
    return NewNode;
}