#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

int main(){
    ifstream file("NE.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string contents(buffer.str());
    cout<<contents;
    file.close();
    return 0;
}