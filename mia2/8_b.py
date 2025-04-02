from typing import List
from math import comb

MODULUS = 10**9 + 7


def calculate_combinations(k: int, ball_counts: List[int]) -> int:
    result = 1
    total_balls = ball_counts[0]

    for i in range(1, k):
        result = (
            result
            * comb(total_balls + ball_counts[i] - 1, ball_counts[i] - 1)
            % MODULUS
        )
        total_balls += ball_counts[i]

    return result


k = int(input())
ball_counts = [int(input()) for _ in range(k)]
print(calculate_combinations(k, ball_counts))
