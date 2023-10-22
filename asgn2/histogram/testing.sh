#!/bin/bash

make

echo testing histogram example 1
./histogram < example1.txt > testing.out
diff example1.out testing.out

echo testing histogram example 2
./histogram < example2.txt > testing.out
diff example2.out testing.out

echo testing histogram example 3
./histogram < example3.txt > testing.out
diff example3.out testing.out

echo testing histogram example 4
./histogram < example4.txt > testing.out
diff example4.out testing.out
