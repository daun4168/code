a = 10
print(id(a))
a += 20
print(id(a))

a = "ABC"
print(id(a))
a += "DEF"
print(id(a))

a = ['a', 'b']
print(id(a))
a.append('c')
print(id(a))

def fun1(a, b, c):
  print(a, b, c)

fun2 = fun1(b=1)
fun2(a=10, b=3, c=5)
