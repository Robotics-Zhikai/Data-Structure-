#pragma once
#include "main.h"

//双指针


/*
141. 环形链表
给定一个链表，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，
我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 
如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

如果链表中存在环，则返回 true 。 否则，返回 false 。
*/


// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution141 {
public:
    bool solveMethod1(ListNode* head){//32ms 11MB
        set<ListNode*> Unique; //n的空间复杂度
        ListNode* cur = head;
        while(cur!=NULL){
            if (Unique.find(cur)==Unique.end()){
                Unique.insert(cur);
            }
            else
                return 1;
            cur = cur->next;
        }
        return 0;
    }
    bool solveMethod2(ListNode* head){ //8ms 7.9MB
        ListNode* slow = head; //用快慢指针的方法做 如果有环，那么慢指针肯定会被快指针追上
        ListNode* fast = head;

        //慢指针每次移动一个结点，快指针每次移动两个结点
        //如果没有环，那么快指针绝不可能跟在慢指针的后边 但是有环的话就可能跟在了慢指针后边
        while(fast!=NULL){
            slow = slow->next;
            fast = fast->next!=NULL?fast->next->next:NULL;
            if (fast!=NULL && fast->next==slow)
                return 1;
        }
        return 0;
    }
    bool hasCycle(ListNode *head) {
        return solveMethod2(head);
    }
};

/*
142. 环形链表 II
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 
如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。

说明：不允许修改给定的链表。

进阶：

你是否可以使用 O(1) 空间解决此题？

*/

class Solution142 { //这个容易忘且不好往出想，要多复习这里用到的快慢指针的方法！！！
public:
    ListNode *detectCycle(ListNode *head) {
    //仍然用快慢指针，只不过要稍加数学推导，
    //见这个链接https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/huan-xing-lian-biao-ii-by-leetcode-solution/
    //同时需要注意的是，在推导过程中有一前提假设，就是慢指针肯定没有绕环形链表完整的一圈过。
    //因为快指针走的速度是慢指针速度的两倍，这样在慢指针走到整个链表长度的一半时就会和快指针相遇
    //因此，快指针走的路程a+n(b+c)+b=2(a+b),也就是等于2倍的慢指针走的路程
    //进而经过变换，得到(n-1)(b+c)+c = a。可以快慢指针相遇的地点为起始点，引入第三个指针找到链表开始入环的第一个结点
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast!=NULL){
            slow = slow->next;
            fast = fast->next!=NULL?fast->next->next:NULL;
            if (slow!=NULL && slow == fast){
                ListNode* ptr = slow;
                slow = head;
                while(slow!=ptr){
                    slow = slow->next;
                    ptr = ptr->next;
                }
                return slow;
            }
        }
        return NULL;
    }
};


/*
287. 寻找重复数
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。

*/

class Solution287 {
public:
    int solveMethod1(vector<int>& nums){
        sort(nums.begin(),nums.end());//不能排序，因为题目中要求必须不修改nums
        for (int i = 0;i<nums.size()-1;i++){
            if (nums[i]==nums[i+1])
                return nums[i];
        }
        return 0;
    }
    int solveMethod2(vector<int> & nums){
        //不修改nums，充分利用题目条件：给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n）
        //用二分法来做，说是二分法，其实就是每趟扫描剪枝掉绝不可能出现重复数的数集合
        //https://leetcode-cn.com/problems/find-the-duplicate-number/solution/er-fen-fa-si-lu-ji-dai-ma-python-by-liweiwei1419/
        int left = 1;
        int right = nums.size()-1; //[left,right]是可能出现重复数的范围
        int mid = (left+right)/2;  
        while(left<right){
            int cnt = 0;
            for(auto num:nums){
                if (num<=mid)
                    cnt++;
            }
            if (cnt>mid){ //意味着在nums中小于等于mid的数的数量比mid还大，那么肯定在[left,mid]区间有重复数
                right = mid; //说明重复数出现在[left,mid]区间
            }
            else{
                left = mid+1;
            }
            mid = (left+right)/2;  
        } //最终的时间复杂度是nlogn,空间复杂度是1
        return right;
    }
    int solveMethod3(vector<int> & nums){ //这个要能根据题中条件想到链表
        //用快慢指针的方法，每个nums的值表示指向的下一个结点的index，当有重复元素时，
        //表明重复元素的值所指向的index有两个元素指向该元素，也就是有一个环，用判断环形链表入口的三指针方法
        //把环形链表入口找到，即可找到重复的整数
        int slow = 0;
        int fast = 0;
        while(fast!=nums.size()){ //肯定有重复元素，这也就造成了这个while循环如果里边不return的话这个函数就不return了
            slow = nums[slow]; //slow指针每次移动一格
            fast = nums[nums[fast]]; //fast指针每次移动两格
            if (fast==slow){
                int ptr= slow;
                slow = 0;
                while(slow!=ptr){
                    slow = nums[slow];
                    ptr = nums[ptr];
                }
                return slow; //返回的是进入环形链表的index，正好是重复的值
            }
        }
        return 0;
    }

