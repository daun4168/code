# Python timeout
# Use cpp code

import sys
import os
from collections import defaultdict
from heapq import *


inf = 1000000000


class Graph(object):
    def __init__(self):
        self.g = defaultdict(list)

    def dijkstra(self, src):
        q = [(0, src)]
        seen = {}
        dist = defaultdict(lambda: inf)
        prev = defaultdict(list)
        while q:
            cost, v1 = heappop(q)
            if v1 in seen:
                continue
            seen[v1] = True
            for c, v2 in self.g[v1]:
                if v2 in seen:
                    continue
                if cost + c < dist[v2]:
                    dist[v2] = cost + c
                    prev[v2] = [v1]
                    heappush(q, (cost + c, v2))
                elif cost + c == dist[v2]:
                    prev[v2].append(v1)
        return prev

    def addEdge(self, src, dst, dist):
        self.g[src].append((dist, dst))
        self.g[dst].append((dist, src))

    def removeEdge(self, src, dst):
        for s in self.g[src]:
            if s[1] == dst:
                self.g[src].remove(s)
                break
        for s in self.g[dst]:
            if s[1] == src:
                self.g[dst].remove(s)
                break


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
    f = open('campus1_input.txt')
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
    N, M = readints()
    g = Graph()
    for i in range(M):
        src, dst, dist = readints()
        g.addEdge(src, dst, dist)

    isToll = [False for i in range(N + 1)]
    for i in range(1, N + 1):
        g.dijkstra(i)
        prev = g.dijkstra(i)
        for src, dsts in prev.items():
            for dst in dsts:
                if dst != i:
                    isToll[dst] = True

    print(f'Case #{t+1}')
    print(isToll.count(False) - 1, end=' ')
    for idx, value in enumerate(isToll):
        if not value and idx != 0:
            print(idx, end=' ')
    print()
f.close()
