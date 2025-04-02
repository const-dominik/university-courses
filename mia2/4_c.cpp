#include <bits/stdc++.h>
#include <vector>

const int MAX_NODES = 200010;

int parent[MAX_NODES], res, root, visited[MAX_NODES];

std::vector<int> g[MAX_NODES];

void dfs(int node)
{
    visited[node] = 1;

    for (int i = 0; i < g[node].size(); i++)
    {
        int next = g[node][i];

        if (node == next)
        {
            if (root != node)
            {
                parent[node] = root;
                res++;
            }
        }

        else if (!visited[next])
        {
            dfs(next);
        }

        else if (visited[next] == 1)
        {
            res++;

            if (!root)
                root = node;

            parent[node] = root;
        }
    }

    visited[node] = 2;
}

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie();
    std::cout.tie();

    int numNodes;
    std::cin >> numNodes;

    for (int i = 1; i <= numNodes; i++)
    {
        std::cin >> parent[i];

        if (root == 0 && i == parent[i])
        {
            root = i;
        }

        g[i].push_back(parent[i]);
    }

    for (int i = 1; i <= numNodes; i++)
    {
        if (!(visited[i]))
        {
            dfs(i);
        }
    }

    std::cout << res << std::endl;

    for (int i = 1; i <= numNodes; i++)
        std::cout << parent[i] << ' ';

    return 0;
}