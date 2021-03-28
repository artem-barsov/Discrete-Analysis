import sys
import random

def main():
    nTests = int(sys.argv[1])
    ops = list('+-*/^<>=')
    if len(sys.argv) > 2 and sys.argv[2]:
        ops = list(sys.argv[2])
        if any([x not in '+-*/^<>=' for x in ops]):
            sys.exit('Wrong arithmetic operation set')
    for _ in range(nTests):
        op = random.choice(ops)
        if op != '^':
            print(random.randint(0, 10**10000))
            print(random.randint(0, 10**1000))
        else:
            print(random.randint(0, 10**10))
            print(random.randint(0, 10**4))
        print(op)

main()
