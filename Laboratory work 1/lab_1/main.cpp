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

    Tree* graph = nullptr; // https://stackoverflow.com/questions/18940175/cannot-delete-stdvector-stdarray
    Tree tre;
    Node* result = new Node(0);
    Node* cur = new Node(0);
    int choose = 0;
    int restriction = 0;
    int* data = new int[2];
    data[0] = 0;
    data[1] = 0;
    cout << "Выберите пункт:" << endl;
    cout << "0 -- Exit\n";
    cout << "1 -- Depth-first search (DFS)\n";
    cout << "2 -- Iterative deepening depth-first search (IDDFS)\n";
    cout << "3 -- Depth-first search (DFS) STEPS\n";
    cout << "4 -- Iterative deepening depth-first search (IDDFS) STEPS\n";
    cout << "Other -- Default -- Depth-first search (DFS)\n";
    cin >> choose;

    graph = new Tree();

    switch (choose) // https://stackoverflow.com/questions/34829955/what-is-causing-this-cannot-jump-from-switch-statement-to-this-case-label
    {
    case 0: // nothing, exit
    {
        break;
    }
    case 1: // DFS
    {
        result = graph->contPreOrder(data);
        break;
    }
    case 2: // idDFS
    {
        cout << "Введите ограничение:" << endl;
        cin >> restriction;
        int local_number = 0;
        // NEED TO DELETE PREVIOUS RESULT ALLOCATION
        result = nullptr;
        while (result == nullptr && local_number <= restriction)
        {
            delete graph;
            graph = new Tree();
            cout << local_number << endl;
            result = graph->contPreOrderRestriction(local_number, data);
            local_number = local_number + 1;
            cout << "Количество созданных вершин: " << data[0] << endl;
            cout << "Количество шагов: " << data[1] << endl;
            data[0] = 0;
            data[1] = 0;
        }
        break;
    }
    case 3: // DFS steps
    {
        result = graph->contPreOrderBySteps(data);
        break;
    }
    case 4: // idDFS steps
    {
        // need to add
        break;
    }
    default: // default DFS
    {
        result = graph->contPreOrder(data);
        break;
    }
    }
    /*if (choose == 2)
    {
        cout << "Введите ограничение:" << endl;
        cin >> restriction;
        result = tre.contPreOrderRestriction(restriction, data);
    }
    if (choose == 4)
    {
        cout << "Введите ограничение:" << endl;
        cin >> restriction;
        result = tre.contPreOrderRestrictionBySteps(restriction, data);
    }*/
    // ADD NAME/DELETE OLD METHODS
    // UPDATE AND BUG FIX

    // ---------- FOUND PATH OUTPUT / NO FOUND PATH MESSAGE ----------

    cout << "Количество созданных вершин: " << data[0] << endl;
    cout << "Количество шагов: " << data[1] << endl;
    if (result != nullptr)
    {
        cout << "Итоговый путь:" << endl;
        cur = result;
        while (cur != nullptr)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    cout << cur->arr[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
            cur = cur->parent;
        }
    }
    else
    {
        cout << "Итоговый путь не найден.\n";
    }

    // ---------- END ----------

    delete graph;
    cout << "Press enter to exit...";
    fflush(stdin); // hahaha, classic...
    getchar(); // waiting enter
}