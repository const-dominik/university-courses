from collections import defaultdict

n = int(input())

tree = defaultdict(set)

for _ in range(n - 1):
    u, v = map(int, input().split())
    tree[u].add(v)
    tree[v].add(u)

visited = set()
ans = 0
Q = [(1, 1, 0)]

while Q:
    u, cnt, num = Q.pop()
    visited.add(u)
    dep = 0

    for i in tree[u]:
        if i not in visited:
            dep += 1

    if dep == 0:
        ans += cnt * num
    else:
        for i in tree[u]:
            if i not in visited:
                Q.append((i, cnt / dep, num + 1))

print(ans)
