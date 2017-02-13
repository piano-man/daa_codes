//wrong output
# include<stdio.h>
# include<stdlib.h>
# include<limits.h>
main()
{
    int arr[5] = {9,7,5,3};
    int k = 6;
    int freq[100];
    int i;
    int rem;
    for(i=0;i<4;i++)
    {
        freq[arr[i]%k]++;

    }
    for(i=0;i<5;i++)
    {
        rem  = arr[i]%k;
        if(rem!=0 && k/rem == 2)
        {
            if(freq[rem]%2==0)
            arr[i]=INT_MIN;
        }
        else if(rem == 0)
        {
            if(freq[rem]%2==0)
            arr[i]=INT_MIN;
        
        }
        else
        {
            if(freq[rem]==freq[k-rem])
            arr[i]= INT_MIN ;

        }

    }
    int count = 0;
    for(i=0;i<4;i++)
    {
        if(arr[i]> -10000)
        count = 1;
    
    }
    if(count ==0)
    printf("the array can be split");
    else
    printf("the array cannot be split");
}