    int findDuplicate(vector<int>& nums) {
        return solveMethod3(nums); //时间复杂度是n，空间复杂度是1
        // return solveMethod2(nums);
    }
}; //注意这个不断优化的过程


/*
3. 无重复字符的最长子串
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。     
*/

class Solution3 {
public:
    int review(string s){
        if (s.empty()){
            return 0;
        }
        int left = 0;
        int right = 0;
        unordered_set<char> SET;
        int res = INT_MIN;

        while(right<s.size()){
            while(right<s.size() && SET.find(s[right])==SET.end()){
                SET.insert(s[right]);
                right++;
            }
            res = max(res,right-left);
            if(right<s.size()){
                while(SET.find(s[right])!=SET.end()){
                    SET.erase(s[left]);
                    left++;
                }
                SET.insert(s[right]);
                right++;
                res = max(res,right-left);
            }
        }
        return res;
    }
    int lengthOfLongestSubstring(string s) { //一遍过，一开始想的就是双指针的方法
        if (s.empty())
            return 0;
        int left = 0;
        int right = 1;
        int MAXlen = 1;

        while (right<s.size()){
            //下边的这个for空间复杂度是1，时间复杂度是n；可借助map unorderedmap来以空间换时间进而判断新加入的字符是否独特
            for(int i = left;i<right;i++){ //新扩展一个right，然后判断[left,right)内的数是否都与right的数不相同
                if (s[i]==s[right]){ //[left,right]内存放各字符肯定都互不相同的字符串
                    left = i+1;
                    break;
                }
            }
            MAXlen = right-left+1>MAXlen?right-left+1:MAXlen;
            right++;//不断扩展右边界
        }//本质上还是一种暴力的求解方法
        return MAXlen;
    }
};


