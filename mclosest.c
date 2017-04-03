#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<math.h>

struct point2d {
	int x,y;
};

struct point3d {
	int x,y,z;
};

void closestpair2d(struct point2d *,struct point2d *, int);
void closestpair3d(struct point3d *,struct point3d *,int);
void euclideanMST(struct point2d **,struct point2d *,int);

int main()
{
	struct point2d *points,close2d[2],**mst;
	struct point3d *plane,close3d[2];
	int i,n,m;
	scanf("%d",&n);
	points = (struct point2d *)malloc(n*sizeof(struct point2d));
	for(i=0;i<n;i++)
		scanf("%d%d",&(points[i].x),&(points[i].y));
	scanf("%d",&m);
	plane = (struct point3d *)malloc(m*sizeof(struct point3d));
	for(i=0;i<m;i++)
		scanf("%d%d%d",&(plane[i].x),&(plane[i].y),&(plane[i].z));
	closestpair2d(close2d,points,n);
	closestpair3d(close3d,plane,m);
	mst = (struct point2d **)malloc((n-1)*sizeof(struct point2d *));
	for(i=0;i<n;i++)
		mst[i]=(struct point2d *)malloc(2*sizeof(struct point2d));
	euclideanMST(mst,points,n);
	return 0;
}
/////////////////////////////////////////First Question//////////////////////////////////////
float dist(struct point2d p1,struct point2d p2)
{
    return sqrt( (float)(p1.x - p2.x)*(float)(p1.x - p2.x) +
                 (float)(p1.y - p2.y)*(float)(p1.y - p2.y)
               );
}

struct point2d * bruteForce(struct point2d points[], int start, int end,struct point2d * left)
{
    float min = FLT_MAX;
    int i,j;
    
    for (i = start; i <= end; ++i)
        for (j = i+1; j <= end; ++j)
            if (dist(points[i], points[j]) < min) {
                min = dist(points[i], points[j]);
                left[0] = points[i];
                left[1] = points[j];
            }
    return left;
}

void sort(struct point2d *points, int n) 
{
	int i,j,swapx,swapy;
	for(i=0;i<n-1;i++) {
		for(j=0;j<n-i-1;j++) {
			if(points[j].x>points[j+1].x) {
				swapx = points[j].x;
				swapy = points[j].y;
				points[j].x = points[j+1].x;
				points[j+1].x = swapx;
				points[j].y = points[j+1].y;
				points[j+1].y = swapy;
			}
		}
	}	
}


float findsmall(struct point2d * left,struct point2d * right, struct point2d * small) 
{
	float d1,d2;
	d1 = dist(left[0],left[1]);
	d2 = dist(right[0],right[1]);
	if(d1 < d2) {
		small = left;
		return d1;
	}
	else {
		small = right;
		return d2;
	}	
}
	
	
float stripClosest(struct point2d strip[], int size, float d,struct point2d *left)
{
	float min = d;  
	sort(strip,size);
	int i,j;
	for (i = 0; i < size; ++i)
	        for (j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
			if (dist(strip[i],strip[j]) < min) {
		            	min = dist(strip[i], strip[j]);
		            	left[0] = strip[i];
		            	left[1] = strip[j];
		        }
		 }
 
	return min;
}
	
struct point2d * divandcon(struct point2d *points,int start,int end,int n)
{
	struct point2d *left, *right, *small;
	float small_dist;
	int i,j;
	left = (struct point2d *)malloc(2*sizeof(struct point2d));
	right = (struct point2d *)malloc(2*sizeof(struct point2d));
	small = (struct point2d *)malloc(2*sizeof(struct point2d));
	
	if ((end-start) <= 3)
        	return bruteForce(points,start,end,left);
/////bruteforce
	
	        
        int mid = (start+end)/2;
    	struct point2d midPoint = points[mid];
    	
    	left = divandcon(points,start,mid,n);
    	right = divandcon(points,mid+1,end,n);
    	
    	small_dist = findsmall(left,right,small);
    	
