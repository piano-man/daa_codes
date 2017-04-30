#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    struct node *parent;
    int **board;
    int x,y;    //blank tile coordinates
    int cost;
    int level;
};

void solve(int **);
int isSolvable ( int ** );
struct node *create_node ( int **, int, int, int, int, int, struct node * );
void push ( struct node* [], int *, struct node* );
struct node * pop_min ( struct node* [], int * );
int calcCost ( int ** );
void print_board ( int ** );
int isSafe(int , int );
void printPath( struct node * );

int main()
{
    int i,**board;

    board = (int **)malloc(3*sizeof(int *));
    board[0] = (int *)malloc(3*sizeof(int));
    board[1] = (int *)malloc(3*sizeof(int));
    board[2] = (int *)malloc(3*sizeof(int));

    for ( i = 0;i < 3;i = i + 1 ) {
        scanf( "%d%d%d", &board[i][0], &board[i][1], &board[i][2]);
    }
    solve ( board );

    return 0;
}

void solve(int **board)
{
    /* Print the steps required to solve the puzzle or print unsolvable */
    int sol = 0;

    sol = isSolvable ( board );

    if ( sol == 0 ) {
        printf ( "Unsolvable\n" );
        return;
    }

    struct node* queue[100000];
    int size = 0;
    int x, y;
    int i, j;

    for ( i = 0;i < 3;i++ ) {
        for( j = 0;j < 3;j++ ) {
            if ( board[i][j] == 0 ) {
                x = i;
                y = j;
            }
        }
    }

    // printf ( "x = %d y = %d\n", x, y );

    int row[] = { 1, 0, -1, 0 };
    int col[] = { 0, -1, 0, 1 };

    // for ( i = 0;i < 4;i++ ) {
    //     printf ( "%d %d\n", row[i], col[i]);
    // }

    struct node *root = (struct node *)malloc(sizeof(struct node));
    root = create_node ( board, x, y, x, y, 0, NULL );
    root->cost = calcCost ( board );

    // printf ( "Cost of root = %d\n", root->cost );

    push ( queue, &size, root );

    struct node *min_node = (struct node *)malloc(sizeof(struct node));

    while ( size != 0 ) {
       // printf ( "size=%d\n", size );
        min_node = pop_min ( queue, &size );

        // printf ( "min_node x %d, y %d\n",min_node->x,min_node->y);

        if ( min_node->cost == 0)
        {
            printPath( min_node );
            return;
        }

        for ( i = 0;i < 4;i++ ) {
            if ( isSafe ( min_node->x + row[i], min_node->y + col[i] ) ) {
                struct node *child = create_node ( min_node->board, min_node->x, min_node->y, min_node->x + row[i],min_node->y + col[i], min_node->level + 1, min_node );                
                child->cost = calcCost( child->board );
                //print_board ( child->board );

                push ( queue, &size, child );
            }
        }
    }
}

int isSolvable ( int **board ) 
{   
    int inv = 0;
    int i, j, k = 0;
    int arr[9];

    for ( i = 0;i < 3;i++ ) {
        for ( j = 0;j < 3;j++ ) {
            arr[k] = board[i][j];
            k++;
        }
    }

    for ( i = 0;i < 8;i++ ) {
        for ( j = i + 1;j < 9;j++ ) {
            if ( arr[i] && arr[j] && arr[i] > arr[j] ) {
                inv++;
            }
        }
    }

    // printf ( "%d\n", inv );

    if ( inv % 2 == 0 ) {
        return 1;
    } else {
        return 0;
    }
}

struct node *create_node ( int **board, int x, int y, int newx, int newy, int level, struct node *parent )
{
    struct node *newnode = ( struct node * ) malloc ( sizeof ( struct node ) );

    int temp;
    int i, j;

    newnode->level = level;
    newnode->parent = parent;

    newnode->board = (int **)malloc(3*sizeof(int *));
    newnode->board[0] = (int *)malloc(3*sizeof(int));
    newnode->board[1] = (int *)malloc(3*sizeof(int));
    newnode->board[2] = (int *)malloc(3*sizeof(int));

    for ( i = 0;i < 3;i++ ) {
        for ( j = 0;j < 3;j++ ) {
            newnode->board[i][j] = board[i][j];
        }
    }

    temp = newnode->board[x][y];
    newnode->board[x][y] = newnode->board[newx][newy];
    newnode->board[newx][newy] = temp;

    newnode->x = newx;
    newnode->y = newy;

    return newnode;
}

void push ( struct node* queue[], int *size, struct node *new )
{
    queue[*size] = new;
    *size = *size + 1;
}

struct node *pop_min ( struct node* queue[], int *size )
{
    struct node* min_node = (struct node *)malloc(sizeof(struct node));
    struct node* temp = (struct node *)malloc(sizeof(struct node));
    int min = INT_MAX;
    int i;
    int min_ind = 0;

  //   printf ( "size = %d\n", *size );

//   for ( i = 0;i < *size;i++ ) {
//       printf ( "%d\n", queue[i]->level ); 
//   }


    for ( i = 0;i < *size;i++ ) {
        if ( queue[i]->cost + queue[i]->level < min ) {
            min = queue[i]->cost + queue[i]->level;
            min_node = queue[i];
            min_ind = i;
            // printf ( "min = %dx\n", min );
        }
    }

    temp = queue[*size - 1];
    queue[*size - 1] = queue[min_ind];
    queue[min_ind] = temp;

    *size = *size - 1;

   // printf ( "level = %d, min_ind =%d size = %d\n",min_node->level, min_ind, *size );

    return min_node;
}

int calcCost ( int **board ) 
{
    int final[3][3];
    int i, j, k = 0;
    int cost = 0;
    
    for ( i = 0;i < 3;i++ ) {
        for ( j = 0;j < 3;j++ ) {
            final[i][j] = k;
            k++;
            // printf ( "%d %d %d ",i, j, final[i][j]);
        }
    }


    for ( i = 0;i < 3;i++ ) {
        for ( j = 0;j < 3;j++ ) {
            if ( (board[i][j]) && (board[i][j] != final[i][j]) ) {
                cost++;
            }
        }
    }

    return cost;
}

void print_board ( int **board )
{
    int i, j;

    for ( i = 0;i < 3;i++ ) {
        for ( j = 0;j < 3;j++ ) {
            printf ( "%d ", board[i][j] );
        }
        printf ( "\n" );
    }

    printf ( "\n" );
}

int isSafe(int x, int y)
{
    return (x >= 0 && x < 3 && y >= 0 && y < 3);
}

void printPath( struct node* root )
{
    if (root == NULL)
        return;
    printPath( root->parent );
    print_board ( root->board );
 
    printf("\n");
}