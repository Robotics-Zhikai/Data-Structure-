#pragma once
#include "main.h"

/*
剑指 Offer 09. 用两个栈实现队列
用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，
分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 - 1)
*/
class CQueueOffer09 {
public:
	CQueueOffer09() {

	}

	void appendTail(int value) {
		left.push(value);
	}

	int deleteHead() { //对于每个元素来说，删除的复杂度是O(1)的，虽然看起来每次操作需要O(n)，但是就拿每个单独的元素来讲，只有插入和删除操作
		if (right.empty() == 1)
		{
			while (left.empty() == 0)
			{
				right.push(left.top());
				left.pop();
			}
		}

		if (right.empty() == 1)
			return -1;
		else
		{
			int tmp = right.top();
			right.pop();
			return tmp;
		}
	}

	stack<int> left;
	stack<int> right;
};

/*
剑指 Offer 31. 栈的压入、弹出序列
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如，序列 {1,2,3,4,5} 是某栈的压栈序列，
序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。

*/

class SolutionOffer31 {
public:
    bool ComplexMethod(vector<int>& pushed, vector<int>& popped){ //复杂的实现 这个是第一次想到的
        if (pushed.empty()&&popped.empty())
            return 1;
        else if (pushed.empty() || popped.empty())
            return 0;
        int poppedIndex = 0;
        int pushedIndex = -1;
        stack<int> pushStack;
        do{
            do{
                pushedIndex++;
                pushStack.push(pushed[pushedIndex]);
            }while((pushedIndex<pushed.size()-1) && poppedIndex<popped.size() && (pushed[pushedIndex]!=popped[poppedIndex]));
           
            while((!pushStack.empty()) && (poppedIndex<popped.size()) && (pushStack.top()==popped[poppedIndex])){
                
                pushStack.pop();
                poppedIndex++;
            }
        }while(pushedIndex<pushed.size()-1);
        if (pushStack.empty())
            return 1;
        else
            return 0;
    }
    bool EasyMethod(vector<int>& pushed, vector<int>& popped){ //简单的实现 这个是看题解的方法复现的
        stack<int> stackpushed;
        int popindex = 0;
        for(auto &n : pushed){ //主要是上边复杂的实现方法需要维护两个变量，而这个只需要维护一个变量，另一个变量被冒号表达式解决了
            stackpushed.push(n);
            while(!stackpushed.empty() && popindex<popped.size() && stackpushed.top()==popped[popindex]){
                stackpushed.pop();
                popindex++;
            }
        }   
        return stackpushed.empty();
    }
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        return EasyMethod(pushed,popped);
		return ComplexMethod(pushed,popped);
    }
};


/*
155. 最小栈
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) —— 将元素 x 推入栈中。
pop() —— 删除栈顶的元素。
top() —— 获取栈顶元素。
getMin() —— 检索栈中的最小元素。
*/
//leetcode 155
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int val) {
        if (MIN.empty())
            MIN.push(val);
        else if (MIN.top()>=val){
            MIN.push(val);
        }
        STACK.push(val);
    }
    
    void pop() {
        if (!MIN.empty() && MIN.top()==STACK.top()){
            MIN.pop();
        }
        STACK.pop();
    }
    
    int top() {
        return STACK.top();
    }
    
    int getMin() {    
        return MIN.top();
    }
private:
    stack<int> MIN;
    stack<int> STACK;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

