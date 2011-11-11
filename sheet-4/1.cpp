#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<string.h>

using namespace std;

int i, j, k, m, e, c, co, len[20];
long int sp;
int weight[20][20], cost[20][20];
long int path[20][20];
int node[20];
char name[20];

void get_node();
void get_wt();
void display_given();
void display_result();
void shortpath(int, int);

int main() 
{
    int n1, n2;
    char ch = 'Y';
    get_node();
    get_wt();
    display_given();
    while (ch == 'Y' || ch == 'y') {
	printf("\nEnter nodes to calculate shortest path:");
	scanf("%d %d", &n1, &n2);
	shortpath(n1, n2);
//	cout << "\nTo continue, press y: ";
	cin >> ch;
    }
    cout << "\n";
    return 0;
}


/* Get info regarding nodes. */
void get_node() 
{
    printf("\nEnter the no of nodes in the graph:");
    scanf("%d", &m);
    for (i = 1; i <= m; i++)
	 {
	printf("\nEnter the name of the node %d:", i);
	cin >> name[i];
	printf("%c", name[i]);
	node[i] = i;
	}
    for (i = 1; i <= m; i++)
	 {
	for (j = 1; j <= m; j++)
	     {
	    weight[i][j] = 0;
	    cost[i][j] = 0;
	    path[i][j] = 0;
	    }
	}
}

 
/* Get weights between the nodes and their neighbours(immediate) */
void get_wt() 
{
    int node1, node2;
    int w;
    printf("\nEnter the no of edges:");
    scanf("%d", &e);
    for (k = 1; k <= e; k++)
	 {
	printf("\nEnter the snode,dnode and wt of the edge %d:", k);
	cin >> node1 >> node2 >> w;
	for (i = 1; i <= m; i++)
	     {
	    for (j = 1; j <= m; j++)
		 {
		if (node[i] == node1 && node[j] == node2) {
		    weight[i][j] = w;	// Updating the weight matrix
		    weight[j][i] = w;
		}
		}
	    }
	}
    for (i = 1; i <= m; i++)
	 {
	for (j = 1; j <= m; j++)
	     {
	    if (weight[i][j] != 0)
		 {
		cost[i][j] = weight[i][j];
		path[i][j] = (i * 10) + j;
		}
	    
	    else
		cost[i][j] = 9999;	//infinity
	    }
	}
}

void display_given() 
{
    printf("\nMatrix representation of given graph:\n");
    for (i = 1; i <= m; i++)
	cout << "   " << name[i];
    printf("\n");
    for (i = 1; i <= m; i++)
	 {
	printf("%c", name[i]);
	for (j = 1; j <= m; j++)
	    cout << "   " << weight[i][j];
	printf("\n");
	}
/*
     printf("\nMatrix representation of cost graph:\n");
    for (i = 1; i <= m; i++)
	printf("   %c", name[i]);
    printf("\n");
    for (i = 1; i <= m; i++)
	 {
	printf("%c", name[i]);
	for (j = 1; j <= m; j++)
	     {
	    if (cost[i][j] < 9999)
		printf("  %d", cost[i][j]);
	    
	    else
		printf("  %c", 236);	//236 is ascii value for infinity character
	    }
	printf("\n");
	}
*/  
   printf("\nMatrix representation of path graph:\n");
    for (i = 1; i <= m; i++)
	printf("   %c", name[i]);
    printf("\n");
    for (i = 1; i <= m; i++)
	 {
	printf("%c", name[i]);
	for (j = 1; j <= m; j++)
	    printf("  %ld", path[i][j]);
	printf("\n");
	}
}

 void shortpath(int node1, int node2) 
{
    
	//Using Dijkstra's Algorithm for finding the shortest path
	for (k = 1; k <= m; k++)
	 {
	for (i = 1; i <= m; i++)
	     {
	    for (j = 1; j <= m; j++)
		 {
		 if (cost[i][j] > cost[i][k] + cost[k][j])
		     {
		    cost[i][j] = cost[i][k] + cost[k][j];
		    path[i][j] = (path[i][k] * 10) + j;
		    }
		}
	    }
	}
    for (i = 1; i <= m; i++)
	 {
	for (j = 1; j <= m; j++)
	     {
	    if (node1 == node[i] && node2 == node[j])
		 {
		co = cost[i][j];
		sp = path[i][j];
		}
	    }
	}
    
	//display_result();
	printf("\nThe shortest path for given nodes:\n");
    c = 0;
    i = 1;
    while (sp > 0)
	 {
	len[i] = sp % 10;
	c = c + 1;
	i = i + 1;
	sp = sp / 10;
	}
    for (i = c; i > 1; i--)
	 {
	printf("\t%c", name[len[i]]);
	printf("--->");
	}
    printf("%c", name[len[1]]);
    printf("\nThe weight of the path is :%d", co);
}

 void display_result() 
{
    printf("\nMatrix representation of result cost graph:\n\t");
    for (i = 1; i <= m; i++)
	printf("   %c", name[i]);
    printf("\n");
    for (i = 1; i <= m; i++)
	 {
	printf("%c", name[i]);
	for (j = 1; j <= m; j++)
	     {
	    if (cost[i][j] < 9999)
		printf("  %d", cost[i][j]);
	    
	    else
		printf("  %c", 236);	//236 is ascii value for infinity character
	    }
	printf("\n");
	}
     printf("\nMatrix representation of result path graph:\n\t");
    for (i = 1; i <= m; i++)
	printf("   %c", name[i]);
    printf("\n");
    for (i = 1; i <= m; i++)
	 {
	printf("%c", name[i]);
	for (j = 1; j <= m; j++)
	    printf("  %ld", path[i][j]);
	printf("\n");
	}
}