/*
19. 删除链表的倒数第 N 个结点
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

进阶：你能尝试使用一趟扫描实现吗？

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution19 {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //第一次想到并通过的方法是双指针，时间复杂度是n，空间复杂度是1，这几乎是最优解法了
        //还可以用栈先进后出的方法，先把所有结点压栈，然后弹出第n个结点，就是倒数第n个结点，且栈顶元素就是倒数第n个结点的前置结点
        ListNode* firstBefore = nullptr;
        ListNode* first = head;
        ListNode* second = first;
        int i;
        for (i = 0;i<n && second!=nullptr;i++){
            second = second->next;
        } 
        if (i<n){
            return nullptr;
        }
        while(second!=nullptr){
            firstBefore = first;
            first = first->next;
            second = second->next;
        }
        if (firstBefore==nullptr){
            return first->next;
        }
        else{
            firstBefore->next = first->next;
            return head;
        }

        return nullptr;
    }
};


/*
11. 盛最多水的容器
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。
在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器。


*/
//同样也是双指针。重点是要想到这个思路
//这个题多看看！！！
class Solution11 {
public:
    int solveMethod1(vector<int>& height){
        //用暴力求解的方法，直接超时了 时间复杂度是n^2
        int MAX = INT_MIN;
        int MAXleftIndex = -1;
        int MAXrightIndex = -1;
        int MAXwaterlevel = -1;
        for(int i = 0;i<height.size();i++){
            int j = i+1;
            if (MAXleftIndex!=-1 && MAXrightIndex!=-1){ //加上这个剪枝后过了几个超时的例子，但是还是超时
                if (i>=MAXleftIndex && i<=MAXrightIndex && height[i]<=MAXwaterlevel){
                    j = MAXrightIndex+1;
                }
            } 
            for (j;j<height.size();j++){
                int waterlevel = min(height[i],height[j]);
                if (waterlevel*(j-i)>MAX){
                    MAX = waterlevel*(j-i);
                    MAXleftIndex = i;
                    MAXrightIndex = j;
                    MAXwaterlevel = waterlevel;
                }   
            }
        }
        return MAX;
    }
    int solveMethod2(vector<int>& height){
        //用双指针的方法，一开始指向最靠边的两个边界，然后不断回缩，直到两边界回缩相遇
        //具体回缩的方法是回缩挡板长度小的那个。因为如果回缩长的那个，回缩后装的水肯定不如原来的
        //回缩短的那个还可能超出原来的MAX
        //https://leetcode-cn.com/problems/container-with-most-water/solution/sheng-zui-duo-shui-de-rong-qi-by-leetcode-solution/
        int leftindex = 0;
        int rightindex = height.size()-1;
        int MAX = INT_MIN;
        int cur;
        while(leftindex!=rightindex){
            if ((cur=(rightindex-leftindex)*min(height[leftindex],height[rightindex]))>MAX)
                MAX = cur;
            if (height[leftindex]<=height[rightindex]){
                leftindex++;
            }
            else{
                rightindex--;
            }
        }
        return MAX;
    }
    int maxArea(vector<int>& height) {
        return solveMethod2(height);
    }
};


/*
15. 三数之和
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

*/
//这个用到了两数之和的O(n)求解方法
//https://leetcode-cn.com/problems/3sum/solution/pai-xu-shuang-zhi-zhen-zhu-xing-jie-shi-python3-by/
//https://leetcode-cn.com/problems/3sum/solution/san-shu-zhi-he-by-leetcode-solution/ 
//两个链接结合起来看
class Solution15 {
public:
    vector<vector<int>> solveMethod1(vector<int>& nums) {
        //算是暴力枚举加剪枝
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        for (int i = 0;i<nums.size();i++){
            if (i>0 && nums[i]==nums[i-1]){ //避免重复
                continue;
            }
            if (nums[i]>0) //加这样的一个剪枝仍然超时
                break;
            for (int j = i+1;j<nums.size();j++){
                if (j>i+1 && nums[j]==nums[j-1]){ //避免重复
                    continue;
                }
                if (nums[i]+nums[j]>0)
                    break;
                for (int k = j+1;k<nums.size();k++){
                    if (k>j+1 && nums[k]==nums[k-1]){ //避免重复
                        continue;
                    }
                    if (nums[i]+nums[j]+nums[k]>0)
                        break;
                    if (nums[i]+nums[j]+nums[k]==0){
                        res.push_back({nums[i],nums[j],nums[k]});
                    }
                }
            }
        }
        return res;
    }