//这个不用辅助栈的方法不太容易想到，要反复重点看！！！！
/*
这是不需要辅助栈的方法
stack用来存储和min的差值，min存储最小值，每次出栈的时候通过差值和当前min计算要出栈的值和之前的min
如果差值diff大于等于0，说明要出栈的值大于等于当前min，那么要出栈的值在入栈的时候没有更新min，返回min+diff；
如果差值diff小于0，说明当前要出栈的值就是min(因为入栈的时候我们选择的就是min和入栈元素的最小值)，同时，通过min-diff计算出之前min
要注意的是diff可能会超出int范围，类似于 Integer.MAX_VALUE - 1 这种，所以diff要用Long存
    
class MinStack {

    Integer min = null;
    Stack<Long> data = new Stack<>();

 
    public MinStack1() {

    }

    public void push(int x) {
        if (data.isEmpty()) {
            data.push(0L);
            min = x;
        } else {
            //如果x是最小的数，这里可能越界，所以用Long来保存
            data.push(Long.valueOf(x) - min); //push入的是diff
            min = Math.min(x, min); //更新min
        }
    }

    public void pop() {
        Long diff = data.pop();
        if (diff >= 0) {
            //return min + diff;
        } else {
            int res = min;
            min = (int) (min - diff); //每次pop都要更新一下min，以便min被之后元素改掉的能够被复原
            //return res;
        }
    }

    public int top() {
        Long diff = data.peek();
        if (diff >= 0) {
            return (int) (min + diff);
        } else {
            return min;
        }
    }

    public int getMin() {
        return min;
    }
}
*/

/*
//一种更容易理解的方法，但本质上还是每次都记录了之前的最小值，比辅助栈的方法甚至耗费空间会更多
class MinStack {
    private Node head;
    
    public void push(int x) {
        if(head == null) 
            head = new Node(x, x);
        else 
            head = new Node(x, Math.min(x, head.min), head);
    }

    public void pop() {
        head = head.next;
    }

    public int top() {
        return head.val;
    }

    public int getMin() {
        return head.min;
    }
    
    private class Node {
        int val;
        int min;
        Node next;
        
        private Node(int val, int min) {
            this(val, min, null);
        }
        
        private Node(int val, int min, Node next) {
            this.val = val;
            this.min = min;
            this.next = next;
        }
    }
}

*/

 /*
剑指 Offer 59 - I. 滑动窗口的最大值
给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 

  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

 */
//这个题与上边的最小栈结合起来看

class Solution59_I {
public:
    void MAXpush(int n )
    {
        if (MAX.empty())
            MAX.push_back(n);
        else if (n>=MAX.back()){
            MAX.push_back(n);
        }
    }
    void push(int n)
    {
        DEQ.push_back(n);
        MAXpush(n);
    }
    void pop()
    {
        if (!DEQ.empty() && !MAX.empty()){
            if (DEQ.front()==MAX.front()){
                MAX.pop_front();
            }
            DEQ.pop_front();

            //下边的这个for主要处理的情况是当新加入的值小于最大值时，push不会加入MAX，进而MAX不断从前边流失，
            //最终造成MAX流失为空，此时需要确定新的最大值，需要把deq中的数MAXpush到MAX中
            if(MAX.empty()){ //注意这里容易写错！！ 类比最小栈那个题，容易把这个for丢掉（因为最小栈那个不会从另一个方向流失元素）
                for(int i = 0;i<DEQ.size();i++){
                    MAXpush(DEQ[i]); //这就体现出双端队列的好处了，可以直接遍历
                }
            }
        }   
        
    }
    int getMAX()
    {
        return MAX.back();
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty())
            return nums;
        vector<int> res;
        for(int i = 0;i<k;i++){ //先把第一个窗口完整的弄满
            push(nums[i]);
        }
        
        res.push_back(getMAX());
        for(int base = 1;base<=nums.size()-k;base++){
            push(nums[base+k-1]);
            pop(); 
            res.push_back(getMAX());
        }
        return res;
    }


private:
    deque<int> MAX;
    deque<int> DEQ;
};


/*
剑指 Offer 59 - II. 队列的最大值
请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的**均摊**时间复杂度都是O(1)。

若队列为空，pop_front 和 max_value 需要返回 -1

*/

//这个跟上边的两个题大同小异
//重点是要记住做法 理解做法
class MaxQueue {
public:
    //要求的是均摊时间复杂度是O(1)，因此在某一操作中可能会出现操作了很多次，但是进过均摊分析可以把该
    //处的复杂度均摊到其他操作中（即其他操作可能操作的更少了）
    MaxQueue() {

    }
    
    int max_value() {
        if(MAX.empty())
            return -1;
        else    
            return MAX.back();
    }
    
    void MAXpush(int value)
    {
        if (MAX.empty()){
            MAX.push_back(value);
        }
        else if (value>=MAX.back()){
            MAX.push_back(value);
        }
    }
    void push_back(int value) {
        DEQ.push_back(value);
        MAXpush(value);
    }
    
