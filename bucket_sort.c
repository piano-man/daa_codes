/*Bucket sort */

#include<stdio.h>
#include<stdlib.h>

/*Defining the strcuture for each node in the list*/
typedef struct node
{
float value;
struct node *link;
} node;

void main()
{

/*An array of structures,pointers to the structure*/

node counter[10], *n2,*n1;
float ar[10] = {0.79,0.13,0.16,0.64,0.39,0.20,0.89,0.53,0.71,0.42};
float fa[10],temp;
int i,j,k=0;
float n,a;


/*Initializing the elements of the counter arrray to zero*/

for(i=0;i<10;i++)
{
counter[i].value = 0;
counter[i].link  = 0;
}

/*Redcuing the value equal to index of an array*/

for(i=0;i<10;i++)
{
n = ar[i];
j = n * 100;
j = j/10;

/*Moving the values in to the appropriate bucket*/

/*If there are no elements in the bucket*/

if(counter[j] . value ==0 && counter[j] . link == 0)
counter[j] . value = ar[i];

else
{
/*If there is only one element at that index*/
if(counter[j].link==0 && counter[j] .value != 0)
{
counter[j].link=(node *) malloc(sizeof(node));
n2 = counter[j].link;
n2 -> link = 0;
n2 -> value =ar[i];
continue;
}
/*If there is already an node in the list at this index*/
n2 = counter[j].link ;
while(n2 -> link !=0 )
{
n2 = n2 -> link;
}
n2 -> link =(node *) malloc(sizeof(node));
n2 = n2 -> link;
n2 -> link=0;
n2 -> value = ar[i];
}
}

/*Sorting of all the buckets in order*/

printf("The sorted values after merging all buckets in order are: ");

for(i=0;i<10;i++)
{
/*No nodes at that index*/
if(counter[i] . link ==0 && counter[i] . value == 0)
continue;
else
{
n1 = &counter[i];
n2 = &counter[i] ;

/*If there is more than one node at this Index*/

if(n2 -> link != 0)
{
while(n1!=0)
{
while(n2!= 0)
{
if(n1 -> value   >  n2 -> value)
{
temp =n1 -> value;
n1 -> value =n2 -> value;
n2 -> value =temp;
}
n2 = n2 -> link;
}
n2 = n1 -> link;
n1 = n1 -> link;
}
n1 = &counter[i];
for(; n1!=0; k++)
{
fa[k] = n1 -> value;
n1 = n1 -> link;
}

}

/*If there is only one node at this Index*/

else
{
fa[k] = counter[i].value;
k=k+1;
}
}
}
for(i=0;i<10;i++)
printf("%f",fa[i]);

}