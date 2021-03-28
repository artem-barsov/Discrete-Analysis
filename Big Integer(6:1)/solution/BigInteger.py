import sys

for line in sys.stdin:
    a = int(line)
    b = int(input())
    op = input()
    if op == '+': print(a + b)
    if op == '-':
        if a >= b: print(a - b)
        else: print('Error')
    if op == '*': print(a * b)
    if op == '/':
        if b != 0: print(a // b)
        else: print('Error')
    if op == '^':
        if a!=0 or b!=0: print(a ** b)
        else: print('Error')
    if op == '<': print('true' if a < b else 'false')
    if op == '>': print('true' if a > b else 'false')
    if op == '=': print('true' if a == b else 'false')
