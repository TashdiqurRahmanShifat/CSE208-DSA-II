#include<bits/stdc++.h>
using namespace std;
void bellman(int src,int des,int n, vector<pair<int,pair<int,int>>>&g)
{
    vector<int>distance(n,INT_MAX);
    vector<int>parent(n,-1);
    for(int i=0; i<n; i++)
    {
        parent[i]=i;
    }
    distance[src]=0;
    for(int i=0; i<n-1; i++)
    {
        for(auto &it:g)
        {
            int node=it.first;
            int adj_node=it.second.first;
            int adj_weight=it.second.second;
            if(distance[node]!=INT_MAX&&distance[node]+adj_weight<distance[adj_node])
            {
                distance[adj_node]=distance[node]+adj_weight;
                parent[adj_node]=node;
            }
        }
    }
    int flag=0;
    for(auto &it:g)
    {
        int node=it.first;
        int adj_node=it.second.first;
        int adj_weight=it.second.second;
        if(distance[node]+adj_weight<distance[adj_node])
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        cout<<"Bellman Ford Algorithm:"<<endl;
        cout<<"Negative weight cycle present"<<endl;
        return;
    }

    vector<int>path;
    int last=des;
    while(parent[last]!=last)
    {
        path.push_back(last);
        last=parent[last];
    }
    path.push_back(src);
    reverse(path.begin(),path.end());
    int len=path.size();
    cout<<"Bellman Ford Algorithm:"<<endl;
    cout<<distance[path[len-1]]<<endl;
    for(int i=0; i<path.size()-1; i++)
    {
        cout<<path[i]<<"->";
    }
    cout<<path[len-1];
    cout<<endl;

}
void dijkstra(int src,int des,int n,vector<pair<int,int>>gr[])
{
    vector<bool>visited(n,false);
    vector<int>distance(n,INT_MAX);
    vector<int>parent(n,-1);
    for(int i=0; i<n; i++)
    {
        parent[i]=i;
    }


    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>p;
    int cost=0;
    distance[src]=0;
    p.push({0,src});
    while(!p.empty())
    {
        int node=p.top().second;
        int dist=p.top().first;

        p.pop();
        if(visited[node])continue;
        visited[node]=true;

        for(auto &it:gr[node])
        {
            int adj_vertex=it.first;
            int adj_vertexwt=it.second;
            if(visited[adj_vertex])continue;
            if(distance[node]!=INT_MAX&&distance[node]+adj_vertexwt<distance[adj_vertex])
            {
                distance[adj_vertex]=distance[node]+adj_vertexwt;

                p.push({distance[adj_vertex],adj_vertex});
                parent[adj_vertex]=node;
            }


        }
    }
    vector<int>path;
    int last=des;
    while(parent[last]!=last)
    {
        path.push_back(last);
        last=parent[last];
    }
    path.push_back(src);
    reverse(path.begin(),path.end());
    cout<<"Dijkstra Algorithm:"<<endl;

    int l=path.size();
    cout<<distance[path[l-1]]<<endl;
    for(int i=0; i<path.size()-1; i++)
    {
        cout<<path[i]<<"->";

    }
    cout<<path[l-1];
    cout<<endl;


    //for(int i=0; i<n; i++)
    //{
    //    cout<<distance[i]<<" ";
    //}

}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>>g;
    vector<pair<int,int>>gr[n];
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.push_back({u,{v,w}});
        gr[u].push_back({v,abs(w)});
    }
    int s,d;
    cin>>s>>d;
    bellman(s,d,n,g);
    cout<<endl;
    dijkstra(s,d,n,gr);

}

