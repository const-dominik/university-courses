def get_all_values(num_cubes, cubes):
    all_values = set()
    for cube in cubes:
        all_values.update(set(map(int, cube)))

    if num_cubes > 1:
        for i in range(num_cubes):
            for j in range(i + 1, num_cubes):
                for c1 in cubes[i]:
                    for c2 in cubes[j]:
                        all_values.add(int(c1 + c2))
                        all_values.add(int(c2 + c1))

    return sorted(all_values)


def main():
    num_cubes = int(input())
    cubes = []
    for _ in range(num_cubes):
        numbers = input().split(" ")
        cubes.append(numbers)
    all_values = get_all_values(num_cubes, cubes)

    index = 1
    while index in all_values:
        index += 1

    print(index - 1)


if __name__ == "__main__":
    main()
