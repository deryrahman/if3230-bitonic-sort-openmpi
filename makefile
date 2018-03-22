make: src/bitonic_sort.c
	mpicc -o bitonic_sort src/main.c src/bitonic_sort.c src/utils.c -g -Wall

run: make
	mpirun -np 2 ./bitonic_sort 5000
	mpirun -np 2 ./bitonic_sort 5000
	mpirun -np 2 ./bitonic_sort 5000
	mpirun -np 2 ./bitonic_sort 50000
	mpirun -np 2 ./bitonic_sort 50000
	mpirun -np 2 ./bitonic_sort 50000
	mpirun -np 2 ./bitonic_sort 100000
	mpirun -np 2 ./bitonic_sort 100000
	mpirun -np 2 ./bitonic_sort 100000
	mpirun -np 2 ./bitonic_sort 200000
	mpirun -np 2 ./bitonic_sort 200000
	mpirun -np 2 ./bitonic_sort 200000
	mpirun -np 2 ./bitonic_sort 400000
	mpirun -np 2 ./bitonic_sort 400000
	mpirun -np 2 ./bitonic_sort 400000
