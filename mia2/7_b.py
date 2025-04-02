n = int(input())
ans = 1

x = 1
for i in range(5):
    x *= n - i

print(x * x // 120)
