#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ull;  /* We need 64-bit integers */

typedef struct {
   int a, b;
   ull s;
} triple;                            /* An element in the heap */

typedef struct {
   unsigned int size;                /* Number of elements in the heap */
   triple *data;                     /* The contiguous representation */
} heap;                              /* Data type heap */

/* Initialize H with B triples (a,-(a-1),a^3-(a-1)^3) for a = 1,2,...,B. */
heap init ( int B )
{
   heap H;
   int a;

   H.size = B;
   H.data = (triple *)malloc(B * sizeof(triple));

   /* We have a^3 - (a-1)^3 = 3a^2 - 3a + 1, which increases with a.
      So we initialize H to a sorted array. There is no need to run
      heapify() or makeheap(). */
   for (a=1; a<=B; ++a) {
      H.data[a-1].a = a;
      H.data[a-1].b = -(a-1);
      H.data[a-1].s = (ull)3 * (ull)a * (ull)(a - 1) + (ull)1;
   }

   return H;
}

/* Standard min-heap insertion function */
heap insert ( heap H, int a, int b )
{
   int i, p;
   triple t;

   i = H.size++;
   H.data[i] = (triple){a,b,(ull)a*(ull)a*(ull)a+(ull)b*(ull)b*(ull)b};
   while (i > 0) {
      p = (i-1) / 2;
      if (H.data[p].s <= H.data[i].s) break;
      t = H.data[p]; H.data[p] = H.data[i]; H.data[i] = t;
      i = p;
   } 
   return H;
}

/* Standard min-heap deletemin function */
heap deletemin ( heap H )
{
   int i, l, r, m;
   triple t;

   H.data[0] = H.data[--H.size];
   i = 0;
   while (1) {
      l = 2 * i + 1; r = l + 1;
      if (l >= H.size) break;
      if (r >= H.size) m = l;
      else m = (H.data[l].s <= H.data[r].s) ? l : r;
      if (H.data[i].s <= H.data[m].s) break;
      t = H.data[i]; H.data[i] = H.data[m]; H.data[m] = t;
      i = m;
   }
   return H;
}

/* This implements the loop of deletemin() and insert() */
void cabtaxisearch ( heap H, int B )
{
   triple match[10], t;
   int maxlen, idx, i;

   maxlen = idx = 0; t = (triple){(ull)0,0,0};
   while (H.size > 0) {
      t = H.data[0];     /* Remember the current minimum of H */
      H = deletemin(H);  /* Delete minimum from H */

      /* Given (a,b), we first need to find a suitable next(b):
         If b < 0, then next(b) = b + 1.
         If b = 0, then next(b) = a (since pairs (a,1),(a,2),...,(a,a-1) are avoided).
         If b >= a but b < B, then next(b) = b + 1.
         If b = B, no next(b) exists.
         Insert (a,next(b)) in H, provided that next(b) is defined. */
      if (t.b < 0) H = insert(H,t.a,t.b+1);
      else if (t.b == 0) H = insert(H,t.a,t.a);
      else if (t.b < B) H = insert(H,t.a,t.b+1);

      /* If this mimimum sum is same as the previous minimum sum */
      if ((idx > 0) && (t.s == match[idx-1].s)) {
         match[idx++] = t;
      } else {
         match[0] = t; idx = 1;
      }

      /* If a longer sequence of equal sums is located */
      if (idx > maxlen) {
         maxlen = idx;
         printf("CT(%d) = %Lu\n", maxlen, match[maxlen-1].s);
         for (i=0; i<maxlen; ++i) {
            printf("      = (%d)^3 + (%d)^3\n", match[i].a, match[i].b);
         }
      }
   }
}

/* Free allocated memory */
void windup ( heap H )
{
   free(H.data);
}

int main ( int argc, char *argv[] )
{
   int B;
   heap H;

   if (argc >= 2) B = atoi(argv[1]); else {
      printf("Enter bound B: "); scanf("%d", &B);
   }

   H = init(B);
   cabtaxisearch(H,B);
   windup(H);

   exit(0);
}