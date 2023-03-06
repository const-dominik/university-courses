[n, m] = list(map(int, input().split(" ")))

matrix_a = []
matrix_b = []

a = [[] for _ in range(n+m-1)]
b = [[] for _ in range(n+m-1)]

for i in range(n):
  matrix_a.append(list(map(int, input().split(" "))))
for i in range(n):
  matrix_b.append(list(map(int, input().split(" "))))

for row in range(n):
  for column in range(m):
    a[row+column].append(matrix_a[row][column])
    b[row+column].append(matrix_b[row][column])

for i in range(n+m-1):
  a[i] = sorted(a[i])
  b[i] = sorted(b[i])

if a == b:
  print("YES")
else:
  print("NO")