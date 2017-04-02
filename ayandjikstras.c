#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_path(int *parent, int s, int d) {
	if(s == d) {
		printf("%d ", s);
	}
	else {
		print_path(parent, s, parent[d]);
		printf("%d ", d);
	}
}
int cnt_nodes(int *parent, int s, int d) {
	int c = 1;
	while(s != d) {
		c++;
		d = parent[d];
	}
	return c;
}
void restore_up(int heap[], int id, int dist[]) {
	if(!id) {
		return;
	}
	int par = (id - 1)/2;
	if(dist[heap[id]] < dist[heap[par]]) {
		int temp = heap[id];
		heap[id] = heap[par];
		heap[par] = temp;
		restore_up(heap, par, dist);
	}
}
void insert(int heap[], int val, int *sz, int dist[]) {
	heap[*sz] = val;
	restore_up(heap, *sz, dist);
	*sz = *sz + 1;
}
void heapify(int heap[], int sz, int id, int dist[]) {
	int sm = id;
	int l = 2 * id + 1;
	int r = l + 1;
	if(l < sz && dist[heap[l]] < dist[heap[sm]]) {
		sm = l;
	}
	if(r < sz && dist[heap[r]] < dist[heap[sm]]) {
		sm = r;
	}
	if(sm != id) {
		int temp = heap[id];
		heap[id] = heap[sm];
		heap[sm] = temp;
		heapify(heap,sz, sm, dist);
	}
}
int extract_min(int heap[], int *sz, int dist[]) {
	int mn = heap[0];
	*sz = *sz - 1;
	heap[0] = heap[*sz];
	heapify(heap, *sz, 0, dist);
	return mn;
}
int shortest_path(int n, int **adj, int *parent, int src, int des) {
	int inf = 100000000;
	int dist[n];
	int i;
	for(i = 0; i < n; i++) {
		dist[i] = inf;
	}
	dist[src] = 0;
	int heap[n];
	int sz = 0;
	insert(heap, src, &sz, dist);
	while(sz) {
		int node = extract_min(heap, &sz, dist);
		if(node == des) {
			break;
		}
		for(i = 0; i < n; i++) {
			int k = adj[node][i];
			if(k) {
				if(dist[node] + k < dist[i]) {
					//printf("%d %d\n", node, i);
					dist[i] = dist[node] + k;
					insert(heap, i, &sz, dist);
					parent[i] = node;
				}
			}
		}
	}
	/*for(i = 0; i < n; i++) {
		printf("%d ", dist[i]);
	}
	printf("\n");*/
	return dist[des];
}
int main() {
	freopen("input_graph.txt", "r+", stdin);
	int n;
	scanf("%d", &n);
	int **adj;
	adj = (int **)(calloc(n, sizeof(int *)));
	int i, j;
	for(i = 0; i < n; i++) {
		adj[i] = (int *)(calloc(n, sizeof(int)));


	printf("Shortest Path Length - %d\n", sol1);
	print_path(parent1, src, des);
	printf("\n");
	int cnt = cnt_nodes(parent1, src, des);
	int path[cnt];
	c = 0;
	int s = src;
	int d = des;
	while(1) {
		if(s == d) {
			path[cnt - 1 - c] = s;
			break;
		}
		else {
			path[cnt - 1 - c] = d;
			d = parent1[d];
			c++;
		}
	}
	int mnid = 0;
	int inf = 100000000;
	int mnval = inf;
	for(i = 0; i < cnt - 1; i++) {
		int pre = adj[path[i]][path[i + 1]];
		adj[path[i]][path[i + 1]] = inf;
		int val = shortest_path(n, adj, parent2, src, des);
		if(val < mnval) {
			mnval = val;
			mnid = i;
		}
		adj[path[i]][path[i + 1]] = pre;
	}
	adj[path[mnid]][path[mnid + 1]] = inf;
	int ans = shortest_path(n, adj, parent2, src, des);
	printf("Shortest 2nd Path Length - %d\n", ans);
	print_path(parent2, src, des);
	return 0;
}