    vector<vector<int>> solveMethod2(vector<int>& nums) {
        //复杂度由method1的n^3降到了n^2
        vector<vector<int>> res;
        sort(nums.begin(),nums.end()); //nlogn
        for (int i = 0;i<nums.size();i++){ //n^2
            if (i>0 && nums[i]==nums[i-1]){
                continue;
            }
            if (nums[i]>0)  //因为已经经过排序了，所以nums[i]>0的话就直接退出
                break;
            int leftptr = i+1;
            int rightptr = nums.size()-1;
            while(leftptr<rightptr){ 
                //这里用双指针，实际上经过排序后的数列，求两数之和不用n^2枚举，用这里的双指针方法n的复杂度就能找到(如果包括排序的话是nlogn的复杂度)。
                //可见LeetCode1 两数之和
                if (nums[leftptr]+nums[rightptr]+nums[i]>0){
                    do{ //去除重复
                        rightptr--;
                    }while(rightptr>=0 && nums[rightptr]==nums[rightptr+1]);
                }
                else if (nums[leftptr]+nums[rightptr]+nums[i]<0){
                    do{
                        leftptr++;
                    }while(leftptr<nums.size() && nums[leftptr]==nums[leftptr-1]);
                }
                else{ //找到一个等于0的，然后需要同时动两头的指针才可能找到
                    res.push_back({nums[i],nums[leftptr],nums[rightptr]});
                    do{
                        leftptr++;
                    }while(leftptr<nums.size() && nums[leftptr]==nums[leftptr-1]);
                    do{
                        rightptr--;
                    }while(rightptr>=0 && nums[rightptr]==nums[rightptr+1]);
                }
            }
        }
        return res;
    }

    vector<vector<int>> solveMethod3(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        auto numsbeg = nums.begin();
        for (int i = 0;i<nums.size();i++){
            if (i>0 && nums[i]==nums[i-1]){
                continue;
            }
            if (nums[i]>0)  //因为已经经过排序了，所以nums[i]>0的话就直接退出
                break;
            int leftptr = i+1;
            int rightptr = nums.size()-1;
            while(leftptr<rightptr){
                int curres = *(numsbeg+leftptr)+*(numsbeg+rightptr)+*(numsbeg+i);
                if (curres>0){
                    do{
                        rightptr--;
                    }while(rightptr>=0 && *(numsbeg+rightptr)==*(numsbeg+rightptr+1));
                }
                else if (curres<0){
                    do{
                        leftptr++;
                    }while(leftptr<nums.size() && *(numsbeg+leftptr)==*(numsbeg+leftptr-1));
                }
                else{
                    res.push_back({nums[i],*(numsbeg+leftptr),*(numsbeg+rightptr)});
                    do{
                        leftptr++;
                    }while(leftptr<nums.size() && *(numsbeg+leftptr)==*(numsbeg+leftptr-1));
                    do{
                        rightptr--;
                    }while(rightptr>=0 && *(numsbeg+rightptr)==*(numsbeg+rightptr+1));
                }
            }
        }
        return res;
    }


    vector<vector<int>> threeSum(vector<int>& nums) {
        return solveMethod2(nums);
        return solveMethod3(nums); 
        //method3和method2用到的方法完全一样，只不过method3没有用[],
        //而是用的解引用*。神奇的是，method3在LeetCode提交的运行时间较method2由112ms提升到了60ms
        //暂时还不知为何
    }
};


/*
31. 下一个排列
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间。

示例 1：

输入：nums = [1,2,3]
输出：[1,3,2]
示例 2：

输入：nums = [3,2,1]
输出：[1,2,3]
示例 3：

输入：nums = [1,1,5]
输出：[1,5,1]
示例 4：

输入：nums = [1]
输出：[1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

//如果不做的话可能面试时候想不到，因此要多复习这里的思路
class Solution31 {
public:
    void review(vector<int>& nums){
        int guaiindex = 0;
        for(int i = nums.size()-1;i>0;i--){
            if (nums[i-1]<nums[i]){
                guaiindex = i;
                break;
            }
        }
        if (guaiindex==0){
            reverse(nums.begin(),nums.end());
        }
        else{
            int swapindex = guaiindex;
            for(int i = guaiindex;i<nums.size();i++){
                if (nums[i]>nums[guaiindex-1]){
                    swapindex = i;
                }
                else{
                    break;
                }
            }
            swap(nums[swapindex],nums[guaiindex-1]);
            reverse(nums.begin()+guaiindex,nums.end());
        }
    }
    void nextPermutation(vector<int>& nums) {
        int index = -1;
        for(int i = nums.size()-2;i>=0;i--){
            if (nums[i]<nums[i+1]){
                index = i;
                break;
            }
        } //逆序找到第一个升序的数
        if (index!=-1){
            for (int i = nums.size()-1;i>index;i--){
                if (nums[i]>nums[index]){
                    swap(nums[i],nums[index]);
                    break;
                }
            } //如果找到那么把右边的"第一次”大于它的数进行交换
        }
        
        int l = index+1;
        int r = nums.size()-1;
        while(l<r){
            swap(nums[l],nums[r]);
            l++;
            r--;
        } //最后把右半段逆序排列
        
    }
};


/*
75. 颜色分类
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
*/

