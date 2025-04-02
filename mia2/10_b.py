def transform_string(s, t):
    s_count = {char: s.count(char) for char in set(s)}
    t_count = {char: t.count(char) for char in set(t)}

    if not all(s_count.get(char, 0) >= t_count.get(char, 0) for char in set(t)):
        return "need tree"

    if sorted(s) == sorted(t):
        return "array"

    t_index = 0
    for char in s:
        if char == t[t_index]:
            t_index += 1
            if t_index == len(t):
                break

    if t_index == len(t):
        return "automaton"
    elif sorted(s) == sorted(t):
        return "array"
    else:
        return "both"


s = input()
t = input()
print(transform_string(s, t))
