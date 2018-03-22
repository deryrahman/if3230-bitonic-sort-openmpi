#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>
#include "bitonic_sort.h"
#include "utils.h"

struct timeval st, et;

int main(int argc,char *argv[]) {
  int comm_sz;
  int my_rank;
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int n = atoi(argv[1]);
  int dummy_n = getPowTwo(n);
  int arr[dummy_n];
  int arr2[dummy_n];
  if(my_rank == 0){
    initialize(arr, n, dummy_n);
    memcpy(arr2,arr,dummy_n*sizeof(int));
    writeToFile(arr,n,"./data/input");
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
    int elapsed_paralel = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
    printf("Execution paralel time: %d micro sec\n",elapsed_paralel);
    writeToFile(arr,n,"./data/output");

    gettimeofday(&st,NULL);
    bitSortSer(arr2,0,dummy_n,1);
    gettimeofday(&et,NULL);
    int elapsed_serial = ((et.tv_sec - st.tv_sec) * 1000000) + (et.tv_usec - st.tv_usec);
    printf("Execution serial time: %d micro sec\n",elapsed_serial);

    // calculate speedup
    printf("Speedup : %.3f\n",(float)elapsed_serial/elapsed_paralel);
  }

  MPI_Finalize();
  return 0;
}
