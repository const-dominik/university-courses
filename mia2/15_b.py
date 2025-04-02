def has_solution(ax, ay, bx, by, cx, cy):
    A = ax * ax + ay * ay
    B = bx * bx + by * by
    C = cx * cx + cy * cy
    G = (cy - by) * ax + (ay - cy) * bx + (by - ay) * cx

    try:
        x = ((B - C) * ay + (C - A) * by + (A - B) * cy) / (2 * G)
        y = ((C - B) * ax + (A - C) * bx + (B - A) * cx) / (2 * G)
    except ZeroDivisionError:
        return "No"

    if (ax - x) * (bx - x) + (ay - y) * (by - y) == (bx - x) * (cx - x) + (by - y) * (
        cy - y
    ):
        return "Yes"
    else:
        return "No"


ax, ay, bx, by, cx, cy = map(float, input().split())
print(has_solution(ax, ay, bx, by, cx, cy))