class Solution75 {
public:
    void solveMethod1(vector<int>& nums){
        //并非是一趟扫描排好的
        vector<int> count(3,0);
        for (auto &n:nums){
            count[n]++;
        }
        for (int i = 0;i<count[0];i++){
            nums[i] = 0;
        }
        for (int i = count[0];i<count[0]+count[1];i++){
            nums[i] = 1;
        }
        for (int i = count[0]+count[1];i<count[0]+count[1]+count[2];i++){
            nums[i] = 2;
        }
    }
    void solveMethod2Review(vector<int>& nums){
        int ptr0 = 0;
        int ptr1 = 0;
        for(int i = 0;i<nums.size();i++){
            if (nums[i]==0){
                swap(nums[i],nums[ptr0]);
                if (ptr0==ptr1){
                    ptr0++;
                    ptr1++; 
                    //只要有ptr0++的地方必然有ptr1++，没有ptr0++的地方也有ptr1++的存在，因此ptr1肯定大于ptr0
                }
                else{
                    ptr0++;
                    swap(nums[i],nums[ptr1++]);
                }
            }
            else if (nums[i]==1){
                swap(nums[i],nums[ptr1++]);
            }
        }
    }
    
    void solveMethod2(vector<int>& nums){
        //用双指针的方法进行一趟扫描排序
        //https://leetcode-cn.com/problems/sort-colors/solution/yan-se-fen-lei-by-leetcode-solution/
        //方法二的双指针方法过一遍动画就懂了 这个比较好理解
        int ptr0 = 0; //指向序列0的下一个位置
        int ptr1 = 0; //指向序列1的下一个位置
        for (int i = 0;i<nums.size();i++){
            if (nums[i]==0){
                swap(nums[i],nums[ptr0]);
                if (ptr1 == ptr0){
                    ptr0++;
                    ptr1++;
                }
                else{
                    ptr0++;
                    swap(nums[i],nums[ptr1++]);
                }
            }
            else if (nums[i]==1){
                swap(nums[i],nums[ptr1++]);
            }
        }
    }
    void sortColors(vector<int>& nums) {
        solveMethod2(nums);
    }
};

/*
剑指 Offer 57. 和为s的两个数字
输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。如果有多对数字的和等于s，则输出任意一对即可。

*/
class SolutionOffer57 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        while(left<right){
            while (left<right && nums[left]+nums[right]>target){
                right--;
            }
            if (left<right && nums[left]+nums[right]==target){
                return vector<int>{nums[left],nums[right]};
            }
            while (left<right && nums[left]+nums[right]<target){
                left++;
            }
        }
        return {};
    }
};

/*
剑指 Offer 58 - I. 翻转单词顺序
输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。
*/
class SolutionOffer58I {
public:
    string reverseWords(string s) {
        int right = s.size()-1;
        int left = right;
        vector<string> vecstr;
        while(left>=0 && right>=0){
            while(right>=0 && s[right]==' '){
                right--;
                left--;
            }
            while(left>=0 && s[left]!=' '){
                left--;
            }
            if (right>=0)
                vecstr.push_back(s.substr(left+1,right-left));
            right = left;
        }
        string res;
        for(auto str:vecstr){
            for(char c:str){
                res.push_back(c);
            }
            res.push_back(' ');
        }
        res.pop_back();
        return res;
    }
};


/*
209. 长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，
并返回其长度。如果不存在符合条件的子数组，返回 0 。

*/

