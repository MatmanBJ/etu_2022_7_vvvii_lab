#include <iostream>
#include "./node.h"

Node::Node(int local_depth)
{
    depth = local_depth;
    elements = new char* [3];
    for (int i = 0; i < 3; i++)
    {
        elements[i] = new char[3];
    }
    left = nullptr;
    mid_left = nullptr;
    mid_right = nullptr;
    right = nullptr;
    parent = nullptr;
}

void Node::finalPath (Node* local_outcome)
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
                cout << local_outcome->elements[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        local_outcome = local_outcome->parent;
    }
}