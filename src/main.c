#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>
#include "bitonic_sort.h"
#include "quick_sort.h"

struct timeval st, et;

int main(int argc,char *argv[]) {
  int comm_sz;
  int my_rank;
  int local_n;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int n = atoi(argv[1]);
  int dummy_n = getPowTwo(n);
  local_n = dummy_n/comm_sz;
  int arr[dummy_n];
  // int local_arr[local_n];
  if(my_rank == 0){
    initialize(arr, n, dummy_n);
    // printArr(arr,0,dummy_n);
    for(int i=1; i<comm_sz; i++){
      MPI_Send(arr, dummy_n, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
  } else {
    MPI_Recv(arr, dummy_n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  gettimeofday(&st,NULL);
  bitSort(arr,0,dummy_n,1,comm_sz);
  gettimeofday(&et,NULL);
  if(my_rank == 0){
    int elapsed_serial = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
    printf("Execution serial time: %d micro sec\n",elapsed_serial);
  }


  // if(my_rank==0){
  //   printArr(arr,0,dummy_n);
  // }
  // if(my_rank !=0){
  //   int pos = my_rank*local_n;
  //   MPI_Send(arr+pos, local_n, MPI_INT, 0, 0, MPI_COMM_WORLD);
  // } else {
  //   for(int i=0; i<comm_sz; i++){
  //     int pos = i*local_n;
  //     if(i!=0) {
  //       MPI_Recv(arr+pos, local_n, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  //     }
  //     printf("From proc %d\n", i);
  //     printArr(arr,pos,local_n);
  //   }
  // }

  MPI_Finalize();
  return 0;
}
