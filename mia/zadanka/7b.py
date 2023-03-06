def gcd(a, b):
  if b == 0:
    return a
  else:
    return gcd(b, (a % b))

def find_array_b(arr):
    n = len(arr)
    b = [0] * (n + 1) # Initialize array B with all 0s
    for i in range(n):
        # Find the greatest common divisor of adjacent elements in array A
        gcd_a = gcd(arr[i], arr[(i+1) % n])
        # If gcd is greater than 1, set the (i+1)-th element of array B to gcd
        if gcd_a > 1:
            b[i+1] = gcd_a
    # If all elements in array A are equal, set the first and last elements of array B to that value
    if len(set(arr)) == 1:
        b[0], b[n] = arr[0], arr[0]
    # Otherwise, set the remaining elements of array B to the corresponding elements in array A
    else:
        for i in range(n):
            if b[i+1] == 0:
                b[i+1] = arr[i]
    # Check if each element of array A satisfies the equation Ai = gcd(Bi, Bi+1)
    for i in range(n):
        if arr[i] != gcd(b[i], b[i+1]):
            return "No"
    return "Yes"



t = int(input())
for i in range(t):
  input()
  arr_a = list(map(int, input().split()))
  print(find_array_b(arr_a))