n = int(input())

way = []

for x in range (0, 1667):
    for y in range(0, 1001):
        if 3*x+5*y == n:
            way.append(x+y)

if way == []:
    print("-1")
else:
    print(min(way))