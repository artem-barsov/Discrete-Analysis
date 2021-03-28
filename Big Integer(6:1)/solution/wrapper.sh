#!/usr/bin/env bash

nTests=1000
operation==

make                                                    &&
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
make clean
