t = int(input())

for q in range(0, t):
  n = int(input())

  for i in range(1, n-2, 2):
    print(f"{i+1} {i} ")

  if n % 2 == 0:
    print(f"{n} {n-1}")
  else:
    print(f"{n} {n-2} {n-1}")