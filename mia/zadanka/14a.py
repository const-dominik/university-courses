n = int(input())
x = []
y = []

for i in range(n):
  [a, b] = list(map(int, input().split(" ")))
  x.append(a)
  y.append(b)

if n == 1 or (n == 2 and (x[0] == x[1] or y[0] == y[1])):
  print(-1)
else:
  diff1 = x[0] - x[1]
  diff2 = y[0] - y[1]
  if diff1 == 0:
    diff1 = x[1] - x[2]
  if diff2 == 0:
    diff2 = y[1] - y[2]
  print(abs(diff1*diff2))