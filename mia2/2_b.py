import re

input_values = input().split(" ")
zero_sequence_cost = int(input_values[1])
single_zero_cost = int(input_values[2])

input_string = input()

zero_sequences = re.findall("0+", input_string)

if zero_sequences and zero_sequence_cost < single_zero_cost:
    total_cost = (len(zero_sequences) - 1) * zero_sequence_cost + single_zero_cost
else:
    total_cost = len(zero_sequences) * single_zero_cost

print(total_cost)
