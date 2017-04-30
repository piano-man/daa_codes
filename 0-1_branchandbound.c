#include <stdio.h>
#include <stdlib.h>
struct item{
  int weight;
  int price;
};
struct node{
  int profit;
  int weight;
  int bound;
  int count;
  int level;
};
void enque(struct node* nodes, struct node n, int* size){
  nodes[*size]=n;
  (*size)++;
}
struct node deque(struct node* nodes, int *size){
  struct node temp;
  temp=nodes[0];
  int i;
  for(i=0;i<*size-1;i++){
    nodes[i] = nodes[i+1];
  }
  (*size)--;
  return temp;
}
int knapsack_basic(int,int,int *,int *);
int knapsack_constrained(int,int,int *,int *,int);
int knapsack_multiple(int,int *,int,int *,int *);
int main()
{
  int i,W,n,m,*c,*w,p,*mW;
  scanf("%d",&n);
  scanf("%d",&W);
  c=(int *)malloc(n*sizeof(int));
  w=(int *)malloc(n*sizeof(int));
  for(i=0;i<n;i++)
    scanf("%d",&c[i]);
  for(i=0;i<n;i++)
    scanf("%d",&w[i]);
  printf("Knapsack Basic : %d\n",knapsack_basic(W,n,c,w));
  scanf("%d",&n);
  scanf("%d",&W);
  c=(int *)malloc(n*sizeof(int));
  w=(int *)malloc(n*sizeof(int));
  for(i=0;i<n;i++)
    scanf("%d",&c[i]);
  for(i=0;i<n;i++)
    scanf("%d",&w[i]);
  scanf("%d",&p);
  printf("Knapsack Constrained : %d\n",knapsack_constrained(W,n,c,w,p));
  /*scanf("%d",&n);
  scanf("%d",&m);
  mW=(int *)malloc(m*sizeof(int));
  c=(int *)malloc(n*sizeof(int));
  w=(int *)malloc(n*sizeof(int));
  for(i=0;i<m;i++)
    scanf("%d",&mW[i]);
  for(i=0;i<n;i++)
    scanf("%d",&c[i]);
  for(i=0;i<n;i++)
    scanf("%d",&w[i]);
  printf("Knapsack Multiple : %d\n",knapsack_multiple(m,mW,n,c,w));*/
  return 0;
}
void sort(struct item* array, int n){
  int i,j;
  struct item swap; 
  for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        { 
      float a = 1.0*array[j].price/array[j].weight;
      float b = 1.0*array[j+1].price/array[j+1].weight;
              if (a > b) 
              {
                swap = array[j];
                array[j] = array[j+1];
                array[j+1] = swap;
              }
        }
    }
}
int bound(struct node u, int n, int W, struct item *arr)
{
    if (u.weight >= W)
        return 0;
    int profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;
 
    while ((j < n) && (totweight + arr[j].weight <= W))
    {
        totweight    += arr[j].weight;
        profit_bound += arr[j].price;
        j++;
    }
    if (j < n)
        profit_bound += (W - totweight) * arr[j].price /
                                         arr[j].weight;
 
    return profit_bound;
}
int knapsack_constrained(int W,int n,int *c,int *w,int p)
{
  struct item *items = (struct item*)malloc(sizeof(struct item)*n);
  int i;
  for(i=0;i<n;i++){
    items[i].weight = w[i];
    items[i].price = c[i];
  }
  sort(items, n);
  struct node* queue = (struct node*)malloc(sizeof(struct node)*10000);
  struct node u, v;
  u.level=-1;
  u.profit=u.weight=u.bound=0;
  int size=0;
  u.count=0;
  int maxprofit=0;
  enque(queue, u, &size);
  while(size!=0){
    // if(u.level==n-1){
    //   continue;
    // }
    u = deque(queue, &size);
    v.level=u.level+1;
    v.count=u.count+1;
    v.profit=u.profit+items[v.level].price;
    v.weight=u.weight+items[v.level].weight;
    if(v.profit>maxprofit && v.weight<=W && v.count<=p){
      maxprofit=v.profit;
    }
    v.bound=bound(v, n, W, items);
    if(v.bound>=maxprofit && v.count<=p){
      enque(queue, v, &size);
    }
    v.weight = u.weight;
    v.count=u.count;
          v.profit = u.profit;
          v.bound = bound(v, n, W, items);
    if(v.bound>maxprofit && v.count<=p){
      enque(queue, v, &size);
    }
  }
  return maxprofit;
  
}

int knapsack_basic(int W,int n,int *c,int *w)
{
  struct item *items = (struct item*)malloc(sizeof(struct item)*n);
  int i;
  for(i=0;i<n;i++){
    items[i].weight = w[i];
    items[i].price = c[i];
  }
  sort(items, n);
  struct node* queue = (struct node*)malloc(sizeof(struct node)*10000);
  struct node u, v;
  u.level=-1;
  u.profit=u.weight=u.bound=0;
  int size=0;
  int maxprofit=0;
  enque(queue, u, &size);
  while(size!=0){
    if(u.level==n-1){
      continue;
    }
    u = deque(queue, &size);
    v.level=u.level+1;
    v.profit=u.profit+items[v.level].price;
    v.weight=u.weight+items[v.level].weight;
    if(v.profit>maxprofit && v.weight<=W){
      maxprofit=v.profit;
    }
    v.bound=bound(v, n, W, items);
    if(v.bound>maxprofit){
      enque(queue, v, &size);
    }
    v.weight = u.weight;
          v.profit = u.profit;
          v.bound = bound(v, n, W, items);
    if(v.bound>maxprofit){
      enque(queue, v, &size);
    }
  }
  return maxprofit;
}

int knapsack_multiple(int m,int *mW,int n,int *c,int *w)
{
  /* implement the multiple knapsack problem */ 
}