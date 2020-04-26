# Data-Structure
This Repository store the basic data structure code practice;

Mooc zju Data Structure Programming exercises after class.Yue chen etc.;

Mooc Tsinghua Data Structure Programming exercises after class.Junhui deng.;

20200416 创建SortAlgorithm文件夹 冒泡排序 排序检测 

20200422 编写插入排序算法 构建检测类RandomData 与C++algorithm标准库的sort算法进行比较，发现冒泡、插入是标准库算法运行时间的1000倍

编写希尔排序算法，进一步提升效率，但是还是远不如C++algorithm标准库的sort算法，可以看下边的运行比较，需要注意的是，希尔排序是Sedgewick增量序列，int可能会有溢出，导致不能无限增加数量。希尔排序用的基本排序是插入排序。

排序10000个元素对比：

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/%E5%86%92%E6%B3%A1%E6%8F%92%E5%85%A5%E5%B8%8C%E5%B0%94C%2B%2B%E5%AF%B9%E6%AF%94.png)

排序1000000个元素对比

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/C%2B%2B%E5%B8%8C%E5%B0%94.png)

20200423 Practice9 判断是否是同一颗二叉搜索树 二叉搜索树的插入、删除操作等

20200424 Practice10 堆的各种基本操作 封成了类，储存在.cpp .h 文件中 堆排序调用了这两个文件。之后如果有需要，可以直接弄这两个文件夹。 insert还没有测试 其他都测试了 都是成功的

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