    	struct point2d *strip;
    	strip = (struct point2d *)malloc(n*sizeof(struct point2d));
    	j = 0;
    	for (i = 0; i <= (end-start); i++) {
        	if (abs(points[i].x - midPoint.x) < small_dist) {
        		strip[j] = points[i];
        		j++;
    		}
    	}
    	float dist = stripClosest(strip, j, small_dist,left);
    	if(small_dist<dist) {
    		return small;
    	}
    	else
    		return left;
}


void closestpair2d(struct point2d *close2d, struct point2d *points, int n)
{
	int i;
	
	sort(points,n);
	close2d = divandcon(points,0,n-1,n);
	
	printf("\nx1: %d  y1: %d\nx2: %d  y2:%d\n",close2d[0].x,close2d[0].y,close2d[1].x,close2d[1].y);
	
}


///////////////////////////////Second question/////////////////////////////////////////////////////////////////////

float dist3(struct point3d p1,struct point3d p2)
{
    return sqrt( (float)(p1.x - p2.x)*(float)(p1.x - p2.x) +
                 (float)(p1.y - p2.y)*(float)(p1.y - p2.y) +
		 (float)(p1.z - p2.z)*(float)(p1.z - p2.z)
               );
}

struct point3d * bruteForce3(struct point3d plane[], int start, int end,struct point3d * left)
{
    float min = FLT_MAX;
    int i,j;
    
    for (i = start; i <= end; ++i)
        for (j = i+1; j <= end; ++j)
            if (dist3(plane[i], plane[j]) < min) {
                min = dist3(plane[i], plane[j]);
                left[0] = plane[i];
                left[1] = plane[j];
            }
    return left;
}

void sort3(struct point3d *plane, int n) 
{
	int i,j,swapx,swapy,swapz;
	for(i=0;i<n-1;i++) {
		for(j=0;j<n-i-1;j++) {
			if(plane[j].x>plane[j+1].x) {
				swapx = plane[j].x;
				swapy = plane[j].y;
				swapz = plane[j].z;
				plane[j].x = plane[j+1].x;
				plane[j+1].x = swapx;
				plane[j].y = plane[j+1].y;
				plane[j+1].y = swapy;
				plane[j].z = plane[j+1].z;
				plane[j+1].z = swapz;
			}
		}
	}	
}

float findsmall3(struct point3d * left,struct point3d * right, struct point3d * small) 
{
	float d1,d2;
	d1 = dist3(left[0],left[1]);
	d2 = dist3(right[0],right[1]);
	if(d1 < d2) {
		small = left;
		return d1;
	}
	else {
		small = right;
		return d2;
	}	
}

float stripClosest3(struct point3d strip[], int size, float d,struct point3d *left)
{
	float min = d;  
	sort3(strip,size);
	int i,j;
	for (i = 0; i < size; ++i)
	        for (j = i+1; j < size; ++j) {
			if (dist3(strip[i],strip[j]) < min) {
		            	min = dist3(strip[i], strip[j]);
		            	left[0] = strip[i];
		            	left[1] = strip[j];
		        }
		 }
 
	return min;
}

struct point3d * divandcon3(struct point3d *plane,int start,int end,int n)
{
	struct point3d *left, *right, *small;
	float small_dist;
	int i,j;
	left = (struct point3d *)malloc(2*sizeof(struct point3d));
	right = (struct point3d *)malloc(2*sizeof(struct point3d));
	small = (struct point3d *)malloc(2*sizeof(struct point3d));
	
	if ((end-start) <= 3)
        	return bruteForce3(plane,start,end,left);
	
	        
        int mid = (start+end)/2;
    	struct point3d midPoint = plane[mid];
    	
    	left = divandcon3(plane,start,mid,n);
    	right = divandcon3(plane,mid+1,end,n);
    	
    	small_dist = findsmall3(left,right,small);
    	
