def calculate_new_costs(items, factor):
    return [cost + (index + 1) * factor for index, cost in enumerate(items)]


def calculate_min_sum(items, count):
    return sum(sorted(items)[:count])


def max_souvenirs_and_min_cost(n, S, costs):
    left, right = 0, n
    while left < right:
        mid = (left + right + 1) // 2
        new_costs = calculate_new_costs(list(costs), mid)
        if calculate_min_sum(new_costs, mid) <= S:
            left = mid
        else:
            right = mid - 1
    ans = left
    return ans, calculate_min_sum(calculate_new_costs(costs, ans), ans)


n, S = map(int, input().split())
costs = list(map(int, input().split()))
k, T = max_souvenirs_and_min_cost(n, S, costs)
print(f"{k} {T}")
