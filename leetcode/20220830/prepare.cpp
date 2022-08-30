#include <algorithm>
#include <vector>
#include <string>
using namespace std;
class Solution15 {
public:
    int getNextNum(vector<int>&nums,int index,int op)
    {
        int i;
        if (op==1) {
            for (i = index+1; i<nums.size(); i++){
                if (nums[i]!=nums[index]){
                    return i;
                }
            }
        }
        else{
            for (i = index-1; i>=0; i--){
                if (nums[i]!=nums[index]){
                    return i;
                }
            }
        }
        return i;
    }
    vector<vector<int>> threeSum(vector<int>& nums) 
    {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        for (int i = 0; i<nums.size(); i++) {
            if (i>0 && nums[i]==nums[i-1]) {
                continue;
            }
            int left = i+1;
            int right = nums.size()-1;
            while(left<right) {
                while(left<right && nums[i]+nums[left]+nums[right]>0) {
                    right--;
                }
                while(left<right && nums[i]+nums[left]+nums[right]<0) {
                    left++;
                }
                while(left<right && nums[i]+nums[left]+nums[right]==0) {
                    res.push_back({nums[i],nums[left],nums[right]});
                    left = getNextNum(nums,left,1);
                    right = getNextNum(nums,right,-1);
                }
            }
        }
        return res;
    }
};

class Solution443 {
public:
    int compress(vector<char>& chars) {
        int textIndex = 0;
        int left = 0;
        while(left<chars.size()) {
            int right = left+1;
            while(right<chars.size() && chars[right]==chars[left]){
                right++;
            }
            int num = right-left;
            chars[textIndex] = chars[left];
            if (num>1){
                string numstr = to_string(num);
                for(auto c:numstr){
                    textIndex++;
                    chars[textIndex] = c;
                }
            }
            textIndex++;
            left = right;
        }
        return textIndex;
    }
};

class Solution46 {
public:
    vector<vector<int>> res;
    void DFS(vector<int>& nums,int depth,vector<bool>& isvisited,vector<int>& cur)
    {
        if (depth==nums.size()){
            res.push_back(cur);
            return;
        }
        for (int i = 0; i<nums.size(); i++) {
            if (isvisited[i]==true){
                continue;
            }
            
            cur.push_back(nums[i]);
            isvisited[i] = true;
            DFS(nums,depth+1,isvisited,cur);
            isvisited[i] = false;
            cur.pop_back();
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        res.clear();
        vector<bool> isvisited(nums.size(),false);
        vector<int> cur;
        DFS(nums,0,isvisited,cur);
        return res;
    }
};