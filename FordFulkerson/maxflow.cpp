#include "Graph.h"

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    long long V, E;
    scanf("%lld %lld", &V, &E);
    Graph graph(V, E);
    long long index = 0;
    while (E--) 
    {
        long long u, v, wt;
        scanf("%lld %lld %lld", &u, &v, &wt);
        graph.add_edge(u, v, wt, index);
    }
    clock_t tStart = clock();
    graph.Ford_Fulkerson();
    graph.print_mincut();
    clock_t tEnd = clock();
    printf("Time taken: %.6fs \n", (double)(tEnd - tStart) / CLOCKS_PER_SEC);
    return 0;
}
