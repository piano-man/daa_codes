//segmentation fault
# include<stdio.h>
# include<stdlib.h>
# include<limits.h>
int max(int n1,int n2)
{
    if(n1>n2)
    return n1;
    else 
    return n2;
}
main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    int i;
    int sum = 0;
    int maxlen=0;  
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    int hsum[INT_MAX] = { INT_MIN };
    //for(i=0;i<n;i++)
    //{
      //  sum+=arr[i];
        //hsum[sum]=i;
    
    //}
    //sum=0;
    for(i=0;i<n;i++)
    {
        sum+=arr[i];
        if(sum==0)
        {
            maxlen++;

        }
        else if(sum!=0)
        {   
            if(hsum[sum]== INT_MIN)
            {
                hsum[sum]=i;
                maxlen  = 0;

            }
            if(hsum[sum]!= INT_MIN)
            {
                maxlen = max(maxlen,i-hsum[sum]);
            }

        }

    }
    printf("the longest subarray is %d",maxlen);
}