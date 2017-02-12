# include <stdio.h>
# include <stdlib.h>

int check_MAX_heap(int *,int,int);
void build_MAX_heap(int *,int, int);
int extract_MAX(int *,int, int);
void insert(int *,int,int,int);
void change(int *,int,int,int,int);
int n;
void heapify(int*,int,int,int);

int main()
{
	char ch=' ';
	int *arr,n,k,i,new;
	scanf("%d",&k);
	scanf("%d",&n); /* To have anything non-trivial, n should be >2*n*k*/
	arr = (int *)malloc(2*n*sizeof(int));
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	//	if(!check_MAX_heap(arr,n,k))
	build_MAX_heap(arr,n,k);
	do
	{
		//while(getchar()!='\n'); // To clear the buffer of any leftover characters
		ch=getchar();
		switch(ch)
		{
			case 'i':
				scanf("%d",&new);
				insert(arr,n,k,new);
				n++;
				for(i=0;i<n;i++)
				{
					printf("%d",arr[i]);
				}

				break;
			case 'd':
				printf("%d",extract_MAX(arr,n,k));
				n--;
				break;
			case 'c':
				scanf("%d",&i);
				scanf("%d",&new);
				change(arr,n,k,i,new);
				break;
	}
	}while(ch!='q');
	for(i=0;i<n;i++)
	{
		printf("%d",arr[i]);
	}

	return 0;
}

//int check_MAX_heap(int arr[],int n,int k)
//{
/* The function returns 0 if arr is NOT a k-ary MAX-heap.*/
//}

void build_MAX_heap(int arr[],int n,int k)
{
	int i;	
	for ( i= (n-1)/k; i>=0; i--)
		heapify(arr, n, i, k);
}
void restoreUp(int arr[], int index, int k)
{
	// parent stores the index of the parent variable
	// of the node
	int parent = (index-1)/k;

	// Loop should only run till root node in case the
	//  element inserted is the maximum restore up will
	// send it to the root node
	while (parent>=0)
	{
		if (arr[index] > arr[parent])
		{
			//swap(arr[index], arr[parent]);
			int temp = arr[index];
			arr[index]=arr[parent];
			arr[parent]=temp;
			index = parent;
			parent = (index -1)/k;
		}

		// node has been restored at the correct position
		else
			break;
	}
}
void heapify(int arr[],int len,int index,int k)
{
	// child array to store indexes of all
	// the children of given node
	int child[k+1];

	while (1)
	{
		// child[i]=-1 if the node is a leaf
		// children (no children)
		int i;		
		for (i=1; i<=k; i++)
			child[i] = ((k*index + i) < len) ?
				(k*index + i) : -1;

		// max_child stores the maximum child and
		// max_child_index holds its index
		int max_child = -1, max_child_index ;

		// loop to find the maximum of all
		// the children of a given node
		for (i=1; i<=k; i++)
		{
			if (child[i] != -1 &&
					arr[child[i]] > max_child)
			{
				max_child_index = child[i];
				max_child = arr[child[i]];
			}
		}

		// leaf node
		if (max_child == -1)
			break;

		// swap only if the key of max_child_index
		// is greater than the key of node
		if (arr[index] < arr[max_child_index])
			//swap(arr[index], arr[max_child_index]);
		{
			int temp = arr[index];
			arr[index]=arr[max_child_index];
			arr[max_child_index]=temp;
		}
		index = max_child_index;
	}
}

void insert(int arr[],int n,int k,int new)
{
	arr[n] = new;

	// Increase heap size by 1
	// *n = *n+1;

	// Call restoreUp on the last index
	restoreUp(arr, n, k);
	heapify(arr,n,n,k);
}

int extract_MAX(int arr[],int n,int k)
{
	int max = arr[0];

	// Copy the last node's key to the root node
	arr[0] = arr[n-1];

	// Decrease heap size by 1
	// n = n-1;

	// Call restoreDown on the root node to restore
	// it to the correct position in the heap
	heapify(arr, n, 0, k);

	return max;
}

void change(int arr[],int n,int k,int i,int new)
{
	arr[i]=new;/* This function changes the value of arr[i]= new and makes arr a k-ary max-heap*/
	restoreUp(arr,i,k);
}




