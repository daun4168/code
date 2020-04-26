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


line = []


def readstr():
    global line
    if not line:
        line = sys.stdin.readline().split()
    return line.pop(0)


def readint():
    return int(readstr())


def readfloat():
    return float(readstr())

if __name__ == "__main__":
    sys.stdin = open('sample_input.txt')


    T = readint()
    for t in range(T):
        N = readint()
        xs = []
        ys = []
        xy = {}
        for i in range(N):
            x1 = readint()
            y1 = readint()
            x2 = readint()
            y2 = readint()

            if not xs:
                if x1 == x2:
                    xs.append([x1, x1])
                else:
                    xs.append([x1, x1])
                    xs.append([x2, x2])

            elif x1 == x2:
                for min_max in xs:
                    if x1 < min_max[0]:
                        min_max[0] = x1
                    elif x1 > min_max[1]:
                        min_max[1] = x1
            else:
                new_xs = []
                for min_max in xs:
                    if x1 < min_max[0]:
                        new_xs.append([x1, min_max[1]])
                    elif x1 > min_max[1]:
                        new_xs.append([min_max[0], x1])
                    else:
                        new_xs.append(min_max[:])

                    if x2 < min_max[0]:
                        new_xs.append([x2, min_max[1]])
                    elif x2 > min_max[1]:
                        new_xs.append([min_max[0], x2])
                    else:
                        new_xs.append(min_max[:])

                xs = new_xs

                xs.sort(key=lambda x: (x[0], x[1]))
                pre = None
                for idx, x in enumerate(xs):
                    if x[0] != pre:
                        pre = x[0]
                    else:
                        xs.pop(idx)

                xs.sort(key=lambda x: (x[1], x[0]), reverse=True)
                pre = None
                for idx, x in enumerate(xs):
                    if x[1] != pre:
                        pre = x[1]
                    else:
                        xs.pop(idx)
            # y
            if not ys:
                if y1 == y2:
                    ys.append([y1, y1])
                else:
                    ys.append([y1, y1])
                    ys.append([y2, y2])

            elif y1 == y2:
                for min_max in ys:
                    if y1 < min_max[0]:
                        min_max[0] = y1
                    elif y1 > min_max[1]:
                        min_max[1] = y1
            else:
                new_ys = []
                for min_max in ys:
                    if y1 < min_max[0]:
                        new_ys.append([y1, min_max[1]])
                    elif y1 > min_max[1]:
                        new_ys.append([min_max[0], y1])
                    else:
                        new_ys.append(min_max[:])

                    if y2 < min_max[0]:
                        new_ys.append([y2, min_max[1]])
                    elif y2 > min_max[1]:
                        new_ys.append([min_max[0], y2])
                    else:
                        new_ys.append(min_max[:])

                ys = new_ys

                ys.sort(key=lambda x: (x[0], x[1]))
                pre = None
                for idx, x in enumerate(ys):
                    if x[0] != pre:
                        pre = x[0]
                    else:
                        ys.pop(idx)

                ys.sort(key=lambda x: (x[1], x[0]), reverse=True)
                pre = None
                for idx, x in enumerate(ys):
                    if x[1] != pre:
                        pre = x[1]
                    else:
                        ys.pop(idx)

        min_dist_x = 100000000
        for min_max in xs:
            if min_max[1] - min_max[0] < min_dist_x:
                min_dist_x = min_max[1] - min_max[0]
        min_dist_y = 100000000
        for min_max in ys:
            if min_max[1] - min_max[0] < min_dist_y:
                min_dist_y = min_max[1] - min_max[0]

        print(f'Case #{t+1}')
        Answer = max(min_dist_x, min_dist_y) / 2
        if Answer % 1 == 0:
            print(int(Answer))
        else:
            print(Answer)
``