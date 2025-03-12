#include<bits/stdc++.h>
using namespace std;

class Graph
{
    int num_of_nodes;
    vector<vector<int>>adj;
    vector<int>parent;
    vector<vector<int>>residual_cap;
    int total_match;

    void addEdge(int u,int v,int capacity)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
        residual_cap[u][v]=capacity;
    }

    int bfs(int source,int sink)
    {
        for(int i=0;i<parent.size();i++)
        {
            parent[i]=-1;
        }
        fill(parent.begin(),parent.end(),-1);
        parent[source]=-2;
        queue<pair<int,int>>q;
        q.push({source,INT_MAX});
        while(!q.empty())
        {
            int curr_node=q.front().first;
            int flow=q.front().second;
            q.pop();

            for(auto next_node:adj[curr_node])
            {
                if(parent[next_node]==-1&&residual_cap[curr_node][next_node]>0)
                {
                    parent[next_node]=curr_node;
                    int newflow=min(flow,residual_cap[curr_node][next_node]);
                    if(next_node==sink)
                        return newflow;
                    q.push({next_node,newflow});
                }
            }
        }
        return 0;

    }

    int maximum_flow(int source,int sink)
    {
        int flow=0;
        int newflow;
        while((newflow=bfs(source,sink))>0)
        {
            flow=flow+newflow;
            int last_node=sink;
            while(last_node!=source)
            {
                int prev_node=parent[last_node];
                residual_cap[prev_node][last_node]-=newflow;
                residual_cap[last_node][prev_node]+=newflow;
                last_node=prev_node;
            }
        }
        return flow;
    }

    void find_nodes(int source)
    {
        for(int i=0;i<parent.size();i++)
        {
            parent[i]=-1;
        }
        parent[source]=-2;
        queue<int>q;
        q.push(source);
        while(!q.empty())
        {
            int curr_node=q.front();
            q.pop();
            for(auto next_node:adj[curr_node])
            {
                if(parent[next_node]==-1&&residual_cap[curr_node][next_node]>0)
                {
                    parent[next_node]=curr_node;
                    q.push(next_node);
                }
            }
        }

    }

public:
    Graph(int total_team,int current_team,vector<vector<int>>&against,vector<int>&wins,vector<int>&left)
    {
        total_match=((total_team-1)*(total_team-2))/2;
        num_of_nodes=2+total_team+total_match;
        adj.resize(num_of_nodes);
        parent.resize(num_of_nodes);
        residual_cap.resize(num_of_nodes,vector<int>(num_of_nodes,0));
        int current_match=1;
        for(int i=0;i<total_team;i++)
        {
            if(i==current_team)continue;
            for(int j=i+1;j<total_team;j++)
            {
                if(j==current_team)continue;
                addEdge(0,current_match,against[i][j]);
                addEdge(current_match,total_match+i+1,INT_MAX);
                addEdge(current_match,total_match+j+1,INT_MAX);
                current_match++;
            }
        }
        for(int i=0;i<total_team;i++)
        {
            if(i==current_team)continue;
            addEdge(total_match+1+i,num_of_nodes-1,wins[current_team]+left[current_team]-wins[i]);
        }
    }

    void elimination_check(vector<int>&count_team,int total_team)
    {
        find_nodes(0);
        for(int i=0;i<total_team;i++)
        {
            if(parent[total_match+i+1]!=-1)
            {
                count_team.push_back(i);
            }
        }
    }

    bool check_flow()
    {
        int flow=maximum_flow(0,num_of_nodes-1);
        for(int i=1;i<total_match+1;i++)
        {
            if(residual_cap[0][i]>0)
                return false;
        }
        return true;
    }
};

void eliminated(vector<int>&count_team,vector<int>&wins,int total_team,int winleft)
{
    int winner_id_so_far,maxwin=-1;
    for(int i=0;i<total_team;i++)
    {
        if(wins[i]>maxwin)
        {
            winner_id_so_far=i;
            maxwin=wins[i];
        }
    }
    if(maxwin>winleft)
    {
        count_team.push_back(winner_id_so_far);
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    vector<string>team(n);
    vector<int>wins(n);
    vector<int>losses(n);
    vector<int>left(n);
    vector<vector<int>>against(n,vector<int>(n));
    for(int i=0;i<n;i++)
    {
        string name;
        cin>>name;
        team[i]=name;
        int win,lost,remains;
        cin>>win>>lost>>remains;
        wins[i]=win;
        losses[i]=lost;
        left[i]=remains;
        for(int j=0;j<n;j++)
        {
            int x;
            cin>>x;
            against[i][j]=x;
        }
    }
    for(int i=0;i<n;i++)
    {
        vector<int>count_team;
        eliminated(count_team,wins,n,wins[i]+left[i]);
        if(count_team.size()==0)
        {
            Graph graph(n,i,against,wins,left);
            bool check=graph.check_flow();
            if(check==false)
                graph.elimination_check(count_team,n);
        }
        int size=count_team.size();
        if(count_team.size()>0)
        {
            cout<<team[i]<<" is eliminated."<<endl;
            cout<<"They can win at most "<<wins[i]<<" + "<<left[i]<<" = "<<wins[i]+left[i]<<" games."<<endl;
            int num_of_win=0;
            for(int j=0;j<size;j++)
            {
                num_of_win+=wins[count_team[j]];
            }
            cout<<team[count_team[0]];
            for(int j=1;j<size-1;j++)
            {
                cout<<" , "<<team[count_team[j]];
            }
            if(size>1)
                cout<<" and "<<team[count_team[size-1]]<<" have ";
            else cout<<" has ";
            cout<<"won a total of "<<num_of_win<<" games."<<endl;
            int num_of_games=0;
            for(int j=0;j<size;j++)
            {
                for(int k=j+1;k<size;k++)
                {
                    num_of_games+=against[count_team[j]][count_team[k]];
                }
            }
            cout<<"They play each other "<<num_of_games<<" times."<<endl;
            double final_result=((num_of_win*1.0)+num_of_games)/size;
            cout<<"So on average, each of the teams in this group wins "<<num_of_win+num_of_games<<"/"<<size<<" = "<<final_result<<" games."<<endl;
            cout<<endl;
        }
    }
}
