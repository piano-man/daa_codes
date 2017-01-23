#include <stdio.h>

#include <stdlib.h>

#define MAX 20

void maxheapify(int *, int, int);

int* buildmaxheap(int *, int);
int length;
int extract(int *a,int n)
{
    
    length = n;
    if(length==0)
        printf("no element left");
    int max = a[0];
    a[0] = a[length-1];
    length = length -1;
    maxheapify(a, 0,length);
    return max;
}

void increase_val (int *m, int i, int val)
{
    if(val < m[ i ])
    {
        printf("value can't be inserted");
    }
    m[ i ] = val;
    while( (i > 0) && (m[ i/2 ] < m[ i ])) 
    {
        //swap|(Arr[ i/2 ], Arr[ i ]);
        int temp = m[i/2];
        m[i/2]= m[i];
        m[i]=temp;
        i = i/2;
    }
}
void insert_val (int *m, int val,int length)
{
    //length = length + 1;
    m[ length ] = -1;  //assuming all the numbers greater than 0 are to be inserted in queue.
    increase_val (m, length, val);
}

void main()

{

    int i, t, n;

	int *a = calloc(MAX, sizeof(int));

    int *m = calloc(MAX, sizeof(int));

    printf("Enter no of elements in the array\n");

    scanf("%d", &n);

    printf("Enter the array\n");

    for (i = 0; i < n; i++) {

        scanf("%d", &a[i]);

    }

    m = buildmaxheap(a, n);

    printf("The heap is\n");

    for (t = 0; t < n; t++) {

        printf("%d\n", m[t]);

    }
    int max = extract(m,n);
    printf("the maximum element is : %d",max);
    printf("The heap is\n");

    for (t = 0; t < length; t++) {

        printf("%d\n", m[t]);

    }
    printf("enter the value you want to enter in the heap");
    int val;
    scanf("%d",&val);
    insert_val(m,val,length);
    printf("The heap is\n");

    for (t = 0; t < length+1; t++) {

        printf("%d\n", m[t]);

    }

}

int* buildmaxheap(int a[], int n)

{

    int heapsize = n;

    int j;

    for (j = n/2; j >= 0; j--) {

        maxheapify(a, j, heapsize);

    }

    return a;

}

void maxheapify(int a[], int i, int heapsize)

{

    int temp, largest, left, right, k;

    left = (2*i+1);

    right = ((2*i)+2);

    if (left >= heapsize)

        return;

    else {

        if (left < (heapsize) && a[left] > a[i]) 

            largest = left;

        else

            largest = i;

        if (right < (heapsize) && a[right] > a[largest])  

            largest = right;

        if (largest != i) {

            temp = a[i];

            a[i] = a[largest];

            a[largest] = temp;

            maxheapify(a, largest, heapsize);

        }

    }

}