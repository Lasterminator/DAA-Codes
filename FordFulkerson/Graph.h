#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
using namespace std;

#define EDGE pair<long long, long long>
class Graph
{
public:
    long long V;                      
    long long E; 
    long long sum = 0;                     
    
    vector<EDGE> *adj_list; 
    vector<EDGE> *residual_graph;

    unordered_map<long long, long long> lookup; 
    unordered_map<long long, long long> reverse_lookup; 

    vector<long long> indegree;
    vector<long long> outdegree;

    Graph(long long V, long long E);
    void add_edge(long long u, long long v, long long wt, long long &index);
    void print_graph(vector <EDGE> *graph);
    pair<long long, long long> find_source_sink();
    bool bfs(long long source, long long sink, vector<long long> &parent);
    void Ford_Fulkerson();
    void print_mincut();
};

#endif