#include<bits/stdc++.h>
#include <algorithm>
// #include<Eigen/Eigen>
using namespace std;

struct Node
{
    int val;
    Node* left;
    Node* right;
    Node(int data): val(data){
    }
};

typedef pair<int ,int > pii;
pii compute(string s, int i){
    if(s[i] ==')') return pii{1, i};
    int ans =1;
    while (i< s.length() && s[i] !=')')
    {
        pii info = compute(s, i+1);
        ans *= info.first +1;
        i = info.second +1;
    }
    return {ans, i};
    
}

vector<int> arr(5);

bool check(int mid){
    int temp = mid -arr[0];
    int tot = 0;
    for(int i=0;i<5;i++){
        if(arr[i] - temp < 0) return 0;
        if(arr[0] + temp - arr[i] > 0 && i!=1){
            tot += (arr[0] + temp - arr[i]);
        }
    }
    if(tot <= arr[1] - temp) return true;
    else return false;
}
int main(){
    // string s = "35+6*70+5*6+10";
    // string s1 ="(())()()";
    // pii ans = compute(s1, 0);
    // cout << ans.first << "\n";
    // stack<string> q;
    // int cur =0;
    // for(int i = 0;i<s.size();i++){
    //     if(s[i] > '0' && s[i]<'9'){
    //         if(!q.empty()){
    //             if(q.top() == "*"){
    //                 q.pop();
    //                 cur = cur * stoi(q.top());
    //                 q.pop();
    //             }else if(q.top() == "+" || q.top() == "-"){
    //                 q.push(string(1,s[i]));
    //             }else{
    //                 cur  = cur*10 + s[i]-'0';
    //             }
    //         }else{
    //             cur  = cur*10 + s[i]-'0';
    //         }
    //         cout << cur << " ";
    //     }else if(s[i] == '+' || s[i] == '-'){
    //         q.push(to_string(cur));
    //         cur = 0;
    //         q.push(string(1,s[i]));
    //     }else{
    //         q.push(to_string(cur));
    //         q.push(string(1, s[i]));
    //         cur =0;
    //     }
    // }
    // cout << cur;

    // int T;
    // cin >> T;

    for(int i = 0;i<5;i++){
        cin >>arr[i];
    }
    sort(arr.begin(), arr.end());
    int res =-1;
    int l =0,r=1e12;
    while (l<=r)
    {
        int mid = l +(r-l)/2;
        if(check(mid)){
            l = mid + 1;
            res = mid;
        }else{
            r = mid -1;
        }
    }
    cout << res;
    // priority_queue<int, vector<int>, greater<int>> q;
    // for(int i =1;i<5;i++){
    //     q.push(arr[i]);
    // }
    // while (arr[0]!=0)
    // {
    //     auto t = q.top();
    //     t++;
    //     arr[0] --;
    //     q.pop();
    //     q.push(t);
    // }
    // cout<< q.top();
      
    return 0;
}
