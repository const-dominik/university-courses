from typing import List


def calculate_shortest_path_sums(n, adjacency_matrix, removal_order):
    shortest_path_sums = []
    is_removed = [True] * (n + 1)
    removal_order.reverse()

    for vertex in removal_order:
        current_sum = 0
        is_removed[vertex] = False

        for i in range(1, n + 1):
            for j in range(1, n + 1):
                adjacency_matrix[i][j] = min(
                    adjacency_matrix[i][j],
                    adjacency_matrix[i][vertex] + adjacency_matrix[vertex][j],
                )

                if not is_removed[i] and not is_removed[j]:
                    current_sum += adjacency_matrix[i][j]

        shortest_path_sums.append(current_sum)

    shortest_path_sums.reverse()
    return shortest_path_sums


n = int(input())
adjacency_matrix = [[0] * (n + 1) for _ in range(n + 1)]

for i in range(1, n + 1):
    adjacency_matrix[i][1 : n + 1] = map(int, input().split())

removal_order = list(map(int, input().split()))

shortest_path_sums = calculate_shortest_path_sums(n, adjacency_matrix, removal_order)

print(" ".join(map(str, shortest_path_sums)))
