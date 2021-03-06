# Data-Structure
This Repository store the basic data structure code practice;

数据结构与算法设计，数据结构与算法是无法割裂开的！

Mooc zju Data Structure Programming exercises after class.Yue chen etc.;浙江大学MOOC 陈越

https://www.icourse163.org/learn/ZJU-93001?tid=1450069451#/learn/announce

Mooc Tsinghua Data Structure Programming exercises after class.Junhui deng.;清华大学MOOC 邓俊辉

https://next.xuetangx.com/course/THU08091002048/1515966

北京大学算法设计与分析MOOC课程 屈婉玲

https://www.icourse163.org/learn/PKU-1002525003?tid=1002695005#/learn/announce

## 20200416 

创建SortAlgorithm文件夹 冒泡排序 排序检测 

## 20200422 

编写插入排序算法 构建检测类RandomData 与C++algorithm标准库的sort算法进行比较，发现冒泡、插入是标准库算法运行时间的1000倍

编写希尔排序算法，进一步提升效率，但是还是远不如C++algorithm标准库的sort算法，可以看下边的运行比较，需要注意的是，希尔排序是Sedgewick增量序列，int可能会有溢出，导致不能无限增加数量。希尔排序用的基本排序是插入排序。

排序10000个元素对比：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/%E5%86%92%E6%B3%A1%E6%8F%92%E5%85%A5%E5%B8%8C%E5%B0%94C%2B%2B%E5%AF%B9%E6%AF%94.png)

排序1000000个元素对比

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/C%2B%2B%E5%B8%8C%E5%B0%94.png)

## 20200423 

Practice9 判断是否是同一颗二叉搜索树 二叉搜索树的插入、删除操作等

## 20200424 

Practice10 堆的各种基本操作 封成了类，储存在.cpp .h 文件中 堆排序调用了这两个文件 堆的操作主要是插入删除，需要有一系列的调整，使得根部始终为最大或最小。之后如果有需要，可以直接弄这两个文件夹。 insert还没有测试 其他都测试了 都是成功的。

更新SortAlgorithm文件夹，更新堆排序

排序12.5W个元素 包括500个相同元素的运行时间对比

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/12.5w%E5%B8%8C%E5%B0%94%E5%A0%86.png)

更新：至此测试完毕所有堆相关的.cpp .h文件，可以直接用了。测试的同时，更新了SortAlgorithm文件夹，利用insert的堆函数，对比了用不同方式建立堆的时间复杂度n 和 nlogn。从下图可以看到，慢速与快速的时间差，就是nlogn与n的差别

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/%E6%B5%8B%E8%AF%95insert%E5%A0%86.png)

## 20200425 

归并排序的递归实现

## 20200426 

归并排序的非递归实现

123456个随机元素，包括500个相同元素的运行时间对比 

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/5.png)

发现非递归实现比递归实现更慢

但当排序4086个元素时，非递归实现更快，对比代码可以发现，非递归相对于递归实现主要区别在于当组数不满足2的整数次幂时，非递归方式需要将多余的与最后一个序列进行融合，这就是很耗费时间的地方，而当4096个元素时，正好没有多余的，也就让非递归比递归快了。 

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/6.png)

## 20200427 

实现快速排序，小于阈值时用递归的归并排序。修改插入排序、归并排序的入口参数，改为可以给定确定的范围排序。快速排序的入口参数有cutoff和cishu，前者决定调用归并排序的时机，后者决定快速排序采样的个数，2^cishu+1。下面给出一些测试案例：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/7.png)

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/8.png)

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/9.png)

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/10.png)

可以看到离C++的algorithm库的sort实现还是有一定的距离。

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/11.png)

暂时不知是何原因，快速排序在面对这样的数据时速度不如归并排序。

## 20200501 

新建DivideAndConquer文件夹，存放分治策略相关算法。新建Note文件夹，存放学习笔记。

