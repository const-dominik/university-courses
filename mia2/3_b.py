ribbon_length, piece_length_a, piece_length_b, piece_length_c = map(
    int, input().split()
)

piece_lengths = [piece_length_a, piece_length_b, piece_length_c]

dp_table = [
    [0 for _ in range(3)]
    for _ in range(
        max(piece_length_a, piece_length_b, piece_length_c, ribbon_length) + 1
    )
]

dp_table[0] = [0, 0, 0]
dp_table[piece_length_a] = [1, 0, 0]
dp_table[piece_length_b] = [0, 1, 0]
dp_table[piece_length_c] = [0, 0, 1]

for i in range(min(piece_lengths), ribbon_length + 1):
    for j in range(3):
        if i != piece_lengths[j] and i >= piece_lengths[j]:
            dp_table[i][j] = (
                max(dp_table[i - piece_lengths[j]]) + 1
                if max(dp_table[i - piece_lengths[j]]) > 0
                else 0
            )

print(max(dp_table[ribbon_length]))
