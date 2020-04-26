import sys

input = sys.stdin.readline
def readints():
    line = input()
    results = line.split()
    return list(map(int, results))


stack = list()


def push(a):
    stack.append(a)


def top():
    if len(stack) == 0:
        print("-1")
    else:
        print(stack[len(stack)-1])


def size():
    print(len(stack))


def empty():
    if len(stack) == 0:
        print("1")
    else:
        print("0")


def pop():
    if len(stack) == 0:
        print("-1")
    else:
        print(stack.pop())


mission_number = int(input())


while mission_number > 0:
    mission = (input())
    mission2 = mission.split()

    if mission2[0] == 'push':
        push(mission2[1])
    elif mission2[0] == 'top':
        top()
    elif mission2[0] == 'pop':
        pop()
    elif mission2[0] == 'size':
        size()
    elif mission2[0] == 'empty':
        empty()

    mission_number -= 1


