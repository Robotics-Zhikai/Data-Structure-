#pragma once
#include "main.h"

//并查集 

/*
200. 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。


*/
 
//如果仅仅想知道两个点之间是否是一个集合，那么用路径搜索的方式就很低效了，用并查集才高效
class UnionFind{ //并查集的基本实现
public:
    UnionFind(vector<vector<char>>& grid):_grid(grid),_parent(NUM(),-1),_rank(NUM(),-1){
        for (int i = 0;i<_parent.size();i++){
            if (grid[getRow(i)][getCol(i)]=='1'){
                _parent[i] = i;
                _rank[i] = 1;
            }
        }
    }
    int find(int x) //找到x的根节点并压缩路径
    {
        if (_parent[x]==x){
            return x;
        }
        return _parent[x]=find(_parent[x]);
    }
    void merge(int x,int y){ //合并两棵树
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty){
            return;
        }
        if(_rank[rootx]>_rank[rooty]){
            _parent[rooty] = rootx;
            _rank[rootx]+=_rank[rooty];
        }
        else if (_rank[rootx]<=_rank[rooty]){
            _parent[rootx] = rooty;
            _rank[rooty]+=_rank[rootx];
        }
    }
    int getCount(){ //用来得出最终有多少个集合
        int count = 0;
        for (int i = 0;i<_parent.size();i++){
            if (_parent[i]==i)
                count++;
        }
        return count;
    }

    int getRow(int one){
        return one/_grid[0].size();
    }
    int getCol(int one){
        return one%_grid[0].size();
    }
    int TransTOW2ONE(int row,int col){
        return row*_grid[0].size()+col;
    }
private:
    vector<vector<char>> _grid;
    vector<int> _parent;
    vector<int> _rank; //这里rank定义为树的结点树（而不是树高），为了保证尽可能使树矮
    int NUM(){
        return _grid.size()*_grid[0].size();
    }
};


class Solution200 {
public:
    void DFS(vector<vector<char>>& grid,vector<vector<bool>>& isvisit,int row,int col){
        if (row<0 || row>=grid.size() || col<0 || col>=grid[0].size()) //注意这个退出条件
            return;
        if (isvisit[row][col]==true)
            return;
        if (grid[row][col]=='1'){
            isvisit[row][col] = true; //这个是核心
        }
        else{
            return;
        }
        int left = col-1;
        int right = col+1;
        int down = row-1;
        int up = row+1;
        DFS(grid,isvisit,row,left);
        DFS(grid,isvisit,row,right);
        DFS(grid,isvisit,down,col);
        DFS(grid,isvisit,up,col);
    }

    int solveMethod1(vector<vector<char>>& grid){
        if (grid.size()==0)
            return 0;
        vector<vector<bool>> isvisit(grid.size(),vector<bool>(grid[0].size(),false));
        int res = 0;
        for (int i = 0;i<grid.size();i++){
            for(int j = 0;j<grid[i].size();j++){
                if (grid[i][j]=='1' && isvisit[i][j]==false){
                    DFS(grid,isvisit,i,j); //用DFS扫一遍，把连通的岛屿置isvisit为1
                    res++;
                }
            }
        }
        return res;
    }

    int solveMethod2(vector<vector<char>>& grid){
        UnionFind Union(grid);
        for(int i = 0;i<grid.size();i++){
            for (int j = 0;j<grid[i].size();j++){
                if (grid[i][j]=='1'){
                    grid[i][j] = '0';
                    if (i-1>=0 && grid[i-1][j]=='1'){
                        Union.merge(Union.TransTOW2ONE(i-1,j),Union.TransTOW2ONE(i,j)); //把周围的merge进去
                        // grid[i-1][j] = '0';//只有在表示已经把周围的全部处理完才会置0
                        //这里每次都置0的话是不对的
                    }
                    if (i+1<grid.size() && grid[i+1][j]=='1'){
                        Union.merge(Union.TransTOW2ONE(i+1,j),Union.TransTOW2ONE(i,j));
                        // grid[i+1][j] = '0';
                    }
                    if (j-1>=0 && grid[i][j-1]=='1'){
                        Union.merge(Union.TransTOW2ONE(i,j-1),Union.TransTOW2ONE(i,j));
                        // grid[i][j-1] = '0';
                    }
                    if (j+1<grid[0].size() && grid[i][j+1]=='1'){
                        Union.merge(Union.TransTOW2ONE(i,j+1),Union.TransTOW2ONE(i,j));
                        // grid[i][j+1] = '0';
                    }
                }
            }
        }
        return Union.getCount();
    }
    
