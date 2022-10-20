#include <iostream>
#include <stack>
#include <unordered_set>
#include <string>
#include <list>
#include "./node.h"
#include "./graph.h"

#include <SFML\Graphics.hpp>
#define _HAS_ITERATOR_DEBUGGING 2
#define _ITERATOR_DEBUG_LEVEL 2

using namespace std;

int main()
{
        // ---------- BEGIN ----------

        // here we initializing variables, including main graph class & outcome node,
        // number of nodes created & steps passed.
        // also we get choosed algorithm option by user
        int algorithm_option = 0;
        int algorithm_settingsOption = 0;
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

        cout << "Please, choose algoritm settings:\n"
            << "0 -- Back\n"
            << "1 -- h1\n" //кол-во фишек не на своих местах
            << "2 -- h2\n" //манхэттенское расстояние
            << "3 -- A*(h1)\n"
            << "4 -- A*(h2)\n"
            << "Other -- Default -- h1\n";
        cin >> algorithm_settingsOption;

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
            graph->root->priority = 8;
            outcome = graph->dfs(created_nodes_steps_passed, algorithm_settingsOption);
            cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
            cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
            break;
        }
        case 2: // idDFS
        {
            graph->root->priority = 14;
            int local_number = 0;
            while (outcome == nullptr)
            {
                delete graph;
                graph = new Graph();
                cout << "\n\nDepth: " << local_number << "\n";
                outcome = graph->iterativeDFS(local_number, created_nodes_steps_passed, algorithm_settingsOption);
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
            graph->root->priority = 8;
            outcome = graph->dfsBySteps(created_nodes_steps_passed, algorithm_settingsOption);
            cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
            cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
            break;
        }
        case 4: // idDFS steps
        {
            graph->root->priority = 14;
            int local_number = 0;
            while (outcome == nullptr)
            {
                delete graph;
                graph = new Graph();
                cout << "\n\nDepth: " << local_number << "\n";
                outcome = graph->iterativeDFSBySteps(local_number, created_nodes_steps_passed, algorithm_settingsOption);
                local_number = local_number + 1;
                cout << "Nodes created: " << created_nodes_steps_passed[0] << "\n";
                cout << "Steps passed: " << created_nodes_steps_passed[1] << "\n";
                created_nodes_steps_passed[0] = 0;
                created_nodes_steps_passed[1] = 0;
            }
            break;
        }
        default: // default DFS
        {
            graph->root->priority = 8;
            outcome = graph->dfs(created_nodes_steps_passed, algorithm_settingsOption);
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
                Node::finalPath(outcome);
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