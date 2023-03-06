[k, p] = list(map(int, input().split()))

sum = 0

for i in range(1, k+1):
  num = str(i) + str(i)[::-1]
  sum += int(num)

print(sum % p)