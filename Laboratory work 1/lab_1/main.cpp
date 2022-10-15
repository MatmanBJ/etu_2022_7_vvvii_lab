#include <iostream>
#include <stack>
#include <unordered_set>
#include <string>
#include <list>
#include "./node.h"
#include "./tree.h"

using namespace std;

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