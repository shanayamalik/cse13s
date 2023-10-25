#!/bin/bash

make

echo testing histogram example 1
cat > example1.txt << EOF
3 -4 5 1 7 0
8 0 15 12 3 5
3 3 3 3 3
EOF
cat > example1.out << EOF
[  0:  0] **
[  1:  1] *
[  2:  2] 
[  3:  3] *******
[  4:  4] 
[  5:  5] **
[  6:  6] 
[  7:  7] *
[  8:  8] *
[  9:  9] 
[ 10: 10] 
[ 11: 11] 
[ 12: 12] *
[ 13: 13] 
[ 14: 14] 
[ 15: 15] *
EOF
./histogram < example1.txt > testing.out
diff example1.out testing.out
rm example1.txt example1.out

echo testing histogram example 2
cat > example2.txt << EOF
3 -4 5 1 7 0
8 0 15 12 3 5
18
19 20 30 7 12
50
34
32
19
44
EOF
cat > example2.out << EOF
[  0:  3] *****
[  4:  7] ****
[  8: 11] *
[ 12: 15] ***
[ 16: 19] ***
[ 20: 23] *
[ 24: 27] 
[ 28: 31] *
[ 32: 35] **
[ 36: 39] 
[ 40: 43] 
[ 44: 47] *
[ 48: 51] *
[ 52: 55] 
[ 56: 59] 
[ 60: 63] 
EOF
./histogram < example2.txt > testing.out
diff example2.out testing.out
rm example2.txt example2.out

echo testing histogram example 3
cat > example3.txt << EOF
150
EOF
cat > example3.out << EOF
[  0: 15] 
[ 16: 31] 
[ 32: 47] 
[ 48: 63] 
[ 64: 79] 
[ 80: 95] 
[ 96:111] 
[112:127] 
[128:143] 
[144:159] *
[160:175] 
[176:191] 
[192:207] 
[208:223] 
[224:239] 
[240:255] 
EOF
./histogram < example3.txt > testing.out
diff example3.out testing.out
rm example3.txt example3.out

echo testing histogram example 4
cat > example4.txt << EOF
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 150
EOF
cat > example4.out << EOF
[  0: 15] ***************
[ 16: 31] *
[ 32: 47] 
[ 48: 63] 
[ 64: 79] 
[ 80: 95] 
[ 96:111] 
[112:127] 
[128:143] 
[144:159] *
[160:175] 
[176:191] 
[192:207] 
[208:223] 
[224:239] 
[240:255] 
EOF
./histogram < example4.txt > testing.out
diff example4.out testing.out
rm example4.txt example4.out
