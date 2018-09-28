#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> iPair;

// Creating graph...
struct Graph
{
	int V, E;
	vector<pair<int,iPair> > edges;	
	Graph(int V, int E)
	{
		this->V;
		this->E;
	}
	void addEdge(int u, int v, int w)
	{
		edges.push_back({w,{u,v}});	// Note: First w as sorting according to weight is required.
	}	
	int kruskalMST();
};

// Union-find using path compression to detect cycles.
struct DisjointSets
{
	int *parent, *rank;
	int n;
	
	DisjointSets(int n)
    {
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];
        for (int i = 0; i <= n; i++)
        {
            rank[i] = 0;
            parent[i] = i;
        }
    }
    
    int find(int u)
    {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }
 
    void merge(int x, int y)
    {
        x = find(x), y = find(y);
        
        if (rank[x] > rank[y])
            parent[y] = x;
        else
            parent[x] = y;

        if (rank[x] == rank[y])
            rank[y]++;
    }    
};

// Kruskal...
int Graph::kruskalMST()
{
    int mst_wt = 0;
    sort(edges.begin(), edges.end());
    DisjointSets ds(V);

    vector< pair<int, iPair> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++)
    {
        int u = it->second.first;
        int v = it->second.second;
 
        int set_u = ds.find(u);
        int set_v = ds.find(v);

        if (set_u != set_v)
        {
            cout << u << " - " << v << "\n";
            mst_wt += it->first;
            ds.merge(set_u, set_v);
        }
    }
    return mst_wt;
}

int main()
{
	int V, E;
	cin>>V>>E;
	Graph g(V,E);
	for(int i=0;i<E;i++)
	{
		int u, v, wt;
		cin>>u>>v>>wt;
		g.addEdge(u,v,wt);
	}
	cout << "Edges of MST are \n";
    int mst_wt = g.kruskalMST();
    cout << "\nWeight of MST is " << mst_wt;		
	return 0;
}
