import random
n, m = 500, 500
print(n, m)
for i in range(n):
    for j in range(m):
        print(random.choice(('0', '1')), end='')
    print()
