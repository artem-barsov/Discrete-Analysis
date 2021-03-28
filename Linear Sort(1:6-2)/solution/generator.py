import sys
import random
import string

def get_random_string():
    length = random.randint(20, 50)
    random_list = [ random.choice(string.ascii_letters) for _ in range(length) ]
    return "".join(random_list)

def main():
    for _ in range(int(sys.argv[1])):
        print('+', random.randint(1, 999), sep="", end="")
        print('-', random.randint(100, 9999), sep="", end="")
        print('-', random.randint(1000000, 99999999), sep="", end="\t")
        print(get_random_string())

main()
