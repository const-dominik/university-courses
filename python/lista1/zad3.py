def tabliczka(x1, x2, y1, y2):
    if (abs(x2-x1) != abs(y2-y1)): return False
    low_x, big_x = [x1, x2] if x1 < x2 else [x2, x1]
    low_y, big_y = [y1, y2] if y1 < y2 else [y2, y1]

    xs = [n for n in range(low_x, big_x+1)]
    xs.insert(0, "")
    matrix = [xs]

    for i in range(low_y, big_y + 1):
        line = [i]
        for j in range(big_x - low_x + 1):
            line.append(i*matrix[0][j+1])
        matrix.append(line)
    
    for i in range(len(matrix)):
        print("\t".join(map(str, matrix[i])))
    return matrix

tabliczka(3, 5, 2, 4)
tabliczka(-3, -5, -2, -4)
tabliczka(-3, -5, 2, 4)