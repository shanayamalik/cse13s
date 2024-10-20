#!/bin/bash

make

echo testing coolness with no arguments
cat > noInputs.txt << EOF
Temp	Wind	Coolness
-10.0	5.0	-22.3
-10.0	10.0	-28.3
-10.0	15.0	-32.2

0.0	5.0	-10.5
0.0	10.0	-15.9
0.0	15.0	-19.4

10.0	5.0	1.2
10.0	10.0	-3.5
10.0	15.0	-6.6

20.0	5.0	13.0
20.0	10.0	8.9
20.0	15.0	6.2

30.0	5.0	24.7
30.0	10.0	21.2
30.0	15.0	19.0

40.0	5.0	36.5
40.0	10.0	33.6
40.0	15.0	31.8
EOF
./coolness > testing.out
diff noInputs.txt testing.out
rm noInputs.txt

echo testing coolness with one argument
cat > oneInput.txt << EOF
Temp	Wind	Coolness
32.0	5.0	27.1
32.0	10.0	23.7
32.0	15.0	21.6
EOF
./coolness 32.0 > testing.out
diff oneInput.txt testing.out
rm oneInput.txt

echo testing coolness with two arguments
cat > twoInput.txt << EOF
Temp	Wind	Coolness
32.5	10.0	24.3
EOF
./coolness 32.5 10.0 > testing.out
diff twoInput.txt testing.out
rm twoInput.txt
