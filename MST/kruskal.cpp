#include<bits/stdc++.h>
using namespace std;

void make(int v,int parent[],int size[])
{

    parent[v]=v;
    size[v]=1;
}
int find(int v,int parent[])
{
    if(v==parent[v])return parent[v];
    return parent[v]=find(parent[v],parent);
}
void uni(int u,int v,int parent[],int size[])
{
    int root_u=find(u,parent);
    int root_v=find(v,parent);
    if(root_u!=root_v)
    {
        if(size[root_u]<size[root_v])
            swap(root_u,root_v);
        parent[root_v]=root_u;
        size[root_u]=size[root_u]+size[root_v];
    }
}

void kruskal(int n,int parent[],int size[],vector<pair<float,pair<int,int>>>&weighted_graph,vector<pair<int,int>>&res)
{
    for(int i=0;i<n;i++)
        make(i,parent,size);
    float totalcost=0;

    for(auto &it:weighted_graph)
    {
        float weigh=it.first;
        int u=it.second.first;
        int v=it.second.second;
        if(find(u,parent)==find(v,parent))
            continue;
        uni(u,v,parent,size);
        totalcost+=weigh;

        res.push_back({u,v});
    }
    cout<<"Kruskal's Algorithm:"<<endl;
    cout<<"Total weight = "<<totalcost<<endl;

}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    cin>>n>>m;
    int parent[n];
    int size[n];
    vector<pair<float,pair<int,int>>>weighted_graph;
    for(int i=0;i<m;i++)
    {
        int u,v;
        float wt;
        cin>>u>>v>>wt;
        weighted_graph.push_back({wt,{u,v}});
    }
    sort(weighted_graph.begin(),weighted_graph.end());
    vector<pair<int,int>>res;
    kruskal(n,parent,size,weighted_graph,res);
    for(int i=0;i<res.size();i++)
    {
        cout<<res[i].first<<" "<<res[i].second<<endl;
    }

}
