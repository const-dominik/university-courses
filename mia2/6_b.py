import math


def generate_primes(n):
    primes = [True] * n
    primes[0] = primes[1] = False

    for i in range(2, int(math.sqrt(n)) + 1):
        if primes[i]:
            for j in range(i * i, n, i):
                primes[j] = False

    return primes


def is_t_prime(number, primes):
    sqrt_number = int(math.sqrt(number))
    return primes[sqrt_number] and sqrt_number * sqrt_number == number


n = 10**6 + 1
primes = generate_primes(n)

input()
for number in map(int, input().split()):
    print("YES" if is_t_prime(number, primes) else "NO")
