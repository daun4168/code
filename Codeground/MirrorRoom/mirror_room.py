import sys
import os


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
    inf = open('mirror_room_input.txt')
else:
    inf = sys.stdin

line = []
def readstr():
    global line
    if not line:
        line = inf.readline().split()
    return line.pop(0)


def readint():
    return int(readstr())


def readfloat():
    return float(readstr())


sys.stdout = Unbuffered(sys.stdout)

T = readint()
for t in range(T):
    N = readint()
    mirror = []

    for i in range(N):
        mirror.append(inf.readline())

    visit = [[False for i in range(N)] for j in range(N)]
    x = 0
    y = 0
    LEFT, RIGHT, TOP, BOTTOM = range(4)
    state = LEFT

    while 0 <= x < N and 0 <= y < N:
        visit[y][x] = True

        if state == LEFT:
            if mirror[y][x] == '0':
                x = x + 1
            elif mirror[y][x] == '1':
                y = y - 1
                state = BOTTOM
            elif mirror[y][x] == '2':
                y = y + 1
                state = TOP
        elif state == RIGHT:
            if mirror[y][x] == '0':
                x = x - 1
            elif mirror[y][x] == '1':
                y = y + 1
                state = TOP
            elif mirror[y][x] == '2':
                y = y - 1
                state = BOTTOM
        elif state == TOP:
            if mirror[y][x] == '0':
                y = y + 1
            elif mirror[y][x] == '1':
                x = x - 1
                state = RIGHT
            elif mirror[y][x] == '2':
                x = x + 1
                state = LEFT
        elif state == BOTTOM:
            if mirror[y][x] == '0':
                y = y - 1
            elif mirror[y][x] == '1':
                x = x + 1
                state = LEFT
            elif mirror[y][x] == '2':
                x = x - 1
                state = RIGHT

    Answer = 0
    for i in range(N):
        for j in range(N):
            if visit[i][j] and mirror[i][j] != '0':
                Answer += 1

    print(f'Case #{t+1}')
    print(Answer)

inf.close()
