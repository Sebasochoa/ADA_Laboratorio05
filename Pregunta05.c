#include <stdio.h>
#include <stdlib.h>

typedef int vertex;

typedef struct
{
    int V;
    int **adj;
} *Graph;

static int cnt, indent;
static int *pre;

Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->adj = malloc(sizeof(int *) * V);
    for (int i = 0; i < V; i++)
    {
        G->adj[i] = malloc(sizeof(int) * V);
        for (int j = 0; j < V; j++)
            G->adj[i][j] = 0;
    }
    return G;
}

Graph readMatrixFile(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
        return NULL;
    int V;
    if (fscanf(f, "%d", &V) != 1 || V <= 0)
    {
        fclose(f);
        return NULL;
    }
    Graph G = GRAPHinit(V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            fscanf(f, "%d", &G->adj[i][j]);
    fclose(f);
    return G;
}

void printIndent(int k)
{
    for (int i = 0; i < k; i++)
        putchar(' ');
}

void dfsR_trace(Graph G, vertex v)
{
    pre[v] = cnt++;
    printIndent(indent);
    printf("%d dfsR(G,%d)\n", v, v);
    indent += 2;
    for (vertex w = 0; w < G->V; w++)
    {
        printIndent(indent);
        if (G->adj[v][w])
        {
            if (pre[w] == -1)
            {
                printf("%d-%d dfsR(G,%d)\n", v, w, w);
                dfsR_trace(G, w);
            }
            else
                printf("%d-%d\n", v, w);
        }
    }
    indent -= 2;
    printIndent(indent);
    printf("%d\n", v);
}

void GRAPHdfs_trace(Graph G)
{
    cnt = 0;
    indent = 0;
    pre = malloc(sizeof(int) * G->V);
    for (int v = 0; v < G->V; v++)
        pre[v] = -1;
    for (int v = 0; v < G->V; v++)
        if (pre[v] == -1)
            dfsR_trace(G, v);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("uso: %s archivo_matriz\n", argv[0]);
        return 1;
    }
    Graph G = readMatrixFile(argv[1]);
    if (!G)
    {
        printf("error de archivo\n");
        return 1;
    }
    GRAPHdfs_trace(G);
    printf("pre:");
    for (int v = 0; v < G->V; v++)
        printf(" %d", pre[v]);
    printf("\n");
    return 0;
}
