#include "bitonic_sort.h"

void bitSwap(int* a, int* b, int dir){
  if((*a>*b) == dir){
    swap(a,b);
  }
}

void bitMerge(int* arr, int lo, int n, int dir){
  if(n>1){
    int m = n/2;
    for(int i=lo; i<lo+m; i++){
      bitSwap(arr+i, arr+(i+m), dir);
    }
    bitMerge(arr, lo, m, dir);
    bitMerge(arr, lo+m, n-m, dir);
  }
}

void bitSort(int* arr, int lo, int n, int dir, int n_proc){
  int m = n/2;
  int my_rank;
  int comm_sz;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  if(n_proc>1){
    int gap = n_proc>>1;
    if((my_rank%n_proc)<(n_proc>>1)){
      bitSort(arr, lo, m, 1, n_proc>>1);
      // printf("<- | n proc = %d | rank = %d | idx = %d | lo =  %d | n = %d | gap %d\n", n_proc, my_rank, my_rank*m, lo, n, gap);
      int neighbour_proc = (my_rank+gap)%comm_sz;
      // printf("<- | rank = %d | | lo =  %d | n = %d | gap %d\nsend to proc %d\n", my_rank, lo, n, gap, neighbour_proc);
      MPI_Send(arr+lo, m, MPI_INT, neighbour_proc, gap, MPI_COMM_WORLD);
      MPI_Recv(arr+lo+m, m, MPI_INT, neighbour_proc, gap, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      bitMerge(arr, lo, n, dir);
    } else {
      bitSort(arr, lo+m, m, 0, n_proc>>1);
      // printf("-> | n proc = %d | rank = %d | idx = %d | lo =  %d | n = %d | gap %d\n", n_proc, my_rank, my_rank*m, lo, n, gap);
      int neighbour_proc = (my_rank-gap+comm_sz)%comm_sz;
      // printf("-> | rank = %d | | lo =  %d | n = %d | gap %d\nsend to proc %d\n", my_rank, lo, n, gap, neighbour_proc);
      MPI_Recv(arr+lo, m, MPI_INT, neighbour_proc, gap, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send(arr+lo+m, m, MPI_INT, neighbour_proc, gap, MPI_COMM_WORLD);
      bitMerge(arr, lo, n, dir);
    }
  } else {
    // printf("n %d rank %d lo %d\n", n, my_rank, lo);
    // if(my_rank*n == lo){
      bitSortSer(arr,lo,n,dir);
    // }
  }
}

void bitSortSer(int* arr, int lo, int n, int dir){
  int m = n/2;
  if(n>1){
    // printf("<- \n");
    bitSortSer(arr, lo, m, 1);
    // printf("-> \n");
    bitSortSer(arr, lo+m, m, 0);
    // printf("merge \n");
    bitMerge(arr, lo, n, dir);
  }
}
