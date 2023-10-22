#!/bin/bash

rm coolness
make

echo testing coolness with no arguments
./coolness > testing.out
diff noInputs.txt testing.out

echo testing coolness with one argument
./coolness 32.0 > testing.out
diff oneInput.txt testing.out

echo testing coolness with two arguments
./coolness 32.5 10.0 > testing.out
diff twoInput.txt testing.out

