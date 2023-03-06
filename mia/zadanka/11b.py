t = int(input())
a = "Ashishgup"
b = "FastestFinger"

def isprime(num):
  if num <= 2: return False
  for n in range(2,int(num**0.5)+1):
    if num % n == 0:
      return False
  return True 

for q in range(t):
  n = int(input())

  if n == 2:
    print(a)
  elif n == 1 or (n % 4 == 2 and isprime(n/2)) or (n & (n-1) == 0):
    print(b)
  else:
    print(a)