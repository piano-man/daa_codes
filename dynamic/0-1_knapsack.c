// A Dynamic Programming based solution for 0-1 Knapsack problem
#include<stdio.h>
 int *p1;
 int v1;
 int v2;
 int K[1000][1000];
 
// A utility function that returns maximum of two integers
int max(int a, int b) { return (a > b)? a : b; }
 
// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
   int i, w;
   //v1 = n+1;
   //v2 = W+1;
   //int K[n+1][W+1];
 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }
   //p1 = K;
 
   return K[n][W];
}
//printing elements added
printlist(int W,int n,int wt[],int val[])
{
    
    while(W>0)
    {
        if(K[n-1][W]==K[n][W])
        {
            
        }
        else
        {
            printf("%d \n",wt[n-1]);

        }
        W = W-wt[n-1];
        n= n-1;
        
    }
}
 
int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int  W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d \n", knapSack(W, wt, val, n));
    printlist(W,n,wt,val);
    return 0;
}