class Solution209 {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        //n的时间复杂度 滑动窗口 双指针 先不断增大 然后再不断减小 右边界负责增大 左边界负责减小
        int left = 0;
        int right = 0;
        int res = INT_MAX;

        int sum = 0;

        while(right<nums.size() && left<=right){
            while(right<nums.size() && sum<target){
                sum+=nums[right++];
            }

            while(left<=right && sum>=target){
            
                if (right-left < res){
                    res = right-left;
                }
                sum-=nums[left++];
            }
        }
        return res==INT_MAX?0:res;
        
        
    }
};


/*
349. 两个数组的交集
给定两个数组，编写一个函数来计算它们的交集。

*/
class Solution349 {
public:
    vector<int> solveMethod1(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> SET1;
        unordered_set<int> SET2;
        for(int n:nums1){
            SET1.insert(n);
        }
        for(int n:nums2){
            SET2.insert(n);
        }
        vector<int> res;
        for(int n:SET1){
            if (SET2.find(n)!=SET2.end()){
                res.push_back(n);
            }
        }
        return res;
    }
    vector<int> solveMethod2(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int pointer1 = 0;
        int pointer2 = 0;
        vector<int> res;
        while(pointer2<nums2.size() && pointer1<nums1.size()){
            bool flag = 0;
            while(pointer1<nums1.size() && nums1[pointer1]<=nums2[pointer2]){
                if (nums1[pointer1]==nums2[pointer2] && !flag){
                    flag = 1;
                    res.push_back(nums2[pointer2]);
                }
                pointer1++;
            }
            pointer2++;
        }
        return res;
    }
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        return solveMethod2(nums1,nums2);
    }
};

/*
18. 四数之和
给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。
请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]] ：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。

*/
class Solution18 {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size()<4){
            return {};
        }
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for(int i = 0;i<nums.size()-3;i++){
            if (i>0 && nums[i]==nums[i-1]){
                continue;
            }
            for(int j = i+1;j<nums.size()-2;j++){
                if (j>i+1 && nums[j]==nums[j-1]){
                    continue;
                }
                int newtarget = target-(nums[i]+nums[j]);
                int left = j+1;
                int right = nums.size()-1;
                
                while(left<right){
                    if (nums[left]+nums[right]<newtarget){
                        left++;
                    }
                    else if (nums[left]+nums[right]>newtarget){
                        right--;
                    }
                    else{
                        if (left>j+1 && nums[left]==nums[left-1] && right<nums.size()-1 && nums[right]==nums[right+1]){
                        }
                        else{
                            res.push_back(vector<int>{nums[i],nums[j],nums[left],nums[right]});
                        }
                        left++;
                        right--;
                    }
                }
            }
        }
        return res;
    }
};


/*
443. 压缩字符串
给你一个字符数组 chars ，请使用下述算法压缩：

从一个空字符串 s 开始。对于 chars 中的每组 连续重复字符 ：

如果这一组长度为 1 ，则将字符追加到 s 中。
否则，需要向 s 追加字符，后跟这一组的长度。
压缩后得到的字符串 s 不应该直接返回 ，需要转储到字符数组 chars 中。需要注意的是，
如果组长度为 10 或 10 以上，则在 chars 数组中会被拆分为多个字符。

请在 修改完输入数组后 ，返回该数组的新长度。

你必须设计并实现一个只使用常量额外空间的算法来解决此问题

*/
class Solution443 {
public:
    int compress(vector<char>& chars) {
        int valid = 0;
        int cur = 0;

        while(cur<chars.size()){
            char curchar = chars[cur];
            int count = 0;
            while(cur<chars.size() && chars[cur]==curchar){
                count++;
                cur++;
            }
            string charNum = to_string(count);
            chars[valid++] = curchar;
            if (count!=1){
                for(char c:charNum){
                    chars[valid++] = c;
                }
            }
        }
        int popsize = chars.size()-valid;
        for(int i = 0;i<popsize;i++){
            chars.pop_back();
        }
        return valid;
    }
};