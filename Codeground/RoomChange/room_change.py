import sys
import os


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
    f = open('room_change_input.txt.txt')
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


def readfloat():
    return float(readstr())


def readints():
    return [int(ele) for ele in f.readline().split()]


T = readint()
for t in range(T):

    print(f'Case #{t+1}')
    print()

f.close()
