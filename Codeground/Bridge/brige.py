import sys
import os
from math import sqrt

inf = 10000000000000
class Unbuffered:
    def __init__(self, stream):
        self.stream = stream

    def write(self, data):
        self.stream.write(data)
        self.stream.flush()

    def writelines(self, datas):
        self.stream.writelines(datas)
        self.stream.flush()

    def __getattr__(self, attr):
        return getattr(self.stream, attr)




line = []
line_len = 0
line_index = 0


def readstr():
    global line, line_len, line_index
    if line_index >= line_len:
        line = sys.stdin.readline().split()
        line_index = 0
        line_len = len(line)
    line_index += 1
    return line[line_index - 1]


def readint():
    return int(readstr())


def readints():
    return [int(ele) for ele in sys.stdin.readline().split()]


def dist(p1, p2):
    return sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)


def dist2(p1, p2):
    return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2


def cal_min_dist(p1, p2, p3):
    a = dist(p2, p3)
    b = dist(p1, p3)
    c = dist(p1, p2)
    a2 = dist2(p2, p3)
    b2 = dist2(p1, p3)
    c2 = dist2(p1, p2)
    cosB = (c2 + a2 - b2) / (2 * c * a)
    cosC = (a2 + b2 - c2) / (2 * a * b)

    if cosB <= 0:
        return c
    elif cosC <= 0:
        return b

    sinB = sqrt(1 - cosB ** 2)
    return c * sinB

sys.stdin = open('bridge.txt')
sys.stdout = Unbuffered(sys.stdout)


T = readint()
for t in range(T):
    N, M = readints()
    a = []
    for i in range(N):
        a.append(tuple(readints()))
    b = []
    for i in range(M):
        b.append(tuple(readints()))

    close_line = 0
    close_line_dist = inf

    for i in range(M):
        new_dist = cal_min_dist(a[0], b[i], b[i - 1])
        if new_dist < close_line_dist:
            close_line_dist = new_dist
            close_line = i

    min_dist = close_line_dist
    i = 1
    while i < N:
        new_dist = cal_min_dist(a[i], b[close_line], b[close_line - 1])
        left_dist = cal_min_dist(a[i], b[close_line - 1], b[close_line - 2])
        right_dist = cal_min_dist(a[i], b[(close_line + 1) % M],
                                  b[close_line])
        if new_dist <= left_dist and new_dist <= right_dist:
            min_dist = min(new_dist, min_dist)
            i += 1
            continue
        if left_dist < new_dist:
            close_line = (close_line - 1) % M
        elif right_dist < new_dist:
            close_line = (close_line + 1) % M

    close_line = 0
    close_line_dist = inf

    for i in range(N):
        new_dist = cal_min_dist(b[0], a[i], a[i - 1])
        if new_dist < close_line_dist:
            close_line_dist = new_dist
            close_line = i

    min_dist = min(min_dist, close_line_dist)
    i = 1
    while i < M:
        new_dist = cal_min_dist(b[i], a[close_line], a[close_line - 1])
        left_dist = cal_min_dist(b[i], a[close_line - 1], a[close_line - 2])
        right_dist = cal_min_dist(b[i], a[(close_line + 1) % N],
                                  a[close_line])
        if new_dist <= left_dist and new_dist <= right_dist:
            min_dist = min(new_dist, min_dist)
            i += 1
            continue
        if left_dist < new_dist:
            close_line = (close_line - 1) % N
        elif right_dist < new_dist:
            close_line = (close_line + 1) % N


    min_dist = round(min_dist, 10)
    print(f'Case #{t+1}')
    print(f'{min_dist:.10f}')
