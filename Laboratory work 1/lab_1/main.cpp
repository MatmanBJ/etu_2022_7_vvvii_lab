#include <iostream>
#include <stack>
#include <unordered_set>
#include <string>
#include <list>
#include "./node.h"
#include "./graph.h"

using namespace std;

int main()
{
    // ---------- BEGIN ----------

    // here we initializing variables, including main graph class & outcome node,
    // number of nodes created & steps passed.
    // also we get choosed algorithm option by user
    int algorithm_option = 0;
    int created_nodes_steps_passed[2];
    Graph* graph = nullptr; // https://stackoverflow.com/questions/18940175/cannot-delete-stdvector-stdarray
    Node* outcome = nullptr;

    cout << "Please, choose the target:\n"
    << "0 -- Exit\n"
    << "1 -- Depth-first search (DFS)\n"
    << "2 -- Iterative deepening depth-first search (IDDFS)\n"
    << "3 -- Depth-first search (DFS) STEPS\n"
    << "4 -- Iterative deepening depth-first search (IDDFS) STEPS\n"
    << "Other -- Default -- Depth-first search (DFS)\n";
    cin >> algorithm_option;

    created_nodes_steps_passed[0] = 0;
    created_nodes_steps_passed[1] = 0;
    graph = new Graph();

    // ---------- ALGORITHM ----------

    // here we doing the choosed algorithm option & showing created nodes & passed steps
    switch (algorithm_option) // https://stackoverflow.com/questions/34829955/what-is-causing-this-cannot-jump-from-switch-statement-to-this-case-label
    {
    case 0: // nothing, exit
    {
        break;
    }
    case 1: // DFS
    {
        outcome = graph->dfs(created_nodes_steps_passed);
        cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
        cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
        break;
    }
    case 2: // idDFS
    {
        int local_number = 0;
        while (outcome == nullptr)
        {
            delete graph;
            graph = new Graph();
            cout << "\n\nDepth: " << local_number << "\n";
            outcome = graph->iterativeDFS(local_number, created_nodes_steps_passed);
            local_number = local_number + 1;
            cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
            cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
            created_nodes_steps_passed[0] = 0;
            created_nodes_steps_passed[1] = 0;
        }
        break;
    }
    case 3: // DFS steps
    {
        outcome = graph->dfsBySteps(created_nodes_steps_passed);
        cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
        cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
        break;
    }
    case 4: // idDFS steps
    {
        // need to add
        cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
        cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
        break;
    }
    default: // default DFS
    {
        outcome = graph->dfs(created_nodes_steps_passed);
        cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
        cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
        break;
    }
    }

    // ---------- FOUND PATH OUTPUT / NO FOUND PATH MESSAGE ----------

    // if there is path, we ask user if he wants to see it (yes or no),
    // if he wants (y), we show it,
    // if he doesn't want (n/other), we don't show it.
    if (outcome != nullptr) // if outcome is not nullptr, print
    {
        char local_path = 'n';
        cout << "Do you want to see the path? [y=yes/n=no/other=no]";
        fflush(stdin);
        cin >> local_path;
        if (local_path == 'y')
        {
            Node::thePath(outcome);
        }
    }
    else
    {
        cout << "The path hasn't been found.\n";
    }

    // ---------- END ----------

    // here we are freeing the nodes allocated memory
    // (the nodes pointers are not freed because the has been
    // freed with graph pointer, it has it's own destructor)
    // and waiting user to press "enter" or something else
    // to sontinue and finish
    delete graph;
    cout << "Press enter to exit...";
    fflush(stdin);
    getchar();
}