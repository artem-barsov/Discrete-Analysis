from random import *

m = 1000000
min_l, max_l = 5000, 15000
n = 800

print(n)
for i in range(n):
    l = -2*max_l + randint(0, m + 2*max_l)
    print(l, l + randint(min_l, max_l))
print(m)
