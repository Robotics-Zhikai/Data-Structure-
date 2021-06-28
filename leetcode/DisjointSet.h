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


