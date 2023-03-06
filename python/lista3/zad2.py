import timeit
from tabulate import tabulate

def isPerfect(n):
    if n <= 1: return False
    
    sum = 1
    i = 2
    
    while i <= n/2:
        if n % i == 0:
            sum += i
        i += 1

    return sum == n

def pierwsze_imperatywna(n):
    pierwsze = []
    i = 0
    while i <= n:
        if isPerfect(i):
            pierwsze.append(i)
        i += 1

    return pierwsze

def pierwsze_skladana(n):
    return [x for x in range(n+1) if isPerfect(x)]

def pierwsze_funkcyjna(n):
    one_to_n = list(range(1, n+1))
    return list(filter(lambda x: isPerfect(x), one_to_n))

def test(setup, test_code):
    times = timeit.repeat(setup = setup,
                          stmt = test_code,
                          repeat = 3,
                          number = 1000)
    return min(times)

setup1 = '''
from __main__ import pierwsze_imperatywna'''

test_code1 = '''
n = xxx
pierwsze_imperatywna(n)
    '''

setup2 = '''
from __main__ import pierwsze_skladana'''

test_code2 = '''
n = xxx
pierwsze_skladana(n)
    '''

setup3 = '''
from __main__ import pierwsze_funkcyjna'''

test_code3 = '''
n = xxx
pierwsze_funkcyjna(n)
    '''

headers = ["n", "imperatywna", "skladana",  "funkcyjna"]
times = []
for i in range(10, 100, 10):
    test_1 = test_code1.replace("xxx", str(i))
    test_2 = test_code2.replace("xxx", str(i))
    test_3 = test_code3.replace("xxx", str(i))
    time1 = test(setup1, test_1)
    time2 = test(setup2, test_2)
    time3 = test(setup3, test_3)
    data = [i, time1, time2, time3]
    times.append(data)

print(tabulate(times, headers, tablefmt="grid"))