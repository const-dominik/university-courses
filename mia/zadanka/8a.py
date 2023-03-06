[n, g] = list(map(int, input().split(" ")))

pairs = lambda x: int((x*(x-1))//2)

bigger = n % g
l = n // g

print(f"{bigger * pairs(l + 1) + (g-bigger)*pairs(l)} {pairs(n-g+1)}")