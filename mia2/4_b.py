def calculate_time(n, a, l):
    i = 0
    time = 0
    while i < n:
        while i < n and a[i] <= l:
            i += 1
        if i == n:
            break
        time += 1
        while i < n and a[i] > l:
            i += 1
    return time


def process_queries(m, a, l, time):
    results = []
    for _ in range(m):
        query = input()
        if query == "0":
            results.append(str(time))
            continue
        query_type, hairline, growth = map(int, query.split())
        hairline -= 1
        if a[hairline] > l:
            continue
        a[hairline] += growth
        if a[hairline] <= l:
            continue
        if (
            hairline > 0
            and a[hairline - 1] > l
            and hairline < n - 1
            and a[hairline + 1] > l
        ):
            time -= 1
        elif (hairline > 0 and a[hairline - 1] > l) or (
            hairline < n - 1 and a[hairline + 1] > l
        ):
            continue
        else:
            time += 1
    return results


n, m, l = map(int, input().split())
a = list(map(int, input().split()))
time = calculate_time(n, a, l)
results = process_queries(m, a, l, time)
for result in results:
    print(result)
