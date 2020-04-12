#include <bits/stdc++.h>
using namespace std;

// 只是测试！只是测试！只是测试！

vector<vector<int>> G;
unordered_map<unsigned int,int> idHash;
vector<unsigned int> ids;
vector<unsigned int> inputs;
vector<int> inDegrees;
vector<bool> vis;
vector<vector<unsigned int>> res3;
vector<vector<unsigned int>> res4;
vector<vector<unsigned int>> res5;
vector<vector<unsigned int>> res6;
vector<vector<unsigned int>> res7;
int nodeCnt;

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
    for(int &v:G[cur]){
        if(v==head && depth>=3 && depth<=7){
            vector<unsigned int> tmp;
            for(int &x:path)
                tmp.push_back(ids[x]);
            resappend(tmp);
        }
        if(depth<7 && !vis[v] && v>head){
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
    nodeCnt=tmp.size();
    ids=tmp;
    nodeCnt=0;
    for(unsigned int &x:tmp){
        idHash[x]=nodeCnt++;
    }
    int sz=inputs.size();
    //G=new vector<int>[nodeCnt];
    G=vector<vector<int>>(nodeCnt);
    inDegrees=vector<int>(nodeCnt,0);
    for(int i=0;i<sz;i+=2){
        int u=idHash[inputs[i]],v=idHash[inputs[i+1]];
        G[u].push_back(v);
        ++inDegrees[v];
    }

    // get res
    vis=vector<bool>(nodeCnt,false);
    vector<int> path;
    for(int i=0;i<nodeCnt;i++){
        if(!G[i].empty()){
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

    double rtime=(clock()-t)/CLOCKS_PER_SEC;
    cout<<"runtime: "<<rtime<<"s"<<endl;
}