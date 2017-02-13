#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
   int n1, n2, capacity;
   int *val;
} medHeap;

medHeap initMedHeap ( int n )
{
   medHeap H;

   H.n1 = H.n2 = 0;
   H.capacity = n;
   H.val = (int *)malloc(n * sizeof(int));
   return H;
}

medHeap insMaxHeap ( medHeap H, int x )
{
   int i, p, t;

   H.val[H.n1] = x;
   i = H.n1;
   while (i > 0) {
      p = (i - 1) / 2;
      if (H.val[p] >= H.val[i]) break;
      t = H.val[p]; H.val[p] = H.val[i]; H.val[i] = t;
      i = p;
   }
   H.n1++;
   return H;
}

medHeap insMinHeap ( medHeap H, int x )
{
   int i, p, t;

   H.val[H.capacity-1-H.n2] = x;
   i = H.n2;
   while (i > 0) {
      p = (i - 1) / 2;
      if (H.val[H.capacity-1-p] <= H.val[H.capacity-1-i]) break;
      t = H.val[H.capacity-1-p];
      H.val[H.capacity-1-p] = H.val[H.capacity-1-i];
      H.val[H.capacity-1-i] = t;
      i = p;
   }
   H.n2++;
   return H;
}

medHeap delMaxHeap ( medHeap H )
{
   int i, l, r, m, t;

   H.n1--; H.val[0] = H.val[H.n1]; i = 0;
   while (i < H.n1) {
      l = 2*i + 1; r = 2*i + 2;
      if (l >= H.n1) break;
      if (l == H.n1 - 1) m = l;
      else m = (H.val[l] >= H.val[r]) ? l : r;
      if (H.val[i] >= H.val[m]) break;
      t = H.val[i]; H.val[i] = H.val[m]; H.val[m] = t;
      i = m;
   }
   return H;
}

medHeap delMinHeap ( medHeap H )
{
   int i, l, r, m, t;

   H.n2--; H.val[H.capacity-1] = H.val[H.capacity-1-H.n2]; i = 0;
   while (i < H.n2) {
      l = 2*i + 1; r = 2*i + 2;
      if (l >= H.n2) break;
      if (l == H.n2 - 1) m = l;
      else m = (H.val[H.capacity-1-l] <= H.val[H.capacity-1-r]) ? l : r;
      if (H.val[H.capacity-1-i] <= H.val[H.capacity-1-m]) break;
      t = H.val[H.capacity-1-i];
      H.val[H.capacity-1-i] = H.val[H.capacity-1-m];
      H.val[H.capacity-1-m] = t;
      i = m;
   }
   return H;
}

int getMedian ( medHeap H )
{
   if ((H.n1 == 0) && (H.n2 == 0)) {
      fprintf(stderr, "*** Error in getMedian: Heap is empty\n");
      return -1;
   }
   return ((H.n1 == H.n2) ? H.val[0] : H.val[H.capacity-1]);
}

medHeap insMedHeap ( medHeap H, int x )
{
   int m;

   if ((H.n1 == 0) && (H.n2 == 0)) {            /* Insertion in an empty heap */
      H.val[H.capacity-1] = x;
      H.n2 = 1;
   } else if (H.n1 + H.n2 == H.capacity) {        /* Insertion in a full heap */
      fprintf(stderr, "*** Error in insMedHeap: Heap is full\n");
   } else {
      m = getMedian(H);                             /* Get the current median */
      if (x <= m) {                                      /* Insert in maxheap */
         if (H.n2 == H.n1) {
            H = delMaxHeap(H);         /* Deletion of m from the smaller half */
            H = insMinHeap(H,m);         /* Insertion of m in the larger half */
         }
         H = insMaxHeap(H,x);           /* Insertion of x in the smaller half */
      } else {                                           /* Insert in minheap */
         if (H.n2 == H.n1 + 1) {
            H = delMinHeap(H);          /* Deletion of m from the larger half */
            H = insMaxHeap(H,m);        /* Insertion of m in the smaller half */
         }
         H = insMinHeap(H,x);            /* Insertion of x in the larger half */
      }
   }
   return H;
}

medHeap delMedHeap ( medHeap H )
{
   if (H.n1 == H.n2) {                      /* Deletion from the smaller half */
      if (H.n1 == 0)
         fprintf(stderr, "*** Error in delMedHeap: MaxHeap is empty\n");
      else
         H = delMaxHeap(H);
   } else {                                  /* Deletion from the larger half */
      if (H.n2 == 0)
         fprintf(stderr, "*** Error in delMedHeap: MinHeap is empty\n");
      else
         H = delMinHeap(H);
   }
   return H;
}

medHeap medHeapSort ( medHeap H )
{
   int m;

   while (H.n1 + H.n2 > 0) {
      m = getMedian(H);
      H = delMedHeap(H);
      if (H.n1 == H.n2) H.val[H.capacity-1-H.n2] = m;  /* Deletion in minheap */
      else H.val[H.n1] = m;                            /* Deletion in maxheap */
   }
   return H;
}

void printArray ( medHeap H )
{
   int i;

   printf("    ");
   for (i=0; i<H.capacity; ++i) {
      printf("%5d", H.val[i]);
      if (i % 15 == 14) printf("\n    ");
   }
   if (i % 15) printf("\n");
}

int main ( int argc, char *argv[] )
{
   int n, i, x;
   medHeap H;

   srand((unsigned int)time(NULL));
   if (argc > 1) n = atoi(argv[1]); else scanf("%d", &n);

   H = initMedHeap(n);
   printf("\n+++ MedHeap initialized\n");

   printf("\n+++ Going to insert elements one by one in MedHeap\n");
   for (i=0; i<n; ++i) {
      x = 1 + rand() % 9999;
      H = insMedHeap(H,x);
      printf("    Insert(%4d) done. Current median = %4d.\n", x, getMedian(H));
   }

   H = medHeapSort(H);
   printf("\n+++ Median Heap Sort done\n");
   printArray(H);
   
   free(H.val);

   exit(0);
}