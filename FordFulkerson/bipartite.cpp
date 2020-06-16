#include "Graph.h"

int main()
{
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    long long m, n, E;
    scanf("%lld %lld %lld", &m, &n, &E);
    long long V = m + n;
    Graph graph(V + 2, E);
    long long index = -1;
    long long ind = 0;
    long long source = V;
    long long sink = V + 1;
    unordered_map<long long, long long> left_lookup;
    unordered_map<long long, long long> l_reverse_lookup;
    unordered_map<long long, long long> right_lookup;
    unordered_map<long long, long long> r_reverse_lookup;
    while (E--) 
    {
        long long u, v;
        scanf("%lld %lld", &u, &v);
        if (left_lookup.find(u) == left_lookup.end())
        {
            left_lookup[u] = ind;
            l_reverse_lookup[ind] = u;
            ind++;
        }
        if (right_lookup.find(v) == right_lookup.end())
        {
            right_lookup[v] = ind;
            r_reverse_lookup[ind] = v;
            ind++;
        }
        long long u_lookup = left_lookup[u], v_lookup = right_lookup[v];
        graph.add_edge(u_lookup, v_lookup, 1, index);
    }
    for (auto it : left_lookup)
    {
        graph.add_edge(source, it.second, 1, index);
    }
    for (auto it : right_lookup)
    {
        graph.add_edge(it.second, sink, 1, index);
    }
    clock_t tStart, tEnd;
    tStart = clock();
    graph.Ford_Fulkerson();
    auto residual_graph = graph.residual_graph;
    for (long long u = 0; u < V; ++u)
    {
        for (EDGE e : residual_graph[u])
        {
            long long v = e.first;
            if (e.second == 0)
            {
                if(l_reverse_lookup.find(u) != l_reverse_lookup.end())
                {
                    printf("%lld %lld\n", 
                    l_reverse_lookup[u], r_reverse_lookup[v]);
                }
            }
        }
    }
    tEnd = clock();
    printf("Time taken: %.6fs \n", (double)(tEnd - tStart) / CLOCKS_PER_SEC);
}