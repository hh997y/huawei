#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
unordered_map<unsigned int,int> idHash;
unordered_map<int,vector<int>> lastlayerHash;
unordered_map<int,unordered_map<int,int>> tlastlayerHash;
// vector<unordered_map<int,int>> llastlayer;
// vector<unsigned int> tmply;
vector<unsigned int> ids;
vector<unsigned int> inputs;
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
    for(int &v:graph[cur]){
        // if(count(lastlayerHash[head].begin(),lastlayerHash[head].end(),v)>0 && depth>=2 && depth<=6 && v>head && !vis[v]){
        if(tlastlayerHash[head].count(v)>0 && depth>=2 && depth<=6 && v>head && !vis[v]){
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
    nodeCnt=0;
    // map
    for(unsigned int &x:tmp){
        idHash[x]=nodeCnt++;
    }
    graph=vector<vector<int>>(nodeCnt);
    for(int i=0;i<inputs.size();i+=2){
        int u=idHash[inputs[i]],v=idHash[inputs[i+1]];
        graph[u].push_back(v);

        if (tlastlayerHash.count(v)>0){
            // cout<<v<<endl;
            // lastlayerHash[v].push_back(u);  // x
            tlastlayerHash[v].emplace(u,0);
        }
        else{
            // cout<<v<<endl;
            // vector<int> tlast;  // x
            // tlast.push_back(u);  // x
            // lastlayerHash.emplace(v, tlast);
            unordered_map<int,int> tt;
            tt.emplace(u,0);
            tlastlayerHash.emplace(v,tt);
        }
    }
    // auto iter = llastlayer[lastlayerHash[idHash[1086]]].begin();//auto自动识别为迭代器类型unordered_map<int,string>::iterator
    // while (iter!= llastlayer[lastlayerHash[idHash[1086]]].end())
    // {  
    //     cout << ids[iter->first] << "," << iter->second << endl;  
    //     ++iter;  
    // }  
    // cout<<llastlayer[1086]<<endl;

    // get res
    vis=vector<bool>(nodeCnt,false);
    vector<int> path;
    for(int i=0;i<nodeCnt;i++){
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

    // // cout test
    // for(int i=0; i<res3.size(); i++){
    //     for (int j=0; j<res3[i].size(); j++){
    //         cout<<res3[i][j];
    //         cout<<" ";
    //     }
    //     cout<<" "<<endl;
    // }
    cout<<num<<endl;

    double rtime=(clock()-t)/CLOCKS_PER_SEC;
    cout<<"runtime: "<<rtime<<"s"<<endl;
}