DivideAndConquer 实现了幂乘算法，常规的幂乘算法是O(n)的复杂度，用分治策略递归实现是O(logn)的复杂度。测试1.000000001的50051000001次方效果如下所示，可以看到，math库的powl和我自己写的logn运行时间是差不多的。据此可感受logn对于n的差距！！封装了一个Number类，可以按照常规的如n=2.1;n^3的复杂度进行运算。

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/12.png)

## 20200519
看来文件分级还是挺重要的，不分级查找时n的复杂度 分级logn的复杂度

新建Graph文件夹，存储图相关的数据结构练习。

添加Graph/Practice1,并添加代码。visualization的OpenGL可视化函数的头文件有修改。

## 20200520
更新Graph/Practice1

修改visualization.h visualization.cpp 更新了函数名，并新添了一个绘制带箭头直线的功能，可以调整箭头在直线的位置，也可以调整箭头的长度，夹角，粗度。

更新了ConvexHull.cpp，添加了Point的几个重载函数，可以做除法加法，norm取模

更新了Graph.cpp Graph.h，创建存储图的邻接矩阵的数据结构，创建图的可视化函数

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/13.png)
![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/14.png)
![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/15.png)

## 20200521
创建领接表与邻接矩阵相互转换的函数

创建插入节点函数 插入边函数 

由于节点不是所有情况下都是以坐标点的形式存在，所以修改typedef Point GraphNode;//节点不只有位置的形式，还可能是机器人的状态，以后只需改Point即可改数据类型，只不过对于可视化会出现问题。

## 20200523
修改插入边函数，为了更广泛的适应需求，将insert改做update，既能插入边，又能更新值。领接表与邻接矩阵的实现方式是截然不同的。

定义了重载函数，使得领接表类可以直接等于邻接矩阵类，邻接矩阵类可以直接等于领接表类。也可以本类赋值。直接用=即可

## 20200531 
编写DFS函数，有一个等号的运算符重载函数不能用，不知道为啥；开始写空心框的可视化函数，以便可以直观地显示DFS、BFS的正确性。

## 20200601
编写空心框可视化函数，用于DFS显示；删除等号运算符重载函数，否则在调用GraphAdjList TransferMat2List(GraphAdjMat Mat)等带有赋值的函数时会出现错误。C++在赋值时不光有值的赋值，还有其他操作，最好不要自己定义赋值重载函数。

实现mat格式的DFS递归非递归，BFS非递归遍历。测试时BFS、DFS、DFSNotrecur同时测试，用已经实现的空心框可视化函数对正确性进行检验，正常情况下所有遍历的最小连通子集里的所有节点都有三个框，见下图：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/16.png)

## 20200603
实现领接表形式的遍历算法，修改领接表的元素结构为新的更广的地址，这样可以在实现遍历算法时减少复杂度。

## 20200604 
完成同样的BFS DFS，领接表形式更快。测试485个节点的图，取相同的一点进行遍历，有如下结果：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/17.png)

更新update value函数，更新insert node 函数，添加deletenode函数 用到了容器的erase函数。

## 20200608 0609 06010 0611 0612 0613
毕业季

## 20201022
开始继续维护这个仓库，修改了普遍采用的函数的兼容性问题。

## 20201023
主要基于邻接表的数据结构，实现了图的Dijkstra算法和路径的可视化，连通性、出入度的计算、最短路径的计算等。开始着手要写basic-wheel的更新脚本，涉及到文件的树状遍历。

某一节点到某一节点的最短路径的可视化：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/18.png)

## 20201024
实现Floyd算法，添加了能够产生任意给定节点和边的图生成函数。并对程序的严谨性进行了确保。

## 20201025 26
在Graph/Practice中改进Heap的实现，运用了模板，实现算法与数据的分离。并利用Heap对Dijkstra进行了改进。
## 20201028
完成图的部分算法和template Heap模板类
## 20201105
实现prim最小生成树算法 思考如何在模板中调用“<类型>” 类型中的成员数据 这样可以把graph的可视化和相关算法分开