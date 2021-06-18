#pragma once
#include "main.h"

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