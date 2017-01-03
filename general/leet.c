#include <stdio.h>



void quickSort( int a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
    // divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
  
}



int partition( int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
    
   while( 1)
   {
    do ++i; while( a[i] <= pivot && i <= r );
    do --j; while( a[j] > pivot );
    if( i >= j ) break;
    t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}


int singleNumber(int* nums, int numsSize) {
    quickSort(nums,0,numsSize-1);
    for(int j = 0; j < numsSize; j++){
        printf("%i ",nums[j]);
    }
    int i = 0;
    if (numsSize == 1){
        return nums[0];
    }
    while(i < numsSize){
        printf("%i vs %i\n",nums[i],nums[i+1]);
        if (nums[i] == nums[i+1]){
            i+=2;
        }
        else{
            break;
        }
    }
    return nums[i];
}



int main(void){
  int a[21] = {17,12,5,-6,12,4,17,-5,2,-3,2,4,5,16,-3,-4,15,15,-4,-5,-6};
  printf("Number:%i\n",singleNumber(a,21));
  return 1;
}