    	struct point3d *strip;
    	strip = (struct point3d *)malloc(n*sizeof(struct point3d));
    	j = 0;
    	for (i = 0; i <= (end-start); i++) {
        	if (abs(plane[i].x - midPoint.x) < small_dist) {
        		strip[j] = plane[i];
        		j++;
    		}
    	}
    	float dist = stripClosest3(strip, j, small_dist,left);
    	if(small_dist<dist) {
    		return small;
    	}
    	else
    		return left;
}

void closestpair3d(struct point3d *close3d, struct point3d *plane,int m)
{
	int i;
	sort3(plane,m);
	close3d = divandcon3(plane,0,m-1,m);
	printf("\nx1: %d  y1: %d z1: %d\nx2: %d  y2:%d z2: %d\n",close3d[0].x,close3d[0].y,close3d[0].z,close3d[1].x,close3d[1].y,close3d[1].z);
}

//////////////////////////////////////////////////////////////////
int compareX (const void *a, const void *b) {
	struct point2d *p = (struct point2d *)a;
	struct point2d *q = (struct point2d *)b;
	return ((p->x)-(q->x));
}


int belongsto(struct point2d a, struct point2d b, struct point2d ** list, int size) 
{
	int i;
	for(i=0;i<size;i++){
		if(list[i][0].x==a.x && list[i][0].y==a.y && list[i][1].x==b.x && list[i][1].y==b.y)
			return 1;
		else if(list[i][0].x==b.x && list[i][0].y==b.y && list[i][1].x==a.x && list[i][1].y==a.y)
			return 1;
	}
	return 0;
}


float stripClosest4(struct point2d strip[], int size, float d,struct point2d *left,float prev,struct point2d **list,int sizel)
{
	float min = d;  
	sort(strip,size);
	int i,j;
	int test = 0;
	for (i = 0; i < size; ++i)
	        for (j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
			if (dist(strip[i],strip[j]) < min && (dist(strip[i], strip[j])>=prev)) {
				if(!(belongsto(strip[i],strip[j],list,sizel))) {
					test = 1;
		            		min = dist(strip[i], strip[j]);
		            		left[0] = strip[i];
		            		left[1] = strip[j];
				}		        
			}
		 }
 
	return min;
}


struct point2d * bruteForce4(struct point2d points[], int start, int end,struct point2d * left,float prev,struct point2d **list,int sizel)
{
    float min = FLT_MAX;
    int i,j;
    int test=0;
	for (i = start; i <= end; ++i)
	    	for (j = i+1; j <= end; ++j)
	        	if ( (dist(points[i], points[j]) < min) && (dist(points[i], points[j])>=prev) ) {
				if(!(belongsto(points[i],points[j],list,sizel))) {
					test = 1;
	        	        	min = dist(points[i], points[j]);
	        	        	left[0] = points[i];
	        	        	left[1] = points[j];
				}
			}
	if(test ==0) {
		left[0].x = 0;
		left[0].y = 0;
		left[1].x = 99999;
		left[1].y = 99999;
	}
	
    return left;
}

struct point2d * divandcon4(struct point2d *points,int start,int end,int n,float prev,struct point2d** list, int sizel)
{
	struct point2d *left, *right, *small;
	float small_dist;
	int i,j;
	left = (struct point2d *)malloc(2*sizeof(struct point2d));
	right = (struct point2d *)malloc(2*sizeof(struct point2d));
	small = (struct point2d *)malloc(2*sizeof(struct point2d));
	
	if ((end-start) <= 3)
        	return bruteForce4(points,start,end,left,prev,list,sizel);	
	        
        int mid = (start+end)/2;
    	struct point2d midPoint = points[mid];
    	
    	left = divandcon4(points,start,mid,n,prev,list,sizel);
    	right = divandcon4(points,mid+1,end,n,prev,list,sizel);
    	
    	small_dist = findsmall(left,right,small);
    	
