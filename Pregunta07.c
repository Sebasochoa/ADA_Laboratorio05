#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct
{
    vertex v;
    link it;
} Frame;
typedef struct
{
    Frame *a;
    int n, cap;
} Stack;

static int cnt;
static int *pre;

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
void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
    G->adj[v] = NEW(w, G->adj[v]);
}

Graph readAdjFile(const char *path)
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
    char line[1 << 15];
    fgets(line, sizeof(line), f);
    for (int i = 0; i < V; i++)
    {
        if (!fgets(line, sizeof(line), f))
            break;
        char *p = line;
        while (*p == ' ' || *p == '\t')
            p++;
        if (*p == '\0' || *p == '\n')
            continue;
        int v = atoi(p);
        while (*p && *p != ' ' && *p != '\t' && *p != ':' && *p != '\n')
            p++;
        if (*p == ':')
            p++;
        while (*p)
        {
            while (*p == ' ' || *p == '\t')
                p++;
            if (*p == '\n' || *p == '\0')
                break;
            int w = atoi(p);
            GRAPHinsertArc(G, v, w);
            while (*p && *p != ' ' && *p != '\t' && *p != '\n')
                p++;
        }
    }
    fclose(f);
    return G;
}

void Sinit(Stack *S, int cap)
{
    S->a = malloc(sizeof(Frame) * cap);
    S->n = 0;
    S->cap = cap;
}
void Spush(Stack *S, Frame f)
{
    if (S->n == S->cap)
    {
        S->cap *= 2;
        S->a = realloc(S->a, sizeof(Frame) * S->cap);
    }
    S->a[S->n++] = f;
}
Frame Spop(Stack *S) { return S->a[--S->n]; }
int Sempty(Stack *S) { return S->n == 0; }

void GRAPHdfs_iter(Graph G)
{
    cnt = 0;
    pre = malloc(sizeof(int) * G->V);
    for (vertex v = 0; v < G->V; v++)
        pre[v] = -1;
    Stack S;
    Sinit(&S, G->V ? G->V : 1);
    for (vertex s = 0; s < G->V; s++)
    {
        if (pre[s] != -1)
            continue;
        pre[s] = cnt++;
        Spush(&S, (Frame){s, G->adj[s]});
        while (!Sempty(&S))
        {
            Frame *t = &S.a[S.n - 1];
            if (t->it == NULL)
            {
                Spop(&S);
                continue;
            }
            vertex w = t->it->w;
            t->it = t->it->next;
            if (pre[w] == -1)
            {
                pre[w] = cnt++;
                Spush(&S, (Frame){w, G->adj[w]});
            }
        }
    }
    free(S.a);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("uso: %s archivo_lista\n", argv[0]);
        return 1;
    }
    Graph G = readAdjFile(argv[1]);
    if (!G)
    {
        printf("error de archivo\n");
        return 1;
    }
    GRAPHdfs_iter(G);
    printf("pre:");
    for (int v = 0; v < G->V; v++)
        printf(" %d", pre[v]);
    printf("\n");
    return 0;
}
