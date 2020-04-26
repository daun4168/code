from collections import defaultdict
from heapq import *


class Graph(object):
    def __init__(self):
        self.g = defaultdict(list)

    def dijkstra(self, src):
        q = [(0, src)]
        seen = set()
        dist = {src: 0}
        prev = defaultdict(list)
        while q:
            cost, v1 = heappop(q)
            if v1 in seen:
                continue
            seen.add(v1)
            for c, v2 in self.g.get(v1, ()):
                if v2 in seen:
                    continue
                if v2 not in dist or cost + c < dist[v2]:
                    dist[v2] = cost + c
                    prev[v2] = [v1]
                    heappush(q, (cost + c, v2))
                elif cost + c == dist[v2]:
                    prev[v2].append(v1)
        return dist, prev

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


if __name__ == '__main__':
    graph = Graph()
    graph.addEdge(1, 2, 1)
    graph.addEdge(1, 3, 2)
    graph.addEdge(1, 4, 3)
    graph.addEdge(2, 4, 1)
    graph.addEdge(3, 5, 2)
    graph.removeEdge(1, 3)
    src = 1

    for key, value in graph.dijkstra(src)[0].items():
        print(f'{src} to {key} : {value}')

