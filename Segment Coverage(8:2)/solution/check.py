# Ввод
n = int(input())
lr = []
for i in range(n):
    lr.append(list(map(int, input().split())))
m = int(input())

# Вычисления покрытия
a = [0] * m
for l, r in lr:
    for x in range(l, r):
        if 0 <= x < m: a[x] += 1

# Вычисление непокрытых клеток
zeros = []
for i in range(len(a)):
    if a[i] == 0: zeros.append(i)
# print(zeros)

# Группировка непокрытых клеток
groups = []
l = zeros[0]
acc = 1
for i in range(len(zeros)-1):
    if zeros[i] != zeros[i+1]-1:
        groups.append((zeros[i]-acc+1, zeros[i]+1))
        acc = 1
    else: acc += 1
groups.append((zeros[-1]-acc+1, zeros[-1]+1))

# Вывод
for l, r in groups:
    print(f'[{l} ; {r}]')
