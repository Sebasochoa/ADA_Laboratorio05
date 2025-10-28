#include <stdio.h>
#include <stdlib.h>

typedef int vertex;
typedef struct node
{
    vertex w;
    struct node *next;
} *link;
typedef struct graph
{
    int V;
    link *adj;
} *Graph;

static int cnt, indent, pre[10000];

Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->adj = calloc(V, sizeof(link));
    return G;
}
link NEW(vertex w, link next)
{
    link a = malloc(sizeof(*a));
    a->w = w;
    a->next = next;
    return a;
}
void addEdge(Graph G, vertex v, vertex w)
{
    G->adj[v] = NEW(w, G->adj[v]);
    G->adj[w] = NEW(v, G->adj[w]);
}

static void printIndent(int k)
{
    for (int i = 0; i < k; i++)
        putchar(' ');
}

static void dfsR_trace(Graph G, vertex v)
{
    pre[v] = cnt++;
    printIndent(indent);
    printf("%d dfsR(G,%d)\n", v, v);
    indent += 2;
    for (link a = G->adj[v]; a; a = a->next)
    {
        vertex w = a->w;
        printIndent(indent);
        if (pre[w] == -1)
        {
            printf("%d-%d dfsR(G,%d)\n", v, w, w);
            dfsR_trace(G, w);
        }
        else
            printf("%d-%d\n", v, w);
    }
    indent -= 2;
    printIndent(indent);
    printf("%d\n", v);
}

void GRAPHdfs_trace(Graph G)
{
    cnt = 0;
    indent = 0;
    for (vertex v = 0; v < G->V; v++)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR_trace(G, v);
}

int main()
{
    Graph G = GRAPHinit(10);
    addEdge(G, 3, 7);
    addEdge(G, 1, 4);
    addEdge(G, 7, 8);
    addEdge(G, 0, 5);
    addEdge(G, 5, 2);
    addEdge(G, 3, 8);
    addEdge(G, 2, 9);
    addEdge(G, 0, 6);
    addEdge(G, 4, 9);
    addEdge(G, 2, 6);
    addEdge(G, 6, 4);
    GRAPHdfs_trace(G);
    printf("pre:");
    for (int v = 0; v < G->V; v++)
        printf(" %d", pre[v]);
    printf("\n");
    return 0;
}
