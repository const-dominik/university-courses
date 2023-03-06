n = int(input())
s = input()
chars = set(s)

ret = [0] * n

for char in chars:
  last = -1
  
  for i in range(len(s)):
    if s[i] == char:
      last = i
    
    if last == -1:
      ret[i] = float("inf")
    else:
      ret[i] = max(ret[i], i-last+1)

print(min(ret))