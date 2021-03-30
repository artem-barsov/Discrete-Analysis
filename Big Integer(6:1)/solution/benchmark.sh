#!/usr/bin/env bash

nTests=1000
ops=('+' '-' '*' '/' '^' '<' '>' '=')

make -s && {
    set -f
    echo "Number of tests: $nTests"
    echo -e "Oper.\tPython\tMy C++"
    for op in ${ops[*]}; do
        python generator.py $nTests $op > tests.txt
        echo -ne "$op\t"
        echo -ne $(/usr/bin/time -f "%e" python BigInteger.py <tests.txt 2>&1 1>/dev/null) "\t"
        echo -e $(/usr/bin/time -f "%e" ./solution <tests.txt 2>&1 1>/dev/null)
    done
    set +f
}
make -s clean
