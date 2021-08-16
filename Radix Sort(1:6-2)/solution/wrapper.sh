#!/bin/sh

make                                            &&
echo "Built main program"                       &&
cd benchmark                                    &&
make                                            &&
echo "Built benchmark"                          &&
python ../generator.py 100000 > ../test.txt     &&
echo "Test generation completed"                &&
./benchmark < ../test.txt                       &&
echo "Sorting completed"                        &&
diff radix_out.txt stl_out.txt                  &&
echo "Comparison completed"                     &&
make clean                                      &&
cd ..                                           &&
make clean
