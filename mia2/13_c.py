import math

num_cows = int(input().strip())
weights = list(map(int, input().strip().split()))

num_scenarios = int(input().strip())
scenarios = []
for i in range(num_scenarios):
    start, step = map(int, input().strip().split())
    scenarios.append({"id": i, "start": start - 1, "step": step, "total_weight": 0})

scenarios.sort(key=lambda x: x["step"])

sqrt_num_cows = int(math.sqrt(num_cows))

cumulative_weights = [0] * num_cows

for i in range(num_scenarios):
    if scenarios[i]["step"] > sqrt_num_cows:
        j = scenarios[i]["start"]
        while j < num_cows:
            scenarios[i]["total_weight"] += weights[j]
            j += scenarios[i]["step"]
    else:
        if i == 0 or scenarios[i]["step"] > scenarios[i - 1]["step"]:
            j = num_cows - 1
            while j >= 0:
                cumulative_weights[j] = weights[j]
                if j + scenarios[i]["step"] < num_cows:
                    cumulative_weights[j] += cumulative_weights[
                        j + scenarios[i]["step"]
                    ]
                j -= 1
        scenarios[i]["total_weight"] = cumulative_weights[scenarios[i]["start"]]

scenarios.sort(key=lambda x: x["id"])

for i in range(num_scenarios):
    print(scenarios[i]["total_weight"])
