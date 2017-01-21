# include <stdio.h>
# include <stdlib.h>
struct node 
{
	int data;
	struct node *left, *right,*parent;
};
//struct node * currentnode;
struct queue
{
	int front,rear,size;
	struct node* *array;
};
struct node * newnode(int data)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = data;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=NULL;
	return temp;

};
struct queue* CreateQueue()
{
	struct queue *q=(struct queue *)malloc(sizeof(struct queue));
	q->front=-1;
	q->rear=-1;
	q->size=100;
	q->array=(struct node **)malloc(q->size*sizeof(struct node *));
	int i;
	for(i=0;i<q->size;i++)
	{
		q->array[i]=NULL;
	}
	return q;
};
//standard queue functions
int isEmpty(struct queue *q)
{
	return q->front == -1;
}
int oneitem(struct queue *q)
{
	return q->front == q->rear;
}
int isFull(struct queue *q)
{
	return q->rear==q->size-1;

}
void enqueue(struct queue *q,struct node *root)
{
	if(isFull(q))
		return;
	q->array[++q->rear]=root;
	if(isEmpty(q))
		++q->front;

}
struct node * dequeue(struct queue *q)
{
	if(isEmpty(q))
		return NULL;
	struct node *temp=q->array[q->front];
	if(oneitem(q))
		q->front=q->rear=-1;
	else
		++q->front;
	return temp;
}
struct node *getfront(struct queue *q)
{
	return q->array[q->front];
}
int hasbothchild(struct node * temp)
{
	return temp&&temp->left&&temp->right;
}
void insert(struct node **root,int data,struct queue *q)
{
	struct node *temp=newnode(data);
	if(!*root)
	{
		*root=temp;
		//currentnode = temp;
	}
	else
	{
	struct node *front=getfront(q);

	if(!front->left){
		front->left=temp;
		temp->parent=front;
	}

	if(!front->right){
		front->right=temp;
		temp->parent=front; 
	}
	if(hasbothchild(front))
		{
			dequeue(front); 
		}
	enqueue(q,temp);
	//currentnode = temp;
	}
}
generate(struct queue *q)
{
	struct node * currentnode;
	struct node * finalroot;
	while(!isEmpty(q))
	{
		int temp;
		currentnode = dequeue(q);
		while(currentnode->parent!=NULL)
		{
			if(currentnode->data>currentnode->parent->data)
			{
				temp=currentnode->data;
				currentnode->data=currentnode->parent->data;
				currentnode->parent->data=temp;

			}
			finalroot=currentnode;
		}


	}

}
void main()
{
	struct node *root=NULL;
	struct queue *q = CreateQueue();
	
	int i;
	for(i=0;i<10;i++)
	{
		insert(&root,i,q);
	}
	printf("root data is %d",root->data);
	generate(q);

}