    int pop_front() {
        if (!DEQ.empty() && !MAX.empty()){
            if(DEQ.front()==MAX.front()){
                MAX.pop_front();
            }
            int res = DEQ.front();
            DEQ.pop_front();

            if (MAX.empty()){ //重点是这一步，就需要用平摊分析来分析 。当发现MAX为空时，需要把DEQ中的元素MAXpush到MAX中
                for(int i = 0;i<DEQ.size();i++){
                    MAXpush(DEQ[i]);
                }
            }
            return res;
        }
        else   
            return -1;
    }
private:
    deque<int> DEQ;
    deque<int> MAX;
};


/*

739. 每日温度
请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。
如果气温在这之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。


*/

class Solution739 {
public:
    vector<int> solveMethod1(vector<int>& temperatures){
        //时间复杂度是n^2，空间复杂度是1，直接超时了
        //题解的暴力法没有这里的实现这么暴力，而是充分利用了[30,100]范围内的温度值的条件，然后从后往前遍历
        vector<int> res(temperatures.size(),0);
        for(int i = 0;i<temperatures.size();i++){
            for (int j = 1;i+j<temperatures.size();j++){
                if (temperatures[i+j]>temperatures[i]){
                    res[i] = j;
                    break;
                }
            }
        }
        return res;
    }
    vector<int> solveMethod2(vector<int>& temperatures){ 
        //用单调栈的方法 时间复杂度是n，因为每个元素进一次单调栈然后出一次单调栈（均摊分析的思想）
        //这个也是重点是思路，想通了很简单
        //可以跟着https://leetcode-cn.com/problems/daily-temperatures/solution/mei-ri-wen-du-by-leetcode-solution/ 这个里边的实际数据实例走一遍
        stack<int> staIndex; //下标的stack,因为要求的是下标的差，因此存储下标更有意义
        vector<int> res(temperatures.size(),0);
        for(int i = 0;i<temperatures.size();i++){
            while(!staIndex.empty() && temperatures[i]>temperatures[staIndex.top()]){
                res[staIndex.top()] = i-staIndex.top();
                //如果找到当前温度比栈顶大的，就一直往出弹，并能够得出结果
                staIndex.pop();
            }
            staIndex.push(i);
        }
        return res;
    }
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        return solveMethod2(temperatures);
    }
};


/*
581. 最短无序连续子数组
给你一个整数数组 nums ，你需要找出一个 连续子数组 ，
如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

请你找出符合题意的 最短 子数组，并输出它的长度。


*/

