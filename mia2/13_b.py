def calculate_prefix_sum(array):
    prefix_sum = [0, array[0]]
    for i in range(1, len(array)):
        prefix_sum.append(prefix_sum[i] + array[i])
    return prefix_sum


num_stones = int(input())
stone_costs = list(map(int, input().split()))

sorted_prefix_sum = calculate_prefix_sum(sorted(stone_costs))
original_prefix_sum = calculate_prefix_sum(stone_costs)

num_queries = int(input())

for _ in range(num_queries):
    query_type, left, right = map(int, input().split())
    if query_type == 1:
        print(original_prefix_sum[right] - original_prefix_sum[left - 1])
    else:
        print(sorted_prefix_sum[right] - sorted_prefix_sum[left - 1])
