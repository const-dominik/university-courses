import math

def pierwiastek(n):
    i = 1
    k = 0

    while k + 2*i-1 <= n:
        k += 2*i - 1
        i += 1

    return i-1

for i in range(1, 1000):
    correct = math.floor(math.sqrt(i))
    p = pierwiastek(i)
    if (correct != p):
        print(f"Błąd dla {i}: jest {p}, powinno być {correct}.")