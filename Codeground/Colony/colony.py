import sys
import os
import bisect


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


if os.name == 'nt':
    f = open('colony.txt')
else:
    f = sys.stdin
sys.stdout = Unbuffered(sys.stdout)

line = []
line_len = 0
line_index = 0


def readstr():
    global line, line_len, line_index
    if line_index >= line_len:
        line = f.readline().split()
        line_index = 0
        line_len = len(line)
    line_index += 1
    return line[line_index - 1]


def readint():
    return int(readstr())


def readints():
    return [int(ele) for ele in f.readline().split()]


T = readint()
for t in range(T):
    N = readint()
    g1 = []
    g2 = []
    for i in range(N):
        x1, y1, x2, y2 = readints()
        g1.append((x1, y1, i + 1))
        g2.append((x2, y2, i + 1))

    g1.sort()
    g2.sort()

    min_year = N + 1
    for x1, y1, year1 in g1:
        max_x2 = x1 + N - year1
        min_x2 = x1 - N + year1

        left_idx = bisect.bisect_left(g2, (min_x2,))
        right_idx = bisect.bisect_right(g2, (max_x2,))
        if right_idx == N:
            right_idx = N - 1

        for i in range(left_idx, right_idx + 1):
            x2, y2, year2 = g2[i]
            dist = abs(x1 - x2) + abs(y1 - y2)
            new_min_year = max(year1 + dist, year2)
            min_year = min(new_min_year, min_year)

    print(f'Case #{t+1}')
    if min_year > N:
        print(-1)
    else:
        print(min_year)

f.close()
