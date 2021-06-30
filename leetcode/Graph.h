#pragma once
#include "main.h"
using namespace std;
/*
207. 课程表
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

*/

class Solution207 {
public:
    bool solveMethod1(int numCourses, vector<vector<int>>& prerequisites){
        //这是用迭代的方式实现，方法容易理解，而用递归的方式的话需要具备一定的抽象能力，能把问题抽象成求环
        map<int,int> inNum; //记录入度
        map<int,set<int>> outEdge; //这个就用vector<vector<int>>的邻接表形式存储就行，用map反而很复杂
        for (int i = 0;i<numCourses;i++){
            inNum[i] = 0;
        }
        for(int i = 0;i<prerequisites.size();i++){
            inNum[prerequisites[i][0]]++;
            outEdge[prerequisites[i][1]].insert(prerequisites[i][0]);
        }

        queue<int> zeroIn;
        for (auto& ele:inNum){ //先把所有入度为0的加入
            if (ele.second == 0){
                zeroIn.push(ele.first);
            }
        }
        int visited = 0;
        while(!zeroIn.empty()){
            int frontnum = zeroIn.front();
            set<int> Outset = outEdge[frontnum];
            for(auto& ele:Outset){
                inNum[ele]--;
                if (inNum[ele]==0){ //一旦有结点入度为0，就加入到队列中
                    zeroIn.push(ele);
                }
            }
            zeroIn.pop();
            visited++;
        }
        if (visited!=numCourses)
            return false;
        else 
            return true;
    }

    bool DFS(vector<vector<int>>& outEdge,int root,vector<bool>& isdead,vector<bool>& isvisit)
    {
        //写递归程序就是先写主要的递归部分，然后写边界条件，最后添加条件剪枝优化
        if (isvisit[root]==1)//说明有环
            return false;
        if (outEdge[root].empty()){ //说明没有任何可用边了，这个点以后再也不用访问了
            isdead[root] = 1;
            return true;
        }
        bool res = true;
        isvisit[root] = 1;
        for(int i = 0;i<outEdge[root].size();i++){
            int nextroot = outEdge[root][i];
            if (isdead[nextroot]==0){
                res = res && DFS(outEdge,nextroot,isdead,isvisit);
                if (res==0)
                    break;
            }
        }
        isdead[root] = 1;
        isvisit[root] = 0;
        return res;
    }
    //https://leetcode-cn.com/problems/course-schedule/solution/ke-cheng-biao-by-leetcode-solution/
    //递归实现是按照这个里边所示的图进行实现的
    bool solveMethod2(int numCourses, vector<vector<int>>& prerequisites){
        //用邻接表储存图的数据结构，然后用递归的方法求图中是否有环，如果有环说明这个课程安排不合理，
        //不满足拓扑排序
        vector<vector<int>> outEdge(numCourses,vector<int>{}); //根本不需要用map

        for(int i = 0;i<prerequisites.size();i++){
            outEdge[prerequisites[i][1]].push_back(prerequisites[i][0]);
        }
        vector<bool> isdead(numCourses,0);//注意这个isdead 的设计，能够避免重复计算
        vector<bool> isvisit(numCourses,0);
        for (int i = 0;i<numCourses;i++){
            if (isdead[i]==0 && !DFS(outEdge,i,isdead,isvisit)){
                return false;
            }
        }
        return true;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        return solveMethod2(numCourses,prerequisites); //这个的速度和耗费内存远快于迭代实现
    }
};


/*
399. 除法求值
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，
其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。
每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，
请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。
如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

*/

class Solution399 {
public:
    /*
        for (int k = 0; k < nvars; k++) {
            for (int i = 0; i < nvars; i++) {
                for (int j = 0; j < nvars; j++) {
                    if (graph[i][k] > 0 && graph[k][j] > 0) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                }
            }
        }
        作者：LeetCode-Solution
        链接：https://leetcode-cn.com/problems/evaluate-division/solution/chu-fa-qiu-zhi-by-leetcode-solution-8nxb/
        来源：力扣（LeetCode）
        著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。


    注意这个Floyd算法的计算顺序，固定中间点，然后枚举所有的i,j 
    而不是固定i,j枚举所有中间点
    后者会造成遗漏
    */
    bool DFS(const vector<vector<optional<double>>>& Graph,vector<bool>& isvisit,int curindex,int ENDindex,double & res){
        if (curindex==ENDindex)
            return 1;
        isvisit[curindex] = 1;
        for(int i = 0;i<Graph[curindex].size();i++){
            if (Graph[curindex][i].has_value() && isvisit[i]==0){
                if (DFS(Graph,isvisit,i,ENDindex,res)){
                    res*=Graph[curindex][i].value();
                    isvisit[curindex] = 0;
                    return 1;
                }
            }
        }
        isvisit[curindex] = 0;
        return 0;
    }
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_map<string,int> MAP;
        int index = 0;
        for(int i = 0;i<equations.size();i++){
            for(int j = 0;j<equations[i].size();j++){
                string& str = equations[i][j];
                if (MAP.find(str)==MAP.end()){
                    MAP[str] = index++; //对所有变量进行标号
                }
            }
        }
        
        vector<vector<optional<double>>> Graph(MAP.size(),vector<optional<double>>(MAP.size(),optional<double>{}));
        for (int i = 0;i<equations.size();i++){
            vector<string> & vecstr = equations[i];
            Graph[MAP[vecstr[0]]][MAP[vecstr[1]]] = values[i];
            Graph[MAP[vecstr[1]]][MAP[vecstr[0]]] = 1/values[i];
        } 
        //重点是要能够把本问题转化到图的数据结构 稍加思索就可知a/b等价于a结点有一条边指向b结点
        //然后任意结点之间是否可计算就可以通过找是否有一条通路来得到
        
        vector<bool> isvisit(queries.size(),0);
        vector<double> vecRes(queries.size(),-1);
        for (int i = 0;i<queries.size();i++){
            vector<string> & vecstr = queries[i];
            auto begin = MAP.find(vecstr[0]);
            auto end = MAP.find(vecstr[1]);
            if (begin==MAP.end()||end==MAP.end())
                continue;

            double res = 1;
            if (DFS(Graph,isvisit,begin->second,end->second,res)){
                vecRes[i] = res;
            }
        }
        return vecRes;

    }
    //还有一种并查集的方法，目前还理解不了，先从最简单的并查集的题目开始做起吧
};



