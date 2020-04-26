import sys
import os
import csv


class Unbuffered(object):
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
    inf = open('test.txt', 'r')
    # inf = open('frog_jump_input.txt', 'r')
else:
    inf = sys.stdin
sys.stdout = Unbuffered(sys.stdout)

line = []
line_len = 0
line_index = 0


def readstr():
    global line
    global line_len
    global line_index
    if line_index >= line_len:
        line = inf.readline().split()
        line_index = 0
        line_len = len(line)
    line_index += 1
    return line[line_index - 1]


def readint():
    return int(readstr())


T = readint()
for t in range(T):
    N = readint()
    a = []
    for i in range(N):
        a.append(readint())
    K = readint()

    before_jump = 0
    before_stone = 0
    jump_num = 0
    can_jump = True

    for i in range(N):
        if a[i] - before_stone > K:
            can_jump = False
            break
        if a[i] - before_jump > K:
            jump_num += 1
            before_jump = before_stone
        before_stone = a[i]


    if can_jump:
        Answer = jump_num + 1
    else:
        Answer = -1

    print(f'Case #{t+1}')
    print(Answer)

inf.close()
