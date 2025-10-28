#include <stdio.h>
#include <stdlib.h>

typedef int vertex;

typedef struct
{
    int V;
    int **adj;
} *Graph;

static int cnt;
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

void GRAPHdfs_iter_matrix(Graph G)
{
    int V = G->V;
    pre = malloc(sizeof(int) * V);
    for (int i = 0; i < V; i++)
        pre[i] = -1;
    int *stack = malloc(sizeof(int) * V);
    int top = 0;
    cnt = 0;
    for (vertex s = 0; s < V; s++)
    {
        if (pre[s] != -1)
            continue;
        pre[s] = cnt++;
        stack[top++] = s;
        while (top)
        {
            vertex v = stack[--top];
            for (vertex w = 0; w < V; w++)
            {
                if (G->adj[v][w] && pre[w] == -1)
                {
                    pre[w] = cnt++;
                    stack[top++] = w;
                }
            }
        }
    }
    free(stack);
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
    GRAPHdfs_iter_matrix(G);
    printf("pre:");
    for (int v = 0; v < G->V; v++)
        printf(" %d", pre[v]);
    printf("\n");
    return 0;
}
