import sys
import platform
import math


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


def un(N):
    if N == 1:
        return 2
    elif N == 2:
        return 3

    root = int(math.sqrt(N))

    for b in range(2, root+1):
        if b == N - 1:
            return b
        n = N
        k = n % b
        while n > 0:
            n = n // b
            if n % b != k:
                break
        if n == 0:
            return b

    # N = ab + a
    for divisor in range(root, 1, -1):
        if N % divisor == 0:
            b = N // divisor - 1
            if b > divisor:
                return b
    return N - 1


if platform.python_version() == '3.6.5':
    inf = open('uniform_number_input.txt')
else:
    inf = sys.stdin

sys.stdout = Unbuffered(sys.stdout)
T = int(inf.readline())

for t in range(T):
    N = int(inf.readline())
    print(f'Case #{t+1}')
    print(un(N))

inf.close()
