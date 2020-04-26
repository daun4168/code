from sys import stdin

line = []
line_len = 0
line_index = 0

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


test_cases = readint()
for test_case in range(test_cases):
    print()
