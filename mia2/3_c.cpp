#include <iostream>
#include <vector>
#include <algorithm>

std::vector<long long> calculate_shortest_path_sums(int n, std::vector<std::vector<long long>> &adjacency_matrix, std::vector<int> &removal_order)
{
    std::vector<long long> shortest_path_sums;
    std::vector<bool> is_removed(n + 1, true);
    std::reverse(removal_order.begin(), removal_order.end());

    for (auto vertex : removal_order)
    {
        long long current_sum = 0;
        is_removed[vertex] = false;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                adjacency_matrix[i][j] = std::min(
                    adjacency_matrix[i][j],
                    adjacency_matrix[i][vertex] + adjacency_matrix[vertex][j]);

                if (!is_removed[i] && !is_removed[j])
                {
                    current_sum += adjacency_matrix[i][j];
                }
            }
        }

        shortest_path_sums.push_back(current_sum);
    }

    std::reverse(shortest_path_sums.begin(), shortest_path_sums.end());
    return shortest_path_sums;
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<long long>> adjacency_matrix(n + 1, std::vector<long long>(n + 1));

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            std::cin >> adjacency_matrix[i][j];
        }
    }

    std::vector<int> removal_order(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> removal_order[i];
    }

    std::vector<long long> shortest_path_sums = calculate_shortest_path_sums(n, adjacency_matrix, removal_order);

    for (auto sum : shortest_path_sums)
    {
        std::cout << sum << " ";
    }

    return 0;
}