    	struct point2d *strip;
    	strip = (struct point2d *)malloc(n*sizeof(struct point2d));
    	j = 0;
    	for (i = 0; i <= (end-start); i++) {
        	if (abs(points[i].x - midPoint.x) < small_dist) {
        		strip[j] = points[i];
        		j++;
    		}
    	}
    	float dist = stripClosest4(strip, j, small_dist,left,prev,list,sizel);
    	if(small_dist<dist) {
    		return small;
    	}
    	else
    		return left;
}

int find_node (struct point2d *p, int x1, int y1, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if (p[i].x == x1 && p[i].y == y1) {
			return i;
		}
	}
}

int find (int parent[100], int x) {
	if (parent[x] != x) {
		parent[x] = find (parent, parent[x]);
	}
	return parent[x];
}

void union_n (int x, int y, int parent[100], int rank[100]) {
	int p = find(parent, x);
	int q = find(parent, y);
	if (p == q) {
		return;
	}
	if (rank[p] < rank[q]) {
		parent[p] = q;
	}
	else if (rank[p] > rank[q]) {
		parent[q] = p;
	}
	else {
		parent[q] = p;
		rank[p]++;
	}
}

void euclideanMST(struct point2d **mst,struct point2d *points,int n)
{
	/* find out the Euclidean MST and store the MST in 2d-array mst.
	   Each of the n-1 edges are store by storing it's two endpoints.
	 */
	int i;
	qsort(points,n,sizeof(struct point2d),compareX);
	struct point2d **list;
	(list) = (struct point2d **)malloc(n*(n-1)*sizeof(struct point2d*));
	for(i=0;i<(n*(n-1));i++)
		list[i] = (struct point2d *)malloc(2*sizeof(struct point2d));
	struct point2d *temp;
	temp = (struct point2d *)malloc(2*sizeof(struct point2d));
	float *dis;
	
	float prev = FLT_MIN;
	dis = (float *)malloc(n*(n-1)*sizeof(float));
	for(i=0;i<n*(n-1);i++) {
		temp[0].x = 0;
		temp[1].x = 99999;
		temp[0].y = 0;
		temp[1].y = 99999;
		
		temp = divandcon4(points,0,n-1,n,prev,list,i);
		dis[i] = dist(temp[0],temp[1]);
		prev = dis[i];
		list[i][0] = temp[0];
		list[i][1] = temp[1];
		
		if (temp[0].x == 0 && temp[1].x == 99999) {
			break;
		}
	}
	int k = i-1;
	for (i = 0; i <= k; i++) {
		printf ("%d %d-%d  %d-%d : %f\n",i, list[i][0].x, list[i][0].y, list[i][1].x, list[i][1].y, dis[i]);
	}
	int nodes[100][3];
	for (i = 0; i <=k; i++) {
		nodes[i][0] = find_node (points, list[i][0].x, list[i][0].y, n);
		nodes[i][1] = find_node (points, list[i][1].x, list[i][1].y, n);
	}
	printf("\nPoints\n");
	for (i = 0; i < n; i++) {
		printf ("%d %d\n", points[i].x, points[i].y);
	}
	printf("\nNodes\n");
	for (i = 0; i <= k; i++) {
		printf ("%d %d\n", nodes[i][0], nodes[i][1]);
	}
	
	int parent[100], rank[100];
	for (i = 0; i < n; i++) {
		parent[i] = i;
		rank[i] = 0;
	}
	int f=0,c=0,r,s;
	int final[100][2];
	while (f < n-1) {
		r = find (parent, nodes[c][0]);
		s = find (parent, nodes[c][1]);
		if (r != s) {
			final[f][0] = nodes[c][0];
			final[f][1] = nodes[c][1];
			f++;
			union_n (r, s, parent, rank);
		}
		c++;	
	}
	for (i = 0; i < f; i++) {
		mst[i][0] = points[final[i][0]];
		mst[i][1] = points[final[i][1]];
	}

	printf("\nMST: \n");
	for (i = 0; i < f; i++) {
		printf("x1:%d y1:%d x2:%d y2:%d\n", mst[i][0].x,mst[i][0].y,mst[i][1].x,mst[i][1].y);
	}	

}