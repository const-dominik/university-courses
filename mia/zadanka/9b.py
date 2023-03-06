q = int(input())

index = 0
intervals = [0]*101

def does_match(i, j):
  [a, b] = intervals[i]
  [c, d] = intervals[j]

  return (c < a and a < d) or (c < b and b < d)

def bfs(start, end, n):
  visited = [False]*101
  queue = [start]

  while not len(queue) == 0:
    a = queue.pop()
    visited[a] = True

    for i in range(1, n+1):
      if not visited[i] and does_match(a, i):
        queue.append(i)

  return visited[end]

for i in range(1, q+1):
  [t, a, b] = list(map(int, input().split()))
  if t == 1:
    index += 1
    intervals[index] = [a, b]
  elif t == 2:
    if bfs(a, b, index):
      print("YES")
    else:
      print("NO")