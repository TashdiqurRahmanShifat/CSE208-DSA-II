#include<bits/stdc++.h>
using namespace std;

void mat(vector<vector<int>>dist,int n)
{
    for(int r=1; r<=n; r=2*r)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                for(int k=1; k<=n; k++)
                {
                    if(dist[i][k]!=INT_MAX&&dist[k][j]!=INT_MAX)
                    {
                        dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                    }
                }

            }

        }
    }
    int flag=0;
    for(int i=1; i<=n; i++)
    {
        if(dist[i][i]>0)
        {
            cout<<"Self Loop Exists"<<endl;
            flag=1;
            break;
        }
        if(dist[i][i]<0)
        {
            cout<<"Negative Weight Cycle Present"<<endl;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        cout<<"Shortest distance matrix"<<endl;

        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(dist[i][j]==INT_MAX)
                    cout<<"INF ";
                else
                    cout<<dist[i][j]<<" ";
            }
            cout<<endl;
        }
    }
}

void floyd(vector<vector<int>>dist,int n)
{
    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(dist[i][k]!=INT_MAX&&dist[k][j]!=INT_MAX)
                {
                    dist[i][j]=min(dist[i][j],(dist[i][k]+dist[k][j]));
                }
            }

        }
    }
    int flag=0;
    for(int i=1; i<=n; i++)
    {
        if(dist[i][i]>0)
        {
            cout<<"Self Loop Exists"<<endl;
            flag=1;
            break;
        }
        if(dist[i][i]<0)
        {
            cout<<"Negative Weight Cycle Present"<<endl;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        cout<<"Shortest distance matrix"<<endl;

        for(int i=1; i<=n; i++)
        {
            for(int j=1; j<=n; j++)
            {
                if(dist[i][j]==INT_MAX)
                    cout<<"INF ";
                else
                    cout<<dist[i][j]<<" ";
            }
            cout<<endl;
        }
    }

}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n,m;
    cin>>n>>m;
    vector<vector<int>>dist(n+1,vector<int>(n+1));

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=n; j++)
        {
            if(i==j)dist[i][j]=0;
            else dist[i][j]=INT_MAX;
        }
    }

    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        dist[u][v]=w;
    }
    floyd(dist,n);
    mat(dist,n);
}
