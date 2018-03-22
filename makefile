make: src/bitonic_sort.c
	mpicc -o bitonic_sort src/main.c src/bitonic_sort.c src/quick_sort.c src/utils.c -g -Wall

run: make
	mpirun -np 8 ./bitonic_sort 128
