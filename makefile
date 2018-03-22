make: src/bitonic_sort.c
	mpicc -o bitonic_sort src/main.c src/bitonic_sort.c src/utils.c -g -Wall

run: make
	mpirun -np 1 ./bitonic_sort 10000
	mpirun -np 2 ./bitonic_sort 10000
