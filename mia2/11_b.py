def calculate(n, q, a):
    sums = [0] * (n + 1)
    for _ in range(q):
        l, r = map(int, input().split())
        sums[l - 1] += 1
        sums[r] -= 1
    for i in range(n):
        sums[i + 1] += sums[i]
    a = sorted([0] + a)
    sums = sorted(sums)
    max_sum = sum(x * y for x, y in zip(a, sums))
    print(max_sum)


n, q = map(int, input().split())
a = list(map(int, input().split()))
calculate(n, q, a)
