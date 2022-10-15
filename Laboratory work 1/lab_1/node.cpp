#include <iostream>
#include "./node.h"

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