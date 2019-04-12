#include<iostream>
#include"base/ReadData.h"
#include "base/Utils.h"
#include "base/WriteData.h"
#include<string>
#include<vector>
#include<memory>
#include<limits>
#include<map>
#include<algorithm>
#include<set>
#include<stack>
using namespace std;

struct Edge;
struct requestInfo;
struct Node;
//存放原始拓扑信息
/**
 *  500 955
    0 1 20000 4
    0 20 30000 1
    1 2 20000 5
 * */
vector<int> gridTopo[956];
//存放所有业务需求信息
/**
    0 49
    0 1 2 3 23 43 63 83 103 123 143 163 183 203 223 243 263 283 303 323 343
    0 20 21 22 42 62 82 102 122 142 162 182 202 222 242 262 282 302 322 342 343
    0 1 21 41 42 43 44 64 84 104 124 144 164 184 204 224 244 264 284 304 324 344 343
 * */
vector<int> request[4001];
//节点到节点的路径（包含备用路径）
map<int,map<int,vector<vector<int>>>> edger;
map<int,map<int,vector<int>>> costs;
vector<vector<int>> costvv(500,vector<int>(500,INT16_MAX));
//存放开始结束地址
map<int,map<int,Edge>> ways;
vector<requestInfo> reqinfos;
map<int,Node> nodes;

void clear()
{
    for(int i=0;i<956;i++) gridTopo[i].clear();
    for(int i=0;i<4001;i++) request[i].clear();
}

void readTxt()
{

    DataReader reader("data/gridtopoAndRequest.txt");
    vector<string> lines = reader.readLines();
    for(int i = 0;i<956;i++)
    {
        vector<string> sv;
        Utils::splitString(lines[i]," ",sv);
        for(const string& s : sv)
        {
            gridTopo[i].push_back(stoi(s));
        }
    }
    for(int i = 0;i<4001;i++)
    {
        vector<string> sv;
        Utils::splitString(lines[956+i]," ",sv);
        for(const string& s : sv)
        {
            request[i].push_back(stoi(s));
        }
    }

}
struct Node{
    int nodeid;
    vector<Edge> edges;
    explicit Node(int nodeid)
            :nodeid(nodeid)
    {}
    explicit Node() = default;
};

//边信息
struct Edge {
    Node from;
    Node to;
    int maxBindWidth;
    int perCost;
    int curBindWidth;
    explicit Edge(int from, int to, int maxBindWidth, int perCost)
            :   maxBindWidth(maxBindWidth),
                perCost(perCost),curBindWidth(maxBindWidth)
    {
        if(nodes.find(from)==nodes.end())
        {
            this->from = Node(from);
            nodes[from] = this->from;
        }
        else
        {
            this->from = nodes[from];
        }
        if(nodes.find(to)==nodes.end())
        {
            this->to = Node(to);
            nodes[to] = this->to;
        }
        else
        {
            this->to = nodes[to];
        }
    }
    explicit Edge() = default;
};


//请求信息
struct requestInfo
{
    int id;
    int from;
    int to;
    int equality;
    requestInfo(int id,int equalisty)
        :   id(id),equality(equalisty){}
};