class Solution581 {
public:
    int solveMethod1(vector<int>& nums){
        //基础是插入排序，
        //然后记录插入排序过程中swap的最大index和最小index，进而right-left+1就得到了最终结果
        //这个复杂度是n^2，虽然有剪枝，但是本质上还是n^2
        int right = -1;
        int left = nums.size();
        int MINupper = INT_MAX;
        for(int i = 1;i<nums.size();i++){
            if (nums[i]>=nums[i-1])
                continue;
            if (nums[i]>=MINupper){ 
                //如果当前值大于最左侧边界，就不用swap多次了，swap一次后直接剪枝即可
                swap(nums[i],nums[i-1]);
                if (i>right)
                    right = i;
            }
            else{
                bool swapflag = 0;
                int j = i;
                for(;j>0;j--){
                    if (nums[j]<nums[j-1]){
                        if (j>right)
                            right = j;
                        swap(nums[j],nums[j-1]);
                        swapflag = 1;
                    }
                    else
                        break;
                }
                if (swapflag==1 && j<left){
                    left = j;
                    MINupper = nums[left];
                }
            }
        }
        if (right==-1)
            return 0;
        else    
            return right-left+1;
    }
    int solveMethod2(vector<int>& nums){
        //直接调用排序然后比较边界不一样的数，就是问题的解
        //这个排序的复杂度是nlogn
        //36ms 远远超过method1
        vector<int> copy = nums;
        sort(copy.begin(),copy.end());
        int left = -1;
        int right = -1;
        for(int i = 0;i<nums.size();i++){
            if (nums[i]!=copy[i]){
                left = i;
                break;
            }
        }
        for (int i = nums.size()-1;i>=0;i--){
            if (nums[i]!=copy[i]){
                right = i;
                break;
            }
        }
        if (left==-1 || right==-1){
            return 0;
        }
        else{
            return right-left+1;
        }
    }
    int solveMethod3(vector<int>& nums){
        //用单调栈的方法解决
        //这个不太好写 多写写！！！！
        //这个其实本质上还是method1中插入排序要找最左侧，只不过借助栈把没必要比较的都弹出去了
        //时间复杂度和空间复杂度都是n
        //有空间复杂度为1的解法，但是不太容易想到
        if (nums.empty() || nums.size()==1)
            return 0;
        stack<int> CorrectTOP; //栈的栈顶是迄今为止排序正确的 直接存放nums中的元素
    
        int left = INT_MAX; //存放最左侧下标
        for (int i = 0;i<nums.size();i++){
            while(!CorrectTOP.empty()&&CorrectTOP.top()>nums[i]){
                CorrectTOP.pop();
                if (CorrectTOP.size()<left)
                    left = CorrectTOP.size(); //这个反应了左侧下标的变化
            }
            CorrectTOP.push(nums[i]);
        }
        
        int right = INT_MAX; //存放最右侧下标
        while(!CorrectTOP.empty()){
            CorrectTOP.pop();
        }
        for (int i = nums.size()-1;i>=0;i--){
            while(!CorrectTOP.empty()&&CorrectTOP.top()<nums[i]){ //这个小于号容易写错成小于等于号
                CorrectTOP.pop();
                if (CorrectTOP.size()<right)
                    right = CorrectTOP.size();
            }
            CorrectTOP.push(nums[i]);
        }
        right = nums.size()-right;

        if (left==INT_MAX ||right==INT_MAX){
            return 0;
        }
        else 
            return right-left;

    }
    int findUnsortedSubarray(vector<int>& nums) {
        return solveMethod3(nums); //还是单调栈的套路
    }
};



/*
20. 有效的括号
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
*/

class Solution20 {
public:
    bool isValid(string s) {
        stack<char> sta;
        //如果s的长度为奇数的话，直接返回false，这样也算是一种剪枝
        for(char c:s){
            if (c==')'){
                while(!sta.empty() && sta.top()!='('){
                    if (sta.top()=='['||sta.top()=='{'){
                        return 0;
                    }
                    sta.pop();
                }
                if (!sta.empty()){
                    sta.pop();
                }
                else{ //注意加这个else的判断
                    return 0;
                }
            }
            else if (c==']'){
                while(!sta.empty() && sta.top()!='['){
                    if (sta.top()=='('||sta.top()=='{'){
                        return 0;
                    }
                    sta.pop();
                }
                if (!sta.empty()){
                    sta.pop();
                }
                else{
                    return 0;
                }
            }
            else if (c=='}'){
                while(!sta.empty() && sta.top()!='{'){
                    if (sta.top()=='['||sta.top()=='('){
                        return 0;
                    }
                    sta.pop();
                }
                if (!sta.empty()){
                    sta.pop();
                }
                else{
                    return 0;
                }
            }
            else{
                sta.push(c);
            }
            
        }
        if (sta.empty()){
            return 1;
        }
        else{
            return 0;
        }
    }
};


/*
剑指 Offer 39. 数组中出现次数超过一半的数字
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。
*/
class SolutionOffer39 {
public:
    /*
摩尔投票法找的其实不是众数，而是占一半以上的数。当数组没有超过一半的数，则可能返回非众数，比如[1, 1, 2, 2, 2, 3, 3]，最终返回3。

投票法简单来说就是不同则抵消，占半数以上的数字必然留到最后 可以用一个栈实现这个

    */
    int majorityElement(vector<int>& nums) {
        stack<int> STA;
        for(int i = 0;i<nums.size();i++){
            if (STA.empty()){
                STA.push(nums[i]);
            }
            else{
                if (nums[i]!=STA.top()){
                    STA.pop();
                }
                else{
                    STA.push(nums[i]);
                }
            }
        }
        return STA.top();
    }
};