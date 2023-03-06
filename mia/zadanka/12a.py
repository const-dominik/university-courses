s = input()
n = int(input())
 
if len(s) % n != 0:
  print("NO")
  exit(0)
 
step = len(s) // n
 
n, step = step, n
 
for i in range(0, step):
    ss = s[i * n : (i + 1) * n]
    if (all(ss[j] == ss[len(ss) - j - 1] for j in range(0, len(ss)))):
        continue
    else:
        print("NO")
        exit(0)
 
print("YES")