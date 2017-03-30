procedure FindAllPaths(u, dest)
{
   push u to stack;
   if(u == dest)
   {
      print stack;
   }
   else
   {
      foreach v that is adjacent with u and not in stack now
      {
         FindAllPaths(v, dest);
      }
   }
   pop from stack;
}
 

 #include<string.h>
 
#define N 5
#define true 1
#define false 0
 
int graph[N][N] = {
  {0, 1, 1, 0, 1},
  {0, 0, 0, 0, 0},
  {0, 1, 0, 1, 0},
  {0, 0, 0, 0, 0},
  {0, 0, 1, 1, 0},
};
 
int path[N];
int visited[N];
int indx = 0;
 
void printPath (int src, int dest);
void print_stack_elements ();
 
int main ()
{
// set all nodes unvisited
  memset (visited, 0, sizeof (visited));
  printPath (0, 3);
  return 0;
}
 
void printPath (int src, int dest)
{
  visited[src] = true;
  path[indx] = src;
  indx++;
 
  if (src == dest)
    {
      print_stack_elements ();
    }
  else
    {
      int i;
      for (i = 0; i < N; i++)
    {
      if (visited[i] == false && graph[src][i])
        printPath (i, dest);
    }
    }
 
  visited[src] = false;
  indx--;
}
 
void print_stack_elements ()
{
  int i;
  for (i = 0; i < indx; i++)
    printf ("%d ", path[i]);
 
  printf ("\n");
}

