#include <stdio.h>
#include <stdlib.h>

int knapsack_basic(int,int,int *,int *);
int knapsack_constrained(int,int,int *,int *,int);
int knapsack_multiple(int,int *,int,int *,int *);
int main()
{
	//freopen("input.txt", "r+", stdin);
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
  scanf("%d",&n);
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
  printf("Knapsack Multiple : %d\n",knapsack_multiple(m,mW,n,c,w));
  return 0;
}

struct node {
	int level;
	int profit;
	int bound;
	int cnt;
	int wt;
};

struct node2 {
	int level;
	int profit;
	int bound;
	int wt[10];
};
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
void bub_sort(int n, int *c, int *w) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n - 1; j++) {
			float val = c[j];
			float val2 = c[j + 1];
			val/=w[j];
			val2/=w[j + 1];
			if(val < val2) {
				swap(c + j, c + j + 1);
				swap(w + j, w + j + 1);
			}
		}
	}
}
void push(struct node qu[], int *front, int *rear, struct node temp) {
	if(*front == -1 && *rear == -1) {
		*front = *front + 1;
	}
	*rear = (*rear + 1)%40000;
	qu[*rear] = temp;
}
struct node pop(struct node qu[], int *front, int *rear) {
	struct node temp;
	temp = qu[*front];
	if(*front == *rear) {
		*front = -1;
		*rear = -1;
	}
	else {
		*front = (*front + 1)%40000;
	}
	return temp;
}

void push2(struct node2 qu[], int *front, int *rear, struct node2 temp) {
	if(*front == -1 && *rear == -1) {
		*front = *front + 1;
	}
	*rear = (*rear + 1)%40000;
	qu[*rear] = temp;
}
struct node2 pop2(struct node2 qu[], int *front, int *rear) {
	struct node2 temp;
	temp = qu[*front];
	if(*front == *rear) {
		*front = -1;
		*rear = -1;
	}
	else {
		*front = (*front + 1)%40000;
	}
	return temp;
}
int empty(int front, int rear) {
	if(front == -1 && rear == -1) {
		return 1;
	}
	return 0;
}
int calc_bound(int n, int *c, int *w, struct node u, int W, int k) {
	if(u.wt >= W) {
		return 0;
	}
	int profit_b = u.profit;
	int j = u.level + 1;
	int tot = u.wt;
	int ctr = u.cnt;
	while((ctr < k) && (j < n) && (tot + w[j] <= W)) {
		profit_b+=c[j];
		tot+=w[j];
		j++;
		ctr++;
	}
	if((j < n) && (ctr < k)) {
		profit_b += (((W - tot) * c[j])/w[j] + 1);
	}
	return profit_b;
}
int calc_bound2(int m, int *mW, int n, int *c, int *w, struct node2 u, int id) {
	if(u.wt[id] > mW[id]) {
		return 0;
	}
	int profit_b = u.profit;
	int j = u.level + 1;
	int sum = 0;
	int i;
	for(i = 0; i < m; i++) {
		int tot = u.wt[i];
		while(j < n && tot + w[j] <= mW[i]) {
			profit_b += c[j];
			tot+=w[j];
			j++;
		}
		sum+=mW[i] - tot;
	}
	while(j < n && w[j] <= sum) {
		profit_b+=c[j];
		sum-=w[j];
	}
	if(j < n) {
		profit_b +=(sum * c[j])/w[j] + 1;
	}
	return profit_b;
}
int calc_constraint2(int m, int *mW, int n, int *c, int *w) {
	int front = -1;
	int rear = -1;
	bub_sort(n, c, w);
	struct node2 qu[4000];
	struct node2 u, v;
	u.level = -1;
	u.profit = 0;
	int i;
	for(i = 0; i < m; i++) {
		u.wt[i] = 0;
	}
	int mxP = 0;
	push2(qu, &front, &rear, u);
	while(!empty(front, rear)) {
		u = pop2(qu, &front, &rear);
		v.level = u.level + 1;
		int id = v.level;
		v.profit = u.profit + c[id];
		for(i = 0; i < m; i++) {
			v.wt[i] = u.wt[i];
		}
		for(i = 0; i < m; i++) {
			if(v.wt[i] + w[id] <= mW[i] && v.profit > mxP) {
				mxP = v.profit;
				v.wt[i]+=w[id];
				v.bound = calc_bound2(m, mW, n, c, w, v, i);
				if(v.bound > mxP) {
					push2(qu, &front, &rear, v);
				}
				v.wt[i]-=w[id];
			}
		}
		v.profit = u.profit;
		v.bound = calc_bound2(m, mW, n, c, w, v, 0);
		if(v.bound > mxP) {
			push2(qu, &front, &rear, v);
		}
	}
	return mxP;
}
int calc_constraint(int W, int n, int *c, int *w, int k) {
	int front = -1, rear = -1;
	bub_sort(n, c, w);
	struct node qu[40000];
	struct node u, v;
	u.level = -1;
	u.wt = 0;
	u.profit = 0;
	u.cnt = 0;
	push(qu, &front, &rear, u);
	int mxP = 0;
	while(!empty(front, rear)) {
		u = pop(qu, &front, &rear);
		v.level = u.level + 1;
		int id = v.level;
		v.wt = u.wt + w[id];
		v.profit =  u.profit + c[id];
		v.cnt = u.cnt + 1;
		if(v.wt <= W && v.profit > mxP && v.cnt <= k) {
			mxP = v.profit;
		}
		v.bound = calc_bound(n, c, w, v, W, k);
		if(v.bound > mxP) {
			push(qu, &front, &rear, v);
		}
		v.wt = u.wt;
		v.profit = u.profit;
		v.cnt = u.cnt;
		v.bound = calc_bound(n, c, w, v, W, k);
		if(v.bound > mxP) {
			push(qu, &front, &rear, v);
		}
	}
	return mxP;	
}
int knapsack_basic(int W,int n,int *c,int *w)
{
	int ans = calc_constraint(W, n, c, w, n);
	return ans;
  /* Implement basic 0/1 knapsack problem */
}

int knapsack_constrained(int W,int n,int *c,int *w,int p)
{
	int ans = calc_constraint(W, n, c, w, p);
	return ans;
  /* implement the constrained knapsack with the maximum number of elements*/
}

int knapsack_multiple(int m,int *mW,int n,int *c,int *w)
{
	int ans = calc_constraint2(m, mW, n, c, w);
	return ans;
  /* implement the multiple knapsack problem */ 
}