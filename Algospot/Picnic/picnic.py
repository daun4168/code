from sys import stdin
import numpy

line = []
line_len = 0
line_index = 0


def readstr():
    global line, line_len, line_index
    if line_index >= line_len:
        line = stdin.readline().split()
        line_index = 0
        line_len = len(line)
    line_index += 1
    return line[line_index - 1]


def readint():
    return int(readstr())


def readints():
    return [int(ele) for ele in stdin.readline().split()]


def find_pair_num(n, s_idx, visited):
    if n == 0:
        return 1

    pair_num = 0
    for i in range(s_idx, m - n + 1):
        a, b = pairs[i]
        if a not in visited and b not in visited:
            new_visited = set(visited)
            new_visited.add(a)
            new_visited.add(b)
            pair_num += find_pair_num(n-1, i+1, new_visited)

    return pair_num


test_cases = readint()
for test_case in range(test_cases):
    n, m = readints()
    pairs = []
    for i in range(m):
        a = readint()
        b = readint()
        pairs.append((a, b))

    pnum = find_pair_num(n // 2, 0, set())
    print(pnum)





