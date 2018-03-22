#include "quick_sort.h"

int partition(int* arr, int lo, int hi, int up){
  int pivot = arr[hi];
  int i = (lo - 1);

  for (int j = lo; j <= hi- 1; j++){
    if (((arr[j] <= pivot) && up) || ((arr[j] >= pivot) && !up)){
      i++;
      swap(arr+i, arr+j);
    }
  }
  swap(arr+(i+1), arr+hi);
  return (i + 1);
}

void quickSort(int* arr, int lo, int hi, int up){
  if (lo < hi){
    int pi = partition(arr, lo, hi, up);
    quickSort(arr, lo, pi - 1, up);
    quickSort(arr, pi + 1, hi, up);
  }
}
