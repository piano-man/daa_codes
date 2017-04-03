#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void find_all(int n, int node, int pa, int d, int path[][100], int par[], int *cnt, int **adj, int vis[]) {
	//printf("%d ", node);
	vis[node] = 1;
	par[node] = pa;
	if(node == d) {
		int temp = d;
		int c = 1;
		while(1) {
			path[*cnt][c] = temp;
			temp = par[temp];
			c++;
			if(temp == -1) {
				break;
			}
		}
		path[*cnt][0] = c - 1;
		*cnt = *cnt + 1;
	}
	else {
		int i;
		for(i = 0; i < n; i++) {
			if(adj[node][i] && !vis[i]) {
				find_all(n, i, node, d, path, par, cnt, adj, vis);
			} 
		}
	}
	vis[node] = 0;
	par[node] = -1;
}
int main() {
	///freopen("input_graph.txt", "r+", stdin);
	int n;
	scanf("%d", &n);
	int **adj;
	adj = (int **)(calloc(n, sizeof(int *)));
	int i, j;
	for(i = 0; i < n; i++) {
		adj[i] = (int *)(calloc(n, sizeof(int)));
	}
	int *parent1, *parent2;
	int a, b, c;
	parent1 = (int *)(calloc(n, sizeof(int)));
	parent2 = (int *)(calloc(n, sizeof(int)));
	while(1) {
		scanf("%d %d %d", &a, &b, &c);
		if(a == -1) {
			break;
		}
		adj[a][b] = c;
		//adj[b][a] = c;
	}
	int src, des;
	scanf("%d %d", &src, &des);
	int path[100][100];
	int par[n];
	int vis[n];
	for(i = 0; i < n; i++) {
		par[i] = -1;
		vis[i] = 0;
	}
	for(i = 0; i < 100; i++) {
		path[i][0] = 0;
	}
	int cnt = 0;
	find_all(n, src, -1, des, path, par, &cnt, adj, vis);
	for(i = 0; i < cnt; i++) {
		for(j = 0; j < path[i][0]; j++) {
			printf("%d ", path[i][j + 1]);
		}
		printf("\n");
	}
	return 0;
}