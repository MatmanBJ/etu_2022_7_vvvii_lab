#include <iostream>
#include "./node.h"

Node::Node(int hig)
{
    height = hig;
    arr = new char* [3];
    for (int i = 0; i < 3; i++)
    {
        arr[i] = new char[3];
    }
    left = nullptr;
    mid_left = nullptr;
    mid_right = nullptr;
    right = nullptr;
    parent = nullptr;
}

void Node::thePath (Node* local_outcome)
{
    int i = 0;
    int j = 0;
    cout << "Here's the right path from the begin to the solution:\n";
    while (local_outcome != nullptr)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                cout << local_outcome->arr[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        local_outcome = local_outcome->parent;
    }
}