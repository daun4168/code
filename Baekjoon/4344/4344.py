def split():
    number = input()
    A = number.split()
    return list(map(int, A))

def avr(a):
    return (sum(a) - a[0])/a[0]

def over(a):
    n = 1
    count = 0
    while n <= a[0]:
        if avr(a) < a[n]:
            count += 1
        n += 1
    return count

casenumber = int(input())

while casenumber > 0:
    case_and_score = split()
    percent = round((over(case_and_score)/case_and_score[0])*100, 3)
    print(f"{percent:.3f}%")

    casenumber -= 1




