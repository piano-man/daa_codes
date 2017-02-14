# include<stdio.h>
# include<stdlib.h>
int main()
{
    FILE *fp;
    fp = fopen("f1.txt","r");
    int n1,n2,n3;
    fscanf(fp,"%d %d %d",&n1,&n2,&n3);
    printf("%d %d %d",n1,n2,n3);
     fscanf(fp,"%d %d %d",&n1,&n2,&n3);
    printf("%d %d %d",n1,n2,n3);
    return 0;
}
