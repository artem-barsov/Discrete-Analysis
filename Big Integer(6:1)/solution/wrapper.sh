#!/usr/bin/env bash

nTests=100
operation=

make -s                                                 &&

echo -n "Generating tests... "                          &&
python generator.py "$nTests" "$operation" > tests.txt  &&
echo "OK."                                              &&

echo -n "Testing python BigInteger... "                 &&
time python BigInteger.py < tests.txt > py_out.txt      &&
echo "OK."                                              &&

echo -n "Testing my C++ BigInteger... "                 &&
time ./solution < tests.txt > cpp_out.txt               &&
echo "OK."                                              &&

echo -n "Comparing output... "                          &&
diff py_out.txt cpp_out.txt                             &&
echo "OK."

echo "Start benchmark? [Y/n]"
read ans
case $ans in y|Y|yes|Yes|'' )
    ./benchmark.sh ;;
esac

make -s clean
