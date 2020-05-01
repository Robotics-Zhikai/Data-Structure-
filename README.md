# Data-Structure
This Repository store the basic data structure code practice;

数据结构与算法设计，数据结构与算法是无法割裂开的！

Mooc zju Data Structure Programming exercises after class.Yue chen etc.;浙江大学MOOC 陈越

https://www.icourse163.org/learn/ZJU-93001?tid=1450069451#/learn/announce

Mooc Tsinghua Data Structure Programming exercises after class.Junhui deng.;清华大学MOOC 邓俊辉

https://next.xuetangx.com/course/THU08091002048/1515966

北京大学算法设计与分析MOOC课程 屈婉玲

https://www.icourse163.org/learn/PKU-1002525003?tid=1002695005#/learn/announce

20200416 创建SortAlgorithm文件夹 冒泡排序 排序检测 

20200422 编写插入排序算法 构建检测类RandomData 与C++algorithm标准库的sort算法进行比较，发现冒泡、插入是标准库算法运行时间的1000倍

编写希尔排序算法，进一步提升效率，但是还是远不如C++algorithm标准库的sort算法，可以看下边的运行比较，需要注意的是，希尔排序是Sedgewick增量序列，int可能会有溢出，导致不能无限增加数量。希尔排序用的基本排序是插入排序。

排序10000个元素对比：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/%E5%86%92%E6%B3%A1%E6%8F%92%E5%85%A5%E5%B8%8C%E5%B0%94C%2B%2B%E5%AF%B9%E6%AF%94.png)

排序1000000个元素对比

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/C%2B%2B%E5%B8%8C%E5%B0%94.png)

20200423 Practice9 判断是否是同一颗二叉搜索树 二叉搜索树的插入、删除操作等

20200424 Practice10 堆的各种基本操作 封成了类，储存在.cpp .h 文件中 堆排序调用了这两个文件 堆的操作主要是插入删除，需要有一系列的调整，使得根部始终为最大或最小。之后如果有需要，可以直接弄这两个文件夹。 insert还没有测试 其他都测试了 都是成功的

更新SortAlgorithm文件夹，更新堆排序

排序12.5W个元素 包括500个相同元素的运行时间对比

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/12.5w%E5%B8%8C%E5%B0%94%E5%A0%86.png)

更新：至此测试完毕所有堆相关的.cpp .h文件，可以直接用了。测试的同时，更新了SortAlgorithm文件夹，利用insert的堆函数，对比了用不同方式建立堆的时间复杂度n 和 nlogn。从下图可以看到，慢速与快速的时间差，就是nlogn与n的差别

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/%E6%B5%8B%E8%AF%95insert%E5%A0%86.png)

20200425 归并排序的递归实现

20200426 归并排序的非递归实现

123456个随机元素，包括500个相同元素的运行时间对比 

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/5.png)

发现非递归实现比递归实现更慢

但当排序4086个元素时，非递归实现更快，对比代码可以发现，非递归相对于递归实现主要区别在于当组数不满足2的整数次幂时，非递归方式需要将多余的与最后一个序列进行融合，这就是很耗费时间的地方，而当4096个元素时，正好没有多余的，也就让非递归比递归快了。 

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/6.png)

20200427 实现快速排序，小于阈值时用递归的归并排序。修改插入排序、归并排序的入口参数，改为可以给定确定的范围排序。快速排序的入口参数有cutoff和cishu，前者决定调用归并排序的时机，后者决定快速排序采样的个数，2^cishu+1。下面给出一些测试案例：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/7.png)

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/8.png)

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/9.png)

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/10.png)

可以看到离C++的algorithm库的sort实现还是有一定的距离。

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/11.png)

暂时不知是何原因，快速排序在面对这样的数据时速度不如归并排序。

20200501 新建DivideAndConquer文件夹，存放分治策略相关算法。新建Note文件夹，存放学习笔记。

DivideAndConquer 实现了幂乘算法，常规的幂乘算法是O(n)的复杂度，用分治策略递归实现是O(logn)的复杂度。测试1.000000001的50051000001次方效果如下所示，可以看到，math库的powl和我自己写的logn运行时间是差不多的。据此可感受logn对于n的差距！！封装了一个Number类，可以按照常规的如n=2.1;n^3进行运算。

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/12.png)




