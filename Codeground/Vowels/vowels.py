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
    f = open('vowels.txt')
else:
    f = sys.stdin
sys.stdout = Unbuffered(sys.stdout)

T = int(f.readline())
for t in range(T):

    N = int(f.readline())
    string = f.readline()

    aeiou = []
    a_indexs = [i for i, x in enumerate(string) if x == 'a']

    for a_index in a_indexs:
        idx = a_index
        isFound = False
        state = 'e'
        while idx < len(string):
            if state == 'e' and string[idx] == 'e':
                state = 'i'
            elif state == 'i' and string[idx] == 'i':
                state = 'o'
            elif state == 'o' and string[idx] == 'o':
                state = 'u'
            elif state == 'u' and string[idx] == 'u':
                isFound = True
                break
            idx += 1

        if isFound:
            aeiou.append((idx - a_index, a_index + 1, idx + 1))
        else:
            break

    print(f'Case #{t+1}')
    if not aeiou:
        print('-1 -1')
    else:
        aeiou.sort()
        print(f"{aeiou[0][1]} {aeiou[0][2]}")

f.close()
