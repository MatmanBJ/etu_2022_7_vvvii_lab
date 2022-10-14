#include <iostream>
#include <stack>
#include <unordered_set>
#include <string>
#include <list>

using namespace std;

struct Node {
    Node(int hig);
    char** arr;
    int height;
    struct Node* left;
    struct Node* mid_left;
    struct Node* mid_right;
    struct Node* right;
    struct Node* parent;
};

typedef unordered_set<string> Myset;
typedef list<Node*> List;

struct Containers {
    Myset unset;
    List list;
    List list_caim;
};

class Tree {
public:
    Tree();
    ~Tree();
    Node* contPreOrder(int*);
    Node* contPreOrderRestriction(int, int*);
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

Node::Node(int hig) {
    height = hig;
    arr = new char* [3];
    for (int i = 0; i < 3; i++) {
        arr[i] = new char[3];
    }
    left = nullptr;
    mid_left = nullptr;
    mid_right = nullptr;
    right = nullptr;
    parent = nullptr;
}

Tree::Tree() {
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

Tree::~Tree() {
    DestroyNode(root);
}

void Tree::DestroyNode(Node* node) {
    if (node) {
        DestroyNode(node->left);
        DestroyNode(node->mid_left);
        DestroyNode(node->mid_right);
        DestroyNode(node->right);
        delete node;
    }
}

Node* Tree::contPreOrder(int* data) {
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

Node* Tree::contPreOrderRestriction(int restriction, int* data) {
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

Node* Tree::contPreOrderBySteps(int* data) {
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

Node* Tree::contPreOrderRestrictionBySteps(int restriction, int* data) {
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

string Tree::getString(Node* cur) {
    string str;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            str.push_back((*cur).arr[i][j]);
        }
    }
    return str;
}

void Tree::unlock(Node* cur, int* data) {
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

Node* Tree::fillArr(Node* cur) {
    Node* NewNode = new Node(cur->height + 1);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            (*NewNode).arr[i][j] = (*cur).arr[i][j];
        }
    }
    return NewNode;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Tree tre;
    Node* result = new Node(0);
    Node* cur = new Node(0);
    int choose = 0;
    int restriction = 0;
    int* data = new int[2];
    data[0] = 0;
    data[1] = 0;
    cout << "Выберите пункт:" << endl;
    cout << "1 - Обход в глубину" << endl;
    cout << "2 - Обход в глубину с ограничением" << endl;
    cout << "3 - Обход в глубину по шагам" << endl;
    cout << "4 - Обход в глубину с ограничением по шагам" << endl;
    cin >> choose;
    if (choose == 1) {
       result = tre.contPreOrder(data);
    }
    if (choose == 2) {
        cout << "Введите ограничение:" << endl;
        cin >> restriction;
        result = tre.contPreOrderRestriction(restriction, data);
    }
    if (choose == 3) {
       result = tre.contPreOrderBySteps(data);
    }
    if (choose == 4) {
        cout << "Введите ограничение:" << endl;
        cin >> restriction;
        result = tre.contPreOrderRestrictionBySteps(restriction, data);
    }
    cout << "Количество созданных вершин: " << data[0] << endl;
    cout << "Количество шагов: " << data[1] << endl;
    if (result != nullptr) {
        cout << "Итоговый путь:" << endl;
        cur = result;
        while (cur != nullptr) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    cout << cur->arr[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cur = cur->parent;
        }
    }
    else {
        cout << "Итоговый путь не найден." << endl;
    }
    system("pause");
}