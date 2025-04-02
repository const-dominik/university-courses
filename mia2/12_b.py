t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))

    for i in range(n):
        if arr[i] > 1:
            break
    if (i + 1) % 2:
        print("First")
    else:
        print("Second")
