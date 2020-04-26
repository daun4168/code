from sys import stdin
from typing import List, Tuple, Any

line = []
line_len = 0
line_index = 0


def ndarray(value, dim):
    """
    :param value: init value of each element
    :param dim: a tuple of dimensions
    :return: n-dimension array
    """
    if type(dim) == int:
        return [value for _ in range(dim)]
    elif len(dim) == 1:
        return [value for _ in range(dim[0])]
    else:
        return [ndarray(value, dim[1:]) for _ in range(dim[0])]


def readstr():
    global line
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


xy = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]


def isword(word, x, y):
    if x < 0 or x >= 5 or y < 0 or y >= 5:
        return False
    if not word:
        return True

    if mem[len(word) - 1][x][y] != -1:
        if mem[len(word) - 1][x][y] == 1:
            return True
        else:
            return False

    if word[0] == game[x][y]:
        for newx, newy in xy:
            if isword(word[1:], x + newx, y + newy):
                mem[len(word) - 1][x][y] = 1
                return True
    mem[len(word) - 1][x][y] = 0
    return False


if __name__ == "__main__":
    stdin = open("sample_input.txt", 'r')
    test_cases = readint()
    for test_case in range(test_cases):
        game = []

        for i in range(5):
            game.append(readstr())

        N = readint()
        for n in range(N):
            word = readstr()
            is_found = False

            mem = ndarray(-1, (len(word), 5, 5))

            for x in range(5):
                for y in range(5):
                    is_found = isword(word[:], x, y)

                    if is_found:
                        break
                if is_found:
                    break

            if is_found:
                print(word, 'YES')
            else:
                print(word, 'NO')
