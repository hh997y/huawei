#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
unordered_map<unsigned int,int> idHash;
unordered_map<int,vector<int>> lastlayerHash;
unordered_map<int,unordered_map<int,int>> tlastlayerHash;
vector<unsigned int> ids;
vector<unsigned int> inputs;
vector<bool> vis;
vector<vector<unsigned int>> res3;
vector<vector<unsigned int>> res4;
vector<vector<unsigned int>> res5;
vector<vector<unsigned int>> res6;
vector<vector<unsigned int>> res7;
vector<vector<bool>> lastlayer;
int nodenum;

void resappend(vector<unsigned int> tmp){
    if (tmp.size()==3){
        res3.push_back(tmp);
    }
    else if (tmp.size()==4){
        res4.push_back(tmp);
    }
    else if (tmp.size()==5){
        res5.push_back(tmp);
    }
    else if (tmp.size()==6){
        res6.push_back(tmp);
    }
    else if (tmp.size()==7){
        res7.push_back(tmp);
    }
}

void dfs(int head,int cur,int depth,vector<int> &path){
    vis[cur]=true;
    path.push_back(cur);
    for(int &v:graph[cur]){
        if(lastlayer[head][v]==1 && depth>=2 && depth<=6 && v>head && !vis[v]){
            vector<unsigned int> tmp;
            for(int &x:path)
                tmp.push_back(ids[x]);
            tmp.push_back(ids[v]);  // x
            resappend(tmp);
        }
        if(depth<6 && !vis[v] && v>head){  // x
            dfs(head,v,depth+1,path);
        }
    }
    vis[cur]=false;
    path.pop_back();
}

int main()
{
    double t=clock();

    // input
    string readin = "/data/test_data.txt";
    FILE* file=fopen(readin.c_str(),"r");
    unsigned int u,v,c;
    int cnt=0;
    while(fscanf(file,"%u,%u,%u",&u,&v,&c)!=EOF){
        inputs.push_back(u);
        inputs.push_back(v);
        ++cnt;
    }
    
    // graph
    auto tmp=inputs;
    sort(tmp.begin(),tmp.end());
    tmp.erase(unique(tmp.begin(),tmp.end()),tmp.end());
    ids=tmp;
    nodenum=0;
    // map
    for(unsigned int &x:tmp){
        idHash[x]=nodenum++;
    }
    cout<<"node num: "<<nodenum<<endl;
    graph=vector<vector<int>>(nodenum);
    vector<bool> layer(nodenum,false);
    lastlayer=vector<vector<bool>>(nodenum,layer);
    for(int i=0;i<inputs.size();i+=2){
        int u=idHash[inputs[i]],v=idHash[inputs[i+1]];
        graph[u].push_back(v);
        lastlayer[v][u] = true;
    }

    // get res
    vis=vector<bool>(nodenum,false);
    vector<int> path;
    for(int i=0;i<nodenum;i++){
        if(!graph[i].empty()){
            dfs(i,i,1,path);
        }
    }

    sort(res3.begin(),res3.end());
    sort(res4.begin(),res4.end());
    sort(res5.begin(),res5.end());
    sort(res6.begin(),res6.end());
    sort(res7.begin(),res7.end());

    // output
    string writeout = "/projects/student/result.txt";
    ofstream out(writeout);
    int num;
    num = res3.size() + res4.size() + res5.size() + res6.size() + res7.size();
    out<<num<<endl;
    for(auto &x:res3){
        out<<x[0];
        for(int i=1;i<x.size();i++)
            out<<","<<x[i];
        out<<endl;
    }
    for(auto &x:res4){
        out<<x[0];
        for(int i=1;i<x.size();i++)
            out<<","<<x[i];
        out<<endl;
    }
    for(auto &x:res5){
        out<<x[0];
        for(int i=1;i<x.size();i++)
            out<<","<<x[i];
        out<<endl;
    }
    for(auto &x:res6){
        out<<x[0];
        for(int i=1;i<x.size();i++)
            out<<","<<x[i];
        out<<endl;
    }
    for(auto &x:res7){
        out<<x[0];
        for(int i=1;i<x.size();i++)
            out<<","<<x[i];
        out<<endl;
    }

    cout<<num<<endl;

    double rtime=(clock()-t)/CLOCKS_PER_SEC;
    cout<<"runtime: "<<rtime<<"s"<<endl;
}
