#include "utils.h"

void swap(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

void rng(int* arr, int n) {
    int seed = 13515097;
    srand(seed);
    for(long i = 0; i < n; i++) {
        arr[i] = (int)rand();
    }
}

int getMax(int* arr, int n){
  int max_x = arr[0];
  for(int i=0; i<n; i++){
    max_x = ((max_x<arr[i])?arr[i]:max_x);
  }
  return max_x;
}

void buildDummy(int* arr, int n, int dummy_n, int max_x){
  for(long i = n; i < dummy_n; i++) {
    arr[i]=max_x;
  }
}

void printArr(int* arr, int lo, int n){
    for(int i=lo; i<lo+n; i++){
      printf("%d\n", arr[i]);
    }
}

void initialize(int* arr, int n, int dummy_n){
  rng(arr,n);
  int max_x = getMax(arr,n);
  buildDummy(arr,n,dummy_n,max_x);
}

int getPowTwo(int n){
  int d=1;
  while (d>0 && d<n) d<<=1;
  return d;
}

void writeToFile(int* arr, int n, char* path){
  FILE* f = fopen(path,"w");
  for(int i=0; i<n; i++) {
      fprintf(f, "%d\n", arr[i]);
  }
  fclose(f);
}
