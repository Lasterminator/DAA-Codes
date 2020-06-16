#include "Graph.h"

Graph ::Graph(long long V, long long E)
{
    this->V = V;
    this->E = E;
    adj_list = new vector<EDGE>[V];
    residual_graph = new vector<EDGE>[V];
    indegree.resize(V, 0);
    outdegree.resize(V, 0);
}
void Graph ::add_edge(long long u, long long v, long long wt, long long &index)
{
    if (index == -1) {
        outdegree[u]++;
        indegree[v]++;
        adj_list[u].push_back({v, wt});
        residual_graph[u].push_back({v, wt});
        return;
    }
    if (lookup.find(u) == lookup.end()) {
        lookup[u] = index;
        reverse_lookup[index] = u;
        index++;
    }
    if (lookup.find(v) == lookup.end()) {
        lookup[v] = index;
        reverse_lookup[index] = v;
        index++;
    }
    long long u_lookup = lookup[u], v_lookup = lookup[v];
    outdegree[u_lookup]++;
    indegree[v_lookup]++;
    adj_list[u_lookup].push_back({v_lookup, wt});
    residual_graph[u_lookup].push_back({v_lookup, wt});
}

void Graph ::print_graph(vector<EDGE> *graph)
{
    for (long long u = 0; u < V; ++u)
    {
        for (EDGE e : graph[u])
        {
            printf("%lld %lld %lld\n", 
            reverse_lookup[u], reverse_lookup[e.first], e.second);
        }
    }
}

pair<long long, long long> Graph ::find_source_sink()
{
    long long source = -1, sink = -1;
    long long src_ct = 0, sink_ct = 0;
    
    for (long long i = 0; i < V; ++i)
    {
        if (indegree[i] == 0)
        {
            source = i;
            ++src_ct;
        }
        if (outdegree[i] == 0)
        {
            sink = i;
            ++sink_ct;
        }
    }
    if (source == -1 || sink == -1)
    {
        printf("Error Log: No Source/Sink Vertex\n");
        exit(0);
    }
    if (src_ct > 1)
    {
        printf("More than one source\n");
    }
    if (sink_ct > 1)
    {
        printf("More than one sink\n");
    }
    return {source, sink};
}
bool Graph::bfs(long long source, long long sink, vector<long long> &parent)
{
    vector<bool> visited(V, false);
    queue<long long> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;
    while (!q.empty())
    {
        long long u = q.front();
        q.pop();

        for (EDGE e : residual_graph[u])
        {
            int v = e.first;
            if (!visited[v] && e.second != 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[sink];
}
void Graph ::Ford_Fulkerson()
{
    pair<long long, long long> nodes = find_source_sink(); // O(V)
    long long source = nodes.first;
    long long sink = nodes.second;

    vector<long long> parent(V);
    long long max_flow = 0;

    while (bfs(source, sink, parent)) 
    {
        long long b = INT_MAX; 
        for (long long v = sink; v != source; v = parent[v])
        {
            long long u = parent[v];
            for (EDGE e : residual_graph[u])
            {
                if (e.first == v)
                {
                    b = min(b, e.second);
                    break;
                }
            }
        }
        if (b == 0)
        {
            printf("Error Log: 0 Bottleneck capacity\n");
            exit(0);
        }
        for (long long v = sink; v != source; v = parent[v])
        {
            long long u = parent[v];
            for (EDGE &e : residual_graph[u])
            {
                if (e.first == v)
                {
                    e.second = e.second - b;
		    break;
                }
            }
            bool edge_found = false;
            for (EDGE &e : residual_graph[v])
            {
                if (e.first == u)
                {
                    e.second = e.second + b;
                    edge_found = true;
		    break;
                }
            }
            if(!edge_found)
            {
                residual_graph[v].push_back({u, b});
            }
        }
        max_flow += b;
    }
    printf("%lld\n", max_flow);
}

void Graph::print_mincut()
{
    vector<bool> visited(V, false);
    queue<long long> q;
    pair<long long, long long> nodes = find_source_sink();
    long long source = nodes.first;
    q.push(source);
    visited[source] = true;
    while (!q.empty())
    {
        long long u = q.front();
        q.pop();

        for (EDGE e : residual_graph[u])
        {
            long long v = e.first;
            if (!visited[v] && e.second != 0)
            {
                q.push(v);
                visited[v] = true;
            }
        }
    }
    for (long long u = 0; u < V; ++u)
    {
        if (visited[u])
        {
            for (EDGE e : adj_list[u])
            {
                long long v = e.first;
                
                if (!visited[v])
                {
                    printf("%lld,%lld\n",
                    reverse_lookup[u], reverse_lookup[v]);
                    sum += e.second;                    
                }
            }
        }
    }
    printf("%lld\n",sum);
}
