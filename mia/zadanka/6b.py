t = pow(10,9)+7
n = input()
l = [1, 2]

for i in range(2, len(n)):
  l.append((l[i-2] + l[i-1]) % t)
  
ans = 1

for i in range(len(n)):
  if n[i] == "m" or n[i] == "w":
    print(0)
    exit(0)

i = 0

while i < len(n):
    count = 0
    if n[i] == "n":
      while i < len(n) and n[i] == "n":
        count += 1
        i += 1
      ans = ans * l[count-1] % t
    elif n[i] == "u":
      while i < len(n) and n[i] == "u":
        count += 1
        i += 1
      ans = ans * l[count-1] % t
    else:
      i += 1
 
print(ans)