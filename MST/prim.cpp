#include<bits/stdc++.h>
using namespace std;
void prim(int n,float weight[],int parent[],bool mst[],int initial,vector<pair<int,float>>graph[])
{
    for(int i=0;i<n;i++)
    {
        weight[i]=INT_MAX;
        parent[i]=-1;
        mst[i]=false;
    }
    priority_queue<pair<int,float>,vector<pair<int,float>>,greater<pair<int,float>>>p;
    int start=initial;

    weight[start]=0;
    parent[start]=-1;
    p.push({0,start});


    while(!p.empty())
    {
        int index=p.top().second;
        p.pop();
        if(mst[index]==true)continue;
        mst[index]=true;
        for(auto &it:graph[index])
        {
            int ind=it.first;
            float wt=it.second;
            if(mst[ind]==false&&wt<weight[ind])
            {
                weight[ind]=wt;

                p.push({weight[ind],ind});
                parent[ind]=index;

            }

        }
    }
}
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<pair<int,float>>graph[n];
    for(int i=0;i<m;i++)
    {
        int u,v;
        float wt;
        cin>>u>>v>>wt;
        graph[u].push_back({v,wt});
        graph[v].push_back({u,wt});
    }
    float weight[n];
    int parent[n];
    bool mst[n];
    int root=0;

    prim(n,weight,parent,mst,root,graph);
    float totalweight=0;
    cout<<"Prim-Jarnik's Algorithm:"<<endl;
    for(int i=0;i<n;i++)
        totalweight+=weight[i];
    cout<<"Total Weight = "<<totalweight<<endl;
    cout<<"Root node = "<<root<<endl;
    for(int i=0;i<n;i++)
    {
        if(parent[i]==-1)continue;
        cout<<parent[i]<<" "<<i<<endl;
    }
}
