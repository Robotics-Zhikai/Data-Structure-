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

20200424 Practice10 堆的各种基本操作 封成了类，储存在.cpp .h 文件中 堆排序调用了这两个文件。之后如果有需要，可以直接弄这两个文件夹。 inset还没有测试 其他都测试了 都是成功的

更新SortAlgorithm文件夹，更新堆排序

排序12.5W个元素 包括500个相同元素的运行时间对比

![image](https://github.com/Robotics-Zhikai/Data-Structure-/blob/master/image/12.5w%E5%B8%8C%E5%B0%94%E5%A0%86.png)

