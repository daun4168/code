import sys
from heapq import *


class MinHeap:
    def __init__(self):
        self.heap = []

    def push(self, ele):
        heappush(self.heap, ele)

    def pop(self):
        return heappop(self.heap)

    def top(self):
        return self.heap[0]

    def size(self):
        return len(self.heap)

    def empty(self):
        return self.size() == 0


class MaxHeap:
    def __init__(self):
        self.heap = []

    def push(self, ele):
        heappush(self.heap, -ele)

    def pop(self):
        return -heappop(self.heap)

    def top(self):
        return -self.heap[0]

    def size(self):
        return len(self.heap)

    def empty(self):
        return self.size() == 0


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


T = readint()
for t in range(T):
    N, a, b = readints()



    min_heap = MinHeap()
    max_heap = MaxHeap()

    A = 1983
    max_heap.push(A)
    ret = A

    for i in range(1, N):
        A = (A * a + b) % 20090711
        if min_heap.size() == max_heap.size():
            max_heap.push(A)

        else:
            min_heap.push(A)

        if not min_heap.empty() and not max_heap.empty() and min_heap.top() < max_heap.top():
            min_heap.push(max_heap.pop())
            max_heap.push(min_heap.pop())

        ret = (ret + max_heap.top()) % 20090711

    print(ret)
