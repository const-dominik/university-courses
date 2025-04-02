V, E = map(int, input().split())
edges = [list(map(int, input().split())) for _ in range(E)]

graph = {i: [] for i in range(1, V + 1)}
for v1, v2 in edges:
    graph[v1].append(v2)
    graph[v2].append(v1)

degrees = [len(graph[node]) for node in graph]

if degrees.count(1) == 2 and degrees.count(2) == V - 2 and E == V - 1:
    print("bus topology")
elif all(degree == 2 for degree in degrees):
    print("ring topology")
elif degrees.count(E) == 1 and degrees.count(1) == V - 1:
    print("star topology")
else:
    print("unknown topology")
