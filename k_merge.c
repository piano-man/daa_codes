#include<stdio.h>
#include<stdlib.h>
#define INT_MAX 1000
 
typedef struct heapNode{
        int data;
        int arrayNum;
        int itemNum;
} heapNode ;
 
int leftChild(int i){
    return (i*2)+1;
}
int rightChild(int i){
    return (2*i)+2;
}
 
heapNode * createNode( int data, int arrayNum, int itemNum){
    heapNode * newNode = (heapNode *)malloc(sizeof(heapNode));
    newNode->data = data;
    newNode->arrayNum = arrayNum;
    newNode->itemNum = itemNum;
     
    return newNode;
}
 
void swap(heapNode * a[], int i, int j){
    heapNode * temp = a[i];
    a[i] = a[j];
    a[j] = temp;    
}
 
void minHeapify(heapNode * a[], int i, int len){
    int smallest =i;
    int left, right;
     
    left = leftChild(i);
    right = rightChild(i);
     
    if(left <= len && a[i]->data > a[left]->data){
        smallest = left;
    }
    if(right <= len && a[smallest]->data > a[right]->data){
        smallest = right;
    }
    if(smallest != i){
        swap(a, i, smallest);
        minHeapify(a, smallest, len);
    }
}
 
void buildHeap(heapNode *a[], int len){
    int i = len/2 +1;
    for(; i>=0; i--){
        minHeapify(a,i, len);
    }
}
 
void mergeKSortedArrays(int a[5][5], int N, int K, int result[]){
   int i;
   heapNode *minHeap[K];
   /* Put all elements in an array */
   for(i=0;i<K; i++){
       minHeap[i] = createNode(a[i][0], i, 0);
   }
 
   /* Build min heap with those entered elements */
   buildHeap(minHeap,K-1);
         
   /* Now we have to take every element one by one and replace 
    root with that and heapify again */
   for(i=0; i<N*K; i++){
      heapNode * minNode = minHeap[0];
                                         
      /* Put the root of min heap in result array */
      result[i] = minNode->data;
      /* If there are elements to be considered in that array */
        if(minNode->itemNum + 1< N){
            minHeap[0] = createNode(
                                    a[minNode->arrayNum][minNode->itemNum + 1],
                                    minNode->arrayNum, minNode->itemNum + 1
                              );
        }       
        /* else put INT_MAX at root */
        else{
            minHeap[0] = createNode(INT_MAX, minNode->arrayNum, 
                         minNode->itemNum + 1);
        }
        /* Heapify again */
         minHeapify(minHeap, 0, K-1);
   }       
}
 
int main(){
 
    int N = 5;
    int K = 4;
    int a[4][5] = { 
            2,3,5,6,7,
                    4,7,8,9,10,
                    3,5,11,13,45,
                    1,4,5,7,8
                  };
 
   int result[K*N];
   mergeKSortedArrays(a, N, K, result);          
 
   for(int i=0; i<N*K; i++){
       printf("%d  ", result[i]);
   }
    
   return 0;
}