void insert(int from,int to,vector<int>* ptr,requestInfo& info)
{

    for(int j = 0;j<ptr->size();j++)
    {
        for(int i = j+1;i<ptr->size();i++)
        {
            vector<int> v;
            for(int k = j;k<=i;k++)
            {
                v.push_back(ptr->at(k));
            }
            if(edger.find(ptr->at(j))!=edger.end())
            {

                if(edger[ptr->at(j)].find(ptr->at(i))==edger[ptr->at(j)].end())
                {
                    edger[ptr->at(j)][ptr->at(i)] = vector<vector<int>>{v};
                }
                else
                {
                    if(find(edger[ptr->at(j)][ptr->at(i)].begin(),edger[ptr->at(j)][ptr->at(i)].end(),v)==edger[ptr->at(j)][ptr->at(i)].end())
                        edger[ptr->at(j)][ptr->at(i)].push_back(v);
                }
            }
            else
            {
                edger[ptr->at(j)][ptr->at(i)] = vector<vector<int>>{v};
            }
        }
    }for(int j = ptr->size()-1;j>=0;j--)
    {
        for(int i = j-1;i>=0;i--)
        {
            vector<int> v;
            for(int k = j;k>=i;k--)
            {
                v.push_back(ptr->at(k));
            }
            if(edger.find(ptr->at(j))!=edger.end())
            {

                if(edger[ptr->at(j)].find(ptr->at(i))==edger[ptr->at(j)].end())
                {
                    edger[ptr->at(j)][ptr->at(i)] = vector<vector<int>>{v};
                }
                else
                {
                    if(find(edger[ptr->at(j)][ptr->at(i)].begin(),edger[ptr->at(j)][ptr->at(i)].end(),v)==
                            edger[ptr->at(j)][ptr->at(i)].end())
                        edger[ptr->at(j)][ptr->at(i)].push_back(v);
                }
            }
            else
            {
                edger[ptr->at(j)][ptr->at(i)] = vector<vector<int>>{v};
            }
        }
    }


}
void GenerateOriginalDistance()
{
    for(int i = 1;i<956;i++)
    {
        auto ptr = gridTopo+i;
        int from = ptr->at(0);
        int to = ptr->at(1);

        costvv[from][to] = ptr->at(3);
        costvv[to][from] = ptr->at(3);
        ways[from][to]=Edge(from,to,ptr->at(2),ptr->at(3));
        ways[to][from]=Edge(to,from,ptr->at(2),ptr->at(3));
        costvv[from][from] = 0;
        costvv[to][to] = 0;
    }
    for(int i = 1;i<4001;)
    {

        if((request+i)->size()==2)
        {
            requestInfo info((request+i)->at(0),(request+i)->at(1));
            ++i;
            while((request+i)->size()!=2 && i <4001)
            {
                info.from= *((request+i)->begin());
                info.to = *((request+i)->end()-1);

                insert(info.from,info.to,(request+i),info);
//                insert(info.to,info.from,(request+i),info);
//                reverse(edger[info.to][info.from].begin(),edger[info.to][info.from].end());
                ++i;
            }
            reqinfos.push_back(info);
        }
    }
}

void computeCosts(requestInfo& requestInfo)
{
    auto edges = edger[requestInfo.from][requestInfo.to];
    costs[requestInfo.from][requestInfo.to]={};
    for(const auto& f : edges)
    {
        int sum = 0;
        for(const auto& zh : f)
        {
            sum+=(zh*requestInfo.equality);
        }
        costs[requestInfo.from][requestInfo.to].push_back(sum);
    }
}
void DijkstraUpdate(int it) {
    vector<int> selectNodes{it};
    while (selectNodes.size() != nodes.size()) {
        vector<Edge> compareVector;
        for (auto s : selectNodes)
            for (auto &item : ways[s]) {
                if (find(selectNodes.begin(), selectNodes.end(), item.second.to.nodeid) == selectNodes.end())
                    compareVector.push_back(item.second);
            }
        sort(compareVector.begin(), compareVector.end(),
             [](Edge lhs, Edge rhs) -> bool { return lhs.perCost < rhs.perCost; });
        Edge beSelected = compareVector[0];
        selectNodes.push_back(beSelected.to.nodeid);
        for (const auto item : ways[beSelected.to.nodeid]) {
            auto i = item.first;
//                if(find(selectNodes.begin(),selectNodes.end(),i) == selectNodes.end())
//                {
            int r = costvv[it][beSelected.to.nodeid] + costvv[beSelected.to.nodeid][i];
            if (r < costvv[it][i]) {
                costvv[it][i] = r;
            }
//                }
        }
        compareVector.clear();
    }
}

void initDistance()
{
    for(auto& it : edger)
    {
        for(auto& item : it.second)
        {
            vector<int> v{};
            item.second.push_back(v);
        }
    }
}

void initializeRoadsScore(requestInfo& requestInfo,vector<int>& score)
{
    auto edges = edger[requestInfo.from][requestInfo.to];
    int scoreSum = 0;
    for(auto& it : edges)
    {
        for(int i = 1;i<edges.size();i++)
        {
            const Edge &edge = ways[it[i]][it[i-1]];
            scoreSum += (edge.maxBindWidth/edge.perCost);
        }
        score.push_back(scoreSum);
    }


}