    int numIslands(vector<vector<char>>& grid) {    
        return solveMethod2(grid);
    }
};


/*

128. 最长连续序列
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。


进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗？

*/


class UnionFind1{
public:
    UnionFind1(int SIZE):_parent(SIZE,-1),_rank(SIZE,1) 
    //注意这个构造函数，外界只需要给一个多大的集合就行，具体元素的值是什么不管
    {
        for(int i = 0;i<_parent.size();i++){
            _parent[i] = i; //首先自指
        }
    }
    
    //然后依据每个元素的index来进行分类

    int find(int x){ //这里的函数参数都应该是索引，不应该是索引对应的值
        if (x==_parent[x])
            return x;
        return _parent[x] = find(_parent[x]);
    }
    void merge(int x,int y){
        int rootx = find(x);
        int rooty = find(y);
        if (rootx==rooty)
            return;
        if (_rank[rootx]>_rank[rooty]){
            _parent[rooty] = rootx;
            _rank[rootx]+=_rank[rooty];
        }
        else{
            _parent[rootx] = rooty;
            _rank[rooty]+=_rank[rootx];
        }
    }
    int getSize(int x){
        return _rank[find(x)];
    }


private:
    vector<int> _parent; //在parent中索引为index的值就是索引为index的元素的父元素所在index
    vector<int> _rank; //同样是一个子树的结点大小
};


class Solution128 {
public:
    int solveMethod1(vector<int> & nums){ //用排序和单调栈的方法 时间复杂度是nlogn，空间复杂度是n
        if (nums.empty())
            return 0;
        sort(nums.begin(),nums.end());
        stack<int> sta;
        int MAX = INT_MIN;
        int count = 0;
        for (int i = 0;i<nums.size();i++){
            while(!sta.empty() && sta.top()+1!=nums[i]){
                sta.pop();
                count--;
            }
            sta.push(nums[i]);
            count++;
            if (count>MAX){
                MAX = count;
            }
        }
        return MAX;
    }
    int solveMethod2(vector<int>& nums){ //仍然是先排序然后计数
        if (nums.empty())
            return 0;
        sort(nums.begin(),nums.end());
        int MAX = INT_MIN;
        int curLen = 1;
        for (int i = 0;i<nums.size()-1;i++){
            if (nums[i+1]==nums[i]+1){
                curLen++;
            }
            else if (nums[i+1]==nums[i]){ //这个容易遗漏掉
                continue;
            }
            else{
                if (curLen>MAX){
                    MAX = curLen;
                }
                curLen = 1; //需要重头开始计数
            }
        }
        if (curLen>MAX){ //这个容易遗漏掉，可能会出现一直不更新MAX的情况
            MAX = curLen;
        }
        return MAX;
    }
    int solveMethod3(vector<int>& nums){
        //借助哈希表，时间复杂度就是n，空间复杂度也是n
        //这个不好从一开始往出想，但是想明白了很简单
        if (nums.empty())
            return 0;
        unordered_set<int> SET;
        for(int n:nums){
            SET.insert(n);
        }
        int MAX = INT_MIN;
        for (int n:SET){
            if (SET.find(n-1)!=SET.end()){ 
                //如果比他小一个的找到了，那就直接跳过.因为从比他小一个的数开始计算肯定大于从该数开始计算的值
                continue;
            }
            else{
                int i = 1;
                while(SET.find(n+i)!=SET.end()){
                    i++;
                }
                if (i>MAX){
                    MAX = i;
                }
            }
        }
        return MAX;
    }
    int solveMethod4(vector<int>& nums){
        //用并查集来做
        if (nums.empty())
            return 0;
        unordered_map<int,int> MAP;
        int index = 0;
        for (int n:nums){
            MAP[n] = index++;
        } //一方面这个是用来去重的，另一方面这个要建立一个index与值的对应关系

        UnionFind1 UNION(index);
        int res = 1;
        for(auto& m:MAP){
            auto found = MAP.find(m.first+1);
            if (found!=MAP.end()){
                UNION.merge(m.second,found->second); //把这两个下标的元素合并为一类
                res = max(res,UNION.getSize(m.second));
            }
        }
        return res;
    }
    int longestConsecutive(vector<int>& nums) {
        return solveMethod4(nums);
        return solveMethod3(nums);
        return solveMethod2(nums);
    }
};