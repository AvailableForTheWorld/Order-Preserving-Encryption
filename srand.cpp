#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    long long a,b;
    long long min_value,max_value;
    cout<<"请输入a,b的值"<<endl;
    cin>>a>>b;
    cout<<"请输入数据集的数值范围"<<endl;
    cin>>min_value>>max_value;
    int n;
    cout<<"请输入产生多少个数据："<<endl;
    cin>>n;
    ofstream wstream("result.txt",ios::ate);
    srand((unsigned)time(NULL));
    vector<long long>v;
    for(int i=0;i<n;++i){
        long long key = (rand()%(max_value-min_value))+min_value;
        long long value = a * key + b + rand()%(a-1);
        v.push_back(value);
        wstream<<key<<" "<<value<<endl;
    }
    sort(v.begin(),v.end());
    int c,d;
    while(true){
        cout<<"请输入查询的范围[c,d]"<<endl;
        cin>>c>>d;
        long long query_min=a * c + b  ,query_max = a * d + b + (a-1);
        cout<<"查询结果如下："<<endl;
        for(int i=0;i<n;++i){
            if(v[i]>=query_min&&v[i]<=query_max){
                cout<<v[i]<<endl;
            }else if(v[i]>query_max){
                break;
            }
        }
    }
    
    return 0;
}