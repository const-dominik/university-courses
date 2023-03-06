t = int(input())

while t != 0:
  n = int(input())

  ret = 0
  
  vals = list(map(int, input().split(" ")))

  for val in vals:
    ret |= val
    
  print(ret)
  t -= 1