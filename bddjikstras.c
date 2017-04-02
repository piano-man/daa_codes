#include <stdio.h>
#include <stdlib.h>

int mindis( int visited[], int dist[], int n)

{
	int i = 0;
	int minn = 99999999,mini = -1;
	for( i = 0; i < n; i++ ) {
		if ( !visited[i] && dist[i] < minn ) {
			minn = dist[i];
			mini = i;
		}
	}
	return mini;
}

void print(int dis[],int n)
{
	int i;
	for( i = 0; i < n; i++) {
		printf("%d %d\n",i,dis[i] );
	}
}

int shortest_path(int n, int **adj, int *parent1, int src,int des)
{
	int dist[n], visited[n];
	int i;
	for( i = 0; i < n; i++ ) {
		dist[i] = 999999999;
		visited[i] = 0;	
	}
	dist[src] = 0;
	//parent1[src] = src;
	//printf("Source :%d\n",src);
	for( i = 0; i < n-1; i++ ) {
		int u = mindis(visited,dist,n);
		int v;
		if ( u == des ) {
			break;
		}
		visited[u] = 1;
		for( v = 0; v < n; v++) {
			if ( visited[v] == 0 && adj[u][v] && dist[v] != 9999999 && dist[u] + adj[u][v] < dist[v] ) {
				dist[v] = dist[u] + adj[u][v];
				parent1[v] = u;
			}
		}
	}
	//print(dist,n);
	return dist[des];
}

void print_path( int *parent1, int sc, int ds)
{
	if ( sc == ds ) {
		printf("%d", sc);
	} else {
		print_path(parent1,sc,parent1[ds]);
		printf("->%d", ds);
	}
}

int count(int *parent1, int src, int des)
{
	if ( src == des ) {
		return 1;
	} else {
		return count(parent1,src,parent1[des]) + 1;
	}
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
		adj[b][a] = c;
		//printf("%d %d %d\n", a,b,c);
	}
	int src, des;
	scanf("%d %d", &src, &des);
	src = 0;
	int sol1 = shortest_path(n, adj, parent1, src,des);
	printf("Shortest Path Length - %d\n", sol1);
	print_path(parent1, src,des);
	printf("\n");
	// for( i = 0; i < n; i++) {
	// 	printf("%d ", parent1[i]);
	// }
	// printf("\n");
	int num_nodes = count(parent1,src,des);
	//printf("%d\n", num_nodes);
	int path[num_nodes];
	int ctr = 0;
	int cnt = 0;
	int s = src;
	int d = des;
	while(1) {
		if ( s == d ) {
			path[num_nodes - 1 - ctr] = s;
			break;
		} else {
			path[num_nodes - 1 - ctr] = d;
			d = parent1[d];
			ctr++;
		}
	}
	// for( i = 0; i < n; i++) {
	// 	printf("%d ", path[i]);
	// }
	//printf("source and destination : %d %d\n",s,d );
	int minid, minval = 9999999;
	for( i = 0; i < num_nodes - 1; i++) {
		//printf("%d %d\n",path[i],path[i+1]);
		int pre = adj[path[i]][path[i+1]];
		//printf("%d\n", pre);
		adj[path[i]][path[i+1]] = 99999999;
		int val = shortest_path(n,adj,parent2,src,des);
		//printf("%d\n",val);
		if ( val < minval ) {
			minid = i;
			minval = val;
		}
		//printf("%d\n",minid );
		adj[path[i]][path[i+1]] = pre;
		//printf("%d loop finish\n",i );
	}
	adj[path[minid]][path[minid+1]] = 9999999;
	int sol2 = shortest_path(n,adj,parent2,src,des);
	printf("Shortest Path Length - %d\n", sol2);
	print_path(parent2, src,des);
	printf("\n");
	return 0;
}