# include<stdio.h>
# include<stdlib.h>
# include<limits.h>
struct hash
{
    int arr[100];
    int size;
}
main()
{   
    struct hash h1;
    int n;
    scanf("%d",&n);
    int arr1[n];
    int i;
    for(i=0;i<n;i++)
    {
        scanf("%d",&(arr1[i]));
    }
    for(i=0;i<n;i++)
    {
        h1.arr[i]= INT_MIN ;
    }
    for(i=0;i<n;i++)
    {
        if(h1.arr[arr1[i]])
    }


}