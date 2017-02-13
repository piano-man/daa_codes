//wrong output
# include<stdio.h>
# include<stdlib.h>

void swap(int *n1,int *n2)
{
    int temp;
    temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
int min_heapify(int arr[],int i,int *n)
{
    int min;
    int l = 2*i+1;
    int r = 2*i+2;
    min = i;
    if(l<*n && arr[l]<arr[i])
        min = l;
    if(r<n && arr[r]<arr[i])
        min = r;
    if(min!=i)
    {
        swap(&arr[min],&arr[i]);
        min_heapify(arr,min,n);
    }
}
int extract(int arr[],int *n)
{
    int min = arr[0];
    arr[0]=arr[*n];
    (*n)--;
    min_heapify(arr,0,n);
    return min;

}
int build(int arr[])
{
    int i;
    int n = (int)sizeof(arr)/sizeof(arr[0]);
    for(i=n/2-1;i>=0;i--)
    {
        min_heapify(arr,i,&n);

    }
}
int insert(int arr[],int ele,int *n)
{
    (*n)++;
    int i = *n-1;
    arr[i]=ele;
    int parent = (i-1)/2;
    if(arr[i]<arr[parent])
        swap(&arr[i],&arr[parent]);


}
main()
{
    int i;
    printf("enter the number of ropes");
    int n;
    scanf("%d",&n);
    int arr[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    build(arr);
    while(n!=1)
    {
    int n1 = extract(arr,&n);
    int n2 = extract(arr,&n);
    int ele = n1+n2;
    insert(arr,ele,&n);
    }
    printf("the minimum value is %d",arr[0]);


}