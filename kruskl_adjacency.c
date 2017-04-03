#include <stdio.h>
#include <stdlib.h>

struct node {
	int wt;
	int r;
	int c;
};
void sort_array(int n, struct node arr[]) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n - 1; j++) {
			if(arr[j].wt > arr[j + 1].wt) {
				struct node temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
void dfs(int n, int node, int pa, int *par, int **tree) {
	par[node] = pa;
	int i;
	for(i = 0; i < n; i++) {
		if(i != pa && tree[node][i]) {
			dfs(n, i, node, par, tree);
		}
	}
}
int findp(int a, int p[]) {
	if(p[a] == a) {
		return a;
	}
	return (p[a] = findp(p[a], p));
}
void union1(int a, int b, int p[]) {
	int pa = findp(a, p);
	int pb = findp(b, p);
	if(pa != pb) {
		p[pa] = pb;
	}
}
void mst(int n, int **adj, int *par) {
	int **tree;
	tree = (int **)(calloc(n, sizeof(int *)));
	int i, j;
	for(i = 0; i < n; i++) {
		tree[i] = (int *)(calloc(n, sizeof(int)));
	}
	
	int cnt = 0;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			if(adj[i][j]) {
				cnt++;
			}
		}
	}
	cnt/=2;
	struct node arr[cnt];
	cnt = 0;
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			if(adj[i][j]) {
				arr[cnt].wt = adj[i][j];
				arr[cnt].r = i;
				arr[cnt].c = j;
				cnt++;
			}
		}
	}
	sort_array(cnt, arr);
	int p[n];
	for(i = 0; i < n; i++) {
		p[i] = i;
	}
	for(i = 0; i < cnt; i++) {
		int pa = findp(arr[i].r, p);
		int pb = findp(arr[i].c, p);
		if(pa != pb) {
			tree[arr[i].r][arr[i].c] = arr[i].wt;
			tree[arr[i].c][arr[i].r] = arr[i].wt;
			union1(arr[i].r, arr[i].c, p);
		}
	}
	/*for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			printf("%d ",tree[i][j]);
		}
		printf("\n");
	}*/
	dfs(n, 0, -1, par, tree);
	for(i = 1; i < n; i++) {
		printf("%d %d\n", i, par[i]);
	}
}
int main() {
	int n;
	scanf("%d", &n);
	int **adj;
	adj = (int **)(calloc(n, sizeof(int *)));
	int i, j;
	for(i = 0; i < n; i++) {
		adj[i] = (int *)(calloc(n, sizeof(int)));
	}
	int *par;
	par = (int *)(calloc(n, sizeof(int)));
	int a, b, c;
	while(1) {
		scanf("%d %d %d", &a, &b, &c);
		if(a == -1) {
			break;
		}
		adj[a][b] = c;
		adj[b][a] = c;
	}
	mst(n, adj, par);
	return 0;
}