def split_public_key(pk, a, b):
    n = len(pk)
    pref_mod_a = 0
    prefix_positions = []

    for i, digit in enumerate(pk, 1):
        pref_mod_a = (pref_mod_a * 10 + int(digit)) % a
        if i < n and pref_mod_a == 0 and pk[i] != "0":
            prefix_positions.append(i)

    suff_mod_b = 0
    p_b = 1
    i = n

    for pos in reversed(prefix_positions):
        for i in range(i - 1, pos - 1, -1):
            suff_mod_b = (suff_mod_b + int(pk[i]) * p_b) % b
            p_b = p_b * 10 % b

        if not suff_mod_b:
            return "YES", int(pk[:i]), int(pk[i:])
    return "NO", None, None


public_key = input()
a, b = map(int, input().split())
result, part1, part2 = split_public_key(public_key, a, b)

print(result)
if result == "YES":
    print(part1)
    print(part2)