void allocateRoad(vector<requestInfo>&infos,int &costsum, vector<vector<int>>& res,
        vector<requestInfo>& blocked,float threshold)
{
    for (auto &i : infos) {
        bool flag = false;
//        computeCosts(i);
        vector<int> score;
        initializeRoadsScore(i, score);
//        vector<int> v = costs[i.from][i.to];
        vector<int> v = score;
//        sort(v.begin(), v.end(),[](int lhs,int rhs)->bool{return lhs < rhs;});
        sort(score.begin(), score.end(), [](int lhs, int rhs) -> bool { return lhs > rhs; });
        vector<int> tmp = costs[i.from][i.to];
        vector<int> roads;
        int currentCost = 0;
//        for (auto x : v) {
        for (auto x : score) {
            int index = find(v.begin(), v.end(), x) - v.begin();
//            int index = find(tmp.begin(), tmp.end(), x) - tmp.begin();
            auto k = edger[i.from][i.to][index];
            map<int, int> recover;
            for (int j = 1; j < k.size(); j++) {
                Edge &edge = ways[k[j - 1]][k[j]];
                if (edge.curBindWidth - edge.perCost * i.equality > edge.maxBindWidth * threshold) {
                    recover[j] = edge.curBindWidth;
                    edge.curBindWidth -= edge.perCost * i.equality;

                    currentCost += edge.perCost * i.equality;
                    if (roads.empty()) {
                        roads.push_back(edge.from.nodeid);
                        roads.push_back(edge.to.nodeid);
                    } else {
                        if (roads[roads.size() - 1] != edge.from.nodeid) {
                            roads.push_back(edge.from.nodeid);
                        }
                        roads.push_back(edge.to.nodeid);
                    }
//                    cout << edge.from << "->" << edge.to << endl;
                    if (edge.to.nodeid == i.to) {
                        flag = true;
                        break;
                    }

                } else {
                    for (auto &rec : recover) {
                        Edge &edgetmp = ways[k[rec.first - 1]][k[rec.first]];
                        edgetmp.curBindWidth = rec.second;
                    }
                    currentCost = 0;
                    roads.clear();
                    break;
                }

            }
            if (flag)
                break;

        }
        costsum += currentCost;
        res[i.id] = roads;


        if (!flag) {
//            cout << i.id << "----------阻塞-----------" << endl;
            blocked.push_back(i);
        }
    }
}

void allocate(int costsum,vector<vector<int>>& res,
        vector<requestInfo>& block)
{
    float k = 0.8;
    vector<requestInfo> blocked2 = reqinfos;
    vector<requestInfo> blocked3;
    while(k>=0.2)
    {
        k=k-0.0001;
        allocateRoad(blocked2,costsum,res,blocked3,k);
        blocked2 = blocked3;
        cout << blocked2.size() << endl;
        blocked3.clear();
    }
    block = blocked3;
}
void initilizeGraph()
{
    for(auto& i : ways)
    {
        for(auto& j : i.second)
        {
            Edge& edge = j.second;
            edge.from.edges.push_back(edge);
            edge.
        }
    }
}

void getRoadFromNode(int fromid,int toid,deque<Node>& st)
{
    Node& from = nodes[fromid];
    Node& to = nodes[toid];

    vector<bool> visited(nodes.size(),false);
    visited[from.nodeid] = true;
    st.push_back(from);
    for(int i = 0;i<from.edges.size();i++)
    {
        if(from.nodeid == to.nodeid)
        {
            auto& road = edger[from.nodeid][to.nodeid];
            road.emplace_back();
            for(int j = 0;j < st.size();i++)
            {
                road[road.size()-1].push_back(st[st.size()-j-1].nodeid);
            }
            st.pop_back();
            visited[from.nodeid] = false;
            break;
        }
        if(!visited[i])
        {
            getRoadFromNode(i,toid,st);
        }
        if(i == from.edges.size()-1)
        {
            st.pop_back();
            visited[from.nodeid]=false;
        }
    }
}

int main()
{
    clear();
    readTxt();
    /**
     * 此处写自己代码
     */
    GenerateOriginalDistance();
    initilizeGraph();
    vector<vector<int>> res(reqinfos.size(),vector<int>{});
    int costsum=0;
    int count = 0;
    vector<requestInfo> blocked;
    deque<Node> st;
    getRoadFromNode(0,344,st);
    cout << 1 << endl;
//    allocate(costsum,res,blocked);



//    cout << costsum << endl;
//    for(int m = 0;m < res.size();m++) {
//        //writer.writeLine(to_string(reqinfos[m].id)+" "+to_string(reqinfos[m].equality));
//        cout << reqinfos[m].id << " " << reqinfos[m].equality << endl;
//        for (int n = 0; n < res[m].size() - 1; n++) {
//            cout << res[m][n]<< " ";
//            cout.flush();
//        }
//        cout << res[m][res[m].size() - 1] << endl;
////        for(auto n : res[m])
////        {
////            writer.write(to_string(n)+" ");
//////                cout << n << " ";
//////                cout.flush();
////        }
//        //writer.write("\n");
//    }
}