#include<iostream>
#include<fstream>
#include<set>
#include<numeric>

int main(){
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");



    if(!fin.is_open()){
        std::cout<<"File was not opened";
        return 0;
    }
    std::set<long long> set;
    while(fin.peek()!=EOF){
        int a;
        fin>>a;
        set.insert(a);
    }
    fin.close();

    long long result=0;
    for(auto iter = set.begin(); iter!=set.end(); ++iter){
        result+=*iter;
    }

    fout<<result;
    fout.close();
    return 0;
}
